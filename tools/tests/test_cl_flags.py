"""tools/cl_flags.py and build.py's include confinement: what a source may make the compiler do and read."""
import json
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
# Round 3, finding 1: Windows aliases of an allowed directory are other strings.
ALIASES = ["/ICode/LOWERLINK", "/ICode/lowerlink.", "/ICODE~1/LOWERL~1", "/ICode/lowerlink::$INDEX_ALLOCATION",
           "/ICode/GameEngine/Include/", "/ICode//GameEngine/Include", "/I./Code/GameEngine/Include"]
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
    shutil.rmtree(path, ignore_errors=True)
    path.mkdir(parents=True, exist_ok=True)
    build._include_escape.cache_clear()
    yield path
    shutil.rmtree(path, ignore_errors=True)
    build._include_escape.cache_clear()


# ------------------------------------------------- flags
def test_every_flag_master_s_sources_carry_passes():
    # Every first `// cl:` line build.source_extra_flags reads under Code/, and the banked
    # attempts' and generators' flag lines (two reverse/ notes are prose, never compiled).
    out = subprocess.run(["git", "-C", str(build.ROOT), "grep", "-n", "-I", "^// cl:", "--", "Code", "tools",
                          "reverse/attempts"], capture_output=True, text=True, encoding="utf-8",
                         errors="replace").stdout
    seen, refused = set(), []
    values = build._include_values()
    for line in out.splitlines():
        path, _number, text = line.split(":", 2)
        if path in seen:
            continue
        seen.add(path)
        found = cl_flags.problems(tokens(text[len("// cl:"):]),
                                  None if path.startswith("tools/") else values)
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
    assert cl_flags.problems(tokens(ALLOWED)) == []


def test_prose_is_refused_as_not_a_flag():
    assert [reason for _, reason in cl_flags.problems(tokens("(none, base flags)"))] == ["is not a flag"] * 3


# ------------------------------------------------- A: include values are exact strings from the list
def test_master_s_include_values_are_all_listed():
    values = build._include_values()
    assert len(values) > 500 and "Code/GameEngine/Include" in values and "reference/shims" in values


@pytest.mark.parametrize("line", ALIASES)
def test_any_other_spelling_of_an_allowed_value_is_refused(line):
    values = frozenset({"Code/lowerlink", "Code/GameEngine/Include"})
    found = cl_flags.problems(tokens(line), values)
    assert found and found[0][1].startswith("include path")


def test_listed_values_pass_in_every_form_build_reads():
    values = frozenset({"Code/a", "reference/shims/b c", "x.h"})
    assert cl_flags.problems(tokens('/ICode/a -I Code/a /I"reference/shims/b c" /FIx.h /ICode\\a'), values) == []
    assert cl_flags.problems(tokens("/ICode/b /FIy.h"), values) == [
        ("/ICode/b", f"include path is not in {cl_flags.INCLUDE_ROOTS}"),
        ("/FIy.h", f"include path is not in {cl_flags.INCLUDE_ROOTS}")]


def test_a_missing_list_refuses_every_include_flag(scratch, monkeypatch):
    monkeypatch.setattr(build, "ROOT", scratch)            # a tree without reverse/cl_include_roots.txt
    assert build._include_values() == frozenset()
    assert cl_flags.problems(tokens("/ICode"), build._include_values())


def test_the_list_file_format():
    assert cl_flags.parse_include_roots("# comment\nCode\n\n  # also\nreference/shims/a b\r\n") == \
        frozenset({"Code", "reference/shims/a b"})


# ------------------------------------------------- B: what the compiler opened stays inside
def note(path):
    """A /showIncludes line as cl prints it under Wine (or natively on Windows)."""
    text = str(path)
    if os.name != "nt":
        text = "Z:" + text.replace("/", "\\")
    return f"Note: including file: {text}"


