"""game_smoke: the pure parts (CRC pairing, outcome judges, call stubs, RVA moves).

The profile redirect and guard are boot_smoke's: tests/test_boot_smoke_profile.py.

No game is started; the debugger itself is exercised by the retail control runs
(`python3 tools/game_smoke.py ... --retail`), not here.
"""
import argparse
import sys
import unittest
from pathlib import Path
from types import SimpleNamespace
from unittest import mock

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
        self.assertEqual(gs.judge_skirmish(s, SKIRMISH, 100, shot={"path": "x.png", "black": False, "stddev": 40}), "pass")

    def test_menu_only_is_no_game(self):                    # the shell map simulates too
        s = [(t, 30 * t, 4) for t in range(60)]
        self.assertEqual(gs.judge_skirmish(s, SKIRMISH, 100), "no-game")

    def test_stalled_frame_counter_fails(self):
        s = [(t, 77, SKIRMISH) for t in range(60)]
        self.assertEqual(gs.judge_skirmish(s, SKIRMISH, 100), "no-frames")

    def test_blank_window_fails(self):
        s = [(t, 30 * t, SKIRMISH) for t in range(60)]
        self.assertEqual(gs.judge_skirmish(s, SKIRMISH, 100, shot={"path": "x.png", "black": False, "stddev": 2.0}), "blank-window")

    def test_crash_wins(self):
        s = [(t, 30 * t, SKIRMISH) for t in range(60)]
        self.assertEqual(gs.judge_skirmish(s, SKIRMISH, 100, crash="exit-0x29a"), "exit-0x29a")


class JudgeRecord(unittest.TestCase):
    def test_changing_crcs_pass(self):
        self.assertEqual(gs.judge_record("pass", [(25, 1), (50, 2), (75, 3)]), "pass")

    def test_constant_crcs_mean_an_empty_world(self):            # seen live: observers only
        self.assertEqual(gs.judge_record("pass", [(f, 841115588) for f in (25, 50, 75, 100)]), "crc-constant")

    def test_too_few_or_failed_run(self):
        self.assertEqual(gs.judge_record("pass", [(25, 1)]), "no-crcs")
        self.assertEqual(gs.judge_record("exit-0x1", [(25, 1), (50, 2), (75, 3)]), "exit-0x1")


class PieceMover(unittest.TestCase):
    def test_moves_retail_rva_into_its_piece(self):
        move = gs.piece_mover([[".text", 0x1000, 0x5000, 0x2000], [".data", 0x9F0000, 0x9F8000, 0x20000]])
        self.assertEqual(move(0x1010), 0x5010)
        self.assertEqual(move(0x9FE78C), 0xA0678C)

    def test_relayout_moved_copy_wins_over_its_int3_filler(self):
        pieces = [[".text", 0x1000, 0x1000, 0x400000],                 # scaffold, retail order
                  [".text", 0x22D290, 0x22D290, 0x200],                 # filler left at a moved unit
                  [".text$r000017", 0x22D290, 0xE41230, 0x200],         # the moved unit
                  [".data", 0x9F0000, 0x9F0000, 0x20000],
                  [".odata", 0x9FE780, 0xF00000, 0x10]]                # our own copy of a datum
        move = gs.piece_mover([p for p in pieces if p[2] != 0x22D290 or p[0] != ".text"] + [pieces[1]])
        self.assertEqual(move(0x22D2A0), 0xE41240)                     # never the filler
        self.assertTrue(move.ours(0x22D2A0))
        self.assertEqual(move(0x9FE78C), 0xF0000C)                     # owned data
        self.assertEqual(move(0x9FE758), 0x9FE758)                     # retail data left in place
        self.assertFalse(move.ours(0x9FE758))

    def test_two_moved_copies_are_ambiguous(self):
        move = gs.piece_mover([[".text$r000001", 0x1000, 0x5000, 0x10], [".text$r000002", 0x1008, 0x6000, 0x10]])
        with self.assertRaises(KeyError):
            move(0x100C)

    def test_unplaceable_harness_address_refuses_the_run(self):
        move = gs.piece_mover([[".text", 0x1000, 0x1000, 0x100]])
        with self.assertRaises(SystemExit) as e:
            gs.map_addresses(move, ["GameLogic::getCRC"])
        self.assertIn("GameLogic::getCRC", str(e.exception))

    def test_rva_outside_every_piece_is_refused(self):
        with self.assertRaises(KeyError):
            gs.piece_mover([[".text", 0x1000, 0x5000, 0x10]])(0x2000)


class Coverage(unittest.TestCase):
    def test_report_counts_units_and_bytes_that_ran(self):
        units = {0xE41230: (0x22D290, 0x200, "GameEngine::execute"), 0xE50000: (0x23CB2C, 0x21E, "getCRC"),
                 0xE60000: (0x1000, 0x10, "never")}
        rep = gs.coverage_report(units, [(3.0, None, 0xE41230), (40.0, 25, 0xE50000), (41.0, 25, 0x123)])
        self.assertEqual((rep["units"], rep["units_run"], rep["bytes"], rep["bytes_run"], rep["run_before_game"]),
                         (3, 2, 0x200 + 0x21E + 0x10, 0x200 + 0x21E, 1))
        self.assertEqual(rep["run"][1], ["0x23cb2c", 0x21E, "getCRC", 25])

    ROWS = [(0x3000, 0x20, "b", "x.cpp"), (0x1000, 0x40, "f", "x.cpp"), (0x1000, 0x30, "e", "y.cpp"),
            (0x1010, 0x8, "inner", "x.cpp"), (0x1040, 0x10, "g", "x.cpp"), (0x900000, 4, "data", "x.cpp")]

    def test_ledger_units_one_per_start_in_code_and_never_inside_another(self):
        units, skipped = gs.ledger_units(self.ROWS, lambda r: r < 0x800000)
        self.assertEqual(units, [[0x1000, 0x40, "e|f"], [0x1040, 0x10, "g"], [0x3000, 0x20, "b"]])
        self.assertEqual(skipped, {"not code": 1, "inside another row": 1})

    def test_ledger_units_and_their_digest_ignore_row_order(self):
        units, _ = gs.ledger_units(self.ROWS, lambda r: r < 0x800000)
        again, _ = gs.ledger_units(list(reversed(self.ROWS)), lambda r: r < 0x800000)
        self.assertEqual(gs.units_digest(units), gs.units_digest(again))
        self.assertNotEqual(gs.units_digest(units), gs.units_digest(units[:-1]))

    def test_ledger_coverage_is_retail_only_and_needs_coverage(self):
        ns = lambda **k: SimpleNamespace(**dict(dict(coverage=True, coverage_units="ledger", retail=True), **k))
        gs.check_coverage_args(ns())
        gs.check_coverage_args(ns(coverage_units=None, retail=False))           # the authored list, as before
        gs.check_coverage_args(ns(coverage=False, coverage_units=None))         # a normal run
        with self.assertRaises(SystemExit):
            gs.check_coverage_args(ns(retail=False))
        with self.assertRaises(SystemExit):
            gs.check_coverage_args(ns(coverage=False))

    def test_receipt_names_the_list_by_hash(self):
        units = {0x401000: (0x1000, 0x40, "e|f"), 0x403000: (0x3000, 0x20, "b")}
        cov = gs.coverage_report(units, [(1.0, None, 0x403000)])
        cov.update(source={"units_from": "ledger", "units": 2, "units_sha256": "ab"}, armed=2)
        rec = gs.coverage_receipt(cov, "coverage_skirmish_retail.json")
        self.assertEqual((rec["units_from"], rec["units_sha256"], rec["armed"], rec["units_run"], rec["file"]),
                         ("ledger", "ab", 2, 1, "coverage_skirmish_retail.json"))
        self.assertNotIn("run", rec)

    def test_the_result_file_keeps_the_run_list_and_stdout_does_not(self):
        import io
        import json
        import tempfile
        from contextlib import redirect_stdout
        cov = gs.coverage_report({0x3000: (0x3000, 32, "b"), 0x4000: (0x4000, 8, "c")}, [(1.0, None, 0x3000)],
                                 {0x4000: "write failed"})
        cov.update(source={"units_from": "ledger", "units": 2, "units_sha256": "ab"}, armed=1, observed_by_harness=[])
        out = {"outcome": "pass", "image": "retail", "receipt": {"result": "pass"}, "coverage": cov}
        with tempfile.TemporaryDirectory() as d, mock.patch.object(gs, "OUT", Path(d)):
            printed = io.StringIO()
            with redirect_stdout(printed):
                path = gs.write_result("skirmish", out)
            kept = json.loads(path.read_text())
            self.assertEqual(path.name, "skirmish_retail.json")
            self.assertEqual(kept["coverage"]["run"], [["0x3000", 32, "b", None]])
            self.assertEqual(kept["coverage"]["not_observed"], [["0x4000", 8, "c", "write failed"]])
            self.assertEqual((kept["receipt"]["coverage"]["units_sha256"], kept["receipt"]["coverage"]["armed"],
                              kept["receipt"]["coverage"]["not_observed"]), ("ab", 1, 1))
            self.assertNotIn("run", json.loads(printed.getvalue())["coverage"])
            self.assertTrue((Path(d) / "coverage_skirmish_retail.json").exists())

    def test_a_run_without_coverage_writes_what_it_always_did(self):
        import io
        import json
        import tempfile
        from contextlib import redirect_stdout
        out = {"outcome": "pass", "image": "retail", "receipt": {"result": "pass"}}
        with tempfile.TemporaryDirectory() as d, mock.patch.object(gs, "OUT", Path(d)):
            with redirect_stdout(io.StringIO()) as printed:
                path = gs.write_result("skirmish", out)
            self.assertEqual(path.read_text(), json.dumps(out, indent=1, default=str))
            self.assertEqual(printed.getvalue(), json.dumps(out, indent=1, default=str) + "\n")
            self.assertEqual(sorted(p.name for p in Path(d).iterdir()), ["skirmish_retail.json"])


