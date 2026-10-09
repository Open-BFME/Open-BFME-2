"""tools/data_rows.py (ported from Open-BFME-1's tools/tests/test_data_rows.py).

Open-BFME-1 builds its fixtures with data_scaffold.Coff and
test_reloc_ledger.image_with, neither of which this repository has; the two
small writers below produce the same objects and image. Its provider_repair,
reloc_ledger reference-lookup, delta_sources and hook tests cover tools this
port does not include, and its dx8wrapper.cpp case names a BFME 1 source, so
they are not here. Tests that compile skip without MSVC 7.1.
"""
import struct
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import data_rows  # noqa: E402
import reloc_ledger  # noqa: E402

BASE = 0x400000
CODE, RDATA, DATA = 0x60000020, 0x40000040, 0xC0000040  # section characteristics
SECTIONS = [(".text", BASE + 0x1000, BASE + 0x2000, CODE), (".rdata", BASE + 0x2000, BASE + 0x3000, RDATA),
            (".data", BASE + 0x3000, BASE + 0x5000, DATA)]
FUNCTION = 0x20  # COFF symbol type of a function


# --------------------------------------------------------------------------- fixtures

def make_pe(sections):
    """A minimal PE image: sections = [(name, rva, virtual size, raw bytes)]."""
    count = len(sections)
    pe = 0x40
    optional = 224
    headers = pe + 24 + optional + 40 * count
    raw_at = (headers + 0x1FF) & ~0x1FF
    table, body = bytearray(), bytearray()
    for name, rva, vsize, raw in sections:
        raw = bytes(raw)
        rsize = (len(raw) + 0x1FF) & ~0x1FF
        table += name.encode().ljust(8, b"\0") + struct.pack("<IIIIIIHHI", vsize, rva, rsize,
                                                              raw_at + len(body), 0, 0, 0, 0, 0x40000040)
        body += raw.ljust(rsize, b"\0")
    image_size = max(rva + vsize for _, rva, vsize, _ in sections)
    opt = bytearray(optional)
    struct.pack_into("<H", opt, 0, 0x10B)
    struct.pack_into("<I", opt, 28, BASE)
    struct.pack_into("<I", opt, 56, (image_size + 0xFFF) & ~0xFFF)
    struct.pack_into("<I", opt, 92, 16)
    head = bytearray(raw_at)
    struct.pack_into("<I", head, 0x3C, pe)
    head[pe:pe + 4] = b"PE\0\0"
    struct.pack_into("<HHIIIHH", head, pe + 4, 0x14C, count, 0, 0, 0, optional, 0x102)
    head[pe + 24:pe + 24 + optional] = opt
    head[pe + 24 + optional:pe + 24 + optional + len(table)] = table
    return reloc_ledger.Image(bytes(head + body))


def image_with(rdata=b"", data=b"", data_vsize=None, text=b"\xc3" * 16):
    return make_pe([(".text", 0x1000, 0x1000, text), (".rdata", 0x2000, 0x1000, rdata),
                    (".data", 0x3000, data_vsize or 0x1000, data)])


def write_coff(path, sections, symbols):
    """sections [(name, flags, body or None, size, relocs [(offset, symbol index[, type])])],
    symbols [(name, value, section number, storage[, type])]: one i386 COFF object.
    A relocation is DIR32 and a symbol's type 0 (data) unless given."""
    head = 20 + 40 * len(sections)
    strings, headers, body = bytearray(4), bytearray(), bytearray()
    for name, flags, data, size, relocs in sections:
        raw_ptr = head + len(body) if data is not None else 0
        body += data or b""
        rel_ptr = head + len(body) if relocs else 0
        for offset, symbol, *kind in relocs:
            body += struct.pack("<IIH", offset, symbol, kind[0] if kind else data_rows.DIR32)
        headers += name.encode().ljust(8, b"\0") + struct.pack(
            "<IIIIIIHHI", 0, 0, size, raw_ptr, rel_ptr, 0, len(relocs), 0, flags)
    table = bytearray()
    for name, value, section, storage, *typ in symbols:
        raw = name.encode("latin-1")
        if len(raw) <= 8:
            field = raw.ljust(8, b"\0")
        else:
            field = struct.pack("<II", 0, len(strings))
            strings += raw + b"\0"
        table += field + struct.pack("<IhHBB", value, section, typ[0] if typ else 0, storage, 0)
    struct.pack_into("<I", strings, 0, len(strings))
    path.write_bytes(struct.pack("<HHIIIHH", 0x14C, len(sections), 0, head + len(body), len(symbols), 0, 0)
                     + bytes(headers) + bytes(body) + bytes(table) + bytes(strings))


