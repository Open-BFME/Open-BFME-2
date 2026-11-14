"""Seeded static-image defects; no compiler, linker or game required."""
import json
import pytest
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import image_iso as iso


class Memory:
    def __init__(self, base):
        self.base = base
        self.bytes = bytearray(0x5000)
        self.relocations = set()
        self.inits = []

    def read(self, rva, size):
        if 0 <= rva and rva + size <= len(self.bytes):
            return bytes(self.bytes[rva:rva + size])
        return None

    def put(self, rva, data):
        self.bytes[rva:rva + len(data)] = data

    def pointer(self, rva, target):
        self.put(rva, struct.pack("<I", self.base + target))
        self.relocations.add(rva)

    def in_text(self, va):
        return 0x100 <= va - self.base < 0x1000

    def readonly(self, rva, size=1):
        return self.read(rva, size) is not None

    def initializers(self):
        return self.inits


def public(name, rva, extent=4):
    return dict(name=name, rva=rva, extent=extent, object=name + ".obj", source="Code/" + name + ".cpp")


def row(name, rva, size=4, kind="global"):
    return dict(name=name, names="", address=hex(rva), size=str(size), kind=kind)


def checker(publics, addresses):
    return iso.Checker(Memory(0x10000000), Memory(0x400000), publics, addresses)


def test_pointer_wrong_unknown_and_interior_are_distinct():
    c = checker([public("array", 0x2000, 16), public("other", 0x3000)],
                {"array": {0x2100}, "other": {0x3100}})
    assert c.pointer(c.ours.base + 0x2008, c.retail.base + 0x2108) == "equal"
    assert c.pointer(c.ours.base + 0x3000, c.retail.base + 0x2108) == "wrong"
    assert c.pointer(c.ours.base + 0x4000, c.retail.base + 0x2108) == "unchecked"
    c.addresses["unused"] = {0x900}
    # One image location with two distinct retail candidates cannot pass.
    mapping = iso.Correspondence([public("a", 0x200), public("b", 0x200)],
                                 {"a": {0x100}, "b": {0x110}})
    assert mapping.resolve(0x200) is None


def test_global_wrong_pointer_contents_and_unchecked_are_all_counted():
    c = checker([public("global", 0x2000, 16), public("right", 0x3000), public("wrong", 0x3100)],
                {"global": {0x2200}, "right": {0x3200}, "wrong": {0x3300}})
    for offset, target in ((0, 0x3100), (4, 0x4000), (8, 0x3000)):
        c.ours.pointer(0x2000 + offset, target)
        c.retail.pointer(0x2200 + offset, 0x3200)
    c.ours.put(0x200c, b"bad!")
    c.retail.put(0x220c, b"good")
    c.ledger([row("global", 0x2200, 16), row("missing", 0x2300)], {})
    assert c.counts["wrong_pointers"] == 1
    assert c.counts["pointers_unchecked"] == 1
    assert c.counts["pointers_equal"] == 1
    assert c.counts["global_contents"] == 1
    c.retail.put(0x2300, b"seed")
    c.ledger([row("missing", 0x2300)], {})
    assert c.counts["no_object_retail_nonzero"] == 1


def test_short_vtable_wrong_slot_and_abi_body_are_detected():
    c = checker([public("vt", 0x2000, 8), public("f", 0x300), public("g", 0x400)],
                {"vt": {0x2100}, "f": {0x100}, "g": {0x200}})
    c.retail.pointer(0x2100, 0x100)
    c.retail.pointer(0x2104, 0x100)
    c.retail.pointer(0x2108, 0x100)
    c.ours.pointer(0x2000, 0x400)  # wrong function row
    c.ours.pointer(0x2004, 0x300)  # correct row, wrong callee stack cleanup
    c.ours.put(0x300, b"\xc2\x08\x00")
    c.retail.put(0x100, b"\xc2\x04\x00")
    c.ledger([row("vt", 0x2100, 12, "vtable")], {0x100: 3})
    assert c.counts["vtable_short"] == 1
    assert c.counts["vtable_slot"] == 2
    assert c.counts["vtable_slots_unanalyzed"] == 1


def test_unrowed_forwarder_adjustment_is_checked():
    c = checker([public("f", 0x300)], {"f": {0x100}})
    for image, start, target in ((c.ours, 0x500, 0x300), (c.retail, 0x600, 0x100)):
        image.put(start, b"\x83\xe9\x08\xe9" + struct.pack("<i", target - start - 8))
        image.put(target, b"\xc3")
    assert c.slot(c.ours.base + 0x500, c.retail.base + 0x600, {0x100: 1})[0] is True
    c.ours.put(0x502, b"\x04")
    assert c.slot(c.ours.base + 0x500, c.retail.base + 0x600, {0x100: 1})[0] is False


def test_constructor_seed_proves_undersized_and_split_without_ledger_gap():
    c = checker([public("object", 0x2000, 4), public("field", 0x3000, 4)],
                {"object": {0x2100}, "field": {0x2108}})
    c.retail.inits = [0x100]
    # mov ecx, object; call ctor; ret. ctor stores at +8, then returns.
    c.retail.put(0x100, b"\xb9" + struct.pack("<I", c.retail.base + 0x2100) +
                 b"\xe8" + struct.pack("<i", 0x200 - 0x10a) + b"\xc3")
    c.retail.put(0x200, b"\xc7\x41\x08\xe8\x03\x00\x00\xc3")
    evidence = iso.storage_evidence(c.retail, [row("object", 0x2100, 4)])
    assert len(evidence) == 1
    assert evidence[0]["offset"] == 8 and evidence[0]["width"] == 4
    c.storage(evidence)
    assert c.counts["storage_undersized"] == 1
    assert c.counts["storage_split"] == 1
    # Correctly interior-bound field and enough storage are clean.
    c = checker([public("object", 0x2000, 12), public("field", 0x2008, 4)],
                {"object": {0x2100}, "field": {0x2108}})
    c.storage(evidence)
    assert not c.defects


def test_constructor_scan_stops_on_ecx_clobber_or_control_flow():
    c = checker([], {})
    c.retail.inits = [0x100]
    c.retail.put(0x100, b"\xb9" + struct.pack("<I", c.retail.base + 0x2100) +
                 b"\xe8" + struct.pack("<i", 0x200 - 0x10a) + b"\xc3")
    for prefix in (b"\x31\xc9", b"\x75\x02", b"\xc3"):
        c.retail.put(0x200, prefix + b"\xc7\x41\x08\xe8\x03\x00\x00\xc3")
        assert iso.storage_evidence(c.retail, [row("object", 0x2100)]) == []


def test_initializer_missing_duplicate_order_and_unresolved():
    c = checker([public("a", 0x300), public("b", 0x400)], {"a": {0x100}, "b": {0x200}})
    c.retail.inits = [0x100, 0x200, 0x250]
    c.ours.inits = [0x400, 0x300, 0x300, 0x777]
    c.initializers()
    assert c.counts["initializer_count"] == 1
    assert c.counts["initializer_order"] == 1
    assert c.counts["initializers_unanalyzed"] == 1
    assert c.report()["g2_pass"] is False
    assert c.report()["complete"] is False


def test_map_preserves_provider_and_static_names(tmp_path):
    path = tmp_path / "exit.map"
    path.write_text(" 0001:00000000 _foo 10001000 f provider.obj\n"
                    " 0001:00000004 _$E1 10001004 f other.obj\n")
    entries = iso.read_map(path, 0x10000000)
    assert [(e["name"], e["rva"], e["object"]) for e in entries] == [
        ("_foo", 0x1000, "provider.obj"), ("_$E1", 0x1004, "other.obj")]


def test_manifest_hash_mismatch_refuses(tmp_path):
    import pytest
    obj = tmp_path / "fake.obj"
    obj.write_bytes(b"not trusted")
    manifest = tmp_path / "objects.json"
    manifest.write_text(json.dumps([dict(path="fake.obj", sha256="0" * 64, source="Code/fake.cpp")]))
    with pytest.raises(ValueError, match="hash mismatch"):
        iso.attach_objects([], manifest)


def test_retail_gap_never_proves_undersized():
    c = checker([public("g", 0x2000, 4)], {"g": {0x2100}})
    c.ledger([row("g", 0x2100, 100)], {})
    assert c.counts["globals_retail_extent_unanalyzed"] == 1
    assert c.counts["storage_undersized"] == 0


def test_initializer_proven_missing_without_unresolved_entries():
    c = checker([public("a", 0x300)], {"a": {0x100}})
    c.retail.inits = [0x100, 0x200]
    c.ours.inits = [0x300]
    c.initializers()
    assert c.counts["initializer_count"] == 1
    assert c.counts["initializers_missing_or_unresolved"] == 1


def write_pe(path, base, wrong=False):
    data = bytearray(0xc00)
    data[:2] = b"MZ"
    struct.pack_into("<I", data, 0x3c, 0x80)
    data[0x80:0x84] = b"PE\0\0"
    struct.pack_into("<HHIIIHH", data, 0x84, 0x14c, 2, 0, 0, 0, 0xe0, 0x102)
    opt = 0x98
    struct.pack_into("<H", data, opt, 0x10b)
    for offset, value in ((16, 0x1000), (28, base), (32, 0x1000), (36, 0x200),
                          (56, 0x3000), (60, 0x200), (92, 16)):
        struct.pack_into("<I", data, opt + offset, value)
    for i, (name, va, raw, flags) in enumerate(((b".text", 0x1000, 0x200, 0x60000020),
                                               (b".rdata", 0x2000, 0x600, 0x40000040))):
        at = opt + 0xe0 + i * 40
        data[at:at + len(name)] = name
        struct.pack_into("<IIII", data, at + 8, 0x400, va, 0x400, raw)
        struct.pack_into("<I", data, at + 36, flags)
    # Two functions, one vtable and one initialized scalar.
    data[0x220] = 0xc3
    data[0x230] = 0xc3
    struct.pack_into("<I", data, 0x600, base + (0x1030 if wrong else 0x1020))
    struct.pack_into("<I", data, 0x604, 99 if wrong else 42)
    path.write_bytes(data)


def test_cli_pe_report_and_tsv_are_real_outputs(tmp_path, monkeypatch):
    import csv
    root = tmp_path / "repo"
    (root / "reverse").mkdir(parents=True)
    monkeypatch.setattr(iso.build, "ROOT", root)
    data = [row("vt", 0x2000, 4, "vtable"), row("scalar", 0x2004)]
    with (root / "reverse/data_ledger.csv").open("w") as f:
        w = csv.DictWriter(f, fieldnames=list(data[0]))
        w.writeheader()
        w.writerows(data)
    (root / "reverse/functions.csv").write_text(
        "name,target_rva,target_size,notes,source\n"
        "f,0x1020,1,,Code/f.cpp\n"
        "g,0x1030,1,,Code/g.cpp\n")
    ours, retail = tmp_path / "exit.exe", tmp_path / "retail.exe"
    write_pe(ours, 0x10000000, wrong=True)
    write_pe(retail, 0x400000)
    mapfile = tmp_path / "exit.map"
    mapfile.write_text("".join(f" 0001:00000000 {n} {0x10000000 + r:08x} f {n}.obj\n"
                               for n, r in (("vt", 0x2000), ("scalar", 0x2004),
                                            ("f", 0x1020), ("g", 0x1030))))
    entries = []
    for name, extent in (("vt", 4), ("scalar", 4), ("f", 1), ("g", 1)):
        obj = tmp_path / (name + ".obj")
        iso.link_cycle.write_coff(obj, [(".rdata", 0x40000040, bytes(extent), 0)],
                                  [(name, 1, 0, iso.link_cycle.EXTERNAL)])
        entries.append(dict(path=obj.name, sha256=iso.digest(obj), source="Code/" + name + ".cpp"))
    manifest = tmp_path / "objects.json"
    manifest.write_text(json.dumps(entries))
    receipt = dict(kind="diagnostic", commit="a" * 40, base="0x10000000",
                   image_sha256=iso.digest(ours), map_sha256=iso.digest(mapfile), stubbed=["missing"],
                   exports_requested=0, rsrc=False, fixed_no=True)
    (tmp_path / "image_receipt.json").write_text(json.dumps(receipt))
    out = tmp_path / "report"
    assert iso.main(["--image", str(ours), "--map", str(mapfile), "--retail", str(retail),
                     "--objects", str(manifest), "--out", str(out)]) == 1
    report = json.loads((out / "report.json").read_text())
    assert report["counts"]["vtable_slot"] == 1
    assert report["counts"]["global_contents"] == 1
    assert report["inputs"]["receipt"]["kind"] == "diagnostic"
    assert len((out / "defects.tsv").read_text().splitlines()) == 3
    import pytest
    mapfile.write_text("tampered")
    with pytest.raises(SystemExit):
        iso.main(["--image", str(ours), "--map", str(mapfile), "--retail", str(retail)])


def test_fold_requires_whole_retail_byte_proof_and_keeps_expected_alias():
    c = checker([public("f", 0x300), public("g", 0x300)], {"f": {0x100}, "g": {0x200}})
    assert c.mapping.resolve(0x300) is None
    c.retail.put(0x100, b"\xc2\x04\x00")
    c.retail.put(0x200, b"\xc2\x04\x00")
    c.ours.put(0x300, b"\xc2\x04\x00")
    c.mapping.prove_folds(c.retail, {0x100: 3, 0x200: 3})
    assert c.pointer(c.ours.base + 0x300, c.retail.base + 0x200) == "equal"
    assert c.slot(c.ours.base + 0x300, c.retail.base + 0x100, {0x100: 3})[0] is True
    bad = checker([public("f", 0x300), public("g", 0x300)], {"f": {0x100}, "g": {0x200}})
    bad.retail.put(0x100, b"\xc2\x04\x00")
    bad.retail.put(0x200, b"\xc2\x08\x00")
    bad.mapping.prove_folds(bad.retail, {0x100: 3, 0x200: 3})
    assert bad.mapping.resolve(0x300) is None


def test_repeated_data_name_requires_source_qualification():
    publics = [public("?s@@3HA", 0x300, 16), public("?s@@3HA", 0x500, 16)]
    publics[0]["source"], publics[1]["source"] = "Code/a.cpp", "Code/b.cpp"
    addresses = {"?s@@3HA": {0x100}}
    c = iso.Checker(Memory(0x10000000), Memory(0x400000), publics, addresses)
    assert c.pointer(c.ours.base + 0x500, c.retail.base + 0x100) == "unchecked"
    assert c.mapping.resolve(0x508) is None  # no unqualified interior range
    qualified = {("?s@@3HA", "Code/a.cpp"): {0x100}}
    c = iso.Checker(c.ours, c.retail, publics, addresses, qualified)
    assert c.pointer(c.ours.base + 0x300, c.retail.base + 0x100) == "equal"
    assert c.mapping.resolve(0x308) == 0x108
    assert c.mapping.resolve(0x500) is None
    assert c.mapping.resolve(0x508) is None


def test_duplicate_local_initializers_resolve_by_manifest_source():
    publics = [public("_$E1", 0x300), public("_$E1", 0x500)]
    publics[0]["source"], publics[1]["source"] = "Code/a.cpp", "Code/b.cpp"
    qualified = {("_$E1", "Code/a.cpp"): {0x100}, ("_$E1", "Code/b.cpp"): {0x200}}
    c = iso.Checker(Memory(0x10000000), Memory(0x400000), publics,
                    {"_$E1": {0x100, 0x200}}, qualified)
    c.retail.inits, c.ours.inits = [0x100, 0x200], [0x300, 0x500]
    c.initializers()
    assert c.counts["initializers_unanalyzed"] == 0
    assert c.counts["initializers_missing_or_unresolved"] == 0
    assert not c.defects
    c.ours.inits.reverse()
    c.initializers()
    assert c.counts["initializer_order"] == 1


def test_string_wstring_float_bytes_and_other_kind_accounting():
    publics = [public(n, a, 4) for n, a in (("s", 0x2000), ("ws", 0x2004), ("f", 0x2008))]
    c = checker(publics, {"s": {0x2100}, "ws": {0x2104}, "f": {0x2108}})
    c.ours.put(0x2000, b"bad\0" + b"a\0\0\0" + struct.pack("<f", 2.0))
    c.retail.put(0x2100, b"yes\0" + b"b\0\0\0" + struct.pack("<f", 1.0))
    rows = [row("s", 0x2100, 4, "string"), row("ws", 0x2104, 4, "wstring"),
            row("f", 0x2108, 4, "float"), row("imp", 0x2200, 4, "import"),
            row("rtti", 0x2204, 4, "rtti")]
    c.ledger(rows, {})
    for kind in ("string", "wstring", "float"):
        assert c.counts[kind + "_compared"] == 1
        assert c.counts[kind + "_contents"] == 1
    for kind in ("import", "rtti"):
        assert c.counts[kind + "_ledger_entries"] == c.counts[kind + "_unanalyzed"] == 1


def test_one_sided_adjustor_is_wrong_and_plain_forwarder_is_equal():
    c = checker([public("f", 0x300)], {"f": {0x100}})
    c.ours.put(0x300, b"\xc3")
    c.retail.put(0x100, b"\xc3")
    c.retail.put(0x600, b"\x83\xe9\x08\xe9" + struct.pack("<i", 0x100 - 0x608))
    assert c.slot(c.ours.base + 0x300, c.retail.base + 0x600, {0x100: 1})[0] is False
    c.ours.put(0x500, b"\x83\xc1\x04\xe9" + struct.pack("<i", 0x300 - 0x508))
    assert c.slot(c.ours.base + 0x500, c.retail.base + 0x100, {0x100: 1})[0] is False
    c.retail.put(0x600, b"\xe9" + struct.pack("<i", 0x100 - 0x605))
    assert c.slot(c.ours.base + 0x300, c.retail.base + 0x600, {0x100: 1})[0] is True


def test_interval_index_matches_exhaustive_overlap_reference():
    import random
    rng = random.Random(712)
    publics = [public(str(i), rng.randrange(10, 250), rng.randrange(1, 80)) for i in range(80)]
    addresses = {str(i): {1000 + i * 100} for i in range(80)}
    mapping = iso.Correspondence(publics, addresses)
    for rva in range(350):
        wanted = set(mapping.exact.get(rva, ()))
        wanted.update(target + rva - start for start, size, target in mapping.spans
                      if start < rva < start + size)
        assert mapping.candidates(rva) == wanted


