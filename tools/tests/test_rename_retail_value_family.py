"""`tools/rename.py function --respell --identity --basis retail` on a stand-in value family
(tools/retail_identity.py StandInValueFamily): the real entry is the fixture, its facts served from an image the test
writes. The map's insert helpers were rowed on a builtin value (void*) where retail's value is the size-only struct its
own node creator is rowed on, so no class proves it: retail's node size does, in a member every row reaches by calls,
and each spelling swaps the builtin value for the struct and nothing else. A pin of the old spelling on a member's
address is retired; a caller outside the family keeps its name and must bind the respelled row."""
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

F = R.MAP_UINT_RECORD_INSERT
COPY = F.copy
OLD_COPY = F.rows[COPY][0]
NEW_COPY = F.respell(OLD_COPY)
OLD_UNIQUE = F.rows[0x00534827][0]
OLD_PIN = F.retired[0x0053479F][0]
CALLER = F.callers[0x00534A2A][0]
SOURCES = {0x00534A0D: "Code/Lib/InsertHint.cpp", 0x00534827: "Code/Lib/Insert.cpp", 0x005348E7: "Code/Lib/Lower.cpp"}
CALLER_SOURCE = "Code/Lib/Subscript.cpp"
MEMBER_SOURCE = "Code/Lib/Record.cpp"
SIZES = {0x00534A0D: 29, 0x005348E7: 294, 0x00534827: 134, 0x0053479F: 136, 0x00534743: 34, 0x00534A2A: 132}
PREPARED = {src: f"// {src} on the record value\n".encode()
            for src in sorted(set(SOURCES.values()) | {CALLER_SOURCE})}


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
    entries += [(name, at, MEMBER_SOURCE) for at, name in sorted(F.members.items())]
    entries += [(CALLER, 0x00534A2A, CALLER_SOURCE)]
    for name, at, source in entries:
        if name in skip:
            continue
        size = (resize or {}).get(name, SIZES[at])
        rows.append(f"{name},,0x{at:08X},{size},{source},matched,row\n")
    rows += list(extra)
    return "".join(rows)


def seed(root, files):
    for rel, text in files.items():
        write(root / rel, text)
    git(root, "init", "-q")
    git(root, "add", "-A")
    git(root, "-c", "user.email=t@t", "-c", "user.name=t", "commit", "-q", "-m", "seed")
    return root


def files(registered=(), identity="", dup_defs=""):
    out = {
        "reverse/functions.csv": ledger_rows(),
        "reverse/symbols.csv": f"name,address,notes\n{OLD_PIN},0x0053479F,ICF twin\n",
        "reverse/deleted_rows.csv": "name,target_rva,reason\n",
        "reverse/name_basis.csv": "kind,old,new,basis,evidence,source,rva\n",
        "reverse/data_rows.csv": "name,address,address_kind,size,section,source,status,evidence,model\n",
        "reverse/exports.csv": "ordinal,rva,target_rva,section,kind,name\n",
        "reverse/gate_baseline.txt": "",
        "reverse/code_identity_baseline.tsv": "# wrong bindings\n" + identity,
        "reverse/dup_defs_baseline.tsv": "# divergent COMDATs\n" + dup_defs,
        "reverse/tu_map.csv": "rva,size,kind,tu,confidence,by,evidence,source\n",
        "reverse/data_ledger.csv": "address,size,section,kind,name,source,status,names,defs,refs\n",
        "reverse/canonical_classes.csv": "class,header,notes\n" + "".join(f"{c},Code/Lib/{c}.h,registered\n" for c in registered),
        MEMBER_SOURCE: "// the record map's own rows\n",
    }
    for src in set(SOURCES.values()) | {CALLER_SOURCE}:
        out[src] = "// void* value\n"
    return out


@pytest.fixture
def tree(tmp_path, image):
    return seed(tmp_path, files())


