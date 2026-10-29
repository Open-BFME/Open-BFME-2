"""header_adopt_lane: source surgery, header generation, failure taxonomy and the closure check."""
import csv
import os
import sys
import time
from pathlib import Path
from types import SimpleNamespace

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import header_adopt_lane as lane  # noqa: E402

UNIT = """// cl: /O2
typedef float Real;
// struct Coord3D { int fake; };
struct Coord3D
{
    Real x, y, z;
    void zero() { x = y = z = 0.0f; }
};
template <class T>
class StringBase { T *p; };
class AsciiString : public StringBase<char> { char *m_data; };
void use(Coord3D *c) { c->zero(); }
"""

CONTRACT = {"class": "Coord3D", "key": "struct", "key_by": "bytes", "size": 12, "size_by": "zh", "bases": [],
            "fields": [{"offset": o, "size": 4, "kind": "f4", "type": "float", "name": n}
                       for o, n in ((0, "x"), (4, "y"), (8, "z"))]}


@pytest.fixture(params=[("Coord2D", "Coord2DCtorView"),
                        ("Coord3D", "Coord3DCtorView"),
                        ("Coord3D", "Coord3DDerivedView"),
                        ("Coord3D", "Coord3DInline")])
def constructor_companion(tmp_path, monkeypatch, request):
    name, companion_name = request.param
    directory = "Code/Libraries/Include/Lib"
    header = f"{directory}/{name}.h"
    companion = f"{directory}/{companion_name}.h"
    for path in (header, companion):
        full = tmp_path / path
        full.parent.mkdir(parents=True, exist_ok=True)
        full.write_text(f"class {name} {{}};\n")
    source = "Code/Body.cpp"
    body = tmp_path / source
    body.write_text(f'#include "Libraries/Include/Lib/{companion_name}.h"\n')
    queue = tmp_path / "header_queue.tsv"
    queue.write_text("class\tsource\theader\n" + f"{name}\t{source}\t{header}\n")
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    monkeypatch.setattr(lane, "QUEUE", queue)
    monkeypatch.setattr(lane, "registered", lambda: {name: header})
    monkeypatch.setattr(lane, "tracked_headers", lambda: [header, companion])
    calls = []
    monkeypatch.setattr(lane, "gate_one", lambda source: calls.append(source))
    monkeypatch.setattr(lane, "link_ok", lambda sources: dict.fromkeys(sources, True))
    return name, source, header, companion, body, queue, calls


def test_constructor_companion_uses_the_same_default_and_explicit_verdict(constructor_companion):
    name, source, header, companion, body, queue, calls = constructor_companion
    # The CLI and repair_queue's trusted-base verdict must agree without --header.
    assert lane.verdict(name, source) == []
    assert lane.verdict(name, source, header=header) == []
    assert lane.accept(name, [source]) == 0
    assert queue.read_text() == "class\tsource\theader\n"
    assert calls == [source, source, source]


def test_constructor_companion_cannot_retire_a_byte_mismatch(constructor_companion, monkeypatch):
    name, source, header, companion, body, queue, calls = constructor_companion
    before = queue.read_bytes()
    monkeypatch.setattr(lane, "gate_one", lambda source: "byte mismatch")
    assert lane.verdict(name, source) == ["byte mismatch"]
    assert lane.accept(name, [source]) == 1
    assert queue.read_bytes() == before


@pytest.mark.parametrize("case", ["comment", "disabled", "private", "missing", "ambiguous",
                                  "unapproved", "other-class", "other-header"])
def test_constructor_companion_does_not_bypass_adoption_checks(constructor_companion, monkeypatch, case):
    name, source, header, companion, body, queue, calls = constructor_companion
    text = body.read_text()
    explicit = None
    if case == "comment":
        body.write_text("/*\n" + text + "*/\n")
    elif case == "disabled":
        body.write_text("#if 0\n" + text + "#endif\n")
    elif case == "private":
        body.write_text(f"class {name} {{ float x, y; }};\n" + text)
    elif case == "missing":
        (lane.ROOT / companion).unlink()
    elif case == "ambiguous":
        basename = Path(companion).name
        body.write_text(f'#include "{basename}"\n')
        monkeypatch.setattr(lane, "tracked_headers", lambda: [header, companion, f"Code/Other/{basename}"])
    elif case in ("unapproved", "other-class"):
        fake = (f"Code/Other/{Path(companion).name}" if case == "unapproved" else
                "Code/Libraries/Include/Lib/" + ("Coord3D" if name == "Coord2D" else "Coord2D") + "CtorView.h")
        (lane.ROOT / fake).parent.mkdir(parents=True, exist_ok=True)
        (lane.ROOT / fake).write_text(f"#define CANONICAL_{name.upper()}_H\nclass {name} {{}};\n")
        body.write_text(f'#include "{fake.removeprefix("Code/")}"\n')
    elif case == "other-header":
        explicit = f"Code/Other/{name}.h"
        (lane.ROOT / explicit).parent.mkdir(parents=True)
        (lane.ROOT / explicit).write_text(f"class {name} {{}};\n")
    problems = lane.verdict(name, source, header=explicit)
    assert problems, case
    assert any(("private body" if case == "private" else "does not #include") in p for p in problems)
    assert calls == [source]  # Even rejected includes still run the byte gate.


