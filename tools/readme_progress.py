#!/usr/bin/env python3
"""Render the README progress card and the Discord post: the road to a finished decomp.

Finished means the whole game is built from readable source, builds the normal
way, and plays. The card asks two questions; every figure states what it
divides by (README, "How each figure is measured"), and every one comes from
the repository at a commit or from a recorded census row: no clock enters a
figure and nothing is predicted.

Does it work?
  Byte match          progress.py's BYTE-MATCHED: everything that rebuilds to
                      the original's exact bytes (our C++, library source,
                      generated C++, attached prebuilt libraries, reviewed
                      assembly, verified .text data), over all non-padding
                      .text bytes. Program code only: the note beside it reads
                      "game data & assets: not measured yet" until the image
                      ownership history (tools/image_ownership.py record) holds
                      a row, then that row's share of the image that is ours.
  Linking             the census's LINKING: executable game code in units that
                      link cleanly, over the census tree's executable game code
                      (one census snapshot; it holds still between censuses).
                      Units linking under census rules is not a normal build,
                      so the caption counts every problem the newest census
                      recorded (progress.link_problems: unresolved names,
                      hard-coded addresses, duplicate names, losing COMDAT
                      copies, wrongly selected providers). While
                      tools/link_census.py measures under rules the newest row
                      was not measured under, that row predates a rule change:
                      the row shows "being re-measured", not a change.
  Next milestone      the first normal build, then the first playtest. It moves
                      on only on a record of the exit test (a whole-program link
                      with no /FORCE and no stubs); no census or link_cycle
                      record shows one yet, so it stays put (MILESTONE).

Is the source clean?
  Hand-written code   authored C++ over executable game code (progress.py's
                      AUTHORED C++). GAME CODE C++*, which also counts generated
                      C++ and retained assembly, says how the code is stored,
                      not whether the game works; progress.py prints it, the
                      card does not.
  Readable names      declared names that are not placeholders (name_metric).
  Shortcuts removed   escape-hatch items retired since Phase 2 began, from
                      reverse/hatch_baseline.tsv (asm_bytes, a byte count, apart).
  Original file layout  (files then - files now) / (files then - TUs), files the
                      .cpp/.c/.asm under Code/, TUs the count the committed
                      reverse/tu_map.csv names (an estimate).
  Shared class definitions  duplicate private class copies removed since Phase 2
                      began (progress.class_copies_at).
"Then" is progress.PHASE2_START; progress.phase2_baselines() recomputes its
counts and --check-baselines compares them with the recorded ones.

The change beside a figure is the change in its percentage since the last
Discord post, from the figures that post saved (docs/discord-progress.json).
When the census behind Linking changed its rules since then, or the TU
estimate behind file layout changed, the two figures measure different things:
the row says "accounting changed" and why, never an arrow.

--discord posts every time (the daily run); --discord-on-change posts only when
a "Does it work?" figure differs from the last post's (the hourly runs). With
--post-record PATH a successful post is recorded in PATH before anything else
(the workflow keeps it across re-runs with actions/cache, keyed on the run ID),
so a retried run neither posts twice nor loses the post's saved figures.
--publish commits the card and pushes it, drawing it again on the tree it pushes
onto whenever commits that landed meanwhile changed an input.
"""
import argparse
import csv
import json
import os
import subprocess
import sys
import time
from datetime import datetime, timezone
from pathlib import Path
from urllib.error import HTTPError, URLError
from urllib.request import Request, urlopen

import name_metric
import progress

STATE = "docs/discord-progress.json"
OWNERSHIP = "reverse/image_ownership_history.csv"
README = "https://github.com/Open-BFME/Open-BFME-2#readme"
DOT = "·"
UP, DOWN = "▲", "▼"
TITLE = f"BFME 2 {DOT} Road to a finished decomp"
SUBTITLE = "Finished means: the whole game is built from readable source, builds the normal way, and plays"
WORKS_HEADING, CLEAN_HEADING = "Does it work?", "Is the source clean?"
FOOTER = (f"Shortcuts, file layout and shared classes count from the start of Phase 2 ({progress.PHASE2_DATE}). "
          "How each figure is measured: README")

# (key, label, caption) for "Does it work?"; (key, label) for "Is the source clean?".
WORKS = (("matched", "Byte match", "Every byte of the game's program code is recreated by compiling our source"),
         ("linked", "Linking", "Share of game code that links into one program"))
