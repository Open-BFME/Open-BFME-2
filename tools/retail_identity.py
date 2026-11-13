#!/usr/bin/env python3
"""Changes retail's own bytes prove, where a vote would have nothing to add.

A vote judges a name. Which class a family of rows is instantiated on is something retail
states itself: a store of one vftable, the calls that reach it, the element stride. The basis
is `retail`, and each record's evidence names the first site read and what retail holds there:

    retail:<site> <fact>=<value> [<fact>=<value> ...]

so any route proven this way records it the same way, whatever it proves. `facts_problems`
reads a list of Facts against the image; `record` writes them; `well_formed` reads the form.

FAMILIES holds the respells this route may make, each spelled out whole: every row and pin by
its exact name and address, every fact by its site. Nothing here generalizes from a family's
shape to another class: another family is another reviewed entry (Verifier-Change).

EXTENTS holds the same for one global's bounds, what `rename.py global --retype` may do with
--address and --absorb: where an object starts and what lies inside it, which no compiler or
byte proves. Each is an entry of its own too.
"""
import collections
import hashlib
import json
import re
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build  # noqa: E402

BASIS = "retail"
RECORD_RE = re.compile(r"retail:0x[0-9A-F]{8}(?: [a-z][a-z0-9-]*=\S+)+")
IMAGE_BASE = 0x00400000

# kind: stores (a dword store of `value` through opcode `code`), calls or jumps (E8/E9 rel32
# to `value`), stride or offset (the instruction `code`, whose operand is `value`), slot (one word of a
# vftable: `site` is the word, `value` the VA it holds, `code` (table VA, index, slot count); build it with slot()),
# word (one word of a vftable, its length not stated; build it with word()), copy (the instructions `code`, a load
# and a store of one `value`-byte key), compare (the instructions `code`, a compare of the key with the field at
# +`value` and the branch on it), alloc (the instruction `code`, a push of the byte count `value` an allocation
# takes).
Fact = collections.namedtuple("Fact", "kind site value code", defaults=(None,))
# mov dword ptr [reg], imm32: the opcodes that write an object's first word, its vftable pointer
VPTR_STORES = ("c700", "c701", "c702", "c703", "c706", "c707")


def slot(table, index, count, target_rva):
    """The fact that retail's `count`-slot vftable at VA `table` holds the body at `target_rva` at `index`."""
    return Fact("slot", table - IMAGE_BASE + 4 * index, target_rva + IMAGE_BASE, (table, index, count))


def expected(fact):
    if fact.kind == "stores":
        return bytes.fromhex(fact.code) + struct.pack("<I", fact.value)
    if fact.kind in ("calls", "jumps"):
        opcode = b"\xe8" if fact.kind == "calls" else b"\xe9"
        return opcode + struct.pack("<i", fact.value - (fact.site + 5))
    if fact.kind in ("stride", "offset", "copy", "compare", "alloc"):
        return bytes.fromhex(fact.code)
    if fact.kind in ("slot", "word"):
        return struct.pack("<I", fact.value)
    raise ValueError(f"unknown retail fact {fact.kind!r}")


_verified = [None]        # (image bytes, the sha256 they were held to): the object itself, so its identity cannot be reused


def image_problem():
    """Why the image the build reads is not the one the manifest names, or None. The manifest is read every
    time, and a past verdict counts only for these very bytes against that very hash; hashing them once is
    only a saving, since exe_image serves one object per process."""
    data = build.exe_image()[0]
    wanted = [entry.get("sha256") for entry in json.loads(build.MANIFEST.read_text(encoding="utf-8")).get("files", ())
              if entry.get("path") == "files/" + build.EXE.name]
    if len(wanted) != 1 or not wanted[0]:
        return f"{build.MANIFEST.name} names no one sha256 for {build.EXE.name}"
    if _verified[0] is not None and _verified[0][0] is data and _verified[0][1] == wanted[0]:
        return None
    got = hashlib.sha256(data).hexdigest()
    if got != wanted[0]:
        return f"{build.EXE.name} is sha256 {got}, not the manifest's {wanted[0]}"
    _verified[0] = (data, wanted[0])
    return None


def read_retail(rva, size):
    """Retail's bytes at `rva`, from the image the manifest names; tests replace this."""
    problem = image_problem()
    if problem:
        raise ValueError(problem)
    return build.read_target_bytes(rva, size)


def section_name(rva):
    """The name of the image section holding `rva`, or None; tests replace this."""
    problem = image_problem()
    if problem:
        raise ValueError(problem)
    for section in build.exe_image()[1]:
        if section["rva"] <= rva < section["rva"] + section["size"]:
            return section["name"]
    return None


def slot_problem(fact):
    """Why `fact` is not a word of the table it names, or None: the site is that table's word for that index,
    the whole table is in .rdata, the target is in .text, and the word after the table is not code, so the
    count is the table's. A slot fact says what a table holds; a dword in the wrong place proves nothing."""
    table, index, count = fact.code
    start = table - IMAGE_BASE
    if not 0 <= index < count:
        return f"slot {index} is outside the {count}-slot table 0x{table:08X}"
    if fact.site != start + 4 * index:
        return f"0x{fact.site:08X} is not slot {index} of table 0x{table:08X}"
    if section_name(start) != ".rdata" or section_name(start + 4 * count - 1) != ".rdata":
        return f"table 0x{table:08X} is not all in .rdata"
    if section_name(fact.value - IMAGE_BASE) != ".text":
        return f"slot {index} of table 0x{table:08X} names 0x{fact.value:08X}, which is not in .text"
    after = struct.unpack("<I", read_retail(start + 4 * count, 4))[0]
    if IMAGE_BASE <= after and section_name(after - IMAGE_BASE) == ".text":
        return f"table 0x{table:08X} has more than {count} slots: the next word is code"
    return None


def image_size():
    """The bytes the image spans, its headers to its last section's end; tests replace this."""
    problem = image_problem()
    if problem:
        raise ValueError(problem)
    return max(section["rva"] + section["size"] for section in build.exe_image()[1])


def leaf_problem(rva, size):
    """Why retail's `size` bytes at `rva` are not a leaf, or None. The image is fixed-base with no relocation table,
    so a would-be relocation is read from the code: a branch out of the body, or an immediate or displacement that
    is an address in the image. The whole body must decode, since an undecoded tail would hide one."""
    from capstone import CS_ARCH_X86, CS_MODE_32, Cs
    from capstone.x86 import X86_OP_IMM, X86_OP_MEM
    md = Cs(CS_ARCH_X86, CS_MODE_32)
    md.detail = True
    start = rva + IMAGE_BASE
    decoded = 0
    for ins in md.disasm(read_retail(rva, size), start):
        decoded += ins.size
        branch = ins.mnemonic == "call" or ins.mnemonic.startswith(("j", "loop"))
        for op in ins.operands:
            value = None
            if op.type == X86_OP_IMM:
                value = op.imm & 0xFFFFFFFF
                if branch:
                    if not start <= value < start + size:
                        return f"0x{ins.address - IMAGE_BASE:08X} branches out of the body, to 0x{value:08X}"
                    continue
            elif op.type == X86_OP_MEM:
                value = op.mem.disp & 0xFFFFFFFF
            if value is not None and IMAGE_BASE <= value < IMAGE_BASE + image_size():
                return f"0x{ins.address - IMAGE_BASE:08X} names the image address 0x{value:08X}"
    if decoded != size:
        return f"only {decoded} of {size} bytes decode at 0x{rva:08X}"
    return None


def table_store_fact(family, at):
    """The row's own `stores` fact that writes the family's table as this object's vftable pointer, its dword at the
    declared offset; None when it declares no such fact. facts_problems reads the fact against retail."""
    offset = family.table_stores[at]
    for fact in family.rows[at][1]:
        if (fact.kind == "stores" and fact.value == family.table and fact.code in VPTR_STORES
                and at <= fact.site and fact.site + len(bytes.fromhex(fact.code)) == at + offset):
            return fact
    return None


def facts_problems(facts):
    """Why retail does not hold `facts`, one line each; [] when it holds them all. An unreadable
    site is a problem, never a pass."""
    out = []
    for fact in facts:
        want = expected(fact)
        try:
            got = read_retail(fact.site, len(want))
        except Exception as error:                     # noqa: BLE001 - whatever the read raises refuses
            out.append(f"0x{fact.site:08X} cannot be read: {error}")
            continue
        if bytes(got) != want:
            out.append(f"retail at 0x{fact.site:08X} holds {bytes(got).hex()}, not {want.hex()} ({fact.kind})")
            continue
        if fact.kind == "slot":
            try:
                problem = slot_problem(fact)
            except Exception as error:                 # noqa: BLE001 - whatever the read raises refuses
                problem = f"slot at 0x{fact.site:08X} cannot be read: {error}"
            if problem:
                out.append(problem)
    return out


def _value(fact):
    return f"{fact.value}" if fact.kind in ("stride", "offset", "copy", "compare", "alloc") else f"0x{fact.value:08X}"


def record(facts):
    """The evidence of a record proven by `facts`: retail:<first site> <kind>=<value> ..."""
    return f"retail:0x{facts[0].site:08X} " + " ".join(f"{f.kind}={_value(f)}" for f in facts)


def well_formed(evidence):
    return bool(RECORD_RE.fullmatch(evidence or ""))


class Family:
    """One class's instantiations, renamed from a stand-in class: `rows` {rva: (old name, facts)},
    `pins` {rva: (old name, facts)}; `table` is the VA of the vftable every record of the class
    stores, `copy` the row with that VA as its dword `copy_store` bytes in, `owner` {name, rva, facts} the
    class's own rowed member installing the same table."""

    def __init__(self, old, new, table, copy, copy_store, owner, rows, pins, spellings=None, leaves=None,
                 table_stores=None):
        self.old, self.new, self.table, self.copy, self.copy_store = old, new, table, copy, copy_store
        self.owner, self.rows, self.pins = owner, rows, pins
        self.spellings = spellings
        # {rva: size}: rows with nothing to bind, so no reference can show the binding survived. Each is a reviewed
        # read of one body: leaf_problem holds it against retail, and the rebuilt body must have no relocations.
        self.leaves = leaves or {}
        strangers = sorted(set(self.leaves) - set(rows))
        if strangers:
            raise ValueError(f"0x{strangers[0]:08X} is a leaf but no row of the family")
        # {rva: offset}: rows whose only references are data, which the code-reference scan cannot see. Each must bind
        # the table at that offset, in retail (its own stores fact, table_store_fact) and in the rebuilt body.
        self.table_stores = table_stores or {}
        strangers = sorted(set(self.table_stores) - set(rows))
        if strangers:
            raise ValueError(f"0x{strangers[0]:08X} stores the table but is no row of the family")
        both = sorted(set(self.leaves) & set(self.table_stores))
        if both:
            raise ValueError(f"0x{both[0]:08X} cannot be both a leaf and a store of the table")
        for at in sorted(self.table_stores):
            if table_store_fact(self, at) is None:
                raise ValueError(f"0x{at:08X} declares no store of the table at +{self.table_stores[at]}")
        if spellings is not None:
            claimed = [old_name for old_name, _facts in [*rows.values(), *pins.values()]]
            for old_name in claimed:
                if spellings.get(old_name, old_name) == old_name:
                    raise ValueError(f"{old_name} needs a spelling of its own: a row left out would respell to itself")
            strangers = sorted(set(spellings) - set(claimed))
            if strangers:
                raise ValueError(f"{strangers[0]} is spelled but is no row or pin of the family")

    def respell(self, name):
        """`name` under the new class: its written-out spelling when the family spells its members out, since a
        member's scope is no class fragment; else its whole `V<old>@@` class fragments and the head of its copy ctor."""
        if self.spellings is not None:
            return self.spellings.get(name, name)
        name = name.replace(f"V{self.old}@@", f"V{self.new}@@")
        return name.replace(f"??0{self.old}@@", f"??0{self.new}@@")

    @property
    def table_name(self):
        return f"??_7{self.new}@@6B@"

    def facts(self):
        return ([f for _name, facts in self.rows.values() for f in facts] + list(self.owner["facts"])
                + [f for _name, facts in self.pins.values() for f in facts])

    def evidence(self):
        return record(self.rows[self.copy][1])


class BodyFamily:
    """A class with no vftable, respelled from a real class retail's bytes contradict. `rows` and `pins` are
    Family's, and `spellings` {old: new} writes out each new name, since the container can change with the
    class and no fragment swap states that. `retired` {rva: (old name, facts)} are the old class's pins on an
    address `members` already rows under the new class: they go, rather than stack a second name.

    With no table to prove the class, these stand in for it, and the constructor requires every one:
    `element` is the new class's element copy, by its own bytes, and what reaches it from the rows;
    `old_element` and `old_members` are the same for the old class, so the two are told apart by what each
    copies; `members` {rva: name} are the new class's other rows, and `member_facts` show their bodies reach
    the same element copy; `bindings` [(row rva, offset, target name)] are the REL32s each rebuilt row must
    hold, the check the rebuilt copy's table store is for a Family. `copy` is the row the plan is keyed on.

    `forced_moves` {rva: (row name, source)} are the only rows `rename.py --forced-move` may take out of
    `source` for this family, under the owner's exception of 2026-11-09 (docs/consolidation.md): each is
    reviewed here, so each new one needs its own Verifier-Change, and its name must spell the old class."""

    def __init__(self, old, new, copy, spellings, element, old_element, old_members, members, member_facts, bindings,
                 rows, pins, retired=None, forced_moves=None):
        for label, value in (("element", element), ("old_element", old_element), ("old_members", old_members),
                             ("members", members), ("member_facts", member_facts), ("bindings", bindings)):
            if not value:
                raise ValueError(f"a family with no table still needs its {label}")
        strangers = sorted({at for at, _offset, _target in bindings} - set(rows))
        if strangers or set(rows) - {at for at, _offset, _target in bindings}:
            raise ValueError(f"every row needs a binding and every binding a row: {strangers}")
        if copy not in rows:
            raise ValueError(f"0x{copy:08X} is not a row of the family")
        for old_name, _facts in [*rows.values(), *pins.values()]:
            if spellings.get(old_name, old_name) == old_name:
                raise ValueError(f"{old_name} needs a spelling of its own: a row left out would respell to itself")
        if set(retired or ()) - set(members):
            raise ValueError("only a pin on an address the new class rows is retired")
        self.old, self.new, self.copy, self.spellings = old, new, copy, spellings
        self.element, self.old_element, self.old_members = tuple(element), tuple(old_element), old_members
        self.members, self.member_facts, self.bindings = members, tuple(member_facts), tuple(bindings)
        self.rows, self.pins, self.retired = rows, pins, retired or {}
        for at, (name, _source) in (forced_moves or {}).items():
            if not re.search(rf"[UV]{re.escape(old)}@@", name):
                raise ValueError(f"forced move 0x{at:08X} {name} does not spell the old class {old}")
            if at in rows or at in pins:
                raise ValueError(f"forced move 0x{at:08X} is the family's own row")
        self.forced_moves = forced_moves or {}

    def respell(self, name):
        """`name`'s written-out spelling; a name the family does not spell stays as it is, and so proves nothing."""
        return self.spellings.get(name, name)

    def facts(self):
        return ([f for _name, facts in self.rows.values() for f in facts]
                + [f for _name, facts in self.pins.values() for f in facts]
                + [f for _name, facts in self.retired.values() for f in facts]
                + list(self.element) + list(self.old_element) + list(self.member_facts))

    def evidence(self):
        return record(self.rows[self.copy][1])


def stand_in_swap(name, old, new):
    """`name` with the stand-in struct `old` read as the class `new`: its `U<old>@@` fragments become `V<new>@@`, an
    operator scoped in it (`??4<old>@@`) is scoped in `new`, and the pointer and reference back-references that
    name a struct (`PAU1@`, `ABU0@`) name a class. That is the whole respelling a stand-in element allows."""
    name = name.replace(f"??4{old}@@", f"??4{new}@@").replace(f"U{old}@@", f"V{new}@@")
    return re.sub(r"(PA|PB|AA|AB)U(\d)@", r"\1V\2@", name)


class StandInElementFamily:
    """STL helper instantiations over a registered element class, rowed under a size-only stand-in struct that has no
    constructor of its own, so no store of a table can prove the element (P134). Retail proves it through the class's
    own rows instead: `members` {rva: name} are rows of `new` (scoped in it or instantiated over it), and every row of
    the family reaches a member or another row of the family by a direct call in its own facts.

    `rows` and `pins` are Family's. `spellings` {old: new} writes each new name out, and each must be stand_in_swap of
    the old one. `stride` is the element size every stride fact states; the plan holds it to the registered header's
    sizeof assertion. `duplicates` {rva: (old name, facts)} are stand-in rows at an address `members` already rows
    under exactly the respelled name: they are retired, never respelled into a second row. `retired` {rva: (old name,
    facts)} are stand-in pins on an address `members` rows: they go. `bindings` [(row rva, offset, target name)] are
    the REL32s each rebuilt row must hold; each is one of that row's own call facts, to a member or a respelled row
    or pin at the call's target. `copy` is the row the plan is keyed on."""

    def __init__(self, old, new, copy, stride, spellings, members, bindings, rows, pins, duplicates, retired):
        for label, value in (("members", members), ("bindings", bindings), ("rows", rows)):
            if not value:
                raise ValueError(f"a stand-in element family still needs its {label}")
        if copy not in rows:
            raise ValueError(f"0x{copy:08X} is not a row of the family")
        claimed = [*rows.values(), *pins.values(), *duplicates.values(), *retired.values()]
        for old_name, _facts in claimed:
            if f"{old}@@" not in old_name:
                raise ValueError(f"{old_name} does not spell the stand-in {old}")
            if spellings.get(old_name) != stand_in_swap(old_name, old, new) or spellings[old_name] == old_name:
                raise ValueError(f"{old_name} must respell by the stand-in swap alone, to {stand_in_swap(old_name, old, new)}")
        if set(spellings) != {old_name for old_name, _facts in claimed}:
            raise ValueError("every spelling is a row's or pin's and every row and pin has one")
        for at, name in members.items():
            if not re.search(rf"(?:[VU@]|\?\?[0-9]){re.escape(new)}@@", name):
                raise ValueError(f"member 0x{at:08X} {name} is no row of {new}")
        for at, (old_name, _facts) in duplicates.items():
            if members.get(at) != spellings[old_name]:
                raise ValueError(f"duplicate 0x{at:08X} is retired only onto {new}'s own row of its respelling")
        if set(retired) - set(members):
            raise ValueError("only a pin on an address the new class rows is retired")
        if set(duplicates) & set(rows) or set(pins) & set(retired):
            raise ValueError("a row is respelled or retired, a pin respelled or retired, never both")
        named = dict(members)
        named.update({at: spellings[name] for at, (name, _facts) in [*rows.items(), *pins.items()]})
        reach = set(members) | set(rows) | set(pins)
        for at, (old_name, facts) in [*rows.items(), *duplicates.items()]:
            calls = [f for f in facts if f.kind == "calls"]
            if not any(f.value in reach for f in calls):
                raise ValueError(f"0x{at:08X} {old_name} reaches no member or row of the family by a call")
            for f in facts:
                if f.kind == "stride" and f.value != stride:
                    raise ValueError(f"0x{f.site:08X} states a stride of {f.value}, not the element's {stride}")
        for at, offset, target in bindings:
            if at not in rows:
                raise ValueError(f"binding 0x{at:08X} is no row of the family")
            fact = next((f for f in rows[at][1] if f.kind == "calls" and f.site == at + offset - 1), None)
            if fact is None:
                raise ValueError(f"0x{at:08X}+{offset} is not one of the row's own calls")
            if named.get(fact.value) != target:
                raise ValueError(f"0x{at:08X}+{offset} calls 0x{fact.value:08X}, which is not {target}")
        if set(rows) - {at for at, _offset, _target in bindings}:
            raise ValueError("every row needs a binding: a row with nothing to bind cannot show its element survived")
        self.old, self.new, self.copy, self.stride, self.spellings = old, new, copy, stride, spellings
        self.members, self.bindings = dict(members), tuple(bindings)
        self.rows, self.pins, self.duplicates, self.retired = rows, pins, duplicates, retired

    def respell(self, name):
        return self.spellings.get(name, name)

    def facts(self):
        return [f for _name, facts in [*self.rows.values(), *self.duplicates.values(), *self.pins.values(),
                                       *self.retired.values()] for f in facts]

    def evidence(self):
        return record(self.rows[self.copy][1])


# The builtin keys a StandInScalarKeyFamily may prove, by mangling code: the key's width in bytes, and the short jcc
# opcodes a compare of the key may branch on. Only unsigned int (P139); another key is another reviewed entry.
SCALAR_KEYS = {"I": (4, frozenset((0x72, 0x73, 0x76, 0x77)))}        # jb, jae, jbe, ja


def scalar_swap(tree, old, code):
    """`tree` (a rename.type_tree) with each struct `old` replaced by the builtin `code`: the whole respelling a
    stand-in key allows. Back-references are resolved in the tree, so their renumbering is no difference."""
    if tree == ("C", "U", ("Q", (("N", old),))):
        return ("B", code)
    if isinstance(tree, tuple):
        return tuple(scalar_swap(node, old, code) for node in tree)
    return tree


def _subtrees(tree):
    yield tree
    if isinstance(tree, tuple):
        for node in tree:
            yield from _subtrees(node)


def _whole(code):
    """The instructions `code` decodes to, all of it, with operand details; ValueError if any byte is left over."""
    from capstone import CS_ARCH_X86, CS_MODE_32, Cs
    md = Cs(CS_ARCH_X86, CS_MODE_32)
    md.detail = True
    raw = bytes.fromhex(code)
    out = list(md.disasm(raw, 0))
    if sum(ins.size for ins in out) != len(raw):
        raise ValueError(f"{code} does not decode whole")
    return out


def key_copy_problem(fact, width):
    """Why `fact` is not one load and one store of a `width`-byte key through the same register, or None."""
    from capstone.x86 import X86_OP_MEM, X86_OP_REG
    try:
        load, store, *rest = _whole(fact.code)
    except ValueError as error:
        return str(error)
    ops = [list(load.operands), list(store.operands)]
    if rest or load.mnemonic != "mov" or store.mnemonic != "mov" or any(len(o) != 2 for o in ops):
        return f"{fact.code} is not one mov load and one mov store"
    (dst, src), (mem, reg) = ops
    if not (dst.type == X86_OP_REG and src.type == X86_OP_MEM and mem.type == X86_OP_MEM and reg.type == X86_OP_REG
            and dst.reg == reg.reg):
        return f"{fact.code} does not load a register from memory and store that register"
    if {dst.size, src.size, mem.size, reg.size} != {width} or fact.value != width:
        return f"{fact.code} moves {sorted({dst.size, src.size, mem.size, reg.size})} bytes, not the key's {width}"
    return None


