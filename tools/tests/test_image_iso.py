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
