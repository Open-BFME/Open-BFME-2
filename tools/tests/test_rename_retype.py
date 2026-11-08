"""tools/rename.py `global --retype` on a miniature tree: a rowed 4-byte placeholder
global retyped to its real extent, every declaration respelled, the data row, pins,
notes and data_ledger.csv row re-keyed, the bridging /alternatename and its hatch line
removed; and its refusals (overlap, non-zero retail bytes, a second definition, a
surviving old symbol, a converged address, a compiler-built type). Retail bytes and
verification are injected; the post-build object check runs on real COFF objects."""
import os
import re
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import rename  # noqa: E402
from rename import Refusal, VerifyFailed  # noqa: E402

REAL_SCAN = rename.compiler_scan

OWNER = "Code/Game/ThunksRva00401000.cpp"
USER = "Code/Game/Register.cpp"
BRIDGED = "Code/Game/EraseRva00403000.cpp"
OLD = "?g_00A01000@@3IA"
NEW = "?g_00A01000@@3PAIA"
VEC = "?g_00A01000@@3V?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@A"
TYPE = "unsigned int [3]"

FUNCTIONS = f"""name,export_rva,target_rva,target_size,source,status,notes
?thunk@@YAXXZ,,0x00401000,10,{OWNER},matched,ecx=&{OLD}
?reg@@YAXPAX@Z,,0x00402000,16,{USER},matched,
?erase@@YAXXZ,,0x00403000,16,{BRIDGED},matched,
"""
DATA_ROWS = f"""name,address,address_kind,size,section,source,status,evidence,model
{OLD},0x00A01000,rva,4,.data,{OWNER},matched,"zero-initialized (.bss)",m
?g_00A02000@@3HA,0x00A02000,rva,4,.data,{OWNER},matched,other,m
"""
LEDGER = f"""address,size,section,kind,name,source,status,names,defs,refs
0x00A01000,4,.data,global,{OLD},{OWNER},provisional,{OLD};{VEC},1,8
0x00A02000,4,.data,global,?g_00A02000@@3HA,{OWNER},owned,,1,2
"""
HATCHES = f"""# Escape-hatch register, shrink-only.
# mode: enforce
alternatename\t{BRIDGED}\t{VEC}\t1
alternatename\tCode/Game/Other.cpp\t?x@@3HA\t1
"""
OWNER_SRC = f"""// cl: /O2
unsigned g_00A01000;\t// retail RVA 0x00A01000 (.bss), defined here
int g_00A02000;
// ?thunk@@YAXXZ @ 0x00401000: dtor thunk, ecx=&g_00A01000 ({OLD})
void thunk() {{ ((char *)&g_00A01000)[0] = 0; }}
"""
USER_SRC = """extern unsigned int g_00A01000;
void reg(void *p) { (void)p; (void)&g_00A01000; }
"""
BRIDGED_SRC = f"""namespace _STL {{ template <class T> struct vector {{ T *a, *b, *c; void erase(T *); }}; }}
extern _STL::vector<void *> g_00A01000;
// the four-byte {OLD} owner; bind to it
#pragma comment(linker, "/alternatename:{VEC}={OLD}")
void erase() {{ g_00A01000.erase(0); }}
"""
BRIDGED_PREPARED = """namespace _STL { template <class T> struct vector { T *a, *b, *c; void erase(T *); }; }
extern unsigned int g_00A01000[3];
void erase() { reinterpret_cast<_STL::vector<void *> *>(&g_00A01000)->erase(0); }
"""


def _git(root, *args):
    return subprocess.run(["git", "-C", str(root), *args], check=True, capture_output=True, text=True).stdout


@pytest.fixture
def tree(tmp_path, monkeypatch):
    files = {
        "reverse/functions.csv": FUNCTIONS,
        "reverse/data_rows.csv": DATA_ROWS,
        "reverse/data_ledger.csv": LEDGER,
        "reverse/hatch_baseline.tsv": HATCHES,
        "reverse/symbols.csv": f"name,address,notes\n{OLD},0x00E01000,data pin\n",
        "reverse/deleted_rows.csv": "name,target_rva,reason\n",
        "reverse/data_converged.csv": "address,name,evidence\n",
        OWNER: OWNER_SRC, USER: USER_SRC, BRIDGED: BRIDGED_SRC,
    }
    for rel, text in files.items():
        path = tmp_path / rel
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(text.encode("utf-8"))
    _git(tmp_path, "init", "-q")
    _git(tmp_path, "add", "-A")
    monkeypatch.setattr(rename, "retail_extent", lambda ctx, rva, size: (".data", ".data", bytes(size)))
    monkeypatch.setattr(rename, "retail_relocated", lambda ctx, rva, size: [])
    monkeypatch.setattr(rename, "compiler_scan", lambda ctx, words: {"spelled": set(), "asm": set(), "cleared": set()})
    return tmp_path


def write(root, rel, text):
    (root / rel).write_bytes(text.encode("utf-8"))


def ctx_of(root):
    return rename.Context(root, object_scan=False)


def plan(root, **overrides):
    args = dict(name=OLD, new=NEW, basis=None, evidence="image_iso out-of-object +4/+8; retail .bss",
                retype=TYPE, size="12", prepared={BRIDGED: BRIDGED_PREPARED.encode()})
    args.update(overrides)
    return rename.plan_rename("global", ctx=ctx_of(root), **args)


def text(p, rel):
    return p.after[rel].decode()


# ------------------------------------------------------------ the plan

def test_retype_respells_declarations_and_rekeys_every_ledger(tree):
    p = plan(tree)
    assert "unsigned int g_00A01000[3];\t// retail RVA 0x00A01000 (.bss), defined here" in text(p, OWNER)
    assert NEW in text(p, OWNER) and OLD not in text(p, OWNER)              # the comment follows
    assert text(p, USER).startswith("extern unsigned int g_00A01000[3];\n")
    assert "alternatename" not in text(p, BRIDGED) and OLD not in text(p, BRIDGED)
    rows = text(p, "reverse/data_rows.csv")
    assert rows.splitlines()[1].startswith(f"{NEW},0x00A01000,rva,12,.data,{OWNER},matched,")
    assert "Retyped from ?g_00A01000@@3IA (4 B) to unsigned int [3] (12 B)" in rows
    assert rows.splitlines()[2] == f"?g_00A02000@@3HA,0x00A02000,rva,4,.data,{OWNER},matched,other,m"
    ledger = text(p, "reverse/data_ledger.csv").splitlines()
    assert ledger[1] == f"0x00A01000,12,.data,global,{NEW},{OWNER},owned,,1,8"   # the vector alias is gone
    assert ledger[2] == LEDGER.splitlines()[2]                                # other rows untouched
    assert f"ecx=&{NEW}" in text(p, "reverse/functions.csv")
    assert p.renamed_pins == [(OLD, NEW, "0x00E01000")]
    hatches = text(p, "reverse/hatch_baseline.tsv")
    assert VEC not in hatches and "?x@@3HA\t1" in hatches                     # the bridge's line goes
    assert p.after["reverse/deleted_rows.csv"].decode().splitlines()[-1].startswith(f'{OLD},0x00A01000,"Retyped')
    assert p.verify == [BRIDGED, USER, OWNER]
    assert 0x00A01000 in p.claims
    assert p.retype["removed"] == [(BRIDGED, VEC)] and p.retype["size"] == 12
    assert p.subject() == "Retype g_00A01000 as unsigned int [3] (12 B, retail extent verified)"


def test_ledger_keeps_a_different_identifier_bound_at_the_address(tree):
    write(tree, "reverse/data_ledger.csv", LEDGER.replace(f";{VEC}", f";{VEC};?TheVector@@3HA"))
    _git(tree, "add", "-A")
    row = text(plan(tree), "reverse/data_ledger.csv").splitlines()[1]
    assert row == f"0x00A01000,12,.data,global,{NEW},{OWNER},provisional,?TheVector@@3HA;{NEW},1,8"


# ------------------------------------------------------------ refusals

@pytest.mark.parametrize("extra,message", [
    ("?g_00A01008@@3HA,0x00A01008,rva,4,.data,Code/Game/X.cpp,matched,x,m\n", "data row ?g_00A01008@@3HA"),
    ("?g_00E01004@@3HA,0x00E01004,va,4,.data,Code/Game/X.cpp,matched,x,m\n", "at 0x00A01004"),
])
def test_overlapping_data_row_refuses(tree, extra, message):
    with open(tree / "reverse/data_rows.csv", "a", newline="\n") as f:
        f.write(extra)
    _git(tree, "add", "-A")
    with pytest.raises(Refusal, match=re.escape("overlaps another owner") + ".*" + re.escape(message)):
        plan(tree)


def test_overlapping_ledger_name_or_code_refuses(tree):
    with open(tree / "reverse/data_ledger.csv", "a", newline="\n") as f:
        f.write("0x00A01004,4,.data,global,?g_00A01004@@3IA,,unowned,,0,3\n")
    _git(tree, "add", "-A")
    with pytest.raises(Refusal, match=r"overlaps another owner: data_ledger.csv name \?g_00A01004@@3IA"):
        plan(tree)
    with pytest.raises(Refusal, match="overlaps another owner"):
        plan(tree, size="0x1001")                    # reaches g_00A02000's row


def test_non_zero_retail_bytes_refuse_without_an_initializer(tree, monkeypatch):
    monkeypatch.setattr(rename, "retail_extent",
                        lambda ctx, rva, size: (".data", ".data", bytes(4) + b"\x01" + bytes(size - 5)))
    with pytest.raises(Refusal, match=r"non-zero bytes at 0x00A01000\+0x4"):
        plan(tree)
    p = plan(tree, initializer="{0, 1, 0}")          # spelled: then ./build.sh's data_rows check decides
    assert "unsigned int g_00A01000[3] = {0, 1, 0};" in text(p, OWNER)


def test_extent_leaving_the_section_refuses(tree, monkeypatch):
    monkeypatch.setattr(rename, "retail_extent", lambda ctx, rva, size: (".data", ".rsrc", bytes(size)))
    with pytest.raises(Refusal, match="not inside retail .data"):
        plan(tree)


def test_a_second_definition_refuses(tree):
    write(tree, USER, "unsigned int g_00A01000;\n")
    _git(tree, "add", "-A")
    with pytest.raises(Refusal, match="second definition"):
        plan(tree)


def test_a_surviving_old_symbol_refuses(tree):
    write(tree, USER, USER_SRC + f'#pragma comment(linker, "/alternatename:?other@@3HA={OLD}")\n')
    _git(tree, "add", "-A")
    with pytest.raises(Refusal, match="still spells"):
        plan(tree)


def test_unrewritten_bridge_refuses(tree):
    with pytest.raises(Refusal, match="still spells|hatch_baseline"):
        plan(tree, prepared={})                      # the bridged unit's vector extern stays, with its pragma


@pytest.mark.parametrize("overrides,message", [
    (dict(new="?g_other@@3PAIA"), "keeps the identifier"),
    (dict(new=OLD), "nothing to retype"),
    (dict(size="0"), "positive"),
    (dict(name="?nothing@@3HA"), "names 0 reverse/data_rows.csv rows"),
])
def test_argument_refusals(tree, overrides, message):
    with pytest.raises(Refusal, match=re.escape(message)):
        plan(tree, **overrides)


def test_converged_address_refuses(tree):
    write(tree, "reverse/data_converged.csv", f"address,name,evidence\n0x00A01000,{OLD},link\n")
    _git(tree, "add", "-A")
    with pytest.raises(Refusal, match="converged"):
        plan(tree)


def test_owner_initializer_needs_respelling(tree):
    write(tree, OWNER, OWNER_SRC.replace("unsigned g_00A01000;", "unsigned g_00A01000 = 7;"))
    _git(tree, "add", "-A")
    with pytest.raises(Refusal, match="--initializer"):
        plan(tree)


# ------------------------------------------------------------ review of 03c0d18c27 (Codex)

def test_split_line_extern_is_respelled_and_verified(tree):                    # finding 1
    write(tree, USER, USER_SRC.replace("extern unsigned int g_00A01000;", "extern unsigned int\n g_00A01000;"))
    _git(tree, "add", "-A")
    p = plan(tree)
    assert text(p, USER).startswith("extern unsigned int g_00A01000[3];\n")
    assert USER in p.verify


def test_an_unparsable_declaration_refuses(tree):                              # finding 1
    write(tree, USER, USER_SRC.replace("extern unsigned int g_00A01000;", "extern unsigned int /* x */ g_00A01000,\n"
                                                                           "    g_other;"))
    _git(tree, "add", "-A")
    with pytest.raises(Refusal, match="cannot respell|declares g_00A01000"):
        plan(tree)


def test_every_unit_naming_the_identifier_is_verified_even_unchanged(tree):    # finding 1
    write(tree, "Code/Game/Use.cpp", "void use() { (void)&g_00A01000; }\n")
    with open(tree / "reverse/functions.csv", "a", newline="\n") as f:
        f.write("?use@@YAXXZ,,0x00404000,8,Code/Game/Use.cpp,matched,\n")
    _git(tree, "add", "-A")
    p = plan(tree)
    assert "Code/Game/Use.cpp" not in p.after and "Code/Game/Use.cpp" in p.verify