_LOAD = data_rows.load


def use_ledger(monkeypatch, path):
    """Point data_rows at `path`: DATA_ROWS, and load(), whose default argument
    is bound to DATA_ROWS at import (as in Open-BFME-1)."""
    monkeypatch.setattr(data_rows, "DATA_ROWS", path)
    monkeypatch.setattr(data_rows, "load", lambda path=path: _LOAD(path))


def ledger(*rows):
    lines = [data_rows.HEADER] + [",".join(r) for r in rows]
    return ("\n".join(lines) + "\n").encode()


def row(name="?g@@3HA", address="0x00403000", kind="va", size="4", section=".data",
        source="Code/G.cpp", status="matched", evidence="ZH defines it", model="m"):
    return [name, address, kind, size, section, source, status, evidence, model]


def problems_of(raw, sources_ok=None):
    problems = []
    data_rows.check(raw, problems, sources_ok, SECTIONS)
    return problems


# --------------------------------------------------------------------------- integrity

def test_a_clean_ledger_passes_and_rva_and_va_mean_the_same_place():
    assert problems_of(ledger(row(), row("?h@@3HA", "0x00003004", "rva"))) == []
    assert data_rows.va_of(dict(zip(data_rows.FIELDS, row(address="0x00003004", kind="rva")))) == BASE + 0x3004


def test_integrity_refusals():
    assert "address_kind" in problems_of(ledger(row(kind="")))[0]
    assert "overlaps" in problems_of(ledger(row(size="8"), row("?h@@3HA", "0x00403004")))[0]
    assert "one owner per address" in problems_of(ledger(row(), row("?h@@3HA")))[0]
    assert "one row per name" in problems_of(ledger(row(), row(address="0x00403008")))[0]
    assert "is in .data" in problems_of(ledger(row(section=".rdata")))[0]
    assert "no single retail section" in problems_of(ledger(row(address="0x00402FFE")))[0]
    assert "not tracked" in problems_of(ledger(row()), sources_ok=set())[0]
    assert "empty model" in problems_of(ledger(row(model="")))[0]
    assert "bad header" in problems_of(b"name,address\n")[0]


def test_a_source_outside_code_is_refused():
    # BFME 2's tree: Open-BFME-1's game/ is Code/ here
    assert "must be a Code/ .c/.cpp file" in problems_of(ledger(row(source="game/G.cpp")))[0]
    assert "must be a Code/ .c/.cpp file" in problems_of(ledger(row(source="Code/G.h")))[0]
    assert problems_of(ledger(row(source="Code/G.c"))) == []


def test_the_header_only_ledger_is_clean_and_owns_nothing():
    assert problems_of(ledger()) == []
    assert data_rows.check(ledger(), [], None, SECTIONS) == 0
    assert data_rows.parse(ledger()) == []
    assert "no line ending" in problems_of(data_rows.HEADER.encode())[0]


# --------------------------------------------------------------------------- verification

def compiled(tmp_path, monkeypatch, sections, symbols, source_text="// fixture\n"):
    """A fake object for Code/G.cpp: sections [(name, flags, body, size, relocs)],
    symbols [(name, value, section[, type])]."""
    obj = tmp_path / "G.obj"
    write_coff(obj, sections, [(name, value, section, 3 if name.startswith("$") else 2, *typ)
                               for name, value, section, *typ in symbols])
    (tmp_path / "Code").mkdir(exist_ok=True)
    (tmp_path / "Code/G.cpp").write_text(source_text)
    monkeypatch.setattr(data_rows, "ROOT", tmp_path)
    monkeypatch.setattr(data_rows._tools()[0], "obj_path", lambda source: obj)


