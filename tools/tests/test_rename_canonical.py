"""Renaming a class registered in reverse/canonical_classes.csv.

The gate credits first: tools/class_gate.py and tools/repair_queue.py accept a
registered class's private views and header_queue.tsv rows respelled in place
only when the change records an approved rename (a name_basis.csv
`class,OLD,NEW` row, the one registry key moved under the same header, and
HEAD's own rename.py verify-record accepting the record's approval), only for
HEAD's copy of the same path, and only for that class. Real throwaway git repositories; the
real gate runs against their index. Then the naming route (name_lane serves a
registered placeholder's class and member keys from its canonical header;
name_evidence may grade it), and tools/rename.py class / member on a registered
class: the key, contract and header_queue rows move, everything rolls back, and
what it cannot move refuses. Verification is injected."""
import importlib
import os
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import class_gate  # noqa: E402
import class_views  # noqa: E402
from test_name_lane_registered import (  # noqa: E402,F401  (the fixture and its tree)
    CONTRACT, CTOR, SLOT, SOUND, TREE, VFTABLE, lane_of, registered)

OLD, NEW = "Rva00401000Base", "FXNugget"
HEADER = "Code/Game/Rva00401000Base.h"
BASIS = "kind,old,new,basis,evidence,source,rva\n"
RECORD = f"class,{OLD},{NEW},canonical:zh,ZH FXList.h,{HEADER},\n"
REGISTRY = "class,header,notes\n"
OLD_KEY = f"{OLD},{HEADER},contract class_contracts/{OLD}.json\n"
NEW_KEY = f"{NEW},{HEADER},contract class_contracts/{NEW}.json\n"
VIEW = "class {cls} {{\npublic:\n    int m_nuggetType;\n    void run();\n}};\nvoid {cls}::run() {{ m_nuggetType = 1; }}\n"
UNIT = "Code/Game/SoundFXNugget.cpp"


def run(root, *args):
    return subprocess.run(["git", *args], cwd=root, capture_output=True, text=True, check=True)


def write(root, rel, text):
    path = root / rel
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_bytes(text.encode("latin-1"))


# ---------------------------------------------------------------- the record

@pytest.mark.parametrize("basis,registry,expected", [
    (BASIS + RECORD, REGISTRY + NEW_KEY, {OLD: NEW}),
    (BASIS, REGISTRY + NEW_KEY, {}),                                            # no record
    (BASIS + RECORD, REGISTRY + OLD_KEY, {}),                                   # key not moved
    (BASIS + RECORD, REGISTRY + OLD_KEY + NEW_KEY, {}),                         # OLD still registered
    (BASIS + RECORD, REGISTRY + NEW_KEY.replace(HEADER, "Code/Game/Other.h"), {}),   # header changed
    (BASIS + RECORD + RECORD.replace(NEW, "FXOther"), REGISTRY + NEW_KEY, {}),  # OLD towards two names
])
def test_a_rename_counts_only_when_recorded_and_the_key_moves(basis, registry, expected):
    assert class_gate.recorded_class_renames(BASIS, basis, REGISTRY + OLD_KEY, registry) == expected


def test_a_record_already_in_base_is_no_new_rename():
    assert class_gate.recorded_class_renames(BASIS + RECORD, BASIS + RECORD, REGISTRY + OLD_KEY,
                                             REGISTRY + NEW_KEY) == {}


def test_an_unregistered_class_record_credits_nothing():
    record = "class,Rva00402000Thing,Thing,inferred,agree:x,Code/Game/T.cpp,\n"
    assert class_gate.recorded_class_renames(BASIS, BASIS + record, REGISTRY + OLD_KEY, REGISTRY + OLD_KEY) == {}


# ---------------------------------------------------------------- class_gate

class Repo:
    def __init__(self, root, monkeypatch):
        self.root = root
        monkeypatch.setattr(class_gate, "ROOT", root)
        monkeypatch.setattr(class_views, "CANONICAL", root / "reverse" / "canonical_classes.csv")
        # the credit mechanics; the approval check itself runs for real in the approval tests
        monkeypatch.setattr(class_gate, "base_verify_record", lambda *a: (True, "stubbed"))
        run(root, "init", "-q")
        run(root, "config", "core.autocrlf", "false")
        run(root, "config", "user.email", "t@example.com")
        run(root, "config", "user.name", "t")
        write(root, "reverse/canonical_classes.csv", REGISTRY + OLD_KEY + "Widget,Code/Game/Widget.h,\n")
        write(root, "reverse/name_basis.csv", BASIS)
        write(root, "reverse/class_gate_mode.txt", "# mode: enforce\n")
        write(root, HEADER, VIEW.format(cls=OLD).split("void")[0])
        write(root, UNIT, VIEW.format(cls=OLD))
        write(root, "Code/Game/Plain.cpp", "int plain() { return 0; }\n")
        run(root, "add", "-A")
        run(root, "commit", "-q", "-m", "base")

    def rename(self, *, record=True, key=True):
        """What tools/rename.py class writes: the views, the key, the record."""
        for rel in (HEADER, UNIT):
            write(self.root, rel, (self.root / rel).read_text(encoding="latin-1").replace(OLD, NEW))
        if key:
            write(self.root, "reverse/canonical_classes.csv", REGISTRY + NEW_KEY + "Widget,Code/Game/Widget.h,\n")
        if record:
            write(self.root, "reverse/name_basis.csv", BASIS + RECORD)
        run(self.root, "add", "-A")

    def gate(self, capsys):
        capsys.readouterr()
        rc = class_gate.main(["--staged"])
        return rc, capsys.readouterr().err


@pytest.fixture
def repo(tmp_path, monkeypatch):
    return Repo(tmp_path, monkeypatch)


def test_a_recorded_rename_keeps_each_private_view(repo, capsys):
    repo.rename()
    assert repo.gate(capsys) == (0, "")


def test_an_unrecorded_rename_is_refused(repo, capsys):
    """The key moved to NEW but no name_basis.csv record says a rename did it."""
    repo.rename(record=False)
    rc, err = repo.gate(capsys)
    assert rc == 1 and f"{UNIT}: declares its own `{NEW}`" in err, err


def test_a_record_naming_an_unmoved_key_credits_nothing(repo, capsys):
    """The record names OLD -> NEW but the registry moves OLD to a third name."""
    repo.rename()
    write(repo.root, "reverse/canonical_classes.csv", REGISTRY + NEW_KEY + f"FXOther,{HEADER},\n"
          "Widget,Code/Game/Widget.h,\n")
    write(repo.root, UNIT, VIEW.format(cls="FXOther"))
    run(repo.root, "add", "-A")
    rc, err = repo.gate(capsys)
    assert rc == 1 and "declares its own `FXOther`" in err, err


def test_a_moved_unit_gets_no_credit(repo, capsys):
    repo.rename()
    run(repo.root, "mv", UNIT, "Code/Game/Moved.cpp")
    rc, err = repo.gate(capsys)
    assert rc == 1 and "Code/Game/Moved.cpp: declares its own `FXNugget`" in err, err


def test_a_unit_that_lacked_the_old_class_gets_no_credit(repo, capsys):
    repo.rename()
    write(repo.root, "Code/Game/Plain.cpp", VIEW.format(cls=NEW))
    run(repo.root, "add", "-A")
    rc, err = repo.gate(capsys)
    assert rc == 1 and "Code/Game/Plain.cpp: declares its own `FXNugget`" in err, err
    assert UNIT not in err


def test_the_credit_is_for_the_class_whose_key_moved(repo, capsys):
    """A unit that held OLD at HEAD may not also gain a copy of another registered class."""
    repo.rename()
    write(repo.root, UNIT, VIEW.format(cls=NEW) + "class Widget { int m_size; };\n")
    run(repo.root, "add", "-A")
    rc, err = repo.gate(capsys)
    assert rc == 1 and "declares its own `Widget`" in err and f"`{NEW}`" not in err, err


def test_an_old_view_respelled_as_another_class_gets_no_credit(repo, capsys):
    repo.rename()
    write(repo.root, UNIT, VIEW.format(cls="Widget"))
    run(repo.root, "add", "-A")
    rc, err = repo.gate(capsys)
    assert rc == 1 and "declares its own `Widget`" in err, err


