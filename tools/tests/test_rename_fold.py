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


def test_refused_when_one_file_would_declare_new_twice_behind_a_declspec(tree, monkeypatch):
    # BuddyThread.cpp defines BuddyThreadClass beside its placeholder view
    # `class __declspec(novtable) Rva0055133F`; the class-head pattern missed it.
    retail(monkeypatch)
    append(tree, "Code/Game/BaseCtor.cpp", f"class __declspec(novtable) {NEW} {{ public: virtual ~{NEW}(); }};\n")
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


# ------------------------------------------------------------ several bases

# GlobalWeatherSystem (BFME 2, 0x00318588..0x003186A5) has two bases: its
# destructor stores its own table at +0 and its own Snapshot-subobject table at
# +0xC first, then restores the Snapshot base's table at +0xC; its deleting
# destructor sits in slot 0 of the +0 table and the `this -= 0xC` adjustor
# thunk ??_E...@@WM@AEPAXI@Z in slot 0 of the +0xC table; the constructor
# stores the inlined base's +0xC table before its own. One seat rowed the
# constructor under the real name, another the destructors under Rva00318637.
MI_OLD = "Rva00502000"
MI_NEW = "WeatherHub"
MI_TABLE, MI_SECOND, MI_BASE2 = 0x00800400, 0x00800300, 0x00800500
MI_CTOR, MI_DTOR, MI_GDTOR, MI_THUNK = 0x00501000, 0x00502000, 0x00502040, 0x00502060
MI_STORES = {
    MI_TABLE: ([MI_GDTOR, PURECALL], {0x00501008: 0, 0x00502003: 0}),
    MI_SECOND: ([MI_THUNK, PURECALL], {0x0050100F: 0xC, 0x0050200A: 0xC}),
    MI_BASE2: ([PURECALL], {0x00501002: 0xC, 0x00502020: 0xC, 0x00506002: 0}),
}

MI_FUNCTIONS = f"""name,export_rva,target_rva,target_size,source,status,notes
??0{MI_NEW}@@QAE@XZ,,0x00501000,40,Code/Game/MiCtor.cpp,matched,ctor stores both own tables
??1{MI_OLD}@@UAE@XZ,,0x00502000,40,Code/Game/MiDtor.cpp,matched,MI dtor
??_G{MI_OLD}@@UAEPAXI@Z,,0x00502040,28,Code/Game/MiDtor.cpp,matched,deleting dtor
??_E{MI_OLD}@@WM@AEPAXI@Z,,0x00502060,8,Code/Game/MiDtor.cpp,matched,this-adjusting (-0xC) thunk
??0Second@@QAE@XZ,,0x00506000,20,Code/Game/Second.cpp,matched,the second base's ctor
??0Other@@QAE@XZ,,0x00507000,20,Code/Game/Other.cpp,matched,unrelated ctor
"""

MI_CTOR_SRC = f"""class First {{ public: virtual ~First(); }};
class Second {{ public: Second(); virtual void save() = 0; }};
class {MI_NEW} : public First, public Second
{{
public:
\t{MI_NEW}();
\tvirtual void save();
}};
{MI_NEW}::{MI_NEW}() {{}}
"""

MI_DTOR_SRC = f"""class First {{ public: virtual ~First(); }};
class Second {{ public: virtual void save() = 0; }};
class {MI_OLD} : public First, public Second
{{
public:
\tvirtual ~{MI_OLD}();
}};
{MI_OLD}::~{MI_OLD}() {{}}
"""


def mi_ledger(primary=f"??_7{MI_NEW}@@6BFirst@@@"):
    return ("address,size,section,kind,name,source,status,names,defs,refs\n"
            f"0x00800300,8,.rdata,vtable,??_7{MI_NEW}@@6BSecond@@@,,literal,,0,2\n"
            f"0x00800400,8,.rdata,vtable,{primary},,literal,,0,2\n")


def make_mi_tree(root, ledger_text=None):
    files = {
        "reverse/functions.csv": MI_FUNCTIONS,
        "reverse/symbols.csv": "name,address,notes\n",
        "reverse/deleted_rows.csv": "name,target_rva,reason\n",
        "reverse/data_rows.csv": "name,address,address_kind,size,section,source,status,evidence,model\n",
        "reverse/data_ledger.csv": mi_ledger() if ledger_text is None else ledger_text,
        "reverse/exports.csv": "ordinal,rva,target_rva,section,kind,name\n",
        "reverse/gate_baseline.txt": "",
        "Code/Game/MiCtor.cpp": MI_CTOR_SRC,
        "Code/Game/MiDtor.cpp": MI_DTOR_SRC,
        "Code/Game/Second.cpp": "class Second { public: Second(); };\nSecond::Second() {}\n",
        "Code/Game/Other.cpp": OTHER,
    }
    for rel, text in files.items():
        path = root / rel
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(text.encode("utf-8"))
    _git(root, "init", "-q")
    _git(root, "add", "-A")
    return root


def mi_tables():
    return {t: (list(slots), dict(stores)) for t, (slots, stores) in MI_STORES.items()}


def mi_plan(root):
    return rename.plan_rename("class", ctx=ctx_of(root), name=MI_OLD, new=MI_NEW, fold=True)


@pytest.mark.parametrize("name,disp", [
    (f"??_E{MI_OLD}@@WM@AEPAXI@Z", 12), (f"??_G{MI_OLD}@@W3AEPAXI@Z", 4),
    (f"??_E{MI_OLD}@@WBA@AEPAXI@Z", 16), (f"??_E{MI_OLD}@@OM@AEPAXI@Z", 12),
    (f"??_E{MI_OLD}@@UAEPAXI@Z", None), (f"??1{MI_OLD}@@UAE@XZ", None),
])
def test_adjustor_of_decodes_the_thunk_displacement(name, disp):
    assert rename.adjustor_of(name) == disp


def test_fold_accepts_an_adjustor_thunk_on_the_classs_second_table(tmp_path, monkeypatch):
    """The false reject of 2026-11-01 (re_attempts: ??1Rva00318637@@UAE@XZ): the
    deleting destructor's adjustor thunk sits on the class's own +0xC table,
    which the rows owning the +0 table install at +0xC themselves."""
    root = make_mi_tree(tmp_path)
    retail(monkeypatch, MI_STORES)
    p = mi_plan(root)
    assert p.fold == MI_TABLE
    assert f"??_G{MI_OLD}@@UAEPAXI@Z at 0x00502040 is slot 0;" in p.evidence + ";"
    assert (f"??_E{MI_OLD}@@WM@AEPAXI@Z at 0x00502060 is slot 0 of secondary vftable 0x00C00300 "
            f"(installed at +0xC by ??1{MI_OLD}@@UAE@XZ at 0x00502000)") in p.evidence
    rename.apply_rename(p, ctx=ctx_of(root), verify=lambda ctx, sources: True)
    fns = (root / "reverse/functions.csv").read_text()
    assert f"??_E{MI_NEW}@@WM@AEPAXI@Z,,0x00502060,8" in fns and MI_OLD not in fns


def test_refused_when_the_thunks_table_is_not_installed_at_its_displacement(tmp_path, monkeypatch):
    # the rows owning the +0 table install their second table at +0x10: the
    # thunk's -0xC names a subobject they do not have
    root = make_mi_tree(tmp_path)
    tables = mi_tables()
    tables[MI_SECOND] = ([MI_THUNK, PURECALL], {0x0050100F: 0x10, 0x0050200A: 0x10})
    tables[MI_BASE2] = ([PURECALL], {0x00501002: 0x10, 0x00502020: 0x10, 0x00506002: 0})
    retail(monkeypatch, tables)
    with pytest.raises(Refusal, match=r"adjusts this by 0xC, but no row owning 0x00C00400 installs a table at \+0xC"):
        mi_plan(root)


def test_refused_when_the_thunk_is_off_the_second_table(tmp_path, monkeypatch):
    root = make_mi_tree(tmp_path)
    tables = mi_tables()
    tables[MI_SECOND] = ([PURECALL, PURECALL], dict(MI_STORES[MI_SECOND][1]))
    retail(monkeypatch, tables)
    with pytest.raises(Refusal, match=r"WM@AEPAXI@Z at 0x00502060 is on no slot of secondary vftable 0x00C00300"):
        mi_plan(root)


def test_refused_when_the_thunk_sits_on_the_base_table_restored_there(tmp_path, monkeypatch):
    # the thunk in a slot of the second base's own table (which the destructor
    # restores at +0xC last and the constructor stores there first) proves
    # nothing about this class
    root = make_mi_tree(tmp_path)
    tables = mi_tables()
    tables[MI_SECOND] = ([PURECALL, PURECALL], dict(MI_STORES[MI_SECOND][1]))
    tables[MI_BASE2] = ([MI_THUNK], dict(MI_STORES[MI_BASE2][1]))
    retail(monkeypatch, tables)
    with pytest.raises(Refusal, match="on no slot of secondary vftable 0x00C00300"):
        mi_plan(root)


def test_refused_when_the_rows_disagree_on_the_second_table(tmp_path, monkeypatch):
    root = make_mi_tree(tmp_path)
    tables = mi_tables()
    tables[MI_SECOND] = (list(MI_STORES[MI_SECOND][0]), {0x0050200A: 0xC})
    tables[OTHER_TABLE] = ([PURECALL], {0x0050100F: 0xC})
    retail(monkeypatch, tables)
    with pytest.raises(Refusal, match=r"install different tables at \+0xC"):
        mi_plan(root)


def test_refused_when_a_third_class_owns_the_second_table(tmp_path, monkeypatch):
    # Other's constructor installs the +0xC table as its own primary table:
    # retail folded identical tables of distinct classes
    root = make_mi_tree(tmp_path)
    tables = mi_tables()
    tables[MI_SECOND][1][0x00507004] = 0
    retail(monkeypatch, tables)
    with pytest.raises(Refusal, match=r"secondary vftable 0x00C00300 .* is also the own vftable of Other"):
        mi_plan(root)


