#!/usr/bin/env python3
"""Admission rules for the two ledger inputs the byte gate takes on trust.

reverse/symbols.csv pins and `object-symbol=` alias rows in functions.csv both
add a NAME -> ADDRESS fact that the REL32 resolver then believes for every
caller. Neither is proven by bytes: a pin naming the wrong function, or a row
renamed through object-symbol=, makes a wrong callee byte-match (audit
exploits 3 and 6, both passed the real pre-commit hook). So new ones are
admitted only under rules a reviewer could check by hand:

symbols.csv, per ADDED line (an edited line counts as added):
  * the address is an RVA inside the image. 108 pins were written as VAs
    (0x400000 too high) and silently named nothing;
  * it lies in an executable section. Data pins do nothing for REL32
    resolution and were the bypass for the data-identity checks; data gets a
    data ledger, not pins;
  * it does not give an address that already has a real (non-placeholder)
    name -- a ledger row or an existing pin -- a DIFFERENT name. One address,
    one identity; an ICF fold is recorded by renaming the owner row, not by
    stacking names. The one exception is an ICF fold PROVEN the way /OPT:ICF
    itself decides one (fold_proof_problems). A pin whose notes carry
    `fold-proof=<source>` is admitted onto a named address only when
      - the pinned name resolves nowhere else: no address the byte gate's
        symbol map gives it (gen-alias twins and baselined alias rows
        included), and no proposed row of any kind or pin that names it, is
        anything but that body or a thunk straight to it. Retail then has ONE
        body for both names; a byte-identical twin it did not fold is not a
        fold;
      - that matched ledger source's object defines the name, and its body,
        compiled and REL32-resolved exactly as the byte gate resolves a row,
        reproduces retail's whole body at the address: the extent of a ledger
        row already there, at least build.MIN_LIB_CONCRETE non-relocation
        bytes, nothing masked and nothing unresolved;
      - it carries the relocations of EVERY matched ledger body of that extent
        there: the same offsets, types and addends, each DIR32 binding the same
        external symbol or the same TU-local symbol of the same object, because
        the byte compare copies each DIR32 slot from retail and so cannot tell
        money_put's constructor from money_get's. A jump table into the body
        itself must hold retail's address of its label; any other relocation
        type is refused;
      - each callee with no address yet (a same-type instantiation) is a
        function the object defines, called directly with a zero addend, and
        is proven the same way at the address retail calls before it resolves
        the call.
    This is what lets two instantiations of one template (vector<A*>::push_back
    and vector<B*>::push_back), which /OPT:ICF folds onto one retail body, each
    be pinned there. A wrong body, callee, relocation target or second address
    is still refused, and a name nothing compiles cannot be proven. Write such
    pins with `--add NAME ADDRESS --notes "... fold-proof=<source>"`. The
    identity holds in the other order too (fold_pin_conflicts): an added row
    or pin that gives a fold-pinned name another address is refused unless
    the same change retires the fold pin.
There is no count limit: bulk generators add thousands of legitimate pins in
one commit, and every one of them is judged by the rules above.

functions.csv, per ADDED row:
  * no new alias row (build.is_alias_row): object-symbol= binding a real
    name to bytes compiled under another symbol. The existing ones are keyed
    `alias-row` lines in reverse/gate_baseline.txt (shrink-only), and only
    those still resolve callers (build.load_symbol_map). A tool-generated ICF
    fold list is the only future way in.

Existing violations are reported by --report and not re-judged per commit.

  python3 tools/pin_admission.py --staged          # pre-commit: index vs HEAD
  python3 tools/pin_admission.py --range OLD NEW   # pre-push
  python3 tools/pin_admission.py --report          # every current violation
"""
import argparse
import csv
import functools
import io
import re
import struct
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build  # noqa: E402

ROOT = build.ROOT
PINS = "reverse/symbols.csv"
LEDGER = "reverse/functions.csv"
IMAGE_BASE = 0x400000


def git_text(spec):
    out = subprocess.run(["git", "-C", str(ROOT), "show", spec], capture_output=True)
    return out.stdout.decode("utf-8", errors="replace") if out.returncode == 0 else ""


def csv_rows(text):
    return list(csv.DictReader(io.StringIO(text)))


