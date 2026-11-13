"""`tools/rename.py function --respell` (signature only) preparing a hand-written header.

BehaviorModuleInterface slot 43 was rowed `?slot43@BehaviorModule@@UAEXH@Z` with its int parameter guessed
along with the placeholder identifier; retail's overrides load the argument with `fld dword [esp+4]` and
Object's caller pushes a float. 4d67bacc1ab admits the respell itself (`UAEXH` -> `UAEXM`), but the
declaration lives only in the registered hand-written BehaviorModule.h and in two reference/shims copies,
while --respell prepared Code .cpp sources only (lk106, LINK-514 cause 6).

A signature-only respell (the identifier and `this` stay) may now prepare a hand-written Code header,
registered or not but never one tools/header_adopt_lane.py generates, and the reference/shims copies of a
prepared Code header (same path tail). Each prepared header may change only the parameter lists of lines
declaring the respelled identifier; a copy left unprepared refuses; every ledger source including a
prepared header is rebuilt, and after the build none of their objects may still name the old spelling.
"""
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import rename  # noqa: E402
from rename import Refusal  # noqa: E402

OLD = "?slot43@Module@@UAEXH@Z"          # virtual void Module::slot43(int)
NEW = "?slot43@Module@@UAEXM@Z"          # virtual void Module::slot43(float)
RVA = 0x00405000
REASON = "signature-only: retail's overrides load the argument with fld dword [esp+4]"

HEADER = "Code/Include/Game/Module.h"
SHIM = "reference/shims/shimdir/Game/Module.h"
MODULE_H = """// Hand-written canonical Module header.
#pragma once
class Module
{
public:
\tvirtual void slot42() { }
\tvirtual void slot43(int) { }\t\t\t// 43
\tvirtual void slot44() { }
};
"""
MODULE_H_FLOAT = MODULE_H.replace("slot43(int)", "slot43(float)")

FUNCTIONS = f"""name,export_rva,target_rva,target_size,source,status,notes
{OLD},,0x00405000,3,Code/Game/ModuleRow.cpp,matched,ret 4 default
?spawn@@YAXXZ,,0x00406000,8,Code/Game/Spawn.cpp,matched,includes the header
?shimmed@@YAXXZ,,0x00407000,8,Code/Game/Shimmed.cpp,matched,includes the shim copy
?other@@YAXXZ,,0x00408000,8,Code/Game/Other.cpp,matched,unrelated
"""


def _git(root, *args):
    subprocess.run(["git", "-C", str(root), *args], check=True, capture_output=True)


@pytest.fixture
def tree(tmp_path):
    files = {
        "reverse/functions.csv": FUNCTIONS,
        "reverse/symbols.csv": "name,address,notes\n",
        "reverse/deleted_rows.csv": "name,target_rva,reason\n",
        "reverse/name_basis.csv": "kind,old,new,basis,evidence,source,rva\n",
        "reverse/data_rows.csv": "name,address,address_kind,size,section,source,status,evidence,model\n",
        "reverse/exports.csv": "ordinal,rva,target_rva,section,kind,name\n",
        "reverse/gate_baseline.txt": "",
        "reverse/canonical_classes.csv": f"class,header,notes\nModule,{HEADER},existing header\n",
        HEADER: MODULE_H,
        SHIM: MODULE_H,
        "Code/Game/ModuleRow.cpp": '#include "../Include/Game/Module.h"\nvoid anchor(Module *m) { m->slot44(); }\n',
        "Code/Game/Spawn.cpp": '#include "../Include/Game/Module.h"\nvoid spawn() { }\n',
        "Code/Game/Shimmed.cpp": '// cl: /I../../reference/shims/shimdir\n#include "Game/Module.h"\nvoid shimmed() { }\n',
        "Code/Game/Other.cpp": "void other() { }\n",
    }
    for rel, text in files.items():
        path = tmp_path / rel
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(text.encode("utf-8"))
    _git(tmp_path, "init", "-q")
    _git(tmp_path, "add", "-A")
    return tmp_path


def plan(root, prepared=None, **overrides):
    if prepared is None:
        prepared = {HEADER: MODULE_H_FLOAT.encode(), SHIM: MODULE_H_FLOAT.encode()}
    kwargs = dict(rva=RVA, new=NEW, respell=True, basis="inferred", evidence=REASON, prepared=prepared)
    kwargs.update(overrides)
    return rename.plan_rename("function", ctx=rename.Context(root, object_scan=False), **kwargs)


def test_a_signature_only_respell_prepares_a_registered_header_and_its_shim_copy(tree):
    got = plan(tree)
    assert got.new == NEW and (OLD, NEW, RVA) in got.renamed_rows
    assert got.after[HEADER] == MODULE_H_FLOAT.encode() and got.after[SHIM] == MODULE_H_FLOAT.encode()
    # every includer of either copy is rebuilt; the headers themselves have no rows to verify
    assert {"Code/Game/ModuleRow.cpp", "Code/Game/Spawn.cpp", "Code/Game/Shimmed.cpp"} <= set(got.verify)
    assert "Code/Game/Other.cpp" not in got.verify
    assert HEADER not in got.verify and SHIM not in got.verify
    assert {f"file:{HEADER}", f"file:{SHIM}"} <= set(rename.claim_keys(got))
    assert got.respelled_headers == {"old": OLD, "headers": [HEADER, SHIM]}