def test_an_object_reference_the_text_does_not_spell_refuses(tree):            # finding 1
    ctx = ctx_of(tree)
    ctx.object_scan = True
    ctx._consumer_lookup = lambda symbols: {"Code/Game/Macro.cpp"} if OLD in symbols else set()
    write(tree, "Code/Game/Macro.cpp", "#define G (*(int *)0)\nvoid m() { G; }\n")
    _git(tree, "add", "-A")
    args = dict(name=OLD, new=NEW, basis=None, evidence="x", retype=TYPE, size="12",
                prepared={BRIDGED: BRIDGED_PREPARED.encode()})
    with pytest.raises(Refusal, match="never spells g_00A01000"):
        rename.plan_rename("global", ctx=ctx, **args)


def test_prepared_second_definition_refuses(tree):                             # finding 2
    prepared = BRIDGED_PREPARED.replace("extern unsigned int g_00A01000[3];", "unsigned int\n g_00A01000[3];")
    with pytest.raises(Refusal, match="outside its data row's source"):
        plan(tree, prepared={BRIDGED: prepared.encode()})


def test_prepared_declaration_of_another_type_refuses(tree):
    prepared = BRIDGED_PREPARED.replace("extern unsigned int g_00A01000[3];", "extern unsigned int g_00A01000;")
    with pytest.raises(Refusal, match="not unsigned int"):
        plan(tree, prepared={BRIDGED: prepared.encode()})


def test_another_owners_ledger_row_at_the_address_refuses(tree):               # finding 3
    write(tree, "reverse/data_ledger.csv",
          LEDGER.replace(f"global,{OLD},{OWNER},provisional", "global,?OtherOwner@@3HA,Code/Game/Other.cpp,owned"))
    _git(tree, "add", "-A")
    with pytest.raises(Refusal, match=r"binds 0x00A01000 to \?OtherOwner@@3HA"):
        plan(tree)


def test_a_ledger_row_of_this_symbol_from_another_source_refuses(tree):        # finding 3
    write(tree, "reverse/data_ledger.csv", LEDGER.replace(f"global,{OLD},{OWNER},", f"global,{OLD},Code/Game/Other.cpp,"))
    _git(tree, "add", "-A")
    with pytest.raises(Refusal, match="another owner's row"):
        plan(tree)


def test_a_shrink_refuses(tree):                                               # finding 4
    prepared = BRIDGED_PREPARED.replace("unsigned int g_00A01000[3]", "unsigned short g_00A01000")
    with pytest.raises(Refusal, match="smaller than the row's 4 B"):
        plan(tree, new="?g_00A01000@@3GA", retype="unsigned short", size="2", prepared={BRIDGED: prepared.encode()})


def test_same_size_type_change_is_allowed(tree):
    prepared = BRIDGED_PREPARED.replace("unsigned int g_00A01000[3]", "int g_00A01000")
    p = plan(tree, new="?g_00A01000@@3HA", retype="int", size="4", prepared={BRIDGED: prepared.encode()})
    assert ",rva,4,.data," in text(p, "reverse/data_rows.csv").splitlines()[1]


# ------------------------------------------------------------ review of 010e6e9e21 (Codex, round 2)

@pytest.mark.parametrize("new_type", ["unsigned int *", "void *", "_STL::vector<void *>", "Widget", "int &",
                                      "unsigned int *[3]", "const"])
def test_non_arithmetic_types_refuse(tree, new_type):                       # finding 1
    with pytest.raises(Refusal, match="not an arithmetic type"):
        plan(tree, retype=new_type)


@pytest.mark.parametrize("initializer", ["reinterpret_cast<unsigned int *>(14688564)", "{0x00E02134, 0, 0}",
                                         "{1, 4194304u, 2}"])
def test_an_initializer_spelling_a_retail_address_refuses(tree, monkeypatch, initializer):   # finding 1
    monkeypatch.setattr(rename, "retail_extent", lambda ctx, rva, size: (".data", ".data", b"\x01" + bytes(size - 1)))
    with pytest.raises(Refusal, match="inside retail's address range"):
        plan(tree, initializer=initializer)


def test_a_relocated_retail_word_refuses(tree, monkeypatch):                # finding 1
    monkeypatch.setattr(rename, "retail_extent",
                        lambda ctx, rva, size: (".data", ".data", bytes(4) + (0xE02134).to_bytes(4, "little") + bytes(4)))
    monkeypatch.setattr(rename, "retail_relocated", lambda ctx, rva, size: [4])
    with pytest.raises(Refusal, match=r"retail relocates a dword at 0x00A01000\+0x4"):
        plan(tree, initializer="{0, 1, 0}")


def test_a_macro_argument_declaration_refuses(tree):                        # finding 2
    write(tree, USER, "#define DECL(x) extern unsigned int x\nDECL(g_00A01000);\nvoid reg(void *p) { (void)p; }\n")
    _git(tree, "add", "-A")
    with pytest.raises(Refusal, match="function-like macro DECL"):
        plan(tree)


def test_a_declaring_macro_body_refuses(tree):                              # finding 2
    write(tree, USER, "#define DECLARE extern unsigned int g_00A01000\nDECLARE;\nvoid reg(void *p) { (void)p; }\n")
    _git(tree, "add", "-A")
    with pytest.raises(Refusal, match="#define DECLARE declares g_00A01000"):
        plan(tree)


def test_a_file_scope_mention_outside_a_declaration_refuses(tree):          # finding 2
    write(tree, USER, USER_SRC + "STATIC_ASSERT_SIZE g_00A01000;\n" .replace(" g_00A01000;", "(g_00A01000);"))
    _git(tree, "add", "-A")
    with pytest.raises(Refusal, match="at file scope outside any declaration"):
        plan(tree)


def test_macro_and_file_scope_uses_that_declare_nothing_pass(tree):
    write(tree, USER, USER_SRC + "#define REGISTRY (*reinterpret_cast<int *>(&g_00A01000))\n"
                                 "namespace n { int *first = (int *)&g_00A01000; }\n"
                                 "int use() { return REGISTRY + sizeof(g_00A01000); }\n")
    _git(tree, "add", "-A")
    p = plan(tree)
    assert text(p, USER).startswith("extern unsigned int g_00A01000[3];\n")


def test_a_computed_include_unit_is_rebuilt(tree):                          # finding 3
    write(tree, "Code/Game/Global.h", "extern unsigned int g_00A01000;\ninline int extent() { return sizeof(g_00A01000); }\n")
    consumer = "Code/Game/HeaderUser.cpp"
    write(tree, consumer, '#define GLOBAL_HEADER "Global.h"\n#include GLOBAL_HEADER\nint size() { return extent(); }\n')
    with open(tree / "reverse/functions.csv", "a", newline="\n") as f:
        f.write(f"?size@@YAHXZ,,0x00405000,6,{consumer},matched,\n")
    _git(tree, "add", "-A")
    p = plan(tree)
    assert "Code/Game/Global.h" in p.after and consumer in p.verify


# ------------------------------------------------------------ review of c18c2dbbaa (Codex, round 3)
# Declarations are judged on each unit's preprocessed text: whatever a macro, a nested
# macro argument or a computed include builds is plain C++ there.

NESTED_EXPANDED = ('#line 1 "Code/Game/Register.cpp"\n\n'
                   'void reg(void *p) { extern unsigned int g_00A01000; (void)sizeof(g_00A01000); }\n')


def test_preprocessed_stale_local_extern_is_found():                        # finding 1
    problems = rename.preprocessed_problems(NESTED_EXPANDED, "g_00A01000", TYPE)
    assert problems and "declares g_00A01000 as `extern unsigned int g_00A01000;`" in problems[0]


@pytest.mark.parametrize("expanded", [
    "struct S { int a; }; static void f() { extern unsigned int a, g_00A01000; }\n",  # a declarator list
    "namespace n { unsigned int g_00A01000; }\n",
    "extern \"C\" unsigned int g_00A01000[3];\n",
])
def test_preprocessed_other_declarations_are_found(expanded):
    assert rename.preprocessed_problems(expanded, "g_00A01000", TYPE)


@pytest.mark.parametrize("expanded", [
    "extern unsigned int g_00A01000[3];\nvoid reg() { (void)sizeof(g_00A01000); }\n",
    "unsigned int g_00A01000[3];\n#pragma comment(linker, \"/alternatename:g_00A01000=x\")\n",
    "extern unsigned int g_00A01000[3];\nconst char *s = \"unsigned g_00A01000;\";\n",
    "void f() { int *p = (int *)&g_00A01000; return; }\n",
    "int unrelated;\n",
])
def test_preprocessed_new_type_and_uses_pass(expanded):
    assert rename.preprocessed_problems(expanded, "g_00A01000", TYPE) == []


def test_the_object_check_reads_every_unit_preprocessed(tree, objects, monkeypatch):   # finding 1
    made, tmp = objects
    made["ThunksRva00401000.cpp"] = coff(tmp / "owner.obj", [(NEW, 1, 2)])
    made["Register.cpp"] = coff(tmp / "user.obj", [])                         # sizeof leaves no symbol
    monkeypatch.setattr(rename, "preprocess_unit",
                        lambda ctx, rel: (NESTED_EXPANDED if rel == USER else "unsigned int g_00A01000[3];\n", None))
    problems = rename.retype_object_problems(ctx_of(tree), retype_record([OWNER, USER]))
    assert problems and problems[0].startswith(f"{USER} declares g_00A01000 as")
    monkeypatch.setattr(rename, "preprocess_unit", lambda ctx, rel: (None, "the preprocessor refused it: C1083"))
    assert rename.retype_object_problems(ctx_of(tree), retype_record([OWNER])) == \
        [f"{OWNER}: the preprocessor refused it: C1083"]


def test_the_nested_macro_attack_is_refused_through_apply(tree, objects, monkeypatch):   # finding 1, end to end
    made, tmp = objects
    made["ThunksRva00401000.cpp"] = coff(tmp / "owner.obj", [(NEW, 1, 2)])
    made["Register.cpp"] = coff(tmp / "user.obj", [])
    made["EraseRva00403000.cpp"] = coff(tmp / "erase.obj", [(NEW, 0, 2)])
    write(tree, USER, "#define DECL(dummy,x) extern unsigned int x\n"
                      "void reg(void *p) { DECL((0), g_00A01000); (void)sizeof(g_00A01000); }\n")
    _git(tree, "add", "-A")
    p = plan(tree)                                   # the text scans cannot read the nested argument
    before = snapshot(tree)
    monkeypatch.setattr(rename, "preprocess_unit",
                        lambda ctx, rel: (NESTED_EXPANDED if rel == USER else "unsigned int g_00A01000[3];\n", None))
    with pytest.raises(VerifyFailed, match="declares g_00A01000 as `extern unsigned int g_00A01000;`"):
        rename.apply_rename(p, ctx=ctx_of(tree), verify=lambda ctx, sources: True, checks=None)
    assert snapshot(tree) == before


def _real_compiler():
    try:
        import build
        return (build.ROOT / "build.sh").exists() and build.vc71_root().exists()
    except Exception:
        return False


@pytest.mark.skipif(not _real_compiler(), reason="needs MSVC 7.1 (srv1's worktree)")
@pytest.mark.parametrize("body,stale", [
    ("#define DECL(dummy,x) extern unsigned int x\nvoid reg(void *p) { DECL((0), g_00A01000); "
     "(void)sizeof(g_00A01000); }\n", True),
    ('#define HDR "retype_pp_hdr.h"\n#include HDR\nint size() { return extent(); }\n', True),
    ("extern unsigned int g_00A01000[3];\nint size() { return sizeof(g_00A01000); }\n", False),
])
def test_the_real_preprocessor_expands_what_the_text_scans_miss(body, stale):
    import build
    root = build.ROOT
    scratch = root / "build" / "retype_pp_test"
    scratch.mkdir(parents=True, exist_ok=True)
    (scratch / "retype_pp_hdr.h").write_bytes(b"extern unsigned int g_00A01000;\n"
                                              b"inline int extent() { return sizeof(g_00A01000); }\n")
    unit = scratch / "unit.cpp"
    unit.write_bytes(body.encode())
    text, why = rename.preprocess_unit(rename.Context(root, object_scan=False), unit.relative_to(root).as_posix())
    assert why is None, why
    assert bool(rename.preprocessed_problems(text, "g_00A01000", TYPE)) == stale
    assert not list(scratch.glob("*.obj"))           # preprocessing writes no object


# ------------------------------------------------------------ review of 92c6d902ed (Codex, round 4)
# The preprocessed check is fail-closed: every occurrence is a declaration parsed as the
# new type with C++ linkage, or a plain use; anything else refuses.

def wrapped(statement):
    return "void f() { " + statement + " (void)sizeof(g_00A01000); }\n"


@pytest.mark.parametrize("statement", [
    "extern unsigned int (g_00A01000);",                                          # finding 1
    "extern unsigned int a, (g_00A01000);",
    "extern unsigned int * (g_00A01000);",
    "extern unsigned int g_00A01000[2][3];",
    "extern __declspec(dllimport) unsigned int g_00A01000[3];",
    "typedef unsigned int U; extern U g_00A01000[3];",                              # an alias is not read through
    "extern const unsigned int g_00A01000[3];",
    "extern unsigned int (*g_00A01000)[3];",
    'extern "C" unsigned int g_00A01000[3];',
    "Mystery g_00A01000;",                                                          # an unknown type name
    "unknown_fn(g_00A01000);",                                                      # neither function nor keyword
])
def test_unreadable_or_wrong_declarations_refuse(statement):
    assert rename.preprocessed_problems(wrapped(statement), "g_00A01000", TYPE), statement


