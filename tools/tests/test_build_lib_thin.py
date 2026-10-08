"""build.compile_function on library-member rows: every relocation site of a
lib member is masked, and a masked comparison over fewer than MIN_LIB_CONCRETE
bytes is refused as thin. A REL32 site counts as concrete only when it is
proven: the member's own call (addend 0) names a callee the ledger places
exactly where retail's displacement lands. Anything short of that stays masked,
so a thin body is still refused."""
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
def lib(monkeypatch):
    def setup(retail, member=MEMBER, relocs=RELOCS):
        monkeypatch.setattr(build, "read_target_bytes", lambda rva, size: retail[:size])
        monkeypatch.setattr(build, "read_object_symbol_bytes",
                            lambda output, symbol, size, code_only=False: (member[:size], list(relocs)))
        return build.compile_function(dict(ROW), symbol_map, Path("unused.obj"))
    symbol_map = {}
    setup.symbols = symbol_map
    return setup


def thin(patch):
    return patch["masked"] and patch["concrete"] < build.MIN_LIB_CONCRETE


def test_call_to_the_rowed_callee_is_concrete(lib):
    lib.symbols["_report_failure"] = [CALLEE]
    patch = lib(body(CALLEE))
    assert patch["bytes"] == patch["target"]
    assert patch["concrete"] == 10
    assert not thin(patch)


def test_call_landing_elsewhere_stays_masked(lib):
    lib.symbols["_report_failure"] = [CALLEE]
    patch = lib(body(CALLEE + 0x40))
    assert patch["bytes"] == patch["target"]      # the mask still hides the difference
    assert patch["concrete"] == 6
    assert thin(patch)


def test_callee_without_an_address_stays_masked(lib):
    patch = lib(body(CALLEE))
    assert patch["concrete"] == 6
    assert thin(patch)


def test_nonzero_addend_stays_masked(lib):
    lib.symbols["_report_failure"] = [CALLEE]
    member = MEMBER[:10] + struct.pack("<i", -4)
    patch = lib(body(CALLEE), member=member)
    assert patch["concrete"] == 6
    assert thin(patch)


def test_data_relocation_is_never_credited(lib):
    lib.symbols["_report_failure"] = [CALLEE]
    # every address the site could be read as: an absolute RVA, and the place a
    # displacement of those four bytes would land
    lib.symbols["___security_cookie"] = [COOKIE_VA - build.IMAGE_BASE,
                                         (RVA + 2 + 4 + COOKIE_VA) & 0xFFFFFFFF]
    patch = lib(body(CALLEE))
    assert patch["concrete"] == 10                # only the REL32 site, not the DIR32
