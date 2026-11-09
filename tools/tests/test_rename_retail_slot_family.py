"""`tools/rename.py function --respell --identity --basis retail` on a slot-and-operand family
(tools/retail_identity.py SlotOperandFamily): the real entry is the fixture, its facts served from an image the
test writes. The table the row fills is ICF-shared, so its name is never evidence; the element is proved by the
destructor the row's own body passes to the CRT's vector iterator, and the rebuilt row must bind it."""
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import allowed_symbols  # noqa: E402
import rename  # noqa: E402
import retail_identity as R  # noqa: E402
from rename import Refusal, VerifyFailed  # noqa: E402

F = R.RENDERER_VECTOR
COPY = F.copy
HANDLER = 0x00766EDC
OLD_COPY = F.rows[COPY][0]
NEW_COPY = F.respell(OLD_COPY)
UNIT = "Code/Lib/VectorResize.cpp"
WRITER_UNIT = "Code/Lib/SentenceDtor.cpp"
SIZES = {COPY: 384, HANDLER: 10}
PREPARED = {UNIT: b"// the resize under its new element\n"}
TABLE = F.slot.code[0]


def write(path, text):
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_bytes(text.encode("utf-8"))


def git(root, *args):
    subprocess.run(["git", "-C", str(root), *args], check=True, capture_output=True)


@pytest.fixture
def image(monkeypatch):
    """Retail as the family's facts say it is, the table's next word not code; a test edits a site to break one."""
    bytes_at = {}
    for fact in F.facts():
        for i, byte in enumerate(R.expected(fact)):
            bytes_at[fact.site + i] = byte
    _table, _index, count = F.slot.code
    for i in range(4):
        bytes_at[TABLE - R.IMAGE_BASE + 4 * count + i] = 0x25      # 0x25252525: no address in the image

    def read(rva, size):
        return bytes(bytes_at[rva + i] for i in range(size))
    monkeypatch.setattr(R, "read_retail", read)
    monkeypatch.setattr(R, "section_name", lambda rva: ".text" if rva < 0x00700000 or 0x00760000 <= rva < 0x00780000
                        else ".rdata" if rva < 0x00900000 else None)
    return bytes_at


def ledger_rows(writer_size=347, skip=(), rename_at=None):
    rows = ["name,export_rva,target_rva,target_size,source,status,notes\n"]
    entries = [(old, at, SIZES[at], UNIT) for at, (old, _f) in sorted(F.rows.items())]
    entries += [(F.writer["name"], F.writer["rva"], writer_size, WRITER_UNIT),
                (F.element_dtor["name"], F.element_dtor["rva"], 8, "Code/Lib/SentenceDraw.cpp")]
    entries += [(name, at, 96, "Code/Lib/CRT.cpp") for at, name in sorted(F.iterators.items())]
    for name, at, size, source in entries:
        if name in skip:
            continue
        if rename_at == name:
            at += 1
        rows.append(f"{name},,0x{at:08X},{size},{source},matched,row\n")
    return "".join(rows)


@pytest.fixture
def tree(tmp_path, image):
    files = {
        "reverse/functions.csv": ledger_rows(),
        "reverse/symbols.csv": "name,address,notes\n",
        "reverse/deleted_rows.csv": "name,target_rva,reason\n",
        "reverse/name_basis.csv": "kind,old,new,basis,evidence,source,rva\n",
        "reverse/data_rows.csv": "name,address,address_kind,size,section,source,status,evidence,model\n",
        "reverse/exports.csv": "ordinal,rva,target_rva,section,kind,name\n",
        "reverse/gate_baseline.txt": "",
        "reverse/tu_map.csv": "rva,size,kind,tu,confidence,by,evidence,source\n",
        # the folded table is named for another instantiation, as in the real ledger: it must not matter
        "reverse/data_ledger.csv": ("address,size,section,kind,name,source,status,names,defs,refs\n"
                                    "0x007D3BC8,24,.rdata,vtable,??_7?$VectorClass@UAddInfoStruct@MixFileFactoryClass@@@@6B@,,"
                                    "literal,,0,4\n"),
        UNIT: "// resize\n",
        WRITER_UNIT: "// sentence dtor\n",
        "Code/Lib/SentenceDraw.cpp": "// renderer dtor\n",
        "Code/Lib/CRT.cpp": "// iterators\n",
    }
    for rel, text in files.items():
        write(tmp_path / rel, text)
    git(tmp_path, "init", "-q")
    git(tmp_path, "add", "-A")
    git(tmp_path, "-c", "user.email=t@t", "-c", "user.name=t", "commit", "-q", "-m", "seed")
    return tmp_path


