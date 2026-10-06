"""game_smoke: the pure parts (CRC pairing, outcome judges, call stubs, RVA moves).

The profile redirect and guard are boot_smoke's: tests/test_boot_smoke_profile.py.

No game is started; the debugger itself is exercised by the retail control runs
(`python3 tools/game_smoke.py ... --retail`), not here.
"""
import sys
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import game_smoke as gs  # noqa: E402

SKIRMISH = 2


class PairCrcs(unittest.TestCase):
    def test_matching_playback_pairs_every_frame(self):
        ev = []
        for f in (100, 200, 300):
            ev += [(f, 0x1000 + f, False), (f, 0x1000 + f, True)]    # recorded, then computed
        c = gs.pair_crcs(ev)
        self.assertEqual(c["pairs"], 3)
        self.assertEqual(c["mismatches"], [])
        self.assertEqual(c["last_frame"], 300)
        self.assertEqual(gs.judge_playback(c, recorded_last=330, played_last=320), "pass")

    def test_one_differing_crc_is_a_desync(self):           # positive control
        ev = [(100, 1, False), (100, 1, True), (200, 2, False), (200, 3, True)]
        c = gs.pair_crcs(ev)
        self.assertEqual(c["mismatches"], [(200, 2, 3)])
        self.assertEqual(gs.judge_playback(c), "desync")

    def test_order_within_a_frame_does_not_matter(self):
        ev = [(100, 7, True), (100, 7, False)]
        self.assertEqual(gs.pair_crcs(ev)["mismatches"], [])

    def test_unpaired_frames_are_reported_not_compared(self):
        c = gs.pair_crcs([(100, 1, False), (200, 9, True)])
        self.assertEqual((c["pairs"], c["unpaired_recorded"], c["unpaired_computed"]), (0, [100], [200]))
        self.assertEqual(gs.judge_playback(c), "no-crcs")

    def test_short_playback_fails(self):
        ev = [(f, f, p) for f in (100, 200, 300) for p in (False, True)]
        self.assertEqual(gs.judge_playback(gs.pair_crcs(ev), recorded_last=900, played_last=310), "playback-short")
        self.assertEqual(gs.judge_playback(gs.pair_crcs(ev), recorded_last=900, played_last=None), "playback-short")

    def test_crash_wins(self):
        c = gs.pair_crcs([(f, f, p) for f in (1, 2, 3) for p in (False, True)])
        self.assertEqual(gs.judge_playback(c, crash="crash-at-0x1234"), "crash-at-0x1234")


class JudgeSkirmish(unittest.TestCase):
    def test_simulating_skirmish_passes(self):
        s = [(t, 30 * t if t >= 10 else 5, SKIRMISH if t >= 10 else 4) for t in range(60)]
        self.assertEqual(gs.judge_skirmish(s, SKIRMISH, 100, shot={"stddev": 40}), "pass")

    def test_menu_only_is_no_game(self):                    # the shell map simulates too
        s = [(t, 30 * t, 4) for t in range(60)]
        self.assertEqual(gs.judge_skirmish(s, SKIRMISH, 100), "no-game")

    def test_stalled_frame_counter_fails(self):
        s = [(t, 77, SKIRMISH) for t in range(60)]
        self.assertEqual(gs.judge_skirmish(s, SKIRMISH, 100), "no-frames")

    def test_blank_window_fails(self):
        s = [(t, 30 * t, SKIRMISH) for t in range(60)]
        self.assertEqual(gs.judge_skirmish(s, SKIRMISH, 100, shot={"stddev": 2.0}), "blank-window")

    def test_crash_wins(self):
        s = [(t, 30 * t, SKIRMISH) for t in range(60)]
        self.assertEqual(gs.judge_skirmish(s, SKIRMISH, 100, crash="exit-0x29a"), "exit-0x29a")


class PieceMover(unittest.TestCase):
    def test_moves_retail_rva_into_its_piece(self):
        move = gs.piece_mover([[".text", 0x1000, 0x5000, 0x2000], [".data", 0x9F0000, 0x9F8000, 0x20000]])
        self.assertEqual(move(0x1010), 0x5010)
        self.assertEqual(move(0x9FE78C), 0xA0678C)

    def test_rva_outside_every_piece_is_refused(self):
        with self.assertRaises(KeyError):
            gs.piece_mover([[".text", 0x1000, 0x5000, 0x10]])(0x2000)


class StubCode(unittest.TestCase):
    def test_crc_then_autosave_stub(self):
        from capstone import Cs, CS_ARCH_X86, CS_MODE_32
        calls = [{"call": 0x63CB2C, "ecx": 0x5000000, "args": [0], "flag": 0xE02D87},
                 {"call": 0x6DD7E6, "ecx": 0x5100000}]
        code = gs.stub_code(calls, 0x1000800)
        got = [f"{i.mnemonic} {i.op_str}".strip() for i in Cs(CS_ARCH_X86, CS_MODE_32).disasm(code, 0x1000000)]
        self.assertEqual(got, [
            "mov byte ptr [0xe02d87], 1", "push 0", "mov ecx, 0x5000000", "mov eax, 0x63cb2c", "call eax",
            "mov dword ptr [0x1000800], eax", "mov byte ptr [0xe02d87], 0",
            "mov ecx, 0x5100000", "mov eax, 0x6dd7e6", "call eax", "mov dword ptr [0x1000804], eax", "int3"])

    def test_args_are_pushed_right_to_left(self):
        code = gs.stub_code([{"call": 1, "ecx": 2, "args": [7, 8]}], 0)
        self.assertEqual(code[:10], bytes.fromhex("6808000000 6807000000"))