def key_compare_problem(fact, width, branches):
    """Why `fact` is not a `width`-byte compare with the field at +value, branched on by one of `branches`, or None."""
    from capstone.x86 import X86_OP_MEM
    try:
        cmp, jcc, *rest = _whole(fact.code)
    except ValueError as error:
        return str(error)
    if rest or cmp.mnemonic != "cmp" or len(cmp.operands) != 2:
        return f"{fact.code} is not one cmp and one branch"
    fields = [op for op in cmp.operands if op.type == X86_OP_MEM]
    if len(fields) != 1 or fields[0].mem.disp != fact.value or {op.size for op in cmp.operands} != {width}:
        return f"{fact.code} does not compare {width} bytes with the field at +{fact.value}"
    if jcc.size != 2 or jcc.bytes[0] not in branches:
        return f"{fact.code} branches with {jcc.mnemonic}, not with the key's signedness"
    return None


class StandInScalarKeyFamily:
    """A map's helpers rowed on a size-only stand-in struct where retail's key is a builtin (P139). There is no class
    to prove it, so retail's own handling of the key does, on the tree the family's copy builds:
    - `key_copy` (row rva, copy fact): retail copies the key as one load and one store of the builtin's width. The
      row is a member, reached from the family's `copy` along `copy_path`: (row rva, calls fact) pairs, the first in
      `copy`, each call reaching the next pair's row and the last the copy fact's row.
    - `key_compare` (row rva, compare fact): retail compares the key with the builtin's width and branches with its
      signedness (SCALAR_KEYS). `compare_path`'s calls, all in that same row, reach a row of the family and a member.
    `members` {rva: name} are rows instantiated over the value type the respelled copy builds (`pair<const key, V>`).
    `rows`, `pins`, `spellings` and `bindings` are a StandInElementFamily's. Each spelling is scalar_swap of the old
    one, compared on decoded trees. There are no duplicates or retired pins."""

    def __init__(self, old, new, code, copy, spellings, members, bindings, rows, pins, key_copy, copy_path,
                 key_compare, compare_path):
        import rename                                  # lazily: rename imports this module inside its functions too
        if code not in SCALAR_KEYS:
            raise ValueError(f"{code!r} is no builtin key this route proves")
        width, branches = SCALAR_KEYS[code]
        for label, value in (("members", members), ("bindings", bindings), ("rows", rows),
                             ("copy path", copy_path), ("compare path", compare_path)):
            if not value:
                raise ValueError(f"a scalar key family still needs its {label}")
        if copy not in rows:
            raise ValueError(f"0x{copy:08X} is not a row of the family")
        claimed = [*rows.values(), *pins.values()]
        if set(spellings) != {old_name for old_name, _facts in claimed}:
            raise ValueError("every spelling is a row's or pin's and every row and pin has one")

        def tree(name):
            try:
                return rename.type_tree(name)
            except rename.Unparsed as error:
                raise ValueError(f"{name} cannot be decoded: {error}") from None
        for old_name, _facts in claimed:
            if f"U{old}@@" not in old_name:
                raise ValueError(f"{old_name} does not spell the stand-in {old}")
            before, after = tree(old_name), tree(spellings[old_name])
            if scalar_swap(before, old, code) != after or before == after:
                raise ValueError(f"{old_name} must respell by the scalar swap alone ({old} to the builtin {code})")
        key = ("CV", "$$CB", ("B", code))
        value_types = {node for node in _subtrees(tree(spellings[rows[copy][0]]))
                       if isinstance(node, tuple) and node[:2] == ("T", "pair") and node[2][:1] == (key,)}
        if len(value_types) != 1:
            raise ValueError(f"the respelled copy names {len(value_types)} value types over the key, not one")
        value_type = next(iter(value_types))
        for at, name in members.items():
            if value_type not in set(_subtrees(tree(name))):
                raise ValueError(f"member 0x{at:08X} {name} is no instantiation over the copy's value type")
        if copy_path[0][0] != copy:
            raise ValueError("the copy path starts in the family's copy")
        hops = [*(at for at, _fact in copy_path[1:]), key_copy[0]]
        for (at, fact), target in zip(copy_path, hops):
            if fact.kind != "calls" or fact.value != target:
                raise ValueError(f"0x{fact.site:08X} in 0x{at:08X} does not call 0x{target:08X}, the path's next row")
        if key_copy[0] not in members:
            raise ValueError(f"the key's copy at 0x{key_copy[0]:08X} is in no member")
        if key_copy[1].kind != "copy":
            raise ValueError("the key's copy must be a copy fact")
        problem = key_copy_problem(key_copy[1], width)
        if problem:
            raise ValueError(f"the key's copy: {problem}")
        if key_compare[1].kind != "compare":
            raise ValueError("the key's compare must be a compare fact")
        problem = key_compare_problem(key_compare[1], width, branches)
        if problem:
            raise ValueError(f"the key's compare: {problem}")
        if any(at != key_compare[0] or fact.kind != "calls" for at, fact in compare_path):
            raise ValueError("the compare path is calls in the compare's own row")
        reached = {fact.value for _at, fact in compare_path}
        if not reached & set(rows) or not reached & set(members):
            raise ValueError("the compare's row must reach a row of the family and a member")
        named = dict(members)
        named.update({at: spellings[name] for at, (name, _facts) in [*rows.items(), *pins.items()]})
        reach = set(members) | set(rows) | set(pins)
        for at, (old_name, facts) in rows.items():
            if not any(f.kind == "calls" and f.value in reach for f in facts):
                raise ValueError(f"0x{at:08X} {old_name} reaches no member or row of the family by a call")
        for at, offset, target in bindings:
            if at not in rows:
                raise ValueError(f"binding 0x{at:08X} is no row of the family")
            fact = next((f for f in rows[at][1] if f.kind == "calls" and f.site == at + offset - 1), None)
            if fact is None:
                raise ValueError(f"0x{at:08X}+{offset} is not one of the row's own calls")
            if named.get(fact.value) != target:
                raise ValueError(f"0x{at:08X}+{offset} calls 0x{fact.value:08X}, which is not {target}")
        if set(rows) - {at for at, _offset, _target in bindings}:
            raise ValueError("every row needs a binding: a row with nothing to bind cannot show its key survived")
        self.old, self.new, self.code, self.copy, self.spellings = old, new, code, copy, spellings
        self.members, self.bindings, self.rows, self.pins = dict(members), tuple(bindings), rows, pins
        self.key_copy, self.copy_path = key_copy, tuple(copy_path)
        self.key_compare, self.compare_path = key_compare, tuple(compare_path)
        self.value_type, self.duplicates, self.retired = value_type, {}, {}

    def respell(self, name):
        return self.spellings.get(name, name)

    def located(self):
        """[(row rva, fact)] for every fact a row other than the family's own holds: the paths and the key facts."""
        return [*self.copy_path, self.key_copy, *self.compare_path, self.key_compare]

    def facts(self):
        return ([f for _name, facts in [*self.rows.values(), *self.pins.values()] for f in facts]
                + [fact for _at, fact in self.located()])

    def evidence(self):
        return record(self.rows[self.copy][1])


# The builtin values a StandInValueFamily may replace, by mangling code: the decoded tree and the width in bytes. Only
# void* (P143); another builtin is another reviewed entry.
BUILTIN_VALUES = {"PAX": (("P", "PA", ("B", "X")), 4)}
NODE_HEADER = 16                                       # _Rb_tree_node_base: color, parent, left, right


def value_swap(tree, key, old, new):
    """`tree` (a rename.type_tree) with the builtin value `old` (a decoded tree) read as the struct `new` where it is
    the value of pair<const key, .> or the mapped type of map<key, ., ...>: the two places a map's helpers spell their
    value. Any other `old` (a void* parameter, a pair over another key) stays. That is the whole respelling a
    stand-in value allows."""
    struct = ("C", "U", ("Q", (("N", new),)))
    if isinstance(tree, tuple) and len(tree) == 3 and tree[:2] == ("T", "pair") and tree[2] == (("CV", "$$CB", key), old):
        return ("T", "pair", (("CV", "$$CB", key), struct))
    if isinstance(tree, tuple) and len(tree) == 3 and tree[:2] == ("T", "map") and tree[2][:2] == (key, old):
        tree = ("T", "map", (key, struct) + tree[2][2:])
    if isinstance(tree, tuple):
        return tuple(value_swap(node, key, old, new) for node in tree)
    return tree


def node_alloc_problem(fact):
    """Why `fact` is not one push of the immediate `value` (the byte count an allocation takes), or None."""
    from capstone.x86 import X86_OP_IMM
    try:
        push, *rest = _whole(fact.code)
    except ValueError as error:
        return str(error)
    if rest or push.mnemonic != "push" or len(push.operands) != 1 or push.operands[0].type != X86_OP_IMM:
        return f"{fact.code} is not one push of an immediate"
    if push.operands[0].imm != fact.value:
        return f"{fact.code} pushes {push.operands[0].imm}, not {fact.value}"
    return None


class StandInValueFamily:
    """A map's insert helpers rowed on a builtin value where retail's value is a size-only stand-in struct, the one
    the map's own node creator is already rowed on (P143). No class proves the struct, so retail's node does:
    - `node` (member rva, alloc fact): the creator pushes the node's byte count, and `node_call`, the call that
      follows at once, takes it. The count is NODE_HEADER plus pair<const key, new> (the key's width, then
      `value_size`), and it is not NODE_HEADER plus pair<const key, old>: retail allocates the new value, never the old.
    - `members` {rva: name} are rows instantiated over pair<const key, new>; the node lies in one of them. Every row
      reaches the node's member by calls: the rows' own facts and `member_path` ((member rva, calls fact) pairs).
    - `retired` {rva: (old name, facts)} are pins of an old spelling on an address a member rows under exactly its
      respelling: a second name there, so they go, never respelled.
    - `callers` {rva: (name, facts)} are rows outside the family that call a family row; `caller_bindings`, like
      `bindings`, are what each rebuilt caller must bind (the respelled row it calls).
    `rows`, `spellings` and `bindings` are a StandInScalarKeyFamily's. Each spelling is value_swap of the old one,
    compared on decoded trees. No pin is respelled in place and there are no duplicates."""

    def __init__(self, old, new, key, value_size, copy, spellings, members, bindings, rows, retired, node, node_call,
                 member_path, callers, caller_bindings):
        import rename                                  # lazily: rename imports this module inside its functions too
        if old not in BUILTIN_VALUES:
            raise ValueError(f"{old!r} is no builtin value this route replaces")
        if key not in SCALAR_KEYS:
            raise ValueError(f"{key!r} is no builtin key this route reads")
        old_tree, old_width = BUILTIN_VALUES[old]
        key_tree, key_width = ("B", key), SCALAR_KEYS[key][0]
        for label, value in (("members", members), ("bindings", bindings), ("rows", rows),
                             ("member path", member_path)):
            if not value:
                raise ValueError(f"a stand-in value family still needs its {label}")
        if copy not in rows:
            raise ValueError(f"0x{copy:08X} is not a row of the family")
        claimed = [*rows.values(), *retired.values()]
        if set(spellings) != {old_name for old_name, _facts in claimed}:
            raise ValueError("every spelling is a row's or retired pin's and every row and retired pin has one")

        def tree(name):
            try:
                return rename.type_tree(name)
            except rename.Unparsed as error:
                raise ValueError(f"{name} cannot be decoded: {error}") from None
        for old_name, _facts in claimed:
            before, after = tree(old_name), tree(spellings[old_name])
            if value_swap(before, key_tree, old_tree, new) != after or before == after:
                raise ValueError(f"{old_name} must respell by the value swap alone ({old} to the struct {new})")
        value_type = ("T", "pair", (("CV", "$$CB", key_tree), ("C", "U", ("Q", (("N", new),)))))
        for at, name in members.items():
            if value_type not in set(_subtrees(tree(name))):
                raise ValueError(f"member 0x{at:08X} {name} is no instantiation over pair<const {key}, {new}>")
        terms = set()
        for at, (old_name, _facts) in retired.items():
            if members.get(at) != spellings[old_name]:
                raise ValueError(f"pin 0x{at:08X} is retired only onto the member that rows its respelling there")
            identifier = rename._identifier(old_name)
            if not identifier:
                raise ValueError(f"{old_name} has no identifier a consumer's source would spell")
            terms.add((identifier,))
        if set(retired) & set(rows) or set(callers) & (set(rows) | set(members)):
            raise ValueError("a row, a member, a retired pin and a caller are four different addresses")
        node_at, alloc = node
        if node_at not in members:
            raise ValueError(f"the node's count at 0x{node_at:08X} is in no member")
        if alloc.kind != "alloc":
            raise ValueError("the node's count must be an alloc fact")
        problem = node_alloc_problem(alloc)
        if problem:
            raise ValueError(f"the node's count: {problem}")
        if node_call.kind != "calls" or node_call.site != alloc.site + len(expected(alloc)):
            raise ValueError("the node's count must feed the call that follows it at once")
        if value_size <= 0 or value_size % 4 or value_size == old_width:
            raise ValueError(f"a value of {value_size} bytes is no dword-aligned struct retail can tell from {old}")
        if alloc.value != NODE_HEADER + key_width + value_size:
            raise ValueError(f"retail's node holds {alloc.value - NODE_HEADER} bytes of pair, not pair<const {key}, "
                             f"{new}>'s {key_width + value_size}")
        edges = {}
        for at, (_old_name, facts) in rows.items():
            edges.setdefault(at, set()).update(f.value for f in facts if f.kind == "calls")
        for at, fact in member_path:
            if at not in members or fact.kind != "calls":
                raise ValueError("the member path is calls in members")
            edges.setdefault(at, set()).add(fact.value)
        for at, (old_name, _facts) in rows.items():
            seen, frontier = {at}, [at]
            while frontier:
                for nxt in edges.get(frontier.pop(), ()):
                    if nxt not in seen:
                        seen.add(nxt)
                        frontier.append(nxt)
            if node_at not in seen:
                raise ValueError(f"0x{at:08X} {old_name} reaches no node of the new value by calls")
        named = dict(members)
        named.update({at: spellings[name] for at, (name, _facts) in rows.items()})
        for table, bound, label in ((rows, bindings, "row of the family"), (callers, caller_bindings, "caller")):
            for at, offset, target in bound:
                if at not in table:
                    raise ValueError(f"binding 0x{at:08X} is no {label}")
                fact = next((f for f in table[at][1] if f.kind == "calls" and f.site == at + offset - 1), None)
                if fact is None:
                    raise ValueError(f"0x{at:08X}+{offset} is not one of the {label}'s own calls")
                if named.get(fact.value) != target or (table is callers and fact.value not in rows):
                    raise ValueError(f"0x{at:08X}+{offset} calls 0x{fact.value:08X}, which is not {target}")
            if set(table) - {at for at, _offset, _target in bound}:
                raise ValueError(f"every {label} needs a binding: one with nothing to bind cannot show the value survived")
        self.old, self.new, self.key, self.value_size, self.copy = old, new, key, value_size, copy
        self.spellings, self.members, self.bindings, self.rows = spellings, dict(members), tuple(bindings), rows
        self.retired, self.node, self.node_call, self.member_path = retired, node, node_call, tuple(member_path)
        self.callers, self.caller_bindings = callers, tuple(caller_bindings)
        self.value_type, self.pins, self.duplicates = value_type, {}, {}
        # A unit can name a retired pin without defining it only by declaring it, and that declaration spells the
        # pin's identifier, in the unit or in a header it includes (its types may come from other headers). A unit
        # that instantiates the old tree defines its own copy and leaves nothing unresolved. rename.py rebuilds
        # every stale object of a unit spelling the identifier, or including such a file transitively, before
        # reading it; the mangled text is no such term, since ordinary C++ never spells it.
        self.consumer_terms = tuple(sorted(terms))

    def respell(self, name):
        return self.spellings.get(name, name)

    def located(self):
        """[(member rva, fact)] for every fact a member holds: the node's count, its call and the member path."""
        return [self.node, (self.node[0], self.node_call), *self.member_path]

    def facts(self):
        return ([f for _name, facts in [*self.rows.values(), *self.retired.values(), *self.callers.values()]
                 for f in facts] + [fact for _at, fact in self.located()])

    def evidence(self):
        return record(self.rows[self.copy][1])


# The keys a RetypedTreeFamily may give a tree, by mangling code: the key as a template argument, its const form (the
# pair's first, and the pointee of a const pointer or reference to the key) and its width in bytes. Only const char*
# (P144); another key is another reviewed entry.
TREE_KEYS = {"PBD": (("P", "PB", ("B", "D")), ("P", "QB", ("B", "D")), 4)}


def _struct(name):
    return ("C", "U", ("Q", (("N", name),)))


def tree_swap(tree, old_key, old_value, new_key, new_value, new_compare):
    """`tree` (a rename.type_tree) with a builtin-keyed tree read as one with the new key, comparator and value, all
    together. Four shapes change, and only whole: pair<const old_key, old_value> becomes pair<new const key, new
    value>; an _Rb_tree whose key, pair and comparator are old_key, that pair and less<old_key> takes the new key and
    comparator; a map over <old_key, old_value, less<old_key>, ...> takes the new key, value and comparator; a pointer
    or reference to const old_key (how the pair's first is passed) points or refers to the new const key. Nothing else
    changes: a key passed by value, the builtins in any other template, a pair or tree over another key or value."""
    key_arg, const_key, _width = TREE_KEYS[new_key]
    key = ("B", old_key)
    value = BUILTIN_VALUES[old_value][0]
    less = ("C", "U", ("Q", (("T", "less", (key,)), ("N", "_STL"))))
    old_pair = ("T", "pair", (("CV", "$$CB", key), value))
    pair_class = ("C", "U", ("Q", (old_pair, ("N", "_STL"))))
    new_pair = ("T", "pair", (const_key, _struct(new_value)))

    def walk(node):
        if not isinstance(node, tuple):
            return node
        if node == old_pair:
            return new_pair
        if len(node) == 3 and node[0] == "T":
            args = node[2]
            if node[1] == "_Rb_tree" and len(args) == 5 and (args[0], args[1], args[3]) == (key, pair_class, less):
                return ("T", "_Rb_tree", (key_arg, walk(args[1]), walk(args[2]), _struct(new_compare), walk(args[4])))
            if node[1] == "map" and len(args) == 4 and args[:3] == (key, value, less):
                return ("T", "map", (key_arg, _struct(new_value), _struct(new_compare), walk(args[3])))
        if len(node) == 3 and node[0] == "P" and node[1] in ("PB", "AB") and node[2] == key:
            return ("P", node[1], const_key)
        return tuple(walk(child) for child in node)
    return walk(tree)


class RetypedTreeFamily:
    """A tree's helpers rowed on <unsigned, void*> under less<unsigned>, where retail's tree has another key,
    comparator and value (P144). They change together, which no one fact shows, so three kinds of fact must agree:
    - `nodes` [(rva, alloc fact, call fact)]: retail's node allocations push NODE_HEADER plus the new key's width plus
      `value_size`, never NODE_HEADER plus pair<const old key, old value>, and the call that follows at once takes the
      count. Every row reaches one of them by calls: its own facts and `node_path` (calls in members or node owners).
    - `witness` (caller rva, caller name, call fact, pin name): a matched row outside the family calls the address of
      a family row, and the pin it binds there spells the map over exactly the new key, value and comparator.
      rename.py ties the caller, its call and the pin to the ledger.
    - `spellings` {old: new}: each row's new name is tree_swap of its old one and nothing else, and names the new
      pair; each old name spells the old pair and less<old key>.
    `members` {rva: name} are rows outside the family that the rows call; `bindings` [(row rva, offset, target)] are
    the REL32s each rebuilt row must hold, to a respelled row or a member, one at least per row; `callers` and
    `caller_bindings` are rows outside the family, rebuilt under their own names, that call a family row. There are
    no pins, retired pins or duplicates: a pin the new spelling needs is admitted by tools/pin_admission.py."""

    def __init__(self, old_key, old_value, new_key, new_value, new_compare, value_size, copy, spellings, members,
                 bindings, rows, nodes, node_path, witness, callers, caller_bindings):
        import rename                                  # lazily: rename imports this module inside its functions too
        if old_key not in SCALAR_KEYS:
            raise ValueError(f"{old_key!r} is no builtin key this route reads")
        if old_value not in BUILTIN_VALUES:
            raise ValueError(f"{old_value!r} is no builtin value this route replaces")
        if new_key not in TREE_KEYS:
            raise ValueError(f"{new_key!r} is no key this route gives a tree")
        for label, value in (("rows", rows), ("nodes", nodes), ("bindings", bindings), ("witness", witness)):
            if not value:
                raise ValueError(f"a retyped tree family still needs its {label}")
        if copy not in rows:
            raise ValueError(f"0x{copy:08X} is not a row of the family")
        if set(spellings) != {old_name for old_name, _facts in rows.values()}:
            raise ValueError("every spelling is a row's and every row has one")
        key_arg, const_key, key_width = TREE_KEYS[new_key]
        old_tree, old_width = BUILTIN_VALUES[old_value]
        old_key_tree = ("B", old_key)
        old_pair = ("T", "pair", (("CV", "$$CB", old_key_tree), old_tree))
        old_less = ("C", "U", ("Q", (("T", "less", (old_key_tree,)), ("N", "_STL"))))
        new_pair = ("T", "pair", (const_key, _struct(new_value)))
        new_map = ("T", "map", (key_arg, _struct(new_value), _struct(new_compare), ("C", "V", ("Q", (
            ("T", "allocator", (("C", "U", ("Q", (new_pair, ("N", "_STL")))),)), ("N", "_STL"))))))

        def tree(name):
            try:
                return rename.type_tree(name)
            except rename.Unparsed as error:
                raise ValueError(f"{name} cannot be decoded: {error}") from None
        for old_name, _facts in rows.values():
            before, after = tree(old_name), tree(spellings[old_name])
            if tree_swap(before, old_key, old_value, new_key, new_value, new_compare) != after or before == after:
                raise ValueError(f"{old_name} must respell by the tree swap alone (<{old_key}, {old_value}, less> to "
                                 f"<{new_key}, {new_value}, {new_compare}>)")
            if not {old_pair, old_less} <= set(_subtrees(before)):
                raise ValueError(f"{old_name} does not spell pair<const {old_key}, {old_value}> and less<{old_key}>")
            if new_pair not in set(_subtrees(after)):
                raise ValueError(f"{spellings[old_name]} is no instantiation over the new pair")
        if value_size <= 0 or value_size % 4 or value_size == old_width:
            raise ValueError(f"a value of {value_size} bytes is no dword-aligned struct retail can tell from {old_value}")
        owners = set(members)
        for at, alloc, call in nodes:
            if alloc.kind != "alloc":
                raise ValueError(f"the node count at 0x{at:08X} must be an alloc fact")
            problem = node_alloc_problem(alloc)
            if problem:
                raise ValueError(f"the node count at 0x{at:08X}: {problem}")
            if call.kind != "calls" or call.site != alloc.site + len(expected(alloc)):
                raise ValueError(f"the node count at 0x{at:08X} must feed the call that follows it at once")
            if alloc.value != NODE_HEADER + key_width + value_size:
                raise ValueError(f"retail's node at 0x{at:08X} holds {alloc.value - NODE_HEADER} bytes of pair, not "
                                 f"pair<const {new_key}, {new_value}>'s {key_width + value_size}")
            owners.add(at)
        if set(callers) & (set(rows) | set(members)) or set(rows) & owners:
            raise ValueError("a row, a member or node and a caller are different addresses")
        edges = {}
        for at, (_old_name, facts) in rows.items():
            edges.setdefault(at, set()).update(f.value for f in facts if f.kind == "calls")
        for at, fact in node_path:
            if at not in owners or fact.kind != "calls":
                raise ValueError("the node path is calls in members or node owners")
            edges.setdefault(at, set()).add(fact.value)
        node_at = {at for at, _alloc, _call in nodes}
        for at, (old_name, _facts) in rows.items():
            seen, frontier = {at}, [at]
            while frontier:
                for nxt in edges.get(frontier.pop(), ()):
                    if nxt not in seen:
                        seen.add(nxt)
                        frontier.append(nxt)
            if not seen & node_at:
                raise ValueError(f"0x{at:08X} {old_name} reaches no node of the new value by calls")
        caller_at, caller_name, call, pin_name = witness
        if call.kind != "calls" or call.value not in rows:
            raise ValueError("the witness must call a row of the family")
        if caller_at in rows or caller_at in callers:
            raise ValueError("the witness is a row outside the family and its rebuilt callers")
        if new_map not in set(_subtrees(tree(pin_name))):
            raise ValueError(f"the witness pin {pin_name} spells no map<{new_key}, {new_value}, {new_compare}>")
        named = dict(members)
        named.update({at: spellings[name] for at, (name, _facts) in rows.items()})
        for table, bound, label in ((rows, bindings, "row of the family"), (callers, caller_bindings, "caller")):
            for at, offset, target in bound:
                if at not in table:
                    raise ValueError(f"binding 0x{at:08X} is no {label}")
                fact = next((f for f in table[at][1] if f.kind == "calls" and f.site == at + offset - 1), None)
                if fact is None:
                    raise ValueError(f"0x{at:08X}+{offset} is not one of the {label}'s own calls")
                if named.get(fact.value) != target or (table is callers and fact.value not in rows):
                    raise ValueError(f"0x{at:08X}+{offset} calls 0x{fact.value:08X}, which is not {target}")
            if set(table) - {at for at, _offset, _target in bound}:
                raise ValueError(f"every {label} needs a binding: one with nothing to bind cannot show the tree survived")
        self.old, self.new = f"{old_key}/{old_value}", f"{new_key}/{new_value}/{new_compare}"
        self.old_key, self.old_value, self.new_key = old_key, old_value, new_key
        self.new_value, self.new_compare, self.value_size, self.copy = new_value, new_compare, value_size, copy
        self.spellings, self.members, self.bindings, self.rows = spellings, dict(members), tuple(bindings), rows
        self.nodes, self.node_path, self.witness = tuple(nodes), tuple(node_path), witness
        self.callers, self.caller_bindings = callers, tuple(caller_bindings)
        self.new_map, self.pins, self.retired, self.duplicates = new_map, {}, {}, {}

    def respell(self, name):
        return self.spellings.get(name, name)

    def facts(self):
        return ([f for _name, facts in [*self.rows.values(), *self.callers.values()] for f in facts]
                + [f for _at, alloc, call in self.nodes for f in (alloc, call)]
                + [fact for _at, fact in self.node_path] + [self.witness[2]])

    def evidence(self):
        return record(self.rows[self.copy][1])