def test_library_provider_basename_and_rtti_vtable_offset(tmp_path):
    assert iso.object_name("lib:member.obj") == "member.obj"
    assert iso.object_name(r"C:\lib\a.lib:member.obj") == "member.obj"
    obj = tmp_path / "member.obj"
    iso.link_cycle.write_coff(obj, [(".rdata", 0x40000040, bytes(8), 0)],
                              [("rtti", 1, 0, iso.link_cycle.EXTERNAL),
                               ("vt", 1, 4, iso.link_cycle.EXTERNAL)])
    manifest = tmp_path / "objects.json"
    manifest.write_text(json.dumps([dict(path=obj.name, sha256=iso.digest(obj), source="Code/a.cpp")]))
    publics = [dict(public("vt", 0x2000), object="lib:member.obj")]
    result = iso.attach_objects(publics, manifest)
    assert result["extents_attached"] == 1
    assert publics[0]["extent"] == 4  # RTTI's preceding word is excluded


def test_capstone_moffs_a1_a3_pointer_translation():
    import capstone
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    c = checker([public("global", 0x2000)], {"global": {0x2100}})
    for opcode in (b"\xa1", b"\xa3"):
        a = opcode + struct.pack("<I", c.ours.base + 0x2000)
        b = opcode + struct.pack("<I", c.retail.base + 0x2100)
        ins = next(md.disasm(a, 0x300))
        assert (ins.disp_offset, ins.disp_size) == (1, 4)
        c.ours.put(0x300, a); c.retail.put(0x100, b)
        c.ours.relocations.add(0x301); c.retail.relocations.add(0x101)
        assert c.code_equal(0x300, 0x100, 5) is True


def test_manifest_writer_response_map_and_deps_source(tmp_path):
    import hashlib
    work = tmp_path / "work"
    work.mkdir()
    obj = work / "a.obj"
    iso.link_cycle.write_coff(obj, [(".data", 0x40000040, bytes(8), 0)],
                              [("g", 1, 0, iso.link_cycle.EXTERNAL)])
    obj.with_suffix(".deps.json").write_text(json.dumps(
        dict(path="Code/a.cpp", object=hashlib.md5(obj.read_bytes()).hexdigest())))
    rsp = work / "link.rsp"
    rsp.write_text('"a.obj"\n/OUT:"exit.exe"\n')
    mapfile = work / "exit.map"
    mapfile.write_text(" Preferred load address is 10000000\n"
                       " 0001:00000000 g 10002000 a.obj\n")
    out = tmp_path / "snap" / "objects.json"
    metadata = iso.write_object_manifest(rsp, mapfile, out, cwd=work)
    assert metadata["counts"]["objects_snapshotted"] == 1
    entries = json.loads(out.read_text())
    assert entries[0]["source"] == "Code/a.cpp"
    publics = iso.read_map(mapfile, 0x10000000)
    assert iso.attach_objects(publics, out, mapfile)["extents_attached"] == 1
    assert publics[0]["extent"] == 8
    # Exact consumed bytes survive later writes to the shared original.
    obj.write_bytes(b"changed")
    assert iso.attach_objects(publics, out, mapfile)["extents_attached"] == 1
    mapfile.write_text("changed map")
    import pytest
    with pytest.raises(ValueError, match="MAP hash mismatch"):
        iso.attach_objects(publics, out, mapfile)


def test_manifest_writer_extracts_selected_archive_member(tmp_path):
    obj = tmp_path / "member.obj"
    iso.link_cycle.write_coff(obj, [(".data", 0x40000040, bytes(4), 0)],
                              [("g", 1, 0, iso.link_cycle.EXTERNAL)])
    raw = obj.read_bytes()
    header = (f"{'member.obj/':<16}{0:<12}{0:<6}{0:<6}{0:<8}{len(raw):<10}" + "`\n").encode()
    library = tmp_path / "a.lib"
    library.write_bytes(b"!<arch>\n" + header + raw + (b"\n" if len(raw) % 2 else b""))
    rsp = tmp_path / "link.rsp"
    rsp.write_text('"a.lib"\n')
    mapfile = tmp_path / "exit.map"
    mapfile.write_text(" Preferred load address is 10000000\n"
                       " 0001:00000000 g 10002000 a:member.obj\n")
    out = tmp_path / "snap" / "objects.json"
    result = iso.write_object_manifest(rsp, mapfile, out, cwd=tmp_path)
    assert result["counts"]["objects_snapshotted"] == 1
    publics = iso.read_map(mapfile, 0x10000000)
    assert iso.attach_objects(publics, out, mapfile)["extents_attached"] == 1


def test_response_parser_nested_quotes_and_wine_paths(tmp_path):
    nested = tmp_path / "nested.rsp"
    nested.write_text('/DEFAULTLIB:"libs with spaces/a.lib"\n')
    rsp = tmp_path / "exit.rsp"
    rsp.write_text('"some file.obj" @"nested.rsp" "Z:\\tmp\\absolute.obj" /OUT:"out.obj"')
    assert iso.response_inputs(rsp, tmp_path) == [
        tmp_path / "some file.obj", tmp_path / "libs with spaces/a.lib",
        Path("/tmp/absolute.obj")]


def test_unknown_string_bytes_count_as_unanalyzed_and_unregistered_kind_is_counted():
    c = checker([], {})
    c.ledger([row("missing", 0x2100, 4, "string"), row("weird", 0x2200, 4, "new-kind")], {})
    assert c.counts["string_unanalyzed"] == 1
    assert c.counts["new-kind_unanalyzed"] == 1


def test_cli_duplicate_initializer_object_symbols_are_source_qualified(tmp_path, monkeypatch):
    root = tmp_path / "repo"
    (root / "reverse").mkdir(parents=True)
    monkeypatch.setattr(iso.build, "ROOT", root)
    (root / "reverse/data_ledger.csv").write_text("address,size,kind,name,source,names\n")
    (root / "reverse/functions.csv").write_text(
        "name,target_rva,target_size,notes,source\n"
        "first,0x1020,1,object-symbol=_$E1,Code/a.cpp\n"
        "second,0x1030,1,object-symbol=_$E1,Code/b.cpp\n")
    ours, retail = tmp_path / "exit.exe", tmp_path / "retail.exe"
    for path, base in ((ours, 0x10000000), (retail, 0x400000)):
        write_pe(path, base)
        raw = bytearray(path.read_bytes())
        raw[0x200:0x20f] = (b"\x68" + struct.pack("<I", base + 0x2028) +
                           b"\x68" + struct.pack("<I", base + 0x2020) + b"\xe8" + bytes(4))
        struct.pack_into("<II", raw, 0x620, base + 0x1020, base + 0x1030)
        path.write_bytes(raw)
    mapfile = tmp_path / "exit.map"
    mapfile.write_text(" Preferred load address is 10000000\n"
                       " 0001:00000020 _$E1 10001020 f a.obj\n"
                       " 0001:00000030 _$E1 10001030 f b.obj\n")
    entries = []
    for name in ("a", "b"):
        obj = tmp_path / (name + ".obj")
        iso.link_cycle.write_coff(obj, [(".text", 0x60000020, b"\xc3", 0)],
                                  [("_$E1", 1, 0, iso.link_cycle.EXTERNAL)])
        entries.append(dict(path=obj.name, sha256=iso.digest(obj), source="Code/" + name + ".cpp"))
    manifest = tmp_path / "objects.json"
    manifest.write_text(json.dumps(entries))
    receipt = dict(kind="diagnostic", base="0x10000000", stubbed=[],
                   image_sha256=iso.digest(ours), map_sha256=iso.digest(mapfile))
    (tmp_path / "image_receipt.json").write_text(json.dumps(receipt))
    out = tmp_path / "report"
    assert iso.main(["--image", str(ours), "--map", str(mapfile),
                     "--retail", str(retail), "--objects", str(manifest), "--out", str(out)]) == 1
    counts = json.loads((out / "report.json").read_text())["counts"]
    assert counts["initializers_retail"] == counts["initializers_image"] == 2
    assert counts["initializers_unanalyzed"] == counts["initializers_missing_or_unresolved"] == 0


def test_pooled_literal_alias_requires_complete_ours_and_both_retail_values():
    for name, value in (("??_C@_0fixture", b"CommandPoints\0"),
                        ("??_C@_1fixture", "00000000".encode("utf-16le") + b"\0\0")):
        c = checker([public(name, 0x2000, len(value))], {name: {0x2100}})
        c.ours.put(0x2000, value)
        c.retail.put(0x2100, value)
        c.retail.put(0x2200, value)
        assert c.pointer(c.ours.base + 0x2000, c.retail.base + 0x2200) == "equal"
        assert c.counts["pointers_literal_aliases"] == 1
        # Matching prefix alone is not an alias.
        c.retail.put(0x2200, b"X")
        c.literal_cache.clear()
        assert c.pointer(c.ours.base + 0x2000, c.retail.base + 0x2200) == "wrong"
        # A changed linked literal is not an alias of two equal retail copies.
        c.retail.put(0x2200, value)
        c.ours.put(0x2000, b"X")
        c.literal_cache.clear()
        assert c.pointer(c.ours.base + 0x2000, c.retail.base + 0x2200) == "wrong"


def test_identical_arbitrary_globals_and_ambiguous_literals_are_not_aliases():
    c = checker([public("global", 0x2000, 4)], {"global": {0x2100}})
    assert c.pointer(c.ours.base + 0x2000, c.retail.base + 0x2200) == "wrong"
    c = checker([public("??_C@_0ambiguous", 0x2000)],
                {"??_C@_0ambiguous": {0x2100, 0x2200}})
    assert c.pointer(c.ours.base + 0x2000, c.retail.base + 0x2200) == "unchecked"


def test_literal_alias_never_accepts_a_terminated_prefix_of_another_string():
    name = "??_C@_0prefix"
    c = checker([public(name, 0x2000, 6)], {name: {0x2100}})
    c.ours.put(0x2000, b"name\0")
    c.retail.put(0x2100, b"name\0")
    c.retail.put(0x2200, b"nameX\0")
    assert c.pointer(c.ours.base + 0x2000, c.retail.base + 0x2200) == "wrong"


def absolute_case(tmp_path, body, *, symbol="getter", object_body=None,
                  linked_body=None, relocs=(), data_rows=None, extra_rows=()):
    import csv
    from types import SimpleNamespace
    p = public(symbol, 0x300, len(body))
    p["coff"] = dict(offset=0, section=dict(body=object_body if object_body is not None else body,
        size=len(body), flags=0x60000020, relocations=tuple(relocs)))
    c = checker([p], {symbol: {0x100}})
    c.retail.put(0x100, body)
    c.ours.put(0x300, linked_body if linked_body is not None else body)
    c.retail.sections = [
        SimpleNamespace(Name=b".text", VirtualAddress=0x100, Misc_VirtualSize=0xf00, SizeOfRawData=0xf00),
        SimpleNamespace(Name=b".rdata", VirtualAddress=0x2000, Misc_VirtualSize=0x500, SizeOfRawData=0x500),
        SimpleNamespace(Name=b".data", VirtualAddress=0x3000, Misc_VirtualSize=0x500, SizeOfRawData=0x500)]
    ledger = tmp_path / "functions.csv"
    rows = [dict(name=symbol, target_rva="0x100", target_size=str(len(body)), source=p["source"],
                 status="matched", notes=""), *extra_rows]
    with ledger.open("w") as f:
        w = csv.DictWriter(f, fieldnames=list(rows[0]))
        w.writeheader()
        w.writerows(rows)
    return c, ledger, data_rows or []


def test_absolute_address_getter_reports_owner_and_operand_offset(tmp_path):
    value = 0x403100
    body = b"\xb8" + struct.pack("<I", value) + b"\xc3"
    c, ledger, data = absolute_case(tmp_path, body,
        data_rows=[dict(row("TheGlobal", 0x3100, 16), source="Code/Global.cpp")])
    result = iso.unrelocated_retail_addresses(c, ledger, data)
    assert result["counts"]["defects"] == 1 and result["counts"]["ambiguous"] == 0
    d = result["defects"][0]
    assert d["offset"] == 1 and d["retail_address"] == "0x403100"
    assert d["target_kind"] == "data" and d["symbol"] == "getter"
    assert d["ledger_global_exists"] and d["ledger_global_extent_covers"]
    assert d["retail_owners"][0]["name"] == "TheGlobal"
    assert c.defects[0]["family"] == "unrelocated_retail_address"
    assert json.loads(c.defects[0]["evidence"])["offset"] == 1


def test_absolute_memory_displacement_even_in_compare_is_address(tmp_path):
    body = b"\x83\x3d" + struct.pack("<I", 0x402100) + b"\x00\xc3"
    c, ledger, data = absolute_case(tmp_path, body)
    result = iso.unrelocated_retail_addresses(c, ledger, data)
    assert result["by_kind"] == {"rdata": 1}
    d = result["defects"][0]
    assert d["operand_kind"] == "displacement" and d["offset"] == 2
    assert d["retail_owners"] == "none" and not d["ledger_global_exists"]


def test_absolute_moffs_a1_and_a3_and_text_target(tmp_path):
    for opcode in (b"\xa1", b"\xa3", b"\xb8"):
        body = opcode + struct.pack("<I", 0x400200) + b"\xc3"
        target_row = dict(name="code_target", target_rva="0x200", target_size="4",
                          source="Code/target.cpp", status="matched", notes="")
        c, ledger, data = absolute_case(tmp_path, body, extra_rows=[target_row])
        result = iso.unrelocated_retail_addresses(c, ledger, data)
        assert result["by_kind"] == {"text": 1}
        assert result["defects"][0]["retail_owners"][0]["name"] == "code_target"


def test_real_constant_capacity_accessor_is_ambiguous_not_a_defect(tmp_path):
    # Actual capacity formula for a 512-byte element, not an address.
    value = 0xffffffff // 512
    body = b"\xb8" + struct.pack("<I", value) + b"\xc3"
    c, ledger, data = absolute_case(tmp_path, body, symbol="?max_size@_STL@@QBEIXZ")
    c.retail.sections[-1].Misc_VirtualSize = 0x400000
    result = iso.unrelocated_retail_addresses(c, ledger, data)
    assert result["counts"]["defects"] == 0 and result["counts"]["ambiguous"] == 1
    assert result["ambiguous"][0]["ambiguity_reason"] == "capacity_accessor_numeric_interpretation"
    assert not c.defects


def test_comparison_and_add_without_owner_remain_unresolved(tmp_path):
    for prefix in (b"\x3d", b"\x05"):  # cmp eax,imm / add eax,imm
        body = prefix + struct.pack("<I", 0x403100) + b"\xc3"
        c, ledger, data = absolute_case(tmp_path, body)
        result = iso.unrelocated_retail_addresses(c, ledger, data)
        assert result["counts"]["defects"] == 0
        assert result["ambiguous"][0]["ambiguity_reason"] == "integer_or_pointer_use_unresolved"


def test_arithmetic_that_then_dereferences_is_not_numeric_only(tmp_path):
    body = b"\xb8" + struct.pack("<I", 0x403100) + b"\x83\xc0\x04\x8b\x00\xc3"
    c, ledger, data = absolute_case(tmp_path, body)
    result = iso.unrelocated_retail_addresses(c, ledger, data)
    assert result["counts"]["defects"] == 1 and result["counts"]["ambiguous"] == 0


def test_typed_nonaddress_data_collision_is_ambiguous_but_untyped_word_is_not(tmp_path):
    value = 0x403100
    body = b"\xb8" + struct.pack("<I", value) + b"\xc3"
    for kind, expected in (("float", 1), ("global", 0)):
        c, ledger, data = absolute_case(tmp_path, body,
            data_rows=[dict(row("numeric_payload", 0x2200, 4, kind), source="Code/number.cpp")])
        c.retail.put(0x2200, struct.pack("<I", value))
        result = iso.unrelocated_retail_addresses(c, ledger, data)
        assert result["counts"]["ambiguous"] == expected
        assert result["counts"]["defects"] == 1 - expected
        if expected:
            assert result["ambiguous"][0]["numeric_data_witnesses"][0]["kind"] == "float"


def test_object_relocation_also_requires_image_fixup(tmp_path):
    body = b"\xb8" + struct.pack("<I", 0x403100) + b"\xc3"
    object_body = b"\xb8" + bytes(4) + b"\xc3"
    linked_body = b"\xb8" + struct.pack("<I", 0x10003100) + b"\xc3"
    c, ledger, data = absolute_case(tmp_path, body, object_body=object_body,
                                   linked_body=linked_body, relocs=[(1, 6)])
    result = iso.unrelocated_retail_addresses(c, ledger, data)
    assert result["counts"]["defects"] == 1
    assert result["by_family"] == {"missing_image_relocation": 1}
    assert result["defects"][0]["linked_operand"] == "0x10003100"
    assert result["counts"]["operands_with_object_relocation"] == 1
    c.ours.relocations.add(0x301)
    c.defects.clear()
    result = iso.unrelocated_retail_addresses(c, ledger, data)
    assert not result["defects"]
    assert result["counts"]["operands_with_object_and_image_relocation"] == 1


def test_partial_relocation_does_not_falsely_pass_operand(tmp_path):
    body = b"\xb8" + struct.pack("<I", 0x403100) + b"\xc3"
    c, ledger, data = absolute_case(tmp_path, body, relocs=[(2, 10)])
    result = iso.unrelocated_retail_addresses(c, ledger, data)
    assert result["counts"]["partial_operand_relocation_unanalyzed"] == 1
    assert result["counts"]["defects"] == 0


def test_relative_call_is_not_an_absolute_retail_operand(tmp_path):
    body = b"\xe8" + struct.pack("<i", 0x200 - 0x105) + b"\xc3"
    c, ledger, data = absolute_case(tmp_path, body)
    result = iso.unrelocated_retail_addresses(c, ledger, data)
    assert result["counts"]["defects"] == 0
    assert result["counts"]["relative_control_operands_excluded"] == 1