def test_consolidation_transfers_all_debt_and_only_acceptance_retires_it(tmp_path, monkeypatch):
    queue = tmp_path / "header_queue.tsv"
    cols = ["class", "source", "retail_rvas", "header", "failure", "retry_budget", "acceptance"]
    rows = [dict(zip(cols, ["Coord3D", source, rva, "Coord3D.h", "original failure", "3",
                           lane.acceptance_command("Coord3D", source)]))
            for source, rva in [("Code/A.cpp", "0x10"), ("Code/B.cpp", "0x20"),
                                ("Code/Other.cpp", "0x30")]]
    with queue.open("w", newline="") as handle:
        writer = csv.DictWriter(handle, cols, delimiter="\t", lineterminator="\n")
        writer.writeheader()
        writer.writerows(rows)
    assert lane.transfer_sources(["Code/A.cpp", "Code/B.cpp"], "Code/T.cpp", queue) == 2
    with queue.open(newline="") as handle:
        moved = list(csv.DictReader(handle, delimiter="\t"))
    assert len(moved) == len(rows)
    for before, after in zip(rows[:2], moved[:2]):
        assert after == dict(before, source="Code/T.cpp",
                             acceptance=lane.acceptance_command("Coord3D", "Code/T.cpp"))
    assert moved[2] == rows[2]
    monkeypatch.setattr(lane, "QUEUE", queue)
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    monkeypatch.setattr(lane, "verdict", lambda *args: ["not adopted"])
    assert lane.accept("Coord3D", ["Code/T.cpp"]) == 1
    assert len(list(csv.DictReader(queue.open(), delimiter="\t"))) == 3
    monkeypatch.setattr(lane, "verdict", lambda *args: [])
    assert lane.accept("Coord3D", ["Code/T.cpp"]) == 0
    assert list(csv.DictReader(queue.open(), delimiter="\t")) == rows[2:]


def test_swap_strips_the_view_and_includes_the_header_where_it_stood():
    out = lane.swap(UNIT, ["Coord3D"], "../Lib/Coord3D.h")
    assert "Real x, y, z;" not in out
    assert out.index('#include "../Lib/Coord3D.h"') < out.index("void use")
    assert "// struct Coord3D { int fake; };" in out          # a commented-out head is not a view
    assert lane.swap("void f();\n", ["Coord3D"], "x.h") is None


def test_dependency_views_go_with_the_class():
    out = lane.swap(UNIT, ["AsciiString", "StringBase"], "ascii_string.h")
    assert "StringBase" not in out.split("void use")[0].split('#include "ascii_string.h"')[1]
    assert "template <class T>" not in out
    assert out.count('#include "ascii_string.h"') == 1


@pytest.mark.parametrize("indent", ["", "    ", "\t"])
def test_swap_preserves_nested_snapshot_and_only_replaces_global_view(indent):
    allocator = ("namespace EA { namespace Allocator {\n"
                 "class GeneralAllocator {\npublic:\n"
                 + indent + "struct Snapshot { unsigned m_magic; };\n"
                 "};\n}}\n")
    assert lane.body_span(allocator, "Snapshot") is None
    assert lane.swap(allocator, ["Snapshot"], "Snapshot.h") is None
    text = allocator + "    class Snapshot { int game; };\n"
    out = lane.swap(text, ["Snapshot"], "Snapshot.h")
    assert out == allocator + '#include "Snapshot.h"\n'


def test_nested_record_does_not_bypass_header_acceptance(tmp_path, monkeypatch):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    (tmp_path / "Snapshot.h").write_text("class Snapshot {};\n")
    (tmp_path / "unit.cpp").write_text("class Allocator {\nstruct Snapshot { int magic; };\n};\n")
    assert lane.verdict("Snapshot", "unit.cpp", "Snapshot.h", gate=lambda _: None) == [
        "does not #include Snapshot.h"]


