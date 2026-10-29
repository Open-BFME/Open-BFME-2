"""ms_header_audit: index entries, comparison, classification and check().

The index here is built from a small fake Microsoft header parsed by the
tool's own parser, so no toolchain is needed; the real index is validated by
`ms_header_audit.py index --validate`.
"""
import sys
from types import SimpleNamespace
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))

import ms_header_audit as mha  # noqa: E402

WINDEF = "Vc7/PlatformSDK/Include/WinDef.h"
STRAY = "Vc7/PlatformSDK/Include/MAPIWin.h"

FAKE_HEADER = """\
#define WINAPI __stdcall
#define MAX_PATH 260
typedef unsigned long DWORD;
typedef struct tagRECT { long left; long top; long right; long bottom; } RECT;
extern "C" __declspec(dllimport) DWORD __stdcall GetTickCount(void);
extern "C" double __cdecl sqrt(double);
inline float sin(float _X) {return (sinf(_X));}
#ifndef NOMINMAX
#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif
#endif
#ifdef UNICODE
typedef wchar_t TCHAR;
#else
typedef char TCHAR;
#endif
#ifdef RC_INVOKED
#define NOMINMAX
#endif
"""


def header_line(text):
    return FAKE_HEADER.splitlines().index(text) + 1


def fake_index():
    # what the kitchen sink sees: the default configuration's branches only
    decls, macros, _ = mha.parse_text(FAKE_HEADER, "cpp")
    entries = {}
    for d in decls:
        entries.setdefault(d.name, []).append({"k": d.kind, "f": WINDEF, "l": d.line, "lang": "cpp", "pp": True,
                                               "link": d.linkage, "tmpl": d.tmpl, "d": d.d})
    active, raw = {"cpp": {}, "c": {}}, {}
    for name, defs in macros.items():
        params, body, line = defs[0]
        # the probe prints a function-like body with placeholder parameters
        rename = {p: f"__MSA_P{j}__" for j, p in enumerate(params or ())}
        text = " ".join(rename.get(s, s) for _, s in body)
        raw[name] = (params, body)
        for unit in active:
            active[unit][name] = (params, text)
        entries.setdefault(name, []).append({"k": "macro", "f": WINDEF, "l": line, "lang": "raw", "pp": False,
                                             "link": None, "tmpl": False,
                                             "d": {"params": params, "body": text,
                                                   "active": {"cpp": text, "c": text}}})
    # a stray SDK header that also defines MAX_PATH, outside windows.h's reach
    entries["MAX_PATH"].insert(0, {"k": "macro", "f": STRAY, "l": 250, "lang": "raw", "pp": False, "link": None,
                                   "tmpl": False, "d": {"params": None, "body": "260",
                                                        "active": {"cpp": "260", "c": "260"}}})
    # windows.h defines NOMINMAX only for the resource compiler
    entries["NOMINMAX"] = [{"k": "macro", "f": WINDEF, "l": header_line("#define NOMINMAX"), "lang": "raw",
                            "pp": False, "link": None, "tmpl": False,
                            "d": {"params": None, "body": "", "active": {"cpp": None, "c": None}}}]
    regions = mha.directive_regions(FAKE_HEADER)
    return {"version": mha.TOOL_VERSION, "roots": [], "entries": entries, "core": [WINDEF],
            "core_order": {WINDEF: 0}, "public": {WINDEF: "windows.h", STRAY: "MAPIWin.h"},
            "units": {}, "active_macros": active, "raw_macros": raw,
            "config_regions": {WINDEF: regions, STRAY: regions},
            "header_text": {WINDEF: FAKE_HEADER, STRAY: FAKE_HEADER}}


INDEX = fake_index()


def scan(text, path="Code/Game/Fixture.cpp"):
    res = mha.scan_text(path, text, INDEX)
    return res, {o[1]: o for o in res["occ"]}


def test_index_records_kinds_and_sites():
    kinds = {name: {e["k"] for e in es} for name, es in INDEX["entries"].items()}
    assert kinds["DWORD"] == {"typedef"}
    assert {"typedef"} <= kinds["RECT"] and {"struct"} <= kinds["tagRECT"]
    assert kinds["GetTickCount"] == {"function"}
    assert kinds["WINAPI"] == {"macro"}


def test_best_site_prefers_headers_windows_h_reaches():
    site = mha.best_site(INDEX, INDEX["entries"]["MAX_PATH"])
    assert site["f"] == WINDEF


def test_identical_copies_are_drop_in():
    res, occ = scan("typedef unsigned long DWORD;\n"
                    "typedef struct tagRECT { long left; long top; long right; long bottom; } RECT;\n"
                    "#define MAX_PATH 260\n")
    assert occ["DWORD"][3] == "same"
    assert occ["tagRECT"][3] == "same"
    assert occ["MAX_PATH"][3] == "same"
    assert mha.classify("Code/Game/Fixture.cpp", res, INDEX)[0] == mha.DROP_IN
    assert mha.suggested_headers(res, INDEX) == ["windows.h"]


def test_member_names_only_need_adapting():
    res, occ = scan("typedef struct tagRECT { long x; long top; long right; long bottom; } RECT;\n")
    assert occ["tagRECT"][3] == "source"
    assert mha.classify("Code/Game/Fixture.cpp", res, INDEX)[0] == "adapt"


def test_layout_difference_conflicts():
    res, occ = scan("struct tagRECT { short left; short top; short right; short bottom; };\n")
    assert occ["tagRECT"][3] == "abi"
    assert "size" in occ["tagRECT"][4]
    assert mha.classify("Code/Game/Fixture.cpp", res, INDEX)[0] == "conflicting"


