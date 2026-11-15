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
import build as B
import exit_link as E


def test_link_input_manifest_covers_objects_libraries_and_control_files(tmp_path):
    folder = tmp_path / "link"
    folder.mkdir()
    rsp = folder / "exit.rsp"
    rsp.write_text('"a.obj"\n"runtime.lib"\n"resource.obj"\n/DEF:"link/retail.def"\n')
    for name in ("a.obj", "runtime.lib", "resource.obj", "link/retail.def"):
        (tmp_path / name).write_bytes(name.encode())
    before = V.link_input_manifest(rsp, root=tmp_path)
    assert {entry["path"] for entry in before} == {
        "a.obj", "runtime.lib", "resource.obj", "link/retail.def", "link/exit.rsp"}
    assert all(len(entry["sha256"]) == 64 for entry in before)
    (tmp_path / "runtime.lib").write_bytes(b"changed")
    assert V.link_input_manifest(rsp, root=tmp_path) != before


def test_link_input_manifest_refuses_missing_input(tmp_path):
    rsp = tmp_path / "exit.rsp"
    rsp.write_text('"missing.obj"\n')
    (tmp_path / "retail.def").write_text("EXPORTS\n")
    with pytest.raises(FileNotFoundError):
        V.link_input_manifest(rsp, root=tmp_path)


def test_local_base_link_is_scoped_and_preserves_failure(tmp_path, monkeypatch):
    monkeypatch.setattr(E, "ROOT", tmp_path)
    original = tmp_path / "build/exit_link"
    monkeypatch.setattr(E, "OUT", original)
    def link(rows, *, native_output):
        assert rows == ["test-row"]
        assert E.OUT == native_output
        assert native_output.parent == tmp_path / "build/modern/link"
        assert native_output.is_dir()
        return 1
    monkeypatch.setattr(E, "run_link", link)
    assert E.run_local_base(["test-row"]) == 1
    assert E.OUT == original
    assert not original.exists()


def test_local_base_link_restores_scope_on_refusal(tmp_path, monkeypatch):
    monkeypatch.setattr(E, "ROOT", tmp_path)
    original = E.OUT
    def refuse(*args, **kwargs):
        raise SystemExit("proof refused")
    monkeypatch.setattr(E, "run_link", refuse)
    with pytest.raises(SystemExit, match="proof refused"):
        E.run_local_base([])
    assert E.OUT == original


def test_native_link_rejects_reference_directory(tmp_path, monkeypatch):
    monkeypatch.setattr(E, "ROOT", tmp_path)
    monkeypatch.setattr(E, "OUT", tmp_path / "build/exit_link")
    with pytest.raises(ValueError, match="isolated"):
        E.run_link([], native_output=E.OUT)


def test_context_refuses_reference_output(tmp_path, monkeypatch):
    monkeypatch.setattr(B, "ROOT", tmp_path)
    context = B.CompilationContext()
    with pytest.raises(ValueError):
        context.validate_output(tmp_path / "build/match/example.obj")
    assert not (tmp_path / "build").exists()


def test_context_does_not_change_reference_globals(tmp_path, monkeypatch):
    before = B.BUILD_DIR
    monkeypatch.setattr(B, "ROOT", tmp_path)
    context = B.CompilationContext()
    context.validate_output(tmp_path / "build/modern/objects/example.obj")
    assert context.defines == ("BFME2_MODERN=1",)
    assert B.BUILD_DIR == before


def test_context_rejects_hardlinked_object(tmp_path, monkeypatch):
    monkeypatch.setattr(B, "ROOT", tmp_path)
    original = tmp_path / "reference.obj"
    original.write_bytes(b"reference")
    out = tmp_path / "build/modern/objects/other.obj"
    out.parent.mkdir(parents=True)
    os.link(original, out)
    with pytest.raises(ValueError, match="linked"):
        B.CompilationContext().validate_output(out)
    assert original.read_bytes() == b"reference"


def test_compile_rejects_all_inputs_before_writing(tmp_path):
    good = tmp_path / "Code/good.cpp"
    good.parent.mkdir()
    good.write_text("int x;")
    with pytest.raises(ValueError, match="source"):
        V.compile_sources(["Code/good.cpp", "../outside.cpp"], root=tmp_path)
    assert not (tmp_path / "build").exists()


def test_compile_uses_context_and_requires_current_receipt(tmp_path, monkeypatch):
    source = tmp_path / "Code/example.cpp"
    source.parent.mkdir()
    source.write_text("int x;")
    monkeypatch.setattr(B, "ROOT", tmp_path)
    calls = []

    def compile_one(src, out, *, inventory, context):
        assert src == source and inventory
        context.validate_output(out)
        out.parent.mkdir(parents=True, exist_ok=True)
        out.write_bytes(b"test object")
        calls.append(out)

    monkeypatch.setattr(B, "compile_source", compile_one)
    monkeypatch.setattr(B, "compile_is_current", lambda *a, **kw: False)
    with pytest.raises(ValueError, match="receipt"):
        V.compile_sources(["Code/example.cpp"], root=tmp_path)
    assert len(calls) == 1
    assert not (tmp_path / "build/match").exists()


def test_variant_receipt_rejects_reference_command_and_changed_object(tmp_path, monkeypatch):
    monkeypatch.setattr(B, "ROOT", tmp_path)
    source = tmp_path / "example.cpp"
    source.write_text("int answer = 42;")
    output = tmp_path / "build/modern/objects/example.obj"
    output.parent.mkdir(parents=True)
    output.write_bytes(b"original object")
    context = B.CompilationContext()

    def command(src, out, *, context=None):
        return ["cl", *(["-DBFME2_MODERN=1"] if context else [])], {}

    monkeypatch.setattr(B, "compiler_command", command)
    monkeypatch.setattr(B, "_legacy_header_free", lambda *args: True)
    payload = {"source": B._hash_file(str(source)), "object": B._hash_file(str(output)),
               "deps": {}, "cmd": B._cmd_fingerprint(*command(source, output, context=context))}
    B._deps_sidecar(output).write_text(json.dumps(payload))
    assert B.compile_is_current(source, output, strict=True, context=context)
    assert not B.compile_is_current(source, output, strict=True)
    output.write_bytes(b"replaced object with different bytes")
    assert not B.compile_is_current(source, output, strict=True, context=context)


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
