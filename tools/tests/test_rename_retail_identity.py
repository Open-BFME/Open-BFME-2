"""`tools/rename.py function --respell --identity --basis retail`: a class family respelled on
retail's own bytes (tools/retail_identity.py), with one row moved alone into its approved unit.

The real family's table is the fixture: its facts are served from an image the test writes, each
one breakable alone, and its rows and pins are ledger rows at their real addresses."""
import hashlib
import struct
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import allowed_symbols  # noqa: E402
import pin_admission  # noqa: E402
import rename  # noqa: E402
import retail_identity as R  # noqa: E402
from rename import Refusal, VerifyFailed  # noqa: E402

F = R.ENABLE_REGION_RECORD
COPY, NEW_COPY = F.copy, F.respell(F.rows[F.copy][0])
EVIDENCE = F.evidence()
DONOR = "Code/GameClient/FXList.cpp"
STANDIN = "Code/Lib/Standin.cpp"
TU = "Code/Logic/LivingWorldCampaign.cpp"
SPAWN = "Code/Lib/SpawnArmy.cpp"
TABLE_RVA = F.table - R.IMAGE_BASE


def write(path, text):
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_bytes(text.encode("utf-8"))


def git(root, *args):
    subprocess.run(["git", "-C", str(root), *args], check=True, capture_output=True)


def track(root, rel, text):
    """A tracked file: the plan's scans read what git tracks."""
    write(root / rel, text)
    git(root, "add", "-A")


def csv_of(rows):
    return "".join(rows)


@pytest.fixture
def image(monkeypatch):
    """Retail as the family's facts say it is; a test edits a site to break one."""
    bytes_at = {}
    for fact in F.facts():
        want = R.expected(fact)
        for i, byte in enumerate(want):
            bytes_at[fact.site + i] = byte

    def read(rva, size):
        return bytes(bytes_at[rva + i] for i in range(size))
    monkeypatch.setattr(R, "read_retail", read)
    return bytes_at


@pytest.fixture
def tree(tmp_path, image):
    rows = ["name,export_rva,target_rva,target_size,source,status,notes\n"]
    for at, (old, _facts) in sorted(F.rows.items()):
        source = DONOR if at == F.copy else STANDIN
        rows.append(f"{old},,0x{at:08X},8,{source},matched,family row\n")
    rows.append(f"{F.owner['name']},,0x{F.owner['rva']:08X},14,{SPAWN},matched,owner\n")
    rows.append(f"?stay@@YAXXZ,,0x00001000,8,{DONOR},matched,keeps its source\n")
    rows.append(f"?ownTu@@YAXXZ,,0x00001010,8,{TU},matched,tu row\n")
    pins = ["name,address,notes\n"] + [f"{old},0x{at:08X},sweep\n" for at, (old, _f) in sorted(F.pins.items())]
    tu_map = ["rva,size,kind,tu,confidence,by,evidence,source\n"]
    for at in F.rows:
        tu_map.append(f"0x{at:08X},8,code,{TU},approved,C,C=x,{DONOR if at == F.copy else STANDIN}\n")
    files = {
        "reverse/functions.csv": csv_of(rows),
        "reverse/symbols.csv": csv_of(pins),
        "reverse/deleted_rows.csv": "name,target_rva,reason\n",
        "reverse/name_basis.csv": "kind,old,new,basis,evidence,source,rva\n",
        "reverse/data_rows.csv": "name,address,address_kind,size,section,source,status,evidence,model\n",
        "reverse/exports.csv": "ordinal,rva,target_rva,section,kind,name\n",
        "reverse/gate_baseline.txt": "",
        "reverse/tu_map.csv": csv_of(tu_map),
        "reverse/data_ledger.csv": ("address,size,section,kind,name,source,status,names,defs,refs\n"
                                    f"0x{TABLE_RVA:08X},4,.rdata,vtable,{F.table_name},,literal,,0,5\n"),
        DONOR: "class FXList { public: virtual ~FXList(); };\nvoid stay() {}\n",
        STANDIN: "// family stand-in\n" + "".join(f"// {old}\n" for old, _f in F.rows.values() if old != F.rows[F.copy][0]),
        TU: "void ownTu() {}\n",
        SPAWN: "void spawn() {}\n",
    }
    for rel, text in files.items():
        write(tmp_path / rel, text)
    git(tmp_path, "init", "-q")
    git(tmp_path, "add", "-A")
    git(tmp_path, "-c", "user.email=t@t", "-c", "user.name=t", "commit", "-q", "-m", "seed")
    return tmp_path


@pytest.fixture(autouse=True)
def fresh_map(monkeypatch):
    import csv
    import tu_map

    def current_rows(layout):
        with open(layout.root / "reverse/tu_map.csv", newline="") as handle:
            return list(csv.DictReader(handle)), []
    monkeypatch.setattr(tu_map, "current_rows", current_rows)


PREPARED_STANDIN = "// family stand-in\n" + "".join(f"// {F.respell(old)}\n" for old, _f in F.rows.values()
                                                    if old != F.rows[F.copy][0])
PREPARED_TU = f"// {NEW_COPY}\nvoid ownTu() {{}}\n"
GOOD_RELOCS = [(F.copy_store, rename.DIR32, F.table_name)]


def context(root, refs=(), relocs=GOOD_RELOCS):
    ctx = rename.Context(root, object_scan=False)
    state = {"refs": list(refs), "relocs": list(relocs)}
    ctx.identity_refs = lambda sources: [r for r in state["refs"] if r["source"] in sources]
    ctx.object_symbol_relocs = lambda source, name: state["relocs"]
    return ctx, state


def plan(ctx, **overrides):
    kwargs = dict(rva=COPY, new=NEW_COPY, respell=True, identity=True, basis="retail", evidence=EVIDENCE,
                  prepared={TU: PREPARED_TU.encode(), STANDIN: PREPARED_STANDIN.encode()},
                  move_to=TU, move_rows=[COPY])
    kwargs.update(overrides)
    return rename.plan_rename("function", ctx=ctx, **kwargs)


def ref(row, rva, target=0x1234, cls="owner", symbol="x", source=TU):
    return dict(source=source, row=row, rva=rva, symbol=symbol, target=target, cls=cls)


def after_refs():
    return [ref(F.respell(old), at) for at, (old, _f) in F.rows.items()]


def apply(ctx, got, state, refs=None, relocs=None):
    def verify(c, sources):
        state["refs"] = after_refs() if refs is None else refs
        if relocs is not None:
            state["relocs"] = relocs
        return True
    return rename.apply_rename(got, ctx=ctx, verify=verify, checks=None)


# ------------------------------------------------------------------ the plan

