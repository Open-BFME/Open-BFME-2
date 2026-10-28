#!/usr/bin/env python3
"""Source-path strings in worldbuilder.exe and game.dat, and the TU-evidence triage built on them.

Both binaries keep the `__FILE__` strings their assert and debug macros push. This tool
extracts every `.cpp`/`.c` path string from each image and writes one row per string
occurrence to reverse/worldbuilder_source_paths.csv:

  binary, binary_sha256  the image the string was read from and that image's SHA-256
  offset, path_offset    file offset of the whole printable run, and of the path inside it
  encoding               ascii or utf-16le
  raw                    the whole printable run, exactly as stored
  path                   the path as cut from the run (what __FILE__ pushed)
  normalized             repo-style spelling: build root stripped, `\\` -> `/`, `..` resolved
  rule                   the normalization rule applied (strip-root:<root>, fesl-view, none)
  producer_root          bfme2-code, tools-worldbuilder (the editor's own Code/Tools/WorldBuilder/),
                         fesl (\\views\\feslbuild_main\\...), juice (c:\\dev\\lotr\\...), other
  present_in_game_dat    yes when game.dat's own strings carry the same normalized path
                         (case-insensitive), else no
  flags                  how the path was cut out of its run: prefix=<text> (binary-adjacent
                         bytes stripped before the path), suffix=<text>, message (the path sits
                         inside a longer message), unaligned (the stripped path does not start on
                         a 4-byte boundary, so the cut is ambiguous; kept, never dropped)

Extraction. A printable run (ASCII >= 6, or UTF-16LE >= 6 characters) is searched for
paths anchored at a drive letter (`X:\\`), a leading separator or `..\\`; whatever printable
bytes precede the anchor are binary-adjacent data (an immediate, a float, an earlier
literal's tail) and are stripped into `flags`. String literals are 4-byte aligned in
both images, so a stripped path starting on a boundary is a clean cut and one that does
not is flagged `unaligned`.

Provenance. Rows for worldbuilder.exe are DONOR facts: the editor (BFME 2's internal
WorldBuilder build, RSDS C:\\Projects\\bfme2\\Run\\WorldBuilderI.pdb) was built from the same
tree, so a path proves only that a file of that spelling existed in that build. It never
proves that a game.dat function belongs to that file, and the WorldBuilder path count is
no denominator for game files. Rows for game.dat are TARGET facts (game.dat's own
strings). TU approval stays with tools/tu_map.py (wb_name_leads + its w_score gate).

Triage. triage_items() (served by tools/next_work.py's tu-evidence tier through
tools/repair_queue.py tu_evidence_items) emits one LEAD per non-editor WorldBuilder path the
live TU map (tu_skeleton.map_rows()) has no TU for, with: the game RVAs paired by
reverse/wb_name_leads.csv with a WB body that pushes that path (every file the body
pushes, from reverse/wb/wb_functions.jsonl.xz, not only the first), their current
ledger owner, source and tu_map confidence, same-basename TUs already in the map, and
whether game.dat's own strings carry the path. Unaligned (ambiguous) cuts stay in the
inventory but lead nowhere. A lead is never proof and never a reason to create an empty TU.

    python3 tools/wb_source_paths.py inventory    # rewrite the CSV from the two images
    python3 tools/wb_source_paths.py check        # exit 1 when the CSV differs from a rebuild
    python3 tools/wb_source_paths.py triage [--json] [--limit N]
"""
import argparse
import bisect
import csv
import hashlib
import io
import json
import lzma
import posixpath
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
IMAGE_DIR = Path("baselines/bfme2/workshop-vanilla-1.06/files")
IMAGES = (("worldbuilder.exe", IMAGE_DIR / "worldbuilder.exe"), ("game.dat", IMAGE_DIR / "game.dat"))
OUT = Path("reverse/worldbuilder_source_paths.csv")
LEADS = Path("reverse/wb_name_leads.csv")
FUNCTIONS = Path("reverse/functions.csv")
WB_FUNCTIONS = Path("reverse/wb/wb_functions.jsonl.xz")
WB_MATCHES = Path("reverse/wb/matches_full.jsonl.xz")
IMAGE_BASE = 0x400000

