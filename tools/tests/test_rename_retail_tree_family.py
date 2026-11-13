"""`tools/rename.py function --respell --identity --basis retail` on a retyped tree family
(tools/retail_identity.py RetypedTreeFamily): the real entry is the fixture, its facts served from an image the test
writes. A tree's copy chain was rowed on map<unsigned, void*> under less<unsigned> where retail's tree has another key,
comparator and value. They change together, so three kinds of fact must agree: retail's node allocations push the new
pair's size, every row reaches one by calls, and a matched caller outside the family binds a pin at a row's address
that spells the map over exactly the new key, value and comparator. Each spelling is the tree swap and nothing else."""
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

F = R.BIG_MEMBER_MAP_COPY
C = R.Fact
COPY = F.copy
OLD_COPY = F.rows[COPY][0]
NEW_COPY = F.respell(OLD_COPY)
OLD_MAP_COPY = F.rows[0x00603FC0][0]
OLD_MAKE = F.rows[0x00604251][0]
CALLER = F.callers[0x0060426C][0]
WITNESS_AT, WITNESS, WITNESS_CALL, PIN = F.witness
OLD_PIN = F.pins[0x0021983A][0]
NEW_PIN = ("?get_allocator@?$_Rb_tree_base@U?$pair@QBDUBigArchiveMemberInfo@@@_STL@@V?$allocator@U?$pair@QBDUBigArchive"
           "MemberInfo@@@_STL@@@2@@_STL@@QBE?AV?$allocator@U?$pair@QBDUBigArchiveMemberInfo@@@_STL@@@2@XZ")
OLD_PIN_LINE = f"{OLD_PIN},0x0021983A,callee read from the copy\n"
LOWER, BIG = "Code/Lib/Lower.cpp", "Code/Lib/Big.cpp"
SOURCES = {0x00603EEB: LOWER, 0x00603B9C: LOWER, 0x00603FC0: BIG, 0x00603FD2: BIG, 0x00604251: BIG}
CALLER_SOURCE = BIG
WITNESS_SOURCE = "Code/Lib/Witness.cpp"
MEMBER_SOURCE = "Code/Lib/Module.cpp"
NODE_SOURCE = "Code/Lib/Base.cpp"
NODE_NAMES = {0x0030087C: "??0Base@@QAE@XZ", 0x0029E11A: "?create@Base@@QAEPAXXZ"}
SIZES = {0x00603EEB: 165, 0x00603B9C: 115, 0x00603FC0: 18, 0x00603FD2: 29, 0x00604251: 27, 0x0060426C: 29,
         0x006045A2: 270, 0x00413E55: 30, 0x0030087C: 36, 0x0029E11A: 34}
PREPARED = {src: f"// {src} on the member map\n".encode() for src in (LOWER, BIG)}


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
    entries += [(name, at, NODE_SOURCE) for at, name in sorted(NODE_NAMES.items())]
    entries += [(CALLER, 0x0060426C, CALLER_SOURCE), (WITNESS, WITNESS_AT, WITNESS_SOURCE)]
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


def files(identity="", pins=None):
    out = {
        "reverse/functions.csv": ledger_rows(),
        "reverse/symbols.csv": "name,address,notes\n" + (f"{PIN},0x00604251,caller binding\n{OLD_PIN_LINE}"
                                                         if pins is None else pins),
        "reverse/deleted_rows.csv": "name,target_rva,reason\n",
        "reverse/name_basis.csv": "kind,old,new,basis,evidence,source,rva\n",
        "reverse/data_rows.csv": "name,address,address_kind,size,section,source,status,evidence,model\n",
        "reverse/exports.csv": "ordinal,rva,target_rva,section,kind,name\n",
        "reverse/gate_baseline.txt": "",
        "reverse/code_identity_baseline.tsv": "# wrong bindings\n" + identity,
        "reverse/dup_defs_baseline.tsv": "# divergent COMDATs\n",
        "reverse/tu_map.csv": "rva,size,kind,tu,confidence,by,evidence,source\n",
        "reverse/data_ledger.csv": "address,size,section,kind,name,source,status,names,defs,refs\n",
        "reverse/canonical_classes.csv": "class,header,notes\n",
        MEMBER_SOURCE: "// the module tree's clone\n",
        NODE_SOURCE: "// the folded base constructor and node creator\n",
        WITNESS_SOURCE: "// the archive's insert, on the real types\n",
    }
    for src in (LOWER, BIG):
        out[src] = "// pointer-pair tree\n"
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


UNDONE = "the code-identity check does not prove"


def undone(ctx, got, state, refs=None, relocs=None):
    with pytest.raises(VerifyFailed, match=UNDONE):
        land(ctx, got, state, refs=refs, relocs=relocs)
    assert OLD_COPY in (Path(ctx.root) / "reverse/functions.csv").read_text()
    return rename.retail_identity_problems(ctx, got.identity)