# what the compiler's sizeof probe answers for the fixture objects' symbols
SIZES = {"?t@@3PAUX@@A": 8, "?g@@3HA": 4, "?a@@3HA": 4, "?b@@3NA": 8, "?p@@3PBDB": 4,
         "?fp@@3P6AXXZA": 4, "?dp@@3PAHA": 4, "?table@@3PAP6AXXZA": 12}


def fixture_sizer(source, symbol):
    return (SIZES[symbol], "fixture sizeof") if symbol in SIZES else (None, "the sizeof probe does not compile")


def verify(img, entry, homes):
    """verify_row with a fixed name -> homes map (`homes` may also be a Resolver)."""
    resolve = homes if callable(homes) else (lambda name, function=None: homes.get(name, set()))
    return data_rows.verify_row(dict(zip(data_rows.FIELDS, entry)), img, resolve,
                                compile=False, sizer=fixture_sizer)


def test_initialised_symbol_needs_retail_bytes_and_retail_pointers(tmp_path, monkeypatch):
    # retail .data at 0x403000: {0x00402010 (pointer to _target), 7}
    img = image_with(data=struct.pack("<2I", BASE + 0x2010, 7))
    body = struct.pack("<2I", 0, 7)
    compiled(tmp_path, monkeypatch, [(".data", 0xC0300040, body, 8, [(0, 1)])],
             [("?t@@3PAUX@@A", 0, 1), ("_target", 0, 0)], "X *t[2] = { &target, (X *)7 };\n")
    entry = row("?t@@3PAUX@@A", size="8")
    assert verify(img, entry, {"_target": {BASE + 0x2010}})[0]
    ok, message = verify(img, entry, {"_target": {BASE + 0x2020}})
    assert not ok and "retail points at 0x00402010" in message
    assert "no retail address" in verify(img, entry, {})[1]
    assert "size 4 unproven" in verify(img, row("?t@@3PAUX@@A", size="4"), {"_target": {BASE + 0x2010}})[1]


def test_initializer_bytes_must_equal_retail(tmp_path, monkeypatch):
    img = image_with(data=struct.pack("<I", 5))
    compiled(tmp_path, monkeypatch, [(".data", 0xC0300040, struct.pack("<I", 6), 4, [])], [("?g@@3HA", 0, 1)])
    assert "differs" in verify(img, row(), {})[1]


def test_zero_filled_symbols_are_checked_alone_at_their_own_address(tmp_path, monkeypatch):
    # .bss holds ?b (8 bytes) then ?a (4): MSVC's by-name order is not retail's;
    # each symbol only needs retail zeros over its own extent at its own address
    img = image_with(data=bytes(4) + b"\x01" + bytes(11))
    compiled(tmp_path, monkeypatch, [(".bss", 0xC0300080, None, 12, [])], [("?b@@3NA", 0, 1), ("?a@@3HA", 8, 1)])
    assert verify(img, row("?a@@3HA", "0x00403000"), {})[0]            # retail order: a first
    assert verify(img, row("?b@@3NA", "0x00403008", size="8"), {})[0]
    ok, message = verify(img, row("?b@@3NA", "0x00403004", size="8"), {})
    assert not ok and "non-zero" in message


def test_a_relocation_to_a_tu_local_cannot_be_placed(tmp_path, monkeypatch):
    img = image_with(data=struct.pack("<I", BASE + 0x2000))
    compiled(tmp_path, monkeypatch, [(".data", 0xC0300040, bytes(4), 4, [(0, 1)])],
             [("?p@@3PBDB", 0, 1), ("$SG1", 0, 2)], 'const char *p = "x";\n')
    ok, message = verify(img, row("?p@@3PBDB"), {})
    assert not ok and "TU-local" in message


