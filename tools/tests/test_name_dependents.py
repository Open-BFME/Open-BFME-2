"""name_dependents: a ledger change that takes a call target away re-verifies
every unit that calls it.

In a fork of this repository, a7a39472e7 retracted the row named
`?baseConstruct@BFME2NativeNetwork@@QAEPAV1@XZ` and broke 38 rows in 40 units
that still called that name, because the hooks byte-verified only the units
whose own rows changed. These tests pin the parts of the repair: which names
count as lost, which units reference them (and when a cached object is no
evidence for that), and that both hooks feed those units to the byte build.
The live test replays the breakage on the real ledger and the real object cache.
"""

import argparse
import hashlib
import json
import struct
import subprocess
import sys
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "tools" / "tests"))

import name_dependents as nd  # noqa: E402
# The real hooks in a throwaway repository, with every checker stubbed.
from test_hook_fail_closed import (SOURCE, built, git, ledger_only_commit,  # noqa: E402,F401
                                   push_refs, repo, run, write)

OLD = "?baseConstruct@BFME2NativeNetwork@@QAEPAV1@XZ"
NEW = "??0SubsystemInterface@@QAE@XZ"


def coff(names):
    """A minimal COFF object whose symbol table holds `names` (one aux record
    after the first, as a section symbol has), long names in the string table."""
    entries, strings = [], b""
    for index, name in enumerate(names):
        raw = name.encode("latin-1")
        if len(raw) <= 8:
            field = raw.ljust(8, b"\0")
        else:
            field = b"\0\0\0\0" + struct.pack("<I", 4 + len(strings))
            strings += raw + b"\0"
        aux = 1 if index == 0 else 0
        entries.append(field + struct.pack("<IhHBB", 0, 0, 0x20, 2, aux))
        if aux:
            entries.append(b"\0" * 18)
    table = 20
    header = struct.pack("<HHIIIHH", 0x14C, 0, 0, table, len(entries), 0, 0)
    return header + b"".join(entries) + struct.pack("<I", 4 + len(strings)) + strings


def compiled(root, source, names, text, built_from=None):
    """Write `source` as `text` and its object holding `names`, with the build's
    sidecar recording the text the object was compiled from (`built_from`,
    default `text`)."""
    import build
    path = root / source
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_bytes(text.encode("utf-8"))
    obj = root / "obj" / (Path(source).stem + ".obj")
    obj.parent.mkdir(exist_ok=True)
    obj.write_bytes(coff(names))
    digest = hashlib.md5((built_from or text).encode("utf-8")).hexdigest()
    build._deps_sidecar(obj).write_text(json.dumps({"cmd": "x", "source": digest, "deps": {}}))
    return obj


def rows(*specs):
    return [{"name": n, "target_rva": a, "target_size": "8", "source": s, "status": "matched",
             "notes": ""} for n, a, s in specs]


def admit_all(row):
    return True


def test_coff_symbol_names_reads_long_short_and_skips_aux():
    data = coff([".text", OLD, "_memset", "??_Gx@@UAEPAXI@Z"])
    assert nd.coff_symbol_names(data) == {".text", OLD, "_memset", "??_Gx@@UAEPAXI@Z"}


def test_rename_removal_pin_drop_and_move_lose_a_target():
    old = nd.call_targets(rows((OLD, "0x1000", "a.cpp"), ("?f@@YAXXZ", "0x2000", "b.cpp")),
                          [{"name": "_memset", "address": "0x3000"}], admit_all)
    # Rename one row, drop the pin, move the other row.
    new = nd.call_targets(rows((NEW, "0x1000", "a.cpp"), ("?f@@YAXXZ", "0x2004", "b.cpp")),
                          [], admit_all)
    assert nd.lost_names(old, new) == {OLD: {0x1000}, "?f@@YAXXZ": {0x2000}, "_memset": {0x3000}}


def test_additive_and_unchanged_changes_lose_nothing():
    base = rows((OLD, "0x1000", "a.cpp"))
    old = nd.call_targets(base, [{"name": OLD, "address": "0x1000"}], admit_all)
    # Row gone but the pin still offers the same address; plus a new pin.
    new = nd.call_targets([], [{"name": OLD, "address": "0x1000"},
                               {"name": "_new", "address": "0x5000"}], admit_all)
    assert nd.lost_names(old, new) == {}


def test_unadmitted_alias_row_gives_its_name_no_target():
    alias = rows((OLD, "0x1000", "a.cpp"))
    assert nd.call_targets(alias, [], lambda row: False) == {}