@functools.lru_cache(maxsize=1)
def image_layout():
    """(SizeOfImage, [(start, end, executable)]) of the retail image."""
    data = build.EXE.read_bytes()
    pe = build.u32(data, 0x3C)
    coff = pe + 4
    count = build.u16(data, coff + 2)
    optional = coff + 20
    size_of_image = build.u32(data, optional + 56)
    table = optional + build.u16(data, coff + 16)
    sections = []
    for i in range(count):
        at = table + i * 40
        start = build.u32(data, at + 12)
        size = max(build.u32(data, at + 8), build.u32(data, at + 16))
        executable = bool(build.u32(data, at + 36) & 0x20000020)
        sections.append((start, start + size, executable))
    return size_of_image, sections


# Address-derived names (Rva00380459Dtor, ?ji_0062af44, Gen004ED3A2) disclaim
# identity whatever follows the digits; GEN_PLACEHOLDER_RE stops at a trailing
# hex letter (the D of "Dtor"), so it is widened here.
ADDRESS_NAME_RE = re.compile(r"(?:[Rr]va|[Gg]en|ji|dup)_?[0-9A-Fa-f]{8}")


def is_placeholder(name, rva):
    return bool(build.GEN_PLACEHOLDER_RE.search(name) or build.DUP_ALIAS_RE.match(name)
                or ADDRESS_NAME_RE.search(name) or build.is_ghidra_autoname(name, rva))


def pin_problems(pin, names_at, prove=None):
    """Why one pin line may not be added ([] = admissible).

    prove(pin, rva) -> [problems] is consulted only for a real name, carrying
    fold-proof=<source> in its notes, on an address that already carries a
    different real name; without both such a pin is refused."""
    try:
        rva = int(pin["address"], 16)
    except (KeyError, TypeError, ValueError):
        return [f"unparseable address {pin.get('address')!r}"]
    size_of_image, sections = image_layout()
    if not 0 < rva < size_of_image:
        hint = (f" (a VA? the RVA would be 0x{rva - IMAGE_BASE:08X})"
                if 0 < rva - IMAGE_BASE < size_of_image else "")
        return [f"0x{rva:08X} is outside the image (SizeOfImage 0x{size_of_image:X}){hint}"]
    section = next((s for s in sections if s[0] <= rva < s[1]), None)
    if section is None or not section[2]:
        return [f"0x{rva:08X} is not in an executable section: data is not pinned here"]
    # A placeholder pin name adds no identity; a real one may not stack on
    # another real one.
    others = [] if is_placeholder(pin["name"], rva) else sorted(
        n for n in names_at.get(rva, ()) if n != pin["name"] and not is_placeholder(n, rva))
    if others:
        why = (f"0x{rva:08X} already carries the real name {others[0]}; one address, one "
               "identity (rename the owner instead of stacking a second name)")
        if prove is None or not FOLD_PROOF_RE.search(pin.get("notes") or ""):
            return [why]
        failed = prove(pin, rva)
        if failed:
            return [why + "; no ICF fold proof: " + "; ".join(failed)]
    return []


FOLD_PROOF_RE = re.compile(r"(?:^|[\s;,])fold-proof=([^\s;,]+)")
FOLD_PROOF_DEPTH = 8
SYM_CLASS_EXTERNAL = 2  # IMAGE_SYM_CLASS_EXTERNAL


def fold_prover(rows, pins=()):
    """prove(pin, rva) for pin_problems, judged against ledger `rows` and the
    proposed pin set `pins`. The byte gate's symbol map is loaded once, and only
    when a pin actually carries a proof to check."""
    cache = []

    def symbol_map():
        if not cache:
            cache.append(build.load_symbol_map())
        return cache[0]

    return lambda pin, rva: fold_proof_problems(pin, rva, rows, symbol_map, pins)


