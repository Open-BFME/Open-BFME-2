"""tools/rename.py `global --retype` on a miniature tree: a rowed 4-byte placeholder
global retyped to its real extent, every declaration respelled, the data row, pins,
notes and data_ledger.csv row re-keyed, the bridging /alternatename and its hatch line
removed; and its refusals (overlap, non-zero retail bytes, a second definition, a
surviving old symbol, a converged address, a compiler-built type). Retail bytes and
verification are injected; the post-build object check runs on real COFF objects."""
import re
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import rename  # noqa: E402
from rename import Refusal, VerifyFailed  # noqa: E402

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
    with open(tree / "reverse/data_rows.csv", "a") as f:
        f.write(extra)
    _git(tree, "add", "-A")
    with pytest.raises(Refusal, match=re.escape("overlaps another owner") + ".*" + re.escape(message)):
        plan(tree)


def test_overlapping_ledger_name_or_code_refuses(tree):
    with open(tree / "reverse/data_ledger.csv", "a") as f:
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


def test_token_pasted_units_are_preprocessed(tree):                             # finding 2
    consumer = "Code/Game/Hidden.cpp"
    write(tree, consumer, "#define DECL(x) extern unsigned int g_##x\n#define SIZE(x) sizeof(g_##x)\n"
                          "int hidden() { DECL(00A01000); return SIZE(00A01000); }\n")
    header = "Code/Game/Paste.h"
    write(tree, header, "#define NAME(x) x##00A01000\n")
    includer = "Code/Game/Includer.cpp"
    write(tree, includer, '#include "Paste.h"\nint i() { return 0; }\n')
    other = "Code/Game/Unrelated.cpp"
    write(tree, other, "#define CAT(a, b) a##b\n#define P(x) p##x\nint u() { return 0; }\n")
    with open(tree / "reverse/functions.csv", "a", newline="\n") as f:
        for i, rel in enumerate((consumer, includer, other)):
            f.write(f"?f{i}@@YAHXZ,,0x0040{5 + i}000,6,{rel},matched,\n")
    _git(tree, "add", "-A")
    p = plan(tree)
    assert consumer in p.verify and includer in p.verify and other not in p.verify


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
    return made, tmp_path


def retype_record(sources):
    return {"word": "g_00A01000", "old": OLD, "new": NEW, "type": TYPE, "size": 12, "owner": OWNER,
            "row": {"address": "0x00A01000"}, "sources": sources}


def test_object_check_passes_a_clean_owner(tree, objects):
    made, tmp = objects
    made["ThunksRva00401000.cpp"] = coff(tmp / "owner.obj", [(NEW, 1, 2)])
    made["Register.cpp"] = coff(tmp / "user.obj", [(NEW, 0, 2)])
    assert rename.retype_object_problems(ctx_of(tree), retype_record([OWNER, USER])) == []


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