def test_only_units_whose_objects_carry_the_exact_name_are_dependents(tmp_path):
    caller = compiled(tmp_path, "Code/caller.cpp", [".text", OLD], "void a();\n")
    # The lost name is a substring of this one, but it is a different symbol.
    lookalike = compiled(tmp_path, "Code/lookalike.cpp", [".text", "?" + OLD], "void b();\n")
    unrelated = compiled(tmp_path, "Code/unrelated.cpp", [".text", "?g@@YAXXZ"], "void c();\n")
    found = nd.dependents({OLD: {0x1000}}, {"Code/caller.cpp": [caller],
                                            "Code/lookalike.cpp": [lookalike],
                                            "Code/unrelated.cpp": [unrelated]}, tmp_path)
    assert found == {"Code/caller.cpp"}


def test_rename_breaking_a_dependent_lists_it_and_updated_dependent_does_not(tmp_path):
    old_rows = rows((OLD, "0x1000", "Code/home.cpp"), ("?c@@YAXXZ", "0x9000", "Code/caller.cpp"))
    new_rows = rows((NEW, "0x1000", "Code/home.cpp"), ("?c@@YAXXZ", "0x9000", "Code/caller.cpp"))
    objects = {}

    def objects_of(_rows):
        return objects

    # Caller still calls the old name: it must be re-verified.
    objects["Code/caller.cpp"] = [compiled(tmp_path, "Code/caller.cpp", [".text", OLD, "?c@@YAXXZ"],
                                           "void c() { x->baseConstruct(); }\n")]
    objects["Code/home.cpp"] = []
    assert "Code/caller.cpp" in nd.dependent_sources(
        old_rows, [], new_rows, [], admitted=admit_all, objects_of=objects_of, root=tmp_path)
    # Caller updated to the new name in the same change: nothing calls the old one.
    compiled(tmp_path, "Code/caller.cpp", [".text", NEW, "?c@@YAXXZ"],
             "void c() { new (x) SubsystemInterface; }\n")
    assert "Code/caller.cpp" not in nd.dependent_sources(
        old_rows, [], new_rows, [], admitted=admit_all, objects_of=objects_of, root=tmp_path)
    # No lost target, no scan at all.
    assert nd.dependent_sources(old_rows, [], old_rows, [], admitted=admit_all,
                                objects_of=lambda _r: pytest.fail("scanned"), root=tmp_path) == set()


def test_objectless_source_widens_on_its_text(tmp_path):
    code = tmp_path / "Code"
    code.mkdir()
    (code / "mentions.cpp").write_text("void f() { x->baseConstruct(); }\n")
    (code / "silent.cpp").write_text("void f() {}\n")
    found = nd.dependents({OLD: {0x1000}}, {"Code/mentions.cpp": [tmp_path / "none.obj"],
                                            "Code/silent.cpp": [tmp_path / "none2.obj"]}, tmp_path)
    assert found == {"Code/mentions.cpp"}


def test_an_object_compiled_from_other_text_is_judged_on_the_source_text(tmp_path):
    import build
    # Built while the source called something else, then put back to calling the lost
    # name without a rebuild (a reverted experiment): the object lacks the name, but
    # its sidecar shows it is not this text's object.
    calls = "void f() { x->baseConstruct(); }\n"
    stale = compiled(tmp_path, "Code/stale.cpp", [".text", "?other@@YAXXZ"], calls,
                     built_from="void f() { other(); }\n")
    # No sidecar, no proof of what the object was compiled from.
    bare = compiled(tmp_path, "Code/bare.cpp", [".text"], calls)
    build._deps_sidecar(bare).unlink()
    # A current object outranks the text: a comment naming the identifier is no call.
    current = compiled(tmp_path, "Code/current.cpp", [".text", "?other@@YAXXZ"],
                       "// once called baseConstruct\nvoid f() { other(); }\n")
    found = nd.dependents({OLD: {0x1000}}, {"Code/stale.cpp": [stale], "Code/bare.cpp": [bare],
                                            "Code/current.cpp": [current]}, tmp_path)
    assert found == {"Code/stale.cpp", "Code/bare.cpp"}