def test_every_row_and_pin_is_respelled_and_one_row_moves_alone(tree):
    ctx, _ = context(tree)
    got = plan(ctx)
    rows = got.after["reverse/functions.csv"].decode()
    for at, (old, _f) in F.rows.items():
        assert old not in rows and F.respell(old) in rows
    assert f"{NEW_COPY},,0x{COPY:08X},8,{TU},matched" in rows
    for at, (old, _f) in F.rows.items():
        if at != COPY:
            assert f"{F.respell(old)},,0x{at:08X},8,{STANDIN},matched" in rows
    assert f"?stay@@YAXXZ,,0x00001000,8,{DONOR},matched" in rows                     # its source keeps its other rows
    assert got.removed == []
    pins = got.after["reverse/symbols.csv"].decode()
    for at, (old, _f) in F.pins.items():
        assert old not in pins and f"{F.respell(old)},0x{at:08X},sweep" in pins
    tu_map = got.after["reverse/tu_map.csv"].decode()
    assert f"0x{COPY:08X},8,code,{TU},approved,C,C=x,{TU}" in tu_map
    assert f"0x{0x0052C2F3:08X},8,code,{TU},approved,C,C=x,{STANDIN}" in tu_map
    assert DONOR in got.verify and TU in got.verify and STANDIN in got.verify
    assert got.subject().endswith("by retail identity")


def test_each_record_names_what_retail_holds_for_that_row(tree):
    ctx, _ = context(tree)
    basis = plan(ctx).after["reverse/name_basis.csv"].decode()
    first = f"function,{F.rows[COPY][0]},{NEW_COPY},retail,{EVIDENCE},{TU},0x{COPY:08X}"
    assert first in basis
    stride = R.record(F.rows[0x0052C8EF][1])
    assert stride == "retail:0x0052C8FD calls=0x0052C2F3 stride=8"
    assert f"retail,{stride},{STANDIN},0x0052C8EF" in basis
    assert all(R.well_formed(R.record(facts)) for _old, facts in F.rows.values())


def test_the_record_format_is_not_this_familys(tree):
    """Another route's facts read and record the same way: the bridge lane's store loop, for one."""
    facts = [R.Fact("stride", 0x001B653B, 4, "83c004")]
    assert R.record(facts) == "retail:0x001B653B stride=4"
    assert R.well_formed(R.record(facts))
    for bad in ("", "retail:", "retail:0x1", "retail:0x001B653B", "agree:nl-1", "retail:0x001b653b stride=4",
                "retail:0x001B653B stride=4\n"):
        assert not R.well_formed(bad), bad


def bases(tmp_path, *records):
    path = tmp_path / "name_basis.csv"
    write(path, "kind,old,new,basis,evidence,source,rva\n" + "".join(f"{r}\n" for r in records))
    return allowed_symbols.Bases(path)


def test_a_familys_own_record_is_evidence(tmp_path):
    got = bases(tmp_path, f"function,{F.rows[COPY][0]},{NEW_COPY},retail,{EVIDENCE},{TU},0x{COPY:08X}")
    assert got.lookup(NEW_COPY, COPY) == ("evidence", "retail")


@pytest.mark.parametrize("label, kind, old, new, evidence, rva", [
    ("a real function under an invented fact", "function", "?x@@YAXXZ", "?doFXPos@FXList@@QBEXPBUCoord3D@@PBVMatrix3D@@M0@Z",
     "retail:0x00000001 invented=true", "0x001E296E"),
    ("the family's evidence on a stranger", "function", "?x@@YAXXZ", NEW_COPY, EVIDENCE, "0x001E296E"),
    ("the family's row at another address", "function", F.rows[COPY][0], NEW_COPY, EVIDENCE, "0x001E296E"),
    ("the family's row under another row's facts", "function", F.rows[COPY][0], NEW_COPY, R.record(F.rows[0x0052C2F3][1]), f"0x{COPY:08X}"),
    ("another spelling at the family's row", "function", F.rows[COPY][0], "??0Other@@QAE@ABV0@@Z", EVIDENCE, f"0x{COPY:08X}"),
    ("another old name", "function", "?x@@YAXXZ", NEW_COPY, EVIDENCE, f"0x{COPY:08X}"),
    ("no address", "function", F.rows[COPY][0], NEW_COPY, EVIDENCE, ""),
    ("not a function record", "global", F.rows[COPY][0], NEW_COPY, EVIDENCE, f"0x{COPY:08X}"),
])
def test_a_retail_record_outside_the_table_grants_nothing(tmp_path, label, kind, old, new, evidence, rva):
    got = bases(tmp_path, f"{kind},{old},{new},retail,{evidence},{TU},{rva}")
    assert got.lookup(new, int(rva, 16) if rva else 0) is None, label


@pytest.mark.parametrize("spelled", ["0052BD3A", "52BD3A", "0x52BD3A", "0x0052bd3a", "0X0052BD3A", " 0x0052BD3A", "0x0052BD3A ", "", "x"])
def test_only_the_planners_spelling_of_the_address_grants(tmp_path, spelled):
    """The review's repro: a prefixless address read as no address made the grant hold at every address."""
    got = bases(tmp_path, f"function,{F.rows[COPY][0]},{NEW_COPY},retail,{EVIDENCE},{TU},{spelled}")
    assert got.lookup(NEW_COPY, 0x001E296E) is None
    assert got.lookup(NEW_COPY, COPY) is None
    assert not R.record_proven(F.rows[COPY][0], NEW_COPY, spelled, EVIDENCE)


def test_the_planners_spelling_grants_at_its_address_only(tmp_path):
    got = bases(tmp_path, f"function,{F.rows[COPY][0]},{NEW_COPY},retail,{EVIDENCE},{TU},0x{COPY:08X}")
    assert got.lookup(NEW_COPY, COPY) == ("evidence", "retail")
    assert got.lookup(NEW_COPY, 0x001E296E) is None


def test_the_table_and_its_hash_are_protected_paths():
    import protected_paths
    paths = ["tools/retail_identity.py", "baselines/bfme2/workshop-vanilla-1.06/manifest.json", "tools/pin_admission.py"]
    assert set(protected_paths.protected(paths + ["Code/a.cpp"])) == set(paths)


def image_copy(tmp_path, monkeypatch, edit):
    """The real image with `edit` applied, as the build would read it; skipped where there is none.
    Patches the module retail_identity reads: a long test run can hold more than one copy of `build`."""
    build = R.build
    if not Path(build.EXE).exists():
        pytest.skip("no retail image here")
    data = bytearray(Path(build.EXE).read_bytes())
    edit(data)
    copy = tmp_path / build.EXE.name
    copy.write_bytes(data)
    monkeypatch.setattr(build, "exe_image", lambda: (bytes(data), build.pe_sections(bytes(data))))
    monkeypatch.setattr(build, "EXE", copy)
    monkeypatch.setattr(R, "_verified", [None])