def test_refused_when_the_second_table_holds_a_third_classs_deleting_destructor(tmp_path, monkeypatch):
    root = make_mi_tree(tmp_path)
    append(root, "reverse/functions.csv", "??_GOther@@UAEPAXI@Z,,0x00507100,28,Code/Game/Other.cpp,matched,del\n")
    tables = mi_tables()
    tables[MI_SECOND][0][1] = 0x00507100
    retail(monkeypatch, tables)
    with pytest.raises(Refusal, match=r"secondary vftable 0x00C00300 .* slot 1 holds Other's deleting destructor"):
        mi_plan(root)


def test_a_thunk_and_a_primary_deleting_destructor_are_different_kinds(tmp_path, monkeypatch):
    # NEW's own scalar deleting destructor and OLD's thunk are two functions;
    # two primary deleting destructors stay refused
    root = make_mi_tree(tmp_path)
    write(root, "reverse/functions.csv", MI_FUNCTIONS.replace(f"??_G{MI_OLD}@@UAEPAXI@Z", f"??_G{MI_NEW}@@UAEPAXI@Z"))
    retail(monkeypatch, MI_STORES)
    mi_plan(root)
    append(root, "reverse/functions.csv", f"??_G{MI_OLD}@@UAEPAXI@Z,,0x00502080,28,Code/Game/MiDtor.cpp,matched,dup\n")
    tables = mi_tables()
    tables[MI_TABLE][0][1] = 0x00502080
    retail(monkeypatch, tables)
    with pytest.raises(Refusal, match="both names have a deleting destructor row"):
        mi_plan(root)


def test_a_stale_ledger_is_read_through_the_installing_rows_objects(tmp_path, monkeypatch):
    """data_ledger.csv is a tool-written cache: a row landed after its last
    regeneration binds its table only in its object. The installing rows'
    DIR32 bindings (live_vtable_names) supply the name; nothing else does."""
    root = make_mi_tree(tmp_path, ledger_text=mi_ledger(primary=f"??_7{MI_OLD}@@6BFirst@@@"))
    retail(monkeypatch, MI_STORES)
    with pytest.raises(Refusal, match=f"nothing ties {MI_NEW} to it"):
        mi_plan(root)
    seen = []

    def live(ctx, rows, table):
        seen.append(sorted(r["name"] for r in rows))
        return {f"??_7{MI_NEW}@@6BFirst@@@": "the DIR32 bindings of Code/Game/MiCtor.cpp"} if table == MI_TABLE else {}

    monkeypatch.setattr(rename, "live_vtable_names", live)
    p = mi_plan(root)
    assert f"??_7{MI_NEW}@@6BFirst@@@ (the DIR32 bindings of Code/Game/MiCtor.cpp)" in p.evidence
    assert seen[-1] == [f"??0{MI_NEW}@@QAE@XZ", f"??1{MI_OLD}@@UAE@XZ"]
    # a third class's name among the live bindings is still a third name
    monkeypatch.setattr(rename, "live_vtable_names",
                        lambda ctx, rows, table: {f"??_7{MI_NEW}@@6BFirst@@@": "objects", "??_7Other@@6B@": "objects"}
                        if table == MI_TABLE else {})
    with pytest.raises(Refusal, match="also named for Other"):
        mi_plan(root)


def test_live_vtable_names_needs_an_object_scan(tree):
    ctx = ctx_of(tree)
    assert rename.live_vtable_names(ctx, ctx.rows(), TABLE) == {}


# ------------------------------------------------------------ a nested NEW

# RegionDetailsStructuresPage's icon (BFME 2, LINK-181): its constructor
# 0x005E28FE is rowed under the nested StrategicInGameUI::...::Impl::Icon, its
# destructor 0x005E278E and deleting destructor under the placeholder
# Rva005E278E. The destructor's first +0 store is the icon's vftable, which
# the data ledger names ??_7Icon@Impl@Page@UI@@6B@. A token rewrite cannot
# declare the enclosing scopes, so the units come as prepared C++.
N_OLD = "Rva00602000"
N_NEW = "UI::Page::Impl::Icon"
N_SCOPE = "Icon@Impl@Page@UI"
N_TABLE = 0x00800600
N_CTOR, N_DTOR, N_GDTOR = 0x00601000, 0x00602000, 0x00602040
N_STORES = {
    N_TABLE: ([N_GDTOR, PURECALL], {0x00601010: 0, 0x00602003: 0}),
    OTHER_TABLE: ([PURECALL], {0x00601002: 0, 0x00602030: 0}),    # the base's, stored first / restored last
}

N_FUNCTIONS = f"""name,export_rva,target_rva,target_size,source,status,notes
??0{N_SCOPE}@@QAE@AAV123@H@Z,,0x00601000,40,Code/Game/IconCtor.cpp,matched,icon ctor
??1{N_OLD}@@UAE@XZ,,0x00602000,40,Code/Game/IconDtor.cpp,matched,dtor
??_G{N_OLD}@@UAEPAXI@Z,,0x00602040,28,Code/Game/IconDtor.cpp,matched,deleting dtor
__ehhandler$??1{N_OLD}@@UAE@XZ,,0x00700000,10,Code/Game/IconDtor.cpp,matched,eh handler
$L10,,0x00700010,8,Code/Game/IconDtor.cpp,matched,gen-funclet;parent=??1{N_OLD}@@UAE@XZ
??0Other@@QAE@XZ,,0x00605000,20,Code/Game/Other.cpp,matched,unrelated ctor
"""

N_LEDGER = ("address,size,section,kind,name,source,status,names,defs,refs\n"
            f"0x00800600,8,.rdata,vtable,??_7{N_SCOPE}@@6B@,,literal,,0,2\n")

N_DTOR_SRC = f"""// ??1{N_OLD}@@UAE@XZ @ 0x00602000
class Base {{ public: virtual ~Base(); }};
class {N_OLD} : public Base
{{
public:
\tvirtual ~{N_OLD}();
}};
{N_OLD}::~{N_OLD}() {{}}
"""

N_DTOR_PREPARED = """// ??1Icon@Impl@Page@UI@@UAE@XZ @ 0x00602000
class Base { public: virtual ~Base(); };
namespace UI { class Page { public: class Impl; }; }
class UI::Page::Impl { public: class Icon; };
class UI::Page::Impl::Icon : public Base
{
public:
\tvirtual ~Icon();
};
UI::Page::Impl::Icon::~Icon() {}
"""

N_CTOR_SRC = """namespace UI { class Page { public: class Impl; }; }
class UI::Page::Impl { public: class Icon; };
class UI::Page::Impl::Icon { public: Icon(Impl &, int); virtual ~Icon(); };
UI::Page::Impl::Icon::Icon(Impl &, int) {}
"""


def make_nested_tree(root, functions=N_FUNCTIONS, ledger_text=N_LEDGER):
    files = {
        "reverse/functions.csv": functions,
        "reverse/symbols.csv": "name,address,notes\n",
        "reverse/deleted_rows.csv": "name,target_rva,reason\n",
        "reverse/data_rows.csv": "name,address,address_kind,size,section,source,status,evidence,model\n",
        "reverse/data_ledger.csv": ledger_text,
        "reverse/exports.csv": "ordinal,rva,target_rva,section,kind,name\n",
        "reverse/gate_baseline.txt": "",
        "Code/Game/IconCtor.cpp": N_CTOR_SRC,
        "Code/Game/IconDtor.cpp": N_DTOR_SRC,
        "Code/Game/Other.cpp": OTHER,
    }
    for rel, text in files.items():
        path = root / rel
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(text.encode("utf-8"))
    _git(root, "init", "-q")
    _git(root, "add", "-A")
    return root


def n_tables():
    return {t: (list(slots), dict(stores)) for t, (slots, stores) in N_STORES.items()}


def n_plan(root, prepared="default", new=N_NEW, old=N_OLD):
    if prepared == "default":
        prepared = {"Code/Game/IconDtor.cpp": N_DTOR_PREPARED.encode("utf-8")}
    return rename.plan_rename("class", ctx=ctx_of(root), name=old, new=new, fold=True, prepared=prepared)


@pytest.mark.parametrize("name,expected", [
    (f"??1{N_SCOPE}@@UAE@XZ", ("1", N_NEW)),
    (f"??0{N_SCOPE}@@QAE@AAV123@H@Z", ("0", N_NEW)),
    (f"??_G{N_SCOPE}@@UAEPAXI@Z", ("_G", N_NEW)),
    (f"??1{N_OLD}@@UAE@XZ", ("1", N_OLD)),
    ("??1?$vector@H@_STL@@QAE@XZ", None),
    (f"?m@{N_OLD}@@QAEXXZ", None),
])
def test_special_member_reads_a_nested_class(name, expected):
    assert rename.special_member(name) == expected


def test_nested_scope_spellings_round_trip():
    assert rename.class_scope(N_NEW) == N_SCOPE
    assert rename.scope_class(N_SCOPE + "@") == N_NEW
    assert rename.GLOBAL_VTABLE.match(f"??_7{N_SCOPE}@@6BBase@@@").group(1) == N_SCOPE + "@"
    assert rename.adjustor_of(f"??_E{N_SCOPE}@@W3AEPAXI@Z") == 4


