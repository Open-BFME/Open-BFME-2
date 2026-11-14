"""tools/rename.py initializers: respell a unit's `_$E<n>` rows to the ordinals its object registers, paired by
`.CRT$XCU` position with retail's table (SpawnBehavior.cpp's shape: rows _$E16 and _$E88 become _$E1 and _$E3 once
the unit leaves the Zero Hour headers). The object is a real COFF file; retail's table and the object lookup are
injected."""
import struct
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import build as rename_build  # noqa: E402
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


KEY_A, KEY_B, KEY_C = (f"?s_key@?$ModuleTag@${k}@FX@@2PBDB" for k in ("05", "00", "01"))
STR_A, STR_B, STR_C = (f"??_C@_0M@{k}@KEY?$AA@" for k in ("AAAA", "BBBB", "CCCC"))
STATICS = {KEY_A: 0x00A02C40, KEY_B: 0x00A02C44, KEY_C: 0x00A02C48,
           STR_A: 0x00860100, STR_B: 0x00860110, STR_C: 0x00860120}
LEDGER = "".join(f"0x{at:08X},4,.data,global,{name},{{src}},owned,,0,4\n" for name, at in STATICS.items())


def va(name):
    return STATICS[name] + rename.IMAGE_BASE


def functions(rows=None):
    rows = rows if rows is not None else (
        f"_$E16,,0x{FIRST:08X},16,{SRC},matched,initializer of the Drawable.h copy\n"
        f'_$E88,,0x{SECOND:08X},16,{SRC},matched,"initializer of g, after the copy"\n')
    return ("name,export_rva,target_rva,target_size,source,status,notes\n" + rows
            + f"?update@Spawn@@QAEXXZ,,0x00600000,32,{SRC},matched,\n"
            + f"_$E16,,0x007B0000,16,{OTHER},matched,another unit's own _$E16\n"
            + f"?pool@@YAXXZ,,0x{POOL:08X},26,Code/Game/Pool.cpp,matched,\n")


