"""boot_smoke/game_smoke picture judging: a black, flat, missing or partly hidden
frame never counts as a picture. No game is started; frames are PIL fixtures."""
import random
import sys
import tempfile
import unittest
from pathlib import Path
from unittest import mock

from PIL import Image, ImageDraw

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import boot_smoke as bs  # noqa: E402
import game_smoke as gs  # noqa: E402

W, H = 1024, 768


def noise(lo, hi, seed=1):
    rng = random.Random(seed)
    img = Image.new("RGB", (W // 8, H // 8))
    img.putdata([tuple(rng.randint(lo, hi) for _ in range(3)) for _ in range(img.width * img.height)])
    return img.resize((W, H), Image.NEAREST)


def menu():
    """A busy picture with a green button bar in the bottom band, as the main menu."""
    img = noise(20, 200)
    d = ImageDraw.Draw(img)
    d.rectangle((0, int(H * 0.89), W, int(H * 0.97)), fill=(20, 160, 30))
    return img


def judged(img):
    with tempfile.TemporaryDirectory() as d:
        path = Path(d) / "shot.png"
        with (mock.patch.object(bs, "windows_of", return_value=[("BFME2", (0, 0, W, H), 7)]),
              mock.patch.object(bs, "under_wine", return_value=True),
              mock.patch.object(bs, "root_capture", return_value=(img, "xvfb-root", None))):
            shot = bs.window_picture(1, path)
        return shot, bs.classify_picture(shot)


class Frames(unittest.TestCase):
    def test_black_frame_is_no_picture(self):
        shot, outcome = judged(Image.new("RGB", (W, H)))
        self.assertTrue(shot["black"])
        self.assertEqual(outcome, "no-picture")

    def test_near_black_noise_is_no_picture(self):            # nothing above the black level
        shot, outcome = judged(noise(0, bs.BLACK))
        self.assertGreater(shot["stddev"], 0)
        self.assertEqual(outcome, "no-picture")

    def test_flat_grey_is_blank(self):
        self.assertEqual(judged(Image.new("RGB", (W, H), (90, 90, 90)))[1], "blank-window")

    def test_flat_green_is_blank_not_menu(self):              # the bar test alone would pass it
        shot, outcome = judged(Image.new("RGB", (W, H), (20, 160, 30)))
        self.assertGreater(shot["menu_bar"], bs.MENU_BAR)
        self.assertEqual(outcome, "blank-window")

    def test_picture_without_button_bar_is_loading(self):
        self.assertEqual(judged(noise(20, 200))[1], "loading-screen")

    def test_menu_picture_reaches_menu(self):
        self.assertEqual(judged(menu())[1], "reached-menu")

    def test_failed_or_refused_capture_is_no_picture(self):
        with (mock.patch.object(bs, "windows_of", return_value=[("BFME2", (0, 0, W, H), 7)]),
              mock.patch.object(bs, "under_wine", return_value=True),
              mock.patch.object(bs, "root_capture", return_value=(None, "xvfb-root", "covered"))):
            shot = bs.window_picture(1, Path("unused.png"))
        self.assertEqual(shot, {"capture": "none", "method": "xvfb-root", "why": "covered"})
        self.assertEqual(bs.classify_picture(shot), "no-picture")

    def test_no_window_is_no_window(self):
        with mock.patch.object(bs, "windows_of", return_value=[]):
            self.assertIsNone(bs.window_picture(1, Path("unused.png")))
        self.assertEqual(bs.classify_picture(None), "no-window")

    def test_stats_without_black_flag_are_refused(self):      # an old-style dict cannot pass
        self.assertEqual(bs.classify_picture({"path": "x.png", "stddev": 60, "menu_bar": 0.8}), "no-picture")

    def test_windows_uses_printwindow_never_the_screen(self):
        with (mock.patch.object(bs, "windows_of", return_value=[("BFME2", (0, 0, W, H), 7)]),
              mock.patch.object(bs, "under_wine", return_value=False),
              mock.patch.object(bs, "print_window", return_value=None) as pw,
              mock.patch.object(bs, "root_capture") as root):
            shot = bs.window_picture(1, Path("unused.png"))
        pw.assert_called_once_with(7)
        root.assert_not_called()
        self.assertEqual(bs.classify_picture(shot), "no-picture")


class RootCaptureRefusal(unittest.TestCase):
    def test_wholly_visible_window_is_captured(self):
        self.assertIsNone(bs.capture_refusal((10, 10, 1034, 778), (2048, 1536), [True] * 5))

    def test_window_off_the_screen_is_refused(self):            # measured: 1024x768 at y 315 on 1050 lines
        self.assertIn("not wholly", bs.capture_refusal((303, 315, 1327, 1083), (1400, 1050), [True] * 5))
        self.assertIn("not wholly", bs.capture_refusal((-5, 0, 1019, 768), (2048, 1536), [True] * 5))

    def test_covered_window_is_refused(self):
        self.assertIn("covers", bs.capture_refusal((0, 0, 1024, 768), (2048, 1536), [True, True, False, True, True]))
        self.assertIn("covers", bs.capture_refusal((0, 0, 1024, 768), (2048, 1536), []))

    def test_empty_client_area_is_refused(self):
        self.assertEqual(bs.capture_refusal((0, 0, 0, 0), (2048, 1536), [True] * 5), "empty client area")

    def test_probe_points_lie_inside_the_rectangle(self):
        rect = (100, 50, 1124, 818)
        for x, y in bs.probe_points(rect):
            self.assertTrue(rect[0] <= x < rect[2] and rect[1] <= y < rect[3])


class SkirmishNeedsAPicture(unittest.TestCase):
    S = [(t, t * 10, 2) for t in range(30)]

    def test_missing_capture_fails(self):
        self.assertEqual(gs.judge_skirmish(self.S, 2, 100, shot=None), "no-picture")
        self.assertEqual(gs.judge_skirmish(self.S, 2, 100, shot={"capture": "none"}), "no-picture")

    def test_black_capture_fails(self):
        shot, _ = judged(Image.new("RGB", (W, H)))
        self.assertEqual(gs.judge_skirmish(self.S, 2, 100, shot=shot), "no-picture")

    def test_flat_capture_fails(self):
        shot, _ = judged(Image.new("RGB", (W, H), (90, 90, 90)))
        self.assertEqual(gs.judge_skirmish(self.S, 2, 100, shot=shot), "blank-window")

    def test_picture_passes(self):
        shot, _ = judged(noise(20, 200))
        self.assertEqual(gs.judge_skirmish(self.S, 2, 100, shot=shot), "pass")


if __name__ == "__main__":
    unittest.main()
