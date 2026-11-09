"""Host fake Win32 events against the real game_smoke.Game.run; no game launch."""

import ctypes
from pathlib import Path
import sys
import tempfile
import unittest
from unittest import mock
from types import SimpleNamespace

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import game_smoke as runner


def event(code, *, pid=200, tid=201, file_handle=0, process_handle=21,
          exception=0, first_chance=0, exit_code=0):
    raw = bytearray(256)

    def put(offset, value, width=4):
        raw[offset:offset + width] = value.to_bytes(width, "little")

    put(0, code)
    put(4, pid)
    put(8, tid)
    if code == runner.CREATE_PROCESS:
        put(16, file_handle, 8)
        put(24, process_handle, 8)
        put(32, 22, 8)
        put(40, 0x400000, 8)
    elif code == runner.EXCEPTION:
        put(16, exception)
        put(32, 0x401000, 8)
        put(168, first_chance)
    elif code == runner.EXIT_PROCESS:
        put(16, exit_code)
    return bytes(raw)


class Clock:
    now = 0.0

    def time(self):
        return self.now

    def monotonic(self):
        return self.now


class Kernel:
    def __init__(self, clock, events, *, fail_continue=False, fail_close=None,
                 hard_wait=False, game_wait_result=0, fail_duplicate=False, emit_exit=True):
        self.clock, self.events = clock, list(events)
        self.fail_continue, self.fail_close = fail_continue, fail_close
        self.hard_wait, self.game_wait_result = hard_wait, game_wait_result
        self.fail_duplicate, self.emit_exit = fail_duplicate, emit_exit
        self.delivered, self.continued, self.closed = [], [], []
        self.terminated, self.waited, self.duplicated = [], [], []
        self.QueryFullProcessImageNameW = lambda *args: self.query_image(*args)
        self.GetFinalPathNameByHandleW = lambda *args: 0
        self.OpenThread = lambda *args: 0
        self.VirtualAllocEx = lambda *args: 0

    def CreateProcessW(self, application, command, process_security, thread_security,
                       inherit, flags, environment, directory, startup, info):
        assert flags == runner.DEBUG_PROCESS and not inherit
        info._obj.hProcess, info._obj.hThread = 11, 12
        info._obj.pid, info._obj.tid = 100, 101
        return 1

    def query_image(self, handle, flags, buffer, count):
        buffer.value = "game.dat" if handle == 21 else "lotrbfme2.exe"
        count._obj.value = len(buffer.value)
        return 1

    def GetCurrentProcess(self):
        return ctypes.c_void_p(-1).value

    def DuplicateHandle(self, source_process, source_handle, target_process, target_handle,
                        access, inherit, options):
        self.duplicated.append(source_handle.value)
        if self.fail_duplicate:
            return 0
        target_handle._obj.value = 41
        return 1

    def WaitForDebugEvent(self, output, milliseconds):
        if self.events and not self.hard_wait:
            raw = self.events.pop(0)
            ctypes.memmove(output, raw, len(raw))
            self.delivered.append(raw)
            return 1
        self.clock.now += milliseconds / 1000
        return 0

    def ContinueDebugEvent(self, pid, tid, status):
        self.continued.append((pid, tid, status))
        return not (self.fail_continue and len(self.continued) == 3)

    def CloseHandle(self, handle):
        value = handle.value if hasattr(handle, "value") else handle
        self.closed.append(value)
        return value != self.fail_close

    def TerminateProcess(self, handle, exit_code):
        value = handle.value if hasattr(handle, "value") else handle
        self.terminated.append(value)
        if self.emit_exit:
            pid, tid = {11: (100, 101), 21: (200, 201), 23: (100, 101)}[value]
            self.events.append(event(runner.EXIT_PROCESS, pid=pid, tid=tid, exit_code=1))
        return 1

    def WaitForSingleObject(self, handle, milliseconds):
        self.waited.append((handle.value, milliseconds))
        return self.game_wait_result if handle.value == 41 else 0


