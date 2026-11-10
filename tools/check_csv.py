#!/usr/bin/env python3
"""Fast integrity check for reverse/functions.csv, symbols.csv and data_rows.csv (<1s).

Catches the corruption classes that break the full gate long after the fact:
duplicate rows from union merges, two agents claiming overlapping bytes,
malformed rows, rows pointing at missing sources, and mixed line terminators in
the union-merged ledgers. Run it before committing, after every merge/rebase,
and in hooks.

Exit 0: both ledgers clean. Exit 1: every problem printed with the fix.
"""
import argparse
import csv
import io
import re
import subprocess
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import ledger_io  # noqa: E402  (after the path insert that makes it importable)

ROOT = Path(__file__).resolve().parents[1]
FUNCTIONS = ROOT / "reverse" / "functions.csv"
SYMBOLS = ROOT / "reverse" / "symbols.csv"
DELETED = ROOT / "reverse" / "deleted_rows.csv"
RE_ATTEMPTS = ROOT / "reverse" / "re_attempts.log"
BODY_OWNERS = ROOT / "reverse" / "body_owners.csv"
DATA_ROWS = ROOT / "reverse" / "data_rows.csv"

# realcrc.cpp is linked twice in the retail exe, so these two symbols
# legitimately appear at two addresses each. Any other duplicate name is a bug.
ALLOWED_DUP_NAMES = {
    "?CRC_Memory@@YAKPBEKK@Z",
    "?CRC_String@@YAKPBDK@Z",
}

FUNCTIONS_HEADER = "name,export_rva,target_rva,target_size,source,status,notes"
SYMBOLS_HEADER = "name,address,notes"


def placeholder_row(name, source, notes):
    """Distinguish generated scaffolding from a byte-verified named ICF twin.

    gen-alias is also the verifier's exact marker for relocation twins. A real
    method emitting its own body can carry it; the marker alone does not make
    that method a generated identity. Synthetic aliases still yield to owners.
    Full-byte verification independently validates every claimed twin.
    """
    notes = notes.lstrip()
    if not notes.startswith("gen-"):
        return False
    if notes.split(";", 1)[0].strip() != "gen-alias":
        return True
    return (source.replace("\\", "/").startswith(("Code/gen_asm/", "Code/gen_small/"))
            or re.match(r"^(?:\??(?:dup_|d_[0-9a-fA-F]|Gen_)|\?\?[01]Gen_)", name) is not None)


LF_READ = set()     # what check_lf_ledger was given in this verdict, so a new register cannot miss check_lf_rules


def check_lf_ledger(raw, label, problems, *, allow_empty=False):
    """Require canonical LF framing for one union-merged ledger."""
    LF_READ.add(label)
    if allow_empty and not raw:
        return
    try:
        census = ledger_io.terminator_census(raw)
    except ValueError as exc:
        problems.append(f"{label}: {exc}")
        return
    if set(census) == {b"\n"}:
        return
    spelling = {b"\n": "LF", b"\r\n": "CRLF", b"\r\r\n": "CRCRLF"}
    detail = "; ".join(
        f"{spelling.get(term, repr(term))} on {len(lines)} line(s) "
        f"(line {lines[0]})" for term, lines in sorted(census.items()))
    problems.append(
        f"{label} must use LF line terminators: {detail}. It is union-merged, "
        "so differently terminated rows duplicate on the next rebase.")


def check_lf_rules(spec, problems):
    """Every ledger check_lf_ledger read must have eol=lf in .gitattributes at `spec`. Without it a Windows checkout
    turns the file CRLF and check_lf_ledger fails there alone, which no Linux check can see (2026-11-09: master was red
    for an hour over forced_row_moves.csv)."""
    rels = [f"reverse/{label}" for label in sorted(LF_READ)]
    if not rels:
        return
    where = [] if spec is None else ["--cached"] if spec == "" else [f"--source={spec}"]
    out = subprocess.run(["git", "-C", str(ROOT), "check-attr", *where, "eol", "--", *rels],
                         capture_output=True, text=True)
    if out.returncode:
        problems.append(f"cannot read the eol rules of {', '.join(rels)}: {out.stderr.strip()}")
        return
    rules = dict(line.split(": eol: ", 1) for line in out.stdout.splitlines())
    for rel in rels:
        if rules.get(rel) != "lf":
            problems.append(f"{rel} must stay LF, but .gitattributes gives it eol={rules.get(rel)}: a Windows checkout "
                            f"would turn it CRLF and fail there alone. Add `{rel} text eol=lf merge=union`.")