def fold_proof_problems(pin, rva, rows, symbol_map, pins=()):
    """Why `pin` is NOT proven to be an ICF fold onto rva ([] = proven).

    /OPT:ICF gives two COMDATs one body only when their bytes AND their
    relocations are identical, and a fold gives that body to a name that has
    none of its own. The proof checks all three, for the pinned name and for
    every callee its proof has to place:

    identity  -- the name resolves nowhere else. Every address the byte gate's
                 symbol map gives it (build.load_symbol_map keeps gen-alias
                 twins and baselined alias rows), and every proposed row of any
                 kind or pin that names it, must be rva itself or an
                 incremental-link thunk straight to it. A name with a body of
                 its own elsewhere is a byte-identical twin retail did NOT
                 fold, and the extra candidate would let a caller of the owner
                 be written as the twin.
    bytes     -- the ledger source compiles, the name's body is read from its
                 object and resolved exactly as compile_function resolves a
                 row, and it equals retail's whole body at rva: the extent of a
                 ledger row there, nothing masked, nothing unresolved, and (for
                 the pinned name) at least MIN_LIB_CONCRETE non-relocation bytes.
    relocations -- compile_function copies every DIR32 slot from retail, so
                 equal bytes say nothing about a vtable store, a global, a
                 string, a float, an import or a function-pointer operand. The
                 body must carry relocations at the same offsets, of the same
                 types and with the same in-place addends as EVERY matched
                 ledger body of that extent at rva; each DIR32 must bind the
                 same external symbol, or the same TU-local symbol of the same
                 object, and a DIR32 into the body's own section (a jump table)
                 must hold retail's address of that label. A REL32's target is
                 retail's, as the byte compare resolved it. Any other
                 relocation type is refused.
    callees   -- a callee instantiated for the same new type has no address
                 yet (vector<T*>::push_back calls _M_insert_overflow<T*>). It
                 must be a function this object defines, called directly with a
                 zero addend, and is proven the same way (identity, bytes,
                 relocations) at the address retail's call names before it
                 resolves the call.

    symbol_map() returns the byte gate's symbol map."""
    match = FOLD_PROOF_RE.search(pin.get("notes") or "")
    if not match:
        return ["notes carry no fold-proof=<ledger source> naming a unit whose object "
                "defines this name"]
    name, source = pin["name"], match.group(1)
    base = symbol_map()
    problems = identity_problems(name, rva, rows, pins, base)
    if problems:
        return problems
    if not any(r.get("source") == source and r.get("status") == "matched" for r in rows):
        return [f"fold-proof source {source} has no matched ledger row"]
    path = build.ROOT / source
    if not path.is_file():
        return [f"fold-proof source {source} does not exist"]
    if path.suffix.lower() == build.LIB_SUFFIX:
        return [f"fold-proof source {source} is a library: a member is compared with every "
                "relocation masked, which proves no fold"]
    extents, owners = {}, {}
    for r in rows:
        try:
            address, size = int(r["target_rva"], 16), int(r["target_size"])
        except (KeyError, TypeError, ValueError):
            continue
        extents.setdefault(address, set()).add(size)
        if (r.get("status") == "matched" and not build.is_alias_row(r)
                and "gen-alias" not in build.notes_tokens(r)
                and not build.is_funclet_row(r, build.ledger_object_symbol(r))):
            owners.setdefault((address, size), []).append(r)
    proof = {"source": source, "rows": rows, "pins": pins, "base": base,
             "extents": extents, "owners": owners, "compiled": set(),
             "overlay": dict(base), "proven": {}}
    problems = _compile_unit(source, proof)
    if problems:
        return problems
    proof["output"] = output = build.row_object(
        {"name": name, "export_rva": "", "target_rva": "0x0", "target_size": "0",
         "source": source, "status": "matched", "notes": ""})
    try:
        compiled, relocs = build.read_object_symbol_bytes(output, name, code_only=True)
    except (OSError, ValueError, SystemExit) as error:
        return [f"{source}: {error}"]
    relocated = sum(min(build.RELOC_WIDTH.get(t, 4), len(compiled) - o)
                    for o, t, _ in relocs if o < len(compiled))
    if len(compiled) - relocated < build.MIN_LIB_CONCRETE:
        return [f"only {len(compiled) - relocated} non-relocation bytes; too few to prove a fold"]
    return _prove_body(name, rva, proof, 0)


def _compile_unit(source, proof):
    """Build `source`'s object(s) through the gate's own compile path, once."""
    if source in proof["compiled"]:
        return []
    try:
        build.compile_rows([r for r in proof["rows"] if r.get("source") == source],
                           [build.ROOT / source])
    except SystemExit as error:
        return [f"{source} does not compile ({error})"]
    proof["compiled"].add(source)
    return []


