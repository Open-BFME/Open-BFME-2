"""Native Windows rehoming still requires a successful gate and exact bodies."""
import sys
import unittest
from pathlib import Path
from types import SimpleNamespace
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import rehome_rows


class RehomeVerificationTests(unittest.TestCase):
    def verify(self, *, returncode=0, stdout="Functions: OK 1/1 matched", emitted=b"retail", unresolved=()):
        def native_run(command, **kwargs):
            # A Windows process cannot execute the Bash build.sh entry point.
            if command[0].endswith(".sh") or command[0] == "python3":
                raise OSError("not a native executable")
            self.assertEqual(command[0], sys.executable)
            self.assertEqual(Path(command[1]).name, "build.py")
            return SimpleNamespace(returncode=returncode, stdout=stdout)

        with (patch.object(rehome_rows.sys, "platform", "win32"),
              patch.object(rehome_rows.subprocess, "run", side_effect=native_run),
              patch.object(rehome_rows, "_SYMBOLS", {}),
              patch.object(rehome_rows.build, "obj_path", return_value=Path("home.obj")),
              patch.object(rehome_rows.build, "compile_function", return_value={
                  "bytes": emitted, "target": b"retail", "unresolved": unresolved
              }) as compile_body):
            accepted = rehome_rows.all_exact([{"name": "body"}], "Code/Home.cpp")
            return accepted, compile_body.call_count

    def test_native_windows_gate_accepts_only_exact_body(self):
        self.assertEqual(self.verify(), (True, 1))
        self.assertEqual(self.verify(emitted=b"different"), (False, 1))
        self.assertEqual(self.verify(unresolved=("missing",)), (False, 1))

    def test_failed_gate_never_checks_or_rehomes_old_object(self):
        self.assertEqual(self.verify(returncode=1), (False, 0))

    def test_empty_success_output_is_not_gate_proof(self):
        self.assertEqual(self.verify(stdout=""), (False, 0))


if __name__ == "__main__":
    unittest.main()