def test_the_identity_check_credits_the_same_body(repo):
    repo.rename()
    renames = class_gate.approved_class_renames("HEAD", "")
    assert renames == {OLD: NEW}
    canon = {NEW: HEADER, "Widget": "Code/Game/Widget.h"}
    text = class_gate.git_text(f":{UNIT}")
    assert class_gate.introduced_identities(UNIT, text, canon, class_renames=renames) == []
    assert [k for k, _a, _w in class_gate.introduced_identities(UNIT, text, canon)] == [NEW]
    plain = VIEW.format(cls=NEW)
    assert [k for k, _a, _w in class_gate.introduced_identities("Code/Game/Plain.cpp", plain, canon,
                                                                class_renames=renames)] == [NEW]


# ---------------------------------------------------------------- repair_queue header debt

QUEUE_HEAD = "class\tsource\tretail_rvas\theader\tfailure\tretry_budget\tacceptance\n"


def queue_row(cls, source, rvas):
    return f"{cls}\t{source}\t{rvas}\t{HEADER}\tfield renames: m_nuggetType\t3\tpython3 tools/header_adopt_lane.py\n"


@pytest.fixture
def debt(tmp_path, monkeypatch):
    write(tmp_path, "reverse/functions.csv", "name,export_rva,target_rva,target_size,source,status,notes\n")
    write(tmp_path, "reverse/canonical_classes.csv", REGISTRY + OLD_KEY)
    write(tmp_path, "reverse/name_basis.csv", BASIS)
    write(tmp_path, "reverse/header_queue.tsv", QUEUE_HEAD + queue_row(OLD, UNIT, "0x00401000 0x00401040")
          + queue_row(OLD, "Code/Game/Other.cpp", "0x00402000"))
    write(tmp_path, UNIT, VIEW.format(cls=OLD))
    run(tmp_path, "init", "-q")
    run(tmp_path, "config", "core.autocrlf", "false")
    run(tmp_path, "add", "-A")
    run(tmp_path, "-c", "user.name=t", "-c", "user.email=", "commit", "-qm", "init")
    os.environ["REPAIR_ROOT"] = str(tmp_path)
    try:
        import repair_queue
        rq = importlib.reload(repair_queue)
    finally:
        del os.environ["REPAIR_ROOT"]
    # the credit mechanics; the approval check itself runs for real in the approval tests
    monkeypatch.setattr(rq, "_base_verified", lambda candidates: dict(candidates))

    def stage(queue, *, record=True, key=True):
        write(tmp_path, "reverse/header_queue.tsv", QUEUE_HEAD + queue)
        write(tmp_path, "reverse/canonical_classes.csv", REGISTRY + (NEW_KEY if key else OLD_KEY))
        write(tmp_path, "reverse/name_basis.csv", BASIS + (RECORD if record else ""))
        run(tmp_path, "add", "-A")
        return rq.removed_header_rows()
    return stage


def test_a_recorded_rename_carries_its_header_rows(debt):
    queue = queue_row(NEW, UNIT, "0x00401000 0x00401040") + queue_row(NEW, "Code/Game/Other.cpp", "0x00402000")
    assert debt(queue) == []


@pytest.mark.parametrize("record,key", [(False, True), (True, False)])
def test_an_unrecorded_rename_retires_nothing(debt, record, key):
    queue = queue_row(NEW, UNIT, "0x00401000 0x00401040") + queue_row(NEW, "Code/Game/Other.cpp", "0x00402000")
    assert debt(queue, record=record, key=key) == [(OLD, "Code/Game/Other.cpp"), (OLD, UNIT)]


def test_a_row_carried_to_another_source_is_removed_debt(debt):
    queue = queue_row(NEW, "Code/Game/Elsewhere.cpp", "0x00401000 0x00401040") + \
        queue_row(NEW, "Code/Game/Other.cpp", "0x00402000")
    assert debt(queue) == [(OLD, UNIT)]


def test_a_row_that_loses_an_rva_is_removed_debt(debt):
    queue = queue_row(NEW, UNIT, "0x00401000") + queue_row(NEW, "Code/Game/Other.cpp", "0x00402000")
    assert debt(queue) == [(OLD, UNIT)]


def test_a_dropped_row_is_still_removed_debt(debt):
    assert debt(queue_row(NEW, UNIT, "0x00401000 0x00401040")) == [(OLD, "Code/Game/Other.cpp")]


def test_another_class_gets_no_credit(debt):
    queue = queue_row("Widget", UNIT, "0x00401000 0x00401040") + queue_row(NEW, "Code/Game/Other.cpp", "0x00402000")
    assert debt(queue) == [(OLD, UNIT)]


def test_repair_queue_keeps_class_gates_rule_inline(debt, tmp_path):
    """The inline copy (the hooks run repair_queue's base copy through stdin) agrees."""
    debt(queue_row(NEW, UNIT, "0x00401000 0x00401040"))
    import repair_queue as rq
    show = lambda rev, rel: run(tmp_path, "show", f"{rev}:{rel}").stdout  # noqa: E731
    texts = [show(rev, rel) for rev, rel in (("HEAD", "reverse/name_basis.csv"), ("", "reverse/name_basis.csv"),
                                              ("HEAD", "reverse/canonical_classes.csv"),
                                              ("", "reverse/canonical_classes.csv"))]
    assert rq.recorded_class_renames() == class_gate.recorded_class_renames(*texts) == {OLD: NEW}


# ---------------------------------------------------------------- rename.py class on a registered class

@pytest.fixture
def evidence_stubbed(monkeypatch):
    """The agreement-record and canonical-evidence gates have their own tests."""
    import rename
    monkeypatch.setattr(rename, "check_agreement", lambda *a, **k: None)
    monkeypatch.setattr(rename, "check_canonical", lambda *a, **k: None)
    monkeypatch.setattr(rename, "check_registered_basis",
                        lambda ctx, header, basis, evidence, old, new: rename.basis_kind(basis))
    return rename


def plan_of(root, kind="class", **kwargs):
    import rename
    kwargs.setdefault("basis", "inferred")
    kwargs.setdefault("evidence", "agree:abc")
    if kind == "class":
        kwargs.setdefault("name", OLD)
        kwargs.setdefault("new", NEW)
    return rename.plan_rename(kind, ctx=rename.Context(root, object_scan=False), **kwargs)


def after(plan, rel):
    return plan.after[rel].decode("utf-8")


def snapshot(root):
    files = {p.relative_to(root).as_posix(): p.read_bytes()
             for p in root.rglob("*") if p.is_file() and ".git" not in p.parts}
    files.pop("reverse/.add_match.lock", None)
    return {k: v for k, v in files.items() if not k.startswith("build/")}


def test_the_registration_moves_with_the_class(registered, evidence_stubbed):
    p = plan_of(registered)
    registry = after(p, "reverse/canonical_classes.csv")
    assert f"{NEW},{HEADER},contract class_contracts/{NEW}.json\n" in registry and f"\n{OLD}," not in registry
    assert "Coord3D,Code/Game/Coord3D.h,readable" in registry
    assert p.moves == [(CONTRACT, f"reverse/class_contracts/{NEW}.json")]
    import json
    contract = json.loads(after(p, f"reverse/class_contracts/{NEW}.json"))
    assert contract["class"] == NEW and contract["vslots"] == {"1": f"?doFX@{NEW}@@UBEXXZ"}
    queue = after(p, "reverse/header_queue.tsv").splitlines()
    assert queue[1].split("\t")[:3] == [NEW, SOUND, "0x00401100"]
    assert f"class {NEW}\n" in after(p, HEADER) and "int m_04;" in after(p, HEADER)
    assert f"class SoundFXNugget : public {NEW}" in after(p, SOUND)       # the private view follows
    rows = after(p, "reverse/functions.csv")
    assert f"??0{NEW}@@QAE@XZ,,0x00401000" in rows and f"?doFX@{NEW}@@UBEXXZ,,0x00401040" in rows
    assert f"calls ??0{NEW}@@QAE@XZ" in rows and OLD not in rows
    assert f"??_7{NEW}@@6B@,0x00A01000" in after(p, "reverse/data_rows.csv")
    assert after(p, "reverse/name_basis.csv").splitlines()[-1].startswith(f"class,{OLD},{NEW},inferred,agree:abc,")
    tombs = after(p, "reverse/deleted_rows.csv")
    assert f"{CTOR},0x00401000" in tombs and f"{VFTABLE},0x00A01000" in tombs
    assert p.verify == ["Code/Game/BaseCtor.cpp", "Code/Game/BaseSlots.cpp", SOUND]
    assert p.registered["old"] == OLD and p.registered["header"] == HEADER
    assert CONTRACT not in p.mentions and "reverse/header_queue.tsv" not in p.mentions
    assert any("file name spells" in w for w in p.warnings)                 # the header keeps its path
    base = {rel: (registered / rel).read_text() for rel in ("reverse/name_basis.csv", "reverse/canonical_classes.csv")}
    assert class_gate.recorded_class_renames(base["reverse/name_basis.csv"], after(p, "reverse/name_basis.csv"),
                                             base["reverse/canonical_classes.csv"], registry) == {OLD: NEW}