FIELDS = ("binary", "binary_sha256", "offset", "path_offset", "encoding", "raw", "path", "normalized", "rule",
          "producer_root", "present_in_game_dat", "flags")

_ASCII_RUN = re.compile(rb"[\x20-\x7e]{6,}")
_UTF16_RUN = re.compile(rb"(?:[\x20-\x7e]\x00){6,}")
# A path: anchored at a drive letter, a leading separator or ..\ ; no spaces (the build
# roots have none); ends at .cpp/.c not followed by an identifier character.
_PATH = re.compile(r"(?:[A-Za-z]:[\\/]|[\\/]|\.\.[\\/])[A-Za-z0-9_.\-\\/]*?\.(?:cpp|c)(?![A-Za-z0-9_])", re.I)
# Build roots, tried in order on the backslash form. (pattern, producer when not editor)
_ROOTS = (
    (re.compile(r"^[a-z]:\\projects\\bfme2patch\d+\\bfme2\\", re.I), None),
    (re.compile(r"^[a-z]:\\projects\\bfme2\\", re.I), None),
    (re.compile(r"^[a-z]:\\dev\\lotr\\bfme2\\production\\", re.I), "juice"),
)
_FESL = re.compile(r"^\\views\\feslbuild_main\\", re.I)
EDITOR = "code/tools/worldbuilder/"


def normalize(path):
    """(normalized, rule, producer_root) for one raw path string."""
    text = path.replace("/", "\\")
    for pattern, producer in _ROOTS:
        m = pattern.match(text)
        if m:
            rest = posixpath.normpath(text[m.end():].replace("\\", "/"))
            head, _, tail = rest.partition("/")
            if head.lower() == "code":
                rest = "Code/" + tail
            if producer is None:
                producer = ("tools-worldbuilder" if rest.lower().startswith(EDITOR)
                            else "bfme2-code" if rest.startswith("Code/") else "other")
            return rest, f"strip-root:{m.group(0)}", producer
    if _FESL.match(text):
        return posixpath.normpath(text.lstrip("\\").replace("\\", "/")), "fesl-view", "fesl"
    return posixpath.normpath(text.replace("\\", "/")), "none", "other"


def cut(run, run_offset, width=1):
    """[(path, path_offset, flags)] for every path in one printable run (decoded text).
    WIDTH is the encoding's bytes per character, for offsets and the alignment test."""
    out = []
    for m in _PATH.finditer(run):
        flags = []
        before, after = run[:m.start()], run[m.end():]
        if before:
            if " " in before:
                flags.append("message")
            else:
                flags.append(f"prefix={before}")
        if after:
            flags.append(f"suffix={after}")
        offset = run_offset + m.start() * width
        if before and " " not in before and offset % 4:
            flags.append("unaligned")
        out.append((m.group(0), offset, ";".join(flags)))
    return out


def extract(data):
    """[(offset, path_offset, encoding, raw, path, flags)] for one image's bytes, in offset order."""
    found = []
    for m in _ASCII_RUN.finditer(data):
        raw = m.group().decode("ascii")
        for path, off, flags in cut(raw, m.start()):
            found.append((m.start(), off, "ascii", raw, path, flags))
    for m in _UTF16_RUN.finditer(data):
        raw = m.group().decode("utf-16le")
        for path, off, flags in cut(raw, m.start(), 2):
            found.append((m.start(), off, "utf-16le", raw, path, flags))
    found.sort()
    return found


