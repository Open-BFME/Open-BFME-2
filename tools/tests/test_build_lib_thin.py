"""build.compile_function on library-member rows: every relocation site of a
lib member is masked, and a masked comparison over fewer than MIN_LIB_CONCRETE
bytes is refused as thin. A site counts as concrete only when retail proves its
four bytes (build.proven_rel32_sites): it is the member's own REL32, with
addend 0, touched by no other relocation, and retail's displacement lands
exactly on the start of the one matched ledger row that IS the symbol the
relocation names (build.ledger_entry_points). Anything short of that -- a
symbols.csv pin, a build_call_thunks() hit, an alias, gen-alias, gen-dump or
unmatched row, a name two rows share, a nonzero addend, any other relocation
type -- stays masked, and a thin body is still refused.

The symbol map is built by the real load_symbol_map from the fixture's rows,
pins and thunk scan, so a credit that consulted the resolver's candidate list
instead of the rows is exercised against exactly the entries it would accept.
The last test runs the real @__security_check_cookie@4 row against the real
msvcrt.lib member, retail image and ledger."""
import csv
import struct
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
import build  # noqa: E402
import coffar  # noqa: E402

RVA = 0x00629BAB
CALLEE = 0x00629B7A
COOKIE_VA = 0x00DD7F10
# The body's own jmp opcode: build_call_thunks() reports it as a "thunk" of
# whatever it jumps to (retail: 0x00629BB4 in _report_failure's list).
OWN_JMP = RVA + 9
FORWARDER = 0x00747640
SITE = 10   # the jmp's REL32 operand


def body(rel_to):
    """cmp ecx,[cookie]; jne +1; ret; jmp rel_to  (14 bytes, 6 outside relocations)."""
    jmp_end = RVA + 14
    return (b"\x3b\x0d" + struct.pack("<I", COOKIE_VA) + b"\x75\x01\xc3\xe9"
            + struct.pack("<i", rel_to - jmp_end))


MEMBER = b"\x3b\x0d\0\0\0\0\x75\x01\xc3\xe9\0\0\0\0"
RELOCS = [(2, build.DIR32, "___security_cookie"), (SITE, build.REL32, "_report_failure")]
ROW = {"name": "@__security_check_cookie@4", "export_rva": "", "target_rva": f"0x{RVA:08X}",
       "target_size": "14", "source": "vendor/msvc71crt/msvcrt.lib", "status": "matched",
       "notes": "vendored=msvc71-crt;member=build\\intel\\dll_obj\\secchk.obj"}


@pytest.fixture
def lib(monkeypatch, tmp_path):
    rows, pins, thunks, reviewed = [], [], {}, set()
    symbols_csv = tmp_path / "symbols.csv"
    monkeypatch.setattr(build, "load_all_function_rows", lambda: [dict(row) for row in rows])
    monkeypatch.setattr(build, "build_call_thunks",
                        lambda: {body_rva: list(at) for body_rva, at in thunks.items()})
    monkeypatch.setattr(build, "SYMBOLS", symbols_csv)
    monkeypatch.setattr(build, "gate_baselined",
                        lambda check, row: (check, row["name"]) in reviewed)

    def row(name, rva, size=49, notes="", status="matched"):
        rows.append({"name": name, "export_rva": "", "target_rva": f"0x{rva:08X}",
                     "target_size": str(size), "source": "vendor/msvc71crt/msvcrt.lib",
                     "status": status, "notes": notes})

    def setup(retail, member=MEMBER, relocs=RELOCS):
        with symbols_csv.open("w", newline="") as handle:
            writer = csv.writer(handle)
            writer.writerow(["name", "address", "notes"])
            writer.writerows([name, f"0x{address:08X}", ""] for name, address in pins)
        build.ledger_entry_points.cache_clear()
        setup.symbol_map = build.load_symbol_map()
        monkeypatch.setattr(build, "read_target_bytes", lambda rva, size: retail[:size])
        monkeypatch.setattr(build, "read_object_symbol_bytes",
                            lambda output, symbol, size, code_only=False: (member[:size], list(relocs)))
        return build.compile_function(dict(ROW), setup.symbol_map, Path("unused.obj"))

    setup.row, setup.pins, setup.thunks, setup.reviewed = row, pins, thunks, reviewed
    yield setup
    build.ledger_entry_points.cache_clear()


def thin(patch):
    return patch["masked"] and patch["concrete"] < build.MIN_LIB_CONCRETE


