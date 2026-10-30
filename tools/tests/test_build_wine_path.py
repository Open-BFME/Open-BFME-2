"""build's Wine launches leave nothing holding a caller's pipes: wine_path
(`winepath -w`) and the compile in try_compile_source."""
import os
import subprocess
import sys
import threading
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


# A stand-in for `wine cl.exe ... -showIncludes` that, like a compile booting
# Wine's services, leaves a long-lived process holding its stdout and stderr.
FAKE_CL = """\
import subprocess, sys
subprocess.Popen([sys.executable, "-c", "import time; time.sleep(60)"])
print("Note: including file: Z:/sdk/windows.h")
print("unit.cpp")
"""


@pytest.mark.skipif(os.name == "nt", reason="the compile runs cl through Wine only off Windows")
def test_a_compile_returns_while_a_process_it_started_holds_its_stdio(tmp_path, monkeypatch):
    sys.path.insert(0, str(TOOLS))
    import build
    fake_cl = tmp_path / "cl.py"
    fake_cl.write_text(FAKE_CL)
    seen = []
    monkeypatch.setattr(build, "compiler_command", lambda source, output: ([sys.executable, str(fake_cl)],
                                                                          dict(os.environ)))
    monkeypatch.setattr(build, "_cmd_fingerprint", lambda command, env: "fingerprint")
    monkeypatch.setattr(build, "_restore_object", lambda source, output, fingerprint: False)
    monkeypatch.setattr(build, "_write_deps_sidecar", lambda source, output, fingerprint, stdout, *rest:
                        seen.append(stdout))
    monkeypatch.setattr(build, "_store_object", lambda source, output, fingerprint: None)
    result = []
    worker = threading.Thread(target=lambda: result.append(
        build.try_compile_source(tmp_path / "unit.cpp", tmp_path / "out" / "unit.obj")), daemon=True)
    worker.start()
    worker.join(20)
    assert result, "the compile was still waiting on its output after 20 s"
    assert result[0] == (True, "unit.cpp", 0)
    # the dependency list still comes from the full output (-showIncludes notes included)
    assert seen == ["Note: including file: Z:/sdk/windows.h\nunit.cpp\n"]


# cl prints in its ANSI code page; 0x81 is undefined in cp1252 and invalid UTF-8.
FAKE_CL_ANSI = r"""
import sys
sys.stdout.buffer.write(b"Z:\\code\\caf\x81.cpp(2) : error C2059: syntax error : ';'\r\n")
sys.exit(2)
"""


def test_a_compile_whose_output_the_host_cannot_decode_still_reports_it(tmp_path, monkeypatch):
    sys.path.insert(0, str(TOOLS))
    import build
    fake_cl = tmp_path / "cl.py"
    fake_cl.write_text(FAKE_CL_ANSI)
    monkeypatch.setattr(build, "compiler_command", lambda source, output: ([sys.executable, str(fake_cl)],
                                                                          dict(os.environ)))
    monkeypatch.setattr(build, "_cmd_fingerprint", lambda command, env: "fingerprint")
    monkeypatch.setattr(build, "_restore_object", lambda source, output, fingerprint: False)
    ok, text, code = build.try_compile_source(tmp_path / "unit.cpp", tmp_path / "out" / "unit.obj")
    assert (ok, code) == (False, 2)
    assert "error C2059: syntax error" in text and "\ufffd" in text