def resolved_addresses(name, rows, pins, symbol_map):
    """Every address `name` already has: its candidates in the byte gate's
    symbol map (build.load_symbol_map keeps gen-alias twins and baselined alias
    rows, and adds each body's incremental-link thunks), every proposed ledger
    row that names it -- of any kind, a superset of the rows that map keeps --
    and every proposed pin."""
    found = set(symbol_map.get(name, ()))
    for row in rows:
        if row.get("name") != name:
            continue
        try:
            found.add(int(row["target_rva"], 16))
        except (KeyError, TypeError, ValueError):
            continue
    for other in pins:
        if other.get("name") != name:
            continue
        try:
            found.add(int(other["address"], 16))
        except (KeyError, TypeError, ValueError):
            continue
    return found


def _enters(address, rva):
    """True when `address` is rva or an incremental-link thunk (jmp rel32)
    straight to it: the one body either way."""
    if address == rva:
        return True
    try:
        entry = build.read_target_bytes(address, 5)
    except (OSError, ValueError):
        return False
    return (len(entry) == 5 and entry[0] == 0xE9
            and (address + 5 + struct.unpack_from("<i", entry, 1)[0]) & 0xFFFFFFFF == rva)


def identity_problems(name, rva, rows, pins, symbol_map):
    """[] when retail can serve `name` from one body only, the one at rva."""
    elsewhere = sorted(a for a in resolved_addresses(name, rows, pins, symbol_map)
                       if not _enters(a, rva))
    if elsewhere:
        return [f"{name} already has its own address 0x{elsewhere[0]:08X}; an ICF fold "
                "gives one body to a name that has none, it never adds a second address to "
                "a name that resolves elsewhere (a byte-identical twin retail did not fold "
                "is not a fold)"]
    return []


def _prove_body(name, rva, proof, depth):
    """[] when `name`'s body in proof["output"] is retail's body at rva: identity,
    bytes and relocations (see fold_proof_problems)."""
    source, output, proven = proof["source"], proof["output"], proof["proven"]
    if name in proven:
        return [] if proven[name] == rva else [
            f"{name} would be proven at both 0x{proven[name]:08X} and 0x{rva:08X}"]
    if depth > FOLD_PROOF_DEPTH:
        return [f"callee chain deeper than {FOLD_PROOF_DEPTH} at {name}"]
    if depth:  # the pinned name itself was judged before anything compiled
        problems = identity_problems(name, rva, proof["rows"], proof["pins"], proof["base"])
        if problems:
            return problems
    try:
        compiled, relocs, info = build.read_object_symbol_bytes(output, name, code_only=True,
                                                                detail=True)
    except (OSError, ValueError, SystemExit) as error:
        return [f"{source}: {error}"]
    extents = proof["extents"].get(rva, set())
    if len(compiled) not in extents:
        return [f"{source} compiles {name} to {len(compiled)} bytes; the ledger body at "
                f"0x{rva:08X} is {'/'.join(map(str, sorted(extents))) or 'unrowed'}"]
    proven[name] = rva  # provisional: a recursive call back to it resolves here
    probe = {"name": name, "export_rva": "", "target_rva": f"0x{rva:08X}",
             "target_size": str(len(compiled)), "source": source, "status": "matched",
             "notes": ""}
    try:
        patch = build.compile_function(probe, proof["overlay"], output)
    except (OSError, ValueError, SystemExit) as error:
        return [f"{source}: {error}"]
    target = patch["target"]
    if patch["unresolved"]:
        unresolved = set(patch["unresolved"])
        sites = {}
        for k, (offset, rtype, callee) in enumerate(relocs):
            if rtype != build.REL32 or callee not in unresolved or offset >= len(target):
                continue
            if offset + 4 > len(target):
                return [f"{name}: REL32 to {callee} runs past the body"]
            # A fold proves a callee's entry, not an interior target a COFF
            # addend would encode: only direct calls and jumps with a zero
            # addend may name the address the callee is proven at.
            if (offset < 1 or compiled[offset - 1] not in (0xE8, 0xE9)
                    or compiled[offset:offset + 4] != b"\0" * 4):
                return [f"{name}: REL32 to {callee} at +0x{offset:x} is not a direct call or "
                        "jump with a zero addend"]
            # ...and only of a function this object defines under that one name:
            # a section symbol or a label reads back as some other body.
            symbol = info["symbols"][info["reloc_symbols"][k]]
            defined = [s for s in info["symbols"] if s["name"] == callee and s["section"] > 0]
            if (symbol.get("storage") != SYM_CLASS_EXTERNAL or symbol["section"] <= 0
                    or len(defined) != 1):
                return [f"{name}: +0x{offset:x} calls {callee}, which is not one external "
                        "function this object defines"]
            called = (rva + offset + 4 + struct.unpack_from("<i", target, offset)[0]) & 0xFFFFFFFF
            sites.setdefault(callee, set()).add(called)
        for callee in sorted(unresolved):
            called = sites.get(callee, set())
            if len(called) != 1:
                return [f"{name}: unresolved {callee} is not one REL32 call target"]
            address = next(iter(called))
            problems = _prove_body(callee, address, proof, depth + 1)
            if problems:
                return problems
            proof["overlay"][callee] = [address]
        try:
            patch = build.compile_function(probe, proof["overlay"], output)
        except (OSError, ValueError, SystemExit) as error:
            return [f"{source}: {error}"]
        if patch["unresolved"]:
            return [f"{name}: unresolved callees {sorted(set(patch['unresolved']))[:3]}"]
    if patch["masked"]:
        return [f"{name}: body could only be compared masked"]
    if patch["bytes"] != target:
        first = next((i for i, (a, b) in enumerate(zip(patch["bytes"], target)) if a != b),
                     min(len(patch["bytes"]), len(target)))
        return [f"{source}'s {name} differs from retail 0x{rva:08X} at +0x{first:x}"]
    return _binding_problems(name, rva, target, (compiled, relocs, info), proof)