class Probes(unittest.TestCase):
    """--coverage probes on the real Game._arm / _hit / _arm_probes, over a fake address space."""
    BASE = 0x400000

    def game(self, mem, unreadable=()):
        g = gs.Game.__new__(gs.Game)
        g.base, g.bps, g.stepping, g.res, g.covered = self.BASE, {}, {}, {}, []
        g.probe_units, g.probe_shared, g.probe_failed = {}, set(), {}
        g.read = lambda va, n: None if va in unreadable else bytes([mem[va]])
        g.write = lambda va, data, code=False: mem.__setitem__(va, data[0]) or True
        g.seconds = lambda: 1.0
        g.logic = lambda: (7, 2)
        ctx = gs.WOW64_CONTEXT()

        def context(tid, flags=0x10003):
            ctx.eip = 0x12345                                                  # past the int3; _hit rewinds it
            return 1, ctx
        g._context = context
        g.k = SimpleNamespace(Wow64SetThreadContext=lambda *a: 1, CloseHandle=lambda *a: 1)
        return g

    def test_a_unit_under_a_harness_breakpoint_is_observed_through_it(self):     # review: InitRandom 0x233F82
        seed, other = self.BASE + 0x233F82, self.BASE + 0x1000
        mem = {seed: 0x55, other: 0x8B}
        g = self.game(mem)
        fired = []
        self.assertIsNone(g._arm(seed, lambda game, tid, ctx: fired.append(1) or True))   # the harness's own, kept
        g.probe_units = {0x233F82: (0x233F82, 0x45, "InitRandom"), 0x1000: (0x1000, 8, "f")}
        g._arm_probes()
        self.assertEqual((g.res["coverage_armed"], g.res["coverage_shared"]), (1, ["0x233f82"]))
        self.assertEqual(g.bps[seed][0], b"\x55")                               # the harness's breakpoint untouched
        g._hit(1, seed)
        g._hit(1, seed)                                                         # kept: fires again, recorded once
        self.assertEqual(fired, [1, 1])
        rep = gs.coverage_report(g.probe_units, g.covered, g.probe_failed)
        self.assertEqual(rep["run"], [["0x233f82", 0x45, "InitRandom", 7]])
        self.assertEqual(rep["not_observed"], [])

    def test_a_harness_breakpoint_armed_later_on_a_probe_keeps_the_real_byte(self):
        va = self.BASE + 0x2000
        mem = {va: 0x55}
        g = self.game(mem)
        g.probe_units = {0x2000: (0x2000, 16, "g")}
        g._arm_probes()
        self.assertEqual(mem[va], 0xCC)
        self.assertIsNone(g._arm(va, lambda game, tid, ctx: False))             # a tick's arm()
        self.assertEqual(g.bps[va][0], b"\x55")                                 # never the probe's own int3
        g._hit(1, va)
        self.assertEqual((mem[va], g.covered), (0x55, [(1.0, 7, 0x2000)]))

    def test_a_probe_that_was_not_planted_is_not_counted_and_says_why(self):
        ok, bad = self.BASE + 0x1000, self.BASE + 0x3000
        g = self.game({ok: 0x8B}, unreadable={bad})
        g.probe_units = {0x1000: (0x1000, 8, "f"), 0x3000: (0x3000, 4, "h")}
        g._arm_probes()
        self.assertEqual((g.res["coverage_armed"], g.probe_failed), (1, {0x3000: "read failed"}))
        rep = gs.coverage_report(g.probe_units, g.covered, g.probe_failed)
        self.assertEqual((rep["units"], rep["units_observable"], rep["not_observed"]),
                         (2, 1, [["0x3000", 4, "h", "read failed"]]))

    def test_without_probes_arm_is_the_old_read_then_write(self):
        va = self.BASE + 0x1000
        mem = {va: 0x55}
        g = self.game(mem)
        h1, h2 = (lambda game, tid, ctx: True), (lambda game, tid, ctx: True)
        g._arm(va, h1)
        g._arm(va, h2)                                                          # re-reads, as it always did
        self.assertEqual((g.bps[va], g.probe_shared), ((b"\xCC", h2), set()))


