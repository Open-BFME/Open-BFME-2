"""`tools/rename.py function --respell`: a row whose correct name differs from
its current one by more than the identifier.

`function` derives the new name by rewriting the identifier, so a row whose real
name differs anywhere else had no landing path. Two measured corrections needed
one: a 16-byte dispatcher named `AsObject` that reaches the vtable slot retail
overrides to return the Drawable (so its return type is wrong, not just its
identifier), and a class template rowed at the wrong width, where the identifier
is already right and only the template argument moves.

The new name is taken literally. Because no word rewrite can turn `Object *`
into `Drawable *`, the C++ comes in `--prepared` and the plan refuses to leave
any source still spelling the old name. Default behaviour is untouched: without
`--respell` a signature change is still refused, and the refusal now says what
would carry it. Identifier-only renames themselves are covered by the existing
rename suites, so they are not repeated here.
"""
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import name_agreement  # noqa: E402
import rename  # noqa: E402
from rename import Refusal  # noqa: E402

# A placeholder row whose real name differs in its return type and parameter
# too, which is the shape of the corrections this mode exists for.
OLD = "?Rva00113BA0@@YAHPAVGenSlot08@@@Z"
NEW = "?AsObject@@YAPAVObject@@PAVThing@@@Z"
IDENTIFIER_ONLY = "?AsObject@@YAHPAVGenSlot08@@@Z"
RVA = 0x00401000

# the identifier is already right here; only the template argument moves
WIDE_OLD = "?Rva00402000Get@@YAHPBD@Z"
WIDE_NEW = "?getSingleBitFromName@?$BitFlags@$0CEP@@@SAHPBD@Z"
WIDE_RVA = 0x00402000

FUNCTIONS = f"""name,export_rva,target_rva,target_size,source,status,notes
{OLD},,0x00401000,16,Code/Game/Module_AsObject.cpp,matched,BFME1 byte-identical donor
{WIDE_OLD},,0x00402000,54,Code/Game/BitFlags.cpp,matched,width anchor
?other@@YAXXZ,,0x00403000,8,Code/Game/Other.cpp,matched,unrelated
"""
SYMBOLS = "name,address,notes\n"
DELETED = "name,target_rva,reason\n"
NAME_BASIS = "kind,old,new,basis,evidence,source,rva\n"
# An inferred name needs a recorded approval, so each respell cites one.
NAME_AGREED = f"""id,kind,old,new,rva,agents,key,status,detail
nl-respell0001,function,Rva00113BA0,AsObject,0x00401000,w-aaaaaaaaaaaa@s1;w-bbbbbbbbbbbb@s2,Code/Game/Module_AsObject.cpp|function|0x00401000|Rva00113BA0,agreed,two-agent agreement
nl-respell0002,function,Rva00402000Get,getSingleBitFromName,0x00402000,w-aaaaaaaaaaaa@s1;w-bbbbbbbbbbbb@s2,Code/Game/BitFlags.cpp|function|0x00402000|Rva00402000Get,agreed,two-agent agreement
"""

AS_OBJECT = f"""// cl: /Ob0
// {OLD}, retail 0x00401000 (16B).
class Object;
class Thing
{{
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual Object *asObjectMeth();
}};
inline Object *AsObject(Thing *thing) {{ return thing ? thing->asObjectMeth() : 0; }}
Object *anchorAsObject(Thing *thing) {{ return AsObject(thing); }}
"""

AS_DRAWABLE = f"""// cl: /Ob0
// {NEW}, retail 0x00401000 (16B).
class Drawable;
class Thing
{{
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual Drawable *asDrawableMeth();
}};
inline Drawable *AsDrawable(Thing *thing) {{ return thing ? thing->asDrawableMeth() : 0; }}
Drawable *anchorAsDrawable(Thing *thing) {{ return AsDrawable(thing); }}
"""

