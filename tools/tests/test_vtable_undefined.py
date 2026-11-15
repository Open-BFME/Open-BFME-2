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
                meta={"commit": "base"}, digests={"unit.obj": "before-digest"},
                references={"objects": {"unit.obj": {"digest": "before-digest", "weaks": ()}}})


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



# Sol r1: no name-only COFF bindings or guessed before-state weak resolution.
def test_r1_before_resolved_weak_must_not_become_old_debt(tmp_path, monkeypatch):
    p = object_file(tmp_path / "unit.obj", refs=("W",))
    ix = saved_index(("W", "D"), ("D",))
    ix["references"]["objects"]["unit.obj"]["weaks"] = (("W", "D"),)
    monkeypatch.setattr(A, "registered_slot_targets", lambda ref: set())
    assert A.audit_vtable_targets(ix, [p], "tip", True) == 1


@pytest.mark.parametrize("damage", [
    lambda ix: ix["references"].clear(),
    lambda ix: ix["references"]["objects"]["unit.obj"].update(digest="other"),
    lambda ix: ix["references"]["objects"]["unit.obj"].pop("weaks"),
])
def test_r1_old_debt_needs_digest_bound_weak_provenance(tmp_path, monkeypatch, damage):
    p = object_file(tmp_path / "unit.obj", refs=("W",))
    ix = saved_index(("W",))
    damage(ix)
    monkeypatch.setattr(A, "registered_slot_targets", lambda ref: set())
    assert A.audit_vtable_targets(ix, [p], "tip", True) == 2


def test_r1_unproven_weak_default_is_not_silently_old_debt(tmp_path, monkeypatch):
    p = object_file(tmp_path / "unit.obj", refs=("W",))
    ix = saved_index(("W", "D"))
    ix["references"]["objects"]["unit.obj"]["weaks"] = (("W", "D"),)
    monkeypatch.setattr(A, "registered_slot_targets", lambda ref: set())
    assert A.audit_vtable_targets(ix, [p], "tip", True) == 2


def test_r1_static_same_spelling_does_not_resolve_an_external(tmp_path):
    p = tmp_path / "unit.obj"
    # Last W is the external relocation target; first W is a distinct local.
    link_cycle.write_coff(p, [(".rdata", 0x40301040, b"\0" * 4, 2),
                             (".text", 0x60500020, b"\xc3", 0)],
                          [(VT, 1, 0, 2), ("W", 2, 0, 3), ("W", 0, 0, 2)], {1: [(0, "W", 6)]})
    assert A.new_vtable_targets(p, set()) == [(VT, 0, "W")]


def test_r1_actual_static_symbol_target_is_defined(tmp_path):
    p = tmp_path / "unit.obj"
    link_cycle.write_coff(p, [(".rdata", 0x40301040, b"\0" * 4, 2),
                             (".text", 0x60500020, b"\xc3", 0)],
                          [(VT, 1, 0, 2), ("W", 2, 0, 3)], {1: [(0, "W", 6)]})
    assert A.new_vtable_targets(p, set()) == []


def test_r1_static_neighbour_bounds_the_table(tmp_path):
    p = tmp_path / "unit.obj"
    link_cycle.write_coff(p, [(".rdata", 0x40301040, b"\0" * 8, 2)],
                          [(VT, 1, 0, 2), ("next", 1, 4, 3),
                           ("W", 0, 0, 2), ("unrelated", 0, 0, 2)],
                          {1: [(0, "W", 6), (4, "unrelated", 6)]})
    assert A.new_vtable_targets(p, set()) == [(VT, 0, "W")]


@pytest.mark.parametrize("damage", ["section", "relocation"])
def test_r1_invalid_sections_or_relocation_bounds_are_inconclusive(tmp_path, monkeypatch, damage):
    p = object_file(tmp_path / "unit.obj")
    raw = bytearray(p.read_bytes())
    sections, symbols = link_cycle.parse_coff(raw)
    if damage == "section":
        table = next(y for y in symbols.values() if y.name == VT)
        symptr = struct.unpack_from("<I", raw, 8)[0]
        struct.pack_into("<h", raw, symptr + table.i * 18 + 12, 3)
    else:
        relptr = struct.unpack_from("<I", raw, 20 + 24)[0]
        struct.pack_into("<I", raw, relptr, sections[0].size)
    p.write_bytes(raw)
    monkeypatch.setattr(A, "registered_slot_targets", lambda ref: set())
    assert A.audit_vtable_targets(saved_index(), [p], "tip", True) == 2


def test_r1_current_weak_default_resolves_to_actual_object_definition(tmp_path):
    p = tmp_path / "unit.obj"
    link_cycle.write_coff(p, [(".rdata", 0x40301040, b"\0" * 4, 2),
                             (".text", 0x60500020, b"\xc3", 0)],
                          [(VT, 1, 0, 2), ("D", 2, 0, 2), ("W", 0, 0, 2)], {1: [(0, "W", 6)]})
    raw = bytearray(p.read_bytes())
    _, syms = link_cycle.parse_coff(raw)
    wi = next(y.i for y in syms.values() if y.name == "W")
    di = next(y.i for y in syms.values() if y.name == "D")
    symptr, count = struct.unpack_from("<II", raw, 8)
    record = symptr + wi * 18
    raw[record + 16:record + 18] = bytes((105, 1))
    raw[record + 18:record + 18] = struct.pack("<II", di, 3) + b"\0" * 10
    struct.pack_into("<I", raw, 12, count + 1)
    p.write_bytes(raw)
    assert A.new_vtable_targets(p, set()) == []



