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


def splash():
    """A picture with the title splash's coarse shape, and fine detail its thumbnail does not see."""
    img = Image.frombytes("L", (16, 12), bs.TITLE_SPLASH).resize((800, 600), Image.BILINEAR).convert("RGB")
    return img


class Labels(unittest.TestCase):
    def test_the_title_splash_is_not_loading(self):
        shot, outcome = judged(splash())
        self.assertTrue(shot["title_splash"])
        self.assertEqual(outcome, "title-splash")

    def test_another_picture_short_of_the_menu_is_loading(self):
        shot, outcome = judged(noise(20, 200))
        self.assertFalse(shot["title_splash"])
        self.assertEqual(outcome, "loading-screen")

    def test_the_menu_is_not_the_splash(self):
        shot, outcome = judged(menu())
        self.assertFalse(shot["title_splash"])
        self.assertEqual(outcome, "reached-menu")

    @staticmethod
    def over(eips, every=1.0, start=270.0):
        return [(start + i * every, e) for i, e in enumerate(eips)]

    LOW, HIGH = 0x10000000, 0x11000000

    def span(self, samples, failures=0):
        return bs.main_thread_span(samples, self.LOW, self.HIGH, failures)

    def test_a_tight_loop_over_the_span_is_a_spin(self):
        span = self.span(self.over([0x1085646D, 0x10856470, 0x1085646A] * 10))
        self.assertTrue(span["spinning"])
        self.assertEqual((span["low"], span["high"], span["spread"], span["samples"], span["seconds"]),
                         ("0x1085646a", "0x10856470", 6, 30, 29.0))

    def test_the_thresholds_are_these(self):
        # Literal on purpose: a wrong label misstates how far the game runs, so widening one is a reviewed change.
        self.assertEqual((bs.SPIN_WINDOW, bs.SPIN_MIN_SECONDS, bs.SPIN_MIN_SAMPLES, bs.SPIN_SPAN), (64, 25.0, 20, 30.0))

    def test_the_evidence_limits_are_these(self):
        # Literal on purpose, as above. Real hangs measured: no failures, a largest gap of 1.0 s. Retail's healthiest
        # worst case on these samples: 2.7 s between two.
        self.assertEqual((bs.SPIN_MAX_FAILURES, bs.SPIN_MAX_GAP), (2, 3.0))

    def test_the_event_grace_is_this(self):
        # Literal for the same reason: it decides how late a crash can still change a run's label.
        self.assertEqual(bs.EVENT_GRACE, 2.0)

    def test_failed_samples_limit_a_hang(self):
        self.assertTrue(self.span(self.over([self.LOW] * 30), failures=2)["spinning"])
        self.assertFalse(self.span(self.over([self.LOW] * 30), failures=3)["spinning"])

    def test_the_review_case_ten_failures_among_twenty_good_samples_is_no_hang(self):
        # Twenty good reads a little over a second apart, the failed ones hiding what ran between them.
        twenty = [(270.0 + i * 1.5, self.LOW) for i in range(20)]
        self.assertTrue(self.span(twenty)["spinning"])
        self.assertFalse(self.span(twenty, failures=10)["spinning"])

    def test_a_gap_in_the_good_samples_limits_a_hang(self):
        before = [(270.0 + i, self.LOW) for i in range(12)]
        at_limit = before + [(284.0 + i, self.LOW) for i in range(15)]         # 281 to 284
        over = before + [(284.1 + i, self.LOW) for i in range(15)]             # 281 to 284.1
        self.assertEqual(self.span(at_limit)["largest_gap"], 3.0)
        self.assertTrue(self.span(at_limit)["spinning"])
        self.assertEqual(self.span(over)["largest_gap"], 3.1)
        self.assertFalse(self.span(over)["spinning"])

    def test_only_the_largest_gap_counts_wherever_it_falls(self):
        for hole in (1, 10, 28):
            times = [270.0 + i + (4.0 if i >= hole else 0.0) for i in range(29)]
            self.assertFalse(self.span([(t, self.LOW) for t in times])["spinning"], hole)

    def test_the_span_reports_its_evidence(self):
        span = self.span(self.over([self.LOW] * 30), failures=1)
        self.assertEqual((span["failures"], span["largest_gap"]), (1, 1.0))

    def test_one_sample_has_no_gap(self):
        self.assertEqual(self.span([(270.0, self.LOW)])["largest_gap"], 0.0)

    def test_sixty_five_bytes_is_not_a_spin(self):
        self.assertFalse(self.span(self.over([self.LOW] * 29 + [self.LOW + 65]))["spinning"])

    def test_a_thread_parked_outside_the_image_is_not_a_spin(self):
        # Retail's own control at 120 s: 30 samples at 0x79A9C844, spread 0, an intro movie playing.
        span = bs.main_thread_span(self.over([0x79A9C844] * 30), 0x400000, 0x400000 + 0xB00000, 0)
        self.assertEqual(span["spread"], 0)
        self.assertFalse(span["inside_image"])
        self.assertFalse(span["spinning"])

    def test_the_image_bounds_are_exact(self):
        self.assertTrue(self.span(self.over([self.LOW] * 30))["spinning"])                       # its first byte
        self.assertFalse(self.span(self.over([self.LOW - 1] * 30))["spinning"])
        self.assertTrue(self.span(self.over([self.HIGH - 1] * 30))["spinning"])                  # its last
        self.assertFalse(self.span(self.over([self.HIGH] * 30))["spinning"])
        self.assertFalse(self.span(self.over([self.LOW] * 29 + [self.LOW - 1]))["spinning"])     # straddling it

    def test_the_menu_bar_outranks_a_splash_match(self):
        shot = {"path": "x", "black": False, "stddev": 60, "menu_bar": bs.MENU_BAR, "title_splash": True}
        self.assertEqual(bs.classify_picture(shot), "reached-menu")

    def test_the_window_is_exact(self):
        inside = self.over([self.LOW] * 29 + [self.LOW + bs.SPIN_WINDOW - 1])
        just_over = self.over([self.LOW] * 29 + [self.LOW + bs.SPIN_WINDOW])
        self.assertTrue(self.span(inside)["spinning"])
        self.assertFalse(self.span(just_over)["spinning"])

    def test_a_short_span_is_not_a_spin_however_tight(self):
        # What two seconds of a long copy looks like: the reason the test is not over 2 s.
        self.assertFalse(self.span(self.over([self.LOW] * 8, every=0.25))["spinning"])
        self.assertFalse(self.span(self.over([self.LOW] * 25, every=1.0))["spinning"])    # 24 s
        self.assertTrue(self.span(self.over([self.LOW] * 26, every=1.0))["spinning"])     # 25 s

    def test_too_few_samples_are_not_a_spin_however_long(self):
        self.assertFalse(self.span(self.over([self.LOW] * 19, every=2.0))["spinning"])
        self.assertTrue(self.span(self.over([self.LOW] * 20, every=2.0))["spinning"])

    def test_a_thread_at_work_is_not_a_spin(self):
        self.assertFalse(self.span(self.over([self.LOW, self.LOW + 0x5000, self.LOW + 0x9000] * 10))["spinning"])

    def test_no_samples_say_nothing(self):
        self.assertIsNone(self.span([]))

    def test_the_sampling_stays_inside_the_timeout(self):
        self.assertLess(bs.SPIN_MIN_SECONDS, bs.SPIN_SPAN)


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