def test_allocation_padding_is_not_a_size(tmp_path, monkeypatch):
    # a 4-byte int alone in an 8-byte allocation (4 bytes of alignment padding)
    compiled(tmp_path, monkeypatch, [(".data", 0xC0300040, bytes(8), 8, [])], [("?g@@3HA", 0, 1)])
    img = image_with(data=bytes(8))
    ok, message = verify(img, row(size="8"), {})
    assert not ok and "size 8 unproven" in message
    assert verify(img, row(size="4"), {})[0]


def test_no_compiler_sizeof_no_size(tmp_path, monkeypatch):
    compiled(tmp_path, monkeypatch, [(".data", 0xC0300040, bytes(8), 8, [])], [("?s@@3US@@A", 0, 1)])
    ok, message = verify(image_with(data=bytes(8)), row("?s@@3US@@A", size="8"), {})
    assert not ok and "unproven" in message and "does not compile" in message


def test_verify_with_no_rows_reads_nothing_and_passes(tmp_path, monkeypatch):
    """The ledger starts empty: the gate's data check must be a no-op on it."""
    empty = tmp_path / "data_rows.csv"
    empty.write_bytes(ledger())
    use_ledger(monkeypatch, empty)
    monkeypatch.setattr(reloc_ledger, "Image", lambda *a: pytest.fail("read the retail image"))
    monkeypatch.setattr(data_rows, "Resolver", lambda *a: pytest.fail("built a resolver"))
    logged = []
    assert data_rows.verify(log=logged.append) == 0
    assert data_rows.verify(sources=["Code/G.cpp"], log=logged.append) == 0
    assert logged == []
    assert data_rows.load(empty) == [] and data_rows.load(tmp_path / "absent.csv") == []


def test_a_failing_row_fails_the_gate(tmp_path, monkeypatch):
    path = tmp_path / "data_rows.csv"
    path.write_bytes(ledger(row()))
    use_ledger(monkeypatch, path)
    monkeypatch.setattr(reloc_ledger, "Image", lambda *a: object())
    monkeypatch.setattr(data_rows, "Resolver", lambda rows: (lambda name: set()))
    monkeypatch.setattr(data_rows, "verify_row", lambda *a, **k: (False, "initializer differs from retail at +0x0"))
    logged = []
    with pytest.raises(SystemExit):
        data_rows.verify(log=logged.append)
    assert logged[-1] == "Data rows: FAIL 1 of 1"
    assert data_rows.verify(sources=["Code/Other.cpp"], log=logged.append) == 0  # another source's rows only


def test_the_resolver_reads_this_repositorys_ledgers(tmp_path, monkeypatch):
    build = data_rows._tools()[0]
    symbols = tmp_path / "symbols.csv"
    symbols.write_text("name,address,notes\n?pinned@@3HA,0x00001234,\n")
    monkeypatch.setattr(data_rows, "SYMBOLS", symbols)
    monkeypatch.setattr(data_rows, "DIR32_ADDRESSES", tmp_path / "absent.csv")
    monkeypatch.setattr(build, "load_function_rows",
                        lambda: [{"name": "?f@@YAXXZ", "target_rva": "0x00002000", "notes": ""}])
    resolve = data_rows.Resolver([dict(zip(data_rows.FIELDS, row()))], SECTIONS)
    assert resolve("?f@@YAXXZ") == {BASE + 0x2000}
    assert resolve("?g@@3HA") == {BASE + 0x3000}
    assert resolve("?pinned@@3HA") == {BASE + 0x1234}  # an RVA pin; below the image base it has one reading
    assert resolve("?unknown@@3HA") == set()


# --------------------------------------------------------------------------- pin readings (review of cd1336610f)