def read_ledger(path, spec):
    """spec: None = working tree, "" = git index (staged), else a ref/SHA."""
    if spec is None:
        return path.read_bytes()
    rel = path.relative_to(ROOT).as_posix()
    out = subprocess.run(["git", "-C", str(ROOT), "show", f"{spec}:{rel}"],
                         capture_output=True)
    if out.returncode != 0:
        raise SystemExit(f"check_csv: cannot read {spec}:{rel}: "
                         f"{out.stderr.decode().strip()}")
    return out.stdout


def read_blobs(rels, spec):
    """{rel: bytes} for many paths in one `git cat-file --batch` (read_ledger's
    one `git show` per path cost ~4.5s over the attempt bank, every commit)."""
    if spec is None:
        return {rel: (ROOT / rel).read_bytes() for rel in rels}
    names = "".join(f"{spec}:{rel}\n" for rel in rels).encode()
    # Large requests and replies can block both sides writing to pipes on
    # macOS. File-backed streams preserve the batch protocol without that cycle.
    with tempfile.TemporaryFile() as request, tempfile.TemporaryFile() as output, \
            tempfile.TemporaryFile() as errors:
        request.write(names)
        request.seek(0)
        result = subprocess.run(["git", "-C", str(ROOT), "cat-file", "--batch"],
                                stdin=request, stdout=output, stderr=errors)
        output.seek(0)
        errors.seek(0)
        result = subprocess.CompletedProcess(result.args, result.returncode,
                                             output.read(), errors.read())
    result.check_returncode()
    out = result.stdout
    blobs, pos = {}, 0
    for rel in rels:
        end = out.index(b"\n", pos)
        header = out[pos:end].split()
        if header[-1] == b"missing":
            raise SystemExit(f"check_csv: cannot read {spec}:{rel}")
        size = int(header[2])
        blobs[rel] = out[end + 1:end + 1 + size]
        pos = end + 1 + size + 1
    return blobs


def known_sources(spec):
    """Sources a ledger row may legally reference for the given state.

    A row whose source exists on disk but is not in git is the worst failure
    class this tool guards: the row pushes fine locally and breaks every
    other clone ("references missing source file"). So worktree/staged modes
    require git-tracked (staged counts during a commit), and --ref mode
    requires presence in that commit's tree.
    """
    if spec:  # a ref/SHA
        out = subprocess.run(["git", "-C", str(ROOT), "ls-tree", "-r", "--name-only", spec],
                             capture_output=True, text=True)
        if out.returncode != 0:
            raise SystemExit(f"check_csv: git ls-tree {spec} failed: {out.stderr.strip()}")
        return set(out.stdout.splitlines())
    tracked = subprocess.run(["git", "-C", str(ROOT), "ls-files"],
                             capture_output=True, text=True)
    if tracked.returncode != 0:
        raise SystemExit(f"check_csv: git ls-files failed: {tracked.stderr.strip()}")
    allowed = set(tracked.stdout.splitlines())
    staged = subprocess.run(["git", "-C", str(ROOT), "diff", "--cached", "--name-only",
                             "--diff-filter=ACMRT"], capture_output=True, text=True)
    if staged.returncode == 0:
        allowed.update(staged.stdout.splitlines())
    return allowed


def tombstones(raw=None):
    """(name, rva) pairs deleted on purpose -> why. See reverse/deleted_rows.csv.

    functions.csv merges with git's union driver, which cannot express a
    deletion: any branch forked before the delete puts the row back with no
    conflict. Without this, a proven-wrong row silently returns to master.
    """
    if raw is None:
        if not DELETED.exists():
            return {}
        raw = DELETED.read_bytes()
    out = {}
    for line in raw.decode("utf-8", errors="replace").splitlines():
        if not line.strip() or line.startswith("#") or line.startswith("name,"):
            continue
        row = next(csv.reader(io.StringIO(line)))
        if len(row) < 2:
            continue
        try:
            out[(row[0], int(row[1], 16))] = row[2] if len(row) > 2 else ""
        except ValueError:
            continue
    return out


