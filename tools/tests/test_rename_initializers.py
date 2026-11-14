"""tools/rename.py initializers: respell a unit's `_$E<n>` rows to the ordinals its object registers, paired by
`.CRT$XCU` position with retail's table (SpawnBehavior.cpp's shape: rows _$E16 and _$E88 become _$E1 and _$E3 once
the unit leaves the Zero Hour headers). The object is a real COFF file; retail's table and the object lookup are
injected."""
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import link_cycle  # noqa: E402
import rename  # noqa: E402
from rename import Refusal, VerifyFailed  # noqa: E402

SRC = "Code/Game/Spawn.cpp"
OTHER = "Code/Game/Other.cpp"
FIRST, SECOND, POOL = 0x007B0BFF, 0x007B0C0F, 0x007B0C1F
TABLE = [0x007B0000, FIRST, SECOND, POOL]
CODE = 0x60000020
XCU = 0x40300040
BODY = b"\xA1\x00\x00\x00\x00\x99\x2B\xC2\xD1\xF8\xA3\x00\x00\x00\x00\xC3"


def functions(rows=None):
    rows = rows if rows is not None else (
        f"_$E16,,0x{FIRST:08X},16,{SRC},matched,initializer of the Drawable.h copy\n"
        f'_$E88,,0x{SECOND:08X},16,{SRC},matched,"initializer of g, after the copy"\n')
    return ("name,export_rva,target_rva,target_size,source,status,notes\n" + rows
            + f"?update@Spawn@@QAEXXZ,,0x00600000,32,{SRC},matched,\n"
            + f"_$E16,,0x007B0000,16,{OTHER},matched,another unit's own _$E16\n"
            + f"?pool@@YAXXZ,,0x{POOL:08X},26,Code/Game/Pool.cpp,matched,\n")


def make_tree(root, *, fn=None, deleted="", identity="", gate=""):
    files = {
        "reverse/functions.csv": fn or functions(),
        "reverse/deleted_rows.csv": "name,target_rva,reason\n" + deleted,
        "reverse/symbols.csv": "name,address,notes\n",
        "reverse/body_owners.csv": "target_rva,name,target_size,source,evidence\n",
        "reverse/code_identity_baseline.tsv": "# mode shadow\n" + identity,
        "reverse/gate_baseline.txt": gate,
        SRC: "int g = frames / 2;\n",
        OTHER: "int h = frames / 3;\n",
    }
    for rel, content in files.items():
        path = root / rel
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(content.encode("utf-8"))
    subprocess.run(["git", "-C", str(root), "init", "-q"], check=True)
    subprocess.run(["git", "-C", str(root), "add", "-A"], check=True)
    return root


def write_object(path, registered=("_$E1", "_$E3"), defined=("_$E1", "_$E2", "_$E3"), comdat=False):
    """A unit's object: `defined` local code symbols 16 bytes apart (_$E2 is the atexit callback no
    `.CRT$XCU` entry names), `registered` in `.CRT$XCU` order."""
    text = BODY * len(defined)
    xcu = b"\0" * (4 * len(registered))
    sections = [(".text", CODE, text, 0), (".CRT$XCU", XCU | (link_cycle.COMDAT if comdat else 0), xcu,
                                           2 if comdat else 0)]
    symbols = [(name, 1, 16 * i, link_cycle.STATIC) for i, name in enumerate(defined)]
    symbols += [(name, 0, 0, link_cycle.EXTERNAL) for name in registered if name not in defined]
    relocs = {2: [(4 * i, name, link_cycle.DIR32) for i, name in enumerate(registered)]}
    return link_cycle.write_coff(path, sections, symbols, relocs)


@pytest.fixture
def tree(tmp_path, monkeypatch):
    def build(table=TABLE, **object_args):
        root = make_tree(tmp_path / "repo", **build.tree_args)
        obj = write_object(tmp_path / "spawn.obj", **object_args)
        monkeypatch.setattr(rename, "retail_initializers", lambda ctx: list(table))
        monkeypatch.setattr(rename, "_source_object", lambda ctx, rel, current=True: obj if rel == SRC else None)
        return root, obj
    build.tree_args = {}
    return build


