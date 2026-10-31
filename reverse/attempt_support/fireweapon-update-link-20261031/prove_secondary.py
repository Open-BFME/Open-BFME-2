import csv, json, struct, sys
from pathlib import Path
sys.path.insert(0, "tools")
import build
ctor = "Code/GameEngine/Source/GameLogic/Object/Behavior/FireWeaponWhenDeadBehavior.cpp"
dtor = "Code/GameEngine/Source/Common/Rva00589079Derived.cpp"
owner = "Code/GameEngine/Source/Common/VslotSmallBodiesE.cpp"
name = "?update@FireWeaponWhenDeadBehavior@@UAE?AW4UpdateSleepTime@@XZ"
with Path("reverse/functions.csv").open(newline="") as f:
    row = next(r for r in csv.DictReader(f) if r["name"] == name)
symbols = build.load_symbol_map()
p = build.compile_function(row, symbols, build.obj_path(Path(owner)))
assert p["bytes"] == p["target"] and not p["unresolved"] and not p.get("masked")
table = "??_7FireWeaponWhenDeadBehavior@@6BUpdateModule@@@"
body, refs = build.read_object_symbol_bytes(build.obj_path(Path(ctor)), table)
native = [v - 0x400000 for v in struct.unpack("<3I", build.read_target_bytes(0x8496e8, 12))]
assert len(body) == 12 and len(refs) == 3
assert refs[0] == (0, 6, name) and symbols[name] == [native[0]]
assert refs[2][0:2] == (8, 6) and symbols[refs[2][2]] == [native[2]]
mask = {"name": refs[1][2], "target_rva": "0x004DF396", "target_size": "26", "source": ctor, "notes": ""}
p = build.compile_function(mask, symbols, build.obj_path(Path(ctor)))
assert p["bytes"] == p["target"] and not p["unresolved"] and not p.get("masked")
dtor_table = "??_7FireWeaponWhenDeadBehavior@@6BRva00482E96_S2@@@"
dbody, drefs = build.read_object_symbol_bytes(build.obj_path(Path(dtor)), dtor_table)
assert len(dbody) == 4 and drefs == [(0, 6, name)]
for source, symbol, rva, size, offset, target in [(ctor, "??0FireWeaponWhenDeadBehavior@@QAE@PAVThing@@PBVModuleData@@@Z", 0x482d80, 203, 69, table), (dtor, "??1FireWeaponWhenDeadBehavior@@UAE@XZ", 0x482e96, 39, 16, dtor_table)]:
    assert int.from_bytes(build.read_target_bytes(rva, size)[offset:offset+4], "little") == 0xc496e8
    _, relocations = build.read_object_symbol_bytes(build.obj_path(Path(source)), symbol, code_only=True)
    assert (offset, 6, target) in relocations
proof = {"native_table_rva": "0x008496E8", "native_slots": [hex(x) for x in native], "constructor_size": len(body), "constructor_relocations": refs, "update_exact_34": True, "mask_getter_exact_resolved_26": True, "wake_slot_existing_binding": True, "dtor_first_slot_corrected_without_alias": drefs, "scope_limit": "The destructor retains its pre-existing one-slot opaque secondary view. Its other two secondary slots are not recovered here; this proof does not claim full class-view unification."}
Path("build/fireweapon-update-link-20261031/final-secondary-proof.json").write_text(json.dumps(proof, indent=2) + "\n")
print("Native constructor Update table: all 3 slots verified; member34 and mask26 exact; destructor first-slot provider corrected without alias. Remaining opaque destructor secondary slots stay open.")