# The CRT's vector iterators (ehvecctr.cpp, ehvecdtr.cpp): the only calls a SlotOperandFamily's operand may feed.
ITERATOR_NAMES = ("??_L@YGXPAXIHP6EX0@Z1@Z", "??_M@YGXPAXIHP6EX0@Z@Z")


def _special_member_class(name):
    """The class `name` is a constructor or destructor of (`??0X@@...` / `??1X@@...`), or None."""
    if not name.startswith(("??0", "??1")) or "@@" not in name:
        return None
    return name[3:name.index("@@")]


class SlotOperandFamily:
    """A row rowed under the wrong element type, where the table it fills cannot name the class: /OPT:ICF shares the
    table between instantiations, so its name says only which one the ledger chose, and that name is never read here.
    Retail states the element another way: the row's own body passes a rowed destructor of the element to the CRT's
    vector iterator (??_L or ??_M), and that destructor's row names the element.

    `old_element` and `new_element` are element types as mangled after `U` (`RendererDataStruct@Render2DSentenceClass`);
    every spelling swaps exactly `U<old_element>@@` for `U<new_element>@@` and nothing else. `slot` is the copy row's
    word in the table. `writer` {name, rva, facts} is a rowed constructor or destructor of the class enclosing the new
    element whose facts write that table as a vftable pointer: the container of these elements uses this table.
    `element_dtor` {name, rva} is the new element's rowed destructor. `operands` [(push, call)] are the copy's pushes of
    that destructor (`68` imm32), each followed in the row by a call to a rowed iterator of `iterators` {rva: name}.
    Every row other than the copy is proved by the copy loading its address (its handler: `68` or `b8` imm32).

    After the build the rebuilt copy must bind the element destructor at each push (DIR32) and the iterator at each
    call (REL32): retail_identity_problems reads both. Another family of this kind is another reviewed entry."""

    def __init__(self, old_element, new_element, copy, spellings, slot, writer, element_dtor, operands, iterators,
                 rows, pins=None):
        if copy not in rows:
            raise ValueError(f"0x{copy:08X} is not a row of the family")
        if slot.kind != "slot" or slot.value != copy + IMAGE_BASE:
            raise ValueError("the slot fact must be the copy's word in the table")
        old_frag, new_frag = f"U{old_element}@@", f"U{new_element}@@"
        if old_frag == new_frag:
            raise ValueError("the element does not change")
        for old_name, _facts in rows.values():
            want = old_name.replace(old_frag, new_frag)
            if old_frag not in old_name or spellings.get(old_name) != want:
                raise ValueError(f"{old_name} must respell by the element swap alone, to {want}")
        if set(spellings) != {old_name for old_name, _facts in rows.values()}:
            raise ValueError("every spelling is a row's and every row has one")
        if element_dtor["name"] != f"??1{new_element}@@QAE@XZ":
            raise ValueError(f"{element_dtor['name']} is not the destructor of {new_element}")
        scope = new_element.split("@", 1)[1] if "@" in new_element else None
        if not scope or _special_member_class(writer["name"]) != scope:
            raise ValueError(f"{writer['name']} is no constructor or destructor of {scope}, the class enclosing the element")
        stores = [f for f in writer["facts"] if f.kind == "stores" and f.value == slot.code[0] and f.code in VPTR_STORES]
        if not stores or len(stores) != len(writer["facts"]):
            raise ValueError("the writer's facts are its stores of the table as a vftable pointer, and nothing else")
        if not operands:
            raise ValueError("a family of this kind needs the copy's operands")
        copy_facts = set(rows[copy][1])
        if slot not in copy_facts:
            raise ValueError("the slot fact is one of the copy's facts")
        for push, call in operands:
            if not (push.kind == "stores" and push.code == "68" and push.value == element_dtor["rva"] + IMAGE_BASE):
                raise ValueError(f"0x{push.site:08X} must push {element_dtor['name']}")
            if not (call.kind == "calls" and call.site > push.site and iterators.get(call.value) in ITERATOR_NAMES):
                raise ValueError(f"0x{call.site:08X} must call a vector iterator after the push")
            if push not in copy_facts or call not in copy_facts:
                raise ValueError("each operand is one of the copy's facts")
        strangers = sorted(set(iterators) - {call.value for _push, call in operands})
        if strangers:
            raise ValueError(f"0x{strangers[0]:08X} is an iterator no operand calls")
        for at, (old_name, facts) in rows.items():
            if at != copy and (len(facts) != 1 or facts[0].kind != "stores" or facts[0].code not in ("68", "b8")
                               or facts[0].value != at + IMAGE_BASE):
                raise ValueError(f"0x{at:08X} must be proved by the copy loading its address, and by nothing else")
        self.old, self.new, self.copy, self.spellings = old_element, new_element, copy, spellings
        self.slot, self.writer, self.element_dtor = slot, writer, element_dtor
        self.operands, self.iterators = tuple(operands), dict(iterators)
        self.rows, self.pins = rows, pins or {}

    def respell(self, name):
        return self.spellings.get(name, name)

    def facts(self):
        return [f for _name, facts in self.rows.values() for f in facts] + list(self.writer["facts"])

    def evidence(self):
        return record(self.rows[self.copy][1])


C = Fact
_VECTOR = "?$vector@VFXList@@V?$allocator@VFXList@@@_STL@@@_STL@@"
ENABLE_REGION_RECORD = Family(
    old="FXList", new="EnableRegionRecord", table=0x00C61A20, copy=0x0052BD3A, copy_store=0x10,
    owner={"name": "??1EnableRegionRecord@@UAE@XZ", "rva": 0x004E156B,
           "facts": (C("stores", 0x004E156B, 0x00C61A20, "c701"),)},
    rows={
        0x0052BD3A: ("??0FXList@@QAE@ABV0@@Z", (C("stores", 0x0052BD48, 0x00C61A20, "c706"),)),
        0x0052C2F3: ("??$_Construct@VFXList@@V1@@_STL@@YAXPAVFXList@@ABV1@@Z", (C("calls", 0x0052C30F, 0x0052BD3A),)),
        0x0052C8EF: ("??$__uninitialized_copy@PAVFXList@@PAV1@@_STL@@YAPAVFXList@@PAV1@00ABU__false_type@0@@Z",
                     (C("calls", 0x0052C8FD, 0x0052C2F3), C("stride", 0x0052C903, 8, "83c708"))),
        0x0052CAC9: (f"??0{_VECTOR}QAE@ABV01@@Z",
                     (C("calls", 0x0052CB09, 0x0052C8EF), C("stride", 0x0052CAF1, 8, "c1f803"))),
        # the destructor unwinds the member the act's copy ctor builds with 0x0052CAC9: this+8 in both
        0x0052CB26: (f"??1{_VECTOR}QAE@XZ",
                     (C("offset", 0x0052D584, 8, "8d4e08"), C("calls", 0x0052D587, 0x0052CAC9),
                      C("offset", 0x00797252, 8, "83c108"), C("jumps", 0x00797255, 0x0052CB26))),
        0x00565ACB: (f"?_M_insert_overflow@{_VECTOR}IAEXPAVFXList@@ABV3@ABU__false_type@2@I_N@Z",
                     (C("calls", 0x00565B1E, 0x0052C2F3), C("calls", 0x00565B09, 0x0052C8EF),
                      C("stride", 0x00565ADA, 8, "c1f803"))),
        0x0056625E: (f"?push_back@{_VECTOR}QAEXABVFXList@@@Z",
                     (C("calls", 0x00566270, 0x0052C2F3), C("calls", 0x0056628B, 0x00565ACB),
                      C("stride", 0x00566275, 8, "83460408"))),
        0x005655DC: ("??$__uninitialized_fill_n@PAVFXList@@IV1@@_STL@@YAPAVFXList@@PAV1@IABV1@ABU__false_type@0@@Z",
                     (C("calls", 0x005655EF, 0x0052C2F3), C("stride", 0x005655F5, 8, "83c608"))),
        # ParseEnableRegion fills a record (its table loaded at 0x004E1595) and hands it to this thunk
        0x00566527: ("?rva00566527@Rva00566527@@QAEXABVFXList@@@Z",
                     (C("jumps", 0x0056652A, 0x0056625E), C("stores", 0x004E1595, 0x00C61A20, "be"),
                      C("calls", 0x004E15B8, 0x00566527))),
    },
    pins={
        0x0052C8EF: ("??$__uninitialized_copy@PBVFXList@@PAV1@@_STL@@YAPAVFXList@@PBV1@0PAV1@ABU__false_type@0@@Z",
                     (C("calls", 0x0052CB09, 0x0052C8EF),)),
        0x000B6378: ("??0?$_Vector_base@VFXList@@V?$allocator@VFXList@@@_STL@@@_STL@@QAE@IABV?$allocator@VFXList@@@1@@Z",
                     (C("calls", 0x0052CAF5, 0x000B6378),)),
        0x005659CA: (f"?_M_clear@{_VECTOR}IAEXXZ", (C("calls", 0x00565B61, 0x005659CA),)),
        0x00523D6C: ("?allocate@?$allocator@VFXList@@@_STL@@QBEPAVFXList@@IPBX@Z", (C("calls", 0x00565AF7, 0x00523D6C),)),
        0x0021983A: (f"?get_allocator@{_VECTOR}QBE?AV?$allocator@VFXList@@@2@XZ", (C("calls", 0x0052CAE4, 0x0021983A),)),
        0x0014F3C4: ("??0?$_STLP_alloc_proxy@PAVFXList@@V1@V?$allocator@VFXList@@@_STL@@@_STL@@"
                     "QAE@ABV?$allocator@VFXList@@@1@PAVFXList@@@Z", (C("calls", 0x000B638E, 0x0014F3C4),)),
    })
_RECORD = "UBfmeStringRecord0021A940"
_RECORD_ALLOC = f"V?$allocator@{_RECORD}@@@"
_RECORD_TREE = f"?$_Rb_tree@{_RECORD}@@U1@U?$_Identity@{_RECORD}@@@_STL@@U?$less@{_RECORD}@@@3@{_RECORD_ALLOC}3@@_STL@@"
_RECORD_SET = f"?$set@{_RECORD}@@U?$less@{_RECORD}@@@_STL@@{_RECORD_ALLOC}3@@_STL@@"
_RECORD_NODE = f"?$_Rb_tree_node@{_RECORD}@@@"
_LADDER_PAIR = "U?$pair@$$CBJVLadderPref@@@_STL@@"
_LADDER_TREE = (f"?$_Rb_tree@J{_LADDER_PAIR}U?$_Select1st@{_LADDER_PAIR}@2@U?$less@J@2@"
                f"V?$allocator@{_LADDER_PAIR}@2@@_STL@@")
_LADDER_MAP = f"?$map@JVLadderPref@@U?$less@J@_STL@@V?$allocator@{_LADDER_PAIR}@3@@_STL@@"
_LADDER_BASE = f"?$_Rb_tree_base@{_LADDER_PAIR}V?$allocator@{_LADDER_PAIR}@2@@_STL@@"
_RECORD_MCOPY = f"?_M_copy@{_RECORD_TREE}AAEPAU{_RECORD_NODE}2@PAU32@0@Z"
_RECORD_TREE_COPY = f"??0{_RECORD_TREE}QAE@ABV01@@Z"
# The member at +0x54 of the hero sub-class record: its copy ctor builds it with 0x0021DBBA, its dtor tears it
# down with the record tree's 0x0021D61F. The nodes are the same 0x24 bytes as map<long, LadderPref>'s, so node
# size says nothing; the element copies differ: a dword and three narrow strings against wide, narrow, word, dword.
HERO_RECORD_SET = BodyFamily(
    old="LadderPref", new="BfmeStringRecord0021A940", copy=0x0021DBBA,
    # map<long,LadderPref>'s destructor stays what it is; the respell stops the sub-class copy's unit emitting it.
    forced_moves={0x005DFF76: (f"??1{_LADDER_MAP}QAE@XZ", "Code/GameEngine/Source/Common/Rva0021E85ACopy.cpp")},
    spellings={
        f"??0{_LADDER_TREE}QAE@ABV01@@Z": _RECORD_TREE_COPY,
        f"??0{_LADDER_MAP}QAE@ABV01@@Z": f"??0{_RECORD_SET}QAE@ABV01@@Z",
        f"?get_allocator@{_LADDER_BASE}QBE?AV?$allocator@{_LADDER_PAIR}@2@XZ":
            f"?get_allocator@?$_Rb_tree_base@{_RECORD}@@{_RECORD_ALLOC}_STL@@@_STL@@QBE?AV?$allocator@{_RECORD}@@@2@XZ",
    },
    element=(C("calls", 0x0021D7DC, 0x0021D13B), C("calls", 0x0021D144, 0x0021C48E), C("calls", 0x0021C4A2, 0x0021B8C5),
             C("calls", 0x0021B8E1, 0x0021AAE1), C("calls", 0x0021AAF3, 0x00219B0B),
             C("offset", 0x00219B1B, 0, "8b07"), C("offset", 0x00219B1F, 0, "8906"),
             C("calls", 0x00219B2B, 0x000365F0), C("calls", 0x00219B3B, 0x000365F0), C("calls", 0x00219B4B, 0x000365F0)),
    old_element=(C("calls", 0x005DFCBD, 0x005DFBDE), C("calls", 0x005DFBFA, 0x005DFBB8), C("calls", 0x005DFBCA, 0x005BA3F5),
                 C("calls", 0x005BA40B, 0x00037050), C("calls", 0x005BA41B, 0x000365F0),
                 C("offset", 0x005BA420, 8, "668b4708")),
    old_members={0x005DFCA9: f"?_M_create_node@{_LADDER_TREE}IAEPAU?$_Rb_tree_node@{_LADDER_PAIR}@2@ABU?$pair@$$CBJVLadderPref@@@2@@Z",
                 0x005BA3F5: "??0LadderPref@@QAE@ABV0@@Z"},
    members={
        0x0021D7CF: _RECORD_MCOPY,
        0x0021D13B: f"?_M_clone_node@{_RECORD_TREE}IAEPAU{_RECORD_NODE}2@PAU32@@Z",
        0x0021C48E: f"?_M_create_node@{_RECORD_TREE}IAEPAU{_RECORD_NODE}2@AB{_RECORD}@@@Z",
        0x0021B8C5: f"??$_Construct@{_RECORD}@@U1@@_STL@@YAXPA{_RECORD}@@ABU1@@Z",
        0x0021AAE1: "??0BfmeStringRecord0021A940@@QAE@ABU0@@Z",
        0x00219B0B: "??0BfmeStringRecord00219B0B@@QAE@ABU0@@Z",
        0x0021D842: f"??4{_RECORD_TREE}QAEAAV01@ABV01@@Z",
        0x0021DA96: f"??4{_RECORD_SET}QAEAAV01@ABV01@@Z",
        0x0021D61F: f"??1{_RECORD_TREE}QAE@XZ",
        0x0021DA0E: f"??1{_RECORD_SET}QAE@XZ",
    },
    # operator= reaches the same _M_copy, the dtor tears down this member, and the set's dtor is the same tree's
    member_facts=(C("calls", 0x0021DA9D, 0x0021D842), C("calls", 0x0021D879, 0x0021D7CF),
                  C("offset", 0x0021E520, 0x54, "8d4e54"), C("calls", 0x0021E52A, 0x0021D61F),
                  C("jumps", 0x0021DA0E, 0x0021D61F)),
    bindings=((0x0021DBBA, 0x5C, _RECORD_MCOPY), (0x0021E134, 0x08, _RECORD_TREE_COPY)),
    rows={
        0x0021DBBA: (f"??0{_LADDER_TREE}QAE@ABV01@@Z",
                     (C("offset", 0x0021E912, 0x54, "8d4b54"), C("calls", 0x0021E919, 0x0021DBBA),
                      C("calls", 0x0021DC15, 0x0021D7CF))),
        0x0021E134: (f"??0{_LADDER_MAP}QAE@ABV01@@Z", (C("calls", 0x0021E13B, 0x0021DBBA),)),
    },
    pins={0x0021983A: (f"?get_allocator@{_LADDER_BASE}QBE?AV?$allocator@{_LADDER_PAIR}@2@XZ",
                       (C("calls", 0x0021DBD7, 0x0021983A),))},
    retired={0x0021D7CF: (f"?_M_copy@{_LADDER_TREE}AAEPAU?$_Rb_tree_node@{_LADDER_PAIR}@2@PAU32@0@Z",
                          (C("calls", 0x0021DC15, 0x0021D7CF),))})
_LOCO = "Rva001E3E43"
# One class rowed under two names. Both constructors store the table; the destructor stores it first; its deleting
# destructor is slot 0 and reaches the destructor; the copy ctor reaches the assignment; xfer is slot 3.
# The assignment only copies fields and xfer only calls through its Xfer argument's vftable, so neither binds anything:
# the copy ctor's call and slot 3 are their facts. The destructor's references are data: its store of the table is its fact.
LOCOMOTOR = Family(
    old=_LOCO, new="Locomotor", table=0x00BDE888, copy=0x001E4641, copy_store=0x24,
    owner={"name": "??0Locomotor@@QAE@PBVLocomotorTemplate@@_N@Z", "rva": 0x001E449A,
           "facts": (C("stores", 0x001E44B2, 0x00BDE888, "c706"),)},
    rows={
        0x001E4641: (f"??0{_LOCO}@@QAE@ABV0@@Z", (C("stores", 0x001E4663, 0x00BDE888, "c706"),)),
        # the copy ctor loads its own handler, whose funclet's notes the respell carries
        0x00769F90: (f"__ehhandler$??0{_LOCO}@@QAE@ABV0@@Z", (C("stores", 0x001E4641, 0x00B69F90, "b8"),)),
        0x001E3E43: (f"??1{_LOCO}@@UAE@XZ", (C("stores", 0x001E3E43, 0x00BDE888, "c701"),)),
        0x001E4625: (f"??_G{_LOCO}@@UAEPAXI@Z", (slot(0x00BDE888, 0, 4, 0x001E4625), C("calls", 0x001E4628, 0x001E3E43))),
        0x001E3CF4: (f"??4{_LOCO}@@QAEAAV0@ABV0@@Z", (C("calls", 0x001E4679, 0x001E3CF4),)),
        0x001E525A: (f"?xfer@{_LOCO}@@MAEXPAVXfer@@@Z", (slot(0x00BDE888, 3, 4, 0x001E525A),)),
    },
    pins={},
    spellings={
        f"??0{_LOCO}@@QAE@ABV0@@Z": "??0Locomotor@@QAE@ABV0@@Z",
        f"__ehhandler$??0{_LOCO}@@QAE@ABV0@@Z": "__ehhandler$??0Locomotor@@QAE@ABV0@@Z",
        f"??1{_LOCO}@@UAE@XZ": "??1Locomotor@@UAE@XZ",
        f"??_G{_LOCO}@@UAEPAXI@Z": "??_GLocomotor@@UAEPAXI@Z",
        f"??4{_LOCO}@@QAEAAV0@ABV0@@Z": "??4Locomotor@@QAEAAV0@ABV0@@Z",
        f"?xfer@{_LOCO}@@MAEXPAVXfer@@@Z": "?xfer@Locomotor@@MAEXPAVXfer@@@Z",
    },
    leaves={0x001E3CF4: 335, 0x001E525A: 382},
    table_stores={0x001E3E43: 2})
