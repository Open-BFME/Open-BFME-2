"""Host-only debug-event failure injection for boot_smoke.run; no game is launched."""

import contextlib
import ctypes
import sys
import threading
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

    def sleep(self, seconds):
        self.now += seconds


class FakeUser:
    def __init__(self):
        self.ShowWindowAsync = lambda *args: 1


class FakeKernel:
    def __init__(self, clock, events, *, fail_continue=False, fail_close=None,
                 wait_error=False, fail_terminate=False, wait_result=0, game_wait_result=0,
                 fail_duplicate=False, emit_exit=True, fail_suspend=False, resume_failures=0, resume_fail_from=0,
                 resume_raises=0, raises=(), other_suspend_on=0, other_resume_on=0, fail_context=False, sampler_cost=0.0,
                 context_cost=0.0, suspended=0, spinning=False, thread_exit_at=None, timed_events=(), wait_late=0.0,
                 stream_from=None, look_cost=0.0, wait_error_on=0):
        # The main thread: it only moves while its suspend count is zero, as a real one does, and the count
        # persists, so a suspend left outstanding reads as identical EIPs, exactly what a spin looks like.
        self.fail_suspend = fail_suspend
        self.resume_failures = resume_failures        # how many resumes fail; -1 is every one
        self.resume_fail_from = resume_fail_from      # every resume from this one on fails
        self.resume_raises = resume_raises            # how many resumes raise; -1 is every one
        self.raises = raises                          # "suspend", "context": those calls raise
        self.other_suspend_on = other_suspend_on      # while our Nth suspend holds it, another party suspends, for good
        self.other_resume_on = other_resume_on        # while our Nth suspend holds it, another party resumes it
        self.fail_context = fail_context
        self.sampler_cost = sampler_cost              # seconds one suspend takes, on the run's clock
        self.context_cost = context_cost              # seconds one context read takes, thread still suspended
        self.suspended = suspended
        self.spinning = spinning                      # it runs, and stays where it is
        self.thread_exit_at = thread_exit_at          # run time the thread is gone: every call on it fails
        self.suspends, self.resumes = 0, 0
        self.moved, self.ticked = 0.0, clock.now
        # An event is deliverable from its due time, whatever the debugger was doing at that moment.
        self.timed_events = sorted(timed_events, key=lambda e: e[0])        # (run time it becomes due, raw event)
        self.wait_late = wait_late                    # a wait may return this long after it was due to
        self.stream_from = stream_from                # from this run time, an event is always pending
        self.look_cost = look_cost                    # seconds a zero wait takes
        self.looks = 0
        self.wait_error_on = wait_error_on            # only this WaitForDebugEvent fails, hard
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

    def gone(self):
        return self.thread_exit_at is not None and self.clock.now >= self.thread_exit_at

    def tick(self):
        if not self.suspended and not self.spinning and not self.gone():
            self.moved += self.clock.now - self.ticked
        self.ticked = self.clock.now

    def SuspendThread(self, handle):
        self.tick()
        self.calls.append("suspend")
        self.clock.now += self.sampler_cost
        if "suspend" in self.raises:
            raise OSError("exception: access violation")
        if self.fail_suspend or self.gone():
            self.last_error = 5
            return -1
        before = self.suspended
        self.suspends += 1
        self.suspended += 1
        if self.suspends == self.other_suspend_on:
            self.suspended += 1
        if self.suspends == self.other_resume_on:
            self.suspended -= 1
        return before

    def ResumeThread(self, handle):
        self.tick()
        self.resumes += 1
        if self.resume_raises:
            self.resume_raises -= 1 if self.resume_raises > 0 else 0
            raise OSError("exception: access violation")
        if self.resume_failures or (self.resume_fail_from and self.resumes >= self.resume_fail_from) or self.gone():
            self.resume_failures -= 1 if self.resume_failures > 0 else 0
            self.last_error = 5
            return -1
        before = self.suspended
        self.suspended = max(0, self.suspended - 1)
        return before

    def Wow64GetThreadContext(self, handle, context):
        self.tick()
        self.clock.now += self.context_cost
        if "context" in self.raises:
            raise OSError("exception: access violation")
        if self.fail_context or self.gone():
            self.last_error = 5
            return 0
        context._obj.eip = 0x401000 + int(self.moved * 0x1000)      # a thread at work moves on
        return 1

    def deliver(self, output, raw):
        ctypes.memmove(output, raw, len(raw))
        self.delivered.append(raw)
        return 1

    def WaitForDebugEvent(self, output, milliseconds):
        self.tick()
        self.looks += 1
        assert self.clock.now < 1000 and self.looks < 100000, "the run never ended"
        if self.looks == self.wait_error_on:
            self.last_error = 5
            return 0
        if self.events and not self.wait_error:
            return self.deliver(output, self.events.pop(0))
        if not milliseconds:
            self.clock.now += self.look_cost
        end = self.clock.now + milliseconds / 1000 + (self.wait_late if milliseconds else 0)
        if self.timed_events and self.timed_events[0][0] <= end and not self.wait_error:
            at, raw = self.timed_events.pop(0)
            self.clock.now = max(self.clock.now, at)
            return self.deliver(output, raw)
        if self.stream_from is not None and not self.terminated and self.stream_from <= end and not self.wait_error:
            self.clock.now = max(self.clock.now, self.stream_from) + 0.01
            return self.deliver(output, debug_event(8))
        self.clock.now = end
        self.tick()
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

    def run_case(self, events, *, timeout=2, real_samples=False, shots_at=(), shot_cost=0.0, **failures):
        clock = FakeClock()
        kernel = FakeKernel(clock, events, **failures)
        self.captured_at = None
        self.clock, self.shot_threads = clock, []

        def capture(pid):
            self.captured_at = clock.now

        def timed_capture(pid, path):
            # A slow capture blocks whichever thread runs it: on the event loop that is the run's own clock.
            self.shot_threads.append(threading.current_thread())
            if threading.current_thread() is threading.main_thread():
                clock.now += shot_cost
            return {"black": False, "path": str(path)}
        patches = [mock.patch.object(runner, "window_picture", side_effect=timed_capture)] if shot_cost else []
        for patch in patches:
            patch.start()
            self.addCleanup(patch.stop)
        sampled = {} if real_samples else {"return_value": []}
        with (mock.patch.object(runner, "k32", return_value=kernel),
              mock.patch.object(runner.ctypes, "WinDLL", return_value=FakeUser(), create=True),
              mock.patch.object(runner.ctypes, "get_last_error", side_effect=kernel.get_last_error, create=True),
              mock.patch.object(runner, "time", clock),
              mock.patch.object(runner, "sample_eips", **sampled) if not real_samples else contextlib.nullcontext(),
              mock.patch.object(runner, "windows_of", return_value=[]),
              mock.patch.object(runner, "window_texts", return_value=[]),
              mock.patch.object(runner, "screenshot", side_effect=capture),
              mock.patch.object(runner, "stack_words", return_value=None)):
            result = runner.run(Path("launcher.exe"), Path("/mock-game"), "-win", timeout,
                                version_lie=False, appdata=Path("/mock-sandbox-appdata"), shots_at=shots_at)
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
                                  guard=[], compat=None, no_focus_lie=True, shots_at=(), no_version_lie=True,
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