def test_calling_convention_and_dllimport_conflict():
    res, occ = scan('extern "C" unsigned long __cdecl GetTickCount(void);\n')
    assert occ["GetTickCount"][3] == "abi"
    assert "calling convention" in occ["GetTickCount"][4]
    assert "dllimport" in occ["GetTickCount"][4]


def test_matching_prototype_through_local_macros_is_same():
    _, occ = scan('#define WINAPI __stdcall\n'
                  'extern "C" __declspec(dllimport) DWORD WINAPI GetTickCount(void);\n')
    assert occ["GetTickCount"][3] == "same"


def test_macro_value_difference_conflicts():
    _, occ = scan("#define MAX_PATH 256\n")
    assert occ["MAX_PATH"][3] == "abi"


def test_unrelated_type_with_a_microsoft_name_is_not_reported():
    res, occ = scan("struct tagRECT { int width; int height; float scale; };\n")
    assert "tagRECT" not in occ or occ["tagRECT"][3] == "collision"
    assert mha.classify("Code/Game/Fixture.cpp", res, INDEX)[0] is None


def test_a_shim_named_after_a_microsoft_header_is_a_shim():
    res, _ = scan("typedef unsigned long DWORD;\n", path="reference/shims/win32/windef.h")
    assert mha.classify("reference/shims/win32/windef.h", res, INDEX)[0] == "shim"


def test_check_refuses_only_new_definitions():
    old = "int f();\ntypedef unsigned long DWORD;\n"
    texts = {"new": {"Code/Game/Fixture.cpp": old + "#define MAX_PATH 260\n"},
             "moved": {"Code/Game/Fixture.cpp": "typedef unsigned long DWORD;\nint f();\n"}}
    for label, expect in (("new", 1), ("moved", 0)):
        problems = mha.check(["Code/Game/Fixture.cpp"], read_new=texts[label].get,
                             read_old=lambda p: old, index=INDEX)
        assert len(problems) == expect, (label, problems)
    problems = mha.check(["Code/Game/Fixture.cpp"], read_new=texts["new"].get, read_old=lambda p: old, index=INDEX)
    assert "MAX_PATH" in problems[0] and "<windows.h>" in problems[0]


def test_check_ignores_paths_outside_the_scan():
    assert mha.check(["tools/x.cpp", "Code/gen_asm/x.cpp"], read_new=lambda p: "typedef unsigned long DWORD;\n",
                     read_old=lambda p: None, index=INDEX) == []


def test_extra_root_arguments():
    roots = mha.parse_root_args(["DXSDK=C:/dx/Include", "C:/other/inc"])
    assert roots[0][0] == "DXSDK" and roots[0][1] == Path("C:/dx/Include")
    assert roots[1][0] == "inc"


def test_preprocessor_uses_wine_paths_and_compiler_environment(tmp_path, monkeypatch):
    import build
    monkeypatch.setattr(mha, "vc71_root", lambda: tmp_path)
    monkeypatch.setattr(mha.os, "name", "posix")
    monkeypatch.setattr(build, "compiler_environment", lambda root: {"WINEPATH": "compiler-dlls"})
    # The test simulates Wine even on a Windows host; do not produce Z:C:\...
    # from that host's tmp_path when constructing the fake Wine mapping.
    def fake_wine_path(path):
        return "Z:\\" + str(path).lstrip("/\\").replace(":", "").replace("/", "\\")

    monkeypatch.setattr(build, "wine_path", fake_wine_path)
    calls = []
    monkeypatch.setattr(mha.subprocess, "run", lambda command, **kw:
                        calls.append((command, kw)) or SimpleNamespace(returncode=0, stdout="ok", stderr=""))
    assert mha.run_cl_e(["#include <windows.h>"], [("sdk", tmp_path / "include")], workdir=tmp_path)[0]
    command, kwargs = calls[0]
    assert command[0] == "wine" and command[-1].startswith("Z:\\")
    assert kwargs["env"] == {"WINEPATH": "compiler-dlls", "INCLUDE": fake_wine_path(tmp_path / "include")}


def test_preprocessor_line_paths_recover_header_provenance_under_wine(tmp_path, monkeypatch):
    import build
    monkeypatch.setattr(mha.os, "name", "posix")
    monkeypatch.setattr(build, "wine_path", lambda path: "T:\\SDK")
    roots = [("sdk", tmp_path)]
    assert mha._label_for("T:\\SDK\\WinDef.h", roots) == "sdk/WinDef.h"
    assert mha._label_for(str(tmp_path / "WinDef.h"), roots) == "sdk/WinDef.h"
    assert mha._label_for("T:\\Other\\WinDef.h", roots) is None


def test_queue_round_trip_and_repair_queue_lane(tmp_path, monkeypatch, capsys):
    res, _ = scan("typedef unsigned long DWORD;\n#define MAX_PATH 256\n")
    queue, occurrences = tmp_path / "reverse/ms_header_queue.tsv", tmp_path / "occ.tsv"
    queue.parent.mkdir()
    rows = mha.write_queue({"Code/Game/A.cpp": res, "Code/Game/Clean.cpp": scan("int x;\n")[0]}, INDEX,
                           queue=queue, occurrences=occurrences)
    assert [r[:2] for r in rows] == [["Code/Game/A.cpp", "conflicting"]]
    monkeypatch.setattr(mha, "QUEUE", queue)
    got = mha.read_queue()
    assert got[0]["file"] == "Code/Game/A.cpp" and got[0]["headers"] == "<windows.h>"
    import repair_queue
    import next_work
    source = tmp_path / "Code/Game/A.cpp"
    source.parent.mkdir(parents=True)
    source.write_text("// queued source\n")
    monkeypatch.setattr(repair_queue, "ROOT", tmp_path)
    monkeypatch.setattr(next_work, "busy_keys", lambda: set())
    assert repair_queue.main(["ms-headers", "--class", "conflicting"]) == 0
    assert "Code/Game/A.cpp" in capsys.readouterr().out