class Stall(unittest.TestCase):
    """--stall-after: Game.stall_watch / stall_sample / thread_stacks over a fake game, and stall_report."""
    STACK = {"esp": 0x19F000, "ebp": 0x19F040, "regs": {"eip": "0x401234", "esp": "0x19f000"},
             "words": [0x401100, 7, 0x402200]}

    def game(self, frames, main=(22, 201), threads=None):
        g = gs.Game.__new__(gs.Game)
        g.res, g.watch, g.stall_after, g.t0, g.k, g.hproc = {}, None, 120.0, 0.0, object(), 9
        g.main_thread, g.threads, g.main_exited = main, threads or {}, False
        g.clock = 0.0
        g.seconds = lambda: g.clock
        it = iter(frames)
        g.logic = lambda: (next(it), 2)
        return g

    def drive(self, g, until):
        took = []
        for t in range(until + 1):
            g.clock = float(t)
            if g.stall_watch(float(t)):
                took.append(t)
        return took

    def test_a_run_that_progresses_is_never_sampled(self):                      # the old path
        g = self.game(iter([None] * 30 + list(range(10_000))))
        with mock.patch.object(gs.boot_smoke, "while_suspended", side_effect=AssertionError("suspended")), \
                mock.patch.object(gs.boot_smoke, "thread_eip", side_effect=AssertionError("suspended")):
            self.assertEqual(self.drive(g, 600), [])
        self.assertNotIn("stall", g.res)

    def test_no_new_frame_for_stall_after_gives_five_samples_three_seconds_apart(self):
        g = self.game(iter([None] * 10 + [0] * 10_000), threads={202: (33, 0x401500), 201: (22, 0x400000)})
        with mock.patch.object(gs.boot_smoke, "while_suspended", return_value=(dict(self.STACK), True)) as susp, \
                mock.patch.object(gs.boot_smoke, "thread_eip", return_value=0x7BC01234) as teip:
            took = self.drive(g, 300)
        self.assertEqual(took, [130, 133, 136, 139, 142])                       # frame 0 from 10 s; 120 s later
        st = g.res["stall"]
        self.assertEqual((st["trigger"]["seconds"], st["trigger"]["frame"], st["trigger"]["unchanged_since"]),
                         (130.0, 0, 10.0))
        self.assertEqual((len(st["samples"]), st["failures"], susp.call_count), (5, 0, 6))   # 5 main + 1 thread
        self.assertEqual(st["samples"][0]["eip"], 0x401234)
        self.assertEqual(st["threads"], [{"tid": 202, "start": 0x401500, "eip": 0x401234, "clean": True,
                                          "words": self.STACK["words"]}])                  # once, main left out
        self.assertEqual(teip.call_count, 0)

    def test_a_sample_that_could_not_suspend_is_a_counted_failure(self):
        g = self.game(iter([0] * 10_000))
        with mock.patch.object(gs.boot_smoke, "while_suspended", side_effect=[(None, False)] + [(dict(self.STACK), True)] * 4), \
                mock.patch.object(gs.boot_smoke, "thread_eip"):
            self.drive(g, 300)
        self.assertEqual((len(g.res["stall"]["samples"]), g.res["stall"]["failures"]), (4, 1))

    def test_without_a_main_thread_only_the_threads_are_read(self):
        g = self.game(iter([0] * 10_000), main=None, threads={202: (33, 0x401500)})
        with mock.patch.object(gs.boot_smoke, "while_suspended", return_value=(None, False)) as susp:
            self.assertEqual(self.drive(g, 300), [120])
        st = g.res["stall"]
        self.assertEqual((st["main_thread"], st["samples"], susp.call_count), (None, [], 1))     # the thread only
        self.assertEqual(st["threads"], [{"tid": 202, "start": 0x401500, "eip": None, "clean": False, "words": []}])
        self.assertIn("CREATE_PROCESS", st["main_thread_why"])

    def test_a_read_that_raises_is_a_recorded_failure_not_a_lost_run(self):
        g = self.game(iter([0] * 10_000), threads={202: (33, 0x401500), 203: (34, 0x401600)})
        with mock.patch.object(gs.boot_smoke, "while_suspended",
                               side_effect=[OSError("gone"), (dict(self.STACK), True),          # the two threads
                                            OSError("access denied")] + [(dict(self.STACK), True)] * 4):
            self.assertEqual(self.drive(g, 300), [120, 123, 126, 129, 132])
        st = g.res["stall"]
        self.assertEqual((len(st["samples"]), st["failures"]), (4, 1))
        self.assertIn("OSError: access denied", st["failure_reasons"][0])
        self.assertEqual([(t["tid"], t["eip"], t.get("error")) for t in st["threads"]],
                         [(202, None, "OSError: gone"), (203, 0x401234, None)])

    def test_other_threads_are_bounded_in_count(self):
        g = self.game(iter([0] * 10_000), threads={202: (33, 1), 203: (34, 2), 204: (35, 3)})
        with mock.patch.object(gs, "STALL_THREADS", 2), \
                mock.patch.object(gs.boot_smoke, "while_suspended", return_value=(dict(self.STACK), True)) as susp:
            self.drive(g, 125)
        st = g.res["stall"]
        self.assertEqual([t.get("skipped") for t in st["threads"]], [None, None, "past the thread bound"])
        self.assertEqual(susp.call_count, 2 + 2)                                # 2 threads, then main at 120 and 123

    def test_a_main_thread_that_exited_is_never_sampled_and_says_so(self):
        g = self.game(iter([0] * 10_000), main=None)
        g.main_exited = True
        with mock.patch.object(gs.boot_smoke, "while_suspended", side_effect=AssertionError("stale handle")), \
                mock.patch.object(gs.boot_smoke, "thread_eip"):
            self.assertEqual(self.drive(g, 300), [120])
        self.assertEqual((g.res["stall"]["samples"], g.res["stall"]["main_thread_why"]), ([], "main thread exited"))

    def test_a_main_thread_exiting_between_samples_stops_the_samples(self):
        g = self.game(iter([0] * 10_000))
        calls = []

        def sample(*a):
            calls.append(1)
            if len(calls) == 2:                                                 # its EXIT_THREAD arrives
                g.main_thread, g.main_exited = None, True
            return dict(self.STACK), True
        with mock.patch.object(gs.boot_smoke, "while_suspended", side_effect=sample), \
                mock.patch.object(gs.boot_smoke, "thread_eip"):
            self.drive(g, 300)
        self.assertEqual((len(g.res["stall"]["samples"]), g.res["stall"]["main_thread_why"]), (2, "main thread exited"))

    def test_a_thread_left_suspended_stops_the_run_s_evidence(self):
        g = self.game(iter([0] * 10_000))
        with mock.patch.object(gs.boot_smoke, "while_suspended", side_effect=gs.boot_smoke.ThreadNotResumed(5)), \
                mock.patch.object(gs.boot_smoke, "thread_eip"):
            with self.assertRaises(gs.boot_smoke.ThreadNotResumed):
                self.drive(g, 300)

    RAW = {"trigger": {"seconds": 130.0, "frame": 0, "stall_after": 120.0, "unchanged_since": 10.0},
           "main_thread": {"tid": 201}, "failures": 0,
           "threads": [{"tid": 202, "start": 0x2001500, "eip": 0x7BC01234, "clean": True, "words": [0x2002200, 5]}],
           "samples": [{"seconds": 130.0, "frame": 0, "clean": True, "eip": 0x2001234, "esp": 1, "ebp": 2, "regs": {},
                        "words": [0x2001100, 0x2002200]},
                       {"seconds": 133.0, "frame": 0, "clean": True, "eip": 0x2001240, "esp": 1, "ebp": 2, "regs": {},
                        "words": [0x2001180, 0x2002200]},
                       {"seconds": 136.0, "frame": 0, "clean": False, "eip": 0x2009999, "esp": 1, "ebp": 2, "regs": {},
                        "words": [0x2009000]}]}

    def report(self, **kw):
        lab = lambda va, loaded, ri, pieces: f"f{va - loaded:x}" if 0 <= va - loaded < 0x10000 else None  # noqa: E731
        frames = lambda words, loaded, ri, pieces, limit: [[hex(w), lab(w, loaded, ri, pieces)] for w in words  # noqa: E731
                                                           if lab(w, loaded, ri, pieces)]
        ri = SimpleNamespace(base=0x400000, img=SimpleNamespace(code=lambda rva: rva < 0x10000),
                             where=lambda va: {"retail_rva": hex(va - 0x400000 + 0x100)})
        with mock.patch.object(gs.boot_smoke, "address_label", side_effect=lab), \
                mock.patch.object(gs.boot_smoke, "image_frames", side_effect=frames):
            return gs.stall_report(self.RAW, 0x2000000, ri, where=lambda va: f"ntdll+{va & 0xFFF:#x}", **kw)

    def test_the_report_names_each_address_and_the_candidates_every_sample_holds(self):
        rep = self.report()
        s0 = rep["samples"][0]
        self.assertEqual((s0["eip"], s0["eip_label"], s0["eip_retail_rva"]), ("0x2001234", "f1234", "0x1334"))
        self.assertEqual(s0["scan_candidates"][1], ["0x2002200", "f2200", "0x2300"])
        self.assertNotIn("frames", s0)                                          # scan candidates, never "frames"
        self.assertIn("not a call chain", rep["method"])
        self.assertFalse(rep["eip_agree"])                                      # the two clean eips differ
        self.assertEqual(rep["common_scan_candidates"], [["0x2002200", "f2200", "0x2300"]])   # unclean left out
        self.assertEqual(rep["threads"][0]["eip_label"], "ntdll+0x234")         # outside the image
        self.assertEqual(rep["threads"][0]["scan_candidates"], [["0x2002200", "f2200", "0x2300"]])
        self.assertNotIn("words", rep["threads"][0])
        rec = gs.stall_receipt(rep)
        self.assertEqual((rec["samples"], rec["stall_after"], rec["eip_agree"], rec["eip"], rec["common_scan_candidates"]),
                         (2, 120.0, False, "f1234", ["f2200"]))

    def test_an_unsymbolized_section_still_gives_a_receipt(self):
        raw = dict(self.RAW, report_error="KeyError: 'x'")
        rec = gs.stall_receipt(raw)
        self.assertEqual((rec["samples"], rec["stall_after"], rec["report_error"]), (2, 120.0, "KeyError: 'x'"))

    def test_an_overlay_image_is_not_symbolized(self):
        rep = self.report(overlay=True)
        self.assertEqual((rep["samples"][0]["eip_label"], rep["samples"][0]["scan_candidates"],
                          rep["common_scan_candidates"]), (None, None, None))
        self.assertIn("overlay", rep["note"])

    def test_the_receipt_gains_a_stall_section_only_when_there_was_one(self):
        import io
        import json
        import tempfile
        from contextlib import redirect_stdout
        rep = self.report()
        with tempfile.TemporaryDirectory() as d, mock.patch.object(gs, "OUT", Path(d)), redirect_stdout(io.StringIO()):
            kept = json.loads(gs.write_result("skirmish", {"image": "real", "receipt": {}, "stall": rep}).read_text())
            plain = json.loads(gs.write_result("record", {"image": "real", "receipt": {}}).read_text())
        self.assertEqual(kept["receipt"]["stall"]["frame"], 0)
        self.assertEqual(plain, {"image": "real", "receipt": {}})