def test_apply_moves_the_contract_and_rolls_everything_back(registered, evidence_stubbed, monkeypatch):
    rename = evidence_stubbed
    before = snapshot(registered)
    monkeypatch.setattr(rename, "registered_object_problems", lambda ctx, plan: [])
    p = plan_of(registered)
    rename.apply_rename(p, ctx=rename.Context(registered, object_scan=False),
                        verify=lambda ctx, sources: True, checks=None)
    assert not (registered / CONTRACT).exists() and (registered / f"reverse/class_contracts/{NEW}.json").exists()
    assert run(registered, "diff", "--cached", "--name-status", "-M").stdout.startswith("R")   # git mv, not a copy
    run(registered, "reset", "-q", "--hard")
    run(registered, "clean", "-qfdx")
    assert snapshot(registered) == before
    p = plan_of(registered)
    with pytest.raises(rename.VerifyFailed):
        rename.apply_rename(p, ctx=rename.Context(registered, object_scan=False),
                            verify=lambda ctx, sources: False, checks=None)
    assert snapshot(registered) == before


def test_recover_restores_a_killed_run_with_the_moved_contract(registered, evidence_stubbed):
    """A run killed after its writes: the journal puts the contract back at its own
    path with its own bytes, not the respelled ones the move carried."""
    rename = evidence_stubbed
    before = snapshot(registered)
    ctx = rename.Context(registered, object_scan=False)
    p = plan_of(registered)
    rename.write_journal(ctx, p)
    for old, new in p.moves:
        run(registered, "mv", old, new)
    for rel, data in p.after.items():
        write(registered, rel, data.decode("utf-8"))
    (path, record), = list(rename.journals(ctx))
    rename.restore_journal(ctx, record)
    path.unlink()
    assert snapshot(registered) == before


def test_a_stale_object_symbol_rolls_the_rename_back(registered, evidence_stubbed, monkeypatch):
    rename = evidence_stubbed
    before = snapshot(registered)
    monkeypatch.setattr(rename, "registered_object_problems",
                        lambda ctx, plan: [f"Code/Game/BaseCtor.cpp's object still names {CTOR}"])
    with pytest.raises(rename.VerifyFailed, match="still names"):
        rename.apply_rename(plan_of(registered), ctx=rename.Context(registered, object_scan=False),
                            verify=lambda ctx, sources: True, checks=None)
    assert snapshot(registered) == before


def test_registered_object_problems_reads_each_rebuilt_object(registered, evidence_stubbed, monkeypatch):
    rename = evidence_stubbed
    import build
    import reloc_ledger
    p = plan_of(registered)
    objects = {"BaseCtor": [f"??0{NEW}@@QAE@XZ", f"??_7{NEW}@@6B@"], "BaseSlots": [f"?doFX@{OLD}@@UBEXXZ"],
               "SoundFXNugget": [f"??0{NEW}@@QAE@XZ"]}
    monkeypatch.setattr(build, "obj_path", lambda path: path.with_suffix(".obj"))
    for stem in objects:
        (registered / f"Code/Game/{stem}.obj").write_bytes(stem.encode())
    monkeypatch.setattr(reloc_ledger, "parse_coff", lambda data: ({}, {
        i: {"name": n} for i, n in enumerate(objects[data.decode()])}))
    assert rename.registered_object_problems(rename.Context(registered, object_scan=False), p) == [
        f"Code/Game/BaseSlots.cpp's object still names ?doFX@{OLD}@@UBEXXZ"]


@pytest.mark.parametrize("edit,message", [
    (("reverse/canonical_classes.csv", REGISTRY + OLD_KEY + f"{NEW},Code/Game/X.h,\n"), "registered in"),
    ((f"reverse/class_contracts/{NEW}.json", '{"class": "%s"}\n' % NEW), "registered in"),
    ((CONTRACT, '{"class": "Rva00409999Other"}\n'), "is the contract of Rva00409999Other"),
    ((CONTRACT, None), "is missing"),
    (("reverse/canonical_classes.csv", REGISTRY + OLD_KEY + OLD_KEY), "registers Rva00401000Base 2 times"),
    (("reverse/canonical_classes.csv", REGISTRY), "orphan contract"),
    (("reverse/gate_baseline.txt", f"{SOUND}\t{CTOR}\n"), "frozen, shrink-only"),
])
def test_a_registration_it_cannot_move_refuses(registered, evidence_stubbed, edit, message):
    rel, text = edit
    if text is None:
        (registered / rel).unlink()
    else:
        write(registered, rel, text)
    run(registered, "add", "-A")
    with pytest.raises(evidence_stubbed.Refusal, match=message):
        plan_of(registered)


def test_a_readable_registered_class_refuses(registered, evidence_stubbed):
    write(registered, "reverse/class_contracts/Coord3D.json", '{"class": "Coord3D"}\n')
    run(registered, "add", "-A")
    with pytest.raises(evidence_stubbed.Refusal, match="placeholder|readable|real"):
        plan_of(registered, name="Coord3D", new="Coord3DView")


def test_fold_of_a_registered_class_still_refuses(registered, evidence_stubbed):
    import rename
    with pytest.raises(rename.Refusal, match="registered"):
        rename.plan_rename("class", ctx=rename.Context(registered, object_scan=False), name=OLD, new="SoundFXNugget",
                           fold=True, basis=None, evidence="")


def test_the_rename_needs_approval_evidence(registered):
    import rename
    with pytest.raises(rename.Refusal):
        plan_of(registered, evidence="")
    with pytest.raises(rename.Refusal):
        plan_of(registered, basis="canonical:zh", evidence="FXList.h says so")


# ---------------------------------------------------------------- --merge-existing

LIST = "Code/Game/FXList.cpp"
LIST_SRC = (f"// cl: /O2\nclass {NEW};\nclass FXList {{ public: void addFXNugget({NEW} *nugget); }};\n"
            f"void FXList::addFXNugget({NEW} *nugget) {{ (void)nugget; }}\n")
ADD = f"?addFXNugget@FXList@@QAEXPAV{NEW}@@@Z"


@pytest.fixture
def spelled(registered):
    """NEW is already spelled as a type: a forward declaration and a parameter type."""
    write(registered, LIST, LIST_SRC)
    with open(registered / "reverse/functions.csv", "ab") as handle:
        handle.write(f"{ADD},,0x00402000,16,{LIST},matched,\n".encode("utf-8"))
    run(registered, "add", "-A")
    return registered


def test_a_spelled_new_name_needs_merge_existing(spelled, evidence_stubbed):
    with pytest.raises(evidence_stubbed.Refusal, match="--merge-existing"):
        plan_of(spelled)


def test_merge_existing_takes_a_new_spelled_only_as_a_type(spelled, evidence_stubbed):
    p = plan_of(spelled, basis="canonical:zh", evidence="zh cite", merge=True)
    assert LIST not in p.after                                   # NEW's own spellings stay as they are
    assert ADD in after(p, "reverse/functions.csv")
    assert f"??0{NEW}@@QAE@XZ,,0x00401000" in after(p, "reverse/functions.csv")
    assert any("merged into FXNugget" in m for m in p.registered["moved"])


def test_merge_existing_takes_an_inferred_basis(spelled, evidence_stubbed):
    """Allowed because the revert is exact (the reversed landing diff): see the revert tests."""
    p = plan_of(spelled, merge=True)
    assert p.basis == "inferred" and LIST not in p.after


def test_merge_existing_needs_a_registered_class(spelled, evidence_stubbed):
    write(spelled, "Code/Game/Lone.cpp", "struct Rva00405000Lone { int a; };\nint lone(Rva00405000Lone *p) { return p->a; }\n")
    with open(spelled / "reverse/functions.csv", "ab") as handle:
        handle.write("?lone@@YAHPAURva00405000Lone@@@Z,,0x00405000,8,Code/Game/Lone.cpp,matched,\n".encode("utf-8"))
    run(spelled, "add", "-A")
    with pytest.raises(evidence_stubbed.Refusal, match="not registered"):
        plan_of(spelled, name="Rva00405000Lone", new="Lone", basis="canonical:zh", evidence="x", merge=True)