def test_refresh_combines_donors_and_preserves_unrelated_debt(tmp_path):
    queue, occurrences = tmp_path / "queue.tsv", tmp_path / "occ.tsv"
    debt = scan("typedef unsigned long DWORD;\n")[0]
    mha.write_queue({"Code/A.cpp": debt, "Code/B.cpp": debt, "Code/Other.cpp": debt},
                    INDEX, queue=queue, occurrences=occurrences)
    untouched = next(line for line in queue.read_bytes().splitlines(keepends=True)
                     if line.startswith(b"Code/Other.cpp\t"))
    assert mha.refresh_queue({"Code/T.cpp": debt}, INDEX, ["Code/A.cpp", "Code/B.cpp"],
                             queue=queue, occurrences=occurrences)
    rows = mha.read_queue(queue)
    assert [r["file"] for r in rows] == ["Code/Other.cpp", "Code/T.cpp"]
    assert rows[1]["defs"] == "1"
    assert untouched in queue.read_bytes().splitlines(keepends=True)
    assert "Code/A.cpp" not in occurrences.read_text()
    assert "Code/B.cpp" not in occurrences.read_text()
    assert "Code/Other.cpp" in occurrences.read_text()
    assert "Code/T.cpp" in occurrences.read_text()
    assert not mha.refresh_queue({"Code/T.cpp": debt}, INDEX,
                                 queue=queue, occurrences=occurrences)


def test_refresh_removes_clean_scope_but_keeps_failed_analysis_queued(tmp_path):
    queue, occurrences = tmp_path / "queue.tsv", tmp_path / "occ.tsv"
    debt = scan("typedef unsigned long DWORD;\n")[0]
    mha.write_queue({"Code/A.cpp": debt, "Code/Other.cpp": debt}, INDEX,
                    queue=queue, occurrences=occurrences)
    mha.refresh_queue({"Code/T.cpp": scan("int x;\n")[0]}, INDEX, ["Code/A.cpp"],
                      queue=queue, occurrences=occurrences)
    assert [r["file"] for r in mha.read_queue(queue)] == ["Code/Other.cpp"]
    failed = dict(scan("int x;\n")[0], error="analysis timeout")
    mha.refresh_queue({"Code/T.cpp": failed}, INDEX, queue=queue, occurrences=occurrences)
    row = next(r for r in mha.read_queue(queue) if r["file"] == "Code/T.cpp")
    assert row["class"] == "failed" and "analysis timeout" in row["note"]


def test_self_referencing_typedef_terminates():
    # an autoconf script once parsed as `typedef > > ... EOF EOF ... int bool`
    text = " >> confdefs.h <<\\EOF\nEOF\n  cat > conftest.$ac_ext <<EOF\ntypedef int bool;\n"
    ctx = mha.TypeCtx(INDEX, "cpp", mha.parse_text(text, "cpp")[0])
    assert "EOF" in ctx.canon(["EOF"])


def test_scanned_paths():
    assert mha.scanned_path("vendor/stlport/vector")
    assert not mha.scanned_path("vendor/stlport/config/new_compiler/configure")
    assert not mha.scanned_path("vendor/stlport/README")
    assert not mha.scanned_path("Code/gen_asm/foo.cpp")
    assert mha.scanned_path("reference/shims/gamespy/windows.h")


def test_collisions_do_not_break_the_queue(tmp_path):
    res, _ = scan("typedef unsigned long DWORD;\nstruct tagRECT { int width; int height; float scale; };\n")
    rows = mha.write_queue({"Code/Game/B.cpp": res}, INDEX, queue=tmp_path / "q.tsv", occurrences=tmp_path / "o.tsv")
    # the game's own tagRECT stays, and including windows.h beside it is a
    # redefinition: the file is no drop-in
    assert rows[0][1] == "conflicting" and "tagRECT" not in rows[0][-1]


def test_unrelated_cpp_overloads_are_not_reported():
    _, occ = scan("float sqrt(float x);\n")
    assert "sqrt" not in occ
    _, occ = scan("double sqrt(double x);\n")
    assert occ["sqrt"][3] == "mangle"
    # same ABI (a reference is a pointer) but a different C++ type: an overload
    _, occ = scan('extern "C++" double sqrt(const AsciiString &s);\n')
    assert "sqrt" not in occ


def test_forward_declarations_alone_do_not_queue_a_file():
    res, occ = scan("struct tagRECT;\n")
    assert occ["tagRECT"][3] == "fwd"
    assert mha.classify("Code/Game/Fixture.cpp", res, INDEX)[0] is None