def check_functions(raw, problems, sources_ok, deleted_raw=None):
    deleted = tombstones(deleted_raw)
    check_lf_ledger(raw, "functions.csv", problems)
    text = raw.decode("utf-8", errors="replace")
    rows = list(csv.reader(io.StringIO(text)))
    if not rows or ",".join(rows[0]) != FUNCTIONS_HEADER:
        problems.append(f"functions.csv: bad header (expected '{FUNCTIONS_HEADER}')")
        return
    header_count = sum(1 for r in rows if ",".join(r) == FUNCTIONS_HEADER)
    if header_count > 1:
        problems.append(f"functions.csv: header appears {header_count} times "
                        "(bad merge). Fix: python3 tools/dedup_csv.py")

    seen_exact = set()
    by_rva = {}
    by_name = {}
    matched_ranges = []
    for i, r in enumerate(rows[1:], start=2):
        if not r or (len(r) == 1 and not r[0]):
            continue
        if len(r) != 7:
            problems.append(f"functions.csv line {i}: {len(r)} fields, expected 7: {r[:2]}...")
            continue
        name, export_rva, target_rva, target_size, source, status, _notes = r
        if not name:
            problems.append(f"functions.csv line {i}: empty name")
            continue
        if export_rva:
            try:
                int(export_rva, 16)
            except ValueError:
                problems.append(f"functions.csv line {i} ({name}): bad export_rva '{export_rva}'")
        if not target_rva:
            problems.append(f"functions.csv line {i} ({name}): empty target_rva")
            continue
        try:
            rva = int(target_rva, 16)
        except ValueError:
            problems.append(f"functions.csv line {i} ({name}): bad target_rva '{target_rva}'")
            continue
        try:
            size = int(target_size) if target_size else 0
        except ValueError:
            problems.append(f"functions.csv line {i} ({name}): bad target_size '{target_size}'")
            continue
        if status not in ("matched", "unmatched"):
            problems.append(f"functions.csv line {i} ({name}): bad status '{status}'")
        if status == "matched" and size <= 0:
            problems.append(f"functions.csv line {i} ({name}): matched with target_size {size}")
        if not source:
            problems.append(f"functions.csv line {i} ({name}): empty source")
        elif source not in sources_ok:
            hint = ("file exists on disk but is NOT tracked by git — `git add` it"
                    if (ROOT / source).exists()
                    else "a commit added rows without adding the file")
            problems.append(f"functions.csv line {i} ({name}): source not in git: {source} ({hint})")

        if (name, rva) in deleted:
            problems.append(f"functions.csv line {i}: {name} @ {target_rva} was deleted on "
                            f"purpose and has come back (a union merge from a branch that "
                            f"forked before the delete). Reason it was deleted: "
                            f"{deleted[(name, rva)]}. Drop the row again, or — if you can "
                            f"byte-prove it — remove its line from reverse/deleted_rows.csv "
                            f"in the same commit.")

        key = (name, target_rva)
        if key in seen_exact:
            problems.append(f"functions.csv line {i}: exact duplicate row for {name} @ {target_rva}. "
                            "Fix: python3 tools/dedup_csv.py")
        seen_exact.add(key)

        rva = int(target_rva, 16)
        gen_row = placeholder_row(name, source, _notes)
        if rva in by_rva and by_rva[rva][0] != name:
            prev_name, prev_size, prev_gen = by_rva[rva]
            if prev_size != size:
                problems.append(f"functions.csv: two names claim target_rva {target_rva} with "
                                f"different sizes: {prev_name} ({prev_size}B) and {name} ({size}B). "
                                "Byte-verify decides which is real.")
            elif gen_row != prev_gen:
                # A gen-* placeholder sharing an exact range with a real identity
                # is not an ICF alias — the placeholder is the same function under
                # a synthetic name and must yield (union merges land both sides
                # silently; this is the only gate that can see it).
                problems.append(f"functions.csv: {name} and {prev_name} claim the same range "
                                f"at {target_rva} but exactly one is a gen-* placeholder. "
                                "Retract the placeholder row and tombstone it in "
                                "reverse/deleted_rows.csv.")
            # same (rva, size), same kind: ICF alias group — identical COMDATs
            # folded to one address in retail; each byte-verifies independently.
        by_rva.setdefault(rva, (name, size, gen_row))

        identity = {"name": name, "source": source, "notes": _notes}
        previous = by_name.setdefault(name, [])
        for old_rva, old_identity in previous:
            if old_rva != rva and name not in ALLOWED_DUP_NAMES \
                    and ledger_io.same_function_name(identity, old_identity):
                hint = ledger_io.local_label_hint(identity, [old_identity])
                problems.append(f"functions.csv: {name} claims two addresses: "
                                f"0x{old_rva:08X} and 0x{rva:08X}. " +
                                (hint or "One is wrong."))
        previous.append((rva, identity))

        if status == "matched":
            matched_ranges.append((rva, rva + size, name))

    matched_ranges.sort()
    for (a_start, a_end, a_name), (b_start, b_end, b_name) in zip(matched_ranges, matched_ranges[1:]):
        if b_start < a_end:
            if a_start == b_start and a_end == b_end:
                continue  # ICF alias group: identical range claimed by multiple names
            problems.append(f"functions.csv: matched ranges overlap: {a_name} "
                            f"[0x{a_start:08X}-0x{a_end:08X}) and {b_name} @ 0x{b_start:08X}. "
                            "The full gate will refuse to patch. Byte-verify decides which is real.")
    return len([r for r in rows[1:] if len(r) == 7])