def _bindings(body, relocs, info, size, output):
    """[(offset, type, binding)] for every relocation in the first `size` bytes
    of a body read with read_object_symbol_bytes(detail=True) from `output`.
    Every binding carries the site's in-place addend. A REL32's is
    ("call", addend): its target is checked by the byte compare. Every other
    site names what it refers to without reading retail -- ("self", offset) for
    a target inside the body's own section (a jump table), ("extern", symbol,
    addend) for an external symbol, ("local", object, symbol index, addend) for
    a TU-local one (a static or a section symbol is one symbol only within its
    own object)."""
    sites = []
    for k, (offset, rtype, symbol_name) in enumerate(relocs):
        if offset >= size:
            continue
        index = info["reloc_symbols"][k]
        symbol = info["symbols"][index]
        addend = struct.unpack_from("<i", body, offset)[0] if offset + 4 <= len(body) else None
        if rtype == build.REL32:
            binding = ("call", addend)
        elif symbol["section"] == info["section"]:
            binding = ("self", symbol["value"] - info["value"] + (addend or 0))
        elif symbol.get("storage") == SYM_CLASS_EXTERNAL:
            binding = ("extern", symbol_name, addend)
        else:
            binding = ("local", str(output), index, addend)
        sites.append((offset, rtype, binding))
    return sorted(sites, key=lambda site: site[0])


def _describe(binding):
    kind, addend = binding[0], binding[-1]
    suffix = f"{addend:+d}" if addend else ""
    if kind == "call":
        return f"a call with addend {addend}"
    if kind == "self":
        return f"its own +0x{binding[1]:x}"
    if kind == "extern":
        return binding[1] + suffix
    return f"TU-local symbol #{binding[2]} of {Path(binding[1]).name}{suffix}"