CLEAN = (("authored", "Hand-written code"), ("names", "Readable names"), ("shortcuts", "Shortcuts removed"),
         ("layout", "Original file layout"), ("classes", "Shared class definitions"))
LABELS = {key: label for key, label, *_ in WORKS + CLEAN}
CARD_FILL = {"matched": "#2ea043", "linked": "#d29922", "authored": "#58a6ff",
             "names": "#a371f7", "shortcuts": "#e05c7a", "layout": "#f0883e", "classes": "#e05c7a"}
# Discord draws each bar as ten square emoji (a wider row wraps on a phone); it has no pink square.
BLOCK = {"matched": "\U0001f7e9", "linked": "\U0001f7e8", "authored": "\U0001f7e6",
         "names": "\U0001f7ea", "shortcuts": "\U0001f7e5", "layout": "\U0001f7e7", "classes": "\U0001f7e5"}
REST_BLOCK = "⬛"
WIDTH = 10
# Counts, not bytes: their change compares the displayed percentages, so a
# visible 0.01 change keeps its arrow and "· 0.00" means unchanged.
COUNTED = frozenset({"names", "shortcuts", "layout", "classes"})
NOT_MEASURED_DATA = "game data & assets: not measured yet"
# Card geometry: text wraps within the 824 px between the margins.
LEFT, RIGHT, TEXT_WIDTH, TEXT_PX, LINE_STEP = 28, 852, 824, 12.5, 16


def _count(current, key):
    value = current.get(key)
    if value is not None and (type(value) is not int or value < 0):
        raise ValueError(f"Invalid {key}: {value!r}")
    return value


def measures(current):
    """{key: (count, denominator)}; (None, None) for a figure the state lacks.
    Linking is one census snapshot: its bytes and its denominator (the
    census tree's executable game code) both come from the census. The Phase 2
    figures count what was retired since progress.PHASE2_START."""
    total = current["total"]
    game = progress.game_executable(current, total)
    matched, authored = progress.rebuildable(current), current["authored"]
    cpp = progress.game_represented(current)
    inclusive = any(k in current for k in ('linked_game_executable', 'game_executable', 'link_coverage_rules'))
    if inclusive and any(current.get(k) in (None, '') for k in
                         ('linked_game_executable', 'game_executable', 'link_coverage_rules')):
        raise ValueError('Incomplete linking coverage snapshot')
    linked, linked_game = ((current['linked_game_executable'], current['game_executable']) if inclusive
                          else (current.get("linked_authored"), current.get("linked_game_code")))
    if (linked is None) != (linked_game is None):
        raise ValueError("A census stored linked_authored without game_code, or the reverse")
    if not 0 <= authored <= cpp <= game <= total or not 0 <= matched <= total or (
            linked is not None and not 0 <= linked <= linked_game <= total):
        raise ValueError("Invalid progress split")
    readable, names = current.get("readable_names"), current.get("declared_names")
    if (readable is None) != (names is None) or (names is not None and not 0 <= readable <= names):
        raise ValueError("Invalid readable-names count")
    items, files, target, copies = (_count(current, key) for key in
                                    ("hatch_items", "source_files", "tu_target", "class_copies"))
    if target is not None and target >= progress.PHASE2_SOURCE_FILES:
        raise ValueError(f"Invalid tu_target: {target} TUs, not fewer than the {progress.PHASE2_SOURCE_FILES} files")
    since = progress.PHASE2_HATCH_ITEMS, progress.PHASE2_SOURCE_FILES, progress.PHASE2_CLASS_COPIES
    return {"matched": (matched, total), "cpp": (cpp, game), "linked": (linked, linked_game),
            "authored": (authored, game), "names": (readable, names),
            "shortcuts": (since[0] - items, since[0]) if items is not None else (None, None),
            "layout": ((since[1] - files, since[1] - target) if files is not None and target is not None
                       else (None, None)),
            "classes": (since[2] - copies, since[2]) if copies is not None else (None, None)}


def share(value, denominator):
    """The figure as the card prints it."""
    return f"{progress.percent(value, denominator):.2f}%"


def problems(current):
    """Every link problem the newest census recorded (progress.link_problems), or None."""
    return current.get("link_problems")


def remeasuring(current):
    """(census tool rules, the newest row's rules) while tools/link_census.py
    measures under rules the newest census row was not measured under, else None."""
    census, tool = current.get("census"), current.get("census_tool_rules")
    if census and tool and tool != progress.census_rules(census):
        return tool, progress.census_rules(census)
    return None