def test_fold_into_a_nested_class(tmp_path, monkeypatch):
    """The nested NEW is spelled as its decorated scope in every mangled name
    (rows, the EH handler, a funclet's parent= token) and the units are the
    prepared C++, which the build then verifies."""
    root = make_nested_tree(tmp_path)
    retail(monkeypatch, n_tables())
    p = n_plan(root)
    assert p.fold == N_TABLE
    assert f"??_7{N_SCOPE}@@6B@ (data_ledger.csv)" in p.evidence
    assert p.verify == ["Code/Game/IconDtor.cpp"]
    assert f"class:{N_NEW}" in rename.claim_keys(p) and "file:Code/Game/IconDtor.cpp" in rename.claim_keys(p)
    rename.apply_rename(p, ctx=ctx_of(root), verify=lambda ctx, sources: True)
    fns = (root / "reverse/functions.csv").read_text()
    assert f"??1{N_SCOPE}@@UAE@XZ,,0x00602000,40" in fns
    assert f"??_G{N_SCOPE}@@UAEPAXI@Z,,0x00602040,28" in fns
    assert f"__ehhandler$??1{N_SCOPE}@@UAE@XZ,,0x00700000" in fns
    assert f"parent=??1{N_SCOPE}@@UAE@XZ" in fns
    assert N_OLD not in fns
    assert (root / "Code/Game/IconDtor.cpp").read_text() == N_DTOR_PREPARED
    assert (root / "Code/Game/IconCtor.cpp").read_text() == N_CTOR_SRC
    deleted = (root / "reverse/deleted_rows.csv").read_text()
    assert f'??1{N_OLD}@@UAE@XZ,0x00602000,"Renamed to ??1{N_SCOPE}@@UAE@XZ by tools/rename.py' in deleted


def test_nested_fold_refused_without_prepared_units(tmp_path, monkeypatch):
    root = make_nested_tree(tmp_path)
    retail(monkeypatch, n_tables())
    before = snapshot(root)
    with pytest.raises(Refusal, match=r"IconDtor.cpp spells Rva00602000: .* --prepared"):
        n_plan(root, prepared=None)
    assert snapshot(root) == before


def test_nested_fold_refused_when_a_prepared_unit_still_spells_old(tmp_path, monkeypatch):
    root = make_nested_tree(tmp_path)
    retail(monkeypatch, n_tables())
    with pytest.raises(Refusal, match="prepared Code/Game/IconDtor.cpp still spells Rva00602000"):
        n_plan(root, prepared={"Code/Game/IconDtor.cpp": N_DTOR_SRC.encode("utf-8")})


def test_prepared_needs_a_nested_new(tree, monkeypatch):
    retail(monkeypatch)
    with pytest.raises(Refusal, match="--prepared goes with a nested --into"):
        plan(tree, prepared={"Code/Game/BaseCtor.cpp": BASE_CTOR.encode("utf-8")})


@pytest.mark.parametrize("new,why", [
    ("UI::Page::Impl::", "not a type identifier"),
    ("UI::class::Icon", "not a type identifier"),
    (f"UI::{N_OLD}::Icon", "own scope names"),
])
def test_nested_new_spelling_is_checked(tmp_path, monkeypatch, new, why):
    root = make_nested_tree(tmp_path)
    retail(monkeypatch, n_tables())
    with pytest.raises(Refusal, match=why):
        n_plan(root, new=new)


def test_nested_fold_refuses_a_name_back_reference(tmp_path, monkeypatch):
    # equals(const OLD &) spells its own class as the name back-reference 1:
    # under the nested scope 1 would name Icon alone, and cl emits V1234@
    root = make_nested_tree(tmp_path, functions=N_FUNCTIONS +
                            f"?equals@{N_OLD}@@QBE_NABV1@@Z,,0x00602100,20,Code/Game/IconDtor.cpp,matched,method\n")
    retail(monkeypatch, n_tables())
    with pytest.raises(Refusal, match=r"carries a name back-reference \(1\)"):
        n_plan(root)


def test_nested_fold_refuses_a_respelling_cl_would_compress(tmp_path, monkeypatch):
    # a method named Impl: ?Impl@Icon@Impl@Page@UI@@ spells Impl twice, which
    # cl would encode as a back-reference
    root = make_nested_tree(tmp_path, functions=N_FUNCTIONS +
                            f"?Impl@{N_OLD}@@QAEXXZ,,0x00602200,20,Code/Game/IconDtor.cpp,matched,method\n")
    retail(monkeypatch, n_tables())
    with pytest.raises(Refusal, match="spells Impl twice"):
        n_plan(root)


def test_nested_fold_refused_when_the_vftable_is_not_named_new(tmp_path, monkeypatch):
    root = make_nested_tree(tmp_path, ledger_text=N_LEDGER.replace(N_SCOPE, "Icon@Impl@Other@UI"))
    retail(monkeypatch, n_tables())
    with pytest.raises(Refusal, match=rf"not \?\?_7{N_SCOPE}@@6B@: nothing ties {N_NEW} to it"):
        n_plan(root)


def test_a_nested_third_class_owning_the_table_is_an_icf_fold(tmp_path, monkeypatch):
    # a nested class's constructor installing the table as its only one is a
    # third owner, as a global class's is (SPECIAL_MEMBER reads nested scopes)
    root = make_nested_tree(tmp_path, functions=N_FUNCTIONS +
                            "??0Thing@Outer@@QAE@XZ,,0x00606000,20,Code/Game/Other.cpp,matched,nested ctor\n")
    tables = n_tables()
    tables[N_TABLE][1][0x00606004] = 0
    retail(monkeypatch, tables)
    with pytest.raises(Refusal, match="also the own vftable of Outer::Thing"):
        n_plan(root)


def test_cli_nested_dry_run_reads_prepared_files(tmp_path, monkeypatch, capsys):
    root = make_nested_tree(tmp_path / "tree")
    retail(monkeypatch, n_tables())
    prepared = tmp_path / "IconDtor.cpp"
    prepared.write_bytes(N_DTOR_PREPARED.encode("utf-8"))
    before = snapshot(root)
    assert rename.main(["class", "--fold", N_OLD, "--into", N_NEW, "--prepared",
                        f"Code/Game/IconDtor.cpp={prepared}", "--root", str(root), "--no-claim",
                        "--no-object-scan", "--dry-run"]) == 0
    out = capsys.readouterr().out
    assert f"rename: class {N_OLD} -> {N_NEW} (fold)" in out
    assert f"??1{N_SCOPE}@@UAE@XZ" in out
    assert snapshot(root) == before
    with pytest.raises(SystemExit):
        rename.main(["class", "--name", N_OLD, "--new", "Icon", "--basis", "inferred", "--evidence", "x",
                     "--prepared", f"Code/Game/IconDtor.cpp={prepared}", "--root", str(root), "--no-claim",
                     "--dry-run"])


# ------------------------------------------------------------ stores through this + d

# retail_vtables reads each install's displacement from its own instruction.
# PlanRetreatsPhaseBehavior::Impl's destructor (0x005770F7) holds its +4
# subobject in edi: `lea edi,[esi+4]` ... `mov [esi],0xC6E8F8; mov
# [edi],0xC6E8EC`, which read as two +0 stores. this_stores follows the
# registers holding this + d from the thiscall entry.
THIS_BODY = bytes.fromhex(
    "B800000000"        # 1000 mov eax,<FuncInfo>
    "E8F60F0000"        # 1005 call 0x2000 (__EH_prolog: clobbers eax only)
    "56"                # 100A push esi
    "8BF1"              # 100B mov esi,ecx              esi = this
    "8D7E04"            # 100D lea edi,[esi+4]          edi = this+4
    "C706F8E8C600"      # 1010 mov [esi],T              +0
    "C707ECE8C600"      # 1016 mov [edi],S              +4
    "E8DF1F0000"        # 101C call 0x3000              clobbers eax, ecx, edx
    "C70674BABD00"      # 1021 mov [esi],B              +0
    "8B4508"            # 1027 mov eax,[ebp+8]
    "C70011111100"      # 102A mov [eax],X              another object: absent
    "C70122222200"      # 1030 mov [ecx],X              ecx clobbered: absent
    "85C0"              # 1036 test eax,eax
    "7403"              # 1038 je 0x103D
    "8D7E08"            # 103A lea edi,[esi+8]          on one way in only
    "C70733333300"      # 103D mov [edi],X              the ways disagree: absent
    "C7460C44444400"    # 1043 mov [esi+0xC],X          +0xC
    "C3")               # 104A ret


def test_this_stores_follows_this_through_registers():
    assert rename.this_stores(THIS_BODY, 0x1000, {0x2000}) == {0x1010: 0, 0x1016: 4, 0x1021: 0, 0x1043: 12}


def test_this_stores_trusts_no_register_after_an_unknown_call():
    # without the EH helper's address, the first call clobbers ecx before
    # `mov esi,ecx`: nothing is proven
    assert rename.this_stores(THIS_BODY, 0x1000, ()) == {}


def test_this_displacements_reads_no_image_for_a_scratch_root(tree):
    ctx = ctx_of(tree)
    assert rename.this_displacements(ctx, ctx.rows()[0]) == {}


def proven(monkeypatch, mapping):
    """this_displacements as the retail bodies would give it: {store: d}."""
    monkeypatch.setattr(rename, "this_displacements",
                        lambda ctx, row: {s: d for s, d in mapping.items()
                                          if rename._rva(row["target_rva"]) <= s <
                                          rename._rva(row["target_rva"]) + int(row["target_size"])})


def mi_aliased_tables():
    """MI_STORES with every +0xC store read as +0, as retail_vtables reads a
    store through a register holding this + 0xC."""
    tables = mi_tables()
    for table in (MI_SECOND, MI_BASE2):
        for store in list(tables[table][1]):
            if tables[table][1][store] == 0xC:
                tables[table][1][store] = 0
    return tables


MI_PROVEN = {0x00501002: 0xC, 0x00501008: 0, 0x0050100F: 0xC,
             0x00502003: 0, 0x0050200A: 0xC, 0x00502020: 0xC}


def test_a_secondary_table_stored_through_a_register_ties_the_thunk(tmp_path, monkeypatch):
    """The false reject of 2026-11-04 (LINK-181, ??_ERva005770F7@@W3AEPAXI@Z):
    the rows owning the class's table install its +4 table through `edi`, so
    the instruction reads +0 and no row seemed to install anything at +4."""
    root = make_mi_tree(tmp_path)
    retail(monkeypatch, mi_aliased_tables())
    with pytest.raises(Refusal, match=r"adjusts this by 0xC, but no row owning 0x00C00400 installs a table at \+0xC"):
        mi_plan(root)
    proven(monkeypatch, MI_PROVEN)
    p = mi_plan(root)
    assert (f"??_E{MI_OLD}@@WM@AEPAXI@Z at 0x00502060 is slot 0 of secondary vftable 0x00C00300 "
            f"(installed at +0xC by ??1{MI_OLD}@@UAE@XZ at 0x00502000)") in p.evidence


