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