def test_include_confinement_accepts_the_checkout_and_the_toolchain(scratch):
    (scratch / "inside.h").write_text("", encoding="utf-8")
    header = build.vc71_root() / "Vc7" / "include" / "stdio.h"
    assert build.include_confinement("\n".join([note(scratch / "inside.h"), note(header), "other output"])) is None


def test_include_confinement_refuses_a_file_outside(scratch, tmp_path):
    (tmp_path / "sentinel.h").write_text("#error outside\n", encoding="utf-8")
    assert "outside" in build.include_confinement(note(tmp_path / "sentinel.h"))


def test_include_confinement_follows_a_link_and_a_case_variant_of_one(scratch, tmp_path):
    (tmp_path / "sentinel.h").write_text("", encoding="utf-8")
    link(tmp_path, scratch / "lowerlink")
    assert "outside" in build.include_confinement(note(scratch / "lowerlink" / "sentinel.h"))
    if os.name != "nt":                                       # Wine opens lowerlink for LOWERLINK
        assert "outside" in build.include_confinement(note(scratch / "LOWERLINK" / "sentinel.h"))


def test_include_confinement_refuses_import_output_and_an_unresolvable_file(scratch):
    (scratch / "x.tlh").write_text("", encoding="utf-8")
    assert "#import output" in build.include_confinement(note(scratch / "x.tlh"))
    assert "does not resolve" in build.include_confinement(note(scratch / "lowerlink." / "missing.h"))


def test_a_trusted_seat_link_is_inside(scratch, tmp_path, monkeypatch):
    (tmp_path / "sentinel.h").write_text("", encoding="utf-8")
    link(tmp_path, scratch / "seatlink")
    rel = scratch.relative_to(build.ROOT).as_posix() + "/seatlink"
    monkeypatch.setattr(build, "_trusted_include_links", lambda: frozenset({rel}))
    assert build.include_confinement(note(scratch / "seatlink" / "sentinel.h")) is None


def test_an_object_built_from_a_header_outside_is_never_current(scratch, tmp_path):
    source, obj = scratch / "unit.cpp", scratch / "unit.obj"
    source.write_text("int f() { return 1; }\n", encoding="utf-8")
    obj.write_bytes(b"obj")
    (tmp_path / "outside.h").write_text("", encoding="utf-8")
    command, env = build.compiler_command(source, obj)
    meta = {"cmd": build._cmd_fingerprint(command, env), "source": build._hash_file(str(source)),
            "deps": {str(tmp_path / "outside.h"): build._hash_file(str(tmp_path / "outside.h"))}}
    build._deps_sidecar(obj).write_text(json.dumps(meta), encoding="utf-8")
    assert build.compile_is_current(source, obj) is False
    meta["deps"] = {}
    build._deps_sidecar(obj).write_text(json.dumps(meta), encoding="utf-8")
    assert build.compile_is_current(source, obj) is True


def test_an_assembler_source_naming_an_include_is_refused(scratch):
    source = scratch / "unit.asm"
    source.write_text(".386\n.model flat\nINCLUDE Z:\\tmp\\x.inc\nEND\n", encoding="utf-8")
    ok, text, _code = build.try_compile_source(source, scratch / "unit.obj")
    assert not ok and "include confinement" in text


@pytest.fixture
def compiler(monkeypatch):
    try:
        build.vc71_root()
    except SystemExit:
        pytest.skip("MSVC 7.1 is not set up here")
    monkeypatch.setenv("BFME_OBJSTORE", "off")              # a scratch compile never enters the store


def compile_text(scratch, text):
    source = scratch / "unit.cpp"
    source.write_text(text, encoding="utf-8")
    return build.try_compile_source(source, scratch / "unit.obj")