# The exit test is a whole-program link with no /FORCE and no stubs. The census
# links under /FORCE and link_cycle links with stubs, and neither records such a
# link, so no figure moves the milestone; fewer counted problems are not that
# evidence. It moves when a tool records the exit test.
MILESTONE = "Next milestone: first normal build, then the first playtest"


def milestone(current):
    return MILESTONE


def ownership(root=None):
    """The newest image-ownership history row as {date, ours, content}, or None
    (no history yet: game data and assets are not measured)."""
    path = (root or progress.ROOT) / OWNERSHIP
    if not path.exists():
        return None
    rows = list(csv.DictReader(path.read_text(encoding="utf-8").splitlines()))
    if not rows:
        return None
    ours, content = int(rows[-1]["ours"]), int(rows[-1]["content_bytes"])
    if not 0 <= ours <= content or not content:
        raise ValueError(f"{OWNERSHIP}: invalid ownership figures")
    return {"date": rows[-1]["date"][:10], "ours": ours, "content": content}


def side_note(current, key):
    """The note on the right of a "Does it work?" caption."""
    if key == "matched":
        owned = current.get("ownership")
        return (f"whole game file: {share(owned['ours'], owned['content'])} ours ({owned['date']})" if owned
                else NOT_MEASURED_DATA)
    census = current.get("census")
    return f"measured {census['date'][:10]}" if census else None


def caption(current, key, text):
    found = problems(current) if key == "linked" else None
    return text + (f"; {found['total']:,} problems recorded" if found else "")


def rules_changed(previous, current):
    """(previous rules, current rules) when the census behind Linking
    was measured under other rules at the last post, else None."""
    if previous and previous.get('link_coverage_rules') != current.get('link_coverage_rules'):
        return (previous.get('link_coverage_rules') or 'authored-only',
                current.get('link_coverage_rules') or 'authored-only')
    if not previous or not previous.get("census") or not current.get("census"):
        return None
    before, after = progress.census_rules(previous["census"]), progress.census_rules(current["census"])
    return (before, after) if before != after else None


def target_changed(previous, current):
    """(previous, current) TU estimates when the map's count moved since the last post."""
    if previous and previous.get("tu_target") is not None and current.get("tu_target") is not None \
            and previous["tu_target"] != current["tu_target"]:
        return previous["tu_target"], current["tu_target"]
    return None


def changes(previous, current, key):
    """Why the figure cannot be compared with the last post's:
    [(what changed, note)], empty when it can."""
    if not previous or current is None:
        return []
    out = []
    if key == "matched" and "assembly" not in previous and "assembly" in current:
        out.append(("accounting", "; reviewed assembly now counted, not new recovery"))
    rules = rules_changed(previous, current) if key == "linked" else None
    if rules:
        out.append(("accounting", rule_note(previous, rules)))
    target = target_changed(previous, current) if key == "layout" else None
    if target:
        out.append(("accounting", f"; the TU map's estimate moved from {target[0]:,} to {target[1]:,} files, "
                                  "not a change in progress"))
    return out


def notes(previous, current, key):
    """changes()' notes and the re-measuring note, as sentences for their own lines."""
    lines = [note[2:3].upper() + note[3:] for _, note in changes(previous, current, key) if note]
    pending = remeasuring(current) if key == "linked" else None
    if pending:
        lines.append(f"The counting rules changed ({pending[1]} to {pending[0]}): this is the last figure under the "
                     "old rules until the next census")
    return lines


def delta_since(previous, key, value, denominator, current=None):
    """The change in the figure's percentage since the last post, in points,
    from the figures that post saved; None when that post has no such figure,
    a byte figure's change rounds to 0.00, or (changes) the two do not measure
    the same thing. Counts compare displayed percentages, including zero."""
    if current is not None and (changes(previous, current, key) or (key == "linked" and remeasuring(current))):
        return None
    try:
        was, was_over = measures(previous)[key] if previous else (None, None)
    except KeyError:
        return None  # a state saved before these figures existed
    if was is None:
        return None
    if key in COUNTED:
        return round(round(progress.percent(value, denominator), 2) - round(progress.percent(was, was_over), 2), 2)
    delta = progress.percent(value, denominator) - progress.percent(was, was_over)
    return delta if round(abs(delta), 2) else None


def arrow(delta):
    """UP 0.21 / DOWN 0.05: the change since the last post, in percentage points."""
    return f"{UP if delta > 0 else DOWN if delta < 0 else DOT} {abs(delta):.2f}"