def test_still_refused_when_the_proven_secondary_store_is_elsewhere(tmp_path, monkeypatch):
    # the register holds this + 0x10, not this + 0xC: the thunk's subobject
    # is still not one the owning rows have
    root = make_mi_tree(tmp_path)
    retail(monkeypatch, mi_aliased_tables())
    proven(monkeypatch, {s: (0x10 if d else 0) for s, d in MI_PROVEN.items()})
    with pytest.raises(Refusal, match=r"adjusts this by 0xC, but no row owning 0x00C00400 installs a table at \+0xC"):
        mi_plan(root)


# A constructor-only placeholder (PlanRetreatsPhaseBehavior::Impl's
# 0x005776A7): an inlined base constructor stores the base's table first, then
# the class stores its own. Each store's base register provably holds this,
# so the last +0 store is the class's own table.
BASE_FIRST = 0x00401001


def base_first_tables():
    tables = {t: (list(s), dict(i)) for t, (s, i) in STORES.items()}
    tables[OTHER_TABLE] = ([PURECALL], {BASE_FIRST: 0})
    return tables


def test_a_constructor_storing_a_base_table_first_owns_its_last_table(tree, monkeypatch):
    retail(monkeypatch, base_first_tables())
    with pytest.raises(Refusal, match="installs no vftable retail shows as its own"):
        plan(tree)
    proven(monkeypatch, {BASE_FIRST: 0, 0x00401002: 0, 0x00402000: 0, 0x00402018: 0})
    p = plan(tree)
    assert (f"??0{OLD}@@QAE@XZ at 0x00401000 installs retail vftable 0x00C00000 as its own (its last +0 store; "
            "every vftable store in it is through this)") in p.evidence


def test_a_constructor_with_an_unproven_store_owns_nothing(tree, monkeypatch):
    # one store's base register is not this + d (a new'ed object's [eax]):
    # the constructor stays ambiguous
    retail(monkeypatch, base_first_tables())
    proven(monkeypatch, {0x00401002: 0, 0x00402000: 0, 0x00402018: 0})
    with pytest.raises(Refusal, match="installs no vftable retail shows as its own"):
        plan(tree)


def test_a_third_class_constructor_owning_the_table_is_still_an_icf_fold(tree, monkeypatch):
    # Other's constructor stores a base table and then TABLE, each through
    # this: TABLE is Other's own too, so retail folded two classes' tables
    tables = base_first_tables()
    tables[OTHER_TABLE][1][0x00405002] = 0
    tables[TABLE][1][0x00405008] = 0
    retail(monkeypatch, tables)
    proven(monkeypatch, {BASE_FIRST: 0, 0x00401002: 0, 0x00402000: 0, 0x00402018: 0,
                         0x00405002: 0, 0x00405008: 0})
    with pytest.raises(Refusal, match="also the own vftable of Other"):
        plan(tree)


# A destructor whose own vptr store the compiler dropped (0x003ABA36): it
# restores only the +0x18 base's table through the null-guarded cast
# `this ? this + 0x18 : 0`, then tail-jumps to the primary base destructor.
GUARDED_BODY = bytes.fromhex(
    "8BC1"              # 1000 mov eax,ecx
    "F7D8"              # 1002 neg eax                  CF = this != 0
    "8D5118"            # 1004 lea edx,[ecx+0x18]
    "1BC0"              # 1007 sbb eax,eax              this ? -1 : 0
    "23C2"              # 1009 and eax,edx              this ? this+0x18 : 0
    "C70054B5BB00"      # 100B mov [eax],T              +0x18
    "E900000000")       # 1011 jmp base dtor


def test_this_stores_reads_the_null_guarded_cast():
    assert rename.this_stores(GUARDED_BODY, 0x1000) == {0x100B: 0x18}


def test_this_stores_needs_the_carry_of_the_neg():
    # a flag write between neg and sbb: the mask no longer says this != 0
    body = GUARDED_BODY[:7] + bytes.fromhex("85C9") + GUARDED_BODY[7:]
    assert rename.this_stores(body, 0x1000) == {}
    # nor does a neg of anything but this
    body = bytes.fromhex("8B4508F7D88D51181BC023C2C70054B5BB00C3")
    assert rename.this_stores(body, 0x1000) == {}



# ------------------------------------------------------------ a destructor-only placeholder
#
# 0x00BFE408's class (DelayedSplineCameraEventModule's table): the constructor
# 0x002BAE57 is rowed under one placeholder, the destructor 0x002BAEAB and the
# deleting destructor 0x002BAE8F (slot 0) under another. MSVC dropped the
# empty-bodied destructor's vptr store, so the destructor placeholder installs
# no table; the deleting destructor in slot 0 of the constructor's own table
# ties it there. A second constructor 0x003FD64D under a third placeholder
# also installs the table as its own.
D_OLD = "Rva00402000"           # destructor-only placeholder
D_NEW = "Rva00401000"           # the constructor's placeholder; the vftable's name
D_CO = "Rva00403000"            # a second constructor's placeholder on the same table
D_DTOR, D_GDTOR = 0x00402000, 0x00402010


def d_functions(extra=""):
    return (f"""name,export_rva,target_rva,target_size,source,status,notes
??0{D_NEW}@@QAE@XZ,,0x00401000,13,Code/Game/Ctor.cpp,matched,ctor installs vtable 0x00C00000
??1{D_OLD}@@QAE@XZ,,0x00402000,7,Code/Game/Dtor.cpp,matched,dtor
??_G{D_OLD}@@QAEPAXI@Z,,0x00402010,29,Code/Game/Dtor.cpp,matched,deleting dtor
__ehhandler$??1{D_OLD}@@QAE@XZ,,0x00402100,10,Code/Game/Dtor.cpp,matched,handler of the dtor
??0Other@@QAE@XZ,,0x00405000,20,Code/Game/Other.cpp,matched,unrelated ctor
""" + extra)


def d_ledger(extra=""):
    return ("address,size,section,kind,name,source,status,names,defs,refs\n"
            f"0x00800000,12,.rdata,vtable,??_7{D_NEW}@@6B@,,literal,??_7{D_NEW}@@6B@,0,1\n" + extra)


D_CTOR_SRC = f"class {D_NEW}\n{{\npublic:\n\t{D_NEW}();\n\tvirtual ~{D_NEW}();\n}};\n{D_NEW}::{D_NEW}() {{}}\n"
D_DTOR_SRC = (f"class {D_OLD}\n{{\npublic:\n\t~{D_OLD}();\n}};\n{D_OLD}::~{D_OLD}() {{}}\n"
              f"void anchor() {{ delete new {D_OLD}; }}\n")


def make_dtor_tree(root, functions=None, ledger_text=None):
    files = {
        "reverse/functions.csv": functions or d_functions(),
        "reverse/symbols.csv": "name,address,notes\n",
        "reverse/deleted_rows.csv": "name,target_rva,reason\n",
        "reverse/data_rows.csv": "name,address,address_kind,size,section,source,status,evidence,model\n",
        "reverse/data_ledger.csv": ledger_text or d_ledger(),
        "reverse/exports.csv": "ordinal,rva,target_rva,section,kind,name\n",
        "reverse/gate_baseline.txt": "",
        "Code/Game/Ctor.cpp": D_CTOR_SRC,
        "Code/Game/Dtor.cpp": D_DTOR_SRC,
        "Code/Game/Other.cpp": OTHER,
    }
    for rel, text in files.items():
        path = root / rel
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(text.encode("utf-8"))
    _git(root, "init", "-q")
    _git(root, "add", "-A")
    return root


def d_tables(co_owner=False):
    # slot 1 holds the deleting destructor; only the constructor(s) store
    stores = {0x00401002: 0}
    if co_owner:
        stores[0x00403005] = 0
    return {TABLE: ([PURECALL, D_GDTOR, PURECALL], stores)}


def d_retail(monkeypatch, tables=None, calls=None):
    retail(monkeypatch, d_tables() if tables is None else tables)
    calls = {D_GDTOR: {D_DTOR, 0x0002FD60}} if calls is None else calls
    monkeypatch.setattr(rename, "retail_calls", lambda ctx, rva, size: set(calls.get(rva, ())))


def d_plan(root, old=D_OLD, new=D_NEW):
    return rename.plan_rename("class", ctx=ctx_of(root), name=old, new=new, fold=True)


def test_a_destructor_only_placeholder_folds_into_the_tables_owner(tmp_path, monkeypatch):
    root = make_dtor_tree(tmp_path)
    d_retail(monkeypatch)
    p = d_plan(root)
    assert p.fold == TABLE
    assert f"??0{D_NEW}@@QAE@XZ at 0x00401000 installs retail vftable 0x00C00000 as its own" in p.evidence
    assert f"??_G{D_OLD}@@QAEPAXI@Z at 0x00402010 is slot 1" in p.evidence
    assert f"??1{D_OLD}@@QAE@XZ at 0x00402000 is called by ??_G{D_OLD}@@QAEPAXI@Z at 0x00402010" in p.evidence
    assert f"{D_OLD} installs no vftable (destructor-only)" in p.evidence
    rename.apply_rename(p, ctx=ctx_of(root), verify=lambda ctx, sources: True)
    fns = (root / "reverse/functions.csv").read_text()
    assert f"??1{D_NEW}@@QAE@XZ,,0x00402000,7,Code/Game/Dtor.cpp,matched," in fns
    assert f"??_G{D_NEW}@@QAEPAXI@Z,,0x00402010,29,Code/Game/Dtor.cpp,matched," in fns
    assert f"__ehhandler$??1{D_NEW}@@QAE@XZ,,0x00402100" in fns
    assert D_OLD not in fns
    assert f"class {D_NEW}\n" in (root / "Code/Game/Dtor.cpp").read_text()
    assert (root / "Code/Game/Ctor.cpp").read_text() == D_CTOR_SRC