def test_indented_global_private_view_still_fails_acceptance(tmp_path, monkeypatch):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    (tmp_path / "Snapshot.h").write_text("class Snapshot {};\n")
    (tmp_path / "unit.cpp").write_text('#include "Snapshot.h"\n    class Snapshot { int game; };\n')
    assert lane.verdict("Snapshot", "unit.cpp", "Snapshot.h", gate=lambda _: None) == [
        "still declares a private body"]


def test_generated_header_spells_the_contract():
    text = lane.generate(CONTRACT, "data", {})
    assert "struct Coord3D {" in text and "float x;" in text and "float z;" in text
    assert "Coord3D() {}" not in text
    assert "Coord3D() {}" in lane.generate(CONTRACT, "data+ctor", {})


def test_failure_taxonomy():
    assert lane.failure_class("x.cpp(3) : error C2039: 'zero' : is not a member") == "C2039 missing member"
    assert lane.failure_class("x.cpp(3) : error C2371: 'Bool' : redefinition") == "C2371"
    assert lane.failure_class("Functions: FAIL ?f@@YAXXZ") == "bytes/callee identity"


def test_closure_diff_flags_lost_rows(tmp_path):
    head = "name,retail_rva,closed_strict\n"
    before, same, lost = tmp_path / "a.csv", tmp_path / "b.csv", tmp_path / "c.csv"
    before.write_text(head + "?f@@YAXXZ,0x00401000,1\n?g@@YAXXZ,0x00401010,0\n")
    same.write_text(head + "?f@@YAXXZ,0x00401000,1\n?g@@YAXXZ,0x00401010,1\n")
    lost.write_text(head + "?f@@YAXXZ,0x00401000,0\n?g@@YAXXZ,0x00401010,1\n")
    assert lane.closure_diff(before, same) == 0      # negative control: closure only grew
    assert lane.closure_diff(before, lost) == 1      # positive control: a closed row was lost


def test_view_methods_merge_void_spelling_and_skip_declspec_special_members(tmp_path, monkeypatch):
    # Region3D views spell width() and width(void), and declare
    # `__declspec(nothrow) Region3D(const Region3D&);`: both once made every
    # generated methods header C2535.
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    (tmp_path / "a.cpp").write_text("struct Region3D {\n    float lo, hi;\n"
                                    "    float width() const { return hi - lo; }\n"
                                    "    bool in(const Coord3D *p) const;\n"
                                    "    __declspec(nothrow) Region3D(const Region3D&);\n};\n")
    (tmp_path / "b.cpp").write_text("struct Region3D {\n    float lo, hi;\n"
                                    "    float width(void) const { return hi - lo; }\n"
                                    "    bool in(const Coord3D *query) const { return query != 0; }\n};\n")
    assert len(lane.view_methods("Region3D", ["a.cpp", "b.cpp"])) == 1   # in() names a class not included
    methods = lane.view_methods("Region3D", ["a.cpp", "b.cpp"], {"Coord3D"})
    assert len(methods) == 2                    # one width, one in(): pointer parameter names do not count
    assert "{" in methods[lane.signature("bool in(const Coord3D *p) const;", "Region3D")]   # the body wins


def test_view_methods_keeps_hump_underscore_identifiers(tmp_path, monkeypatch):
    # WWLib method names are hump-underscore identifiers (Delete_This,
    # Add_Ref); the old all-uppercase-sounds-like-a-type filter dropped every
    # such method, so generated headers shipped vtables whose slot 0 was the
    # delete-dtor instead of the base class's Delete_This.
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    (tmp_path / "rc.cpp").write_text(
        "class RefCountClass {\n"
        "public:\n"
        "    void Release_Ref(void);\n"
        "    virtual void Delete_This(void);\n"
        "    virtual ~RefCountClass(void);\n"
        "private:\n"
        "    int NumRefs;\n};\n")
    methods = lane.view_methods("RefCountClass", ["rc.cpp"])
    assert "virtual void Delete_This(void);" in " ".join(methods.values())


def test_generated_header_orders_destructor_last():
    # A leading destructor would put the delete-dtor in the class vtable's
    # first slot; the donor order keeps member virtuals before it.
    methods = {"void Delete_This();": "virtual void Delete_This();",
               "~dtor": "virtual ~RefCountClass(void) {}"}
    contract = {"class": "RefCountClass", "key": "class", "key_by": "bytes", "size": 8, "size_by": "zh",
                "bases": [], "fields": []}
    text = lane.generate(contract, "data+methods", methods, None)
    assert text.index("Delete_This") < text.rindex("~RefCountClass")