def tag(previous, current, key, value, denominator):
    """(css class, text) beside a figure's label, or None."""
    if key == "linked" and remeasuring(current):
        return "muted", "being re-measured"
    if changes(previous, current, key):
        return "muted", "accounting changed"
    delta = delta_since(previous, key, value, denominator, current)
    if delta is None:
        return None
    return ("up" if delta > 0 else "down" if delta < 0 else "muted"), arrow(delta)


def wrap(text, width=TEXT_WIDTH, separators=(". ", "; ", ": ", ", ", " "), size=TEXT_PX):
    """Card lines at most `width` px wide (progress.text_width), broken after a
    sentence where one fits, else a `;` clause, a `:` or `,`, else between
    words; a single word wider than `width` stays whole."""
    if progress.text_width(text, size) <= width or not separators:
        return [text]
    separator, rest = separators[0], separators[1:]
    parts = text.split(separator)
    pieces = [part + separator.rstrip() for part in parts[:-1]] + parts[-1:]
    lines = []
    for piece in pieces:
        if lines and progress.text_width(lines[-1] + " " + piece, size) <= width:
            lines[-1] += " " + piece
        else:
            lines += wrap(piece, width, rest, size)
    return lines


def escape(text):
    return text.replace("&", "&amp;").replace("<", "&lt;").replace(">", "&gt;")


def _text(x, y, css, size, body, weight=None, anchor=None, extra="", markup=""):
    """One <text>: `body` is plain text (escaped here), `markup` SVG appended after it."""
    return (f'    <text x="{x}" y="{y}" class="{css}" font-size="{size}"'
            + (f' font-weight="{weight}"' if weight else "") + (f' text-anchor="{anchor}"' if anchor else "")
            + f"{extra}>{escape(body)}{markup}</text>\n")


def _tspan(found, size):
    return (f'<tspan class="{found[0]}" dx="10" font-size="{size}" font-weight="600">{found[1]}</tspan>'
            if found else "")


def bar_x(rows, current, previous):
    """Where the compact bars start: past the widest label and its tag."""
    widest = 0
    for key, label in CLEAN:
        value, denominator = rows[key]
        found = tag(previous, current, key, value, denominator) if value is not None else None
        widest = max(widest, progress.text_width(label, 14) + (10 + progress.text_width(found[1], 12) if found else 0))
    return LEFT + int(widest) + 24