def resolver(tmp_path, monkeypatch, pins, sections):
    """A Resolver over `pins` ("name,0xADDRESS") alone, built the way verify() builds
    one (Resolver(rows)), with `sections` standing for retail's."""
    build = data_rows._tools()[0]
    symbols = tmp_path / "symbols.csv"
    symbols.write_text("name,address,notes\n" + "".join(f"{pin},\n" for pin in pins))
    monkeypatch.setattr(data_rows, "SYMBOLS", symbols)
    monkeypatch.setattr(data_rows, "DIR32_ADDRESSES", tmp_path / "absent.csv")
    monkeypatch.setattr(build, "load_function_rows", lambda: [])
    monkeypatch.setattr(data_rows, "retail_sections", lambda exe=None: sections)
    return data_rows.Resolver([])


# .text runs past RVA 0x400000, so pin 0x00401010 reads as RVA 0x401010 (VA 0x00801010)
# and as VA 0x00401010 (RVA 0x1010), both in .text: 7,192 retail pins are like that
HIGH_TEXT = [(".text", BASE + 0x1000, BASE + 0x501000, CODE), (".rdata", BASE + 0x501000, BASE + 0x502000, RDATA),
             (".data", BASE + 0x502000, BASE + 0x503000, DATA)]


def high_text_image(pointer):
    return make_pe([(".text", 0x1000, 0x500000, b"\xc3" * 16), (".rdata", 0x501000, 0x1000, b""),
                    (".data", 0x502000, 0x1000, struct.pack("<I", pointer))])


def test_a_code_pin_is_an_rva_so_a_high_relocation_cannot_take_its_va_reading(tmp_path, monkeypatch):
    resolve = resolver(tmp_path, monkeypatch, ["?f@@YAXXZ,0x00401010"], HIGH_TEXT)
    assert resolve("?f@@YAXXZ") == resolve("?f@@YAXXZ", True) == {BASE + 0x401010}  # never both
    compiled(tmp_path, monkeypatch, [(".data", 0xC0300040, bytes(4), 4, [(0, 1)])],
             [("?fp@@3P6AXXZA", 0, 1), ("?f@@YAXXZ", 0, 0, FUNCTION)], "void f();\nvoid (*fp)() = &f;\n")
    entry = row("?fp@@3P6AXXZA", "0x00902000")
    ok, message = verify(high_text_image(0x00401010), entry, resolve)  # retail points at RVA 0x1010, not f
    assert not ok and "retail points at 0x00401010" in message
    assert verify(high_text_image(BASE + 0x401010), entry, resolve)[0]  # the pin's own RVA


# a function pinned as a VA whose RVA reading is not code, as ??1Rva0033DDA1E4@@QAE@XZ
# is at 0x0088BA39 (RVA 0x0048BA39 in .text; as an RVA, .rdata)
LEGACY = [(".text", BASE + 0x1000, BASE + 0x10000, CODE), (".rdata", BASE + 0x400000, BASE + 0x402000, RDATA),
          (".data", BASE + 0x402000, BASE + 0x403000, DATA)]


def test_a_legacy_va_function_pin_stands_for_its_code_when_its_rva_reading_is_not(tmp_path, monkeypatch):
    resolve = resolver(tmp_path, monkeypatch, ["??1X@@QAE@XZ,0x00401010"], LEGACY)
    assert resolve("??1X@@QAE@XZ", True) == {0x00401010}         # VA 0x00401010 = RVA 0x1010, .text
    assert resolve("??1X@@QAE@XZ", False) == {BASE + 0x401010}   # as data it is the .rdata RVA
    img = make_pe([(".text", 0x1000, 0xF000, b"\xc3"), (".rdata", 0x400000, 0x2000, b""),
                   (".data", 0x402000, 0x1000, struct.pack("<I", 0x00401010))])
    compiled(tmp_path, monkeypatch, [(".data", 0xC0300040, bytes(4), 4, [(0, 1)])],
             [("?fp@@3P6AXXZA", 0, 1), ("??1X@@QAE@XZ", 0, 0, FUNCTION)])
    ok, message = verify(img, row("?fp@@3P6AXXZA", "0x00802000"), resolve)  # a pointer to the dtor
    assert ok, message