def test_imported_game_operators_are_not_simd_header_copies():
    # bfme_colmathaabox/vector3.h uses dllimport to suppress an out-of-line
    # copy. It still overloads on Vector3, not the SDK's SIMD vector types.
    for operator in ("*", "+"):
        index = index_from(
            "struct SimdVector { float data[4]; };\n"
            f"inline SimdVector operator{operator}(float k, const SimdVector &v) {{return v;}}\n",
            label="Vc7/include/dvec.h")
        prefix = "class Vector3 { public: float X, Y, Z; };\n"
        for ending in (";", " {return v;}"):
            text = prefix + ("__declspec(dllimport) __forceinline Vector3 "
                             f"operator{operator}(float k, const Vector3 &v){ending}\n")
            res = mha.scan_text("reference/shims/fixture/vector3.h", text, index)
            assert not any(o[1] == f"operator{operator}" for o in res["occ"])
            assert not mha.check(["reference/shims/fixture/vector3.h"],
                                 read_new=lambda p: text, read_old=lambda p: "",
                                 index=index)


def test_imported_matching_operator_still_reports_abi_conflict():
    index = index_from("inline SimdVector operator*(float k, const SimdVector &v) {return v;}\n",
                       label="Vc7/include/dvec.h")
    text = "__declspec(dllimport) SimdVector operator*(float k, const SimdVector &v);\n"
    occ = mha.scan_text("Code/Fixture.cpp", text, index)["occ"]
    assert any(o[1] == "operator*" and o[3] == "abi" and "dllimport" in o[4] for o in occ)
    assert mha.check(["Code/Fixture.cpp"], read_new=lambda p: text,
                     read_old=lambda p: "", index=index)


def test_imported_named_function_and_allocator_conflicts_remain():
    for name in ("free", "operator new"):
        index = index_from(f"void *{name}(unsigned int size);\n", label="Vc7/include/new")
        text = f"__declspec(dllimport) void *{name}(const char *size);\n"
        occ = mha.scan_text("Code/Fixture.cpp", text, index)["occ"]
        assert any(o[1] == name and o[3] == "abi" for o in occ)


def crt_free_index():
    entry = {"k": "function", "f": "Vc7/include/stdlib.h", "l": 279, "lang": "cpp", "pp": True, "link": "C",
             "tmpl": False, "d": {"params": [["void", "*"]], "ret": ["void"], "cc": "__cdecl", "dllimport": True,
                                  "variadic": False}}
    return dict(INDEX, entries=dict(INDEX["entries"], free=[entry]),
                core_order=dict(INDEX["core_order"], **{"Vc7/include/stdlib.h": 1}),
                config_regions=dict(INDEX["config_regions"], **{"Vc7/include/stdlib.h": mha.directive_regions("")}),
                header_text=dict(INDEX["header_text"], **{"Vc7/include/stdlib.h":
                                                         "\n" * 278 + "_CRTIMP void __cdecl free(void *);\n"}))


def test_emptied_crtimp_drops_the_crt_dllimport():
    index = crt_free_index()
    text = 'extern "C" void __cdecl free(void *);\n'
    md = "// cl: -MD\n" + text
    occ = mha.scan_text("Code/A.cpp", md, index)["occ"][0]
    assert occ[3] == "abi"
    # sampled free callers reach the game allocator wrapper, not CRT free
    assert mha.VERIFY_CALLEE in occ[4] and "0x430830" in occ[4]
    assert mha.scan_text("Code/A.cpp", "// cl: -MD -D_CRTIMP=\n" + text, index)["occ"][0][3] == "same"
    assert mha.scan_text("Code/A.cpp", "#define _CRTIMP\n" + md, index)["occ"][0][3] == "same"


def test_function_exception_specs_survive_parsing():
    for suffix, expected in (("", None), (" throw()", []),
                             (" throw(...)", ["..."]), (" throw(int)", ["int"])):
        for ending in (";", " { return; }"):
            decls, _, _ = mha.parse_text('extern "C" void release(void *)' + suffix + ending, "cpp")
            fn = next(d for d in decls if d.name == "release")
            assert fn.d.get("throws") == expected
            assert fn.d["ret"] == ["void"]
            assert fn.d["params"] == [["void", "*"]]


def test_exception_contract_changes_are_not_drop_in(tmp_path):
    # /EHsc assumes an unspecified extern-C function cannot throw; replacing
    # free(void*) throw(...) with stdlib.h removed three native EH frames.
    for local, real in ((" throw(...)", ""), ("", " throw(...)"),
                        (" throw()", ""), ("", " throw()"),
                        (" throw()", " throw(...)"), (" throw(int)", " throw(...)")):
        index = index_from('extern "C" void release(void *)' + real + ";\n")
        res = mha.scan_text("Code/Fixture.cpp", 'extern "C" void release(void *)' + local + ";\n", index)
        occ = next(o for o in res["occ"] if o[1] == "release")
        assert occ[3] == "abi"
        assert "exception specification" in occ[4]
        assert mha.classify("Code/Fixture.cpp", res, index)[0] == "conflicting"
        mha.write_queue({"Code/Fixture.cpp": res}, index,
                        queue=tmp_path / "queue.tsv", occurrences=tmp_path / "occurrences.tsv")
        assert mha.read_queue(tmp_path / "queue.tsv")[0]["class"] == "conflicting"
    for spec in ("", " throw()", " throw(...)", " throw(int)"):
        text = 'extern "C" void release(void *)' + spec + ";\n"
        index = index_from(text)
        res = mha.scan_text("Code/Fixture.cpp", text, index)
        assert mha.classify("Code/Fixture.cpp", res, index)[0] == mha.DROP_IN