def plan(root):
    return rename.plan_rename("initializers", ctx=rename.Context(root, object_scan=False), source=SRC)


# ------------------------------------------------------------ the pairing

def test_rows_take_their_objects_ordinals_in_crt_order(tree):
    root, _obj = tree()
    result = plan(root)
    assert result.renamed_rows == [("_$E16", "_$E1", FIRST), ("_$E88", "_$E3", SECOND)]
    fns = result.after["reverse/functions.csv"].decode()
    # only the ordinal changes; the rest of each record keeps its bytes (the quoted note too)
    assert f"_$E1,,0x{FIRST:08X},16,{SRC},matched,initializer of the Drawable.h copy\n" in fns
    assert f'_$E3,,0x{SECOND:08X},16,{SRC},matched,"initializer of g, after the copy"\n' in fns
    # another unit's same-named row is a different function and stays
    assert f"_$E16,,0x007B0000,16,{OTHER},matched" in fns
    deleted = result.after["reverse/deleted_rows.csv"].decode()
    assert f"_$E16,0x{FIRST:08X},\"Respelled to _$E1 by tools/rename.py initializers" in deleted
    assert f"_$E88,0x{SECOND:08X},\"Respelled to _$E3 by tools/rename.py initializers" in deleted
    assert result.verify == [SRC]
    assert rename.claim_keys(result) == [FIRST, SECOND, f"file:{SRC}"]
    assert set(result.after) == {"reverse/functions.csv", "reverse/deleted_rows.csv"}


def test_a_row_already_spelled_right_is_left_alone(tree):
    tree.tree_args = {"fn": functions(f"_$E1,,0x{FIRST:08X},16,{SRC},matched,copy\n"
                                      f"_$E88,,0x{SECOND:08X},16,{SRC},matched,g\n")}
    root, _obj = tree()
    assert plan(root).renamed_rows == [("_$E88", "_$E3", SECOND)]


def test_order_comes_from_the_table_not_the_names(tree):
    # the object registers _$E3 before _$E1: the row first in retail's table takes _$E3
    root, _obj = tree(registered=("_$E3", "_$E1"))
    assert plan(root).renamed_rows == [("_$E16", "_$E3", FIRST), ("_$E88", "_$E1", SECOND)]


# ------------------------------------------------------------ refusals

def test_refuses_a_count_mismatch(tree):
    root, _obj = tree(registered=("_$E1", "_$E2", "_$E3"))
    with pytest.raises(Refusal, match=r"registers 3 `_\$E` initializer\(s\).*rows 2"):
        plan(root)


def test_refuses_a_row_with_no_table_entry(tree):
    root, _obj = tree(table=[0x007B0000, FIRST, POOL])
    with pytest.raises(Refusal, match=r"_\$E88 at 0x007B0C0F is no entry of retail's .CRT\$XCU table"):
        plan(root)


def test_refuses_a_row_the_table_lists_twice(tree):
    root, _obj = tree(table=[FIRST, SECOND, FIRST])
    with pytest.raises(Refusal, match=r"is 2 entries of retail's"):
        plan(root)


def test_refuses_two_rows_at_one_address(tree):
    tree.tree_args = {"fn": functions() + f"?alias@@YAXXZ,,0x{FIRST:08X},16,Code/Game/Alias.cpp,matched,\n"}
    root, _obj = tree()
    with pytest.raises(Refusal, match=r"2 rows sit at 0x007B0BFF"):
        plan(root)


def test_refuses_table_and_address_order_that_disagree(tree):
    root, _obj = tree(table=[0x007B0000, SECOND, FIRST, POOL])
    with pytest.raises(Refusal, match=r"different order in retail's .CRT\$XCU table than by address"):
        plan(root)


def test_refuses_a_comdat_registration(tree):
    root, _obj = tree(comdat=True)
    with pytest.raises(Refusal, match=r"COMDAT .CRT\$XCU contribution"):
        plan(root)