def test_a_real_compile_reading_outside_through_a_link_fails(compiler, scratch, tmp_path):
    (tmp_path / "sentinel.h").write_text("int sentinel;\n", encoding="utf-8")
    link(tmp_path, scratch / "lowerlink")
    for name in ("lowerlink", "LOWERLINK"):              # Wine opens lowerlink for LOWERLINK too
        ok, text, _ = compile_text(scratch, f'#include "{name}/sentinel.h"\nint f() {{ return sentinel; }}\n')
        assert not ok and "include confinement" in text and not (scratch / "unit.obj").exists(), name


def test_a_real_compile_climbing_out_or_aliased_out_fails(compiler, scratch, tmp_path):
    (tmp_path / "sentinel.h").write_text("int sentinel;\n", encoding="utf-8")
    climb = os.path.relpath(tmp_path / "sentinel.h", scratch).replace("\\", "/")
    for text in (f'#include "{climb}"\nint f() {{ return sentinel; }}\n',
                 f'#pragma include_alias("quiet.h", "{climb}")\n#include "quiet.h"\nint f() {{ return sentinel; }}\n',
                 f'#define OUT "{climb}"\n#include OUT\nint f() {{ return sentinel; }}\n'):
        ok, out, _ = compile_text(scratch, text)
        assert not ok and "include confinement" in out, text


def test_a_real_compile_of_a_utf16_source_reading_outside_fails(compiler, scratch, tmp_path):
    (tmp_path / "sentinel.h").write_text("int sentinel;\n", encoding="utf-8")
    climb = os.path.relpath(tmp_path / "sentinel.h", scratch).replace("\\", "/")
    source = scratch / "unit.cpp"
    source.write_bytes(f'#include "{climb}"\r\nint f() {{ return sentinel; }}\r\n'.encode("utf-16"))
    ok, out, _ = build.try_compile_source(source, scratch / "unit.obj")
    assert not ok and "include confinement" in out


def test_a_real_compile_inside_the_checkout_passes(compiler, scratch):
    (scratch / "inside.h").write_text("int inside;\n", encoding="utf-8")
    ok, text, _ = compile_text(scratch, '#include "inside.h"\nint f() { return inside; }\n')
    assert ok, text


# ------------------------------------------------- build.py at compile time
def test_build_refuses_to_compile_a_source_with_a_refused_flag(scratch):
    source = scratch / "evil.cpp"
    source.write_text("// cl: /O2 /B1 Z:\\evil.dll /MD\nint f() { return 1; }\n", encoding="utf-8")
    with pytest.raises(cl_flags.Refused) as refused:
        build.source_extra_flags(source)
    assert "/B1" in str(refused.value) and isinstance(refused.value, ValueError)  # a sweep skips it
    with pytest.raises(cl_flags.Refused):
        build.compiler_command(source, scratch / "evil.obj")


@pytest.mark.parametrize("line", RESPONSE_FILES[:4] + ALIASES[:4])
def test_build_refuses_a_response_file_or_an_unlisted_include_value(scratch, line):
    source = scratch / "rsp.cpp"
    source.write_text(f"// cl: /O2 {line}\nint f() {{ return 1; }}\n", encoding="utf-8")
    with pytest.raises(cl_flags.Refused):
        build.source_extra_flags(source)


@pytest.mark.parametrize("injected", [["-B1x.dll"], ["-IZ:/outside"], ["-I", "/outside"], ["@x.rsp"],
                                      ["-ICode/NotListed"]])
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


def test_build_passes_allowed_flags_through_unchanged(scratch):
    source = scratch / "good.cpp"
    source.write_text("// cl: /O1 /Ob2 /EHsc /MD /DNDEBUG /ICode/GameEngine/Include\nint f() { return 1; }\n",
                      encoding="utf-8")
    assert build.source_extra_flags(source) == ["-O1", "-Ob2", "-EHsc", "-MD", "-DNDEBUG",
                                                "-ICode/GameEngine/Include"]


