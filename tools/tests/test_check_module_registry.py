import sys
from pathlib import Path

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