def test_identical_inline_body_does_not_override_exception_contract():
    index = index_from("inline int helper() throw() { return 1; }\n")
    res = mha.scan_text("Code/Fixture.cpp", "inline int helper() throw(...) { return 1; }\n", index)
    occ = next(o for o in res["occ"] if o[1] == "helper")
    assert occ[3] == "abi" and "exception specification" in occ[4]


def test_a_game_function_sharing_a_c_name_is_an_overload():
    _, occ = scan("void GetTickCount(const char *name);\n")
    assert "GetTickCount" not in occ
    _, occ = scan('extern "C" void GetTickCount(const char *name);\n')
    assert occ["GetTickCount"][3] == "abi"


# -- review findings ----------------------------------------------------------

def test_an_inline_body_is_compared_not_just_its_signature():
    # `inline float sin(float x){return 0.0f;}` once came out drop-in
    res, occ = scan("inline float sin(float x) {return 0.0f;}\n")
    assert occ["sin"][3] == "unverified"
    assert mha.classify("Code/Game/Fixture.cpp", res, INDEX)[0] == "unverified"
    # the same tokens, a parameter renamed: proven identical
    res, occ = scan("inline float sin(float y) {return (sinf(y));}\n")
    assert occ["sin"][3] == "same" and occ["sin"][4] == "identical inline body"
    assert mha.classify("Code/Game/Fixture.cpp", res, INDEX)[0] == mha.DROP_IN


def test_a_macro_body_that_differs_is_unverified():
    res, occ = scan("#define min(a,b) ((a) < (b) ? (a) : (b))\n")
    assert occ["min"][3] == "unverified"
    assert mha.classify("Code/Game/Fixture.cpp", res, INDEX)[0] == "unverified"
    _, occ = scan("#define min(x,y) (((x) < (y)) ? (x) : (y))\n")
    assert occ["min"][3] == "same"


def test_configuration_macros_are_never_removable():
    # windows.h defines NOMINMAX only under RC_INVOKED; always.h's is an input
    res, occ = scan("#define NOMINMAX\n")
    assert occ["NOMINMAX"][3] == "config"
    assert mha.classify("Code/Game/Fixture.cpp", res, INDEX)[0] is None
    for name in ("UNICODE", "WIN32_LEAN_AND_MEAN", "_WIN32_WINNT", "STRICT"):
        assert name in mha.CONFIG_MACROS


def test_identical_text_from_an_inactive_branch_is_not_drop_in():
    _, occ = scan("typedef char TCHAR;\n")
    assert occ["TCHAR"][3] == "same"
    # under /DUNICODE the real TCHAR is wchar_t
    res, occ = scan("// cl: /DUNICODE\ntypedef char TCHAR;\n")
    assert occ["TCHAR"][3] == "unknown" and "inactive" in occ["TCHAR"][4]
    assert mha.classify("Code/Game/Fixture.cpp", res, INDEX)[0] == "adapt"
    # NOMINMAX switches windows.h's min off: the local copy must stay
    res, occ = scan("#define NOMINMAX\n#define min(a,b) (((a) < (b)) ? (a) : (b))\n")
    assert occ["min"][3] == "unknown" and "inactive" in occ["min"][4]
    assert mha.classify("Code/Game/Fixture.cpp", res, INDEX)[0] == "adapt"


def test_a_real_macro_inactive_in_the_unit_configuration_is_not_trusted():
    # NOMINMAX's only real site sits under RC_INVOKED: identical text proves nothing
    config = mha.UnitConfig(INDEX, "cpp", mha.file_defines("", "cpp", "Code/A.cpp")[0], {})
    assert config.trusted(INDEX["entries"]["NOMINMAX"][0]) is False
    assert config.trusted(INDEX["entries"]["DWORD"][0]) is True


def test_unreadable_real_headers_are_not_verifiable():
    entry = dict(INDEX["entries"]["DWORD"][0], f="Vc7/PlatformSDK/Include/Unknown.h")
    index = dict(INDEX, entries=dict(INDEX["entries"], DWORD=[entry]))
    res = mha.scan_text("Code/A.cpp", "typedef unsigned long DWORD;\n", index)
    assert res["occ"][0][3] == "unknown" and "not verifiable" in res["occ"][0][4]


def test_cond_value_and_guards():
    defines = {"_WIN32_WINNT": "(0x0501)", "FOO": ""}
    assert mha.cond_value("_WIN32_WINNT >= 0x0500", defines) is True
    assert mha.cond_value("defined(FOO) && !defined(BAR)", defines) is True
    assert mha.cond_value("FOO", defines) is None
    lines, chains = mha.directive_regions("#ifndef _X_\n#define _X_\n#ifndef SIZE\n#define SIZE 1\n#endif\n"
                                          "int a;\n#endif\n")
    chain = chains[mha.bisect.bisect_left(lines, 6) - 1]
    assert mha.chain_value(chain, {"_X_": "", "SIZE": "1"}) is True  # guards hold


def write_tree(root, files):
    for rel, text in files.items():
        path = root / rel
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text)