# ------------------------------------------------------------------ the entry

def test_the_entry_is_what_the_coordinator_reviewed():
    assert F in R.FAMILIES and isinstance(F, R.RetypedTreeFamily)
    assert (F.old_key, F.old_value, F.new_key, F.new_value, F.new_compare, F.value_size, F.copy) == (
        "I", "PAX", "PBD", "BigArchiveMemberInfo", "Rva006038D4Less", 12, 0x00603EEB)
    assert set(F.rows) == {0x00603EEB, 0x00603B9C, 0x00603FC0, 0x00603FD2, 0x00604251}
    assert set(F.members) == {0x00413E55} and set(F.callers) == {0x0060426C}
    assert [at for at, _alloc, _call in F.nodes] == [0x0030087C, 0x0029E11A]
    assert all(alloc == C("alloc", alloc.site, 0x20, "6a20") for _at, alloc, _call in F.nodes)
    assert (WITNESS_AT, WITNESS_CALL) == (0x006045A2, C("calls", 0x006045FE, 0x00604251))
    assert NEW_COPY == ("??0?$_Rb_tree@PBDU?$pair@QBDUBigArchiveMemberInfo@@@_STL@@U?$_Select1st@U?$pair@QBDUBigArchive"
                        "MemberInfo@@@_STL@@@2@URva006038D4Less@@V?$allocator@U?$pair@QBDUBigArchiveMemberInfo@@@_STL@@"
                        "@2@@_STL@@QAE@ABV01@@Z")
    assert all(R.family_of(at, F.respell(old)) is F for at, (old, _f) in F.rows.items())
    assert set(F.pins) == {0x0021983A} and F.pins[0x0021983A][1] == (C("calls", 0x00603F08, 0x0021983A),)
    assert F.respell(OLD_PIN) == NEW_PIN and F.consumer_terms == (("get_allocator",),)
    assert not F.retired and not F.duplicates
    assert F.key_params == {0x00603FD2: (0,), 0x00604251: (0,)}


def test_the_real_image_states_them_all():
    if not R.build.EXE.exists():
        pytest.skip("no retail image here")
    assert R.facts_problems(F.facts()) == []


PARAMS = {F.rows[at][0]: indices for at, indices in F.key_params.items()}


def swap(name, key_params=()):
    return R.tree_swap(rename.type_tree(name), F.old_key, F.old_value, F.new_key, F.new_value, F.new_compare,
                       key_params=key_params)


def test_the_swap_is_a_decoded_one():
    """The new types enter the name table, so the back-references renumber: no text substitution respells them."""
    for old, new in F.spellings.items():
        assert swap(old, PARAMS.get(old, ())) == rename.type_tree(new)
    assert OLD_COPY.replace("IU?$pair@$$CBIPAX", "PBDU?$pair@QBDUBigArchiveMemberInfo@@") != NEW_COPY


@pytest.mark.parametrize("name", [
    "?f@@YAXI@Z",                                                    # an unsigned passed by value
    "?f@@YAXPAX@Z",                                                  # a void* outside the tree
    "??0?$vector@IV?$allocator@I@_STL@@@_STL@@QAE@XZ",               # another template's unsigned
    "??0?$pair@$$CBHPAX@_STL@@QAE@ABU01@@Z",                         # a pair over another key
    "?f@@YAXPAI@Z",                                                  # a pointer to a non-const unsigned
    "?f@@YAXPBI@Z",                                                  # a const unsigned* nobody named (review 1)
    "??0?$vector@PBIV?$allocator@PBI@_STL@@@_STL@@QAE@XZ",           # vector<const unsigned *> (review 1)
    "?f@@YAXABU?$pair@$$CBIPAX@Unrelated@@@Z",                       # another namespace's pair (review 2)
    "?f@@YAXT?$allocator@U?$pair@$$CBIPAX@_STL@@@_STL@@@Z",                                         # a union spelling of the allocator (review 3)
    "?f@@YAXW4?$allocator@U?$pair@$$CBIPAX@_STL@@@_STL@@@Z",                                        # an enum spelling of it (review 3)
    "?f@@YAXABU?$map@IPAXU?$less@I@_STL@@V?$allocator@U?$pair@$$CBIPAX@_STL@@@2@@_STL@@@Z",   # map as a struct
    "??0?$_Rb_tree_node@U?$pair@$$CBIPAX@_STL@@@_STL@@QAE@XZ",       # a member of a shape that is no scope
    "?f@@YAXABU?$pair@$$CBIPAX@_STL@@@Z",                            # the old pair alone, in no tree
    "??0?$vector@U?$pair@$$CBIPAX@_STL@@V?$allocator@U?$pair@$$CBIPAX@_STL@@@2@@_STL@@QAE@XZ",  # a vector of it
    "??0?$map@IHU?$less@I@_STL@@V?$allocator@U?$pair@$$CBIH@_STL@@@2@@_STL@@QAE@XZ",   # a map over another value
    "??0?$_Rb_tree@IU?$pair@$$CBIH@_STL@@U?$_Select1st@U?$pair@$$CBIH@_STL@@@2@U?$less@I@2@V?$allocator@U?$pair@$$CBIH"
    "@_STL@@@2@@_STL@@QAE@ABV01@@Z",                                 # a tree over another value
])
def test_the_swap_leaves_what_is_no_part_of_the_tree(name):
    assert swap(name) == rename.type_tree(name)