def test_missing_object_or_different_bytes_are_unanalyzed(tmp_path):
    body = b"\xb8" + struct.pack("<I", 0x403100) + b"\xc3"
    c, ledger, data = absolute_case(tmp_path, body)
    del c.publics[0]["coff"]
    result = iso.unrelocated_retail_addresses(c, ledger, data)
    assert result["counts"]["rows_without_unique_coff_location"] == 1
    assert result["counts"]["defects"] == 0
    c, ledger, data = absolute_case(tmp_path, body, object_body=b"\xb9" + body[1:])
    result = iso.unrelocated_retail_addresses(c, ledger, data)
    assert result["counts"]["rows_byte_evidence_differs"] == 1
    assert result["counts"]["defects"] == 0


def test_cfg_does_not_decode_skipped_inline_data(tmp_path):
    body = b"\xeb\x05\xb8" + struct.pack("<I", 0x403100) + b"\xc3"
    c, ledger, data = absolute_case(tmp_path, body)
    result = iso.unrelocated_retail_addresses(c, ledger, data)
    assert result["counts"]["defects"] == 0
    assert result["counts"]["bytes_unvisited_code_or_data"] == 5


def test_manifest_windows_paths_preserve_code_relocation_offsets(tmp_path):
    directory = tmp_path / "objects"
    directory.mkdir()
    obj = directory / "code.obj"
    iso.link_cycle.write_coff(obj, [(".text", 0x60000020, b"\xb8" + bytes(4) + b"\xc3", 0)],
        [("f", 1, 0, iso.link_cycle.EXTERNAL), ("target", 0, 0, iso.link_cycle.EXTERNAL)],
        {1: [(1, "target", iso.link_cycle.DIR32)]})
    manifest = tmp_path / "objects.json"
    manifest.write_text(json.dumps([dict(path="objects\\code.obj", sha256=iso.digest(obj), source="Code/f.cpp")]))
    p = public("f", 0x300, 6)
    p["object"] = "code.obj"
    iso.attach_objects([p], manifest)
    assert p["coff"]["section"]["relocations"] == ((1, iso.link_cycle.DIR32),)
    assert p["coff"]["offset"] == 0


def test_absolute_instruction_with_both_displacement_and_immediate(tmp_path):
    body = b"\xc7\x05" + struct.pack("<I", 0x402100) + struct.pack("<I", 0x403100) + b"\xc3"
    c, ledger, data = absolute_case(tmp_path, body)
    result = iso.unrelocated_retail_addresses(c, ledger, data)
    assert [(d["offset"], d["operand_kind"]) for d in result["defects"]] == [(2, "displacement")]
    assert [(d["offset"], d["operand_kind"]) for d in result["ambiguous"]] == [(6, "immediate")]
    assert result["ambiguous"][0]["ambiguity_reason"] == "integer_or_pointer_use_unresolved"


def test_coff_operand_offset_includes_symbol_start(tmp_path):
    body = b"\xb8" + struct.pack("<I", 0x403100) + b"\xc3"
    c, ledger, data = absolute_case(tmp_path, body)
    c.publics[0]["coff"] = dict(offset=3, section=dict(
        body=b"\x90" * 3 + body, size=9, flags=0x60000020, relocations=((4, 6),)))
    c.ours.relocations.add(0x301)
    result = iso.unrelocated_retail_addresses(c, ledger, data)
    assert result["counts"]["operands_with_object_relocation"] == 1
    assert result["counts"]["defects"] == 0


def test_code_symbol_with_two_coff_locations_is_unanalyzed(tmp_path):
    obj = tmp_path / "a.obj"
    body = b"\xb8" + struct.pack("<I", 0x403100) + b"\xc3"
    iso.link_cycle.write_coff(obj,
        [(".text$a", 0x60000020, body, 0), (".text$b", 0x60000020, body, 0)],
        [("getter", 1, 0, iso.link_cycle.EXTERNAL), ("getter", 2, 0, iso.link_cycle.EXTERNAL)])
    manifest = tmp_path / "objects.json"
    manifest.write_text(json.dumps([dict(path=obj.name, sha256=iso.digest(obj), source="Code/getter.cpp")]))
    c, ledger, data = absolute_case(tmp_path, body)
    p = c.publics[0]
    del p["coff"]
    p["object"] = obj.name
    counts = iso.attach_objects([p], manifest)
    assert counts["code_symbol_locations_ambiguous"] == 1 and "coff" not in p
    result = iso.unrelocated_retail_addresses(c, ledger, data)
    assert result["counts"]["rows_without_unique_coff_location"] == 1


def test_capacity_name_does_not_hide_a_dereference(tmp_path):
    body = b"\xb8" + struct.pack("<I", 0x403100) + b"\x8b\x00\xc3"
    c, ledger, data = absolute_case(tmp_path, body, symbol="?max_size@_STL@@QBEIXZ")
    result = iso.unrelocated_retail_addresses(c, ledger, data)
    assert result["counts"]["defects"] == 1 and result["counts"]["ambiguous"] == 0


def test_absolute_address_inside_global_extent_has_no_exact_global(tmp_path):
    body = b"\xb8" + struct.pack("<I", 0x403104) + b"\xc3"
    c, ledger, data = absolute_case(tmp_path, body, data_rows=[row("container", 0x3100, 16)])
    result = iso.unrelocated_retail_addresses(c, ledger, data)
    d = result["defects"][0]
    assert d["ledger_global_exists"] is False and d["ledger_global_extent_covers"] is True
    assert d["retail_owners"][0]["offset"] == 4


def test_address_only_cli_keeps_ambiguous_out_of_defects_tsv(tmp_path, monkeypatch):
    root = tmp_path / "repo"
    (root / "reverse").mkdir(parents=True)
    monkeypatch.setattr(iso.build, "ROOT", root)
    (root / "reverse/data_ledger.csv").write_text(
        "address,size,kind,name,source,names\n0x2004,4,global,scalar,Code/scalar.cpp,\n")
    (root / "reverse/functions.csv").write_text(
        "name,target_rva,target_size,status,notes,source\n"
        "getter,0x1020,6,matched,,Code/getter.cpp\n"
        "constant,0x1030,6,matched,,Code/constant.cpp\n")
    ours, retail = tmp_path / "exit.exe", tmp_path / "retail.exe"
    entries = []
    for path, base in ((ours, 0x10000000), (retail, 0x400000)):
        write_pe(path, base)
        raw = bytearray(path.read_bytes())
        raw[0x220:0x226] = b"\xb8" + struct.pack("<I", 0x402004) + b"\xc3"
        raw[0x230:0x236] = b"\x3d" + struct.pack("<I", 0x402008) + b"\xc3"
        path.write_bytes(raw)
    for name, opcode in (("getter", b"\xb8"), ("constant", b"\x3d")):
        obj = tmp_path / (name + ".obj")
        body = opcode + struct.pack("<I", 0x402004 if name == "getter" else 0x402008) + b"\xc3"
        iso.link_cycle.write_coff(obj, [(".text", 0x60000020, body, 0)],
                                  [(name, 1, 0, iso.link_cycle.EXTERNAL)])
        entries.append(dict(path=obj.name, sha256=iso.digest(obj), source="Code/" + name + ".cpp"))
    manifest = tmp_path / "objects.json"
    manifest.write_text(json.dumps(entries))
    mapfile = tmp_path / "exit.map"
    mapfile.write_text(" 0001:00000020 getter 10001020 f getter.obj\n"
                       " 0001:00000030 constant 10001030 f constant.obj\n")
    (tmp_path / "image_receipt.json").write_text(json.dumps(dict(
        kind="diagnostic", base="0x10000000", stubbed=[],
        image_sha256=iso.digest(ours), map_sha256=iso.digest(mapfile))))
    out = tmp_path / "report"
    assert iso.main(["--image", str(ours), "--map", str(mapfile), "--retail", str(retail),
                     "--objects", str(manifest), "--out", str(out), "--address-only"]) == 1
    import csv
    with (out / "defects.tsv").open() as f:
        defects = list(csv.DictReader(f, delimiter="\t"))
    with (out / "ambiguous.tsv").open() as f:
        ambiguous = list(csv.DictReader(f, delimiter="\t"))
    assert len(defects) == len(ambiguous) == 1
    assert defects[0]["family"] == "unrelocated_retail_address"
    assert json.loads(defects[0]["evidence"])["offset"] == 1
    assert ambiguous[0]["family"] == "unrelocated_retail_address_ambiguous"
    assert json.loads((out / "report.json").read_text())["analysis_scope"] == "absolute address code/data and defined-data pointer evidence only"
    assert json.loads((out / "report.json").read_text())["relocation_bounds"]["counts"] == {}


def test_float_literal_gap_is_not_nonaddress_payload(tmp_path):
    value = 0x403100
    body = b"\xb8" + struct.pack("<I", value) + b"\xc3"
    c, ledger, data = absolute_case(tmp_path, body,
        data_rows=[row("__real@3f800000", 0x2200, 8, "float")])
    c.retail.put(0x2200, struct.pack("<I", 0x3f800000) + struct.pack("<I", value))
    result = iso.unrelocated_retail_addresses(c, ledger, data)
    assert result["counts"]["defects"] == 1 and result["counts"]["ambiguous"] == 0


def test_untyped_value_then_comparison_and_overwrite_is_ambiguous(tmp_path):
    body = b"\xb8" + struct.pack("<I", 0x403100) + b"\x83\xf8\x01\xb8\x00\x00\x00\x00\xc3"
    c, ledger, data = absolute_case(tmp_path, body)
    result = iso.unrelocated_retail_addresses(c, ledger, data)
    assert result["counts"]["defects"] == 0
    assert result["ambiguous"][0]["ambiguity_reason"] == "integer_or_pointer_use_unresolved"


def test_printable_class_tag_getter_is_not_claimed_as_address(tmp_path):
    # TEX happens to lie in .text in retail, but is an integer class ID.
    body = b"\xb8" + struct.pack("<I", int.from_bytes(b"TEX", "big")) + b"\xc3"
    c, ledger, data = absolute_case(tmp_path, body)
    c.retail.sections[-1].Misc_VirtualSize = 0x400000
    result = iso.unrelocated_retail_addresses(c, ledger, data)
    assert result["counts"]["defects"] == 0 and result["counts"]["ambiguous"] == 1
    assert result["ambiguous"][0]["ambiguity_reason"] == "printable_integer_tag_or_address"


def test_inline_month_store_is_ambiguous_not_a_pointer_claim(tmp_path):
    value = int.from_bytes(b"Mon", "big")
    body = b"\xc7\x44\x24\x04" + struct.pack("<I", value) + b"\xc3"
    c, ledger, data = absolute_case(tmp_path, body)
    c.retail.sections[-1].Misc_VirtualSize = 0x400000
    result = iso.unrelocated_retail_addresses(c, ledger, data)
    assert not result["defects"] and len(result["ambiguous"]) == 1


def test_stored_rgb_scalar_and_push_without_owner_or_type_are_ambiguous(tmp_path):
    for body in (b"\xc7\x00" + struct.pack("<I", 0x403100) + b"\xc3",
                 b"\x68" + struct.pack("<I", 0x403100) + b"\xc3"):
        c, ledger, data = absolute_case(tmp_path, body)
        result = iso.unrelocated_retail_addresses(c, ledger, data)
        assert not result["defects"]
        assert result["ambiguous"][0]["ambiguity_reason"] == "integer_or_pointer_use_unresolved"


def test_bitmask_integer_is_numeric_even_when_result_indexes_memory(tmp_path):
    body = b"\x25" + struct.pack("<I", 0x403100) + b"\x8b\x04\x85\x00\x00\x00\x00\xc3"
    c, ledger, data = absolute_case(tmp_path, body)
    result = iso.unrelocated_retail_addresses(c, ledger, data)
    assert not result["defects"]
    assert result["ambiguous"][0]["ambiguity_reason"] == "arithmetic_or_comparison_context"


def test_numeric_witness_elsewhere_demotes_getter_but_not_absolute_displacement(tmp_path):
    value = 0x403100
    body = b"\xb8" + struct.pack("<I", value) + b"\xc3"
    c, ledger, data = absolute_case(tmp_path, body)
    # A separate bitmask supplies an explicit numeric interpretation of the same bits.
    p = public("number", 0x500, 6)
    numeric = b"\x25" + struct.pack("<I", value) + b"\xc3"
    p["coff"] = dict(offset=0, section=dict(body=numeric, size=6, flags=0x60000020, relocations=()))
    c.publics.append(p)
    c.retail.put(0x200, numeric); c.ours.put(0x500, numeric)
    with ledger.open("a") as f:
        f.write("number,0x200,6,Code/number.cpp,matched,\n")
    q = public("absolute_load", 0x700, 6)
    load = b"\xa1" + struct.pack("<I", value) + b"\xc3"
    q["coff"] = dict(offset=0, section=dict(body=load, size=6, flags=0x60000020, relocations=()))
    c.publics.append(q)
    c.retail.put(0x280, load); c.ours.put(0x700, load)
    with ledger.open("a") as f:
        f.write("absolute_load,0x280,6,Code/absolute_load.cpp,matched,\n")
    result = iso.unrelocated_retail_addresses(c, ledger, data)
    assert result["counts"]["defects"] == 1
    assert result["defects"][0]["operand_kind"] == "displacement"
    assert any(d["ambiguity_reason"] == "numeric_interpretation_elsewhere" for d in result["ambiguous"])


def test_p7_literal_getter_is_a_data_address_even_without_a_ledger_owner(tmp_path):
    body = b"\xb8" + struct.pack("<I", 0xdc2274) + b"\xc3"
    c, ledger, data = absolute_case(tmp_path, body, symbol="?Rva00226140Get@@YAHXZ")
    c.retail.sections[-1].Misc_VirtualSize = 0xaa7000
    result = iso.unrelocated_retail_addresses(c, ledger, data)
    assert result["counts"]["defects"] == 1 and result["counts"]["ambiguous"] == 0
    d = result["defects"][0]
    assert d["retail_address"] == "0xdc2274" and d["target_kind"] == "data"
    assert d["retail_owners"] == "none" and not d["ledger_global_exists"]


def test_large_base_relative_field_offset_is_ambiguous_not_absolute_address(tmp_path):
    body = b"\x8b\x83" + struct.pack("<I", 0x403100) + b"\xc3"
    c, ledger, data = absolute_case(tmp_path, body)
    result = iso.unrelocated_retail_addresses(c, ledger, data)
    assert result["counts"]["defects"] == 0 and result["counts"]["ambiguous"] == 1
    assert result["ambiguous"][0]["ambiguity_reason"] == "base_relative_displacement_unresolved"


def test_source_data_row_owner_is_reported_independently_of_inventory(tmp_path):
    body = b"\xb8" + struct.pack("<I", 0x403100) + b"\xc3"
    c, ledger, data = absolute_case(tmp_path, body)
    ledger.with_name("data_rows.csv").write_text(
        "name,address,address_kind,size,source,status\n"
        "RealGlobal,0x403100,va,8,Code/RealGlobal.cpp,matched\n")
    result = iso.unrelocated_retail_addresses(c, ledger, data)
    d = result["defects"][0]
    assert d["ledger_global_exists"] and d["source_global_exists"]
    assert d["retail_owners"][0]["register"] == "data_rows"
    assert d["retail_owners"][0]["name"] == "RealGlobal"


def test_missing_source_data_register_is_unknown_not_no_global(tmp_path):
    body = b"\xb8" + struct.pack("<I", 0x403100) + b"\xc3"
    c, ledger, data = absolute_case(tmp_path, body)
    result = iso.unrelocated_retail_addresses(c, ledger, data)
    assert result["counts"]["source_data_rows_available"] == 0
    assert result["defects"][0]["source_global_exists"] is None


def test_pushed_pointer_to_exact_global_start_is_a_defect(tmp_path):
    body = b"\x68" + struct.pack("<I", 0x403100) + b"\xc3"
    c, ledger, data = absolute_case(tmp_path, body, data_rows=[row("table", 0x3100, 16)])
    result = iso.unrelocated_retail_addresses(c, ledger, data)
    assert result["by_origin"] == {"code": 1}
    assert result["defects"][0]["address_evidence"] == "exact_ledger_start"
    assert not result["ambiguous"]


def test_printable_tag_that_is_exact_function_start_is_a_defect(tmp_path):
    value = 0x4b2d3a
    body = b"\x68" + struct.pack("<I", value) + b"\xc3"
    owner = dict(name="function_target", target_rva=hex(value - 0x400000), target_size="10",
                 source="Code/target.cpp", status="matched", notes="")
    c, ledger, data = absolute_case(tmp_path, body, extra_rows=[owner])
    c.retail.sections[0].Misc_VirtualSize = 0x100000
    result = iso.unrelocated_retail_addresses(c, ledger, data)
    assert len(result["defects"]) == 1 and not result["ambiguous"]


def test_exact_pointer_comparison_is_not_numeric_proof(tmp_path):
    body = b"\x3d" + struct.pack("<I", 0x403100) + b"\xc3"
    c, ledger, data = absolute_case(tmp_path, body, data_rows=[row("table", 0x3100, 16)])
    result = iso.unrelocated_retail_addresses(c, ledger, data)
    assert len(result["defects"]) == 1 and not result["ambiguous"]


def test_exact_start_with_real_numeric_witness_stays_ambiguous(tmp_path):
    body = b"\x25" + struct.pack("<I", 0x403100) + b"\xc3"
    c, ledger, data = absolute_case(tmp_path, body, data_rows=[row("coincidence", 0x3100, 16)])
    result = iso.unrelocated_retail_addresses(c, ledger, data)
    assert not result["defects"]
    assert result["ambiguous"][0]["ambiguity_reason"] == "arithmetic_or_comparison_context"


def test_exact_string_object_start_is_an_address_argument(tmp_path):
    body = b"\x68" + struct.pack("<I", 0x403100) + b"\xc3"
    c, ledger, data = absolute_case(tmp_path, body, data_rows=[row("empty_string", 0x3100, 8, "string")])
    c.retail.put(0x3100, bytes(8))
    result = iso.unrelocated_retail_addresses(c, ledger, data)
    assert len(result["defects"]) == 1 and not result["ambiguous"]