class MorePlayers(unittest.TestCase):
    def test_four_brutal_ais_and_no_fps_cap(self):
        info, glob = 0x6000000, 0x6400000
        g = FakeGame({0x400000 + gs.RVA["TheSkirmishGameInfo"]: info, 0x400000 + gs.RVA["TheGlobalData"]: glob})
        slots = [0x6100000 + 0x1000 * i for i in range(5)]
        for i, sl in enumerate(slots):
            g.mem[info + gs.SLOTS_OFF + 4 * i] = sl
            g.mem[sl + gs.SLOT_STATE] = 1
        gs.skirmish_setup(True, players=4, difficulty="brutal", fast=True)(g, 1, None)
        self.assertEqual([g.u32(sl + gs.SLOT_STATE) for sl in slots], [1, 5, 5, 5, 5])
        self.assertEqual(g.mem[("byte", glob + gs.USE_FPS_LIMIT_OFF)], 0)
        self.assertIn("slot 4 brutal AI", g.res["setup"]["players"])


class BlockDiff(unittest.TestCase):
    def test_first_differing_frame_per_block(self):
        a = [(25, {"objects": 1, "shroud": 7}), (50, {"objects": 2, "shroud": 8})]
        b = [(25, {"objects": 1, "shroud": 9}), (50, {"objects": 3, "shroud": 9})]
        self.assertEqual(gs.block_diff(a, b), {"shroud": 25, "objects": 50})
        self.assertEqual(gs.block_diff(a, a), {})

    def test_pre_and_post_byte_stores_wrap_the_call(self):
        code = gs.stub_code([{"call": 1, "ecx": 2, "pre": [(0xA02D7C, 1)], "post": [(0xA02D7C, 0)]}], 0x100)
        self.assertTrue(code.startswith(bytes.fromhex("C6057C2DA00001")))
        self.assertTrue(code.endswith(bytes.fromhex("C6057C2DA00000 CC")))


class Halving(unittest.TestCase):
    def test_finds_the_one_guilty_unit(self):
        guilty, steps = gs.halve(list(range(0, 160, 10)), lambda h: 70 in h)
        self.assertEqual(guilty, [70])
        self.assertLessEqual(len(steps), 8)                            # at most two runs per level

    def test_interaction_returns_the_remaining_set(self):
        guilty, _ = gs.halve([1, 2, 3, 4], lambda h: 1 in h and 4 in h)
        self.assertEqual(guilty, [1, 2, 3, 4])

    def test_queue_items_are_desync_repairs(self):
        rows = [{"target_rva": "0x00401000", "name": "f", "source": "Code/a.cpp", "target_size": "16"}]
        item = gs.desync_items(rows, "desync", "--overlay closed --relayout")[0]
        self.assertEqual((item["check"], item["size"]), ("desync", 16))
        self.assertIn("rva:0x00401000 --overlay closed --relayout", item["pass_test"])
        crash = gs.desync_items(rows, "crash-at-0x7", "--overlay closed --relayout --own-data")[0]
        self.assertEqual(crash["check"], "boot-crash")                   # an in-game crash is a crash repair


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
        glob = 0x6300000
        g.mem[0x400000 + gs.RVA["TheGlobalData"]] = glob
        g.mem[glob + gs.FIXED_SEED_OFF] = 0xFFFFFFFF                    # reset to -1 after parsing
        req = gs.skirmish_setup(True, seed=7)(g, 1, None)
        self.assertEqual((req["call"], req["args"]), (0x400000 + gs.RVA["InitRandom"], [7]))   # reseeds in-game
        self.assertEqual(g.u32(self.INFO + gs.SEED_OFF), 7)
        self.assertEqual(g.u32(glob + gs.FIXED_SEED_OFF), 7)
        self.assertEqual(g.res["setup"]["fixed_seed_before"], 0xFFFFFFFF)
        g2 = self.game()
        g2.mem[self.INFO + gs.SEED_OFF] = 1791300000
        gs.skirmish_setup(True)(g2, 1, None)                            # no seed: left alone
        self.assertEqual(g2.u32(self.INFO + gs.SEED_OFF), 1791300000)

    def slots3(self):
        g = self.game()
        slot0, slot2 = 0x6200000, 0x6300000
        g.mem[self.INFO + gs.SLOTS_OFF] = slot0
        g.mem[self.INFO + gs.SLOTS_OFF + 8] = slot2
        for sl in (slot0, self.SLOT1, slot2):
            g.mem[sl + gs.SLOT_TEMPLATE] = 0xFFFFFFFE                   # -2, observer
        g.mem[slot2 + gs.SLOT_STATE] = 1
        return g, slot0, slot2

    def test_default_is_an_observer_watching_two_random_ais(self):
        g, slot0, slot2 = self.slots3()
        gs.skirmish_setup(True)(g, 1, None)
        self.assertEqual(g.res["setup"]["templates_before"], [0xFFFFFFFE] * 3)
        self.assertEqual([g.u32(x + gs.SLOT_TEMPLATE) for x in (slot0, self.SLOT1, slot2)],
                         [0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF])       # local player cannot command
        self.assertEqual([g.u32(x + gs.SLOT_STATE) for x in (self.SLOT1, slot2)], [gs.SLOT_EASY_AI] * 2)

    def test_player_mode_gives_slot_zero_a_faction_and_one_ai(self):
        g, slot0, slot2 = self.slots3()
        gs.skirmish_setup(True, player=True)(g, 1, None)
        self.assertEqual([g.u32(x + gs.SLOT_TEMPLATE) for x in (slot0, self.SLOT1, slot2)],
                         [0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFE])
        self.assertEqual(g.u32(slot2 + gs.SLOT_STATE), 1)

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


