"""build.wine_path: path conversion through `winepath -w` under Wine."""
import os
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]

# A stand-in for winepath that, like the first Wine program under a persistent
# wineserver, leaves behind a long-lived process (services.exe, winedevice.exe
# ...) holding every stdio stream it inherited.
FAKE_WINEPATH = """\
import subprocess, sys, time
subprocess.Popen([sys.executable, "-c", "import time; time.sleep(60)"])
print("Z:" + sys.argv[-1].replace("/", "\\\\"))
"""


@pytest.mark.skipif(os.name == "nt", reason="winepath runs only off Windows")
def test_wine_path_leaves_nothing_holding_the_callers_pipes(tmp_path):
    bin_dir = tmp_path / "bin"
    bin_dir.mkdir()
    winepath = bin_dir / "winepath"
    winepath.write_text(f"#!{sys.executable}\n" + FAKE_WINEPATH)
    winepath.chmod(0o755)
    caller = ("import sys; sys.path.insert(0, sys.argv[1]); import build; "
              "print(build.wine_path('/home/user/unit.cpp'))")
    env = dict(os.environ, PATH=f"{bin_dir}{os.pathsep}{os.environ.get('PATH', '')}")
    # what a boat.dev command or a hook does: wait for EOF on the tool's output
    done = subprocess.run([sys.executable, "-c", caller, str(TOOLS)], env=env,
                          stdin=subprocess.DEVNULL, capture_output=True, text=True, timeout=20)
    assert done.returncode == 0, done.stderr
    assert done.stdout.strip() == "Z:\\home\\user\\unit.cpp"


@pytest.mark.skipif(os.name == "nt", reason="winepath runs only off Windows")
def test_a_failing_winepath_still_reports_its_error(tmp_path, monkeypatch):
    sys.path.insert(0, str(TOOLS))
    import build
    bin_dir = tmp_path / "bin"
    bin_dir.mkdir()
    winepath = bin_dir / "winepath"
    winepath.write_text(f"#!{sys.executable}\nimport sys\nprint('no drive', file=sys.stderr)\nsys.exit(3)\n")
    winepath.chmod(0o755)
    monkeypatch.setenv("PATH", f"{bin_dir}{os.pathsep}{os.environ.get('PATH', '')}")
    monkeypatch.setattr(build, "_WINE_PATH_CACHE", {})
    with pytest.raises(subprocess.CalledProcessError) as failure:
        build.wine_path("/nowhere/unit.cpp")
    assert failure.value.returncode == 3 and "no drive" in failure.value.stderr