BITFLAGS = f"""// cl: /O1
// {WIDE_OLD}
template <int N> class BitFlags {{ public: static int getSingleBitFromName(const char *token); }};
template <int N> int BitFlags<N>::getSingleBitFromName(const char *token) {{ return token ? 0 : -1; }}
template int BitFlags<304>::getSingleBitFromName(const char *token);
"""
BITFLAGS_WIDE = BITFLAGS.replace("304", "591").replace(WIDE_OLD, WIDE_NEW)
OTHER = "void other() {}\n"

# The approval is only an index: agreement is recomputed from the votes, so two
# distinct workers must have voted each spelling.
KEY_AS_OBJECT = "Code/Game/Module_AsObject.cpp|function|0x00401000|Rva00113BA0"
KEY_WIDE = "Code/Game/BitFlags.cpp|function|0x00402000|Rva00402000Get"
WORKERS = ("w-aaaaaaaaaaaa", "w-bbbbbbbbbbbb")
NAME_VOTES = "key,hash,model,session,worker,date\n" + "".join(
    f"{key},{name_agreement.digest(key, spelling)},seat{n},s{n},{worker},2026-11-07\n"
    for key, spelling in ((KEY_AS_OBJECT, "AsObject"), (KEY_WIDE, "getSingleBitFromName"))
    for n, worker in enumerate(WORKERS))


def _git(root, *args):
    subprocess.run(["git", "-C", str(root), *args], check=True, capture_output=True)


@pytest.fixture
def tree(tmp_path):
    files = {
        "reverse/functions.csv": FUNCTIONS,
        "reverse/symbols.csv": SYMBOLS,
        "reverse/deleted_rows.csv": DELETED,
        "reverse/name_basis.csv": NAME_BASIS,
        "reverse/name_agreed.csv": NAME_AGREED,
        "reverse/name_votes.csv": NAME_VOTES,
        "reverse/data_rows.csv": "name,address,address_kind,size,section,source,status,evidence,model\n",
        "reverse/exports.csv": "ordinal,rva,target_rva,section,kind,name\n",
        "reverse/gate_baseline.txt": "",
        "Code/Game/Module_AsObject.cpp": AS_OBJECT,
        "Code/Game/BitFlags.cpp": BITFLAGS,
        "Code/Game/Other.cpp": OTHER,
    }
    for rel, text in files.items():
        path = tmp_path / rel
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(text.encode("utf-8"))
    _git(tmp_path, "init", "-q")
    _git(tmp_path, "add", "-A")
    return tmp_path


def plan(root, **overrides):
    kwargs = dict(rva=RVA, basis="inferred", evidence="agree:nl-respell0001")
    kwargs.update(overrides)
    return rename.plan_rename("function", ctx=rename.Context(root, object_scan=False), **kwargs)


# ------------------------------------------------------- the default is unchanged

def test_without_respell_a_signature_change_is_still_refused(tree):
    with pytest.raises(Refusal) as error:
        plan(tree, new=NEW)
    assert "beyond the identifier" in str(error.value)


def test_the_refusal_names_both_the_identifier_rewrite_and_the_way_to_carry_it(tree):
    """The old message left the reader with no next step; it cost a batch."""
    with pytest.raises(Refusal) as error:
        plan(tree, new=NEW)
    assert IDENTIFIER_ONLY in str(error.value)
    assert "--respell" in str(error.value)


# -------------------------------------------------------------- what respell needs

def test_respell_without_prepared_sources_is_refused(tree):
    with pytest.raises(Refusal) as error:
        plan(tree, new=NEW, respell=True)
    assert "--prepared" in str(error.value)


def test_respell_refuses_an_identifier_only_spelling(tree):
    """That case has a simpler path, which stays authoritative."""
    with pytest.raises(Refusal) as error:
        plan(tree, new=IDENTIFIER_ONLY, respell=True,
             prepared={"Code/Game/Module_AsObject.cpp": AS_DRAWABLE.encode()})
    assert "without --respell" in str(error.value)