class UntilFrame(unittest.TestCase):
    """--until-frame stops on the logic frame, not on time, and waits for that frame's CRC."""

    class Clock:
        def __init__(self, frames):
            self.frames, self.i, self.res = frames, -1, {}

        def logic(self):
            self.i += 1
            return self.frames[self.i], SKIRMISH

        def seconds(self):
            return 1000.0 * self.i                   # far past any --seconds

    def opts(self, until):
        from types import SimpleNamespace
        return SimpleNamespace(seconds=60, until_frame=until)

    def test_stops_at_the_frame_not_the_time(self):
        g = self.Clock([10, 4990, 5003])
        tick = gs.skirmish_tick(self.opts(5000), [], SKIRMISH)
        self.assertEqual([tick(g), tick(g), tick(g)], [None, None, "done"])

    def test_waits_for_the_crc_at_the_frame(self):
        g, hook = self.Clock([5001, 5002, 5003]), gs.FrameHook(every=25)
        tick = gs.skirmish_tick(self.opts(5000), [], SKIRMISH, hook)
        hook.crcs = [(4975, 1)]
        self.assertIsNone(tick(g))
        hook.crcs.append((5000, 2))
        self.assertEqual(tick(g), "done")

    def test_tick_records_the_frame_reached(self):
        a, g = self.opts(5000), self.Clock([10, 4990])
        tick = gs.skirmish_tick(a, [], SKIRMISH)
        tick(g), tick(g)
        self.assertEqual(a.reached, 4990)

    def finished(self, name, reached, crcs, outcome="pass"):
        import tempfile
        from types import SimpleNamespace
        from unittest import mock
        a = SimpleNamespace(retail=True, image="boot", until_frame=5000, reached=reached, scenario=name)
        out = {"run": {}, "profile_touched": False, "guard": {}, "outcome": outcome, "crcs": crcs}
        with tempfile.TemporaryDirectory() as d, mock.patch.object(gs, "OUT", Path(d)), \
                mock.patch("builtins.print"):
            rc = gs.finish(a, name, out)
        return rc, out["outcome"]

    def test_a_pass_short_of_the_frame_fails(self):                 # review finding 6
        crcs = [(f, f) for f in range(25, 201, 25)]
        self.assertEqual(self.finished("record", 200, crcs), (1, "short-of-frame"))
        self.assertEqual(self.finished("skirmish", 4990, None), (1, "short-of-frame"))
        self.assertEqual(self.finished("determinism", None, None), (1, "short-of-frame"))

    def test_the_frame_without_its_crc_fails(self):
        crcs = [(f, f) for f in range(25, 4976, 25)]
        self.assertEqual(self.finished("record", 5003, crcs), (1, "short-of-frame"))
        self.assertEqual(self.finished("record", 5003, crcs + [(5000, 1)]), (0, "pass"))

    def test_a_failure_keeps_its_own_outcome(self):
        self.assertEqual(self.finished("determinism", 200, [(25, 1)], "desync"), (1, "desync"))

    def test_without_it_seconds_still_rule(self):
        g = self.Clock([10, 20])
        tick = gs.skirmish_tick(self.opts(None), [], SKIRMISH)
        self.assertEqual([tick(g), tick(g)], [None, "done"])


class FaultWords(unittest.TestCase):
    """--fault-words sizes the stack window a fault keeps (P153 needed a crashing function's own arguments)."""

    def test_range(self):
        self.assertEqual(gs.fault_words_arg("1024"), 1024)
        self.assertEqual(gs.fault_words_arg("0x400"), 1024)
        for bad in ("0", "4097"):
            with self.assertRaises(argparse.ArgumentTypeError):
                gs.fault_words_arg(bad)

    def test_capture_uses_the_runs_window(self):
        game = SimpleNamespace(k=None, hproc=None, fault_words=1024)
        with mock.patch.object(gs.boot_smoke, "fault_capture", return_value={"words": [1, 2], "esp": 4}) as cap:
            res = {}
            gs.Game.capture_fault(game, 7, res)
            cap.assert_called_once_with(None, None, 7, 1024)
            gs.Game.capture_fault(game, 7, res, n=16)
            self.assertEqual(cap.call_args[0][3], 16)
        self.assertEqual(res["fault_words"], [1, 2])
        self.assertEqual(gs.FAULT_WORDS, 256)


if __name__ == "__main__":
    unittest.main()


class OneBase(unittest.TestCase):
    """Overlay boots hit the same Mesa failure at the old base: every default comes from one definition."""

    @staticmethod
    def base_default(main, argv):
        seen = []
        add = argparse.ArgumentParser.add_argument

        def spy(self, *names, **options):
            if "--base" in names:
                seen.append(options["default"])
            return add(self, *names, **options)

        def stop(self, *a, **k):
            raise SystemExit(0)

        with mock.patch.object(argparse.ArgumentParser, "add_argument", spy), \
                mock.patch.object(argparse.ArgumentParser, "parse_args", stop):
            try:
                main(argv)
            except SystemExit:
                pass
        return seen

    def test_every_overlay_default_is_the_image_base(self):
        import inspect
        import boot_image
        import boot_relayout
        import boot_smoke
        import exit_link
        import real_image
        self.assertEqual(real_image.IMAGE_BASE, 0x2000000)
        self.assertEqual(exit_link.BASE, real_image.IMAGE_BASE)
        for build_image in (boot_image.build_image, boot_relayout.build_image):
            self.assertEqual(inspect.signature(build_image).parameters["base"].default, real_image.IMAGE_BASE)
        for main in (boot_image.main, boot_smoke.main, gs.main):
            self.assertEqual(self.base_default(main, []), [real_image.IMAGE_BASE], main.__module__)

    def test_where_names_an_address_at_the_new_base(self):
        import real_image
        base = real_image.IMAGE_BASE
        game = SimpleNamespace(base=base, size=0x1000, dlls=[])
        self.assertEqual(gs.Game.where(game, base + 0x234), "image+0x234")