def test_a_source_with_uncommitted_edits_is_judged_on_the_committed_text(tmp_path):
    # Its working copy already calls the new name and its object was built from that
    # copy, but the state being committed still makes the old call.
    obj = compiled(tmp_path, "Code/caller.cpp", [".text", NEW],
                   "void f() { new (x) SubsystemInterface; }\n")
    objects = {"Code/caller.cpp": [obj]}
    assert nd.dependents({OLD: {0x1000}}, objects, tmp_path) == set()
    committed = {"Code/caller.cpp": b"void f() { x->baseConstruct(); }\n"}
    assert nd.dependents({OLD: {0x1000}}, objects, tmp_path, unsettled={"Code/caller.cpp"},
                         committed=committed.get) == {"Code/caller.cpp"}
    committed = {"Code/caller.cpp": b"void f() {}\n"}
    assert nd.dependents({OLD: {0x1000}}, objects, tmp_path, unsettled={"Code/caller.cpp"},
                         committed=committed.get) == set()


@pytest.mark.parametrize("name,word", [
    (OLD, "baseConstruct"), (NEW, "SubsystemInterface"),
    ("??_GGameEngineDeletingBase@@UAEPAXI@Z", "GameEngineDeletingBase"),
    ("_memset", "memset"), ("@foo@8", "foo"),
    # Templates: a function template names itself, a template class its members.
    ("??$distance@PAH@_STL@@YAHPAH0@Z", "distance"), ("??0?$vector@H@_STL@@QAE@XZ", "vector"),
    ("??1?$basic_string@D@_STL@@QAE@XZ", "basic_string"),
    ("??$?8DV?$char_traits@D@_STL@@@_STL@@YA_NPBD0@Z", None)])
def test_bare_identifier(name, word):
    assert nd.bare_identifier(name) == word


def test_a_lost_name_without_an_identifier_widens_every_objectless_source(tmp_path):
    # The text test looks for identifiers; a lost operator template has none, so it
    # must not be dropped just because another lost name has one.
    code = tmp_path / "Code"
    code.mkdir()
    (code / "silent.cpp").write_text("bool f(const char *a) { return s == a; }\n")
    current = compiled(tmp_path, "Code/current.cpp", [".text", "?other@@YAXXZ"], "void g();\n")
    operator = "??$?8DV?$char_traits@D@_STL@@@_STL@@YA_NPBD0@Z"
    objects = {"Code/silent.cpp": [tmp_path / "none.obj"], "Code/current.cpp": [current]}
    assert nd.dependents({OLD: {0x1000}}, objects, tmp_path) == set()
    assert nd.dependents({OLD: {0x1000}, operator: {0x2000}}, objects, tmp_path) == {"Code/silent.cpp"}


@pytest.mark.parametrize("newline", [b"\n", b"\r\n"])
def test_states_read_the_checked_ledgers_and_refuse_an_unreadable_one(tmp_path, newline):
    repo = tmp_path / "repo"
    repo.mkdir()

    def sh(*args):
        return subprocess.run(["git", *args], cwd=repo, check=True, capture_output=True,
                              text=True).stdout.strip()

    sh("init", "-q")
    sh("config", "user.name", "Fixture")
    sh("config", "user.email", "fixture@example.invalid")
    sh("config", "core.autocrlf", "false")
    old_call = b"old call" + newline
    new_call = b"new call" + newline
    header = "name,export_rva,target_rva,target_size,source,status,notes\n"
    (repo / "reverse").mkdir()
    (repo / "Code").mkdir()
    (repo / "reverse/functions.csv").write_text(header + f"{OLD},,0x1000,8,Code/a.cpp,matched,\n")
    (repo / "reverse/symbols.csv").write_text("name,address,notes\n")
    (repo / "Code/caller.cpp").write_bytes(old_call)
    sh("add", "-A")
    sh("commit", "-qm", "base")
    base = sh("rev-parse", "HEAD")
    staged = argparse.Namespace(staged=True, range=None)
    assert not nd.ledgers_differ(staged, repo)

    (repo / "reverse/functions.csv").write_text(header + f"{NEW},,0x1000,8,Code/a.cpp,matched,\n")
    sh("add", "reverse/functions.csv")
    (repo / "Code/caller.cpp").write_bytes(new_call)  # left unstaged
    assert nd.ledgers_differ(staged, repo)
    (old_rows, _), (new_rows, _) = nd.states(staged, repo)
    assert [r["name"] for r in old_rows] == [OLD] and [r["name"] for r in new_rows] == [NEW]
    unsettled, committed = nd.working_copy(staged, repo)
    assert unsettled == {"Code/caller.cpp"} and committed("Code/caller.cpp") == old_call

    sh("commit", "-qm", "rename")
    ranged = argparse.Namespace(staged=False, range=[base, sh("rev-parse", "HEAD")])
    assert nd.ledgers_differ(ranged, repo)
    unsettled, committed = nd.working_copy(ranged, repo)
    assert unsettled == {"Code/caller.cpp"} and committed("Code/caller.cpp") == old_call
    sh("rm", "-q", "reverse/symbols.csv")
    sh("commit", "-qm", "no pins")
    with pytest.raises(SystemExit, match="cannot read"):
        nd.states(argparse.Namespace(staged=False, range=[base, sh("rev-parse", "HEAD")]), repo)


