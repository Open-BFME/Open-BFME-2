#!/usr/bin/env python3
"""Exception-data verifier: a matched row's EH tables and funclets must be retail's.

The function gate compares a row's .text bytes and nothing else. The C++ EH
data cl emits beside a function -- the `mov eax,FuncInfo; jmp
___CxxFrameHandler` thunk and the unwind funclets in `.text$x`, the FuncInfo,
unwind map, try map and handler arrays in `.xdata$x` -- is never looked at, so
a wrong set of destructible locals (maxState), a dllimport destructor call or
a whole build flag (/G7: retail's static-guard funclets are `and al,0FEh`,
ours were `and eax,-2`) all stayed green. research/16 measured 538 such rows.

For every matched row whose object function has associative `.xdata$x` /
`.text$x` COMDATs, this walks the relocations from the function into its EH
sections, reading retail at each site to learn where retail put the target,
then compares each EH section byte for byte (relocation sites masked) at that
address. Verdicts:

  EXACT             every EH section equals retail and the FuncInfo sits where
                    retail's frame-handler thunk points
  bytes_differ      an EH section differs (detail names it; `guard-and` is the
                    /G7 static-guard funclet)
  reloc_conflict    two relocations place one EH section at different addresses
  fi_not_at_retail  bytes agree but retail's thunk names another FuncInfo
  unmapped          an EH section is never reached from the function
  obj_only          the object has EH data, retail's function has no EH frame
  retail_only       retail has an EH frame, the object has no EH data

Rows with EH data on neither side are not reported. A row that is not EXACT
fails unless reverse/eh_baseline.csv lists it. That baseline is debt keyed by
(name, target_rva): it may only shrink (`--assert-shrink-only REV`), and
`--write-baseline` drops fixed rows but never adds one.

  python3 tools/eh_verify.py SOURCE...        rows of these sources (pre-commit)
  python3 tools/eh_verify.py --all            the whole ledger (shadow run)
  --objdir DIR                                read objects from DIR instead of build/match
"""
import argparse
import collections
import csv
import json
import os
import struct
import subprocess
import sys
import time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build  # noqa: E402

ROOT = build.ROOT
BASELINE = ROOT / "reverse" / "eh_baseline.csv"
BASELINE_FIELDS = ["name", "target_rva", "verdict"]
EH_MAGIC = (0x19930520, 0x19930521, 0x19930522)
DIR32, REL32 = 0x0006, 0x0014
FRAME_HANDLERS = {"___CxxFrameHandler", "__EH_prolog", "__CxxFrameHandler"}


class Image:
    """The retail image laid out by RVA (sections at their virtual addresses)."""

    def __init__(self):
        data, sections = build.exe_image()
        self.base = build.u32(data, build.u32(data, 0x3C) + 4 + 20 + 28)
        size = max(s["rva"] + s["size"] for s in sections)
        image = bytearray(size)
        for s in sections:
            raw = data[s["raw_pointer"]:s["raw_pointer"] + min(s["raw_size"], s["size"])]
            image[s["rva"]:s["rva"] + len(raw)] = raw
        self.bytes = bytes(image)
        self.size = size

    def dword(self, rva):
        return struct.unpack_from("<I", self.bytes, rva)[0]

    def frame_funcinfo(self, rva):
        """(thunk_rva, funcinfo_rva) when retail's function sets up a C++ EH frame."""
        head = self.bytes[rva:rva + 48]
        offsets = [1] if head[:1] == b"\xb8" else []          # mov eax,thunk; call __EH_prolog
        push = head.find(b"\x6a\xff\x68")                    # push -1; push thunk
        if 0 <= push <= 12:
            offsets.append(push + 3)
        push = head.find(b"\x6a\xff\x64\xa1\0\0\0\0\x68")  # push -1; mov eax,fs:[0]; push thunk
        if 0 <= push <= 12:
            offsets.append(push + 9)
        # /O2 may schedule a stack-argument load into edx between the FS
        # load and handler push (Render2DClass geometry allocator, 0x11BD80).
        # Require the complete unchanged FS installation, not an arbitrary
        # push whose immediate happens to name a FuncInfo thunk.
        push = head.find(b"\x6a\xff\x64\xa1\0\0\0\0\x8b\x54\x24")
        if 0 <= push <= 12 and head[push + 12:push + 13] == b"\x68" \
                and head[push + 17:push + 25] == b"\x50\x64\x89\x25\0\0\0\0":
            offsets.append(push + 13)
        for offset in offsets:
            thunk = struct.unpack_from("<I", head, offset)[0] - self.base
            if 0 <= thunk < self.size - 10 and self.bytes[thunk] == 0xB8 \
                    and self.bytes[thunk + 5] == 0xE9:
                funcinfo = self.dword(thunk + 1) - self.base
                if 0 <= funcinfo < self.size - 4 and self.dword(funcinfo) in EH_MAGIC:
                    return thunk, funcinfo
        return None