def test_a_key_parameter_is_retyped_only_where_named():
    """Review round 1: the const-key pointer rule applies to the listed parameter positions and no others."""
    tree = rename.type_tree("?f@@YAXPBIPBI@Z")
    once = swap("?f@@YAXPBIPBI@Z", (1,))
    assert once != tree and once == rename.type_tree("?f@@YAXPBIPBQBD@Z")
    assert swap("?f@@YAXPBIPBI@Z", (2,)) == tree                    # past the parameter list: nothing
    assert swap("?f@@YAXIPBI@Z", (0,)) == rename.type_tree("?f@@YAXIPBI@Z")   # a by-value key at that position


# review 4's counterexample: a constructor of a class nested in the tree, and its destructor
NESTED_OLD = "??0Nested@" + OLD_COPY[len("??0"):-len("QAE@ABV01@@Z")] + "QAE@XZ"
NESTED_NEW = "??0Nested@" + NEW_COPY[len("??0"):-len("QAE@ABV01@@Z")] + "QAE@XZ"
NESTED_DTOR = "??1Nested@" + OLD_COPY[len("??0"):-len("QAE@ABV01@@Z")] + "QAE@XZ"
# review 5's counterexample: a free function template named like the tree, _STL::_Rb_tree<...>()
FREE_OLD = "?" + OLD_COPY[len("??0"):-len("QAE@ABV01@@Z")] + "YAXXZ"
FREE_NEW = "?" + NEW_COPY[len("??0"):-len("QAE@ABV01@@Z")] + "YAXXZ"
UNION_OLD = OLD_COPY[:-len("@Z")] + "T?$allocator@U?$pair@$$CBIPAX@_STL@@@_STL@@@Z"                     # review 3's counterexample
UNION_NEW = NEW_COPY[:-len("@Z")] + "T?$allocator@U?$pair@QBDUBigArchiveMemberInfo@@@_STL@@@_STL@@@Z"
UNRELATED_OLD = OLD_COPY[:-len("@Z")] + "ABU?$pair@$$CBIPAX@Unrelated@@@Z"         # review 2's counterexample
UNRELATED_NEW = NEW_COPY[:-len("@Z")] + "ABU?$pair@QBDUBigArchiveMemberInfo@@@Unrelated@@@Z"
EXTRA_OLD = OLD_COPY[:-len("@Z")] + "PBI@Z"                         # the copy with an unrelated const unsigned *
EXTRA_NEW = NEW_COPY[:-len("@Z")] + "PBQBD@Z"


def kwargs():
    return dict(old_key=F.old_key, old_value=F.old_value, new_key=F.new_key, new_value=F.new_value,
                new_compare=F.new_compare, value_size=F.value_size, copy=F.copy, spellings=dict(F.spellings),
                members=dict(F.members), bindings=tuple(F.bindings), rows=dict(F.rows), nodes=tuple(F.nodes),
                node_path=tuple(F.node_path), witness=F.witness, callers=dict(F.callers),
                caller_bindings=tuple(F.caller_bindings), pins=dict(F.pins), key_params=dict(F.key_params))


LESS_COPY = NEW_COPY.replace("URva006038D4Less@@", "U?$less@PBD@2@")       # the default comparator: no pin spells it
OTHER_MAP_PIN = PIN.replace("Rva006038D4Less", "BfmeCStringLess")
SMALL_PIN = PIN.replace("BigArchiveMemberInfo", "BigArchiveSlot")
BY_VALUE = "?f@@YAXI@Z"
BY_VALUE_RETYPED = "?f@@YAXPBD@Z"
NODE0, NODE1 = F.nodes


def node(at=None, alloc=None, call=None, which=NODE0):
    return (which[0] if at is None else at, which[1] if alloc is None else alloc, which[2] if call is None else call)