# ---- review of f3aaa6ed74 (Codex, final): a declaration-shaped statement never falls back to an operand

@pytest.mark.parametrize("statement", [
    "extern __declspec(align(4)) unsigned int a, g_00A01000;",                   # the reproductions
    "extern __declspec(align(4)) unsigned int *g_00A01000;",
    "extern __declspec(align(4)) unsigned int g_00A01000[3];",                   # attribute: not the bare type
    "static unsigned int a = 1, *g_00A01000;",
    "extern unsigned int a, *g_00A01000;",
    "extern unsigned int a, &g_00A01000;",
    "typedef unsigned int T[sizeof(g_00A01000)], *(*g_00A01000);",
    "extern __declspec(align(4)) unsigned int (*g_00A01000)[3];",
    "const unsigned int *g_00A01000, b;",
])
def test_a_declaration_shaped_statement_must_parse_or_refuse(statement):
    assert rename.preprocessed_problems(wrapped(statement), "g_00A01000", TYPE), statement


# ---- re-check of 3da3431c75 (Codex): declaration shape is syntax, not a known-type list

@pytest.mark.parametrize("prefix,statement", [
    ("struct T {};", "::T *g_00A01000;"),                                           # the reproductions
    ("typedef struct { int a; } T;", "T *g_00A01000;"),
    ("typedef unsigned int A, B;", "A *g_00A01000;"),
    ("typedef struct {\n unsigned char idLength;\n short xOrigin;\n} TTargaHeader;",   # WorldHeightMapTiles.cpp
     "TTargaHeader g_00A01000;"),
    ("typedef struct z_stream_s { unsigned char *next_in; unsigned avail_in; } z_stream;",   # zlib.h
     "z_stream *g_00A01000;"),
    ("", "Undeclared *g_00A01000;"),                                                 # a name no list knows
    ("", "Undeclared g_00A01000[3];"),
    ("", "ns::Inner<int, ns::Other<int> > *g_00A01000;"),
    ("", "const Undeclared &g_00A01000, h;"),
    ("int a = 1;", "a * g_00A01000;"),                                              # an expression of that shape
])
def test_declaration_shaped_statements_refuse_whatever_the_names(prefix, statement):
    text = prefix + "\nvoid f() { " + statement + " (void)sizeof(g_00A01000); }\n"
    assert rename.preprocessed_problems(text, "g_00A01000", TYPE), statement


@pytest.mark.parametrize("statement", [
    "int n = unsigned(g_00A01000[0]) + 1;",                                          # functional casts: uses
    "return unsigned(g_00A01000[0]) + 1;",
    "int m = (int)sizeof(unsigned int) * g_00A01000[0];",
    "unsigned int *q = new unsigned int[g_00A01000[0]];",
    "int take(void *); take(g_00A01000);",
    "int r = 2 * g_00A01000[1];",
    "reinterpret_cast<_STL::vector<void *> *>(g_00A01000)->erase(0);",               # Rva0020DAE0.cpp's shape
    "static_cast<unsigned int *>(g_00A01000)[0] = 1;",
    "const_cast<unsigned int *>(g_00A01000)[1] = 2;",
])
def test_uses_beside_type_names_pass(statement):
    text = "int f() { " + statement + " return 0; }\n"
    assert rename.preprocessed_problems(text, "g_00A01000", TYPE) == [], statement


# ---- re-check of 7bb8321170 (Codex): a declared function's call with `&`, `*` or `(` first

MEMSET = ("extern \"C\" __declspec(dllimport) void * __cdecl memset(void *, int, unsigned int);\n"   # the CRT's
          "int take(unsigned int *);\n")


@pytest.mark.parametrize("statement", [
    "memset( &g_00A01000, 0, 12 );",                                                 # Rva007ADC9CMaskInits.cpp:64
    "memset(&g_00A01000[1], 0, 4);",
    "::memset(&g_00A01000, 0, 12);",
    "take(*&g_00A01000);",
    "take((g_00A01000));",
    "take(&(g_00A01000)[0]);",
])
def test_a_declared_functions_call_with_a_unary_first_argument_passes(statement):
    text = MEMSET + "void f() { " + statement + " }\n"
    assert rename.preprocessed_problems(text, "g_00A01000", TYPE) == [], statement


@pytest.mark.parametrize("prefix,statement", [
    ("typedef unsigned int T;", "T (&g_00A01000);"),                                # a type, not a function
    ("struct T { T(int); };", "T (*g_00A01000);"),                                  # a constructor makes no call
    ("typedef struct { int a; } T;", "T ((g_00A01000));"),
    ("struct S {}; void S(int);", "S(&g_00A01000);"),                               # both: refused, not guessed
    ("", "undeclared(&g_00A01000);"),                                                # no declared function
])
def test_the_leading_name_must_be_a_declared_function_and_no_type(prefix, statement):
    text = prefix + "\nvoid f() { " + statement + " (void)sizeof(g_00A01000); }\n"
    assert rename.preprocessed_problems(text, "g_00A01000", TYPE), statement


# ---- re-check of 83ba508ece (Codex): a function typedef is a type, not a function

FUNCTION_TYPEDEFS = [
    "typedef void F(int);",                                                   # DisplayStaticDebugView.h:13
    "typedef void F(DebugDisplayInterface *, void *, FILE *);",
    "typedef void (F)(int);",                                                 # the controlbarvtables Display.h
    "typedef void (*F)(int);",
    "typedef void (__cdecl *F)(int);",
    "struct C; typedef void (C::*F)(int);",
    "typedef int A, F(int), (*G)(char *p);",                                  # a list mixing them
    "using F = void(int);",
]


@pytest.mark.parametrize("decl", FUNCTION_TYPEDEFS)
def test_function_typedefs_are_types(decl):
    types, _ = rename._names(decl)
    assert "F" in types, decl


def test_the_declarator_reader_names_the_typedef_not_its_parameters():
    # (_names' older typedef patterns may also collect parameter names: a stricter refusal only)
    assert rename._typedef_names(" void F(char *p, int (*cb)(int q))") == {"F"}
    assert rename._typedef_names(" int A, F(int), (*G)(char *p), H[3], *J") == {"A", "F", "G", "H", "J"}


@pytest.mark.parametrize("decl", FUNCTION_TYPEDEFS)
@pytest.mark.parametrize("statement", ["F(*g_00A01000);", "F(&g_00A01000);", "F((g_00A01000));",
                                       "F(*g_00A01000)[3];"])
def test_a_function_typedef_in_front_refuses(decl, statement):
    text = decl + "\nvoid h() { " + statement + " (void)sizeof(g_00A01000); }\n"
    assert rename.preprocessed_problems(text, "g_00A01000", TYPE), (decl, statement)


def test_the_hidden_function_typedef_reproduction_is_refused_through_apply(tree, objects, monkeypatch):
    made, tmp = objects
    src = ("typedef void DebugDisplayCallback(int);\n#define DECL(dummy,x) DebugDisplayCallback (*x)\n"
           "void reg(void *p) { DECL((0), g_00A01000); (void)sizeof(g_00A01000); }\n")
    write(tree, USER, src)
    _git(tree, "add", "-A")
    p = plan(tree)
    for rel in p.verify:
        made[rel.rsplit("/", 1)[-1]] = coff(tmp / (rel.rsplit("/", 1)[-1] + ".obj"), [(NEW, 1, 2)] if rel == OWNER else [])
    expanded = ("typedef void DebugDisplayCallback(int); "
                "void reg(void *p){ DebugDisplayCallback (*g_00A01000); (void)sizeof(g_00A01000); }")
    assert rename.preprocessed_problems(expanded, "g_00A01000", TYPE)
    monkeypatch.setattr(rename, "preprocess_unit",
                        lambda ctx, rel: (expanded if rel == USER else "extern unsigned int g_00A01000[3];", None))
    before = snapshot(tree)
    with pytest.raises(VerifyFailed):
        rename.apply_rename(p, ctx=ctx_of(tree), verify=lambda ctx, sources: True, checks=None)
    assert snapshot(tree) == before


def test_a_pointer_returning_function_is_a_function():
    assert "memset" in rename._names("void *memset(void *, int, unsigned int);")[1]
    assert "emset" not in rename._names("void *memset(void *, int, unsigned int);")[1]


def test_typedef_struct_names_help_the_parser():
    types, _ = rename._names("typedef struct { int a; } TTargaHeader; typedef unsigned int A, B;")
    assert {"TTargaHeader", "A", "B"} <= types


def test_a_function_head_naming_the_identifier_refuses():
    text = "void f(int a, unsigned *g_00A01000) { (void)a; }\n"
    assert rename.preprocessed_problems(text, "g_00A01000", TYPE)


def test_the_align_reproduction_is_refused_through_apply(tree, objects, monkeypatch):
    made, tmp = objects
    made["ThunksRva00401000.cpp"] = coff(tmp / "owner.obj", [(NEW, 1, 2)])
    made["Register.cpp"] = coff(tmp / "user.obj", [])
    made["EraseRva00403000.cpp"] = coff(tmp / "erase.obj", [(NEW, 0, 2)])
    body = ("#define DECL(dummy,x) extern __declspec(align(4)) unsigned int a, x\n"
            "void reg(void *p) { DECL((0), g_00A01000); (void)sizeof(g_00A01000); }\n")
    write(tree, USER, body)
    _git(tree, "add", "-A")
    p = plan(tree)
    expanded = "void reg(void *p) { extern __declspec(align(4)) unsigned int a, g_00A01000; (void)sizeof(g_00A01000); }"
    monkeypatch.setattr(rename, "preprocess_unit",
                        lambda ctx, rel: (expanded if rel == USER else "unsigned int g_00A01000[3];\n", None))
    before = snapshot(tree)
    with pytest.raises(VerifyFailed, match="declares g_00A01000 as"):
        rename.apply_rename(p, ctx=ctx_of(tree), verify=lambda ctx, sources: True, checks=None)
    assert snapshot(tree) == before


def test_the_attribute_parser_balances_nested_parentheses():
    head = rename.split_declaration("extern __declspec(align(4)) unsigned int a, g;", set())
    assert head and head[2] == "__declspec(align(4)) unsigned int"
    assert rename.split_declaration("extern __declspec(align(4) unsigned int g;", set()) is None


def test_parentheses_around_the_name_alone_change_nothing():
    assert rename.preprocessed_problems(wrapped("extern unsigned int (g_00A01000)[3];"), "g_00A01000", TYPE) == []
    assert rename.preprocessed_problems(wrapped("extern unsigned int (*g_00A01000)[3];"), "g_00A01000", TYPE)
    assert rename.preprocessed_problems(wrapped("extern unsigned int (g_00A01000[3];"), "g_00A01000", TYPE)


def test_c_linkage_block_refuses():                                               # finding 3
    expanded = 'int dummy = 0; extern "C" { extern unsigned int g_00A01000[3]; }; void reg(void *p) { (void)sizeof(g_00A01000); }'
    problems = rename.preprocessed_problems(expanded, "g_00A01000", TYPE)
    assert problems and "(C linkage)" in problems[0]


@pytest.mark.parametrize("statement", [
    "extern unsigned int g_00A01000[3];",
    "extern unsigned g_00A01000[3];",                                               # the same type, spelled short
    "extern unsigned int a, g_00A01000[3], b;",
    "int *p = (int *)&g_00A01000;",
    "struct V { int a; }; V *v = reinterpret_cast<V *>(g_00A01000);",
    "_STL::vector<int, _STL::allocator<int> > *r = (_STL::vector<int, _STL::allocator<int> > *)&g_00A01000;",
    "int take(void *); take(g_00A01000);",                                         # a declared function's argument
    "if (g_00A01000[0] == 1) return;",
    "for (int i = 0; i < 3; ++i) g_00A01000[i] = 0;",
    "int n = sizeof g_00A01000;",
    "return;",
])
def test_declarations_of_the_new_type_and_plain_uses_pass(statement):
    text = "namespace _STL { template <class T> struct allocator {}; template <class T, class A> struct vector {}; }\n" \
           + wrapped(statement)
    assert rename.preprocessed_problems(text, "g_00A01000", TYPE) == [], statement


def test_parenthesized_declarator_is_refused_through_apply(tree, objects, monkeypatch):    # finding 1
    made, tmp = objects
    made["ThunksRva00401000.cpp"] = coff(tmp / "owner.obj", [(NEW, 1, 2)])
    made["Register.cpp"] = coff(tmp / "user.obj", [])
    made["EraseRva00403000.cpp"] = coff(tmp / "erase.obj", [(NEW, 0, 2)])
    write(tree, USER, "#define DECL(dummy,x) extern unsigned int (x)\n"
                      "void reg(void *p) { DECL((0), g_00A01000); (void)sizeof(g_00A01000); }\n")
    _git(tree, "add", "-A")
    p = plan(tree)
    before = snapshot(tree)
    expanded = "void reg(void *p) { extern unsigned int (g_00A01000); (void)sizeof(g_00A01000); }"
    monkeypatch.setattr(rename, "preprocess_unit",
                        lambda ctx, rel: (expanded if rel == USER else "unsigned int g_00A01000[3];\n", None))
    with pytest.raises(VerifyFailed, match="declares g_00A01000 as"):
        rename.apply_rename(p, ctx=ctx_of(tree), verify=lambda ctx, sources: True, checks=None)
    assert snapshot(tree) == before