def test_a_second_constructors_class_on_the_table_stands_beside_the_fold(tmp_path, monkeypatch):
    # 0x003FD64D's placeholder also installs the table as its own: overloads
    # or an ICF fold, the slot's body is the owner's either way; not folded
    root = make_dtor_tree(
        tmp_path, d_functions(f"??0{D_CO}@@QAE@HD@Z,,0x00403000,40,Code/Game/Other.cpp,matched,second ctor\n"),
        d_ledger().replace(f"??_7{D_NEW}@@6B@,0,1", f"??_7{D_NEW}@@6B@;??_7{D_CO}@@6B@,0,2"))
    d_retail(monkeypatch, d_tables(co_owner=True))
    p = d_plan(root)
    assert f"also installed as its own by {D_CO} (??0{D_CO}@@QAE@HD@Z at 0x00403000)" in p.evidence
    assert f"{D_CO} is not folded" in p.evidence
    # the two constructor placeholders still never fold into each other here
    with pytest.raises(Refusal):
        d_plan(root, old=D_CO, new=D_NEW)


def test_a_destructor_only_fold_needs_the_destructor_called_by_its_deleting_destructor(tmp_path, monkeypatch):
    root = make_dtor_tree(tmp_path)
    d_retail(monkeypatch, calls={D_GDTOR: {0x00499999, 0x0002FD60}})       # a base's destructor
    with pytest.raises(Refusal, match="called by no deleting destructor"):
        d_plan(root)


def test_a_destructor_only_fold_needs_the_deleting_destructor_on_the_table(tmp_path, monkeypatch):
    root = make_dtor_tree(tmp_path)
    d_retail(monkeypatch, {TABLE: ([PURECALL, PURECALL, PURECALL], {0x00401002: 0})})
    with pytest.raises(Refusal, match="on no slot of retail vftable 0x00C00000"):
        d_plan(root)


def test_a_destructor_only_fold_refuses_a_third_name_with_no_installer(tmp_path, monkeypatch):
    root = make_dtor_tree(tmp_path, ledger_text=d_ledger().replace(
        f"??_7{D_NEW}@@6B@,0,1", f"??_7{D_NEW}@@6B@;??_7Rva00409999@@6B@,0,2"))
    d_retail(monkeypatch)
    with pytest.raises(Refusal, match="a third name for the table"):
        d_plan(root)


def test_a_destructor_only_fold_still_refuses_a_third_deleting_destructor_in_a_slot(tmp_path, monkeypatch):
    root = make_dtor_tree(tmp_path, d_functions(
        "??_GOther@@UAEPAXI@Z,,0x00405100,28,Code/Game/Other.cpp,matched,del\n"))
    d_retail(monkeypatch, {TABLE: ([PURECALL, D_GDTOR, 0x00405100], {0x00401002: 0})})
    with pytest.raises(Refusal, match="slot 2 holds Other's deleting destructor"):
        d_plan(root)


def test_a_destructor_only_fold_refuses_a_deleting_destructor_other_tables_also_hold(tmp_path, monkeypatch):
    # 0x00537E60 (??_GRva00535776): one ICF-folded deleting destructor in slot
    # 0 of three preferences classes' tables; the slot of T named none of
    # them, yet the fold passed into each. Another class's own table holding
    # the same body makes the slot no tie.
    root = make_dtor_tree(tmp_path, ledger_text=d_ledger(
        "0x00800200,8,.rdata,vtable,??_7Other@@6B@,,literal,??_7Other@@6B@,0,1\n"))
    tables = d_tables()
    tables[OTHER_TABLE] = ([D_GDTOR, PURECALL], {0x00405002: 0})       # ??0Other's own table
    d_retail(monkeypatch, tables)
    with pytest.raises(Refusal, match=r"also slot 0 of retail vftable 0x00C00200: an ICF-folded deleting "
                                      r"destructor of distinct classes"):
        d_plan(root)
    # the same refusal for the other candidate: the placeholder folds into neither
    with pytest.raises(Refusal, match="so Rva00402000 is no single class"):
        d_plan(root, new="Other")


def test_a_destructors_first_store_ties_no_class_when_other_tables_hold_its_deleting_destructor(tmp_path,
                                                                                               monkeypatch):
    # 0x00535776 (??1Rva00535776) stores the Profile preferences table first,
    # but an inlined base destructor's restore stores the same, and its
    # deleting destructor 0x00537E60 is slot 0 of two derived classes' tables
    # too: the fold passed into all three.
    root = make_dtor_tree(tmp_path)
    tables = {TABLE: ([PURECALL, D_GDTOR, PURECALL], {0x00401002: 0, D_DTOR: 0}),
              OTHER_TABLE: ([D_GDTOR, PURECALL], {0x00405002: 0})}
    d_retail(monkeypatch, tables)
    with pytest.raises(Refusal, match="no constructor of Rva00402000 installs 0x00C00000, so Rva00402000 is no "
                                      "single class"):
        d_plan(root)
    d_retail(monkeypatch, {TABLE: tables[TABLE]})       # T alone holds it: the destructor's store ties it
    assert d_plan(root).fold == TABLE


def test_a_constructor_owning_the_table_ties_the_class_whatever_shares_its_deleting_destructor(tmp_path,
                                                                                              monkeypatch):
    # OLD's own constructor installs T, so OLD is T's class even though retail
    # shares its deleting destructor's body with another class's table.
    root = make_dtor_tree(tmp_path, f"""name,export_rva,target_rva,target_size,source,status,notes
??0{D_OLD}@@QAE@XZ,,0x00402200,13,Code/Game/Dtor.cpp,matched,ctor installs vtable 0x00C00000
??1{D_OLD}@@QAE@XZ,,0x00402000,7,Code/Game/Dtor.cpp,matched,dtor
??_G{D_OLD}@@QAEPAXI@Z,,0x00402010,29,Code/Game/Dtor.cpp,matched,deleting dtor
??0Other@@QAE@XZ,,0x00405000,20,Code/Game/Other.cpp,matched,unrelated ctor
""")
    d_retail(monkeypatch, {TABLE: ([PURECALL, D_GDTOR, PURECALL], {0x00402202: 0}),
                           OTHER_TABLE: ([D_GDTOR, PURECALL], {0x00405002: 0})})
    p = d_plan(root)
    assert p.fold == TABLE
    assert f"??0{D_OLD}@@QAE@XZ at 0x00402200 installs retail vftable 0x00C00000 as its own" in p.evidence


def test_a_placeholder_with_a_method_is_not_destructor_only(tmp_path, monkeypatch):
    root = make_dtor_tree(tmp_path, d_functions(
        f"?run@{D_OLD}@@QAEXXZ,,0x00402200,5,Code/Game/Dtor.cpp,matched,a method\n"))
    d_retail(monkeypatch)
    with pytest.raises(Refusal, match="installs no vftable retail shows as its own"):
        d_plan(root)


def test_a_placeholder_without_a_deleting_destructor_is_not_destructor_only(tmp_path, monkeypatch):
    root = make_dtor_tree(tmp_path, d_functions().replace(
        f"??_G{D_OLD}@@QAEPAXI@Z,,0x00402010,29,Code/Game/Dtor.cpp,matched,deleting dtor\n", ""))
    d_retail(monkeypatch)
    with pytest.raises(Refusal, match="installs no vftable retail shows as its own"):
        d_plan(root)


def test_a_destructor_storing_another_table_is_not_destructor_only(tmp_path, monkeypatch):
    # the destructor stores a table at +0: the old route judges it (its first
    # +0 store is its own table, not the constructor's)
    root = make_dtor_tree(tmp_path)
    tables = d_tables()
    tables[OTHER_TABLE] = ([PURECALL], {0x00402003: 0})
    d_retail(monkeypatch, tables)
    with pytest.raises(Refusal, match="nothing ties|not that class"):
        d_plan(root)


def test_a_destructor_only_fold_needs_a_table_owner(tmp_path, monkeypatch):
    root = make_dtor_tree(tmp_path)
    d_retail(monkeypatch, {TABLE: ([PURECALL, D_GDTOR, PURECALL], {})})
    with pytest.raises(Refusal, match=f"and {D_NEW} installs none either"):
        d_plan(root)


def test_a_destructor_only_fold_into_a_class_with_its_own_destructor_is_refused(tmp_path, monkeypatch):
    root = make_dtor_tree(tmp_path, d_functions(
        f"??1{D_NEW}@@UAE@XZ,,0x00406000,7,Code/Game/Ctor.cpp,matched,another dtor\n"))
    d_retail(monkeypatch, calls={D_GDTOR: {D_DTOR}})
    with pytest.raises(Refusal, match="one class has one"):
        d_plan(root)



# ------------------------------------------------------------ a destructor under an inlined base destructor
#
# DamageModule's destructor 0x004B96CC (placeholder Rva004B96CC): BehaviorModule's
# destructor is inline, so retail's body stores DamageModule's +0x10 table, then
# BehaviorModule's own tables at +0 and +0x0C, and the optimizer dropped
# DamageModule's own +0/+0x0C stores. Its first +0 store names the base's table;
# the DamageModule constructor 0x004B9704 calls ??0BehaviorModule 0x00253330, which
# installs those tables last, and the deleting destructor 0x004B973B sits in slot 0
# of the constructor's own table 0x00C598E4.
R_BASE_CTOR = 0x00407000
BASE_TABLE = 0x00800300
IFACE_TABLE = 0x00800400


def r_functions(extra=""):
    return d_functions(f"??0Base@@QAE@XZ,,0x00407000,20,Code/Game/Other.cpp,matched,base ctor\n" + extra)