class NewSaves(unittest.TestCase):
    """The autosave's name is fixed: in a profile with an earlier save, reload found nothing new and never loaded."""

    def setUp(self):
        import tempfile
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.appdata = Path(self.tmp.name)
        self.saves = gs.sandbox_profile(self.appdata) / "Save"
        self.saves.mkdir(parents=True)

    def write(self, name, text, when=None):
        import os
        path = self.saves / name
        path.write_text(text)
        if when:
            os.utime(path, (when, when))
        return path

    def names(self, before):
        return [q.name for q in gs.new_saves(self.appdata, before)]

    def test_nothing_written_is_nothing_new(self):
        self.write("Auto Save for Udun.BfME2Skirmish", "old", 1000)
        self.assertEqual(self.names(gs.saves_state(self.appdata)), [])

    def test_a_new_name_is_new(self):
        before = gs.saves_state(self.appdata)
        self.write("other.BfME2Skirmish", "new")
        self.assertEqual(self.names(before), ["other.BfME2Skirmish"])

    def test_the_fixed_name_rewritten_is_new(self):
        self.write("Auto Save for Udun.BfME2Skirmish", "old", 1000)
        before = gs.saves_state(self.appdata)
        self.write("Auto Save for Udun.BfME2Skirmish", "old", 2000)       # same size, later
        self.assertEqual(self.names(before), ["Auto Save for Udun.BfME2Skirmish"])

    def test_the_fixed_name_at_another_size_is_new(self):
        self.write("Auto Save for Udun.BfME2Skirmish", "old", 1000)
        before = gs.saves_state(self.appdata)
        self.write("Auto Save for Udun.BfME2Skirmish", "longer", 1000)    # same time, larger
        self.assertEqual(self.names(before), ["Auto Save for Udun.BfME2Skirmish"])

    def test_an_old_neighbour_is_not_new(self):
        self.write("map mp tournament udun.map", "keep", 1000)
        before = gs.saves_state(self.appdata)
        self.write("Auto Save for Udun.BfME2Skirmish", "new")
        self.assertEqual(self.names(before), ["Auto Save for Udun.BfME2Skirmish"])


# --------------------------------------------------------------------------- G4/G5: the suite judge
def run_file(folder, name, crcs, retail=True, seed=1, perturb=None, at=None, outcome="pass", until=100, kind="determinism",
             setup=None, **extra):
    """A record/reload/load result file as finish() writes one, with only what the suite judge reads."""
    import json
    scenario = {"kind": kind, "map": "maps\\m.map", "seed": seed, "players": 2, "player": False, "ai": True,
                "difficulty": "easy", "fast": False, "mode": 2, "crc_every": 25, "until_frame": until,
                **extra, "perturb_frame": perturb}
    body = {"scenario": scenario, "outcome": outcome, "crcs": [[f, c] for f, c in crcs.items()],
            "perturbed": {"frame": at} if at is not None else None,
            "run": {"setup": setup or {"seed": seed, "players": "slot 0 observer, slot 1 easy AI, slot 2 easy AI"}},
            "receipt": {"image_kind": "retail" if retail else "real", "image_sha256": "r" if retail else "i"}}
    path = Path(folder) / f"{name}.json"
    path.write_text(json.dumps(body))
    return path


SAME = {25: 1, 50: 2, 75: 3, 100: 4}