@pytest.mark.parametrize("label, change, message", [
    # the negative near misses the coordinator asked for: each is one fact short of the tree
    ("the comparator left as less<char const *>", lambda k: k["spellings"].update({OLD_COPY: LESS_COPY}),
     "tree swap alone"),
    ("a witness pin over another comparator", lambda k: k.update(witness=(*F.witness[:3], OTHER_MAP_PIN)),
     "spells no map"),
    ("a witness pin over another value", lambda k: k.update(witness=(*F.witness[:3], SMALL_PIN)), "spells no map"),
    ("the old pair's node", lambda k: k.update(nodes=(node(alloc=C("alloc", NODE0[1].site, 0x18, "6a18")), NODE1)),
     "holds 8 bytes"),
    ("a node of another size", lambda k: k.update(nodes=(NODE0, node(alloc=C("alloc", NODE1[1].site, 0x24, "6a24"),
                                                                     which=NODE1))), "holds 20 bytes"),
    ("a value as wide as the old one", lambda k: k.update(value_size=4), "no dword-aligned struct"),
    ("a value of no dword size", lambda k: k.update(value_size=10), "no dword-aligned struct"),
    ("a by-value key retyped too", lambda k: (k["rows"].update({0x00604251: (BY_VALUE, F.rows[0x00604251][1])}),
                                              k["spellings"].pop(OLD_MAKE), k["key_params"].pop(0x00604251),
                                              k["spellings"].update({BY_VALUE: BY_VALUE_RETYPED})),
     "tree swap alone"),
    # the builtins and the new key
    ("another old value", lambda k: k.update(old_value="PAH"), "no builtin value"),
    ("a signed old key", lambda k: k.update(old_key="H"), "no builtin key"),
    ("another new key", lambda k: k.update(new_key="PAD"), "no key this route gives"),
    # the spellings
    ("a spelling that changes more than the tree",
     lambda k: k["spellings"].update({OLD_COPY: NEW_COPY.replace("QAE", "UAE")}), "tree swap alone"),
    ("a spelling left as it was", lambda k: k["spellings"].update({OLD_COPY: OLD_COPY}), "tree swap alone"),
    ("a spelling left out", lambda k: k["spellings"].pop(OLD_COPY), "every spelling"),
    ("a spelling no row has", lambda k: k["spellings"].update({"?x@@YAXXZ": "?y@@YAXXZ"}), "every spelling"),
    ("a spelling that does not decode", lambda k: k["spellings"].update({OLD_COPY: NEW_COPY[:-3]}),
     "cannot be decoded"),
    # the nodes
    ("no nodes", lambda k: k.update(nodes=()), "needs its nodes"),
    ("a count that is no push", lambda k: k.update(nodes=(node(alloc=C("alloc", NODE0[1].site, 0x20, "b820000000")),
                                                          NODE1)), "one push of an immediate"),
    ("a count of another kind", lambda k: k.update(nodes=(node(alloc=C("stride", NODE0[1].site, 0x20, "6a20")), NODE1)),
     "must be an alloc fact"),
    ("a count no call takes", lambda k: k.update(nodes=(node(call=C("calls", NODE0[2].site + 1, 0x000307F0)), NODE1)),
     "feed the call"),
    ("a node at a row", lambda k: k.update(nodes=(node(at=0x00603FC0), NODE1)), "different addresses"),
    # the reach
    ("a row reaching no node",
     lambda k: k["rows"].update({0x00603FC0: (OLD_MAP_COPY, (C("calls", 0x00603FC7, 0x00001000),))}),
     "reaches no node|which is not"),
    ("no node path, so the copy of nodes reaches none", lambda k: k.update(node_path=()), "reaches no node"),
    ("a node path in no member", lambda k: k.update(node_path=((0x00001000, F.node_path[0][1]),)), "node path is calls"),
    # the witness
    ("a witness calling no row", lambda k: k.update(witness=(WITNESS_AT, WITNESS, C("calls", 0x006045FE, 0x00001000),
                                                             PIN)), "call a row of the family"),
    ("a witness that is a row", lambda k: k.update(witness=(0x00603FD2, WITNESS, WITNESS_CALL, PIN)),
     "row outside the family"),
    ("a witness that is a rebuilt caller", lambda k: k.update(witness=(0x0060426C, WITNESS, WITNESS_CALL, PIN)),
     "row outside the family"),
    # the bindings
    ("a binding no call states", lambda k: k.update(bindings=tuple((a, o + 1, t) for a, o, t in F.bindings)),
     "not one of the row of the family's own calls"),
    ("a binding to another target",
     lambda k: k.update(bindings=tuple((a, o, "?other@@YAXXZ" if a == 0x00603FC0 else t) for a, o, t in F.bindings)),
     "which is not"),
    ("a row with no binding", lambda k: k.update(bindings=tuple(b for b in F.bindings if b[0] != 0x00603FC0)),
     "every row of the family needs a binding"),
    ("a caller with no binding", lambda k: k.update(caller_bindings=()), "every caller needs a binding"),
    ("a caller that is a row", lambda k: k["callers"].update({0x00603FC0: k["rows"][0x00603FC0]}),
     "different addresses"),
    # review round 1: a const unsigned * at an unlisted position is no key, and a listed one must be a key
    ("an unrelated const unsigned * retyped too",
     lambda k: (k["rows"].update({COPY: (EXTRA_OLD, F.rows[COPY][1])}), k["spellings"].pop(OLD_COPY),
                k["spellings"].update({EXTRA_OLD: EXTRA_NEW})), "tree swap alone"),
    ("another namespace's pair retyped too (review 2)",
     lambda k: (k["rows"].update({COPY: (UNRELATED_OLD, F.rows[COPY][1])}), k["spellings"].pop(OLD_COPY),
                k["spellings"].update({UNRELATED_OLD: UNRELATED_NEW})), "tree swap alone"),
    ("a union spelling of the allocator retyped too (review 3)",
     lambda k: (k["rows"].update({COPY: (UNION_OLD, F.rows[COPY][1])}), k["spellings"].pop(OLD_COPY),
                k["spellings"].update({UNION_OLD: UNION_NEW})), "tree swap alone"),
    ("a nested class's constructor in the tree retyped (review 4)",
     lambda k: (k["rows"].update({COPY: (NESTED_OLD, F.rows[COPY][1])}), k["spellings"].pop(OLD_COPY),
                k["spellings"].update({NESTED_OLD: NESTED_NEW})), "tree swap alone"),
    ("a free function template named like the tree retyped (review 5)",
     lambda k: (k["rows"].update({COPY: (FREE_OLD, F.rows[COPY][1])}), k["spellings"].pop(OLD_COPY),
                k["spellings"].update({FREE_OLD: FREE_NEW})), "tree swap alone"),
    ("key parameters on no row", lambda k: k["key_params"].update({0x00001000: (0,)}), "name no row"),
    ("key parameters with no index", lambda k: k["key_params"].update({0x00603FD2: ()}), "name no row"),
    ("a key parameter that is the tree", lambda k: k["key_params"].update({0x00603FD2: (1,)}),
     "no pointer or reference to const"),
    ("a key parameter past the list", lambda k: k["key_params"].update({0x00604251: (5,)}),
     "no pointer or reference to const"),
    ("a factory whose key is left unnamed", lambda k: k["key_params"].pop(0x00604251), "tree swap alone"),
    # the pins respelled in place
    ("a pin proved by no call to it",
     lambda k: k["pins"].update({0x0021983A: (OLD_PIN, (C("calls", 0x00603F08, 0x00001000),))}), "calls to it"),
    ("a pin proved by nothing", lambda k: k["pins"].update({0x0021983A: (OLD_PIN, ())}), "calls to it"),
    ("a pin at a row", lambda k: k["pins"].update({0x00603FC0: (OLD_PIN, (C("calls", 0x00603F08, 0x00603FC0),))}),
     "every spelling|at a row"),
    ("a pin left out of the spellings", lambda k: k["spellings"].pop(OLD_PIN), "every spelling"),
    ("a pin respelled onto another value",
     lambda k: k["spellings"].update({OLD_PIN: NEW_PIN.replace("BigArchiveMemberInfo", "BigArchiveSlot")}),
     "tree swap alone"),
    ("a pin over another pair", lambda k: (k["pins"].update({0x0021983A: (OLD_PIN.replace("$$CBIPAX", "$$CBHPAX"),
                                                                          F.pins[0x0021983A][1])}),
                                           k["spellings"].pop(OLD_PIN),
                                           k["spellings"].update({OLD_PIN.replace("$$CBIPAX", "$$CBHPAX"): NEW_PIN})),
     "tree swap alone|does not spell"),
])
def test_the_constructor_refuses_each_missing_condition(label, change, message):
    k = kwargs()
    change(k)
    with pytest.raises(ValueError, match=message):
        R.RetypedTreeFamily(**k)