@pytest.fixture
def scanning(tree, tmp_path, monkeypatch):
    """compiler_scan itself over this tree. `texts` {rel: what the preprocessor gives, None to fail};
    `stale` the units whose objects are not current; `asked` the units it preprocessed."""
    import build
    import name_dependents
    state = {"texts": {}, "stale": set(), "missing": set(), "asked": []}

    def preprocess(ctx, rel):
        state["asked"].append(rel)
        text = state["texts"].get(rel, "")
        return (None, "the preprocessor refused it") if text is None else (text, None)
    obj = tmp_path / "current.obj"
    obj.write_bytes(b"")

    def objects(rows):
        return {r["source"]: [tmp_path / "gone.obj" if r["source"] in state["missing"] else obj]
                for r in rows if r.get("status") == "matched"}
    monkeypatch.setattr(rename, "compiler_scan", REAL_SCAN)
    monkeypatch.setattr(rename, "preprocess_unit", preprocess)
    monkeypatch.setattr(name_dependents, "_row_objects", objects)
    monkeypatch.setattr(name_dependents, "_data_row_objects", lambda rows: {})
    monkeypatch.setattr(build, "compile_is_current",
                        lambda source, output: Path(source).relative_to(tree).as_posix() not in state["stale"])
    return tree, state


def add_unit(root, rel, text, rva):
    write(root, rel, text)
    with open(root / "reverse/functions.csv", "a", newline="\n") as f:
        f.write(f"?f{rva:x}@@YAHXZ,,0x{rva:08X},6,{rel},matched,\n")
    _git(root, "add", "-A")


def test_a_nested_paste_with_no_paste_in_the_consumer_joins_the_rebuild(scanning):
    """The review's repro: the consumer has no `##` and never calls the macro that pastes."""
    tree, state = scanning
    write(tree, "Code/Game/Paste.h", "#define CAT(a,b) a##b\n#define WRAP(x) CAT(g,x)\n")
    consumer = "Code/Game/Hidden.cpp"
    add_unit(tree, consumer, '#include "Paste.h"\nint f(){extern unsigned WRAP(_00A01000);return sizeof(WRAP(_00A01000));}\n',
             0x00405000)
    state["texts"][consumer] = "int f(){extern unsigned g_00A01000;return sizeof(g_00A01000);}\n"
    p = plan(tree)
    assert consumer in p.verify and consumer not in p.retype["cleared"]


def test_a_unit_reaching_a_paste_that_does_not_spell_it_is_cleared(scanning):
    tree, state = scanning
    write(tree, "Code/Game/Paste.h", "#define P(x) p##x\n")
    reached, unrelated = "Code/Game/Reached.cpp", "Code/Game/Unrelated.cpp"
    add_unit(tree, reached, '#include "Paste.h"\nint P(q);\n', 0x00405000)
    add_unit(tree, unrelated, "int u;\n", 0x00406000)
    state["texts"][reached] = "int pq;\n"
    p = plan(tree)
    assert reached in state["asked"] and reached not in p.verify and reached in p.retype["cleared"]
    assert unrelated not in state["asked"]                      # no paste and a current object: its object speaks


def test_a_stale_object_whose_unit_spells_it_joins_the_rebuild(scanning):
    tree, state = scanning
    stale = "Code/Game/Stale.cpp"
    add_unit(tree, stale, '#include "Holds.h"\nint s;\n', 0x00405000)      # header-only: its .cpp never spells it
    state["stale"].add(stale)
    state["texts"][stale] = "extern unsigned int g_00A01000;\nint s;\n"
    assert stale in plan(tree).verify


def test_a_stale_object_whose_unit_does_not_spell_it_is_cleared_and_not_rebuilt(scanning):
    tree, state = scanning
    stale = "Code/Game/Stale.cpp"
    add_unit(tree, stale, "int s;\n", 0x00405000)
    state["stale"].add(stale)
    state["texts"][stale] = "int s;\n"
    p = plan(tree)
    assert stale not in p.verify and stale in p.retype["cleared"]


def test_a_missing_object_is_asked_too(scanning):
    tree, state = scanning
    missing = "Code/Game/Missing.cpp"
    add_unit(tree, missing, "int m;\n", 0x00405000)
    state["missing"].add(missing)
    state["texts"][missing] = "extern unsigned int g_00A01000;\n"
    assert missing in plan(tree).verify


@pytest.mark.parametrize("why", ["a stale unit", "a missing unit"])
def test_a_failed_preprocess_refuses_and_names_the_unit(scanning, capsys, why):
    tree, state = scanning
    unit = "Code/Game/Broken.cpp"
    add_unit(tree, unit, "int b;\n", 0x00405000)
    state["stale" if "stale" in why else "missing"].add(unit)
    state["texts"][unit] = None
    with pytest.raises(Refusal, match=r"did not preprocess.*Code/Game/Broken.cpp"):
        plan(tree)
    assert "did not preprocess: Code/Game/Broken.cpp" in capsys.readouterr().out


def test_a_stale_asm_rebuilds_rather_than_being_read(scanning):
    tree, state = scanning
    unit = "Code/Game/Thunk.asm"
    add_unit(tree, unit, "; no compiler reads this\n", 0x00405000)
    state["stale"].add(unit)
    p = plan(tree)
    assert unit in p.verify and unit not in state["asked"] and unit not in p.retype["cleared"]


def test_a_current_asm_is_left_to_its_object(scanning):
    tree, state = scanning
    unit = "Code/Game/Thunk.asm"
    add_unit(tree, unit, "; no compiler reads this\n", 0x00405000)
    assert unit not in plan(tree).verify and unit not in state["asked"]


def test_a_stale_generated_asm_refuses(scanning):
    tree, state = scanning
    unit = "Code/gen_asm/Thunk.asm"
    (tree / "Code/gen_asm").mkdir()
    add_unit(tree, unit, "; generated\n", 0x00405000)
    state["stale"].add(unit)
    with pytest.raises(Refusal, match="generated source.*never edited"):
        plan(tree)


def test_the_scan_asks_about_an_absorbed_identifier_too(scanning, monkeypatch):
    tree, state = scanning
    add_inner(tree)
    stale = "Code/Game/Stale.cpp"
    add_unit(tree, stale, "int s;\n", 0x00405000)
    state["stale"].add(stale)
    state["texts"][stale] = "extern int g_00A01008;\n"
    held = {f.site: __import__("retail_identity").expected(f) for f in (AT_START, AT_INNER)}
    monkeypatch.setattr(__import__("retail_identity"), "read_retail", lambda rva, size: held[rva][:size])
    assert stale in absorbing(tree, monkeypatch).verify


@pytest.mark.parametrize("text,spells", [
    ("extern unsigned g_00A01000;\n", True),
    ("int g_00A01000x;\n", True),                                                    # text, not tokens: errs towards a rebuild
    ('int __identifier("?g_00A01000@@3IA");\n', True),
    ("void f() { __asm mov eax, g_00A01000 }\n", True),
    ('#pragma comment(linker, "/alternatename:?g_00A01000@@3IA=_y")\n', True),
    ('#pragma comment(linker, "/alternatename:?g_00A0" "1000@@3IA=_y")\n', True),    # split, as cl -E leaves it
    ('const char *a = "g_00A0"\n#line 40 "other.h"\n    "1000";\n', True),
    ('const wchar_t *b = L"g_00A0" L"1000";\n', True),
    ("int other;\n", False),
    ('const char *a = "g_00A0"; int b; const char *c = "1000";\n', False),
    # escapes: cl -E leaves them as written, and a wrong clearance is never checked again
    (r'#pragma comment(linker, "/alternatename:?g_\060\060A01000@@3IA=_y")' + "\n", True),
    (r'#pragma comment(linker, "/alternatename:?g_\x30" "\x30" "A01000@@3IA=_y")' + "\n", True),
    (r'const char *a = "g_\060\x30" "A01000";' + "\n", True),
    (r'const wchar_t *a = L"g_\u0030\U00000030A01000";' + "\n", True),
    (r'const char *a = "g_\x30" "0A01000";' + "\n", True),  # each literal decoded alone: joined first, the hex would run on
    (r'const char *a = "\?g_00A01000";' + "\n", True),
    # what does not decode cleanly counts as a hit, never a clearance
    (r'#pragma comment(linker, "/alternatename:?g_\x30\x30A01000@@3IA=_y")' + "\n", True),  # hex is greedy: this one is out of range
    (r'const char *a = "\q";' + "\n", True),
    (r'const char *a = "\x";' + "\n", True),
    (r'const char *a = "\xFFFFFFFFFF";' + "\n", True),
    # escapes that spell nothing clear as before
    (r'const char *a = "tab\t\n\\ \x41\101";' + "\n", False),
    (r'const char *a = "C:\\Game\\Data";' + "\n", False),
    (r"int c = '\x30'; const char *d = " + '"it\'s";\n', False),
    (r'const char *a = "g_\060\061A01000";' + "\n", False),  # decodes to another name
])
def test_preprocessed_text_is_searched_as_text(text, spells):
    assert rename.preprocessed_spells(text, ["g_00A01000"]) is spells


def test_an_exported_name_refuses(tree):
    write(tree, "reverse/exports.csv", f"ordinal,rva,target_rva,section,kind,name\n1,0x00A01000,,.data,data,{OLD}\n")
    _git(tree, "add", "-A")
    with pytest.raises(Refusal, match="an exported name is retail's own"):
        plan(tree)


def test_a_shim_naming_the_identifier_refuses(tree):
    (tree / "reference/shims/x").mkdir(parents=True)
    write(tree, "reference/shims/x/Holds.h", "extern unsigned g_00A01000;\n")
    _git(tree, "add", "-A")
    with pytest.raises(Refusal, match="a shim is not this retype's to respell"):
        plan(tree)


def test_forced_include_units_are_preprocessed(tree):                            # finding 4
    write(tree, "Code/Game/Global.h", "extern unsigned int g_00A01000;\ninline int extent() { return sizeof(g_00A01000); }\n")
    consumer = "Code/Game/Forced.cpp"
    write(tree, consumer, "// cl: /FIGlobal.h\nint hidden() { return extent(); }\n")
    with open(tree / "reverse/functions.csv", "a", newline="\n") as f:
        f.write(f"?hidden@@YAHXZ,,0x00405000,6,{consumer},matched,\n")
    _git(tree, "add", "-A")
    p = plan(tree)
    assert "Code/Game/Global.h" in p.after and consumer in p.verify


def test_a_string_initializer_is_not_an_address(tree, monkeypatch):           # finding 2
    monkeypatch.setattr(rename, "retail_extent", lambda ctx, rva, size: (".data", ".data", b"4194304\0"))
    prepared = BRIDGED_PREPARED.replace("unsigned int g_00A01000[3]", "unsigned char g_00A01000[8]")
    p = plan(tree, new="?g_00A01000@@3PAEA", retype="unsigned char [8]", size="8", initializer='"4194304"',
             prepared={BRIDGED: prepared.encode()})
    assert 'unsigned char g_00A01000[8] = "4194304";' in text(p, OWNER)
    assert rename.image_literals("{'A', \"0x00E02134\"}") == []
    assert rename.image_literals("{040000000}") == ["040000000"]          # octal 0x800000


# ------------------------------------------------------------ apply, post-build proof

def snapshot(root):
    return {p.relative_to(root).as_posix(): p.read_bytes() for p in root.rglob("*")
            if p.is_file() and ".git" not in p.parts and "add_match.lock" not in p.name}


def test_apply_rolls_back_when_the_objects_do_not_prove_it(tree, monkeypatch):
    before = snapshot(tree)
    monkeypatch.setattr(rename, "retype_object_problems",
                        lambda ctx, r: ["data_rows.py refuses the retyped row: initializer differs from retail at +0x4"])
    with pytest.raises(VerifyFailed, match="initializer differs from retail"):
        rename.apply_rename(plan(tree), ctx=ctx_of(tree), verify=lambda ctx, sources: True, checks=None)
    assert snapshot(tree) == before
    monkeypatch.setattr(rename, "retype_object_problems", lambda ctx, r: [])
    rename.apply_rename(plan(tree), ctx=ctx_of(tree), verify=lambda ctx, sources: True, checks=None)
    assert "unsigned int g_00A01000[3];" in (tree / OWNER).read_text()


def coff(path, symbols):
    """A real COFF object: one .data section, the given (name, section, storage) symbols."""
    import link_cycle
    link_cycle.write_coff(path, [(".data", 0xC0300040, bytes(12), 0)],
                          [(name, section, 0, storage) for name, section, storage in symbols], {})
    return path


