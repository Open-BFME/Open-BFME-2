"""tools/rename.py class --fold on a miniature tree: one retail class rowed
under two placeholder names (its constructor under one, its destructors and
vftable under the other) folds into the name its vftable carries, only on
retail vftable evidence. The retail image is injected (rename.retail_vtables)
and so is verification, as in test_rename_virtual.py."""
import csv
import io
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import rename  # noqa: E402
from rename import Refusal, VerifyFailed  # noqa: E402

OLD = "BfmeWidgetBase"          # a placeholder (bfme token): the constructor's name
NEW = "Rva00402000"             # a placeholder: the destructors' and the vftable's name
TABLE = 0x00800000              # retail vftable rva (VA 0x00C00000)
DERIVED_TABLE = 0x00800100
OTHER_TABLE = 0x00800200
PURECALL = 0x0003B810
CTOR, DTOR, GDTOR = 0x00401000, 0x00402000, 0x00402010


def functions(new):
    return f"""name,export_rva,target_rva,target_size,source,status,notes
??0{OLD}@@QAE@XZ,,0x00401000,13,Code/Game/BaseCtor.cpp,matched,base ctor installs vtable 0x00C00000
??1{new}@@UAE@XZ,,0x00402000,7,Code/Game/Inline.cpp,matched,empty virtual dtor
??_G{new}@@UAEPAXI@Z,,0x00402010,29,Code/Game/Inline.cpp,matched,deleting dtor
??0Derived@@QAE@XZ,,0x00403000,40,Code/Game/DerivedCtor.cpp,matched,calls ??0{OLD}@@QAE@XZ
??1Derived@@UAE@XZ,,0x00404000,40,Code/Game/DerivedDtor.cpp,matched,inlines ??1{new}@@UAE@XZ
??0Other@@QAE@XZ,,0x00405000,20,Code/Game/Other.cpp,matched,unrelated ctor
"""


def symbols(new):
    return f"""name,address,notes
??1{OLD}@@UAE@XZ,0x00402000,base dtor pin under the constructor's name
??1Gen_uwm_00402000@@QAE@XZ,0x00402000,gen-uw-pin dtor target
"""


def ledger(new):
    return ("address,size,section,kind,name,source,status,names,defs,refs\n"
            f"0x00800000,20,.rdata,vtable,??_7{new}@@6B@,,literal,??_7{new}@@6B@;?g_00C00000@@3QBQBXB,0,3\n"
            "0x00800100,8,.rdata,vtable,??_7Derived@@6B@,,literal,,0,2\n")


BASE_CTOR = f"""// cl: /O2
// ??0{OLD}@@QAE@XZ @ 0x00401000
class {OLD}
{{
public:
\t{OLD}();
private:
\tunsigned char m_pad[4];
\tunsigned char m_04;
}};

{OLD}::{OLD}()
{{
\tm_04 = 0;
}}
"""


def inline(new):
    return f"""// ??1{new}@@UAE@XZ @ 0x00402000
class {new}
{{
public:
\tvirtual ~{new}();
}};

{new}::~{new}()
{{
}}
"""


DERIVED_CTOR = f"""class {OLD}
{{
public:
\t{OLD}();
\tvirtual ~{OLD}();
}};
class Derived : public {OLD}
{{
public:
\tDerived();
}};
Derived::Derived() {{}}
"""


def derived_dtor(new):
    return f"""class {new}
{{
public:
\tvirtual ~{new}();
}};
class Derived : public {new}
{{
public:
\tvirtual ~Derived();
}};
Derived::~Derived() {{}}
"""


OTHER = "class Other { public: Other(); };\nOther::Other() {}\n"


def _git(root, *args):
    subprocess.run(["git", "-C", str(root), *args], check=True, capture_output=True)


def make_tree(root, new=NEW):
    files = {
        "reverse/functions.csv": functions(new),
        "reverse/symbols.csv": symbols(new),
        "reverse/deleted_rows.csv": 'name,target_rva,reason\n?gone@@YAXXZ,0x00100000,"old, retired"\n',
        "reverse/data_rows.csv": "name,address,address_kind,size,section,source,status,evidence,model\n",
        "reverse/data_ledger.csv": ledger(new),
        "reverse/exports.csv": "ordinal,rva,target_rva,section,kind,name\n",
        "reverse/gate_baseline.txt": "",
        "Code/Game/BaseCtor.cpp": BASE_CTOR,
        "Code/Game/Inline.cpp": inline(new),
        "Code/Game/DerivedCtor.cpp": DERIVED_CTOR,
        "Code/Game/DerivedDtor.cpp": derived_dtor(new),
        "Code/Game/Other.cpp": OTHER,
    }
    for rel, text in files.items():
        path = root / rel
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(text.encode("utf-8"))
    _git(root, "init", "-q")
    _git(root, "add", "-A")
    return root