def preview(source, before, after, clean=True):
    return (f"{source}: {'LINKS' if clean else 'does not link'}  "
            f"LINKED {before:,} -> {after:,} bytes (census 2026-10-27 at bf3dd31211; "
            f"file's own bytes {max(before, after):,})\n")


@pytest.mark.parametrize("output,code,expected", [
    (preview("Code/FX.cpp", 5649, 5649), 0, True),
    (preview("Code/FX.cpp", 5649, 0, False), 1, False),
    (preview("Code/FX.cpp", 0, 42), 0, True),
    (preview("Code/FX.cpp", 0, 0, False), 1, True),
    ("Code/FX.cpp(3): error C2259: cannot instantiate abstract class\n", 1, None),
    ("Code/FX.cpp: UNKNOWN (missing object)\n", 1, None),
    (preview("Code/Other.cpp", 5649, 5649), 0, None),
    (preview("Code/FX.cpp", 5649, 5649) * 2, 0, None),
    (preview("Code/FX.cpp", 5649, 5649), 2, None),
])
def test_link_guard_requires_explicit_per_unit_coverage(output, code, expected, tmp_path, monkeypatch):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    (tmp_path / "tools").mkdir()
    (tmp_path / "tools/link_check.py").touch()

    def run(command, **kwargs):
        assert command == [sys.executable, "tools/link_check.py", "./Code/FX.cpp"]
        assert kwargs["cwd"] == tmp_path
        return SimpleNamespace(stdout=output, stderr="", returncode=code)

    monkeypatch.setattr(lane.subprocess, "run", run)
    assert lane.link_ok(["./Code/FX.cpp"]) == {"./Code/FX.cpp": expected}


@pytest.mark.parametrize("output,code,passes", [
    (preview("Code/FX.cpp", 5649, 0, False), 1, False),
    ("Code/FX.cpp: UNKNOWN (missing object)\n", 1, False),
    (preview("Code/FX.cpp", 5649, 5649), 0, True),
    (preview("Code/FX.cpp", 0, 0, False), 1, True),
])
def test_header_acceptance_keeps_debt_unless_linked_bytes_are_preserved(output, code, passes, tmp_path, monkeypatch):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    (tmp_path / "Code").mkdir()
    (tmp_path / "Code/FX.cpp").write_text('#include "../Snapshot.h"\n')
    (tmp_path / "Snapshot.h").write_text("class Snapshot {};\n")
    (tmp_path / "tools").mkdir()
    (tmp_path / "tools/link_check.py").touch()
    queue = tmp_path / "header_queue.tsv"
    original = "class\tsource\nSnapshot\tCode/FX.cpp\n"
    queue.write_text(original)
    monkeypatch.setattr(lane, "QUEUE", queue)
    monkeypatch.setattr(lane.subprocess, "run", lambda *args, **kwargs: SimpleNamespace(
        stdout=output, stderr="", returncode=code))

    assert lane.accept("Snapshot", ["Code/FX.cpp"], "Snapshot.h", gate=lambda source: None) == (not passes)
    assert queue.read_text() == ("class\tsource\n" if passes else original)


def test_link_guard_has_no_verdict_without_checker(tmp_path, monkeypatch):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    assert lane.link_ok(["Code/FX.cpp"]) == {"Code/FX.cpp": None}


def test_bad_byte_gate_does_not_run_link_preview(tmp_path, monkeypatch):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    (tmp_path / "FX.cpp").write_text('#include "Snapshot.h"\n')
    (tmp_path / "Snapshot.h").touch()

    def unexpected(sources):
        raise AssertionError("link preview ran after byte failure")

    monkeypatch.setattr(lane, "link_ok", unexpected)
    assert lane.verdict("Snapshot", "FX.cpp", "Snapshot.h", gate=lambda source: "bytes differ") == ["bytes differ"]


# ---- merge blockers: the classes whose header unblocks the most merge donors rank first

CTOR_VIEW = """class Module { public: virtual ~Module(); };
class UpdateModule : public Module
{
public:
    UpdateModule();
    int m_phase;
};
"""
XFER_VIEW = """class UpdateModule
{
public:
    virtual int getModuleNameKey() const;   // slot 0 of its own
    int m_phase;
};
"""
FAKE_VIEW = """struct UpdateModule
{
    void *m_vtable;
    int m_phase;
};
"""
SAME_VIEW = """class Helper { int a; };
"""


