"""Modern build outputs must never alias the reference verifier's cache."""
import json
import os
import subprocess
import shutil
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build_variant as V


def redirect(link, target):
    if os.name == "nt":
        result = subprocess.run(["cmd", "/c", "mklink", "/J", str(link), str(target)],
                                capture_output=True, text=True)
        assert result.returncode == 0, result.stdout + result.stderr
    else:
        link.symlink_to(target, target_is_directory=True)


def test_paths_are_separate_and_read_only(tmp_path):
    paths = V.variant_paths(tmp_path, "modern")
    assert paths == {name: tmp_path / "build" / "modern" / name
                     for name in ("objects", "link", "reports")}
    assert not (tmp_path / "build").exists()


@pytest.mark.parametrize("variant", ["reference", "../match", "", "Modern", "modern/../match"])
def test_refuses_non_modern_variant(tmp_path, variant):
    with pytest.raises(ValueError):
        V.variant_paths(tmp_path, variant)


def test_refuses_output_symlink(tmp_path):
    outside = tmp_path / "outside"
    outside.mkdir()
    (tmp_path / "build").mkdir()
    redirect(tmp_path / "build/modern", outside)
    with pytest.raises(ValueError, match="redirect"):
        V.variant_paths(tmp_path, "modern")


def test_refuses_redirected_child(tmp_path):
    match = tmp_path / "build/match"
    match.mkdir(parents=True)
    (tmp_path / "build/modern").mkdir()
    redirect(tmp_path / "build/modern/objects", match)
    with pytest.raises(ValueError, match="redirect"):
        V.variant_paths(tmp_path, "modern")


def test_plan_has_explicit_non_verified_identity(tmp_path, capsys):
    assert V.main(["--plan"], root=tmp_path) == 0
    report = json.loads(capsys.readouterr().out)
    assert report["variant"] == "modern"
    assert report["action"] == "plan"
    assert report["compiled"] is False
    assert report["defines"] == ["BFME2_MODERN=1"]
    assert not (tmp_path / "build").exists()


def test_no_implicit_success_without_an_action(tmp_path):
    with pytest.raises(SystemExit) as error:
        V.main([], root=tmp_path)
    assert error.value.code == 2


def test_no_arbitrary_output_override(tmp_path):
    with pytest.raises(SystemExit) as error:
        V.main(["--plan", "--out", "build/match"], root=tmp_path)
    assert error.value.code == 2


def test_refuses_regular_file_as_output(tmp_path):
    (tmp_path / "build/modern").mkdir(parents=True)
    (tmp_path / "build/modern/link").write_text("keep me")
    with pytest.raises(ValueError, match="is a file"):
        V.variant_paths(tmp_path, "modern")
    assert (tmp_path / "build/modern/link").read_text() == "keep me"


@pytest.mark.parametrize("arguments, module, forwarded, code", [
    (["Code/source with spaces.cpp"], "build.py", ["Code/source with spaces.cpp"], 0),
    (["--variant", "modern", "--plan"], "build_variant.py", ["--plan"], 0),
    (["--variant", "reference"], None, [], 2),
])
def test_shell_dispatch_preserves_default(tmp_path, arguments, module, forwarded, code):
    # Substitute only Python, so this exercises the actual shell routing without
    # compiling the entire reference game. The receiver prints its exact argv.
    receiver = tmp_path / "python3"
    receiver.write_text('#!/bin/sh\nprintf \'%s\\n\' "$@"\n', newline="\n")
    receiver.chmod(0o755)
    if os.name == "nt":
        bash = Path(os.environ.get("ProgramFiles", "C:/Program Files")) / "Git/bin/bash.exe"
        prefix = 'export PATH="$(cygpath -u "$1"):$PATH"; '
    else:
        bash = shutil.which("bash")
        prefix = 'export PATH="$1:$PATH"; '
    assert bash, "Bash is required to test build.sh"
    result = subprocess.run([str(bash), "-c", prefix + 'exec bash "$2" "${@:3}"',
                             "variant-test", str(tmp_path), str(V.ROOT / "build.sh"), *arguments],
                            capture_output=True, text=True)
    assert result.returncode == code, result.stderr
    if module:
        lines = result.stdout.splitlines()
        assert lines[0].endswith("/tools/" + module)
        assert lines[1:] == forwarded
    else:
        assert not result.stdout