PRIVATE = {"DISPLAY": ":91", "BFME_PRIVATE_DISPLAY": ":91"}
GAME = 7


class FakeUser32:
    """The user32 calls root_capture makes, over a scripted desktop: the game's client
    area in screen coordinates and the windows above it, top-most last. `later` is the
    desktop the second look (after the copy) sees."""

    def __init__(self, client, above=(), later=None, screen=(2048, 1536)):
        self.screen, self.looks = screen, [(client, list(above))] + ([later] if later else [])
        self.n = 0

    def now(self):
        return self.looks[min(self.n, len(self.looks) - 1)]

    def GetSystemMetrics(self, i):
        return self.screen[i]

    def GetClientRect(self, h, ref):
        l, t, r, b = self.now()[0]
        ref._obj.left, ref._obj.top, ref._obj.right, ref._obj.bottom = 0, 0, r - l, b - t
        return 1

    def ClientToScreen(self, h, ref):
        ref._obj.x, ref._obj.y = self.now()[0][:2]
        return 1

    def GetWindow(self, h, cmd):
        assert cmd == bs.GW_HWNDPREV
        chain = [GAME] + [w for w, _ in self.now()[1]]
        i = chain.index(h) + 1
        if i == len(chain):
            self.n += 1                         # one walk ends a look
            return 0
        return chain[i]

    def IsWindowVisible(self, w):
        return 1

    def GetWindowRect(self, w, ref):
        ref._obj.left, ref._obj.top, ref._obj.right, ref._obj.bottom = dict(self.now()[1])[w]
        return 1


def black_game_under_green_window():
    """What the screen shows: the game renders nothing (black 1024x768) and another
    window draws a green bar where the menu buttons would be (the review's case)."""
    img = Image.new("RGB", (W, H))
    ImageDraw.Draw(img).rectangle((100, 680, 924, 750), fill=(20, 160, 30))
    for x in range(0, W, 7):                    # some texture, so it is not flat
        ImageDraw.Draw(img).line((x, 690, x, 740), fill=(200, 200, 200))
    return img