OLD_OF = {new: old for old, new in F.spellings.items()}
GOOD_RELOCS = {}
for _at, _offset, _target in F.bindings:
    GOOD_RELOCS.setdefault(F.respell(F.rows[_at][0]), []).append((_offset, rename.REL32, _target))
for _at, _offset, _target in F.caller_bindings:
    GOOD_RELOCS.setdefault(F.callers[_at][0], []).append((_offset, rename.REL32, _target))


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


PIN_CONSUMERS = rename.pin_consumers


@pytest.fixture(autouse=True)
def objects(monkeypatch):
    monkeypatch.setattr(rename, "pin_consumers", lambda ctx, names, words, rebuilt, groups=(): ([], 0))
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


# The names are long enough that the landing's refusal cuts its first problem short: each undone landing is matched
# on the refusal, and what it found is read whole from the same check.
UNDONE = "the code-identity check does not prove"


def undone(ctx, got, state, refs=None, relocs=None):
    with pytest.raises(VerifyFailed, match=UNDONE):
        land(ctx, got, state, refs=refs, relocs=relocs)
    assert OLD_COPY in (Path(ctx.root) / "reverse/functions.csv").read_text()
    return rename.retail_identity_problems(ctx, got.identity)


# ------------------------------------------------------------------ the entry

def test_the_entry_is_what_the_coordinator_reviewed():
    assert F in R.FAMILIES and isinstance(F, R.StandInValueFamily)
    assert (F.old, F.new, F.key, F.value_size, F.copy) == ("PAX", "Rva00534743Record", "I", 12, 0x00534A0D)
    assert set(F.rows) == {0x00534A0D, 0x005348E7, 0x00534827}
    assert set(F.members) == {0x0053479F, 0x00534743}
    assert set(F.retired) == {0x0053479F} and F.respell(OLD_PIN) == F.members[0x0053479F]
    assert set(F.callers) == {0x00534A2A}
    assert NEW_COPY == ("?insert@?$map@IURva00534743Record@@U?$less@I@_STL@@V?$allocator@U?$pair@$$CBIURva00534743Record"
                        "@@@_STL@@@3@@_STL@@QAE?AU?$_Rb_tree_iterator@U?$pair@$$CBIURva00534743Record@@@_STL@@U?$_Nonconst"
                        "_traits@U?$pair@$$CBIURva00534743Record@@@_STL@@@2@@2@U32@ABU?$pair@$$CBIURva00534743Record@@@2@@Z")
    assert F.node == (0x00534743, R.Fact("alloc", 0x00534746, 0x20, "6a20"))
    assert F.node_call == R.Fact("calls", 0x00534748, 0x000307F0)
    assert all(R.family_of(at, F.respell(old)) is F for at, (old, _f) in F.rows.items())
    assert not F.pins and not F.duplicates


def test_the_real_image_states_them_all():
    if not R.build.EXE.exists():
        pytest.skip("no retail image here")
    assert R.facts_problems(F.facts()) == []


def test_the_swap_is_a_decoded_one():
    """The struct enters the name table, so the back-references renumber: a text substitution would not respell it."""
    assert "@2@@_STL@@QAE" in OLD_COPY and "@3@@_STL@@QAE" in NEW_COPY
    assert OLD_COPY.replace("PAX", "URva00534743Record@@") != NEW_COPY
    key, old = ("B", "I"), R.BUILTIN_VALUES["PAX"][0]
    assert R.value_swap(rename.type_tree(OLD_COPY), key, old, F.new) == rename.type_tree(NEW_COPY)


def test_the_swap_leaves_another_void_pointer():
    """A void* that is no value of the map (a parameter, a pair over another key) stays a void*."""
    key, old = ("B", "I"), R.BUILTIN_VALUES["PAX"][0]
    for name in ("?f@@YAXPAX@Z", "??0?$pair@$$CBHPAX@_STL@@QAE@ABU01@@Z", "??0?$map@HPAXU?$less@H@_STL@@V?$allocator@U?$pair"
                 "@$$CBHPAX@_STL@@@2@@_STL@@QAE@XZ"):
        tree = rename.type_tree(name)
        assert R.value_swap(tree, key, old, F.new) == tree