def test_included_project_headers_are_inspected(tmp_path, monkeypatch):
    # Rva00041004Lock.cpp was drop-in while its Rva00041004Lock.h defined a
    # CRITICAL_SECTION that conflicts with <windows.h>
    monkeypatch.setattr(mha, "ROOT", tmp_path)
    monkeypatch.setattr(mha, "_HEADER_SCANS", {})
    write_tree(tmp_path, {
        "Code/Inc/Lock.h": "struct tagRECT { short left; short top; short right; short bottom; };\n",
        "Code/Inc/Same.h": "typedef struct tagRECT { long left; long top; long right; long bottom; } RECT;\n",
        "Code/Inc/Plain.h": "typedef unsigned long DWORD;\n#define NOMINMAX\n",
        "Code/Inc/Own.h": "#pragma once\nstruct tagRECT { unsigned char data[24]; };\n",
    })
    tu = "typedef unsigned long DWORD;\n"
    res = mha.scan_text("Code/Src/A.cpp", '#include "../Inc/Lock.h"\n' + tu, INDEX)
    assert mha.classify("Code/Src/A.cpp", res, INDEX)[0] == "conflicting"
    assert res["closure"][0][0] == "Code/Inc/Lock.h" and res["closure"][0][2] == "tagRECT"
    # the Rva00041004Lock.h shape: an unrelated game type under a Microsoft name
    res = mha.scan_text("Code/Src/A.cpp", '#include "../Inc/Own.h"\n' + tu, INDEX)
    assert mha.classify("Code/Src/A.cpp", res, INDEX)[0] == "conflicting"
    assert "redefinition" in res["closure"][0][5]
    # an identical struct in an included header is a redefinition once the
    # real header comes in
    res = mha.scan_text("Code/Src/A.cpp", '#include "../Inc/Same.h"\n' + tu, INDEX)
    assert mha.classify("Code/Src/A.cpp", res, INDEX)[0] == "adapt"
    # -I directories from `// cl:` resolve angled includes; an identical
    # typedef is harmless, but the header's NOMINMAX joins the configuration
    res = mha.scan_text("Code/Src/A.cpp", "// cl: /ICode/Inc\n#include <Plain.h>\n"
                        "#define min(a,b) (((a) < (b)) ? (a) : (b))\n" + tu, INDEX)
    occ = {o[1]: o for o in res["occ"]}
    assert res["closure"] == [] and occ["DWORD"][3] == "same" and occ["min"][3] == "unknown"
    # unresolved includes leave the closure unchecked
    res = mha.scan_text("Code/Src/A.cpp", '#include "Missing.h"\n' + tu, INDEX)
    assert mha.classify("Code/Src/A.cpp", res, INDEX)[0] == "adapt"
    assert "unresolved include" in res["closure"][0][5]
    # a Microsoft header resolves to the toolchain, not to a blocker
    res = mha.scan_text("Code/Src/A.cpp", "#include <windows.h>\n" + tu, INDEX)
    assert res["closure"] == [] and mha.classify("Code/Src/A.cpp", res, INDEX)[0] == mha.DROP_IN


def test_check_maps_rename_sources():
    # a renamed file's grandfathered definitions are not new
    old = "typedef unsigned long DWORD;\n"
    texts = {"Code/Game/Old.cpp": old}
    kwargs = dict(read_new=lambda p: old, read_old=texts.get, index=INDEX)
    assert len(mha.check(["Code/Game/New.cpp"], **kwargs)) == 1
    assert mha.check(["Code/Game/New.cpp"], renames={"Code/Game/New.cpp": "Code/Game/Old.cpp"}, **kwargs) == []
    paths, renames = mha.parse_name_status("R096\0Code/Game/Old.cpp\0Code/Game/New.cpp\0M\0Code/B.cpp\0"
                                           "C100\0Code/C.cpp\0Code/D.cpp\0")
    assert paths == ["Code/Game/New.cpp", "Code/B.cpp", "Code/D.cpp"]
    assert renames == {"Code/Game/New.cpp": "Code/Game/Old.cpp"}


def test_check_ignores_forward_declarations_and_config_macros():
    old = "int f();\n"
    new = old + "struct tagRECT;\n#define NOMINMAX\n"
    assert mha.check(["Code/Game/Fixture.cpp"], read_new=lambda p: new, read_old=lambda p: old, index=INDEX) == []


def test_incomplete_analysis_is_failed_and_refused(monkeypatch, tmp_path):
    # a timeout or recursion is an explicit failure, never an empty list
    big = "typedef unsigned long DWORD;\n" + "int x;\n" * 5000
    res = mha.scan_text("Code/Game/Fixture.cpp", big, INDEX, timeout=0)
    assert res["error"] == "timeout" and mha.classify("Code/Game/Fixture.cpp", res, INDEX)[0] == "failed"
    problems = mha.check(["Code/Game/Fixture.cpp"], read_new=lambda p: big, read_old=lambda p: None,
                         index=INDEX, timeout=0)
    assert len(problems) == 1 and "analysis incomplete (timeout)" in problems[0]

    def deep(*args, **kwargs):
        raise RecursionError
    monkeypatch.setattr(mha, "parse_text", deep)
    problems = mha.check(["Code/Game/Fixture.cpp"], read_new=lambda p: "int x;\n", read_old=lambda p: None,
                         index=INDEX)
    assert len(problems) == 1 and "recursion" in problems[0]
    rows = mha.write_queue({"Code/Game/F.cpp": mha.scan_text("Code/Game/F.cpp", "int x;\n", INDEX)}, INDEX,
                           queue=tmp_path / "q.tsv", occurrences=tmp_path / "o.tsv")
    row = dict(zip(mha.QUEUE_HEADER, rows[0]))
    assert row["class"] == "failed" and "analysis incomplete" in row["note"]