def check_symbols(raw, problems):
    # Rows may be 2-field (name,address — the form docs/matching.md tells agents
    # to append) or 3-field with notes. A name may legitimately appear at several
    # addresses: build.py's load_symbol_map treats them all as REL32 resolution
    # candidates. Only exact duplicates and malformed rows are errors.
    #
    # The file must carry canonical LF. It is merge=union, so a pin differing
    # from its twin only by a carriage return is a distinct line and duplicates
    # on the next merge.
    check_lf_ledger(raw, "symbols.csv", problems)
    text = raw.decode("utf-8", errors="replace")
    rows = list(csv.reader(io.StringIO(text)))
    if not rows or ",".join(rows[0]) != SYMBOLS_HEADER:
        problems.append(f"symbols.csv: bad header (expected '{SYMBOLS_HEADER}')")
        return
    seen_exact = set()
    for i, r in enumerate(rows[1:], start=2):
        if not r or (len(r) == 1 and not r[0]):
            continue
        if len(r) < 2:
            problems.append(f"symbols.csv line {i}: {len(r)} fields, expected at least 2: {r}...")
            continue
        # >3 fields happens when notes contain commas; the gate only reads
        # name and address, so that is fine.
        name, address = r[0], r[1]
        if not name or not address:
            problems.append(f"symbols.csv line {i}: empty name or address")
            continue
        try:
            addr = int(address, 16)
        except ValueError:
            problems.append(f"symbols.csv line {i} ({name}): bad address '{address}'")
            continue
        # Short addresses are only inconsistent zero-padding and parse fine, but
        # more than eight hex digits cannot be a 32-bit RVA in any spelling, so
        # it is always a typo — three such rows reached the ledger before this
        # check existed, each one digit too long and silently parsing correctly.
        if len(address.removeprefix("0x").removeprefix("0X")) > 8:
            problems.append(f"symbols.csv line {i} ({name}): address '{address}' has "
                            f"more than 8 hex digits; write it as 0x{addr:08X}")
        if (name, addr) in seen_exact:
            problems.append(f"symbols.csv line {i}: exact duplicate row for {name}. "
                            "Fix: python3 tools/dedup_csv.py")
        seen_exact.add((name, addr))
    return len(rows) - 1


ATTEMPTS_DIR = "reverse/attempts/"
ATTEMPT_NAME = re.compile(r"^0x[0-9a-f]{8}\.cpp$")
ATTEMPT_LIMIT = 64 * 1024


def _attempt_paths(spec):
    """Stash files as they exist in the state being gated, never on disk.

    A working-tree scan would fail an unrelated `--ref` push over a stray
    uncommitted file, so this reads the same source of truth known_sources does.
    """
    return sorted(p for p in known_sources(spec)
                  if p.startswith(ATTEMPTS_DIR) and p != ATTEMPTS_DIR)


def check_attempts(spec, problems):
    """Validate banked near-miss bodies under reverse/attempts/.

    A stash is evidence handed to the next agent, so a malformed one is worse
    than none: it gets served at a score nobody measured. Absent directory means
    nothing banked yet, which is the normal state and passes.
    """
    paths = _attempt_paths(spec)
    if not paths:
        return 0
    import re_log

    matched = {}
    for row in csv.reader(io.StringIO(read_ledger(FUNCTIONS, spec).decode(
            "utf-8", errors="replace"))):
        if len(row) == 7 and row[5] == "matched":
            matched.setdefault(row[2].lower(), []).append((row[0], row[4]))

    blobs = read_blobs(paths, spec)
    for rel in paths:
        name = rel[len(ATTEMPTS_DIR):]
        if not ATTEMPT_NAME.match(name):
            problems.append(
                f"{rel}: name must be the lowercase rva it banks, e.g. "
                f"0x000c8220.cpp — serving looks the stash up by address.")
            continue
        blob = blobs[rel]
        if len(blob) > ATTEMPT_LIMIT:
            problems.append(f"{rel}: {len(blob)} bytes, over {ATTEMPT_LIMIT}. "
                            f"That is not one function body; delete it.")
        lines = blob.decode("utf-8", errors="replace").splitlines()
        if len(lines) < 2 or not re_log._STASH_SCORE.match(lines[1]):
            problems.append(
                f"{rel}: line 2 must read '// partial score=<0..1> date=<iso>'. "
                f"An unreadable score cannot be ranked; rewrite or delete it.")
            continue
        rva = name[:-len(".cpp")]
        claims = matched.get(rva, [])
        # A stash on a matched rva is an orphan ONLY when real C++ already owns
        # it. Every dump candidate is matched by construction -- a naked
        # transcription lands byte-verified -- and converting those is exactly
        # what a stash is for, so the dump lane must survive this check.
        for sym, source in claims:
            # Same two-part test progress.py uses to route a row to its `dump`
            # lane: an .asm/.lib row is retail re-encoded by extension alone,
            # and a .cpp row is one when its body is a naked/__emit lift.
            if Path(source).suffix.lower() in (".asm", ".s", ".lib"):
                continue
            text = read_ledger(ROOT / source, spec).decode("utf-8", errors="replace")
            if "__declspec(naked)" in text or "_emit" in text:
                continue
            problems.append(
                f"{rel}: {rva} already has real C++ at {source} ({sym}). "
                f"It landed — delete the stash.")
            break
    return len(paths)


