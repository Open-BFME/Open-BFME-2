"""Host-only debug-event failure injection for boot_smoke.run; no game is launched."""

import ctypes
import sys
import unittest
from pathlib import Path
from types import SimpleNamespace
from unittest import mock


ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import boot_smoke as runner


def debug_event(code, *, pid=200, tid=201, file_handle=0, process_handle=21,
                thread_handle=22, exception=0, first_chance=0, exit_code=0):
    raw = bytearray(256)

    def put(offset, value, width=4):
        raw[offset:offset + width] = value.to_bytes(width, "little")

    put(0, code)
    put(4, pid)
    put(8, tid)
    if code == runner.CREATE_PROCESS:
        put(16, file_handle, 8)
        put(24, process_handle, 8)
        put(32, thread_handle, 8)
        put(40, 0x400000, 8)
    elif code == runner.EXCEPTION:
        put(16, exception)
        put(32, 0x401000, 8)
        put(168, first_chance)
    elif code == runner.EXIT_PROCESS:
        put(16, exit_code)
    return bytes(raw)


class FakeClock:
    def __init__(self):
        self.now = 0.0

    def time(self):
        return self.now

    def monotonic(self):
        return self.now


class FakeUser:
    def __init__(self):
        self.ShowWindowAsync = lambda *args: 1


class FakeKernel:
    def __init__(self, clock, events, *, fail_continue=False, fail_close=None,
                 wait_error=False, fail_terminate=False, wait_result=0, game_wait_result=0,
                 fail_duplicate=False, emit_exit=True):
        self.clock = clock
        self.events = list(events)
        self.fail_continue = fail_continue
        self.fail_close = fail_close
        self.wait_error = wait_error
        self.fail_terminate = fail_terminate
        self.wait_result = wait_result
        self.game_wait_result = game_wait_result
        self.fail_duplicate = fail_duplicate
        self.emit_exit = emit_exit
        self.last_error = 0
        self.delivered = []
        self.continued = []
        self.closed = []
        self.terminated = []
        self.waited = []
        self.duplicated = []
        self.calls = []
        self.QueryFullProcessImageNameW = lambda *args: self.query_image(*args)

    def get_last_error(self):
        return self.last_error

    def CreateProcessW(self, application, command, process_security, thread_security,
                       inherit, flags, environment, directory, startup, info):
        assert flags == runner.DEBUG_PROCESS and not inherit
        info._obj.hProcess = 11
        info._obj.hThread = 12
        info._obj.pid = 100
        info._obj.tid = 101
        return 1

    def query_image(self, handle, flags, buffer, count):
        assert handle in (21, 23)
        buffer.value = "game.dat"
        count._obj.value = len(buffer.value)
        return 1

    def GetCurrentProcess(self):
        return ctypes.c_void_p(-1).value

    def DuplicateHandle(self, source_process, source_handle, target_process, target_handle,
                        access, inherit, options):
        assert source_process == target_process == ctypes.c_void_p(-1).value
        assert (access, inherit, options) == (0, False, 0x2)
        self.duplicated.append(source_handle.value)
        if self.fail_duplicate:
            self.last_error = 6
            return 0
        target_handle._obj.value = 41
        return 1

    def WaitForDebugEvent(self, output, milliseconds):
        if self.events and not self.wait_error:
            raw = self.events.pop(0)
            ctypes.memmove(output, raw, len(raw))
            self.delivered.append(raw)
            return 1
        self.clock.now += milliseconds / 1000
        self.last_error = 5 if self.wait_error else 121
        return 0

    def ContinueDebugEvent(self, pid, tid, status):
        self.continued.append((pid, tid, status))
        self.calls.append(("continue", pid))
        if self.fail_continue and len(self.continued) == 2:
            self.last_error = 5
            return 0
        return 1

    def CloseHandle(self, handle):
        value = handle.value if hasattr(handle, "value") else handle
        self.closed.append(value)
        if value == self.fail_close:
            self.last_error = 6
            return 0
        return 1

    def TerminateProcess(self, handle, exit_code):
        value = handle.value if hasattr(handle, "value") else handle
        self.terminated.append(value)
        self.calls.append(("terminate", value))
        if self.fail_terminate and value == 11:
            self.last_error = 5
            return 0
        pid, tid = {11: (100, 101), 21: (200, 201), 23: (300, 301)}[value]
        if self.emit_exit:
            self.events.append(debug_event(runner.EXIT_PROCESS, pid=pid, tid=tid, exit_code=1))
        return 1

    def WaitForSingleObject(self, handle, milliseconds):
        self.waited.append((handle.value, milliseconds))
        self.calls.append(("wait", handle.value))
        return self.game_wait_result if handle.value == 41 else self.wait_result