def test_view_signatures_read_head_bases_and_vtable_shape():
    sigs = lane.view_signatures(CTOR_VIEW + "// class Ghost : public X { };\n")
    assert sigs["UpdateModule"] == ("class", "", "public Module", False, False, "")
    assert lane.view_signatures(XFER_VIEW)["UpdateModule"][5] == "getModuleNameKey"
    assert sigs["Module"][4] is True and "Ghost" not in sigs
    assert lane.view_signatures(FAKE_VIEW)["UpdateModule"][3] is True
    assert lane.base_names("public BehaviorModule, public virtual UpdateModuleInterface, Pair<int, int>") == [
        "BehaviorModule", "UpdateModuleInterface", "Pair"]


def test_disagreement_names_the_first_blocking_kind():
    ctor, xfer, fake = (lane.view_signatures(t)["UpdateModule"] for t in (CTOR_VIEW, XFER_VIEW, FAKE_VIEW))
    assert lane.disagreement([ctor, xfer], False) == "base"
    assert lane.disagreement([xfer, fake], False) == "fake-vtable"
    assert lane.disagreement([xfer, ("class", "", "", False, False, "")], False) == "vfptr"
    assert lane.disagreement([xfer, ("class", "", "", False, True, "~UpdateModule")], False) == "vslot"
    assert lane.disagreement([("class", "", "public M", False, True, "a"), ("class", "", "public M", False, True, "b")],
                             False) is None                            # an override introduces no slot
    assert lane.disagreement([xfer, ("struct", "", "", False, True, "getModuleNameKey")], False) == "key/declspec"
    assert lane.disagreement([xfer, xfer], False) is None              # tu_views reconciles these
    assert lane.disagreement([xfer, xfer], True) == "canonical-copy"   # a registered class: the lane's work


def _queue(files):
    tus = {"Code/A.cpp": {"Code/A.cpp": [1], "Code/A_xfer.cpp": [1, 2]},
           "Code/B.cpp": {"Code/B.cpp": [1], "Code/B2.cpp": [1], "Code/B3.cpp": [1]}}
    return ([{"tu": t} for t in sorted(tus)], lambda tu: tus[tu], lambda f: files[f])


def test_compute_merge_blockers_counts_donors_rows_tus_and_bases():
    files = {"Code/A.cpp": CTOR_VIEW + SAME_VIEW, "Code/A_xfer.cpp": XFER_VIEW + SAME_VIEW,
             "Code/B.cpp": CTOR_VIEW + "class Coord3D { float x; };\n",
             "Code/B2.cpp": FAKE_VIEW + "class Coord3D { float x; };\n", "Code/B3.cpp": "int x;\n"}
    queue, donors_of, read = _queue(files)
    got = lane.compute_merge_blockers(queue, donors_of, read, canon={"Coord3D": "Coord3D.h"})
    assert sorted(got) == ["Coord3D", "UpdateModule"]                  # Helper agrees; Module is in one file per TU
    um = got["UpdateModule"]
    assert (um["donors"], um["rows"], um["tus"]) == (4, 5, ["Code/A.cpp", "Code/B.cpp"])
    assert um["kinds"] == {"base": 2} and um["bases"] == ["Module"]
    assert um["virtual"] is True and got["Coord3D"]["virtual"] is False    # XFER_VIEW declares a virtual
    assert got["Coord3D"]["kinds"] == {"canonical-copy": 1}


def test_merge_rank_lifts_prerequisites_and_drops_invented_bases():
    blockers = {"UpdateModule": {"donors": 50, "bases": ["BehaviorModule", "InventedBase"]},
                "BehaviorModule": {"donors": 5, "bases": ["Module"]},
                "Module": {"donors": 1, "bases": []},
                "Object": {"donors": 70, "bases": ["Thing"]},
                "Coord3D": {"donors": 2, "bases": []},
                "Lonely": {"donors": 3, "bases": []}}
    order = [("value types", ["Coord3D"]), ("object", ["Object"])]
    ranked = lane.merge_rank(blockers, {}, order)
    assert ranked == [("Coord3D", 70, 2), ("Object", 70, 70), ("Module", 50, 1),
                      ("BehaviorModule", 50, 5), ("UpdateModule", 50, 50), ("Lonely", 3, 3)]
    assert lane.merge_rank(blockers, {}, order) == ranked              # deterministic


@pytest.fixture
def merge_cache(tmp_path, monkeypatch):
    """The lane's merge cache in tmp_path, a fake tree state, and a counting compute."""
    directory = tmp_path / "cache" / "merge_blockers"
    monkeypatch.setattr(lane, "merge_cache_dir", lambda: directory)
    state = {"inputs": ("headA", ""), "ancestor": True, "calls": 0}
    monkeypatch.setattr(lane, "merge_inputs", lambda: state["inputs"])

    def git(*args, strip=True):
        if args[:2] == ("merge-base", "--is-ancestor"):
            return "" if state["ancestor"] else None
        return None
    monkeypatch.setattr(lane, "_git", git)

    def compute():
        state["calls"] += 1
        return {"classes": {"X": {"donors": state["calls"]}}, "destinations": {}}
    monkeypatch.setattr(lane, "compute_merge_payload", compute)
    return directory, state