def kwargs():
    return dict(old=F.old, new=F.new, key=F.key, value_size=F.value_size, copy=F.copy, spellings=dict(F.spellings),
                members=dict(F.members), bindings=tuple(F.bindings), rows=dict(F.rows), retired=dict(F.retired),
                node=F.node, node_call=F.node_call, member_path=tuple(F.member_path), callers=dict(F.callers),
                caller_bindings=tuple(F.caller_bindings))


INT_INSERT = ("?insert@?$map@HURva00534743Record@@U?$less@H@_STL@@V?$allocator@U?$pair@$$CBHURva00534743Record@@@_STL"
              "@@@3@@_STL@@QAE?AU?$_Rb_tree_iterator@U?$pair@$$CBHURva00534743Record@@@_STL@@U?$_Nonconst_traits@U?$"
              "pair@$$CBHURva00534743Record@@@_STL@@@2@@2@U32@ABU?$pair@$$CBHURva00534743Record@@@2@@Z")
INT_NODE = ("?_M_create_node@?$_Rb_tree@HU?$pair@$$CBHURva00534743Record@@@_STL@@U?$_Select1st@U?$pair@$$CBHURva005347"
            "43Record@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHURva00534743Record@@@_STL@@@2@@_STL@@IAEPAU?$"
            "_Rb_tree_node@U?$pair@$$CBHURva00534743Record@@@_STL@@@2@ABU?$pair@$$CBHURva00534743Record@@@2@@Z")
C = R.Fact


