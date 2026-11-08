"""tools/cl_flags.py: the `// cl:` flags a source may carry, as the gate and build.py apply them."""
import os
import shutil
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
import build  # noqa: E402
import cl_flags  # noqa: E402

DANGEROUS = [
    "/B1 x.dll", "/B1x.dll", "/B2 x.dll", "/B2Z:\\x.dll", "/Bxpp.exe", "/Bd", "/Bt",
    "/Fax.cod", "/FAsc", "/FaZ:\\home\\claude\\.bashrc", "/Fo/tmp/x.obj", "/Fdx.pdb", "/Fex.exe",
    "/Fmx.map", "/FRx.sbr", "/Frx.sbr", "/Fpx.pch", "/Fx", "/Fix.i",
    "/Yc", "/Ycpre.h", "/Yupre.h", "/YX", "/Yl", "/Y-",
    "/link /out:x", "@x.rsp", "@Z:\\x.rsp", "/P", "/E", "/EP", "/clr", "/AIdir", "/FUx.dll",
    "/clang:-fplugin=x.so", "/clang:-Xclang", "/clang:-load", "/clang:-plugin", "/clang:-mtune=native",
    "/clang:@x.rsp", "/d1reportAllClassLayout", "/d2Zi+", "/Zi", "/doc",
]
# Codex security review of f30e3b5270, P1 1: a response file given as an argument.
RESPONSE_FILES = ["/I @Code/evil.rsp", "-I @Code/evil.rsp", "/I@Code/evil.rsp", '/I"@Code/evil.rsp"',
                  "/FI@Code/evil.rsp", "/DX=@evil.rsp", "/clang:-mllvm @Code/evil.rsp"]
OUTSIDE = [
    "/I/etc", '/I"Z:\\home"', "/IC:/sdk", "/I../../x", "/I..\\x", "/ICode/../../x", "/I //server/share",
    "/I /etc", "-I ../x", "/FI/etc/passwd", "/FI../x.h",
    '/FI"Z:\\secret\\evil.h"',              # P2: a quoted /FI value
]
ALLOWED = (
    "/O1 /O2 /Ox /Od /Os /Ot /Og /Og- /Oi /Oi- /Oy /Oy- /Oa /Ow /Op /Ob0 /Ob1 /Ob2 /G5 /G6 /G7 /GX /GX- "
    "/GR /GR- /GS /GS- /GF /GF- /GZ /Gy /Gz /Gs /Gs4096 /EHsc /EHs /EHa /EHs-c- /EHsc- /EHc- /EHs- "
    "/arch:SSE /arch:SSE2 /arch:IA32 /Z7 /Ze /Zc:wchar_t /vmg /vmm /vd0 /vd1 /vd2 /RTCu /RTC1 /TP /TC "
    "/hotpatch /QIfist /QI0f /MD /MT /DNDEBUG /D_STLP_NO_EXCEPTIONS /DWINVER=0x0400 /UFOO /d1Binl "
    "/d2inlS100 /d2Gmanaged /clang:-mllvm /clang:-branch-folder-reorder-blocks=false /clang:-mno-sse "
    "/clang:-mno-sse2 /clang:-mmmx /clang:-fno-math-errno /clang:-mfpmath=387 /clang:-tail-dup-size=20 "
    "/clang:-tail-dup-placement=true /clang:-tail-dup-placement-threshold=20 "
    '/ICode/Libraries/Include /I"reference/shims/a b" /I reference/shims/sweep -I Code /FIzh_ascii.h'
)
# P1 2: line breaks str.splitlines honours and git does not.
BREAKS = ["\u2028", "\u2029", "\x85", "\v", "\f", "\x1c", "\x1d", "\x1e", "\r"]


def tokens(line):
    return build._source_flag_tokens(line)


def in_checkout():
    return {"root": str(build.ROOT), "trusted": build._trusted_include_links()}