def test_merge_existing_refuses_a_second_body(spelled, evidence_stubbed):
    write(spelled, LIST, LIST_SRC + f"class {NEW} {{ public: virtual void doFX() const; }};\n"
                                    f"void {NEW}::doFX() const {{}}\n")
    run(spelled, "add", "-A")
    with pytest.raises(evidence_stubbed.Refusal, match=r"FXList.cpp spells FXNugget::doFX\("):
        plan_of(spelled, basis="canonical:zh", evidence="zh cite", merge=True)


@pytest.mark.parametrize("row", [f"?run@{NEW}@@QAEXXZ", f"??_7{NEW}@@6B@", NEW])
def test_merge_existing_refuses_a_new_name_that_owns_a_row(spelled, evidence_stubbed, row):
    with open(spelled / "reverse/symbols.csv", "ab") as handle:
        handle.write(f"{row},0x00403000,pin\n".encode("utf-8"))
    run(spelled, "add", "-A")
    with pytest.raises(evidence_stubbed.Refusal, match="scopes|identifier"):
        plan_of(spelled, basis="canonical:zh", evidence="zh cite", merge=True)


VIEWS = "Code/Game/NuggetViews.cpp"


def defined(root, body):
    """A unit outside the rewrite with its own definition of NEW."""
    write(root, VIEWS, f"// cl: /O2\nclass {NEW} {{\npublic:\n    virtual void play();\n{body}}};\n"
                       f"int nuggetType({NEW} *n);\n")
    with open(root / "reverse/functions.csv", "ab") as handle:
        handle.write(f"?nuggetType@@YAHPAV{NEW}@@@Z,,0x00404000,8,{VIEWS},matched,\n".encode("utf-8"))
    run(root, "add", "-A")
    run(root, "-c", "user.name=t", "-c", "user.email=", "commit", "-qm", "a private view of NEW")   # clean, as prepared needs


def layouts(monkeypatch, rename, fields, size, **layout):
    """What the compiler would report for VIEWS (view_layouts reads CodeView); `layout`
    overrides keys of the reported layout, or replaces it entirely with `whole=`."""
    seen = []
    whole = layout.pop("whole", None)

    def fake(ctx, unit):
        seen.append(unit)
        reported = dict({"vfptr": True, "bases": [], "fields": fields, "size": size, "fwd": False}, **layout)
        member = {"fwd": False, "size": 4, "bases": [], "vfptr": False, "fields": [[0, "m_val", "int", 4]]}
        return {NEW: whole if whole is not None else reported,
                "Coord2D": {"fwd": False, "size": 8, "bases": [], "vfptr": False,
                            "fields": [[0, "x", "float", 4], [4, "y", "float", 4]]},
                "FwdOnly": {"fwd": True},
                "Polymorphic": dict(member, vfptr=True),
                "Based": dict(member, bases=[["Coord2D", 0]]),
                "VirtualBased": dict(member, bases=[["virtual Coord2D", -1]])}
    monkeypatch.setattr(rename, "view_layouts", fake)
    return seen


def test_merge_existing_compares_each_definition_with_the_contract(spelled, evidence_stubbed, monkeypatch):
    defined(spelled, "    int m_nuggetType;\n    int m_08;\n")
    seen = layouts(monkeypatch, evidence_stubbed, [[4, "m_nuggetType", "int", 4], [8, "m_08", "int", 4]], 12)
    p = plan_of(spelled, basis="canonical:zh", evidence="zh cite", merge=True)
    assert seen == [VIEWS] and VIEWS in p.verify and VIEWS not in p.after


@pytest.mark.parametrize("fields,size,layout,message", [
    ([[4, "unrelated", "double[20]", 160]], 164, {}, r"unrelated \(double\[20\]\) is not a scalar"),
    ([[4, "m_nuggetType", "int[1]", 4]], 8, {}, r"m_nuggetType \(int\[1\]\) is not a scalar"),   # arrays never compare
    ([[4, "m_inner", "Hidden", 4]], 8, {}, r"m_inner \(Hidden\) is not a scalar"),             # not in the stream
    ([[4, "m_inner", "FwdOnly", 4]], 8, {}, r"m_inner \(FwdOnly\) is not a scalar"),           # forward-only
    ([[4, "m_inner", "Polymorphic", 4]], 8, {}, r"m_inner \(Polymorphic\) is not a scalar"),   # has a vfptr
    ([[4, "m_inner", "Based", 4]], 8, {}, r"m_inner \(Based\) is not a scalar"),               # has a base
    ([[4, "m_inner", "VirtualBased", 4]], 8, {}, r"m_inner \(VirtualBased\) is not a scalar"), # unresolved vbase
    ([[4, "m_pos", "Coord2D", 4]], 8, {}, r"m_pos \(Coord2D\) is not a scalar"),               # another size
    ([[4, "m_nuggetType", "float", 4]], 8, {}, r"at \+0x4 is 4 B f4; the contract has m_nuggetType, 4 B i4"),
    ([[4, "reservedActualData", "float", 4]], 8, {}, r"reservedActualData at \+0x4"),     # never padding
    ([[4, "m_type", "int", 4]], 8, {}, r"m_type at \+0x4 is 4 B i4; the contract has m_nuggetType"),
    ([[4, "m_nuggetType", "int", 4], [12, "m_extra", "int", 4]], 16, {}, r"m_extra \(4 B i4, \+0xC\) is a field"),
    ([[4, "m_nuggetType", "int", 4]], 20, {}, "over the contract's 12"),
    ([[4, "m_nuggetType", "int", 4]], 8, {"vfptr": False}, r"m_nuggetType|lacks the vfptr"),
    ([[4, "m_nuggetType", "bitfield", 0]], 8, {}, "bitfield"),
    ([[4, "m_nuggetType", "int", 4]], 8, {"bases": [["virtual Rva00406000Base", -1]]}, "has bases"),
    ([[4, "m_pos", "Coord2D", 8]], 12, {}, r"m_pos\.x"),                                   # an aggregate's scalars
    ([], 8, {"whole": {"fwd": True}}, "no complete layout"),
    ([], 8, {"unparsed": 0x1234}, "no complete layout"),
])
def test_merge_existing_refuses_a_definition_unlike_the_contract(spelled, evidence_stubbed, monkeypatch,
                                                                 fields, size, layout, message):
    defined(spelled, "".join(f"    {t} {n};\n" for _o, n, t, _s in fields) or "    int m_any;\n")
    layouts(monkeypatch, evidence_stubbed, fields, size, **layout)
    with pytest.raises(evidence_stubbed.Refusal, match=message):
        plan_of(spelled, basis="canonical:zh", evidence="zh cite", merge=True)


RESHAPED = f'// cl: /O2\n#include "{OLD}.h"\nint nuggetType({NEW} *n) {{ return n->m_08; }}\n'


def never_compiled(monkeypatch, rename):
    """A prepared unit is part of the rewrite: merge_definitions must not compile it."""
    def refuse(ctx, unit):
        raise AssertionError(f"compiled {unit}")
    monkeypatch.setattr(rename, "view_layouts", refuse)


def test_prepared_units_join_a_merge_and_are_verified(spelled, evidence_stubbed, monkeypatch):
    defined(spelled, "    int m_nuggetType;\n")                  # VIEWS defines its own FXNugget today
    never_compiled(monkeypatch, evidence_stubbed)
    p = plan_of(spelled, merge=True, prepared={VIEWS: RESHAPED.encode()})
    assert p.after[VIEWS] == RESHAPED.encode() and p.source_counts[VIEWS] == {"prepared": 1}
    assert VIEWS in p.verify


@pytest.mark.parametrize("text,message", [
    (RESHAPED + f"class {OLD};\n", "still spells Rva00401000Base"),
    (RESHAPED + f"class {NEW} {{ public: int m_x; }};\n", "defines its own FXNugget"),
    (RESHAPED.replace(f'#include "{OLD}.h"\n', ""), "without #including its canonical header"),
    (RESHAPED + f"void {NEW}::doFX() const {{}}\n", r"FXNugget::doFX\(, a second body"),
])
def test_a_prepared_unit_must_name_the_class_through_its_header(spelled, evidence_stubbed, monkeypatch,
                                                                text, message):
    defined(spelled, "    int m_nuggetType;\n")
    never_compiled(monkeypatch, evidence_stubbed)
    with pytest.raises(evidence_stubbed.Refusal, match=message):
        plan_of(spelled, merge=True, prepared={VIEWS: text.encode()})


CANONICAL_LAYOUT = {"fwd": False, "size": 12, "bases": [], "vfptr": True,
                    "fields": [[4, "m_04", "int", 4], [8, "m_08", "int", 4]]}