@pytest.fixture
def tree(tmp_path):
    return make_tree(tmp_path)


# Retail as LookupTablePostEffect's base shows it: the constructor stores the
# table once, the destructor stores it first, the deleting destructor (slot 1)
# stores it first; the derived constructor stores the base table and then its
# own, the derived destructor its own first and then the base table.
STORES = {
    TABLE: ([PURECALL, GDTOR, PURECALL, PURECALL, PURECALL],
            {0x00401002: 0, 0x00402000: 0, 0x00402018: 0, 0x00403005: 0, 0x00404020: 0}),
    DERIVED_TABLE: ([0x00404000, PURECALL], {0x00403010: 0, 0x00404002: 0}),
}


def retail(monkeypatch, tables=None):
    tables = STORES if tables is None else tables
    monkeypatch.setattr(rename, "retail_vtables", lambda ctx: tables)


def with_store(table, store, disp=0, base=None):
    """STORES (or `base`) plus one more install of `table`."""
    out = {t: (list(slots), dict(stores)) for t, (slots, stores) in (base or STORES).items()}
    out.setdefault(table, ([PURECALL], {}))[1][store] = disp
    return out


def ctx_of(root):
    return rename.Context(root, object_scan=False)


def plan(root, old=OLD, new=NEW, **overrides):
    return rename.plan_rename("class", ctx=ctx_of(root), name=old, new=new, fold=True, **overrides)


def snapshot(root):
    return {p.relative_to(root).as_posix(): p.read_bytes()
            for p in root.rglob("*") if p.is_file() and ".git" not in p.parts}


def write(root, rel, text):
    (root / rel).write_bytes(text.encode("utf-8"))      # LF, as the ledgers require


def append(root, rel, text):
    write(root, rel, (root / rel).read_bytes().decode("utf-8") + text)


# ------------------------------------------------------------ the fold

@pytest.mark.parametrize("new", [NEW, "WidgetBase"])
def test_fold_respells_the_placeholder_into_the_vftables_name(tmp_path, monkeypatch, new):
    """A placeholder folds into the name the vftable carries, placeholder or
    readable alike: no name is invented, so no name_basis.csv record."""
    root = make_tree(tmp_path, new)
    retail(monkeypatch)
    p = plan(root, new=new, evidence="seat note")
    assert p.kind == "class" and p.fold and p.basis == "fold"
    assert "retail vftable 0x00C00000" in p.evidence
    assert f"??0{OLD}@@QAE@XZ at 0x00401000 installs" in p.evidence
    assert f"??_7{new}@@6B@" in p.evidence
    assert p.evidence.endswith("; seat note")
    assert p.verify == ["Code/Game/BaseCtor.cpp", "Code/Game/DerivedCtor.cpp"]
    assert f"class:{OLD}" in rename.claim_keys(p) and f"class:{new}" in rename.claim_keys(p)
    assert p.subject() == f"Fold class {OLD} into {new} (retail vftable 0x00C00000)"
    seen = []
    rename.apply_rename(p, ctx=ctx_of(root), verify=lambda ctx, sources: seen.append(sources) or True)
    assert seen == [p.verify]

    fns = (root / "reverse/functions.csv").read_text()
    assert f"??0{new}@@QAE@XZ,,0x00401000,13,Code/Game/BaseCtor.cpp,matched," in fns
    assert f"calls ??0{new}@@QAE@XZ" in fns
    assert OLD not in fns
    pins = (root / "reverse/symbols.csv").read_text()
    # the pin under the constructor's name became the destructor row's own name: dropped
    assert OLD not in pins and f"??1{new}@@UAE@XZ" not in pins
    assert "??1Gen_uwm_00402000@@QAE@XZ,0x00402000,gen-uw-pin dtor target" in pins
    assert p.dropped_pins == [(f"??1{OLD}@@UAE@XZ", f"??1{new}@@UAE@XZ", "0x00402000")]
    deleted = (root / "reverse/deleted_rows.csv").read_text()
    assert deleted.startswith('name,target_rva,reason\n?gone@@YAXXZ,0x00100000,"old, retired"\n')
    assert (f'??0{OLD}@@QAE@XZ,0x00401000,"Renamed to ??0{new}@@QAE@XZ by tools/rename.py '
            '(fold: retail vftable 0x00C00000)"\n') in deleted
    assert not (root / "reverse/name_basis.csv").exists()

    base = (root / "Code/Game/BaseCtor.cpp").read_text()
    assert f"class {new}\n" in base and f"{new}::{new}()" in base and OLD not in base
    assert f"class Derived : public {new}" in (root / "Code/Game/DerivedCtor.cpp").read_text()
    assert (root / "Code/Game/Inline.cpp").read_text() == inline(new)       # NEW's own unit untouched


