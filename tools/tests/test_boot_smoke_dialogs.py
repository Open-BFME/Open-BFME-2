"""boot_smoke: the game's own crash box read and classified, quiet exceptions decoded.

No game runs; window lists, memory and the debugger's run() are fixtures."""
import struct
import sys
import unittest
from pathlib import Path
from types import SimpleNamespace
from unittest import mock

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import boot_smoke as bs  # noqa: E402
import real_image  # noqa: E402

STACKWALK = ("Release Crash at Thu Nov 07 02:41:55 2026\n; Reason Error parsing INI file 'Data\\INI\\Object.ini'\n"
             "Stack Dump:\n10294F3A GameEngine::init\n0x1065C82E\n00000004\n1029abcd 1029ABCD")
GAME_CRASH = {"title": "Game crash", "class": "#32770", "rect": [855, 584, 1192, 952], "children": [
    {"class": "Static", "id": 20, "text": ""},                   # the icon
    {"class": "Static", "id": 0xFFFF, "text": STACKWALK},
    {"class": "Button", "id": 1, "text": "OK"}]}
MAIN = {"title": "The Lord of the Rings(tm), The Battle for Middle-earth(tm) II", "class": "Game Window",
        "rect": [-32000, -32000, -31840, -31969], "children": []}


class Dialogs(unittest.TestCase):
    def test_game_crash_box_is_read(self):
        d = bs.crash_dialog([MAIN, GAME_CRASH])
        self.assertEqual(d["title"], "Game crash")
        self.assertEqual(d["text"], STACKWALK)                   # the static text, not "OK"
        self.assertEqual(d["addresses"], [0x10294F3A, 0x1065C82E, 0x1029ABCD])

    def test_every_crash_title_counts(self):
        for title in ("Game crash", "Error hit", "Assertion failed", "Exception", " game CRASH "):
            self.assertIsNotNone(bs.crash_dialog([dict(GAME_CRASH, title=title)]), title)

    def test_other_windows_are_not_crashes(self):
        self.assertIsNone(bs.crash_dialog([MAIN]))
        self.assertIsNone(bs.crash_dialog([dict(GAME_CRASH, title="Options")]))
        self.assertIsNone(bs.crash_dialog([]))

    def test_text_falls_back_to_all_children(self):
        self.assertEqual(bs.dialog_text({"children": [{"class": "Edit", "text": "boom"}]}), "boom")

    def test_addresses_skip_small_values_and_longer_words(self):
        self.assertEqual(bs.dialog_addresses("00000004 0x0000ffff 123456789 10294F3A"), [0x10294F3A])


def timeout_run(dialogs, shot):
    return {"outcome": "timeout", "first_chance": [], "probes_hit": [], "image_base": 0x400000, "pid": 7,
            "windows": [(w["title"], tuple(w["rect"])) for w in dialogs], "dialogs": dialogs,
            "screenshot": shot, "main_eips": [], "quiet": [],
            "main_stack": {"esp": 0x19F000, "regs": {"eip": "0x7bd6382c"}, "words": [0x401234]}}


class Classification(unittest.TestCase):
    OPTS = dict(retail=True, base=0x400000, args="-win", overlay=None, appdata=Path("/mock-sandbox-appdata"),
                game_dir=Path("/mock-game"), guard=[], compat=None, no_focus_lie=True, no_version_lie=True,
                timeout=2, probes=False, defocus=None, int3_faults=False, relayout=False)

    def smoke(self, report):
        with (mock.patch.object(bs, "prepare_sandbox_profile"),
              mock.patch.object(bs.real_image, "install_game_dat", return_value="0" * 64),
              mock.patch.object(bs, "run", return_value=report),
              mock.patch.object(bs, "address_label", side_effect=lambda va, *a: f"row+{va & 0xFF:#x}"),
              mock.patch.object(bs, "image_frames", return_value=[["0x401234", "WinMain+0x34"]]),
              mock.patch.object(bs, "ProfileGuard") as guard):
            guard.return_value.check.return_value = ({"changed": []}, False)
            return bs.smoke(SimpleNamespace(**self.OPTS))

    def test_crash_box_is_crash_dialog_not_loading_screen(self):
        out = self.smoke(timeout_run([MAIN, GAME_CRASH], {"path": "x.png", "black": False, "stddev": 42,
                                                         "menu_bar": 0.0}))
        self.assertEqual(out["outcome"], "crash-dialog")
        self.assertEqual(out["receipt"]["result"], "crash-dialog")
        self.assertEqual(out["crash"]["dialog"]["text"], STACKWALK)
        self.assertEqual(out["crash"]["dialog"]["frames"][0], ["0x10294f3a", "row+0x3a"])
        self.assertEqual(out["main_stack"]["frames"], [["0x401234", "WinMain+0x34"]])

    def test_crash_box_wins_over_a_menu_picture(self):
        out = self.smoke(timeout_run([GAME_CRASH], {"path": "x.png", "black": False, "stddev": 51,
                                                    "menu_bar": 0.74}))
        self.assertEqual(out["outcome"], "crash-dialog")

    def test_without_a_box_the_picture_decides(self):
        out = self.smoke(timeout_run([MAIN], {"path": "x.png", "black": False, "stddev": 42, "menu_bar": 0.0}))
        self.assertEqual(out["outcome"], "loading-screen")
        self.assertNotIn("crash", out)

    def test_result_of_keeps_crash_dialog(self):
        self.assertEqual(real_image.result_of("crash-dialog"), "crash-dialog")
        self.assertEqual(real_image.result_of("crash-at-?f@@YAXXZ"), "crashed")


class QuietExceptions(unittest.TestCase):
    def memory(self, blobs):
        def read(k, hproc, va, n):
            for at, b in blobs.items():
                if at <= va < at + len(b):
                    return b[va - at:va - at + n]
            return b""
        return read

    def test_cpp_throw_names_its_type(self):
        ti, cta, ct, td = 0x1000, 0x2000, 0x3000, 0x4000
        blobs = {ti: struct.pack("<IIII", 0, 0, 0, cta), cta: struct.pack("<II", 1, ct),
                 ct: struct.pack("<II", 0, td), td: struct.pack("<II", 0, 0) + b".?AVErrorCode@@\0junk"}
        with mock.patch.object(bs, "read_memory", side_effect=self.memory(blobs)), \
                mock.patch.object(bs, "stack_words", return_value={"words": [1, 2]}):
            q = bs.quiet_exception(None, 0, 0, 0xE06D7363, 0x7B000000, [0x19930520, 0x5000, ti])
        self.assertEqual((q["type"], q["throw_info"], q["stack"]), (".?AVErrorCode@@", "0x1000", [1, 2]))

    def test_unreadable_throw_info_is_none(self):
        with mock.patch.object(bs, "read_memory", return_value=b""), \
                mock.patch.object(bs, "stack_words", return_value=None):
            self.assertIsNone(bs.quiet_exception(None, 0, 0, 0xE06D7363, 0, [0x19930520, 0, 0x1000])["type"])

    def test_debug_string_text(self):
        with mock.patch.object(bs, "read_memory", side_effect=self.memory({0x9000: b"INI load failed\0zz"})):
            q = bs.quiet_exception(None, 0, 0, 0x40010006, 0x7B000000, [16, 0x9000])
        self.assertEqual(q["text"], "INI load failed")


if __name__ == "__main__":
    unittest.main()