class RunnerDebugTests(unittest.TestCase):
    def test_kernel_bindings_use_checked_return_types(self):
        exports = type("Exports", (), {})()
        for name in ("WaitForDebugEvent", "ContinueDebugEvent", "CloseHandle",
                     "TerminateProcess", "WaitForSingleObject", "CreateProcessW",
                     "GetCurrentProcess", "DuplicateHandle"):
            setattr(exports, name, lambda *args: 1)
        with mock.patch.object(runner.ctypes, "WinDLL", return_value=exports, create=True):
            kernel = runner.k32()
        for name in ("WaitForDebugEvent", "ContinueDebugEvent", "CloseHandle",
                     "TerminateProcess", "CreateProcessW", "DuplicateHandle"):
            self.assertIs(getattr(kernel, name).restype, runner.wt.BOOL)
        self.assertIs(kernel.WaitForSingleObject.restype, runner.wt.DWORD)
        self.assertIs(kernel.GetCurrentProcess.restype, runner.wt.HANDLE)

    def run_case(self, events, **failures):
        clock = FakeClock()
        kernel = FakeKernel(clock, events, **failures)
        with (mock.patch.object(runner, "k32", return_value=kernel),
              mock.patch.object(runner.ctypes, "WinDLL", return_value=FakeUser(), create=True),
              mock.patch.object(runner.ctypes, "get_last_error", side_effect=kernel.get_last_error, create=True),
              mock.patch.object(runner, "time", clock),
              mock.patch.object(runner, "sample_eips", return_value=[]),
              mock.patch.object(runner, "windows_of", return_value=[]),
              mock.patch.object(runner, "window_texts", return_value=[]),
              mock.patch.object(runner, "main_stack", return_value=None),
              mock.patch.object(runner, "screenshot", return_value=None),
              mock.patch.object(runner, "stack_words", return_value=None)):
            result = runner.run(Path("launcher.exe"), Path("/mock-game"), "-win", 2,
                                version_lie=False, appdata=Path("/mock-sandbox-appdata"))
        return kernel, result

    def test_normal_exit_requires_continuation_and_bounded_cleanup(self):
        kernel, result = self.run_case([debug_event(3, file_handle=31), debug_event(5, exit_code=0)])
        self.assertEqual((result["outcome"], result["pid"], result["image_base"]),
                         ("exit", 200, 0x400000))
        self.assertEqual(result["exit_code"], 0)
        self.assertEqual(kernel.continued, [(200, 201, runner.DBG_CONTINUE)] * 2 +
                         [(100, 101, runner.DBG_CONTINUE)])
        self.assertEqual(kernel.terminated, [11])
        self.assertEqual(result["cleanup"]["exit_events"], [100])
        self.assertEqual(kernel.closed.count(31), 1)
        self.assertEqual(kernel.duplicated, [21])
        self.assertEqual([handle for handle, _ in kernel.waited], [11, 41])
        self.assertLessEqual(kernel.waited[1][1], 5000)
        self.assertGreater(kernel.calls.index(("wait", 41)), kernel.calls.index(("continue", 200), 1))
        self.assertEqual(kernel.closed.count(41), 1)
        self.assertIn("game-process", result["cleanup"]["close"])
        self.assertEqual(result["debugger_errors"], [])

    def test_failed_game_handle_duplication_refuses_exit(self):
        kernel, result = self.run_case([debug_event(3), debug_event(5, exit_code=0)],
                                       fail_duplicate=True)
        self.assertEqual(result["outcome"], "debugger-error")
        self.assertEqual(kernel.duplicated, [21])
        self.assertEqual([handle for handle, _ in kernel.waited], [11])
        self.assertNotIn(41, kernel.closed)
        self.assertIn({"operation": "DuplicateHandle:game-process", "error": 6},
                      result["debugger_errors"])

    def test_unsignaled_game_process_refuses_exit(self):
        kernel, result = self.run_case([debug_event(3), debug_event(5, exit_code=0)],
                                       game_wait_result=258)
        self.assertEqual(result["outcome"], "debugger-error")
        self.assertEqual([handle for handle, _ in kernel.waited], [11, 41])
        self.assertIn({"operation": "WaitForSingleObject:200", "error": 258},
                      result["debugger_errors"])
        self.assertEqual(kernel.closed.count(41), 1)

    def test_failed_game_handle_close_is_uncertain_without_retry(self):
        kernel, result = self.run_case([debug_event(3), debug_event(5, exit_code=0)],
                                       fail_close=41)
        self.assertEqual(result["outcome"], "debugger-error")
        self.assertEqual(kernel.closed.count(41), 1)
        self.assertNotIn("game-process", result["cleanup"]["close"])
        self.assertIn({"label": "game-process", "handle": 41},
                      result["cleanup"]["uncertain_handles"])
        self.assertIn({"operation": "CloseHandle:game-process", "error": 6},
                      result["debugger_errors"])

    def test_second_game_create_refuses_replacing_owned_handle(self):
        kernel, result = self.run_case([debug_event(3),
                                        debug_event(3, pid=300, tid=301, process_handle=23)])
        self.assertEqual(result["outcome"], "debugger-error")
        self.assertEqual(kernel.duplicated, [21])
        self.assertEqual(kernel.closed.count(41), 1)
        self.assertIn({"operation": "CREATE_PROCESS:multiple-game", "error": 300},
                      result["debugger_errors"])

    def test_failed_exit_continuation_refuses_natural_exit_without_retry(self):
        kernel, result = self.run_case([debug_event(3), debug_event(5, exit_code=0)],
                                       fail_continue=True)
        self.assertEqual(result["outcome"], "debugger-error")
        self.assertEqual(kernel.continued, [(200, 201, runner.DBG_CONTINUE)] * 2)
        self.assertIn({"operation": "ContinueDebugEvent", "error": 5}, result["debugger_errors"])
        self.assertIn({"operation": "cleanup:missing-exit-events", "error": [100, 200]},
                      result["debugger_errors"])

    def test_second_chance_crash_continues_once_before_cleanup(self):
        kernel, result = self.run_case([debug_event(3), debug_event(1, exception=0xC0000005)])
        self.assertEqual(result["outcome"], "crash")
        self.assertEqual(kernel.continued[:2], [(200, 201, runner.DBG_CONTINUE),
                                                (200, 201, runner.DBG_NOT_HANDLED)])
        self.assertEqual(len(kernel.continued), len(kernel.delivered))
        self.assertEqual(set(result["cleanup"]["exit_events"]), {100, 200})

    def test_second_chance_breakpoint_is_not_swallowed(self):
        kernel, result = self.run_case([debug_event(3), debug_event(1, exception=0x80000003)])
        self.assertEqual(result["outcome"], "crash")
        self.assertEqual(kernel.continued[1], (200, 201, runner.DBG_NOT_HANDLED))
        self.assertEqual(len(kernel.continued), len(kernel.delivered))

    def test_failed_event_file_close_is_not_retried_or_accepted(self):
        kernel, result = self.run_case([debug_event(3, file_handle=31)], fail_close=31)
        self.assertEqual(result["outcome"], "debugger-error")
        self.assertEqual(kernel.closed.count(31), 1)
        self.assertIn({"operation": "CloseHandle:create-process:200", "error": 6},
                      result["debugger_errors"])
        self.assertIn({"label": "create-process:200", "handle": 31},
                      result["cleanup"]["uncertain_handles"])

    def test_failed_process_information_close_is_not_reported_closed(self):
        kernel, result = self.run_case([debug_event(3), debug_event(5, exit_code=0)],
                                       fail_close=11)
        self.assertEqual(result["outcome"], "debugger-error")
        self.assertEqual(kernel.closed.count(11), 1)
        self.assertNotIn("pi-process", result["cleanup"]["close"])
        self.assertIn({"label": "pi-process", "handle": 11},
                      result["cleanup"]["uncertain_handles"])

    def test_hard_wait_error_is_not_a_timeout(self):
        kernel, result = self.run_case([debug_event(3)], wait_error=True)
        self.assertEqual(result["outcome"], "debugger-error")
        self.assertIn({"operation": "WaitForDebugEvent", "error": 5}, result["debugger_errors"])
        self.assertEqual(kernel.delivered, [])

    def test_documented_wait_timeout_keeps_timeout_classification(self):
        kernel, result = self.run_case([debug_event(3)])
        self.assertEqual(result["outcome"], "timeout")
        self.assertEqual(result["debugger_errors"], [])
        self.assertEqual(set(result["cleanup"]["exit_events"]), {100, 200})
        self.assertGreaterEqual(kernel.clock.now, 2)

    def test_cleanup_wait_timeout_refuses_successful_exit(self):
        kernel, result = self.run_case([debug_event(3), debug_event(5, exit_code=0)],
                                       wait_result=258)
        self.assertEqual(result["outcome"], "debugger-error")
        self.assertIn({"operation": "WaitForSingleObject:100", "error": 258},
                      result["debugger_errors"])
        self.assertEqual(kernel.waited[0][0], 11)
        self.assertLessEqual(kernel.waited[0][1], 5000)

    def test_failed_termination_requires_exit_proof(self):
        kernel, result = self.run_case([debug_event(3), debug_event(5, exit_code=0)],
                                       fail_terminate=True)
        self.assertEqual(result["outcome"], "debugger-error")
        self.assertIn({"operation": "TerminateProcess:100", "error": 5}, result["debugger_errors"])
        self.assertIn({"operation": "cleanup:missing-exit-events", "error": [100]},
                      result["debugger_errors"])

    def test_smoke_preserves_debugger_error_classification(self):
        options = SimpleNamespace(retail=True, base=0x400000, args="-win", overlay=None,
                                  appdata=Path("/mock-sandbox-appdata"), game_dir=Path("/mock-game"),
                                  guard=[], compat=None, no_focus_lie=True, no_version_lie=True,
                                  timeout=2, probes=False, defocus=None, int3_faults=False,
                                  relayout=False)
        report = {"outcome": "debugger-error", "first_chance": [], "probes_hit": [],
                  "debugger_errors": [{"operation": "ContinueDebugEvent", "error": 5}]}
        with (mock.patch.object(runner, "prepare_sandbox_profile"),
              mock.patch.object(runner.real_image, "install_game_dat", return_value="0" * 64),
              mock.patch.object(runner, "run", return_value=report),
              mock.patch.object(runner, "ProfileGuard") as guard):
            guard.return_value.check.return_value = ({"changed": []}, False)
            outcome = runner.smoke(options)
        self.assertEqual(outcome["outcome"], "debugger-error")
        self.assertEqual(outcome["run"]["debugger_errors"], report["debugger_errors"])

    def test_redirect_failure_terminates_game_before_continuation(self):
        loader_stop = debug_event(runner.EXCEPTION, exception=0x4000001F, first_chance=1)
        with mock.patch.object(runner, "install_appdata_lie", side_effect=runner.RedirectError("refused")):
            kernel, result = self.run_case([debug_event(3), loader_stop])
        self.assertEqual(result["outcome"], "profile-redirect-failed")
        self.assertEqual(kernel.calls.index(("terminate", 21)) + 1,
                         kernel.calls.index(("continue", 200), 1))
        self.assertEqual(kernel.terminated.count(21), 1)
        self.assertEqual(len(kernel.continued), len(kernel.delivered))

    def test_missing_cleanup_exit_is_bounded_and_refuses_success(self):
        kernel, result = self.run_case([debug_event(3), debug_event(5, exit_code=0)],
                                       emit_exit=False)
        self.assertEqual(result["outcome"], "debugger-error")
        self.assertIn({"operation": "cleanup:missing-exit-events", "error": [100]},
                      result["debugger_errors"])
        self.assertGreaterEqual(kernel.clock.now, 5)
        self.assertLess(kernel.clock.now, 6)


