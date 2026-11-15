"""Changed vtable slots may not introduce names absent from code/pins/export aliases."""
import hashlib
import os
from pathlib import Path
import struct
import subprocess
import sys

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import link_batch_audit as A
import link_cycle

VT = "??_7Rva003560ED@@6B@"
ONE = "?vslot01@Rva00355D66@@UAEXH@Z"
FIVE = "?vslot05@Rva00355D66@@UAE_NXZ"


def object_file(path, refs=(ONE, FIVE), own=(), prefix=0, adjacent=False):
    """Real COFF, two missing B4 slot targets; optional RTTI prefix/adjacent data."""
    symbols = [(VT, 1, prefix, 2)] + [(n, 2 if n in own else 0, 0, 2) for n in refs]
    rels = [(prefix + i * 4, name, 6) for i, name in enumerate(refs)]
    body = b"\0" * (prefix + 4 * len(refs))
    if prefix:
        symbols.append(("??_R4Locator", 0, 0, 2))
        rels.append((0, "??_R4Locator", 6))
    if adjacent:
        symbols += [("next_global", 1, len(body), 2), ("unrelated_missing", 0, 0, 2)]
        rels.append((len(body), "unrelated_missing", 6))
        body += b"\0" * 4
    sections = [(".rdata", 0x40301040, body, 2), (".text", 0x60500020, b"\xc3", 0)]
    link_cycle.write_coff(path, sections, symbols, {1: rels})
    return path


def saved_index(touches=(), defined=()):
    return dict(objects=["unit.obj"], touches={"unit.obj": set(touches)},
                strong={n: [0] for n in defined}, comdat={}, common={},
                meta={"commit": "base"})


def test_b4_positive_control_flags_exactly_vslot01_and_vslot05(tmp_path):
    p = object_file(tmp_path / "unit.obj")
    assert A.new_vtable_targets(p, set()) == [(VT, 0, ONE), (VT, 1, FIVE)]


def test_clean_object_with_defined_and_registered_slots(tmp_path):
    p = object_file(tmp_path / "unit.obj", own=(ONE,))
    assert A.new_vtable_targets(p, {FIVE}) == []


def test_existing_unresolved_target_is_not_new(tmp_path):
    p = object_file(tmp_path / "unit.obj")
    assert A.new_vtable_targets(p, set(), {ONE}) == [(VT, 1, FIVE)]


def test_rtti_prefix_and_neighbouring_relocations_are_outside_table(tmp_path):
    p = object_file(tmp_path / "unit.obj", prefix=4, adjacent=True)
    assert {t[2] for t in A.new_vtable_targets(p, set())} == {ONE, FIVE}


@pytest.mark.parametrize("damage", [
    lambda b: b[:12],
    lambda b: b[:-8],
    lambda b: b[:8] + struct.pack("<I", len(b) + 100) + b[12:],
    lambda b: b[:52] + b"\xff\xff" + b[54:],
])
def test_malformed_coff_is_not_clean(tmp_path, damage):
    p = object_file(tmp_path / "unit.obj")
    p.write_bytes(damage(p.read_bytes()))
    with pytest.raises((ValueError, OSError)):
        A.new_vtable_targets(p, set())


def test_audit_refuses_new_slots_even_without_old_linked_status(tmp_path, monkeypatch, capsys):
    p = object_file(tmp_path / "unit.obj")
    ix = saved_index()
    ix["blockers"] = {"Code/unit.cpp": {"object": "unit.obj", "linked": False}}
    monkeypatch.setattr(A, "registered_slot_targets", lambda ref: set())
    assert A.audit_vtable_targets(ix, [p], "tip", True) == 1
    out = capsys.readouterr().out
    assert ONE in out and FIVE in out


def test_audit_retains_old_debt_but_does_not_hide_removed_provider(tmp_path, monkeypatch):
    p = object_file(tmp_path / "unit.obj")
    monkeypatch.setattr(A, "registered_slot_targets", lambda ref: set())
    assert A.audit_vtable_targets(saved_index((ONE, FIVE)), [p], "tip", True) == 0
    # ONE was defined, not unresolved, before: removing its body makes a new defect.
    assert A.audit_vtable_targets(saved_index((ONE, FIVE), (ONE,)), [p], "tip", True) == 1


def test_audit_pin_removal_cannot_hide_behind_old_debt(tmp_path, monkeypatch):
    p = object_file(tmp_path / "unit.obj")
    monkeypatch.setattr(A, "registered_slot_targets", lambda ref: {ONE} if ref == "base" else set())
    assert A.audit_vtable_targets(saved_index((ONE, FIVE)), [p], "tip", True) == 1


def test_stale_or_missing_before_proof_is_inconclusive(tmp_path, monkeypatch):
    p = object_file(tmp_path / "unit.obj")
    monkeypatch.setattr(A, "registered_slot_targets", lambda ref: set())
    assert A.audit_vtable_targets(saved_index(), [p], "tip", False) == 2
    ix = saved_index()
    ix["touches"] = {}
    assert A.audit_vtable_targets(ix, [p], "tip", True) == 2