class Obj:
    """The parts of a COFF object this check needs: sections with their
    relocations, COMDAT associations, and the symbol table."""

    def __init__(self, path):
        data = path.read_bytes()
        nsec, symtab, nsym, optsize = (build.u16(data, 2), build.u32(data, 8),
                                       build.u32(data, 12), build.u16(data, 16))
        strtab = symtab + 18 * nsym
        self.sections = []
        for index in range(nsec):
            o = 20 + optsize + 40 * index
            name = data[o:o + 8].rstrip(b"\0").decode("latin1")
            if name.startswith("/"):
                start = strtab + int(name[1:])
                name = data[start:data.index(b"\0", start)].decode("latin1")
            raw_size, raw_ptr, rel_ptr = struct.unpack_from("<III", data, o + 16)
            nrel = build.u16(data, o + 32)
            chars = build.u32(data, o + 36)
            body = data[raw_ptr:raw_ptr + raw_size] if raw_ptr and not chars & 0x80 else bytes(raw_size)
            relocs = [struct.unpack_from("<IIH", data, rel_ptr + 10 * k) for k in range(nrel)]
            self.sections.append({"name": name, "index": index + 1, "data": body,
                                  "relocs": relocs, "assoc": None})
        self.symbols, self.by_name = {}, {}
        index = 0
        while index < nsym:
            o = symtab + 18 * index
            raw = data[o:o + 8]
            if raw[:4] == b"\0\0\0\0":
                start = strtab + struct.unpack_from("<I", raw, 4)[0]
                name = data[start:data.index(b"\0", start)].decode("latin1")
            else:
                name = raw.rstrip(b"\0").decode("latin1")
            value, section, _type, storage, naux = struct.unpack_from("<IHHBB", data, o + 8)
            if section >= 0xFFFE:      # absolute / debug
                section = 0
            symbol = {"name": name, "value": value, "section": section, "storage": storage}
            self.symbols[index] = symbol
            if naux == 1 and storage == 3 and 0 < section <= nsec and value == 0:
                _len, _nr, _nl, _chk, number, select = struct.unpack_from("<IHHIHB", data, o + 18)
                if select == 5:
                    self.sections[section - 1]["assoc"] = number
            if storage in (2, 3) and section > 0:
                self.by_name.setdefault(name, symbol)
            index += 1 + naux

    def eh_sections(self, function_section):
        return [s for s in self.sections if s["assoc"] == function_section
                and (s["name"].startswith(".xdata") or s["name"].startswith(".text$x"))]


def _signed(value):
    return struct.unpack("<i", struct.pack("<I", value))[0]