_ENUM = "_ENUM_VALUE@EnumParameterClass"
_RENDERER = "RendererDataStruct@Render2DSentenceClass"


def _resize(element):
    return f"?Resize@?$VectorClass@U{element}@@@@UAE_NHPBU{element}@@@Z"


# Render2DSentenceClass's renderer vector (P104). Its Resize 0x00155690 was rowed on EnumParameterClass::_ENUM_VALUE,
# a donor label; the element the body copies and destroys is the one 0x00001E13 destroys, rowed
# ??1RendererDataStruct@Render2DSentenceClass (a reference to the other name bound WWSaveLoad's real _ENUM_VALUE
# destructor, a StringClass free on +0). The table 0x007D3BC8 whose word 2 is this Resize is /OPT:ICF-shared: the
# AddInfoStruct vector's ctor 0x00154DA0, dtor 0x00156750 and ??_G 0x00156930 write it too, and its words mix
# AddInfoStruct, RenderDeviceDescClass and Vector2 instantiations, so its name is no evidence for the class and is
# not read. What ties the table to this element's container is ~Render2DSentenceClass writing it at 0x00157D06.
RENDERER_VECTOR = SlotOperandFamily(
    old_element=_ENUM, new_element=_RENDERER, copy=0x00155690,
    spellings={_resize(_ENUM): _resize(_RENDERER), "__ehhandler$" + _resize(_ENUM): "__ehhandler$" + _resize(_RENDERER)},
    slot=slot(0x00BD3BC8, 2, 6, 0x00155690),
    writer={"name": "??1Render2DSentenceClass@@QAE@XZ", "rva": 0x00157C70,
            "facts": (C("stores", 0x00157D06, 0x00BD3BC8, "c707"),)},
    element_dtor={"name": f"??1{_RENDERER}@@QAE@XZ", "rva": 0x00001E13},
    # the new vector's EH unwind (??_L) and the old vector's delete[] (??_M), each handed 0x00001E13
    operands=((C("stores", 0x001556FC, 0x00401E13, "68"), C("calls", 0x0015570A, 0x00629512)),
              (C("stores", 0x001557BD, 0x00401E13, "68"), C("calls", 0x001557C6, 0x00629110))),
    iterators={0x00629512: "??_L@YGXPAXIHP6EX0@Z1@Z", 0x00629110: "??_M@YGXPAXIHP6EX0@Z@Z"},
    rows={
        0x00155690: (_resize(_ENUM), (slot(0x00BD3BC8, 2, 6, 0x00155690),
                                      C("stores", 0x001556FC, 0x00401E13, "68"), C("calls", 0x0015570A, 0x00629512),
                                      C("stores", 0x001557BD, 0x00401E13, "68"), C("calls", 0x001557C6, 0x00629110))),
        # the copy pushes its own handler
        0x00766EDC: ("__ehhandler$" + _resize(_ENUM), (C("stores", 0x00155698, 0x00B66EDC, "68"),)),
    })
_SKT_OLD, _SKT = "BfmeAssignRecord44", "ScoredKillTracker"
_SKT_VEC = f"?$vector@U{_SKT_OLD}@@V?$allocator@U{_SKT_OLD}@@@_STL@@@_STL@@"
_SKT_STAND_IN = {
    # the vector of trackers' helpers, rowed on a 44-byte stand-in with no constructor of its own
    0x0055AC1F: f"??4{_SKT_OLD}@@QAEAAU0@ABU0@@Z",
    0x004143A4: f"??$__copy@PAU{_SKT_OLD}@@PAU1@H@_STL@@YAPAU{_SKT_OLD}@@PAU1@00ABUrandom_access_iterator_tag@0@PAH@Z",
    0x00414760: f"?erase@{_SKT_VEC}QAEPAU{_SKT_OLD}@@PAU3@0@Z",
    0x004149B4: f"?clear@{_SKT_VEC}QAEXXZ",
    0x004146E2: f"??1{_SKT_VEC}QAE@XZ",
    0x0041484C: f"?reserve@{_SKT_VEC}QAEXI@Z",
}
_SKT_PINS = {
    0x004143D6: f"??$_M_allocate_and_copy@PAU{_SKT_OLD}@@@{_SKT_VEC}IAEPAU{_SKT_OLD}@@IPAU2@0@Z",
    0x00414403: f"??$__copy_ptrs@PAU{_SKT_OLD}@@PAU1@@_STL@@YAPAU{_SKT_OLD}@@PAU1@00ABU__false_type@0@@Z",
}
_SKT_DUPLICATES = {
    0x00414793: f"?_M_clear@{_SKT_VEC}IAEXXZ",
    0x004144F0: f"??$_Destroy@PAU{_SKT_OLD}@@@_STL@@YAXPAU{_SKT_OLD}@@0@Z",
}
_SKT_RETIRED = {
    0x00414793: f"?_M_clear@{_SKT_VEC}IAEXXZ",
    0x0007E364: f"?allocate@?$allocator@U{_SKT_OLD}@@@_STL@@QBEPAU{_SKT_OLD}@@IPBX@Z",
}


def _skt(name):
    return stand_in_swap(name, _SKT_OLD, _SKT)


# ScoredKillTracker's vector (P134). Its helpers were rowed on BfmeAssignRecord44, a 44-byte struct three units laid
# out as an AsciiString, so the link kept a _Destroy and a ~vector that release a tracker's vftable as a string. The
# stand-in has no constructor, so no table store proves the element; the class's own rows do. The assignment calls
# rva0055A91A and hookToKeeper on this, the copy steps 0x2C and calls that assignment, and erase, clear, the
# destructor and reserve reach the class's rowed _Destroy, _M_clear and allocate.
SCORED_KILL_TRACKER_VECTOR = StandInElementFamily(
    old=_SKT_OLD, new=_SKT, copy=0x0055AC1F, stride=0x2C,
    spellings={name: _skt(name) for name in [*_SKT_STAND_IN.values(), *_SKT_PINS.values(),
                                              *_SKT_DUPLICATES.values(), *_SKT_RETIRED.values()]},
    members={
        0x0055A91A: "?rva0055A91A@ScoredKillTracker@@QAEXXZ",
        0x0055A93C: "?hookToKeeper@ScoredKillTracker@@QAEXPAVRva0039BCF8@@@Z",
        0x004144F0: "??$_Destroy@PAVScoredKillTracker@@@_STL@@YAXPAVScoredKillTracker@@0@Z",
        0x0041445C: "??$__destroy_aux@PAVScoredKillTracker@@@_STL@@YAXPAVScoredKillTracker@@0ABU__false_type@0@@Z",
        0x00414793: "?_M_clear@?$vector@VScoredKillTracker@@V?$allocator@VScoredKillTracker@@@_STL@@@_STL@@IAEXXZ",
        0x0007E364: "?allocate@?$allocator@VScoredKillTracker@@@_STL@@QBEPAVScoredKillTracker@@IPBX@Z",
        0x00414359: ("??$__uninitialized_copy@PAVScoredKillTracker@@PAV1@@_STL@@YAPAVScoredKillTracker@@PAV1@00"
                     "ABU__false_type@0@@Z"),
    },
    bindings=(
        (0x0055AC1F, 0x0F, "?rva0055A91A@ScoredKillTracker@@QAEXXZ"),
        (0x0055AC1F, 0x4D, "?hookToKeeper@ScoredKillTracker@@QAEXPAVRva0039BCF8@@@Z"),
        (0x004143A4, 0x1D, _skt(_SKT_STAND_IN[0x0055AC1F])),
        (0x00414760, 0x15, _skt(_SKT_PINS[0x00414403])),
        (0x00414760, 0x20, "??$_Destroy@PAVScoredKillTracker@@@_STL@@YAXPAVScoredKillTracker@@0@Z"),
        (0x004149B4, 0x06, _skt(_SKT_STAND_IN[0x00414760])),
        (0x004146E2, 0x1B, "??$_Destroy@PAVScoredKillTracker@@@_STL@@YAXPAVScoredKillTracker@@0@Z"),
        (0x0041484C, 0x3B, _skt(_SKT_PINS[0x004143D6])),
        (0x0041484C, 0x45, "?_M_clear@?$vector@VScoredKillTracker@@V?$allocator@VScoredKillTracker@@@_STL@@@_STL@@IAEXXZ"),
        (0x0041484C, 0x55, "?allocate@?$allocator@VScoredKillTracker@@@_STL@@QBEPAVScoredKillTracker@@IPBX@Z"),
    ),
    rows={
        # mov ebx,ecx; call rva0055A91A (ecx still this); ...; mov ecx,ebx; call hookToKeeper
        0x0055AC1F: (_SKT_STAND_IN[0x0055AC1F], (C("offset", 0x0055AC25, 0, "8bd9"), C("calls", 0x0055AC2D, 0x0055A91A),
                                                 C("offset", 0x0055AC69, 0, "8bcb"), C("calls", 0x0055AC6B, 0x0055A93C))),
        0x004143A4: (_SKT_STAND_IN[0x004143A4], (C("stride", 0x004143AD, 0x2C, "6a2c"), C("calls", 0x004143C0, 0x0055AC1F),
                                                 C("stride", 0x004143C5, 0x2C, "8345082c"))),
        0x00414760: (_SKT_STAND_IN[0x00414760], (C("calls", 0x00414774, 0x00414403), C("calls", 0x0041477F, 0x004144F0))),
        0x004149B4: (_SKT_STAND_IN[0x004149B4], (C("calls", 0x004149B9, 0x00414760),)),
        0x004146E2: (_SKT_STAND_IN[0x004146E2], (C("calls", 0x004146FC, 0x004144F0),)),
        0x0041484C: (_SKT_STAND_IN[0x0041484C], (C("stride", 0x00414860, 0x2C, "6a2c"), C("calls", 0x00414886, 0x004143D6),
                                                 C("calls", 0x00414890, 0x00414793), C("calls", 0x004148A0, 0x0007E364),
                                                 C("stride", 0x004148A5, 0x2C, "6bdb2c"))),
    },
    pins={
        # reserve's copy helper, whose body fills through the class's rowed __uninitialized_copy
        0x004143D6: (_SKT_PINS[0x004143D6], (C("calls", 0x00414886, 0x004143D6), C("calls", 0x004143F4, 0x00414359))),
        # erase's backward move, whose body calls the family's __copy
        0x00414403: (_SKT_PINS[0x00414403], (C("calls", 0x00414774, 0x00414403), C("calls", 0x00414416, 0x004143A4))),
    },
    duplicates={
        0x00414793: (_SKT_DUPLICATES[0x00414793], (C("calls", 0x0041479B, 0x004144F0),)),
        0x004144F0: (_SKT_DUPLICATES[0x004144F0], (C("calls", 0x004144FE, 0x0041445C),)),
    },
    retired={
        0x00414793: (_SKT_RETIRED[0x00414793], (C("calls", 0x00414890, 0x00414793),)),
        0x0007E364: (_SKT_RETIRED[0x0007E364], (C("calls", 0x004148A0, 0x0007E364),)),
    })
_UI_OLD = "Rva00534581Element"
_UI_TREE_OLD = ("?$_Rb_tree@URva00534581Element@@U?$pair@$$CBURva00534581Element@@H@_STL@@U?$_Select1st@U?$pair@$$CB"
                "URva00534581Element@@H@_STL@@@3@U?$less@URva00534581Element@@@3@V?$allocator@U?$pair@$$CB"
                "URva00534581Element@@H@_STL@@@3@@_STL@@")
_UI_TREE = ("?$_Rb_tree@IU?$pair@$$CBIH@_STL@@U?$_Select1st@U?$pair@$$CBIH@_STL@@@2@U?$less@I@2@V?$allocator@U?$pair@"
            "$$CBIH@_STL@@@2@@_STL@@")
_UI_PAIR_OLD, _UI_PAIR = "U?$pair@$$CBURva00534581Element@@H@_STL@@", "U?$pair@$$CBIH@_STL@@"
# the node type as a tree member spells it, where _STL is the back-reference 2
_UI_NODE_OLD, _UI_NODE = f"?$_Rb_tree_node@{_UI_PAIR_OLD}@2@", f"?$_Rb_tree_node@{_UI_PAIR}@2@"
_UI_SPELLINGS = {
    # rows
    f"??0{_UI_TREE_OLD}QAE@ABV01@@Z": f"??0{_UI_TREE}QAE@ABV01@@Z",
    ("??0?$map@URva00534581Element@@HU?$less@URva00534581Element@@@_STL@@V?$allocator@U?$pair@$$CBURva00534581Element"
     "@@H@_STL@@@3@@_STL@@QAE@ABV01@@Z"): "??0?$map@IHU?$less@I@_STL@@V?$allocator@U?$pair@$$CBIH@_STL@@@2@@_STL@@QAE@ABV01@@Z",
    f"??0Rva005344C0@@QAE@PBHABV{_UI_TREE_OLD}@Z": f"??0Rva005344C0@@QAE@PBHABV{_UI_TREE}@Z",
    # pins
    (f"?get_allocator@?$_Rb_tree_base@{_UI_PAIR_OLD}V?$allocator@{_UI_PAIR_OLD}@2@@_STL@@QBE?AV?$allocator@"
     f"{_UI_PAIR_OLD}@2@XZ"):
        f"?get_allocator@?$_Rb_tree_base@{_UI_PAIR}V?$allocator@{_UI_PAIR}@2@@_STL@@QBE?AV?$allocator@{_UI_PAIR}@2@XZ",
    f"??0?$_Rb_tree_base@{_UI_PAIR_OLD}V?$allocator@{_UI_PAIR_OLD}@2@@_STL@@QAE@ABV?$allocator@{_UI_PAIR_OLD}@1@@Z":
        f"??0?$_Rb_tree_base@{_UI_PAIR}V?$allocator@{_UI_PAIR}@2@@_STL@@QAE@ABV?$allocator@{_UI_PAIR}@1@@Z",
    f"?_M_copy@{_UI_TREE_OLD}AAEPAU{_UI_NODE_OLD}PAU32@0@Z": f"?_M_copy@{_UI_TREE}AAEPAU{_UI_NODE}PAU32@0@Z",
    ("??0?$_STLP_alloc_proxy@PAU?$_Rb_tree_node@U?$pair@$$CBURva00534581Element@@H@_STL@@@_STL@@U12@V?$allocator@U?$"
     "_Rb_tree_node@U?$pair@$$CBURva00534581Element@@H@_STL@@@_STL@@@2@@_STL@@QAE@ABV?$allocator@U?$_Rb_tree_node@U?$"
     "pair@$$CBURva00534581Element@@H@_STL@@@_STL@@@1@PAU?$_Rb_tree_node@U?$pair@$$CBURva00534581Element@@H@_STL@@@1@@Z"):
        ("??0?$_STLP_alloc_proxy@PAU?$_Rb_tree_node@U?$pair@$$CBIH@_STL@@@_STL@@U12@V?$allocator@U?$_Rb_tree_node@U?$"
         "pair@$$CBIH@_STL@@@_STL@@@2@@_STL@@QAE@ABV?$allocator@U?$_Rb_tree_node@U?$pair@$$CBIH@_STL@@@_STL@@@1@PAU?$"
         "_Rb_tree_node@U?$pair@$$CBIH@_STL@@@1@@Z"),
}
_UI_ROW_NAMES = {0x00534581: f"??0{_UI_TREE_OLD}QAE@ABV01@@Z",
                 0x0053462F: next(n for n in _UI_SPELLINGS if n.startswith("??0?$map@")),
                 0x005346BC: f"??0Rva005344C0@@QAE@PBHABV{_UI_TREE_OLD}@Z"}
_UI_PIN_NAMES = {0x0021983A: next(n for n in _UI_SPELLINGS if n.startswith("?get_allocator@")),
                 0x001F0534: next(n for n in _UI_SPELLINGS if n.startswith("??0?$_Rb_tree_base@")),
                 0x005344C8: next(n for n in _UI_SPELLINGS if n.startswith("?_M_copy@")),
                 0x0014F3C4: next(n for n in _UI_SPELLINGS if n.startswith("??0?$_STLP_alloc_proxy@"))}

# The pathfinder's map<unsigned int,int> copy (P139). Its copy chain was rowed on Rva00534581Element, a struct
# holding one short, so the link copied and compared the key at 16 bits. No class can prove a builtin, so retail's
# handling of the key does. _Construct, which the copy reaches through _M_copy, _M_clone_node and _M_create_node, moves
# the key as one dword. subscript, which builds its pair through the family's 0x005346BC and looks the key up through
# the map's rowed _M_lower_bound, compares it as an unsigned dword (jae). The members are PathDoXfer.cpp's rows of the
# same map.
MAP_UINT_INT_COPY = StandInScalarKeyFamily(
    old=_UI_OLD, new="unsigned int", code="I", copy=0x00534581, spellings=dict(_UI_SPELLINGS),
    members={
        0x00382B7F: f"?_M_create_node@{_UI_TREE}IAEPAU{_UI_NODE}ABU?$pair@$$CBIH@2@@Z",
        0x0060C9D9: "??$_Construct@U?$pair@$$CBIH@_STL@@U12@@_STL@@YAXPAU?$pair@$$CBIH@0@ABU10@@Z",
        0x004FF3B6: f"?_M_lower_bound@{_UI_TREE}ABEPAU{_UI_NODE}ABI@Z",
    },
    bindings=(
        (0x00534581, 0x1E, _UI_SPELLINGS[_UI_PIN_NAMES[0x0021983A]]),
        (0x00534581, 0x26, _UI_SPELLINGS[_UI_PIN_NAMES[0x001F0534]]),
        (0x00534581, 0x5C, _UI_SPELLINGS[_UI_PIN_NAMES[0x005344C8]]),
        (0x0053462F, 0x08, _UI_SPELLINGS[_UI_ROW_NAMES[0x00534581]]),
        (0x005346BC, 0x13, _UI_SPELLINGS[_UI_ROW_NAMES[0x00534581]]),
    ),
    rows={
        # the tree's copy: get_allocator, the base constructor, then _M_copy of the source's root
        0x00534581: (_UI_ROW_NAMES[0x00534581], (C("calls", 0x0053459E, 0x0021983A), C("calls", 0x005345A6, 0x001F0534),
                                                 C("calls", 0x005345DC, 0x005344C8))),
        # the map's copy and the pair's two-argument constructor copy the tree
        0x0053462F: (_UI_ROW_NAMES[0x0053462F], (C("calls", 0x00534636, 0x00534581),)),
        0x005346BC: (_UI_ROW_NAMES[0x005346BC], (C("calls", 0x005346CE, 0x00534581),)),
    },
    pins={
        0x0021983A: (_UI_PIN_NAMES[0x0021983A], (C("calls", 0x0053459E, 0x0021983A),)),
        0x001F0534: (_UI_PIN_NAMES[0x001F0534], (C("calls", 0x005345A6, 0x001F0534),)),
        0x005344C8: (_UI_PIN_NAMES[0x005344C8], (C("calls", 0x005345DC, 0x005344C8),)),
        # the base constructor's body builds its node allocator's proxy
        0x0014F3C4: (_UI_PIN_NAMES[0x0014F3C4], (C("calls", 0x001F053F, 0x0014F3C4),)),
    },
    copy_path=((0x00534581, C("calls", 0x005345DC, 0x005344C8)), (0x005344C8, C("calls", 0x005344D5, 0x0053444F)),
               (0x0053444F, C("calls", 0x00534458, 0x00382B7F)), (0x00382B7F, C("calls", 0x00382B93, 0x0060C9D9))),
    # mov edx,[ecx]; mov [eax],edx: the key, one dword
    key_copy=(0x0060C9D9, C("copy", 0x0060C9E5, 4, "8b118910")),
    # cmp eax,[esi+10h]; jae: the key against the node's, unsigned
    key_compare=(0x00534A2A, C("compare", 0x00534A4D, 0x10, "3b46107348")),
    compare_path=((0x00534A2A, C("calls", 0x00534A40, 0x004FF3B6)), (0x00534A2A, C("calls", 0x00534A63, 0x005346BC))))
_UR_INSERT = ("?insert@?$map@IPAXU?$less@I@_STL@@V?$allocator@U?$pair@$$CBIPAX@_STL@@@2@@_STL@@QAE?AU?$_Rb_tree_iterator@"
              "U?$pair@$$CBIPAX@_STL@@U?$_Nonconst_traits@U?$pair@$$CBIPAX@_STL@@@2@@2@U32@ABU?$pair@$$CBIPAX@2@@Z")
_UR_UNIQUE_HINT = ("?insert_unique@?$_Rb_tree@IU?$pair@$$CBIPAX@_STL@@U?$_Select1st@U?$pair@$$CBIPAX@_STL@@@2@U?$less@I@2@"
                   "V?$allocator@U?$pair@$$CBIPAX@_STL@@@2@@_STL@@QAE?AU?$_Rb_tree_iterator@U?$pair@$$CBIPAX@_STL@@"
                   "U?$_Nonconst_traits@U?$pair@$$CBIPAX@_STL@@@2@@2@U32@ABU?$pair@$$CBIPAX@2@@Z")
_UR_UNIQUE = ("?insert_unique@?$_Rb_tree@IU?$pair@$$CBIPAX@_STL@@U?$_Select1st@U?$pair@$$CBIPAX@_STL@@@2@U?$less@I@2@"
              "V?$allocator@U?$pair@$$CBIPAX@_STL@@@2@@_STL@@QAE?AU?$pair@U?$_Rb_tree_iterator@U?$pair@$$CBIPAX@_STL@@"
              "U?$_Nonconst_traits@U?$pair@$$CBIPAX@_STL@@@2@@_STL@@_N@2@ABU?$pair@$$CBIPAX@2@@Z")
_UR_M_INSERT_PAX = ("?_M_insert@?$_Rb_tree@IU?$pair@$$CBIPAX@_STL@@U?$_Select1st@U?$pair@$$CBIPAX@_STL@@@2@U?$less@I@2@"
                    "V?$allocator@U?$pair@$$CBIPAX@_STL@@@2@@_STL@@AAE?AU?$_Rb_tree_iterator@U?$pair@$$CBIPAX@_STL@@"
                    "U?$_Nonconst_traits@U?$pair@$$CBIPAX@_STL@@@2@@2@PAU_Rb_tree_node_base@2@0ABU?$pair@$$CBIPAX@2@0@Z")