def test_a_shim_copy_left_unprepared_is_refused(tree):
    with pytest.raises(Refusal, match=f"{SHIM} still declares slot43"):
        plan(tree, prepared={HEADER: MODULE_H_FLOAT.encode()})


def test_a_shim_that_copies_no_prepared_code_header_is_refused(tree):
    with pytest.raises(Refusal, match="or a reference/shims copy of a prepared Code header"):
        plan(tree, prepared={SHIM: MODULE_H_FLOAT.encode()})


def test_a_generated_header_is_never_prepared(tree):
    generated = "// Module: canonical layout, generated by tools/header_adopt_lane.py from\n" + MODULE_H
    (tree / HEADER).write_bytes(generated.encode())
    _git(tree, "add", "-A")
    with pytest.raises(Refusal, match="generated by tools/header_adopt_lane.py"):
        plan(tree, prepared={HEADER: generated.replace("slot43(int)", "slot43(float)").encode(),
                             SHIM: MODULE_H_FLOAT.encode()})


@pytest.mark.parametrize("edit,why", [
    # another member's line changes too
    (lambda t: t.replace("slot44()", "slot44(int)"), "does not declare slot43"),
    # a line is added next to the respelled declaration
    (lambda t: t.replace("\tvirtual void slot44() { }\n", "\tvirtual void slot44() { }\n\tvirtual void extra();\n"),
     "adds or removes lines"),
    # the respelled line changes outside its parameter list
    (lambda t: t.replace("slot43(float) { }", "slot43(float) { return; }"), "changes more than slot43's parameter list"),
    # nothing changes
    (lambda t: MODULE_H, "does not change slot43's declaration"),
])
def test_a_prepared_header_changes_only_the_respelled_parameter_list(tree, edit, why):
    text = edit(MODULE_H_FLOAT)
    with pytest.raises(Refusal, match=why):
        plan(tree, prepared={HEADER: text.encode(), SHIM: MODULE_H_FLOAT.encode()})


def test_a_header_respell_is_bounded_by_max_files(tree):
    with pytest.raises(Refusal, match="touched headers reach more than 2 ledger sources"):
        plan(tree, max_files=2)


def test_headers_are_prepared_only_with_the_respelled_word(tree):
    ctx = rename.Context(tree, object_scan=False)
    p = rename.Plan("function", OLD, NEW, "inferred", "", "Code/Game/ModuleRow.cpp", RVA)
    with pytest.raises(Refusal, match="must be an existing Code C[+][+] source"):
        rename._batch_source_edits(ctx, p, {HEADER: MODULE_H_FLOAT.encode()})
    with pytest.raises(Refusal, match="must be an existing Code C[+][+] source"):
        rename._batch_source_edits(ctx, p, {SHIM: MODULE_H_FLOAT.encode()}, view_headers=True)
    assert rename._batch_source_edits(ctx, p, {HEADER: MODULE_H_FLOAT.encode(), SHIM: MODULE_H_FLOAT.encode()},
                                      respell_word="slot43")
    assert HEADER not in p.verify and SHIM not in p.verify


def test_a_class_move_still_never_prepares_a_canonical_header(tree):
    ctx = rename.Context(tree, object_scan=False)
    p = rename.Plan("function", OLD, NEW, "inferred", "", "Code/Game/ModuleRow.cpp", RVA)
    with pytest.raises(Refusal, match="is the registered header of Module"):
        rename._batch_source_edits(ctx, p, {HEADER: MODULE_H_FLOAT.encode()}, view_headers=True)


def test_a_rebuilt_includer_still_naming_the_old_spelling_fails_verification(tree, monkeypatch):
    import build
    import reloc_ledger
    p = plan(tree)
    objects = {}
    for rel in p.verify:
        obj = tree / "objs" / (Path(rel).stem + ".obj")
        obj.parent.mkdir(parents=True, exist_ok=True)
        obj.write_bytes(rel.encode())
        objects[str(tree / rel)] = obj
    monkeypatch.setattr(build, "obj_path", lambda path: objects[str(path)])
    names = {"Code/Game/Spawn.cpp": [NEW], "Code/Game/Shimmed.cpp": [OLD], "Code/Game/ModuleRow.cpp": [NEW]}
    monkeypatch.setattr(reloc_ledger, "parse_coff", lambda data: (
        {}, {i: {"name": n} for i, n in enumerate(names.get(data.decode(), []))}))
    assert rename.respelled_header_object_problems(rename.Context(tree, object_scan=False), p) == [
        f"Code/Game/Shimmed.cpp's object still names {OLD}"]
    names["Code/Game/Shimmed.cpp"] = [NEW]
    assert rename.respelled_header_object_problems(rename.Context(tree, object_scan=False), p) == []