def test_typed_first_pointer_argument_without_ledger_owner_is_detected(tmp_path):
    body = b"\x6a\x00\x68" + struct.pack("<I", 0x403100) + b"\xe8" + struct.pack("<i", 0x200 - 0x10c) + b"\xc3"
    callee = dict(name="?add@MultiIniFieldParse@@QAEXPBUFieldParse@@I@Z", target_rva="0x200", target_size="5",
                  source="Code/parser.cpp", status="matched", notes="")
    c, ledger, data = absolute_case(tmp_path, body, extra_rows=[callee])
    result = iso.unrelocated_retail_addresses(c, ledger, data)
    assert len(result["defects"]) == 1 and not result["ambiguous"]
    assert result["defects"][0]["address_evidence"] == "typed_first_pointer_argument"
    # A later push means the literal is not the first stack argument.
    body = b"\x68" + struct.pack("<I", 0x403100) + b"\x6a\x00\xe8" + struct.pack("<i", 0x200 - 0x10c) + b"\xc3"
    c, ledger, data = absolute_case(tmp_path, body, extra_rows=[callee])
    result = iso.unrelocated_retail_addresses(c, ledger, data)
    assert not result["defects"] and len(result["ambiguous"]) == 1


def with_data_section(c):
    from types import SimpleNamespace
    c.ours.sections = [SimpleNamespace(Name=b".data", VirtualAddress=0x2000,
        Misc_VirtualSize=0x20, SizeOfRawData=0x10)]
    return c


def test_data_word_exact_function_start_and_unknown_interior_are_distinct(tmp_path):
    target = dict(name="code_target", target_rva="0x200", target_size="16",
                  source="Code/target.cpp", status="matched", notes="")
    c, ledger, data = absolute_case(tmp_path, b"\xc3", extra_rows=[target])
    with_data_section(c)
    c.publics.append(public("manual_vtable", 0x2000, 16))
    c.ours.put(0x2000, struct.pack("<IIII", 0x400200, 0x400204, 0x403100, 0x400200))
    c.ours.relocations.add(0x200c)
    result = iso.unrelocated_retail_addresses(c, ledger, data)
    assert result["by_origin"] == {"data": 1}
    d = result["defects"][0]
    assert d["symbol"] == "manual_vtable" and d["offset"] == 0
    assert d["row_rva"] is None and d["image_rva"] == "0x2000"
    assert d["target_kind"] == "text"
    assert len(result["ambiguous"]) == 2
    assert result["counts"]["data_words_with_image_relocation"] == 1
    assert result["counts"]["data_virtual_zerofill_bytes_not_scanned"] == 0x10
    assert result["counts"]["data_aligned_words_considered"] == 4


def test_data_literal_payload_and_import_directory_are_excluded(tmp_path):
    from types import SimpleNamespace
    target = dict(name="code_target", target_rva="0x200", target_size="4",
                  source="Code/target.cpp", status="matched", notes="")
    c, ledger, data = absolute_case(tmp_path, b"\xc3", extra_rows=[target])
    with_data_section(c)
    c.ours.put(0x2000, struct.pack("<IIII", 0x400200, 0, 0x400200, 0x400200))
    c.publics.append(public("??_C@_1wide", 0x2000, 8))
    c.publics.append(public("next", 0x2008, 4))
    directories = [SimpleNamespace(VirtualAddress=0, Size=0) for _ in range(13)]
    directories[12] = SimpleNamespace(VirtualAddress=0x200c, Size=4)
    c.ours.pe = SimpleNamespace(OPTIONAL_HEADER=SimpleNamespace(DATA_DIRECTORY=directories))
    result = iso.unrelocated_retail_addresses(c, ledger, data)
    assert result["counts"]["data_literal_payload_candidates_excluded"] == 1
    assert result["counts"]["data_directory_words_excluded"] == 1
    assert result["by_origin"] == {"data": 1}
    assert result["defects"][0]["image_rva"] == "0x2008"


def test_data_word_matching_exact_global_start_is_a_defect(tmp_path):
    c, ledger, data = absolute_case(tmp_path, b"\xc3", data_rows=[row("global", 0x3100, 4)])
    with_data_section(c)
    c.ours.put(0x2000, struct.pack("<I", 0x403100))
    result = iso.unrelocated_retail_addresses(c, ledger, data)
    assert result["by_origin"] == {"data": 1}
    assert result["defects"][0]["ledger_global_exists"]
    assert result["counts"]["data_candidate_attribution_unresolved"] == 1


def test_overwritten_stack_argument_does_not_prove_pointer_use(tmp_path):
    body = b"\x68" + struct.pack("<I", 0x403100) + b"\xc7\x04\x24\x00\x00\x00\x00\xe8" + struct.pack("<i", 0x200 - 0x111) + b"\xc3"
    callee = dict(name="?add@MultiIniFieldParse@@QAEXPBUFieldParse@@I@Z", target_rva="0x200", target_size="5",
                  source="Code/parser.cpp", status="matched", notes="")
    c, ledger, data = absolute_case(tmp_path, body, extra_rows=[callee])
    result = iso.unrelocated_retail_addresses(c, ledger, data)
    assert not result["defects"] and len(result["ambiguous"]) == 1


def test_merged_import_lookup_and_hint_names_are_not_absolute_pointers(tmp_path):
    from types import SimpleNamespace
    target = dict(name="code_target", target_rva="0x200", target_size="4",
                  source="Code/target.cpp", status="matched", notes="")
    c, ledger, data = absolute_case(tmp_path, b"\xc3", extra_rows=[target])
    with_data_section(c)
    c.ours.put(0x2000, struct.pack("<IIII", 0x400200, 0x400200, 0x400200, 0x400200))
    entry = SimpleNamespace(hint_name_table_rva=0x2008, name=b"import")
    descriptor = SimpleNamespace(struct=SimpleNamespace(OriginalFirstThunk=0x2000,
        FirstThunk=0x4000, Name=0x4010), dll=b"x.dll", imports=[entry])
    c.ours.pe = SimpleNamespace(DIRECTORY_ENTRY_IMPORT=[descriptor])
    result = iso.unrelocated_retail_addresses(c, ledger, data)
    assert result["counts"]["data_directory_words_excluded"] == 4
    assert not result["defects"] and not result["ambiguous"]


def bounds_case(tmp_path, addend=24, size=20, kind=6):
    body = b"\x68" + struct.pack("<i", addend) + b"\xc3"
    linked = b"\x68" + struct.pack("<I", (0x10002000 + addend if kind == 6 else
        0x2000 + addend - 0x305) & 0xffffffff) + b"\xc3"
    c, ledger, _ = absolute_case(tmp_path, body, linked_body=linked, relocs=[(1, kind)])
    c.publics[0]["coff"]["section"]["relocation_targets"] = {1:dict(name="CPUNames", cls=2, section=0)}
    c.publics.extend([public("CPUNames", 0x2000, size), public("unrelated", 0x2000 + size, 16)])
    c.mapping = iso.Correspondence(c.publics, {"getter":{0x100}, "CPUNames":{0x3000}, "unrelated":{0x4000}})
    return c, ledger


def test_out_of_object_detects_p12_even_when_retail_arithmetic_is_correct(tmp_path):
    c, ledger = bounds_case(tmp_path)
    data = [row("CPUNames", 0x3000, 20), row("VideoNames", 0x3018, 16)]
    result = iso.relocation_bounds(c, data, ledger)
    assert result["counts"]["defects"] == 1
    d = result["defects"][0]
    assert d["symbol"] == "CPUNames" and d["addend"] == 24 and d["symbol_size"] == 20
    assert not d["one_past"] and d["actual_va"] == "0x10002018"
    assert d["actual_owners"][0]["name"] == "unrelated"
    assert d["retail_va"] == "0x403018" and d["retail_owners"][0]["name"] == "VideoNames"
    assert c.defects[0]["family"] == "out_of_object_pointer"


def test_bounds_inside_negative_and_beyond_end_are_distinct(tmp_path):
    for addend, expected in [(0,0),(19,0),(20,0),(24,1),(28,1),(-4,0)]:
        c, ledger = bounds_case(tmp_path, addend)
        result = iso.relocation_bounds(c, [], ledger)
        assert result["counts"]["defects"] == expected


def test_bounds_requires_actual_selected_target_and_extent(tmp_path):
    c, ledger = bounds_case(tmp_path)
    c.publics.append(public("CPUNames", 0x2800, 24))
    assert iso.relocation_bounds(c, [], ledger)["counts"]["target_map_ambiguous_or_absent"] == 1
    c, ledger = bounds_case(tmp_path)
    c.publics[1]["extent"] = None
    assert iso.relocation_bounds(c, [], ledger)["counts"]["target_extent_unanalyzed"] == 1
    c, ledger = bounds_case(tmp_path)
    c.ours.put(0x301, struct.pack("<I",0x10003018))
    assert iso.relocation_bounds(c, [], ledger)["counts"]["linked_target_resolution_differs_unanalyzed"] == 1


def test_rel32_bounds_and_static_symbol_object_qualification(tmp_path):
    c, ledger = bounds_case(tmp_path, kind=20)
    target = c.publics[0]["coff"]["section"]["relocation_targets"][1]
    target["cls"] = iso.link_cycle.STATIC
    c.publics[1]["object"] = c.publics[0]["object"]
    c.publics.append(public("CPUNames", 0x2800, 100))
    result = iso.relocation_bounds(c, [], ledger)
    assert result["counts"]["defects"] == 1


def test_bounds_only_cli_is_wired_and_writes_defects(tmp_path, monkeypatch):
    root=tmp_path/"root"; (root/"reverse").mkdir(parents=True)
    (root/"reverse/data_ledger.csv").write_text("address,size,kind,name,source,names\n0x3000,20,global,CPUNames,Code/names.cpp,\n0x3018,16,global,VideoNames,Code/names.cpp,\n")
    (root/"reverse/functions.csv").write_text("name,target_rva,target_size,status,notes,source\ngetter,0x1020,11,matched,,Code/getter.cpp\n")
    monkeypatch.setattr(iso.build,"ROOT",root)
    ours,retail=tmp_path/"exit.exe",tmp_path/"retail.exe"
    for path,base in [(ours,0x10000000),(retail,0x400000)]:
        write_pe(path,base)
        raw=bytearray(path.read_bytes());raw[0x220:0x22b]=b"\x68"+struct.pack("<I",base+0x3018)+b"\x68"+struct.pack("<I",base+0x3014)+b"\xc3";path.write_bytes(raw)
    obj=tmp_path/"getter.obj"
    iso.link_cycle.write_coff(obj,[(".text",0x60000020,b"\x68"+struct.pack("<I",24)+b"\x68"+struct.pack("<I",20)+b"\xc3",0),
        (".data",0xc0000040,bytes(40),0)],[("getter",1,0,2),("CPUNames",2,0,2),("unrelated",2,20,2)],{1:[(1,"CPUNames",6),(6,"CPUNames",6)]})
    manifest=tmp_path/"objects.json";manifest.write_text(json.dumps([dict(path=obj.name,sha256=iso.digest(obj),source="Code/getter.cpp")]))
    mapfile=tmp_path/"exit.map";mapfile.write_text(" 0001:00000020 getter 10001020 f getter.obj\n 0002:00000000 CPUNames 10003000 getter.obj\n 0002:00000014 unrelated 10003014 getter.obj\n")
    (tmp_path/"image_receipt.json").write_text(json.dumps(dict(kind="diagnostic",base="0x10000000",stubbed=[],image_sha256=iso.digest(ours),map_sha256=iso.digest(mapfile))))
    out=tmp_path/"out"
    assert iso.main(["--image",str(ours),"--map",str(mapfile),"--retail",str(retail),"--objects",str(manifest),"--out",str(out),"--relocation-bounds-only"])==1
    r=json.loads((out/"report.json").read_text())
    assert r["relocation_bounds"]["counts"]["defects"]==1
    assert r["defects"][0]["family"]=="out_of_object_pointer"
    assert "out_of_object_pointer" in (out/"defects.tsv").read_text()

    assert r["relocation_bounds"]["counts"]["leads"] == 1
    assert len(r["defects"]) == 1
    assert "out_of_object_pointer_lead" in (out/"relocation_leads.tsv").read_text()


def test_stlport_end_sentinel_is_a_lead_not_a_defect(tmp_path):
    c, ledger = bounds_case(tmp_path, addend=112, size=112)
    result = iso.relocation_bounds(c, [], ledger)
    assert result["counts"]["defects"] == 0 and result["counts"]["leads"] == 1
    assert result["leads"][0]["reason"] == "one_past_address"
    assert not c.defects


def test_indexed_negative_displacement_is_a_lead_not_a_defect(tmp_path):
    body = b"\x8b\x04\x85" + struct.pack("<i", -43) + b"\xc3"
    linked = b"\x8b\x04\x85" + struct.pack("<I", 0x10002000 - 43) + b"\xc3"
    c, ledger, _ = absolute_case(tmp_path, body, linked_body=linked, relocs=[(3,6)])
    c.publics[0]["coff"]["section"]["relocation_targets"] = {3:dict(name="arr",cls=2,section=0)}
    c.publics.append(public("arr",0x2000,80))
    result = iso.relocation_bounds(c, [], ledger)
    assert result["counts"]["defects"] == 0 and result["counts"]["leads"] == 1
    assert result["leads"][0]["reason"] == "indexed_displacement"
    assert not c.defects


def test_absolute_dereference_and_add_base_at_end_are_defects(tmp_path):
    for opcode, reason in [(b"\xa1","absolute_dereference"),(b"\xa3","absolute_dereference"),(b"\x05","out_of_bounds_add_base")]:
        c, ledger = bounds_case(tmp_path, addend=20, size=20)
        sec=c.publics[0]["coff"]["section"]
        sec["body"] = opcode + sec["body"][1:]
        c.ours.put(0x300, opcode + c.ours.read(0x301,5))
        result=iso.relocation_bounds(c,[],ledger)
        assert result["counts"]["defects"] == 1 and result["defects"][0]["reason"] == reason


def test_crt_section_marker_loop_is_a_lead(tmp_path):
    c,ledger=bounds_case(tmp_path,addend=4,size=4)
    c.publics[0]["coff"]["section"]["relocation_targets"][1]["name"]="___rtc_iaa"
    c.publics[1]["name"]="___rtc_iaa"
    result=iso.relocation_bounds(c,[],ledger)
    assert result["counts"]["leads"] == 1 and not result["defects"]
    assert result["leads"][0]["reason"] == "crt_section_marker"


def test_unknown_operand_is_ambiguous_not_a_defect(tmp_path):
    c,ledger=bounds_case(tmp_path)
    c.ours.put(0x300,b"\xc3")
    result=iso.relocation_bounds(c,[],ledger)
    assert result["counts"]["ambiguous"] == 1 and not result["defects"]
    assert result["ambiguous"][0]["reason"] == "relocation_not_a_decoded_operand"


def test_unanalyzed_reason_samples_are_capped_and_counted(tmp_path):
    c,ledger=bounds_case(tmp_path)
    sec=c.publics[0]["coff"]["section"]
    sec["body"]=bytes(80);sec["relocations"]=tuple((i*4,6) for i in range(20))
    sec["relocation_targets"]={i*4:dict(name="missing",cls=2,section=0) for i in range(20)}
    c.publics[0]["extent"]=80
    result=iso.relocation_bounds(c,[],ledger)
    assert result["counts"]["target_map_ambiguous_or_absent"] == 20
    assert len(result["unanalyzed_samples"]["target_map_ambiguous_or_absent"]) == 8


def test_address_and_bounds_only_modes_cannot_silently_skip_both(tmp_path):
    import pytest
    with pytest.raises(SystemExit) as exc:
        iso.main(["--image", str(tmp_path/"missing.exe"), "--map", str(tmp_path/"missing.map"),
                  "--address-only", "--relocation-bounds-only"])
    assert exc.value.code == 2


def test_comparison_only_beyond_end_is_ambiguous_not_a_defect(tmp_path):
    c,ledger=bounds_case(tmp_path,addend=752,size=744)
    sec=c.publics[0]["coff"]["section"];sec["body"]=b"\x3d"+sec["body"][1:]
    c.ours.put(0x300,b"\x3d"+c.ours.read(0x301,5))
    result=iso.relocation_bounds(c,[],ledger)
    assert result["counts"]["ambiguous"] == 1 and not result["defects"]
    assert result["ambiguous"][0]["reason"] == "beyond_end_comparison"


def test_comparison_with_absolute_memory_beyond_end_is_still_a_defect(tmp_path):
    body=b"\x83\x3d"+struct.pack("<I",24)+b"\x00\xc3"
    linked=b"\x83\x3d"+struct.pack("<I",0x10002018)+b"\x00\xc3"
    c,ledger,_=absolute_case(tmp_path,body,linked_body=linked,relocs=[(2,6)])
    c.publics[0]["coff"]["section"]["relocation_targets"]={2:dict(name="arr",cls=2,section=0)}
    c.publics.append(public("arr",0x2000,20))
    result=iso.relocation_bounds(c,[],ledger)
    assert result["counts"]["defects"] == 1 and not result["ambiguous"]
    assert result["defects"][0]["reason"] == "absolute_dereference"


def test_defined_data_pointer_image_check_uses_kept_copy(tmp_path,monkeypatch):
    import data_rows
    p=public("names",0x2000,8);c=checker([p],{})
    c.retail.data=b"unused fixture"
    records=[dict(tier="A",reason="retail_string_start",row="names",source=p["source"],object=p["object"],
        retail_rva="0x3000",offset=4,retail_value="0xbfaa80",object_value="0xbfaa80",entities=[])]
    monkeypatch.setattr(data_rows,"defined_data_pointer_report",lambda *args:dict(mode="report-only",counts=dict(tier_a=1,tier_b=0),findings=records))
    import reloc_ledger
    monkeypatch.setattr(reloc_ledger,"Image",lambda *args:None)
    c.ours.put(0x2004,struct.pack("<I",0xbfaa80))
    r=iso.defined_data_pointers(c,tmp_path/"manifest.json",tmp_path)
    assert r["counts"]["tier_a"]==1 and c.defects[0]["family"]=="defined_data_unrelocated_pointer"
    c.defects.clear();c.ours.put(0x2004,struct.pack("<I",0x10003000))
    r=iso.defined_data_pointers(c,tmp_path/"manifest.json",tmp_path)
    assert r["counts"]["tier_a"]==0 and not c.defects