def test_merge_cache_is_keyed_by_head_and_dirty_fingerprint_and_refreshable(merge_cache):
    _, state = merge_cache
    assert lane.merge_blockers() == {"X": {"donors": 1}}
    assert lane.merge_blockers() == {"X": {"donors": 1}} and state["calls"] == 1
    assert lane.merge_blockers(refresh=True) == {"X": {"donors": 2}}
    state["inputs"] = ("headA", "f00d")                                # same HEAD, Code/ edited: a miss
    assert lane.merge_blockers() == {"X": {"donors": 3}}


def test_merge_cache_reuses_an_ancestor_only_with_the_same_fingerprint(merge_cache):
    _, state = merge_cache
    lane.merge_blockers()                                              # clean headA
    state["inputs"] = ("headB", "beef")                                # headA is an ancestor, but dirty
    assert lane.merge_blockers() == {"X": {"donors": 2}} and state["calls"] == 2
    state["inputs"] = ("headC", "")                                    # clean reuses clean headA
    assert lane.merge_blockers() == {"X": {"donors": 1}} and state["calls"] == 2
    state["inputs"] = ("headD", "beef")                                # dirty reuses the same dirt only
    assert lane.merge_blockers() == {"X": {"donors": 2}} and state["calls"] == 2
    state["ancestor"] = False
    state["inputs"] = ("headE", "")
    assert lane.merge_blockers() == {"X": {"donors": 3}}


def test_merge_cache_ignores_an_entry_of_another_payload_version(merge_cache, monkeypatch):
    _, state = merge_cache
    lane.merge_blockers()
    monkeypatch.setattr(lane, "MERGE_PAYLOAD_VERSION", lane.MERGE_PAYLOAD_VERSION + 1)
    state["inputs"] = ("headB", "")                                    # neither exact nor ancestor reuse
    assert lane.cached_merge_payload(("headA", "")) is None and lane.cached_merge_payload(state["inputs"]) is None
    assert lane.merge_blockers() == {"X": {"donors": 2}}


def test_porcelain_z_keeps_the_first_path_whole_and_both_rename_paths():
    status = " M Code/x.cpp\0R  Code/new.cpp\0Code/old.cpp\0?? reverse/n.csv\0"
    assert lane.porcelain_paths(status) == [(" M", "Code/x.cpp"), ("R ", "Code/new.cpp"), ("R ", "Code/old.cpp"),
                                            ("??", "reverse/n.csv")]


def test_merge_inputs_fingerprint_follows_the_first_dirty_file(tmp_path, monkeypatch):
    (tmp_path / "Code").mkdir()
    edited = tmp_path / "Code/x.cpp"
    edited.write_text("int a;\n")
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    answers = {("rev-parse", "HEAD"): "head", ("config", "-f", ".gitmodules", "--get-regexp", r"\.path$"): ""}

    def git(*args, strip=True):
        if args[0] == "status":
            assert strip is False and "-z" in args
            return " M Code/x.cpp\0"
        return answers.get(args)
    monkeypatch.setattr(lane, "_git", git)
    before = lane.merge_inputs()
    edited.write_text("int b;\n")
    after = lane.merge_inputs()
    assert before[0] == after[0] == "head" and before[1] and before[1] != after[1]


