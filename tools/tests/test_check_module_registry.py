import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import check_module_registry as cmr  # noqa: E402


def test_data_class_convention():
    assert cmr.data_class("FlammableUpdate") == "FlammableUpdateModuleData"
    assert cmr.data_class("WeaponChangeSpecialPowerModule") == "WeaponChangeSpecialPowerModuleData"


def test_module_of_strips_data_suffix():
    assert cmr.module_of("ActiveBodyModuleData") == "ActiveBody"
    assert cmr.module_of("BeaconClientUpdate") == "BeaconClientUpdate"


def test_names_module_accepts_both_spellings():
    mods = {"BeaconClientUpdate"}
    assert cmr.names_module("BeaconClientUpdate", mods)
    assert cmr.names_module("BeaconClientUpdateModuleData", mods)
    assert cmr.names_module("WeaponChangeSpecialPowerModuleData", {"WeaponChangeSpecialPowerModule"})


def test_names_module_rejects_neighbour():
    assert not cmr.names_module("CleanupHazardUpdateModuleData", {"BeaconClientUpdate"})
    assert not cmr.names_module("SupplyTruckAIUpdateModuleData", {"ActiveBody", "HighlanderBody"})


def test_read_keys_ignores_comments(tmp_path):
    f = tmp_path / "keys.txt"
    f.write_text("# header\ndata 0x00000001 ?x # reason\n\ninstance 0x00000002 ?y\n")
    assert cmr.read_keys(f) == {"data 0x00000001 ?x", "instance 0x00000002 ?y"}


def test_objdump_keeps_embedded_opcodes_inside_instructions():
    instructions = cmr.parse_objdump_output("""
  401000: b8 e8 68 c3 00    mov eax,0xc368e8
  401005: 68 00 20 40 00    push 0x402000
  40100a: e8 f1 1f 00 00    call 0x403000
  40100f: ff 15 00 40 40 00 call DWORD PTR ds:0x404000
  401015: c2 04 00          ret 0x4
""")
    cmr.validate_instructions(instructions, 0x401000, 24)
    assert len(instructions) == 5
    assert [cmr.direct_call_target(ins) for ins in instructions] == [
        None, None, 0x403000, None, None]
    assert cmr.immediate_operand(instructions[1]) == 0x402000


@pytest.mark.parametrize("instructions,size", [
    ([], 1),
    ([cmr.Instruction(0x401001, 1, "ret", "")], 2),
    ([cmr.Instruction(0x401000, 1, "ret", "")], 2),
    ([cmr.Instruction(0x401000, 2, "ret", "")], 1),
    ([cmr.Instruction(0x401000, 1, ".byte", "0xe8")], 1),
])
def test_incomplete_disassembly_fails(instructions, size):
    with pytest.raises(ValueError, match="incomplete disassembly"):
        cmr.validate_instructions(instructions, 0x401000, size)


class RegistryImage:
    def candidate_callers(self, target):
        assert target == cmr.ADD_MODULE_RVA
        return [0x1001, 0x1014]  # First candidate is inside a mov immediate.

    def function_containing(self, rva):
        return 0x1000, 26

    def instructions(self, start):
        assert start == 0x1000
        return [
            cmr.Instruction(0x401000, 5, "mov", "eax,0xc368e8"),
            cmr.Instruction(0x401005, 5, "push", "0x600000"),
            cmr.Instruction(0x40100A, 5, "push", "0x402000"),
            cmr.Instruction(0x40100F, 5, "push", "0x403000"),
            cmr.Instruction(0x401014, 5, "call", hex(cmr.ADD_MODULE_RVA + cmr.IMAGE_BASE)),
            cmr.Instruction(0x401019, 1, "ret", ""),
        ]

    def string(self, va):
        return "PhysicsBehavior" if va == 0x600000 else None

    def is_code(self, va):
        return 0x401000 <= va < 0x500000


def test_registrations_require_instruction_boundaries(monkeypatch):
    monkeypatch.setattr(cmr, "EXPECTED_REGISTRATIONS", 1)
    assert cmr.decode_registrations(RegistryImage()) == [("PhysicsBehavior", 0x2000, 0x3000)]


def test_registration_count_mismatch_fails():
    with pytest.raises(SystemExit, match="decoder no longer fits retail"):
        cmr.decode_registrations(RegistryImage())


def test_factory_skips_helpers_and_stops_at_ret(monkeypatch):
    img = RegistryImage()
    monkeypatch.setattr(img, "instructions", lambda start: [
        cmr.Instruction(0x401000, 5, "mov", "eax,0xc368e8"),
        cmr.Instruction(0x401005, 5, "call", "0x402000"),
        cmr.Instruction(0x40100A, 5, "call", "0x403000"),
        cmr.Instruction(0x40100F, 5, "push", "0x404000"),
        cmr.Instruction(0x401014, 3, "ret", "0x4"),
        cmr.Instruction(0x401017, 5, "call", "0x405000"),
    ])
    assert cmr.factory_callees(img, 0x1000, {0x2000}) == (0x3000, 0x4000)


def test_wrong_factory_alias_cannot_legitimize_a_ctor(monkeypatch):
    monkeypatch.setattr(cmr, "Image", RegistryImage)
    monkeypatch.setattr(cmr, "EXPECTED_REGISTRATIONS", 1)
    monkeypatch.setattr(cmr, "factory_callees", lambda *args: (0x4000, None))
    monkeypatch.setattr(cmr, "load_names", lambda: {
        0x2000: ["?friend_newModuleData@DumbProjectileBehaviorModuleData@@",
                 "?friend_newModuleData@PhysicsBehaviorModuleData@@"],
        0x4000: ["??0DumbProjectileBehaviorModuleData@@QAE@XZ"],
    })
    violations, count = cmr.scan()
    assert count == 1
    assert {v[0] for v in violations} == {"data", "ctor"}


def test_verified_shared_ctor_accepts_both_classes(monkeypatch):
    monkeypatch.setattr(cmr, "Image", RegistryImage)
    monkeypatch.setattr(cmr, "decode_registrations", lambda img: [
        ("PhysicsBehavior", 0x2000, 0x3000), ("ActiveBody", 0x2100, 0x3100)])
    monkeypatch.setattr(cmr, "factory_callees", lambda *args: (0x4000, None))
    monkeypatch.setattr(cmr, "load_names", lambda: {
        0x2000: ["?friend_newModuleData@PhysicsBehaviorModuleData@@"],
        0x2100: ["?friend_newModuleData@ActiveBodyModuleData@@"],
        0x4000: ["??0ActiveBodyModuleData@@QAE@XZ"],
    })
    assert cmr.scan() == ([], 2)
