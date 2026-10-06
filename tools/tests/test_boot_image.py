"""boot_image: retail .reloc parsing and the linked-image equivalence check.

The check tests need a linked image (`python3 tools/boot_image.py link`, about
15 s with the VS2003 toolchain); they skip without one.
"""
import json
import shutil
import struct
import sys
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import boot_image  # noqa: E402

BOOT = ROOT / "build" / "boot"


def block(page, offsets):
    entries = [0x3000 | o for o in offsets]
    if len(entries) % 2:
        entries.append(0)
    return struct.pack("<II", page, 8 + 2 * len(entries)) + struct.pack(f"<{len(entries)}H", *entries)


class ParseBlocks(unittest.TestCase):
    def test_stops_at_overwritten_block_and_resumes(self):
        good = block(0x1000, [0x10, 0x20]) + block(0x2000, [0x30])
        junk = b"\xe0\x2d\xa7\x00" * 6                    # import descriptors written over the table
        tail = block(0x9000, [0x40])
        sites, pages, stop = boot_image.parse_blocks(good + junk + tail)
        self.assertEqual(sites, [0x1010, 0x1020, 0x2030])
        self.assertEqual(stop, len(good))
        more, more_pages, _ = boot_image.parse_blocks(good + junk + tail, len(good + junk))
        self.assertEqual((more, more_pages), ([0x9040], [0x9000]))

    def test_rejects_pages_out_of_order(self):
        sites, _, _ = boot_image.parse_blocks(block(0x2000, [1]) + block(0x1000, [2]))
        self.assertEqual(sites, [0x2001])


@unittest.skipUnless((BOOT / "boot.exe").exists() and (BOOT / "boot.json").exists(), "no linked boot image")
class CheckImage(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.r = boot_image.Retail()
        sites, _ = boot_image.all_sites(cls.r)
        cls.pieces, _ = boot_image.plan(cls.r, sites)
        cls.base = int(json.loads((BOOT / "boot.json").read_text())["base"], 16)
        cls.publics = boot_image.read_publics(BOOT / "boot.map", cls.base)
        cls.tmp = Path(tempfile.mkdtemp())

    @classmethod
    def tearDownClass(cls):
        shutil.rmtree(cls.tmp, ignore_errors=True)

    def mutated(self, rva_in_piece, piece, value):
        """A copy of boot.exe with the dword at retail RVA `rva_in_piece` set to value."""
        import pefile
        exe = self.tmp / f"m_{rva_in_piece:x}_{value:x}.exe"     # pefile keeps earlier copies mapped
        shutil.copyfile(BOOT / "boot.exe", exe)
        pe = pefile.PE(str(exe))
        new_rva = self.publics[f"_bootp_{piece.start:08X}"] + rva_in_piece - piece.start
        off = pe.get_offset_from_rva(new_rva)
        pe.close()
        data = bytearray(exe.read_bytes())
        data[off:off + 4] = struct.pack("<I", value)
        exe.write_bytes(bytes(data))
        return exe

    def text_piece(self):
        return next(p for p in self.pieces if p.name == ".text")

    def test_clean_image_is_equivalent(self):
        counts, bad = boot_image.check_image(self.r, self.pieces, BOOT / "boot.exe", self.base, self.publics)
        self.assertEqual((counts.get("reloc-bad", 0), counts["bytes-differ"], bad), (0, 0, []))

    def test_wrong_pointer_is_caught(self):
        p = self.text_piece()
        site, _, tgt = next(x for x in p.relocs if x[2][0] == "piece")
        counts, _ = boot_image.check_image(self.r, self.pieces, self.mutated(site, p, self.base + 0x1234),
                                           self.base, self.publics)
        self.assertEqual(counts.get("reloc-bad"), 1)

    def test_unrelocated_retail_address_is_caught(self):
        p = self.text_piece()
        site, _, tgt = next(x for x in p.relocs if x[2][0] == "piece")
        retail_value = self.r.u32(site)                    # the 0x400000-based address, not moved
        counts, _ = boot_image.check_image(self.r, self.pieces, self.mutated(site, p, retail_value),
                                           self.base, self.publics)
        self.assertEqual(counts.get("reloc-bad"), 1)

    def test_changed_byte_is_caught(self):
        p = self.text_piece()
        sites = {s for s, _, _ in p.relocs}
        a = next(x for x in range(p.start + 0x100, p.start + 0x1000, 4)
                 if not any(x - 3 <= s <= x + 3 for s in sites))
        original = self.r.u32(a)
        counts, _ = boot_image.check_image(self.r, self.pieces, self.mutated(a, p, original ^ 0xFF),
                                           self.base, self.publics)
        self.assertEqual(counts["bytes-differ"], 1)


if __name__ == "__main__":
    unittest.main()