# a private copy no text scan sees: its include is compiled out, its head carries a __declspec
HIDDEN = (f'// cl: /O2\n#if 0\n#include "{OLD}.h"\n#endif\n'
          f"class __declspec(align(4)) {NEW} {{ public: double m_unrelated[20]; }};\n"
          f"int nuggetType({NEW} *n) {{ return (int)n->m_unrelated[0]; }}\n")


def compiled(monkeypatch, rename, streams):
    """view_layouts as the compiler would answer after the build: `streams` maps a unit to
    its classes; the reference units (BaseCtor.cpp, BaseSlots.cpp) compile the canonical class."""
    seen = []

    def fake(ctx, unit):
        seen.append(unit)
        return streams.get(unit, {NEW: CANONICAL_LAYOUT})
    monkeypatch.setattr(rename, "view_layouts", fake)
    monkeypatch.setattr(rename, "registered_object_problems", lambda ctx, plan: [])
    return seen


def apply_prepared(root, rename, text):
    p = plan_of(root, merge=True, prepared={VIEWS: text.encode()})
    assert p.registered["references"] == ["Code/Game/BaseCtor.cpp", "Code/Game/BaseSlots.cpp"]
    return rename.apply_rename(p, ctx=rename.Context(root, object_scan=False), verify=lambda ctx, sources: True,
                               checks=None)


def test_a_prepared_unit_compiling_the_canonical_class_lands(spelled, evidence_stubbed, monkeypatch):
    defined(spelled, "    int m_nuggetType;\n")
    seen = compiled(monkeypatch, evidence_stubbed, {VIEWS: {NEW: CANONICAL_LAYOUT}})
    apply_prepared(spelled, evidence_stubbed, RESHAPED)
    assert VIEWS in seen and "Code/Game/BaseCtor.cpp" in seen
    assert (spelled / VIEWS).read_bytes() == RESHAPED.encode()


STORAGE = {"fwd": False, "size": 76, "bases": [], "vfptr": False, "fields": [[0, "m_bytes", "uchar[76]", 76]]}
WITH_STORAGE = dict(CANONICAL_LAYOUT, size=88, fields=[[4, "m_04", "int", 4], [8, "m_08", "int", 4],
                                                        [12, "m_10", "Storage", 76]])


def test_byte_array_storage_compares_by_structure(spelled, evidence_stubbed, monkeypatch):
    """The real FXNugget holds `Rva0042526Member { uchar m_bytes[76]; }` storage: compared by its compiled
    shape (element kind and count), so the canonical class itself is readable."""
    defined(spelled, "    int m_nuggetType;\n")
    stream = {NEW: WITH_STORAGE, "Storage": STORAGE}
    compiled(monkeypatch, evidence_stubbed, {"Code/Game/BaseCtor.cpp": stream, "Code/Game/BaseSlots.cpp": stream,
                                             VIEWS: stream})
    apply_prepared(spelled, evidence_stubbed, RESHAPED)
    other = dict(STORAGE, fields=[[0, "m_bytes", "uchar[72]", 72], [72, "m_tail", "int", 4]])
    compiled(monkeypatch, evidence_stubbed, {"Code/Game/BaseCtor.cpp": stream, "Code/Game/BaseSlots.cpp": stream,
                                             VIEWS: {NEW: WITH_STORAGE, "Storage": other}})
    run(spelled, "reset", "-q", "--hard")
    run(spelled, "clean", "-qfd", "--", "reverse")
    with pytest.raises(evidence_stubbed.VerifyFailed, match="is not the canonical class"):
        apply_prepared(spelled, evidence_stubbed, RESHAPED)


@pytest.mark.parametrize("stream,message", [
    ({NEW: dict(CANONICAL_LAYOUT, fields=[[4, "m_unrelated", "double[20]", 160]], size=164)},
     "is not the canonical class"),
    ({NEW: dict(CANONICAL_LAYOUT, fields=[[4, "m_04", "float", 4], [8, "m_08", "int", 4]])}, "is not the canonical class"),
    ({NEW: dict(CANONICAL_LAYOUT, fields=[[4, "m_type", "int", 4], [8, "m_08", "int", 4]])}, "is not the canonical class"),
    ({NEW: dict(CANONICAL_LAYOUT, size=16)}, "sizeof 16 vs 12"),
    ({NEW: dict(CANONICAL_LAYOUT, fields=[[4, "m_04", "Hidden", 4], [8, "m_08", "int", 4]])},
     "Hidden has no complete layout"),
    ({NEW: dict(CANONICAL_LAYOUT, fields=[[4, "m_04", "bitfield", 0], [8, "m_08", "int", 4]])}, "bitfield"),
    ({NEW: dict(CANONICAL_LAYOUT, bases=[["virtual Hidden", -1]])}, "virtual base"),
    ({}, "type info is missing"),
    ({NEW: {"fwd": True}}, "type info is missing"),
    ({NEW: CANONICAL_LAYOUT, OLD: CANONICAL_LAYOUT}, "still defines Rva00401000Base"),
])
def test_a_prepared_unit_keeping_its_own_class_rolls_back(spelled, evidence_stubbed, monkeypatch, stream, message):
    defined(spelled, "    int m_nuggetType;\n")
    before = snapshot(spelled)
    compiled(monkeypatch, evidence_stubbed, {VIEWS: stream})
    with pytest.raises(evidence_stubbed.VerifyFailed, match=message):
        apply_prepared(spelled, evidence_stubbed, RESHAPED)
    assert snapshot(spelled) == before


def test_a_private_copy_the_text_scan_misses_is_caught_by_its_type_records(spelled, evidence_stubbed, monkeypatch):
    """`#if 0` around the include and `class __declspec(align(4)) FXNugget` pass the text pre-filter."""
    defined(spelled, "    int m_nuggetType;\n")
    before = snapshot(spelled)
    hidden = dict(CANONICAL_LAYOUT, vfptr=False, size=160, fields=[[0, "m_unrelated", "double[20]", 160]])
    compiled(monkeypatch, evidence_stubbed, {VIEWS: {NEW: hidden}})
    with pytest.raises(evidence_stubbed.VerifyFailed, match="keeps its own FXNugget"):
        apply_prepared(spelled, evidence_stubbed, HIDDEN)
    assert snapshot(spelled) == before


def test_reference_units_that_disagree_refuse(spelled, evidence_stubbed, monkeypatch):
    defined(spelled, "    int m_nuggetType;\n")
    compiled(monkeypatch, evidence_stubbed, {"Code/Game/BaseSlots.cpp": {NEW: dict(CANONICAL_LAYOUT, size=16)}})
    with pytest.raises(evidence_stubbed.VerifyFailed, match="reference units disagree"):
        apply_prepared(spelled, evidence_stubbed, RESHAPED)


def test_a_derived_class_in_a_prepared_unit_is_fine(spelled, evidence_stubbed, monkeypatch):
    defined(spelled, "    int m_nuggetType;\n")
    never_compiled(monkeypatch, evidence_stubbed)
    text = RESHAPED + f"class LightPulseFXNugget : public {NEW} {{ public: int m_color; }};\n"
    assert plan_of(spelled, merge=True, prepared={VIEWS: text.encode()}).after[VIEWS] == text.encode()


@pytest.mark.parametrize("rel,message", [
    ("Code/Game/Unrowed.cpp", "missing|no matched rows"),            # not a ledger source
    (HEADER, "must be an existing Code C\\+\\+ source"),              # a header, not a unit
])
def test_a_prepared_path_must_be_a_matched_unit(spelled, evidence_stubbed, rel, message):
    with pytest.raises(evidence_stubbed.Refusal, match=message):
        plan_of(spelled, merge=True, prepared={rel: RESHAPED.encode()})


def test_prepared_needs_merge_existing(spelled, evidence_stubbed):
    with pytest.raises(evidence_stubbed.Refusal, match="--prepared goes with"):
        plan_of(spelled, prepared={VIEWS: RESHAPED.encode()})


def test_the_cli_takes_prepared_with_merge_existing(spelled, evidence_stubbed, monkeypatch, tmp_path, capsys):
    rename = evidence_stubbed
    defined(spelled, "    int m_nuggetType;\n")
    never_compiled(monkeypatch, rename)
    sheet = tmp_path / "reshaped.cpp"
    sheet.write_bytes(RESHAPED.encode())
    argv = ["class", "--name", OLD, "--new", NEW, "--basis", "inferred", "--evidence", "agree:abc",
            "--merge-existing", "--prepared", f"{VIEWS}={sheet}", "--dry-run", "--no-claim", "--no-object-scan",
            "--root", str(spelled)]
    assert rename.main(argv) == 0, capsys.readouterr().err
    assert f"{VIEWS} (prepared 1)" in capsys.readouterr().out
    with pytest.raises(SystemExit):
        rename.main([a for a in argv if a != "--merge-existing"])