def _apply_run(tmp_path, monkeypatch, claim_result, released):
    """run --apply of a fixed header over two census units whose tournament passes both."""
    import json
    import claims
    import class_contract
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    monkeypatch.setattr(lane, "SCRATCH", tmp_path / "build/header_lane")
    monkeypatch.setattr(lane, "QUEUE", tmp_path / "header_queue.tsv")
    monkeypatch.setattr(class_contract, "CONTRACTS", tmp_path / "contracts")
    units = ["Code/A.cpp", "Code/Elsewhere/NoRows.cpp"]
    for unit in units:
        (tmp_path / unit).parent.mkdir(parents=True, exist_ok=True)
        (tmp_path / unit).write_text("struct Coord3D { float x, y, z; };\n")
    monkeypatch.setattr(class_contract, "census", lambda name: list(units))
    path = class_contract.contract_path("Coord3D")
    path.parent.mkdir()
    path.write_text(json.dumps({**CONTRACT, "queue": []}), encoding="utf-8")
    monkeypatch.setattr(lane, "tournament", lambda *a, **k: {"registered": {
        "verdicts": dict.fromkeys(units), "seconds": 0.0, "header": "", "renames": {},
        "texts": {u: '#include "Coord3D.h"\n' for u in units}}})
    registered = []
    monkeypatch.setattr(lane, "register", lambda *a: registered.append(a))
    monkeypatch.setattr(lane, "write_queue", lambda *a: None)
    asked = []

    def claim(keys, **kwargs):
        asked.append((list(keys), kwargs.get("atomic_only")))
        return claim_result(keys)
    monkeypatch.setattr(claims, "claim", claim)
    monkeypatch.setattr(claims, "release", lambda keys, **k: released.extend(keys) or list(keys))
    monkeypatch.setattr(claims, "_blocking_records", lambda root=None: [
        {claims.key_of("file:Code/Elsewhere/NoRows.cpp"): {"owner": "seat-7"}}])
    args = type("A", (), {"name": "Coord3D", "header": "Coord3D.h", "generate": False, "sample": None, "seed": 1,
                          "jobs": 1, "variants": "data", "apply": True})()
    return lane.run(args), units, asked, registered


def test_apply_refuses_when_a_census_unit_is_held_by_another_seat(tmp_path, monkeypatch, capsys):
    import claims
    held = claims.key_of("file:Code/Elsewhere/NoRows.cpp")
    released = []
    code, units, asked, registered = _apply_run(
        tmp_path, monkeypatch, lambda keys: claims.ClaimResult([], [held]), released)
    assert code == 3 and not registered
    assert asked == [(["file:Code/A.cpp", "file:Code/Elsewhere/NoRows.cpp"], True)]   # all or nothing
    assert all((tmp_path / u).read_text().startswith("struct Coord3D") for u in units)  # nothing rewritten
    out = capsys.readouterr().out
    assert "refusing to apply" in out and "Code/Elsewhere/NoRows.cpp (seat-7)" in out
    assert not (tmp_path / "build/header_lane/Coord3D.claims").exists()


def test_apply_claims_the_units_it_rewrites_and_release_gives_them_back(tmp_path, monkeypatch, capsys):
    import claims
    released = []
    code, units, asked, registered = _apply_run(
        tmp_path, monkeypatch, lambda keys: claims.ClaimResult([claims.key_of(k) for k in keys], []), released)
    assert code == 0 and registered
    assert all((tmp_path / u).read_text().startswith("#include") for u in units)
    assert "header_adopt_lane.py release --class Coord3D" in capsys.readouterr().out
    assert lane.main(["release", "--class", "Coord3D"]) == 0
    assert released == ["file:Code/A.cpp", "file:Code/Elsewhere/NoRows.cpp"]
    assert not (tmp_path / "build/header_lane/Coord3D.claims").exists()


def test_header_destination_takes_one_official_path_and_never_guesses(tmp_path):
    bfme1, zh = (tmp_path / tree for _, tree in lane.REFERENCE_HEADER_TREES)
    for base, rel, text in ((bfme1, "GameEngine/Include/GameLogic/Module/UpgradeModule.h", "class UpgradeModule { };\n"),
                            (zh, "GameEngine/Include/GameLogic/Module/UpgradeModule.h", "class UpgradeModule { };\n"),
                            (zh, "GameEngine/Include/Common/Team.h", "class Team { };\nclass TeamA { };\n"),
                            (zh, "GameEngine/Include/Common/Team2.h", "class TeamA { };\n"),
                            (zh, "GameEngine/Include/Common/Fwd.h", "class Absent;\n")):
        (base / rel).parent.mkdir(parents=True, exist_ok=True)
        (base / rel).write_text(text)
    index = lane.reference_header_index(root=tmp_path)
    none = lambda p: False                                             # noqa: E731
    got = lane.header_destination("UpgradeModule", index, none)
    assert got["header"] == "Code/GameEngine/Include/GameLogic/Module/UpgradeModule.h"
    assert got["evidence"].startswith("bfme1: ")                       # BFME 1 before ZH
    assert lane.header_destination("Team", index, none)["header"] == "Code/GameEngine/Include/Common/Team.h"
    assert lane.header_destination("TeamA", index, none)["header"] is None    # two headers: ambiguous
    assert lane.header_destination("Absent", index, none)["header"] is None   # a declaration is no definition
    occupied = lane.header_destination("Team", index, lambda p: True)
    assert occupied["header"] is None and "overwrite" in occupied["why"]