def test_a_function_takes_only_a_code_home_and_data_only_a_data_home(tmp_path, monkeypatch):
    resolve = resolver(tmp_path, monkeypatch, ["?f@@YAXXZ,0x00003000", "?g@@3HA,0x00001000"], SECTIONS)
    assert resolve("?f@@YAXXZ", True) == set() and resolve("?f@@YAXXZ", False) == {BASE + 0x3000}
    assert resolve("?g@@3HA", False) == set() and resolve("?g@@3HA", True) == {BASE + 0x1000}
    compiled(tmp_path, monkeypatch, [(".data", 0xC0300040, bytes(4), 4, [(0, 1)])],
             [("?fp@@3P6AXXZA", 0, 1), ("?f@@YAXXZ", 0, 0, FUNCTION)])
    ok, message = verify(image_with(data=struct.pack("<I", BASE + 0x3000)), row("?fp@@3P6AXXZA"), resolve)
    assert not ok and "no retail address in the ledgers (as code)" in message


# a data pin's VA reading counts, but not when its RVA reading lands in a section too
AMBIGUOUS = [(".text", BASE + 0x1000, BASE + 0x11000, CODE), (".data", BASE + 0x11000, BASE + 0x12000, DATA),
             (".rdata", BASE + 0x400000, BASE + 0x411018, RDATA)]


def test_a_pin_whose_rva_and_va_readings_both_land_places_nothing(tmp_path, monkeypatch):
    resolve = resolver(tmp_path, monkeypatch,
                       ["?d@@3HA,0x00411010",   # RVA: .rdata at 0x00811010; VA: .data at 0x00411010
                        "?v@@3HA,0x00411800",   # RVA: no section; VA: .data at 0x00411800
                        "?w@@3HA,0x00011800"],  # RVA: .data at 0x00411800; below the base, one reading
                       AMBIGUOUS)
    assert resolve("?d@@3HA") == set() and "ambiguous" in resolve.ambiguous["?d@@3HA"][0]
    assert resolve("?v@@3HA") == resolve("?w@@3HA") == {BASE + 0x11800}
    img = make_pe([(".text", 0x1000, 0x10000, b"\xc3"),
                   (".data", 0x11000, 0x1000, bytes(0x100) + struct.pack("<I", 0x00411010)),
                   (".rdata", 0x400000, 0x11018, b"")])
    compiled(tmp_path, monkeypatch, [(".data", 0xC0300040, bytes(4), 4, [(0, 1)])],
             [("?dp@@3PAHA", 0, 1), ("?d@@3HA", 0, 0)], "extern int d;\nint *dp = &d;\n")
    ok, message = verify(img, row("?dp@@3PAHA", "0x00411100"), resolve)  # either reading would have passed
    assert not ok and "ambiguous" in message


def test_dir32nb_holds_an_rva_and_a_stub_counts_for_its_body(tmp_path, monkeypatch):
    # retail .text: an ILT stub at RVA 0x1000 (jmp f) and f's body at RVA 0x1010;
    # .data: the stub's RVA (DIR32NB), f's RVA (DIR32NB), the stub's VA (DIR32)
    text = (b"\xe9" + struct.pack("<i", 0x1010 - 0x1005)).ljust(0x10, b"\xcc") + b"\xc3"
    img = image_with(data=struct.pack("<3I", 0x1000, 0x1010, BASE + 0x1000), text=text)
    relocs = [(0, 1, data_rows.DIR32NB), (4, 1, data_rows.DIR32NB), (8, 1, data_rows.DIR32)]
    compiled(tmp_path, monkeypatch, [(".data", 0xC0300040, bytes(12), 12, relocs)],
             [("?table@@3PAP6AXXZA", 0, 1), ("?f@@YAXXZ", 0, 0, FUNCTION)])
    entry = row("?table@@3PAP6AXXZA", size="12")
    ok, message = verify(img, entry, {"?f@@YAXXZ": {BASE + 0x1010}})
    assert ok, message
    ok, message = verify(img, entry, {"?f@@YAXXZ": {BASE + 0x1020}})
    assert not ok and "+0x0 (0x00403000): retail points at 0x00401000" in message