@pytest.mark.parametrize("label, change, message", [
    # the node's size: retail's count must be the header and the new pair, and never the old pair's
    ("the old value's node", lambda k: k.update(node=(0x00534743, C("alloc", 0x00534746, 0x18, "6a18"))), "holds 8 bytes"),
    ("another node size", lambda k: k.update(node=(0x00534743, C("alloc", 0x00534746, 0x24, "6a24"))), "holds 20 bytes"),
    ("a value as wide as the old one", lambda k: k.update(value_size=4), "no dword-aligned struct"),
    ("a value of no dword size", lambda k: k.update(value_size=10), "no dword-aligned struct"),
    ("a count that pushes another value", lambda k: k.update(node=(0x00534743, C("alloc", 0x00534746, 0x20, "6a18"))),
     "pushes 24"),
    ("a count that is no push", lambda k: k.update(node=(0x00534743, C("alloc", 0x00534746, 0x20, "b820000000"))),
     "one push of an immediate"),
    ("a count of another kind", lambda k: k.update(node=(0x00534743, C("stride", 0x00534746, 0x20, "6a20"))),
     "must be an alloc fact"),
    ("a count in no member", lambda k: k.update(node=(0x00534A2A, F.node[1])), "in no member"),
    ("a count no call takes", lambda k: k.update(node_call=C("calls", 0x00534749, 0x000307F0)), "feed the call"),
    ("a count taken by a jump", lambda k: k.update(node_call=C("jumps", 0x00534748, 0x000307F0)), "feed the call"),
    # the builtins
    ("another old value", lambda k: k.update(old="PAH"), "no builtin value"),
    ("a signed key", lambda k: k.update(key="H"), "no builtin key"),
    # the spellings
    ("a spelling onto the signed key", lambda k: k["spellings"].update({OLD_COPY: INT_INSERT}), "value swap alone"),
    ("a spelling that changes more than the value",
     lambda k: k["spellings"].update({OLD_COPY: NEW_COPY.replace("QAE", "UAE")}), "value swap alone"),
    ("a spelling left as it was", lambda k: k["spellings"].update({OLD_COPY: OLD_COPY}), "value swap alone"),
    ("a spelling left out", lambda k: k["spellings"].pop(OLD_COPY), "every spelling"),
    ("a spelling no row has", lambda k: k["spellings"].update({"?x@@YAXXZ": "?y@@YAXXZ"}), "every spelling"),
    ("a spelling that does not decode", lambda k: k["spellings"].update({OLD_COPY: NEW_COPY[:-3]}), "cannot be decoded"),
    # the members
    ("a member over another value type", lambda k: k["members"].update({0x00534743: INT_NODE}), "no instantiation"),
    ("no members", lambda k: k.update(members={}), "needs its members"),
    ("a pin retired onto no member", lambda k: k["members"].pop(0x0053479F), "retired only onto the member"),
    ("a pin retired onto another name",
     lambda k: k["members"].update({0x0053479F: F.members[0x00534743]}), "retired only onto the member|no instantiation"),
    # the reach
    ("a row reaching no node",
     lambda k: k["rows"].update({0x00534827: (OLD_UNIQUE, (C("calls", 0x00534889, 0x00001000),))}), "reaches no node"),
    ("no member path", lambda k: k.update(member_path=()), "needs its member path"),
    ("a member path in no member", lambda k: k.update(member_path=((0x00534A2A, F.member_path[0][1]),)),
     "calls in members"),
    ("a member path to another row",
     lambda k: k.update(member_path=((0x0053479F, C("calls", 0x005347C7, 0x00001000)),)), "reaches no node"),
    # the bindings
    ("a binding no call states", lambda k: k.update(bindings=tuple((a, o + 1, t) for a, o, t in F.bindings)),
     "not one of the row of the family's own calls"),
    ("a binding to another target",
     lambda k: k.update(bindings=tuple((a, o, "?other@@YAXXZ" if a == 0x00534827 else t) for a, o, t in F.bindings)),
     "which is not"),
    ("a row with no binding", lambda k: k.update(bindings=tuple(b for b in F.bindings if b[0] != 0x00534827)),
     "every row of the family needs a binding"),
    ("a caller with no binding", lambda k: k.update(caller_bindings=()), "every caller needs a binding"),
    ("a caller binding to a member",
     lambda k: k.update(callers={0x00534A2A: (CALLER, (C("calls", 0x00534A7B, 0x0053479F),))},
                        caller_bindings=((0x00534A2A, 0x52, F.members[0x0053479F]),)), "which is not"),
    ("a caller that is a row", lambda k: k["callers"].update({0x00534827: k["rows"][0x00534827]}), "four different"),
    ("a row that is a retired pin", lambda k: k["retired"].update({0x00534827: k["retired"][0x0053479F]}),
     "retired only onto|four different"),
])
def test_the_constructor_refuses_each_missing_condition(label, change, message):
    k = kwargs()
    change(k)
    with pytest.raises(ValueError, match=message):
        R.StandInValueFamily(**k)


def test_the_real_kwargs_build():
    R.StandInValueFamily(**kwargs())


# ------------------------------------------------------------------ the plan

def test_the_rows_are_respelled_and_the_pin_retired(tree):
    ctx, _ = context(tree)
    got = plan(ctx)
    rows = got.after["reverse/functions.csv"].decode()
    for at, (old, _f) in F.rows.items():
        assert old not in rows and f"{F.respell(old)},,0x{at:08X},{SIZES[at]},{SOURCES[at]},matched" in rows
    assert f"{CALLER},,0x00534A2A" in rows                                       # the caller keeps its name
    assert OLD_PIN not in got.after["reverse/symbols.csv"].decode()
    basis = got.after["reverse/name_basis.csv"].decode()
    assert f"function,{OLD_COPY},{NEW_COPY},retail,{F.evidence()},{SOURCES[COPY]},0x{COPY:08X}" in basis
    assert sum(1 for _line in basis.splitlines()[1:]) == len(F.rows)
    assert got.identity["retired"] == [(OLD_PIN, 0x0053479F, F.members[0x0053479F])]
    bound = got.identity["bindings"]
    assert len(bound) == len(F.bindings) + len(F.caller_bindings)
    assert (CALLER_SOURCE, CALLER, 0x52, NEW_COPY) in bound


