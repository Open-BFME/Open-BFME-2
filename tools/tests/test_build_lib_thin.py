"""build.compile_function on library-member rows: every relocation site of a
lib member is masked, and a masked comparison over fewer than MIN_LIB_CONCRETE
bytes is refused as thin. A REL32 site counts as concrete only when it is
proven: the member's own call (addend 0) names a callee whose own ledger row
starts exactly where retail's displacement lands. A symbols.csv pin or a
build_call_thunks() hit is a resolver candidate, not a row, so a call landing
there stays masked, as does anything else short of a row, and a thin body is
still refused.

The symbol map is built by the real load_symbol_map from the fixture's rows,
pins and thunk scan, so a credit that consulted the resolver's candidate list
instead of the rows is exercised against exactly the entries it would accept."""
import csv
import struct
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
import build  # noqa: E402

RVA = 0x00629BAB
CALLEE = 0x00629B7A
COOKIE_VA = 0x00DD7F10
# The body's own jmp opcode: build_call_thunks() reports it as a "thunk" of
# whatever it jumps to (retail: 0x00629BB4 in _report_failure's list).
OWN_JMP = RVA + 9
FORWARDER = 0x00747640


def body(rel_to):
    """cmp ecx,[cookie]; jne +1; ret; jmp rel_to  (14 bytes, 6 outside relocations)."""
    jmp_end = RVA + 14
    return (b"\x3b\x0d" + struct.pack("<I", COOKIE_VA) + b"\x75\x01\xc3\xe9"
            + struct.pack("<i", rel_to - jmp_end))


MEMBER = b"\x3b\x0d\0\0\0\0\x75\x01\xc3\xe9\0\0\0\0"
RELOCS = [(2, 0x0006, "___security_cookie"), (10, 0x0014, "_report_failure")]
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

    def row(name, rva, size=49, notes=""):
        rows.append({"name": name, "export_rva": "", "target_rva": f"0x{rva:08X}",
                     "target_size": str(size), "source": "vendor/msvc71crt/msvcrt.lib",
                     "status": "matched", "notes": notes})

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


def test_call_to_the_rowed_callee_is_concrete(lib):
    lib.row("_report_failure", CALLEE)
    patch = lib(body(CALLEE))
    assert patch["bytes"] == patch["target"]
    assert patch["concrete"] == 10
    assert not thin(patch)


def test_call_landing_elsewhere_stays_masked(lib):
    lib.row("_report_failure", CALLEE)
    patch = lib(body(CALLEE + 0x40))
    assert patch["bytes"] == patch["target"]      # the mask still hides the difference
    assert patch["concrete"] == 6
    assert thin(patch)


def test_callee_without_an_address_stays_masked(lib):
    patch = lib(body(CALLEE))
    assert patch["concrete"] == 6
    assert thin(patch)


def test_nonzero_addend_stays_masked(lib):
    lib.row("_report_failure", CALLEE)
    member = MEMBER[:10] + struct.pack("<i", -4)
    patch = lib(body(CALLEE), member=member)
    assert patch["concrete"] == 6
    assert thin(patch)


def test_data_relocation_is_never_credited(lib):
    lib.row("_report_failure", CALLEE)
    # every address the site could be read as: an absolute RVA, and the place a
    # displacement of those four bytes would land
    lib.row("___security_cookie", COOKIE_VA - build.IMAGE_BASE, size=4)
    lib.row("___security_cookie", (RVA + 2 + 4 + COOKIE_VA) & 0xFFFFFFFF, size=4)
    patch = lib(body(CALLEE))
    assert patch["concrete"] == 10                # only the REL32 site, not the DIR32


def test_pin_without_a_row_stays_masked(lib):
    # A symbols.csv pin is an unproven candidate: the resolver accepts it, the
    # credit must not.
    lib.pins.append(("_report_failure", CALLEE))
    patch = lib(body(CALLEE))
    assert CALLEE in lib.symbol_map["_report_failure"]
    assert patch["concrete"] == 6
    assert thin(patch)


def test_jmp_inside_a_body_is_not_the_callee(lib):
    # The thunk scan lists the body's own jmp as a "thunk" of its target; a
    # call landing there lands mid-function, never on the named callee.
    lib.row("_report_failure", CALLEE)
    lib.thunks[CALLEE] = [OWN_JMP]
    patch = lib(body(OWN_JMP))
    assert OWN_JMP in lib.symbol_map["_report_failure"]
    assert patch["concrete"] == 6
    assert thin(patch)


def test_rowed_forwarder_is_not_the_callee(lib):
    # A separate function that only jumps to the callee (retail:
    # _lua_pushcclosure, listed under _luaV_Cclosure) is a different function.
    lib.row("_report_failure", CALLEE)
    lib.row("_forwards_to_report_failure", FORWARDER, size=5)
    lib.thunks[CALLEE] = [FORWARDER]
    patch = lib(body(FORWARDER))
    assert FORWARDER in lib.symbol_map["_report_failure"]
    assert patch["concrete"] == 6
    assert thin(patch)


def test_unreviewed_alias_row_is_no_evidence(lib):
    lib.row("_report_failure", CALLEE, notes="object-symbol=_some_other_body")
    patch = lib(body(CALLEE))
    assert patch["concrete"] == 6
    assert thin(patch)


def test_reviewed_alias_row_counts_like_the_resolver(lib):
    lib.row("_report_failure", CALLEE, notes="object-symbol=_some_other_body")
    lib.reviewed.add(("alias-row", "_report_failure"))
    patch = lib(body(CALLEE))
    assert CALLEE in lib.symbol_map["_report_failure"]
    assert patch["concrete"] == 10
    assert not thin(patch)