GOOD_RELOCS = {NEW_COPY: [(offset, kind, target)
                          for _source, _name, offset, kind, target in rename.slot_operand_bindings(F, UNIT, NEW_COPY)]}


def context(root, refs=(), relocs=None):
    ctx = rename.Context(root, object_scan=False)
    state = {"refs": list(refs), "relocs": GOOD_RELOCS if relocs is None else relocs}
    ctx.identity_refs = lambda sources: [r for r in state["refs"] if r["source"] in sources]
    ctx.object_symbol_relocs = lambda source, name: state["relocs"].get(name, [])
    return ctx, state


def plan(ctx, **overrides):
    kwargs = dict(rva=COPY, new=NEW_COPY, respell=True, identity=True, basis="retail", evidence=F.evidence(),
                  prepared=dict(PREPARED))
    kwargs.update(overrides)
    return rename.plan_rename("function", ctx=ctx, **kwargs)


def after_refs():
    return [dict(source=UNIT, row=F.respell(old), rva=at, symbol="x", target=0x1234, cls="owner")
            for at, (old, _f) in F.rows.items()]


def land(ctx, got, state, refs=None, relocs=None):
    def verify(c, sources):
        state["refs"] = after_refs() if refs is None else refs
        if relocs is not None:
            state["relocs"] = relocs
        return True
    return rename.apply_rename(got, ctx=ctx, verify=verify, checks=None)


# ------------------------------------------------------------------ the entry

def test_the_entry_is_what_the_coordinator_reviewed():
    assert F in R.FAMILIES and isinstance(F, R.SlotOperandFamily)
    assert set(F.rows) == {0x00155690, 0x00766EDC}
    assert NEW_COPY == "?Resize@?$VectorClass@URendererDataStruct@Render2DSentenceClass@@@@UAE_NHPBURendererDataStruct@Render2DSentenceClass@@@Z"
    assert F.writer["name"] == "??1Render2DSentenceClass@@QAE@XZ" and F.writer["facts"][0].site == 0x00157D06
    assert F.element_dtor == {"name": "??1RendererDataStruct@Render2DSentenceClass@@QAE@XZ", "rva": 0x00001E13}
    assert sorted(F.iterators.values()) == sorted(R.ITERATOR_NAMES)
    assert R.family_of(COPY, NEW_COPY) is F and R.family_of(HANDLER, F.respell(F.rows[HANDLER][0])) is F


def test_the_real_image_states_them_all():
    if not R.build.EXE.exists():
        pytest.skip("no retail image here")
    assert R.facts_problems(F.facts()) == []


def kwargs():
    return dict(old_element=F.old, new_element=F.new, copy=F.copy, spellings=dict(F.spellings), slot=F.slot,
                writer=dict(F.writer), element_dtor=dict(F.element_dtor), operands=F.operands,
                iterators=dict(F.iterators), rows=dict(F.rows))


def push(value, site=0x001556FC):
    return R.Fact("stores", site, value, "68")


@pytest.mark.parametrize("label, change, message", [
    ("a spelling that changes more than the element",
     lambda k: k["spellings"].update({OLD_COPY: NEW_COPY.replace("UAE_N", "QAE_N")}), "element swap alone"),
    ("a spelling left out", lambda k: k["spellings"].pop(OLD_COPY), "element swap alone"),
    ("a spelling no row has", lambda k: k["spellings"].update({"?x@@YAXXZ": "?y@@YAXXZ"}), "every spelling"),
    ("an element dtor of another type",
     lambda k: k["element_dtor"].update(name="??1AddInfoStruct@MixFileFactoryClass@@QAE@XZ"), "not the destructor"),
    ("a writer of another class",
     lambda k: k["writer"].update(name="??1MixFileFactoryClass@@QAE@XZ"), "no constructor or destructor"),
    ("a writer that is no special member",
     lambda k: k["writer"].update(name="?Reset@Render2DSentenceClass@@QAEXXZ"), "no constructor or destructor"),
    ("a writer fact that is no vptr store",
     lambda k: k["writer"].update(facts=(R.Fact("stores", 0x00157D06, TABLE, "b8"),)), "stores of the table"),
    ("a writer storing another table",
     lambda k: k["writer"].update(facts=(R.Fact("stores", 0x00157D06, TABLE + 4, "c707"),)), "stores of the table"),
    ("no operands", lambda k: k.update(operands=()), "needs the copy's operands"),
    ("a push of another body",
     lambda k: k.update(operands=((push(0x00401E14), F.operands[0][1]),) + F.operands[1:]), "must push"),
    ("a call that is no iterator",
     lambda k: k.update(iterators={**F.iterators, 0x00629512: "?other@@YAXXZ"}), "must call a vector iterator"),
    ("a call before its push",
     lambda k: k.update(operands=((F.operands[0][0], R.Fact("calls", 0x001556F0, 0x00629512)),) + F.operands[1:]),
     "must call a vector iterator"),
    ("an iterator nothing calls", lambda k: k["iterators"].update({0x00629000: "??_L@YGXPAXIHP6EX0@Z1@Z"}), "no operand calls"),
    ("an operand the copy's facts leave out",
     lambda k: k["rows"].update({COPY: (OLD_COPY, tuple(f for f in F.rows[COPY][1] if f != F.operands[1][1]))}),
     "one of the copy's facts"),
    ("a slot of another row", lambda k: k.update(slot=R.slot(TABLE, 2, 6, 0x00155691)), "the copy's word"),
    ("a second row proved some other way",
     lambda k: k["rows"].update({HANDLER: (F.rows[HANDLER][0], (R.Fact("calls", 0x00155698, HANDLER),))}),
     "loading its address"),
])
def test_the_constructor_refuses_each_missing_condition(label, change, message):
    k = kwargs()
    change(k)
    with pytest.raises(ValueError, match=message):
        R.SlotOperandFamily(**k)