# ------------------------------------------------- reads a source directs itself (early warning)
READ_DIRECTIVES = [
    ('#import "Z:\\evil.tlb"', ["#import"]), ("  #  using <x.dll>", ["#using"]),
    ('#pragma include_alias("a.h", "/etc/passwd")', ["#pragma include_alias"]),
    ('__pragma(include_alias("a.h", "b.h"))', ["#pragma include_alias"]),
    ('??=import "x.tlb"', ["#import"]),                         # a trigraph for #
    ('#imp\\\nort "x.tlb"', ["#import"]),                       # a line splice inside the name
    ('#\\\npragma include_alias("a.h", "b.h")', ["#pragma include_alias"]),
    ('# /* comment */ import "x.tlb"', ["#import"]),            # a comment is whitespace
    ('int x;\r#import "x.tlb"', ["#import"]),                   # a lone carriage return
    ('#pragma\vinclude_alias("a.h", "b.h")', ["#pragma include_alias"]),   # round 3: a vertical tab
    ('x = "n/*";\n#pragma include_alias("a.h", "b.h")\n// */', ["#pragma include_alias"]),  # round 3
]
NOT_READ_DIRECTIVES = ["using namespace std;", "// #import x", "/* #import y */", 'const char *s = "#import";',
                       '#include "import.h"', "#pragma once", "int using_x;", "#pragma warning(disable: 4786)"]


@pytest.mark.parametrize("text, names", READ_DIRECTIVES)
def test_a_file_reading_directive_is_found_as_the_preprocessor_finds_it(text, names):
    assert cl_flags.read_directives(text) == names


@pytest.mark.parametrize("text", NOT_READ_DIRECTIVES)
def test_lookalikes_are_not_read_directives(text):
    assert cl_flags.read_directives(text) == []


def test_master_s_sources_hold_no_read_directive():
    import conversion_gate
    assert conversion_gate.tree_read_directives("HEAD") == []


# ------------------------------------------------- round 4: assembler sources (P1, P3)
ASM_REFUSED = [
    ("x CATSTR <incl>,<ude>", "catstr"), ("x TEXTEQU <include>", "textequ"), ("x EQU <include>", "equ<"),
    ("x EQU<include>", "equ<"), ("y SUBSTR <include x>, 1, 7", "substr"), ("y INSTR <a>, <b>", "instr"),
    ("y SIZESTR <abc>", "sizestr"), ("m MACRO a, b", "macro"), ("FOR arg, <a, b>", "for"),
    ("FORC c, <abc>", "forc"), ("IRP arg, <a>", "irp"), ("IRPC c, <abc>", "irpc"), ("REPEAT 2", "repeat"),
    ("REPT 2", "rept"), ("WHILE x", "while"), ("% x", "%"), ("  %x", "%"),
    ("    mov eax, @CatStr(<1>, <2>)", "@catstr"), ("x = @SizeStr(<abc>)", "@sizestr"),
    ("INCLUDE Z:\\outside\\sentinel.inc", "include"), ("  includelib evil.lib", "includelib"),
    ("label: INCLUDE x.inc", "include"), ("Include x.inc", "include"), ("COMMENT ! anything !", "comment"),
    ("EXITM <include>", "exitm"), ("PURGE m", "purge"),
]
ASM_ALLOWED = ["; for each entry, include the bias", "    mov eax, 1 ; repeat while x", "    db 'for', 0",
               "x = 5", "x EQU 5", "PUBLIC _f", "_f PROC", "    jmp eax", "_TEXT SEGMENT", "END", ".386"]


@pytest.mark.parametrize("line, name", ASM_REFUSED)
def test_every_masm_include_or_text_macro_facility_is_found(line, name):
    assert name in cl_flags.asm_directives(".386\n" + line + "\nEND\n")


@pytest.mark.parametrize("line", ASM_ALLOWED)
def test_plain_assembler_and_prose_in_comments_pass(line):
    assert cl_flags.asm_directives(line) == []