class GameRunLifecycle(unittest.TestCase):
    def run_case(self, events, **failures):
        clock = Clock()
        kernel = Kernel(clock, events, **failures)
        with (mock.patch.object(runner.boot_smoke, "k32", return_value=kernel),
              mock.patch.object(runner.boot_smoke, "check_sandbox_appdata"),
              mock.patch.object(runner, "image_size", return_value=0xC00000),
              mock.patch.object(runner.time, "time", side_effect=clock.time),
              mock.patch.object(runner.time, "monotonic", side_effect=clock.monotonic),
              mock.patch.object(runner.ctypes, "get_last_error", return_value=5, create=True)):
            game = runner.Game(Path("/mock-game"), "-win", Path("/mock-appdata"), version_lie=False)
            result = game.run(2)
        return kernel, result

    @staticmethod
    def natural_events():
        return [event(runner.CREATE_PROCESS, pid=100, tid=101, process_handle=23),
                event(runner.CREATE_PROCESS, file_handle=31),
                event(runner.EXIT_PROCESS, exit_code=0)]

    def test_natural_exit_requires_continuation_and_owned_game_wait(self):
        kernel, result = self.run_case(self.natural_events())
        self.assertEqual(result["stopped"], "exit")
        self.assertEqual(kernel.duplicated, [21])
        self.assertEqual([handle for handle, _ in kernel.waited], [11, 41])
        self.assertEqual(kernel.closed.count(31), 1)
        self.assertEqual(kernel.closed.count(41), 1)

    def test_failed_exit_continuation_refuses_exit(self):
        kernel, result = self.run_case(self.natural_events(), fail_continue=True)
        self.assertEqual(result["stopped"], "debugger-error")
        self.assertEqual(len(kernel.continued), len(kernel.delivered))
        self.assertIn("cleanup:uncontinued-event", [error["operation"] for error in result["debugger_errors"]])

    def test_unsignaled_game_refuses_exit(self):
        kernel, result = self.run_case(self.natural_events(), game_wait_result=258)
        self.assertEqual(result["stopped"], "debugger-error")
        self.assertIn(41, [handle for handle, _ in kernel.waited])

    def test_failed_game_handle_duplication_refuses_exit(self):
        _, result = self.run_case(self.natural_events(), fail_duplicate=True)
        self.assertEqual(result["stopped"], "debugger-error")
        self.assertIn("DuplicateHandle:game-process", [error["operation"] for error in result["debugger_errors"]])

    def test_failed_event_file_close_refuses_exit(self):
        kernel, result = self.run_case(self.natural_events(), fail_close=31)
        self.assertEqual(result["stopped"], "debugger-error")
        self.assertEqual(kernel.closed.count(31), 1)
        self.assertEqual(result["cleanup"]["uncertain_handles"],
                         [{"label": "create-process:200", "handle": 31}])

    def test_second_chance_crash_is_continued_once(self):
        events = self.natural_events()[:2] + [event(runner.EXCEPTION, exception=0xC0000005)]
        kernel, result = self.run_case(events)
        self.assertEqual(result["stopped"], "crash")
        self.assertEqual(len(kernel.continued), len(kernel.delivered))
        self.assertEqual(kernel.continued.count((200, 201, runner.DBG_NOT_HANDLED)), 1)

    def test_hard_wait_error_is_not_timeout(self):
        _, result = self.run_case([], hard_wait=True)
        self.assertEqual(result["stopped"], "debugger-error")

    def test_debugger_error_cannot_become_scenario_pass(self):
        self.assertEqual(runner.crash_outcome({"stopped": "debugger-error"}), "debugger-error")
        with tempfile.TemporaryDirectory() as directory, mock.patch.object(runner, "OUT", Path(directory)):
            report = {"run": {"stopped": "debugger-error"}, "outcome": "pass",
                      "profile_touched": False, "guard": {}}
            code = runner.finish(SimpleNamespace(retail=True), "synthetic", report)
        self.assertEqual(code, 1)
        self.assertEqual(report["outcome"], "debugger-error")


