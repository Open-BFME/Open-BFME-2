"""Terminator-preserving ledger rewrite. The ONLY safe way to drop/edit rows.

Parse records with csv.reader for identity, but rewrite by operating on the raw
bytes record-by-record. The Open-BFME-2 ledgers are LF-only; retaining each
record's bytes and refusing mixed input keeps union merges deterministic.
"""
import collections
import csv
import io
import re

TERM = re.compile(rb"\r*\n")


def local_funclet(row):
    """A raw compiler label with explicit parent ownership, never an alias.

    This identifies a ledger namespace only. The byte gate must establish the
    label's local COFF storage and its exact parent EH location independently.
    """
    source = row.get("source", "").replace("\\", "/")
    tokens = [token.strip() for token in row.get("notes", "").split(";")]
    parents = [token[7:] for token in tokens if token.startswith("parent=")]
    return bool(re.fullmatch(r"\$L\d+", row.get("name", ""))
                and source.startswith("Code/") and source.endswith(".cpp")
                and not source.startswith(("Code/gen_asm/", "Code/gen_small/"))
                and "gen-funclet" in tokens
                and len(parents) == 1 and parents[0]
                and not any(token.startswith("object-symbol=") for token in tokens))


LOCAL_STATIC = re.compile(r"_\$E\d+")


def local_static(row):
    """A compiler-local `_$E<n>` initializer or atexit callback, never an alias.

    Every object numbers its own, so two TUs' `_$E2` are different functions.
    This identifies a ledger namespace only. The byte gate must read the row
    from that name's single local COFF definition in the row's own object.
    """
    source = row.get("source", "").replace("\\", "/")
    tokens = [token.strip() for token in row.get("notes", "").split(";")]
    return bool(LOCAL_STATIC.fullmatch(row.get("name", ""))
                and source.startswith("Code/") and source.endswith(".cpp")
                and not source.startswith(("Code/gen_asm/", "Code/gen_small/"))
                and not any(token.startswith(("object-symbol=", "gen-")) for token in tokens))


def same_function_name(left, right):
    """External names are global; proven compiler labels belong to one TU."""
    if left["name"] != right["name"]:
        return False
    if (local_funclet(left) and local_funclet(right)
            or local_static(left) and local_static(right)):
        return left["source"].replace("\\", "/") == right["source"].replace("\\", "/")
    return True


def local_label_hint(identity, claims):
    """Why a `$L<n>` row collided, when per-TU scoping would have let it through.

    A compiler label is not a global name: same_function_name scopes one to its
    source when BOTH rows satisfy local_funclet. A bare duplicate-name refusal
    does not say so, and advice to repoint the existing claim is wrong here --
    that claim belongs to another TU. 144 open add_match and 13 open check_csv
    false-reject records are this: a worker read the refusal as a verdict on
    identity when it was a verdict on notes.

    `identity` is the proposed row, `claims` the rows already holding the name.
    Returns the missing condition, or None when the name is not a label or the
    collision is genuine (same source, or a peer that is itself unscoped).
    """
    name = identity.get("name", "")
    if not re.fullmatch(r"\$L\d+", name):
        return None
    source = identity.get("source", "").replace("\\", "/")
    tokens = [token.strip() for token in identity.get("notes", "").split(";")]
    parents = [token[7:] for token in tokens if token.startswith("parent=")]
    if not (source.startswith("Code/") and source.endswith(".cpp")):
        missing = "its source must be a Code/**.cpp translation unit"
    elif source.startswith(("Code/gen_asm/", "Code/gen_small/")):
        missing = ("its source is a generated tree, which owns its own labels; "
                   "a label scopes only to a hand-written TU")
    elif "gen-funclet" not in tokens:
        missing = "its notes must carry a `gen-funclet` token"
    elif len(parents) != 1 or not parents[0]:
        missing = ("its notes must carry exactly one non-empty `parent=<owner>` "
                   f"token (found {len(parents)})")
    elif any(token.startswith("object-symbol=") for token in tokens):
        missing = ("its notes carry `object-symbol=`, which marks generator "
                   "scaffolding rather than a proven label, so it stays global")
    else:
        unscoped = [row for row in claims if not local_funclet(row)]
        if not unscoped:
            return None            # same source: a real duplicate, not scoping
        # The addresses are already in the caller's first line; name the sources,
        # which is what says WHICH row needs the notes.
        return (f"{name} would scope to {source}, but the row already holding it "
                "is not itself a proven label: " +
                ", ".join(sorted({row["source"].replace("\\", "/")
                                  for row in unscoped})) +
                ". Both sides must satisfy ledger_io.local_funclet before the "
                "same label can name two addresses.")
    return (f"{name} is a compiler-local label, which belongs to ONE translation "
            f"unit, not to the image: {missing}. Scope it and this collision goes "
            "away -- do not reach for --replace-existing, which repoints the "
            "other TU's claim. See ledger_io.local_funclet.")


def split_records(raw):
    """[(payload_bytes, terminator_bytes)] over the whole file, order preserved."""
    out, pos = [], 0
    for m in TERM.finditer(raw):
        out.append((raw[pos:m.start()], m.group(0)))
        pos = m.end()
    if pos != len(raw):
        raise ValueError("ledger does not end with a newline (truncated last row?)")
    return out


def fields(payload):
    return next(csv.reader(io.StringIO(payload.decode("utf-8"))), [])


def terminator_census(raw):
    """{terminator_bytes: [1-based line numbers]}, in file order.

    Matches the terminators only rather than reusing split_records: this runs in
    the commit hook over a 4 MB symbols.csv, and slicing out 70,000 payloads it
    never reads took the walk from 109ms to 145ms.
    """
    census = collections.defaultdict(list)
    end = 0
    for number, match in enumerate(TERM.finditer(raw), 1):
        census[match.group(0)].append(number)
        end = match.end()
    if end != len(raw):
        raise ValueError("ledger does not end with a newline (truncated last row?)")
    return census


def uniform_terminator(raw, label):
    """The one line ending `raw` uses; a file mixing two is not appendable.

    reverse/symbols.csv is `merge=union`. A pin differing from its twin only by a
    `\\r` is a DISTINCT line to the merge driver, so the same pin lands twice and
    every later rebase compounds it -- that is how 4,172 pins became 8,784.
    Matching the file keeps each batch a pure append.

    Open-BFME-2 applies the same uniform-terminator rule to every union-merged
    ledger, including functions.csv.
    """
    census = terminator_census(raw)
    if len(census) > 1:
        spelling = {b"\n": "LF", b"\r\n": "CRLF", b"\r\r\n": "CRCRLF"}
        detail = "; ".join(
            f"{spelling.get(term, repr(term))} on {len(lines)} line(s) "
            f"(first {lines[0]})" for term, lines in sorted(census.items()))
        raise SystemExit(f"{label} mixes line terminators -- {detail}. Union-merging it "
                         "duplicates every row whose terminator differs. Repair it with "
                         "python3 tools/dedup_csv.py before appending.")
    return next(iter(census), b"\n")


def lf_terminator(raw, label):
    """Require the canonical Open-BFME-2 LF terminator and return it."""
    eol = uniform_terminator(raw, label)
    if eol != b"\n":
        raise SystemExit(f"{label} must use LF line endings; normalize it before appending")
    return eol


def rewrite(raw, keep):
    """keep(fields) -> True to retain the record. Terminators are preserved."""
    kept, dropped = [], 0
    for payload, term in split_records(raw):
        if keep(fields(payload)):
            kept.append(payload + term)
        else:
            dropped += 1
    return b"".join(kept), dropped
