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


class Fn:
    def __init__(self, f):
        self.f = f

    def __call__(self, *a):
        return self.f(*a)


class FakeUser32:
    """The user32 calls window_texts makes, over a scripted desktop: top-level windows in
    z-order {hwnd: (pid, visible, title, class, children)}, children [(hwnd, class, id, text)].
    Only InternalGetWindowText answers for text: GetWindowTextW would send WM_GETTEXT to a
    stopped thread, so it is deliberately absent."""

    def __init__(self, tops):
        self.tops = tops
        self.kids = {c[0]: c for _, _, _, _, kids in tops.values() for c in kids}
        for name in ("EnumWindows", "EnumChildWindows", "GetWindowThreadProcessId", "IsWindowVisible",
                     "InternalGetWindowText", "GetClassNameW", "GetDlgCtrlID", "GetWindowRect"):
            setattr(self, name, Fn(getattr(self, name)))       # ctypes-style: argtypes can be set

    def EnumWindows(self, cb, _):
        for h in self.tops:
            if not cb(h, 0):
                break
        return 1

    def EnumChildWindows(self, h, cb, _):
        for c in self.tops[h][4]:
            if not cb(c[0], 0):
                break
        return 1

    def GetWindowThreadProcessId(self, h, ref):
        ref._obj.value = self.tops[h][0]
        return 1

    def IsWindowVisible(self, h):
        return self.tops[h][1]

    def InternalGetWindowText(self, h, buf, n):
        buf.value = (self.tops[h][2] if h in self.tops else self.kids[h][3])[:n - 1]
        return len(buf.value)

    def GetClassNameW(self, h, buf, n):
        buf.value = self.tops[h][3] if h in self.tops else self.kids[h][1]
        return len(buf.value)

    def GetDlgCtrlID(self, h):
        return self.kids[h][2]

    def GetWindowRect(self, h, ref):
        ref._obj.left, ref._obj.top, ref._obj.right, ref._obj.bottom = 10, 20, 30, 40
        return 1


GAME_PID, OTHER_PID = 7, 8
DESKTOP = {
    0x50: (OTHER_PID, True, "Game crash", "#32770",          # another process's box, enumerated first
           [(0x51, "Static", 0xFFFF, "someone else's crash")]),
    0x10: (GAME_PID, True, MAIN["title"], "Game Window", []),   # the game, minimised behind its box
    0x20: (GAME_PID, True, "Game crash", "#32770",            # the game's owned popup
           [(0x21, "Static", 1088, ""), (0x22, "Button", 1, "OK"), (0x23, "Static", 0xFFFF, STACKWALK)]),
}


def read_windows(pid, desktop=DESKTOP):
    with mock.patch.object(bs.ctypes, "WinDLL", return_value=FakeUser32(desktop), create=True), \
            mock.patch.object(bs.ctypes, "WINFUNCTYPE", lambda *types: (lambda f: f), create=True):
        return bs.window_texts(pid)


class WindowReader(unittest.TestCase):
    """window_texts through a scripted user32 (review of 002895da8b: the reader itself was untested)."""

    def test_control_text_is_collected(self):
        box = [w for w in read_windows(GAME_PID) if w["title"] == "Game crash"]
        self.assertEqual(len(box), 1)
        self.assertEqual([(c["class"], c["id"], c["text"]) for c in box[0]["children"]],
                         [("Static", 1088, ""), ("Button", 1, "OK"), ("Static", 0xFFFF, STACKWALK)])
        self.assertEqual(bs.crash_dialog(read_windows(GAME_PID))["text"], STACKWALK)

    def test_another_process_crash_box_is_left_out(self):
        windows = read_windows(GAME_PID)
        self.assertNotIn("someone else's crash", [c["text"] for w in windows for c in w["children"]])
        self.assertIsNone(bs.crash_dialog(read_windows(GAME_PID, {0x50: DESKTOP[0x50], 0x10: DESKTOP[0x10]})))

    def test_owned_popup_is_included(self):
        windows = read_windows(GAME_PID)
        self.assertEqual([(w["title"], w["class"]) for w in windows],
                         [(MAIN["title"], "Game Window"), ("Game crash", "#32770")])
        self.assertEqual(bs.crash_dialog(windows)["title"], "Game crash")