def section_placements(image, obj, symbol, eh):
    """Placement evidence from the parent's relocation graph; no byte guesses."""
    function = obj.sections[symbol["section"] - 1]
    rva = symbol["retail_rva"]
    eh_index = {s["index"] for s in eh}
    base = {function["index"]: rva - symbol["value"]}
    work, conflicts = [function["index"]], []
    while work:
        section = obj.sections[work.pop() - 1]
        start = base[section["index"]]
        for offset, symbol_index, rtype in section["relocs"]:
            if rtype not in (DIR32, REL32):
                continue
            site = start + offset
            target = obj.symbols.get(symbol_index)
            if target is None or not target["section"] or not 0 <= site < image.size - 4:
                continue
            if target["section"] not in eh_index and target["section"] != function["index"]:
                continue
            addend = _signed(struct.unpack_from("<I", section["data"], offset)[0])
            value = image.dword(site)
            if rtype == REL32:
                where = site + 4 + _signed(value) - addend
            else:
                where = value - image.base - addend
            want = (where - target["value"]) & 0xFFFFFFFF
            if target["section"] in base:
                if base[target["section"]] != want:
                    conflicts.append(obj.sections[target["section"] - 1]["name"])
                continue
            if not 0 <= want < image.size:
                conflicts.append(obj.sections[target["section"] - 1]["name"])
                continue
            base[target["section"]] = want
            work.append(target["section"])

    return base, conflicts


def verify_row(image, obj, name, rva):
    """(verdict, detail) for one row, or None when neither side has EH data."""
    symbol = obj.by_name.get(name)
    if symbol is None:
        return None
    function = obj.sections[symbol["section"] - 1]
    eh = obj.eh_sections(function["index"])
    has_obj = any(s["name"].startswith(".xdata") for s in eh)
    retail = image.frame_funcinfo(rva)
    if not has_obj and not retail:
        return None
    if not has_obj:
        return "retail_only", "retail sets up an EH frame; the object emits no .xdata$x"
    if not retail:
        return "obj_only", "the object emits .xdata$x; retail's function has no EH frame"

    base, conflicts = section_placements(image, obj, dict(symbol, retail_rva=rva), eh)

    unmapped = [s["name"] for s in eh if s["index"] not in base]
    if unmapped:
        return "unmapped", "never reached from the function: " + ", ".join(sorted(set(unmapped)))
    differ = []
    for s in eh:
        at, body = base[s["index"]], s["data"]
        masked = set()
        for offset, _symbol, _rtype in s["relocs"]:
            masked.update(range(offset, offset + 4))
        theirs = image.bytes[at:at + len(body)]
        diff = [k for k in range(len(body)) if k not in masked and (k >= len(theirs) or theirs[k] != body[k])]
        if diff:
            what = s["name"]
            if s["name"].startswith(".text$x") and b"\x83\xe0\xfe" in body and b"\x24\xfe" in theirs:
                what += " guard-and"   # `and eax,-2` where retail has /G7's `and al,0FEh`
            elif s["name"].startswith(".text$x") and any(
                    obj.symbols[i]["name"].startswith("__imp_") for _o, i, _t in s["relocs"]):
                what += " dllimport"
            differ.append(f"{what} @0x{at:X}: {len(diff)} byte(s)")
    if differ:
        return "bytes_differ", "; ".join(differ)
    if conflicts:
        return "reloc_conflict", "two placements for " + ", ".join(sorted(set(conflicts)))
    funcinfo = retail[1]
    if not any(s["name"].startswith(".xdata") and base[s["index"]] <= funcinfo < base[s["index"]] + len(s["data"])
               for s in eh):
        return "fi_not_at_retail", f"retail's handler thunk names FuncInfo 0x{funcinfo:X}"
    return "EXACT", ""


def verified_funclet_locations(image, obj, name, rva):
    """Compiler-local labels at proven retail locations, only for exact EH data.

    Equivalent cleanup bytes alone cannot identify a state. The parent graph
    binds each associative EH section to a retail address, so each symbol's
    offset determines its own address even when several bodies are identical.
    """
    if verify_row(image, obj, name, rva) != ("EXACT", ""):
        return {}
    symbol = obj.by_name[name]
    eh = obj.eh_sections(symbol["section"])
    base, conflicts = section_placements(image, obj, dict(symbol, retail_rva=rva), eh)
    if conflicts:
        return {}
    code = {s["index"] for s in eh if s["name"].startswith(".text$x")}
    return {s["name"]: base[s["section"]] + s["value"]
            for s in obj.symbols.values()
            if s["section"] in code and s["name"].startswith("$L")}