@pytest.mark.parametrize("edit,message", [
    (('{"kind": "i4", "name": "m_08"', '{"name": "m_08"'), "lacks an offset, size, kind or name"),
    (('"kind": "i4", "name": "m_08"', '"kind": "bitfield", "name": "m_08"'), "is bitfield, not a scalar"),
    (('"kind": "i4", "name": "m_08"', '"kind": "S:Opaque", "name": "m_08"'), "is S:Opaque, not a scalar"),
    (('"kind": "i4", "name": "m_08"', '"kind": "A", "name": "m_08"'), "is A, not a scalar"),
    (('"size": 12,\n', '"bases": ["Rva00406000Base"],\n "size": 12,\n'), "the contract has bases"),
    (('"size": 12,\n', ''), "records no sizeof"),
])
def test_merge_existing_refuses_a_contract_it_cannot_compare(spelled, evidence_stubbed, monkeypatch, edit, message):
    text = (spelled / CONTRACT).read_text()
    assert edit[0] in text
    write(spelled, CONTRACT, text.replace(edit[0], edit[1], 1))
    defined(spelled, "    int m_nuggetType;\n")
    layouts(monkeypatch, evidence_stubbed, [[4, "m_nuggetType", "int", 4]], 8)
    with pytest.raises(evidence_stubbed.Refusal, match=message):
        plan_of(spelled, basis="canonical:zh", evidence="zh cite", merge=True)


# ---------------------------------------------------------------- the approval behind a credit, for real
#
# The gates run HEAD's own tools/rename.py verify-record. These trees commit this
# checkout's tools, so HEAD has it; the votes are real name_lane votes from two workers.

APPROVED_MODELS = {"seat-a": "claude-opus-5-5", "seat-b": "gpt-6.1-sol"}


def vote_key(root, key, answer, monkeypatch, workers=APPROVED_MODELS, commit=True):
    """Two workers serve `key` and vote `answer`; the agreement id name_lane recorded. The
    votes land in a commit of their own (as name_lane submit pushes do) unless `commit` is
    False: the gates count only votes already in the base revision."""
    import csv as csv_module
    import json
    import name_lane
    from types import SimpleNamespace
    _rel, _kind, scope, ident = key.split("|")
    answer_key = name_lane.answer_key(_kind, scope, ident)
    for worker, model in workers.items():
        monkeypatch.setenv("BFME_CLAIM_OWNER", worker)
        args = SimpleNamespace(session=f"{worker}-{ident}", model=model, count=1, file=None, list_only=False,
                               registered=OLD, key=[key])
        assert name_lane.cmd_next(lane_of(root), args) == 0
        sheet = root / f"build/answer-{worker}-{ident}.json"
        sheet.write_bytes(json.dumps({HEADER: {answer_key: answer}}).encode("utf-8"))
        name_lane.cmd_submit(lane_of(root), SimpleNamespace(answer=str(sheet), session=f"{worker}-{ident}",
                                                            model=model))
    rows = [r for r in csv_module.DictReader((root / "reverse/name_agreed.csv").read_text().splitlines())
            if r["key"] == key and r["new"] == answer and r["status"] == "agreed"]
    assert rows, (root / "reverse/name_agreed.csv").read_text()
    if commit:
        run(root, "add", "--", "reverse")
        run(root, "-c", "user.name=t", "-c", "user.email=", "commit", "-qm", f"votes for {key}")
    return rows[-1]["id"]


@pytest.fixture
def approved(registered, monkeypatch):
    import shutil
    (registered / "tools").mkdir(exist_ok=True)
    for path in TOOLS.glob("*.py"):
        shutil.copy(path, registered / "tools" / path.name)
    # as the real tree's .gitignore: name_lane's scratch and the ledger lock stay out of every commit
    write(registered, ".gitignore", "build/\nreverse/.add_match.lock\n")
    run(registered, "add", "-A")
    run(registered, "-c", "user.name=t", "-c", "user.email=", "commit", "-qm", "tools")
    monkeypatch.setattr(class_gate, "ROOT", registered)
    monkeypatch.setattr(class_views, "CANONICAL", registered / "reverse" / "canonical_classes.csv")
    import rename
    monkeypatch.setattr(rename, "registered_object_problems", lambda ctx, plan: [])
    return registered


def land(root, monkeypatch, evidence, *, new=NEW, basis="inferred", stub=False):
    """Plan and apply the class rename, stage it; `stub` forges past the planner's own check."""
    import rename
    if stub:
        monkeypatch.setattr(rename, "check_agreement", lambda *a, **k: None)
        monkeypatch.setattr(rename, "check_canonical", lambda *a, **k: None)
        monkeypatch.setattr(rename, "check_registered_basis", lambda *a, **k: "inferred")
    p = plan_of(root, new=new, basis=basis, evidence=evidence)
    rename.apply_rename(p, ctx=rename.Context(root, object_scan=False), verify=lambda ctx, sources: True,
                        checks=None)
    run(root, "add", "-A")
    return p


def gates(root, capsys):
    """(class_gate's exit, its stderr, the header_queue rows repair_queue counts as removed)."""
    capsys.readouterr()
    rc = class_gate.main(["--staged"])
    err = capsys.readouterr().err
    os.environ["REPAIR_ROOT"] = str(root)
    try:
        import repair_queue
        rq = importlib.reload(repair_queue)
    finally:
        del os.environ["REPAIR_ROOT"]
    return rc, err, rq.removed_header_rows()


def test_an_agreed_rename_is_credited_by_both_gates(approved, monkeypatch, capsys):
    agreement = vote_key(approved, f"{HEADER}|class||{OLD}", NEW, monkeypatch)
    land(approved, monkeypatch, f"agree:{agreement}")
    rc, err, removed = gates(approved, capsys)
    assert rc == 0, err
    assert removed == []


def assert_refused(root, capsys, why):
    import re
    rc, err, removed = gates(root, capsys)
    assert rc == 1 and f"{SOUND}: declares its own `" in err, err
    assert "no rename credit" in err and re.search(why, err), err
    assert removed == [(OLD, SOUND)]


def test_votes_cast_against_another_text_are_no_credit(approved, monkeypatch, capsys):
    """nl- votes carry no fingerprint; the credit binds them to the header text they named."""
    agreement = vote_key(approved, f"{HEADER}|class||{OLD}", NEW, monkeypatch)
    write(approved, HEADER, (approved / HEADER).read_text() + "// a later edit\n")
    run(approved, "-c", "user.name=t", "-c", "user.email=", "commit", "-qam", "header edited after the votes")
    land(approved, monkeypatch, f"agree:{agreement}")
    assert_refused(approved, capsys, "changed after the vote by w-[0-9a-f]+ was recorded")


def test_a_header_edited_with_the_votes_is_no_credit(approved, monkeypatch, capsys):
    """Two votes, then `int m_04` -> `float m_04` committed together with them and the agreement."""
    agreement = vote_key(approved, f"{HEADER}|class||{OLD}", NEW, monkeypatch, commit=False)
    write(approved, HEADER, (approved / HEADER).read_text().replace("int m_04;", "float m_04;"))
    run(approved, "add", "-A")
    run(approved, "-c", "user.name=t", "-c", "user.email=", "commit", "-qm", "votes and a header edit")
    land(approved, monkeypatch, f"agree:{agreement}")
    assert_refused(approved, capsys, "also changes Code/Game/Rva00401000Base.h")


def test_a_forged_agreement_is_no_credit(approved, monkeypatch, capsys):
    land(approved, monkeypatch, "agree:does-not-exist", stub=True)
    assert_refused(approved, capsys, "not in reverse/name_agreed.csv")


def test_votes_added_by_the_judged_commit_count_for_nothing(approved, monkeypatch, capsys):
    """Real two-worker votes and their agreement, but staged with the rename itself."""
    agreement = vote_key(approved, f"{HEADER}|class||{OLD}", NEW, monkeypatch, commit=False)
    land(approved, monkeypatch, f"agree:{agreement}")
    assert_refused(approved, capsys, "not in reverse/name_agreed.csv")


