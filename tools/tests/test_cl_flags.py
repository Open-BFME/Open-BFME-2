"""tools/cl_flags.py: the `// cl:` flags a source may carry, as the gate and build.py apply them."""
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
    "/clang:-fplugin=x.so", "/clang:-Xclang", "/clang:-load", "/clang:-mtune=native",
    "/d1reportAllClassLayout", "/d2Zi+", "/Zi", "/doc",
]
OUTSIDE = [
    "/I/etc", '/I"Z:\\home"', "/IC:/sdk", "/I../../x", "/I..\\x", "/ICode/../../x", "/I //server/share",
    "/I /etc", "-I ../x", "/FI/etc/passwd", "/FI../x.h",
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


def tokens(line):
    return build._source_flag_tokens(line)


def test_every_flag_master_s_sources_carry_passes():
    # Every first `// cl:` line build.source_extra_flags reads under Code/, and the banked
    # attempts' and generators' flag lines (two reverse/ notes are prose, never compiled).
    out = subprocess.run(["git", "-C", str(build.ROOT), "grep", "-n", "-I", "^// cl:", "--", "Code", "tools",
                          "reverse/attempts"], capture_output=True, text=True, errors="replace").stdout
    seen, refused = set(), []
    for line in out.splitlines():
        path, _number, text = line.split(":", 2)
        if path in seen:
            continue
        seen.add(path)
        found = cl_flags.problems(tokens(text[len("// cl:"):]))
        if found:
            refused.append((path, cl_flags.describe(found)))
    assert len(seen) > 15000
    assert refused == []


@pytest.mark.parametrize("line", DANGEROUS)
def test_a_flag_that_loads_code_or_writes_files_is_refused(line):
    found = cl_flags.problems(tokens("/O2 " + line + " /MD"))
    assert found and found[0][0] == line.split()[0]


@pytest.mark.parametrize("line", OUTSIDE)
def test_an_include_path_outside_the_checkout_is_refused(line):
    found = cl_flags.problems(tokens(line))
    assert found and found[0][1].startswith("include path")


def test_the_flag_families_in_use_pass():
    assert cl_flags.problems(tokens(ALLOWED)) == []


def test_prose_is_refused_as_not_a_flag():
    assert [reason for _, reason in cl_flags.problems(tokens("(none, base flags)"))] == ["is not a flag"] * 3


def test_rewritten_paths_are_not_judged_again():
    assert cl_flags.problems(["-I", "/abs/after/rewrite", "-IZ:/x", "-O2"], paths=False) == []
    assert cl_flags.problems(["-I", "/abs", "-B1x.dll"], paths=False) == [("-B1x.dll", "loads code or writes files")]


@pytest.fixture
def scratch():
    """A directory inside the checkout (compiler_command takes only its sources), removed after."""
    import shutil
    path = build.ROOT / "build" / "test_cl_flags"
    path.mkdir(parents=True, exist_ok=True)
    yield path
    shutil.rmtree(path, ignore_errors=True)


def test_build_refuses_to_compile_a_source_with_a_refused_flag(scratch):
    tmp_path = scratch
    source = tmp_path / "evil.cpp"
    source.write_text("// cl: /O2 /B1 Z:\\evil.dll /MD\nint f() { return 1; }\n")
    with pytest.raises(cl_flags.Refused) as refused:
        build.source_extra_flags(source)
    assert "/B1" in str(refused.value) and isinstance(refused.value, ValueError)  # a sweep skips it
    with pytest.raises(cl_flags.Refused):
        build.compiler_command(source, tmp_path / "evil.obj")


def test_build_refuses_a_flag_injected_after_the_line(tmp_path, monkeypatch):
    # flag_defaults.apply adds region tokens from reverse/ data: they are checked too.
    source = tmp_path / "region.cpp"
    source.write_text("// cl: /O2 /MD\nint f() { return 1; }\n")
    monkeypatch.setattr(build.flag_defaults, "apply", lambda source, flags: ["-B1x.dll"] + flags)
    with pytest.raises(cl_flags.Refused):
        build.source_extra_flags(source)
    source.write_text("int f() { return 1; }\n")
    with pytest.raises(cl_flags.Refused):
        build.source_extra_flags(source)


def test_build_passes_allowed_flags_through_unchanged(tmp_path):
    source = tmp_path / "good.cpp"
    source.write_text("// cl: /O1 /Ob2 /EHsc /MD /DNDEBUG /Ireference/shims/include\nint f() { return 1; }\n")
    assert build.source_extra_flags(source) == ["-O1", "-Ob2", "-EHsc", "-MD", "-DNDEBUG",
                                                "-Ireference/shims/include"]
