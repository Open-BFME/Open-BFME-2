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
# to `value`), stride or offset (the instruction `code`, whose operand is `value`).
Fact = collections.namedtuple("Fact", "kind site value code", defaults=(None,))


def expected(fact):
    if fact.kind == "stores":
        return bytes.fromhex(fact.code) + struct.pack("<I", fact.value)
    if fact.kind in ("calls", "jumps"):
        opcode = b"\xe8" if fact.kind == "calls" else b"\xe9"
        return opcode + struct.pack("<i", fact.value - (fact.site + 5))
    if fact.kind in ("stride", "offset"):
        return bytes.fromhex(fact.code)
    raise ValueError(f"unknown retail fact {fact.kind!r}")


_verified = [None]        # the image data last held to the manifest: exe_image reads it once per process


def image_problem():
    """Why the image the build reads is not the one the manifest names, or None."""
    data = build.exe_image()[0]
    if _verified[0] is data:
        return None
    wanted = [entry.get("sha256") for entry in json.loads(build.MANIFEST.read_text(encoding="utf-8")).get("files", ())
              if entry.get("path") == "files/" + build.EXE.name]
    if len(wanted) != 1 or not wanted[0]:
        return f"{build.MANIFEST.name} names no one sha256 for {build.EXE.name}"
    got = hashlib.sha256(data).hexdigest()
    if got != wanted[0]:
        return f"{build.EXE.name} is sha256 {got}, not the manifest's {wanted[0]}"
    _verified[0] = data
    return None


def read_retail(rva, size):
    """Retail's bytes at `rva`, from the image the manifest names; tests replace this."""
    problem = image_problem()
    if problem:
        raise ValueError(problem)
    return build.read_target_bytes(rva, size)


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

    def __init__(self, old, new, table, copy, copy_store, owner, rows, pins):
        self.old, self.new, self.table, self.copy, self.copy_store = old, new, table, copy, copy_store
        self.owner, self.rows, self.pins = owner, rows, pins

    def respell(self, name):
        """`name` under the new class: its whole `V<old>@@` class fragments, and the head of its copy ctor."""
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
FAMILIES = (ENABLE_REGION_RECORD,)


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
    for each in FAMILIES:
        problems = facts_problems(each.facts())
        print(f"{each.old} -> {each.new}: {len(each.facts())} facts, {len(problems)} problem(s)")
        for line in problems:
            print("  " + line)
        sys.exit(1 if problems else 0)