def test_data_pointers_only_cli_catches_plain_number_string_pointer(tmp_path,monkeypatch):
    root=tmp_path/"root";(root/"reverse").mkdir(parents=True)
    monkeypatch.setattr(iso.build,"ROOT",root)
    (root/"reverse/data_rows.csv").write_text("name,address,address_kind,size,section,source,status,evidence,model\nnames,0x2020,rva,4,.rdata,Code/names.cpp,matched,fixture,test\n")
    (root/"reverse/data_ledger.csv").write_text("address,size,kind,name,source,names\n")
    (root/"reverse/functions.csv").write_text("name,target_rva,target_size,source,status,notes\n")
    ours,retail=tmp_path/"exit.exe",tmp_path/"retail.exe"
    for path,base in [(ours,0x10000000),(retail,0x400000)]:
        write_pe(path,base);raw=bytearray(path.read_bytes())
        raw[0x620:0x624]=struct.pack("<I",0x402100);raw[0x700:0x707]=b"OBJECT\0";path.write_bytes(raw)
    obj=tmp_path/"names.obj"
    iso.link_cycle.write_coff(obj,[(".rdata",0x40000040,struct.pack("<I",0x402100),0)],[("names",1,0,2)])
    manifest=tmp_path/"objects.json";manifest.write_text(json.dumps([dict(path=obj.name,sha256=iso.digest(obj),source="Code/names.cpp",provider="names.obj")]))
    mapfile=tmp_path/"exit.map";mapfile.write_text(" 0002:00000020 names 10002020 names.obj\n")
    (tmp_path/"image_receipt.json").write_text(json.dumps(dict(kind="diagnostic",base="0x10000000",stubbed=[],image_sha256=iso.digest(ours),map_sha256=iso.digest(mapfile))))
    for mode in ("--data-pointers-only","--address-only"):
        out=tmp_path/mode.removeprefix("--")
        assert iso.main(["--image",str(ours),"--map",str(mapfile),"--retail",str(retail),"--objects",str(manifest),"--out",str(out),mode])==1
        r=json.loads((out/"report.json").read_text())
        assert r["defined_data_pointers"]["counts"]["tier_a"]==1
        assert any(d["family"]=="defined_data_unrelocated_pointer" for d in r["defects"])
        assert "defined_data_unrelocated_pointer" in (out/"defects.tsv").read_text()


STORE_ECX = b"\xc7\x01"          # mov dword [ecx], imm32
DATA = [(0x1000, 0x5000)]


def vptr_retail(extra=b""):
    """Retail: ctor 0x200 stores table 0x2000 (2 slots, then a third code
    word at 0x2008 that a data word references), 0x280 stores a string whose
    first word only looks like code, 0x2c0 holds `extra` (each test's
    store pattern) and ends in ret."""
    retail = Memory(0x400000)
    store = lambda table: STORE_ECX + struct.pack("<I", retail.base + table)
    retail.put(0x200, store(0x2000) + b"\xc3")
    retail.put(0x280, store(0x2100) + b"\xc3")
    retail.put(0x2c0, extra + b"\xc3")
    retail.put(0x300, b"\xc3")
    retail.put(0x310, b"\x33\xc0\xc3")
    retail.put(0x320, b"\xc3")
    retail.put(0x330, b"\x90")
    for slot, target in enumerate((0x300, 0x310, 0x320)):
        retail.put(0x2000 + 4 * slot, struct.pack("<I", retail.base + target))
    retail.put(0x2100, struct.pack("<I", retail.base + 0x330))
    retail.put(0x3000, struct.pack("<I", retail.base + 0x2008))
    rows = [(0x200, 7), (0x280, 7), (0x2c0, len(extra) + 1), (0x300, 1), (0x310, 3), (0x320, 1)]
    return retail, rows


def stores_at(retail, rows, function, **kw):
    stores, counts = iso.retail_vptr_stores(retail, rows, data_ranges=DATA, **kw)
    return [s for s in stores if s["function"] == function], counts


def test_retail_vptr_stores_bound_tables_and_skip_strings():
    retail, rows = vptr_retail()
    stores, counts = iso.retail_vptr_stores(retail, rows, data_ranges=DATA)
    assert [(s["function"], s["table"], s["slots"], s["extent"]) for s in stores] == [(0x200, 0x2000, 2, "unproven")]
    assert counts["discovery_slot0_unrowed"] == 1   # the string at 0x2100
    stores, _ = iso.retail_vptr_stores(retail, rows, data_ranges=DATA, ledger_extents={0x2000: 12})
    assert (stores[0]["slots"], stores[0]["extent"]) == (3, "ledger")


def test_transient_only_when_overwritten_in_one_straight_line():
    base = 0x400000
    store = lambda table: STORE_ECX + struct.pack("<I", base + table)
    straight = store(0x2000) + store(0x2000)
    branched = store(0x2000) + b"\x74\x06" + store(0x2000)      # je over the second store
    rebased = store(0x2000) + b"\x8b\xce" + store(0x2000)       # mov ecx, esi: another object
    called = store(0x2000) + b"\xe8\x00\x00\x00\x00" + store(0x2000)
    for body, first_transient in ((straight, True), (branched, False), (rebased, False), (called, False)):
        retail, rows = vptr_retail(body)
        stores, _ = stores_at(retail, rows, 0x2c0)
        assert [s["transient"] for s in stores] == [first_transient, False], body.hex()


def vptr_case(table_symbol, extent, words, follower=None, filler=b"AAAA", **kw):
    """Image: the ctor's copy at 0x400 installs `table_symbol` at 0x3000."""
    retail, rows = vptr_retail()
    ours = Memory(0x10000000)
    ours.put(0x400, STORE_ECX + bytes(4) + b"\xc3")
    ours.pointer(0x402, 0x3000)
    ours.put(0x500, b"\xc3")
    ours.put(0x510, b"\x33\xc0\xc3")
    for slot, word in enumerate(words):
        if word:
            ours.pointer(0x3000 + 4 * slot, word)
    publics = [public("ctor", 0x400, 7), public("f300", 0x500, 1), public("f310", 0x510, 3),
               public(table_symbol, 0x3000, extent)]
    if follower:
        publics.append(public(follower, 0x3000 + extent, 4))
        ours.put(0x3000 + extent, filler)
    addresses = {"ctor": {0x200}, "f300": {0x300}, "f310": {0x310}}
    c = iso.Checker(ours, retail, publics, addresses)
    stores, _ = stores_at(retail, rows, 0x200, **kw)
    return c, stores


def judge(c, stores, sizes=None):
    return iso.vptr_store_report(c, stores, sizes or {0x200: 7, 0x300: 1, 0x310: 3})["stores"]


def test_full_table_is_no_defect_found_only_with_a_ledger_extent():
    c, stores = vptr_case("??_7Good@@6B@", 8, (0x500, 0x510), ledger_extents={0x2000: 8})
    assert [s["verdict"] for s in judge(c, stores)] == ["no-defect-found"]
    assert not c.defects
    c, stores = vptr_case("??_7Good@@6B@", 8, (0x500, 0x510))
    assert [s["verdict"] for s in judge(c, stores)] == ["extent-unproven"]


def test_incidental_reference_truncating_a_table_to_zero_is_never_ok():
    retail, rows = vptr_retail()
    retail.put(0x3004, struct.pack("<I", retail.base + 0x2001))   # unrelated word holds T+1
    stores, _ = iso.retail_vptr_stores(retail, rows, data_ranges=DATA)
    assert stores[0]["slots"] == 0
    c, _ = vptr_case("??_7Good@@6B@", 8, (0x500, 0x510))
    assert [s["verdict"] for s in judge(c, stores)] == ["unanalyzed-empty-table"]


def test_zero_placeholder_is_p18_shape():
    c, stores = vptr_case("?g_00C59B20@@3DA", 1, (), follower="next", filler=b"")
    store = judge(c, stores)[0]
    assert store["verdict"] == "zero-placeholder"
    # A one-byte placeholder (P18's char g_00C59B20) cannot hold even slot 0.
    assert store["slots"] == {"past-extent": 2}
    assert [d["family"] for d in c.defects] == ["vptr_store_zero"]


def test_slot_past_the_image_extent_fails_even_when_it_holds_the_expected_target():
    # A one-slot ??_7 followed by an unrelated global that happens to hold f310.
    c, stores = vptr_case("??_7Short@@6B@", 4, (0x500, 0x510), follower="g_unrelated",
                          ledger_extents={0x2000: 8})
    c.ours.pointer(0x3004, 0x510)
    store = judge(c, stores)[0]
    assert store["verdict"] == "bad" and store["slots"] == {"match": 1, "past-extent": 1}
    assert c.defects[0]["family"] == "vptr_store_slot"


def test_alias_name_needs_a_proven_fold_to_credit_a_slot():
    # f300's image address also carries g, ledgered at retail 0x310 (`xor eax,eax; ret`);
    # their retail bodies differ, so the name proves nothing and the body decides.
    c, stores = vptr_case("??_7Alias@@6B@", 8, (0x500, 0x500), ledger_extents={0x2000: 8})
    c.publics.append(public("g", 0x500, 1))
    c.addresses["g"] = {0x310}
    store = judge(c, stores)[0]
    # The correspondence maps 0x500 to 0x300 alone; the alias g does not rescue slot 1.
    assert store["slots"] == {"match": 1, "wrong": 1} and store["verdict"] == "bad"
    # An unrowed body with retail's bytes is equivalent, not wrong.
    c, stores = vptr_case("??_7Copy@@6B@", 8, (0x500, 0x520), ledger_extents={0x2000: 8})
    c.ours.put(0x520, b"\x33\xc0\xc3")
    c.publics.append(public("copy", 0x520, 3))
    assert judge(c, stores)[0]["slots"] == {"match": 1, "equiv": 1}


def test_store_in_a_differently_laid_out_image_copy_is_unanalyzed():
    c, stores = vptr_case("??_7Good@@6B@", 8, (0x500, 0x510), ledger_extents={0x2000: 8})
    # A relocated mov [ecx], imm32 at the retail offset, but the rest of the
    # function differs, so the offset proves no correspondence.
    c.ours.put(0x406, b"\x90")
    assert judge(c, stores)[0]["verdict"] == "unanalyzed-layout"


def test_store_without_image_fixup_is_unanalyzed():
    c, stores = vptr_case("??_7Good@@6B@", 8, (0x500, 0x510), ledger_extents={0x2000: 8})
    c.ours.relocations.discard(0x402)
    # Without the fixup the immediate is compared raw, so the layout check refuses first.
    assert judge(c, stores)[0]["verdict"] in ("unanalyzed-layout", "unanalyzed-fixup")


# Reproductions from the Codex re-check of 874198de22.

def test_interior_pointer_is_bounded_by_its_owner_extent():
    # ??_7Short covers 0x3000..0x3008; the store installs 0x3004, so the
    # second slot (0x3008) lies past the owner even though it holds f310.
    c, stores = vptr_case("??_7Short@@6B@", 8, (), ledger_extents={0x2000: 8})
    c.ours.pointer(0x402, 0x3004)
    c.ours.pointer(0x3004, 0x500)
    c.ours.pointer(0x3008, 0x510)
    c.publics.append(public("later", 0x3100, 4))
    store = judge(c, stores)[0]
    assert store["verdict"] == "bad" and store["slots"] == {"match": 1, "past-extent": 1}


def test_partial_last_slot_is_past_extent():
    c, stores = vptr_case("??_7Short@@6B@", 5, (0x500, 0x510), ledger_extents={0x2000: 8})
    store = judge(c, stores)[0]
    assert store["verdict"] == "bad" and store["slots"] == {"match": 1, "past-extent": 1}


def test_unknown_image_extent_is_never_no_defect_found():
    c, stores = vptr_case("??_7Short@@6B@", None, (0x500, 0x510), ledger_extents={0x2000: 8})
    c.publics.append(public("later", 0x3100, 4))
    store = judge(c, stores)[0]
    assert store["image_extent"] == "unproven" and store["verdict"] == "extent-unproven"


def test_proven_fold_still_needs_the_expected_image_body():
    c, stores = vptr_case("??_7Alias@@6B@", 8, (0x500, 0x510), ledger_extents={0x2000: 8})
    c.retail.put(0x320, b"\x33\xc0\xc3")           # retail fold twin of 0x310
    c.publics.append(public("g", 0x510, 3))
    c.addresses["g"] = {0x320}
    c.mapping = iso.Correspondence(c.publics, c.addresses)
    sizes = {0x200: 7, 0x300: 1, 0x310: 3, 0x320: 3}
    c.mapping.prove_folds(c.retail, sizes)
    c.ours.put(0x510, b"\xc2\x04\x00")              # image body: ret 4
    store = judge(c, stores, sizes)[0]
    assert store["verdict"] == "bad" and store["slots"] == {"match": 1, "wrong": 1}


def test_relative_branch_to_another_destination_breaks_layout():
    c, stores = vptr_case("??_7Good@@6B@", 8, (0x500, 0x510), ledger_extents={0x2000: 8})
    c.retail.put(0x200, b"\xeb\x00" + STORE_ECX + struct.pack("<I", c.retail.base + 0x2000) + b"\xc3")
    c.ours.put(0x400, b"\xeb\x04" + STORE_ECX + bytes(4) + b"\xc3")
    c.ours.relocations.discard(0x402)
    c.ours.pointer(0x404, 0x3000)
    stores, _ = stores_at(c.retail, [(0x200, 9), (0x300, 1), (0x310, 3)], 0x200, ledger_extents={0x2000: 8})
    assert judge(c, stores, {0x200: 9, 0x300: 1, 0x310: 3})[0]["verdict"].startswith("unanalyzed")


def test_discovery_counts_what_it_cannot_see():
    retail, rows = vptr_retail()
    retail.put(0x340, b"\x0f")
    retail.put(0x350, b"\x83\xe9\x04\xe9" + bytes(8))
    retail.put(0x2100, struct.pack("<I", retail.base + 0x350))
    _, counts = iso.retail_vptr_stores(retail, rows + [(0x340, 1), (0x6000, 4)], data_ranges=DATA)
    assert counts["discovery_undecoded_bytes"] == 1
    assert counts["discovery_rows_unreadable"] == 1
    assert counts["discovery_slot0_unrowed_adjustor"] == 1


def test_alias_without_a_fold_cannot_settle_an_undecided_body():
    # Slot 1's retail body reads a global; the image copy's pointer has no
    # correspondence, so the bytes cannot decide. Its alias h names two retail
    # bodies that are not a proven fold, so the name cannot decide either.
    c, stores = vptr_case("??_7Undecided@@6B@", 8, (0x500, 0x520), ledger_extents={0x2000: 8})
    c.retail.put(0x2004, struct.pack("<I", c.retail.base + 0x360))
    c.retail.put(0x360, b"\xa1" + struct.pack("<I", c.retail.base + 0x3800) + b"\xc3")
    c.retail.put(0x370, b"\xc2\x04\x00")
    c.ours.put(0x520, b"\xa1" + bytes(4) + b"\xc3")
    c.ours.pointer(0x521, 0x4000)
    c.publics.append(public("h", 0x520, 6))
    c.addresses["h"] = {0x360, 0x370}
    store = judge(c, stores, {0x200: 7, 0x300: 1, 0x360: 6, 0x370: 3})[0]
    assert store["slots"] == {"match": 1, "unk": 1} and store["verdict"] == "unanalyzed-slots"
    assert not c.defects


class KeptCopyMemory:
    def __init__(self, base, words):
        self.base, self.words = base, words

    def read(self, rva, size):
        body = self.words.get(rva)
        return None if body is None else (body + bytes(size))[:size]


COMDAT_CODE = 0x60001020
BODY = b"\x8b\x41\x04\xe8\x00\x00\x00\x00\xc3"
ROW = dict(target_rva="0x00001000", target_size="9", source="Code/Owner.cpp")


def kept_public(body=BODY, relocs=((4, 0x14),), flags=COMDAT_CODE, source="Code/Rival.cpp", offset=0, name="?f@@YAXXZ"):
    return dict(name=name, rva=0x5000, object="rival.obj", source=source, extent=len(body), external=True,
                coff=dict(offset=offset, section=dict(body=body, size=len(body), flags=flags, relocations=relocs)))


def judged(public, image=BODY, retail=BODY, ledger=None):
    return iso.kept_copies(KeptCopyMemory(0x10000000, {0x5000: image}), KeptCopyMemory(0x400000, {0x1000: retail}),
                           public if isinstance(public, list) else [public], ledger if ledger is not None else {"?f@@YAXXZ": [ROW]})


def test_kept_copy_equal_to_retail_is_not_listed():
    kept = judged(kept_public())
    assert kept["counts"] == {"rowed_comdats_checked": 1} and kept["names"] == []


def test_a_rival_units_different_copy_is_listed_with_who_kept_it():
    other = BODY[:1] + b"\x51" + BODY[2:]              # isKindOf's shape: another field offset under the row's name
    kept = judged(kept_public(), image=other)
    assert kept["counts"]["kept_copy_differs"] == kept["counts"]["kept_copy_differs_other_unit"] == 1
    entry = kept["names"][0]
    assert (entry["retail_rva"], entry["size"], entry["owner_source"], entry["kept_source"], entry["kept_is_owner"]) == (
        "0x00001000", 9, "Code/Owner.cpp", "Code/Rival.cpp", False)


def test_the_owners_own_differing_copy_is_counted_apart():
    kept = judged(kept_public(source="Code/Owner.cpp"), image=BODY[:1] + b"\x51" + BODY[2:])
    assert kept["counts"]["kept_copy_differs_owner_unit"] == 1 and kept["names"][0]["kept_is_owner"] is True


def test_relocation_fields_are_masked_and_only_they_are():
    linked = BODY[:4] + b"\x11\x22\x33\x44" + BODY[8:]
    assert judged(kept_public(), image=linked)["names"] == []
    assert judged(kept_public(relocs=()), image=linked)["counts"]["kept_copy_differs"] == 1


def test_a_section_relocation_masks_two_bytes():
    assert iso._masked(b"\x01\x02\x03\x04\xc3", [(0, 0xA)]) == b"\x00\x00\x03\x04\xc3"
    assert iso._masked(b"\x01\x02\x03\x04\xc3", [(0, 0x14)]) == b"\x00\x00\x00\x00\xc3"