# Orphans that already exist: 6 .cpp under Code/ own no matched row, the oldest
# added 2026-08-03. They fail build.py's verify_source_claims, but that runs only
# in the FULL gate -- which no commit or push hook invokes -- so they accumulated
# silently for weeks while every routine gate stayed green. This is a ratchet,
# not a clean-up: it cannot fail the fleet today, and it refuses the 7th.
# It may only ever be LOWERED, never raised to get green.
ORPHAN_BASELINE = 6


def read_data_rows(spec):
    """data_rows.csv at `spec` (b"" when that state has none)."""
    if spec is None:
        return DATA_ROWS.read_bytes() if DATA_ROWS.exists() else b""
    rel = DATA_ROWS.relative_to(ROOT).as_posix()
    out = subprocess.run(["git", "-C", str(ROOT), "show", f"{spec}:{rel}"], capture_output=True)
    return out.stdout if out.returncode == 0 else b""


RETIRED_ROW_HELP = """\
The ledger is a cache derived from objects. This usually means it was regenerated from objects
older than the retirement, such as a downloaded index. Your commit does not need this change.

  Not changing the ledger on purpose: leave it out. Before committing:
      git checkout HEAD -- reverse/data_ledger.csv
  If it is already committed (a commit touching only the ledger first hears of this at push), restore
  master's copy and commit that, or amend the commit that brought it:
      git checkout refs/remotes/origin/master -- reverse/data_ledger.csv

  Regenerating on purpose: rebuild your objects from this tree with ./build.sh and run
  python3 tools/data_ledger.py on those fresh objects, not on a downloaded index.

  Fresh objects still define the name: a source still spells it, so the retirement missed a unit,
  which is not yours to fix here. Leave the ledger out as above, which clears this refusal, and tell
  whoever retired it:
      git log -S'<name>' --format='%h %an %s' -- reverse/deleted_rows.csv
  and record it so a tooling seat picks it up:
      python3 tools/re_log.py record '<name>' <address> <size> blocked "false-reject check_csv retired name: ..."

  Bringing the name back on purpose: row it in reverse/data_rows.csv in the same commit.
"""


def ledger_rows(raw):
    """{name: row} of a data_ledger.csv."""
    text = raw.decode("utf-8", errors="replace")
    return {row["name"]: row for row in csv.DictReader(io.StringIO(text))}


def ledger_at(spec):
    """data_ledger.csv's bytes at `spec` (None: working tree, "": index), b"" when that state has none."""
    if spec is None:
        path = ROOT / "reverse" / "data_ledger.csv"
        return path.read_bytes() if path.exists() else b""
    out = subprocess.run(["git", "-C", str(ROOT), "show", f"{spec}:reverse/data_ledger.csv"], capture_output=True)
    return out.stdout if out.returncode == 0 else b""


def ledger_base(spec):
    """What `spec`'s ledger is new against, or None. A commit is judged from where its branch leaves master,
    since pre-push passes only the tip and a ledger-only commit can take pre-commit's early exit. Without a
    master to compare, or for what is not yet a commit (pre-commit's tree, the index), its parent."""
    def git(*args):
        out = subprocess.run(["git", "-C", str(ROOT), *args], capture_output=True, text=True)
        return out.stdout.strip() if out.returncode == 0 else None
    if spec is None or spec == "" or git("cat-file", "-t", spec) != "commit":
        return git("rev-parse", "--verify", "--quiet", "HEAD")
    return (git("merge-base", spec, "refs/remotes/origin/master")
            or git("rev-parse", "--verify", "--quiet", f"{spec}^"))