def test_a_changed_image_states_no_fact(tmp_path, monkeypatch):
    """The review's repro, a byte no fact reads: every fact would still hold byte for byte."""
    def change_a_byte(data):
        data[len(data) // 2] ^= 0xFF
    image_copy(tmp_path, monkeypatch, change_a_byte)
    verified_hash = R.json.loads(R.build.MANIFEST.read_text(encoding="utf-8"))["files"][0]["sha256"]
    monkeypatch.setattr(R, "_verified", [(b"an image verified earlier", verified_hash)])    # says nothing of this one
    assert "not the manifest's" in R.image_problem()
    problems = R.facts_problems(F.facts())
    assert len(problems) == len(F.facts()) and all("not the manifest's" in p for p in problems)
    assert not R.pin_respell_proven(OLD_GET, NEW_GET, GET)


def test_a_verdict_counts_for_those_bytes_against_that_hash(tmp_path, monkeypatch):
    """Long-lived process: neither other bytes nor a changed manifest may reuse a past verdict."""
    build = R.build
    data = b"image"
    good = R.hashlib.sha256(data).hexdigest()
    manifest = tmp_path / "manifest.json"
    entry = '{"files": [{"path": "files/game.dat", "sha256": "%s"}]}'
    manifest.write_text(entry % good, encoding="utf-8")
    monkeypatch.setattr(build, "MANIFEST", manifest)
    monkeypatch.setattr(build, "EXE", tmp_path / "game.dat")
    monkeypatch.setattr(build, "exe_image", lambda: (data, []))
    monkeypatch.setattr(R, "_verified", [None])
    assert R.image_problem() is None
    assert R._verified[0][0] is data
    monkeypatch.setattr(R.hashlib, "sha256", lambda raw: pytest.fail("the same bytes and hash were hashed again"))
    assert R.image_problem() is None
    monkeypatch.undo()
    monkeypatch.setattr(build, "MANIFEST", manifest)
    monkeypatch.setattr(build, "EXE", tmp_path / "game.dat")
    monkeypatch.setattr(build, "exe_image", lambda: (data, []))
    manifest.write_text(entry % ("0" * 64), encoding="utf-8")
    assert "not the manifest's" in R.image_problem()                                  # the manifest changed under it
    manifest.write_text(entry % good, encoding="utf-8")
    other = bytes(bytearray(b"image"))                                                # equal bytes, another object: read afresh
    monkeypatch.setattr(build, "exe_image", lambda: (other, []))
    assert R.image_problem() is None and R._verified[0][0] is other
    monkeypatch.setattr(build, "exe_image", lambda: (b"other", []))
    assert "not the manifest's" in R.image_problem()


def test_the_real_image_states_them_all(monkeypatch):
    build = R.build
    if not Path(build.EXE).exists():
        pytest.skip("no retail image here")
    monkeypatch.setattr(R, "_verified", [None])
    assert R.image_problem() is None
    assert R._verified[0][0] is build.exe_image()[0]
    assert R.facts_problems(F.facts()) == []


@pytest.mark.parametrize("label, text", [("no entry", '{"files": []}'), ("no hash", '{"files": [{"path": "files/game.dat"}]}'),
                                         ("another image's entry", '{"files": [{"path": "files/other", "sha256": "x"}]}')])
def test_a_manifest_naming_no_hash_refuses(tmp_path, monkeypatch, label, text):
    build = R.build
    manifest = tmp_path / "manifest.json"
    manifest.write_text(text, encoding="utf-8")
    monkeypatch.setattr(build, "MANIFEST", manifest)
    monkeypatch.setattr(build, "EXE", tmp_path / "game.dat")
    monkeypatch.setattr(build, "exe_image", lambda: (b"image", []))
    monkeypatch.setattr(R, "_verified", [None])
    assert "names no one sha256" in R.image_problem(), label
    assert "cannot be read" in R.facts_problems([R.Fact("stride", 0x100, 8, "90")])[0]


# ------------------------------------------------------------------ what refuses

def every_fact():
    """The table walked here, not through Family.facts(), so a fact it leaves out still gets read."""
    return ([f for _old, facts in F.rows.values() for f in facts] + list(F.owner["facts"])
            + [f for _old, facts in F.pins.values() for f in facts])


def test_each_byte_of_each_fact_retail_does_not_hold_refuses(tree, image):
    ctx, _ = context(tree)
    for fact in every_fact():
        for site in range(fact.site, fact.site + len(R.expected(fact))):
            was = image[site]
            image[site] = (was + 1) & 0xFF
            with pytest.raises(Refusal, match="retail does not state"):
                plan(ctx)
            image[site] = was
    plan(ctx)


def test_what_each_kind_of_fact_reads():
    assert R.expected(R.Fact("stores", 0x100, 0x00C61A20, "c706")) == bytes.fromhex("c706201ac600")
    assert R.expected(R.Fact("calls", 0x0052C30F, 0x0052BD3A)) == bytes.fromhex("e826faffff")
    assert R.expected(R.Fact("jumps", 0x00797255, 0x0052CB26)) == bytes.fromhex("e9cc58d9ff")
    assert R.expected(R.Fact("stride", 0x100, 8, "83c708")) == bytes.fromhex("83c708")
    with pytest.raises(ValueError):
        R.expected(R.Fact("other", 0x100, 8, "90"))


def test_an_unreadable_site_is_a_problem(tree, image):
    fact = F.facts()[0]
    del image[fact.site]
    assert "cannot be read" in R.facts_problems([fact])[0]


@pytest.mark.parametrize("change, message", [
    (dict(evidence="retail:0x0052BD48 stores=0x00C61A24"), "must name the proof"),
    (dict(evidence=""), "must name the proof"),
    (dict(evidence="agree:nl-1"), "must name the proof"),
    (dict(also=[(0x0052C2F3, "?x@@YAXXZ")]), "no --old, no --also"),
    (dict(old=F.rows[COPY][0]), "no --old, no --also"),
    (dict(prepared={}), "--prepared"),
    (dict(new="??0Other@@QAE@ABV0@@Z"), "proves only the families"),
    (dict(rva=0x00001000), "proves only the families"),
    (dict(move_to=None), "names the rows --move-to moves"),
    (dict(move_rows=[]), "only those"),
    (dict(move_rows=[0x00001000]), "not a row of the family"),
    (dict(prepared={STANDIN: PREPARED_STANDIN.encode()}), "needs its prepared bytes"),
])
def test_what_the_request_may_not_say(tree, change, message):
    ctx, _ = context(tree)
    with pytest.raises(Refusal, match=message):
        plan(ctx, **change)


def test_only_the_retail_basis_moves_a_row_alone(tree):
    ctx, _ = context(tree)
    with pytest.raises(Refusal, match="--move-rows goes with --basis retail"):
        plan(ctx, basis="inferred")


def test_a_row_the_map_does_not_approve_does_not_move(tree):
    other = (tree / "reverse/tu_map.csv").read_text().replace(f"0x{COPY:08X},8,code,{TU},approved",
                                                              f"0x{COPY:08X},8,code,{TU},proposed")
    write(tree / "reverse/tu_map.csv", other)
    ctx, _ = context(tree)
    with pytest.raises(Refusal, match="not approved"):
        plan(ctx)


def test_a_moved_row_may_not_leave_its_funclets(tree):
    text = (tree / "reverse/functions.csv").read_text()
    text += f"$L1,,0x00797000,8,{DONOR},matched,parent={F.rows[COPY][0]}\n"
    write(tree / "reverse/functions.csv", text)
    ctx, _ = context(tree)
    with pytest.raises(Refusal, match="has funclets"):
        plan(ctx)


def test_the_tables_class_must_be_rowed_and_named(tree):
    good = (tree / "reverse/functions.csv").read_text()
    write(tree / "reverse/functions.csv", good.replace(F.owner["name"], "??1Other@@UAE@XZ"))
    ctx, _ = context(tree)
    with pytest.raises(Refusal, match="is not rowed"):
        plan(ctx)
    write(tree / "reverse/functions.csv", good)
    ledger = (tree / "reverse/data_ledger.csv").read_text()
    write(tree / "reverse/data_ledger.csv", ledger.replace(F.table_name, "??_7Other@@6B@"))
    ctx, _ = context(tree)
    with pytest.raises(Refusal, match="does not name"):
        plan(ctx)


def test_a_missing_row_or_pin_refuses(tree):
    good = (tree / "reverse/functions.csv").read_text()
    old = F.rows[0x0052C2F3][0]
    write(tree / "reverse/functions.csv", good.replace(old, "?gone@@YAXXZ"))
    ctx, _ = context(tree)
    with pytest.raises(Refusal, match="is not the one row"):
        plan(ctx)
    write(tree / "reverse/functions.csv", good)
    pins = (tree / "reverse/symbols.csv").read_text()
    old = F.pins[0x0021983A][0]
    write(tree / "reverse/symbols.csv", pins.replace(f"{old},0x0021983A", f"{old},0x00001000"))
    ctx, _ = context(tree)
    with pytest.raises(Refusal, match="is not at"):
        plan(ctx)


def test_a_new_spelling_already_taken_refuses(tree):
    text = (tree / "reverse/symbols.csv").read_text() + f"{F.respell(F.pins[0x0021983A][0])},0x00001000,taken\n"
    write(tree / "reverse/symbols.csv", text)
    ctx, _ = context(tree)
    with pytest.raises(Refusal, match="already names"):
        plan(ctx)


def test_a_unit_still_spelling_an_old_name_refuses(tree):
    ctx, _ = context(tree)
    with pytest.raises(Refusal, match="still spells"):
        plan(ctx, prepared={TU: PREPARED_TU.encode(), STANDIN: (PREPARED_STANDIN + f"// {F.rows[0x0052C2F3][0]}\n").encode()})
    track(tree, "Code/Other.cpp", f"// {F.pins[0x0021983A][0]}\n")
    ctx, _ = context(tree)
    with pytest.raises(Refusal, match="still spells"):
        plan(ctx)


def test_the_frozen_exception_is_this_one_register_on_the_copy_alone(tree):
    baseline = "reverse/code_identity_baseline.tsv"
    track(tree, baseline, f"# mode: shadow\n{DONOR}\t{F.rows[COPY][0]}\tx\t0x1\tdivergent\n")
    ctx, _ = context(tree)
    got = plan(ctx)
    assert any("retire identity " + DONOR + " in the next commit" in w for w in got.warnings)
    track(tree, baseline, f"# mode: shadow\n{DONOR}\t{F.rows[0x0052C2F3][0]}\tx\t0x1\tdivergent\n")
    ctx, _ = context(tree)
    with pytest.raises(Refusal, match="frozen"):
        plan(ctx)
    track(tree, baseline, "# mode: shadow\n")
    track(tree, "reverse/x_baseline.txt", f"{F.rows[COPY][0]}\n")
    ctx, _ = context(tree)
    with pytest.raises(Refusal, match="frozen"):
        plan(ctx)


# ------------------------------------------------------------------ after the build

def test_the_landing_writes_it_all(tree):
    ctx, state = context(tree)
    apply(ctx, plan(ctx), state)
    assert (tree / TU).read_bytes() == PREPARED_TU.encode()
    assert NEW_COPY in (tree / "reverse/functions.csv").read_text()
    assert (tree / DONOR).exists()


def test_a_rebuilt_copy_not_storing_the_table_is_undone(tree):
    before = (tree / "reverse/functions.csv").read_bytes()
    for relocs in ([], [(F.copy_store, rename.DIR32, "??_7Other@@6B@")], [(F.copy_store + 4, rename.DIR32, F.table_name)],
                   [(F.copy_store, 20, F.table_name)]):
        ctx, state = context(tree)
        with pytest.raises(VerifyFailed, match="does not store"):
            apply(ctx, plan(ctx), state, relocs=relocs)
        assert (tree / "reverse/functions.csv").read_bytes() == before


def test_a_row_with_no_references_is_undone(tree):
    ctx, state = context(tree)
    with pytest.raises(VerifyFailed, match="no references"):
        apply(ctx, plan(ctx), state, refs=after_refs()[1:])


def test_a_new_wrong_binding_is_undone(tree):
    ctx, state = context(tree)
    worse = after_refs() + [ref("?ownTu@@YAXXZ", 0x00001010, cls="wrong", symbol="bad")]
    with pytest.raises(VerifyFailed, match="gains a wrong binding"):
        apply(ctx, plan(ctx), state, refs=worse)


def test_an_old_wrong_binding_is_not_this_changes(tree):
    known = ref("?ownTu@@YAXXZ", 0x00001010, cls="wrong", symbol="bad")
    ctx, state = context(tree, refs=[known])
    apply(ctx, plan(ctx), state, refs=after_refs() + [known])


def test_an_unreadable_scan_refuses_on_both_sides(tree):
    def broken(sources):
        raise allowed_symbols.UnverifiedFunclet("funclet $L1")
    ctx, _ = context(tree)
    ctx.identity_refs = broken
    with pytest.raises(Refusal, match="./build.sh"):
        plan(ctx)
    ctx, state = context(tree)
    got = plan(ctx)
    ctx.identity_refs = broken
    with pytest.raises(VerifyFailed, match="cannot read the rebuilt units"):
        apply(ctx, got, state)


# ------------------------------------------------------------------ pin admission

@pytest.fixture
def admission(monkeypatch):
    monkeypatch.setattr(pin_admission, "image_layout", lambda: (0x01000000, [(0x1000, 0x00800000, True)]))
    monkeypatch.setattr(pin_admission.build, "gate_baselined", lambda check, row: False)
    return pin_admission


def pin(name, address, notes="sweep"):
    return {"name": name, "address": f"0x{address:08X}", "notes": notes}


def owner(name, address):
    return {"name": name, "export_rva": "", "target_rva": f"0x{address:08X}", "target_size": "7", "source": "Code/x.cpp",
            "status": "matched", "notes": ""}


GET = 0x0021983A
OLD_GET, NEW_GET = F.pins[GET][0], F.respell(F.pins[GET][0])
REAL = "?get_allocator@?$vector@H@_STL@@QBEXXZ"


def test_the_pin_respelled_is_the_same_pin(image, admission):
    assert admission.judge([pin(OLD_GET, GET)], [pin(NEW_GET, GET)], [owner(REAL, GET)], [owner(REAL, GET)]) == []


def test_the_old_pin_with_new_notes_is_not_gone(image, admission):
    """The review's repro: changed notes must not read as a respell."""
    rows = [owner(REAL, GET)]
    got = admission.judge([pin(OLD_GET, GET)], [pin(OLD_GET, GET, "other notes"), pin(NEW_GET, GET)], rows, rows)
    assert got and "already carries the real name" in got[0]
    spelled = dict(pin(OLD_GET, GET, "other notes"), address=f"0x{GET:08x}")      # nor another spelling of its address
    assert admission.judge([pin(OLD_GET, GET)], [spelled, pin(NEW_GET, GET)], rows, rows)
    # with no owner at the address only the new spelling can be refused: the old pin stays and they stack
    got = admission.judge([pin(OLD_GET, GET)], [pin(OLD_GET, GET, "other notes"), pin(NEW_GET, GET)], [], [])
    assert got and NEW_GET in got[0] and "already carries the real name" in got[0]


UNRELATED = "?unrelated@@YAXXZ"


def test_the_exemption_covers_the_one_respelled_pin(image, admission):
    """The review's repro: no owner at the address, the respelling, and a stranger beside it."""
    got = admission.judge([pin(OLD_GET, GET)], [pin(NEW_GET, GET), pin(UNRELATED, GET)], [], [])
    assert len(got) == 1 and UNRELATED in got[0] and "already carries the real name" in got[0]
    # and in the other order of the lines
    assert admission.judge([pin(OLD_GET, GET)], [pin(UNRELATED, GET), pin(NEW_GET, GET)], [], [])


def test_the_old_name_with_whitespace_is_still_the_old_name(image, admission):
    for spelled in (OLD_GET + " ", " " + OLD_GET, OLD_GET + "\t"):
        got = admission.judge([pin(OLD_GET, GET)], [pin(spelled, GET), pin(NEW_GET, GET)], [], [])
        # the old pin is not gone, so the respelling gets no exemption and is the line refused
        assert got and got[0].startswith(f"{admission.PINS}: {NEW_GET},") and "already carries the real name" in got[0], repr(spelled)


def test_the_respelling_may_not_appear_twice(image, admission):
    assert admission.judge([pin(OLD_GET, GET)], [pin(NEW_GET, GET, "one"), pin(NEW_GET, GET, "two")],
                           [owner(REAL, GET)], [owner(REAL, GET)])


def test_the_respelling_alone_is_still_admitted_with_no_owner(image, admission):
    assert admission.judge([pin(OLD_GET, GET)], [pin(NEW_GET, GET)], [], []) == []


def test_a_respelled_pin_may_change_its_notes_and_spelling(image, admission):
    rows = [owner(REAL, GET)]
    assert admission.judge([pin(OLD_GET, GET)], [dict(pin(NEW_GET, GET, "other"), address=f"0x{GET:08x}")], rows, rows) == []


def test_any_other_change_still_stacks_a_second_name(image, admission):
    rows = [owner(REAL, GET)]
    other = "?get_allocator@?$vector@D@_STL@@QBEXXZ"
    assert admission.judge([pin(other, GET)], [pin(NEW_GET, GET)], rows, rows)          # not the family's old pin
    assert admission.judge([pin(OLD_GET, GET)], [pin(OLD_GET, GET), pin(NEW_GET, GET)], rows, rows)   # the old one stays
    assert admission.judge([pin(OLD_GET, GET)], [pin(NEW_GET.replace("Enable", "Disable"), GET)], rows, rows)
    assert admission.judge([], [pin(NEW_GET, GET)], rows, rows)                          # nothing was respelled
    moved = 0x00523D6C
    named = [owner(REAL, moved)]
    assert admission.judge([pin(OLD_GET, moved)], [pin(NEW_GET, moved)], named, named)  # the family's name, elsewhere
    assert admission.judge([pin(OLD_GET, GET)], [pin(NEW_GET, moved)], named, named)    # respelled onto another address


def test_a_fact_retail_does_not_hold_stops_the_pin(image, admission):
    rows = [owner(REAL, GET)]
    fact = F.facts()[0]
    image[fact.site] = (image[fact.site] + 1) & 0xFF
    assert admission.judge([pin(OLD_GET, GET)], [pin(NEW_GET, GET)], rows, rows)
    assert not R.pin_respell_proven(OLD_GET, NEW_GET, GET)


def test_the_table_reads_retail():
    """The real facts on the real image, where one is present."""
    build = R.build
    if not Path(build.EXE).exists():
        pytest.skip("no retail image here")
    assert R.facts_problems(F.facts()) == []
    assert struct.unpack("<I", R.read_retail(F.copy + F.copy_store, 4))[0] == F.table


# ---- P69: a family that spells its members out, a slot fact, and the table's name by the owner's fact

def test_the_existing_familys_spellings_are_unchanged():
    pairs = sorted((old, F.respell(old)) for old, _facts in [*F.rows.values(), *F.pins.values()])
    assert F.spellings is None
    assert hashlib.sha256(repr(pairs).encode()).hexdigest() == "07c2439204df7910aa8c72235ecf26b3a9f370e793bb311d916336a1e4689dc2"
    assert NEW_COPY == "??0EnableRegionRecord@@QAE@ABV0@@Z"


def spelled(**overrides):
    args = dict(old="Old", new="New", table=0x00C00000, copy=0x1000, copy_store=0, owner=dict(name="??0New@@QAE@XZ", rva=0x2000, facts=()),
                rows={0x1000: ("??0Old@@QAE@ABV0@@Z", ()), 0x1100: ("?xfer@Old@@MAEXPAVXfer@@@Z", ())},
                pins={}, spellings={"??0Old@@QAE@ABV0@@Z": "??0New@@QAE@ABV0@@Z", "?xfer@Old@@MAEXPAVXfer@@@Z": "?xfer@New@@MAEXPAVXfer@@@Z"})
    args.update(overrides)
    return R.Family(**args)


def test_a_spelled_family_writes_each_member_out():
    family = spelled()
    assert family.respell("?xfer@Old@@MAEXPAVXfer@@@Z") == "?xfer@New@@MAEXPAVXfer@@@Z"
    assert family.respell("?other@Old@@QAEXXZ") == "?other@Old@@QAEXXZ"


def test_a_row_the_spellings_leave_out_refuses():
    with pytest.raises(ValueError, match="needs a spelling"):
        spelled(spellings={"??0Old@@QAE@ABV0@@Z": "??0New@@QAE@ABV0@@Z"})


def test_a_pin_the_spellings_leave_out_refuses():
    with pytest.raises(ValueError, match="needs a spelling"):
        spelled(pins={0x1200: ("?pinned@Old@@QAEXXZ", ())})


def test_a_spelling_to_itself_refuses():
    with pytest.raises(ValueError, match="needs a spelling"):
        spelled(spellings={"??0Old@@QAE@ABV0@@Z": "??0New@@QAE@ABV0@@Z", "?xfer@Old@@MAEXPAVXfer@@@Z": "?xfer@Old@@MAEXPAVXfer@@@Z"})


def test_a_spelling_of_no_row_refuses():
    with pytest.raises(ValueError, match="no row or pin"):
        spelled(spellings={"??0Old@@QAE@ABV0@@Z": "??0New@@QAE@ABV0@@Z", "?xfer@Old@@MAEXPAVXfer@@@Z": "?xfer@New@@MAEXPAVXfer@@@Z",
                           "?stray@Old@@QAEXXZ": "?stray@New@@QAEXXZ"})


TABLE = 0x00C00000
WORDS = {0x00800000: 0x00401000, 0x00800004: 0x00402000, 0x00800008: 0x41414141}


@pytest.fixture
def table_image(monkeypatch):
    words = dict(WORDS)

    def read(rva, size):
        assert size == 4
        return struct.pack("<I", words[rva])
    monkeypatch.setattr(R, "read_retail", read)
    monkeypatch.setattr(R, "section_name", lambda rva: ".text" if rva < 0x00700000 else ".rdata" if rva < 0x00900000 else ".data")
    return words


def test_a_slot_retail_holds_is_no_problem(table_image):
    assert R.expected(R.slot(TABLE, 1, 2, 0x2000)) == struct.pack("<I", 0x00402000)
    assert R.facts_problems([R.slot(TABLE, 0, 2, 0x1000), R.slot(TABLE, 1, 2, 0x2000)]) == []
    assert R.record([R.slot(TABLE, 1, 2, 0x2000)]) == "retail:0x00800004 slot=0x00402000"
    assert R.well_formed(R.record([R.slot(TABLE, 1, 2, 0x2000)]))


def test_a_slot_pointing_elsewhere_refuses(table_image):
    assert "holds" in R.facts_problems([R.slot(TABLE, 1, 2, 0x3000)])[0]


def test_a_slot_past_the_tables_count_refuses(table_image):
    fact = R.Fact("slot", 0x00800008, 0x41414141, (TABLE, 2, 2))
    assert "outside" in R.facts_problems([fact])[0]


def test_a_slot_off_its_table_refuses(table_image):
    fact = R.Fact("slot", 0x00800004, 0x00402000, (TABLE, 0, 2))
    assert "is not slot" in R.facts_problems([fact])[0]


def test_a_table_outside_rdata_refuses(table_image, monkeypatch):
    monkeypatch.setattr(R, "section_name", lambda rva: ".text" if rva < 0x00700000 else ".data")
    assert ".rdata" in R.facts_problems([R.slot(TABLE, 0, 2, 0x1000)])[0]


def test_a_target_outside_text_refuses(table_image):
    table_image[0x00800000] = 0x00C00000
    assert "not in .text" in R.facts_problems([R.Fact("slot", 0x00800000, 0x00C00000, (TABLE, 0, 2))])[0]


def test_a_table_longer_than_its_count_refuses(table_image):
    table_image[0x00800008] = 0x00403000
    assert "more than 2 slots" in R.facts_problems([R.slot(TABLE, 0, 2, 0x1000)])[0]


def test_an_unreadable_slot_is_a_problem(table_image):
    del table_image[0x00800008]
    assert "cannot be read" in R.facts_problems([R.slot(TABLE, 0, 2, 0x1000)])[0]


def aliased(**overrides):
    row = dict(name=f"??_7{F.old}@@6B@", names=f"{F.table_name};??_7{F.old}@@6B@")
    row.update(overrides)
    return row


def test_the_name_column_is_enough_as_before(image):
    assert R.table_named(F, dict(name=F.table_name, names=""), 0x100)


def test_an_alias_with_the_owners_store_names_the_table(image):
    assert R.table_named(F, aliased(), 0x100)


def test_an_alias_needs_the_stand_ins_table(image):
    assert not R.table_named(F, aliased(name="??_7Stranger@@6B@"), 0x100)


def test_no_alias_names_nothing(image):
    assert not R.table_named(F, aliased(names=f"??_7{F.old}@@6B@"), 0x100)


def test_an_alias_whose_family_has_no_table_fact_refuses(image):
    family = R.Family(F.old, F.new, F.table, F.copy, F.copy_store, dict(F.owner, facts=()), F.rows, F.pins)
    assert not R.table_named(family, aliased(), 0x100)


def test_an_alias_whose_store_is_another_table_refuses(image):
    other = dict(F.owner, facts=(R.Fact("stores", F.owner["rva"], F.table + 4, "c701"),))
    family = R.Family(F.old, F.new, F.table, F.copy, F.copy_store, other, F.rows, F.pins)
    assert not R.table_named(family, aliased(), 0x100)


def test_an_alias_whose_store_is_outside_the_owner_refuses(image):
    assert not R.table_named(F, aliased(), 0)


def test_an_alias_whose_store_retail_does_not_hold_refuses(image):
    site = F.owner["facts"][0].site
    image[site] = (image[site] + 1) & 0xFF
    assert not R.table_named(F, aliased(), 0x100)


def owner_fact(image, monkeypatch, code):
    """F's owner holding one stores fact of the table at its first byte, and retail holding it."""
    at = F.owner["rva"]
    fact = R.C("stores", at, F.table, code)
    for i, byte in enumerate(R.expected(fact)):
        image[at + i] = byte
    monkeypatch.setattr(F, "owner", dict(F.owner, facts=(fact,)))
    return fact


def test_an_alias_backed_by_a_load_refuses(image, monkeypatch):
    owner_fact(image, monkeypatch, "b8")
    assert not R.table_named(F, aliased(), 0x100)


def test_an_alias_backed_by_a_store_into_another_field_refuses(image, monkeypatch):
    owner_fact(image, monkeypatch, "c74104")
    assert not R.table_named(F, aliased(), 0x100)


def test_an_alias_needs_the_whole_store_inside_the_owner(image, monkeypatch):
    owner_fact(image, monkeypatch, "c701")
    assert R.table_named(F, aliased(), 6)
    assert not R.table_named(F, aliased(), 5)
    assert not R.table_named(F, aliased(), 1)


def test_the_plan_takes_the_alias_only_at_the_tables_address(tree):
    ledger = (tree / "reverse/data_ledger.csv").read_text()
    aliased_row = ledger.replace(f",{F.table_name},", f",??_7{F.old}@@6B@,", 1)
    assert aliased_row != ledger
    fields = [line for line in aliased_row.splitlines() if line.startswith(f"0x{TABLE_RVA:08X},")][0].split(",")
    fields[7] = f"{F.table_name};??_7{F.old}@@6B@"
    good = "\n".join([aliased_row.splitlines()[0], ",".join(fields)]) + "\n"
    write(tree / "reverse/data_ledger.csv", good)
    ctx, _ = context(tree)
    plan(ctx)
    wrong = good.replace(f"0x{TABLE_RVA:08X},", f"0x{TABLE_RVA + 16:08X},")
    write(tree / "reverse/data_ledger.csv", wrong)
    ctx, _ = context(tree)
    with pytest.raises(Refusal, match="does not name"):
        plan(ctx)


# ---- a declared leaf: no reference can show its binding survived, so retail and the rebuilt body must show there is none

LEAF = 0x00566527


def row_size(tree, at):
    for line in (tree / "reverse/functions.csv").read_text().splitlines():
        fields = line.split(",")
        if len(fields) > 3 and fields[2].startswith("0x") and int(fields[2], 16) == at:
            return int(fields[3])
    raise AssertionError(hex(at))


@pytest.fixture
def leaf(tree, image, monkeypatch):
    """F with one row declared a leaf, and retail's body there a plain leaf of the row's size."""
    size = row_size(tree, LEAF)
    saved = {at: image[at] for at in image if LEAF <= at < LEAF + size}
    for at in range(LEAF, LEAF + size):
        image[at] = 0x90
    image[LEAF + size - 1] = 0xC3
    monkeypatch.setattr(F, "leaves", {LEAF: size})
    monkeypatch.setattr(R, "section_name", lambda rva: ".text" if rva < 0x00700000 else ".rdata" if rva < 0x00900000 else None)
    monkeypatch.setattr(R, "image_size", lambda: 0x00900000)
    # the row's own facts sit in the body this fixture replaced: the leaf checks are what is under test here
    monkeypatch.setattr(R, "facts_problems", lambda facts: [])
    return size, saved


def leaf_context(tree, relocs=()):
    ctx, state = context(tree)
    new = F.respell(F.rows[LEAF][0])
    ctx.object_symbol_relocs = lambda source, name: list(relocs) if name == new else GOOD_RELOCS
    return ctx, state


def without_leaf():
    return [r for r in after_refs() if r["rva"] != LEAF]


def test_a_declared_leaf_with_no_relocations_lands(tree, leaf):
    ctx, state = leaf_context(tree)
    apply(ctx, plan(ctx), state, refs=without_leaf())


def test_a_declared_leaf_that_gains_a_relocation_is_undone(tree, leaf):
    ctx, state = leaf_context(tree, relocs=[(1, rename.REL32, "?target@@YAXXZ")])
    with pytest.raises(VerifyFailed, match="declared leaf .* has 1 relocation"):
        apply(ctx, plan(ctx), state, refs=without_leaf())


def test_a_declared_leaf_that_cannot_be_read_is_undone(tree, leaf):
    ctx, state = leaf_context(tree)
    ctx.object_symbol_relocs = lambda source, name: None if name == F.respell(F.rows[LEAF][0]) else GOOD_RELOCS
    with pytest.raises(VerifyFailed, match="declared leaf .* cannot be read"):
        apply(ctx, plan(ctx), state, refs=without_leaf())


def test_an_undeclared_row_with_no_references_is_still_undone(tree, leaf):
    ctx, state = leaf_context(tree)
    missing = [r for r in without_leaf() if r["rva"] != F.copy]
    with pytest.raises(VerifyFailed, match="no references"):
        apply(ctx, plan(ctx), state, refs=missing)


@pytest.mark.parametrize("label, body, message", [
    ("a call out", bytes.fromhex("e800010000"), "branches out"),
    ("a jump out", bytes.fromhex("e900010000"), "branches out"),
    ("an address loaded", bytes.fromhex("b800104000"), "image address"),
    ("an address read", bytes.fromhex("a100104000"), "image address"),
    ("the image's first byte, in no section", bytes.fromhex("b800004000"), "image address"),
    ("the image's last byte", bytes.fromhex("b8ffffcf00"), "image address"),
])
def test_a_body_retail_shows_referencing_something_is_no_leaf(tree, leaf, image, label, body, message):
    for i, byte in enumerate(body):
        image[LEAF + i] = byte
    ctx, _ = leaf_context(tree)
    with pytest.raises(Refusal, match=message):
        plan(ctx)


def test_a_jump_inside_the_body_is_still_a_leaf(tree, leaf, image):
    image[LEAF], image[LEAF + 1] = 0xEB, 0x00
    ctx, _ = leaf_context(tree)
    plan(ctx)


def test_a_small_constant_is_not_an_address(tree, leaf, image):
    for i, byte in enumerate(bytes.fromhex("b810000000")):
        image[LEAF + i] = byte
    ctx, _ = leaf_context(tree)
    plan(ctx)


def test_a_value_past_the_image_is_not_an_address(tree, leaf, image):
    for i, byte in enumerate(bytes.fromhex("b80000d000")):
        image[LEAF + i] = byte
    ctx, _ = leaf_context(tree)
    plan(ctx)


def test_a_body_that_does_not_decode_is_no_leaf(tree, leaf, image):
    size, _ = leaf
    image[LEAF + size - 1] = 0xE8
    ctx, _ = leaf_context(tree)
    with pytest.raises(Refusal, match="no leaf"):
        plan(ctx)


def test_an_unreadable_body_is_no_leaf(tree, leaf, image):
    del image[LEAF]
    ctx, _ = leaf_context(tree)
    with pytest.raises(Refusal, match="no leaf: it cannot be read"):
        plan(ctx)


# ---- a row proved by its store of the table: its references are data, which the scan does not read

def store_row(image, monkeypatch, code="c701", offset=2, value=None, site=LEAF):
    """F with the row at LEAF holding one stores fact, retail holding it too, and that store declared."""
    old, _facts = F.rows[LEAF]
    fact = R.C("stores", site, F.table if value is None else value, code)
    for i, byte in enumerate(R.expected(fact)):
        image[site + i] = byte
    monkeypatch.setattr(F, "rows", {**F.rows, LEAF: (old, (fact,))})
    monkeypatch.setattr(F, "table_stores", {LEAF: offset})
    return fact


def store_context(tree, relocs):
    ctx, state = context(tree)
    new = F.respell(F.rows[LEAF][0])
    ctx.object_symbol_relocs = lambda source, name: relocs if name == new else GOOD_RELOCS
    return ctx, state


def test_a_row_binding_the_table_at_its_store_lands(tree, image, monkeypatch):
    store_row(image, monkeypatch)
    ctx, state = store_context(tree, [(2, rename.DIR32, F.table_name)])
    apply(ctx, plan(ctx), state, refs=without_leaf())


@pytest.mark.parametrize("label, relocs", [
    ("another table", [(2, rename.DIR32, "??_7Other@@6B@")]),
    ("another offset", [(8, rename.DIR32, F.table_name)]),
    ("another reference kind", [(2, rename.REL32, F.table_name)]),
    ("nothing", []),
])
def test_a_row_that_stops_binding_the_table_is_undone(tree, image, monkeypatch, label, relocs):
    store_row(image, monkeypatch)
    ctx, state = store_context(tree, relocs)
    with pytest.raises(VerifyFailed, match="does not store"):
        apply(ctx, plan(ctx), state, refs=without_leaf())


def test_a_store_that_cannot_be_read_is_undone(tree, image, monkeypatch):
    store_row(image, monkeypatch)
    ctx, state = store_context(tree, None)
    with pytest.raises(VerifyFailed, match="cannot be read"):
        apply(ctx, plan(ctx), state, refs=without_leaf())


def only_the_store_is_read(monkeypatch):
    """The whole family's facts pass, so a refusal can only come from the store's own read."""
    real = R.facts_problems
    monkeypatch.setattr(R, "facts_problems", lambda facts: real(facts) if len(facts) == 1 else [])


def test_a_table_store_retail_does_not_hold_refuses(tree, image, monkeypatch):
    store_row(image, monkeypatch)
    only_the_store_is_read(monkeypatch)
    image[LEAF + 2] ^= 0xFF
    ctx, _ = store_context(tree, [(2, rename.DIR32, F.table_name)])
    with pytest.raises(Refusal, match="does not store the table: retail at .* holds"):
        plan(ctx)


def test_a_table_store_retail_cannot_read_refuses(tree, image, monkeypatch):
    store_row(image, monkeypatch)
    only_the_store_is_read(monkeypatch)
    del image[LEAF + 2]
    ctx, _ = store_context(tree, [(2, rename.DIR32, F.table_name)])
    with pytest.raises(Refusal, match="does not store the table: .* cannot be read"):
        plan(ctx)


@pytest.mark.parametrize("label, kwargs", [
    ("a load, not a store", dict(code="b8", offset=1)),
    ("a store into another field", dict(code="c74104", offset=3)),
    ("a store of another table", dict(value=F.table + 4)),
    ("a store declared at the wrong offset", dict(offset=3)),
])
def test_a_row_whose_fact_is_not_the_table_store_refuses(tree, image, monkeypatch, label, kwargs):
    store_row(image, monkeypatch, **kwargs)
    ctx, _ = store_context(tree, [(kwargs.get("offset", 2), rename.DIR32, F.table_name)])
    with pytest.raises(Refusal, match="declares no store"):
        plan(ctx)


def test_a_row_declaring_a_store_without_its_fact_refuses(tree, monkeypatch):
    monkeypatch.setattr(F, "table_stores", {LEAF: 2})
    ctx, _ = store_context(tree, [(2, rename.DIR32, F.table_name)])
    with pytest.raises(Refusal, match="declares no store"):
        plan(ctx)


def test_a_store_past_the_row_refuses(tree, image, monkeypatch):
    store_row(image, monkeypatch, site=LEAF + 6, offset=8)
    ctx, _ = store_context(tree, [(8, rename.DIR32, F.table_name)])
    with pytest.raises(Refusal, match="past its row"):
        plan(ctx)


def stored_rows(code="c701"):
    return {0x1000: ("??0Old@@QAE@ABV0@@Z", ()),
            0x1100: ("?xfer@Old@@MAEXPAVXfer@@@Z", (R.C("stores", 0x1100, 0x00C00000, code),))}


def test_a_store_starting_before_its_row_refuses():
    rows = stored_rows()
    rows[0x1100] = (rows[0x1100][0], (R.C("stores", 0x10FE, 0x00C00000, "c701"),))
    with pytest.raises(ValueError, match="declares no store"):
        spelled(rows=rows, table_stores={0x1100: 0})


def test_a_family_may_declare_its_table_store():
    assert spelled(rows=stored_rows(), table_stores={0x1100: 2}).table_stores == {0x1100: 2}
    assert spelled().table_stores == {}


@pytest.mark.parametrize("label, kwargs, message", [
    ("no row", dict(table_stores={0x9999: 2}), "no row of the family"),
    ("no fact", dict(table_stores={0x1100: 2}), "declares no store"),
    ("a leaf too", dict(rows=stored_rows(), table_stores={0x1100: 2}, leaves={0x1100: 8}), "both a leaf and a store"),
    ("another opcode", dict(rows=stored_rows("b8"), table_stores={0x1100: 1}), "declares no store"),
])
def test_a_family_declaring_a_bad_table_store_refuses(label, kwargs, message):
    with pytest.raises(ValueError, match=message):
        spelled(**kwargs)


def test_a_leaf_at_the_wrong_size_refuses(tree, leaf, monkeypatch):
    size, _ = leaf
    monkeypatch.setattr(F, "leaves", {LEAF: size + 1})
    ctx, _ = leaf_context(tree)
    with pytest.raises(Refusal, match="declared"):
        plan(ctx)


def test_a_leaf_that_is_no_row_refuses():
    with pytest.raises(ValueError, match="no row of the family"):
        spelled(leaves={0x9999: 3})


def test_locomotor_spells_every_row_under_the_class():
    family = R.LOCOMOTOR
    assert family.copy in family.rows and family.pins == {}
    for _old, _facts in family.rows.values():
        assert "Rva001E3E43" not in family.respell(_old) and "Locomotor" in family.respell(_old)
    assert family.evidence() == "retail:0x001E4663 stores=0x00BDE888"
    assert R.family_of(family.copy, "??0Locomotor@@QAE@ABV0@@Z") is family


def test_locomotors_slot_facts_name_its_table():
    kinds = [f for f in R.LOCOMOTOR.facts() if f.kind == "slot"]
    assert sorted(f.code for f in kinds) == [(0x00BDE888, 0, 4), (0x00BDE888, 3, 4)]
    assert {f.value for f in kinds} == {0x005E4625, 0x005E525A}


def test_locomotors_alias_is_backed_by_its_owner(monkeypatch):
    held = {f.site: R.expected(f) for f in R.LOCOMOTOR.owner["facts"]}
    monkeypatch.setattr(R, "read_retail", lambda rva, size: held[rva])
    row = dict(name="??_7Rva001E3E43@@6B@", names="??_7Locomotor@@6B@;??_7Rva001E3E43@@6B@")
    assert R.table_named(R.LOCOMOTOR, row, 395)
    assert not R.table_named(R.LOCOMOTOR, dict(row, names="??_7Rva001E3E43@@6B@"), 395)
    assert not R.table_named(R.LOCOMOTOR, dict(row, name="??_7Locomotor2@@6B@"), 395)


def test_only_locomotor_declares_exceptions_and_only_these():
    assert R.LOCOMOTOR.leaves == {0x001E3CF4: 335, 0x001E525A: 382}
    assert R.LOCOMOTOR.table_stores == {0x001E3E43: 2}
    assert [f.new for f in R.FAMILIES if getattr(f, "leaves", None) or getattr(f, "table_stores", None)] == ["Locomotor"]


def test_locomotors_exceptions_hold_in_retail():
    if not Path(R.build.EXE).exists():
        pytest.skip("no retail image here")
    assert R.leaf_problem(0x001E3CF4, 335) is None
    assert R.leaf_problem(0x001E525A, 382) is None
    assert R.facts_problems([R.table_store_fact(R.LOCOMOTOR, 0x001E3E43)]) == []
    # the destructor stores the table, so it could not have passed as a leaf
    assert R.leaf_problem(0x001E3E43, 19) is not None
    # the copy ctor beside it references plenty, so the check can tell them apart
    assert R.leaf_problem(0x001E4641, 78) is not None