def test_fold_carries_records_scoped_by_the_old_name(tree, monkeypatch):
    retail(monkeypatch)
    write(tree, "reverse/name_basis.csv",
          "kind,old,new,basis,evidence,source,rva\n"
          f"member,{OLD}::m_04,{OLD}::m_dirty,inferred,agree:abc,Code/Game/BaseCtor.cpp,\n")
    p = plan(tree)
    rename.apply_rename(p, ctx=ctx_of(tree), verify=lambda ctx, sources: True)
    rows = list(csv.reader(io.StringIO((tree / "reverse/name_basis.csv").read_text())))
    assert rows[-1][:4] == ["carry", f"{OLD}::m_dirty", f"{NEW}::m_dirty", "inferred"]
    assert not any(r[0] == "class" for r in rows)          # the fold itself records nothing


def test_byte_change_restores_everything(tree, monkeypatch):
    retail(monkeypatch)
    before = snapshot(tree)
    p = plan(tree)
    with pytest.raises(VerifyFailed):
        rename.apply_rename(p, ctx=ctx_of(tree), verify=lambda ctx, sources: False)
    assert snapshot(tree) == before


# ------------------------------------------------------------ the evidence gate

def test_refused_without_vftable_evidence(tree, monkeypatch):
    retail(monkeypatch, {})
    before = snapshot(tree)
    with pytest.raises(Refusal, match="installs no vftable retail shows as its own"):
        plan(tree)
    assert snapshot(tree) == before


def test_refused_when_the_vftable_is_not_named_new(tree, monkeypatch):
    retail(monkeypatch)
    write(tree, "reverse/data_ledger.csv", ledger(NEW).replace(f"??_7{NEW}@@6B@", "??_7Rva00999999@@6B@"))
    with pytest.raises(Refusal, match=f"nothing ties {NEW} to it"):
        plan(tree)


def test_refused_when_old_installs_another_table(tree, monkeypatch):
    # the constructor's only store installs a table no ??_7 Rva00402000 names
    tables = {t: (list(s), dict(i)) for t, (s, i) in STORES.items()}
    del tables[TABLE][1][0x00401002]
    tables[OTHER_TABLE] = ([PURECALL], {0x00401002: 0})
    retail(monkeypatch, tables)
    with pytest.raises(Refusal, match="not that class|nothing ties"):
        plan(tree)


def test_refused_when_new_owns_a_different_table(tree, monkeypatch):
    # NEW's destructor stores another table first: NEW is another class
    tables = {t: (list(s), dict(i)) for t, (s, i) in STORES.items()}
    del tables[TABLE][1][0x00402000]
    tables[OTHER_TABLE] = ([PURECALL], {0x00402000: 0})
    retail(monkeypatch, tables)
    with pytest.raises(Refusal, match=f"{NEW} is not that class"):
        plan(tree)


def test_refused_on_an_icf_folded_vftable(tree, monkeypatch):
    # Other's constructor installs the same table as its only one: retail
    # folded two classes' identical vftables (W3DProjectedShadow's 0x007CEFA0)
    retail(monkeypatch, with_store(TABLE, 0x00405004))
    with pytest.raises(Refusal, match="also the own vftable of Other"):
        plan(tree)


def test_a_derived_class_storing_the_base_table_is_no_fold(tree, monkeypatch):
    # Derived's ctor stores TABLE before its own and its dtor after its own:
    # base construction and destruction, not a second owner (STORES has both)
    retail(monkeypatch)
    plan(tree)


def test_refused_when_both_names_have_a_destructor(tree, monkeypatch):
    append(tree, "reverse/functions.csv", f"??1{OLD}@@UAE@XZ,,0x00406000,7,Code/Game/BaseCtor.cpp,matched,dtor\n")
    retail(monkeypatch, with_store(TABLE, 0x00406000))
    with pytest.raises(Refusal, match="one class has one"):
        plan(tree)


def test_refused_when_a_slot_holds_another_classs_deleting_destructor(tree, monkeypatch):
    append(tree, "reverse/functions.csv", "??_GOther@@UAEPAXI@Z,,0x00405100,28,Code/Game/Other.cpp,matched,del\n")
    tables = {t: (list(s), dict(i)) for t, (s, i) in STORES.items()}
    tables[TABLE][0][2] = 0x00405100
    retail(monkeypatch, tables)
    with pytest.raises(Refusal, match="slot 2 holds Other's deleting destructor"):
        plan(tree)