def build(root=ROOT):
    """Inventory rows from the two images under ROOT."""
    per_image = {}
    for name, rel in IMAGES:
        data = (root / rel).read_bytes()
        per_image[name] = (hashlib.sha256(data).hexdigest(), extract(data))
    game = {normalize(path)[0].lower() for *_, path, _ in per_image["game.dat"][1]}
    rows = []
    for name, _ in IMAGES:
        sha, found = per_image[name]
        for offset, path_offset, encoding, raw, path, flags in found:
            normalized, rule, producer = normalize(path)
            rows.append({"binary": name, "binary_sha256": sha, "offset": f"0x{offset:08X}",
                         "path_offset": f"0x{path_offset:08X}", "encoding": encoding, "raw": raw, "path": path,
                         "normalized": normalized, "rule": rule, "producer_root": producer,
                         "present_in_game_dat": "yes" if normalized.lower() in game else "no", "flags": flags})
    return rows


def render(rows):
    buf = io.StringIO()
    writer = csv.DictWriter(buf, FIELDS, lineterminator="\n")
    writer.writeheader()
    writer.writerows(rows)
    return buf.getvalue()


def read(root=ROOT):
    with open(root / OUT, newline="", encoding="utf-8") as fh:
        return list(csv.DictReader(fh))


def summary(rows):
    """{binary: {producer_root: {"strings", "paths", "in_game_dat"}}} over distinct normalized paths."""
    out = {}
    for row in rows:
        slot = out.setdefault(row["binary"], {}).setdefault(row["producer_root"],
                                                            {"strings": 0, "paths": set(), "in_game_dat": set()})
        slot["strings"] += 1
        slot["paths"].add(row["normalized"].lower())
        if row["present_in_game_dat"] == "yes":
            slot["in_game_dat"].add(row["normalized"].lower())
    return {b: {p: {"strings": s["strings"], "paths": len(s["paths"]), "in_game_dat": len(s["in_game_dat"])}
                for p, s in sorted(by.items())} for b, by in out.items()}


# ---------------------------------------------------------------- triage

def _jsonl_xz(path):
    with lzma.open(path, "rt", encoding="utf-8") as fh:
        for line in fh:
            yield line


def wb_body_files(root=ROOT):
    """{wb_va: [normalized lowercase path, ...]} for every WB body that pushes a source path
    (all of them, first-use order, from pe_features' `files`)."""
    out = {}
    for line in _jsonl_xz(root / WB_FUNCTIONS):
        if '"files":[]' in line:
            continue
        rec = json.loads(line)
        out[rec["va"]] = [normalize(f)[0].lower() for f in rec["files"]]
    return out


def wb_pairs(root=ROOT):
    """{game rva: wb_va} from the committed full WorldBuilder match."""
    out = {}
    for line in _jsonl_xz(root / WB_MATCHES):
        rec = json.loads(line)
        out[rec["gd_va"] - IMAGE_BASE] = rec["wb_va"]
    return out


def _leads(root):
    with open(root / LEADS, newline="", encoding="utf-8") as fh:
        return {int(r["target_rva"], 16): r for r in csv.DictReader(fh)}


def _ledger_names(root, rvas):
    out = {}
    with open(root / FUNCTIONS, newline="", encoding="utf-8") as fh:
        for row in csv.DictReader(fh):
            try:
                rva = int(row["target_rva"], 16)
            except ValueError:
                continue
            if rva in rvas:
                out.setdefault(rva, []).append(row["name"])
    return out


class MapIndex:
    """tu_map rows by address, and the set of TUs by lowercase path and basename."""

    def __init__(self, rows):
        self.rows = sorted((int(r["rva"], 16), r) for r in rows if r.get("rva"))
        self.starts = [rva for rva, _ in self.rows]
        self.tus = {}
        for _, r in self.rows:
            if r["tu"]:
                slot = self.tus.setdefault(r["tu"], {})
                slot[r["confidence"]] = slot.get(r["confidence"], 0) + 1
        self.lower = {tu.lower(): tu for tu in self.tus}
        self.by_base = {}
        for tu in self.tus:
            self.by_base.setdefault(posixpath.basename(tu).lower(), []).append(tu)

    def covering(self, rva):
        i = bisect.bisect_right(self.starts, rva) - 1
        if i >= 0:
            start, row = self.rows[i]
            if start <= rva < start + max(1, int(row.get("size") or 0)):
                return row
        return None