def test_refuses_a_registered_name_the_object_does_not_define(tree):
    root, _obj = tree(defined=("_$E1", "_$E2"))
    with pytest.raises(Refusal, match=r"_\$E3 is registered 1 time\(s\) and defined 0 time\(s\)"):
        plan(root)


def test_refuses_nothing_to_respell(tree):
    tree.tree_args = {"fn": functions(f"_$E1,,0x{FIRST:08X},16,{SRC},matched,\n_$E3,,0x{SECOND:08X},16,{SRC},matched,\n")}
    root, _obj = tree()
    with pytest.raises(Refusal, match=r"already carry the ordinals"):
        plan(root)


def test_refuses_to_restore_a_tombstoned_spelling(tree):
    tree.tree_args = {"deleted": f'_$E1,0x{FIRST:08X},"an earlier respell"\n'}
    root, _obj = tree()
    with pytest.raises(Refusal, match=r"retires _\$E1 at 0x007B0BFF"):
        plan(root)


def test_refuses_a_row_a_debt_register_keys(tree):
    tree.tree_args = {"identity": f"{SRC}\t_$E88\t_$E2\t0x{SECOND:08X}\twrong\n"}
    root, _obj = tree()
    with pytest.raises(Refusal, match=r"code_identity_baseline.tsv keys _\$E88"):
        plan(root)


def test_refuses_a_gate_baselined_row(tree):
    tree.tree_args = {"gate": f"bytes 0x{FIRST:08X} _$E16\n"}
    root, _obj = tree()
    with pytest.raises(Refusal, match=r"gate_baseline.txt keys _\$E16"):
        plan(root)


def test_refuses_a_row_bound_through_a_note(tree):
    tree.tree_args = {"fn": functions(f"_$E16,,0x{FIRST:08X},16,{SRC},matched,object-symbol=_$E9\n"
                                      f"_$E88,,0x{SECOND:08X},16,{SRC},matched,g\n")}
    root, _obj = tree()
    with pytest.raises(Refusal, match=r"not read by its own name"):
        plan(root)


def test_refuses_without_a_current_object(tree, monkeypatch):
    root, _obj = tree()
    monkeypatch.setattr(rename, "_source_object", lambda ctx, rel, current=True: None)
    with pytest.raises(Refusal, match=r"no object compiled from its present text"):
        plan(root)


# ------------------------------------------------------------ apply: the rebuilt object is paired again

def test_apply_writes_both_ledgers_after_the_build(tree):
    root, _obj = tree()
    ctx = rename.Context(root, object_scan=False)
    result = rename.plan_rename("initializers", ctx=ctx, source=SRC)
    rename.apply_rename(result, ctx=ctx, verify=lambda ctx, sources: True, checks=None)
    assert (root / "reverse/functions.csv").read_bytes() == result.after["reverse/functions.csv"]
    assert b"Respelled to _$E3" in (root / "reverse/deleted_rows.csv").read_bytes()


def test_apply_refuses_a_rebuilt_object_that_registers_another_order(tree):
    root, obj = tree()
    ctx = rename.Context(root, object_scan=False)
    result = rename.plan_rename("initializers", ctx=ctx, source=SRC)
    before = (root / "reverse/functions.csv").read_bytes()

    def rebuilt(ctx, sources):
        write_object(obj, registered=("_$E3", "_$E1"))
        return True
    with pytest.raises(VerifyFailed, match=r"rebuilt object does not prove"):
        rename.apply_rename(result, ctx=ctx, verify=rebuilt, checks=None)
    assert (root / "reverse/functions.csv").read_bytes() == before


def test_the_cli_takes_no_basis(tree, capsys):
    root, _obj = tree()
    with pytest.raises(SystemExit):
        rename.main(["initializers", "--source", SRC, "--basis", "inferred", "--root", str(root), "--dry-run"])
    assert "pass no --basis" in capsys.readouterr().err