def check_retired_ledger_rows(spec):
    """Refuse a ledger row newly carrying a name deleted_rows.csv retired, unless data_rows.csv rows that
    name today. Only rows new against ledger_base: what is already there blocks nobody. Outside the
    verdict because it needs a base, and verdict() is kept by tree. Returns [] when there is nothing to say."""
    after = ledger_at(spec)
    base = ledger_base(spec)
    if not after or base is None:
        return []
    before = ledger_at(base)
    if before == after:
        return []
    old = ledger_rows(before) if before else {}
    added = {name: row for name, row in ledger_rows(after).items() if name not in old}
    if not added:
        return []
    retired = {}
    deleted = read_ledger(DELETED, spec)
    for row in csv.DictReader(io.StringIO(deleted.decode("utf-8", errors="replace"))):
        retired.setdefault(row.get("name"), row.get("reason") or "")
    rowed = {row.get("name") for row in csv.DictReader(io.StringIO(read_data_rows(spec).decode("utf-8", errors="replace")))}
    hits = sorted(name for name in added if name in retired and name not in rowed)
    if not hits:
        return []
    print(f"check_csv: reverse/data_ledger.csv adds {len(hits)} row(s) for names reverse/deleted_rows.csv retired:", file=sys.stderr)
    for name in hits:
        print(f"  - {name} ({added[name]['address']}, {added[name]['size']} bytes): {retired[name][:120]}", file=sys.stderr)
    print(RETIRED_ROW_HELP, file=sys.stderr)
    raise SystemExit(1)


def data_row_sources(raw):
    """Sources owning a matched data row (tools/data_rows.py): a data-only TU."""
    import data_rows
    try:
        return {row["source"] for _, row in data_rows.parse(raw) if row.get("status") == "matched"}
    except ValueError:
        return set()


def check_orphans(spec, problems, *, data_raw=None):
    """Refuse a NEW Code/*.cpp that owns no matched row.

    A source with no row is presence pretending to be progress: nothing compiles
    it, nothing verifies it, and the only check that catches it is one the
    workflow never runs. Counting rather than listing keeps this a few lines and
    keeps the existing backlog someone else's to clear.
    """
    claimed = set()
    for row in csv.reader(io.StringIO(
            read_ledger(FUNCTIONS, spec).decode("utf-8", errors="replace"))):
        if len(row) == 7 and row[5] == "matched":
            claimed.add(row[4])
    # a data-only TU owns its globals in data_rows.csv (tools/data_rows.py)
    claimed.update(data_row_sources(read_data_rows(spec) if data_raw is None else data_raw))
    orphans = sorted(
        path for path in known_sources(spec)
        if path.startswith("Code/") and path.endswith(".cpp")
        and not path.startswith(("Code/gen_asm/", "Code/gen_small/"))
        and path not in claimed)
    if len(orphans) > ORPHAN_BASELINE:
        problems.append(
            f"{len(orphans)} Code/*.cpp own no matched row, over the "
            f"{ORPHAN_BASELINE} already known. Byte-match one function in your "
            f"new file or delete it -- source presence is not progress. "
            f"Never raise ORPHAN_BASELINE to get green; it only goes down. "
            f"Orphans: {', '.join(orphans)}")
    return len(orphans)


def check_body_owners(raw, functions_raw, problems):
    """Enforce the owner recorded by a completed same-address reconstruction audit.

    This registry makes no assertion that unrelated equal-byte bodies are not
    legitimate folds. A supported rename/rehome updates the owner with evidence.
    """
    if not raw:  # Historical revisions before the registry was introduced.
        return
    check_lf_ledger(raw, "body_owners.csv", problems)
    reader = csv.DictReader(io.StringIO(raw.decode("utf-8")))
    expected = ["target_rva", "name", "target_size", "source", "evidence"]
    if reader.fieldnames != expected:
        problems.append("body_owners.csv: invalid header")
        return
    owners = {}
    for row in reader:
        try:
            address = int(row["target_rva"], 16)
            size = int(row["target_size"])
            if not (address > 0 and size > 0 and row["name"]
                    and row["source"].startswith("Code/") and row["evidence"].strip()
                    and None not in row):
                raise ValueError("invalid ownership record")
        except (ValueError, TypeError, AttributeError):
            problems.append(f"body_owners.csv: invalid owner record {row!r}")
            continue
        if address in owners:
            problems.append(f"body_owners.csv: duplicate owner at 0x{address:08X}")
        owners[address] = row
    actual = {address: [] for address in owners}
    for row in csv.DictReader(io.StringIO(functions_raw.decode("utf-8"))):
        try:
            address = int(row["target_rva"], 16)
        except (ValueError, TypeError):
            continue  # check_functions reports malformed ledger rows.
        if address in actual:
            actual[address].append(row)
    for address, owner in owners.items():
        rows = actual[address]
        if len(rows) != 1:
            problems.append(f"body_owners.csv: audited body 0x{address:08X} must have "
                            f"one owner, found {len(rows)} rows")
            continue
        row = rows[0]
        if any(row.get(key) != owner[key] for key in ("name", "source", "target_size")) \
                or row.get("status") != "matched":
            problems.append(f"body_owners.csv: owner disagrees with functions.csv "
                            f"at 0x{address:08X}; reconcile the audit evidence")