def link(target, at):
    """A directory symlink, or skip where this account cannot make one."""
    try:
        os.symlink(target, at, target_is_directory=True)
    except (OSError, NotImplementedError) as error:
        pytest.skip(f"symlinks unavailable here ({error}): Windows needs Developer Mode or admin rights")


@pytest.fixture
def scratch():
    """A directory inside the checkout (compiler_command takes only its sources), removed after."""
    path = build.ROOT / "build" / "test_cl_flags"
    path.mkdir(parents=True, exist_ok=True)
    cl_flags.forget()
    yield path
    shutil.rmtree(path, ignore_errors=True)
    cl_flags.forget()


def test_every_flag_master_s_sources_carry_passes():
    # Every first `// cl:` line build.source_extra_flags reads under Code/, and the banked
    # attempts' and generators' flag lines (two reverse/ notes are prose, never compiled).
    out = subprocess.run(["git", "-C", str(build.ROOT), "grep", "-n", "-I", "^// cl:", "--", "Code", "tools",
                          "reverse/attempts"], capture_output=True, text=True, encoding="utf-8",
                         errors="replace").stdout
    seen, refused = set(), []
    for line in out.splitlines():
        path, _number, text = line.split(":", 2)
        if path in seen:
            continue
        seen.add(path)
        found = cl_flags.problems(tokens(text[len("// cl:"):]), **in_checkout())
        if found:
            refused.append((path, cl_flags.describe(found)))
    assert len(seen) > 15000
    assert refused == []


@pytest.mark.parametrize("line", DANGEROUS)
def test_a_flag_that_loads_code_or_writes_files_is_refused(line):
    found = cl_flags.problems(tokens("/O2 " + line + " /MD"))
    assert found and found[0][0] == line.split()[0]


@pytest.mark.parametrize("line", RESPONSE_FILES)
def test_a_response_file_is_refused_as_a_flag_or_an_argument(line):
    assert cl_flags.problems(tokens("/O2 " + line))


@pytest.mark.parametrize("line", OUTSIDE)
def test_an_include_path_outside_the_checkout_is_refused(line):
    found = cl_flags.problems(tokens(line))
    assert found and found[0][1].startswith("include path")


def test_the_flag_families_in_use_pass():
    assert cl_flags.problems(tokens(ALLOWED), **in_checkout()) == []


def test_prose_is_refused_as_not_a_flag():
    assert [reason for _, reason in cl_flags.problems(tokens("(none, base flags)"))] == ["is not a flag"] * 3


# ------------------------------------------------- the include walk (security re-check of 488d80c460)
@pytest.fixture
def tree(tmp_path):
    """A checkout: Code/Real, Code/lowerlink -> outside, reference/open-bfme-1/{game,review_link}."""
    root, outside = tmp_path / "checkout", tmp_path / "outside"
    (root / "Code/Real").mkdir(parents=True)
    (root / "reference/open-bfme-1/game").mkdir(parents=True)
    outside.mkdir()
    (outside / "sentinel.h").write_text("#error outside\n", encoding="utf-8")
    link(outside, root / "Code/lowerlink")
    link(outside, root / "reference/open-bfme-1/review_link")
    cl_flags.forget()
    yield root
    cl_flags.forget()


def test_the_walk_passes_real_directories_spelt_as_on_disk(tree):
    walk = lambda path, trusted=(): cl_flags.walk(str(tree), path, trusted)  # noqa: E731
    assert walk("Code/Real") is None
    assert walk("reference/open-bfme-1/game") is None
    assert walk("Code/Missing/deeper") is None                  # nothing there for the compiler to read