@pytest.fixture
def objects(tmp_path, monkeypatch):
    import build
    import data_rows
    made = {}
    monkeypatch.setattr(build, "obj_path", lambda source: made[Path(source).name])
    monkeypatch.setattr(data_rows, "load", lambda: [])
    monkeypatch.setattr(data_rows, "verify_row", lambda row, img, resolve, compile=True: (True, "ok"))
    import reloc_ledger
    monkeypatch.setattr(reloc_ledger, "Image", lambda: None)
    monkeypatch.setattr(rename, "preprocess_unit", lambda ctx, rel: ("", None))
    monkeypatch.setattr(build, "load_function_rows", lambda: [])
    return made, tmp_path


def retype_record(sources):
    return {"word": "g_00A01000", "old": OLD, "new": NEW, "type": TYPE, "size": 12, "owner": OWNER,
            "row": {"address": "0x00A01000"}, "sources": sources, "start": 0x00A01000, "absorbed": []}


def test_object_check_passes_a_clean_owner(tree, objects):
    made, tmp = objects
    made["ThunksRva00401000.cpp"] = coff(tmp / "owner.obj", [(NEW, 1, 2)])
    made["Register.cpp"] = coff(tmp / "user.obj", [(NEW, 0, 2)])
    assert rename.retype_object_problems(ctx_of(tree), retype_record([OWNER, USER])) == []


def test_object_check_reads_a_rebuilt_asm_by_its_object_alone(tree, objects, monkeypatch):
    """The scan rebuilds a stale .asm; no preprocessor reads one, and its object still answers."""
    made, tmp = objects
    asked = []
    monkeypatch.setattr(rename, "preprocess_unit", lambda ctx, rel: asked.append(rel) or ("", None))
    made["ThunksRva00401000.cpp"] = coff(tmp / "owner.obj", [(NEW, 1, 2)])
    made["Thunk.asm"] = coff(tmp / "thunk.obj", [("_thunk", 1, 2)])
    unit = "Code/Game/Thunk.asm"
    assert rename.retype_object_problems(ctx_of(tree), retype_record([OWNER, unit])) == []
    assert asked == [OWNER]
    made["Thunk.asm"] = coff(tmp / "thunk2.obj", [("_thunk", 1, 2), (OLD, 0, 2)])
    problems = rename.retype_object_problems(ctx_of(tree), retype_record([OWNER, unit]))
    assert problems and f"{unit}'s object still names {OLD}" in problems[0]


def test_object_check_refuses_a_compiler_built_global(tree, objects):
    made, tmp = objects
    made["ThunksRva00401000.cpp"] = coff(tmp / "owner.obj", [(NEW, 1, 2), ("??__Eg_00A01000@@YAXXZ", 1, 2)])
    problems = rename.retype_object_problems(ctx_of(tree), retype_record([OWNER]))
    assert problems and "constructs g_00A01000 itself" in problems[0]


def test_object_check_refuses_a_surviving_old_symbol(tree, objects):
    made, tmp = objects
    made["ThunksRva00401000.cpp"] = coff(tmp / "owner.obj", [(NEW, 1, 2)])
    made["Register.cpp"] = coff(tmp / "user.obj", [(OLD, 0, 2)])
    problems = rename.retype_object_problems(ctx_of(tree), retype_record([OWNER, USER]))
    assert problems and "still names ?g_00A01000@@3IA" in problems[0]


def test_object_check_counts_definitions_in_every_rebuilt_object(tree, objects):   # finding 2
    made, tmp = objects
    made["ThunksRva00401000.cpp"] = coff(tmp / "owner.obj", [(NEW, 1, 2)])
    made["EraseRva00403000.cpp"] = coff(tmp / "erase.obj", [(NEW, 1, 2)])      # a second definition
    problems = rename.retype_object_problems(ctx_of(tree), retype_record([OWNER, BRIDGED]))
    assert problems and "defined 2 time(s)" in problems[0]
    made["ThunksRva00401000.cpp"] = coff(tmp / "owner2.obj", [(NEW, 0, 2)])    # defined only outside the owner
    made["EraseRva00403000.cpp"] = coff(tmp / "erase2.obj", [(NEW, 1, 2)])
    problems = rename.retype_object_problems(ctx_of(tree), retype_record([OWNER, BRIDGED]))
    assert problems and f"once, in {OWNER}" in problems[0]


def test_object_check_refuses_a_byte_mismatch(tree, objects, monkeypatch):
    made, tmp = objects
    made["ThunksRva00401000.cpp"] = coff(tmp / "owner.obj", [(NEW, 1, 2)])
    import data_rows
    monkeypatch.setattr(data_rows, "verify_row",
                        lambda row, img, resolve, compile=True: (False, "initializer differs from retail at +0x4"))
    problems = rename.retype_object_problems(ctx_of(tree), retype_record([OWNER]))
    assert problems == ["data_rows.py refuses the retyped row: initializer differs from retail at +0x4"]


# ------------------------------------------------------------ the command line

def test_cli_takes_no_basis_and_needs_size(tree, capsys):
    with pytest.raises(SystemExit):
        rename.main(["global", "--name", OLD, "--new", NEW, "--retype", TYPE, "--evidence", "x",
                     "--root", str(tree), "--dry-run", "--no-claim"])
    with pytest.raises(SystemExit):
        rename.main(["global", "--name", OLD, "--new", NEW, "--retype", TYPE, "--size", "12", "--evidence", "x",
                     "--basis", "inferred", "--root", str(tree), "--dry-run", "--no-claim"])
    assert "--retype" in capsys.readouterr().err


# ------------------------------------------------------------ the data route (P30, P35)
# Retail's statements are read through tools/retail_identity.py: `route` gives it a table of
# this tree's two extents and makes their facts hold.

INNER = "?g_00A01008@@3HA"


def fact(kind, site, value, code=None):
    import retail_identity
    return retail_identity.Fact(kind, site, value, code)


LOW, STORE, HIGH = fact("offset", 0x00401000, -256, "b800ffffff"), fact("stores", 0x0040100B, 0x00E01000, "8888"), \
    fact("offset", 0x00401012, 512, "3d00020000")
AT_START, AT_INNER = fact("stores", 0x00401020, 0x00E01000, "b9"), fact("stores", 0x00401030, 0x00E01008, "a1")


def extent(**overrides):
    import retail_identity
    args = dict(old=OLD, new=NEW, start=0x00A00F00, size=0x300, absorbs=(), facts=(LOW, STORE, HIGH))
    args.update(overrides)
    return retail_identity.Extent(**args)


@pytest.fixture
def route(tree, monkeypatch):
    import retail_identity
    held = {f.site: retail_identity.expected(f) for f in (LOW, STORE, HIGH, AT_START, AT_INNER)}
    monkeypatch.setattr(retail_identity, "read_retail", lambda rva, size: held[rva][:size])
    monkeypatch.setattr(retail_identity, "EXTENTS", (extent(),))
    return tree


def moved(root, **overrides):
    args = dict(address="0x00A00F00", size="0x300")
    args.update(overrides)
    return plan(root, **args)


def add_inner(root):
    """A row inside the placeholder's extent, in its own unit, read by another unit."""
    write(root, "reverse/data_rows.csv", DATA_ROWS + f"{INNER},0x00A01008,rva,4,.data,{OWNER},matched,x,m\n")
    write(root, "reverse/data_ledger.csv", LEDGER + f"0x00A01008,4,.data,global,{INNER},{OWNER},owned,,1,3\n")
    write(root, OWNER, OWNER_SRC + "int g_00A01008;\n")
    write(root, USER, USER_SRC + "extern int g_00A01008;\nint inner() { return g_00A01008; }\n")
    _git(root, "add", "-A")


USER_ABSORBED = """extern unsigned int g_00A01000[3];
void reg(void *p) { (void)p; (void)&g_00A01000; }
int inner() { return *(int *)(g_00A01000 + 2); }
"""
OWNER_ABSORBED = OWNER_SRC.replace("unsigned g_00A01000;", "unsigned int g_00A01000[3];")


def absorbing(root, monkeypatch, facts=(AT_START, AT_INNER), **overrides):
    import retail_identity
    monkeypatch.setattr(retail_identity, "EXTENTS", (extent(start=0x00A01000, size=12, facts=facts,
                                                            absorbs=((INNER, 0x00A01008),)),))
    args = dict(absorb=[INNER], prepared={BRIDGED: BRIDGED_PREPARED.encode(), USER: USER_ABSORBED.encode(),
                                          OWNER: OWNER_ABSORBED.encode()})
    args.update(overrides)
    return plan(root, **args)


# ---- a move

def test_a_move_rekeys_the_row_and_the_ledger_at_the_new_start(route):
    p = moved(route)
    assert p.after["reverse/data_rows.csv"].decode().splitlines()[1].startswith(f"{NEW},0x00A00F00,rva,768,.data,{OWNER},")
    ledger = text(p, "reverse/data_ledger.csv").splitlines()
    assert ledger[1].startswith(f"0x00A00F00,768,.data,global,{NEW},{OWNER},")
    assert text(p, "reverse/deleted_rows.csv").splitlines()[-1].startswith(f'{OLD},0x00A01000,"Retyped')
    assert {0x00A00F00, 0x00A01000} <= set(p.claims)
    assert p.retype["start"] == 0x00A00F00 and p.retype["row"]["address"] == "0x00A00F00"


def test_a_va_row_moves_in_its_own_spelling(route):
    write(route, "reverse/data_rows.csv", DATA_ROWS.replace(f"{OLD},0x00A01000,rva,", f"{OLD},0x00E01000,va,"))
    _git(route, "add", "-A")
    line = text(moved(route), "reverse/data_rows.csv").splitlines()[1]
    assert line.startswith(f"{NEW},0x00E00F00,va,768,")


def test_the_entrys_record_stands_in_retail_identitys_form(route):
    import retail_identity
    p = moved(route)
    record, prose = p.evidence.split("; ", 1)
    assert record == "retail:0x00401000 offset=-256 stores=0x00E01000 offset=512" and retail_identity.well_formed(record)
    assert prose.startswith("image_iso")                        # the prose stays beside it
    assert record in text(p, "reverse/data_rows.csv")


@pytest.mark.parametrize("overrides,message", [
    (dict(address="0x00A01000"), "is not below"),
    (dict(address="0x00E00F00"), "is not below"),           # a VA spelled for an RVA
    (dict(address="zero"), "is not a number"),
    (dict(size="0x40"), "does not contain"),
    (dict(address="0x00A00F04"), "EXTENTS"),                # not the entry's start
    (dict(size="0x400"), "EXTENTS"),                        # not the entry's size
    (dict(new="?g_00A01000@@3PAHA"), "EXTENTS"),            # no entry for this spelling
])
def test_a_move_makes_only_the_change_an_entry_spells_out(route, overrides, message):
    with pytest.raises(Refusal, match=re.escape(message)):
        moved(route, **overrides)


def test_a_move_refuses_an_entry_retail_does_not_hold(route, monkeypatch):
    import retail_identity
    monkeypatch.setattr(retail_identity, "EXTENTS", (extent(facts=(LOW, fact("stores", 0x0040100B, 0x00E01004, "8888"))),))
    with pytest.raises(Refusal, match="retail does not state .* holds"):
        moved(route)


@pytest.mark.parametrize("overrides,message", [
    (dict(facts=(STORE,)), "reach"),
    (dict(facts=(LOW,)), "reach"),
    (dict(facts=(STORE, HIGH)), "reach"),
    (dict(facts=(fact("offset", 0x00401000, -300, "b800ffffff"), STORE)), "reach"),      # bytes differ
    (dict(facts=(fact("offset", 0x00401012, -256, "3d00020000"), STORE)), "reach"),      # the code says 512
    (dict(facts=(LOW, STORE, fact("stores", 0x00401040, 0x00E05000, "a1"))), "outside"),
    (dict(facts=(LOW, fact("stores", 0x0040100C, 0x00E01000, "8888"))), "cannot be read"),
    (dict(facts=(AT_START,), absorbs=((INNER, 0x00A01008),), start=0x00A01000, size=12), "absorbed"),
    (dict(facts=(AT_INNER,), absorbs=((INNER, 0x00A01008),), start=0x00A01000, size=12), "reach"),
])
def test_an_entry_must_reach_its_start_and_every_absorbed_row(monkeypatch, overrides, message):
    import retail_identity
    held = {f.site: retail_identity.expected(f) for f in (LOW, STORE, HIGH, AT_START, AT_INNER)}
    held[0x00401040] = retail_identity.expected(fact("stores", 0x00401040, 0x00E05000, "a1"))
    monkeypatch.setattr(retail_identity, "read_retail", lambda rva, size: held[rva][:size])
    problems = retail_identity.extent_problems(extent(**overrides))
    assert problems and any(message in line for line in problems)


def test_every_entry_of_the_real_table_states_its_extent(monkeypatch):
    """Its shape on any tree; held against the image by the test below where the image is."""
    import retail_identity
    monkeypatch.setattr(retail_identity, "facts_problems", lambda facts: [])
    assert len(retail_identity.EXTENTS) >= 2
    for each in retail_identity.EXTENTS:
        assert retail_identity.extent_problems(each) == []
        assert retail_identity.well_formed(retail_identity.record(each.facts))
        assert retail_identity.extent_of(each.old, each.new) is each


def test_the_real_table_holds_on_the_retail_image():
    import build
    import retail_identity
    if not build.EXE.exists():
        pytest.skip("no retail image here")
    for each in retail_identity.EXTENTS:
        assert retail_identity.extent_problems(each) == []