def test_crt_dllimport_conflicts_carry_the_verify_callee_note(tmp_path):
    index = crt_free_index()
    res = mha.scan_text("Code/A.cpp", '// cl: -MD\nextern "C" void __cdecl free(void *);\n', index)
    rows = mha.write_queue({"Code/A.cpp": res}, index, queue=tmp_path / "q.tsv", occurrences=tmp_path / "o.tsv")
    row = dict(zip(mha.QUEUE_HEADER, rows[0]))
    assert row["class"] == "conflicting" and row["note"] == mha.VERIFY_CALLEE
    assert mha.read_queue(tmp_path / "q.tsv")[0]["note"] == mha.VERIFY_CALLEE


def index_from(header, label=WINDEF, base=None):
    """An index whose kitchen sink is `header` (default branches) parsed as
    the real one is: entries, probed macros, regions and the header text."""
    base = base or INDEX
    decls, macros, _ = mha.parse_text(header, "cpp")
    entries = dict(base["entries"])
    active = {u: dict(base["active_macros"][u]) for u in ("cpp", "c")}
    raw = dict(base["raw_macros"])
    for d in decls:
        entries[d.name] = [{"k": d.kind, "f": label, "l": d.line, "lang": "cpp", "pp": True,
                            "link": d.linkage, "tmpl": d.tmpl, "d": d.d}]
    for name, defs in macros.items():
        params, body, line = defs[0]
        rename = {p: f"__MSA_P{j}__" for j, p in enumerate(params or ())}
        text = " ".join(rename.get(s, s) for _, s in body)
        raw[name] = (params, body)
        for unit in active:
            active[unit][name] = (params, text)
        entries[name] = [{"k": "macro", "f": label, "l": line, "lang": "raw", "pp": False, "link": None,
                          "tmpl": False, "d": {"params": params, "body": text,
                                               "active": {"cpp": text, "c": text}}}]
    return dict(base, entries=entries, active_macros=active, raw_macros=raw,
                core_order=dict(base["core_order"], **{label: len(base["core_order"])}),
                public=dict(base["public"], **{label: "windows.h"}),
                config_regions=dict(base["config_regions"], **{label: mha.directive_regions(header)}),
                header_text=dict(base["header_text"], **{label: header}),
                config_inputs=mha.guard_inputs(mha.tokenize(header)))


def test_crtimp_and_placement_new_guards_are_config_inputs():
    # TerrainResourceManagerGridRva0035A2DC.cpp:5 restores dllimport over
    # /D_CRTIMP=: an input to every CRT header after it, never removable
    index = index_from("#ifndef _CRTIMP\n#ifdef _DLL\n#define _CRTIMP __declspec(dllimport)\n#else\n"
                       "#define _CRTIMP\n#endif\n#endif\n#ifndef __PLACEMENT_NEW_INLINE\n"
                       "#define __PLACEMENT_NEW_INLINE\n#endif\n", label="Vc7/include/crtdefs.h")
    text = ("// cl: /MD /EHsc /D_CRTIMP=\n#undef _CRTIMP\n#define _CRTIMP __declspec(dllimport)\n"
            "#define __PLACEMENT_NEW_INLINE\n")
    res = mha.scan_text("Code/A.cpp", text, index)
    assert {o[1]: o[3] for o in res["occ"]} == {"_CRTIMP": "config", "__PLACEMENT_NEW_INLINE": "config"}
    assert mha.classify("Code/A.cpp", res, index)[0] is None
    assert "__PLACEMENT_VEC_NEW_INLINE" in mha.CONFIG_MACROS
    # never a definition check() counts as growth
    assert mha.check(["Code/A.cpp"], read_new=lambda p: text, read_old=lambda p: None, index=index) == []


def test_guard_inputs_are_selectors_not_guards():
    toks = mha.tokenize("#ifndef _INC_X\n#define _INC_X\n#ifndef MYSEL\nint a;\n#else\nint b;\n#endif\n"
                        "#ifndef _SIZE_T_DEFINED\ntypedef unsigned size_t;\n#define _SIZE_T_DEFINED\n#endif\n"
                        "#ifndef NULL\n#ifdef __cplusplus\n#define NULL 0\n#endif\n#endif\n"
                        "#if (_WIN32_WINNT >= 0x0400)\nint c;\n#endif\n#endif\n")
    assert mha.guard_inputs(toks) == {"MYSEL", "_WIN32_WINNT"}
    index = dict(INDEX, config_inputs={"MYSEL"})
    assert mha.is_config(index, "MYSEL") and not mha.is_config(index, "NULL")


def test_parenthesized_local_macro_values_take_the_right_branch():
    # `_WIN32_WINNT (0x0501)` once evaluated as 0: the #else copy was compared
    text = ("#define _WIN32_WINNT (0x0501)\n#if _WIN32_WINNT >= 0x0500\ntypedef unsigned long DWORD;\n"
            "#else\ntypedef unsigned short DWORD;\n#endif\n")
    res, occ = scan(text)
    assert occ["DWORD"][0] == 3 and occ["DWORD"][3] == "same"
    flipped = text.replace(">= 0x0500", "< 0x0500")
    assert scan(flipped)[1]["DWORD"][3] == "abi"


def test_unresolved_local_conditionals_are_unknown():
    # a condition on a macro the included header may define, or one that does
    # not reduce to an integer, picks no branch for certain
    for cond in ("#include <windows.h>\n#if MAX_PATH > 200\n", "#define F(x) x\n#if F(1)\n"):
        res, occ = scan(cond + "typedef unsigned long DWORD;\n#endif\n")
        assert occ["DWORD"][3] == "unknown" and "not resolve" in occ["DWORD"][4]
        assert mha.classify("Code/Game/Fixture.cpp", res, INDEX)[0] == "adapt"