START = "investigate; this is a lead, not proof; never create an empty TU."


def triage(inventory, map_rows, body_files, pairs, leads, names):
    """Lead records, one per non-editor WorldBuilder path with no TU in the live map.
    Pure: every input is passed in (inventory rows, tu_map rows, {wb_va: [paths]},
    {rva: wb_va}, {rva: lead row}, {rva: [ledger names]})."""
    index = MapIndex(map_rows)
    paths = {}
    for row in inventory:
        if row["binary"] != "worldbuilder.exe" or row["producer_root"] == "tools-worldbuilder":
            continue
        if "unaligned" in row["flags"]:
            continue    # an ambiguous cut stays in the inventory, flagged, but leads nowhere
        key = row["normalized"].lower()
        slot = paths.setdefault(key, {"path": row["normalized"], "producer_root": row["producer_root"],
                                      "in_game_dat": row["present_in_game_dat"] == "yes", "raw": set()})
        slot["raw"].add(row["path"])
    by_path = {}
    for rva, lead in leads.items():
        wb_va = pairs.get(rva)
        for key in dict.fromkeys(body_files.get(wb_va, ())):
            by_path.setdefault(key, []).append((rva, wb_va, lead))
    out = []
    for key, slot in sorted(paths.items()):
        if key in index.lower:
            continue
        cands = []
        for rva, wb_va, lead in sorted(by_path.get(key, ()), key=lambda c: c[0]):
            row = index.covering(rva) or {}
            cands.append({"rva": f"0x{rva:08X}", "wb_va": f"0x{wb_va:08X}", "wb_name": lead.get("wb_name", ""),
                          "score": lead.get("score", ""), "owner": "|".join(names.get(rva, ())),
                          "source": row.get("source", ""), "tu": row.get("tu", ""),
                          "confidence": row.get("confidence", "")})
        alts = [{"tu": tu, "rows": dict(sorted(index.tus[tu].items()))}
                for tu in sorted(index.by_base.get(posixpath.basename(key), ()))]
        out.append({"path": slot["path"], "producer_root": slot["producer_root"], "in_game_dat": slot["in_game_dat"],
                    "raw": sorted(slot["raw"]), "candidates": cands,
                    "alternatives": alts})
    return out