def r_tables(dtor_stores=None):
    """NEW's ctor installs IFACE at +0x10 and then TABLE at +0 (its own), the
    base ctor installs BASE_TABLE at +0; OLD's destructor stores `dtor_stores`
    ({store: (table, disp)}; by default IFACE at +0x10, then BASE_TABLE at +0)."""
    tables = {
        TABLE: ([PURECALL, D_GDTOR, PURECALL], {0x00401002: 0}),
        IFACE_TABLE: ([PURECALL], {0x00401008: 0x10}),
        BASE_TABLE: ([PURECALL], {0x00407002: 0}),
    }
    stores = {0x00402001: (IFACE_TABLE, 0x10), 0x00402003: (BASE_TABLE, 0)} if dtor_stores is None else dtor_stores
    for store, (table, disp) in stores.items():
        tables.setdefault(table, ([PURECALL], {}))[1][store] = disp
    return tables


def r_retail(monkeypatch, tables=None, calls=None):
    calls = {D_GDTOR: {D_DTOR, 0x0002FD60}, 0x00401000: {R_BASE_CTOR}} if calls is None else calls
    d_retail(monkeypatch, r_tables() if tables is None else tables, calls)


def test_an_inlined_base_destructors_restore_takes_the_destructor_only_route(tmp_path, monkeypatch):
    root = make_dtor_tree(tmp_path, r_functions())
    r_retail(monkeypatch)
    p = d_plan(root)
    assert p.fold == TABLE
    assert (f"??1{D_OLD}@@QAE@XZ at 0x00402000 stores 0x00C00400 at +0x10, which {D_NEW}'s constructor installs "
            "there last (its own)") in p.evidence
    assert (f"??1{D_OLD}@@QAE@XZ at 0x00402000 stores 0x00C00300 at +0x0, the table ??0Base@@QAE@XZ at 0x00407000 "
            f"installs there, a base constructor every constructor of {D_NEW} calls: an inlined base destructor's "
            "restore") in p.evidence
    assert f"??_G{D_OLD}@@QAEPAXI@Z at 0x00402010 is slot 1" in p.evidence
    assert f"??1{D_OLD}@@QAE@XZ at 0x00402000 is called by ??_G{D_OLD}@@QAEPAXI@Z at 0x00402010" in p.evidence
    assert f"{D_OLD} installs no table of its own" in p.evidence
    rename.apply_rename(p, ctx=ctx_of(root), verify=lambda ctx, sources: True)
    fns = (root / "reverse/functions.csv").read_text()
    assert f"??1{D_NEW}@@QAE@XZ,,0x00402000,7,Code/Game/Dtor.cpp,matched," in fns
    assert f"??_G{D_NEW}@@QAEPAXI@Z,,0x00402010,29,Code/Game/Dtor.cpp,matched," in fns


def test_an_inlined_base_restore_needs_news_constructor_to_call_the_base(tmp_path, monkeypatch):
    # the base table's installer is no constructor NEW's constructor calls: the
    # destructor's first +0 store names another class, as before
    root = make_dtor_tree(tmp_path, r_functions())
    r_retail(monkeypatch, calls={D_GDTOR: {D_DTOR, 0x0002FD60}})
    with pytest.raises(Refusal, match=f"{D_NEW} is not that class"):
        d_plan(root)


def test_an_inlined_base_restore_needs_a_base_constructor_row(tmp_path, monkeypatch):
    root = make_dtor_tree(tmp_path)                 # no ??0Base row
    r_retail(monkeypatch)
    with pytest.raises(Refusal, match=f"{D_NEW} is not that class"):
        d_plan(root)


def test_an_inlined_base_restore_refuses_a_store_nothing_explains(tmp_path, monkeypatch):
    # +0x10 holds a table neither NEW's constructor nor the base installs there
    root = make_dtor_tree(tmp_path, r_functions())
    r_retail(monkeypatch, r_tables({0x00402001: (OTHER_TABLE, 0x10), 0x00402003: (BASE_TABLE, 0)}))
    with pytest.raises(Refusal, match="not that class|nothing ties"):
        d_plan(root)


def test_an_inlined_base_restore_still_needs_the_deleting_destructor_on_the_table(tmp_path, monkeypatch):
    root = make_dtor_tree(tmp_path, r_functions())
    tables = r_tables()
    tables[TABLE] = ([PURECALL, PURECALL, PURECALL], {0x00401002: 0})
    r_retail(monkeypatch, tables)
    with pytest.raises(Refusal, match="on no slot of retail vftable 0x00C00000"):
        d_plan(root)


def test_an_inlined_base_restore_still_needs_the_destructor_called_by_its_deleting_destructor(tmp_path,
                                                                                           monkeypatch):
    root = make_dtor_tree(tmp_path, r_functions())
    r_retail(monkeypatch, calls={D_GDTOR: {0x00499999}, 0x00401000: {R_BASE_CTOR}})
    with pytest.raises(Refusal, match="called by no deleting destructor"):
        d_plan(root)


def test_an_inlined_base_restore_needs_a_destructor_family(tmp_path, monkeypatch):
    root = make_dtor_tree(tmp_path, r_functions(f"?run@{D_OLD}@@QAEXXZ,,0x00402200,5,Code/Game/Dtor.cpp,matched,m\n"))
    r_retail(monkeypatch)
    with pytest.raises(Refusal, match="not that class|nothing ties"):
        d_plan(root)



# ------------------------------------------------------------ a registered NEW: every unit prepared
#
# DamageModule is registered in canonical_classes.csv (DamageModuleClass.h). A
# token rewrite of Rva004B96CC would leave a private DamageModule view in each
# unit that declares the placeholder, so each such unit comes prepared on the
# shared header, spelling the placeholder nowhere; class_gate and the byte gate
# then judge it as for every rename.
D_HEADER = "Code/Game/NewClass.h"
D_DTOR_PREPARED = f'#include "NewClass.h"\n{D_NEW}::~{D_NEW}() {{}}\n'


def registered_tree(root, extra_units=None):
    make_dtor_tree(root)
    write(root, "reverse/canonical_classes.csv", f"class,header,notes\n{D_NEW},{D_HEADER},shared\n")
    write(root, D_HEADER, f"class {D_NEW}\n{{\npublic:\n\t{D_NEW}();\n\tvirtual ~{D_NEW}();\n}};\n")
    for rel, text in (extra_units or {}).items():
        write(root, rel, text)
    _git(root, "add", "-A")
    return root


def r_plan(root, prepared):
    return rename.plan_rename("class", ctx=ctx_of(root), name=D_OLD, new=D_NEW, fold=True, prepared=prepared)


def test_a_registered_new_without_prepared_units_is_refused(tmp_path, monkeypatch):
    root = registered_tree(tmp_path)
    d_retail(monkeypatch)
    with pytest.raises(Refusal, match="private copy"):
        d_plan(root)


def test_a_registered_new_folds_with_every_unit_prepared(tmp_path, monkeypatch):
    root = registered_tree(tmp_path)
    d_retail(monkeypatch)
    p = r_plan(root, {"Code/Game/Dtor.cpp": D_DTOR_PREPARED.encode("utf-8")})
    assert p.fold == TABLE
    rename.apply_rename(p, ctx=ctx_of(root), verify=lambda ctx, sources: True)
    fns = (root / "reverse/functions.csv").read_text()
    assert f"??1{D_NEW}@@QAE@XZ,,0x00402000,7,Code/Game/Dtor.cpp,matched," in fns
    assert f"??_G{D_NEW}@@QAEPAXI@Z,,0x00402010,29,Code/Game/Dtor.cpp,matched," in fns
    assert (root / "Code/Game/Dtor.cpp").read_text() == D_DTOR_PREPARED
    assert (root / "Code/Game/Ctor.cpp").read_text() == D_CTOR_SRC


def test_a_registered_new_refuses_an_unprepared_unit(tmp_path, monkeypatch):
    # a second unit declares the placeholder; it is not prepared
    root = registered_tree(tmp_path, {"Code/Game/Other.cpp": OTHER + f"class {D_OLD} {{ public: ~{D_OLD}(); }};\n"})
    d_retail(monkeypatch)
    with pytest.raises(Refusal, match=f"Code/Game/Other.cpp spells {D_OLD}: {D_NEW} is registered"):
        r_plan(root, {"Code/Game/Dtor.cpp": D_DTOR_PREPARED.encode("utf-8")})


def test_a_registered_new_refuses_a_prepared_unit_still_spelling_old(tmp_path, monkeypatch):
    root = registered_tree(tmp_path)
    d_retail(monkeypatch)
    with pytest.raises(Refusal, match=f"prepared Code/Game/Dtor.cpp still spells {D_OLD}"):
        r_plan(root, {"Code/Game/Dtor.cpp": D_DTOR_SRC.encode("utf-8")})


# ------------------------------------------------------------ --access: the header's destructor access
#
# CreateModule is registered (CreateModuleClass.h) and declares its virtual
# destructor protected, the spelling (??1CreateModule@@MAE@XZ) every current
# consumer references; the placeholder Rva004B8CDE rows ~CreateModule public
# (UAE). The prepared units compile the header's spelling, so the fold respells
# the destructor family's access with the class token.
D_HEADER_PROTECTED = (f"class {D_NEW}\n{{\npublic:\n\t{D_NEW}();\nprotected:\n\tvirtual ~{D_NEW}();\n}};\n")


def virtual_registered_tree(root):
    make_dtor_tree(root, d_functions().replace(f"{D_OLD}@@QAE", f"{D_OLD}@@UAE"))
    write(root, "reverse/canonical_classes.csv", f"class,header,notes\n{D_NEW},{D_HEADER},shared\n")
    write(root, D_HEADER, D_HEADER_PROTECTED)
    _git(root, "add", "-A")
    return root


def a_plan(root, prepared, access):
    return rename.plan_rename("class", ctx=ctx_of(root), name=D_OLD, new=D_NEW, fold=True, prepared=prepared,
                              access=access)


