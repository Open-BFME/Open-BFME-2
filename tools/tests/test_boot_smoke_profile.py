"""boot_smoke's protection of the owner's profile (also used by game_smoke).

Nothing here starts the game: the redirect is checked as code (its bytes, its
installation against a fake process) and every refusal is checked to happen
before a process could be created.
"""
import ctypes
import os
import struct
import sys
import tempfile
import time
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import boot_smoke as bs  # noqa: E402

RETAIL = bs.boot_image.build.EXE


class SandboxAppdata(unittest.TestCase):
    REAL = r"C:\Users\Someone\AppData\Roaming"

    def test_real_appdata_and_anything_inside_it_are_refused(self):
        for bad in (self.REAL, self.REAL + "\\", self.REAL.upper(), self.REAL + r"\sandbox",
                    self.REAL + r"\My Battle for Middle-earth II Files"):
            with self.assertRaises(bs.RedirectError, msg=bad):
                bs.check_sandbox_appdata(bad, real=self.REAL)

    def test_a_sibling_with_a_common_prefix_is_allowed(self):     # negative control
        for ok in (self.REAL + "2", r"C:\Users\Someone\AppData\Roaming-sandbox", r"D:\scratch\appdata"):
            self.assertEqual(bs.check_sandbox_appdata(ok, real=self.REAL), Path(ok))

    def test_the_default_real_appdata_is_refused(self):
        with self.assertRaises(bs.RedirectError):
            bs.check_sandbox_appdata(bs.real_appdata())

    def test_profile_is_seeded_once_and_never_overwritten(self):
        with tempfile.TemporaryDirectory() as d:
            prof = bs.prepare_sandbox_profile(d, real=r"C:\nowhere")
            self.assertEqual(prof, Path(d) / bs.PROFILE_LEAF)
            self.assertEqual((prof / "Options.ini").read_text(), bs.SANDBOX_OPTIONS)
            (prof / "Options.ini").write_text("StaticGameLOD = High\n")
            bs.prepare_sandbox_profile(d, real=r"C:\nowhere")
            self.assertEqual((prof / "Options.ini").read_text(), "StaticGameLOD = High\n")

    def test_seeded_options_skip_the_first_start_benchmark(self):
        keys = dict(line.split(" = ") for line in bs.SANDBOX_OPTIONS.splitlines())
        self.assertIn("IdealStaticGameLOD", keys)                  # its absence triggers the benchmark
        self.assertEqual(keys["Resolution"], "1024 768")

    def test_preparing_inside_real_appdata_refuses_before_writing(self):
        with tempfile.TemporaryDirectory() as d:
            with self.assertRaises(bs.RedirectError):
                bs.prepare_sandbox_profile(Path(d) / "x", real=d)
            self.assertEqual(os.listdir(d), [])


class AppdataStub(unittest.TestCase):
    MEM, ORIG = 0x01230000, 0x76543210

    def disasm(self, path=r"C:\sandbox\appdata"):
        from capstone import Cs, CS_ARCH_X86, CS_MODE_32
        blob = bs.appdata_stub(self.MEM, self.ORIG, path)
        code = blob[:blob.index(b"\xC2\x10\x00") + 3]
        return blob, [(i.address, i.mnemonic, i.op_str) for i in Cs(CS_ARCH_X86, CS_MODE_32).disasm(code, self.MEM)]

    def test_layout_orig_pointer_and_wide_path(self):
        blob, _ = self.disasm()
        self.assertEqual(struct.unpack_from("<I", blob, 0x80)[0], self.ORIG)
        self.assertEqual(blob[0x100:], "C:\\sandbox\\appdata\0".encode("utf-16-le"))

    def test_appdata_and_pictures_redirect_everything_else_reaches_the_real_call(self):
        _, ins = self.disasm()
        text = [f"{m} {o}" for _, m, o in ins]
        self.assertEqual(text[:7], ["mov eax, dword ptr [esp + 0xc]", "and eax, 0xff", "cmp eax, 0x1a",
                                    f"je {ins[7][0]:#x}", "cmp eax, 0x27", f"je {ins[7][0]:#x}",
                                    f"jmp dword ptr [{self.MEM + 0x80:#x}]"])
        redirect = text[7:]
        self.assertEqual(redirect, ["push esi", "push edi", "mov edi, dword ptr [esp + 0x10]",
                                    f"mov esi, {self.MEM + 0x100:#x}", f"mov ecx, {len(r'C:/sandbox/appdata') * 2 + 2:#x}",
                                    "rep movsb byte ptr es:[edi], byte ptr [esi]", "pop edi", "pop esi",
                                    "mov eax, 1", "ret 0x10"])

    def test_paths_beyond_max_path_are_refused(self):
        with self.assertRaises(bs.RedirectError):
            bs.appdata_stub(self.MEM, self.ORIG, "C:\\" + "x" * 300)