def test_a_relocation_kind_of_unknown_width_is_counted_never_guessed():
    # DIR16 is 2 bytes, not the 4 every kind but SECTION used to be given.
    kept = judged(kept_public(relocs=((4, 1),)), image=b"\xff" * 9)
    assert kept["counts"] == {"rowed_comdats_checked": 1, "unanalyzed_relocation_kind": 1} and kept["names"] == []


def test_a_copy_that_is_only_the_start_of_a_longer_row_differs():
    # The review's case: a nine-byte retail row and a three-byte kept prefix compared equal.
    short = BODY[:3]
    kept = judged(kept_public(body=short, relocs=()), image=short)
    assert kept["counts"]["kept_copy_differs"] == 1


def test_short_jumps_to_different_places_are_different_copies():
    # The review's case: EB 90 and EB CC both stripped to EB.
    row = {"?f@@YAXXZ": [dict(ROW, target_size="2")]}
    kept = judged(kept_public(body=b"\xeb\x90", relocs=()), image=b"\xeb\x90", retail=b"\xeb\xcc", ledger=row)
    assert kept["counts"]["kept_copy_differs"] == 1


def test_a_tail_that_is_padding_on_an_instruction_boundary_is_no_difference():
    for extra in (b"\xcc", b"\x90", b"\xcc\x90\xcc"):
        assert judged(kept_public(body=BODY + extra), image=BODY + extra)["names"] == []          # the copy is longer
        row = {"?f@@YAXXZ": [dict(ROW, target_size=str(9 + len(extra)))]}
        assert judged(kept_public(), retail=BODY + extra, ledger=row)["names"] == []              # the row is longer


def test_padding_not_on_an_instruction_boundary_is_counted_never_passed():
    # EB alone does not decode: nothing shows the CC after it is padding.
    row = {"?f@@YAXXZ": [dict(ROW, target_size="2")]}
    kept = judged(kept_public(body=b"\xeb", relocs=()), image=b"\xeb", retail=b"\xeb\xcc", ledger=row)
    assert kept["counts"]["unanalyzed_padding_unproved"] == 1 and kept["names"] == []


def test_a_jump_onto_the_tail_means_it_is_not_padding():
    # The re-check's case: EB 00 lands on the CC, so those bytes can execute.
    assert iso.same_copy(bytes.fromhex("eb00"), bytes.fromhex("eb00cc"), []) is None
    assert iso.same_copy(bytes.fromhex("eb00cc"), bytes.fromhex("eb00"), []) is None


def test_a_prefix_that_can_fall_through_leaves_the_tail_unproved():
    for body in ("90", "7400c3"[:4], "e800000000", "33c0"):               # nop, je, call, xor: none of them stops
        assert iso.same_copy(bytes.fromhex(body), bytes.fromhex(body) + b"\xcc", []) is None, body


def test_any_branch_into_the_tail_means_it_is_not_padding():
    # je +1 lands past the ret, on the tail, though the body ends in a ret.
    assert iso.same_copy(bytes.fromhex("7401c3"), bytes.fromhex("7401c3cc"), []) is None
    assert iso.same_copy(bytes.fromhex("e801000000c3"), bytes.fromhex("e801000000c3cc90"), []) is None


def test_a_branch_inside_the_body_does_not_touch_the_tail():
    assert iso.same_copy(bytes.fromhex("740190c3"), bytes.fromhex("740190c3cc"), []) is True


def test_a_tail_after_each_unconditional_transfer_is_padding():
    for body in ("c3", "c20400", "ffe0", "ff2500000000"):                  # ret, ret 4, jmp eax, jmp [mem]
        assert iso.same_copy(bytes.fromhex(body), bytes.fromhex(body) + b"\xcc\x90", []) is True, body


def test_a_body_that_stops_decoding_proves_nothing_even_after_a_ret():
    assert iso.same_copy(bytes.fromhex("c30f"), bytes.fromhex("c30fcc"), []) is None


def test_a_relocated_tail_jump_goes_out_of_the_copy_not_onto_its_tail():
    # E9 rel32 to another function: masked to zero it would decode as a jump to the next byte.
    body = bytes.fromhex("e911223344")
    assert iso.same_copy(body, body + b"\xcc", [(1, 0x14)]) is True
    assert iso.same_copy(body[:1] + bytes(4), body[:1] + bytes(4) + b"\xcc", []) is None    # not relocated, it does land there


def test_same_copy_says_true_false_or_unknown():
    assert iso.same_copy(b"\xc3", b"\xc3", []) is True
    assert iso.same_copy(b"\xc3", b"\xc3\xcc", []) is True
    assert iso.same_copy(b"\xc3\xcc", b"\xc3", []) is True
    assert iso.same_copy(b"\xc3", b"\xc2", []) is False
    assert iso.same_copy(b"\xc3", b"\xc3\x55", []) is False
    assert iso.same_copy(b"\xeb", b"\xeb\xcc", []) is None


TWO_ROWS = [dict(ROW), dict(ROW, target_rva="0x00002000", source="Code/Second.cpp")]


def judged_two(first, second, image=BODY, rows=TWO_ROWS):
    return iso.kept_copies(KeptCopyMemory(0x10000000, {0x5000: image}), KeptCopyMemory(0x400000, {0x1000: first, 0x2000: second}),
                           [kept_public()], {"?f@@YAXXZ": rows})


def test_a_name_with_several_rows_is_judged_against_all_and_recorded():
    other = b"\x90" * 9
    kept = judged_two(other, BODY)                    # it matches only the second row
    assert kept["names"] == [] and kept["counts"]["names_with_several_rows"] == 1
    assert kept["several_rows"][0]["retail_rvas"] == ["0x00001000", "0x00002000"]
    assert kept["several_rows"][0]["verdicts"] == [False, True]


def test_the_order_of_several_rows_cannot_change_the_result():
    other = b"\x55" * 9
    assert judged_two(other, BODY)["names"] == judged_two(other, BODY, rows=TWO_ROWS[::-1])["names"] == []
    one = judged_two(other, other)
    two = judged_two(other, other, rows=TWO_ROWS[::-1])
    assert one == two and one["counts"]["kept_copy_differs"] == 1
    assert one["names"][0]["retail_rva"] == "0x00001000" and one["names"][0]["other_retail_rvas"] == "0x00002000"


def test_a_row_repeated_at_one_address_is_not_several_rows():
    assert "names_with_several_rows" not in judged(kept_public(), ledger={"?f@@YAXXZ": [ROW, dict(ROW)]})["counts"]


def test_the_owner_is_any_row_of_a_name_with_several():
    kept = iso.kept_copies(KeptCopyMemory(0x10000000, {0x5000: b"\xff" * 9}), KeptCopyMemory(0x400000, {0x1000: BODY, 0x2000: BODY}),
                           [kept_public(source="Code/Second.cpp")], {"?f@@YAXXZ": TWO_ROWS})
    assert kept["names"][0]["kept_is_owner"] is True


def test_a_copy_longer_than_the_row_differs():
    longer = kept_public(body=BODY + b"\x90\x55")
    assert judged(longer, image=BODY + b"\x90\x55")["counts"]["kept_copy_differs"] == 1


def test_a_symbol_inside_a_section_starts_at_its_offset():
    section = b"\xcc\xcc\xcc\xcc" + BODY
    public = kept_public(body=section, relocs=((8, 0x14),), offset=4)
    assert judged(public, image=BODY[:4] + b"\x11\x22\x33\x44" + BODY[8:])["names"] == []


def test_only_comdats_are_judged():
    kept = judged(kept_public(flags=0x60000020), image=b"\xff" * 9)
    assert kept["counts"] == {} and kept["names"] == []


def test_a_per_object_label_is_no_shared_copy():
    # Found on a real image: 2,688 funclet labels such as $L10008 read as kept copies, each named per object.
    label = dict(kept_public(), external=False)
    found = judged(label, image=b"\xff" * 9)
    assert (found["counts"], found["names"], found["several_rows"]) == ({}, [], [])
    # A label sharing an external's name does not make the external ambiguous.
    assert judged([label, kept_public()], image=BODY)["counts"] == {"rowed_comdats_checked": 1}


def test_a_name_without_a_row_is_skipped():
    assert judged(kept_public(), image=b"\xff" * 9, ledger={})["counts"] == {}


def test_what_it_cannot_read_is_counted_never_passed():
    public = kept_public()
    del public["coff"]
    assert judged(public)["counts"] == {"unanalyzed_no_object_evidence": 1}
    assert judged([kept_public(), kept_public()])["counts"] == {"unanalyzed_repeated_name": 2}
    unreadable = iso.kept_copies(KeptCopyMemory(0x10000000, {}), KeptCopyMemory(0x400000, {0x1000: BODY}), [kept_public()], {"?f@@YAXXZ": [ROW]})
    assert unreadable["counts"]["unanalyzed_unreadable"] == 1


def kept_copy_cli(tmp_path, monkeypatch, wrong):
    root = tmp_path / "repo"
    (root / "reverse").mkdir(parents=True)
    monkeypatch.setattr(iso.build, "ROOT", root)
    (root / "reverse/data_ledger.csv").write_text("address,size,kind,name,source,names\n")
    (root / "reverse/functions.csv").write_text("name,target_rva,target_size,notes,source\n?f@@YAXXZ,0x1020,1,,Code/owner.cpp\n")
    ours, retail = tmp_path / "exit.exe", tmp_path / "retail.exe"
    write_pe(ours, 0x10000000)
    write_pe(retail, 0x400000)
    if wrong:
        raw = bytearray(ours.read_bytes())
        raw[0x220] = 0xc2
        ours.write_bytes(raw)
    mapfile = tmp_path / "exit.map"
    mapfile.write_text(" Preferred load address is 10000000\n 0001:00000020 ?f@@YAXXZ 10001020 f rival.obj\n")
    obj = tmp_path / "rival.obj"
    iso.link_cycle.write_coff(obj, [(".text", COMDAT_CODE, b"\xc3", 0)], [("?f@@YAXXZ", 1, 0, iso.link_cycle.EXTERNAL)])
    manifest = tmp_path / "objects.json"
    manifest.write_text(json.dumps([dict(path=obj.name, sha256=iso.digest(obj), source="Code/rival.cpp")]))
    (tmp_path / "image_receipt.json").write_text(json.dumps(dict(kind="diagnostic", base="0x10000000", stubbed=[],
                                                                 image_sha256=iso.digest(ours), map_sha256=iso.digest(mapfile))))
    return ours, mapfile, retail, manifest, tmp_path / "report"


def test_kept_copies_only_writes_the_list_from_the_real_map(tmp_path, monkeypatch):
    ours, mapfile, retail, manifest, out = kept_copy_cli(tmp_path, monkeypatch, wrong=True)
    assert iso.main(["--image", str(ours), "--map", str(mapfile), "--retail", str(retail), "--objects", str(manifest),
                     "--out", str(out), "--kept-copies-only"]) == 1
    report = json.loads((out / "report.json").read_text())
    assert report["kept_copies"]["counts"]["kept_copy_differs_other_unit"] == 1
    assert "counts" not in report and "defects" not in report
    assert report["object_analysis"]["extents_attached"] == 1
    lines = (out / "kept_copies.tsv").read_text().splitlines()
    assert lines[0].startswith("retail_rva\tsize\tname") and "?f@@YAXXZ" in lines[1] and "Code/rival.cpp" in lines[1]


def test_kept_copies_feed_no_count_and_no_defect(tmp_path, monkeypatch):
    # Report only: whatever the check finds, the rest of the report is the same, key for key.
    ours, mapfile, retail, manifest, out = kept_copy_cli(tmp_path, monkeypatch, wrong=True)
    argv = ["--image", str(ours), "--map", str(mapfile), "--retail", str(retail), "--objects", str(manifest)]
    real = iso.kept_copies
    empty = dict(counts={}, names=[], several_rows=[], matches_only_some_rows=[], scope="stub")
    results, codes = [], []
    for label, stub in (("found", real), ("none", lambda *a: empty)):
        monkeypatch.setattr(iso, "kept_copies", stub)
        folder = tmp_path / label
        codes.append(iso.main(argv + ["--out", str(folder)]))
        report = json.loads((folder / "report.json").read_text())
        results.append(report)
        for name in ("defects.tsv", "ambiguous.tsv", "relocation_leads.tsv", "data_pointer_leads.tsv"):
            assert (folder / name).read_bytes() == (tmp_path / "found" / name).read_bytes()
    assert len(results[0]["kept_copies"]["names"]) == 1 and results[1]["kept_copies"]["names"] == []
    assert codes[0] == codes[1]
    for report in results:
        del report["kept_copies"]
    assert results[0]["counts"] == results[1]["counts"]
    assert results[0]["defects"] == results[1]["defects"]
    assert results[0] == results[1]
    assert (tmp_path / "found" / "kept_copies.tsv").exists()


def test_the_real_object_reader_tells_a_shared_copy_from_a_label(tmp_path):
    # The label is static and rowed, and the bytes differ: only the external symbol may be judged.
    obj = tmp_path / "rival.obj"
    iso.link_cycle.write_coff(obj, [(".text", COMDAT_CODE, b"\xc3\xc3", 0)],
                              [("?f@@YAXXZ", 1, 0, iso.link_cycle.EXTERNAL), ("$L1", 1, 1, iso.link_cycle.STATIC)])
    manifest = tmp_path / "objects.json"
    manifest.write_text(json.dumps([dict(path=obj.name, sha256=iso.digest(obj), source="Code/rival.cpp")]))
    publics = [dict(name=n, rva=r, object="rival.obj", source="", extent=None) for n, r in (("?f@@YAXXZ", 0x5000), ("$L1", 0x5001))]
    iso.attach_objects(publics, manifest)
    assert [p["external"] for p in publics] == [True, False]
    ledger = {"?f@@YAXXZ": [dict(ROW, target_size="2")], "$L1": [dict(ROW, target_size="1")]}
    kept = iso.kept_copies(KeptCopyMemory(0x10000000, {0x5000: b"\xc2\xc3", 0x5001: b"\xc2"}), KeptCopyMemory(0x400000, {0x1000: b"\xc3\xc3"}), publics, ledger)
    assert [entry["name"] for entry in kept["names"]] == ["?f@@YAXXZ"] and kept["counts"]["rowed_comdats_checked"] == 1


def test_a_name_matching_only_some_rows_is_surfaced_not_only_suppressed():
    kept = judged_two(b"\x55" * 9, BODY)
    assert kept["names"] == [] and kept["counts"]["kept_copy_matches_only_some_rows"] == 1
    assert [entry["name"] for entry in kept["matches_only_some_rows"]] == ["?f@@YAXXZ"]
    assert "matches_only_some_rows" in kept and judged_two(BODY, BODY)["matches_only_some_rows"] == []


def test_the_some_rows_names_reach_their_own_file(tmp_path, monkeypatch):
    kept = judged_two(b"\x55" * 9, BODY)
    iso.write_kept_copies(tmp_path, kept)
    lines = (tmp_path / "kept_copies_some_rows.tsv").read_text().splitlines()
    assert lines[0].split("\t")[:2] == ["name", "retail_rvas"] and "?f@@YAXXZ" in lines[1] and "0x00002000" in lines[1]


def git_tree(tmp_path, text):
    import subprocess
    root = tmp_path / "tree"
    (root / "reverse").mkdir(parents=True)
    (root / "reverse/functions.csv").write_text(text)
    for command in (["init", "-q"], ["add", "."], ["-c", "user.name=t", "-c", "user.email=t@t", "commit", "-q", "-m", "x"]):
        subprocess.run(["git", *command], cwd=root, check=True)
    return root, subprocess.run(["git", "rev-parse", "HEAD"], cwd=root, check=True, capture_output=True, text=True).stdout.strip()


def test_the_ledger_is_identified_and_matches_the_images_commit(tmp_path):
    root, commit = git_tree(tmp_path, "name\n")
    identity = iso.ledger_identity(root, commit)
    assert identity["sha256"] == iso.digest(root / "reverse/functions.csv")
    assert (identity["revision"], identity["image_commit"], identity["same_as_image"], identity["warning"]) == (commit, commit, True, None)


def test_a_ledger_other_than_the_images_is_warned_of(tmp_path):
    # The trap behind the false Locomotor::xfer and _Rb_tree_base entries: a newer ledger read against an older image.
    root, commit = git_tree(tmp_path, "name\n")
    (root / "reverse/functions.csv").write_text("name\nmoved\n")
    identity = iso.ledger_identity(root, commit)
    assert identity["same_as_image"] is False and commit in identity["warning"] and "functions.csv" in identity["warning"]


def test_a_later_commit_with_the_same_ledger_is_no_warning(tmp_path):
    import subprocess
    root, commit = git_tree(tmp_path, "name\n")
    (root / "other").write_text("x")
    subprocess.run(["git", "add", "."], cwd=root, check=True)
    subprocess.run(["git", "-c", "user.name=t", "-c", "user.email=t@t", "commit", "-q", "-m", "y"], cwd=root, check=True)
    identity = iso.ledger_identity(root, commit)
    assert identity["same_as_image"] is True and identity["warning"] is None and identity["revision"] != commit


def test_an_image_commit_this_checkout_lacks_cannot_be_called_the_same(tmp_path):
    root, commit = git_tree(tmp_path, "name\n")
    for missing in ("f" * 40, None):
        identity = iso.ledger_identity(root, missing)
        assert identity["same_as_image"] is None and "could not" in identity["warning"]


def test_no_repository_is_said_not_assumed(tmp_path):
    (tmp_path / "reverse").mkdir()
    (tmp_path / "reverse/functions.csv").write_text("name\n")
    identity = iso.ledger_identity(tmp_path, "a" * 40)
    assert identity["revision"] is None and identity["same_as_image"] is None and identity["warning"]