@pytest.mark.parametrize("extra,message", [
    ("0x00A00F80,4,.data,global,?g_00A00F80@@3IA,,unowned,,0,3\n", "data_ledger.csv name ?g_00A00F80@@3IA"),
    ("0x00A00F00,4,.data,global,?g_00A00F00@@3IA,,unowned,,0,3\n", "binds 0x00A00F00"),
])
def test_a_move_refuses_a_name_in_the_space_it_takes(route, extra, message):
    with open(route / "reverse/data_ledger.csv", "a", newline="\n") as f:
        f.write(extra)
    _git(route, "add", "-A")
    with pytest.raises(Refusal, match=re.escape(message)):
        moved(route)


@pytest.mark.parametrize("line,refused", [
    ("0x00A00EFC,8,.data,global,?g_00A00EFC@@3_JA,,unowned,,0,3\n", True),     # the review's repro: four bytes over
    ("0x00A00EFC,4,.data,global,?g_00A00EFC@@3IA,,unowned,,0,3\n", False),     # ends exactly at the new start
])
def test_a_ledger_extent_running_up_from_below_the_start(route, line, refused):
    with open(route / "reverse/data_ledger.csv", "a", newline="\n") as f:
        f.write(line)
    _git(route, "add", "-A")
    if refused:
        with pytest.raises(Refusal, match=r"data_ledger.csv name \?g_00A00EFC@@3_JA at 0x00A00EFC\+8"):
            moved(route)
    else:
        assert moved(route).retype["start"] == 0x00A00F00


def test_a_move_refuses_a_data_row_in_the_space_it_takes(route):
    with open(route / "reverse/data_rows.csv", "a", newline="\n") as f:
        f.write(f"?g_00A00F80@@3HA,0x00A00F80,rva,4,.data,{OWNER},matched,x,m\n")
    _git(route, "add", "-A")
    with pytest.raises(Refusal, match="overlaps another owner: data row"):
        moved(route)


@pytest.mark.parametrize("address", ["0x00A00F00", "0x00A01000"])
def test_a_move_refuses_a_converged_address_at_either_end(route, address):
    write(route, "reverse/data_converged.csv", f"address,name,evidence\n{address},?other@@3HA,link\n")
    _git(route, "add", "-A")
    with pytest.raises(Refusal, match="converged address"):
        moved(route)


def test_a_move_refuses_non_zero_bytes_in_the_space_it_takes(route, monkeypatch):
    monkeypatch.setattr(rename, "retail_extent", lambda ctx, rva, size: (".data", ".data", b"\x01" + bytes(size - 1)))
    with pytest.raises(Refusal, match=r"non-zero bytes at 0x00A00F00\+0x0"):
        moved(route)


# ---- a const placeholder

CONST = "?g_00A01000@@3QBIB"


def const_tree(root, section=".data"):
    write(root, "reverse/functions.csv", FUNCTIONS.replace(OLD, CONST))
    write(root, "reverse/data_rows.csv", DATA_ROWS.replace(f"{OLD},0x00A01000,rva,4,.data", f"{CONST},0x00A01000,rva,4,{section}"))
    write(root, "reverse/data_ledger.csv", LEDGER.replace(f";{VEC}", "").replace(OLD, CONST))
    write(root, "reverse/symbols.csv", "name,address,notes\n")
    write(root, "reverse/hatch_baseline.tsv", HATCHES.replace(f"alternatename\t{BRIDGED}\t{VEC}\t1\n", ""))
    write(root, OWNER, "extern const unsigned int g_00A01000[];\nconst unsigned int g_00A01000[1] = { 0 };\n"
          "void thunk() {}\n")
    write(root, USER, "extern const unsigned int g_00A01000[];\nvoid reg(void *p) { (void)p; }\n")
    write(root, BRIDGED, "void erase() {}\n")
    _git(root, "add", "-A")


def test_a_const_placeholder_becomes_mutable_in_data(route):
    const_tree(route)
    p = plan(route, name=CONST, prepared={})
    assert text(p, OWNER).count("unsigned int g_00A01000[3]") == 2 and "const" not in text(p, OWNER)
    assert text(p, USER).startswith("extern unsigned int g_00A01000[3];")
    assert text(p, "reverse/data_rows.csv").splitlines()[1].startswith(f"{NEW},0x00A01000,rva,12,.data,")


def test_a_const_placeholder_in_read_only_data_stays(route, monkeypatch):
    const_tree(route, ".rdata")
    monkeypatch.setattr(rename, "retail_extent", lambda ctx, rva, size: (".rdata", ".rdata", bytes(size)))
    with pytest.raises(Refusal, match="only a table in retail's .data"):
        plan(route, name=CONST, prepared={})


def test_a_new_const_spelling_is_still_refused(route):
    const_tree(route)
    with pytest.raises(Refusal, match="keeps the identifier"):
        plan(route, name=CONST, new="?g_00A01000@@3QBIB2", prepared={})
    with pytest.raises(Refusal, match="keeps the identifier"):
        plan(route, name=CONST, new="?g_00A01000@@3PBIB", prepared={})


# ---- a global only the ledger owns

def ledger_only(root, line=f"0x00A01000,4,.data,global,{OLD},{OWNER},owned,,1,8"):
    write(root, "reverse/data_rows.csv", DATA_ROWS.replace(DATA_ROWS.splitlines()[1] + "\n", ""))
    write(root, "reverse/data_ledger.csv", LEDGER.replace(LEDGER.splitlines()[1], line))
    _git(root, "add", "-A")


def test_a_ledger_owned_global_gains_its_data_row(route):
    ledger_only(route)
    p = plan(route, model="claude-opus-5-5")
    rows = text(p, "reverse/data_rows.csv").splitlines()
    assert rows[1] == f"?g_00A02000@@3HA,0x00A02000,rva,4,.data,{OWNER},matched,other,m"
    assert rows[2].startswith(f"{NEW},0x00A01000,rva,12,.data,{OWNER},matched,")
    assert rows[2].endswith(",claude-opus-5-5") and "Retyped from" in rows[2]
    assert text(p, "reverse/data_ledger.csv").splitlines()[1].startswith(f"0x00A01000,12,.data,global,{NEW},{OWNER},")
    assert p.retype["row"]["model"] == "claude-opus-5-5"


def test_a_ledger_owned_global_needs_a_model_for_its_row(route):
    ledger_only(route)
    with pytest.raises(Refusal, match="--model"):
        plan(route)


@pytest.mark.parametrize("line", [
    f"0x00A01000,4,.data,global,{OLD},,unowned,,0,8",
    f"0x00A01000,4,.data,global,{OLD},{OWNER},provisional,{OLD};{VEC},1,8",
    f"0x00A01000,4,.data,string,{OLD},{OWNER},owned,,1,8",
])
def test_only_a_source_owned_ledger_global_gains_a_row(route, line):
    ledger_only(route, line)
    with pytest.raises(Refusal, match="names 0 reverse/data_rows.csv rows"):
        plan(route, model="m")


# ---- an absorbed row

def test_an_absorbed_row_goes_from_every_ledger(route, monkeypatch):
    add_inner(route)
    p = absorbing(route, monkeypatch)
    rows = text(p, "reverse/data_rows.csv")
    assert INNER not in rows.replace("; retail", "")
    assert not [line for line in rows.splitlines() if line.startswith(INNER)]
    ledger = text(p, "reverse/data_ledger.csv").splitlines()
    assert not [line for line in ledger if INNER in line]
    assert ledger[1] == f"0x00A01000,12,.data,global,{NEW},{OWNER},owned,,1,11"     # its references stay counted
    tombstones = text(p, "reverse/deleted_rows.csv").splitlines()
    assert tombstones[-1].startswith(f'{INNER},0x00A01008,"Retyped') and f"absorbed at 0x00A01008 into {NEW}" in tombstones[-1]
    assert tombstones[-2].startswith(f'{OLD},0x00A01000,"Retyped')
    assert 0x00A01008 in p.claims
    assert p.retype["absorbed"] == [("g_00A01008", INNER)]
    assert (INNER, NEW, 0x00A01008) in p.renamed_data
    assert USER in p.verify and OWNER in p.verify


def test_an_absorbed_row_noted_on_a_function_row_follows_the_note(route, monkeypatch):
    add_inner(route)
    write(route, "reverse/functions.csv", FUNCTIONS.replace("?erase@@YAXXZ,,0x00403000,16,"
                                                            f"{BRIDGED},matched,", "?erase@@YAXXZ,,0x00403000,16,"
                                                            f"{BRIDGED},matched,reads {INNER}"))
    _git(route, "add", "-A")
    assert f"reads {NEW}" in text(absorbing(route, monkeypatch), "reverse/functions.csv")


@pytest.mark.parametrize("overrides,message", [
    (dict(absorb=["?nothing@@3HA"]), "names 0 data rows"),
    (dict(absorb=["??_C@_01@"]), "is not a global datum"),
    (dict(absorb=["_plain"]), "is not a global datum"),
    (dict(absorb=[OLD]), "is the global being retyped"),
    (dict(size="8"), "not wholly inside"),
    (dict(size="10"), "not wholly inside"),
    (dict(size="16"), "EXTENTS"),                            # not the entry's size
    (dict(facts=(AT_START,)), "where ?g_00A01008@@3HA is absorbed"),
    (dict(facts=(AT_INNER,)), "no fact reaches the start"),
    (dict(prepared={BRIDGED: BRIDGED_PREPARED.encode(), OWNER: OWNER_ABSORBED.encode()}), "--absorb needs --prepared"),
    (dict(prepared={BRIDGED: BRIDGED_PREPARED.encode(), USER: USER_ABSORBED.encode() + b"int r() { return g_00A01008; }\n",
                    OWNER: OWNER_ABSORBED.encode()}), "still names g_00A01008"),
    (dict(prepared={BRIDGED: BRIDGED_PREPARED.encode(), USER: USER_ABSORBED.encode() + f"// {INNER}\n".encode(),
                    OWNER: OWNER_ABSORBED.encode()}), "still names g_00A01008"),
])
def test_an_absorb_refuses_what_it_cannot_prove(route, monkeypatch, overrides, message):
    add_inner(route)
    with pytest.raises(Refusal, match=re.escape(message)):
        absorbing(route, monkeypatch, **overrides)


def test_an_absorbed_row_at_the_start_is_no_interior(route, monkeypatch):
    add_inner(route)
    write(route, "reverse/data_rows.csv", DATA_ROWS + f"{INNER},0x00A01000,rva,4,.data,{OWNER},matched,x,m\n")
    _git(route, "add", "-A")
    with pytest.raises(Refusal, match="not wholly inside"):
        absorbing(route, monkeypatch)


def test_an_absorbed_row_of_another_unit_refuses(route, monkeypatch):
    add_inner(route)
    write(route, "reverse/data_rows.csv", DATA_ROWS + f"{INNER},0x00A01008,rva,4,.data,{USER},matched,x,m\n")
    write(route, "reverse/data_ledger.csv", LEDGER + f"0x00A01008,4,.data,global,{INNER},{USER},owned,,1,3\n")
    _git(route, "add", "-A")
    with pytest.raises(Refusal, match="the retype takes a row of its own unit"):
        absorbing(route, monkeypatch)


def test_an_absorb_needs_both_records_of_the_row_in_its_unit(route, monkeypatch):
    """The review's repro: the data row says OWNER, the ledger row another source."""
    add_inner(route)
    write(route, "reverse/data_ledger.csv", LEDGER + f"0x00A01008,4,.data,global,{INNER},{USER},owned,,1,3\n")
    _git(route, "add", "-A")
    with pytest.raises(Refusal, match="is defined by Code/Game/Register.cpp, not .*own unit"):
        absorbing(route, monkeypatch)


def test_an_absorb_refuses_a_ledger_extent_past_the_owners(route, monkeypatch):
    add_inner(route)
    write(route, "reverse/data_ledger.csv", LEDGER + f"0x00A01008,16,.data,global,{INNER},{OWNER},owned,,1,3\n")
    _git(route, "add", "-A")
    with pytest.raises(Refusal, match="gives .* 16 B at 0x00A01008: not wholly inside"):
        absorbing(route, monkeypatch)


def test_an_unsourced_ledger_row_does_not_disagree(route, monkeypatch):
    add_inner(route)
    write(route, "reverse/data_ledger.csv", LEDGER + f"0x00A01008,4,.data,global,{INNER},,unowned,,0,3\n")
    _git(route, "add", "-A")
    assert absorbing(route, monkeypatch).retype["absorbed"] == [("g_00A01008", INNER)]


def test_an_absorbed_row_with_other_ledger_spellings_refuses(route, monkeypatch):
    add_inner(route)
    write(route, "reverse/data_ledger.csv",
          LEDGER + f"0x00A01008,4,.data,global,{INNER},{OWNER},provisional,{INNER};?other@@3HA,1,3\n")
    _git(route, "add", "-A")
    with pytest.raises(Refusal, match="binds other spellings"):
        absorbing(route, monkeypatch)