def test_respell_refuses_a_bare_identifier(tree):
    with pytest.raises(Refusal) as error:
        plan(tree, new="AsDrawable", respell=True,
             prepared={"Code/Game/Module_AsObject.cpp": AS_DRAWABLE.encode()})
    assert "whole mangled name" in str(error.value)


def test_prepared_sources_are_refused_without_respell(tree):
    with pytest.raises(Refusal) as error:
        plan(tree, new=IDENTIFIER_ONLY,
             prepared={"Code/Game/Module_AsObject.cpp": AS_DRAWABLE.encode()})
    assert "--prepared" in str(error.value)


# ------------------------------------------------------------------- the respell

def test_respell_takes_the_new_name_literally(tree):
    got = plan(tree, new=NEW, respell=True,
               prepared={"Code/Game/Module_AsObject.cpp": AS_DRAWABLE.encode()})
    assert got.new == NEW
    assert (OLD, NEW, RVA) in got.renamed_rows


def test_respell_verifies_the_prepared_source(tree):
    got = plan(tree, new=NEW, respell=True,
               prepared={"Code/Game/Module_AsObject.cpp": AS_DRAWABLE.encode()})
    assert "Code/Game/Module_AsObject.cpp" in got.verify
    assert got.after["Code/Game/Module_AsObject.cpp"] == AS_DRAWABLE.encode()


def test_respell_writes_the_new_name_into_the_ledger(tree):
    got = plan(tree, new=NEW, respell=True,
               prepared={"Code/Game/Module_AsObject.cpp": AS_DRAWABLE.encode()})
    rows = got.after["reverse/functions.csv"].decode()
    assert NEW in rows and OLD not in rows


def test_respell_carries_a_template_argument_and_a_new_scope(tree):
    """The width case: a free placeholder becomes a class template's static."""
    got = rename.plan_rename(
        "function", ctx=rename.Context(tree, object_scan=False), rva=WIDE_RVA,
        new=WIDE_NEW, respell=True, basis="inferred",
        evidence="agree:nl-respell0002",
        prepared={"Code/Game/BitFlags.cpp": BITFLAGS_WIDE.encode()})
    assert got.new == WIDE_NEW
    assert (WIDE_OLD, WIDE_NEW, WIDE_RVA) in got.renamed_rows


# ----------------------------------------------------- nothing may still spell it

def test_a_prepared_source_that_still_spells_the_old_name_is_refused(tree):
    with pytest.raises(Refusal) as error:
        plan(tree, new=NEW, respell=True,
             prepared={"Code/Game/Module_AsObject.cpp": (AS_DRAWABLE + f"// {OLD}\n").encode()})
    assert "still spells" in str(error.value)


def test_another_unit_that_still_spells_the_old_name_is_refused(tree):
    """Every unit naming the row must be prepared, or source and ledger disagree."""
    (tree / "Code/Game/Other.cpp").write_bytes(f"// {OLD}\nvoid other() {{}}\n".encode())
    _git(tree, "add", "-A")
    with pytest.raises(Refusal) as error:
        plan(tree, new=NEW, respell=True,
             prepared={"Code/Game/Module_AsObject.cpp": AS_DRAWABLE.encode()})
    assert "Code/Game/Other.cpp" in str(error.value)


def test_an_alias_pin_on_the_address_is_refused(tree):
    """Its own signature change cannot be derived from this one."""
    (tree / "reverse/symbols.csv").write_bytes(
        b"name,address,notes\n?Rva00113BA0@@YAHPAVGenSlot08View@@@Z,0x00401000,alias\n")
    _git(tree, "add", "-A")
    with pytest.raises(Refusal) as error:
        plan(tree, new=NEW, respell=True,
             prepared={"Code/Game/Module_AsObject.cpp": AS_DRAWABLE.encode()})
    assert "alias pin" in str(error.value)
