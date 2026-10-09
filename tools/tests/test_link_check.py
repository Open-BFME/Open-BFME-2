"""link_check: the per-file LINKED preview agrees with link.exe's rules.

Ported from Open-BFME-1's tools/tests/test_link_check.py; its link-queue
tests (next/publish/serve) have no counterpart here."""
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import link_check as C  # noqa: E402


def index(strong=None, comdat=None, blockers=None, sizes=None):
    return {"meta": {"date": "d", "commit": "c"}, "objects": ["a.obj", "b.obj", "c.obj"],
            "strong": strong or {}, "comdat": comdat or {}, "blockers": blockers or {}, "bytes": sizes or {},
            "common_schema": C.COMMON_SCHEMA, "common": {}, "alternates": {}}


def test_two_inline_copies_fold_silently():
    ix = index(comdat={"f": [(0, "x", None), (1, "y", None)]})
    assert not C.duplicate("f", 2, False, None, ix)


def test_exclusive_definition_collides_with_the_first_definition():
    ix = index(strong={"f": [0]}, comdat={"f": [(0, "x", None)]})
    assert C.duplicate("f", 2, False, None, ix)   # an inline copy after an exclusive first one
    assert C.duplicate("f", 2, True, None, ix)
    ix = index(comdat={"f": [(0, "x", None)]})
    assert C.duplicate("f", 2, True, None, ix)    # an exclusive definition after an inline first one
    assert not C.duplicate("f", 0, False, 0, ix)  # its own old copy is not a second definition


def test_first_definition_is_charged_when_a_later_one_is_exclusive():
    ix = index(strong={"f": [2]}, comdat={"f": [(2, "x", None)]})
    assert C.duplicate("f", 0, False, None, ix)


def test_stale_object_is_never_evidence(tmp_path, monkeypatch):
    """A source edited after its object was compiled: link_census.object_current
    says no (with or without a dependency record) and link_check refuses it.
    Here an object with no dependency record must at least be newer than its
    source (this repository's object_current)."""
    import json
    import os
    import link_census
    source, obj = tmp_path / "f.cpp", tmp_path / "f.obj"
    obj.write_bytes(b"old object")
    source.write_text("int f() { return 2; }\n")
    os.utime(obj, (1_000_000, 1_000_000))
    assert not link_census.object_current(source, obj)  # no sidecar: older than its source
    os.utime(obj, None)
    monkeypatch.setattr(link_census.build, "compiler_command", lambda s, o: (["cl"], {}))
    monkeypatch.setattr(link_census.build, "_cmd_fingerprint", lambda command, env: "cmd")
    sidecar = link_census.build._deps_sidecar(obj)
    sidecar.write_text(json.dumps({"source": link_census.build._hash_file(str(source)), "deps": {}, "cmd": "cmd"}))
    assert link_census.object_current(source, obj)
    source.write_text("int f() { return 3; }\n")  # edited after the compile
    assert not link_census.object_current(source, obj)
    monkeypatch.setattr(C, "ROOT", tmp_path)
    ix = index(blockers={"f.cpp": {"object": "f.obj", "linked": True, "unresolved": [], "duplicates": [],
                                   "losers": [], "addresses": 0}})
    import pytest
    with pytest.raises(SystemExit, match="not current"):
        C.resolve(str(obj), ix)


def test_a_missing_object_is_never_an_empty_clean_one(tmp_path):
    # falsifier from the 2026-09-29 linking audit: object_facts turned a read failure into empty
    # facts, and link_check reported LINKS for an object that does not exist
    import pytest
    import link_census
    missing = tmp_path / "does_not_exist.obj"
    with pytest.raises(link_census.MissingObject):
        link_census.object_facts(missing)
    ix = {**index(), "objects": [], "selection": {"exceptions": {}, "owners": {}},
          "excuses": {"runtime": set(), "imported": {}, "stubs": {}}}
    with pytest.raises(link_census.MissingObject):
        C.check_object(missing, ix, None)
    with pytest.raises(SystemExit):
        C.resolve(str(missing), ix)