_UR_SPELLINGS = {
    # map<unsigned int, .>::insert(iterator, const value_type &), 0x00534A0D
    _UR_INSERT:
        "?insert@?$map@IURva00534743Record@@U?$less@I@_STL@@V?$allocator@U?$pair@$$CBIURva00534743Record@@@_STL@@@3@@"
        "_STL@@QAE?AU?$_Rb_tree_iterator@U?$pair@$$CBIURva00534743Record@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBI"
        "URva00534743Record@@@_STL@@@2@@2@U32@ABU?$pair@$$CBIURva00534743Record@@@2@@Z",
    # _Rb_tree::insert_unique(iterator, const value_type &), 0x005348E7
    _UR_UNIQUE_HINT:
        "?insert_unique@?$_Rb_tree@IU?$pair@$$CBIURva00534743Record@@@_STL@@U?$_Select1st@U?$pair@$$CBIURva00534743"
        "Record@@@_STL@@@2@U?$less@I@2@V?$allocator@U?$pair@$$CBIURva00534743Record@@@_STL@@@2@@_STL@@QAE?AU?$_Rb_"
        "tree_iterator@U?$pair@$$CBIURva00534743Record@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBIURva00534743Record@@"
        "@_STL@@@2@@2@U32@ABU?$pair@$$CBIURva00534743Record@@@2@@Z",
    # _Rb_tree::insert_unique(const value_type &), 0x00534827
    _UR_UNIQUE:
        "?insert_unique@?$_Rb_tree@IU?$pair@$$CBIURva00534743Record@@@_STL@@U?$_Select1st@U?$pair@$$CBIURva00534743"
        "Record@@@_STL@@@2@U?$less@I@2@V?$allocator@U?$pair@$$CBIURva00534743Record@@@_STL@@@2@@_STL@@QAE?AU?$pair@"
        "U?$_Rb_tree_iterator@U?$pair@$$CBIURva00534743Record@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBIURva00534743"
        "Record@@@_STL@@@2@@_STL@@_N@2@ABU?$pair@$$CBIURva00534743Record@@@2@@Z",
    # _Rb_tree::_M_insert, the pin on 0x0053479F: the member's own name there
    _UR_M_INSERT_PAX:
        "?_M_insert@?$_Rb_tree@IU?$pair@$$CBIURva00534743Record@@@_STL@@U?$_Select1st@U?$pair@$$CBIURva00534743Record"
        "@@@_STL@@@2@U?$less@I@2@V?$allocator@U?$pair@$$CBIURva00534743Record@@@_STL@@@2@@_STL@@AAE?AU?$_Rb_tree_"
        "iterator@U?$pair@$$CBIURva00534743Record@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBIURva00534743Record@@@_STL"
        "@@@2@@2@PAU_Rb_tree_node_base@2@0ABU?$pair@$$CBIURva00534743Record@@@2@0@Z",
}
_UR_CREATE_NODE = ("?_M_create_node@?$_Rb_tree@IU?$pair@$$CBIURva00534743Record@@@_STL@@U?$_Select1st@U?$pair@$$CBIURva"
                   "00534743Record@@@_STL@@@2@U?$less@I@2@V?$allocator@U?$pair@$$CBIURva00534743Record@@@_STL@@@2@@_STL@@"
                   "IAEPAU?$_Rb_tree_node@U?$pair@$$CBIURva00534743Record@@@_STL@@@2@ABU?$pair@$$CBIURva00534743Record"
                   "@@@2@@Z")

# The pathfinder's outer map under Rva00534A2A::subscript (P143). Its insert chain (the hint insert 0x00534A0D and the
# two insert_unique 0x005348E7 and 0x00534827) was rowed on void*, so the link took another unit's void* _M_insert,
# whose _M_create_node makes 0x18-byte nodes; retail's _M_insert 0x0053479F calls _M_create_node 0x00534743, which
# allocates 0x20: the 16-byte header and pair<const unsigned int, Rva00534743Record> (the 12-byte inner map). Both are
# already rowed on Rva00534743Record in StlSweepR3Rva00534743.cpp. A pin spelled _M_insert's void* name onto
# 0x0053479F; it goes. subscript calls the hint insert.
MAP_UINT_RECORD_INSERT = StandInValueFamily(
    old="PAX", new="Rva00534743Record", key="I", value_size=12, copy=0x00534A0D, spellings=dict(_UR_SPELLINGS),
    members={
        0x0053479F: _UR_SPELLINGS[_UR_M_INSERT_PAX],
        0x00534743: _UR_CREATE_NODE,
    },
    bindings=(
        (0x00534A0D, 0x12, _UR_SPELLINGS[_UR_UNIQUE_HINT]),
        (0x005348E7, 0x6B, _UR_SPELLINGS[_UR_M_INSERT_PAX]),
        (0x005348E7, 0x114, _UR_SPELLINGS[_UR_UNIQUE]),
        (0x00534827, 0x63, _UR_SPELLINGS[_UR_M_INSERT_PAX]),
    ),
    rows={
        # the hint insert forwards to the tree's hint insert_unique
        0x00534A0D: (_UR_INSERT, (C("calls", 0x00534A1E, 0x005348E7),)),
        # which inserts at the hint through _M_insert, or falls back to the plain insert_unique
        0x005348E7: (_UR_UNIQUE_HINT, (C("calls", 0x00534951, 0x0053479F), C("calls", 0x005349FA, 0x00534827))),
        0x00534827: (_UR_UNIQUE, (C("calls", 0x00534889, 0x0053479F),)),
    },
    retired={0x0053479F: (_UR_M_INSERT_PAX, (C("calls", 0x00534951, 0x0053479F),))},
    # push 20h: the node's byte count, taken by the allocation at once
    node=(0x00534743, C("alloc", 0x00534746, 0x20, "6a20")),
    node_call=C("calls", 0x00534748, 0x000307F0),
    # _M_insert creates the node through the creator
    member_path=((0x0053479F, C("calls", 0x005347C7, 0x00534743)),),
    callers={0x00534A2A: ("?subscript@Rva00534A2A@@QAEAAUTreeStorage534@@ABI@Z", (C("calls", 0x00534A7B, 0x00534A0D),))},
    caller_bindings=((0x00534A2A, 0x52, _UR_SPELLINGS[_UR_INSERT]),))
_BM_OLD_PAIR = "U?$pair@$$CBIPAX@_STL@@"
_BM_OLD_TREE = (f"?$_Rb_tree@I{_BM_OLD_PAIR}U?$_Select1st@{_BM_OLD_PAIR}@2@U?$less@I@2@V?$allocator@{_BM_OLD_PAIR}@2@@"
                "_STL@@")
_BM_PAIR = "U?$pair@QBDUBigArchiveMemberInfo@@@_STL@@"
_BM_TREE = f"?$_Rb_tree@PBD{_BM_PAIR}U?$_Select1st@{_BM_PAIR}@2@URva006038D4Less@@V?$allocator@{_BM_PAIR}@2@@_STL@@"
_BM_COPY = f"??0{_BM_OLD_TREE}QAE@ABV01@@Z"
_BM_M_COPY = f"?_M_copy@{_BM_OLD_TREE}AAEPAU?$_Rb_tree_node@{_BM_OLD_PAIR}@2@PAU32@0@Z"
_BM_MAP_COPY = f"??0?$map@IPAXU?$less@I@_STL@@V?$allocator@{_BM_OLD_PAIR}@2@@_STL@@QAE@ABV01@@Z"
_BM_PAIR_CTOR = f"??0Rva00603FD2@@QAE@PBIABV{_BM_OLD_TREE}@Z"
_BM_MAKE = f"?Rva00604251@@YA?AVRva00603FD2@@ABIABV{_BM_OLD_TREE}@Z"
_BM_SPELLINGS = {
    # the tree's copy constructor, 0x00603EEB
    _BM_COPY: f"??0{_BM_TREE}QAE@ABV01@@Z",
    # its _M_copy, 0x00603B9C
    _BM_M_COPY: f"?_M_copy@{_BM_TREE}AAEPAU?$_Rb_tree_node@{_BM_PAIR}@2@PAU32@0@Z",
    # the map's copy constructor, 0x00603FC0
    _BM_MAP_COPY: (f"??0?$map@PBDUBigArchiveMemberInfo@@URva006038D4Less@@V?$allocator@{_BM_PAIR}@_STL@@@_STL@@QAE@ABV01"
                   "@@Z"),
    # the folder value's constructor from a name pointer and a member tree, 0x00603FD2
    _BM_PAIR_CTOR: f"??0Rva00603FD2@@QAE@PBQBDABV{_BM_TREE}@Z",
    # the folder value's factory, 0x00604251
    _BM_MAKE: f"?Rva00604251@@YA?AVRva00603FD2@@ABQBDABV{_BM_TREE}@Z",
}
_BM_CLONE = ("?_M_clone_node@?$_Rb_tree@W4NameKeyType@@U?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@U"
             "?$_Select1st@U?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@@3@U?$less@W4NameKeyType@@@3"
             "@V?$allocator@U?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@@3@@_STL@@IAEPAU?$_Rb_tree_"
             "node@U?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@@2@PAU32@@Z")
# the pin at 0x00604251, as reverse/symbols.csv holds it
_BM_MAKE_PAIR_PIN = (
    "??$make_pair@PBDV?$map@PBDUBigArchiveMemberInfo@@URva006038D4Less@@V?$allocator@U?$pair@QBDUBigArchiveMemberInfo@"
    "@@_STL@@@_STL@@@_STL@@@_STL@@YA?AU?$pair@PBDV?$map@PBDUBigArchiveMemberInfo@@URva006038D4Less@@V?$allocator@U?$pai"
    "r@QBDUBigArchiveMemberInfo@@@_STL@@@_STL@@@_STL@@@0@ABQBDABV?$map@PBDUBigArchiveMemberInfo@@URva006038D4Less@@V?$"
    "allocator@U?$pair@QBDUBigArchiveMemberInfo@@@_STL@@@_STL@@@0@@Z")

# A BIG archive folder's member map, map<const char *, BigArchiveMemberInfo, Rva006038D4Less> (P144). Its copy chain
# was rowed on map<unsigned int, void *>, so the copy bound the pointer-pair base constructor, whose one definer
# allocated 0x18-byte headers. Retail's base constructor 0x0030087C and node creator 0x0029E11A push 0x20: the 16-byte
# header and pair<const char *const, 12-byte BigArchiveMemberInfo>. Win32BIGFileSystem::rva006045A2, built from these
# types, inserts make_pair(folder, BigMemberMap()) and binds the make_pair pin at 0x00604251, which spells the
# comparator Rva006038D4Less. Rva0060426C (the folder value's copy) calls the tree's copy.
BIG_MEMBER_MAP_COPY = RetypedTreeFamily(
    old_key="I", old_value="PAX", new_key="PBD", new_value="BigArchiveMemberInfo", new_compare="Rva006038D4Less",
    value_size=12, copy=0x00603EEB, spellings=dict(_BM_SPELLINGS),
    members={0x00413E55: _BM_CLONE},
    bindings=(
        (0x00603EEB, 0x5C, _BM_SPELLINGS[_BM_M_COPY]),
        (0x00603B9C, 0x0E, _BM_CLONE),
        (0x00603B9C, 0x3E, _BM_CLONE),
        (0x00603FC0, 0x08, _BM_SPELLINGS[_BM_COPY]),
        (0x00603FD2, 0x13, _BM_SPELLINGS[_BM_COPY]),
        (0x00604251, 0x12, _BM_SPELLINGS[_BM_PAIR_CTOR]),
    ),
    rows={
        # the copy builds its header through the base constructor, then copies the nodes
        0x00603EEB: (_BM_COPY, (C("calls", 0x00603F10, 0x0030087C), C("calls", 0x00603F46, 0x00603B9C))),
        # which clones each node through the 32-byte node clone
        0x00603B9C: (_BM_M_COPY, (C("calls", 0x00603BA9, 0x00413E55), C("calls", 0x00603BD9, 0x00413E55))),
        0x00603FC0: (_BM_MAP_COPY, (C("calls", 0x00603FC7, 0x00603EEB),)),
        0x00603FD2: (_BM_PAIR_CTOR, (C("calls", 0x00603FE4, 0x00603EEB),)),
        0x00604251: (_BM_MAKE, (C("calls", 0x00604262, 0x00603FD2),)),
    },
    # push 20h, then the allocation: the base constructor's header and the creator's node
    nodes=((0x0030087C, C("alloc", 0x0030088E, 0x20, "6a20"), C("calls", 0x00300890, 0x000307F0)),
           (0x0029E11A, C("alloc", 0x0029E11D, 0x20, "6a20"), C("calls", 0x0029E11F, 0x000307F0))),
    # the clone creates its node through the creator
    node_path=((0x00413E55, C("calls", 0x00413E5E, 0x0029E11A)),),
    witness=(0x006045A2, "?rva006045A2@Win32BIGFileSystem@@QAE_NPBD0PAUBigArchiveMemberInfo@@_N@Z",
             C("calls", 0x006045FE, 0x00604251), _BM_MAKE_PAIR_PIN),
    callers={0x0060426C: ("??0Rva0060426C@@QAE@ABV0@@Z", (C("calls", 0x0060427E, 0x00603EEB),))},
    caller_bindings=((0x0060426C, 0x13, _BM_SPELLINGS[_BM_COPY]),))
FAMILIES = (ENABLE_REGION_RECORD, HERO_RECORD_SET, LOCOMOTOR, RENDERER_VECTOR, SCORED_KILL_TRACKER_VECTOR,
            MAP_UINT_INT_COPY, MAP_UINT_RECORD_INSERT,
            BIG_MEMBER_MAP_COPY)

# One body at the same slot of many retail tables, proved one class's virtual: what `rename.py function --to-class` may
# treat as related although no view says so. `tables` holds only the tables the view test refuses, each stated at
# exact addresses for a reader to check by hand: word 0 holds the shared body, word 1 the table's deleting destructor,
# then each direct step in order, ending at the store of the class's vptr. Nothing here generalizes from these
# shapes, and a table not listed stays a fold. Another class is another reviewed entry (Verifier-Change).
# A store of the vptr shows an install at that address, which is why this is a reviewed list and not a rule.
SharedSlot = collections.namedtuple("SharedSlot", "rva cls new table slot vptr own tables notes")


def word(table, index, target_rva):
    """The fact that the dword `index` words into the table at VA `table` holds the body at `target_rva`. It says
    nothing of the table's length: some of these tables abut the next, which a slot fact's count refuses."""
    return Fact("word", table - IMAGE_BASE + 4 * index, target_rva + IMAGE_BASE)


REFCOUNT_DELETE_THIS = SharedSlot(
    rva=0x0006CE57, cls="RefCountClass", new="?Delete_This@RefCountClass@@UAEXXZ", table=0x00BC650C, slot=0, vptr=0x00BC650C,
    # RefCountClass's own table, its constructor and its destructor
    own=(word(0x00BC650C, 0, 0x0006CE57), word(0x00BC650C, 1, 0x00072899),
         C("stores", 0x00072884, 0x00BC650C, "c700"), C("stores", 0x00072892, 0x00BC650C, "c701")),
    tables={
    # Rva006DD51/W3DDynamicLight: slot 1 ??_GRva006DD51@@UAEPAXI@Z
    0x00BC6038: (word(0x00BC6038, 0, 0x0006CE57),
                 word(0x00BC6038, 1, 0x0006DE21),
                 C("calls", 0x0006DE24, 0x0006DD51),
                 C("jumps", 0x0006DD5E, 0x00130E80),
                 C("jumps", 0x00130E8D, 0x0013BE20),
                 C("stores", 0x0013BE5D, 0x00BC650C, "c706")),
    # W3DShroudMaterialPassClass: slot 1 ??_GW3DShroudMaterialPassClass@@UAEPAXI@Z
    0x00BC6244: (word(0x00BC6244, 0, 0x0006CE57),
                 word(0x00BC6244, 1, 0x0006F1DD),
                 C("calls", 0x0006F1E0, 0x0006F1F9),
                 C("jumps", 0x0006F1F9, 0x0013EE40),
                 C("stores", 0x0013EE9E, 0x00BC650C, "c706")),
    # RenderingMethodDelegate: slot 1 ??_GRva0072AED@@UAEPAXI@Z
    0x00BC6540: (word(0x00BC6540, 0, 0x0006CE57),
                 word(0x00BC6540, 1, 0x00072FA9),
                 C("calls", 0x00072FAC, 0x00072AED),
                 C("stores", 0x00072B15, 0x00BC650C, "c706")),
    # Rva00072FE1/W3DShroud: slot 1 ??_GRva00072FE1@@UAEPAXI@Z
    0x00BC6568: (word(0x00BC6568, 0, 0x0006CE57),
                 word(0x00BC6568, 1, 0x00072FC5),
                 C("calls", 0x00072FC8, 0x00072FE1),
                 C("jumps", 0x00072FE1, 0x00072AED),
                 C("stores", 0x00072B15, 0x00BC650C, "c706")),
    # Rva0007DC01ShadowMethod: slot 1 ??_GRva00072FE1@@UAEPAXI@Z
    0x00BC6C24: (word(0x00BC6C24, 0, 0x0006CE57),
                 word(0x00BC6C24, 1, 0x00072FC5),
                 C("calls", 0x00072FC8, 0x00072FE1),
                 C("jumps", 0x00072FE1, 0x00072AED),
                 C("stores", 0x00072B15, 0x00BC650C, "c706")),
    # no class the ledger names: slot 1 ??_G?$ShareBufferClass@VVector2@@@@UAEPAXI@Z
    0x00BCE328: (word(0x00BCE328, 0, 0x0006CE57),
                 word(0x00BCE328, 1, 0x000D1E50),
                 C("calls", 0x000D1E53, 0x000D1DC8),
                 C("stores", 0x000D1DDA, 0x00BC650C, "c706")),
    # UVBufferClass: slot 1 ??_GUVBufferClass@@UAEPAXI@Z
    0x00BCE338: (word(0x00BCE338, 0, 0x0006CE57),
                 word(0x00BCE338, 1, 0x000D20FC),
                 C("calls", 0x000D20FF, 0x000D2118),
                 C("jumps", 0x000D2118, 0x000D1DC8),
                 C("stores", 0x000D1DDA, 0x00BC650C, "c706")),
    # BfmeDynamicNativeVB/BfmeDynamicSortingVB/BfmeDynamicVBBase: slot 1 ??_GBfmeDynamicVBBase@@UAEPAXI@Z
    0x00BD2F40: (word(0x00BD2F40, 0, 0x0006CE57),
                 word(0x00BD2F40, 1, 0x0013ABC0),
                 C("calls", 0x0013ABC3, 0x00139410),
                 C("stores", 0x00139442, 0x00BC650C, "c706")),
    # BfmeDynamicSortingVB: slot 1 ??_GBfmeDynamicSortingVB@@UAEPAXI@Z
    0x00BD2F48: (word(0x00BD2F48, 0, 0x0006CE57),
                 word(0x00BD2F48, 1, 0x0013ABE0),
                 C("calls", 0x0013ABE3, 0x001396D0),
                 C("stores", 0x00139711, 0x00BC650C, "c706")),
    # BfmeDynamicNativeVB: slot 1 ??_GBfmeDynamicNativeVB@@UAEPAXI@Z
    0x00BD2F50: (word(0x00BD2F50, 0, 0x0006CE57),
                 word(0x00BD2F50, 1, 0x0013AC70),
                 C("calls", 0x0013AC73, 0x00139720),
                 C("stores", 0x0013979D, 0x00BC650C, "c706")),
    # no class the ledger names: slot 1 ??_G?$ShareBufferClass@VShaderClass@@@@UAEPAXI@Z
    0x00BD3CEC: (word(0x00BD3CEC, 0, 0x0006CE57),
                 word(0x00BD3CEC, 1, 0x0015CEF0),
                 C("calls", 0x0015CEF3, 0x0015CF10),
                 C("stores", 0x0015CF25, 0x00BC650C, "c706")),
    # no class the ledger names: slot 1 ??_G?$ShareBufferClass@VVector3i16@@@@UAEPAXI@Z
    0x00BD43E8: (word(0x00BD43E8, 0, 0x0006CE57),
                 word(0x00BD43E8, 1, 0x00169CC0),
                 C("calls", 0x00169CC3, 0x00169CE0),
                 C("stores", 0x00169CF5, 0x00BC650C, "c706")),
    # no class the ledger names: slot 1 ??_G?$ShareBufferClass@K@@UAEPAXI@Z
    0x00BD4400: (word(0x00BD4400, 0, 0x0006CE57),
                 word(0x00BD4400, 1, 0x00169D80),
                 C("calls", 0x00169D83, 0x00169DA0),
                 C("stores", 0x00169DB5, 0x00BC650C, "c706")),
    # no class the ledger names: slot 1 ??_G?$ShareBufferClass@G@@UAEPAXI@Z
    0x00BD4408: (word(0x00BD4408, 0, 0x0006CE57),
                 word(0x00BD4408, 1, 0x00169DC0),
                 C("calls", 0x00169DC3, 0x00169DE0),
                 C("stores", 0x00169DF5, 0x00BC650C, "c706")),
    # no class the ledger names: slot 1 ??_G?$ShareBufferClass@D@@UAEPAXI@Z
    0x00BD4410: (word(0x00BD4410, 0, 0x0006CE57),
                 word(0x00BD4410, 1, 0x00169E00),
                 C("calls", 0x00169E03, 0x00169E20),
                 C("stores", 0x00169E35, 0x00BC650C, "c706")),
    # no class the ledger names: slot 1 ??_G?$ShareBufferClass@VVector4@@@@UAEPAXI@Z
    0x00BD4420: (word(0x00BD4420, 0, 0x0006CE57),
                 word(0x00BD4420, 1, 0x00169E80),
                 C("calls", 0x00169E83, 0x00169EA0),
                 C("stores", 0x00169EB5, 0x00BC650C, "c706")),
    # BoxRenderObjClass: slot 1 ??_GOBBoxRenderObjClass@@UAEPAXI@Z
    0x00BD4740: (word(0x00BD4740, 0, 0x0006CE57),
                 word(0x00BD4740, 1, 0x001811B0),
                 C("calls", 0x001811B3, 0x001811D0),
                 C("jumps", 0x001811D0, 0x0013BE20),
                 C("stores", 0x0013BE5D, 0x00BC650C, "c706")),
    # AABoxRenderObjClass: slot 1 ??_GOBBoxRenderObjClass@@UAEPAXI@Z
    0x00BD4950: (word(0x00BD4950, 0, 0x0006CE57),
                 word(0x00BD4950, 1, 0x001811B0),
                 C("calls", 0x001811B3, 0x001811D0),
                 C("jumps", 0x001811D0, 0x0013BE20),
                 C("stores", 0x0013BE5D, 0x00BC650C, "c706")),
    # OBBoxRenderObjClass: slot 1 ??_GOBBoxRenderObjClass@@UAEPAXI@Z
    0x00BD4B60: (word(0x00BD4B60, 0, 0x0006CE57),
                 word(0x00BD4B60, 1, 0x001811B0),
                 C("calls", 0x001811B3, 0x001811D0),
                 C("jumps", 0x001811D0, 0x0013BE20),
                 C("stores", 0x0013BE5D, 0x00BC650C, "c706")),
    # Null3DObjClass: slot 1 ??_GOBBoxRenderObjClass@@UAEPAXI@Z
    0x00BD50D0: (word(0x00BD50D0, 0, 0x0006CE57),
                 word(0x00BD50D0, 1, 0x001811B0),
                 C("calls", 0x001811B3, 0x001811D0),
                 C("jumps", 0x001811D0, 0x0013BE20),
                 C("stores", 0x0013BE5D, 0x00BC650C, "c706")),
    # AABTreeClass: slot 1 ?rva00198170@BfmeThingVJS@@QAEPAXI@Z
    0x00BD5F00: (word(0x00BD5F00, 0, 0x0006CE57),
                 word(0x00BD5F00, 1, 0x00198170),
                 C("calls", 0x00198173, 0x00197F30),
                 C("stores", 0x00197F6B, 0x00BC650C, "c706")),
    # HLodClass: slot 1 ??_GHLodClass@@UAEPAXI@Z
    0x00BD6780: (word(0x00BD6780, 0, 0x0006CE57),
                 word(0x00BD6780, 1, 0x0019F990),
                 C("calls", 0x0019F993, 0x0019EF70),
                 C("calls", 0x0019EFF2, 0x001A54F0),
                 C("calls", 0x001A554C, 0x001A5DD0),
                 C("calls", 0x001A5E27, 0x0013BE20),
                 C("stores", 0x0013BE5D, 0x00BC650C, "c706")),
    # CompositeRenderObjClass: slot 1 ??_GCompositeRenderObjClass@@UAEPAXI@Z
    0x00BD6F30: (word(0x00BD6F30, 0, 0x0006CE57),
                 word(0x00BD6F30, 1, 0x001A6150),
                 C("calls", 0x001A6153, 0x001A5DD0),
                 C("calls", 0x001A5E27, 0x0013BE20),
                 C("stores", 0x0013BE5D, 0x00BC650C, "c706")),
    # CullableClass: slot 1 ??_GScreenMapperClass@@UAEPAXI@Z
    0x00CEFD58: (word(0x00CEFD58, 0, 0x0006CE57),
                 word(0x00CEFD58, 1, 0x00184150),
                 C("calls", 0x00184153, 0x00724510),
                 C("stores", 0x00724510, 0x00BC650C, "c701")),
    },
    notes={
        # ??0W3DShroud's rows also store this table, but on the object it allocates (a call to the global operator new at 0x00073391), so the header
        # that gives W3DShroud no base is not contradicted: the table is the allocated object's own.
        0x00BC6568: (C("calls", 0x00073391, 0x0002FDA0), C("stores", 0x000733A5, 0x00BC6568, "c700")),
    })