def _binding_problems(name, rva, target, read, proof):
    """[] when every relocation of `name`'s body is the one a matched ledger body
    at rva carries (see fold_proof_problems). `read` is the body as
    read_object_symbol_bytes(detail=True) returned it."""
    size = len(target)
    mine = _bindings(*read, size, proof["output"])
    for offset, rtype, binding in mine:
        if rtype not in (build.REL32, build.DIR32):
            return [f"{name}: relocation type 0x{rtype:04X} at +0x{offset:x} cannot be proven"]
        if offset + 4 > size:
            return [f"{name}: the relocation at +0x{offset:x} runs past the body"]
        if binding[0] == "self":
            want = (IMAGE_BASE + rva + binding[1]) & 0xFFFFFFFF
            got = struct.unpack_from("<I", target, offset)[0]
            if got != want:
                return [f"{name}: +0x{offset:x} points at its own +0x{binding[1]:x} "
                        f"(0x{(want - IMAGE_BASE) & 0xFFFFFFFF:08X}); retail holds "
                        f"0x{(got - IMAGE_BASE) & 0xFFFFFFFF:08X}"]
    # Every matched owner of this extent, not any one: a second body claimed at
    # the address (a placeholder row added beside the real owner) must not be
    # able to vouch for relocations the real owner does not carry.
    owners = sorted(proof["owners"].get((rva, size), ()),
                    key=lambda r: (r["source"] != proof["source"], r["source"], r["name"]))
    if not owners:
        return [f"no matched ledger body of {size} bytes at 0x{rva:08X} to compare "
                f"{name}'s relocations with"]
    why = " (DIR32 slots are copied from retail, so equal bytes alone do not prove a fold)"
    for owner in owners:
        problems = _compile_unit(owner["source"], proof)
        if problems:
            return [f"{owner['name']}'s body cannot be read: {problems[0]}"]
        try:
            obj = build.row_object(owner)
            theirs = _bindings(*build.read_object_symbol_bytes(
                obj, build.ledger_object_symbol(owner), code_only=True, detail=True), size, obj)
        except (OSError, ValueError, SystemExit) as error:
            return [f"{owner['name']}'s body cannot be read: {error}"]
        if [site[:2] for site in mine] != [site[:2] for site in theirs]:
            return [f"{name}'s relocations are not those of the ledger body at 0x{rva:08X}: "
                    f"relocations at {_layout(mine)} where {owner['name']} has them at "
                    f"{_layout(theirs)}" + why]
        for (offset, _, a), (_, _, b) in zip(mine, theirs):
            if a != b:
                return [f"{name}'s relocations are not those of the ledger body at "
                        f"0x{rva:08X}: +0x{offset:x} binds {_describe(a)} where "
                        f"{owner['name']} binds {_describe(b)}" + why]
    return []


def _layout(sites):
    return "[" + ", ".join(f"+0x{offset:x}/{rtype:#x}" for offset, rtype, _ in sites) + "]"


def fold_pin_conflicts(pins, rows, added_pins, added_rows):
    """The identity proof in the other order. A fold pin -- a real name stacked
    by fold-proof= on an address that carries another real name -- holds only
    while its name has no body elsewhere, so an added row or pin that gives
    such a name another address is refused unless the same change retires the
    fold pin. Otherwise landing View::setAngle's own row after a setAngle fold
    pin onto its twin would rebuild what admission refuses."""
    names_at = names_by_address(rows, pins)
    folds = {}
    for pin in pins:
        if not FOLD_PROOF_RE.search(pin.get("notes") or ""):
            continue
        try:
            at = int(pin["address"], 16)
        except (KeyError, TypeError, ValueError):
            continue
        if not is_placeholder(pin["name"], at) and any(
                n != pin["name"] and not is_placeholder(n, at) for n in names_at.get(at, ())):
            folds.setdefault(pin["name"], set()).add(at)
    claims = ([(LEDGER, "row", r.get("name"), r.get("target_rva")) for r in added_rows]
              + [(PINS, "pin", p.get("name"), p.get("address")) for p in added_pins])
    problems = []
    for path, kind, name, address in claims:
        if name not in folds:
            continue
        try:
            address = int(address, 16)
        except (TypeError, ValueError):
            continue
        fold_at = next((a for a in sorted(folds[name]) if not _enters(address, a)), None)
        if fold_at is not None:
            problems.append(f"{path}: {name} @0x{address:08X}: {name} is fold-pinned at "
                            f"0x{fold_at:08X}; a {kind} giving it a body elsewhere means retail "
                            "did not fold it there (retire the fold pin in the same change)")
    return problems