class MainThreadSamplerTests(unittest.TestCase):
    """The sampler must never make the hang it reports: suspending the thread it is measuring."""
    GAME = [debug_event(3, file_handle=31)]
    run_case = RunnerDebugTests.run_case

    def span(self, result):
        return runner.main_thread_span(result.get("spin_samples", []), 0x400000, 0x80000000,
                                       result.get("spin_sample_failures", 0))

    def test_a_real_spin_still_reads_as_one(self):
        # The other direction: every check below must leave the true positive standing.
        kernel, result = self.run_case(self.GAME, timeout=40, spinning=True)
        self.assertEqual(result["outcome"], "timeout")
        self.assertEqual(kernel.suspended, 0)
        self.assertEqual(result.get("spin_sample_failures", 0), 0)
        self.assertTrue(self.span(result)["spinning"])

    def test_a_healthy_thread_is_left_running_and_reads_as_working(self):
        kernel, result = self.run_case(self.GAME, timeout=40)
        self.assertEqual(result["outcome"], "timeout")
        self.assertEqual(kernel.suspended, 0)
        self.assertEqual(kernel.suspends, kernel.resumes)
        self.assertGreaterEqual(len(result["spin_samples"]), 20)
        self.assertFalse(self.span(result)["spinning"])

    def test_a_failed_resume_cannot_manufacture_a_hang(self):
        # The review's injection: the first resume fails, the thread stays suspended, and every later
        # balanced pair reads one EIP: spinning=True on a thread that was never spinning.
        kernel, result = self.run_case(self.GAME, timeout=40, resume_failures=-1)
        self.assertEqual(result["outcome"], "debugger-error")
        self.assertTrue(any(e["operation"].startswith("ResumeThread") for e in result["debugger_errors"]))
        self.assertFalse((self.span(result) or {}).get("spinning"))

    def test_only_the_first_resume_failing_does_not_stop_the_run(self):
        kernel, result = self.run_case(self.GAME, timeout=40, resume_failures=1)
        self.assertEqual(result["outcome"], "timeout")
        self.assertEqual(kernel.suspended, 0)
        self.assertFalse(self.span(result)["spinning"])

    def test_a_failed_suspend_is_no_sample_and_no_resume(self):
        kernel, result = self.run_case(self.GAME, timeout=40, fail_suspend=True)
        self.assertEqual(result["outcome"], "timeout")
        self.assertEqual(kernel.resumes, 0)
        self.assertEqual(result.get("spin_samples", []), [])
        self.assertGreater(result["spin_sample_failures"], 0)

    def test_a_thread_someone_else_suspended_says_nothing(self):
        # Not ours to resume past, and an EIP that cannot move is no evidence of a spin.
        kernel, result = self.run_case(self.GAME, timeout=40, suspended=1)
        self.assertEqual(result["outcome"], "timeout")
        self.assertEqual(kernel.suspended, 1)
        self.assertEqual(result.get("spin_samples", []), [])
        self.assertGreater(result["spin_sample_failures"], 0)

    def test_another_suspend_landing_while_we_hold_it_is_no_sample_and_no_hang(self):
        # Our resume finds 2: it is not ours to take further, and every later read sees it held.
        kernel, result = self.run_case(self.GAME, timeout=40, other_suspend_on=1)
        self.assertEqual(result["outcome"], "timeout")
        self.assertEqual(kernel.suspended, 1)
        self.assertEqual(result.get("spin_samples", []), [])
        self.assertGreater(result["spin_sample_failures"], runner.SPIN_MAX_FAILURES)

    def test_a_suspend_landing_part_way_cannot_make_a_hang_of_the_samples_before_it(self):
        kernel, result = self.run_case(self.GAME, timeout=40, spinning=True, other_suspend_on=25)
        self.assertEqual(kernel.suspended, 1)
        self.assertEqual(len(result["spin_samples"]), 24)
        self.assertGreater(result["spin_sample_failures"], runner.SPIN_MAX_FAILURES)
        self.assertFalse(self.span(result)["spinning"])

    def test_another_resume_landing_while_we_hold_it_is_no_sample(self):
        # Our resume finds 0: the read is not known to be of a stopped thread. It runs on, and later reads are good.
        kernel, result = self.run_case(self.GAME, timeout=40, other_resume_on=1)
        self.assertEqual(kernel.suspended, 0)
        self.assertEqual(result["spin_sample_failures"], 1)
        self.assertGreaterEqual(len(result["spin_samples"]), 20)

    def test_a_thread_already_held_is_no_sample_even_when_the_resume_adds_up(self):
        # Held when we arrived, released by its holder while we held it too: our resume finds 1, as on a clean
        # read, but this EIP was not free to move. It runs on from here, and later reads are good.
        kernel, result = self.run_case(self.GAME, timeout=40, suspended=1, other_resume_on=1)
        self.assertEqual(kernel.suspended, 0)
        self.assertEqual(result["spin_sample_failures"], 1)
        self.assertGreaterEqual(len(result["spin_samples"]), 20)

    def test_a_resume_that_raises_is_a_debugger_error(self):
        kernel, result = self.run_case(self.GAME, timeout=40, resume_raises=-1)
        self.assertEqual(result["outcome"], "debugger-error")
        self.assertEqual(kernel.suspended, 1)
        failure = next(e for e in result["debugger_errors"] if e["operation"] == "ResumeThread:spin-sample")
        self.assertIn("access violation", failure["error"])

    def test_a_resume_that_raises_once_is_retried(self):
        kernel, result = self.run_case(self.GAME, timeout=40, resume_raises=1)
        self.assertEqual(result["outcome"], "timeout")
        self.assertEqual(kernel.suspended, 0)

    def test_a_context_read_that_raises_still_resumes_and_is_no_label(self):
        # Nothing to say about the game: it escapes run(), after the resume and the cleanup, and no label is written.
        clock = FakeClock()
        with self.assertRaises(OSError):
            kernel = FakeKernel(clock, [], raises=("context",))
            runner.thread_eip(kernel, 22)
        self.assertEqual(kernel.suspended, 0)
        with self.assertRaises(OSError):
            self.run_case(self.GAME, timeout=40, raises=("context",))

    def test_a_suspend_that_raises_is_no_label(self):
        with self.assertRaises(OSError):
            self.run_case(self.GAME, timeout=40, raises=("suspend",))

    def test_a_main_thread_gone_before_the_span_is_no_sample_and_no_hang(self):
        kernel, result = self.run_case(self.GAME, timeout=40, thread_exit_at=5.0)
        self.assertEqual(result["outcome"], "timeout")
        self.assertEqual(kernel.suspends, 0)
        self.assertEqual(kernel.resumes, 0)
        self.assertEqual(result.get("spin_samples", []), [])
        self.assertEqual(result["main_eips"] if "main_eips" in result else [], [])
        self.assertIsNone(result["main_stack"])
        self.assertGreater(result["spin_sample_failures"], runner.SPIN_MAX_FAILURES)

    def test_a_main_thread_gone_part_way_is_no_hang(self):
        kernel, result = self.run_case(self.GAME, timeout=40, spinning=True, thread_exit_at=35.0)
        self.assertEqual(result["outcome"], "timeout")
        self.assertGreater(len(result["spin_samples"]), 20)
        self.assertGreater(result["spin_sample_failures"], runner.SPIN_MAX_FAILURES)
        self.assertFalse(self.span(result)["spinning"])

    def test_a_thread_gone_between_suspend_and_resume_is_a_debugger_error(self):
        kernel, result = self.run_case(self.GAME, timeout=40, thread_exit_at=10.5, context_cost=1.0)
        self.assertEqual(result["outcome"], "debugger-error")
        self.assertIn("ResumeThread:spin-sample", [e["operation"] for e in result["debugger_errors"]])

    def test_a_failed_context_read_at_every_sample_is_no_hang(self):
        kernel, result = self.run_case(self.GAME, timeout=40, fail_context=True, spinning=True)
        self.assertEqual(result.get("spin_samples", []), [])
        self.assertGreater(result["spin_sample_failures"], runner.SPIN_MAX_FAILURES)

    def test_a_failed_context_read_still_resumes(self):
        kernel, result = self.run_case(self.GAME, timeout=40, fail_context=True)
        self.assertEqual(kernel.suspended, 0)
        self.assertEqual(kernel.suspends, kernel.resumes)
        self.assertEqual(result.get("spin_samples", []), [])

    def test_a_failed_resume_in_the_final_samples_is_a_debugger_error(self):
        # After the span: the eight samples at the timeout go through the same check.
        kernel, result = self.run_case(self.GAME, timeout=40, real_samples=True, resume_failures=0)
        self.assertEqual(result["outcome"], "timeout")
        self.assertEqual(len(result["main_eips"]), 8)
        kernel = None
        with mock.patch.object(runner, "SPIN_SPAN", 0.0):             # no span samples: only the final ones
            kernel, result = self.run_case(self.GAME, timeout=2, real_samples=True, resume_failures=-1)
        self.assertEqual(result["outcome"], "debugger-error")
        self.assertIn("ResumeThread:final-sample", [e["operation"] for e in result["debugger_errors"]])

    # Finding 2: the deadline holds at run time, whatever sampling costs.
    CRASH = debug_event(1, exception=0xC0000005, first_chance=0)

    def test_sampling_does_not_extend_the_deadline(self):
        kernel, result = self.run_case(self.GAME, timeout=2, sampler_cost=0.75)
        self.assertEqual(result["outcome"], "timeout")
        self.assertLessEqual(self.captured_at, 2.0 + 0.75 + 0.75)     # the one sample in flight, then main_stack's suspend
        self.assertGreaterEqual(self.captured_at, 2.0)

    def test_a_crash_delivered_while_a_sample_crossed_the_deadline_counts(self):
        # The review's injection: due at 1.9, the sample in flight ran to 2.5, and the run called it out of time.
        kernel, result = self.run_case(self.GAME, timeout=2, sampler_cost=0.75, timed_events=[(1.9, self.CRASH)])
        self.assertEqual(result["outcome"], "crash")

    def test_a_crash_due_at_the_deadline_counts(self):
        kernel, result = self.run_case(self.GAME, timeout=2, timed_events=[(2.0, self.CRASH)])
        self.assertEqual(result["outcome"], "crash")

    def test_a_crash_a_late_wait_returned_past_the_deadline_counts(self):
        # Deliberate: it really happened, and nothing about a real fault is favourable to the build.
        kernel, result = self.run_case(self.GAME, timeout=2, wait_late=0.3, timed_events=[(2.1, self.CRASH)])
        self.assertEqual(result["outcome"], "crash")

    def test_the_first_look_finding_nothing_past_the_deadline_closes_the_run(self):
        kernel, result = self.run_case(self.GAME, timeout=2, timed_events=[(2.1, self.CRASH)])
        self.assertEqual(result["outcome"], "timeout")
        self.assertEqual(self.captured_at, 2.0)
        kernel, result = self.run_case(self.GAME, timeout=2, sampler_cost=0.75, timed_events=[(2.6, self.CRASH)])
        self.assertEqual(result["outcome"], "timeout")

    def test_a_slow_look_cannot_buy_the_wait_more(self):
        # 0.6 s a look: the look at 1.6 ends at 2.2, past the deadline, and the run ends there, not after another wait.
        with mock.patch.object(runner, "SPIN_SPAN", 0.0):
            kernel, result = self.run_case(self.GAME, timeout=2, look_cost=0.6)
        self.assertEqual(result["outcome"], "timeout")
        self.assertAlmostEqual(self.captured_at, 2.2)

    def test_a_pending_event_is_served_before_the_next_sample(self):
        # The first sample takes so long that the next is due at once, with an event delivered meanwhile: a
        # debug event holds every thread, so a sample taken then reads a stopped thread as if it were running.
        kernel, result = self.run_case(self.GAME, timeout=2, sampler_cost=1.25, timed_events=[(0.5, debug_event(8))])
        sequence = [c for c in kernel.calls if c == "suspend" or c == ("continue", 200)]
        self.assertEqual(sequence[:4], [("continue", 200), "suspend", ("continue", 200), "suspend"])

    def test_a_stream_of_events_cannot_hold_the_run_open(self):
        # The game can raise events for ever. The run takes them for EVENT_GRACE past the deadline, then ends.
        kernel, result = self.run_case(self.GAME, timeout=2, stream_from=1.5)
        self.assertEqual(result["outcome"], "timeout")
        self.assertGreaterEqual(self.captured_at, 2.0 + runner.EVENT_GRACE)
        self.assertLess(self.captured_at, 2.0 + runner.EVENT_GRACE + 0.1)

    def test_a_crash_in_a_stream_counts_until_the_grace_runs_out(self):
        inside, outside = 2.0 + runner.EVENT_GRACE - 0.5, 2.0 + runner.EVENT_GRACE + 0.5
        kernel, result = self.run_case(self.GAME, timeout=2, stream_from=1.5, timed_events=[(inside, self.CRASH)])
        self.assertEqual(result["outcome"], "crash")
        kernel, result = self.run_case(self.GAME, timeout=2, stream_from=1.5, timed_events=[(outside, self.CRASH)])
        self.assertEqual(result["outcome"], "timeout")

    def test_a_hard_error_at_the_zero_wait_is_a_debugger_error(self):
        kernel, result = self.run_case(self.GAME, timeout=2, wait_error=True)
        self.assertEqual(result["outcome"], "debugger-error")
        self.assertEqual(self.captured_at, None)

    def test_a_one_off_hard_error_at_either_wait_ends_the_run_there(self):
        # A later wait that works must not carry the run on to the deadline and overwrite the error with "timeout".
        # The first call delivers the game's create event; the second finds nothing and a sample follows; the third
        # finds nothing with no sample due; the fourth is the waiting call.
        for failing in (2, 3, 4):
            kernel, result = self.run_case(self.GAME, timeout=2, wait_error_on=failing)
            self.assertEqual(result["outcome"], "debugger-error", failing)
            self.assertEqual(self.captured_at, None, failing)

    def test_an_event_due_before_the_deadline_still_counts(self):
        kernel, result = self.run_case(self.GAME, timeout=2, sampler_cost=0.25, timed_events=[(1.0, self.CRASH)])
        self.assertEqual(result["outcome"], "crash")

    def test_no_sampling_cost_is_the_old_timing(self):
        kernel, result = self.run_case(self.GAME, timeout=2)
        self.assertEqual(self.captured_at, 2.0)

    # main_stack runs before the reads that decide the label, so it may not leave the thread frozen for them.
    def test_main_stack_leaves_the_thread_running(self):
        with mock.patch.object(runner, "SPIN_SPAN", 0.0):
            kernel, result = self.run_case(self.GAME, timeout=2)
        self.assertEqual(result["outcome"], "timeout")
        self.assertEqual((kernel.suspends, kernel.resumes, kernel.suspended), (1, 1, 0))
        self.assertIn("main_stack", result)

    def test_a_failed_resume_in_main_stack_is_a_debugger_error(self):
        # The review's injection: it returned normally with the thread frozen, and the label went on being read.
        with mock.patch.object(runner, "SPIN_SPAN", 0.0):
            kernel, result = self.run_case(self.GAME, timeout=2, resume_fail_from=1)
        self.assertEqual(result["outcome"], "debugger-error")
        self.assertEqual(kernel.suspended, 1)
        self.assertEqual(kernel.resumes, runner.RESUME_ATTEMPTS)
        self.assertIn("ResumeThread:main-stack", [e["operation"] for e in result["debugger_errors"]])
        self.assertNotIn("main_stack", result)

    def test_a_resume_raising_in_main_stack_is_a_debugger_error(self):
        with mock.patch.object(runner, "SPIN_SPAN", 0.0):
            kernel, result = self.run_case(self.GAME, timeout=2, resume_raises=-1)
        self.assertEqual(result["outcome"], "debugger-error")
        self.assertIn("ResumeThread:main-stack", [e["operation"] for e in result["debugger_errors"]])

    def test_main_stack_does_not_read_a_thread_it_could_not_suspend(self):
        kernel = FakeKernel(FakeClock(), [], fail_suspend=True)
        with mock.patch.object(runner, "stack_words") as read:
            self.assertIsNone(runner.main_stack(kernel, 21, 22, 201))
        read.assert_not_called()
        self.assertEqual(kernel.resumes, 0)

    def test_main_stack_resumes_when_the_read_raises(self):
        kernel = FakeKernel(FakeClock(), [])
        with mock.patch.object(runner, "stack_words", side_effect=OSError("read")):
            with self.assertRaises(OSError):
                runner.main_stack(kernel, 21, 22, 201)
        self.assertEqual(kernel.suspended, 0)

    def test_main_stack_returns_what_it_read(self):
        kernel = FakeKernel(FakeClock(), [])
        with mock.patch.object(runner, "stack_words", return_value={"words": [1]}) as read:
            self.assertEqual(runner.main_stack(kernel, 21, 22, 201), {"words": [1]})
        read.assert_called_once_with(kernel, 21, 201, n=1024)