def test_the_real_kwargs_build():
    R.SlotOperandFamily(**kwargs())


# ------------------------------------------------------------------ the plan

def test_the_rows_are_respelled_with_their_records(tree):
    ctx, _ = context(tree)
    got = plan(ctx)
    rows = got.after["reverse/functions.csv"].decode()
    for at, (old, _f) in F.rows.items():
        assert old not in rows and f"{F.respell(old)},,0x{at:08X},{SIZES[at]},{UNIT},matched" in rows
    basis = got.after["reverse/name_basis.csv"].decode()
    assert f"function,{OLD_COPY},{NEW_COPY},retail,{F.evidence()},{UNIT},0x{COPY:08X}" in basis
    assert got.identity["operands"] and "table_name" not in got.identity and "bindings" not in got.identity
    deleted = got.after["reverse/deleted_rows.csv"].decode()
    assert OLD_COPY in deleted


def test_the_tables_name_is_not_read(tree):
    """The folded table named for AddInfoStruct, named for nothing, or missing: the plan is the same."""
    ctx, _ = context(tree)
    first = plan(ctx).identity
    path = tree / "reverse/data_ledger.csv"
    path.write_text("address,size,section,kind,name,source,status,names,defs,refs\n")
    git(tree, "add", "-A")
    ctx, _ = context(tree)
    assert plan(ctx).identity == first


def test_each_byte_of_each_fact_refuses(tree, image):
    ctx, _ = context(tree)
    for fact in F.facts():
        for i in range(len(R.expected(fact))):
            keep = image[fact.site + i]
            image[fact.site + i] = keep ^ 0xFF
            with pytest.raises(Refusal, match="retail does not state"):
                plan(ctx)
            image[fact.site + i] = keep


def test_a_slot_of_a_longer_table_refuses(tree, image):
    _table, _index, count = F.slot.code
    at = TABLE - R.IMAGE_BASE + 4 * count
    keep = [image[at + i] for i in range(4)]
    for i, byte in enumerate((0x00, 0x10, 0x40, 0x00)):           # 0x00401000: code
        image[at + i] = byte
    ctx, _ = context(tree)
    with pytest.raises(Refusal, match="more than"):
        plan(ctx)
    for i, byte in enumerate(keep):
        image[at + i] = byte


@pytest.mark.parametrize("name, message", [
    (F.writer["name"], "table's writer"),
    (F.element_dtor["name"], "destructor's row"),
    ("??_L@YGXPAXIHP6EX0@Z1@Z", "is not rowed"),
    ("??_M@YGXPAXIHP6EX0@Z@Z", "is not rowed"),
])
def test_each_tie_must_be_rowed_at_its_address(tree, name, message):
    for variant in (dict(skip={name}), dict(rename_at=name)):
        (tree / "reverse/functions.csv").write_text(ledger_rows(**variant))
        git(tree, "add", "-A")
        ctx, _ = context(tree)
        with pytest.raises(Refusal, match=message):
            plan(ctx)


def test_the_writers_store_must_be_inside_its_row(tree):
    (tree / "reverse/functions.csv").write_text(ledger_rows(writer_size=0x157D06 - 0x157C70 + 5))
    git(tree, "add", "-A")
    ctx, _ = context(tree)
    with pytest.raises(Refusal, match="outside ..1Render2DSentenceClass"):
        plan(ctx)


