"""Reproduce baseline failures using the immutable original module, in memory.

This is a diagnostic control, not a gate or a replacement for the current module.
The expected exit is nonzero while the unrelated baseline failures remain.
"""
import subprocess
import sys
import types
from pathlib import Path
ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT / "tools"))
source = subprocess.check_output(["git", "cat-file", "blob", "3e1f26fe7960113b25f8769414b774143e88df2e"], cwd=ROOT)
module = types.ModuleType("rename")
module.__file__ = str(ROOT / "tools" / "rename.py")
sys.modules["rename"] = module
exec(compile(source, module.__file__, "exec"), module.__dict__)
import pytest
raise SystemExit(pytest.main(["-q", str(ROOT / "tools/tests/test_rename_commit_checks.py"),
                             str(ROOT / "tools/tests/test_rename_iniblock.py")]))