def test_a_pinned_row_refuses_absorption(route, monkeypatch):
    add_inner(route)
    write(route, "reverse/symbols.csv", f"name,address,notes\n{OLD},0x00E01000,data pin\n{INNER},0x00E01008,data pin\n")
    _git(route, "add", "-A")
    with pytest.raises(Refusal, match="symbols.csv pins"):
        absorbing(route, monkeypatch)


@pytest.mark.parametrize("rel,body", [
    ("reverse/hatch_baseline.tsv", HATCHES + f"alternatename\tCode/Game/Other.cpp\t{INNER}\t1\n"),
    ("reverse/gate_baseline.txt", f"{INNER} waits\n"),
    ("reverse/some_whitelist.txt", f"{INNER}\n"),
])
def test_a_frozen_key_refuses_absorption(route, monkeypatch, rel, body):
    add_inner(route)
    write(route, rel, body)
    _git(route, "add", "-A")
    with pytest.raises(Refusal, match="frozen, shrink-only"):
        absorbing(route, monkeypatch)


def test_a_converged_interior_row_refuses_absorption(route, monkeypatch):
    add_inner(route)
    write(route, "reverse/data_converged.csv", f"address,name,evidence\n0x00A01008,{INNER},link\n")
    _git(route, "add", "-A")
    with pytest.raises(Refusal, match="converged global"):
        absorbing(route, monkeypatch)


def test_without_an_absorb_an_interior_row_still_overlaps(route):
    add_inner(route)
    with pytest.raises(Refusal, match="overlaps another owner"):
        plan(route, prepared={BRIDGED: BRIDGED_PREPARED.encode()})


def test_a_second_ledger_name_at_a_moved_owner_still_overlaps(route):
    """`own` gives up the owner where it stands, not its name anywhere in the extent."""
    with open(route / "reverse/data_ledger.csv", "a", newline="\n") as f:
        f.write(f"0x00A01004,4,.data,global,{OLD},,unowned,,0,1\n")
    _git(route, "add", "-A")
    with pytest.raises(Refusal, match="overlaps another owner"):
        plan(route)


# ---- after the build

def route_record(sources, **overrides):
    return dict(retype_record(sources), **overrides)


def test_object_check_refuses_an_absorbed_symbol_in_any_object(tree, objects):
    made, tmp = objects
    made["ThunksRva00401000.cpp"] = coff(tmp / "owner.obj", [(NEW, 1, 2)])
    made["Register.cpp"] = coff(tmp / "user.obj", [("?g_00A01008@@3PAHA", 0, 2)])  # under another spelling too
    problems = rename.retype_object_problems(ctx_of(tree), route_record([OWNER, USER],
                                                                        absorbed=[("g_00A01008", INNER)]))
    assert problems and "still names ?g_00A01008@@3PAHA, absorbed into g_00A01000" in problems[0]


def test_object_check_refuses_an_absorbed_name_after_the_preprocessor(tree, objects, monkeypatch):
    made, tmp = objects
    made["ThunksRva00401000.cpp"] = coff(tmp / "owner.obj", [(NEW, 1, 2)])
    monkeypatch.setattr(rename, "preprocess_unit", lambda ctx, rel: ("extern int g_00A01008;\n", None))
    problems = rename.retype_object_problems(ctx_of(tree), route_record([OWNER], absorbed=[("g_00A01008", INNER)]))
    assert problems and "still names g_00A01008 after the preprocessor" in problems[0]


DIR32 = 6
DATA_FLAGS, CODE_FLAGS, DEBUG_FLAGS = 0xC0300040, 0x60500020, 0x42100040


def object_with(path, sections, symbols, relocations=None):
    """A real COFF object; a symbol is (name, section number, value), external unless named .static."""
    import link_cycle
    link_cycle.write_coff(path, [(name, flags, body, 0) for name, flags, body in sections],
                          [(n, sec, value, 2) for n, sec, value in symbols], relocations or {})
    return path


@pytest.fixture
def references(tree, tmp_path, monkeypatch):
    """retype_reference_problems over OWNER: one function row, whose DIR32 pairs the test gives,
    in an object with no relocations until a test writes one to `made["obj"]`."""
    import build
    import data_rows
    import name_dependents
    pairs = []
    made = {"obj": object_with(tmp_path / "plain.obj", [(".text", CODE_FLAGS, bytes(16))], [("?thunk@@YAXXZ", 1, 0)])}
    monkeypatch.setattr(build, "load_function_rows", lambda: [
        {"name": "?thunk@@YAXXZ", "source": OWNER, "target_size": "10", "notes": ""},
        {"name": "?not_rebuilt@@YAXXZ", "source": "Code/Game/Other.cpp", "target_size": "10", "notes": ""}])
    monkeypatch.setattr(build, "obj_path", lambda source: made["obj"])
    monkeypatch.setattr(build, "_dir32_row_pairs", lambda row, obj, statics: list(pairs) if row["source"] == OWNER else 1 / 0)
    monkeypatch.setattr(data_rows, "load", lambda: made.get("datas", []))
    monkeypatch.setattr(name_dependents, "_row_objects", lambda rows: {})
    monkeypatch.setattr(name_dependents, "_data_row_objects", lambda rows: {})
    return tree, pairs, made, tmp_path


def test_references_at_the_start_pass(references):
    tree, pairs, _made, _tmp = references
    pairs += [(NEW, 0x00E01000), ("?other@@3HA", 0x00E02000), ("?low@@3HA", 0x00E00FFC)]
    assert rename.retype_reference_problems(ctx_of(tree), retype_record([OWNER])) == []


def test_a_reference_with_the_wrong_addend_refuses(references):
    tree, pairs, _made, _tmp = references
    pairs.append((NEW, 0x00E01100))                  # the old table's zero point, read at +0 rather than +0x100
    problems = rename.retype_reference_problems(ctx_of(tree), retype_record([OWNER]))
    assert problems and "its addend is not its offset" in problems[0]


def test_a_reference_through_another_symbol_inside_the_extent_refuses(references):
    tree, pairs, _made, _tmp = references
    pairs.append(("?alias@@3HA", 0x00E01008))
    problems = rename.retype_reference_problems(ctx_of(tree), retype_record([OWNER]))
    assert problems and "inside the extent, through ?alias@@3HA" in problems[0]


def test_a_data_section_reference_no_row_speaks_for_refuses(references):
    """The review's repro: `unsigned char *saved = g_table;` beside a function with no relocations."""
    tree, _pairs, made, tmp = references
    made["obj"] = object_with(tmp / "saved.obj", [(".text", CODE_FLAGS, bytes(16)), (".data", DATA_FLAGS, bytes(4))],
                              [("?thunk@@YAXXZ", 1, 0), ("?saved@@3PAEA", 2, 0), (NEW, 0, 0)],
                              {2: [(0, NEW, DIR32)]})
    problems = rename.retype_reference_problems(ctx_of(tree), retype_record([OWNER]))
    assert problems and "at .data+0x0, where no row says what retail holds" in problems[0]


def test_a_code_reference_outside_every_row_refuses(references):
    tree, _pairs, made, tmp = references
    made["obj"] = object_with(tmp / "code.obj", [(".text", CODE_FLAGS, bytes(16))],
                              [("?thunk@@YAXXZ", 1, 0), (NEW, 0, 0)], {1: [(12, NEW, DIR32)]})
    problems = rename.retype_reference_problems(ctx_of(tree), retype_record([OWNER]))
    assert problems and "at .text+0xc, where no row says" in problems[0]


def test_a_reference_inside_a_row_and_in_debug_data_passes(references):
    tree, pairs, made, tmp = references
    pairs.append((NEW, 0x00A01000 + rename.IMAGE_BASE))
    made["obj"] = object_with(tmp / "row.obj", [(".text", CODE_FLAGS, bytes(16)), (".debug$S", DEBUG_FLAGS, bytes(8))],
                              [("?thunk@@YAXXZ", 1, 0), (NEW, 0, 0)], {1: [(4, NEW, DIR32)], 2: [(0, NEW, 11)]})
    assert rename.retype_reference_problems(ctx_of(tree), retype_record([OWNER])) == []


@pytest.mark.parametrize("ok,message", [(True, "fine"), (False, "the target differs from retail")])
def test_a_data_row_initializer_is_held_to_data_rows(references, monkeypatch, ok, message):
    import data_rows
    import reloc_ledger
    tree, _pairs, made, tmp = references
    made["datas"] = [{"name": "?saved@@3PAEA", "source": OWNER, "size": "4", "address": "0x00A02000",
                      "address_kind": "rva", "section": ".data", "status": "matched"}]
    made["obj"] = object_with(tmp / "saved.obj", [(".text", CODE_FLAGS, bytes(16)), (".data", DATA_FLAGS, bytes(4))],
                              [("?thunk@@YAXXZ", 1, 0), ("?saved@@3PAEA", 2, 0), (NEW, 0, 0)],
                              {2: [(0, NEW, DIR32)]})
    monkeypatch.setattr(reloc_ledger, "Image", lambda: None)
    monkeypatch.setattr(data_rows, "Resolver", lambda rows: None)
    monkeypatch.setattr(data_rows, "verify_row", lambda row, img, resolve, compile=True: (ok, message))
    problems = rename.retype_reference_problems(ctx_of(tree), retype_record([OWNER]))
    assert (problems == []) if ok else (problems and message in problems[0])


OUTSIDE = "Code/Game/Outside.cpp"


@pytest.fixture
def outside(tree, tmp_path, monkeypatch):
    """outside_references over OUTSIDE, whose object the test writes; `state["stale"]` marks it stale."""
    import build
    state = {"stale": False}
    monkeypatch.setattr(build, "compile_is_current", lambda source, output: not state["stale"])
    return tree, tmp_path, state


def outside_problems(tree, tmp_path, symbols, **record):
    path = object_with(tmp_path / "outside.obj", [(".text", CODE_FLAGS, bytes(16))], symbols)
    return rename.outside_references(ctx_of(tree), dict(retype_record([OWNER]), **record), {OUTSIDE: [path]})


@pytest.mark.parametrize("symbol", [OLD, NEW])
def test_a_current_object_outside_the_rebuilt_set_naming_it_refuses(outside, symbol):
    tree, tmp, _state = outside
    problems = outside_problems(tree, tmp, [("?f@@YAXXZ", 1, 0), (symbol, 0, 0)])
    assert len(problems) == 1 and f"{OUTSIDE} references g_00A01000 but this retype did not rebuild it" in problems[0]


def test_a_current_object_naming_an_absorbed_symbol_refuses(outside):
    tree, tmp, _state = outside
    problems = outside_problems(tree, tmp, [("?f@@YAXXZ", 1, 0), (INNER, 0, 0)], absorbed=[("g_00A01008", INNER)])
    assert problems and "did not rebuild it" in problems[0]


def test_a_current_object_that_does_not_name_it_passes(outside):
    tree, tmp, _state = outside
    assert outside_problems(tree, tmp, [("?f@@YAXXZ", 1, 0)]) == []


def test_a_stale_object_the_scan_did_not_clear_refuses(outside):
    tree, tmp, state = outside
    state["stale"] = True
    problems = outside_problems(tree, tmp, [("?f@@YAXXZ", 1, 0)])
    assert problems and "stale or missing and the compiler scan did not clear it" in problems[0]


def test_a_stale_object_the_scan_cleared_passes_and_is_not_read(outside):
    tree, tmp, state = outside
    state["stale"] = True
    assert outside_problems(tree, tmp, [("?f@@YAXXZ", 1, 0), (OLD, 0, 0)], cleared={OUTSIDE}) == []


def test_a_missing_object_the_scan_did_not_clear_refuses(tree, tmp_path):
    problems = rename.outside_references(ctx_of(tree), retype_record([OWNER]), {OUTSIDE: [tmp_path / "gone.obj"]})
    assert problems and "stale or missing" in problems[0]


def test_a_source_with_no_object_mapped_is_not_read_as_clean(tree):
    problems = rename.outside_references(ctx_of(tree), retype_record([OWNER]), {OUTSIDE: []})
    assert problems and "stale or missing" in problems[0]


def test_a_rebuilt_source_is_not_outside(outside):
    tree, tmp, _state = outside
    path = object_with(tmp / "owner.obj", [(".text", CODE_FLAGS, bytes(16))], [(NEW, 1, 0)])
    assert rename.outside_references(ctx_of(tree), retype_record([OWNER]), {OWNER: [path]}) == []


def test_a_missing_object_is_never_a_pass(references):
    tree, _pairs, made, tmp = references
    made["obj"] = tmp / "never-built.obj"
    problems = rename.retype_reference_problems(ctx_of(tree), retype_record([OWNER]))
    assert problems and "has no object" in problems[0]


def test_an_unreadable_body_is_never_a_pass(references, monkeypatch):
    import build
    tree, _pairs, _made, _tmp = references
    monkeypatch.setattr(build, "_dir32_row_pairs", lambda row, obj, statics: None)
    problems = rename.retype_reference_problems(ctx_of(tree), retype_record([OWNER]))
    assert problems and "cannot be read" in problems[0]


def test_the_object_check_runs_the_reference_check(tree, objects, monkeypatch):
    made, tmp = objects
    made["ThunksRva00401000.cpp"] = coff(tmp / "owner.obj", [(NEW, 1, 2)])
    monkeypatch.setattr(rename, "retype_reference_problems", lambda ctx, r: ["a wrong addend"])
    assert rename.retype_object_problems(ctx_of(tree), retype_record([OWNER])) == ["a wrong addend"]