class FakeProcess:
    """kernel32 stand-in over a dict of bytes: enough for install_appdata_lie."""

    def __init__(self, mem=None, alloc=0x02000000, drop_writes=False):
        self.mem, self.alloc, self.drop = dict(mem or {}), alloc, drop_writes
        self.VirtualAllocEx = lambda *a: self.alloc

    def VirtualProtectEx(self, *a):
        return 1

    def ReadProcessMemory(self, h, va, buf, n, got):
        data = bytes(self.mem.get(va.value + i, 0) for i in range(n))
        ctypes.memmove(buf, data, n)
        got._obj.value = n
        return 1

    def WriteProcessMemory(self, h, va, data, n, _):
        if not self.drop:
            for i, b in enumerate(bytes(data)[:n]):
                self.mem[va.value + i] = b
        return 1

    def u32(self, va):
        return struct.unpack("<I", bytes(self.mem.get(va + i, 0) for i in range(4)))[0]


@unittest.skipUnless(RETAIL.exists(), "no retail game.dat")
class InstallRedirect(unittest.TestCase):
    BASE = 0x400000

    def slot(self):
        import pefile
        pe = pefile.PE(str(RETAIL), fast_load=True)
        pe.parse_data_directories([1])
        va = [i.address for d in pe.DIRECTORY_ENTRY_IMPORT for i in d.imports
              if i.name == b"SHGetSpecialFolderPathW"][0]
        pe.close()
        return va

    def test_slot_points_at_the_stub_and_keeps_the_real_function(self):
        slot = self.slot()
        k = FakeProcess({slot + i: b for i, b in enumerate(struct.pack("<I", 0x77001234))})
        with tempfile.TemporaryDirectory() as d:
            info = bs.install_appdata_lie(k, 1, self.BASE, RETAIL, d)
        self.assertEqual(info["slot"], hex(slot))
        self.assertEqual(k.u32(slot), k.alloc)
        self.assertEqual(k.u32(k.alloc + 0x80), 0x77001234)

    def test_a_write_that_does_not_stick_refuses(self):              # positive control
        with tempfile.TemporaryDirectory() as d, self.assertRaises(bs.RedirectError):
            bs.install_appdata_lie(FakeProcess(drop_writes=True), 1, self.BASE, RETAIL, d)

    def test_no_stub_memory_refuses(self):
        with tempfile.TemporaryDirectory() as d, self.assertRaises(bs.RedirectError):
            bs.install_appdata_lie(FakeProcess(alloc=0), 1, self.BASE, RETAIL, d)

    def test_an_image_without_the_import_refuses(self):
        with tempfile.TemporaryDirectory() as d, self.assertRaises(bs.RedirectError):
            bs.install_appdata_lie(FakeProcess(), 1, self.BASE, sys.executable, d)

    def test_real_appdata_refuses_before_touching_the_process(self):
        k = FakeProcess()
        with self.assertRaises(bs.RedirectError):
            bs.install_appdata_lie(k, 1, self.BASE, RETAIL, bs.real_appdata())
        self.assertEqual(k.mem, {})

    def test_focus_arm_is_unique_in_retail(self):
        self.assertIsNotNone(bs.focus_arm_rva(RETAIL))