def test_refused_when_news_deleting_destructor_is_off_the_table(tree, monkeypatch):
    tables = {t: (list(s), dict(i)) for t, (s, i) in STORES.items()}
    tables[TABLE][0][1] = PURECALL
    retail(monkeypatch, tables)
    with pytest.raises(Refusal, match="on no slot of retail vftable 0x00C00000"):
        plan(tree)


# ------------------------------------------------------------ the naming rules

def test_refused_readable_into_placeholder(tmp_path, monkeypatch):
    """docs/naming.md: only a `restored` revert puts a placeholder back over a
    readable name; a fold never does, whatever retail proves."""
    root = make_tree(tmp_path)
    for rel in ("reverse/functions.csv", "reverse/symbols.csv", "Code/Game/BaseCtor.cpp",
                "Code/Game/DerivedCtor.cpp"):
        write(root, rel, (root / rel).read_bytes().decode("utf-8").replace(OLD, "WidgetBase"))
    retail(monkeypatch)
    before = snapshot(root)
    with pytest.raises(Refusal, match="WidgetBase is a readable name"):
        plan(root, old="WidgetBase")
    assert snapshot(root) == before


def test_refused_for_a_registered_class(tree, monkeypatch):
    retail(monkeypatch)
    write(tree, "reverse/canonical_classes.csv", f"class,header,notes\n{OLD},Code/Game/Base.h,\n")
    with pytest.raises(Refusal, match="canonical_classes"):
        plan(tree)
    write(tree, "reverse/canonical_classes.csv", f"class,header,notes\n{NEW},Code/Game/Base.h,\n")
    with pytest.raises(Refusal, match="private copy"):
        plan(tree)


def test_refused_when_one_file_would_declare_new_twice(tree, monkeypatch):
    retail(monkeypatch)
    append(tree, "Code/Game/BaseCtor.cpp", f"class {NEW} {{ public: virtual ~{NEW}(); }};\n")
    with pytest.raises(Refusal, match="would declare class Rva00402000 twice"):
        plan(tree)


# ------------------------------------------------------------ pins

def test_refused_when_a_renamed_pin_would_name_another_address(tree, monkeypatch):
    retail(monkeypatch)
    append(tree, "reverse/symbols.csv", f"??0{OLD}@@QAE@XZ,0x00409990,stray ctor pin\n")
    with pytest.raises(Refusal, match="two addresses"):
        plan(tree)


def test_refused_when_a_renamed_row_takes_an_existing_name(tree, monkeypatch):
    retail(monkeypatch)
    append(tree, "reverse/symbols.csv", f"??0{NEW}@@QAE@XZ,0x00409990,existing\n")
    with pytest.raises(Refusal, match="two addresses"):
        plan(tree)


def test_a_pin_already_naming_the_row_is_dropped_not_duplicated(tree, monkeypatch):
    retail(monkeypatch)
    append(tree, "reverse/symbols.csv", f"??0{NEW}@@QAE@XZ,0x00401000,future name pinned early\n")
    p = plan(tree)
    assert (f"??0{NEW}@@QAE@XZ", f"??0{NEW}@@QAE@XZ", "0x00401000") in p.dropped_pins
    rename.apply_rename(p, ctx=ctx_of(tree), verify=lambda ctx, sources: True)
    pins = (tree / "reverse/symbols.csv").read_text()
    assert f"??0{NEW}@@QAE@XZ" not in pins


# ------------------------------------------------------------ CLI

def test_cli_dry_run(tree, monkeypatch, capsys):
    retail(monkeypatch)
    before = snapshot(tree)
    assert rename.main(["class", "--fold", OLD, "--into", NEW, "--root", str(tree), "--no-claim",
                        "--no-object-scan", "--dry-run"]) == 0
    out = capsys.readouterr().out
    assert f"rename: class {OLD} -> {NEW} (fold)" in out
    assert "symbols.csv pins dropped (now the row's own name) (1)" in out
    assert snapshot(tree) == before


@pytest.mark.parametrize("argv", [
    ["class", "--fold", OLD],                                         # no --into
    ["class", "--fold", OLD, "--into", NEW, "--basis", "inferred"],  # a fold takes no basis
    ["class", "--fold", OLD, "--into", NEW, "--new", NEW],
    ["class", "--name", OLD, "--into", NEW],
])
def test_cli_refuses_mixed_arguments(tree, argv):
    with pytest.raises(SystemExit):
        rename.main(argv + ["--root", str(tree), "--no-claim", "--dry-run"])