def test_refresh_replaces_a_passed_objects_census_definitions(monkeypatch):
    """A duplicate removed from b.obj since the census no longer charges a.obj."""
    import link_census
    from types import SimpleNamespace
    ix = index(strong={"f": [0, 1], "g": [1]}, comdat={"h": [(1, "x", None)]})
    assert C.duplicate("f", 0, True, 0, ix)
    monkeypatch.setattr(link_census, "object_facts", lambda obj, truth: ([], ["g"], [], []))
    monkeypatch.setattr(link_census, "common_definitions", lambda obj: {})
    monkeypatch.setattr(C, "alternate_names", lambda obj: {})
    C.refresh(ix, [SimpleNamespace(name="b.obj"), SimpleNamespace(name="new.obj")], None)
    assert ix["strong"] == {"f": [0], "g": [1]} and ix["comdat"] == {"h": []}
    assert not C.duplicate("f", 0, True, 0, ix)


def _preview(monkeypatch, tmp_path, names):
    import link_census
    ix = index(blockers={"a.cpp": {"object": "a.obj", "linked": False, "unresolved": [], "duplicates": [],
                                   "losers": [], "addresses": 0}}, sizes={"a.cpp": 100})
    monkeypatch.setattr(C, "load_index", lambda: ix)
    monkeypatch.setattr(C, "resolve", lambda path, _: (path.replace(".obj", ".cpp"), tmp_path / path))
    monkeypatch.setattr(link_census, "ledger", lambda: None)
    monkeypatch.setattr(link_census, "RetailTruth", lambda _: None)
    monkeypatch.setattr(C, "refresh", lambda *a: None)
    monkeypatch.setattr(C, "source_bytes", lambda sources: {s: 100 for s in sources})
    monkeypatch.setattr(C, "check_object", lambda *a: {k: [] for k in
                        ("unresolved", "duplicates", "comdat", "addresses", "selected")})
    return C.main(names)


def test_a_file_named_twice_counts_once(monkeypatch, tmp_path, capsys):
    assert _preview(monkeypatch, tmp_path, ["a.obj", "a.obj"]) == 0
    assert "1 of 1 link cleanly; LINKED 0 -> 100 bytes" in capsys.readouterr().out


def test_an_object_outside_the_census_is_refused(monkeypatch, tmp_path):
    import pytest
    with pytest.raises(SystemExit, match="not in census c.*new.cpp"):
        _preview(monkeypatch, tmp_path, ["a.obj", "new.obj"])


def test_staged_and_census_blockers_read_the_census(monkeypatch):
    blockers = {"a.cpp": {"object": "a.obj", "linked": False, "unresolved": ["u"], "duplicates": [], "losers": ["l"],
                          "addresses": 2, "wrong_selected": ["s"]}}
    monkeypatch.setattr(C, "load_index", lambda: index(blockers=blockers))
    assert C.census_blockers() == blockers
    import link_rank
    import class_views
    found, _ = link_rank.blockers()
    assert found == {"a.cpp": {("U", "u"), ("L", "l"), ("S", "s"), ("A", "")}}
    assert class_views.census_blockers() == {"a.cpp": {"u", "l", "s"}}


# The optional mode builds transient tables, never a replacement census.
import copy
import time
import pytest
import link_census


@pytest.fixture
def current_preview(monkeypatch, tmp_path):
    old = {**index(), "selection": {"exceptions": {}, "owners": {}},
           "excuses": {"runtime": set(), "imported": {}, "stubs": {}}}
    present, facts, source_map = [], {}, {}
    clock = {"inputs": "fixed", "tools": "fixed"}
    calls = {"data": 0}

    def add(name, fact=([], [], [], []), *, source=True):
        obj = tmp_path / name
        obj.write_bytes(b"current object")
        present.append(obj)
        facts[obj] = fact
        if source:
            src = tmp_path / name.replace(".obj", ".cpp")
            src.write_text("// current compiler fixture\n")
            source_map[obj] = src
        return obj

    def state(objects, rows):
        return {**clock, "objects": link_census.object_stamps(objects)}

    def data_proof():
        calls["data"] += 1

    monkeypatch.setattr(C, "ROOT", tmp_path)
    monkeypatch.setattr(C, "preview_state", state)
    monkeypatch.setattr(link_census, "objects", lambda rows: (list(present), []))
    monkeypatch.setattr(link_census, "_object_sources", lambda rows: dict(source_map))
    monkeypatch.setattr(link_census, "stale_objects", lambda objects, sources: [])
    monkeypatch.setattr(link_census, "verify_data_objects", data_proof)
    monkeypatch.setattr(link_census, "RetailTruth", lambda rows: None)
    monkeypatch.setattr(link_census, "read_facts", lambda objects, rows: [facts[obj] for obj in objects])
    monkeypatch.setattr(link_census, "object_facts", lambda obj, truth: facts[obj])
    monkeypatch.setattr(link_census, "common_definitions", lambda obj: {})
    monkeypatch.setattr(C, "alternate_names", lambda obj: {})
    monkeypatch.setattr(link_census, "ledger_owners", lambda rows: {"owned": {"owner.obj"}})
    monkeypatch.setattr(link_census, "library_symbols", lambda path: set())
    monkeypatch.setattr(link_census, "retail_imports", lambda: {})
    monkeypatch.setattr(link_census, "import_stubs", lambda: {})
    monkeypatch.setattr(C, "source_bytes", lambda sources: {source: 13 for source in sources})
    # A bounded preview must not compile or publish any recorded tables/status.
    def forbidden(*args, **kwargs):
        pytest.fail("current preview must not compile or publish a census")
    monkeypatch.setattr(C, "write_index", forbidden)
    monkeypatch.setattr(link_census, "record", forbidden)
    monkeypatch.setattr(C.build, "compile_rows", forbidden)
    run = lambda paths: C.check_current_ledger(old, paths, [], time.time())
    return old, add, run, clock, calls, present