def test_new_object_has_no_old_unresolved_debt(tmp_path, monkeypatch):
    p = object_file(tmp_path / "new.obj")
    monkeypatch.setattr(A, "registered_slot_targets", lambda ref: set())
    assert A.audit_vtable_targets(saved_index(), [p], "tip", True) == 1


def test_registry_failure_and_malformed_object_are_inconclusive(tmp_path, monkeypatch):
    p = tmp_path / "bad.obj"
    p.write_bytes(b"bad")
    monkeypatch.setattr(A, "registered_slot_targets", lambda ref: set())
    assert A.audit_vtable_targets(saved_index(), [p], "tip", True) == 2
    monkeypatch.setattr(A, "registered_slot_targets", lambda ref: (_ for _ in ()).throw(ValueError("missing")))
    assert A.audit_vtable_targets(saved_index(), [], "tip", True) == 2


def test_immutable_registry_accepts_matched_rows_pins_and_both_alias_names(tmp_path, monkeypatch):
    def git(*args):
        return subprocess.run(["git", *args], cwd=tmp_path, check=True, capture_output=True, text=True).stdout
    git("init", "-q")
    rev = tmp_path / "reverse"
    rev.mkdir()
    (rev / "functions.csv").write_text("name,status,notes\nrow,matched,object-symbol=real\nnot_matched,unmatched,\n")
    (rev / "symbols.csv").write_text("name,address,notes\npin,0x100,legacy note,with extra comma\n")
    (rev / "export_aliases.csv").write_text("export,target,notes\nalias,target,\n")
    git("add", "reverse")
    git("-c", "user.name=t", "-c", "user.email=t@t", "commit", "-qm", "fixtures")
    monkeypatch.setattr(A.link_check, "ROOT", tmp_path)
    known = A.registered_slot_targets("HEAD")
    assert {"row", "real", "pin", "alias", "target", "__purecall"} <= known
    assert "not_matched" not in known
    (rev / "symbols.csv").write_text("bad_header\n")
    assert A.registered_slot_targets("HEAD") == known
    with pytest.raises(ValueError):
        A.registered_slot_targets("missing-ref")


def test_retained_b4c_objects_exact_two_new_targets():
    value = os.environ.get("BFME_VT_B4_EVIDENCE")
    if not value:
        pytest.skip("set BFME_VT_B4_EVIDENCE to retained B4c evidence (no compilation)")
    root = Path(value)
    before, after = root / "before/00011.obj", root / "after/00011.obj"
    assert hashlib.sha256(before.read_bytes()).hexdigest() == "4fa2d0511877f629f96e80115c64a38907887915976443303c5efa25370a360c"
    assert hashlib.sha256(after.read_bytes()).hexdigest() == "b0e31c12a61d71da03515f3828c51d84ddc397a7da5e298f0e3ebdeda33dfb73"
    old = A.registered_slot_targets("565145b59d49b629743b89e34b042be7bc332671")
    new = A.registered_slot_targets("566fffdaeef4aa246e8259c3ca331e1297f5fdde")
    previous = {s[2] for s in A.new_vtable_targets(before, old)}
    assert A.new_vtable_targets(after, new, previous) == [(VT, 1, ONE), (VT, 5, FIVE)]
    assert A.new_vtable_targets(before, old, previous) == []  # clean unchanged-debt control



def test_standard_batch_audit_calls_slot_check_for_unlinked_changed_unit(tmp_path, monkeypatch):
    p = object_file(tmp_path / "unit.obj")
    marker = tmp_path / "index.pkl"
    marker.touch()
    ix = saved_index()
    ix["meta"]["clean_tree"] = True
    ix["blockers"] = {"Code/unit.cpp": {"object": "unit.obj", "linked": False}}
    monkeypatch.setattr(A, "git", lambda *args: "")
    monkeypatch.setattr(A, "changed_sources", lambda *args: {"Code/unit.cpp"})
    monkeypatch.setattr(A, "changed_identities", lambda *args: set())
    monkeypatch.setattr(A.link_check, "INDEX", marker)
    monkeypatch.setattr(A.link_check, "load_index", lambda: ix)
    monkeypatch.setattr(A.link_check, "require_common_index", lambda *args: None)
    monkeypatch.setattr(A.link_census, "ledger", lambda: [{"source": "Code/unit.cpp"}])
    monkeypatch.setattr(A.link_census, "data_ledger", lambda: [])
    monkeypatch.setattr(A.link_census, "RetailTruth", lambda rows: None)
    monkeypatch.setattr(A.build, "obj_path", lambda source: p)
    monkeypatch.setattr(A.link_census, "object_current", lambda *args: True)
    monkeypatch.setattr(A, "omitted_references", lambda *args: [])
    monkeypatch.setattr(A, "registered_slot_targets", lambda ref: set())
    assert A.audit("base", "tip", ["Code/unit.cpp"]) == 1
