"""class_layouts: CodeView parsing and the VC7.1 overloaded-virtual slot rule."""
import sys
import struct
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import class_layouts  # noqa: E402


def cv_class(name, size, forward=False, kind=0x1004):
    text = name.encode("ascii")
    blob = struct.pack("<HHIIIH", 0, 0x80 if forward else 0, 0, 0, 0, size)
    blob += bytes([len(text)]) + text
    return struct.pack("<HH", len(blob) + 2, kind) + blob


def test_forward_member_size_comes_from_complete_definition():
    stream = struct.pack("<I", 4) + cv_class("AsciiString", 0, True) + cv_class("AsciiString", 4)
    types = class_layouts.TypeStream(stream)
    assert types.size(0x1000) == 4
    assert types.size(0x1001) == 4


def test_missing_or_conflicting_definition_stays_unknown():
    prefix = struct.pack("<I", 4) + cv_class("Impl", 0, True)
    assert class_layouts.TypeStream(prefix).size(0x1000) == 0
    stream = prefix + cv_class("Impl", 4) + cv_class("Impl", 8)
    types = class_layouts.TypeStream(stream)
    assert types.size(0x1000) == 0
    assert types.size(0x1001) == 4
    assert types.size(0x1002) == 8


def test_class_key_and_full_scope_are_required_for_forward_resolution():
    stream = struct.pack("<I", 4) + cv_class("HUD::Impl", 0, True)
    stream += cv_class("Other::Impl", 8) + cv_class("HUD::Impl", 12, kind=0x1005)
    assert class_layouts.TypeStream(stream).size(0x1000) == 0


def test_parsed_cache_changes_when_the_reader_changes(monkeypatch, tmp_path):
    monkeypatch.setattr(class_layouts, "CACHE", tmp_path)
    monkeypatch.setattr(class_layouts, "PARSER_HASH", "old")
    stale = class_layouts.parsed_path("stream")
    stale.write_text('{"AsciiString": {"size": 0}}')
    monkeypatch.setattr(class_layouts, "PARSER_HASH", "fixed")
    assert class_layouts.parsed_path("stream") != stale
    assert not class_layouts.parsed_path("stream").exists()


def toolchain():
    try:
        class_layouts.build_module().vc71_root()
        return True
    except SystemExit:
        return False


@unittest.skipUnless(toolchain(), "MSVC 7.1 not available")
class SlotOrder(unittest.TestCase):
    def test_probe_agrees_with_vcall_thunks(self):
        rows, ok = class_layouts.run_probe()
        self.assertTrue(ok, rows)
        self.assertEqual(len(rows), 6)

    def test_naive_reading_is_caught(self):
        # Positive control: taking CodeView's shared group offset at face value
        # must disagree with the thunks, or the probe proves nothing.
        class_layouts.REVERSED_GROUPS = False
        try:
            rows, ok = class_layouts.run_probe()
        finally:
            class_layouts.REVERSED_GROUPS = True
        self.assertFalse(ok, rows)


class Bodies(unittest.TestCase):
    def test_private_views_skip_templates_and_comments(self):
        text = ("// class Fake {\nstruct Coord3D { float x, y, z; };\n"
                "template <class T>\nclass StringBase { T *p; };\nclass AsciiString : public StringBase<char> {};\n")
        self.assertEqual(class_layouts.class_bodies(text), ["Coord3D", "AsciiString"])

    def test_mangled_numbers(self):
        self.assertEqual(class_layouts.mangled_number("7AE")[0], 8)
        self.assertEqual(class_layouts.mangled_number("M@AE")[0], 12)
        self.assertEqual(class_layouts.mangled_number("BI@AE")[0], 24)


if __name__ == "__main__":
    unittest.main()