SHARED_SLOTS = (REFCOUNT_DELETE_THIS,)


def shared_slot_of(rva, cls, new):
    """The reviewed entry for moving the body at `rva` into `cls` as `new`, or None."""
    for entry in SHARED_SLOTS:
        if (entry.rva, entry.cls, entry.new) == (rva, cls, new):
            return entry
    return None


def shared_slot_facts(entry):
    """Every fact of `entry`, in order."""
    return [*entry.own, *[f for facts in entry.tables.values() for f in facts], *[f for facts in entry.notes.values() for f in facts]]


def shared_slot_problems(entry):
    """Why `entry` does not hold, one line each: each listed table must state the shared body at its slot and end at a
    store of the vptr, and retail must hold every fact (facts_problems: an unreadable site is a problem)."""
    out = []
    for table, facts in entry.tables.items():
        if not facts or facts[0] != word(table, entry.slot, entry.rva):
            out.append(f"table 0x{table:08X} does not open with word {entry.slot} holding 0x{entry.rva:08X}")
        last = facts[-1] if facts else None
        if not last or last.kind != "stores" or last.value != entry.vptr or last.code not in VPTR_STORES:
            out.append(f"table 0x{table:08X} does not end at a store of the vptr 0x{entry.vptr:08X}")
    return out + facts_problems(shared_slot_facts(entry))

# A slot of a class with no retail table of its own: one body at the same slot of many retail tables, which
# `rename.py function --to-class` may move into `cls` as `new`. `tables` {table VA: (class, facts)} holds only the
# tables the view test refuses, each stated at exact addresses for a reader to check by hand: word `slot` holds the
# body, the table's installer stores it, then each step to a registration in order (a call to the installer when the
# factory does not install it itself, the push of the factory's address, the call to `register`). `dead` {table VA:
# (installer rva, facts)} holds tables whose installer nothing in the image reaches: dead_table_problems reads the
# whole image for any rel32 call or jump to the installer, any word equal to its VA, and any word equal to the table's
# VA other than the installer's own store. A table in neither stays a fold. Another class is another entry
# (Verifier-Change).
BaseSlot = collections.namedtuple("BaseSlot", "rva cls new slot register tables dead")