def row_rows(sources):
    rows = [row for row in build.load_function_rows()
            if not row["source"].lower().endswith(build.LIB_SUFFIX)]
    if sources is not None:
        rows = [row for row in rows if row["source"] in sources]
    return rows


def verify(rows, objdir=None):
    """{(name, rva): (verdict, detail)} for the rows with EH data on either side."""
    image, cache, results, missing = Image(), {}, {}, 0
    for row in rows:
        path = build.obj_path(ROOT / row["source"])
        if objdir is not None:
            path = Path(objdir) / path.name
        if path not in cache:
            cache.clear()   # rows arrive grouped by source; keep one parsed object
            cache[path] = Obj(path) if path.exists() else None
        obj = cache[path]
        if obj is None:
            missing += 1
            continue
        name = build.ledger_object_symbol(row)
        if build.is_funclet_row(row, name):
            continue
        verdict = verify_row(image, obj, name, int(row["target_rva"], 16))
        if verdict is not None:
            results[(row["name"], row["target_rva"])] = verdict + (row["source"],)
    return results, missing


def load_baseline(text=None):
    if text is None:
        if not BASELINE.exists():
            return {}
        text = BASELINE.read_text(encoding="utf-8")
    return {(r["name"], r["target_rva"]): r["verdict"] for r in csv.DictReader(text.splitlines())}


def write_baseline(entries):
    with BASELINE.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.writer(handle, lineterminator="\n")
        writer.writerow(BASELINE_FIELDS)
        for (name, rva), verdict in sorted(entries.items(), key=lambda kv: (kv[0][1], kv[0][0])):
            writer.writerow([name, rva, verdict])