def test_the_real_kwargs_build():
    R.RetypedTreeFamily(**kwargs())


# ------------------------------------------------------------------ the plan

def test_the_rows_are_respelled_in_place(tree):
    ctx, _ = context(tree)
    got = plan(ctx)
    rows = got.after["reverse/functions.csv"].decode()
    for at, (old, _f) in F.rows.items():
        assert old not in rows and f"{F.respell(old)},,0x{at:08X},{SIZES[at]},{SOURCES[at]},matched" in rows
    assert f"{CALLER},,0x0060426C" in rows and f"{WITNESS},,0x{WITNESS_AT:08X}" in rows
    assert PIN in got.after.get("reverse/symbols.csv", (tree / "reverse/symbols.csv").read_bytes()).decode()
    basis = got.after["reverse/name_basis.csv"].decode()
    assert f"function,{OLD_COPY},{NEW_COPY},retail,{F.evidence()},{LOWER},0x{COPY:08X}" in basis
    assert sum(1 for _line in basis.splitlines()[1:]) == len(F.rows)
    bound = got.identity["bindings"]
    assert len(bound) == len(F.bindings) + len(F.caller_bindings)
    assert (CALLER_SOURCE, CALLER, 0x13, NEW_COPY) in bound


def test_each_byte_of_each_fact_refuses(tree, image):
    ctx, _ = context(tree)
    for fact in F.facts():
        for i in range(len(R.expected(fact))):
            keep = image[fact.site + i]
            image[fact.site + i] = keep ^ 0xFF
            with pytest.raises(Refusal, match="retail does not state"):
                plan(ctx)
            image[fact.site + i] = keep


