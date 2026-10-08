"""Admission distinguishes unchanged census debt from newly introduced bodies."""
import io
import subprocess
import sys
from pathlib import Path
import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import link_check as C


def facts(monkeypatch, digest="old", verdict=None):
    monkeypatch.setattr(C.link_census, "object_facts",
                        lambda obj, truth: ([("f", digest, 10, verdict)], [], [], []))


def census():
    return {"objects": ["a.obj", "b.obj"],
            "comdat": {"f": [(0, "old", None), (1, "kept", None)]}, "strong": {},
            "selection": {"exceptions": {}, "owners": {}},
            "excuses": {"runtime": set(), "imported": {}, "stubs": {}},
            "common_schema": C.COMMON_SCHEMA, "common": {}, "alternates": {}}


@pytest.mark.parametrize("verdict", [None, "unknown", "wrong"])
def test_unchanged_self_copy_is_existing_admission_debt(monkeypatch, verdict):
    facts(monkeypatch, verdict=verdict)
    assert C.new_variants(Path("a.obj"), census(), None, {"f": {"old"}}) == []


@pytest.mark.parametrize("verdict", [None, "unknown", "wrong"])
def test_changed_self_copy_is_still_refused(monkeypatch, verdict):
    facts(monkeypatch, "new", verdict)
    assert C.new_variants(Path("a.obj"), census(), None, {"f": {"old"}}) == ["f"]


def test_new_file_has_no_self_debt_exemption(monkeypatch):
    facts(monkeypatch, "new", "wrong")
    assert C.new_variants(Path("new.obj"), census(), None) == ["f"]


def test_wrong_body_is_refused_even_without_an_existing_other_copy(monkeypatch):
    facts(monkeypatch, "new", "wrong")
    ix = census()
    ix["comdat"] = {}
    assert C.new_variants(Path("new.obj"), ix, None) == ["f"]


def test_proven_retail_copy_is_allowed(monkeypatch):
    facts(monkeypatch, "new", "retail")
    assert C.new_variants(Path("new.obj"), census(), None) == []


@pytest.mark.parametrize("digest, expected", [("old", 0), ("new", 1)])
def test_cli_uses_census_self_copy_before_refresh(monkeypatch, tmp_path, digest, expected):
    ix = census()
    marker = tmp_path / "index.pkl"
    marker.touch()
    monkeypatch.setattr(C, "INDEX", marker)
    monkeypatch.setattr(C, "load_index", lambda: ix)
    monkeypatch.setattr(C, "resolve", lambda path, index: (path, Path("a.obj")))
    monkeypatch.setattr(C.link_census, "ledger", lambda: None)
    monkeypatch.setattr(C.link_census, "RetailTruth", lambda rows: None)
    monkeypatch.setattr(C, "link_rank", lambda rows: {"a.obj": 0, "b.obj": 1})
    def refresh(index, objects, truth):
        index["comdat"]["f"][0] = (0, digest, "wrong")
    monkeypatch.setattr(C, "refresh", refresh)
    facts(monkeypatch, digest, "wrong")
    assert C.main(["--new-variants", "a.cpp"]) == expected


def cli(monkeypatch, tmp_path, ix, facts_by_object, resolved=None, rank=None):
    """main() over `ix` with object_facts per object name; resolve maps a.cpp -> a.obj.
    Link order (link_rank) is the census's order, then the facts' new objects."""
    marker = tmp_path / "index.pkl"
    marker.touch()
    monkeypatch.setattr(C, "INDEX", marker)
    monkeypatch.setattr(C, "load_index", lambda: ix)
    seen = [] if resolved is None else resolved
    def resolve(path, index):
        seen.append(path)
        return path, Path(Path(path).stem + ".obj")
    monkeypatch.setattr(C, "resolve", resolve)
    monkeypatch.setattr(C.link_census, "ledger", lambda: None)
    monkeypatch.setattr(C.link_census, "RetailTruth", lambda rows: None)
    monkeypatch.setattr(C.link_census, "object_facts",
                        lambda obj, truth: (facts_by_object[obj.name], [], [], []))
    if rank is None:
        order = ix["objects"] + [name for name in facts_by_object if name not in ix["objects"]]
        rank = {name: place for place, name in enumerate(order)}
    monkeypatch.setattr(C, "link_rank", lambda rows: rank)
    return seen