def test_a_fold_with_access_respells_the_destructor_family(tmp_path, monkeypatch):
    root = virtual_registered_tree(tmp_path)
    d_retail(monkeypatch)
    p = a_plan(root, {"Code/Game/Dtor.cpp": D_DTOR_PREPARED.encode("utf-8")}, "protected")
    assert "the destructor family takes protected access as requested" in p.evidence
    rename.apply_rename(p, ctx=ctx_of(root), verify=lambda ctx, sources: True)
    fns = (root / "reverse/functions.csv").read_text()
    assert f"??1{D_NEW}@@MAE@XZ,,0x00402000,7,Code/Game/Dtor.cpp,matched," in fns
    assert f"??_G{D_NEW}@@MAEPAXI@Z,,0x00402010,29,Code/Game/Dtor.cpp,matched," in fns
    assert f"__ehhandler$??1{D_NEW}@@MAE@XZ,,0x00402100" in fns
    assert f"??0{D_NEW}@@QAE@XZ,,0x00401000" in fns          # the constructor keeps its spelling
    assert D_OLD not in fns and f"{D_NEW}@@UAE" not in fns
    deleted = (root / "reverse/deleted_rows.csv").read_text()
    assert f"??1{D_OLD}@@UAE@XZ,0x00402000,\"Renamed to ??1{D_NEW}@@MAE@XZ" in deleted


def test_a_fold_without_access_keeps_the_placeholders_access(tmp_path, monkeypatch):
    root = virtual_registered_tree(tmp_path)
    d_retail(monkeypatch)
    p = r_plan(root, {"Code/Game/Dtor.cpp": D_DTOR_PREPARED.encode("utf-8")})
    rename.apply_rename(p, ctx=ctx_of(root), verify=lambda ctx, sources: True)
    assert f"??1{D_NEW}@@UAE@XZ,,0x00402000" in (root / "reverse/functions.csv").read_text()


def test_a_fold_with_access_needs_prepared_units(tmp_path, monkeypatch):
    root = make_dtor_tree(tmp_path, d_functions().replace(f"{D_OLD}@@QAE", f"{D_OLD}@@UAE"))
    d_retail(monkeypatch)
    with pytest.raises(Refusal, match="--access goes with prepared units"):
        a_plan(root, None, "protected")


def test_a_fold_with_access_refuses_a_nonvirtual_destructor_family(tmp_path, monkeypatch):
    root = registered_tree(tmp_path)                          # the placeholder rows spell QAE
    d_retail(monkeypatch)
    with pytest.raises(Refusal, match="near virtual destructor family only"):
        a_plan(root, {"Code/Game/Dtor.cpp": D_DTOR_PREPARED.encode("utf-8")}, "protected")


def test_a_fold_access_respells_an_adjustor_thunk_with_the_thunk_code():
    post = rename.fold_access_respell("CreateModule", "protected")
    assert post("??1CreateModule@@UAE@XZ") == "??1CreateModule@@MAE@XZ"
    assert post("??_GCreateModule@@UAEPAXI@Z") == "??_GCreateModule@@MAEPAXI@Z"
    assert post("??_ECreateModule@@WM@AEPAXI@Z") == "??_ECreateModule@@OM@AEPAXI@Z"
    assert post("??0CreateModule@@QAE@XZ") == "??0CreateModule@@QAE@XZ"
    assert post("?xfer@CreateModule@@UAEXPAVXfer@@@Z") == "?xfer@CreateModule@@UAEXPAVXfer@@@Z"
    assert post("??1CreateModuleData@@UAE@XZ") == "??1CreateModuleData@@UAE@XZ"
    with pytest.raises(Refusal):
        post("??1CreateModule@@QAE@XZ")


def test_access_goes_with_a_fold_only(tmp_path):
    root = make_dtor_tree(tmp_path)
    with pytest.raises(Refusal, match="--access goes with class --fold"):
        rename.plan_rename("class", ctx=ctx_of(root), name=D_OLD, new="Readable", basis="inferred",
                           evidence="x", access="protected")


def test_prepared_units_still_need_a_nested_or_registered_new(tmp_path, monkeypatch):
    root = make_dtor_tree(tmp_path)
    d_retail(monkeypatch)
    with pytest.raises(Refusal, match="an unregistered global NEW is a token rewrite"):
        r_plan(root, {"Code/Game/Dtor.cpp": D_DTOR_PREPARED.encode("utf-8")})


# ------------------------------------------------------------ a NEW rowed only through virtual methods
#
# 0x00CF1648's class: its constructor 0x00740FD9, destructor and deleting
# destructor are rowed under the placeholder Rva0074104C, whose objects name
# the table ??_7Rva0074104C@@6BRva0074104CBase@@@ (multiple inheritance);
# W3DAptComponentColorPicker is rowed only through Init and Render, slots 1
# and 2 of that table, and no object names the table for it.
V_OLD = "Rva00401000"
V_NEW = "WidgetPicker"
V_GDTOR, V_RUN = 0x00402010, 0x00406000


def v_functions(extra=""):
    return (f"""name,export_rva,target_rva,target_size,source,status,notes
??0{V_OLD}@@QAE@XZ,,0x00401000,13,Code/Game/Ctor.cpp,matched,ctor installs vtable 0x00C00000
??_G{V_OLD}@@UAEPAXI@Z,,0x00402010,29,Code/Game/Ctor.cpp,matched,deleting dtor
?run@{V_NEW}@@UAEXXZ,,0x00406000,20,Code/Game/Picker.cpp,matched,a virtual method
??0Other@@QAE@XZ,,0x00405000,20,Code/Game/Other.cpp,matched,unrelated ctor
""" + extra)


def v_ledger(name=f"??_7{V_OLD}@@6BBase@@@"):
    return ("address,size,section,kind,name,source,status,names,defs,refs\n"
            f"0x00800000,8,.rdata,vtable,{name},,literal,,0,1\n")


V_CTOR_SRC = f"class {V_OLD}\n{{\npublic:\n\t{V_OLD}();\n\tvirtual ~{V_OLD}();\n}};\n{V_OLD}::{V_OLD}() {{}}\n"
V_PICKER_SRC = f"class {V_NEW}\n{{\npublic:\n\tvirtual void run();\n}};\nvoid {V_NEW}::run() {{}}\n"


def make_virtual_tree(root, functions=None, ledger_text=None):
    files = {
        "reverse/functions.csv": functions or v_functions(),
        "reverse/symbols.csv": "name,address,notes\n",
        "reverse/deleted_rows.csv": "name,target_rva,reason\n",
        "reverse/data_rows.csv": "name,address,address_kind,size,section,source,status,evidence,model\n",
        "reverse/data_ledger.csv": ledger_text or v_ledger(),
        "reverse/exports.csv": "ordinal,rva,target_rva,section,kind,name\n",
        "reverse/gate_baseline.txt": "",
        "Code/Game/Ctor.cpp": V_CTOR_SRC,
        "Code/Game/Picker.cpp": V_PICKER_SRC,
        "Code/Game/Other.cpp": OTHER,
    }
    for rel, text in files.items():
        path = root / rel
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(text.encode("utf-8"))
    _git(root, "init", "-q")
    _git(root, "add", "-A")
    return root


def v_tables(slots=(V_GDTOR, V_RUN), extra=None):
    tables = {TABLE: (list(slots), {0x00401002: 0}),
              OTHER_TABLE: ([0x00407000, PURECALL], {0x00401001: 4})}
    tables.update(extra or {})
    return tables


def v_plan(root, old=V_OLD, new=V_NEW):
    return rename.plan_rename("class", ctx=ctx_of(root), name=old, new=new, fold=True)


def test_a_placeholder_folds_into_the_class_whose_virtuals_fill_its_table(tmp_path, monkeypatch):
    root = make_virtual_tree(tmp_path)
    retail(monkeypatch, v_tables())
    p = v_plan(root)
    assert p.fold == TABLE
    assert f"??0{V_OLD}@@QAE@XZ at 0x00401000 installs retail vftable 0x00C00000 as its own" in p.evidence
    assert f"?run@{V_NEW}@@UAEXXZ at 0x00406000 is slot 1 of 0x00C00000 and of no other retail table" in p.evidence
    assert f"??_G{V_OLD}@@UAEPAXI@Z at 0x00402010 is slot 0" in p.evidence
    rename.apply_rename(p, ctx=ctx_of(root), verify=lambda ctx, sources: True)
    fns = (root / "reverse/functions.csv").read_text()
    assert f"??0{V_NEW}@@QAE@XZ,,0x00401000,13,Code/Game/Ctor.cpp,matched," in fns
    assert f"??_G{V_NEW}@@UAEPAXI@Z,,0x00402010,29,Code/Game/Ctor.cpp,matched," in fns
    assert V_OLD not in fns.split("\n", 1)[1].replace(f"Renamed to {V_NEW}", "")
    assert f"class {V_NEW}\n" in (root / "Code/Game/Ctor.cpp").read_text()
    assert (root / "Code/Game/Picker.cpp").read_text() == V_PICKER_SRC


def test_a_virtual_slot_tie_needs_the_virtual_on_the_table(tmp_path, monkeypatch):
    root = make_virtual_tree(tmp_path)
    retail(monkeypatch, v_tables(slots=(V_GDTOR, PURECALL)))
    with pytest.raises(Refusal, match="is on no slot of 0x00C00000"):
        v_plan(root)


def test_a_virtual_slot_tie_refuses_a_virtual_in_another_table(tmp_path, monkeypatch):
    # a base class with a table of its own holds its virtual there too
    root = make_virtual_tree(tmp_path)
    retail(monkeypatch, v_tables(extra={DERIVED_TABLE: ([0x00408000, V_RUN], {0x00408002: 0})}))
    with pytest.raises(Refusal, match="also sits in retail table 0x00C00100"):
        v_plan(root)


def test_a_virtual_slot_tie_refuses_a_third_classs_member_in_a_slot(tmp_path, monkeypatch):
    root = make_virtual_tree(tmp_path, v_functions("?draw@Other@@UAEXXZ,,0x00405100,8,Code/Game/Other.cpp,matched,\n"))
    retail(monkeypatch, v_tables(slots=(V_GDTOR, V_RUN, 0x00405100)))
    with pytest.raises(Refusal, match="slot 2 holds \\?draw@Other@@UAEXXZ"):
        v_plan(root)


