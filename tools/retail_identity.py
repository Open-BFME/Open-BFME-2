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
# vftable: `site` is the word, `value` the VA it holds, `code` (table VA, index, slot count); build it with slot()).
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
    if fact.kind in ("stride", "offset"):
        return bytes.fromhex(fact.code)
    if fact.kind == "slot":
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
    return f"{fact.value}" if fact.kind in ("stride", "offset") else f"0x{fact.value:08X}"


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
    hold, the check the rebuilt copy's table store is for a Family. `copy` is the row the plan is keyed on."""

    def __init__(self, old, new, copy, spellings, element, old_element, old_members, members, member_facts, bindings,
                 rows, pins, retired=None):
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
FAMILIES = (ENABLE_REGION_RECORD, HERO_RECORD_SET, LOCOMOTOR)

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
    sys.exit(1 if failed else 0)