def test_current_new_unit_has_complete_preview_without_writing_census(current_preview, capsys):
    old, add, run, _, calls, _ = current_preview
    new = add("new.obj", ([], ["getter"], [], []))
    prior = copy.deepcopy(old)
    assert run([str(new), str(new)]) == 0
    assert old == prior
    assert calls["data"] == 1
    output = capsys.readouterr().out
    assert "transient current-ledger preview" in output
    assert "census record unchanged" in output
    assert "1 of 1 link cleanly" in output


def test_current_two_new_strong_providers_collide(current_preview, capsys):
    _, add, run, _, _, _ = current_preview
    first = add("first-new.obj", ([], ["same"], [], []))
    second = add("second-new.obj", ([], ["same"], [], []))
    assert run([str(first), str(second)]) == 1
    assert capsys.readouterr().out.count("duplicate   same") == 2


def test_current_order_keeps_first_copy_not_majority(current_preview, capsys):
    old, add, run, _, _, _ = current_preview
    old["objects"] = ["old.obj"]
    old["comdat"] = {"f": [(0, "old", None)]}
    add("earlier-new.obj", ([("f", "new", 5, None)], [], [], []))
    old_copy = add("old.obj", ([("f", "old", 5, None)], [], [], []))
    add("later.obj", ([("f", "old", 5, None)], [], [], []))
    assert run([str(old_copy)]) == 1
    assert "comdat      f" in capsys.readouterr().out


def test_current_removed_provider_is_not_reused_from_census(current_preview, capsys):
    old, add, run, _, _, _ = current_preview
    old["strong"] = {"removed": [0]}
    caller = add("new.obj", ([], [], ["removed"], []))
    assert run([str(caller)]) == 1
    assert "unresolved  removed" in capsys.readouterr().out


def test_current_rereads_already_compiled_providers(current_preview, capsys):
    old, add, run, _, _, _ = current_preview
    old["strong"] = {"gone": [0]}
    add("a.obj")  # current cache already lacks the definition; no compile is needed
    caller = add("new.obj", ([], [], ["gone"], []))
    assert run([str(caller)]) == 1
    assert "unresolved  gone" in capsys.readouterr().out


def test_current_includes_data_only_and_library_providers(current_preview, monkeypatch):
    _, add, run, _, calls, _ = current_preview
    add("data.obj", ([], ["datum"], [], []))
    add("archive-member.obj", ([], ["library_call"], [], []), source=False)
    caller = add("new.obj", ([], [], ["datum", "library_call"], []))
    assert run([str(caller)]) == 0
    assert calls["data"] == 1


def test_current_data_proof_refusal_is_not_ignored(current_preview, monkeypatch):
    _, add, run, _, _, _ = current_preview
    obj = add("new.obj")
    def refuse():
        raise SystemExit("data provider bytes are wrong")
    monkeypatch.setattr(link_census, "verify_data_objects", refuse)
    with pytest.raises(SystemExit, match="data provider bytes"):
        run([str(obj)])


def test_current_owners_still_charge_wrong_selected(current_preview, capsys):
    _, add, run, _, _, _ = current_preview
    add("earlier.obj", ([("owned", "wrong", 3, None)], [], [], []))
    add("owner.obj", ([], ["owned"], [], []))
    caller = add("new.obj", ([], [], ["owned"], []))
    assert run([str(caller)]) == 1
    assert "selected    owned" in capsys.readouterr().out


