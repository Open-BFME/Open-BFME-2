"""`tools/rename.py function --respell --identity --basis retail`: a class family respelled on
retail's own bytes (tools/retail_identity.py), with one row moved alone into its approved unit.

The real family's table is the fixture: its facts are served from an image the test writes, each
one breakable alone, and its rows and pins are ledger rows at their real addresses."""
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