if __name__ == "__main__":
    unittest.main()



class StackKernel:
    """OpenThread, Wow64GetThreadContext and ReadProcessMemory over `memory` (a readable
    range [lo, hi) of dwords); a read past hi fails the way one across a stack's top does."""

    def __init__(self, esp, lo, hi):
        self.esp, self.lo, self.hi, self.reads = esp, lo, hi, []
        self.OpenThread = lambda *args: 7

    def Wow64GetThreadContext(self, handle, ref):
        ctx = ref._obj
        ctx.esp, ctx.ebp, ctx.edx, ctx.eip, ctx.eflags = self.esp, self.esp + 0x40, 0x476E654D, 0x101696DF, 0x10246
        return 1

    def CloseHandle(self, handle):
        return 1

    def ReadProcessMemory(self, hproc, address, buf, size, got):
        at = address.value
        self.reads.append((at, size))
        if not (self.lo <= at and at + size <= self.hi):
            got._obj.value = 0
            return 0
        data = b"".join((w & 0xFFFFFFFF).to_bytes(4, "little") for w in range(at // 4, (at + size) // 4))
        ctypes.memmove(buf, data, size)
        got._obj.value = size
        return 1


class FaultStackTests(unittest.TestCase):
    """The crash record keeps the fault's raw stack (P31: a heap overrun's writer)."""

    def test_stack_words_stops_at_the_first_unreadable_page(self):
        # 0x100 bytes below the stack's top: one 8 KB read would fail and return nothing
        k = StackKernel(esp=0x0019FF00, lo=0x00190000, hi=0x001A0000)
        st = runner.stack_words(k, 5, 201)
        self.assertEqual(len(st["words"]), 0x40)
        self.assertEqual(st["words"][0], 0x0019FF00 // 4)
        self.assertEqual(k.reads, [(0x0019FF00, 0x100), (0x001A0000, 0x1000)])
        self.assertEqual(st["regs"]["edx"], "0x476e654d")
        self.assertEqual((st["regs"]["esp"], st["regs"]["eflags"]), ("0x19ff00", "0x10246"))

    def test_stack_words_reads_all_n_words_a_page_at_a_time(self):
        k = StackKernel(esp=0x00180F00, lo=0x00100000, hi=0x00200000)
        st = runner.stack_words(k, 5, 201)
        self.assertEqual(len(st["words"]), 2048)
        self.assertEqual(st["words"][-1], (0x00180F00 + 2047 * 4) // 4)
        self.assertEqual(k.reads[0], (0x00180F00, 0x100))
        self.assertTrue(all(size <= 0x1000 for _at, size in k.reads))

    STACK = {"esp": 0x0019F000, "ebp": 0x0019F040, "regs": {"edx": "0x476e654d", "eip": "0x101696df"},
             "words": [0x476E654D, 0x1023F4AF, 0x0019F0A0]}
    OPTS = dict(retail=True, base=0x400000, args="-win", overlay=None, appdata=Path("/mock-sandbox-appdata"),
                game_dir=Path("/mock-game"), guard=[], compat=None, no_focus_lie=True, no_version_lie=True,
                timeout=2, probes=False, defocus=None, int3_faults=False, relayout=False)

    def smoke(self, report, **opts):
        with (mock.patch.object(runner, "prepare_sandbox_profile"),
              mock.patch.object(runner.real_image, "install_game_dat", return_value="0" * 64),
              mock.patch.object(runner, "run", return_value=report),
              mock.patch.object(runner, "ledger_row", return_value=("?f@@YAXXZ", "0x1000", "matched")),
              mock.patch.object(runner, "image_frames", return_value=[["0x1023f4af", "?g@@YAXXZ+0x1f"]]),
              mock.patch.object(runner, "ProfileGuard") as guard):
            guard.return_value.check.return_value = ({"changed": []}, False)
            return runner.smoke(SimpleNamespace(**dict(self.OPTS, **opts)))

    def assert_stack(self, out):
        stack = out["crash"]["stack"]
        self.assertEqual(stack["words"], ["0x476e654d", "0x1023f4af", "0x19f0a0"])
        self.assertEqual((stack["esp"], stack["ebp"]), ("0x19f000", "0x19f040"))
        self.assertEqual(stack["regs"]["edx"], "0x476e654d")
        self.assertEqual(stack["frames"], [["0x1023f4af", "?g@@YAXXZ+0x1f"]])
        self.assertIs(out["receipt"]["crash"]["stack"], stack)     # the queue copies the receipt's crash

    def test_real_image_crash_keeps_the_raw_stack(self):
        ri = SimpleNamespace(base=0x10000000)
        report = {"outcome": "exit", "exit_code": 666, "fault": 0x101696DF, "first_chance":
                  [["0xc0000005", 0x101696DF, [0, 0x476E6551]]], "probes_hit": [], "image_base": 0x10000000,
                  "stack": self.STACK, "quiet": []}
        with (mock.patch.object(runner.real_image, "load", return_value=ri),
              mock.patch.object(runner.real_image, "check", return_value=(True, {})),
              mock.patch.object(runner.real_image, "summary", return_value={
                  "image_kind": "diagnostic", "image_sha256": "1" * 64, "image_commit": None}),
              mock.patch.object(runner.real_image, "crash_fields", return_value={
                  "exception": "0xc0000005", "map_symbol": "?rva00033ED0@Rva006C1F60@@QAEPAXIH@Z",
                  "stack_frames": []})):
            out = self.smoke(report, real_image="/mock/exit.exe", rebase=None, retail=False)
        self.assertEqual(out["outcome"], "crash-at-?rva00033ED0@Rva006C1F60@@QAEPAXIH@Z")
        self.assert_stack(out)

    def test_retail_crash_keeps_the_raw_stack(self):
        report = {"outcome": "crash", "code": "0xc0000005", "address": 0x401000, "info": [0, 0],
                  "first_chance": [], "probes_hit": [], "image_base": 0x400000, "stack": self.STACK, "quiet": []}
        self.assert_stack(self.smoke(report))

    def test_retail_handled_fault_then_exit_keeps_the_raw_stack(self):
        report = {"outcome": "exit", "exit_code": 666, "fault": 0x401000, "first_chance":
                  [["0xc0000005", 0x401000, [0, 0]]], "probes_hit": [], "image_base": 0x400000,
                  "stack": self.STACK, "quiet": []}
        self.assert_stack(self.smoke(report))

    def test_a_crash_without_a_stack_read_has_no_stack(self):
        report = {"outcome": "crash", "code": "0xc0000005", "address": 0x401000, "info": [0, 0],
                  "first_chance": [], "probes_hit": [], "image_base": 0x400000, "stack": None, "quiet": []}
        self.assertNotIn("stack", self.smoke(report)["crash"])