def test_no_master_assembler_source_uses_one():
    listing = subprocess.run(["git", "-C", str(build.ROOT), "ls-files", "*.asm", "*.ASM"],
                             capture_output=True, text=True).stdout.split()
    assert len(listing) > 60
    assert [p for p in listing if cl_flags.asm_directives((build.ROOT / p).read_text(errors="replace"))] == []


def test_an_assembler_refusal_leaves_no_object_or_receipt(scratch):
    # P3: a refused source must not leave an earlier object to be reused.
    source, obj = scratch / "unit.asm", scratch / "unit.obj"
    source.write_text(".386\n.model flat\nx CATSTR <incl>,<ude>\nx Z:\\outside\\sentinel.inc\nEND\n", encoding="utf-8")
    obj.write_bytes(b"old object")
    build._deps_sidecar(obj).write_text('{"cmd": "x", "source": "y", "deps": {}}', encoding="utf-8")
    ok, text, _ = build.try_compile_source(source, obj)
    assert not ok and "catstr" in text
    assert not obj.exists() and not build._deps_sidecar(obj).exists()


def test_an_assembler_object_is_never_current_while_its_source_uses_one(scratch):
    # P1: deps {} kept such an object current after the outside file was deleted.
    source, obj = scratch / "unit.asm", scratch / "unit.obj"
    source.write_text(".386\n.model flat\nEND\n", encoding="utf-8")
    obj.write_bytes(b"obj")
    command, env = build.compiler_command(source, obj)
    meta = {"cmd": build._cmd_fingerprint(command, env), "source": build._hash_file(str(source)), "deps": {}}
    build._deps_sidecar(obj).write_text(json.dumps(meta), encoding="utf-8")
    assert build.compile_is_current(source, obj) is True
    source.write_text(".386\n.model flat\nx CATSTR <incl>,<ude>\nEND\n", encoding="utf-8")
    meta["source"] = build._hash_file(str(source))
    build._deps_sidecar(obj).write_text(json.dumps(meta), encoding="utf-8")
    assert build.compile_is_current(source, obj) is False


def test_a_real_assemble_reading_outside_through_a_text_macro_is_refused(compiler, scratch, tmp_path):
    (tmp_path / "sentinel.inc").write_text("PUBLIC _sentinel\n", encoding="utf-8")
    outside = str(tmp_path / "sentinel.inc") if os.name == "nt" else "Z:" + str(tmp_path / "sentinel.inc").replace("/", "\\")
    source = scratch / "unit.asm"
    for text in (f".386\n.model flat\nx CATSTR <incl>,<ude>\nx {outside}\nEND\n",
                 f".386\n.model flat\nINCLUDE {outside}\nEND\n",
                 f".386\n.model flat\nm MACRO a, b\na&b {outside}\nENDM\nm incl, ude\nEND\n"):
        source.write_text(text, encoding="utf-8")
        ok, out, _ = build.try_compile_source(source, scratch / "unit.obj")
        assert not ok and "include confinement" in out and not (scratch / "unit.obj").exists(), text


def test_a_real_plain_assemble_passes(compiler, scratch):
    source = scratch / "unit.asm"
    source.write_text(".386\n.model flat\n_TEXT SEGMENT\nPUBLIC _f\n_f PROC\n    ret\n_f ENDP\n_TEXT ENDS\nEND\n",
                      encoding="utf-8")
    ok, text, _ = build.try_compile_source(source, scratch / "unit.obj")
    assert ok, text