class FrameHookSchedule(unittest.TestCase):
    def test_samples_every_n_frames_once_each(self):
        h = gs.FrameHook(every=25)
        self.assertIsNone(h.due(0, 2))                     # frame 0 is the set-up frame
        self.assertIsNone(h.due(24, 2))
        self.assertEqual(h.due(25, 2), "crc")
        h.crcs.append((25, 0xABC))
        self.assertIsNone(h.due(25, 2))                    # same logic frame, next engine frame
        self.assertEqual(h.due(50, 2), "crc")

    def test_wrong_mode_or_no_logic_is_never_sampled(self):
        h = gs.FrameHook(every=25)
        self.assertIsNone(h.due(50, 9))
        self.assertIsNone(h.due(None, None))

    def test_first_frame_after_load(self):
        h = gs.FrameHook(at_first=True)
        self.assertEqual(h.due(731, 2), "crc")
        h.crcs.append((731, 1))
        self.assertIsNone(h.due(732, 2))

    def test_save_request_wins_once(self):
        h = gs.FrameHook(every=25)
        h.save_requested = True
        self.assertEqual(h.due(40, 2), "save")
        h.save.update(frame=40, code=0)
        self.assertIsNone(h.due(41, 2))


class FakeGame:
    """Memory as a dict of dwords, enough for the breakpoint handlers."""
    base = 0x400000

    def __init__(self, mem):
        self.mem, self.res = dict(mem), {}

    def va(self, name):
        return self.base + gs.RVA[name]

    def u32(self, va):
        return self.mem.get(va)

    def global_ptr(self, name):
        return self.u32(self.va(name))

    def write(self, va, data, code=False):
        if len(data) == 4:
            self.mem[va] = int.from_bytes(data, "little")
        else:
            for i, b in enumerate(data):
                self.mem[("byte", va + i)] = b
        return True


class SkirmishSetup(unittest.TestCase):
    INFO, SLOT1 = 0x6000000, 0x6100000

    def game(self):
        g = FakeGame({0x400000 + gs.RVA["TheSkirmishGameInfo"]: self.INFO,
                      self.INFO + gs.SLOTS_OFF + 4: self.SLOT1, self.SLOT1 + gs.SLOT_STATE: 1})
        g.mem[0x400000 + gs.RVA["TheGameInfo"]] = 0
        return g

    def test_sets_game_info_and_adds_an_easy_ai(self):
        g = self.game()
        self.assertFalse(gs.skirmish_setup(True)(g, 1, None))           # one-shot
        self.assertEqual(g.global_ptr("TheGameInfo"), self.INFO)
        self.assertEqual(g.u32(self.SLOT1 + gs.SLOT_STATE), gs.SLOT_EASY_AI)
        self.assertEqual((g.mem[("byte", self.SLOT1 + 8)], g.mem[("byte", self.SLOT1 + 9)]), (1, 1))

    def test_fixed_seed_replaces_the_time_seed(self):
        g = self.game()
        g.mem[self.INFO + gs.SEED_OFF] = 1791300000                    # time(0)
        gs.skirmish_setup(True, seed=7)(g, 1, None)
        self.assertEqual(g.u32(self.INFO + gs.SEED_OFF), 7)
        g2 = self.game()
        g2.mem[self.INFO + gs.SEED_OFF] = 1791300000
        gs.skirmish_setup(True)(g2, 1, None)                            # no seed: left alone
        self.assertEqual(g2.u32(self.INFO + gs.SEED_OFF), 1791300000)

    def test_no_ai_leaves_slot_one_closed(self):
        g = self.game()
        gs.skirmish_setup(False)(g, 1, None)
        self.assertEqual(g.global_ptr("TheGameInfo"), self.INFO)
        self.assertEqual(g.u32(self.SLOT1 + gs.SLOT_STATE), 1)

    def test_nothing_to_do_without_a_skirmish_info(self):
        g = FakeGame({})
        gs.skirmish_setup(True)(g, 1, None)
        self.assertNotIn("setup", g.res)


class RetailAddresses(unittest.TestCase):
    """The hard-coded RVAs still point at the code they describe in retail."""

    @classmethod
    def setUpClass(cls):
        exe = gs.boot_smoke.boot_image.build.EXE
        if not exe.exists():
            raise unittest.SkipTest("no retail game.dat")
        import pefile
        pe = pefile.PE(str(exe), fast_load=True)
        cls.img = pe.get_memory_mapped_image()
        cls.exe = exe

    def test_breakpoint_sites_are_the_expected_instructions(self):
        img = self.img
        self.assertEqual(img[gs.RVA["handleCRCMessage"]:][:3], bytes.fromhex("55 8BEC"))        # push ebp; mov ebp, esp
        self.assertEqual(img[gs.RVA["fileSlotsSet"]:][:2], bytes.fromhex("6A02"))              # push 2 (GAME_SKIRMISH)
        self.assertEqual(img[gs.RVA["GameState::autoSave"]:][:1], b"\xB8")                     # mov eax, <EH handler>
        self.assertEqual(img[gs.RVA["GameLogic::getCRC"]:][:1], b"\xB8")
        self.assertEqual(img[gs.RVA["GameEngine::update"]:][:3], bytes.fromhex("55 8BEC"))
        for name in ("Debug::AssertDone/exit", "Debug::CrashDone/exit"):
            self.assertEqual(img[gs.RVA[name]:][:8], bytes.fromhex("6A01 FF1508A6BB00"))     # push 1; call [exit]


if __name__ == "__main__":
    unittest.main()