# --------------------------------------------------------------------------- names

def test_cpp_names_reach_namespaced_and_member_data_only():
    assert data_rows.cpp_name("?OurLanguage@@3W4LanguageID@@A") == "::OurLanguage"
    assert data_rows.cpp_name("?x@B@A@@2HA") == "::A::B::x"
    assert data_rows.cpp_name("?render_state@DX8Wrapper@@1URenderStateStruct@@A") == "::DX8Wrapper::render_state"
    assert data_rows.cpp_name("?private_state@DX8Wrapper@@0URenderStateStruct@@A") is None
    assert data_rows.cpp_name("_c_global") == "c_global"
    assert data_rows.cpp_name("?$S1@?1??f@@YAXXZ@4IA") is None


def test_template_static_data_access_decodes_literals_and_nested_types():
    first = "?s_firstList@?$CategoryModuleClass@$0A@@FXParticleSystem@@1PAV12@A"
    default = "?s_defaultModule@?$CategoryModuleClassBase@$04$00@FXParticleSystem@@1PAV?$CategoryModuleClass@$04@2@A"
    facet = "?id@?$num_put@DV?$ostreambuf_iterator@DV?$char_traits@D@_STL@@@_STL@@@_STL@@2V0locale@2@A"
    assert data_rows._cpp_data_access(first) == (
        "::FXParticleSystem::CategoryModuleClass<0 >::s_firstList",
        "::FXParticleSystem::CategoryModuleClass<0 >", True)
    assert data_rows.cpp_name(default) == "::FXParticleSystem::CategoryModuleClassBase<5, 1 >::s_defaultModule"
    assert data_rows.cpp_name(facet) == (
        "::_STL::num_put<char, ::_STL::ostreambuf_iterator<char, ::_STL::char_traits<char > > >::id")
    assert data_rows.cpp_name(first.replace("@@1P", "@@0P")) is None
    assert data_rows.cpp_name("?x@?$Owner@$1bad@@2HA") is None
    assert data_rows.cpp_name("?x@0@2HA") is None


def test_mangled_scalar_sizes():
    assert reloc_ledger.mangled_scalar_size("?g@@3HA") == 4
    assert reloc_ledger.mangled_scalar_size("?b@@3NA") == 8
    assert reloc_ledger.mangled_scalar_size("?OurLanguage@@3W4LanguageID@@A") == 4
    assert reloc_ledger.mangled_scalar_size("?t@@3PAUX@@A") is None  # pointer or array
    assert reloc_ledger.mangled_scalar_size("_c_global") is None


def test_private_data_names_require_the_compiler_access_path():
    symbol = "?buffers@Owner@@0PAY0BE@DA"
    assert data_rows.cpp_name(symbol) is None
    assert data_rows._cpp_data_access(symbol, allow_private=True) == (
        "::Owner::buffers", "::Owner", "private")
    assert data_rows._cpp_data_access("?x@@0HA", allow_private=True)[0] is None


# --------------------------------------------------------------------------- compiler (MSVC 7.1)

def _toolchain():
    build = data_rows._tools()[0]
    try:
        root = build.vc71_root()  # BFME 2's raises when cl.exe is missing
    except SystemExit:
        pytest.skip("MSVC 7.1 toolchain not present")
    if not (root / "Vc7" / "bin" / "cl.exe").exists():
        pytest.skip("MSVC 7.1 toolchain not present")


def test_the_compiler_sizes_what_a_textual_lookup_gets_wrong():
    """The review's real-MSVC case: A::Element is char, B::Element is long, and
    `using namespace B` makes `Element values[2]` 8 bytes. A textual parser
    picked A's typedef (2 bytes); the sizeof probe asks the compiler."""
    _toolchain()
    work = data_rows.ROOT / "build" / "data_rows" / "test_type_scope"
    work.mkdir(parents=True, exist_ok=True)
    source = work / "type_scope.cpp"
    source.write_text("namespace A { typedef char Element; }\nnamespace B { typedef long Element; }\n"
                      "using namespace B;\nElement values[2] = {0,0};\n")
    size, how = data_rows.compiled_size(source, "?values@@3PAJA")
    assert size == 8, how