def refused(patch):
    """The site stayed masked: only the six bytes between relocations count."""
    assert patch["bytes"] == patch["target"]      # the mask still hides the difference
    assert patch["concrete"] == 6
    assert thin(patch)
    return True


def test_call_to_the_rowed_callee_is_concrete(lib):
    lib.row("_report_failure", CALLEE)
    patch = lib(body(CALLEE))
    assert patch["bytes"] == patch["target"]
    assert patch["concrete"] == 10
    assert not thin(patch)


def test_an_object_symbol_that_is_the_name_is_still_the_row(lib):
    # object-symbol= naming the row's own name rebinds nothing.
    lib.row("_report_failure", CALLEE, notes="vendored=x;object-symbol=_report_failure")
    assert lib(body(CALLEE))["concrete"] == 10


# --- wrong landing -----------------------------------------------------------

@pytest.mark.parametrize("lands", [CALLEE + 1, CALLEE + 0x40, CALLEE - 5, RVA])
def test_call_landing_anywhere_but_the_row_start_stays_masked(lib, lands):
    lib.row("_report_failure", CALLEE)
    assert refused(lib(body(lands)))


def test_landing_on_a_different_rowed_function_stays_masked(lib):
    lib.row("_report_failure", CALLEE)
    lib.row("_some_other_function", CALLEE + 0x100)
    assert refused(lib(body(CALLEE + 0x100)))


def test_callee_without_an_address_stays_masked(lib):
    assert refused(lib(body(CALLEE)))


# --- pins and thunk-scan candidates --------------------------------------------

def test_pin_without_a_row_stays_masked(lib):
    # A symbols.csv pin is an unproven candidate: the resolver accepts it, the
    # credit must not.
    lib.pins.append(("_report_failure", CALLEE))
    patch = lib(body(CALLEE))
    assert CALLEE in lib.symbol_map["_report_failure"]
    assert refused(patch)


def test_pin_beside_the_row_stays_masked(lib):
    # The row is elsewhere; a pin at the landing is still only a candidate.
    lib.row("_report_failure", CALLEE)
    lib.pins.append(("_report_failure", CALLEE + 0x200))
    patch = lib(body(CALLEE + 0x200))
    assert CALLEE + 0x200 in lib.symbol_map["_report_failure"]
    assert refused(patch)


def test_jmp_inside_a_body_is_not_the_callee(lib):
    # The thunk scan lists the body's own jmp as a "thunk" of its target; a
    # call landing there lands mid-function, never on the named callee.
    lib.row("_report_failure", CALLEE)
    lib.thunks[CALLEE] = [OWN_JMP]
    patch = lib(body(OWN_JMP))
    assert OWN_JMP in lib.symbol_map["_report_failure"]
    assert refused(patch)


def test_rowed_forwarder_is_not_the_callee(lib):
    # A separate function that only jumps to the callee (retail:
    # _lua_pushcclosure, listed under _luaV_Cclosure) is a different function.
    lib.row("_report_failure", CALLEE)
    lib.row("_forwards_to_report_failure", FORWARDER, size=5)
    lib.thunks[CALLEE] = [FORWARDER]
    patch = lib(body(FORWARDER))
    assert FORWARDER in lib.symbol_map["_report_failure"]
    assert refused(patch)


# --- rows that are not the callee's own ---------------------------------------

def test_unreviewed_alias_row_is_no_evidence(lib):
    lib.row("_report_failure", CALLEE, notes="object-symbol=_some_other_body")
    assert refused(lib(body(CALLEE)))


def test_reviewed_alias_row_is_no_evidence_either(lib):
    # The alias-row register excuses a row from the alias check, so the
    # resolver may use it; it does not make someone else's bytes the callee.
    lib.row("_report_failure", CALLEE, notes="object-symbol=_some_other_body")
    lib.reviewed.add(("alias-row", "_report_failure"))
    patch = lib(body(CALLEE))
    assert CALLEE in lib.symbol_map["_report_failure"]
    assert refused(patch)


def test_gen_alias_row_is_no_evidence(lib):
    lib.row("_report_failure", CALLEE,
            notes="gen-alias;object-symbol=_report_failure;C++ alias")
    assert refused(lib(body(CALLEE)))


def test_gen_dump_row_is_no_evidence(lib):
    lib.row("_report_failure", CALLEE, notes="gen-dump byte-true placeholder")
    assert refused(lib(body(CALLEE)))