class SuiteJudge(unittest.TestCase):
    """G4/G5: a scenario's bar is what two retail runs repeat; every other run is held to it."""

    def setUp(self):
        import tempfile
        self.dir = tempfile.TemporaryDirectory()
        self.addCleanup(self.dir.cleanup)
        self.d = Path(self.dir.name)

    def judge(self, *paths, bar=None, target=None):
        return gs.judge_suite([gs.suite_run(q) for q in paths], bar, target)

    def base(self):
        return [run_file(self.d, "a", SAME), run_file(self.d, "b", SAME),
                run_file(self.d, "p", {25: 1, 50: 2, 75: 9, 100: 9}, perturb=60, at=62)]

    def only_group(self, out):
        (g,) = out["groups"].values()
        return g

    def test_retail_twice_and_a_caught_perturbation_pass(self):
        out = self.judge(*self.base())
        g = self.only_group(out)
        self.assertEqual((out["verdict"], g["retail_repeat"], g["bar"]["through"], g["bar"]["frames"]),
                         ("pass", "repeats", 100, 4))
        self.assertEqual(g["judged"][0]["verdict"], "caught-at-75")
        self.assertEqual(out["reductions"], [])

    def test_without_a_perturbed_run_there_is_no_negative_control(self):
        out = self.judge(*self.base()[:2])
        self.assertEqual(out["verdict"], "fail")
        self.assertIn("no perturbed run was caught: the suite has no negative control", out["problems"])

    def test_a_perturbation_that_changes_nothing_is_missed(self):
        out = self.judge(*self.base()[:2], run_file(self.d, "p", SAME, perturb=60, at=62))
        self.assertEqual((out["verdict"], self.only_group(out)["judged"][0]["verdict"]), ("fail", "missed"))

    def test_a_difference_before_the_perturbation_is_not_a_catch(self):
        out = self.judge(*self.base()[:2], run_file(self.d, "p", {25: 1, 50: 7, 75: 9, 100: 9}, perturb=60, at=62))
        self.assertEqual(self.only_group(out)["judged"][0]["verdict"], "differs-before-perturbation-at-50")
        self.assertEqual(out["verdict"], "fail")

    def test_a_perturbed_run_that_never_perturbed_is_no_control(self):
        out = self.judge(*self.base()[:2], run_file(self.d, "p", {25: 1, 50: 2, 75: 9, 100: 9}, perturb=60))
        self.assertEqual(self.only_group(out)["judged"][0]["verdict"], "not-perturbed")

    def test_every_scheduled_sample_must_be_there(self):
        hole = {25: 1, 50: 2, 100: 4}
        out = self.judge(run_file(self.d, "a", SAME), run_file(self.d, "b", hole),
                         run_file(self.d, "p", {25: 1, 50: 2, 75: 9, 100: 9}, perturb=60, at=62))
        self.assertEqual(out["verdict"], "fail")                  # one complete retail run: no bar
        self.assertEqual(self.only_group(out)["verdict"], "no-bar")
        out = self.judge(*self.base(), run_file(self.d, "i", hole, retail=False))
        self.assertIn("incomplete-from-75", [j["verdict"] for j in self.only_group(out)["judged"]])
        self.assertEqual(out["verdict"], "fail")

    def test_an_image_that_differs_fails_at_its_first_frame(self):
        out = self.judge(*self.base(), run_file(self.d, "i", {25: 1, 50: 5, 75: 3, 100: 4}, retail=False))
        self.assertIn("differs-at-50", [j["verdict"] for j in self.only_group(out)["judged"]])
        self.assertEqual((out["verdict"], self.only_group(out)["verdict"]), ("fail", "fail"))

    def test_an_image_that_matches_passes(self):
        out = self.judge(*self.base(), run_file(self.d, "i", SAME, retail=False))
        self.assertEqual(out["verdict"], "pass")

    def test_metadata_the_run_had_must_match(self):
        other = {"seed": 1, "players": "slot 0 observer, slot 1 easy AI"}
        out = self.judge(*self.base(), run_file(self.d, "i", SAME, retail=False, setup=other))
        self.assertIn("metadata-differs", [j["verdict"] for j in self.only_group(out)["judged"]])

    def test_a_run_that_did_not_pass_is_not_judged_a_match(self):
        out = self.judge(*self.base(), run_file(self.d, "i", SAME, retail=False, outcome="crash-at-x"))
        self.assertIn("run-crash-at-x", [j["verdict"] for j in self.only_group(out)["judged"]])

    def test_retail_differing_from_itself_shortens_the_bar_and_says_so(self):
        out = self.judge(run_file(self.d, "a", SAME), run_file(self.d, "b", {25: 1, 50: 2, 75: 8, 100: 4}),
                         run_file(self.d, "p", {25: 1, 50: 9, 75: 3, 100: 4}, perturb=40, at=40),
                         run_file(self.d, "i", {25: 1, 50: 2, 75: 0, 100: 0}, retail=False))
        g = self.only_group(out)
        self.assertEqual((g["bar"]["through"], g["retail_repeat"]), (50, "differs-at-75"))
        self.assertIn("retail differs from itself at frame 75", g["bar"]["reduction"])
        self.assertEqual(out["verdict"], "pass")                  # held to the frames retail repeats
        self.assertTrue(any("differs from itself" in r for r in out["reductions"]))

    def test_a_run_is_held_to_the_whole_schedule_even_where_the_bar_is_short(self):
        # Sol A1: completeness was checked over the bar's frames only, so a hole past a short bar passed.
        out = self.judge(run_file(self.d, "a", SAME), run_file(self.d, "b", {25: 1, 50: 2, 75: 8, 100: 4}),
                         run_file(self.d, "p", {25: 1, 50: 9, 75: 3, 100: 4}, perturb=40, at=40),
                         run_file(self.d, "i", {25: 1, 50: 2, 75: 0}, retail=False))
        self.assertEqual(self.only_group(out)["bar"]["through"], 50)
        self.assertIn("incomplete-from-100", [j["verdict"] for j in self.only_group(out)["judged"]])
        self.assertEqual(out["verdict"], "fail")

    def test_a_retail_run_whose_setup_is_not_its_scenario_s_sets_no_bar(self):
        # Sol A2: references were never checked against the setup they ran.
        two_ais = {"seed": 1, "players": "slot 0 observer, slot 1 easy AI"}
        out = self.judge(run_file(self.d, "a", SAME), run_file(self.d, "b", SAME, setup=two_ais),
                         run_file(self.d, "p", {25: 1, 50: 2, 75: 9, 100: 9}, perturb=60, at=62))
        self.assertEqual(self.only_group(out)["verdict"], "no-bar")
        self.assertTrue(any("ran {'seed': 1, 'players': 'slot 0 observer, slot 1 easy AI', 'fps_limit': None}" in q
                            for q in out["problems"]))
        self.assertEqual(out["verdict"], "fail")

    def test_an_explicit_bar_holds_today_s_retail_runs_too(self):
        # Sol A4: two retail runs that agree with each other replaced the bar given; they must be judged by it.
        bar = self.judge(*self.base())
        drifted = {25: 1, 50: 2, 75: 3, 100: 5}
        out = self.judge(run_file(self.d, "a2", drifted), run_file(self.d, "b2", drifted),
                         run_file(self.d, "p2", {25: 1, 50: 2, 75: 9, 100: 9}, perturb=60, at=62), bar=bar)
        self.assertEqual([j["verdict"] for j in self.only_group(out)["judged"]][:2], ["differs-at-100", "differs-at-100"])
        self.assertEqual(out["verdict"], "fail")
        out = self.judge(run_file(self.d, "s2", SAME, seed=2), bar=bar)
        self.assertIn("not in the bar given", " ".join(out["problems"]))

    def loads(self, name, setup, crcs=None, retail=True, perturb=None, at=None):
        return run_file(self.d, name, crcs or {150: 5, 175: 6}, retail=retail, perturb=perturb, at=at, kind="load",
                        until=175, saved_frame=125, save_sha256="s", setup=setup)

    def test_two_retail_loads_that_agree_set_a_bar_and_one_that_does_not_is_reported(self):
        # Sol A5: a load records no skirmish set-up, so A2's check left loads without a bar.
        state = {"loaded_frame": 125, "base_seed": 7}
        out = self.judge(self.loads("a", state), self.loads("b", state), self.loads("c", {"loaded_frame": 125, "base_seed": 8}),
                         self.loads("i", state, retail=False), self.loads("p", state, {150: 5, 175: 9}, perturb=160, at=161))
        g = self.only_group(out)
        self.assertEqual((g["bar"]["through"], g["expected_setup"]), (175, state))
        self.assertTrue(any("retail run" in q and "'base_seed': 8" in q for q in out["problems"]))
        verdicts = {Path(j["file"]).stem: j["verdict"] for j in g["judged"]}
        self.assertEqual((verdicts["i"], verdicts["p"], verdicts["c"]), ("matches", "caught-at-175", "metadata-differs"))
        bar = self.judge(self.loads("a", state), self.loads("b", state), self.loads("p", state, {150: 5, 175: 9}, perturb=160, at=161))
        out = self.judge(self.loads("i2", {"loaded_frame": 125, "base_seed": 9}, retail=False), bar=bar)
        self.assertEqual(self.only_group(out)["judged"][0]["verdict"], "metadata-differs")
        out = self.judge(self.loads("i3", state, retail=False), bar=bar)
        self.assertEqual(self.only_group(out)["judged"][0]["verdict"], "matches")

    def test_a_load_that_did_not_resume_at_its_save_sets_no_bar(self):
        early = {"loaded_frame": 3, "base_seed": 7}
        out = self.judge(self.loads("a", early), self.loads("b", early), self.loads("p", early, {150: 5, 175: 9}, perturb=160, at=161))
        self.assertEqual(self.only_group(out)["verdict"], "no-bar")

    def test_scenarios_are_judged_apart(self):
        out = self.judge(*self.base(), run_file(self.d, "s2", SAME, seed=2))
        self.assertEqual(len(out["groups"]), 2)
        self.assertIn("1 complete retail run(s), no bar given", " ".join(out["problems"]))

    def test_a_bar_from_an_earlier_suite_judges_image_runs_alone(self):
        bar = self.judge(*self.base())
        out = self.judge(run_file(self.d, "i", SAME, retail=False),
                         run_file(self.d, "ip", {25: 1, 50: 2, 75: 0, 100: 0}, retail=False, perturb=60, at=60), bar=bar)
        self.assertEqual(out["verdict"], "pass")
        out = self.judge(run_file(self.d, "i", {25: 1, 50: 2, 75: 3, 100: 0}, retail=False), bar=bar)
        self.assertIn("differs-at-100", [j["verdict"] for j in self.only_group(out)["judged"]])
        out = self.judge(run_file(self.d, "s2", SAME, seed=2, retail=False), bar=bar)
        self.assertTrue(any("in the bar, not run" in q for q in out["problems"]))

    def test_an_unscheduled_run_is_a_problem(self):
        out = self.judge(run_file(self.d, "a", SAME, until=None))
        self.assertEqual(self.only_group(out)["verdict"], "unscheduled")
        self.assertEqual(out["verdict"], "fail")

    def test_the_target_reports_what_the_bar_does_not_cover(self):
        out = self.judge(*self.base(), target={"maps": 3, "seeds": 5, "until": 5000})
        self.assertEqual(out["verdict"], "pass")
        self.assertIn("1 map(s) x 1 seed(s) with a bar, target 3 x 5", out["reductions"])
        self.assertIn("bars end at [100], target frame 5000", out["reductions"])

    def test_reload_and_load_are_scheduled_after_the_load(self):
        self.assertEqual(gs.suite_schedule({"kind": "reload", "save_frame": 125, "crc_every": 25, "until_frame": 200}),
                         [150, 175, 200])
        self.assertEqual(gs.suite_schedule({"kind": "load", "saved_frame": 125, "crc_every": 25, "until_frame": 175}),
                         [150, 175])
        self.assertEqual(gs.suite_schedule({"kind": "determinism", "crc_every": 25, "until_frame": 75}), [25, 50, 75])
        self.assertIsNone(gs.suite_schedule({"kind": "load", "saved_frame": None, "crc_every": 25, "until_frame": 75}))

    def test_a_load_of_another_save_is_another_scenario(self):
        one = run_file(self.d, "a", {150: 1}, kind="load", until=150, saved_frame=125, save_sha256="x")
        two = run_file(self.d, "b", {150: 1}, kind="load", until=150, saved_frame=125, save_sha256="y")
        self.assertEqual(len(self.judge(one, two)["groups"]), 2)

    def test_the_command_reads_job_folders_and_skips_other_files(self):
        import contextlib
        import io
        import json
        self.base()
        (self.d / "receipt.json").write_text("{}")
        (self.d / "skirmish_retail.json").write_text(json.dumps({"outcome": "pass"}))
        out = io.StringIO()
        with contextlib.redirect_stdout(out):
            rc = gs.main(["suite", str(self.d), "--target", "1x1x100", "--out", str(self.d / "verdict.out")])
        verdict = json.loads(out.getvalue())
        self.assertEqual((rc, verdict["verdict"]), (0, "pass"))
        self.assertEqual(verdict["not_scenario_runs"], [str(self.d / "skirmish_retail.json")])
        self.assertEqual(json.loads((self.d / "verdict.out").read_text())["verdict"], "pass")