def render(current, previous=None):
    rows = measures(current)
    body = [_text(LEFT, 38, "strong", 20, TITLE, 700)]
    subtitle = wrap(SUBTITLE, size=13)
    body += [_text(LEFT, 60 + 17 * n, "muted", 13, line) for n, line in enumerate(subtitle)]
    y = 60 + 17 * (len(subtitle) - 1) + 36
    body.append(_text(LEFT, y, "muted", 12, WORKS_HEADING.upper(), 600, extra=' letter-spacing="1.2"'))
    y += 30
    for key, label, words in WORKS:
        value, denominator = rows[key]
        if value is None:
            number, width, found, lines, note = "not measured", 0, None, ["not measured yet"], None
        else:
            number = share(value, denominator)
            width = TEXT_WIDTH * min(max(progress.percent(value, denominator), 0), 100) / 100
            found = tag(previous, current, key, value, denominator)
            lines, note = wrap(caption(current, key, words)), side_note(current, key)
        body.append(_text(LEFT, y, "strong", 15, label, 600, markup=_tspan(found, 13)))
        body.append(_text(RIGHT, y, "strong", 20, number, 700, "end"))
        body.append(f'    <rect class="track" x="{LEFT}" y="{y + 10}" width="{TEXT_WIDTH}" height="14" rx="7"/>\n'
                    f'    <rect x="{LEFT}" y="{y + 10}" width="{width:.2f}" height="14" rx="7" fill="{CARD_FILL[key]}"/>\n')
        if note and progress.text_width(lines[-1], TEXT_PX) + 24 + progress.text_width(note, TEXT_PX) > TEXT_WIDTH:
            lines, note = lines + [note], None  # no room beside the caption: a line of its own
        if value is not None:
            lines += [piece for line in notes(previous, current, key) for piece in wrap(line)]
        body += [_text(LEFT, y + 44 + LINE_STEP * n, "muted", TEXT_PX, line) for n, line in enumerate(lines)]
        if note:
            body.append(_text(RIGHT, y + 44, "muted", TEXT_PX, note, anchor="end"))
        y += 76 + LINE_STEP * (len(lines) - 1)
    y -= 6
    body.append(f'    <rect class="box" x="{LEFT}" y="{y}" width="{TEXT_WIDTH}" height="34" rx="8"/>\n')
    head, _, rest = milestone(current).partition(": ")
    body.append(_text(LEFT + 16, y + 22, "muted", 14, f"{head}:", 600,
                      markup=f'<tspan class="strong"> {escape(rest)}</tspan>'))
    y += 34 + 40
    body.append(_text(LEFT, y, "muted", 12, CLEAN_HEADING.upper(), 600, extra=' letter-spacing="1.2"'))
    start = bar_x(rows, current, previous)
    span = RIGHT - 84 - start
    for key, label in CLEAN:
        y += 30
        value, denominator = rows[key]
        found = tag(previous, current, key, value, denominator) if value is not None else None
        number = share(value, denominator) if value is not None else "soon"
        width = span * min(max(progress.percent(value, denominator), 0), 100) / 100 if value is not None else 0
        body.append(_text(LEFT, y, "strong", 14, label, 600, markup=_tspan(found, 12)))
        body.append(f'    <rect class="track" x="{start}" y="{y - 10}" width="{span}" height="10" rx="5"/>\n'
                    f'    <rect x="{start}" y="{y - 10}" width="{width:.2f}" height="10" rx="5" fill="{CARD_FILL[key]}"/>\n')
        body.append(_text(RIGHT, y, "strong", 15, number, 700, "end"))
        extra = [piece for line in notes(previous, current, key) for piece in wrap(line)] if value is not None else []
        for line in extra:
            y += LINE_STEP
            body.append(_text(LEFT, y, "muted", TEXT_PX, line))
    y += 34
    footer = wrap(FOOTER, size=12)
    body += [_text(LEFT, y + 16 * n, "muted", 12, line) for n, line in enumerate(footer)]
    height = y + 16 * (len(footer) - 1) + 20
    matched, linked = rows["matched"], rows["linked"]
    found = problems(current)
    summary = (f"{share(*matched)} byte match, "
               + (f"{share(*linked)} linking" if linked[0] is not None else "linking not measured")
               + (f" ({found['total']:,} problems recorded)" if found else ""))
    clean = ", ".join(f"{LABELS[key].lower()} {share(*rows[key]) if rows[key][0] is not None else 'soon'}"
                      for key, _ in CLEAN)
    return f'''<svg xmlns="http://www.w3.org/2000/svg" width="880" height="{height}" viewBox="0 0 880 {height}" role="img" aria-labelledby="title desc">
  <title id="title">{escape(f"{TITLE}: {summary}")}</title>
  <desc id="desc">{escape(f"{SUBTITLE}. Is the source clean? {clean}. {FOOTER}.")}</desc>
  <style>
    .card {{ fill: #0d1117; stroke: #30363d; }} .track {{ fill: #21262d; }} .box {{ fill: #161b22; stroke: #30363d; }}
    .strong {{ fill: #f0f6fc; }} .muted {{ fill: #8b949e; }} .up {{ fill: #3fb950; }} .down {{ fill: #f85149; }}
    @media (prefers-color-scheme: light) {{
      .card {{ fill: #ffffff; stroke: #d0d7de; }} .track {{ fill: #eaeef2; }} .box {{ fill: #f6f8fa; stroke: #d0d7de; }}
      .strong {{ fill: #1f2328; }} .muted {{ fill: #59636e; }} .up {{ fill: #1a7f37; }} .down {{ fill: #cf222e; }}
    }}
  </style>
  <rect class="card" x="0.5" y="0.5" width="879" height="{height - 1}" rx="12"/>
  <g font-family="{progress.FONT_STACK}" {progress.NO_KERN}>
{"".join(body)}  </g>
</svg>
'''


def rule_note(previous, changed):
    """`; census accounting changed to retail-truth-4 (16.10% under majority-0),
    not a change in progress` (the last post's figure)."""
    before, after = changed
    saved = saved_linking(previous)
    if before == "authored-only" and after == progress.LINK_COVERAGE_RULES:
        return "; generated linked code now counted"
    shown = (f"{progress.percent(*saved):.2f}% under {before}" if saved
             else f"was {before}; the last post saved no Linking figure")
    return f"; census accounting changed to {after} ({shown}), not a change in progress"