def test_a_case_variant_of_a_link_is_refused(tree):
    # P1: realpath() on a case-sensitive host does not resolve Code/LOWERLINK; Wine opens
    # Code/lowerlink and follows it out.
    assert cl_flags.walk(str(tree), "Code/LOWERLINK") == "differs in case from its directory entry"
    assert cl_flags.walk(str(tree), "Code/LowerLink/sentinel.h") == "differs in case from its directory entry"
    assert cl_flags.walk(str(tree), "code/Real") == "differs in case from its directory entry"
    assert cl_flags.problems(tokens("/ICode/LOWERLINK /FIsentinel.h"), root=str(tree))


def test_a_link_is_refused_wherever_it_is_unless_the_seat_trusts_it(tree):
    # P2: a directory under reference/open-bfme-1 authorized its link target.
    assert cl_flags.walk(str(tree), "Code/lowerlink") == "passes a symlink or junction"
    assert cl_flags.walk(str(tree), "reference/open-bfme-1/review_link") == "passes a symlink or junction"
    assert cl_flags.problems(tokens("/Ireference/open-bfme-1/review_link /FIsentinel.h"), root=str(tree))
    trusted = frozenset({"reference/open-bfme-1/review_link"})
    assert cl_flags.walk(str(tree), "reference/open-bfme-1/review_link", trusted) is None
    assert cl_flags.walk(str(tree), "reference/open-bfme-1/REVIEW_LINK", trusted) is not None
    assert cl_flags.walk(str(tree), "Code/lowerlink", trusted) == "passes a symlink or junction"


def test_a_submodule_that_is_itself_a_junction_needs_the_seat_s_trust(tmp_path):
    root = tmp_path / "worktree"
    (root / "reference").mkdir(parents=True)
    (tmp_path / "main/game").mkdir(parents=True)
    link(tmp_path / "main", root / "reference/open-bfme-1")
    cl_flags.forget()
    assert cl_flags.walk(str(root), "reference/open-bfme-1/game") == "passes a symlink or junction"
    assert cl_flags.walk(str(root), "reference/open-bfme-1/game", frozenset({"reference/open-bfme-1"})) is None


def test_the_trust_list_is_read_from_the_seat_s_own_git_dir(tmp_path):
    root, gitdir = tmp_path / "seat", tmp_path / "main/.git/worktrees/seat"
    root.mkdir()
    gitdir.mkdir(parents=True)
    (root / ".git").write_text(f"gitdir: {gitdir}\n", encoding="utf-8")
    assert build._trusted_include_links_of(str(root)) == frozenset()
    build._trusted_include_links_of.cache_clear()
    (gitdir / build.TRUSTED_INCLUDE_LINKS).write_text(
        "# this seat links the submodule in from the main checkout\nreference/open-bfme-1\n\n", encoding="utf-8")
    assert build._trusted_include_links_of(str(root)) == frozenset({"reference/open-bfme-1"})
    build._trusted_include_links_of.cache_clear()


# ------------------------------------------------- build.py at compile time
def test_build_refuses_to_compile_a_source_with_a_refused_flag(scratch):
    source = scratch / "evil.cpp"
    source.write_text("// cl: /O2 /B1 Z:\\evil.dll /MD\nint f() { return 1; }\n", encoding="utf-8")
    with pytest.raises(cl_flags.Refused) as refused:
        build.source_extra_flags(source)
    assert "/B1" in str(refused.value) and isinstance(refused.value, ValueError)  # a sweep skips it
    with pytest.raises(cl_flags.Refused):
        build.compiler_command(source, scratch / "evil.obj")


@pytest.mark.parametrize("line", RESPONSE_FILES[:4])
def test_build_refuses_a_response_file_argument(scratch, line):
    source = scratch / "rsp.cpp"
    source.write_text(f"// cl: /O2 {line}\nint f() {{ return 1; }}\n", encoding="utf-8")
    with pytest.raises(cl_flags.Refused):
        build.source_extra_flags(source)