def test_each_byte_of_each_fact_refuses(tree, image):
    ctx, _ = context(tree)
    for fact in F.facts():
        for i in range(len(R.expected(fact))):
            keep = image[fact.site + i]
            image[fact.site + i] = keep ^ 0xFF
            with pytest.raises(Refusal, match="retail does not state"):
                plan(ctx)
            image[fact.site + i] = keep


def test_a_registered_value_refuses(tmp_path, image):
    ctx, _ = context(seed(tmp_path, files(registered=[F.new])))
    with pytest.raises(Refusal, match="is registered"):
        plan(ctx)


def test_a_value_with_a_constructor_refuses(tree):
    (tree / "reverse/functions.csv").write_text(ledger_rows(
        extra=[f"??0{F.new}@@QAE@XZ,,0x00001000,8,{MEMBER_SOURCE},matched,ctor\n"]))
    git(tree, "add", "-A")
    ctx, _ = context(tree)
    with pytest.raises(Refusal, match="constructor or destructor row of its own"):
        plan(ctx)


@pytest.mark.parametrize("at", sorted(F.members))
def test_each_member_must_be_rowed(tree, at):
    (tree / "reverse/functions.csv").write_text(ledger_rows(skip={F.members[at]}))
    git(tree, "add", "-A")
    ctx, _ = context(tree)
    with pytest.raises(Refusal, match="is not rowed at"):
        plan(ctx)


def test_the_caller_must_be_rowed(tree):
    (tree / "reverse/functions.csv").write_text(ledger_rows(skip={CALLER}))
    git(tree, "add", "-A")
    ctx, _ = context(tree)
    with pytest.raises(Refusal, match="caller .* is not the one matched row"):
        plan(ctx)


def test_the_caller_must_be_prepared(tree):
    ctx, _ = context(tree)
    prepared = {k: v for k, v in PREPARED.items() if k != CALLER_SOURCE}
    with pytest.raises(Refusal, match="prepare it"):
        plan(ctx, prepared=prepared)


def test_a_fact_outside_its_row_refuses(tree):
    (tree / "reverse/functions.csv").write_text(ledger_rows(resize={OLD_UNIQUE: 0x40}))
    git(tree, "add", "-A")
    ctx, _ = context(tree)
    with pytest.raises(Refusal, match="is outside"):
        plan(ctx)


def test_the_node_outside_its_member_refuses(tree):
    (tree / "reverse/functions.csv").write_text(ledger_rows(resize={F.members[0x00534743]: 4}))
    git(tree, "add", "-A")
    ctx, _ = context(tree)
    with pytest.raises(Refusal, match="in no matched row at 0x00534743"):
        plan(ctx)


def test_a_member_fact_is_held_to_the_members_own_row(tree):
    """A row of another name at the member's address lends the node no extent."""
    (tree / "reverse/functions.csv").write_text(ledger_rows(
        resize={F.members[0x00534743]: 4}, extra=[f"?other@@YAXXZ,,0x00534743,34,Code/Lib/Other.cpp,matched,fold\n"]))
    git(tree, "add", "-A")
    ctx, _ = context(tree)
    with pytest.raises(Refusal, match="in no matched row at 0x00534743"):
        plan(ctx)


def test_the_retired_pins_fact_must_lie_in_a_row(tree, image, monkeypatch):
    """A call retail does make, but from no row or caller of the family, proves nothing about the pin."""
    fact = C("calls", 0x00002000, 0x0053479F)
    for i, byte in enumerate(R.expected(fact)):
        image[fact.site + i] = byte
    monkeypatch.setattr(F, "retired", {0x0053479F: (OLD_PIN, (fact,))})
    ctx, _ = context(tree)
    with pytest.raises(Refusal, match="a fact of the retired pin"):
        plan(ctx)


