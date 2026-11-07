"""Seeded static-image defects; no compiler, linker or game required."""
import json
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
    assert c.slot(c.ours.base + 0x500, c.retail.base + 0x600, {0x100: 1}) is True
    c.ours.put(0x502, b"\x04")
    assert c.slot(c.ours.base + 0x500, c.retail.base + 0x600, {0x100: 1}) is False


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
    assert c.slot(c.ours.base + 0x300, c.retail.base + 0x100, {0x100: 3}) is True
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
    assert c.slot(c.ours.base + 0x300, c.retail.base + 0x600, {0x100: 1}) is False
    c.ours.put(0x500, b"\x83\xc1\x04\xe9" + struct.pack("<i", 0x300 - 0x508))
    assert c.slot(c.ours.base + 0x500, c.retail.base + 0x100, {0x100: 1}) is False
    c.retail.put(0x600, b"\xe9" + struct.pack("<i", 0x100 - 0x605))
    assert c.slot(c.ours.base + 0x300, c.retail.base + 0x600, {0x100: 1}) is True


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
    assert json.loads((out / "report.json").read_text())["analysis_scope"] == "absolute address code/data audit only"
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