def test_apply_keeps_the_whole_route_or_nothing(route, monkeypatch):
    add_inner(route)
    before = snapshot(route)
    monkeypatch.setattr(rename, "retype_object_problems", lambda ctx, r: ["a wrong addend"])
    with pytest.raises(VerifyFailed, match="a wrong addend"):
        rename.apply_rename(absorbing(route, monkeypatch), ctx=ctx_of(route), verify=lambda ctx, sources: True, checks=None)
    assert snapshot(route) == before
    monkeypatch.setattr(rename, "retype_object_problems", lambda ctx, r: [])
    rename.apply_rename(absorbing(route, monkeypatch), ctx=ctx_of(route), verify=lambda ctx, sources: True, checks=None)
    assert INNER not in [line.split(",")[0] for line in (route / "reverse/data_rows.csv").read_text().splitlines()]
    assert "g_00A01008" not in (route / USER).read_text()


@pytest.mark.parametrize("flag,value", [("--address", "0x00A00F00"), ("--absorb", INNER), ("--model", "m")])
def test_cli_route_flags_go_with_retype(tree, capsys, flag, value):
    with pytest.raises(SystemExit):
        rename.main(["global", "--name", OLD, "--new", "?g_new@@3IA", flag, value, "--basis", "inferred",
                     "--evidence", "x", "--root", str(tree), "--dry-run", "--no-claim"])
    assert "go with global --retype" in capsys.readouterr().err


# ------------------------------------------------------------ the whole route, live
# The real compiler, real objects and the real scan, on a miniature tree; only retail's bytes
# and its data image are given, since the tree has no retail. Nothing here stubs the scan.

CONSUMER = "Code/Game/Consumer.cpp"
PASTE_H = "Code/Game/Paste.h"
CONSUMER_BEFORE = '#include "Paste.h"\nextern unsigned int WRAP(_00A01000);\nint read() { return sizeof(WRAP(_00A01000)); }\n'
CONSUMER_AFTER = '#include "Paste.h"\nextern unsigned int WRAP(_00A01000)[3];\nint read() { return WRAP(_00A01000)[1]; }\n'


@pytest.fixture
def live(tree, monkeypatch):
    """`tree` built for real, the consumer holding no `##` and never calling the pasting macro.
    `retail` {name: the offset retail's DIR32 holds past the global's start} decides read_target_bytes."""
    import struct
    import subprocess as sp
    import build
    import data_rows
    import name_dependents
    import reloc_ledger
    write(tree, PASTE_H, "#define CAT(a,b) a##b\n#define WRAP(x) CAT(g,x)\n")
    write(tree, CONSUMER, CONSUMER_BEFORE)
    with open(tree / "reverse/functions.csv", "a", newline="\n") as f:
        f.write(f"?read@@YAHXZ,,0x00405000,32,{CONSUMER},matched,\n")
    write(tree, BRIDGED, BRIDGED_SRC.replace(f'#pragma comment(linker, "/alternatename:{VEC}={OLD}")\n', ""))
    write(tree, "reverse/hatch_baseline.tsv", HATCHES.replace(f"alternatename\t{BRIDGED}\t{VEC}\t1\n", ""))
    _git(tree, "add", "-A")
    monkeypatch.setattr(rename, "compiler_scan", REAL_SCAN)
    monkeypatch.setattr(build, "ROOT", tree)
    monkeypatch.setattr(build, "ensure_reference_current", lambda: None)
    objects = tree / "build" / "live"
    objects.mkdir(parents=True)
    monkeypatch.setattr(build, "obj_path", lambda source: objects / (Path(source).stem + ".obj"))

    def compile_units(sources):
        for rel in sources:
            source = tree / rel
            command, env = build.compiler_command(source, build.obj_path(source))
            done = sp.run(command, capture_output=True, env=env, cwd=str(tree), timeout=300)
            assert done.returncode == 0, done.stdout.decode("latin-1")[-600:]
    rows = [dict(zip(("name", "export_rva", "target_rva", "target_size", "source", "status", "notes"), line.split(",")))
            for line in (tree / "reverse/functions.csv").read_text().splitlines()[1:]]
    monkeypatch.setattr(build, "load_function_rows", lambda: rows)
    monkeypatch.setattr(name_dependents, "_row_objects",
                        lambda given: {r["source"]: [build.obj_path(tree / r["source"])] for r in rows})
    monkeypatch.setattr(name_dependents, "_data_row_objects", lambda given: {})
    monkeypatch.setattr(build, "compile_is_current", lambda source, output: output.exists())
    monkeypatch.setattr(data_rows, "load", lambda: [])
    monkeypatch.setattr(data_rows, "Resolver", lambda given: None)
    monkeypatch.setattr(data_rows, "verify_row", lambda row, img, resolve, compile=True: (True, "ok"))
    monkeypatch.setattr(reloc_ledger, "Image", lambda: None)
    retail = {"?read@@YAHXZ": 4}

    def read_target_bytes(rva, size):
        row = next(r for r in rows if int(r["target_rva"], 16) == rva)
        body, relocs = build.read_object_symbol_bytes(build.obj_path(tree / row["source"]), row["name"], size)
        held = bytearray(body[:size].ljust(size, b"\0"))
        for offset, kind, symbol in relocs:
            if kind == 6 and symbol == NEW and offset + 4 <= size:
                struct.pack_into("<I", held, offset, rename.IMAGE_BASE + 0x00A01000 + retail.get(row["name"], 0))
        return bytes(held)
    monkeypatch.setattr(build, "read_target_bytes", read_target_bytes)
    compile_units(sorted({r["source"] for r in rows}))
    return tree, retail, lambda ctx, sources: compile_units(sources) or True


def live_plan(root, consumer=CONSUMER_AFTER):
    prepared = {BRIDGED: BRIDGED_PREPARED.encode()}
    if consumer is not None:
        prepared[CONSUMER] = consumer.encode()
    return plan(root, prepared=prepared)


def sources_of(root):
    return {rel: (root / rel).read_bytes() for rel in (OWNER, USER, BRIDGED, CONSUMER, "reverse/data_rows.csv")}


def test_live_the_scan_selects_a_nested_paste_and_the_retype_lands(live):
    tree, _retail, verify = live
    assert "g_00A01000" not in (tree / CONSUMER).read_text()    # no text scan could have found it
    p = live_plan(tree)
    assert CONSUMER in p.verify and CONSUMER not in p.retype["cleared"]
    rename.apply_rename(p, ctx=ctx_of(tree), verify=verify, checks=None)
    assert (tree / CONSUMER).read_text() == CONSUMER_AFTER


def test_live_the_read_back_catches_a_wrong_addend_on_the_consumer_the_scan_selected(live):
    tree, retail, verify = live
    retail["?read@@YAHXZ"] = 8                                  # the code reads +4; retail holds +8
    before = sources_of(tree)
    with pytest.raises(VerifyFailed, match=r"\?read@@YAHXZ reads .* from base .*its addend is not its offset"):
        rename.apply_rename(live_plan(tree), ctx=ctx_of(tree), verify=verify, checks=None)
    assert sources_of(tree) == before


def test_live_a_stale_declaration_the_scan_selected_is_refused(live):
    """Left unprepared the macro still declares a scalar: the review's repro, caught after the rebuild."""
    tree, _retail, verify = live
    before = sources_of(tree)
    with pytest.raises(VerifyFailed, match="Code/Game/Consumer.cpp"):
        rename.apply_rename(live_plan(tree, consumer=None), ctx=ctx_of(tree), verify=verify, checks=None)
    assert sources_of(tree) == before


def test_live_an_escaped_spelling_in_a_pragma_joins_the_rebuild(live):
    """The real compiler leaves the escapes as written, and the unit has no other mention of the name."""
    tree, _retail, _verify = live
    unit = "Code/Game/Escaped.cpp"
    write(tree, unit, '#pragma comment(linker, "/alternatename:?g_\\x30\\x30A01000@@3IA=_other")\nint e() { return 0; }\n')
    write(tree, "Code/Game/Unrelated.h", "#define Q(x) q##x\n")
    write(tree, unit, '#include "Unrelated.h"\n' + (tree / unit).read_text())
    with open(tree / "reverse/functions.csv", "a", newline="\n") as f:
        f.write(f"?e@@YAHXZ,,0x00406000,6,{unit},matched,\n")
    _git(tree, "add", "-A")
    assert unit in live_plan(tree).verify


# ------------------------------------------------------------ preprocess_unit's inputs and limits
# A stand-in compiler in a real process: what it does is the test's, the tree it runs in is real.

FAKE_CL = r"""
import os, sys, time
script = sys.argv[1]
args = sys.argv[2:]
count = os.environ["FAKE_CL_COUNT"]
with open(count, "a") as f:
    f.write(" ".join(args) + "\n")
tries = sum(1 for _ in open(count))
if script == "hang":
    time.sleep(600)
if script == "hang_once" and tries == 1:
    time.sleep(600)
if script == "c1083_then_spin":
    if not any(a.startswith("-Isweep") for a in args):
        sys.stderr.write("x.cpp(9) : fatal error C1083: Cannot open include file: 'windows.h': No such file or directory\n")
        sys.stderr.flush()
        time.sleep(600)
elif script == "c1083_always":
    sys.stderr.write("x.cpp(9) : fatal error C1083: Cannot open include file: 'windows.h': No such file or directory\n")
    sys.stderr.flush()
    time.sleep(600)
elif script == "silent_once" and tries == 1:
    sys.exit(1)
elif script == "error":
    sys.stderr.write("x.cpp(3) : error C2143: syntax error\n")
    sys.exit(2)
sys.stdout.write("int preprocessed;\n")
"""


@pytest.fixture
def fake_cl(tree, tmp_path, monkeypatch):
    """Run preprocess_unit on `script` under FAKE_CL; returns (result, the argument lists it saw, seconds)."""
    import time
    import build
    compiler, count = tmp_path / "fake_cl.py", tmp_path / "count.txt"
    compiler.write_text(FAKE_CL)
    sweep = tmp_path / "sweep"
    sweep.mkdir()
    monkeypatch.setattr(build, "_SWEEP_INCLUDE_DIRS", [sweep])
    monkeypatch.setattr(build, "wine_path", lambda path: "sweep" if Path(path) == sweep else str(path))
    monkeypatch.setattr(rename, "PREPROCESS_TIMEOUT", 1.5)

    def run(script):
        monkeypatch.setattr(build, "compiler_command", lambda source, output: (
            [sys.executable, str(compiler), script, "-c", "-Fox.obj", "unit.cpp"],
            dict(os.environ, INCLUDE="base", FAKE_CL_COUNT=str(count))))
        started = time.monotonic()
        result = rename.preprocess_unit(ctx_of(tree), OWNER)
        seen = count.read_text().splitlines() if count.exists() else []
        return result, seen, time.monotonic() - started
    return run


def test_a_missing_include_is_retried_with_the_builds_sweep_directories(fake_cl):
    """The real run's hang: C1083 and then a spin. The build retries with these, so the scan must."""
    (text, why), seen, seconds = fake_cl("c1083_then_spin")
    assert why is None and text == "int preprocessed;\n"
    assert len(seen) == 2 and "-Isweep" not in seen[0] and "-Isweep unit.cpp" in seen[1]
    assert seconds < 1.5                                          # it never waited out the spin


def test_a_missing_include_after_the_retry_refuses_without_waiting(fake_cl):
    (text, why), seen, seconds = fake_cl("c1083_always")
    assert text is None and "the preprocessor refused it" in why and "C1083" in why
    assert len(seen) == 2 and seconds < 1.5


def test_a_unit_that_hangs_times_out_twice_and_reports_it(fake_cl):
    (text, why), seen, seconds = fake_cl("hang")
    assert text is None and "timed out twice" in why
    assert len(seen) == 2 and seconds < 10                        # killed, not waited for


def test_a_hang_that_clears_on_the_retry_passes(fake_cl):
    (text, why), seen, _seconds = fake_cl("hang_once")
    assert why is None and text == "int preprocessed;\n" and len(seen) == 2


def test_a_silent_launch_failure_is_retried(fake_cl):
    (text, why), seen, _seconds = fake_cl("silent_once")
    assert why is None and text == "int preprocessed;\n" and len(seen) == 2


def test_a_real_error_is_not_retried(fake_cl):
    (text, why), seen, _seconds = fake_cl("error")
    assert text is None and "C2143" in why and len(seen) == 1


def test_the_scan_refuses_on_a_unit_that_timed_out_and_prints_it(scanning, monkeypatch, capsys):
    tree, state = scanning
    unit = "Code/Game/Hangs.cpp"
    add_unit(tree, unit, "int h;\n", 0x00405000)
    state["stale"].add(unit)
    monkeypatch.setattr(rename, "preprocess_unit", lambda ctx, rel: (
        (None, "the preprocessor timed out twice, 300 s each") if rel == unit else ("", None)))
    with pytest.raises(Refusal, match=r"1 unit\(s\) did not preprocess.*Code/Game/Hangs.cpp"):
        plan(tree)
    assert "did not preprocess: Code/Game/Hangs.cpp: the preprocessor timed out twice" in capsys.readouterr().out