def test_the_ledger_warning_is_recorded_printed_and_changes_nothing_else(tmp_path, monkeypatch, capsys):
    ours, mapfile, retail, manifest, out = kept_copy_cli(tmp_path, monkeypatch, wrong=True)
    argv = ["--image", str(ours), "--map", str(mapfile), "--retail", str(retail), "--objects", str(manifest)]
    calm = dict(sha256="a", revision="b", image_commit="b", same_as_image=True, warning=None)
    loud = dict(calm, same_as_image=False, warning="the ledger is not the image's")
    results = []
    for label, identity in (("calm", calm), ("loud", loud)):
        monkeypatch.setattr(iso, "ledger_identity", lambda *a: identity)
        code = iso.main(argv + ["--out", str(tmp_path / label)])
        results.append((code, json.loads((tmp_path / label / "report.json").read_text()), capsys.readouterr()))
    assert results[0][0] == results[1][0]
    assert "the ledger is not the image's" in results[1][2].err and "the ledger" not in results[0][2].err
    assert results[1][1]["kept_copies"]["ledger"] == loud
    for _code, report, _out in results:
        del report["kept_copies"]
    assert results[0][1] == results[1][1]
    monkeypatch.setattr(iso, "ledger_identity", lambda *a: loud)
    assert iso.main(argv + ["--out", str(tmp_path / "only"), "--kept-copies-only"]) == 1
    only = json.loads((tmp_path / "only" / "report.json").read_text())
    assert only["kept_copies"]["ledger"] == loud and "the ledger is not the image's" in capsys.readouterr().err


def test_main_hands_the_check_every_row_of_a_name(tmp_path, monkeypatch):
    # The rows come from the ledger's stream in main(): the copy matches only the second, later in the file.
    ours, mapfile, retail, manifest, out = kept_copy_cli(tmp_path, monkeypatch, wrong=True)
    functions = iso.build.ROOT / "reverse/functions.csv"
    functions.write_text(functions.read_text() + "?f@@YAXXZ,0x1030,1,,Code/second.cpp\n")
    raw = bytearray(retail.read_bytes())
    raw[0x230] = 0xc2                     # the image's copy, wrong for the first row, is retail's at the second
    retail.write_bytes(raw)
    assert iso.main(["--image", str(ours), "--map", str(mapfile), "--retail", str(retail), "--objects", str(manifest),
                     "--out", str(out), "--kept-copies-only"]) == 1
    kept = json.loads((out / "report.json").read_text())["kept_copies"]
    assert kept["names"] == [] and kept["counts"]["names_with_several_rows"] == 1
    assert kept["several_rows"][0]["retail_rvas"] == ["0x00001020", "0x00001030"]


def test_kept_copies_only_excludes_the_other_modes(tmp_path, monkeypatch):
    with pytest.raises(SystemExit):
        iso.main(["--image", "a", "--map", "b", "--kept-copies-only", "--vptr-stores"])


def test_map_and_pointers_at_the_new_base(tmp_path):
    base = 0x2000000
    path = tmp_path / "exit.map"
    path.write_text(f" 0001:00000000 _foo {base + 0x1000:08x} f provider.obj\n")
    assert [(e["name"], e["rva"]) for e in iso.read_map(path, base)] == [("_foo", 0x1000)]
    c = iso.Checker(Memory(base), Memory(0x400000), [public("array", 0x2000, 16), public("other", 0x3000)],
                    {"array": {0x2100}, "other": {0x3100}})
    assert c.pointer(base + 0x2008, 0x400000 + 0x2108) == "equal"
    assert c.pointer(base + 0x3000, 0x400000 + 0x2108) == "wrong"
    assert c.pointer(0x10000000 + 0x2008, 0x400000 + 0x2108) == "unchecked"    # an address at the old base is not ours


@pytest.mark.parametrize("target,verdict", [(0x3000, "equal"), (0x3100, "wrong"), (0x4000, "unchecked"), (None, "wrong")])
def test_coff_global_pointer_words_without_pe_fixups(target, verdict):
    c = checker([public("global", 0x2000), public("right", 0x3000), public("wrong", 0x3100)],
                {"global": {0x2200}, "right": {0x3200}, "wrong": {0x3300}})
    c.publics[0]["coff"] = dict(offset=0, section=dict(relocations=[(0, iso.link_cycle.DIR32)]))
    c.retail.put(0x2200, struct.pack("<I", c.retail.base + 0x3200))
    c.ours.put(0x2000, struct.pack("<I", c.ours.base + target if target is not None else 0))
    c.ledger([row("global", 0x2200)], {})
    assert c.pointer_words[0]["verdict"] == verdict
    assert c.counts["coff_pointer_words_checked"] == 1
    assert c.counts["pointers_unchecked"] == (verdict == "unchecked")
    assert c.counts["global_pointer"] == (verdict == "wrong")
    assert c.counts["global_contents"] == 0


def test_untyped_address_word_keeps_scalar_check_and_explains_unknown():
    c = checker([public("g", 0x2000), public("target", 0x3000)],
                {"g": {0x2200}, "target": {0x3200}})
    c.retail.put(0x2200, struct.pack("<I", c.retail.base + 0x3200))
    c.ours.put(0x2000, struct.pack("<I", c.ours.base + 0x3000))
    c.ledger([row("g", 0x2200)], {})
    assert c.counts["pointers_unchecked"] == 1
    assert c.counts["global_contents"] == 1
    assert c.pointer_words[0]["candidate_correspondence"] == "equal"
    assert c.pointer_words[0]["verdict"] == "unchecked"


def test_data_coff_pointer_fields_survive_manifest_attachment(tmp_path):
    obj = tmp_path / "g.obj"
    iso.link_cycle.write_coff(obj, [(".data", 0xC0000040, bytes(4), 0)],
        [("g", 1, 0, iso.link_cycle.EXTERNAL), ("target", 0, 0, iso.link_cycle.EXTERNAL)],
        {1: [(0, "target", iso.link_cycle.DIR32)]})
    manifest = tmp_path / "objects.json"
    manifest.write_text(json.dumps([dict(path=obj.name, sha256=iso.digest(obj), source="Code/g.cpp")]))
    p = dict(public("g", 0x2000), object="g.obj")
    iso.attach_objects([p], manifest)
    assert "coff" not in p  # code audits must never decode data as instructions
    assert p["data_coff"]["section"]["relocations"] == ((0, iso.link_cycle.DIR32),)


@pytest.mark.parametrize("extent", [None, 0, 3])
def test_vtable_equal_target_needs_full_table_extent(extent):
    c = checker([public("vt", 0x2000, extent), public("f", 0x300)],
                {"vt": {0x2100}, "f": {0x100}})
    c.ours.pointer(0x2000, 0x300)
    c.retail.pointer(0x2100, 0x100)
    c.ours.put(0x300, b"\xc3")
    c.retail.put(0x100, b"\xc3")
    c.ledger([row("vt", 0x2100, 4, "vtable")], {0x100: 1})
    assert c.counts["vtable_slots_equal"] == 0
    assert c.counts["vtable_slots_unanalyzed"] == 1
    assert c.vtable_slots[0]["verdict"] == "unanalyzed"


def test_vtable_body_cannot_borrow_neighbour_bytes():
    c = checker([public("f", 0x300, 1)], {"f": {0x100}})
    c.ours.put(0x300, b"\xc2\x04\x00")
    c.retail.put(0x100, b"\xc2\x04\x00")
    assert c.slot(c.ours.base + 0x300, c.retail.base + 0x100, {0x100: 3})[0] is None


def test_null_and_data_vtable_targets_are_defects():
    c = checker([public("f", 0x300)], {"f": {0x100}})
    assert c.slot(0, c.retail.base + 0x100, {0x100: 1})[0] is False
    assert c.slot(c.ours.base + 0x2000, c.retail.base + 0x100, {0x100: 1})[0] is False


@pytest.mark.parametrize("wide", [False, True])
def test_unmapped_literal_pointer_uses_complete_ledger_typed_string(wide):
    width = 2 if wide else 1
    data = "hello\0".encode("utf-16le" if wide else "ascii")
    name = "??_C@_1literal" if wide else "??_C@_0literal"
    c = checker([public("g", 0x2000), public(name, 0x3000, len(data))], {"g": {0x2200}})
    c.ours.pointer(0x2000, 0x3000)
    c.retail.put(0x2200, struct.pack("<I", c.retail.base + 0x3200))
    c.ours.put(0x3000, data)
    c.retail.put(0x3200, data)
    c.ledger([row("g", 0x2200), row("retail_literal", 0x3200, len(data), "wstring" if wide else "string")], {})
    assert c.counts["pointers_unchecked"] == 0
    assert c.counts["pointers_ledger_literal_aliases"] == 1
    assert c.counts["pointers_equal"] == 1
    for actual, expected in ((data[:-width], data), (data, data[:-width]), (data, b"x" * len(data))):
        c.ledger_literal_cache.clear()
        c.ours.put(0x3000, actual + b"x" * (len(data) - len(actual)))
        c.retail.put(0x3200, expected + b"x" * (len(data) - len(expected)))
        assert not c.ledger_literal(0x3000, 0x3200)
    c.ours.put(0x3000, data); c.retail.put(0x3200, data)
    c.ledger_literal_cache.clear(); c.publics[1]["extent"] = len(data) - width
    assert not c.ledger_literal(0x3000, 0x3200)
    c.ledger_literal_cache.clear(); c.publics[1]["extent"] = None
    assert not c.ledger_literal(0x3000, 0x3200)
    c.ledger_literal_cache.clear(); c.publics[1]["extent"] = len(data)
    c.retail_literals.clear()
    assert not c.ledger_literal(0x3000, 0x3200)


@pytest.mark.parametrize("extent", [None, 1])
def test_review_wrong_body_survives_missing_or_short_extent(extent):
    c = checker([public("f", 0x300, extent)], {"f": {0x100}})
    c.ours.put(0x300, b"\xc3\x90\x90")
    c.retail.put(0x100, b"\xc2\x04\x00")
    result = c.slot(c.ours.base + 0x300, c.retail.base + 0x100, {0x100: 3})
    assert (result[0] if isinstance(result, tuple) else result) is False


def test_review_writable_retail_string_is_not_a_poolable_literal():
    c = checker([public("g", 0x2000), public("??_C@_0English", 0x3000, 8)], {"g": {0x2200}})
    c.ours.put(0x3000, b"English\0")
    c.retail.put(0x3200, b"English\0")
    # An actual PE32 .data section, with a writable initialized buffer.
    from types import SimpleNamespace
    c.retail.sections = [SimpleNamespace(Name=b".data", VirtualAddress=0x3000, Misc_VirtualSize=0x1000,
                                         SizeOfRawData=0x1000, Characteristics=0xC0000040)]
    c.retail.readonly = lambda rva, size=1: iso.Image.readonly(c.retail, rva, size)
    c.retail_literals = {0x3200: (8, 1)}
    assert not c.ledger_literal(0x3000, 0x3200)


def test_review_slot_reports_each_unanalyzed_cause_in_the_report():
    c = checker([public("vt", 0x2000, 24), public("f", 0x300, None),
                 public("g", 0x400, 1), public("h", 0x500, 5)],
                {"vt": {0x2100}, "f": {0x100}, "g": {0x200}, "h": {0x250}})
    c.ours.put(0x300, b"\xc3"); c.retail.put(0x100, b"\xc3")
    c.ours.put(0x400, b"\x90\xc3"); c.retail.put(0x200, b"\x90\xc3")
    c.ours.put(0x500, b"\xe8" + struct.pack("<i", 0x900 - 0x505) + b"\x90")
    c.retail.put(0x250, b"\xe8" + struct.pack("<i", 0x800 - 0x255) + b"\x90")
    c.ours.put(0x600, b"\xe9" + struct.pack("<i", 0x700 - 0x605))
    for k, (a, b) in enumerate(((0x300, 0x100), (0x400, 0x200), (0x500, 0x250),
                               (0x600, 0x100), (0x800, 0x100), (0x3000, 0x100))):
        c.ours.pointer(0x2000 + 4*k, a); c.retail.pointer(0x2100 + 4*k, b)
    c.ledger([row("vt", 0x2100, 24, "vtable")], {0x100: 1, 0x200: 2, 0x250: 6})
    assert [s["reason"] for s in c.vtable_slots] == [
        "extent-missing", "extent-short", "code-equal-unresolved-operand", "forwarder-unmapped",
        "unmapped", "non-text-target"]


def test_review_data_location_ambiguity_does_not_increment_code_counter(tmp_path):
    obj = tmp_path / "g.obj"
    iso.link_cycle.write_coff(obj,
        [(".data$a", 0xC0000040, bytes(4), 0), (".data$b", 0xC0000040, bytes(4), 0)],
        [("g", 1, 0, iso.link_cycle.STATIC), ("g", 2, 0, iso.link_cycle.STATIC)])
    manifest = tmp_path / "objects.json"
    manifest.write_text(json.dumps([dict(path=obj.name, sha256=iso.digest(obj), source="Code/g.cpp")]))
    counts = iso.attach_objects([dict(public("g", 0x2000), object="g.obj")], manifest)
    assert counts["data_symbol_locations_ambiguous"] == 1
    assert counts["code_symbol_locations_ambiguous"] == 0


@pytest.mark.parametrize("unresolved", ["branch", "imm", "mem"])
@pytest.mark.parametrize("difference", ["byte", "branch", "pointer"])
def test_final_review_unresolved_operand_cannot_hide_later_difference(unresolved, difference):
    c = checker([public("f", 0x300, 16), public("right", 0x600), public("wrong", 0x700)],
                {"f": {0x100}, "right": {0x200}, "wrong": {0x300}})
    if unresolved == "branch":
        a = b"\xe8" + struct.pack("<i", 0x900 - 0x305)
        b = b"\xe8" + struct.pack("<i", 0x800 - 0x105)
    else:
        opcode = b"\xb8" if unresolved == "imm" else b"\xa1"
        a = opcode + struct.pack("<I", c.ours.base + 0x4000)
        b = opcode + struct.pack("<I", c.retail.base + 0x4000)
        c.ours.relocations.add(0x301)
    if difference == "byte":
        aa, bb, equal = b"\x90", b"\xc3", b"\xc3"
    elif difference == "branch":
        aa = b"\xe8" + struct.pack("<i", 0x700 - 0x30a)
        bb = b"\xe8" + struct.pack("<i", 0x200 - 0x10a)
        equal = b"\xe8" + struct.pack("<i", 0x600 - 0x30a)
    else:
        aa = b"\xb9" + struct.pack("<I", c.ours.base + 0x700)
        bb = b"\xb9" + struct.pack("<I", c.retail.base + 0x200)
        equal = b"\xb9" + struct.pack("<I", c.ours.base + 0x600)
        c.ours.relocations.add(0x306)
    c.ours.put(0x300, a + aa); c.retail.put(0x100, b + bb)
    assert c.code_comparison(0x300, 0x100, len(a + aa)) == (False, "body-mismatch")
    c.ours.put(0x305, equal)
    assert c.code_comparison(0x300, 0x100, len(a + aa)) == (None, "code-equal-unresolved-operand")


@pytest.mark.parametrize("name,allowed", [(b".rdata", True), (b".data", False)])
def test_final_review_retail_section_name_controls_literal_credit(name, allowed):
    from types import SimpleNamespace
    c = checker([public("??_C@_0English", 0x3000, 8)], {})
    c.ours.put(0x3000, b"English\0"); c.retail.put(0x3200, b"English\0")
    c.retail.sections = [SimpleNamespace(Name=name, VirtualAddress=0x3000, Misc_VirtualSize=0x1000,
                                         SizeOfRawData=0x1000, Characteristics=0xC0000040)]
    c.retail.readonly = lambda rva, size=1: iso.Image.readonly(c.retail, rva, size)
    c.retail_literals = {0x3200: (8, 1)}
    assert c.ledger_literal(0x3000, 0x3200) is allowed


def test_final_review_one_past_array_is_reported_even_at_another_global():
    c = checker([public("g", 0x2800), public("array", 0x2000, 16), public("following", 0x2010)],
                {"g": {0x2900}, "array": {0x2100}, "following": {0x3100}})
    c.ours.pointer(0x2800, 0x2010); c.retail.pointer(0x2900, 0x2110)
    c.ledger([row("g", 0x2900)], {})
    assert c.counts["wrong_pointers"] == 0
    assert c.counts["pointers_end_equal"] == 0
    assert c.pointer_words[0]["verdict"] == "unchecked"
    assert c.pointer_words[0]["reason"] == "end-pointer-conflict"
    assert c.pointer(c.ours.base + 0x2011, c.retail.base + 0x2111) == "wrong"


def test_final_review_different_decoded_lengths_are_a_body_mismatch():
    c = checker([], {})
    c.ours.put(0x300, b"\x90\x0f"); c.retail.put(0x100, b"\x90\xc3")
    assert c.code_comparison(0x300, 0x100, 2) == (False, "body-mismatch")


@pytest.mark.parametrize("opcode", [b"\x3d", b"\xa1"])
def test_final_review_named_storage_operand_cannot_borrow_array_end_identity(opcode):
    c = checker([public("array", 0x2000, 16), public("following", 0x2010), public("wanted", 0x4000)],
                {"array": {0x2100}, "following": {0x3100}, "wanted": {0x2110}})
    c.ours.put(0x300, opcode + struct.pack("<I", c.ours.base + 0x2010))
    c.retail.put(0x100, opcode + struct.pack("<I", c.retail.base + 0x2110))
    c.ours.relocations.add(0x301)
    assert c.code_comparison(0x300, 0x100, 5) == (False, "body-mismatch")



def test_round4_code_our_mapped_start_cannot_borrow_an_unnamed_end():
    c = checker([public("array", 0x2000, 16), public("following", 0x2010)],
                {"array": {0x2100}, "following": {0x3100}})
    c.ours.put(0x300, b"\xa1" + struct.pack("<I", c.ours.base + 0x2010))
    c.retail.put(0x100, b"\xa1" + struct.pack("<I", c.retail.base + 0x2110))
    c.ours.relocations.add(0x301)
    assert c.code_comparison(0x300, 0x100, 5) == (None, "code-equal-unresolved-operand")
    assert c.counts["pointers_end_equal"] == 0


@pytest.mark.parametrize("proof", [False, True])
def test_round4_data_retail_mapped_start_cannot_borrow_an_end(proof):
    c = checker([public("g", 0x2800), public("array", 0x2000, 16), public("wanted", 0x4000)],
                {"g": {0x2900}, "array": {0x2100}, "wanted": {0x2110}})
    c.ours.pointer(0x2800, 0x2010); c.retail.pointer(0x2900, 0x2110)
    if proof:
        c.publics[0]["data_coff"] = dict(offset=0, section=dict(body=struct.pack("<I", 16),
            relocations=[(0, iso.link_cycle.DIR32)], relocation_targets={0:dict(name="array")}))
    c.ledger([row("g", 0x2900)], {})
    assert c.pointer_words[0]["verdict"] == "unchecked"
    assert c.pointer_words[0]["reason"] == "end-pointer-conflict"
    assert c.counts["wrong_pointers"] == c.counts["pointers_end_equal"] == 0


