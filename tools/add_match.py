#!/usr/bin/env python3
"""Append ONE matched row to reverse/functions.csv, safely.

Hand-editing the ledger has repeatedly corrupted it (mixed line terminators,
wrong column counts, duplicate/overlapping claims). This tool is the safe path:
it validates the claim against the existing ledger, appends with canonical LF,
strips the source's `// <name> present-unmatched` marker,
and byte-verifies the result
with ./build.sh — reverting everything if verification fails. A row never
survives unverified (unless you explicitly pass --no-verify).

Usage:
  python3 tools/add_match.py <mangled-name> <target_rva> <target_size> <source> \\
      [--notes TEXT] [--replace-existing] [--no-verify] [--root DIR]

`--replace-existing` safely repoints the symbol's one existing ledger row before
verification.  `--replace-rva` does the same keyed on the ADDRESS instead of the
name, which is the only way to convert a machine byte-dump: a real conversion
changes the name (`?d_000a8940@@YAXXZ` -> `?addr@SpikeAccessor@@QAEPADXZ`), so
--replace-existing cannot find the row it needs to retire and add_match refuses
the address as already claimed.  It accepts scaffold rows only.  This is the supported path for replacing a 5-byte MASM thunk
claim with the clean C++ body it jumps to; the original row is restored if the
new claim does not byte-verify.
"""

import argparse
import csv
import io
import os
import re
import subprocess
import sys
from pathlib import Path

import ledger_io
from portable_lock import lock

DEFAULT_ROOT = Path(__file__).resolve().parents[1]

MARKER_RE = re.compile(r"^\s*//\s*(\S+)\s+present-unmatched\b")


def fail(*lines):
    for line in lines:
        print(f"add_match: {line}", file=sys.stderr)
    raise SystemExit(1)


def parse_ledger(raw):
    """Strict parse: any malformed row means the ledger is already corrupt and
    our duplicate/overlap validations cannot be trusted — refuse to append."""
    text = raw.decode("utf-8", errors="replace")
    rows = []
    for i, r in enumerate(csv.reader(io.StringIO(text)), start=1):
        if i == 1 or not r or (len(r) == 1 and not r[0]):
            continue
        if len(r) != 7:
            fail(
                f"functions.csv line {i} has {len(r)} fields, expected 7: {r[:3]}...",
                "the ledger is corrupt — fix it first: python3 tools/check_csv.py",
            )
        name, _export, target_rva, target_size, source, status, notes = r
        try:
            rva = int(target_rva, 16)
        except ValueError:
            fail(
                f"functions.csv line {i} ({name}): unparseable target_rva '{target_rva}'",
                "the ledger is corrupt — fix it first: python3 tools/check_csv.py",
            )
        try:
            size = int(target_size) if target_size else 0
        except ValueError:
            fail(
                f"functions.csv line {i} ({name}): unparseable target_size '{target_size}'",
                "the ledger is corrupt — fix it first: python3 tools/check_csv.py",
            )
        rows.append(
            {
                "line": i,
                "name": name,
                "rva": rva,
                "size": size,
                "source": source,
                "status": status,
                "notes": notes,
            }
        )
    return rows


def ledger_key(fields):
    """Return the semantic identity used when rewriting one ledger row."""
    if len(fields) < 3:
        return None
    try:
        return fields[0], int(fields[2], 16)
    except ValueError:
        return None