def test_the_operands_must_be_inside_the_copys_row(tree):
    path = tree / "reverse/functions.csv"
    path.write_text(path.read_text().replace(f"{OLD_COPY},,0x{COPY:08X},384,", f"{OLD_COPY},,0x{COPY:08X},300,"))
    git(tree, "add", "-A")
    ctx, _ = context(tree)
    with pytest.raises(Refusal, match="is outside"):
        plan(ctx)


def test_the_request_may_not_add_rows_or_change_the_evidence(tree):
    ctx, _ = context(tree)
    with pytest.raises(Refusal, match="--evidence must name the proof"):
        plan(ctx, evidence="retail:0x00000001 calls=0x00000002")
    with pytest.raises(Refusal, match="no --old, no --also"):
        plan(ctx, also=[(0x00001000, "?x@@YAXXZ")])
    with pytest.raises(Refusal, match="--prepared"):
        plan(ctx, prepared=None)


def test_another_spelling_is_no_family(tree):
    ctx, _ = context(tree)
    other = NEW_COPY.replace("RendererDataStruct@Render2DSentenceClass", "AddInfoStruct@MixFileFactoryClass")
    with pytest.raises(Refusal, match="proves only the families"):
        plan(ctx, new=other)


# ------------------------------------------------------------------ the rebuilt objects

def test_the_landing_writes_it_all(tree):
    ctx, state = context(tree)
    land(ctx, plan(ctx), state)
    text = (tree / "reverse/functions.csv").read_text()
    assert NEW_COPY in text and OLD_COPY not in text


@pytest.mark.parametrize("label, change", [
    ("no relocations", lambda relocs: []),
    ("the dtor push shifted", lambda relocs: [(o + 1, k, t) if k == rename.DIR32 else (o, k, t) for o, k, t in relocs]),
    ("the old element's destructor",
     lambda relocs: [(o, k, "??1_ENUM_VALUE@EnumParameterClass@@QAE@XZ" if k == rename.DIR32 else t) for o, k, t in relocs]),
    ("a call to another iterator",
     lambda relocs: [(o, k, "??_M@YGXPAXIHP6EX0@Z@Z" if t == "??_L@YGXPAXIHP6EX0@Z1@Z" else t) for o, k, t in relocs]),
    ("one push missing", lambda relocs: relocs[1:]),
])
def test_a_rebuilt_copy_not_binding_the_element_is_undone(tree, label, change):
    ctx, state = context(tree)
    with pytest.raises(VerifyFailed, match="does not bind"):
        land(ctx, plan(ctx), state, relocs={NEW_COPY: change(GOOD_RELOCS[NEW_COPY])})
    assert OLD_COPY in (tree / "reverse/functions.csv").read_text()


def test_an_unreadable_rebuilt_copy_is_undone(tree):
    ctx, state = context(tree)
    ctx.object_symbol_relocs = lambda source, name: None
    with pytest.raises(VerifyFailed, match="cannot be read"):
        land(ctx, plan(ctx), state)


def test_a_row_with_no_references_is_undone(tree):
    ctx, state = context(tree)
    with pytest.raises(VerifyFailed, match="has no references"):
        land(ctx, plan(ctx), state, refs=after_refs()[:1])


def test_a_new_wrong_binding_is_undone(tree):
    ctx, state = context(tree)
    wrong = dict(source=UNIT, row=NEW_COPY, rva=COPY, symbol="x", target=0x1234, cls=next(iter(allowed_symbols.WRONG)))
    with pytest.raises(VerifyFailed, match="gains a wrong binding"):
        land(ctx, plan(ctx), state, refs=after_refs() + [wrong])


def test_empty_operands_are_a_problem(tmp_path):
    identity = dict(rows=[], sources=[], wrong_before=[], operands=[])
    ctx = rename.Context(tmp_path, object_scan=False)
    ctx.identity_refs = lambda sources: []
    assert any("no operands" in p for p in rename.retail_identity_problems(ctx, identity))


def test_the_other_kinds_keep_their_checks(tmp_path):
    """A table family still needs its table store and a body family its bindings: the new branch takes neither."""
    ctx = rename.Context(tmp_path, object_scan=False)
    ctx.identity_refs = lambda sources: []
    ctx.object_symbol_relocs = lambda source, name: []
    table = dict(rows=[], sources=[], wrong_before=[], copy_name="c", copy_source="s", copy_store=0x10, table_name="t")
    assert any("does not store" in p for p in rename.retail_identity_problems(ctx, table))
    body = dict(rows=[], sources=[], wrong_before=[], bindings=[])
    assert any("no bindings" in p for p in rename.retail_identity_problems(ctx, body))