class OwnerProfileGuard(unittest.TestCase):
    def test_unchanged_profile_has_no_diff(self):
        with tempfile.TemporaryDirectory() as d:
            (Path(d) / "Options.ini").write_text("Resolution = 800 600\n")
            self.assertEqual(bs.profile_diff(bs.profile_snapshot(d), bs.profile_snapshot(d)), [])

    def test_rewritten_options_is_caught_even_with_same_size_and_mtime(self):
        with tempfile.TemporaryDirectory() as d:
            opt = Path(d) / "Options.ini"
            opt.write_text("Resolution = 800 600\n")
            st = opt.stat()
            before = bs.profile_snapshot(d)
            opt.write_text("Resolution = 640 480\n")              # same length
            os.utime(opt, ns=(st.st_atime_ns, st.st_mtime_ns))    # and the old mtime
            self.assertEqual(bs.profile_diff(before, bs.profile_snapshot(d)), ["Options.ini (content)"])

    def test_new_save_and_touched_file_are_caught(self):
        with tempfile.TemporaryDirectory() as d:
            f = Path(d) / "Skirmish.ini"
            f.write_text("a")
            before = bs.profile_snapshot(d)
            later = time.time_ns() + 5_000_000_000
            os.utime(f, ns=(later, later))
            (Path(d) / "Save").mkdir()
            (Path(d) / "Save" / "x.BfME2Skirmish").write_bytes(b"x")
            self.assertEqual(bs.profile_diff(before, bs.profile_snapshot(d)),
                             [str(Path("Save/x.BfME2Skirmish")), "Skirmish.ini"])

    def test_guard_object_reports_touched_profile(self):
        with tempfile.TemporaryDirectory() as d:
            (Path(d) / "Options.ini").write_text("a = 1\n")
            g = bs.ProfileGuard(d)
            report, touched = g.check()
            self.assertFalse(touched)
            self.assertEqual(report["changed"], [])
            (Path(d) / "Options.ini").write_text("a = 2\n")
            report, touched = g.check()
            self.assertTrue(touched)
            self.assertIn("Options.ini (content)", report["changed"])

    def test_missing_profile_snapshot_is_empty(self):
        self.assertEqual(bs.profile_snapshot(Path(tempfile.gettempdir()) / "no-such-profile-dir"),
                         {"files": {}, "options_sha256": None})


class RefusesBeforeLaunch(unittest.TestCase):
    """Every entry point refuses the real AppData before a process exists (the
    launcher path below does not even exist, so a launch would fail loudly)."""

    def test_run_requires_a_sandbox(self):
        with self.assertRaises(TypeError):
            bs.run(Path("Z:/nope/lotrbfme2.exe"), Path("Z:/nope"), "-win", 1)
        with self.assertRaises(bs.RedirectError):
            bs.run(Path("Z:/nope/lotrbfme2.exe"), Path("Z:/nope"), "-win", 1, appdata=bs.real_appdata())

    def test_boot_smoke_cli_refuses_real_appdata(self):
        with self.assertRaises(SystemExit) as e:
            bs.main(["--game-dir", "Z:/nope", "--retail", "--appdata", str(bs.real_appdata())])
        self.assertIn("real AppData", str(e.exception))

    def test_game_smoke_refuses_real_appdata(self):
        import game_smoke
        with self.assertRaises(SystemExit) as e:
            game_smoke.main(["skirmish", "--game-dir", "Z:/nope", "--retail", "--appdata", str(bs.real_appdata())])
        self.assertIn("real AppData", str(e.exception))
        with self.assertRaises(bs.RedirectError):
            game_smoke.Game(Path("Z:/nope"), "-win", bs.real_appdata())


if __name__ == "__main__":
    unittest.main()