def names_by_address(ledger_rows, pins):
    names = {}
    for row in ledger_rows:
        if build.is_alias_row(row) or "gen-alias" in build.notes_tokens(row):
            continue
        names.setdefault(int(row["target_rva"], 16), set()).add(row["name"])
    for pin in pins:
        try:
            names.setdefault(int(pin["address"], 16), set()).add(pin["name"])
        except (KeyError, TypeError, ValueError):
            continue
    return names


def pin_key(pin):
    return (pin.get("name"), pin.get("address"), pin.get("notes"))


def row_key(row):
    return tuple(row.get(f) for f in ("name", "export_rva", "target_rva", "target_size",
                                      "source", "status", "notes"))


def judge(old_pins, new_pins, old_rows, new_rows):
    problems = []
    before = {pin_key(p) for p in old_pins}
    after = {pin_key(p) for p in new_pins}
    # Rewriting a VA-stored pin as its RVA (same name and notes, address
    # lowered by the image base) repairs an existing line; it adds nothing.
    repaired = set()
    for pin in old_pins:
        try:
            if pin_key(pin) not in after:
                repaired.add((pin["name"], pin.get("notes"), int(pin["address"], 16) - IMAGE_BASE))
        except (KeyError, TypeError, ValueError):
            continue
    added = []
    for pin in new_pins:
        if pin_key(pin) in before:
            continue
        try:
            if (pin["name"], pin.get("notes"), int(pin["address"], 16)) in repaired:
                continue
        except (KeyError, TypeError, ValueError):
            pass
        added.append(pin)
    # Judge the proposed ownership state. Removed pins/rows must not block a
    # corrected owner, and a newly added ledger owner must still block an alias.
    # Added pins are checked and accumulated below so two new names also conflict.
    retained_pins = [p for p in new_pins if pin_key(p) in before]
    names_at = names_by_address(new_rows, retained_pins)
    prove = fold_prover(new_rows, new_pins)
    for pin in added:
        for why in pin_problems(pin, names_at, prove):
            problems.append(f"{PINS}: {pin['name']},{pin['address']}: {why}")
        try:
            names_at.setdefault(int(pin["address"], 16), set()).add(pin["name"])
        except (KeyError, TypeError, ValueError):
            pass
    old_keys = {row_key(r) for r in old_rows}
    problems += fold_pin_conflicts(new_pins, new_rows, added,
                                   [r for r in new_rows if row_key(r) not in old_keys])
    for row in new_rows:
        if row_key(row) in old_keys or not build.is_alias_row(row):
            continue
        if build.gate_baselined("alias-row", row):
            continue
        problems.append(f"{LEDGER}: {row['name']} @{row['target_rva']}: new object-symbol= "
                        f"alias of {build.ledger_object_symbol(row)}; aliases are admitted only "
                        "from a tool-generated ICF fold list (none exists yet)")
    return problems