def saved_linking(previous):
    """Saved Linking bytes and denominator; absent is optional, malformed raises."""
    inclusive = any(key in previous for key in
                    ("linked_game_executable", "game_executable", "link_coverage_rules"))
    if inclusive:
        if not previous.get("link_coverage_rules"):
            raise ValueError("Invalid saved Linking coverage rules")
        linked, over = (previous.get(key) for key in ("linked_game_executable", "game_executable"))
    else:
        linked, over = (previous.get(key) for key in ("linked_authored", "linked_game_code"))
    if linked is None and over is None and not inclusive:
        return None
    if not all(type(value) is int for value in (linked, over)) or not 0 <= linked <= over:
        raise ValueError(f"Invalid saved Linking figure: {linked!r} over {over!r}")
    total = previous.get("total")
    if total is not None and (type(total) is not int or over > total):
        raise ValueError(f"Invalid saved Linking denominator: {over!r} of {total!r}")
    return linked, over


def blocks(value, total, block, width=WIDTH):
    """`width` square emoji: the value's share in `block`, the rest dark."""
    count = int(min(max(width * value // total, 0), width)) if total else 0   # floor: ten squares only at 100%
    return block * count + REST_BLOCK * (width - count)


def announcement(current, previous):
    """The Discord post: the card's figures, then a link to the README."""
    rows = measures(current)
    lines = [f"*{SUBTITLE}*", "", f"**{WORKS_HEADING}**"]
    for key, label, words in WORKS:
        value, denominator = rows[key]
        if value is None:
            lines += [f"**{label}:** not measured yet", REST_BLOCK * WIDTH, ""]
            continue
        found = tag(previous, current, key, value, denominator)
        note = side_note(current, key)
        lines += [f"**{label}: {share(value, denominator)}**"
                  + ("" if not found else f"  ({found[1]})" if found[0] == "muted" and found[1][0] != DOT
                     else f"  {found[1]}"),
                  blocks(value, denominator, BLOCK[key]),
                  caption(current, key, words) + (f" ({note})" if note else ""),
                  *notes(previous, current, key), ""]
    lines += [f"> {milestone(current)}", "", f"**{CLEAN_HEADING}**"]
    for key, label in CLEAN:
        value, denominator = rows[key]
        if value is None:
            lines.append(f"{REST_BLOCK * WIDTH} {label}: soon")
            continue
        found = tag(previous, current, key, value, denominator)
        lines.append(f"{blocks(value, denominator, BLOCK[key])} **{share(value, denominator)}** {label}"
                     + ("" if not found else f"  ({found[1]})" if found[0] == "muted" and found[1][0] != DOT
                        else f"  {found[1]}"))
        lines += [f"-# {line}" for line in notes(previous, current, key)]
    head, _, _ = FOOTER.rpartition(" How each figure is measured: README")
    lines += ["", f"{head} [How each figure is measured: README]({README})"]
    return {"allowed_mentions": {"parse": []},
            "embeds": [{"title": TITLE, "color": 0x2EA043, "description": "\n".join(lines)}]}


def headline(state):
    """The "Does it work?" figures as the post prints them, the game-data note
    beside byte match included; None for a state they cannot be read from."""
    try:
        rows = measures(state)
    except (KeyError, ValueError, TypeError):
        return None
    found = problems(state)
    return tuple(share(*rows[key]) if rows[key][0] is not None else None for key, *_ in WORKS) + (
        side_note(state, "matched"), found["total"] if found else None, remeasuring(state), milestone(state))


def previous_state():
    path = progress.ROOT / STATE
    return json.loads(path.read_text(encoding="utf-8")) if path.exists() else None


def _write_json(path, value):
    """Write `value` to `path` whole or not at all (a temporary file, then a rename)."""
    path = Path(path)
    path.parent.mkdir(parents=True, exist_ok=True)
    temporary = path.with_name(path.name + ".tmp")
    temporary.write_text(json.dumps(value, indent=2) + "\n", encoding="utf-8")
    os.replace(temporary, path)


def read_record(path):
    """The post record at `path`: the state a successful post saved, or None."""
    return json.loads(Path(path).read_text(encoding="utf-8")) if path and Path(path).exists() else None


def restore_post(record_path):
    """Put this run's recorded post back into docs/discord-progress.json when the
    checkout lacks it: a retried run on a fresh checkout, or a card drawn again
    after publish() reset onto newer commits. The card then compares with the
    post that went out, and the commit carries its figures. A record of another
    run, or one older than the saved state, is left alone."""
    record, run_id = read_record(record_path), os.environ.get("GITHUB_RUN_ID")
    if not record or not run_id or record.get("run_id") != run_id:
        return False
    saved = previous_state()
    if saved and (saved.get("run_id") == run_id or str(saved.get("updated_at", "")) >= str(record.get("updated_at", ""))):
        return False
    _write_json(progress.ROOT / STATE, record)
    print("Discord: this run's post restored from its record")
    return True


def notify(current, on_change=False, record_path=None):
    """Post to Discord and save the figures the post was drawn from: first to
    `record_path` (kept outside the repository, so a failure in a later render
    or push cannot lose it), then to docs/discord-progress.json. With
    `on_change`, post only when a "Does it work?" figure moved since the last post."""
    previous = previous_state()
    run_id = os.environ.get("GITHUB_RUN_ID")
    recorded = read_record(record_path)
    if run_id and any(state and state.get("run_id") == run_id for state in (previous, recorded)):
        print("Discord: this run already posted")
        return
    if on_change and previous and headline(previous) == headline(current):
        print("Discord: no \"Does it work?\" figure changed since the last post; not posted")
        return
    webhook = os.environ.get("DISCORD_PROGRESS_WEBHOOK", "").strip()
    if not webhook.startswith("https://discord.com/api/webhooks/"):
        raise SystemExit("DISCORD_PROGRESS_WEBHOOK is missing or invalid")
    url = webhook + "?wait=true"
    request = Request(url, data=json.dumps(announcement(current, previous)).encode("utf-8"),
                      headers={"Content-Type": "application/json", "User-Agent": "OpenBFME-Progress/1.0"},
                      method="POST")
    try:
        with urlopen(request, timeout=30) as response:
            message = json.load(response)
    except HTTPError as exc:
        raise SystemExit(f"Discord update failed: HTTP {exc.code}") from None
    except URLError:
        raise SystemExit("Discord update failed: connection error") from None
    state = {**current, "updated_at": datetime.now(timezone.utc).isoformat(), "message_id": message["id"],
             "run_id": run_id}
    if record_path:
        _write_json(record_path, state)
    _write_json(progress.ROOT / STATE, state)
    print("Discord: new progress message posted")


# What the workflow commits, and the steps that draw it (in order; without a
# post: the workflow's own card step posts once, before publish()).
OUTPUTS = ("docs/progress.svg", "docs/progress_chart.svg", "docs/progress_map.svg", STATE,
           "reverse/progress_history.csv", "docs/progress_v2.svg", "reverse/progress_v2_history.csv")
RENDER = (("tools/progress_site.py", "history", "--today"), ("tools/readme_progress.py",),
          ("tools/progress_v2.py", "--today", "--svg", "docs/progress_v2.svg"),
          ("tools/progress_site.py", "render", "build/site/index.html", "--svg", "docs"))
OPTIONAL = frozenset({"tools/progress_v2.py"})   # the workflow lets the rules-v2 card fail


def render_again(record_path=None):
    """Draw every output again from the checkout, in fresh processes (progress's
    caches hold the older tree)."""
    for step in RENDER:
        command = [sys.executable, *step]
        if step[0] == "tools/readme_progress.py" and record_path:
            command += ["--post-record", str(record_path)]
        if subprocess.run(command, cwd=progress.ROOT).returncode and step[0] not in OPTIONAL:
            raise SystemExit(f"readme_progress: {' '.join(step)} failed")


def _git(*args, check=True):
    done = subprocess.run(["git", *args], cwd=progress.ROOT, capture_output=True, text=True)
    if check and done.returncode:
        raise SystemExit(f"readme_progress: git {' '.join(args)} failed: {done.stderr.strip()}")
    return done


def _commit_outputs():
    _git("add", "--", *(path for path in OUTPUTS if (progress.ROOT / path).exists()))
    if _git("diff", "--cached", "--quiet", check=False).returncode == 0:
        return False
    _git("commit", "-q", "-m", "docs: update README progress card")
    return True


def publish(render, remote="origin", branch="master", tries=6, wait=time.sleep):
    """Commit the outputs and push them to `branch` so that the card pushed is
    the card of the tree it lands on. Commits land on master continuously: when
    those that landed since the render changed anything but the outputs, reset
    onto them and `render` again (a rebase would carry over a card drawn from
    the older tree); otherwise rebase. Retry a rejected push."""
    base = _git("rev-parse", "HEAD").stdout.strip()
    if not _commit_outputs():
        print("publish: nothing to commit")
        return
    for attempt in range(1, tries + 1):
        _git("fetch", "-q", remote, branch)
        upstream = _git("rev-parse", "FETCH_HEAD").stdout.strip()
        inputs = _git("diff", "--quiet", base, upstream, "--", ".", *(f":(exclude){path}" for path in OUTPUTS),
                      check=False).returncode
        if inputs or _git("rebase", "-q", upstream, check=False).returncode:
            _git("rebase", "--abort", check=False)
            _git("reset", "-q", "--hard", upstream)
            render()
            base = upstream
            print(f"publish: inputs changed; drawn again on {upstream[:10]}")
            if not _commit_outputs():
                print("publish: nothing to commit on the newer tree")
                return
        if _git("push", "-q", remote, f"HEAD:{branch}", check=False).returncode == 0:
            print(f"publish: pushed {_git('rev-parse', '--short=10', 'HEAD').stdout.strip()}")
            return
        wait(10 * attempt)
    raise SystemExit(f"readme_progress: the card was not pushed after {tries} tries")


def collect():
    """Every figure the card draws, from the worktree (CI: the checkout)."""
    matched = progress.matched_at(None)
    notes_ = progress.notes_at(None)
    start, size = progress.retail_text()
    naked = progress.naked_cpp_rows_at(matched, None)
    split = progress.real_split(matched, notes_, start, size, naked, text_data=progress.text_data_at(None))
    census = progress.census_at(None)
    _, total = progress.real_code_denominator(start, size)
    names, placeholders = name_metric.readable()
    current = {"total": total, "cpp_rules": progress.GAME_CPP_RULES,
               "census": census, "declared_names": names, "readable_names": names - placeholders,
               "linked": int(census["linked_bytes"]) if census else None,
               "linked_authored": int(census["linked_authored"]) if census and census.get("linked_authored") else None,
               "linked_game_code": int(census["game_code"]) if census and census.get("game_code") else None,
               "census_tool_rules": progress.census_tool_rules_at(None), "ownership": ownership(),
               "link_problems": progress.link_problems_at(None),
               **progress.cleanup_figures_at(None),
               **{lane: split.get(lane, 0) for lane in ("authored", "vendored", "generated", "library", "data", "assembly")}}
    if census:
        current.update(progress.linking_coverage_at(None) or {})
    return current


def check_baselines():
    """Compare the recorded Phase 2 counts with a recount at progress.PHASE2_START."""
    recorded = {"hatch_items": progress.PHASE2_HATCH_ITEMS, "source_files": progress.PHASE2_SOURCE_FILES,
                "class_copies": progress.PHASE2_CLASS_COPIES}
    found = progress.phase2_baselines()
    for key, value in recorded.items():
        print(f"{key}: recorded {value:,}, at {progress.PHASE2_START} {found[key]:,}"
              + ("" if found[key] == value else "  MISMATCH"))
    if found != recorded:
        raise SystemExit("readme_progress: the recorded Phase 2 counts differ from the commit's")


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--discord", action="store_true", help="post a new Discord progress message")
    parser.add_argument("--discord-on-change", action="store_true",
                        help="post only when a \"Does it work?\" figure changed since the last post")
    parser.add_argument("--check-baselines", action="store_true",
                        help=f"recount the Phase 2 baselines at {progress.PHASE2_START} and compare")
    parser.add_argument("--post-record", metavar="PATH",
                        help="record a successful post here first, and restore this run's post from it")
    parser.add_argument("--publish", action="store_true",
                        help="commit the outputs and push them, drawn again if their inputs moved meanwhile")
    args = parser.parse_args()
    if args.check_baselines:
        check_baselines()
        return
    if args.publish:
        publish(lambda: render_again(args.post_record))
        return
    restore_post(args.post_record)
    current = collect()
    output = progress.ROOT / "docs" / "progress.svg"
    output.write_text(render(current, previous_state()), encoding="utf-8", newline="\n")
    rows = measures(current)
    print(f"{output.relative_to(progress.ROOT)}: " + ", ".join(
        f"{label} {share(*rows[key])}" if rows[key][0] is not None else f"{label} not measured"
        for key, label in LABELS.items()))
    if args.discord or args.discord_on_change:
        notify(current, on_change=not args.discord, record_path=args.post_record)


if __name__ == "__main__":
    sys.exit(main())