def test_each_object_is_exempt_only_for_its_own_census_copies(monkeypatch, tmp_path, capsys):
    # b's census copy "bee" is replaced by its refreshed object; a now emits b's
    # old body. Only a's own census copy ("old") exempts a: had the snapshot
    # mixed objects, "bee" would pass as a's existing debt.
    ix = {**census(), "objects": ["a.obj", "b.obj", "c.obj"],
          "comdat": {"f": [(0, "old", None), (1, "bee", None), (2, "kept", None)]}}
    cli(monkeypatch, tmp_path, ix, {"a.obj": [("f", "bee", 10, "wrong")],
                                    "b.obj": [("f", "bee2", 10, None)]})
    def refresh(index, objects, truth):
        index["comdat"]["f"][1] = (1, "bee2", None)
    monkeypatch.setattr(C, "refresh", refresh)
    assert C.main(["--new-variants", "a.cpp", "b.cpp"]) == 1
    err = capsys.readouterr().err
    assert "link_check [refused] a.cpp: its copy of f would replace" in err and "b.cpp" not in err


def test_own_unchanged_copies_pass_beside_a_second_given_object(monkeypatch, tmp_path):
    ix = census()
    cli(monkeypatch, tmp_path, ix, {"a.obj": [("f", "old", 10, "wrong")],
                                    "b.obj": [("f", "kept", 10, "wrong")]})
    monkeypatch.setattr(C, "refresh", lambda index, objects, truth: None)
    assert C.main(["--new-variants", "a.cpp", "b.cpp"]) == 0


@pytest.mark.parametrize("separator", [b"\0", b"\n", b"\r\n"])
def test_paths_from_lists_what_arguments_do(monkeypatch, tmp_path, separator):
    monkeypatch.setattr(C, "refresh", lambda index, objects, truth: None)
    facts_by_object = {"a b.obj": [("f", "old", 10, None)], "c.obj": [("f", "old", 10, None)]}
    by_argv = cli(monkeypatch, tmp_path, census(), facts_by_object)
    assert C.main(["--new-variants", "Code/a b.cpp", "Code/c.cpp"]) == 0
    listing = tmp_path / "paths"
    listing.write_bytes(separator.join([b"Code/a b.cpp", b"Code/c.cpp"]) + separator)
    by_file = cli(monkeypatch, tmp_path, census(), facts_by_object)
    assert C.main(["--new-variants", "--paths-from", str(listing)]) == 0
    by_stdin = cli(monkeypatch, tmp_path, census(), facts_by_object)
    monkeypatch.setattr(C.sys, "stdin", io.TextIOWrapper(io.BytesIO(listing.read_bytes())))
    assert C.main(["--new-variants", "--paths-from", "-"]) == 0
    assert by_argv == by_file == by_stdin == ["Code/a b.cpp", "Code/c.cpp"]


def test_an_empty_paths_from_list_judges_nothing(monkeypatch, tmp_path):
    seen = cli(monkeypatch, tmp_path, census(), {})
    monkeypatch.setattr(C.sys, "stdin", io.TextIOWrapper(io.BytesIO(b"")))
    assert C.main(["--new-variants", "--paths-from", "-"]) == 0
    assert seen == []


def _git(repo, *args):
    subprocess.run(["git", *args], cwd=repo, check=True, capture_output=True)


def test_staged_lists_units_whole_and_never_as_arguments(monkeypatch, tmp_path):
    # --staged-peers reaches staged() from the commit gate: the unstaged-edit
    # check must not pass every unit on one command line (Windows caps it at
    # 32,767 characters), and a name with a space must survive.
    _git(tmp_path, "init", "-q")
    for name in ("Code/a b.cpp", "Code/c.c", "Code/d.h"):
        (tmp_path / name).parent.mkdir(parents=True, exist_ok=True)
        (tmp_path / name).write_text("int x;\n")
    _git(tmp_path, "add", "Code")
    monkeypatch.setattr(C, "ROOT", tmp_path)
    argv = []
    real = C.subprocess.run
    monkeypatch.setattr(C.subprocess, "run", lambda args, **kw: argv.append(args) or real(args, **kw))
    assert sorted(C.staged()) == ["Code/a b.cpp", "Code/c.c"]
    assert all("Code/a b.cpp" not in args for args in argv)
    (tmp_path / "Code/c.c").write_text("int y;\n")
    with pytest.raises(SystemExit, match="unstaged edits: Code/c.c"):
        C.staged()