def test_build_refuses_a_case_variant_of_a_link_in_the_checkout(scratch, tmp_path):
    (scratch / "inside").mkdir()
    link(tmp_path, scratch / "lowerlink")
    rel = scratch.relative_to(build.ROOT).as_posix()
    cl_flags.forget()
    source = scratch / "walk.cpp"
    for operand in (f"{rel}/inside", f"{rel}/lowerlink", f"{rel}/LOWERLINK", f"{rel}/INSIDE"):
        source.write_text(f"// cl: /O2 /I{operand} /FIsentinel.h\nint f() {{ return 1; }}\n", encoding="utf-8")
        if operand.endswith("/inside"):
            assert build.source_extra_flags(source)[1] == f"-I{operand}"
        else:
            with pytest.raises(cl_flags.Refused):
                build.source_extra_flags(source)


@pytest.mark.parametrize("injected", [["-B1x.dll"], ["-IZ:/outside"], ["-I", "/outside"], ["@x.rsp"]])
def test_build_refuses_a_flag_or_path_injected_after_the_line(scratch, monkeypatch, injected):
    # flag_defaults.apply adds region tokens from reverse/ data (opt=IZ:/outside): checked too.
    source = scratch / "region.cpp"
    source.write_text("// cl: /O2 /MD\nint f() { return 1; }\n", encoding="utf-8")
    monkeypatch.setattr(build.flag_defaults, "apply", lambda source, flags: injected + flags)
    with pytest.raises(cl_flags.Refused):
        build.source_extra_flags(source)
    source.write_text("int f() { return 1; }\n", encoding="utf-8")
    with pytest.raises(cl_flags.Refused):
        build.source_extra_flags(source)


@pytest.mark.parametrize("brk", BREAKS)
def test_build_refuses_a_directive_hidden_behind_another_line_break(scratch, brk):
    # P1 2: git sees one line "// harmless<break>// cl: /B1evil.dll"; str.splitlines sees a directive.
    source = scratch / "split.cpp"
    source.write_text(f"// harmless{brk}// cl: /B1evil.dll\nint f() {{ return 1; }}\n", encoding="utf-8",
                      newline="")
    with pytest.raises(cl_flags.Refused):
        build.source_extra_flags(source)
    if brk == "\r":
        return      # build reads with universal newlines: a lone \r is a newline there (the gate refuses it)
    source.write_text(f"// cl: /O2{brk}/MD\nint f() {{ return 1; }}\n", encoding="utf-8", newline="")
    with pytest.raises(cl_flags.Refused):
        build.source_extra_flags(source)


def test_a_crlf_source_is_one_reading(scratch):
    source = scratch / "crlf.cpp"
    source.write_bytes(b"// cl: /O1 /MD\r\nint f() { return 1; }\r\n")
    assert build.source_extra_flags(source) == ["-O1", "-MD"]


@pytest.mark.parametrize("name", ["CL", "_CL_", "cl", "Link", "_LINK_", "ML", "_ML_", "LIBPATH",
                                  "CCC_OVERRIDE_OPTIONS", "CPATH", "C_INCLUDE_PATH", "CPLUS_INCLUDE_PATH"])
def test_the_compile_environment_drops_every_variable_a_tool_reads_flags_from(monkeypatch, name):
    # P1 3: CL=/B1... and _CL_=/Fa... reached cl.exe through the caller's environment.
    monkeypatch.setenv(name, "/B1Z:\\evil.dll")
    env = build.compiler_environment(build.vc71_root())
    assert not [key for key in env if key.upper() == name.upper()]
    assert "INCLUDE" in env and "LIB" in env                   # what build sets stays


def test_build_passes_allowed_flags_through_unchanged(scratch):
    source = scratch / "good.cpp"
    source.write_text("// cl: /O1 /Ob2 /EHsc /MD /DNDEBUG /Ireference/shims/include\nint f() { return 1; }\n",
                      encoding="utf-8")
    assert build.source_extra_flags(source) == ["-O1", "-Ob2", "-EHsc", "-MD", "-DNDEBUG",
                                                "-Ireference/shims/include"]