def test_the_sizeof_probe_refuses_a_macro_named_like_the_symbol():
    _toolchain()
    work = data_rows.ROOT / "build" / "data_rows" / "test_macro"
    work.mkdir(parents=True, exist_ok=True)
    source = work / "macro.cpp"
    source.write_text("int values[2] = {0, 0};\nshort tiny;\n#define values tiny\n")
    size, how = data_rows.compiled_size(source, "?values@@3PAHA")
    assert size is None and "does not compile" in how
    source.write_text("int values[2] = {0, 0};\n")
    assert data_rows.compiled_size(source, "?values@@3PAHA")[0] == 8


def test_only_a_compiler_proven_arithmetic_type_is_a_number():
    """review_20260930_1105: a pointer with the same reference declaration was a
    'proven scalar'. The compiler's own overload resolution decides now."""
    _toolchain()
    work = data_rows.ROOT / "build" / "data_rows" / "test_arith"
    work.mkdir(parents=True, exist_ok=True)
    source = work / "kinds.cpp"
    source.write_text("int *pointer = (int *)0x00401000;\n"
                      "unsigned short table[3] = { 67, 61, 59 };\n"
                      "double ratio = 1.5;\n"
                      "enum Kind { KA, KB };\nKind kind = KB;\n"
                      "struct Pair { float a, b; };\nPair pair = { 1.0f, 2.0f };\n"
                      "int **handle = 0;\n"
                      "short grid[2][2] = { {1, 2}, {3, 4} };\n")
    expect = {"?pointer@@3PAHA": False, "?table@@3PAGA": True, "?ratio@@3NA": True, "?kind@@3W4Kind@@A": False,
              "?pair@@3UPair@@A": False, "?handle@@3PAPAHA": False, "?grid@@3PAY01FA": False}
    for symbol, want in expect.items():
        assert data_rows.compiled_arithmetic(source, symbol)[0] is want, symbol


def _private_fixture(name, friend=True, extra=""):
    _toolchain()
    work = data_rows.ROOT / "build" / "data_rows" / name
    work.mkdir(parents=True, exist_ok=True)
    source = work / "private_data.cpp"
    grant = "template<class T> friend struct DataRowPrivateProbe;" if friend else ""
    source.write_text(
        "class Owner { " + grant + " static char buffers[9][20]; static int counts[2]; };\n"
        "char Owner::buffers[9][20] = {};\nint Owner::counts[2] = {1, 2};\n" + extra)
    return source


def test_private_friend_probes_prove_the_full_size_and_actual_type():
    source = _private_fixture("test_private_friend")
    buffers = "?buffers@Owner@@0PAY0BE@DA"
    counts = "?counts@Owner@@0PAHA"
    size, how = data_rows.compiled_size(source, buffers)
    assert size == 180, how
    assert "friend access" in how
    assert data_rows.compiled_size(source, counts)[0] == 8
    assert data_rows.compiled_arithmetic(source, buffers)[0] is False
    assert data_rows.compiled_arithmetic(source, counts)[0] is True


def test_private_data_without_explicit_friendship_is_still_refused():
    source = _private_fixture("test_private_no_friend", friend=False)
    for probe in (data_rows.compiled_size, data_rows.compiled_arithmetic):
        value, how = probe(source, "?counts@Owner@@0PAHA")
        assert value is None and "does not compile" in how


@pytest.mark.parametrize("extra", [
    "#define DataRowPrivateProbe ForgedProbe\n",
    "template<class T> struct DataRowPrivateProbe { enum { size_value = 1, kind_value = 1 }; };\n",
])
def test_private_probe_helper_cannot_be_spoofed(extra):
    source = _private_fixture("test_private_spoof", extra=extra)
    for probe in (data_rows.compiled_size, data_rows.compiled_arithmetic):
        value, how = probe(source, "?counts@Owner@@0PAHA")
        assert value is None and "does not compile" in how