def test_staged_fails_closed_when_git_cannot_list(monkeypatch, tmp_path):
    monkeypatch.setattr(C, "ROOT", tmp_path)  # not a repository
    monkeypatch.setenv("GIT_CEILING_DIRECTORIES", str(tmp_path.parent))
    monkeypatch.delenv("GIT_DIR", raising=False)
    with pytest.raises(SystemExit, match="failed"):
        C.staged()


# Link order: link.exe keeps the first copy, so a new copy that sorts after the
# one the census keeps charges only its own unit. The review's replay refused 5
# of 32 accepted upstream commits on STLport instantiations and private-view
# getters whose new object sorted after the existing holder in every case.

def shared(*holders, verdict=None, owners=None, exceptions=None, strong=None):
    """Every census object in `holders` shares one copy "kept" of f."""
    return {**census(), "objects": list(holders),
            "comdat": {"f": [(i, "kept", verdict) for i in range(len(holders))]},
            "strong": strong or {}, "selection": {"exceptions": exceptions or {}, "owners": owners or {}}}


def order(*names):
    return {name: place for place, name in enumerate(names)}


@pytest.mark.parametrize("verdict", [None, "unknown"])
def test_a_split_copy_that_sorts_after_the_kept_one_breaks_no_other_unit(monkeypatch, verdict):
    # list<Drawable*>::begin compiled under a unit's own // cl: flags: the
    # census's copy stays the one every other unit links against.
    facts(monkeypatch, "new", verdict)
    ix = shared("a.obj", "b.obj", verdict=verdict)
    assert C.new_variants(Path("new.obj"), ix, None, rank=order("a.obj", "b.obj", "new.obj")) == []
    assert C.new_variants(Path("new.obj"), ix, None, rank=order("a.obj", "new.obj", "b.obj")) == []
    # First in link order, it becomes the kept copy and every other one loses.
    assert C.new_variants(Path("new.obj"), ix, None, rank=order("new.obj", "a.obj", "b.obj")) == ["f"]


def test_a_wrong_copy_is_refused_only_where_the_link_would_keep_it(monkeypatch):
    # The AsciiString::compare case: a wrong copy kept for everyone re-blocks
    # every unit touching the name; one the link discards blocks only its own.
    facts(monkeypatch, "new", "wrong")
    ix = shared("a.obj", "b.obj", verdict="retail")
    assert C.new_variants(Path("new.obj"), ix, None, rank=order("a.obj", "new.obj", "b.obj")) == []
    assert C.new_variants(Path("new.obj"), ix, None, rank=order("new.obj", "a.obj", "b.obj")) == ["f"]


def test_a_wrong_copy_beside_a_census_map_exception_keeps_the_census_holder(monkeypatch):
    facts(monkeypatch, "new", "wrong")
    ix = shared("a.obj", "b.obj", verdict="retail", exceptions={"f": 1})
    assert C.new_variants(Path("new.obj"), ix, None, rank=order("new.obj", "a.obj", "b.obj")) == []
    ix["comdat"]["f"] = ix["comdat"]["f"][:1]  # the /MAP holder no longer defines it
    assert C.new_variants(Path("new.obj"), ix, None, rank=order("new.obj", "a.obj", "b.obj")) == ["f"]


def test_a_first_unproven_copy_beside_a_proven_one_breaks_no_other_unit(monkeypatch):
    # Retail truth keeps the proven copy wherever the new one sorts.
    facts(monkeypatch, "new", "unknown")
    ix = shared("a.obj", verdict="retail")
    assert C.new_variants(Path("new.obj"), ix, None, rank=order("new.obj", "a.obj")) == []


def test_a_first_copy_kept_over_the_ledger_owners_exclusive_definition_is_refused(monkeypatch):
    # operator new kept from GameMemory.obj while the owner's body is mem_ops.obj's:
    # no copy loses keep_rule (a's is proven), but the kept definition turns wrong.
    facts(monkeypatch, "new", None)
    ix = shared("a.obj", verdict="retail", strong={"f": [1]}, owners={"f": {"b.obj"}})
    ix["objects"] = ["a.obj", "b.obj"]
    assert C.new_variants(Path("new.obj"), ix, None, rank=order("b.obj", "new.obj", "a.obj")) == []
    assert C.new_variants(Path("new.obj"), ix, None, rank=order("new.obj", "b.obj", "a.obj")) == ["f"]