STRICT_HEADER = """\
#ifndef NO_STRICT
#ifndef STRICT
#define STRICT 1
#endif
#endif
#ifdef STRICT
#define DECLARE_HANDLE(name) struct name##__ { int unused; }; typedef struct name##__ *name
#else
#define DECLARE_HANDLE(name) typedef void *name
#endif
DECLARE_HANDLE(HWND);
"""


def test_no_strict_units_do_not_trust_sink_expanded_declarations():
    index = index_from(STRICT_HEADER)
    local = "struct HWND__ { int unused; };\ntypedef struct HWND__ *HWND;\n"
    res = mha.scan_text("Code/A.cpp", local, index)
    assert {o[1]: o[3] for o in res["occ"]} == {"HWND__": "same", "HWND": "same"}
    assert mha.classify("Code/A.cpp", res, index)[0] == mha.DROP_IN
    # under /DNO_STRICT the real HWND is void *: the sink's STRICT text proves nothing
    res = mha.scan_text("Code/A.cpp", "// cl: /DNO_STRICT\n" + local, index)
    assert {o[1]: o[3] for o in res["occ"]} == {"HWND__": "unknown", "HWND": "unknown"}
    assert mha.classify("Code/A.cpp", res, index)[0] == "adapt"


def test_flags_model_undefines_and_runtimes():
    defines, md, _, flags = mha.file_defines("// cl: /MTd /DUNICODE /UUNICODE /U _WIN32\n", "cpp", "Code/A.cpp")
    assert defines["_MT"] == "1" and defines["_DEBUG"] == "1" and not md
    assert "UNICODE" not in defines and "_WIN32" not in defines
    assert mha.file_undefs(flags) == {"UNICODE", "_WIN32"}
    # /U after /D: the unit's TCHAR is char again
    _, occ = scan("// cl: /DUNICODE /UUNICODE\ntypedef char TCHAR;\n")
    assert occ["TCHAR"][3] == "same"
    # a header's `#define _WIN32` under `#ifdef WIN32` does not make the
    # predefined _WIN32 depend on a unit without -DWIN32 (WTypes.h's WINAPI)
    index = index_from("#ifdef WIN32\n#define _WIN32\n#endif\n")
    config = mha.UnitConfig(index, "cpp", mha.file_defines("", "cpp", "Code/A.cpp")[0], {})
    assert "WIN32" in config.delta and not config.depends("_WIN32")
    config = mha.UnitConfig(index, "cpp", {}, {}, {"_WIN32"})
    assert config.depends("_WIN32")


def test_struct_alignment_is_compared():
    index = index_from("struct tm { int tm_sec; int tm_min; };\n", label="Vc7/include/time.h")
    res = mha.scan_text("Code/A.cpp", "struct tm { int tm_sec; int tm_min; };\n", index)
    assert res["occ"][0][3] == "same"
    # #pragma pack(push,1): same size and offsets, alignment 1 against 4
    res = mha.scan_text("Code/A.cpp", "#pragma pack(push,1)\nstruct tm { int tm_sec; int tm_min; };\n"
                                      "#pragma pack(pop)\n", index)
    assert res["occ"][0][3] == "abi" and "alignment 1 vs 4" in res["occ"][0][4]
    assert mha.classify("Code/A.cpp", res, index)[0] == "conflicting"
    # an alignment the layout model does not establish is unknown, never same
    res = mha.scan_text("Code/A.cpp", "struct __declspec(align(16)) tm { int tm_sec; int tm_min; };\n", index)
    assert res["occ"][0][3] == "unknown"


def test_drop_in_is_a_candidate_the_byte_gate_proves(tmp_path, monkeypatch, capsys):
    res, _ = scan("typedef unsigned long DWORD;\n")
    queue = tmp_path / "reverse/ms_header_queue.tsv"
    queue.parent.mkdir()
    rows = mha.write_queue({"Code/Game/A.cpp": res}, INDEX, queue=queue, occurrences=tmp_path / "o.tsv")
    row = dict(zip(mha.QUEUE_HEADER, rows[0]))
    assert row["class"] == "drop-in candidate" and row["note"] == mha.PROVE
    assert "./build.sh" in mha.PROVE and "byte gate is the authority" in mha.PROVE
    monkeypatch.setattr(mha, "QUEUE", queue)
    assert mha.main(["next", "--class", "drop-in"]) == 0
    out = capsys.readouterr()
    assert "Code/Game/A.cpp\tdrop-in candidate" in out.out and mha.PROVE in out.err
    import repair_queue
    import next_work
    source = tmp_path / "Code/Game/A.cpp"
    source.parent.mkdir(parents=True)
    source.write_text("// queued source\n")
    monkeypatch.setattr(repair_queue, "ROOT", tmp_path)
    monkeypatch.setattr(next_work, "busy_keys", lambda: set())
    assert repair_queue.main(["ms-headers", "--class", "drop-in-candidate"]) == 0
    out = capsys.readouterr().out
    assert "Code/Game/A.cpp" in out and "byte gate is the authority" in out


def test_tokenization_honours_the_deadline():
    mha._DEADLINE[0] = mha.time.monotonic() - 1
    try:
        try:
            mha.tokenize("int x;\n" * 2000)
        except mha.AnalysisIncomplete:
            pass
        else:
            raise AssertionError("tokenize ran past its deadline")
    finally:
        mha._DEADLINE[0] = None
    # one huge file: the scan fails in tokenization already
    res = mha.scan_text("Code/A.cpp", "x " * 20000, INDEX, timeout=0)
    assert res["error"] == "timeout"