@pytest.mark.parametrize("kind", ["missing", "stale"])
def test_current_missing_or_stale_provider_refuses_every_result(current_preview, monkeypatch, capsys, kind):
    _, add, run, _, _, _ = current_preview
    obj = add("new.obj")
    if kind == "missing":
        monkeypatch.setattr(link_census, "objects", lambda rows: ([], [obj]))
    else:
        monkeypatch.setattr(link_census, "stale_objects", lambda objects, sources: [obj])
    with pytest.raises(SystemExit, match="missing|lack current compiler evidence"):
        run([str(obj)])
    assert "LINKS" not in capsys.readouterr().out


@pytest.mark.parametrize("part", ["inputs", "tools", "object"])
def test_current_moving_inputs_refuse_before_printing_links(current_preview, monkeypatch, capsys, part):
    _, add, run, clock, _, _ = current_preview
    obj = add("new.obj")
    check = C.check_object
    def move(*args):
        result = check(*args)
        if part == "object":
            obj.write_bytes(b"replaced object with other code")
        else:
            clock[part] = "changed"
        return result
    monkeypatch.setattr(C, "check_object", move)
    with pytest.raises(SystemExit, match="inputs moved"):
        run([str(obj)])
    assert "LINKS" not in capsys.readouterr().out


def test_current_foreign_same_basename_is_not_a_provider(current_preview, tmp_path):
    _, add, run, _, _, _ = current_preview
    add("new.obj")
    elsewhere = tmp_path / "elsewhere"
    elsewhere.mkdir()
    foreign = elsewhere / "new.obj"
    foreign.write_bytes(b"unproven object")
    with pytest.raises(SystemExit, match="not a current matched provider"):
        run([str(foreign)])


def test_current_map_exception_remaps_by_name_and_preserves_unknown():
    old = {**index(comdat={"f": [(0, "a", None), (1, "b", None)]}),
           "selection": {"exceptions": {"f": 1}, "owners": {}}}
    now = {**index(comdat={"f": [(1, "a", None), (2, "b", None)]}),
           "objects": ["new.obj", "a.obj", "b.obj"]}
    selected, unmeasured = C.current_selection(old, now, {"f": {"b.obj"}})
    assert selected == {"exceptions": {"f": 2}, "owners": {"f": {"b.obj"}}}
    assert not unmeasured
    old["selection"]["exceptions"]["f"] = None
    assert C.current_selection(old, now, {})[0]["exceptions"] == {"f": None}


@pytest.mark.parametrize("change", ["body", "order", "removed", "strong"])
def test_current_changed_map_exception_is_never_guessed(change):
    old = {**index(comdat={"f": [(0, "a", None), (1, "b", None)]}),
           "selection": {"exceptions": {"f": 1}, "owners": {}}}
    now = copy.deepcopy(old)
    if change == "body":
        now["comdat"]["f"][1] = (1, "changed", None)
    elif change == "order":
        now["objects"] = ["b.obj", "a.obj", "c.obj"]
    elif change == "removed":
        now["comdat"]["f"] = [(0, "a", None)]
    else:
        old["strong"] = now["strong"] = {"f": [1]}
    selected, unmeasured = C.current_selection(old, now, {})
    assert selected["exceptions"] == {} and unmeasured == {"f"}


def test_current_touched_changed_map_exception_refuses(current_preview):
    old, add, run, _, _, _ = current_preview
    old["comdat"] = {"f": [(0, "old", None)]}
    old["selection"]["exceptions"] = {"f": None}
    obj = add("new.obj", ([], [], ["f"], []))
    with pytest.raises(SystemExit, match="changed /MAP selection exception.*f"):
        run([str(obj)])


@pytest.mark.parametrize("flags", [["--current-ledger"], ["--refresh", "--current-ledger", "--census-only"],
                                   ["--refresh", "--current-ledger", "--new-variants"]])
def test_current_mode_is_explicit_and_separate(flags):
    with pytest.raises(SystemExit) as failed:
        C.main(flags)
    assert failed.value.code == 2


def test_current_provider_names_must_be_unique(current_preview, monkeypatch, tmp_path):
    _, add, run, _, _, present = current_preview
    obj = add("new.obj")
    other = tmp_path / "another-cache" / "new.obj"
    other.parent.mkdir()
    other.write_bytes(b"other current provider")
    present.append(other)
    with pytest.raises(SystemExit, match="object-name collision"):
        run([str(obj)])