def test_a_wrong_copy_of_a_name_nothing_else_defines_breaks_only_resolved_references(monkeypatch):
    # TerrainLogicLoadMap.cpp's inline MapObject::getLocation (e6a0763f3b): the
    # pin proves it wrong, but no census object defines the name, so whoever
    # references it was unresolved already and only the new unit is charged.
    facts(monkeypatch, "new", "wrong")
    ix = {**census(), "objects": ["a.obj"], "comdat": {}}
    assert C.new_variants(Path("new.obj"), ix, None, rank=order("a.obj", "new.obj")) == []
    assert C.new_variants(Path("new.obj"), ix, None, rank=order("new.obj", "a.obj")) == []
    # References an /alternatename resolved now reach the wrong body instead:
    # a private AsciiString::compare displaced the alias to the shared
    # StringBase<char>::compare and was charged to 135 units.
    ix["alternates"] = {"f": [(0, "g")]}
    assert C.new_variants(Path("new.obj"), ix, None, rank=order("a.obj", "new.obj")) == ["f"]
    # An alias in an object the census no longer links resolves nothing.
    assert C.new_variants(Path("new.obj"), ix, None, rank=order("new.obj")) == []
    # So do references an import library resolved.
    ix["alternates"], ix["excuses"] = {}, {**ix["excuses"], "runtime": {"f"}}
    assert C.new_variants(Path("new.obj"), ix, None, rank=order("a.obj", "new.obj")) == ["f"]


def test_an_object_the_census_does_not_link_breaks_nothing(monkeypatch):
    # No matched row names it, so link_order (and the next census) leaves it out.
    facts(monkeypatch, "new", "wrong")
    assert C.new_variants(Path("new.obj"), shared("a.obj"), None, rank=order("a.obj")) == []


def test_census_objects_the_ledger_no_longer_links_are_left_out(monkeypatch):
    # b holds the only other copy but has no matched row now: nothing keeps it.
    facts(monkeypatch, "new", None)
    ix = shared("b.obj")
    assert C.new_variants(Path("new.obj"), ix, None, rank=order("new.obj")) == []
    assert C.new_variants(Path("new.obj"), ix, None, rank=order("new.obj", "b.obj")) == ["f"]


def test_link_rank_is_the_census_link_order_of_the_ledger():
    # One row per compiled source places it as all of them would; a lib's rows
    # name different members, so each counts.
    rows = [{"source": "Code/B.cpp", "target_rva": "0x300"}, {"source": "Code/A.cpp", "target_rva": "0x200"},
            {"source": "Code/B.cpp", "target_rva": "0x100"},
            {"source": "Code/L.lib", "target_rva": "0x250", "notes": "member=x.obj"},
            {"source": "Code/L.lib", "target_rva": "0x150", "notes": "member=y.obj"},
            {"source": "Code/L.lib", "target_rva": "0x050", "notes": "member=x.obj"}]
    rank = C.link_rank(rows)
    assert rank == {obj.name: place for place, obj in enumerate(C.link_census.link_order(rows))}
    b, a = C.build.obj_path(C.ROOT / "Code/B.cpp").name, C.build.obj_path(C.ROOT / "Code/A.cpp").name
    x, y = (C.build.obj_path(C.ROOT / "Code/L.lib", member).name for member in ("x.obj", "y.obj"))
    assert sorted(rank, key=rank.get) == [x, b, y, a]


@pytest.mark.parametrize("shadow, expected, tag", [(False, 1, "refused"), (True, 0, "shadow")])
def test_shadow_reports_what_it_would_refuse(monkeypatch, tmp_path, capsys, shadow, expected, tag):
    monkeypatch.setattr(C, "refresh", lambda index, objects, truth: None)
    cli(monkeypatch, tmp_path, shared("a.obj"), {"new.obj": [("f", "new", 10, None)]},
        rank=order("new.obj", "a.obj"))
    argv = ["--new-variants", "--shadow", "new.cpp"] if shadow else ["--new-variants", "new.cpp"]
    assert C.main(argv) == expected
    assert f"link_check [{tag}] new.cpp: its copy of f would replace" in capsys.readouterr().err


def test_shadow_is_only_for_the_admission_form():
    with pytest.raises(SystemExit):
        C.main(["--shadow", "a.cpp"])