def test_fabricated_votes_in_the_judged_commit_count_for_nothing(approved, monkeypatch, capsys):
    """An agreement and two votes from made-up workers, added in the same change."""
    import name_agreement
    key = f"{HEADER}|class||{OLD}"
    votes = ",".join(name_agreement.VOTE_COLUMNS) + "\n" + "".join(
        f"{key},{name_agreement.digest(key, NEW)},model-{i},s{i},{worker},2026-11-07\n"
        for i, worker in enumerate(("w-000000000001", "w-000000000002")))
    write(approved, "reverse/name_votes.csv", votes)
    write(approved, "reverse/name_agreed.csv", ",".join(name_agreement.AGREED_COLUMNS) + "\n"
          f"nl-fabricated,class,{OLD},{NEW},,w-000000000001;w-000000000002,{key},agreed,\n")
    land(approved, monkeypatch, "agree:nl-fabricated", stub=True)
    assert_refused(approved, capsys, "not in reverse/name_agreed.csv")


def test_a_forged_canonical_basis_is_no_credit(approved, monkeypatch, capsys):
    land(approved, monkeypatch, "trust me", basis="canonical:zh", stub=True)
    assert_refused(approved, capsys, "canonical:zh needs --evidence citing")


def test_another_keys_agreement_is_no_credit(approved, monkeypatch, capsys):
    member = vote_key(approved, f"{HEADER}|member|{OLD}|m_04", "m_nuggetType", monkeypatch)
    land(approved, monkeypatch, f"agree:{member}", stub=True)
    assert_refused(approved, capsys, "kind 'member'")


def test_an_agreement_for_another_name_is_no_credit(approved, monkeypatch, capsys):
    agreement = vote_key(approved, f"{HEADER}|class||{OLD}", NEW, monkeypatch)
    land(approved, monkeypatch, f"agree:{agreement}", new="FXThing", stub=True)
    assert_refused(approved, capsys, "new 'FXNugget'")


def test_an_agreement_reached_on_a_private_view_is_no_credit(approved, monkeypatch, capsys):
    """check_agreement alone accepts any key spelling this class; the registered route wants the header's."""
    import csv as csv_module
    agreement = vote_key(approved, f"{HEADER}|class||{OLD}", NEW, monkeypatch)
    path = approved / "reverse/name_agreed.csv"
    rows = list(csv_module.DictReader(path.read_text().splitlines()))
    with path.open("w", newline="", encoding="utf-8") as handle:
        out = csv_module.DictWriter(handle, fieldnames=list(rows[0]), lineterminator="\n")
        out.writeheader()
        out.writerows([dict(r, key=f"{SOUND}|class||{OLD}") if r["id"] == agreement else r for r in rows])
    run(approved, "add", "--", "reverse/name_agreed.csv")        # in the base: only base ledgers count
    run(approved, "-c", "user.name=t", "-c", "user.email=", "commit", "-qm", "agreement at a view's key")
    land(approved, monkeypatch, f"agree:{agreement}", stub=True)
    assert_refused(approved, capsys, "was reached at|does not agree")


def test_the_registered_route_wants_the_canonical_headers_key(registered, monkeypatch):
    """Behind the vote recount: an agreement check_agreement accepts at another unit's key is refused."""
    import rename
    write(registered, "reverse/name_agreed.csv", "id,kind,old,new,rva,agents,key,status,detail\n"
          f"nl-x,class,{OLD},{NEW},,a;b,{SOUND}|class||{OLD},agreed,\n")
    run(registered, "add", "-A")
    monkeypatch.setattr(rename, "check_basis", lambda *a, **k: "inferred")
    ctx = rename.Context(registered, object_scan=False)
    with pytest.raises(rename.Refusal, match=r"was reached at Code/Game/SoundFXNugget.cpp\|class\|\|"):
        rename.check_registered_basis(ctx, HEADER, "inferred", "agree:nl-x", OLD, NEW)
    write(registered, "reverse/name_agreed.csv", "id,kind,old,new,rva,agents,key,status,detail\n"
          f"nl-x,class,{OLD},{NEW},,a;b,{HEADER}|class||{OLD},agreed,\n")
    assert rename.check_registered_basis(rename.Context(registered, object_scan=False), HEADER, "inferred",
                                         "agree:nl-x", OLD, NEW) == "inferred"


def test_a_citation_inside_a_submodule_is_read_at_the_pinned_commit(registered):
    """A Zero Hour citation lives in reference/open-bfme-1, a gitlink: the superproject's
    `git show BASE:path` cannot read it, so the base's pinned submodule commit is used."""
    import rename
    sub = registered / "reference/donor"
    sub.mkdir(parents=True)
    run(sub, "init", "-q")
    run(sub, "config", "core.autocrlf", "false")
    write(sub, "FXList.h", "class FXNugget;  // pinned\n")
    run(sub, "add", "-A")
    run(sub, "-c", "user.name=t", "-c", "user.email=", "commit", "-qm", "pinned")
    pinned = run(sub, "rev-parse", "HEAD").stdout.strip()
    write(sub, "FXList.h", "class FXNugget;  // newer, unpinned\n")
    run(sub, "-c", "user.name=t", "-c", "user.email=", "commit", "-qam", "newer")
    run(registered, "update-index", "--add", "--cacheinfo", f"160000,{pinned},reference/donor")
    run(registered, "-c", "user.name=t", "-c", "user.email=", "commit", "-qm", "pin the donor")
    ctx = rename.RevisionContext(registered, "HEAD")
    assert ctx.read("reference/donor/FXList.h") == b"class FXNugget;  // pinned\n"
    assert ctx.read("reference/donor/Missing.h") is None
    assert ctx.read(HEADER).startswith(b"#pragma once")


# ---------------------------------------------------------------- reverting an inferred registered rename

def test_an_inferred_registered_rename_reverts_exactly(approved, monkeypatch, capsys):
    import rename
    agreement = vote_key(approved, f"{HEADER}|class||{OLD}", NEW, monkeypatch)
    land(approved, monkeypatch, f"agree:{agreement}")
    run(approved, "-c", "user.name=t", "-c", "user.email=", "commit", "-qm", "rename")
    landed = snapshot(approved)
    rename.revert(rename.Context(approved, object_scan=False), agreement, "the nuggets are not this class",
                  verify=lambda ctx, sources: True, checks=None, claim=False)
    registry = (approved / "reverse/canonical_classes.csv").read_text()
    assert f"\n{OLD},{HEADER},contract class_contracts/{OLD}.json\n" in registry and f"\n{NEW}," not in registry
    assert (approved / CONTRACT).exists() and not (approved / f"reverse/class_contracts/{NEW}.json").exists()
    assert f"class {OLD}\n" in (approved / HEADER).read_text()
    assert (approved / "reverse/header_queue.tsv").read_text().splitlines()[1].startswith(f"{OLD}\t{SOUND}\t")
    assert (approved / "reverse/name_basis.csv").read_text().splitlines()[-1].startswith(
        f"class,{NEW},{OLD},restored,revert:{agreement} ")
    run(approved, "add", "-A")
    rc, err, removed = gates(approved, capsys)               # the revert is credited as the exact inverse
    assert rc == 0, err
    assert removed == []
    assert snapshot(approved) != landed


def test_a_revert_that_changes_more_than_the_inverse_is_no_credit(approved, monkeypatch, capsys):
    import rename
    agreement = vote_key(approved, f"{HEADER}|class||{OLD}", NEW, monkeypatch)
    land(approved, monkeypatch, f"agree:{agreement}")
    run(approved, "-c", "user.name=t", "-c", "user.email=", "commit", "-qm", "rename")
    rename.revert(rename.Context(approved, object_scan=False), agreement, "the nuggets are not this class",
                  verify=lambda ctx, sources: True, checks=None, claim=False)
    view = (approved / SOUND).read_text()
    write(approved, SOUND, view.replace("    int m_nuggetType;\n", "    short m_nuggetType;\n", 1))
    run(approved, "add", "-A")
    rc, err, removed = gates(approved, capsys)
    assert rc == 1 and "beyond the landing's inverse" in err and SOUND in err, err
    assert removed == [(NEW, SOUND)]


UNRELATED = ("function,?rva00405000@@YAXXZ,?setUp@@YAXXZ,inferred,agree:nl-older,Code/Game/Other.cpp,0x00405000\n"
             "function,?setUp@@YAXXZ,?setUp@@YAXXZ,canonical:wb,0x00405000 WorldBuilder,Code/Game/Other.cpp,0x00405000\n")
UNRELATED_TOMB = '?gone@@YAXXZ,0x00406000,"Removed: not ours"\n'