def test_the_pin_must_be_there(tmp_path, image):
    root = seed(tmp_path, {**files(), "reverse/symbols.csv": "name,address,notes\n"})
    ctx, _ = context(root)
    with pytest.raises(Refusal, match="is not at 0x0053479F"):
        plan(ctx)


def test_the_debt_the_respell_fixes_is_carried_and_named(tmp_path, image):
    """The rows' wrong bindings and the old spelling's divergent COMDAT are the defect: the plan carries them and
    names their retirement for the next commit."""
    identity = f"{SOURCES[0x00534827]}\t{OLD_UNIQUE}\t{OLD_PIN}\t0x0053479F\twrong\n"
    root = seed(tmp_path, files(identity=identity, dup_defs=f"divergent\t{OLD_UNIQUE}\n"))
    ctx, _ = context(root)
    got = plan(ctx)
    assert any("retire identity " + SOURCES[0x00534827] in w for w in got.warnings)
    assert any("dup_defs_baseline.tsv keys" in w for w in got.warnings)


def test_a_key_in_any_other_register_still_refuses(tmp_path, image):
    """Only the wrong-binding and divergent-COMDAT keys are carried: a gate baseline line is a check's debt."""
    root = seed(tmp_path, {**files(), "reverse/gate_baseline.txt": f"bytes {OLD_UNIQUE}\n"})
    ctx, _ = context(root)
    with pytest.raises(Refusal, match="is a key in reverse/gate_baseline.txt"):
        plan(ctx)


# ------------------------------------------------------------------ the pin's consumers (review round 1)

CONSUMER = "Code/Lib/Consumer.cpp"
DECLARES = ("#include <map>\n"
            "typedef std::_Rb_tree<unsigned int, std::pair<const unsigned int, void *>, Select, Less, Alloc> Tree;\n"
            "template <> Tree::iterator Tree::_M_insert(Base *, Base *, const Tree::value_type &, Base *);\n")


def consumers_tree(tmp_path, extra):
    return seed(tmp_path, {**files(), **extra})


def real_consumers(monkeypatch, stale, rebuilds):
    """pin_consumers itself, over a fake link inventory: `stale` units' objects are not current until rebuilt, and
    `rebuilds` says whether ./build.sh brings them current. Returns the units ./build.sh was asked to rebuild."""
    asked, done = [], set()
    monkeypatch.setattr(rename, "pin_consumers", PIN_CONSUMERS)
    monkeypatch.setattr(rename, "link_objects", lambda ctx: {s: [f"/obj/{s}.obj"] for s in
                                                            [*SOURCES.values(), CALLER_SOURCE, MEMBER_SOURCE, *stale]})
    monkeypatch.setattr(rename, "object_is_current", lambda ctx, source, path: source not in stale or source in done)

    def rebuild(ctx, sources):
        asked.extend(sources)
        if rebuilds:
            done.update(sources)
        return rebuilds
    monkeypatch.setattr(rename, "rebuild_sources", rebuild)
    return asked


def test_the_family_names_its_consumers_by_source_terms():
    assert F.consumer_terms == (("_M_insert", "void"),)


def test_a_stale_consumer_declaring_the_pin_in_ordinary_cpp_is_rebuilt_first(tmp_path, image, monkeypatch):
    """No mangled text: the declaration spells the identifier and the value's word, so its stale object is not read
    as clean until ./build.sh brings it current."""
    root = consumers_tree(tmp_path, {CONSUMER: DECLARES})
    asked = real_consumers(monkeypatch, stale={CONSUMER}, rebuilds=False)
    ctx, _ = context(root)
    with pytest.raises(Refusal, match="could not rebuild the stale object.*/Consumer.cpp"):
        plan(ctx)
    assert asked == [CONSUMER]


