"""`tools/rename.py function --respell --identity --basis retail` on a stand-in scalar key family
(tools/retail_identity.py StandInScalarKeyFamily): the real entry is the fixture, its facts served from an image the
test writes. The stand-in is a struct the map was rowed on where retail's key is a builtin, so no class proves it:
retail's copy of the key (width) and its compare (signedness) do, in members reached from the family's own rows, and
each spelling swaps the struct for the builtin and nothing else."""
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

F = R.MAP_UINT_INT_COPY
COPY = F.copy
OLD_COPY = F.rows[COPY][0]
NEW_COPY = F.respell(OLD_COPY)
EH = "__ehhandler$" + OLD_COPY
W5 = "Code/Lib/StlSweepW5.cpp"
SOURCES = {0x00534581: W5, 0x0053462F: W5, 0x005346BC: "Code/Lib/PairCopy.cpp"}
SIZES = {0x00534581: 165, 0x0053462F: 18, 0x005346BC: 29, 0x00382B7F: 34, 0x0060C9D9: 23, 0x004FF3B6: 37,
         0x005344C8: 115, 0x0053444F: 30, 0x00534A2A: 132, 0x0021983A: 7, 0x001F0534: 36, 0x0014F3C4: 11}
# the rows a path or a pin's fact lies in, under whatever names the ledger gives them
OTHER_ROWS = {0x005344C8: "?_M_copy_005344C8@x", 0x0053444F: "?_M_clone_node@x", 0x00534A2A: "?subscript@x",
              0x0021983A: "?get_allocator@x", 0x001F0534: "??0?$_Rb_tree_base@x", 0x0014F3C4: "??0?$_STLP_alloc_proxy@x"}
PREPARED = {src: f"// {src} on the builtin key\n".encode() for src in sorted(set(SOURCES.values()))}


def write(path, text):
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_bytes(text.encode("utf-8"))


def git(root, *args):
    subprocess.run(["git", "-C", str(root), *args], check=True, capture_output=True)


@pytest.fixture
def image(monkeypatch):
    bytes_at = {}
    for fact in F.facts():
        for i, byte in enumerate(R.expected(fact)):
            bytes_at[fact.site + i] = byte

    def read(rva, size):
        return bytes(bytes_at[rva + i] for i in range(size))
    monkeypatch.setattr(R, "read_retail", read)
    return bytes_at


def ledger_rows(skip=(), resize=None, extra=()):
    rows = ["name,export_rva,target_rva,target_size,source,status,notes\n"]
    entries = [(old, at, SOURCES[at]) for at, (old, _f) in sorted(F.rows.items())]
    entries += [(name, at, "Code/Lib/PathDoXfer.cpp") for at, name in sorted(F.members.items())]
    entries += [(name, at, "Code/Lib/Other.cpp") for at, name in sorted(OTHER_ROWS.items())]
    for name, at, source in entries:
        if name in skip:
            continue
        size = (resize or {}).get(name, SIZES[at])
        rows.append(f"{name},,0x{at:08X},{size},{source},matched,row\n")
    rows.append(f"{EH},,0x0079741C,10,{W5},matched,funclet\n")
    rows += list(extra)
    return "".join(rows)


def seed(root, files):
    for rel, text in files.items():
        write(root / rel, text)
    git(root, "init", "-q")
    git(root, "add", "-A")
    git(root, "-c", "user.email=t@t", "-c", "user.name=t", "commit", "-q", "-m", "seed")
    return root


def files(registered=()):
    pins = ["name,address,notes\n"] + [f"{old},0x{at:08X},sweep\n" for at, (old, _f) in sorted(F.pins.items())]
    out = {
        "reverse/functions.csv": ledger_rows(),
        "reverse/symbols.csv": "".join(pins),
        "reverse/deleted_rows.csv": "name,target_rva,reason\n",
        "reverse/name_basis.csv": "kind,old,new,basis,evidence,source,rva\n",
        "reverse/data_rows.csv": "name,address,address_kind,size,section,source,status,evidence,model\n",
        "reverse/exports.csv": "ordinal,rva,target_rva,section,kind,name\n",
        "reverse/gate_baseline.txt": "",
        "reverse/tu_map.csv": "rva,size,kind,tu,confidence,by,evidence,source\n",
        "reverse/data_ledger.csv": "address,size,section,kind,name,source,status,names,defs,refs\n",
        "reverse/canonical_classes.csv": "class,header,notes\n" + "".join(f"{c},Code/Lib/{c}.h,registered\n" for c in registered),
        "Code/Lib/PathDoXfer.cpp": "// the map's own rows\n",
        "Code/Lib/Other.cpp": "// rows of the path\n",
    }
    for src in set(SOURCES.values()):
        out[src] = "// stand-in\n"
    return out