# ModuleData declares slot 14 (ModuleData.h `slot14(int) const`), but retail has no ModuleData table: its destructor
# row 0x0049B47C stores the 4-slot Snapshot table 0x00BBB554, which every table here also ends at. 0x000B69A1 is
# slot 14 of 107 tables the view test refuses, each built by a data factory ModuleFactory registers (the push of the
# factory's address before a call to 0x002573EE, which all 309 registrations in module_factory_registrations.csv
# make). That proves the tables module data in ModuleFactory's terms; it does not prove the body ModuleData's own.
MODULE_DATA_SLOT14 = BaseSlot(
    rva=0x000B69A1, cls="ModuleData", new="?slot14@ModuleData@@UBE?AVAsciiString@@H@Z", slot=14, register=0x002573EE,
    tables={
    # W3DBuffDrawModuleData: built by ?friend_newModuleData@W3DBuffDrawModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00BCD270: ("W3DBuffDrawModuleData", (word(0x00BCD270, 14, 0x000B69A1), C("stores", 0x000CEE4E, 0x00BCD270, "c700"),
        C("calls", 0x00064CB5, 0x000CEE4C),
        C("stores", 0x0006562F, 0x00464C94, "68"),
        C("calls", 0x00065642, 0x002573EE))),
    # W3DStreakDrawModuleData: built by ?friend_newModuleData@W3DStreakDrawModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00BCDAB0: ("W3DStreakDrawModuleData", (word(0x00BCDAB0, 14, 0x000B69A1), C("stores", 0x000D053D, 0x00BCDAB0, "c706"),
        C("calls", 0x00064F68, 0x000D0520),
        C("stores", 0x00065668, 0x00464F47, "68"),
        C("calls", 0x0006567B, 0x002573EE))),
    # W3DBoatWakeModelDrawModuleData: built by ?friend_newModuleData@W3DBoatWakeModelDrawModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00BCDE68: ("W3DBoatWakeModelDrawModuleData", (word(0x00BCDE68, 14, 0x000B69A1), C("stores", 0x000D0CDD, 0x00BCDE68, "c700"),
        C("calls", 0x00065080, 0x000D0CD8),
        C("stores", 0x000656DA, 0x0046505F, "68"),
        C("calls", 0x000656ED, 0x002573EE))),
    # W3DProjectileStreamDrawModuleData: built by ?friend_newModuleData@W3DProjectileStreamDrawModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00BCDF18: ("W3DProjectileStreamDrawModuleData", (word(0x00BCDF18, 14, 0x000B69A1), C("stores", 0x000D11EA, 0x00BCDF18, "c706"),
        C("calls", 0x00065109, 0x000D11D2),
        C("stores", 0x0006571A, 0x004650E8, "68"),
        C("calls", 0x00065726, 0x002573EE))),
    # W3DTornadoDrawModuleData: built by ?friend_newModuleData@W3DTornadoDrawModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00BCE198: ("W3DTornadoDrawModuleData", (word(0x00BCE198, 14, 0x000B69A1), C("stores", 0x000D16CC, 0x00BCE198, "c706"),
        C("calls", 0x00065192, 0x000D16B4),
        C("stores", 0x0006574C, 0x00465171, "68"),
        C("calls", 0x0006575F, 0x002573EE))),
    # PillageModuleData: built by ?friend_newModuleData@PillageModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00BF0568: ("PillageModuleData", (word(0x00BF0568, 14, 0x000B69A1), C("stores", 0x00253849, 0x00BF0568, "c706"),
        C("calls", 0x002538AB, 0x00253830),
        C("stores", 0x0025ADC9, 0x0065388A, "68"),
        C("calls", 0x0025ADDC, 0x002573EE))),
    # RefundDieModuleData: built by ?friend_newModuleData@RefundDieModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00BF0660: ("RefundDieModuleData", (word(0x00BF0660, 14, 0x000B69A1), C("stores", 0x002538F8, 0x00BF0660, "c706"),
        C("calls", 0x00253961, 0x002538DB),
        C("stores", 0x00258C13, 0x00653940, "68"),
        C("calls", 0x00258C26, 0x002573EE))),
    # CrushDieModuleData: built by ?friend_newModuleData@CrushDieModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00BF0760: ("CrushDieModuleData", (word(0x00BF0760, 14, 0x000B69A1), C("stores", 0x002539E0, 0x00BF0760, "c706"),
        C("calls", 0x00253A48, 0x002539B3),
        C("stores", 0x00258B6B, 0x00653A27, "68"),
        C("calls", 0x00258B7E, 0x002573EE))),
    # SpecialEnemySenseUpdateModuleData: built by ?friend_newModuleData@SpecialEnemySenseUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00BF1AD8: ("SpecialEnemySenseUpdateModuleData", (word(0x00BF1AD8, 14, 0x000B69A1), C("stores", 0x00254062, 0x00BF1AD8, "c706"),
        C("calls", 0x002540BD, 0x0025404A),
        C("stores", 0x0025918E, 0x0065409C, "68"),
        C("calls", 0x002591A1, 0x002573EE))),
    # QueueProductionExitUpdateModuleData: built by ?friend_newModuleData@QueueProductionExitUpdate@@SAPAVModuleData@@PAVINI@@@Z
    0x00BF1D58: ("QueueProductionExitUpdateModuleData", (word(0x00BF1D58, 14, 0x000B69A1), C("stores", 0x002541FF, 0x00BF1D58, "c700"),
        C("calls", 0x0025425E, 0x002541FA),
        C("stores", 0x00259839, 0x0065424F, "68"),
        C("calls", 0x0025984C, 0x002573EE))),
    # StatusBitsUpgradeIfEldestKindofModuleData: built by ?friend_newModuleData@StatusBitsUpgradeIfEldestKindofModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00BF25D8: ("StatusBitsUpgradeIfEldestKindofModuleData", (word(0x00BF25D8, 14, 0x000B69A1), C("stores", 0x002547F9, 0x00BF25D8, "c706"),
        C("calls", 0x00255710, 0x002547D1),
        C("stores", 0x0025A674, 0x006556EC, "68"),
        C("calls", 0x0025A687, 0x002573EE))),
    # RunOffMapBehaviorModuleData: built by ?friend_newModuleData@RunOffMapBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00BF3298: ("RunOffMapBehaviorModuleData", (word(0x00BF3298, 14, 0x000B69A1), C("stores", 0x00254EE4, 0x00BF3298, "c706"),
        C("calls", 0x00254F45, 0x00254ECE),
        C("stores", 0x00258A18, 0x00654F24, "68"),
        C("calls", 0x00258A2B, 0x002573EE))),
    # UpgradeDieModuleData: built by ?friend_newModuleData@UpgradeDieModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00BF33C0: ("UpgradeDieModuleData", (word(0x00BF33C0, 14, 0x000B69A1), C("stores", 0x002550F5, 0x00BF33C0, "c706"),
        C("calls", 0x00255124, 0x002550ED),
        C("stores", 0x00258D6A, 0x00655103, "68"),
        C("calls", 0x00258D76, 0x002573EE))),
    # SlavedUpdateModuleData: built by ?friend_newModuleData@SlavedUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00BF34C0: ("SlavedUpdateModuleData", (word(0x00BF34C0, 14, 0x000B69A1), C("stores", 0x002552DE, 0x00BF34C0, "c700"),
        C("calls", 0x0025534F, 0x002552D7),
        C("stores", 0x00259CFF, 0x00655340, "68"),
        C("calls", 0x00259D12, 0x002573EE))),
    # StealthDetectorUpdateModuleData: built by ?friend_newModuleData@StealthDetectorUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00BF3540: ("StealthDetectorUpdateModuleData", (word(0x00BF3540, 14, 0x000B69A1), C("stores", 0x0025537A, 0x00BF3540, "c706"),
        C("calls", 0x002553D4, 0x00255371),
        C("stores", 0x00258E43, 0x006553C5, "68"),
        C("calls", 0x00258E56, 0x002573EE))),
    # Rva002553F6: built by ?ModuleFactoryDataAt00255440@@YAPAVModuleData@@PAVINI@@@Z
    0x00BF35C0: ("Rva002553F6", (word(0x00BF35C0, 14, 0x000B69A1), C("stores", 0x002553FF, 0x00BF35C0, "c706"),
        C("calls", 0x00255452, 0x002553F6),
        C("stores", 0x00258E85, 0x00655440, "68"),
        C("calls", 0x00258E91, 0x002573EE))),
    # InvisibilityUpdateModuleData: built by ?friend_newModuleData@InvisibilityUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00BF3640: ("InvisibilityUpdateModuleData", (word(0x00BF3640, 14, 0x000B69A1), C("stores", 0x00255490, 0x00BF3640, "c706"),
        C("calls", 0x0025555E, 0x00255474),
        C("stores", 0x00258EEE, 0x0065553A, "68"),
        C("calls", 0x00258F01, 0x002573EE))),
    # SpawnUnitBehaviorModuleData: built by ?friend_newModuleData@SpawnUnitBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00BF36C0: ("SpawnUnitBehaviorModuleData", (word(0x00BF36C0, 14, 0x000B69A1), C("stores", 0x002559A4, 0x00BF36C0, "c706"),
        C("calls", 0x00255A12, 0x0025598C),
        C("stores", 0x00258339, 0x006559F1, "68"),
        C("calls", 0x0025834C, 0x002573EE))),
    # FadeAndDieOrnamentUpdateModuleData: built by ?friend_newModuleData@FadeAndDieOrnamentUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00BF3740: ("FadeAndDieOrnamentUpdateModuleData", (word(0x00BF3740, 14, 0x000B69A1), C("stores", 0x002555C6, 0x00BF3740, "c706"),
        C("calls", 0x00255622, 0x002555AC),
        C("stores", 0x0025A020, 0x00655601, "68"),
        C("calls", 0x0025A033, 0x002573EE))),
    # CommandSetUpgradeModuleData: built by ?friend_newModuleData@CommandSetUpgradeModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00BF37C0: ("CommandSetUpgradeModuleData", (word(0x00BF37C0, 14, 0x000B69A1), C("stores", 0x00255672, 0x00BF37C0, "c706"),
        C("calls", 0x002556BC, 0x00255652),
        C("stores", 0x0025A59B, 0x00655698, "68"),
        C("calls", 0x0025A5A7, 0x002573EE))),
    # AttributeModifierUpgradeModuleData: built by ?friend_newModuleData@AttributeModifierUpgradeModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00BF38C0: ("AttributeModifierUpgradeModuleData", (word(0x00BF38C0, 14, 0x000B69A1), C("stores", 0x002557F1, 0x00BF38C0, "c706"),
        C("calls", 0x00255814, 0x002557E9),
        C("stores", 0x0025A984, 0x00655802, "68"),
        C("calls", 0x0025A997, 0x002573EE))),
    # CastleUpgradeModuleData: built by ?friend_newModuleData@CastleUpgradeModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00BF3940: ("CastleUpgradeModuleData", (word(0x00BF3940, 14, 0x000B69A1), C("stores", 0x00255841, 0x00BF3940, "c706"),
        C("calls", 0x0025586C, 0x00255836),
        C("stores", 0x0025A9BC, 0x0065585A, "68"),
        C("calls", 0x0025A9CF, 0x002573EE))),
    # UnitCrateCollideModuleData: built by ?friend_newModuleData@UnitCrateCollideModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00BF39C0: ("UnitCrateCollideModuleData", (word(0x00BF39C0, 14, 0x000B69A1), C("stores", 0x00255A8D, 0x00BF39C0, "c706"),
        C("calls", 0x00255AD9, 0x00255A72),
        C("stores", 0x0025B2C1, 0x00655AB8, "68"),
        C("calls", 0x0025B2D4, 0x002573EE))),
    # SalvageCrateCollideModuleData: built by ?friend_newModuleData@SalvageCrateCollideModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00BF3A40: ("SalvageCrateCollideModuleData", (word(0x00BF3A40, 14, 0x000B69A1), C("stores", 0x00255BA3, 0x00BF3A40, "c706"),
        C("calls", 0x00255BF6, 0x00255B7E),
        C("stores", 0x0025B32B, 0x00655BD2, "68"),
        C("calls", 0x0025B33E, 0x002573EE))),
    # VeterancyCrateCollideModuleData: built by ?friend_newModuleData@VeterancyCrateCollideModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00BF3AC0: ("VeterancyCrateCollideModuleData", (word(0x00BF3AC0, 14, 0x000B69A1), C("stores", 0x00255B1C, 0x00BF3AC0, "c706"),
        C("calls", 0x00255B4E, 0x00255B09),
        C("stores", 0x0025B2F6, 0x00655B2D, "68"),
        C("calls", 0x0025B309, 0x002573EE))),
    # CreateCrateDieModuleData: built by ?friend_newModuleData@CreateCrateDieModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00BF40A8: ("CreateCrateDieModuleData", (word(0x00BF40A8, 14, 0x000B69A1), C("stores", 0x00257313, 0x00BF40A8, "c706"),
        C("calls", 0x002573BE, 0x002572EE),
        C("stores", 0x00258BDB, 0x0065739D, "68"),
        C("calls", 0x00258BEE, 0x002573EE))),
    # SubObjectsUpgradeModuleData: built by ?friend_newModuleData@SubObjectsUpgradeModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00BF41A8: ("SubObjectsUpgradeModuleData", (word(0x00BF41A8, 14, 0x000B69A1), C("stores", 0x0025777E, 0x00BF41A8, "c706"),
        C("calls", 0x0025781E, 0x00257768),
        C("stores", 0x0025A6E4, 0x0065780C, "68"),
        C("calls", 0x0025A6F7, 0x002573EE))),
    # RandomSoundSelectorClientBehaviorModuleData: built by ?friend_newModuleData@RandomSoundSelectorClientBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00BF42A8: ("RandomSoundSelectorClientBehaviorModuleData", (word(0x00BF42A8, 14, 0x000B69A1), C("stores", 0x00257874, 0x00BF42A8, "c706"),
        C("calls", 0x0025794E, 0x0025785C),
        C("stores", 0x0025BE63, 0x0065792A, "68"),
        C("calls", 0x0025BE76, 0x002573EE))),
    # TunnelContainModuleData: built by ?friend_newModuleData@TunnelContainModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00BF4328: ("TunnelContainModuleData", (word(0x00BF4328, 14, 0x000B69A1), C("stores", 0x002579AE, 0x00BF4328, "c706"),
        C("calls", 0x00257A2E, 0x0025797E),
        C("stores", 0x002586CB, 0x00657A0A, "68"),
        C("calls", 0x002586DE, 0x002573EE))),
    # LaserUpdateModuleData: built by ?friend_newModuleData@LaserUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C17120: ("LaserUpdateModuleData", (word(0x00C17120, 14, 0x000B69A1), C("stores", 0x0036314E, 0x00C17120, "c700"),
        C("calls", 0x0024D57B, 0x00363147),
        C("stores", 0x002595F2, 0x0064D55A, "68"),
        C("calls", 0x00259605, 0x002573EE))),
    # StealthUpdateModuleData: built by ?friend_newModuleData@StealthUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C184D8: ("StealthUpdateModuleData", (word(0x00C184D8, 14, 0x000B69A1), C("stores", 0x003758AB, 0x00C184D8, "c706"),
        C("calls", 0x0024EC84, 0x0037588B),
        C("stores", 0x00258EB6, 0x0064EC60, "68"),
        C("calls", 0x00258EC9, 0x002573EE))),
    # CastleMemberBehaviorModuleData: built by ?friend_newModuleData@CastleMemberBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C1A380: ("CastleMemberBehaviorModuleData", (word(0x00C1A380, 14, 0x000B69A1), C("stores", 0x00395B07, 0x00C1A380, "c700"),
        C("calls", 0x0024AB47, 0x00395B03),
        C("stores", 0x00257DC5, 0x0064AB26, "68"),
        C("calls", 0x00257DD1, 0x002573EE))),
    # CastleBehaviorModuleData: built by ?friend_newModuleData@CastleBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C1A858: ("CastleBehaviorModuleData", (word(0x00C1A858, 14, 0x000B69A1), C("stores", 0x0039A049, 0x00C1A858, "c706"),
        C("calls", 0x0024AABA, 0x0039A027),
        C("stores", 0x00257D88, 0x0064AA99, "68"),
        C("calls", 0x00257D9B, 0x002573EE))),
    # StrafeAreaUpdateModuleData: built by ?friend_newModuleData@StrafeAreaUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C1B268: ("StrafeAreaUpdateModuleData", (word(0x00C1B268, 14, 0x000B69A1), C("stores", 0x003A4E72, 0x00C1B268, "c706"),
        C("calls", 0x0024D758, 0x003A4E5A),
        C("stores", 0x00259945, 0x0064D737, "68"),
        C("calls", 0x00259958, 0x002573EE))),
    # BloodthirstyUpdateModuleData: built by ?friend_newModuleData@BloodthirstyUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C3F160: ("BloodthirstyUpdateModuleData", (word(0x00C3F160, 14, 0x000B69A1), C("stores", 0x0044E2C4, 0x00C3F160, "c706"),
        C("calls", 0x0024A809, 0x0044E2AC),
        C("stores", 0x0025A306, 0x0064A7E8, "68"),
        C("calls", 0x0025A319, 0x002573EE))),
    # SpecialAbilityUpdateModuleData: built by ?friend_newModuleData@SpecialAbilityUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C3F2A8: ("SpecialAbilityUpdateModuleData", (word(0x00C3F2A8, 14, 0x000B69A1), C("stores", 0x0044EB68, 0x00C3F2A8, "c706"),
        C("calls", 0x0024A8A6, 0x0044EB54),
        C("stores", 0x00259DD9, 0x0064A882, "68"),
        C("calls", 0x00259DEC, 0x002573EE))),
    # BuildingBehaviorModuleData: built by ?friend_newModuleData@BuildingBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C40798: ("BuildingBehaviorModuleData", (word(0x00C40798, 14, 0x000B69A1), C("stores", 0x004564B0, 0x00C40798, "c706"),
        C("calls", 0x0024ABD0, 0x00456489),
        C("stores", 0x00257DF6, 0x0064ABAF, "68"),
        C("calls", 0x00257E09, 0x002573EE))),
    # BridgeBehaviorModuleData: built by ?friend_newModuleData@BridgeBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C40A10: ("BridgeBehaviorModuleData", (word(0x00C40A10, 14, 0x000B69A1), C("stores", 0x0045800E, 0x00C40A10, "c706"),
        C("calls", 0x0024AC5C, 0x00457FF1),
        C("stores", 0x00257E2E, 0x0064AC3B, "68"),
        C("calls", 0x00257E41, 0x002573EE))),
    # RampageBehaviorModuleData: built by ?friend_newModuleData@RampageBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C40EF8: ("RampageBehaviorModuleData", (word(0x00C40EF8, 14, 0x000B69A1), C("stores", 0x00458C31, 0x00C40EF8, "c706"),
        C("calls", 0x0024AD59, 0x00458C0F),
        C("stores", 0x00257ED6, 0x0064AD38, "68"),
        C("calls", 0x00257EE9, 0x002573EE))),
    # InstantDeathBehaviorModuleData: built by ?friend_newModuleData@InstantDeathBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C41F28: ("InstantDeathBehaviorModuleData", (word(0x00C41F28, 14, 0x000B69A1), C("stores", 0x0045D189, 0x00C41F28, "c706"),
        C("calls", 0x0024B234, 0x0045D176),
        C("stores", 0x002581AE, 0x0064B213, "68"),
        C("calls", 0x002581C1, 0x002573EE))),
    # ShipSlowDeathBehaviorModuleData: built by ?friend_newModuleData@ShipSlowDeathBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C42E98: ("ShipSlowDeathBehaviorModuleData", (word(0x00C42E98, 14, 0x000B69A1), C("stores", 0x0045E969, 0x00C42E98, "c706"),
        C("calls", 0x0024B34C, 0x0045E961),
        C("stores", 0x0025821E, 0x0064B328, "68"),
        C("calls", 0x00258231, 0x002573EE))),
    # TransportContainModuleData: built by ?friend_newModuleData@TransportContainModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C442F8: ("TransportContainModuleData", (word(0x00C442F8, 14, 0x000B69A1), C("stores", 0x00468320, 0x00C442F8, "c706"),
        C("calls", 0x0024B8C0, 0x00468301),
        C("stores", 0x0025862A, 0x0064B89C, "68"),
        C("calls", 0x00258636, 0x002573EE))),
    # GarrisonContainModuleData: built by ?friend_newModuleData@GarrisonContainModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C462D8: ("GarrisonContainModuleData", (word(0x00C462D8, 14, 0x000B69A1), C("stores", 0x004797A9, 0x00C462D8, "c706"),
        C("calls", 0x00254FB4, 0x0047978F),
        C("stores", 0x002585E7, 0x00654F90, "68"),
        C("calls", 0x002585FA, 0x002573EE))),
    # AODHordeContainModuleData: built by ?friend_newModuleData@HorseHordeContain@@SAPAVModuleData@@PAVINI@@@Z
    0x00C465F8: ("AODHordeContainModuleData", (word(0x00C465F8, 14, 0x000B69A1), C("stores", 0x002535EF, 0x00C465F8, "c706"),
        C("stores", 0x00258573, 0x006535C4, "68"),
        C("calls", 0x00258586, 0x002573EE))),
    # SiegeEngineContainModuleData: built by ?friend_newModuleData@SiegeEngineContainModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C47180: ("SiegeEngineContainModuleData", (word(0x00C47180, 14, 0x000B69A1), C("stores", 0x0047C94A, 0x00C47180, "c706"),
        C("calls", 0x0024BC13, 0x0047C927),
        C("stores", 0x0025865B, 0x0064BBEF, "68"),
        C("calls", 0x0025866E, 0x002573EE))),
    # HordeSiegeEngineContainModuleData: built by ?friend_newModuleData@HordeSiegeEngineContainModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C47520: ("HordeSiegeEngineContainModuleData", (word(0x00C47520, 14, 0x000B69A1), C("stores", 0x0047DA2A, 0x00C47520, "c706"),
        C("calls", 0x0024BCA2, 0x0047DA08),
        C("stores", 0x00258693, 0x0064BC7E, "68"),
        C("calls", 0x002586A6, 0x002573EE))),
    # RiderChangeContainModuleData: built by ?friend_newModuleData@RiderChangeContainModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C47B00: ("RiderChangeContainModuleData", (word(0x00C47B00, 14, 0x000B69A1), C("stores", 0x0047EAEB, 0x00C47B00, "c706"),
        C("calls", 0x0024BD87, 0x0047EABC),
        C("stores", 0x00258773, 0x0064BD63, "68"),
        C("calls", 0x00258786, 0x002573EE))),
    # ShareExperienceBehaviorModuleData: built by ?friend_newModuleData@ShareExperienceBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C486B0: ("ShareExperienceBehaviorModuleData", (word(0x00C486B0, 14, 0x000B69A1), C("stores", 0x0047FEBD, 0x00C486B0, "c706"),
        C("calls", 0x0024C006, 0x0047FE90),
        C("stores", 0x00259730, 0x0064BFE5, "68"),
        C("calls", 0x00259743, 0x002573EE))),
    # SlaughterHordeContainModuleData: built by ?friend_newModuleData@SlaughterHordeContainModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C48DC0: ("SlaughterHordeContainModuleData", (word(0x00C48DC0, 14, 0x000B69A1), C("stores", 0x0048107A, 0x00C48DC0, "c706"),
        C("calls", 0x0024C095, 0x0048104D),
        C("stores", 0x002587AB, 0x0064C071, "68"),
        C("calls", 0x002587BE, 0x002573EE))),
    # CitadelSlaughterHordeContainModuleData: built by ?friend_newModuleData@CitadelSlaughterHordeContainModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C48E40: ("CitadelSlaughterHordeContainModuleData", (word(0x00C48E40, 14, 0x000B69A1), C("stores", 0x00481155, 0x00C48E40, "c706"),
        C("calls", 0x0024C124, 0x0048112F),
        C("stores", 0x002587E3, 0x0064C100, "68"),
        C("calls", 0x002587F6, 0x002573EE))),
    # ProductionQueueHordeContainModuleData: built by ?friend_newModuleData@ProductionQueueHordeContainModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C490F8: ("ProductionQueueHordeContainModuleData", (word(0x00C490F8, 14, 0x000B69A1), C("stores", 0x0048178A, 0x00C490F8, "c706"),
        C("calls", 0x0024C1B3, 0x00481776),
        C("stores", 0x0025881B, 0x0064C18F, "68"),
        C("calls", 0x0025882E, 0x002573EE))),
    # PropagandaTowerBehaviorModuleData: built by ?friend_newModuleData@PropagandaTowerBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C49288: ("PropagandaTowerBehaviorModuleData", (word(0x00C49288, 14, 0x000B69A1), C("stores", 0x00481988, 0x00C49288, "c700"),
        C("calls", 0x0024C23C, 0x0048197C),
        C("stores", 0x00258853, 0x0064C21B, "68"),
        C("calls", 0x00258866, 0x002573EE))),
    # TerrainResourceBehaviorModuleData: built by ?friend_newModuleData@TerrainResourceBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C49440: ("TerrainResourceBehaviorModuleData", (word(0x00C49440, 14, 0x000B69A1), C("stores", 0x00482052, 0x00C49440, "c706"),
        C("calls", 0x0024C2C5, 0x0048202F),
        C("stores", 0x0025888B, 0x0064C2A4, "68"),
        C("calls", 0x0025889E, 0x002573EE))),
    # ClearanceTestingSlowDeathBehaviorModuleData: built by ?friend_newModuleData@ClearanceTestingSlowDeathBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C49E98: ("ClearanceTestingSlowDeathBehaviorModuleData", (word(0x00C49E98, 14, 0x000B69A1), C("stores", 0x00483E57, 0x00C49E98, "c706"),
        C("calls", 0x0024C569, 0x00483E25),
        C("stores", 0x002589E1, 0x0064C545, "68"),
        C("calls", 0x002589F4, 0x002573EE))),
    # SlaveWatcherBehaviorModuleData: built by ?friend_newModuleData@SlaveWatcherBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C4A298: ("SlaveWatcherBehaviorModuleData", (word(0x00C4A298, 14, 0x000B69A1), C("stores", 0x004846CB, 0x00C4A298, "c700"),
        C("calls", 0x0024C681, 0x004846C7),
        C("stores", 0x00258A8B, 0x0064C660, "68"),
        C("calls", 0x00258A9E, 0x002573EE))),
    # PassiveAreaEffectBehaviorModuleData: built by ?friend_newModuleData@PassiveAreaEffectBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C4A490: ("PassiveAreaEffectBehaviorModuleData", (word(0x00C4A490, 14, 0x000B69A1), C("stores", 0x00484E26, 0x00C4A490, "c706"),
        C("calls", 0x0024C745, 0x00484DF4),
        C("stores", 0x0025ABE9, 0x0064C724, "68"),
        C("calls", 0x0025ABFC, 0x002573EE))),
    # CreateObjectDieModuleData: built by ?friend_newModuleData@CreateObjectDieModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C4A988: ("CreateObjectDieModuleData", (word(0x00C4A988, 14, 0x000B69A1), C("stores", 0x00485DA5, 0x00C4A988, "c706"),
        C("calls", 0x0024C8E2, 0x00485D88),
        C("stores", 0x00258C4B, 0x0064C8C1, "68"),
        C("calls", 0x00258C5E, 0x002573EE))),
    # CreateObjectDieIfEldestKindofModuleData: built by ?friend_newModuleData@CreateObjectDieIfEldestKindofModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C4AA08: ("CreateObjectDieIfEldestKindofModuleData", (word(0x00C4AA08, 14, 0x000B69A1), C("stores", 0x00485E3E, 0x00C4AA08, "c706"),
        C("calls", 0x0024C96B, 0x00485E19),
        C("stores", 0x00258C83, 0x0064C94A, "68"),
        C("calls", 0x00258C96, 0x002573EE))),
    # RebuildHoleExposeDieModuleData: built by ?friend_newModuleData@RebuildHoleExposeDieModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C4AD40: ("RebuildHoleExposeDieModuleData", (word(0x00C4AD40, 14, 0x000B69A1), C("stores", 0x0048672A, 0x00C4AD40, "c706"),
        C("calls", 0x0024CB39, 0x0048671F),
        C("stores", 0x00258D2B, 0x0064CB18, "68"),
        C("calls", 0x00258D3E, 0x002573EE))),
    # BoneFXUpdateModuleData: built by ?friend_newModuleData@BoneFXUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C4B0E8: ("BoneFXUpdateModuleData", (word(0x00C4B0E8, 14, 0x000B69A1), C("stores", 0x004877BE, 0x00C4B0E8, "c706"),
        C("calls", 0x00253C9C, 0x00487797),
        C("stores", 0x0025A0F4, 0x00653C78, "68"),
        C("calls", 0x0025A107, 0x002573EE))),
    # DynamicShroudClearingRangeUpdateModuleData: built by ?friend_newModuleData@DynamicShroudClearingRangeUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C4BEF8: ("DynamicShroudClearingRangeUpdateModuleData", (word(0x00C4BEF8, 14, 0x000B69A1), C("stores", 0x0048B5E0, 0x00C4BEF8, "c706"),
        C("calls", 0x0024CE65, 0x0048B5C6),
        C("stores", 0x00258F96, 0x0064CE44, "68"),
        C("calls", 0x00258FA9, 0x002573EE))),
    # FireWeaponUpdateModuleData: built by ?friend_newModuleData@FireWeaponUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C4C110: ("FireWeaponUpdateModuleData", (word(0x00C4C110, 14, 0x000B69A1), C("stores", 0x0048BC20, 0x00C4C110, "c706"),
        C("calls", 0x0024CF77, 0x0048BC03),
        C("stores", 0x00259316, 0x0064CF56, "68"),
        C("calls", 0x00259329, 0x002573EE))),
    # OilSpillUpdateModuleData: built by ?friend_newModuleData@OilSpillUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C4C2F8: ("OilSpillUpdateModuleData", (word(0x00C4C2F8, 14, 0x000B69A1), C("stores", 0x0048C179, 0x00C4C2F8, "c706"),
        C("calls", 0x0024D000, 0x0048C16C),
        C("stores", 0x0025934E, 0x0064CFDF, "68"),
        C("calls", 0x00259361, 0x002573EE))),
    # FlammableUpdateModuleData: built by ?friend_newModuleData@FlammableUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C4C408: ("FlammableUpdateModuleData", (word(0x00C4C408, 14, 0x000B69A1), C("stores", 0x0048D557, 0x00C4C408, "c706"),
        C("calls", 0x0024D089, 0x0048D541),
        C("stores", 0x002593F6, 0x0064D068, "68"),
        C("calls", 0x00259409, 0x002573EE))),
    # FloodUpdateModuleData: built by ?friend_newModuleData@FloodUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C4C8C0: ("FloodUpdateModuleData", (word(0x00C4C8C0, 14, 0x000B69A1), C("stores", 0x0048DF97, 0x00C4C8C0, "c706"),
        C("calls", 0x0024D19B, 0x0048DF7A),
        C("stores", 0x00259466, 0x0064D17A, "68"),
        C("calls", 0x00259479, 0x002573EE))),
    # LargeGroupBonusUpdateModuleData: built by ?friend_newModuleData@LargeGroupBonusUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C4D2A8: ("LargeGroupBonusUpdateModuleData", (word(0x00C4D2A8, 14, 0x000B69A1), C("stores", 0x004901DB, 0x00C4D2A8, "c706"),
        C("calls", 0x0024D460, 0x004901BD),
        C("stores", 0x00259076, 0x0064D43F, "68"),
        C("calls", 0x00259089, 0x002573EE))),
    # DamageFieldUpdateModuleData: built by ?friend_newModuleData@DamageFieldUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C4D8E8: ("DamageFieldUpdateModuleData", (word(0x00C4D8E8, 14, 0x000B69A1), C("stores", 0x00491123, 0x00C4D8E8, "c706"),
        C("calls", 0x0024D7E1, 0x00491102),
        C("stores", 0x00259386, 0x0064D7C0, "68"),
        C("calls", 0x00259399, 0x002573EE))),
    # MonitorConditionUpdateModuleData: built by ?friend_newModuleData@MonitorConditionUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C4DA50: ("MonitorConditionUpdateModuleData", (word(0x00C4DA50, 14, 0x000B69A1), C("stores", 0x00491604, 0x00C4DA50, "c706"),
        C("calls", 0x0024D86A, 0x004915FD),
        C("stores", 0x002593BE, 0x0064D849, "68"),
        C("calls", 0x002593D1, 0x002573EE))),
    # AttachUpdateModuleData: built by ?friend_newModuleData@AttachUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C4DD18: ("AttachUpdateModuleData", (word(0x00C4DD18, 14, 0x000B69A1), C("stores", 0x00491985, 0x00C4DD18, "c706"),
        C("calls", 0x0024D8F3, 0x00491968),
        C("stores", 0x00259C2B, 0x0064D8D2, "68"),
        C("calls", 0x00259C3E, 0x002573EE))),
    # PickupStuffUpdateModuleData: built by ?friend_newModuleData@PickupStuffUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C4DDE0: ("PickupStuffUpdateModuleData", (word(0x00C4DDE0, 14, 0x000B69A1), C("stores", 0x00491E57, 0x00C4DDE0, "c706"),
        C("calls", 0x0024D97C, 0x00491E37),
        C("stores", 0x00259C60, 0x0064D95B, "68"),
        C("calls", 0x00259C73, 0x002573EE))),
    # WeaponFireSpecialAbilityUpdateModuleData: built by ?friend_newModuleData@WeaponFireSpecialAbilityUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C4E108: ("WeaponFireSpecialAbilityUpdateModuleData", (word(0x00C4E108, 14, 0x000B69A1), C("stores", 0x004926D4, 0x00C4E108, "c706"),
        C("calls", 0x0024DB7A, 0x004926CA),
        C("stores", 0x00259A19, 0x0064DB56, "68"),
        C("calls", 0x00259A2C, 0x002573EE))),
    # TeleportSpecialAbilityUpdateModuleData: built by ?friend_newModuleData@TeleportSpecialAbilityUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C4E208: ("TeleportSpecialAbilityUpdateModuleData", (word(0x00C4E208, 14, 0x000B69A1), C("stores", 0x00492E5B, 0x00C4E208, "c706"),
        C("calls", 0x0024DC24, 0x00492E43),
        C("stores", 0x00259A4E, 0x0064DC00, "68"),
        C("calls", 0x00259A61, 0x002573EE))),
    # SpecialPowerModuleData: built by ?friend_newModuleData@SpecialPowerModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C4E318: ("SpecialPowerModuleData", (word(0x00C4E318, 14, 0x000B69A1), C("stores", 0x004930BC, 0x00C4E318, "c706"),
        C("calls", 0x0024DCAD, 0x004930A0),
        C("stores", 0x0025B614, 0x0064DC8C, "68"),
        C("calls", 0x0025B627, 0x002573EE))),
    # WeaponModeSpecialPowerUpdateModuleData: built by ?friend_newModuleData@WeaponModeSpecialPowerUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C4EA88: ("WeaponModeSpecialPowerUpdateModuleData", (word(0x00C4EA88, 14, 0x000B69A1), C("stores", 0x00494D2F, 0x00C4EA88, "c706"),
        C("calls", 0x0024DD42, 0x00494D26),
        C("stores", 0x002598DB, 0x0064DD21, "68"),
        C("calls", 0x002598EE, 0x002573EE))),
    # AutoPickUpUpdateModuleData: built by ?friend_newModuleData@AutoPickUpUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C4F108: ("AutoPickUpUpdateModuleData", (word(0x00C4F108, 14, 0x000B69A1), C("stores", 0x00496321, 0x00C4F108, "c706"),
        C("calls", 0x0024E0BA, 0x00496308),
        C("stores", 0x00259691, 0x0064E099, "68"),
        C("calls", 0x002596A4, 0x002573EE))),
    # BannerCarrierUpdateModuleData: built by ?friend_newModuleData@BannerCarrierUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C4F870: ("BannerCarrierUpdateModuleData", (word(0x00C4F870, 14, 0x000B69A1), C("stores", 0x00496FB7, 0x00C4F870, "c706"),
        C("calls", 0x0024E1CC, 0x00496FA5),
        C("stores", 0x00259765, 0x0064E1AB, "68"),
        C("calls", 0x00259778, 0x002573EE))),
    # BattlePlanUpdateModuleData: built by ?friend_newModuleData@BattlePlanUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C4FB00: ("BattlePlanUpdateModuleData", (word(0x00C4FB00, 14, 0x000B69A1), C("stores", 0x0049780D, 0x00C4FB00, "c706"),
        C("calls", 0x0024E25B, 0x0049780A),
        C("stores", 0x0025979A, 0x0064E237, "68"),
        C("calls", 0x002597AD, 0x002573EE))),
    # OneRingPenaltyUpdateModuleData: built by ?friend_newModuleData@OneRingPenaltyUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C50298: ("OneRingPenaltyUpdateModuleData", (word(0x00C50298, 14, 0x000B69A1), C("stores", 0x004999F8, 0x00C50298, "c700"),
        C("calls", 0x0024E44D, 0x004999F1),
        C("stores", 0x00259156, 0x0064E42C, "68"),
        C("calls", 0x00259169, 0x002573EE))),
    # ProductionUpdateModuleData: built by ?friend_newModuleData@ProductionUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C515F0: ("ProductionUpdateModuleData", (word(0x00C515F0, 14, 0x000B69A1), C("stores", 0x0049F7FE, 0x00C515F0, "c706"),
        C("calls", 0x0024E8B0, 0x0049F7DB),
        C("stores", 0x00259F81, 0x0064E88F, "68"),
        C("calls", 0x00259F94, 0x002573EE))),
    # MonsterDockUpdateModuleData: built by ?friend_newModuleData@MonsterDockUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C51DA8: ("MonsterDockUpdateModuleData", (word(0x00C51DA8, 14, 0x000B69A1), C("stores", 0x004A1534, 0x00C51DA8, "c706"),
        C("calls", 0x0024EB4D, 0x004A1517),
        C("stores", 0x00259EAD, 0x0064EB2C, "68"),
        C("calls", 0x00259EC0, 0x002573EE))),
    # MissileUpdateModuleData: built by ?friend_newModuleData@MissileUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C53668: ("MissileUpdateModuleData", (word(0x00C53668, 14, 0x000B69A1), C("stores", 0x004A77DA, 0x00C53668, "c706"),
        C("calls", 0x0024EFC4, 0x004A77B8),
        C("stores", 0x0025813E, 0x0064EFA0, "68"),
        C("calls", 0x00258151, 0x002573EE))),
    # ToppleUpdateModuleData: built by ?friend_newModuleData@ToppleUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C538A0: ("ToppleUpdateModuleData", (word(0x00C538A0, 14, 0x000B69A1), C("stores", 0x004A818A, 0x00C538A0, "c706"),
        C("calls", 0x0024F0D9, 0x004A8173),
        C("stores", 0x002590AE, 0x0064F0B8, "68"),
        C("calls", 0x002590C1, 0x002573EE))),
    # PartTheHeavensUpdateModuleData: built by ?friend_newModuleData@PartTheHeavensUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C54E38: ("PartTheHeavensUpdateModuleData", (word(0x00C54E38, 14, 0x000B69A1), C("stores", 0x004ACC0D, 0x00C54E38, "c706"),
        C("calls", 0x0024F521, 0x004ACBF8),
        C("stores", 0x0025926E, 0x0064F4FD, "68"),
        C("calls", 0x00259281, 0x002573EE))),
    # ToggleDeploySpecialAbilityUpdateModuleData: built by ?friend_newModuleData@ToggleDeploySpecialAbilityUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C553D8: ("ToggleDeploySpecialAbilityUpdateModuleData", (word(0x00C553D8, 14, 0x000B69A1), C("stores", 0x004AE54F, 0x00C553D8, "c706"),
        C("calls", 0x0024F83D, 0x004AE547),
        C("stores", 0x002599E4, 0x0064F819, "68"),
        C("calls", 0x002599F7, 0x002573EE))),
    # RespawnUpdateModuleData: built by ?friend_newModuleData@RespawnUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C556F8: ("RespawnUpdateModuleData", (word(0x00C556F8, 14, 0x000B69A1), C("stores", 0x004AFB68, 0x00C556F8, "c706"),
        C("calls", 0x0024F952, 0x004AFB4E),
        C("stores", 0x0025A2D1, 0x0064F92E, "68"),
        C("calls", 0x0025A2E4, 0x002573EE))),
    # SpecialDisguiseUpdateModuleData: built by ?friend_newModuleData@SpecialDisguiseUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C563F8: ("SpecialDisguiseUpdateModuleData", (word(0x00C563F8, 14, 0x000B69A1), C("stores", 0x004B0262, 0x00C563F8, "c706"),
        C("calls", 0x0024F9FC, 0x004B0255),
        C("stores", 0x0025A377, 0x0064F9D8, "68"),
        C("calls", 0x0025A383, 0x002573EE))),
    # AISpecialPowerUpdateModuleData: built by ?friend_newModuleData@AISpecialPowerUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C56F48: ("AISpecialPowerUpdateModuleData", (word(0x00C56F48, 14, 0x000B69A1), C("stores", 0x004B2FD9, 0x00C56F48, "c700"),
        C("calls", 0x0024FD97, 0x004B2FCD),
        C("stores", 0x0025A483, 0x0064FD76, "68"),
        C("calls", 0x0025A48F, 0x002573EE))),
    # BaseUpgradeModuleData: built by ?friend_newModuleData@BaseUpgradeModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C57150: ("BaseUpgradeModuleData", (word(0x00C57150, 14, 0x000B69A1), C("stores", 0x004B36B8, 0x00C57150, "c706"),
        C("calls", 0x0024FE5B, 0x004B3698),
        C("stores", 0x0025A55C, 0x0064FE37, "68"),
        C("calls", 0x0025A56F, 0x002573EE))),
    # ObjectCreationUpgradeModuleData: built by ?friend_newModuleData@ObjectCreationUpgradeModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C577C8: ("ObjectCreationUpgradeModuleData", (word(0x00C577C8, 14, 0x000B69A1), C("stores", 0x004B4264, 0x00C577C8, "c706"),
        C("calls", 0x0024FFD0, 0x004B425B),
        C("stores", 0x0025A7C4, 0x0064FFAC, "68"),
        C("calls", 0x0025A7D7, 0x002573EE))),
    # CostModifierUpgradeModuleData: built by ?friend_newModuleData@CostModifierUpgradeModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C58210: ("CostModifierUpgradeModuleData", (word(0x00C58210, 14, 0x000B69A1), C("stores", 0x004B5BD0, 0x00C58210, "c706"),
        C("calls", 0x0025033A, 0x004B5BAC),
        C("stores", 0x0025A4B4, 0x00650316, "68"),
        C("calls", 0x0025A4C7, 0x002573EE))),
    # AudioLoopUpgradeModuleData: built by ?friend_newModuleData@AudioLoopUpgradeModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C58CF8: ("AudioLoopUpgradeModuleData", (word(0x00C58CF8, 14, 0x000B69A1), C("stores", 0x004B7C13, 0x00C58CF8, "c706"),
        C("calls", 0x002507BC, 0x004B7C00),
        C("stores", 0x0025AAD4, 0x00650798, "68"),
        C("calls", 0x0025AAE7, 0x002573EE))),
    # GrantUpgradeCreateModuleData: built by ?friend_newModuleData@GrantUpgradeCreateModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C594E0: ("GrantUpgradeCreateModuleData", (word(0x00C594E0, 14, 0x000B69A1), C("stores", 0x004B90FA, 0x00C594E0, "c706"),
        C("calls", 0x00250B62, 0x004B90E1),
        C("stores", 0x0025AF71, 0x00650B41, "68"),
        C("calls", 0x0025AF84, 0x002573EE))),
    # InheritUpgradeCreateModuleData: built by ?friend_newModuleData@InheritUpgradeCreateModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C59768: ("InheritUpgradeCreateModuleData", (word(0x00C59768, 14, 0x000B69A1), C("stores", 0x004B9523, 0x00C59768, "c706"),
        C("calls", 0x00250CE7, 0x004B9508),
        C("stores", 0x0025AFDB, 0x00650CC3, "68"),
        C("calls", 0x0025AFEE, 0x002573EE))),
    # AODCrushCollideModuleData: built by ?friend_newModuleData@AODCrushCollideModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C5A350: ("AODCrushCollideModuleData", (word(0x00C5A350, 14, 0x000B69A1), C("stores", 0x004BBFAA, 0x00C5A350, "c706"),
        C("calls", 0x00251077, 0x004BBF89),
        C("stores", 0x0025B1B8, 0x00651056, "68"),
        C("calls", 0x0025B1CB, 0x002573EE))),
    # CivilianSpawnCollideModuleData: built by ?friend_newModuleData@CivilianSpawnCollideModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C5AAB8: ("CivilianSpawnCollideModuleData", (word(0x00C5AAB8, 14, 0x000B69A1), C("stores", 0x004BD669, 0x00C5AAB8, "c706"),
        C("calls", 0x00251345, 0x004BD651),
        C("stores", 0x0025B360, 0x00651324, "68"),
        C("calls", 0x0025B373, 0x002573EE))),
    # ActiveBodyModuleData: built by ?friend_newModuleData@ActiveBodyModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C5AFB8: ("ActiveBodyModuleData", (word(0x00C5AFB8, 14, 0x000B69A1), C("stores", 0x004BF5B8, 0x00C5AFB8, "c706"),
        C("calls", 0x00251409, 0x004BF59F),
        C("stores", 0x0025B3CA, 0x006513E8, "68"),
        C("calls", 0x0025B3DD, 0x002573EE))),
    # RespawnBodyModuleData: built by ?friend_newModuleData@RespawnBodyModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C5BA00: ("RespawnBodyModuleData", (word(0x00C5BA00, 14, 0x000B69A1), C("stores", 0x004C1501, 0x00C5BA00, "c706"),
        C("calls", 0x002515B7, 0x004C14DF),
        C("stores", 0x0025B5DC, 0x00651596, "68"),
        C("calls", 0x0025B5EF, 0x002573EE))),
    # CashHackSpecialPowerModuleData: built by ?friend_newModuleData@CashHackSpecialPowerModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C5C688: ("CashHackSpecialPowerModuleData", (word(0x00C5C688, 14, 0x000B69A1), C("stores", 0x004C289D, 0x00C5C688, "c706"),
        C("calls", 0x0025197B, 0x004C2889),
        C("stores", 0x0025B684, 0x00651957, "68"),
        C("calls", 0x0025B697, 0x002573EE))),
    # CloudBreakSpecialPowerModuleData: built by ?friend_newModuleData@CloudBreakSpecialPowerModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C5D468: ("CloudBreakSpecialPowerModuleData", (word(0x00C5D468, 14, 0x000B69A1), C("stores", 0x004C47AA, 0x00C5D468, "c706"),
        C("calls", 0x00251E7C, 0x004C479A),
        C("stores", 0x0025B879, 0x00651E58, "68"),
        C("calls", 0x0025B88C, 0x002573EE))),
    # DeflectSpecialPowerModuleData: built by ?friend_newModuleData@DeflectSpecialPowerModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C5DAB0: ("DeflectSpecialPowerModuleData", (word(0x00C5DAB0, 14, 0x000B69A1), C("stores", 0x004C5679, 0x00C5DAB0, "c706"),
        C("calls", 0x00252135, 0x004C5671),
        C("stores", 0x0025B991, 0x00652114, "68"),
        C("calls", 0x0025B9A4, 0x002573EE))),
    # CritterEmitterUpdateModuleData: built by ?friend_newModuleData@CritterEmitterUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C5E988: ("CritterEmitterUpdateModuleData", (word(0x00C5E988, 14, 0x000B69A1), C("stores", 0x004C8F0D, 0x00C5E988, "c706"),
        C("calls", 0x00252927, 0x004C8EFF),
        C("stores", 0x0025848B, 0x00652906, "68"),
        C("calls", 0x0025849E, 0x002573EE))),
    # AnimationSoundClientBehaviorModuleData: built by ?friend_newModuleData@AnimationSoundClientBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C5EED0: ("AnimationSoundClientBehaviorModuleData", (word(0x00C5EED0, 14, 0x000B69A1), C("stores", 0x004CA725, 0x00C5EED0, "c706"),
        C("calls", 0x00252BE3, 0x004CA70D),
        C("stores", 0x0025BDB8, 0x00652BC2, "68"),
        C("calls", 0x0025BDCB, 0x002573EE))),
    # ModelConditionSoundSelectorClientBehaviorModuleData: built by ?friend_newModuleData@ModelConditionSoundSelectorClientBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C5F098: ("ModelConditionSoundSelectorClientBehaviorModuleData", (word(0x00C5F098, 14, 0x000B69A1), C("stores", 0x004CAEF2, 0x00C5F098, "c706"),
        C("calls", 0x00252C34, 0x004CAEE6),
        C("stores", 0x0025BDF1, 0x00652C13, "68"),
        C("calls", 0x0025BE04, 0x002573EE))),
    # UpgradeSoundSelectorClientBehaviorModuleData: built by ?friend_newModuleData@UpgradeSoundSelectorClientBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C5F250: ("UpgradeSoundSelectorClientBehaviorModuleData", (word(0x00C5F250, 14, 0x000B69A1), C("stores", 0x004CB9FF, 0x00C5F250, "c706"),
        C("calls", 0x00252C85, 0x004CB9F3),
        C("stores", 0x0025BE2A, 0x00652C64, "68"),
        C("calls", 0x0025BE3D, 0x002573EE))),
    # ModelConditionAudioLoopClientBehaviorModuleData: built by ?friend_newModuleData@ModelConditionAudioLoopClientBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C5F4A8: ("ModelConditionAudioLoopClientBehaviorModuleData", (word(0x00C5F4A8, 14, 0x000B69A1), C("stores", 0x004CC216, 0x00C5F4A8, "c706"),
        C("calls", 0x00252DBB, 0x004CC20A),
        C("stores", 0x0025BE9C, 0x00652D9A, "68"),
        C("calls", 0x0025BEAF, 0x002573EE))),
    # DominateEnemySpecialPowerModuleData: built by ?friend_newModuleData@DominateEnemySpecialPowerModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C5F6F8: ("DominateEnemySpecialPowerModuleData", (word(0x00C5F6F8, 14, 0x000B69A1), C("stores", 0x004CCA4C, 0x00C5F6F8, "c706"),
        C("calls", 0x00252F09, 0x004CCA24),
        C("stores", 0x0025AC1E, 0x00652EE5, "68"),
        C("calls", 0x0025AC31, 0x002573EE))),
    # GiveOrRestoreUpgradeSpecialPowerModuleData: built by ?friend_newModuleData@GiveOrRestoreUpgradeSpecialPowerModuleData@@SAPAVModuleData@@PAVINI@@@Z
    0x00C5F900: ("GiveOrRestoreUpgradeSpecialPowerModuleData", (word(0x00C5F900, 14, 0x000B69A1), C("stores", 0x004CD0B9, 0x00C5F900, "c706"),
        C("calls", 0x00253027, 0x004CD0B1),
        C("stores", 0x0025AD91, 0x00653003, "68"),
        C("calls", 0x0025ADA4, 0x002573EE))),
    },
    dead={
    # Rva004BDCA3: unreachable dead code. Its only installer 0x004BDCA3 (mov eax, ecx; mov [eax], table; ret) has no
    # caller, no jump and no stored pointer anywhere in the image, so nothing builds this table. Its words match
    # W3DLaserDrawModuleData's table in 30 of 32 slots; that is noted, not used as evidence.
    0x00C5AEB8: (0x004BDCA3, (word(0x00C5AEB8, 14, 0x000B69A1), C("stores", 0x004BDCA5, 0x00C5AEB8, "c700"))),
    })