def alias_object(path, directive, weak=False, target_storage=2):
    sections = [(".rdata", 0x40301040, b"\0" * 4, 2),
                (".text", 0x60500020, b"\xc3", 0),
                (".drectve", 0x00100a00, directive.encode("ascii"), 0)]
    symbols = [(VT, 1, 0, 2), ("R", 2, 0, target_storage)]
    if weak:
        symbols.append(("D", 0, 0, 2))
    symbols.append(("W", 0, 0, 2))
    link_cycle.write_coff(path, sections, symbols, {1: [(0, "W", 6)]})
    if weak:
        raw = bytearray(path.read_bytes())
        _, syms = link_cycle.parse_coff(raw)
        wi = next(y.i for y in syms.values() if y.name == "W")
        di = next(y.i for y in syms.values() if y.name == "D")
        symptr, count = struct.unpack_from("<II", raw, 8)
        record = symptr + wi * 18
        raw[record + 16:record + 18] = bytes((105, 1))
        raw[record + 18:record + 18] = struct.pack("<II", di, 3) + b"\0" * 10
        struct.pack_into("<I", raw, 12, count + 1)
        path.write_bytes(raw)
    return path


@pytest.mark.parametrize("weak", [False, True])
def test_r2_unchanged_alias_chain_is_clean(tmp_path, monkeypatch, weak):
    # Both ordinary W -> R and weak W -> D -> R are already resolved.
    source = "D" if weak else "W"
    p = alias_object(tmp_path / "unit.obj", f" /alternatename:{source}=R ", weak)
    ix = saved_index(("W", "D", "R"), ("R",))
    ix["alternates"] = {source: [(0, "R")]}
    ix["references"]["objects"]["unit.obj"]["weaks"] = (("W", "D"),) if weak else ()
    monkeypatch.setattr(A, "registered_slot_targets", lambda ref: set())
    assert A.new_vtable_targets(p, set()) == []
    assert A.audit_vtable_targets(ix, [p], "tip", True) == 0


@pytest.mark.parametrize("directive", [
    " /alternatename:W=A /alternatename:A=W ",             # cycle
    " /alternatename:W=A /alternatename:A=missing ",       # dangling chain
])
def test_r2_unresolved_alias_chains_still_flag_slot(tmp_path, directive):
    p = alias_object(tmp_path / "unit.obj", directive)
    assert A.new_vtable_targets(p, set()) == [(VT, 0, "W")]


def test_r2_alias_name_cannot_bind_an_unrelated_static(tmp_path):
    p = alias_object(tmp_path / "unit.obj", " /alternatename:W=R ", target_storage=3)
    assert A.new_vtable_targets(p, set()) == [(VT, 0, "W")]


def test_r2_alias_can_reach_a_registered_name_without_an_object_symbol(tmp_path):
    p = alias_object(tmp_path / "unit.obj", " /alternatename:W=registered ")
    assert A.new_vtable_targets(p, {"registered"}) == []


def test_r2_weak_alias_chain_with_missing_fallback_still_flags(tmp_path):
    p = alias_object(tmp_path / "unit.obj", " /alternatename:D=missing ", weak=True)
    assert A.new_vtable_targets(p, set()) == [(VT, 0, "W")]



@pytest.mark.parametrize("aliased", [False, True])
@pytest.mark.parametrize("bss", [False, True])
def test_r3_missing_initialized_data_is_inconclusive_but_bss_is_valid(tmp_path, monkeypatch, aliased, bss):
    if aliased:
        p = alias_object(tmp_path / "unit.obj", " /alternatename:W=R ")
    else:
        p = object_file(tmp_path / "unit.obj", refs=("W",), own=("W",))
    raw = bytearray(p.read_bytes())
    header = 20 + 40                          # the target's .text section
    struct.pack_into("<I", raw, header + 20, 0)
    if bss:
        raw[header:header + 8] = b".bss\0\0\0\0"
        struct.pack_into("<I", raw, header + 36, 0xc0000080)
    p.write_bytes(raw)
    monkeypatch.setattr(A, "registered_slot_targets", lambda ref: set())
    assert A.audit_vtable_targets(saved_index(), [p], "tip", True) == (0 if bss else 2)


@pytest.mark.parametrize("search", [0, 1, 2, 3, 4, 0xffffffff])
def test_r3_weak_search_characteristic_requires_modeled_semantics(tmp_path, monkeypatch, search):
    # No /alternatename: weak W defaults directly to the object-defined R.
    p = alias_object(tmp_path / "unit.obj", "", weak=True)
    raw = bytearray(p.read_bytes())
    symptr = struct.unpack_from("<I", raw, 8)[0]
    _, syms = link_cycle.parse_coff(raw)
    wi = next(y.i for y in syms.values() if y.name == "W")
    ri = next(y.i for y in syms.values() if y.name == "R")
    struct.pack_into("<II", raw, symptr + wi * 18 + 18, ri, search)
    p.write_bytes(raw)
    monkeypatch.setattr(A, "registered_slot_targets", lambda ref: set())
    assert A.audit_vtable_targets(saved_index(), [p], "tip", True) == (0 if search in (1, 2, 3) else 2)