def relaid(tree, **kw):
    (tree / "reverse/functions.csv").write_text(ledger_rows(**kw))
    git(tree, "add", "-A")
    return context(tree)[0]


def test_the_member_must_be_rowed(tree):
    with pytest.raises(Refusal, match="is not rowed at 0x00413E55"):
        plan(relaid(tree, skip={F.members[0x00413E55]}))


@pytest.mark.parametrize("name, message", [(CALLER, "caller .* is not the one matched row"),
                                           (WITNESS, "witness .* is not the one matched row")])
def test_the_caller_and_witness_must_be_rowed(tree, name, message):
    with pytest.raises(Refusal, match=message):
        plan(relaid(tree, skip={name}))


def test_the_witness_call_must_lie_in_its_row(tree):
    with pytest.raises(Refusal, match="the witness's call, is outside its row"):
        plan(relaid(tree, resize={WITNESS: 0x20}))


@pytest.mark.parametrize("pins", ["", f"{OTHER_MAP_PIN},0x00604251,x\n", f"{PIN},0x00604252,x\n"])
def test_the_witness_pin_must_be_there(tmp_path, image, pins):
    ctx, _ = context(seed(tmp_path, files(pins=pins + OLD_PIN_LINE)))
    with pytest.raises(Refusal, match="the witness binds no pin"):
        plan(ctx)


def test_the_pin_is_respelled_in_place(tree):
    ctx, _ = context(tree)
    got = plan(ctx)
    pins = got.after["reverse/symbols.csv"].decode()
    assert OLD_PIN not in pins and f"{NEW_PIN},0x0021983A," in pins and f"{PIN},0x00604251," in pins
    assert [(old, new) for old, new, _at in got.renamed_pins] == [(OLD_PIN, NEW_PIN)]


@pytest.mark.parametrize("pins", [f"{PIN},0x00604251,x\n", f"{PIN},0x00604251,x\n{OLD_PIN},0x0021983B,x\n"])
def test_the_old_pin_must_be_there(tmp_path, image, pins):
    ctx, _ = context(seed(tmp_path, files(pins=pins)))
    with pytest.raises(Refusal, match="is not at 0x0021983A"):
        plan(ctx)


def test_the_new_pin_spelling_must_be_free(tmp_path, image):
    ctx, _ = context(seed(tmp_path, files(pins=f"{PIN},0x00604251,x\n{OLD_PIN_LINE}{NEW_PIN},0x00001000,x\n")))
    with pytest.raises(Refusal, match="already names a row or pin"):
        plan(ctx)


def test_the_pins_call_must_lie_in_a_row(tree):
    """A row shrunk past the copy's allocator call leaves the pin's fact in no row of the family."""
    with pytest.raises(Refusal, match="is outside|a call of the pin"):
        plan(relaid(tree, resize={OLD_COPY: 0x1C}))


def test_an_object_still_naming_the_old_pin_refuses(tree, monkeypatch):
    seen = []

    def consumers(ctx, names, words, rebuilt, groups=()):
        seen.append((tuple(names), tuple(groups)))
        return ([f"Code/Lib/Other.cpp references {names[0]}"], 0)
    monkeypatch.setattr(rename, "pin_consumers", consumers)
    ctx, _ = context(tree)
    with pytest.raises(Refusal, match="the old tree's pin.* cannot be respelled"):
        plan(ctx)
    assert seen == [((OLD_PIN,), (("get_allocator",),))]


@pytest.mark.parametrize("at", sorted(NODE_NAMES))
def test_a_node_outside_any_row_refuses(tree, at):
    with pytest.raises(Refusal, match=f"in no one matched row at 0x{at:08X}"):
        plan(relaid(tree, resize={NODE_NAMES[at]: 4}))


def test_the_node_path_must_lie_in_its_members_row(tree):
    with pytest.raises(Refusal, match="the node path"):
        plan(relaid(tree, resize={F.members[0x00413E55]: 4}))


def test_a_fact_outside_its_row_refuses(tree):
    with pytest.raises(Refusal, match="is outside"):
        plan(relaid(tree, resize={OLD_COPY: 0x40}))


def test_the_caller_must_be_prepared(tree):
    ctx, _ = context(tree)
    with pytest.raises(Refusal, match="--prepared|prepare"):
        plan(ctx, prepared={LOWER: PREPARED[LOWER]})