def test_a_rebuilt_consumer_is_then_read(tmp_path, image, monkeypatch):
    root = consumers_tree(tmp_path, {CONSUMER: DECLARES})
    asked = real_consumers(monkeypatch, stale={CONSUMER}, rebuilds=True)
    ctx, _ = context(root)
    plan(ctx)
    assert asked == [CONSUMER]


def test_a_consumer_declaring_through_a_header_is_found(tmp_path, image, monkeypatch):
    """The typedef and the declaration live in a header; the unit only includes it."""
    root = consumers_tree(tmp_path, {"Code/Lib/TreeDecl.h": DECLARES, CONSUMER: '#include "TreeDecl.h"\nint f();\n'})
    asked = real_consumers(monkeypatch, stale={CONSUMER}, rebuilds=False)
    ctx, _ = context(root)
    with pytest.raises(Refusal, match="could not rebuild"):
        plan(ctx)
    assert asked == [CONSUMER]


@pytest.mark.parametrize("text", ["void f(void *p);\n", "int g() { return _M_insert_count; }\n"])
def test_a_unit_spelling_only_one_term_is_no_consumer(tmp_path, image, monkeypatch, text):
    root = consumers_tree(tmp_path, {CONSUMER: text})
    asked = real_consumers(monkeypatch, stale={CONSUMER}, rebuilds=False)
    ctx, _ = context(root)
    plan(ctx)
    assert asked == []


def test_a_unit_still_spelling_an_old_name_refuses(tree):
    write(tree / "Code/Lib/Elsewhere.cpp", f"// {OLD_PIN}\n")
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
        plan(ctx, new=INT_INSERT)


# ------------------------------------------------------------------ the rebuilt objects

def test_the_landing_writes_it_all(tree):
    ctx, state = context(tree)
    land(ctx, plan(ctx), state)
    text = (tree / "reverse/functions.csv").read_text()
    assert NEW_COPY in text and OLD_COPY not in text
    assert OLD_PIN not in (tree / "reverse/symbols.csv").read_text()


@pytest.mark.parametrize("label, change", [
    ("no relocation at all", lambda relocs: []),
    ("another offset", lambda relocs: [(o + 1, k, t) for o, k, t in relocs]),
    ("another type", lambda relocs: [(o, rename.DIR32, t) for o, k, t in relocs]),
    ("the old value's callee", lambda relocs: [(o, k, OLD_OF.get(t, t)) for o, k, t in relocs]),
])
def test_a_rebuilt_row_or_caller_not_binding_its_target_is_undone(tree, label, change):
    for name in [F.respell(old) for old, _f in F.rows.values()] + [CALLER]:
        ctx, state = context(tree)
        found = undone(ctx, plan(ctx), state, relocs={**GOOD_RELOCS, name: change(GOOD_RELOCS[name])})
        assert any(p.startswith(f"{name} does not bind") for p in found), found


def test_a_rebuilt_object_binding_the_retired_pin_is_undone(tree):
    ctx, state = context(tree)
    still = dict(source=SOURCES[0x00534827], row=F.respell(OLD_UNIQUE), rva=0x00534827, symbol=OLD_PIN,
                 target=0x0053479F, cls="owner")
    found = undone(ctx, plan(ctx), state, refs=after_refs() + [still])
    assert any("still binds the retired pin" in p for p in found), found


def test_a_row_with_no_references_is_undone(tree):
    ctx, state = context(tree)
    found = undone(ctx, plan(ctx), state, refs=after_refs()[:1])
    assert any("has no references" in p for p in found), found


def test_a_new_wrong_binding_is_undone(tree):
    ctx, state = context(tree)
    wrong = dict(source=SOURCES[COPY], row=NEW_COPY, rva=COPY, symbol="x", target=0x1234,
                 cls=next(iter(allowed_symbols.WRONG)))
    found = undone(ctx, plan(ctx), state, refs=after_refs() + [wrong])
    assert any("gains a wrong binding" in p for p in found), found