def strip_marker(source_path, name):
    """Remove the `// <token> present-unmatched` line whose token is the full
    mangled name or a prefix of it (markers are often truncated at a @@, e.g.
    `// ?getUnicodeString@Dict@@ present-unmatched`). Byte-level line surgery so
    the file's own line endings survive untouched. Returns new bytes or None."""
    raw = source_path.read_bytes()
    lines = raw.splitlines(keepends=True)
    exact, prefix = [], []
    for index, line in enumerate(lines):
        match = MARKER_RE.match(line.decode("utf-8", errors="replace"))
        if not match:
            continue
        token = match.group(1)
        if token == name:
            exact.append(index)
        elif name.startswith(token):
            prefix.append(index)
    candidates = exact or prefix
    if not candidates:
        return None
    victim = candidates[0]
    stripped = lines[victim].rstrip(b"\r\n").decode("utf-8", errors="replace")
    print(
        f"add_match: stripping marker at {source_path.name}:{victim + 1}: {stripped.strip()}"
    )
    return b"".join(lines[:victim] + lines[victim + 1 :])


def lookup_export_rva(root, name):
    exports = root / "reverse" / "exports.csv"
    if not exports.exists():
        # exports.csv is generated (gitignored); its absence only costs the
        # optional export_rva column, so say so instead of silently omitting
        print(
            "add_match: note: reverse/exports.csv not present — export_rva left empty"
        )
        return ""
    with exports.open(encoding="utf-8", newline="") as handle:
        for row in csv.DictReader(handle):
            if row["kind"] == "code" and row["name"] == name:
                return row["rva"]
    return ""


def remove_stash(rva, root):
    """Drop the banked attempt for `rva` now that real C++ owns the address.

    Only ever called after verification passes: the revert paths above restore
    the tree, and a stash deleted there would take the next agent's head start
    with it. tools/add_match_batch.py writes the ledger on its own and does NOT
    call this, so a batch landing leaves its stash for check_csv to flag.
    """
    stash = Path(root) / "reverse" / "attempts" / f"0x{rva:08x}.cpp"
    if stash.exists():
        stash.unlink()
        print(
            f"add_match: cleared banked attempt {stash.relative_to(Path(root)).as_posix()}"
        )


def record_landing(root, name, rva, size, source_rel, notes):
    """Append the `landed` verdict and report the deferrals this landing may free."""
    record_landings(root, [(name, rva, size, source_rel, notes)])


def record_landings(root, landed):
    """Append `landed` for each (name, rva, size, source, notes); report who was waiting.

    Without it the log's last word on a landed function stayed whatever the
    previous attempt wrote -- ChunkLoadClass::Seek landed with five `blocked`
    rows and nothing after them -- and the rows parked behind it (two motion
    channel constructors citing "unresolved Seek 6150C0") had no way to learn
    their wall was gone. One read of the log for the whole batch. Advisory: a
    verified row is never reverted over this, and a `landed` whose row a later
    gate or revert removes stops standing (re_log._load).
    """
    import re_log

    log = Path(root) / "reverse" / "re_attempts.log"
    if not log.exists() or not landed:
        return
    try:
        eol = ledger_io.lf_terminator(log.read_bytes(), "re_attempts.log")
        for name, rva, size, source_rel, notes in landed:
            evidence = f"add_match verified {source_rel} {size}B"
            if notes:
                evidence += f"; {notes}"
            re_log.append(name, f"0x{rva:08X}", str(size), "landed", evidence,
                          eol=eol, path=log)
        print(f"add_match: recorded `landed` x{len(landed)} in reverse/re_attempts.log -- stage it")
        if log.resolve() != re_log.RE_ATTEMPTS.resolve():
            return
        freed = []
        for name, rva, *_ in landed:
            freed.extend((rva, row) for row in re_log.cites(rva, name))
    except (Exception, SystemExit) as error:  # the LF refusal is a SystemExit
        print(f"add_match: could not record the landing (row stays live): {error}",
              file=sys.stderr)
        return
    for rva, (symbol, at, status, text) in freed:
        print(f"add_match: may unblock {symbol} @ 0x{at:08X} ({status}): {text[:160]}")
    if freed:
        print("add_match: land these, or re-record any that waited on a landed body "
              "with blocked-on=0x<its rva> so the queue serves it as untried")