FORCED_MOVES_REL = "reverse/forced_row_moves.csv"
TU_MAP_REL = "reverse/tu_map.csv"


def read_optional(rel, spec):
    """A ledger an older revision may not have: empty when absent."""
    if spec is None:
        path = ROOT / rel
        return path.read_bytes() if path.exists() else b""
    exists = subprocess.run(["git", "-C", str(ROOT), "cat-file", "-e", f"{spec}:{rel}"], capture_output=True)
    return read_ledger(ROOT / rel, spec) if exists.returncode == 0 else b""


def _csv_rows(raw):
    return list(csv.DictReader(io.StringIO(raw.decode("utf-8", "surrogateescape"))))


def check_forced_moves(register_raw, functions_raw, map_raw, problems, table, sources):
    """reverse/forced_row_moves.csv against the families' reviewed forced_moves `table` {rva: (name, source)}
    (tools/retail_identity.py): a line is a real, reviewed move of its row to the tracked file it names, and
    a reviewed row that has left its source and sits outside an approved unit keeps its line. `sources` are
    the paths the revision tracks (known_sources). Nothing else reads the register, so without this a
    hand-edited line proves nothing and a deleted one goes unnoticed."""
    lines = _csv_rows(register_raw)
    at = {}
    for row in _csv_rows(functions_raw):
        if row.get("target_rva", "").startswith("0x"):
            try:
                at.setdefault(int(row["target_rva"], 16), []).append(row)
            except ValueError:
                pass
    units = {}
    if lines or any(r["source"] != source for rva, (_name, source) in table.items() for r in at.get(rva, ())):
        for row in _csv_rows(map_raw):
            try:
                units[int(row["rva"], 16)] = row
            except (KeyError, TypeError, ValueError):
                pass

    def in_approved_unit(rva, source):
        unit = units.get(rva) or {}
        return unit.get("confidence") == "approved" and (unit.get("tu") or "").lower() == source.lower()

    seen = set()
    for line in lines:
        try:
            rva = int(line["target_rva"], 16)
        except (KeyError, TypeError, ValueError):
            problems.append(f"forced_row_moves.csv: unparseable address {line.get('target_rva')!r}")
            continue
        label = f"forced_row_moves.csv: 0x{rva:08X}"
        if rva in seen:
            problems.append(f"{label} is listed twice")
        seen.add(rva)
        entry = table.get(rva)
        if entry is None:
            problems.append(f"{label} is in no family's reviewed forced_moves (tools/retail_identity.py)")
            continue
        if line.get("name") != entry[0] or line.get("moved_from") != entry[1]:
            problems.append(f"{label} records {line.get('name')} from {line.get('moved_from')}; "
                            f"the family reviewed {entry[0]} from {entry[1]}")
        if "not in its true unit" not in (line.get("statement") or ""):
            problems.append(f"{label} does not say the row is not in its true unit")
        if not (line.get("evidence") or "").strip():
            problems.append(f"{label} has no evidence")
        placed = line.get("placed_in") or ""
        if placed not in sources:
            problems.append(f"{label} is placed in {placed or 'nothing'}, which this revision does not track")
        rows = [r for r in at.get(rva, ()) if r.get("name") == entry[0] and r.get("status") == "matched"]
        if not rows:
            problems.append(f"{label} has no matched row named {entry[0]}")
        elif rows[0]["source"] == entry[1]:
            problems.append(f"{label} says the row moved, and it is still in {entry[1]}")
        elif in_approved_unit(rva, rows[0]["source"]):
            problems.append(f"{label}: the row is in its approved unit {rows[0]['source']}: delete the line")
        elif rows[0]["source"] != placed:
            problems.append(f"{label} says the row is in {placed}, and the ledger has it in {rows[0]['source']}, "
                            "which is not its approved unit")
    for rva, (name, source) in sorted(table.items()):
        for row in at.get(rva, ()):
            if row.get("name") == name and row["source"] != source and rva not in seen \
                    and not in_approved_unit(rva, row["source"]):
                problems.append(f"forced_row_moves.csv: 0x{rva:08X} left {source} for {row['source']}, outside an "
                                "approved unit, with no line: rename.py --forced-move records it, and the line "
                                "stays until the row is in its approved unit")