@pytest.mark.parametrize("proof", [False, True])
def test_round4_data_end_requires_dir32_symbol_and_exact_addend(proof):
    c = checker([public("g", 0x2800), public("array", 0x2000, 16)],
                {"g": {0x2900}, "array": {0x2100}})
    c.ours.pointer(0x2800, 0x2010); c.retail.pointer(0x2900, 0x2110)
    if proof:
        c.publics[0]["data_coff"] = dict(offset=0, section=dict(body=struct.pack("<I", 16),
            relocations=[(0, iso.link_cycle.DIR32)], relocation_targets={0:dict(name="array")}))
    c.ledger([row("g", 0x2900)], {})
    assert c.pointer_words[0]["verdict"] == ("equal" if proof else "unchecked")
    assert c.pointer_words[0]["reason"] == ("proven-end-pointer" if proof else "end-pointer-unproven")
    assert c.counts["pointers_end_equal"] == int(proof)


def test_round4_already_mapped_equal_is_not_end_credit():
    c = checker([public("g", 0x2800), public("array", 0x2000, 16), public("following", 0x2010)],
                {"g": {0x2900}, "array": {0x2100}, "following": {0x2110}})
    c.ours.pointer(0x2800, 0x2010); c.retail.pointer(0x2900, 0x2110)
    c.ledger([row("g", 0x2900)], {})
    assert c.pointer_words[0]["verdict"] == "equal"
    assert c.pointer_words[0]["reason"] == "mapped target identity"
    assert c.counts["pointers_end_equal"] == 0


def test_round4_wrong_interior_mapping_is_not_overridden_by_an_end():
    c = checker([public("array", 0x2000, 16), public("overlap", 0x2008, 16)],
                {"array": {0x2100}, "overlap": {0x3100}})
    assert c.pointer(c.ours.base + 0x2010, c.retail.base + 0x2110) == "wrong"
    assert c.counts["pointers_end_equal"] == 0


@pytest.mark.parametrize("repeated", [False, True])
def test_round5_unmapped_or_ambiguous_public_blocks_unproven_code_end(repeated):
    ps = [public("array", 0x2000, 16), public("following", 0x2010)]
    if repeated:
        ps.append(public("following", 0x3000))
    c = checker(ps, {"array": {0x2100}})
    assert c.pointer_result(c.ours.base + 0x2010, c.retail.base + 0x2110) == (
        "unchecked", "end-pointer-conflict")
    c.ours.put(0x300, b"\xa1" + struct.pack("<I", c.ours.base + 0x2010))
    c.retail.put(0x100, b"\xa1" + struct.pack("<I", c.retail.base + 0x2110))
    c.ours.relocations.add(0x301)
    assert c.code_comparison(0x300, 0x100, 5) == (None, "code-equal-unresolved-operand")
    assert c.counts["pointers_end_equal"] == 0


@pytest.mark.parametrize("opcode", [b"\xa1", b"\xb8"])
@pytest.mark.parametrize("proof", ["missing", "valid", "wrong-symbol", "wrong-addend", "wrong-kind"])
def test_round5_code_end_requires_its_text_dir32_symbol_and_addend(proof, opcode):
    c = checker([public("f", 0x300, 5), public("array", 0x2000, 16), public("other", 0x3000, 16)],
                {"f": {0x100}, "array": {0x2100}, "other": {0x3100}})
    c.ours.put(0x300, opcode + struct.pack("<I", c.ours.base + 0x2010))
    c.retail.put(0x100, opcode + struct.pack("<I", c.retail.base + 0x2110))
    c.ours.relocations.add(0x301)
    if proof != "missing":
        kind = iso.link_cycle.REL32 if proof == "wrong-kind" else iso.link_cycle.DIR32
        addend = 15 if proof == "wrong-addend" else 16
        symbol = "other" if proof == "wrong-symbol" else "array"
        c.publics[0]["coff"] = dict(offset=0, section=dict(body=opcode + struct.pack("<I", addend),
            relocations=[(1, kind)], relocation_targets={1:dict(name=symbol)}))
    expected = (True, "row-identity-and-abi-equal") if proof == "valid" else (None, "code-equal-unresolved-operand")
    assert c.code_comparison(0x300, 0x100, 5) == expected
    assert c.counts["pointers_end_equal"] == int(proof == "valid")


# ---- measurement gaps (waste lane, toollane2-image-iso.md) ---------------------------------------------------

def proven(tmp_path, sizes):
    """reverse/data_rows.csv beside the fixture's functions.csv: the sizes the build proves."""
    lines = ["name,address,address_kind,size,section,source,status,evidence,model"]
    lines += [f"{n},0x00402000,rva,{size},.data,Code/x.cpp,matched,probe,m" for n, size in sizes.items()]
    (tmp_path / "data_rows.csv").write_text("\n".join(lines) + "\n")


@pytest.mark.parametrize("name,size,defects,excluded", [
    ("?defaultModeProbs@@3PAEA", 80, 0, 1),           # an unsigned char array (proven 80 bytes): no pointer there
    ("?table@@3QBGB", 8, 0, 1),                       # a const unsigned short array
    ("?p@@3PAEA", 4, 1, 0),                           # sizeof 4: may be a pointer variable
    ("?q@@3PAEA", None, 1, 0),                        # no proven sizeof: nothing is said
    ("?ptrs@@3PAPAXA", 16, 1, 0),                     # an array of pointers
])
def test_data_word_in_a_nonpointer_container_is_excluded(tmp_path, name, size, defects, excluded):
    c, ledger, data = absolute_case(tmp_path, b"\xc3", data_rows=[row("global", 0x3100, 4)])
    proven(tmp_path, {name: size} if size else {})
    with_data_section(c)
    c.publics.append(public(name, 0x2000, 16))       # the extent to the next symbol says nothing on its own
    c.ours.put(0x2000, struct.pack("<I", 0x403100))
    result = iso.unrelocated_retail_addresses(c, ledger, data)
    assert len(result["defects"]) == defects
    assert result["counts"].get("data_words_in_nonpointer_containers_excluded", 0) == excluded


def test_a_container_word_past_its_proven_payload_is_still_a_defect(tmp_path):
    # image_iso review r1: an array proven 8 bytes, the word at +8 lies past it; a literal "abc" (length 4), the
    # word at +8 lies past its terminator
    for name, size in (("?a@@3PAEA", 8), ("??_C@_03ABCDEFGH@abc?$AA@", None)):
        c, ledger, data = absolute_case(tmp_path, b"\xc3", data_rows=[row("global", 0x3100, 4)])
        proven(tmp_path, {name: size} if size else {})
        with_data_section(c)
        c.publics.append(public(name, 0x2000, 16))
        c.ours.put(0x2000, b"abc\0")
        c.ours.put(0x2008, struct.pack("<I", 0x403100))
        result = iso.unrelocated_retail_addresses(c, ledger, data)
        assert len(result["defects"]) == 1, name


def test_literal_length_is_the_one_its_name_encodes():
    assert iso.literal_length("??_C@_03DEOAGKCL@HZz?$AA@") == 4
    assert iso.literal_length("??_C@_0BA@ABCDEFGH@x@") == 16
    assert iso.literal_length("??_C@_1M@ABCDEFGH@?$AAL?$AAM?$AA?$AA@") == 12
    assert iso.literal_length("__real@3f800000") is None


def test_data_word_in_a_struct_array_is_marked_unproven_not_a_defect(tmp_path):
    # the LZH symbol tables: an array of struct Symbol, whose fields no registered layout proves
    name = "?symbolTable0@LZHLEncoderStat@@2PAUSymbol@1@A"
    c, ledger, data = absolute_case(tmp_path, b"\xc3", data_rows=[row("global", 0x3100, 4)])
    proven(tmp_path, {name: 1096})
    with_data_section(c)
    c.publics.append(public(name, 0x2000, 16))
    c.ours.put(0x2000, struct.pack("<I", 0x403100))
    result = iso.unrelocated_retail_addresses(c, ledger, data)
    assert not result["defects"]
    marked = [d for d in result["ambiguous"] if d.get("ambiguity_reason") == "struct_fields_unproven"]
    assert len(marked) == 1 and marked[0]["container"] == "struct array; non-pointer fields unproven"


def test_data_word_without_a_map_public_is_attributed_to_a_placed_static(tmp_path):
    c, ledger, data = absolute_case(tmp_path, b"\xc3", data_rows=[row("global", 0x3100, 4)])
    proven(tmp_path, {"?numbers@@3PAGA": 16})
    with_data_section(c)
    c.statics = {"?numbers@@3PAGA": [dict(public("?numbers@@3PAGA", 0x2000, 16), static=True)]}
    c.ours.put(0x2000, struct.pack("<I", 0x403100))
    result = iso.unrelocated_retail_addresses(c, ledger, data)
    assert not result["defects"]
    assert result["counts"]["data_words_attributed_to_placed_statics"] == 1
    assert result["counts"]["data_words_in_nonpointer_containers_excluded"] == 1


def static_object(tmp_path, relocations=None, symbols=None):
    obj = tmp_path / "unit.obj"
    iso.link_cycle.write_coff(
        obj, [(".text", 0x60000020, b"\xa1\x04\x00\x00\x00\xc3", 0), (".data", 0xC0000040, bytes(16), 0)],
        symbols or [("fn", 1, 0, iso.link_cycle.EXTERNAL), ("sdata", 2, 4, iso.link_cycle.STATIC)],
        relocations if relocations is not None else {1: [(1, "sdata", iso.link_cycle.DIR32)]})
    manifest = tmp_path / "objects.json"
    manifest.write_text(json.dumps([dict(path="unit.obj", sha256=iso.digest(obj), source="Code/unit.cpp",
                                         provider="unit.obj")]))
    return manifest


def test_place_statics_through_a_relocation_from_a_placed_section(tmp_path):
    # fn (MAP-placed at 0x500) loads sdata (.data+4, a file static the MAP does not list) through a DIR32 to sdata
    # whose in-place addend is 4: the image word there, less the addend and sdata's value, is .data's start
    manifest = static_object(tmp_path)
    image = Memory(0x10000000)
    image.put(0x501, struct.pack("<I", 0x10000000 + 0x2404 + 4))
    placed = iso.place_statics([dict(name="fn", rva=0x500, object="unit.obj")], manifest, {"sdata"}, image)
    assert [(p["rva"], p["extent"], p["source"]) for p in placed["sdata"]] == [(0x2404, 12, "Code/unit.cpp")]


def test_place_statics_through_an_anchor_in_its_own_section(tmp_path):
    manifest = static_object(tmp_path, relocations={},
                             symbols=[("fn", 1, 0, iso.link_cycle.EXTERNAL), ("anchor", 2, 0, iso.link_cycle.EXTERNAL),
                                      ("sdata", 2, 8, iso.link_cycle.STATIC)])
    publics = [dict(name="fn", rva=0x500, object="unit.obj"), dict(name="anchor", rva=0x2100, object="unit.obj")]
    placed = iso.place_statics(publics, manifest, {"sdata"}, Memory(0x10000000))
    assert [p["rva"] for p in placed["sdata"]] == [0x2108]


def test_place_statics_refuses_disagreeing_evidence(tmp_path):
    # the anchor puts .data at 0x2100, the relocation at 0x2400: no placement
    manifest = static_object(tmp_path, symbols=[("fn", 1, 0, iso.link_cycle.EXTERNAL),
                                                ("anchor", 2, 0, iso.link_cycle.EXTERNAL),
                                                ("sdata", 2, 4, iso.link_cycle.STATIC)])
    image = Memory(0x10000000)
    image.put(0x501, struct.pack("<I", 0x10000000 + 0x2404 + 4))
    publics = [dict(name="fn", rva=0x500, object="unit.obj"), dict(name="anchor", rva=0x2100, object="unit.obj")]
    assert iso.place_statics(publics, manifest, {"sdata"}, image) == {}


def test_a_static_the_map_does_not_list_is_compared_through_its_placement():
    c = checker([], {"_pingNames": {0x300}})
    c.retail.put(0x300, b"ABCDEFGH")
    c.ours.put(0x2000, b"ABCDEFGH")
    c.ours.put(0x2100, b"ABCDXXXX")
    c.statics = {"_pingNames": [dict(public("_pingNames", 0x2000, 8), source="Code/a.cpp", static=True),
                                dict(public("_pingNames", 0x2100, 8), source="Code/b.cpp", static=True)]}
    c.ledger([dict(row("_pingNames", 0x300, 8), source="Code/a.cpp")], {})
    assert c.counts["static_data_placed"] == 1 and c.counts["globals_compared"] == 1
    assert not [d for d in c.defects if d["family"] in ("no_object_retail_nonzero", "global_contents")]
    c = checker([], {"_pingNames": {0x300}})
    c.retail.put(0x300, b"ABCDEFGH")
    c.ours.put(0x2100, b"ABCDXXXX")
    c.statics = {"_pingNames": [dict(public("_pingNames", 0x2100, 8), source="Code/b.cpp", static=True)]}
    c.ledger([dict(row("_pingNames", 0x300, 8), source="Code/b.cpp")], {})
    assert [d["family"] for d in c.defects] == ["global_contents"]


@pytest.mark.parametrize("second,family", [(b"\x00\x00\x80\x3f", None), (b"\x00\x00\x00\x40", "pooled_constant_contents")])
def test_pooled_constant_copies_are_compared_by_value(second, family):
    name = "__real@3f800000"
    c = checker([public(name, 0x2000, 4), public(name, 0x2004, 4)], {name: {0x300}})
    c.retail.put(0x300, b"\x00\x00\x80\x3f" + b"\xff" * 4)       # the ledger extent runs past the value
    c.ours.put(0x2000, b"\x00\x00\x80\x3f")
    c.ours.put(0x2004, second)
    c.ledger([row(name, 0x300, 8, kind="float")], {})
    assert c.counts["pooled_constant_rows_compared"] == 1
    assert [d["family"] for d in c.defects] == ([family] if family else [])


def test_place_statics_needs_the_objects_own_provider(tmp_path):
    # image_iso review r1: libB's unit.obj places `anchor`; libA's unit.obj (the manifest's) is another object
    obj = tmp_path / "unit.obj"
    iso.link_cycle.write_coff(obj, [(".data", 0xC0000040, bytes(16), 0)],
                              [("anchor", 1, 0, iso.link_cycle.EXTERNAL), ("sdata", 1, 4, iso.link_cycle.STATIC)])
    manifest = tmp_path / "objects.json"
    manifest.write_text(json.dumps([dict(path="unit.obj", sha256=iso.digest(obj), source="Code/a.cpp",
                                         provider="libA:unit.obj")]))
    publics = [dict(name="anchor", rva=0x2000, object="libB:unit.obj")]
    assert iso.place_statics(publics, manifest, {"sdata"}, Memory(0x10000000)) == {}
    publics = [dict(name="anchor", rva=0x2000, object="libA:unit.obj")]
    assert [p["rva"] for p in iso.place_statics(publics, manifest, {"sdata"}, Memory(0x10000000))["sdata"]] == [0x2004]


def test_a_row_whose_source_has_no_placement_takes_no_other_sources_copy():
    # image_iso review r1: the row's a.cpp static is missing; b.cpp's independent static must not stand in for it
    c = checker([], {"sdata": {0x300}})
    c.retail.put(0x300, b"GOOD")
    c.ours.put(0x2000, b"GOOD")
    c.statics = {"sdata": [dict(public("sdata", 0x2000, 4), source="Code/b.cpp", static=True)]}
    c.ledger([dict(row("sdata", 0x300, 4), source="Code/a.cpp")], {})
    assert c.counts["globals_compared"] == 0
    assert [d["family"] for d in c.defects] == ["no_object_retail_nonzero"]


def test_a_pooled_literal_is_compared_over_its_whole_encoded_length():
    # image_iso review r1: "a\0bc\0" -- the first NUL is not the end
    name = "??_C@_04ABCDEFGH@a?$AAbc?$AA@"
    c = checker([public(name, 0x2000, 5), public(name, 0x2010, 5)], {name: {0x300}})
    c.retail.put(0x300, b"a\0bc\0")
    c.ours.put(0x2000, b"a\0bc\0")
    c.ours.put(0x2010, b"a\0XX\0")
    c.ledger([row(name, 0x300, 5, kind="string")], {})
    assert [d["family"] for d in c.defects] == ["pooled_constant_contents"]


def test_a_pooled_copy_whose_extent_cannot_hold_the_value_proves_nothing():
    # image_iso review r1: the first copy's extent is 2; the bytes after it are another symbol's
    name = "__real@3f800000"
    c = checker([public(name, 0x2000, 2), public("other", 0x2002, 2), public(name, 0x2100, 4)], {name: {0x300}})
    c.retail.put(0x300, b"\x00\x00\x80\x3f")
    c.ours.put(0x2000, b"\x00\x00\x80\x3f")
    c.ours.put(0x2100, b"\x00\x00\x80\x3f")
    c.ledger([row(name, 0x300, 4, kind="float")], {})
    assert c.counts["pooled_constant_rows_compared"] == 0
    assert [d["family"] for d in c.defects] == ["mapping_ambiguous"]


@pytest.mark.parametrize("wide,result", [(b"\0\0", True), (b"\0X", False)])
def test_folded_pooled_names_compare_each_copy_over_its_own_length(wide, result):
    # retail folds the narrow "" and the wide L"" at one address; the narrow copy's extent is 1, the wide one's 2
    narrow, broad = "??_C@_00CNPNBAHC@?$AA@", "??_C@_11LOCGONAA@?$AA?$AA@"
    for names in ([narrow, broad], [broad, narrow]):
        c = checker([public(narrow, 0x2000, 1), public("next", 0x2001, 3), public(broad, 0x2010, 2)],
                    {narrow: {0x300}, broad: {0x300}})
        c.retail.put(0x300, b"\0\0\0\0")
        c.ours.put(0x2000, b"\0ZZZ")
        c.ours.put(0x2010, wide)
        assert c.pooled_copies(names, 0x300, 4) is result