def add_callee_pins(specs, root, name):
    """Write each --pin NAME=0xRVA through tools/pin_admission.add_pins: its rules,
    the pin_consistency check, then a hatch-register admission of exactly these
    pins (a hand-typed pin stays refused). Returns a callable that restores
    symbols.csv and the register when the row does not verify."""
    if not specs:
        return lambda: None
    if root != DEFAULT_ROOT.resolve():
        fail("--pin works on the live tree only (pin_admission reads build.ROOT)")
    pins = []
    for spec in specs:
        pin_name, sep, address = spec.rpartition("=")
        if not sep or not pin_name:
            fail(f"--pin {spec!r}: expected NAME=0xRVA")
        pins.append((pin_name, address))
    import hatch_counters
    import pin_admission

    saved = {path: path.read_bytes() if path.exists() else None
             for path in (root / pin_admission.PINS, root / hatch_counters.BASELINE)}

    def restore():
        for path, data in saved.items():
            if data is not None:
                path.write_bytes(data)

    problems = pin_admission.add_pins(pins, notes=f"callee of {name}",
                                      reason=f"add_match --pin for {name}")
    if problems:
        restore()
        fail("pin admission refused (nothing written):", *problems[:20])
    return restore


def main():
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter
    )
    parser.add_argument("name", help="decorated (mangled) symbol name")
    parser.add_argument("target_rva", help="RVA of the function body, hex (0x...)")
    parser.add_argument("target_size", help="function size in bytes, decimal")
    parser.add_argument("source", help="repo-relative source path (src/...)")
    parser.add_argument("--notes", default="", help="notes column text (no commas)")
    parser.add_argument(
        "--icf-owner",
        help="existing matched symbol at the same RVA and size; "
        "allows a verified identical-code-folding alias",
    )
    parser.add_argument(
        "--replace-existing",
        action="store_true",
        help="replace the symbol's one existing row instead of rejecting it; "
        "the old row is restored if verification fails",
    )
    parser.add_argument(
        "--replace-rva",
        metavar="RVA",
        help="retire the SCAFFOLD row at this address and claim it "
        "under the new name (the dump -> C++ conversion path); "
        "the old row is restored if verification fails",
    )
    parser.add_argument(
        "--pin",
        action="append",
        default=[],
        metavar="NAME=0xRVA",
        help="a callee pin this body needs; judged by tools/pin_admission.py "
        "(its rules + pin_consistency), appended to reverse/symbols.csv and "
        "admitted in the hatch register; removed if verification fails (repeatable)",
    )
    parser.add_argument(
        "--no-verify",
        action="store_true",
        help="skip ./build.sh verification (row lands UNVERIFIED — "
        "verify before committing)",
    )
    parser.add_argument(
        "--root",
        type=Path,
        default=DEFAULT_ROOT,
        help="TEST-ONLY: operate on a copy of the repo rooted here "
        "instead of the live ledger (default: repo root)",
    )
    args = parser.parse_args()

    root = args.root.resolve()
    functions_csv = root / "reverse" / "functions.csv"
    if not functions_csv.exists():
        fail(f"no ledger at {functions_csv}")

    name = args.name
    try:
        rva = int(args.target_rva, 16)
    except ValueError:
        fail(f"target_rva '{args.target_rva}' is not hex (expected e.g. 0x00812340)")
    try:
        size = int(args.target_size)
    except ValueError:
        fail(f"target_size '{args.target_size}' is not a decimal byte count")
    if size <= 0:
        fail(f"target_size must be positive, got {size}")

    source_rel = (
        args.source.lstrip("./") if not Path(args.source).is_absolute() else None
    )
    if source_rel is None:
        try:
            source_rel = Path(args.source).resolve().relative_to(root).as_posix()
        except ValueError:
            fail(f"source {args.source} is not under {root}")
    source_path = root / source_rel
    if not source_path.exists():
        fail(
            f"source does not exist: {source_path}",
            "a ledger row must never point at a missing file",
        )

    for label, value in [
        ("name", name),
        ("source", source_rel),
        ("--notes", args.notes),
    ]:
        bad = set(value) & set(',"\r\n')
        if bad:
            fail(
                f"{label} contains {sorted(bad)} — functions.csv rows are raw "
                "comma-joined fields with no quoting, this would corrupt the ledger"
            )

    # Exclusive lock across validate->append->verify so concurrent agents cannot
    # interleave appends or double-claim, and so revert-on-failure cannot clobber
    # a row someone else appended meanwhile.
    lock_file = (root / "reverse" / ".add_match.lock").open("a")
    lock(
        lock_file,
        exclusive=True,
        wait_notice="add_match: waiting for ledger lock (another add_match is running)...",
    )

    raw = functions_csv.read_bytes()
    if not raw.endswith(b"\n"):
        fail(
            "functions.csv does not end with a newline (truncated last row?) — "
            "fix the ledger before appending"
        )
    eol = ledger_io.lf_terminator(raw, "functions.csv")

    rows = parse_ledger(raw)
    claims = [row for row in rows if row["name"] == name]
    replaced = None
    if args.replace_rva:
        if args.replace_existing:
            fail(
                "--replace-rva and --replace-existing are alternatives: one keys "
                "on the address, the other on the name"
            )
        try:
            old_rva = int(args.replace_rva, 16)
        except ValueError:
            fail(f"--replace-rva '{args.replace_rva}' is not hex")
        at_rva = [row for row in rows if row["rva"] == old_rva]
        if len(at_rva) != 1:
            fail(
                f"--replace-rva 0x{old_rva:08X} matches {len(at_rva)} rows; "
                "it retires exactly one"
            )
        # gen-dump rows pin bytes with no identity; gen-alias rows (dup_*
        # names served by another object's identical body) carry no identity
        # of their own either. AGENTS.md: a gen-* placeholder yields to a real
        # name. Everything else is a real claim and must be retracted on its own.
        if not at_rva[0]["notes"].lstrip().startswith(("gen-dump", "gen-alias")):
            fail(
                f"--replace-rva 0x{old_rva:08X} is {at_rva[0]['name']} "
                f"({at_rva[0]['source']}), not a gen-dump or gen-alias scaffold row",
                "only scaffolding may be taken over by name; retract a real claim "
                "in its own commit so the retraction is reviewable",
            )
        replaced = at_rva[0]
    if args.replace_existing:
        if len(claims) != 1:
            fail(
                f"--replace-existing requires exactly one existing row for {name}; "
                f"found {len(claims)}"
            )
        replaced = claims[0]
    elif claims:
        addresses = ", ".join(
            f"0x{row['rva']:08X} ({row['source']}, {row['status']})" for row in claims
        )
        fail(
            f"{name} is already in the ledger at {addresses}",
            "one name = one address; use --replace-existing only when deliberately "
            "repointing that claim",
        )

    new_end = rva + size
    icf_owner = None
    if args.icf_owner:
        owners = [row for row in rows if row["name"] == args.icf_owner]
        if len(owners) != 1:
            fail(f"--icf-owner {args.icf_owner} must name exactly one existing row")
        icf_owner = owners[0]
        if (
            icf_owner["status"] != "matched"
            or icf_owner["rva"] != rva
            or icf_owner["size"] != size
        ):
            fail(
                f"--icf-owner {args.icf_owner} is not a matched {size}-byte claim "
                f"at 0x{rva:08X}"
            )
    for row in rows:
        if row is replaced:
            continue
        same_icf_group = (
            icf_owner is not None
            and row["status"] == "matched"
            and row["rva"] == rva
            and row["size"] == size
        )
        if row["rva"] == rva:
            if same_icf_group:
                continue
            fail(
                f"target_rva 0x{rva:08X} is already claimed by {row['name']} "
                f"({row['source']}, {row['status']}, line {row['line']})"
            )
        if (
            row["status"] == "matched"
            and row["rva"] < new_end
            and rva < row["rva"] + row["size"]
        ):
            if same_icf_group:
                continue
            fail(
                f"range [0x{rva:08X}, 0x{new_end:08X}) overlaps matched row "
                f"{row['name']} [0x{row['rva']:08X}, 0x{row['rva'] + row['size']:08X}) "
                f"({row['source']}, line {row['line']})"
            )
    export_rva = lookup_export_rva(root, name)
    ledger_row = (
        f"{name},{export_rva},0x{rva:08X},{size},{source_rel},matched,{args.notes}"
    )

    saved_source = source_path.read_bytes()
    restore_pins = add_callee_pins(args.pin, root, name)
    new_source = strip_marker(source_path, name)
    if new_source is not None:
        source_path.write_bytes(new_source)

    if replaced is not None:
        # Drop the old row by CONTENT, not by line number. parse_ledger numbers
        # CSV records while a malformed terminator can make physical-line
        # indexing disagree. ledger_io preserves every retained record byte for
        # byte and the uniform-terminator guard above refuses mixed input.
        key = (replaced["name"], replaced["rva"])
        new_raw, dropped = ledger_io.rewrite(raw, lambda f: ledger_key(f) != key)
        if dropped != 1:
            fail(
                f"internal error: {dropped} ledger rows match {key} — "
                "expected exactly one"
            )
        functions_csv.write_bytes(new_raw + ledger_row.encode("utf-8") + eol)
        print(
            f"add_match: replaced row {replaced['line']}: "
            f"0x{replaced['rva']:08X}/{replaced['size']}B {replaced['source']}"
        )
        print(f"add_match: with: {ledger_row}")
    else:
        with functions_csv.open("ab") as handle:
            handle.write(ledger_row.encode("utf-8") + eol)
        print(f"add_match: appended: {ledger_row}")

    if args.no_verify:
        print(
            "add_match: --no-verify: row is UNVERIFIED — run "
            f"./build.sh {source_rel} before committing"
        )
        return

    build_sh = root / "build.sh"
    if not build_sh.exists():
        # revert: an unverifiable row must not survive
        functions_csv.write_bytes(raw)
        source_path.write_bytes(saved_source)
        restore_pins()
        fail(f"no build.sh at {root} — cannot verify; append reverted")

    if sys.platform == "win32":
        verify_cmd = [sys.executable, str(root / "tools" / "build.py"), source_rel]
        verify_label = f"{sys.executable} tools/build.py {source_rel}"
    else:
        verify_cmd = [str(build_sh), source_rel]
        verify_label = f"./build.sh {source_rel}"
    print(f"add_match: verifying: {verify_label}")
    try:
        result = subprocess.run(verify_cmd, cwd=root)
    except BaseException:
        functions_csv.write_bytes(raw)
        source_path.write_bytes(saved_source)
        restore_pins()
        print(
            "add_match: interrupted — append and marker strip REVERTED", file=sys.stderr
        )
        raise
    if result.returncode != 0:
        functions_csv.write_bytes(raw)
        source_path.write_bytes(saved_source)
        restore_pins()
        fail(
            f"verification failed (exit {result.returncode}) — append and "
            "marker strip REVERTED; nothing was changed"
        )
    print("add_match: verified OK — row is live")
    remove_stash(rva, args.root)
    record_landing(root, args.name, rva, size, source_rel, args.notes)
    if root == DEFAULT_ROOT.resolve() and os.environ.get("BFME_CLAIMS", "on") != "off":
        # Verification has landed this body; a worker no longer needs its
        # shared work claim. A test-only --root must never touch origin.
        try:
            import claims

            claims.release([rva], force=True)
        except Exception as error:  # advisory; the ref expires on its own
            print(
                f"add_match: could not release shared claim: {error}", file=sys.stderr
            )


if __name__ == "__main__":
    main()