def timeout_run(dialogs, shot):
    return {"outcome": "timeout", "first_chance": [], "probes_hit": [], "image_base": 0x400000, "pid": 7,
            "windows": [(w["title"], tuple(w["rect"])) for w in dialogs], "dialogs": dialogs,
            "screenshot": shot, "main_eips": [], "quiet": [],
            "main_stack": {"esp": 0x19F000, "regs": {"eip": "0x7bd6382c"}, "words": [0x401234]}}


class Classification(unittest.TestCase):
    OPTS = dict(retail=True, base=0x400000, args="-win", overlay=None, appdata=Path("/mock-sandbox-appdata"),
                game_dir=Path("/mock-game"), guard=[], compat=None, no_focus_lie=True, shots_at=(), trap_retail_data=False, no_version_lie=True,
                timeout=2, probes=False, defocus=None, int3_faults=False, relayout=False)

    def smoke(self, report):
        with (mock.patch.object(bs, "prepare_sandbox_profile"),
              mock.patch.object(bs.real_image, "install_game_dat", return_value="0" * 64),
              mock.patch.object(bs, "run", return_value=report) as self.ran,
              mock.patch.object(bs, "address_label", side_effect=lambda va, *a: f"row+{va & 0xFF:#x}"),
              mock.patch.object(bs, "image_frames", return_value=[["0x401234", "WinMain+0x34"]]),
              mock.patch.object(bs, "ProfileGuard") as guard):
            guard.return_value.check.return_value = ({"changed": []}, False)
            return bs.smoke(SimpleNamespace(**self.OPTS))

    def test_the_harness_options_reach_the_run(self):
        self.OPTS = dict(self.OPTS, trap_retail_data=True, shots_at=[1.0])
        self.smoke(timeout_run([MAIN], {"path": "x.png", "black": False, "stddev": 42, "menu_bar": 0.0}))
        self.assertIs(self.ran.call_args.kwargs["trap_retail_data"], True)
        self.assertEqual(self.ran.call_args.kwargs["shots_at"], [1.0])

    def test_the_receipt_shows_the_trap_and_its_result(self):
        trap = {"low": "0xbb0000", "high": "0xe30000", "got": "0xbb0000", "error": 0}
        self.OPTS = dict(self.OPTS, trap_retail_data=True)
        out = self.smoke(dict(timeout_run([MAIN], {"path": "x.png", "black": False, "stddev": 42, "menu_bar": 0.0}),
                              retail_trap=trap))
        self.assertEqual((out["receipt"]["mode"], out["receipt"]["trap_retail_data"], out["receipt"]["retail_trap"]),
                         ("boot+retail-trap", True, trap))
        self.OPTS = dict(self.OPTS, trap_retail_data=False)
        out = self.smoke(timeout_run([MAIN], {"path": "x.png", "black": False, "stddev": 42, "menu_bar": 0.0}))
        self.assertEqual((out["receipt"]["mode"], out["receipt"]["trap_retail_data"], out["receipt"]["retail_trap"]),
                         ("boot", False, None))

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

    SHOT = {"path": "x.png", "black": False, "stddev": 42, "menu_bar": 0.0}
    SPINNING = [(270.0 + i, e) for i, e in enumerate([0x82446D, 0x824470, 0x82446A] * 10)]
    WORKING = [(270.0 + i, e) for i, e in enumerate([0x401000, 0x7A0000, 0x452000] * 10)]
    WAITING = [(270.0 + i, 0x79A9C844) for i in range(30)]        # retail's control at 120 s, in a system call

    def run_with(self, shot, samples, failures=None):
        report = timeout_run([MAIN], shot)
        report["spin_samples"] = samples
        if failures is not None:
            report["spin_sample_failures"] = failures
        return self.smoke(report)

    def test_a_spin_on_the_splash_is_a_hang_there(self):
        # The receipt that prompted this: 0998e2bfee, on the title splash, in P30's __lg loop, read "loading-screen".
        out = self.run_with(dict(self.SHOT, title_splash=True), self.SPINNING)
        self.assertEqual(out["outcome"], "hang-on-title-splash")
        self.assertEqual(out["picture"], "title-splash")
        self.assertEqual(out["main_thread_span"]["samples"], 30)
        self.assertEqual(out["receipt"]["result"], "hang-on-title-splash")

    def test_failed_samples_reach_the_label(self):
        # The review's injection: twenty good samples with ten failed ones read hang-on-loading-screen.
        self.assertEqual(self.run_with(self.SHOT, self.SPINNING, 2)["outcome"], "hang-on-loading-screen")
        out = self.run_with(self.SHOT, self.SPINNING, 3)
        self.assertEqual(out["outcome"], "loading-screen")
        self.assertEqual(out["main_thread_span"]["failures"], 3)
        self.assertFalse(out["main_thread_span"]["spinning"])

    def test_a_gap_reaches_the_label(self):
        holed = [(t + (5.0 if t >= 285.0 else 0.0), e) for t, e in self.SPINNING]
        out = self.run_with(self.SHOT, holed)
        self.assertEqual(out["outcome"], "loading-screen")
        self.assertEqual(out["main_thread_span"]["largest_gap"], 6.0)

    def test_the_splash_with_a_working_thread_only_says_splash(self):
        out = self.run_with(dict(self.SHOT, title_splash=True), self.WORKING)
        self.assertEqual(out["outcome"], "title-splash")
        self.assertFalse(out["main_thread_span"]["spinning"])

    def test_no_samples_leave_the_picture_alone(self):
        out = self.run_with(dict(self.SHOT, title_splash=True), [])
        self.assertEqual(out["outcome"], "title-splash")
        self.assertNotIn("main_thread_span", out)

    def test_a_spin_spread_just_over_the_window_is_not_a_hang(self):
        wide = [(270.0 + i, 0x401000 + (i % 2) * bs.SPIN_WINDOW) for i in range(30)]
        self.assertEqual(self.run_with(self.SHOT, wide)["outcome"], "loading-screen")

    def test_a_thread_waiting_outside_the_image_is_not_a_hang(self):
        out = self.run_with(self.SHOT, self.WAITING)
        self.assertEqual(out["outcome"], "loading-screen")
        self.assertFalse(out["main_thread_span"]["inside_image"])

    def test_a_spin_on_another_picture_is_a_hang_there(self):
        self.assertEqual(self.run_with(self.SHOT, self.SPINNING)["outcome"], "hang-on-loading-screen")

    def test_the_menu_stays_the_menu_whatever_the_samples(self):
        out = self.run_with(dict(self.SHOT, menu_bar=0.8), self.SPINNING)
        self.assertEqual(out["outcome"], "reached-menu")

    def test_a_crash_box_outranks_a_spin(self):
        report = timeout_run([MAIN, GAME_CRASH], self.SHOT)
        report["spin_samples"] = self.SPINNING
        self.assertEqual(self.smoke(report)["outcome"], "crash-dialog")

    def test_a_confirmed_hang_is_a_start_up_the_overlay_broke(self):
        # A spin before any window used to read no-window and reach --bisect; the label must not hide it.
        for outcome in ("hang-on-no-window", "hang-on-blank-window", "hang-on-no-picture", "hang-on-title-splash",
                        "hang-on-loading-screen"):
            self.assertTrue(bs.broke(outcome), outcome)

    def test_what_broke_still_says_of_the_rest(self):
        for outcome in ("no-window", "blank-window", "crash-at-x", "crash-dialog", "exit-0x1"):
            self.assertTrue(bs.broke(outcome), outcome)
        for outcome in ("title-splash", "loading-screen", "reached-menu", "no-picture", "debugger-error", "link-error",
                        "guard-violation", "hung", "hanging", "hang"):
            self.assertFalse(bs.broke(outcome), outcome)

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