def test_the_debt_the_respell_fixes_is_carried_and_named(tmp_path, image):
    identity = f"{LOWER}\t{OLD_COPY}\t??0Base@@QAE@XZ\t0x0030087C\twrong\n"
    ctx, _ = context(seed(tmp_path, files(identity=identity)))
    got = plan(ctx)
    assert any("retire identity " + LOWER in w for w in got.warnings)


def test_a_unit_still_spelling_an_old_name_refuses(tree):
    write(tree / "Code/Lib/Elsewhere.cpp", f"// {OLD_MAKE}\n")
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


def test_the_default_comparator_is_no_family(tree):
    ctx, _ = context(tree)
    with pytest.raises(Refusal, match="proves only the families"):
        plan(ctx, new=LESS_COPY)


# ------------------------------------------------------------------ the rebuilt objects

def test_the_landing_writes_it_all(tree):
    ctx, state = context(tree)
    land(ctx, plan(ctx), state)
    text = (tree / "reverse/functions.csv").read_text()
    assert NEW_COPY in text and OLD_COPY not in text
    assert PIN in (tree / "reverse/symbols.csv").read_text()


REGISTER = "pin\treverse/symbols.csv\t0x0030087C\t7\tallow=0123456789abcdef0123456789abcdef01234567\n"


def admissions(tree, monkeypatch):
    """hatch_counters on the test tree: admit() records its calls and re-stamps the register as the real one does."""
    import hatch_counters
    calls = []

    def admit(path, reason, tokens=None, before=None, now=None):
        calls.append((path, tokens))
        (tree / "reverse/hatch_baseline.tsv").write_text(REGISTER.replace("0123456789abcdef", "fedcba9876543210"))
        return {"admitted": [], "kept": ["pin"], "refused": []}
    monkeypatch.setattr(hatch_counters, "ROOT", tree)
    monkeypatch.setattr(hatch_counters, "admit", admit)
    write(tree / "reverse/hatch_baseline.tsv", REGISTER)
    git(tree, "add", "-A")
    return calls


def test_the_pin_respell_restamps_this_changes_admissions(tree, monkeypatch):
    """The plan renames a pin in symbols.csv; the admissions tools made earlier in the change are re-stamped, and
    nothing new is granted (tokens=())."""
    calls = admissions(tree, monkeypatch)
    ctx, state = context(tree)
    got = land(ctx, plan(ctx), state)
    assert calls == [("reverse/symbols.csv", ())]
    assert "fedcba9876543210" in (tree / "reverse/hatch_baseline.tsv").read_text()
    assert b"fedcba9876543210" in got.after["reverse/hatch_baseline.tsv"]       # staged for the hooks' checks


def test_an_undone_respell_restores_the_register(tree, monkeypatch):
    calls = admissions(tree, monkeypatch)
    ctx, state = context(tree)
    undone(ctx, plan(ctx), state, refs=after_refs()[:1])
    assert calls == [("reverse/symbols.csv", ())]
    assert (tree / "reverse/hatch_baseline.tsv").read_text() == REGISTER


def test_the_journal_holds_the_register_before_any_write(tree, monkeypatch):
    """Review round 1: a run killed after the restamp is recovered from its journal, so the register's original
    bytes must be in the journal, written before the first write."""
    calls = admissions(tree, monkeypatch)
    journaled = []
    real = rename.write_journal

    def journal(ctx, plan, claimed=None):
        journaled.append(dict(plan.before))
        return real(ctx, plan, claimed)
    monkeypatch.setattr(rename, "write_journal", journal)
    ctx, state = context(tree)
    land(ctx, plan(ctx), state)
    assert calls == [("reverse/symbols.csv", ())]
    assert journaled[0]["reverse/hatch_baseline.tsv"] == REGISTER.encode()


def test_a_killed_restamp_is_recovered(tree, monkeypatch):
    """The process dies right after the restamp: `rename.py recover` puts the register back from the journal."""
    admissions(tree, monkeypatch)

    def die(*_args):
        raise KeyboardInterrupt
    ctx, state = context(tree)
    got = plan(ctx)
    # killed during the build: the in-process restore never runs, so the journal stays for `rename.py recover`
    monkeypatch.setattr(rename, "restore", die)
    with pytest.raises(KeyboardInterrupt):
        rename.apply_rename(got, ctx=ctx, verify=die, checks=None)
    assert "fedcba9876543210" in (tree / "reverse/hatch_baseline.tsv").read_text()
    monkeypatch.undo()
    rename.recover(rename.Context(tree, object_scan=False), release_claims=False)
    assert (tree / "reverse/hatch_baseline.tsv").read_text() == REGISTER


def test_another_tree_is_never_restamped(tree, monkeypatch):
    """hatch_counters works on its own checkout: a plan for another tree leaves it alone."""
    import hatch_counters
    calls = admissions(tree, monkeypatch)
    monkeypatch.setattr(hatch_counters, "ROOT", tree / "elsewhere")
    ctx, state = context(tree)
    land(ctx, plan(ctx), state)
    assert calls == [] and (tree / "reverse/hatch_baseline.tsv").read_text() == REGISTER