# ------------------------------------------------------------- the real hooks

@pytest.mark.parametrize("hook", ["pre-commit", "pre-push"])
def test_hooks_byte_verify_the_dependents(repo, hook):
    # A row edit that no unit's own rows reflect: delta_sources names nothing.
    base = git(repo, "rev-parse", "HEAD")
    ledger_only_commit(repo)
    if hook == "pre-push":
        git(repo, "commit", "-qm", "row")
    refs = push_refs(repo, base) if hook == "pre-push" else ""
    result = run(repo, hook, refs)
    assert result.returncode == 0, result.stderr
    assert not built(repo)
    # name_dependents names a unit that calls a name the change takes away.
    write(repo, "name-deps.txt", SOURCE + "\n")
    result = run(repo, hook, refs)
    assert result.returncode == 0, result.stderr
    assert built(repo) == {SOURCE}


def test_pre_commit_refuses_a_dependent_with_unstaged_edits(repo):
    ledger_only_commit(repo)
    write(repo, SOURCE, "struct Unit { void f(); };\nvoid Unit::f() { int x = 0; }\n")
    # Not a dependent: an unrelated unstaged edit is not this commit's business.
    assert run(repo, "pre-commit").returncode == 0
    # A dependent: the build would verify the working copy, not the commit.
    write(repo, "name-deps.txt", SOURCE + "\n")
    result = run(repo, "pre-commit")
    assert result.returncode == 1
    assert f"unstaged edits in {SOURCE}, which calls a name this commit renames" in result.stderr
    assert not built(repo)


def test_real_rename_is_refused_for_a_real_dependent(tmp_path, monkeypatch):
    """Replay a7a39472e7's shape on the live ledger: take the SubsystemInterface
    ctor's name away and a unit that calls it must be listed AND fail its bytes."""
    import build

    # Rewritten as text: pin rows with unquoted commas in their notes do not
    # survive a DictWriter round trip.
    functions_text = build.FUNCTIONS.read_bytes().decode("utf-8")
    pins_text = build.SYMBOLS.read_bytes().decode("utf-8")
    functions, pins = nd.csv_dicts(functions_text), nd.csv_dicts(pins_text)
    if not any(r["name"] == NEW for r in functions) or not build.EXE.exists():
        pytest.skip("live ledger or retail image unavailable")
    renamed_text = "".join(NEW + "Retracted" + line[len(NEW):] if line.startswith(NEW + ",")
                           else line for line in functions_text.splitlines(keepends=True))
    unpinned_text = "".join(line for line in pins_text.splitlines(keepends=True)
                            if not line.startswith(NEW + ","))
    renamed, unpinned = nd.csv_dicts(renamed_text), nd.csv_dicts(unpinned_text)
    assert not any(r["name"] == NEW for r in renamed) and not any(p["name"] == NEW for p in unpinned)
    found = nd.dependent_sources(functions, pins, renamed, unpinned)
    dependent = "Code/GameEngine/Source/Common/MultiplayerSettingsCtor.cpp"
    if dependent not in found:
        pytest.skip("object cache does not hold the dependent's current object")
    source = ROOT / dependent
    if not build.compile_is_current(source, build.obj_path(source)):
        pytest.skip("dependent's object is stale; the test must not compile")

    # Green with the real ledger...
    build.verify_functions([dependent])

    # ...red once the name it calls is gone.
    ledger = tmp_path / "functions.csv"
    ledger.write_bytes(renamed_text.encode("utf-8"))
    symbols = tmp_path / "symbols.csv"
    symbols.write_bytes(unpinned_text.encode("utf-8"))
    monkeypatch.setattr(build, "FUNCTIONS", ledger)
    monkeypatch.setattr(build, "SYMBOLS", symbols)
    with pytest.raises(SystemExit) as exc:
        build.verify_functions([dependent])
    assert exc.value.code