BASE_SLOTS = (MODULE_DATA_SLOT14,)


def base_slot_of(rva, cls, new):
    """The reviewed base-slot entry for moving the body at `rva` into `cls` as `new`, or None."""
    for entry in BASE_SLOTS:
        if (entry.rva, entry.cls, entry.new) == (rva, cls, new):
            return entry
    return None


def base_slot_facts(entry):
    """Every fact of `entry`, in order."""
    return [*[f for _cls, facts in entry.tables.values() for f in facts],
            *[f for _installer, facts in entry.dead.values() for f in facts]]


def retail_image():
    """(image bytes, .text start rva, .text end rva, rva -> file offset) of the image the manifest names; tests
    replace this."""
    problem = image_problem()
    if problem:
        raise ValueError(problem)
    data, sections = build.exe_image()
    text = next(s for s in sections if s["name"] == ".text")
    return data, text["rva"], text["rva"] + text["size"], lambda rva: build.rva_to_file_offset(sections, rva)


def dead_table_problems(entry):
    """Why a `dead` table of `entry` is reachable, one line each: a rel32 call or jump to its installer anywhere in
    .text (read at every byte, so a false hit refuses), a word equal to the installer's VA anywhere in the image, or a
    word equal to the table's VA anywhere but the installer's own store."""
    if not entry.dead:
        return []
    data, lo, hi, offset = retail_image()
    text = data[offset(lo):offset(lo) + (hi - lo)]
    out = []
    for table, (installer, facts) in sorted(entry.dead.items()):
        store = next((f for f in facts if f.kind == "stores" and f.value == table), None)
        if store is None or store.code not in VPTR_STORES:
            out.append(f"dead table 0x{table:08X} states no store of itself")
            continue
        for at in range(len(text) - 4):
            if text[at] in (0xE8, 0xE9) and                     (lo + at + 5 + struct.unpack_from("<i", text, at + 1)[0]) & 0xFFFFFFFF == installer:
                out.append(f"dead table 0x{table:08X}: retail 0x{lo + at:08X} is a rel32 to its installer "
                           f"0x{installer:08X}")
        own_store = offset(store.site) + len(store.code) // 2
        for value, allowed, what in ((installer + IMAGE_BASE, set(), "its installer's VA"),
                                     (table, {own_store}, "the table's VA")):
            needle = struct.pack("<I", value)
            at = data.find(needle)
            while at != -1:
                if at not in allowed:
                    out.append(f"dead table 0x{table:08X}: file offset 0x{at:X} holds {what} 0x{value:08X}")
                at = data.find(needle, at + 1)
    return out


def base_slot_problems(entry):
    """Why `entry` does not hold, one line each: each listed table opens with the body at its slot, states a store
    of itself and ends at the push of a factory and the call to `register`; each dead table opens with the body at
    its slot and nothing reaches it; retail holds every fact (an unreadable site is a problem)."""
    out = []
    for table, (_cls, facts) in entry.tables.items():
        if not facts or facts[0] != word(table, entry.slot, entry.rva):
            out.append(f"table 0x{table:08X} does not open with word {entry.slot} holding 0x{entry.rva:08X}")
        if not any(f.kind == "stores" and f.value == table and f.code in VPTR_STORES for f in facts):
            out.append(f"table 0x{table:08X} states no store of itself")
        if len(facts) < 4 or facts[-1].kind != "calls" or facts[-1].value != entry.register                 or facts[-2].kind != "stores" or facts[-2].code != "68":
            out.append(f"table 0x{table:08X} does not end at a factory's push and the call to 0x{entry.register:08X}")
    for table, (_installer, facts) in entry.dead.items():
        if not facts or facts[0] != word(table, entry.slot, entry.rva):
            out.append(f"dead table 0x{table:08X} does not open with word {entry.slot} holding 0x{entry.rva:08X}")
    overlap = set(entry.tables) & set(entry.dead)
    if overlap:
        out.append(f"0x{min(overlap):08X} is both a listed and a dead table")
    out += facts_problems(base_slot_facts(entry))
    try:
        out += dead_table_problems(entry)
    except Exception as error:                         # noqa: BLE001 - whatever the read raises refuses
        out.append(f"the image cannot be read for dead tables: {error}")
    return out


# One global's bounds: `old` becomes `new` at the RVA `start`, `size` bytes, taking the rows `absorbs`
# ((name, rva), ...). A `stores` fact names an address the object holds, an `offset` one its code indexes.
Extent = collections.namedtuple("Extent", "old new start size absorbs facts")
_E12_ITERATOR = "U?$_Deque_iterator@UBfmeE12@@U?$_Nonconst_traits@UBfmeE12@@@_STL@@@_STL@@A"
EXTENTS = (
    # P35: InitPostProcessing fills the indices -256..511 of the table every reader names by its zero point
    Extent(old="?g_bfmeClampTable@@3QBEB", new="?g_bfmeClampTable@@3PAEA", start=0x00A23000, size=0x300, absorbs=(),
           facts=(C("offset", 0x001B6520, -256, "b800ffffff"), C("stores", 0x001B653B, 0x00E23100, "8888"),
                  C("offset", 0x001B6542, 512, "3d00020000"))),
    # P30: one deque<BfmeE12> the rowed initializer constructs and the atexit thunk destroys, its finish
    # iterator read at +0x10
    Extent(old=f"?g_00E031A8@@3{_E12_ITERATOR}", new="?g_00E031A8@@3PAIA", start=0x00A031A8, size=40,
           absorbs=((f"?g_00E031B8@@3{_E12_ITERATOR}", 0x00A031B8),),
           facts=(C("stores", 0x007B02DF, 0x00E031A8, "b9"), C("calls", 0x007B02E4, 0x004226CE),
                  C("stores", 0x007B82E7, 0x00E031A8, "b9"), C("jumps", 0x007B82EC, 0x005858F3),
                  C("stores", 0x00422557, 0x00E031B8, "a1"))),
    # P65: one vector of 0x94-byte records the rowed initializer constructs and the atexit thunk destroys. Its
    # destructor 0x003615E5 reads begin +0 and end +4, and its push_back 0x00361756 compares end with capacity at +8
    Extent(old="?g_validityBegin@@3PAEA", new="?g_validityBegin@@3PAIA", start=0x00A01E68, size=12,
           absorbs=(("?g_validityEnd@@3PAEA", 0x00A01E6C),),
           facts=(C("stores", 0x007AED30, 0x00E01E68, "b9"), C("calls", 0x007AED35, 0x004F710A),
                  C("stores", 0x007B7CAF, 0x00E01E68, "b9"), C("jumps", 0x007B7CB4, 0x003615E5),
                  C("stores", 0x00360CBC, 0x00E01E6C, "a1"), C("offset", 0x0036175F, 8, "3b4608"))),
)


def extent_of(old, new):
    """The entry that takes `old` to `new`, or None."""
    for extent in EXTENTS:
        if extent.old == old and extent.new == new:
            return extent
    return None


def extent_problems(extent):
    """Why retail does not state `extent`, one line each. Its facts must hold on the image, every
    address they name must lie inside it, and they must reach what no compiler or byte can prove:
    the start (named, or an address plus a lowest offset its own instruction encodes) and every
    absorbed row's address."""
    problems = facts_problems(extent.facts)
    if problems:
        return problems
    start, end = IMAGE_BASE + extent.start, IMAGE_BASE + extent.start + extent.size
    addresses = [f.value for f in extent.facts if f.kind == "stores"]
    problems = [f"a fact names 0x{value:08X}, outside 0x{start:08X}..0x{end:08X}" for value in addresses
                if not start <= value < end]
    lowest = [f.value for f in extent.facts if f.kind == "offset" and -2 ** 31 <= f.value < 2 ** 31
              and bytes.fromhex(f.code).endswith(struct.pack("<i", f.value))]
    if start not in addresses and not any(value + offset == start for value in addresses for offset in lowest):
        problems.append(f"no fact reaches the start 0x{start:08X}: name it, or a `stores` address plus an `offset` "
                        "its instruction encodes must land on it")
    problems += [f"no fact names 0x{IMAGE_BASE + rva:08X}, where {name} is absorbed" for name, rva in extent.absorbs
                 if IMAGE_BASE + rva not in addresses]
    return problems


def table_named(family, row, owner_size):
    """Does the data ledger's `row`, at the family's table, name the family's class? Its `name` column says so
    outright. An alias in `names` says so only on the stand-in's own table and only when retail backs it: the
    owner's own write of this exact table as a vftable pointer, the whole instruction inside the owner's body. An
    alias alone proves nothing, and neither does a load of the table's address."""
    if row.get("name") == family.table_name:
        return True
    if row.get("name") != f"??_7{family.old}@@6B@" or family.table_name not in (row.get("names") or "").split(";"):
        return False
    start, end = family.owner["rva"], family.owner["rva"] + owner_size
    stores = [f for f in family.owner["facts"] if f.kind == "stores" and f.value == family.table
              and f.code in VPTR_STORES and start <= f.site and f.site + len(expected(f)) <= end]
    return bool(stores) and not facts_problems(stores)


def forced_move_table():
    """{rva: (row name, source)}: every row any family may force-move (BodyFamily.forced_moves)."""
    return {at: entry for family in FAMILIES for at, entry in getattr(family, "forced_moves", {}).items()}


def family_of(rva, new):
    """The family whose row at `rva` is spelled `new` after its respell, or None."""
    for family in FAMILIES:
        got = family.rows.get(rva)
        if got and family.respell(got[0]) == new:
            return family
    return None


def record_proven(old_name, new_name, rva, evidence):
    """Is this name_basis record a family's own record of its row: the row's old spelling, its respell,
    its address spelled exactly as the planner writes it (0x and eight upper-case digits) and exactly
    the facts the table holds for it? Nothing else speaks for a name as `retail`; a reader that does not
    parse another spelling of the address would hold the grant at no address at all."""
    for family in FAMILIES:
        for at, (old, facts) in family.rows.items():
            if (rva == f"0x{at:08X}" and old == old_name and family.respell(old) == new_name
                    and record(facts) == evidence):
                return True
    return False


def pin_respell_proven(old_name, new_name, rva):
    """Is `old_name` -> `new_name` at `rva` the pin of a family whose retail facts all hold? The
    same pin under its proven class, so no second name on the address."""
    for family in FAMILIES:
        got = family.pins.get(rva)
        if got and got[0] == old_name and family.respell(old_name) == new_name:
            return not facts_problems(family.facts())
    return False


if __name__ == "__main__":
    failed = False
    for each, problems, facts in [(f, facts_problems(f.facts()), f.facts()) for f in FAMILIES] + \
            [(e, extent_problems(e), e.facts) for e in EXTENTS]:
        print(f"{each.old} -> {each.new}: {len(facts)} facts, {len(problems)} problem(s)")
        for line in problems:
            print("  " + line)
        failed = failed or bool(problems)
    for entry in BASE_SLOTS:
        problems = base_slot_problems(entry)
        print(f"0x{entry.rva:08X} -> {entry.new}: {len(entry.tables)} tables, {len(entry.dead)} dead, "
              f"{len(base_slot_facts(entry))} facts, {len(problems)} problem(s)")
        for line in problems:
            print("  " + line)
        failed = failed or bool(problems)
    for entry in SHARED_SLOTS:
        problems = shared_slot_problems(entry)
        print(f"0x{entry.rva:08X} -> {entry.new}: {len(entry.tables)} tables, {len(shared_slot_facts(entry))} facts, "
              f"{len(problems)} problem(s)")
        for line in problems:
            print("  " + line)
        failed = failed or bool(problems)
    sys.exit(1 if failed else 0)