def read_body_owners(spec):
    """An absent registry is valid only for revisions predating its introduction."""
    if spec is None:
        return BODY_OWNERS.read_bytes() if BODY_OWNERS.exists() else b""
    rel = BODY_OWNERS.relative_to(ROOT).as_posix()
    exists = subprocess.run(["git", "-C", str(ROOT), "cat-file", "-e", f"{spec}:{rel}"],
                            capture_output=True)
    return read_ledger(BODY_OWNERS, spec) if exists.returncode == 0 else b""


def main():
    parser = argparse.ArgumentParser(description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    where = parser.add_mutually_exclusive_group()
    where.add_argument("--staged", action="store_true",
                       help="validate the git-staged ledgers instead of the working tree")
    where.add_argument("--ref", metavar="REF",
                       help="validate the ledgers as committed at REF")
    args = parser.parse_args()

    if args.ref:
        # --ref reads git objects only, so a passing verdict is a function of the
        # tree, the retail image data_rows checks against, and this code: kept by
        # tools/ledger_cache.py under those ids. A refusal is never kept.
        print(passing_verdict(args.ref))
        check_retired_ledger_rows(args.ref)
        return
    print(verdict("" if args.staged else None))
    check_retired_ledger_rows("" if args.staged else None)


def passing_verdict(ref):
    """verdict(ref), reused for a tree whose verdict passed under the same code
    and retail image (pre-commit runs `--ref $(git write-tree)`, so the push of
    that commit reads the verdict instead of checking ~99,000 rows again)."""
    import hashlib
    import ledger_cache
    tree = subprocess.run(["git", "-C", str(ROOT), "rev-parse", "--verify", "--end-of-options",
                           f"{ref}^{{tree}}"], capture_output=True, text=True)
    if tree.returncode:
        raise SystemExit(f"check_csv: {ref} is not a commit or tree: {tree.stderr.strip()}")
    import build
    retail = hashlib.sha1(Path(build.EXE).read_bytes()).hexdigest()
    tools = Path(__file__).resolve().parent
    code = ledger_cache.code_hash(*(tools / name for name in
                                    ("check_csv.py", "ledger_io.py", "data_rows.py", "re_log.py", "build.py")))
    return ledger_cache.memo("check_csv.pass", f"{tree.stdout.strip()}:{retail}", lambda: verdict(ref), code)


def verdict(spec):
    """The OK line for the ledgers at `spec` (None: working tree, "": index,
    else a ref or tree); SystemExit(1) after printing every problem."""
    problems = []
    LF_READ.clear()
    deleted_raw = read_ledger(DELETED, spec)
    sources_ok = known_sources(spec)
    n_funcs = check_functions(read_ledger(FUNCTIONS, spec), problems, sources_ok,
                              deleted_raw)
    check_body_owners(read_body_owners(spec), read_ledger(FUNCTIONS, spec), problems)
    n_syms = check_symbols(read_ledger(SYMBOLS, spec), problems)
    check_lf_ledger(deleted_raw, "deleted_rows.csv", problems)
    check_lf_ledger(read_ledger(RE_ATTEMPTS, spec), "re_attempts.log", problems,
                    allow_empty=True)
    check_attempts(spec, problems)
    data_raw = read_data_rows(spec)
    n_data = 0
    if data_raw:
        import data_rows
        check_lf_ledger(data_raw, "data_rows.csv", problems)
        n_data = data_rows.check(data_raw, problems, sources_ok)
    n_orphans = check_orphans(spec, problems, data_raw=data_raw)
    import retail_identity
    check_lf_ledger(read_optional(FORCED_MOVES_REL, spec), "forced_row_moves.csv", problems, allow_empty=True)
    check_forced_moves(read_optional(FORCED_MOVES_REL, spec), read_ledger(FUNCTIONS, spec),
                       read_optional(TU_MAP_REL, spec), problems, retail_identity.forced_move_table(), sources_ok)
    check_lf_rules(spec, problems)

    if problems:
        print(f"check_csv: {len(problems)} problem(s):", file=sys.stderr)
        for p in problems:
            print(f"  - {p}", file=sys.stderr)
        raise SystemExit(1)
    return (f"check_csv: OK (functions.csv {n_funcs} rows, symbols.csv {n_syms} rows"
            + (f", data_rows.csv {n_data} rows" if n_data else "")
            + (f", {n_orphans} known row-less source(s))" if n_orphans else ")"))


if __name__ == "__main__":
    main()