def add_pins(pins, notes="", reason=None):
    """The tool path for new pins: [(name, address)] -> problems ([] = written).

    Each pin is judged by the rules above against the working tree (ledger rows and
    pins), and a name that would then pin several addresses must stay consistent
    (pin_consistency: one name, one body). Nothing is written if any pin fails.
    Otherwise the lines are appended and tools/hatch_counters.py admits exactly these
    addresses, so the hatch register lets a checked, tool-written pin through and
    still refuses one typed into symbols.csv by hand."""
    import hatch_counters
    import pin_consistency
    path = ROOT / PINS
    raw = path.read_bytes()
    eol = b"\r\n" if raw.split(b"\n", 1)[0].endswith(b"\r") else b"\n"
    current = csv_rows(raw.decode("utf-8"))
    rows = build.load_all_function_rows()
    names_at = names_by_address(rows, current)
    # The same ICF fold proof judge() accepts, against the pin set this call proposes.
    proposed = list(current)
    for name, address in pins:
        try:
            proposed.append({"name": name, "address": f"0x{int(address, 16):08X}"})
        except ValueError:
            continue
    prove = fold_prover(rows, proposed)
    have = {(p.get("name"), p.get("address", "").upper().replace("0X", "0x")) for p in current}
    notes = (notes or "").replace(",", ";").replace("\n", " ").strip()
    problems, new = [], []
    for name, address in pins:
        try:
            address = f"0x{int(address, 16):08X}"
        except ValueError:
            problems.append(f"{name},{address}: unparseable address")
            continue
        if (name, address) in have or any(p["name"] == name and p["address"] == address for p in new):
            continue
        pin = {"name": name, "address": address, "notes": notes}
        problems += [f"{name},{address}: {why}"
                     for why in pin_problems(pin, names_at, prove)]
        names_at.setdefault(int(address, 16), set()).add(name)
        new.append(pin)
    problems += fold_pin_conflicts(current + new, rows, new, [])
    if not problems and new:
        pinned = pin_consistency.load_pins(path)
        stacked = {p["name"] for p in new if pinned.get(p["name"])}
        if stacked:
            scanner, baseline = pin_consistency.Scanner(), pin_consistency.read_baseline()
            for name in sorted(stacked):
                addresses = list(pinned[name]) + [int(p["address"], 16) for p in new if p["name"] == name]
                found = scanner.inspect(name, addresses)
                if found and pin_consistency.key_of(name, found["bodies"]) not in baseline:
                    problems.append(f"{name}: {found['kind']}: {found['evidence']} "
                                    "(pin_consistency: one name, one function)")
    if problems or not new:
        return problems
    if raw and not raw.endswith(b"\n"):
        raw += eol
    lines = b"".join(f"{p['name']},{p['address']},{p['notes']}".encode("utf-8") + eol for p in new)
    path.write_bytes(raw + lines)
    hatch_counters.admit(PINS, reason or f"pin_admission --add: {len(new)} checked pin(s)",
                         tokens={p["address"] for p in new}, before=hatch_counters.blob_id(PINS, raw))
    for pin in new:
        print(f"pin admission: added {pin['name']},{pin['address']}")
    return []


def report():
    pins =csv_rows((ROOT / PINS).read_text(encoding="utf-8"))
    rows = build.load_all_function_rows()
    names_at = names_by_address(rows, [])
    prove = fold_prover(rows, pins)  # a proven ICF fold is not a violation
    count = 0
    by_address = {}
    for pin in pins:
        try:
            by_address.setdefault(int(pin["address"], 16), []).append(pin)
        except ValueError:
            pass
    for pin in pins:
        for why in pin_problems(pin, names_at, prove):
            count += 1
            print(f"pin\t{pin['name']}\t{pin['address']}\t{why}")
    for row in rows:
        if build.is_alias_row(row):
            count += 1
            print(f"alias-row\t{row['name']}\t{row['target_rva']}\t"
                  f"{'baselined' if build.gate_baselined('alias-row', row) else 'NEW'}")
    print(f"{count} finding(s)", file=sys.stderr)


def main():
    parser = argparse.ArgumentParser(description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    mode = parser.add_mutually_exclusive_group(required=True)
    mode.add_argument("--staged", action="store_true")
    mode.add_argument("--range", nargs=2, metavar=("OLD", "NEW"))
    mode.add_argument("--report", action="store_true")
    mode.add_argument("--add", nargs="+", metavar="NAME ADDRESS",
                      help="append checked pins (pairs) and admit them in the hatch register")
    parser.add_argument("--notes", default="", help="--add: notes column for the new lines")
    args = parser.parse_args()
    if args.add:
        if len(args.add) % 2:
            parser.error("--add takes NAME ADDRESS pairs")
        problems = add_pins(list(zip(args.add[::2], args.add[1::2])), args.notes)
        if problems:
            print(f"pin admission: REFUSED {len(problems)}; nothing written")
            for line in problems[:20]:
                print(f"  {line}")
            raise SystemExit(1)
        return
    if args.report:
        report()
        return
    old, new = ("HEAD", "") if args.staged else args.range
    problems = judge(csv_rows(git_text(f"{old}:{PINS}")), csv_rows(git_text(f"{new}:{PINS}")),
                     csv_rows(git_text(f"{old}:{LEDGER}")), csv_rows(git_text(f"{new}:{LEDGER}")))
    if problems:
        print(f"pin admission: FAIL {len(problems)}")
        for line in problems[:20]:
            print(f"  {line}")
        raise SystemExit(1)
    print("pin admission: OK")


if __name__ == "__main__":
    main()