def captured(user, screen_shows):
    with (mock.patch.object(bs, "_bitmap", return_value=screen_shows) as copy,
          mock.patch.dict(bs.os.environ, PRIVATE)):
        return bs.root_capture(GAME, user), copy


class RootCapture(unittest.TestCase):
    def test_window_over_part_of_a_black_game_is_refused(self):
        frame = black_game_under_green_window()
        self.assertEqual(bs.classify_picture(bs.picture_stats(frame) | {"path": "x", "menu_bar": bs.menu_bar(frame)}),
                         "reached-menu")              # what the screen copy alone would claim
        user = FakeUser32((0, 0, W, H), [(99, (100, 680, 924, 750))])
        (img, how, why), copy = captured(user, frame)
        self.assertIsNone(img)
        self.assertIn("overlap", why)
        copy.assert_not_called()

    def test_review_case_end_to_end_is_no_picture_and_no_pass(self):
        user = FakeUser32((0, 0, W, H), [(99, (100, 680, 924, 750))])
        with (mock.patch.object(bs, "windows_of", return_value=[("BFME2", (0, 0, W, H), GAME)]),
              mock.patch.object(bs, "under_wine", return_value=True),
              mock.patch.object(bs, "_gdi", return_value=(user, None)),
              mock.patch.object(bs, "_bitmap", return_value=black_game_under_green_window()),
              mock.patch.dict(bs.os.environ, PRIVATE)):
            shot = bs.window_picture(1, Path("unused.png"))
        self.assertEqual(bs.classify_picture(shot), "no-picture")
        self.assertEqual(gs.judge_skirmish([(t, t * 10, 2) for t in range(30)], 2, 100, shot=shot), "no-picture")

    def test_window_appearing_during_the_copy_is_refused(self):
        user = FakeUser32((0, 0, W, H), [], later=((0, 0, W, H), [(99, (1000, 700, 1100, 800))]))
        (img, _, why), copy = captured(user, menu())
        copy.assert_called_once()
        self.assertIsNone(img)
        self.assertIn("after the capture", why)

    def test_window_moving_during_the_copy_is_refused(self):
        user = FakeUser32((0, 0, W, H), [], later=((5, 0, W + 5, H), []))
        (img, _, why), _ = captured(user, menu())
        self.assertIsNone(img)
        self.assertIn("moved", why)

    def test_window_beside_the_game_is_fine(self):
        user = FakeUser32((0, 0, W, H), [(99, (W, 0, W + 300, 200))])
        (img, how, why), _ = captured(user, menu())
        self.assertIsNone(why)
        self.assertEqual(how, "xvfb-root")
        self.assertIsNotNone(img)

    def test_display_not_declared_private_is_refused(self):
        user = FakeUser32((0, 0, W, H))
        for env in ({"DISPLAY": ":91"}, {"DISPLAY": ":91", "BFME_PRIVATE_DISPLAY": ":92"}):
            with (mock.patch.object(bs, "_bitmap", return_value=menu()) as copy,
                  mock.patch.dict(bs.os.environ, env, clear=True)):
                img, _, why = bs.root_capture(GAME, user)
            self.assertIsNone(img)
            self.assertIn("not the private", why)
            copy.assert_not_called()

    def test_window_off_the_screen_is_refused(self):            # measured: 1024x768 at y 315 on 1050 lines
        user = FakeUser32((303, 315, 1327, 1083), screen=(1400, 1050))
        (img, _, why), _ = captured(user, menu())
        self.assertIsNone(img)
        self.assertIn("not wholly", why)


class CaptureRefusal(unittest.TestCase):
    def test_clear_private_window_is_captured(self):
        self.assertIsNone(bs.capture_refusal((10, 10, 1034, 778), (2048, 1536), [], ":9", ":9"))

    def test_any_overlap_is_refused_even_a_corner_pixel(self):
        self.assertIn("overlap", bs.capture_refusal((0, 0, W, H), (2048, 1536), [(5, (W - 1, H - 1, W + 50, H + 50))],
                                                    ":9", ":9"))

    def test_touching_edges_do_not_overlap(self):
        self.assertIsNone(bs.capture_refusal((0, 0, W, H), (2048, 1536), [(5, (W, 0, W + 50, 50))], ":9", ":9"))

    def test_off_screen_and_empty_are_refused(self):
        self.assertIn("not wholly", bs.capture_refusal((-5, 0, 1019, 768), (2048, 1536), [], ":9", ":9"))
        self.assertEqual(bs.capture_refusal((0, 0, 0, 0), (2048, 1536), [], ":9", ":9"), "empty client area")

    def test_missing_display_is_refused(self):
        self.assertIn("not the private", bs.capture_refusal((0, 0, W, H), (2048, 1536), [], None, None))


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