def landed_and_reverted(approved, monkeypatch):
    """An inferred registered rename, committed, then reverted in the working tree."""
    import rename
    with open(approved / "reverse/name_basis.csv", "ab") as handle:
        handle.write(UNRELATED.encode("utf-8"))           # an unrelated name, protected by its LAST record
    with open(approved / "reverse/deleted_rows.csv", "ab") as handle:
        handle.write(UNRELATED_TOMB.encode("utf-8"))      # and an unrelated tombstone, both in the base
    agreement = vote_key(approved, f"{HEADER}|class||{OLD}", NEW, monkeypatch)
    land(approved, monkeypatch, f"agree:{agreement}")
    run(approved, "-c", "user.name=t", "-c", "user.email=", "commit", "-qm", "rename")
    rename.revert(rename.Context(approved, object_scan=False), agreement, "the nuggets are not this class",
                  verify=lambda ctx, sources: True, checks=None, claim=False)
    return agreement


@pytest.mark.parametrize("tamper", ["reorder", "older-record", "duplicate-tombstone", "drop-unrelated-tombstone"])
def test_a_revert_whose_ledgers_change_otherwise_is_no_credit(approved, monkeypatch, capsys, tamper):
    """Name protection reads a name's LAST record: a reordered or repeated line changes meaning."""
    landed_and_reverted(approved, monkeypatch)
    basis = approved / "reverse/name_basis.csv"
    deleted = approved / "reverse/deleted_rows.csv"
    lines = basis.read_bytes().decode().splitlines(keepends=True)
    tombs = deleted.read_bytes().decode().splitlines(keepends=True)
    first, second = UNRELATED.splitlines(keepends=True)
    if tamper == "reorder":                            # the canonical record no longer last: protection drops
        i, j = lines.index(first), lines.index(second)
        lines[i], lines[j] = lines[j], lines[i]
        basis.write_bytes("".join(lines).encode())
    elif tamper == "older-record":
        basis.write_bytes("".join(lines + [first]).encode())
    elif tamper == "duplicate-tombstone":
        deleted.write_bytes("".join(tombs + [tombs[-1]]).encode())
    else:                                              # an unrelated tombstone lifted with the revert
        assert UNRELATED_TOMB.encode() in deleted.read_bytes()
        deleted.write_bytes(deleted.read_bytes().replace(UNRELATED_TOMB.encode(), b""))
    run(approved, "add", "-A")
    rc, err, removed = gates(approved, capsys)
    assert rc == 1 and "no rename credit" in err and "must be base's lines" in err, err
    assert removed == [(NEW, SOUND)]


def test_an_inferred_merge_reverts_to_exactly_the_tree_before_it(approved, monkeypatch, capsys):
    """NEW's pre-existing spellings, which the landing never touched, stay exactly as they were."""
    import rename
    write(approved, LIST, LIST_SRC)
    with open(approved / "reverse/functions.csv", "ab") as handle:
        handle.write(f"{ADD},,0x00402000,16,{LIST},matched,\n".encode("utf-8"))
    run(approved, "add", "-A")
    run(approved, "-c", "user.name=t", "-c", "user.email=", "commit", "-qm", "NEW spelled as a type")
    agreement = vote_key(approved, f"{HEADER}|class||{OLD}", NEW, monkeypatch)
    before = snapshot(approved)
    p = plan_of(approved, evidence=f"agree:{agreement}", merge=True)
    rename.apply_rename(p, ctx=rename.Context(approved, object_scan=False), verify=lambda ctx, sources: True,
                        checks=None)
    run(approved, "add", "-A")
    run(approved, "-c", "user.name=t", "-c", "user.email=", "commit", "-qm", "merge")
    assert (approved / LIST).read_bytes() == before[LIST]                  # the landing never touched it
    rename.revert(rename.Context(approved, object_scan=False), agreement, "the nuggets are not this class",
                  verify=lambda ctx, sources: True, checks=None, claim=False)
    after = snapshot(approved)
    ledgers = ("reverse/name_basis.csv", "reverse/deleted_rows.csv")
    assert {k: v for k, v in after.items() if k not in ledgers} == {k: v for k, v in before.items() if k not in ledgers}
    assert after["reverse/name_basis.csv"].startswith(before["reverse/name_basis.csv"])
    run(approved, "add", "-A")
    rc, err, removed = gates(approved, capsys)
    assert rc == 0, err
    assert removed == []


# ---------------------------------------------------------------- rename.py member on a registered class

def test_a_member_the_contract_already_names_leaves_the_contract(registered, evidence_stubbed):
    p = plan_of(registered, "member", cls=OLD, member="m_04", new="m_nuggetType")
    assert "int m_nuggetType;" in after(p, HEADER)
    assert "m_nuggetType = 0" in after(p, "Code/Game/BaseCtor.cpp")
    assert CONTRACT not in p.after and SOUND not in p.after
    assert any("already names the field m_nuggetType" in w for w in p.warnings)


def test_a_member_the_contract_names_is_respelled_there(registered, evidence_stubbed):
    p = plan_of(registered, "member", cls=OLD, member="m_08", new="m_filterHandle")
    assert '"name": "m_filterHandle"' in after(p, CONTRACT) and "m_08" not in after(p, CONTRACT)
    assert "int m_filterHandle;" in after(p, HEADER) and "int m_filterHandle;" in after(p, SOUND)


@pytest.mark.parametrize("member,new,contract,message", [
    ("m_04", "m_type", None, "names no field m_04 or m_type"),
    ("m_04", "m_nuggetType", ('"offset": 4, "type": "int", "views": 2', '"offset": 8, "type": "int", "views": 2'),
     r"names m_nuggetType at \+0x8"),
    ("m_08", "m_nuggetType", None, "already"),
    ("m_08", "m_filterHandle", ('"vslots"', '"queue": [{"attribute": "name@0x8", "candidates": {"m_08": 1}}],\n "vslots"'),
     "outside its top-level field"),
])
def test_a_member_the_contract_disagrees_with_refuses(registered, evidence_stubbed, member, new, contract, message):
    if contract:
        text = (registered / CONTRACT).read_text()
        assert contract[0] in text
        write(registered, CONTRACT, text.replace(contract[0], contract[1]))
        run(registered, "add", "-A")
    with pytest.raises(evidence_stubbed.Refusal, match=message):
        plan_of(registered, "member", cls=OLD, member=member, new=new)


# ---------------------------------------------------------------- prose never collides

NOTES = "Code/Game/NuggetNotes.cpp"


@pytest.mark.parametrize("text,collides", [
    (f"// a {NEW}-family base ctor; BFME1 {NEW}::m_field04\nint notes() {{ return 0; }}\n", False),
    (f'/* {NEW} */\nconst char *pool = "{NEW}";\nint notes() {{ return 0; }}\n', False),
    (f"class {NEW};\nint notes() {{ return 0; }}\n", True),
    (f"int notes({NEW} *n);\n", True),
    # a backslash-newline splices lines before literals exist: this is code after an empty string
    (f'const char *s = "\\\n"; class {NEW} {{ public: double unrelated[20]; }};\n', True),
    # and a spliced line comment swallows the next line: prose
    (f"// a note \\\nclass {NEW};\nint notes() {{ return 0; }}\n", False),
])
def test_only_a_code_spelling_of_the_new_name_collides(registered, evidence_stubbed, text, collides):
    write(registered, NOTES, text)
    run(registered, "add", "-A")
    if collides:
        with pytest.raises(evidence_stubbed.Refusal, match=f"{NEW} already appears in {NOTES}"):
            plan_of(registered)
    else:
        assert NOTES not in plan_of(registered).after          # prose stays as written


# ---------------------------------------------------------------- mangled names the tokenizer reads

@pytest.mark.parametrize("symbol,classes", [
    # the guard of a function-local static: a compiler-generated `$S4`, then the function's scope
    ("?$S4@?7??doFXPos@LaserFXNugget@@UBEXPBUCoord3D@@PBVMatrix3D@@M0@Z@4IA",
     {"LaserFXNugget", "Coord3D", "Matrix3D", "doFXPos"}),
    # a function-local static whose scope discriminator is a multi-letter encoded number
    ("?deltaX@?BC@??rva002F83F5@Pathfinder@@QAEHPAVPathfindCell@@0ABVLocomotorSet@@_N2HPAUICoord2D@@PAVObject@@H@Z@4PAHA",
     {"deltaX", "rva002F83F5", "Pathfinder", "PathfindCell", "LocomotorSet", "ICoord2D", "Object"}),
])
def test_local_static_names_tokenize(symbol, classes):
    import rename
    assert {symbol[a:b] for a, b in rename.fragments(symbol)} == classes
    assert not rename.ClassText("FXNugget").search(symbol)
    assert rename.ClassText(sorted(classes)[0]).search(symbol)