class Perturbation(unittest.TestCase):
    """Sol A3: the seed is xored at the frame breakpoint, labelled with the frame read there; a reload waits for its
    loaded state."""

    class FrameGame(FakeGame):
        def __init__(self):
            super().__init__({FakeGame.base + gs.RVA["theGameLogicSeed"]: 0x1234})
            self.frame = 0

        def logic(self):
            return self.frame, 2

        def seed(self):
            return self.mem[self.va("theGameLogicSeed")]

    def step(self, hook, game, frame):
        game.frame = frame
        return hook(game, 1, None)

    def test_the_seed_changes_at_the_first_frame_at_or_past_it_and_says_which(self):
        hook, game = gs.FrameHook(), self.FrameGame()
        hook.perturb_at = 60
        self.step(hook, game, 59)
        self.assertEqual((hook.perturbed, game.seed()), ({}, 0x1234))
        self.step(hook, game, 62)
        self.assertEqual(hook.perturbed, {"frame": 62, "seed_before": "0x1234"})
        self.assertEqual(game.seed(), 0x1234 ^ 0x5A5A5A5A)
        self.step(hook, game, 63)
        self.assertEqual(game.seed(), 0x1234 ^ 0x5A5A5A5A)        # once

    def test_a_reload_is_perturbed_only_in_its_loaded_state(self):
        hook, game = gs.FrameHook(), self.FrameGame()
        hook.perturb_at, hook.load_at = 150, 175
        hook.save, hook.load_name = {"frame": 125, "code": 0}, "x"
        hook.load = {"from_frame": 175, "code": 0}                 # loaded, but no CRC of the loaded state yet
        self.step(hook, game, 176)                                 # an engine frame still showing the old frame
        self.assertEqual(hook.perturbed, {})
        hook.load["first_crc"] = (126, 7)
        self.step(hook, game, 150)
        self.assertEqual(hook.perturbed["frame"], 150)


class LoadSetup(unittest.TestCase):
    """Sol A5: cmd_load records the loaded state's setup (a mocked launch, as Sol reproduced it)."""

    def test_a_load_records_the_frame_it_resumed_at_and_its_base_seed(self):
        import tempfile
        with tempfile.TemporaryDirectory() as d:
            d = Path(d)
            (d / "game").mkdir()
            (d / "game" / "smoke.BfME2Skirmish").write_bytes(b"save")
            a = SimpleNamespace(save=None, saved_frame=125, crc_every=25, mode=2, appdata=d / "appdata", game_dir=d / "game",
                                save_name="smoke.BfME2Skirmish", perturb_frame=None, retail=True, image="boot",
                                min_frames=100, until_frame=None, seconds=60, scenario="load")

            def launch(a_, extra, handlers, tick):
                hook = dict(handlers)["GameEngine::update"]
                hook.crcs, hook.rng = [(125, 1), (150, 2)], [(125, "aa", 7), (150, "bb", 7)]
                return None, {"run": {}, "profile_touched": False, "guard": {}}
            with mock.patch.object(gs, "launch", launch), mock.patch.object(gs, "OUT", d), mock.patch("builtins.print"):
                gs.cmd_load(a)
            import json
            kept = json.loads((d / "load_retail.json").read_text())
        self.assertEqual(kept["run"]["setup"], {"loaded_frame": 125, "base_seed": 7})
        self.assertEqual(kept["scenario"]["kind"], "load")
        self.assertEqual(gs.loaded_setup(gs.FrameHook()), {"loaded_frame": None, "base_seed": None})


class ScenarioBlock(unittest.TestCase):
    def args(self, **kw):
        base = dict(map="maps\\m.map", seed=3, players=2, player=False, no_ai=False, difficulty="easy", fast=False,
                    mode=2, crc_every=25, until_frame=500, perturb_frame=None, save_frame=125, load_frame=175)
        return SimpleNamespace(**(base | kw))

    def test_record_and_its_perturbed_twin_share_a_key(self):
        a = gs.scenario_of(self.args(), "record")
        b = gs.scenario_of(self.args(perturb_frame=300), "record_perturbed")
        self.assertEqual((a["kind"], b["perturb_frame"]), ("determinism", 300))
        self.assertEqual(gs.suite_key(a), gs.suite_key(b))
        self.assertIsNone(gs.scenario_of(self.args(), "skirmish"))

    def test_finish_writes_it_into_the_result(self):
        import json
        import tempfile
        a = self.args(retail=True, image="boot", scenario="record")
        out = {"run": {}, "profile_touched": False, "guard": {}, "outcome": "pass", "crcs": [(25, 1)]}
        with tempfile.TemporaryDirectory() as d, mock.patch.object(gs, "OUT", Path(d)), mock.patch("builtins.print"):
            gs.finish(a, "record", out)
            kept = json.loads((Path(d) / "record_retail.json").read_text())
        self.assertEqual(kept["scenario"], gs.scenario_of(a, "record"))
        self.assertEqual(kept["scenario"]["seed"], 3)

    def test_the_setup_a_scenario_implies(self):
        sc = gs.scenario_of(self.args(), "record")
        self.assertEqual(gs.expected_setup(sc), {"seed": 3, "players": "slot 0 observer, slot 1 easy AI, slot 2 easy AI",
                                                 "fps_limit": None})
        sc = gs.scenario_of(self.args(player=True, fast=True, difficulty="hard"), "reload")
        self.assertEqual(gs.expected_setup(sc), {"seed": 3, "players": "slot 0 player, slot 1 hard AI", "fps_limit": "off"})
        self.assertEqual(gs.expected_setup(gs.scenario_of(self.args(no_ai=True), "record"))["players"], "slot 0 observer, ")

    def test_reload_and_load_carry_what_decides_their_simulation(self):
        r = gs.scenario_of(self.args(), "reload")
        self.assertEqual((r["kind"], r["save_frame"], r["load_frame"]), ("reload", 125, 175))
        a = self.args()
        a.loaded_save = {"sha256": "abc", "frame": 125}
        s = gs.scenario_of(a, "load_perturbed")
        self.assertEqual((s["kind"], s["saved_frame"], s["save_sha256"]), ("load", 125, "abc"))