@pytest.fixture
def tree(tmp_path, image):
    return seed(tmp_path, files())


OLD_OF = {new: old for old, new in F.spellings.items()}
GOOD_RELOCS = {}
for _at, _offset, _target in F.bindings:
    GOOD_RELOCS.setdefault(F.respell(F.rows[_at][0]), []).append((_offset, rename.REL32, _target))


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


@pytest.fixture(autouse=True)
def objects(monkeypatch):
    monkeypatch.setattr(rename, "pin_consumers", lambda ctx, names, words, rebuilt: ([], 0))
    monkeypatch.setattr(rename, "object_pin_references", lambda objects, names: [])
    monkeypatch.setattr(rename, "source_objects", lambda ctx, sources: {})


def after_refs():
    return [dict(source=SOURCES[at], row=F.respell(old), rva=at, symbol="x", target=0x1234, cls="owner")
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
    assert F in R.FAMILIES and isinstance(F, R.StandInScalarKeyFamily)
    assert (F.old, F.new, F.code, F.copy) == ("Rva00534581Element", "unsigned int", "I", 0x00534581)
    assert set(F.rows) == {0x00534581, 0x0053462F, 0x005346BC}
    assert set(F.pins) == {0x0021983A, 0x001F0534, 0x005344C8, 0x0014F3C4}
    assert set(F.members) == {0x00382B7F, 0x0060C9D9, 0x004FF3B6}
    assert NEW_COPY == ("??0?$_Rb_tree@IU?$pair@$$CBIH@_STL@@U?$_Select1st@U?$pair@$$CBIH@_STL@@@2@U?$less@I@2@V?$"
                        "allocator@U?$pair@$$CBIH@_STL@@@2@@_STL@@QAE@ABV01@@Z")
    assert F.value_type == ("T", "pair", (("CV", "$$CB", ("B", "I")), ("B", "H")))
    assert F.key_copy[1] == R.Fact("copy", 0x0060C9E5, 4, "8b118910")
    assert F.key_compare[1] == R.Fact("compare", 0x00534A4D, 0x10, "3b46107348")
    assert all(R.family_of(at, F.respell(old)) is F for at, (old, _f) in F.rows.items())
    assert not F.duplicates and not F.retired


def test_the_real_image_states_them_all():
    if not R.build.EXE.exists():
        pytest.skip("no retail image here")
    assert R.facts_problems(F.facts()) == []


def test_the_swap_is_a_decoded_one():
    """Back-references renumber when the struct leaves the name table: a text substitution would not respell it."""
    assert "@3@" in OLD_COPY and "@3@" not in NEW_COPY
    assert OLD_COPY.replace("URva00534581Element@@", "I") != NEW_COPY
    assert R.scalar_swap(rename.type_tree(OLD_COPY), F.old, F.code) == rename.type_tree(NEW_COPY)


def kwargs():
    return dict(old=F.old, new=F.new, code=F.code, copy=F.copy, spellings=dict(F.spellings), members=dict(F.members),
                bindings=tuple(F.bindings), rows=dict(F.rows), pins=dict(F.pins), key_copy=F.key_copy,
                copy_path=tuple(F.copy_path), key_compare=F.key_compare, compare_path=tuple(F.compare_path))


SIGNED_COPY = ("??0?$_Rb_tree@HU?$pair@$$CBHH@_STL@@U?$_Select1st@U?$pair@$$CBHH@_STL@@@2@U?$less@H@2@V?$"
               "allocator@U?$pair@$$CBHH@_STL@@@2@@_STL@@QAE@ABV01@@Z")
INT_CONSTRUCT = "??$_Construct@U?$pair@$$CBHH@_STL@@U12@@_STL@@YAXPAU?$pair@$$CBHH@0@ABU10@@Z"
C = R.Fact


@pytest.mark.parametrize("label, change, message", [
    # the key's signedness: a compare that branches signed (jle) proves no unsigned key
    ("a signed compare", lambda k: k.update(key_compare=(0x00534A2A, C("compare", 0x00534A4D, 0x10, "3b46107e48"))),
     "signedness"),
    ("a signed key", lambda k: k.update(code="H"), "no builtin key"),
    ("a spelling onto the signed key", lambda k: k["spellings"].update({OLD_COPY: SIGNED_COPY}), "scalar swap alone"),
    # the key's width: a word copy (66 prefix) is the stand-in's, not retail's
    ("a word copy", lambda k: k.update(key_copy=(0x0060C9D9, C("copy", 0x0060C9E5, 4, "668b11668910"))), "moves"),
    ("a byte copy", lambda k: k.update(key_copy=(0x0060C9D9, C("copy", 0x0060C9E5, 4, "8a118810"))), "moves"),
    ("a copy of another width", lambda k: k.update(key_copy=(0x0060C9D9, C("copy", 0x0060C9E5, 2, "8b118910"))), "moves"),
    ("a copy through two registers", lambda k: k.update(key_copy=(0x0060C9D9, C("copy", 0x0060C9E5, 4, "8b118908"))),
     "store that register"),
    ("a copy that is no load and store", lambda k: k.update(key_copy=(0x0060C9D9, C("copy", 0x0060C9E5, 4, "8b114090"))),
     "one mov load"),
    ("a word compare", lambda k: k.update(key_compare=(0x00534A2A, C("compare", 0x00534A4D, 0x10, "663b46107348"))),
     "compare 4 bytes"),
    ("a compare of another field", lambda k: k.update(key_compare=(0x00534A2A, C("compare", 0x00534A4D, 0x14, "3b46107348"))),
     "compare 4 bytes"),
    ("a key fact of another kind", lambda k: k.update(key_copy=(0x0060C9D9, C("offset", 0x0060C9E5, 4, "8b118910"))),
     "must be a copy fact"),
    # the callees: a member over another value type, a path call to another row, a compare that reaches no member
    ("a member over another value type", lambda k: k["members"].update({0x0060C9D9: INT_CONSTRUCT}),
     "no instantiation over the copy's value type"),
    ("a path call to another row",
     lambda k: k.update(copy_path=(k["copy_path"][0], (0x005344C8, C("calls", 0x005344D5, 0x00001000)),
                                   *k["copy_path"][2:])), "does not call"),
    ("a path from another row", lambda k: k.update(copy_path=k["copy_path"][1:]), "starts in the family's copy"),
    ("a key copy in no member", lambda k: k["members"].pop(0x0060C9D9), "in no member|does not call"),
    ("a compare that reaches no member",
     lambda k: k.update(compare_path=tuple(p for p in k["compare_path"] if p[1].value != 0x004FF3B6)),
     "reach a row of the family and a member"),
    ("a compare that reaches no row",
     lambda k: k.update(compare_path=tuple(p for p in k["compare_path"] if p[1].value != 0x005346BC)),
     "reach a row of the family and a member"),
    ("a compare path in another row",
     lambda k: k.update(compare_path=((0x00534A2B, k["compare_path"][0][1]), *k["compare_path"][1:])),
     "compare's own row"),
    # the spellings
    ("a spelling that changes more than the key",
     lambda k: k["spellings"].update({OLD_COPY: NEW_COPY.replace("QAE", "UAE")}), "scalar swap alone"),
    ("a spelling left out", lambda k: k["spellings"].pop(OLD_COPY), "every spelling"),
    ("a spelling no row has", lambda k: k["spellings"].update({"?x@@YAXXZ": "?y@@YAXXZ"}), "every spelling"),
    ("a spelling that does not decode", lambda k: k["spellings"].update({OLD_COPY: NEW_COPY[:-3]}), "cannot be decoded"),
    ("a row that does not spell the stand-in",
     lambda k: (k["rows"].update({0x00001000: ("?other@@YAXXZ", (C("calls", 0x00001001, 0x00534581),))}),
                k["spellings"].update({"?other@@YAXXZ": "?other2@@YAXXZ"})), "does not spell the stand-in"),
    # the rows
    ("a row reaching nothing",
     lambda k: k["rows"].update({0x0053462F: (k["rows"][0x0053462F][0], (C("calls", 0x00534636, 0x00001000),))}),
     "reaches no member"),
    ("a binding no call states", lambda k: k.update(bindings=tuple((a, o + 1, t) for a, o, t in F.bindings)),
     "not one of the row's own calls"),
    ("a binding to another target",
     lambda k: k.update(bindings=tuple((a, o, "?other@@YAXXZ" if a == 0x0053462F else t) for a, o, t in F.bindings)),
     "which is not"),
    ("a row with no binding", lambda k: k.update(bindings=tuple(b for b in F.bindings if b[0] != 0x005346BC)),
     "every row needs a binding"),
    ("no members", lambda k: k.update(members={}), "needs its members"),
    ("no compare path", lambda k: k.update(compare_path=()), "needs its compare path"),
])
def test_the_constructor_refuses_each_missing_condition(label, change, message):
    k = kwargs()
    change(k)
    with pytest.raises(ValueError, match=message):
        R.StandInScalarKeyFamily(**k)


def test_the_real_kwargs_build():
    R.StandInScalarKeyFamily(**kwargs())


# ------------------------------------------------------------------ the plan

def test_the_rows_and_pins_are_respelled(tree):
    ctx, _ = context(tree)
    got = plan(ctx)
    rows = got.after["reverse/functions.csv"].decode()
    for at, (old, _f) in F.rows.items():
        assert old not in rows and f"{F.respell(old)},,0x{at:08X},{SIZES[at]},{SOURCES[at]},matched" in rows
    assert f"__ehhandler${NEW_COPY},,0x0079741C,10,{W5},matched" in rows       # the funclet follows its parent
    pins = got.after["reverse/symbols.csv"].decode()
    for at, (old, _f) in F.pins.items():
        assert old not in pins and f"{F.respell(old)},0x{at:08X}" in pins
    basis = got.after["reverse/name_basis.csv"].decode()
    assert f"function,{OLD_COPY},{NEW_COPY},retail,{F.evidence()},{W5},0x{COPY:08X}" in basis
    assert sum(1 for line in basis.splitlines()[1:]) == len(F.rows)
    assert OLD_COPY in got.after["reverse/deleted_rows.csv"].decode()
    assert len(got.identity["bindings"]) == len(F.bindings) and not got.identity["retired"]
    assert "duplicates" not in got.identity


def test_each_byte_of_each_fact_refuses(tree, image):
    ctx, _ = context(tree)
    for fact in F.facts():
        for i in range(len(R.expected(fact))):
            keep = image[fact.site + i]
            image[fact.site + i] = keep ^ 0xFF
            with pytest.raises(Refusal, match="retail does not state"):
                plan(ctx)
            image[fact.site + i] = keep


def test_a_registered_stand_in_refuses(tmp_path, image):
    ctx, _ = context(seed(tmp_path, files(registered=[F.old])))
    with pytest.raises(Refusal, match="is registered"):
        plan(ctx)


def test_a_stand_in_with_a_constructor_refuses(tree):
    (tree / "reverse/functions.csv").write_text(ledger_rows(extra=[f"??0{F.old}@@QAE@XZ,,0x00001000,8,{W5},matched,ctor\n"]))
    git(tree, "add", "-A")
    ctx, _ = context(tree)
    with pytest.raises(Refusal, match="constructor or destructor row of its own"):
        plan(ctx)


@pytest.mark.parametrize("at", sorted(F.members))
def test_each_member_must_be_rowed(tree, at):
    (tree / "reverse/functions.csv").write_text(ledger_rows(skip={F.members[at]}))
    git(tree, "add", "-A")
    ctx, _ = context(tree)
    with pytest.raises(Refusal, match="is not rowed at|is in no matched row"):
        plan(ctx)


def test_a_fact_outside_its_row_refuses(tree):
    (tree / "reverse/functions.csv").write_text(ledger_rows(resize={OLD_COPY: 80}))
    git(tree, "add", "-A")
    ctx, _ = context(tree)
    with pytest.raises(Refusal, match="is outside"):
        plan(ctx)


@pytest.mark.parametrize("at", [0x005344C8, 0x0053444F, 0x00534A2A])
def test_a_path_fact_in_no_row_refuses(tree, at):
    (tree / "reverse/functions.csv").write_text(ledger_rows(skip={OTHER_ROWS[at]}))
    git(tree, "add", "-A")
    ctx, _ = context(tree)
    with pytest.raises(Refusal, match="is in no matched row"):
        plan(ctx)


def test_the_key_copy_outside_its_member_refuses(tree):
    (tree / "reverse/functions.csv").write_text(ledger_rows(resize={F.members[0x0060C9D9]: 0x0C}))
    git(tree, "add", "-A")
    ctx, _ = context(tree)
    with pytest.raises(Refusal, match="in no matched row at 0x0060C9D9"):
        plan(ctx)


def test_a_pin_fact_in_no_row_refuses(tree):
    """The proxy's fact is the base constructor's call: without the row at that pin it lies nowhere."""
    (tree / "reverse/functions.csv").write_text(ledger_rows(skip={OTHER_ROWS[0x001F0534], OTHER_ROWS[0x0014F3C4]}))
    git(tree, "add", "-A")
    ctx, _ = context(tree)
    with pytest.raises(Refusal, match="in no row of the family or at its pins"):
        plan(ctx)


def test_a_unit_still_spelling_an_old_name_refuses(tree):
    write(tree / "Code/Lib/Elsewhere.cpp", f"// {F.pins[0x005344C8][0]}\n")
    git(tree, "add", "-A")
    ctx, _ = context(tree)
    with pytest.raises(Refusal, match="still spells"):
        plan(ctx)


def test_the_request_may_not_add_rows_or_change_the_evidence(tree):
    ctx, _ = context(tree)
    with pytest.raises(Refusal, match="--evidence must name the proof"):
        plan(ctx, evidence="retail:0x00000001 calls=0x00000002")
    with pytest.raises(Refusal, match="no --old, no --also"):
        plan(ctx, also=[(0x00001000, "?x@@YAXXZ")])
    with pytest.raises(Refusal, match="--prepared"):
        plan(ctx, prepared=None)


def test_the_signed_key_is_no_family(tree):
    ctx, _ = context(tree)
    with pytest.raises(Refusal, match="proves only the families"):
        plan(ctx, new=SIGNED_COPY)


# ------------------------------------------------------------------ the rebuilt objects

def test_the_landing_writes_it_all(tree):
    ctx, state = context(tree)
    land(ctx, plan(ctx), state)
    text = (tree / "reverse/functions.csv").read_text()
    assert NEW_COPY in text and OLD_COPY not in text


@pytest.mark.parametrize("label, change", [
    ("no relocation at all", lambda relocs: []),
    ("another offset", lambda relocs: [(o + 1, k, t) for o, k, t in relocs]),
    ("another type", lambda relocs: [(o, rename.DIR32, t) for o, k, t in relocs]),
    ("the stand-in's callee", lambda relocs: [(o, k, OLD_OF.get(t, t)) for o, k, t in relocs]),
])
def test_a_rebuilt_row_not_binding_its_target_is_undone(tree, label, change):
    for at in sorted(F.rows):
        name = F.respell(F.rows[at][0])
        ctx, state = context(tree)
        with pytest.raises(VerifyFailed, match="does not bind"):
            land(ctx, plan(ctx), state, relocs={**GOOD_RELOCS, name: change(GOOD_RELOCS[name])})
        assert OLD_COPY in (tree / "reverse/functions.csv").read_text()


def test_a_row_with_no_references_is_undone(tree):
    ctx, state = context(tree)
    with pytest.raises(VerifyFailed, match="has no references"):
        land(ctx, plan(ctx), state, refs=after_refs()[:1])


def test_a_new_wrong_binding_is_undone(tree):
    ctx, state = context(tree)
    wrong = dict(source=W5, row=NEW_COPY, rva=COPY, symbol="x", target=0x1234, cls=next(iter(allowed_symbols.WRONG)))
    with pytest.raises(VerifyFailed, match="gains a wrong binding"):
        land(ctx, plan(ctx), state, refs=after_refs() + [wrong])