class TimedShotTests(unittest.TestCase):
    """--shots-at pictures the window through a run and decides nothing."""
    GAME = [debug_event(3, file_handle=31)]
    CRASH = debug_event(1, exception=0xC0000005, first_chance=0)
    run_case = RunnerDebugTests.run_case

    def shots(self, picture=None, **case):
        seen = []

        def capture(pid, path):
            seen.append(path.name)
            if isinstance(picture, Exception):
                raise picture
            return picture if picture is None or picture else {"black": False}
        with mock.patch.object(runner, "window_picture", side_effect=capture):
            kernel, result = self.run_case(self.GAME, **case)
        return kernel, result, seen

    def test_each_time_gets_its_own_picture_in_order(self):
        kernel, result, seen = self.shots({"black": True}, timeout=5, shots_at=[1.0, 3.0])
        self.assertEqual(result["outcome"], "timeout")
        self.assertEqual([s["at"] for s in result["timed_shots"]], [1.0, 3.0])
        self.assertEqual(seen, ["smoke_200_at00_1.png", "smoke_200_at01_3.png"])
        self.assertTrue(all(s["black"] for s in result["timed_shots"]))
        self.assertEqual([s["asked"] for s in result["timed_shots"]], [1.0, 3.0])

    def test_two_times_in_one_second_get_two_files(self):
        # The review's case: int(at) named both smoke_<pid>_at1.png, and the second overwrote the first.
        kernel, result, seen = self.shots({"black": True}, timeout=5, shots_at=[1.1, 1.9])
        self.assertEqual(len(set(seen)), 2)
        self.assertEqual([s["at"] for s in result["timed_shots"]], [1.1, 1.9])

    # The review's three scenarios: the flag may not change a run's outcome, last picture or hang evidence.
    def test_a_slow_shot_does_not_take_a_late_crash_into_the_run(self):
        kernel, result = self.run_case(self.GAME, timeout=5, shots_at=[4.0], shot_cost=1.5, timed_events=[(5.2, self.CRASH)])
        self.assertEqual(result["outcome"], "timeout")
        self.assertEqual(self.captured_at, 5.0)

    def test_a_slow_shot_does_not_move_the_last_picture(self):
        kernel, result = self.run_case(self.GAME, timeout=5, shots_at=[4.0], shot_cost=4.0)
        self.assertEqual(self.captured_at, 5.0)

    def test_a_slow_shot_leaves_the_hang_evidence_alone(self):
        def span(result):
            return runner.main_thread_span(result["spin_samples"], 0x400000, 0x80000000, result.get("spin_sample_failures", 0))
        _, plain = self.run_case(self.GAME, timeout=40, spinning=True)
        _, shot = self.run_case(self.GAME, timeout=40, spinning=True, shots_at=[15.0], shot_cost=4.0)
        self.assertTrue(span(plain)["spinning"])
        self.assertTrue(span(shot)["spinning"])
        self.assertEqual(span(shot)["largest_gap"], span(plain)["largest_gap"])
        self.assertEqual(shot["spin_samples"], plain["spin_samples"])

    def test_the_capture_runs_off_the_event_loop(self):
        self.run_case(self.GAME, timeout=3, shots_at=[1.0], shot_cost=0.5)
        self.assertEqual(len(self.shot_threads), 1)
        self.assertIsNot(self.shot_threads[0], threading.main_thread())
        self.assertTrue(self.shot_threads[0].daemon)       # a capture stuck for good may not keep the tool alive

    def test_a_capture_that_never_returns_cannot_hold_the_run(self):
        # PrintWindow can wait on a target stopped at a debug event, for good.
        stuck = threading.Event()
        self.addCleanup(stuck.set)

        def capture(pid, path):
            stuck.wait(30)
            return {"black": False}
        with mock.patch.object(runner, "window_picture", side_effect=capture), mock.patch.object(runner, "SHOT_WAIT", 0.05):
            kernel, result = self.run_case(self.GAME, timeout=3, shots_at=[1.0, 2.0])
        self.assertEqual(result["outcome"], "timeout")
        self.assertEqual(self.captured_at, 3.0)
        self.assertEqual([s["at"] for s in result["timed_shots"]], [1.0, 2.0])
        self.assertIn("not finished", result["timed_shots"][0]["why"])
        self.assertIn("skipped", result["timed_shots"][1]["why"])

    def test_after_the_run_the_worker_takes_nothing_more(self):
        # The re-check's case: past the wait, a queued shot would run during or after teardown.
        stuck, calls = threading.Event(), []
        self.addCleanup(stuck.set)

        def capture(pid, path):
            calls.append(threading.current_thread())
            stuck.wait(30)
            return {"black": False}
        with mock.patch.object(runner, "window_picture", side_effect=capture), mock.patch.object(runner, "SHOT_WAIT", 0.05):
            kernel, result = self.run_case(self.GAME, timeout=4, shots_at=[1.0, 2.0, 3.0])
            self.assertEqual([s["why"][:7] for s in result["timed_shots"]], ["not fin", "skipped", "skipped"])
            stuck.set()                                   # still patched: a worker that went on would be counted
            calls[0].join(10)
        self.assertFalse(calls[0].is_alive())
        self.assertEqual(len(calls), 1)

    def test_a_shot_that_finished_before_the_stuck_one_keeps_its_picture(self):
        stuck, calls = threading.Event(), []
        self.addCleanup(stuck.set)

        def capture(pid, path):
            calls.append(path)
            if len(calls) == 2:
                stuck.wait(30)
            return {"black": False}
        with mock.patch.object(runner, "window_picture", side_effect=capture), mock.patch.object(runner, "SHOT_WAIT", 0.2):
            kernel, result = self.run_case(self.GAME, timeout=4, shots_at=[1.0, 2.0, 3.0])
        self.assertEqual(result["timed_shots"][0]["black"], False)
        self.assertIn("not finished", result["timed_shots"][1]["why"])
        self.assertIn("skipped", result["timed_shots"][2]["why"])

    def test_any_error_in_a_capture_is_recorded_and_later_shots_still_run(self):
        calls = []

        def capture(pid, path):
            calls.append(path)
            if len(calls) == 1:
                raise ValueError("a picture PIL refused")
            return {"black": False}
        with mock.patch.object(runner, "window_picture", side_effect=capture):
            kernel, result = self.run_case(self.GAME, timeout=4, shots_at=[1.0, 2.0])
        self.assertIn("refused", result["timed_shots"][0]["why"])
        self.assertEqual(result["timed_shots"][1]["black"], False)

    def test_a_shot_named_after_a_late_look_is_still_asked_for_once(self):
        kernel, result, seen = self.shots({"black": True}, timeout=5, sampler_cost=3.0, shots_at=[1.0, 2.0])
        self.assertEqual(sorted(s["at"] for s in result["timed_shots"]), [1.0, 2.0])
        self.assertEqual(len(seen), 2)

    def test_a_time_before_the_game_exists_waits_for_it(self):
        with mock.patch.object(runner, "window_picture", return_value={"black": False}) as capture:
            kernel, result = self.run_case([], timeout=4, shots_at=[1.0], timed_events=[(2.0, self.GAME[0])])
        self.assertEqual(capture.call_args[0][0], 200)     # the game's pid, not a placeholder
        self.assertEqual([s["asked"] for s in result["timed_shots"]], [2.0])

    def test_no_times_no_pictures(self):
        kernel, result, seen = self.shots({"black": True}, timeout=3)
        self.assertEqual(seen, [])
        self.assertNotIn("timed_shots", result)

    def test_a_time_past_the_end_is_not_taken(self):
        kernel, result, seen = self.shots({"black": True}, timeout=2, shots_at=[1.0, 9.0])
        self.assertEqual([s["at"] for s in result["timed_shots"]], [1.0])

    def test_no_window_and_a_failed_capture_are_recorded_and_the_run_goes_on(self):
        kernel, result, seen = self.shots(None, timeout=3, shots_at=[1.0])
        self.assertEqual((result["outcome"], result["timed_shots"][0]["why"]), ("timeout", "no window"))
        kernel, result, seen = self.shots(OSError("no display"), timeout=3, shots_at=[1.0])
        self.assertEqual((result["outcome"], result["timed_shots"][0]["why"]), ("timeout", "no display"))

    def test_a_crash_after_a_shot_still_counts_and_stops_the_shots(self):
        kernel, result, seen = self.shots({"black": True}, timeout=5, shots_at=[1.0, 3.0], timed_events=[(2.0, self.CRASH)])
        self.assertEqual(result["outcome"], "crash")
        self.assertEqual([s["at"] for s in result["timed_shots"]], [1.0])

    def test_a_delivered_event_is_served_before_a_shot(self):
        # A debug event holds the game: a picture taken with one pending would show a stopped game.
        # The sample runs the clock to 1.25, past both: the event is pending when the shot falls due.
        kernel, result, seen = self.shots({"black": True}, timeout=3, sampler_cost=1.25, shots_at=[1.0], timed_events=[(1.0, self.CRASH)])
        self.assertEqual(result["outcome"], "crash")
        self.assertEqual(seen, [])

    def test_the_final_picture_stays_the_timeouts_own(self):
        kernel, result, seen = self.shots({"black": True}, timeout=3, shots_at=[1.0])
        self.assertIsNone(result["screenshot"])                  # the fixture's mock of the last picture, untouched

    def test_the_value_parses_sorted_and_refuses_nonsense(self):
        self.assertEqual(runner.shot_times("120,60,60"), [60.0, 120.0])
        self.assertEqual(runner.shot_times("1.1,1.9"), [1.1, 1.9])
        for bad in ("", "0", "-1,5", "x", "nan", "5,nan", "inf", "1,-inf"):
            with self.assertRaises(ValueError):
                runner.shot_times(bad)


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
                game_dir=Path("/mock-game"), guard=[], compat=None, no_focus_lie=True, shots_at=(), no_version_lie=True,
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