@pytest.mark.parametrize("label, change", [
    ("no relocation at all", lambda relocs: []),
    ("another offset", lambda relocs: [(o + 1, k, t) for o, k, t in relocs]),
    ("the old tree's callee", lambda relocs: [(o, k, OLD_OF.get(t, t)) for o, k, t in relocs]),
])
def test_a_rebuilt_row_or_caller_not_binding_its_target_is_undone(tree, label, change):
    for name in [F.respell(old) for old, _f in F.rows.values()] + [CALLER]:
        if change(GOOD_RELOCS[name]) == GOOD_RELOCS[name]:
            continue                                   # _M_copy binds only the member clone, which keeps its name
        ctx, state = context(tree)
        found = undone(ctx, plan(ctx), state, relocs={**GOOD_RELOCS, name: change(GOOD_RELOCS[name])})
        assert any(p.startswith(f"{name} does not bind") for p in found), found


def test_a_new_wrong_binding_is_undone(tree):
    ctx, state = context(tree)
    wrong = dict(source=LOWER, row=NEW_COPY, rva=COPY, symbol="x", target=0x1234,
                 cls=next(iter(allowed_symbols.WRONG)))
    found = undone(ctx, plan(ctx), state, refs=after_refs() + [wrong])
    assert any("gains a wrong binding" in p for p in found), found


def test_the_review_2_counterexample_decodes_and_differs():
    """The constructor case above is only a test if both names decode and the unrelated pair is really retyped in
    the new one: the refusal must come from the swap, not from a name that does not parse."""
    before, after = rename.type_tree(UNRELATED_OLD), rename.type_tree(UNRELATED_NEW)
    assert swap(UNRELATED_OLD) != after and swap(UNRELATED_OLD) != before
    assert swap(UNRELATED_OLD) == rename.type_tree(NEW_COPY[:-len("@Z")] + "ABU?$pair@$$CBIPAX@Unrelated@@@Z")


def test_the_review_3_counterexample_decodes_and_differs():
    """As for review 2's: the union parameter decodes, and the swap leaves it alone, so the refusal is the swap's."""
    assert swap(UNION_OLD) != rename.type_tree(UNION_NEW)
    assert swap(UNION_OLD) == rename.type_tree(NEW_COPY[:-len("@Z")] + "T?$allocator@U?$pair@$$CBIPAX@_STL@@@_STL@@@Z")


def test_each_shape_kind_and_scope_is_what_the_spellings_use():
    """The reviewed kinds and scopes are exactly those the six spellings need: drop one and a spelling fails."""
    assert set(R.TYPE_KINDS) | set(R.SCOPE_SHAPES) == set(R.TREE_SHAPES)
    for name, kind in R.TYPE_KINDS.items():
        other = {"V": "U", "U": "V"}[kind]
        trial = {**R.TYPE_KINDS, name: other}
        old = R.TYPE_KINDS
        R.TYPE_KINDS = trial
        try:
            changed = [o for o, n in F.spellings.items() if swap(o, PARAMS.get(o, ())) != rename.type_tree(n)]
        finally:
            R.TYPE_KINDS = old
        assert changed, f"{name}'s kind is used by no spelling"
    for name in R.SCOPE_SHAPES:
        old = R.SCOPE_SHAPES
        R.SCOPE_SHAPES = old - {name}
        try:
            changed = [o for o, n in F.spellings.items() if swap(o, PARAMS.get(o, ())) != rename.type_tree(n)]
        finally:
            R.SCOPE_SHAPES = old
        assert changed, f"{name} is the scope of no spelling"


@pytest.mark.parametrize("name", [NESTED_OLD, NESTED_DTOR])
def test_a_nested_class_member_of_the_tree_stays_whole(name):
    """Review 4: a special member of a class nested in the tree spells the tree as its enclosing scope; the scope
    rule for named members must not read the nested class's name as a member's."""
    before = rename.type_tree(name)
    assert before[1] in ("??0", "??1") and before[2][1][0] == ("N", "Nested")
    assert swap(name) == before
    assert swap(NESTED_OLD) != rename.type_tree(NESTED_NEW)


def test_a_free_function_template_named_like_the_tree_stays_whole():
    """Review 5: a name with no operator whose qualified name is the shape alone is a free function template, not a
    member of the tree: only ??0 and ??1 take the shape alone as their scope."""
    before = rename.type_tree(FREE_OLD)
    assert before[1] == "" and before[2][1][0][:2] == ("T", "_Rb_tree")
    assert swap(FREE_OLD) == before and swap(FREE_OLD) != rename.type_tree(FREE_NEW)
    assert R.SCOPE_OPERATORS == frozenset(("??0", "??1"))