# ------------------------------------------------- round 4: every final include operand (P2)
def test_canonical_include_spells_tool_operands_as_the_list_does():
    root, toolchain = "/r/checkout", "/r/checkout/reference/open-bfme-1/inputs/toolchains/vs2003"
    canon = lambda operand: cl_flags.canonical_include(operand, root, toolchain)  # noqa: E731
    if os.name != "nt":
        assert canon("Z:\\r\\checkout\\reference\\shims\\sweep") == "reference/shims/sweep"
        assert canon("Z:\\r\\checkout\\reference\\open-bfme-1\\inputs\\toolchains\\vs2003\\Vc7\\PlatformSDK\\Include") \
            == "{toolchain}/Vc7/PlatformSDK/Include"
        assert canon("Z:\\elsewhere\\Include") == "Z:/elsewhere/Include"          # stays itself: never listed
        assert canon("Z:\\r\\checkout\\Code\\LOWERL~1") == "Code/LOWERL~1"        # an alias stays itself
    assert canon("build/stlport46/0123456789abcdef01234567/base") == "{overlay}/base"
    assert canon("build/stlport46/not-a-digest/base") == "build/stlport46/not-a-digest/base"
    assert canon("Code/GameEngine/Include") == "Code/GameEngine/Include"


def test_every_final_include_operand_of_master_s_commands_is_listed():
    # compiler_command checks its own result: one stlport, one SDK and one plain unit, and a ZH tree source.
    rows = __import__("link_census").ledger()
    stl = next(build.ROOT / r["source"] for r in rows if build.stlport_overlay.selected(build.ROOT / r["source"]))
    dx = next(build.ROOT / r["source"] for r in rows if r["source"].lower().endswith(".cpp")
              and build.source_needs_dxsdk(build.ROOT / r["source"]))
    for source in (stl, dx, build.ROOT / rows[0]["source"]):
        build.compiler_command(source, build.ROOT / "build" / "never_written.obj")


def test_tool_added_include_operands_are_checked(scratch, monkeypatch):
    source = scratch / "unit.cpp"
    source.write_text("int f() { return 1; }\n", encoding="utf-8")
    real = build.stlport_overlay.include_dirs
    monkeypatch.setattr(build.stlport_overlay, "include_dirs", lambda s, flags: real(s, flags) + ["-Ibuild/elsewhere"])
    with pytest.raises(cl_flags.Refused):
        build.compiler_command(source, scratch / "unit.obj")
    monkeypatch.setattr(build.stlport_overlay, "include_dirs", real)
    build.compiler_command(source, scratch / "unit.obj")
    with pytest.raises(cl_flags.Refused):                       # the sweep retry's directories, re-checked
        build.check_command_includes(source, ["cl.exe", "-I" + build.wine_path(scratch), "unit.cpp"])
    build.check_command_includes(source, ["cl.exe", "-I" + build.wine_path(build._SWEEP_INCLUDE_DIRS[0]), "unit.cpp"])


def test_the_sage_tree_flags_need_the_list_too(monkeypatch):
    # P2: Generals/ZH reference sources returned their flags before any value check.
    zh = next(p for p in build.ZH_REFERENCE_ROOT.rglob("*.cpp"))
    assert build.source_extra_flags(zh)                         # listed today
    monkeypatch.setattr(build, "_include_values", lambda: frozenset())
    with pytest.raises(cl_flags.Refused):
        build.source_extra_flags(zh)


def test_a_data_rows_probe_is_confined_too(compiler, scratch, tmp_path):
    # data_rows' sizeof and type probes run their own commands: build.run_confined confines them.
    (tmp_path / "sentinel.h").write_text("int sentinel;\n", encoding="utf-8")
    climb = os.path.relpath(tmp_path / "sentinel.h", scratch).replace("\\", "/")
    source, obj = scratch / "probe.cpp", scratch / "probe.obj"
    source.write_text(f'#include "{climb}"\nint f() {{ return sentinel; }}\n', encoding="utf-8")
    command, env = build.compiler_command(source, obj)
    code, text = build.run_confined(command, env, obj)
    assert code == 1 and "include confinement" in text and not obj.exists()
    source.write_text("int f() { return 1; }\n", encoding="utf-8")
    code, text = build.run_confined(*build.compiler_command(source, obj), obj)
    assert code == 0 and obj.exists(), text