def test_header_destination_prefers_the_header_named_for_the_class(tmp_path):
    bfme1 = tmp_path / lane.REFERENCE_HEADER_TREES[0][1]
    for rel, text in (("GameEngine/Source/GameLogic/Object/object.h", "class Object : public Thing { int a; };\n"),
                      ("GameEngine/Source/GameLogic/Object/ObjectStatusBits.h", "class Object { char pad[4]; };\n"),
                      ("A/Twice.h", "class Pair { };\n"), ("B/Twice.h", "class Pair { };\n"),
                      ("C/pair.h", "class Pair2 { };\n"), ("D/pair2.h", "class Pair2 { };\n"),
                      ("E/pair2.h", "class Pair2 { };\n")):
        (bfme1 / rel).parent.mkdir(parents=True, exist_ok=True)
        (bfme1 / rel).write_text(text)
    index = lane.reference_header_index(root=tmp_path)
    got = lane.header_destination("Object", index, lambda p: False)
    assert got["header"] == "Code/GameEngine/Source/GameLogic/Object/object.h"
    assert "named for the class" in got["evidence"] and "ObjectStatusBits.h" in got["evidence"]
    assert lane.header_destination("Pair", index, lambda p: False)["header"] is None    # no header named Pair
    assert lane.header_destination("Pair2", index, lambda p: False)["header"] is None   # two named pair2.h


def test_picker_never_computes_and_starts_one_refresh(merge_cache, monkeypatch):
    directory, state = merge_cache
    monkeypatch.setattr(lane, "compute_merge_payload", lambda: pytest.fail("the picker computed the ranking"))
    monkeypatch.setattr(lane, "refresh_allowed", lambda: True)
    spawned = []
    monkeypatch.setattr(lane, "_spawn_detached", spawned.append)
    payload, note = lane.merge_payload_nonblocking()
    assert payload is None and "DEPENDENCY_ORDER only" in note and "refresh started" in note
    assert len(spawned) == 1 and "refresh-merges" in spawned[0] and (directory / "refresh.lock").exists()
    payload, note = lane.merge_payload_nonblocking()                   # the lock holds: no duplicate
    assert payload is None and "already running" in note and len(spawned) == 1
    old = time.time() - lane.MERGE_LOCK_SECONDS - 60                   # a dead refresh's lock is taken over
    os.utime(directory / "refresh.lock", (old, old))
    lane.merge_payload_nonblocking()
    assert len(spawned) == 2
    lane.store_merge_payload(state["inputs"], {"classes": {"X": {"donors": 9}}})
    assert lane.merge_payload_nonblocking() == ({"classes": {"X": {"donors": 9}}}, "")


def test_no_background_refresh_under_pytest_or_ci(tmp_path, monkeypatch):
    assert not lane.refresh_allowed()                                  # PYTEST_CURRENT_TEST is set here
    monkeypatch.delenv("PYTEST_CURRENT_TEST", raising=False)
    monkeypatch.setenv("CI", "true")
    assert not lane.refresh_allowed()
    assert "no background refresh" in lane.start_refresh(tmp_path, spawn=lambda c: pytest.fail("spawned"))
    assert not (tmp_path / "refresh.lock").exists()


def test_header_classes_follow_local_includes(tmp_path, monkeypatch):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    (tmp_path / "Inc" / "Mod").mkdir(parents=True)
    (tmp_path / "Inc" / "Base.h").write_text("class Base { int b; };\n")
    (tmp_path / "Inc" / "Mod" / "Mid.h").write_text('#include "../Base.h"\n#include <string.h>\nclass Mid : public Base { };\n')
    (tmp_path / "Inc" / "Mod" / "Leaf.h").write_text('#include "Mid.h"\n// #include "Gone.h"\nclass LeafIface { };\nclass Leaf : public Mid { };\n')
    assert lane.header_classes("Inc/Mod/Leaf.h") == ["LeafIface", "Leaf", "Mid", "Base"]
    assert lane.header_classes("Inc/Missing.h") == []


def test_tournament_strips_every_class_the_header_brings(tmp_path, monkeypatch):
    monkeypatch.setattr(lane, "ROOT", tmp_path)
    (tmp_path / "Leaf.h").write_text("class Base { };\nclass Leaf : public Base { };\n")
    seen = []
    monkeypatch.setattr(lane, "try_unit", lambda s, strip, header, key: seen.append(list(strip)) or (s, None, "", []))
    monkeypatch.setattr(lane, "try_renamed", lambda items, jobs: {})
    monkeypatch.setattr(lane, "registered", lambda: {})
    lane.tournament("Leaf", {"fields": [], "key": "class"}, ["u.cpp"], "Leaf.h", ["registered"], 1, fixed_header=True)
    assert seen == [["Leaf", "Base"]]