def make_tree(root, *, fn=None, deleted="", identity="", gate="", symbols="", owners="", ledger=None):
    files = {
        "reverse/functions.csv": fn or functions(),
        "reverse/deleted_rows.csv": "name,target_rva,reason\n" + deleted,
        "reverse/symbols.csv": "name,address,notes\n" + symbols,
        "reverse/body_owners.csv": "target_rva,name,target_size,source,evidence\n" + owners,
        "reverse/data_ledger.csv": "address,size,section,kind,name,source,status,names,defs,refs\n"
                                   + (LEDGER.format(src=SRC) if ledger is None else ledger),
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


def write_object(path, registered=("_$E1", "_$E3"), defined=("_$E1", "_$E2", "_$E3"), comdat=False,
                 kind=link_cycle.DIR32, addend=0):
    """A unit's object: `defined` local code symbols 16 bytes apart (_$E2 is the atexit callback no
    `.CRT$XCU` entry names), `registered` in `.CRT$XCU` order."""
    text = BODY * len(defined)
    xcu = struct.pack("<I", addend) * len(registered)
    sections = [(".text", CODE, text, 0), (".CRT$XCU", XCU | (link_cycle.COMDAT if comdat else 0), xcu,
                                           2 if comdat else 0)]
    symbols = [(name, 1, 16 * i, link_cycle.STATIC) for i, name in enumerate(defined)]
    symbols += [(name, 0, 0, link_cycle.EXTERNAL) for name in registered if name not in defined]
    relocs = {2: [(4 * i, name, kind) for i, name in enumerate(registered)]}
    return link_cycle.write_coff(path, sections, symbols, relocs)


@pytest.fixture
def tree(tmp_path, monkeypatch):
    def build(table=TABLE, retail=None, **object_args):
        root = make_tree(tmp_path / "repo", **build.tree_args)
        obj = write_object(tmp_path / "spawn.obj", **object_args)
        monkeypatch.setattr(rename, "retail_initializers", lambda ctx: list(table))
        bodies = retail or {}
        monkeypatch.setattr(rename_build, "read_target_bytes",
                            lambda rva, size: (bodies.get(rva, BODY) + b"\xCC" * size)[:size])
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
    with pytest.raises(Refusal, match=r"_\$E88 \(_\$E88\) at 0x007B0C0F is no entry of retail's .CRT\$XCU table"):
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


def test_refuses_a_comdat_registration_outside_the_templates(tree):
    # the fixture's 16-byte BODY (load, arithmetic, store) is no template: its COMDAT registration refuses
    root, _obj = tree(comdat=True)
    with pytest.raises(Refusal, match=r"COMDAT-registered _\$E1 \(a1 .*16 bytes\) is no initializer template"):
        plan(root)


def test_refuses_a_registered_name_the_object_does_not_define(tree):
    root, _obj = tree(defined=("_$E1", "_$E2"))
    with pytest.raises(Refusal, match=r"registers _\$E3, which is no STATIC code definition"):
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


COPY = "??__Ecopy@@YAXXZ"


def test_a_row_bound_through_a_note_has_its_note_respelled(tree):
    # the row keeps its name; only its object-symbol= ordinal changes, so no tombstone
    tree.tree_args = {"fn": functions(f'{COPY},,0x{FIRST:08X},16,{SRC},matched,"object-symbol=_$E16;copy, first"\n'
                                      f"_$E88,,0x{SECOND:08X},16,{SRC},matched,g\n")}
    root, _obj = tree()
    result = plan(root)
    assert result.renamed_rows == [("_$E88", "_$E3", SECOND)]
    assert result.notes_rows == [(COPY, FIRST)]
    fns = result.after["reverse/functions.csv"].decode()
    assert f'{COPY},,0x{FIRST:08X},16,{SRC},matched,"object-symbol=_$E1;copy, first"\n' in fns
    assert f"_$E3,,0x{SECOND:08X},16,{SRC},matched,g\n" in fns
    deleted = result.after["reverse/deleted_rows.csv"].decode()
    assert "_$E88,0x007B0C0F" in deleted and COPY not in deleted and "_$E16" not in deleted
    assert rename.claim_keys(result) == [FIRST, SECOND, f"file:{SRC}"]


def test_only_the_note_ordinal_changes_never_a_longer_one(tree):
    tree.tree_args = {"fn": functions(f"{COPY},,0x{FIRST:08X},16,{SRC},matched,object-symbol=_$E1;was _$E16\n"
                                      f"_$E88,,0x{SECOND:08X},16,{SRC},matched,g\n")}
    root, _obj = tree(registered=("_$E3", "_$E1"))
    fns = plan(root).after["reverse/functions.csv"].decode()
    assert f"{COPY},,0x{FIRST:08X},16,{SRC},matched,object-symbol=_$E3;was _$E16\n" in fns


def test_only_noted_rows_write_no_tombstone(tree):
    tree.tree_args = {"fn": functions(f"{COPY},,0x{FIRST:08X},16,{SRC},matched,object-symbol=_$E16\n"
                                      f"?other@@YAXXZ,,0x{SECOND:08X},16,{SRC},matched,object-symbol=_$E88\n")}
    root, _obj = tree()
    result = plan(root)
    assert result.renamed_rows == [] and len(result.notes_rows) == 2
    assert "reverse/deleted_rows.csv" not in result.after


def test_refuses_one_ordinal_claimed_by_two_rows(tree):
    # FXParticleSystemModules' _$E158: an object-symbol row at a retail slot and a bare row elsewhere
    tree.tree_args = {"fn": functions(f"{COPY},,0x{FIRST:08X},16,{SRC},matched,object-symbol=_$E16\n"
                                      f"_$E88,,0x{SECOND:08X},16,{SRC},matched,g\n"
                                      f"_$E16,,0x007B3EB4,16,{SRC},matched,second claim\n")}
    root, _obj = tree()
    with pytest.raises(Refusal, match=r"2 rows of Code/Game/Spawn.cpp bind _\$E16 .*claimed twice"):
        plan(root)


def test_refuses_a_noted_gen_placeholder(tree):
    tree.tree_args = {"fn": functions(f"{COPY},,0x{FIRST:08X},16,{SRC},matched,object-symbol=_$E16;gen-alias\n"
                                      f"_$E88,,0x{SECOND:08X},16,{SRC},matched,g\n")}
    root, _obj = tree()
    with pytest.raises(Refusal, match=r"generated source or carries a gen- note"):
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


def test_refuses_a_relocation_that_registers_nothing(tree):
    # IMAGE_REL_I386_ABSOLUTE names the symbol and relocates nothing
    root, _obj = tree(kind=0)
    with pytest.raises(Refusal, match=r"relocation of type 0x0 at \+0x0, not a DIR32 pointer slot"):
        plan(root)


def test_refuses_a_registration_past_the_entry(tree):
    root, _obj = tree(addend=4)
    with pytest.raises(Refusal, match=r"registers _\$E1\+0x4 at \+0x0, not the function's entry"):
        plan(root)


@pytest.mark.parametrize("record", [
    f'"_$E16",0x{FIRST:08X},note\n',            # a quoted name is still the name
    f"_$E16,0x{FIRST:08x},note\n",              # lowercase hex is the same address
    f"_$E16,0x{FIRST:X},note\n"])               # so is an unpadded one
def test_refuses_a_pin_however_spelled(tree, record):
    tree.tree_args = {"symbols": record}
    root, _obj = tree()
    with pytest.raises(Refusal, match=r"symbols.csv keys _\$E16"):
        plan(root)


def test_refuses_a_quoted_body_owner(tree):
    tree.tree_args = {"owners": f'0x{SECOND:08x},"_$E88",16,{SRC},owned\n'}
    root, _obj = tree()
    with pytest.raises(Refusal, match=r"body_owners.csv keys _\$E88"):
        plan(root)


def test_a_pin_of_the_same_name_elsewhere_is_no_key(tree):
    # another unit's _$E16 at another address is not this row's record
    tree.tree_args = {"symbols": "_$E16,0x007B0000,note\n"}
    root, _obj = tree()
    assert plan(root).renamed_rows[0] == ("_$E16", "_$E1", FIRST)


# ------------------------------------------------------------ COMDAT registrations by exact template

def tpl(store, address):
    """mov dword ptr [store], address; ret -- the one template (11 bytes)."""
    return b"\xC7\x05" + struct.pack("<I", store) + struct.pack("<I", address) + b"\xC3"


def template_object(path, entries, *, plain=(), plain_entries=()):
    """An object registering each of `entries` [(name, code, [(offset, symbol, addend, kind)])] from its own
    COMDAT .text and COMDAT .CRT$XCU section, after `plain` names (BODY, one plain section) or `plain_entries`
    (like `entries`, laid out in one plain .text and registered in one plain .CRT$XCU) if any."""
    sections, symbols, table = [], [], {}
    externals = set()
    if plain:
        sections += [(".text", CODE, BODY * len(plain), 0), (".CRT$XCU", XCU, b"\0" * 4 * len(plain), 0)]
        symbols += [(name, 1, 16 * i, link_cycle.STATIC) for i, name in enumerate(plain)]
        table[2] = [(4 * i, name, link_cycle.DIR32) for i, name in enumerate(plain)]
    elif plain_entries:
        text, relocs, at = bytearray(), [], 0
        for name, code, entry_relocs in plain_entries:
            symbols.append((name, 1, at, link_cycle.STATIC))
            chunk = bytearray(code)
            for offset, symbol, addend, kind in entry_relocs:
                chunk[offset:offset + 4] = struct.pack("<i", addend)
                relocs.append((at + offset, symbol, kind))
                externals.add(symbol)
            text += chunk
            at += len(code)
        sections += [(".text", CODE, bytes(text), 0), (".CRT$XCU", XCU, b"\0" * 4 * len(plain_entries), 0)]
        table[1] = relocs
        table[2] = [(4 * i, name, link_cycle.DIR32) for i, (name, _c, _r) in enumerate(plain_entries)]
    for name, code, relocs in entries:
        text = bytearray(code)
        for offset, _symbol, addend, _kind in relocs:
            text[offset:offset + 4] = struct.pack("<i", addend)
        sections.append((".text", CODE | link_cycle.COMDAT, bytes(text), 2))
        at = len(sections)
        symbols.append((name, at, 0, link_cycle.STATIC))
        table[at] = [(offset, symbol, kind) for offset, symbol, _a, kind in relocs]
        externals.update(symbol for _o, symbol, _a, _k in relocs)
        sections.append((".CRT$XCU", XCU | link_cycle.COMDAT, b"\0" * 4, 2))
        table[len(sections)] = [(0, name, link_cycle.DIR32)]
    symbols += [(name, 0, 0, link_cycle.EXTERNAL) for name in sorted(externals)]
    return link_cycle.write_coff(path, sections, symbols, table)


def entry(name, static, address, *, store_addend=0, extra=(), kind=link_cycle.DIR32, code=None):
    return (name, code if code is not None else tpl(0, 0),
            [(2, static, store_addend, kind), (6, address, 0, link_cycle.DIR32), *extra])


# rows of 11 bytes, retail bodies: FIRST builds KEY_A from STR_A, SECOND KEY_B from STR_B
TPL_ROWS = functions(f"_$E16,,0x{FIRST:08X},11,{SRC},matched,a\n_$E88,,0x{SECOND:08X},11,{SRC},matched,b\n")
TPL_RETAIL = {FIRST: tpl(va(KEY_A), va(STR_A)), SECOND: tpl(va(KEY_B), va(STR_B))}


def template_tree(tree, monkeypatch, tmp_path, entries, *, plain=(), retail=None, fn=None, table=TABLE):
    tree.tree_args = dict(tree.tree_args, fn=fn or TPL_ROWS)
    root, _obj = tree(retail=TPL_RETAIL if retail is None else retail, table=table)
    obj = template_object(tmp_path / "tpl.obj", entries, plain=plain)
    monkeypatch.setattr(rename, "_source_object", lambda ctx, rel, current=True: obj if rel == SRC else None)
    return root, obj


# FXParticleSystemDefaults' lesson in Modules' shape: the object registers _$E1 (KEY_B) before _$E3 (KEY_A);
# retail's table has the KEY_A initializer first. Order would pair FIRST with _$E1; the template pairs it with _$E3.
SWAPPED = [entry("_$E1", KEY_B, STR_B), entry("_$E3", KEY_A, STR_A)]


def test_comdat_rows_pair_by_template_not_by_order(tree, monkeypatch, tmp_path):
    root, _obj = template_tree(tree, monkeypatch, tmp_path, SWAPPED)
    assert plan(root).renamed_rows == [("_$E16", "_$E3", FIRST), ("_$E88", "_$E1", SECOND)]


def test_comdat_rows_already_bound_plan_no_respell(tree, monkeypatch, tmp_path):
    fn = functions(f"{COPY},,0x{FIRST:08X},11,{SRC},matched,object-symbol=_$E3\n"
                   f"?second@@YAXXZ,,0x{SECOND:08X},11,{SRC},matched,object-symbol=_$E1\n")
    root, _obj = template_tree(tree, monkeypatch, tmp_path, SWAPPED, fn=fn)
    with pytest.raises(Refusal, match=r"already carry the ordinals"):
        plan(root)


def test_plain_rows_keep_order_beside_template_ones(tree, monkeypatch, tmp_path):
    # FIRST is a plain initializer (BODY, 11-byte row); SECOND builds KEY_A from its own COMDAT section
    fn = functions(f"_$E16,,0x{FIRST:08X},16,{SRC},matched,a\n_$E88,,0x{SECOND:08X},11,{SRC},matched,b\n")
    root, _obj = template_tree(tree, monkeypatch, tmp_path, [entry("_$E5", KEY_A, STR_A)], plain=("_$E1",), fn=fn,
                               retail={FIRST: BODY, SECOND: tpl(va(KEY_A), va(STR_A))})
    assert plan(root).renamed_rows == [("_$E16", "_$E1", FIRST), ("_$E88", "_$E5", SECOND)]


def test_refuses_a_comdat_row_out_of_order(tree, monkeypatch, tmp_path):
    root, _obj = template_tree(tree, monkeypatch, tmp_path, SWAPPED, table=[0x007B0000, SECOND, FIRST, POOL])
    with pytest.raises(Refusal, match=r"different order in retail's .CRT\$XCU table than by address"):
        plan(root)


def test_refuses_a_comdat_copy_retail_kept_from_another_object(tree, monkeypatch, tmp_path):
    root, _obj = template_tree(tree, monkeypatch, tmp_path, SWAPPED + [entry("_$E5", KEY_C, STR_C)])
    with pytest.raises(Refusal, match=r"registers 3 `_\$E` initializer\(s\) \(.*; 3 of them COMDAT"):
        plan(root)


@pytest.mark.parametrize("missing", [KEY_B, STR_B])
def test_refuses_an_operand_missing_from_the_data_ledger(tree, monkeypatch, tmp_path, missing):
    tree.tree_args = {"ledger": "".join(line for line in LEDGER.format(src=SRC).splitlines(True)
                                        if f",{missing}," not in line)}
    root, _obj = template_tree(tree, monkeypatch, tmp_path, SWAPPED)
    with pytest.raises(Refusal, match=r"is missing from reverse/data_ledger.csv"):
        plan(root)


def test_refuses_an_operand_the_ledger_places_twice(tree, monkeypatch, tmp_path):
    tree.tree_args = {"ledger": LEDGER.format(src=SRC) + f"0x00A09000,4,.data,global,{KEY_B},{SRC},owned,,0,1\n"}
    root, _obj = template_tree(tree, monkeypatch, tmp_path, SWAPPED)
    with pytest.raises(Refusal, match=r"is at several addresses in reverse/data_ledger.csv"):
        plan(root)


def test_refuses_two_rows_with_the_same_template_and_operands(tree, monkeypatch, tmp_path):
    retail = {FIRST: tpl(va(KEY_B), va(STR_B)), SECOND: tpl(va(KEY_B), va(STR_B))}
    root, _obj = template_tree(tree, monkeypatch, tmp_path, SWAPPED, retail=retail)
    with pytest.raises(Refusal, match=r"2 rows' retail bodies are _\$E1's template with its operands"):
        plan(root)


def test_refuses_when_the_stored_address_differs(tree, monkeypatch, tmp_path):
    # same static, another address stored: no row holds both operands
    retail = {FIRST: tpl(va(KEY_A), va(STR_A)), SECOND: tpl(va(KEY_B), va(STR_C))}
    root, _obj = template_tree(tree, monkeypatch, tmp_path, SWAPPED, retail=retail)
    with pytest.raises(Refusal, match=r"0 rows' retail bodies are _\$E1's template"):
        plan(root)


def test_an_operand_addend_is_part_of_the_address(tree, monkeypatch, tmp_path):
    entries = [entry("_$E1", KEY_B, STR_B, store_addend=4), entry("_$E3", KEY_A, STR_A)]
    root, _obj = template_tree(tree, monkeypatch, tmp_path, entries)
    with pytest.raises(Refusal, match=r"0 rows' retail bodies are _\$E1's template with its operands \(0x00E02C48"):
        plan(root)
    retail = {FIRST: tpl(va(KEY_A), va(STR_A)), SECOND: tpl(va(KEY_B) + 4, va(STR_B))}
    root, _obj = template_tree(tree, monkeypatch, tmp_path, entries, retail=retail)
    assert plan(root).renamed_rows == [("_$E16", "_$E3", FIRST), ("_$E88", "_$E1", SECOND)]


@pytest.mark.parametrize("code,why", [
    (b"\xE8\x00\x00\x00\x00\xA3\x00\x00\x00\x00\xC3", "call then store"),     # FXParticleSystemDefaults' shape
    (tpl(0, 0) + b"\x90", "a trailing byte"),
    (b"\xC7\x05" + b"\0" * 8 + b"\xC2", "another last byte"),
    (b"\xC7\x45" + b"\0" * 8 + b"\xC3", "another addressing byte"),
])
def test_refuses_a_body_that_is_no_exact_template(tree, monkeypatch, tmp_path, code, why):
    entries = [entry("_$E1", KEY_B, STR_B, code=code), entry("_$E3", KEY_A, STR_A)]
    root, _obj = template_tree(tree, monkeypatch, tmp_path, entries)
    with pytest.raises(Refusal, match=r"COMDAT-registered _\$E1 .* is no initializer template"):
        plan(root)


@pytest.mark.parametrize("relocs,why", [
    ([(2, KEY_B, 0, link_cycle.DIR32)], "the address operand unrelocated"),
    ([(2, KEY_B, 0, link_cycle.DIR32), (6, STR_B, 0, link_cycle.REL32)], "a REL32 operand"),
    ([(2, KEY_B, 0, 0xB), (6, STR_B, 0, link_cycle.DIR32)], "a SECREL operand"),
    # the held addends keep the template's bytes (05 at +1; 00 00 00 C3 at +7) so only the relocations differ
    ([(1, KEY_B, 0x05, link_cycle.DIR32), (6, STR_B, 0, link_cycle.DIR32)], "a relocation over the opcode"),
    ([(2, KEY_B, 0, link_cycle.DIR32), (6, STR_B, 0, link_cycle.DIR32), (7, STR_C, -0x3D000000, link_cycle.DIR32)],
     "an extra relocation"),
])
def test_refuses_relocations_other_than_the_templates(tree, monkeypatch, tmp_path, relocs, why):
    entries = [("_$E1", tpl(0, 0), relocs), entry("_$E3", KEY_A, STR_A)]
    root, _obj = template_tree(tree, monkeypatch, tmp_path, entries)
    with pytest.raises(Refusal, match=r"_\$E1 has relocations at .*its template takes exactly one DIR32 at each of \+2, \+6"):
        plan(root)


def test_refuses_a_row_of_another_size(tree, monkeypatch, tmp_path):
    fn = functions(f"_$E16,,0x{FIRST:08X},11,{SRC},matched,a\n_$E88,,0x{SECOND:08X},12,{SRC},matched,b\n")
    root, _obj = template_tree(tree, monkeypatch, tmp_path, SWAPPED, fn=fn)
    with pytest.raises(Refusal, match=r"0 rows' retail bodies are _\$E1's template"):
        plan(root)


def test_apply_refuses_a_rebuilt_object_whose_template_builds_another_static(tree, monkeypatch, tmp_path):
    root, obj = template_tree(tree, monkeypatch, tmp_path, SWAPPED)
    ctx = rename.Context(root, object_scan=False)
    result = rename.plan_rename("initializers", ctx=ctx, source=SRC)
    before = (root / "reverse/functions.csv").read_bytes()

    def rebuilt(ctx, sources):
        template_object(obj, [entry("_$E1", KEY_A, STR_A), entry("_$E3", KEY_B, STR_B)])
        return True
    with pytest.raises(VerifyFailed, match=r"rebuilt object does not prove"):
        rename.apply_rename(result, ctx=ctx, verify=rebuilt, checks=None)
    assert (root / "reverse/functions.csv").read_bytes() == before


# ------------------------------------------------------------ Sol r1: capture, repeated and overlapping relocations

THIRD = 0x007B0C2F
THREE_ROWS = functions(f"_$E16,,0x{FIRST:08X},11,{SRC},matched,a\n_$E88,,0x{SECOND:08X},11,{SRC},matched,b\n"
                       f"_$E90,,0x{THIRD:08X},11,{SRC},matched,c\n")
THREE_RETAIL = {FIRST: tpl(va(KEY_A), va(STR_A)), SECOND: tpl(va(KEY_B), va(STR_B)), THIRD: tpl(va(KEY_C), va(STR_C))}
PLAIN_AB = [entry("_$E1", KEY_A, STR_A), entry("_$E3", KEY_B, STR_B)]


def three_tree(tree, monkeypatch, tmp_path, comdat_entries):
    tree.tree_args = dict(tree.tree_args, fn=THREE_ROWS)
    root, _obj = tree(retail=THREE_RETAIL, table=[0x007B0000, FIRST, SECOND, THIRD])
    obj = template_object(tmp_path / "tpl.obj", comdat_entries, plain_entries=PLAIN_AB)
    monkeypatch.setattr(rename, "_source_object", lambda ctx, rel, current=True: obj if rel == SRC else None)
    return root


def test_plain_template_rows_confirm_the_order_pairing(tree, monkeypatch, tmp_path):
    root = three_tree(tree, monkeypatch, tmp_path, [entry("_$E5", KEY_C, STR_C)])
    assert plan(root).renamed_rows == [("_$E16", "_$E1", FIRST), ("_$E88", "_$E3", SECOND), ("_$E90", "_$E5", THIRD)]


def test_refuses_a_comdat_match_that_takes_a_plain_row(tree, monkeypatch, tmp_path):
    # the COMDAT initializer now builds A, as plain _$E1 does: it takes row A, and order would then give
    # plain _$E1 row B and plain _$E3 row C
    root = three_tree(tree, monkeypatch, tmp_path, [entry("_$E5", KEY_A, STR_A)])
    with pytest.raises(Refusal, match=r"order pairs plain _\$E1 with _\$E88 at 0x007B0C0F, but that row is not"):
        plan(root)


def test_refuses_two_relocations_at_one_operand(tree, monkeypatch, tmp_path):
    relocs = [(2, KEY_B, 0, link_cycle.DIR32), (2, KEY_B, 0, link_cycle.DIR32), (6, STR_B, 0, link_cycle.DIR32)]
    root, _obj = template_tree(tree, monkeypatch, tmp_path, [("_$E1", tpl(0, 0), relocs), entry("_$E3", KEY_A, STR_A)])
    with pytest.raises(Refusal, match=r"_\$E1 has relocations at \+2, \+2, \+6; its template takes exactly one"):
        plan(root)


def raw_object(path, text_sections, symbols, relocs, registered):
    """An object of the given (name, flags, body, sel) code sections, symbols [(name, sec, value, class)],
    relocs {sec: [(offset, symbol, kind)]}, and one COMDAT .CRT$XCU section per name in `registered`."""
    sections = list(text_sections)
    table = dict(relocs)
    for name in registered:
        sections.append((".CRT$XCU", XCU | link_cycle.COMDAT, b"\0" * 4, 2))
        table[len(sections)] = [(0, name, link_cycle.DIR32)]
    return link_cycle.write_coff(path, sections, symbols, table)


def test_refuses_a_relocation_reaching_in_from_before_the_body(tree, monkeypatch, tmp_path):
    # _$E1 starts at +1 of its section; a DIR32 at +0 rewrites its opcode bytes C7 05 when linked
    root, _obj = template_tree(tree, monkeypatch, tmp_path, [entry("_$E3", KEY_A, STR_A)])
    body = b"\x90" + tpl(0, 0)
    obj = raw_object(tmp_path / "raw.obj",
                     [(".text", CODE | link_cycle.COMDAT, body, 2), (".text", CODE | link_cycle.COMDAT, tpl(0, 0), 2)],
                     [("_$E1", 1, 1, link_cycle.STATIC), ("_$E3", 2, 0, link_cycle.STATIC)]
                     + [(s, 0, 0, link_cycle.EXTERNAL) for s in (KEY_A, KEY_B, STR_A, STR_B, STR_C)],
                     {1: [(0, STR_C, link_cycle.DIR32), (3, KEY_B, link_cycle.DIR32), (7, STR_B, link_cycle.DIR32)],
                      2: [(2, KEY_A, link_cycle.DIR32), (6, STR_A, link_cycle.DIR32)]},
                     ("_$E1", "_$E3"))
    monkeypatch.setattr(rename, "_source_object", lambda ctx, rel, current=True: obj if rel == SRC else None)
    with pytest.raises(Refusal, match=r"_\$E1 has relocations at -1, \+2, \+6"):
        plan(root)


def test_refuses_a_registered_name_defined_twice(tree, monkeypatch, tmp_path):
    # an EXTERNAL _$E1 in one section and the registered STATIC _$E1 in another: one name, two bodies
    root, _obj = template_tree(tree, monkeypatch, tmp_path, [entry("_$E3", KEY_A, STR_A)])
    obj = raw_object(tmp_path / "raw.obj",
                     [(".text", CODE, tpl(0, 0), 0), (".text", CODE | link_cycle.COMDAT, tpl(0, 0), 2),
                      (".text", CODE | link_cycle.COMDAT, tpl(0, 0), 2)],
                     [("_$E1", 1, 0, link_cycle.EXTERNAL), ("_$E1", 2, 0, link_cycle.STATIC),
                      ("_$E3", 3, 0, link_cycle.STATIC)]
                     + [(s, 0, 0, link_cycle.EXTERNAL) for s in (KEY_A, KEY_B, STR_A, STR_B)],
                     {1: [(2, KEY_A, link_cycle.DIR32), (6, STR_A, link_cycle.DIR32)],
                      2: [(2, KEY_B, link_cycle.DIR32), (6, STR_B, link_cycle.DIR32)],
                      3: [(2, KEY_A, link_cycle.DIR32), (6, STR_A, link_cycle.DIR32)]},
                     ("_$E1", "_$E3"))
    monkeypatch.setattr(rename, "_source_object", lambda ctx, rel, current=True: obj if rel == SRC else None)
    with pytest.raises(Refusal, match=r"_\$E1 is registered 1 time\(s\) and defined 2 time\(s\) in the object"):
        plan(root)


def test_refuses_a_registration_of_no_static_code_symbol(tree, monkeypatch, tmp_path):
    root, _obj = template_tree(tree, monkeypatch, tmp_path, [entry("_$E3", KEY_A, STR_A)])
    obj = raw_object(tmp_path / "raw.obj",
                     [(".text", CODE | link_cycle.COMDAT, tpl(0, 0), 2), (".text", CODE | link_cycle.COMDAT, tpl(0, 0), 2)],
                     [("_$E1", 1, 0, link_cycle.EXTERNAL), ("_$E3", 2, 0, link_cycle.STATIC)]
                     + [(s, 0, 0, link_cycle.EXTERNAL) for s in (KEY_A, KEY_B, STR_A, STR_B)],
                     {1: [(2, KEY_B, link_cycle.DIR32), (6, STR_B, link_cycle.DIR32)],
                      2: [(2, KEY_A, link_cycle.DIR32), (6, STR_A, link_cycle.DIR32)]},
                     ("_$E1", "_$E3"))
    monkeypatch.setattr(rename, "_source_object", lambda ctx, rel, current=True: obj if rel == SRC else None)
    with pytest.raises(Refusal, match=r"registers _\$E1, which is no STATIC code definition"):
        plan(root)
