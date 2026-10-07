"""Judge pin ownership in the proposed ledger, including removals and new rows."""
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import pin_admission


@pytest.fixture
def admission(monkeypatch):
    monkeypatch.setattr(pin_admission, "image_layout",
                        lambda: (0x6000, [(0x1000, 0x5000, True), (0x5000, 0x6000, False)]))
    monkeypatch.setattr(pin_admission.build, "gate_baselined", lambda check, row: False)
    return pin_admission


def pin(name, address="0x00003000"):
    return {"name": name, "address": address, "notes": "retail callsite"}


def row(name):
    return {"name": name, "export_rva": "", "target_rva": "0x00003000",
            "target_size": "3", "source": "Code/x.cpp", "status": "matched", "notes": ""}


PUBLIC = "?addNeighborlessEdges@W3DVolumetricShadow@@QAEXHPAUPolyNeighbor@@@Z"
PROTECTED = "?addNeighborlessEdges@W3DVolumetricShadow@@IAEXHPAUPolyNeighbor@@@Z"


def test_access_correction_replaces_sole_pin(admission):
    # Logged false reject at retail 0x000F17CA: the old public pin is removed.
    assert admission.judge([pin(PUBLIC)], [pin(PROTECTED)], [], []) == []


def test_owner_and_pin_can_be_renamed_together(admission):
    assert admission.judge([pin(PUBLIC)], [pin(PROTECTED)],
                           [row(PUBLIC)], [row(PROTECTED)]) == []


def test_pin_rename_cannot_leave_old_ledger_owner(admission):
    assert admission.judge([pin(PUBLIC)], [pin(PROTECTED)],
                           [row(PUBLIC)], [row(PUBLIC)])


def test_removing_one_pin_does_not_hide_a_surviving_owner(admission):
    assert admission.judge([pin(PUBLIC), pin("?Other@@YAXXZ")],
                           [pin(PROTECTED), pin("?Other@@YAXXZ")], [], [])


def test_new_ledger_owner_blocks_a_different_new_pin(admission):
    assert admission.judge([], [pin("?Wrong@@YAXXZ")], [], [row(PUBLIC)])


def test_new_pin_for_its_new_ledger_owner_passes(admission):
    assert admission.judge([], [pin(PUBLIC)], [], [row(PUBLIC)]) == []


def test_two_new_pin_names_cannot_share_an_address(admission):
    assert admission.judge([], [pin(PUBLIC), pin(PROTECTED)], [], [])


@pytest.mark.parametrize("address", ["0x00403000", "0x00005010", "0x00007000"])
def test_rename_still_checks_image_and_executable_bounds(admission, address):
    assert admission.judge([pin(PUBLIC)], [pin(PROTECTED, address)], [], [])