def triage_items(map_rows, root=ROOT):
    """(items, note) for tools/next_work.py's tu-evidence tier: one investigate-only lead per
    non-editor WorldBuilder path the live TU map has no TU for."""
    missing = [p for p in (OUT, LEADS, WB_FUNCTIONS, WB_MATCHES, FUNCTIONS) if not (root / p).exists()]
    if missing:
        return [], f"no WorldBuilder path leads ({', '.join(p.as_posix() for p in missing)} absent)"
    leads = _leads(root)
    pairs = wb_pairs(root)
    leads = {rva: lead for rva, lead in leads.items() if rva in pairs}
    records = triage(read(root), map_rows, wb_body_files(root), pairs, leads, _ledger_names(root, set(leads)))
    items = []
    for rec in records:
        cands = rec["candidates"]
        shown = "; ".join(f"{c['rva']} WB {c['wb_name'] or '?'} (score {c['score']}) owner "
                          f"{c['owner'] or '-'} in {c['source'] or '-'} tu {c['tu'] or '-'} "
                          f"{c['confidence'] or 'unassigned'}" for c in cands[:6])
        alts = ", ".join(a["tu"] + " (" + ", ".join(f"{k or 'unrated'} {n}" for k, n in a["rows"].items()) + ")"
                         for a in rec["alternatives"])
        items.append({
            "tier": "tu-evidence", "check": "wb-path", "function": rec["path"], "source": rec["path"],
            "target_rva": cands[0]["rva"] if cands else "", "size": 0, "count": max(1, len(cands)),
            "rows": len(cands), "sources": sorted({c["source"] for c in cands if c["source"]}),
            "wb_path": rec,
            "credit_note": f"WorldBuilder path lead, {len(cands)} paired game RVA(s)",
            "why": (f"WorldBuilder ({rec['producer_root']}) pushes {rec['path']}; the live TU map has no TU of that "
                    f"spelling. game.dat's own strings {'carry' if rec['in_game_dat'] else 'do not carry'} it"
                    + (f". Paired game RVAs (wb_name_leads, every file the WB body pushes): {shown}"
                       + (f" (+{len(cands) - 6} more)" if len(cands) > 6 else "") if cands
                       else ". No wb_name_leads pairing reaches a WB body that pushes it")
                    + (f". Same-basename TUs in the map: {alts}" if alts else ". No same-basename TU in the map")
                    + ". Donor fact only: the path proves the spelling existed in WorldBuilder, not that a game "
                      "function belongs to it"),
            "start": (f"{START} python3 tools/wb_source_paths.py triage --path {rec['path']}; "
                      + (f"tools/wb_show.py {cands[0]['rva']} --gd; " if cands else "")
                      + "approval only through tools/tu_map.py's own evidence (wb_name_leads + w_score, F/Z/S "
                        "anchors via tools/name_evidence.py and tools/rename.py)"),
            "claim": [f"file:{rec['path']}"],
            "pass_test": ("the map rebuilt from current inputs gives the paired rows a TU by its own gates, or the "
                          "lead is recorded as not this file (tools/re_log.py); never commit a regenerated map from "
                          "this lane"),
        })
    with_cands = sum(1 for i in items if i["rows"])
    return items, f"{len(items)} WorldBuilder path lead(s) with no TU in the map ({with_cands} with paired game RVAs)"


# ---------------------------------------------------------------- cli

def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    sub = ap.add_subparsers(dest="cmd", required=True)
    sub.add_parser("inventory", help=f"rewrite {OUT} from the two images")
    sub.add_parser("check", help=f"exit 1 when {OUT} differs from a rebuild")
    t = sub.add_parser("triage", help="print the TU-evidence leads")
    t.add_argument("--json", action="store_true")
    t.add_argument("--path", help="only this normalized path (case-insensitive)")
    t.add_argument("--limit", type=int, default=0)
    args = ap.parse_args(argv)
    if args.cmd in ("inventory", "check"):
        text = render(build())
        if args.cmd == "inventory":
            (ROOT / OUT).write_text(text, encoding="utf-8", newline="")
            print(f"wrote {OUT.as_posix()}: {text.count(chr(10)) - 1} row(s)")
            for binary, by in summary(list(csv.DictReader(io.StringIO(text)))).items():
                for producer, s in by.items():
                    print(f"  {binary:16} {producer:18} {s['strings']:5} string(s) {s['paths']:5} path(s) "
                          f"{s['in_game_dat']:5} in game.dat")
            return 0
        current = (ROOT / OUT).read_text(encoding="utf-8") if (ROOT / OUT).exists() else ""
        if current != text:
            print(f"{OUT} is stale: run python3 tools/wb_source_paths.py inventory", file=sys.stderr)
            return 1
        print(f"{OUT} matches a rebuild")
        return 0
    sys.path.insert(0, str(ROOT / "tools"))
    import tu_skeleton
    items, note = triage_items(tu_skeleton.map_rows())
    if args.path:
        items = [i for i in items if i["function"].lower() == args.path.lower().replace("\\", "/")]
    if args.limit:
        items = items[:args.limit]
    if args.json:
        print(json.dumps([i["wb_path"] for i in items], indent=1))
    else:
        print(note)
        for item in items:
            print(f"\n{item['function']}\n  why:   {item['why']}\n  start: {item['start']}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