class FaultCaptureTests(unittest.TestCase):
    """P106: a skirmish's crash keeps the fault's registers, through boot_smoke's capture."""

    def test_the_fault_is_captured_by_boot_smoke_s_path(self):
        game = SimpleNamespace(k=object(), hproc=9)
        st = {"esp": 0x19F000, "ebp": 0x19F040, "regs": {"eax": "0x190100", "esp": "0x19f000"},
              "memory": {"eax": "0011"}, "words": [1, 2, 3]}
        res = {}
        with mock.patch.object(runner.boot_smoke, "fault_capture", return_value=st) as capture:
            runner.Game.capture_fault(game, 77, res)
        capture.assert_called_once_with(game.k, 9, 77, 256)
        self.assertEqual(res["fault_words"], [1, 2, 3])                       # the field crash_fields reads, as before
        self.assertEqual(res["fault_context"], {"esp": 0x19F000, "ebp": 0x19F040, "regs": st["regs"], "memory": {"eax": "0011"}})

    run_case = GameRunLifecycle.run_case

    def test_a_first_chance_fault_in_the_game_is_captured(self):
        crash = GameRunLifecycle.natural_events()[:2] + [event(runner.EXCEPTION, exception=0xC0000005, first_chance=1),
                                                         event(runner.EXCEPTION, exception=0xC0000005)]
        with mock.patch.object(runner.Game, "stack_frames", return_value=[]), \
                mock.patch.object(runner.Game, "capture_fault", autospec=True,
                                  side_effect=lambda game, tid, res: res.update(fault_words=[7])) as capture:
            _, result = self.run_case(crash)
        capture.assert_called_once()
        self.assertEqual((result["stopped"], result["fault_words"]), ("crash", [7]))

    def test_an_unreadable_thread_keeps_the_old_empty_words(self):
        res = {}
        with mock.patch.object(runner.boot_smoke, "fault_capture", return_value=None):
            runner.Game.capture_fault(SimpleNamespace(k=None, hproc=None), 77, res)
        self.assertEqual((res["fault_words"], res["fault_context"]), ([], {}))

    def test_the_real_image_crash_record_has_boot_smoke_s_stack(self):
        res = {"stopped": "crash", "address": 0x2004319, "code": "0xc0000005", "fault_words": [5, 6],
               "fault_context": {"esp": 0x19F000, "ebp": 0x19F040, "regs": {"eax": "0x1"}, "memory": {}}}
        with mock.patch("real_image.crash_fields", return_value={"map_symbol": "f"}) as fields, \
                mock.patch.object(runner.boot_smoke, "fault_stack", return_value={"regs": {"eax": "0x1"}}) as stack:
            crash = runner.crash_record("ri", res, 0x2000000)
        fields.assert_called_once_with("ri", 0x2004319, 0x2000000, [5, 6], "0xc0000005")
        stack.assert_called_once_with(dict(res["fault_context"], words=[5, 6]), 0x2000000, "ri", None)
        self.assertEqual(crash, {"map_symbol": "f", "stack": {"regs": {"eax": "0x1"}}})

    def test_a_crash_with_no_capture_keeps_the_contract_fields_alone(self):
        res = {"stopped": "exit", "fault": 0x2004319, "fault_code": "0xc0000005", "exit_code": 1}
        with mock.patch("real_image.crash_fields", return_value={"map_symbol": "f"}) as fields:
            crash = runner.crash_record("ri", res, 0x2000000)
        fields.assert_called_once_with("ri", 0x2004319, 0x2000000, [], "0xc0000005")
        self.assertEqual(crash, {"map_symbol": "f"})


if __name__ == "__main__":
    unittest.main()