def test_unmatched_row_is_no_evidence(lib):
    lib.row("_report_failure", CALLEE, status="blocked")
    assert refused(lib(body(CALLEE)))


@pytest.mark.parametrize("lands", [CALLEE, CALLEE + 0x400])
def test_a_name_two_rows_share_has_no_row(lib, lands):
    lib.row("_report_failure", CALLEE)
    lib.row("_report_failure", CALLEE + 0x400)
    assert refused(lib(body(lands)))


# --- the site itself -----------------------------------------------------------

@pytest.mark.parametrize("addend,lands", [(-4, CALLEE), (4, CALLEE + 4), (4, CALLEE), (1, CALLEE + 1)])
def test_nonzero_addend_stays_masked(lib, addend, lands):
    lib.row("_report_failure", CALLEE)
    member = MEMBER[:SITE] + struct.pack("<i", addend)
    assert refused(lib(body(lands), member=member))


def test_data_relocation_is_never_credited(lib):
    lib.row("_report_failure", CALLEE)
    # every address the site could be read as: an absolute RVA, and the place a
    # displacement of those four bytes would land
    lib.row("___security_cookie", COOKIE_VA - build.IMAGE_BASE, size=4)
    patch = lib(body(CALLEE))
    assert patch["concrete"] == 10                # only the REL32 site, not the DIR32


def test_data_relocation_landing_like_a_call_is_never_credited(lib):
    lib.row("___security_cookie", (RVA + 2 + 4 + COOKIE_VA) & 0xFFFFFFFF, size=4)
    patch = lib(body(CALLEE))
    assert refused(patch)


@pytest.mark.parametrize("rtype", sorted(set(coffar.RELOC_WIDTH) - {build.REL32}))
def test_only_rel32_is_credited(lib, rtype):
    # The jmp operand itself, named for the rowed callee and landing on it,
    # under any relocation type but REL32.
    lib.row("_report_failure", CALLEE)
    relocs = [RELOCS[0], (SITE, rtype, "_report_failure")]
    patch = lib(body(CALLEE), relocs=relocs)
    # only the cookie's four bytes and this site's own width stay covered
    assert patch["concrete"] == 14 - 4 - coffar.RELOC_WIDTH[rtype]


def test_a_site_another_relocation_touches_stays_masked(lib):
    lib.row("_report_failure", CALLEE)
    relocs = RELOCS + [(SITE + 2, 0x000A, "_report_failure")]
    assert refused(lib(body(CALLEE), relocs=relocs))


def test_a_site_past_the_row_end_is_never_credited(lib):
    lib.row("_report_failure", CALLEE)
    build.ledger_entry_points.cache_clear()
    retail = body(CALLEE)
    # same site, read against a 12-byte extent that cuts the operand in half
    assert build.proven_rel32_sites(RVA, retail[:12], MEMBER, RELOCS) == []
    assert build.proven_rel32_sites(RVA, retail, MEMBER, RELOCS) == [SITE]


# --- the real CRT sibling call ------------------------------------------------

def test_real_security_check_cookie_credits_its_report_failure_call(tmp_path):
    # Real msvcrt.lib member, real retail bytes, real ledger: the jmp at +10
    # in @__security_check_cookie@4 lands on _report_failure's own row at
    # 0x00629B7A, and that is the only site credited -- the DIR32 at +2
    # (___security_cookie) stays masked.
    build.ledger_entry_points.cache_clear()
    try:
        row = next(r for r in build.load_function_rows()
                   if r["name"] == "@__security_check_cookie@4")
        assert build.ledger_entry_points()["_report_failure"] == CALLEE
        archive = dict(coffar.read_archive(build.ROOT / row["source"]))
        obj = tmp_path / "secchk.obj"
        obj.write_bytes(archive[build.ledger_member(row)])
        size = int(row["target_size"])
        member, relocs = build.read_object_symbol_bytes(
            obj, build.ledger_object_symbol(row), size, code_only=True)
        assert sorted((offset, rtype) for offset, rtype, _ in relocs if offset < size) == [
            (2, build.DIR32), (SITE, build.REL32)]
        retail = build.read_target_bytes(int(row["target_rva"], 16), size)
        assert build.proven_rel32_sites(RVA, retail, member, relocs) == [SITE]
        patch = build.compile_function(row, {}, obj)
        assert patch["bytes"] == patch["target"]
        assert patch["concrete"] == 10
        assert not thin(patch)
    finally:
        build.ledger_entry_points.cache_clear()