def test_a_virtual_slot_tie_needs_a_virtual_method(tmp_path, monkeypatch):
    root = make_virtual_tree(tmp_path, v_functions().replace(f"?run@{V_NEW}@@UAEXXZ", f"?run@{V_NEW}@@QAEXXZ"))
    retail(monkeypatch, v_tables())
    with pytest.raises(Refusal, match=f"no row is a virtual method of {V_NEW}"):
        v_plan(root)


def test_a_virtual_slot_tie_refuses_a_table_named_for_a_third_class(tmp_path, monkeypatch):
    root = make_virtual_tree(tmp_path, ledger_text=v_ledger("??_7Third@@6B@"))
    retail(monkeypatch, v_tables())
    with pytest.raises(Refusal, match=f"nothing ties {V_NEW} to it$"):
        v_plan(root)



# ------------------------------------------------------------ a registered base's restore, no base constructor call
#
# ScriptGroup's destructor 0x003B4100 (placeholder Rva003B4100) is
# `mov [ecx], 0x00BBB554; add ecx, 4; jmp clear`: its only +0 store is the
# registered Snapshot's own table (??0Snapshot@@QAE@XZ 0x000053A6 installs it),
# written by the inlined ~Snapshot after ScriptGroup's own store was dropped.
# Snapshot's constructor is inline as well, so neither ScriptGroup constructor
# (0x003B40DF, 0x003B410E) stores or calls one, and no base-constructor call
# proves the restore. The deleting destructor 0x003B4A20 is slot 0 of
# ScriptGroup's own table 0x00C1F470 and calls 0x003B4100 (re_attempts
# ??1Rva003B4100@@UAE@XZ).
SNAP_CTOR = 0x00408000
SNAP_TABLE = 0x00800500
MID_CTOR = 0x00409000
MID_TABLE = 0x00800600
SNAP_H = "Code/Game/Snap.h"


def s_functions(extra=""):
    return d_functions("??0Snap@@QAE@XZ,,0x00408000,9,Code/Game/Snap.cpp,matched,registered base ctor\n"
                       "??0Mid@@QAE@XZ,,0x00409000,9,Code/Game/Mid.cpp,matched,registered middle ctor\n" + extra)


def s_tables(dtor_stores=None, snap_store=0x00408002):
    """NEW's ctor installs TABLE (its own) and calls nothing; the registered
    Snap's ctor installs SNAP_TABLE, Mid's MID_TABLE; OLD's destructor stores
    `dtor_stores` ({store: (table, disp)}; by default SNAP_TABLE at +0)."""
    tables = {
        TABLE: ([PURECALL, D_GDTOR, PURECALL], {0x00401002: 0}),
        SNAP_TABLE: ([PURECALL], {snap_store: 0}),
        MID_TABLE: ([PURECALL], {0x00409002: 0}),
    }
    stores = {0x00402001: (SNAP_TABLE, 0)} if dtor_stores is None else dtor_stores
    for store, (table, disp) in stores.items():
        tables.setdefault(table, ([PURECALL], {}))[1][store] = disp
    return tables


def s_tree(root, *, registered=("Snap", "Mid"), functions=None, mid_base="Snap"):
    root = make_dtor_tree(root, functions or s_functions())
    write(root, "reverse/canonical_classes.csv",
          "class,header,notes\n" + "".join(f"{c},{SNAP_H},registered\n" for c in registered))
    write(root, SNAP_H, "class Snap { public: Snap(); virtual ~Snap(); };\n"
                        f"class Mid : public {mid_base} {{ public: Mid(); virtual ~Mid(); }};\n")
    for rel in ("Code/Game/Snap.cpp", "Code/Game/Mid.cpp"):
        write(root, rel, '#include "Snap.h"\n')
    _git(root, "add", "-A")
    return root


def s_retail(monkeypatch, tables=None, calls=None):
    calls = {D_GDTOR: {D_DTOR, 0x0002FD60}} if calls is None else calls
    d_retail(monkeypatch, s_tables() if tables is None else tables, calls)


def test_a_registered_bases_restore_takes_the_destructor_only_route(tmp_path, monkeypatch):
    root = s_tree(tmp_path)
    s_retail(monkeypatch)
    p = d_plan(root)
    assert p.fold == TABLE
    assert (f"??1{D_OLD}@@QAE@XZ at 0x00402000 stores 0x00C00500 at +0x0, the own table of registered Snap "
            "(??0Snap@@QAE@XZ at 0x00408000 installs it as its own), a base whose constructor is inline: an inlined "
            "base destructor's restore") in p.evidence
    assert f"??_G{D_OLD}@@QAEPAXI@Z at 0x00402010 is slot 1" in p.evidence
    assert f"??1{D_OLD}@@QAE@XZ at 0x00402000 is called by ??_G{D_OLD}@@QAEPAXI@Z at 0x00402010" in p.evidence
    rename.apply_rename(p, ctx=ctx_of(root), verify=lambda ctx, sources: True)
    fns = (root / "reverse/functions.csv").read_text()
    assert f"??1{D_NEW}@@QAE@XZ,,0x00402000,7,Code/Game/Dtor.cpp,matched," in fns


def test_an_unregistered_classs_table_is_no_restore(tmp_path, monkeypatch):
    root = s_tree(tmp_path, registered=())
    s_retail(monkeypatch)
    with pytest.raises(Refusal, match=f"{D_NEW} is not that class"):
        d_plan(root)


def test_a_registered_restore_needs_the_registered_class_to_own_the_table(tmp_path, monkeypatch):
    # Snap's constructor installs another table first: SNAP_TABLE is no own table of it
    root = s_tree(tmp_path)
    tables = s_tables(snap_store=0x00408006)
    tables[OTHER_TABLE] = ([PURECALL], {0x00408002: 0})
    s_retail(monkeypatch, tables)
    with pytest.raises(Refusal, match=f"{D_NEW} is not that class"):
        d_plan(root)


def test_a_registered_restore_is_a_primary_vptr_store_only(tmp_path, monkeypatch):
    # the registered table is stored at +0x10: the old route judges it (refused)
    root = s_tree(tmp_path)
    tables = s_tables({0x00402001: (SNAP_TABLE, 0x10), 0x00402003: (MID_TABLE, 0)})
    s_retail(monkeypatch, tables)
    with pytest.raises(Refusal, match="not that class|nothing ties"):
        d_plan(root)


def test_the_classs_own_table_never_follows_a_bases_restore(tmp_path, monkeypatch):
    # stores in the wrong order: Snap's table, then NEW's own at +0
    root = s_tree(tmp_path)
    s_retail(monkeypatch, s_tables({0x00402001: (SNAP_TABLE, 0), 0x00402003: (TABLE, 0)}))
    with pytest.raises(Refusal, match=f"{D_NEW} is not that class"):
        d_plan(root)


def test_the_classs_own_table_then_a_registered_base(tmp_path, monkeypatch):
    # NEW's own store kept, then the base's restore: in order
    root = s_tree(tmp_path)
    s_retail(monkeypatch, s_tables({0x00402001: (TABLE, 0), 0x00402003: (SNAP_TABLE, 0)}))
    p = d_plan(root)
    assert f"stores 0x00C00000 at +0x0, which {D_NEW}'s constructor installs there last (its own)" in p.evidence
    assert "the own table of registered Snap" in p.evidence


def test_bases_restore_from_the_nearest_up(tmp_path, monkeypatch):
    # Mid's table, then Snap's (Mid derives from Snap): the chain in order
    root = s_tree(tmp_path)
    s_retail(monkeypatch, s_tables({0x00402001: (MID_TABLE, 0), 0x00402003: (SNAP_TABLE, 0)}))
    p = d_plan(root)
    assert "the own table of registered Mid" in p.evidence and "the own table of registered Snap" in p.evidence


def test_bases_restored_out_of_order_are_refused(tmp_path, monkeypatch):
    # Snap's table, then Mid's: Mid is no base of Snap
    root = s_tree(tmp_path)
    s_retail(monkeypatch, s_tables({0x00402001: (SNAP_TABLE, 0), 0x00402003: (MID_TABLE, 0)}))
    with pytest.raises(Refusal, match=f"{D_NEW} is not that class"):
        d_plan(root)


def test_unrelated_registered_tables_are_refused(tmp_path, monkeypatch):
    # Mid's table, then Snap's, but Mid does not derive from Snap
    root = s_tree(tmp_path, mid_base="Other")
    s_retail(monkeypatch, s_tables({0x00402001: (MID_TABLE, 0), 0x00402003: (SNAP_TABLE, 0)}))
    with pytest.raises(Refusal, match=f"{D_NEW} is not that class"):
        d_plan(root)


def test_a_registered_restore_still_needs_the_destructor_called_by_its_deleting_destructor(tmp_path, monkeypatch):
    root = s_tree(tmp_path)
    s_retail(monkeypatch, calls={D_GDTOR: {0x00499999}})
    with pytest.raises(Refusal, match="called by no deleting destructor"):
        d_plan(root)


def test_a_registered_restore_still_needs_the_deleting_destructor_on_the_table(tmp_path, monkeypatch):
    root = s_tree(tmp_path)
    tables = s_tables()
    tables[TABLE] = ([PURECALL, PURECALL, PURECALL], {0x00401002: 0})
    s_retail(monkeypatch, tables)
    with pytest.raises(Refusal, match="on no slot of retail vftable 0x00C00000"):
        d_plan(root)


def test_a_registered_restore_needs_a_destructor_family(tmp_path, monkeypatch):
    root = s_tree(tmp_path, functions=s_functions(f"?run@{D_OLD}@@QAEXXZ,,0x00402200,5,Code/Game/Dtor.cpp,matched,m\n"))
    s_retail(monkeypatch)
    with pytest.raises(Refusal, match="not that class|nothing ties"):
        d_plan(root)