def assert_shrink_range(base, tip):
    """Check each outgoing commit against its parents; temporary growth is debt.

    A merge introduces only keys absent from every parent. Missing baseline
    blobs mean empty debt, while invalid revisions and Git errors fail closed.
    """
    def git(*args):
        result = subprocess.run(["git", *args], cwd=ROOT, capture_output=True, text=True)
        if result.returncode:
            raise SystemExit("EH baseline: Git failed: " + result.stderr.strip())
        return result.stdout

    def keys(rev):
        # Inspect the tree to distinguish a genuinely absent path from failure.
        listed = git("ls-tree", rev, "--", "reverse/eh_baseline.csv")
        if not listed.strip():
            return set()
        return set(load_baseline(git("show", rev + ":reverse/eh_baseline.csv")))

    git("rev-parse", "--verify", base + "^{commit}")
    git("rev-parse", "--verify", tip + "^{commit}")
    bad = 0
    for commit in git("rev-list", "--reverse", base + ".." + tip).splitlines():
        parents = git("rev-list", "--parents", "-n", "1", commit).split()[1:]
        added = keys(commit)
        for parent in parents:
            added -= keys(parent)
        if added:
            for name, rva in sorted(added)[:20]:
                print(f"  added to reverse/eh_baseline.csv in {commit[:10]}: {name} {rva}")
            bad += len(added)
    print(f"EH baseline: {'FAIL' if bad else 'OK'} (outgoing shrink-only; {bad} new key(s))")
    return 1 if bad else 0


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    parser.add_argument("sources", nargs="*")
    parser.add_argument("--sources-from", metavar="FILE",
                        help="also verify the NUL- or newline-separated sources in FILE ('-': stdin); "
                             "the pre-commit hook passes its list this way because Windows caps a "
                             "command line at 32,767 characters")
    parser.add_argument("--all", action="store_true", help="every matched row (shadow run)")
    parser.add_argument("--objdir", help="read objects from this directory")
    parser.add_argument("--json", help="write every verdict to this file")
    parser.add_argument("--write-baseline", action="store_true",
                        help="rewrite the baseline: drop fixed rows, never add (creates it if absent)")
    parser.add_argument("--assert-shrink-only", metavar="REV",
                        help="fail if the baseline has a key that REV's baseline lacks")
    parser.add_argument("--assert-shrink-range", nargs=2, metavar=("BASE", "TIP"),
                        help="refuse new EH debt in every outgoing commit, judged against its parents")
    args = parser.parse_args(argv)
    if args.assert_shrink_range:
        if args.assert_shrink_only or args.write_baseline or args.sources or args.sources_from or args.all:
            parser.error("--assert-shrink-range cannot be combined with verification or baseline writes")
        return assert_shrink_range(*args.assert_shrink_range)
    if args.sources_from:
        data = sys.stdin.buffer.read() if args.sources_from == "-" else Path(args.sources_from).read_bytes()
        entries = data.split(b"\0") if b"\0" in data else [l.rstrip(b"\r") for l in data.split(b"\n")]
        args.sources += [os.fsdecode(entry) for entry in entries if entry]

    if args.assert_shrink_only:
        old = subprocess.run(["git", "show", f"{args.assert_shrink_only}:reverse/eh_baseline.csv"],
                             cwd=ROOT, capture_output=True, text=True)
        if old.returncode != 0:
            print(f"EH baseline: OK (created; {args.assert_shrink_only} has none)")
            return 0
        before = load_baseline(old.stdout)
        grown = sorted(set(load_baseline()) - set(before))
        for name, rva in grown[:20]:
            print(f"  added to reverse/eh_baseline.csv: {name} {rva}")
        if grown:
            print(f"EH baseline: FAIL {len(grown)} new key(s); it may only shrink")
            return 1
        print("EH baseline: OK (shrink-only)")
        return 0

    if not args.all and not args.sources:
        parser.error("name sources or pass --all")
    started = time.time()
    results, missing = verify(row_rows(None if args.all else set(args.sources)), args.objdir)
    counts = collections.Counter(verdict for verdict, _d, _s in results.values())
    details = collections.Counter(
        part.split(" @")[0] for verdict, detail, _s in results.values()
        if verdict == "bytes_differ" for part in detail.split("; "))
    baseline = load_baseline()
    failing = {key: v for key, v in results.items() if v[0] != "EXACT"}
    new = {key: v for key, v in failing.items() if key not in baseline}
    if args.json:
        Path(args.json).write_text(json.dumps(
            {f"{k[0]}@{k[1]}": list(v) for k, v in sorted(results.items())}, indent=0))
    if args.write_baseline:
        if not BASELINE.exists():
            kept = {key: v[0] for key, v in failing.items()}
        elif args.all:
            kept = {key: v for key, v in baseline.items() if key in failing}
        else:
            kept = {key: v for key, v in baseline.items()
                    if key in failing or key not in results and key[0] not in
                    {k[0] for k in results}}
        write_baseline(kept)
        print(f"wrote reverse/eh_baseline.csv: {len(kept)} row(s) (was {len(baseline)})")
    summary = ", ".join(f"{k} {v}" for k, v in sorted(counts.items()))
    print(f"EH verify: {len(results)} row(s) with EH data ({summary}); "
          f"{len(failing)} not exact, {len(failing) - len(new)} in baseline; "
          f"{missing} row(s) without an object; {time.time() - started:.1f}s")
    if details:
        print("  differing sections: " + ", ".join(f"{k} {v}" for k, v in details.most_common()))
    for (name, rva), (verdict, detail, source) in sorted(new.items())[:40]:
        print(f"  FAIL {name} {rva} ({source}): {verdict} -- {detail}")
    if new and not args.write_baseline:
        print(f"EH verify: FAIL {len(new)} row(s) not exact and not in reverse/eh_baseline.csv")
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
