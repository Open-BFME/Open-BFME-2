#!/usr/bin/env python3
"""tools/permute.py body_lines/focus_of: brace-counting body detection."""
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

import permute  # noqa: E402


def picked(source, symbol=None, focus=None):
    lines = source.split("\n")
    focus = focus or permute.focus_of(symbol)
    return [lines[i].strip() for i in permute.body_lines(lines, focus)]


def test_column_zero_definition():
    src = "int Foo::bar(int x)\n{\n    int y = x + 1;\n    return y;\n}\n"
    assert picked(src, "?bar@Foo@@QAEHH@Z") == ["int y = x + 1;", "return y;"]


def test_indented_definition():
    src = "namespace n {\n  int Foo::bar(int x)\n  {\n    return x * 2;\n  }\n}\n"
    assert picked(src, "?bar@Foo@@QAEHH@Z") == ["return x * 2;"]


def test_one_line_definition():
    src = "int Foo::bar(int x) { return x - 1; }\nint other() { return 0; }\n"
    assert picked(src, "?bar@Foo@@QAEHH@Z") == ["int Foo::bar(int x) { return x - 1; }"]


def test_brace_statement_line_is_a_statement():
    src = "void Foo::bar()\n{\n    { Item i; i.go(); }\n}\n"
    assert picked(src, "?bar@Foo@@QAEXXZ") == ["{ Item i; i.go(); }"]


def test_constructor_initializer_list():
    src = ("Foo::Foo(int a, int b)\n    : m_a(a),\n      m_b(b + 1)\n{\n    m_c = 0;\n}\n"
           "void Foo::run()\n{\n    m_c = 5;\n}\n")
    assert permute.focus_of("??0Foo@@QAE@HH@Z") is not None
    assert picked(src, "??0Foo@@QAE@HH@Z") == [": m_a(a),", "m_b(b + 1)", "m_c = 0;"]


def test_destructor_focus_picks_destructor_only():
    src = "Foo::Foo()\n{\n    m_a = 1;\n}\nFoo::~Foo()\n{\n    m_a = 2;\n}\n"
    assert picked(src, "??0Foo@@QAE@XZ") == ["m_a = 1;"]
    assert picked(src, "??1Foo@@UAE@XZ") == ["m_a = 2;"]


def test_multi_function_file_picks_target_not_first_or_last():
    src = ("static int helper(int v)\n{\n    return v;\n}\n"
           "int Foo::target(int v)\n{\n    int t = helper(v);\n    return t;\n}\n"
           "int Foo::later(int v)\n{\n    return v + 9;\n}\n")
    assert picked(src, "?target@Foo@@QAEHH@Z") == ["int t = helper(v);", "return t;"]


def test_call_statement_and_declaration_are_not_definitions():
    src = ("int Foo::bar(int);\nint g = compute(3);\n"
           "int Foo::bar(int x)\n{\n    return Foo::baz(x);\n}\n")
    assert picked(src, "?bar@Foo@@QAEHH@Z") == ["return Foo::baz(x);"]


def test_macro_continuation_is_not_a_definition():
    src = ("#define REC(x) \\\n  track(x); \\\n  note(x)\n"
           "void GameEngine::run()\n{\n    step();\n}\n")
    assert picked(src, "?run@GameEngine@@QAEXXZ") == ["step();"]


def test_split_signature_and_nested_braces():
    src = ("void Foo::bar(int a,\n              int b) const\n{\n    if (a) {\n        b++;\n    }\n"
           "    while (b) { b--; }\n}\n")
    assert picked(src, "?bar@Foo@@QBEXHH@Z") == ["if (a) {", "b++;", "while (b) { b--; }"]


def test_without_focus_every_body():
    src = "int a() { return 1; }\nint b()\n{\n    return 2;\n}\n"
    lines = src.split("\n")
    assert [lines[i].strip() for i in permute.body_lines(lines)] == ["int a() { return 1; }", "return 2;"]


def test_missing_target_falls_back_to_every_body():
    src = "int a()\n{\n    return 1;\n}\n"
    assert picked(src, "?nope@Foo@@QAEHXZ") == ["return 1;"]


def test_return_type_of_indented_and_one_line_definitions():
    src = ("namespace n {\n  int Foo::bar(int x)\n  {\n    return x * 2;\n  }\n}\n"
           "float baz() { return 1.5f * 2.0f; }\n"
           "void Foo::none()\n{\n    return;\n}\n")
    lines = src.split("\n")
    assert permute._return_type(lines, 3) == "int"
    assert permute._return_type(lines, 6) == "float"
    assert permute._return_type(lines, 9) is None


def test_flag_search_preserves_directive_after_bank_metadata(tmp_path, monkeypatch):
    # an invented include directory: the include value allowlist is not what this tests
    monkeypatch.setattr(permute.build, "_include_values", lambda: None)
    metadata = "// symbol\n" + "// partial score=0.8 date=2026-10-20\n" * 16
    source = metadata + "// cl: /O1 /Ob1 /G7 /Oy- /Iinclude-dir\nint body() { return 1; }\n"
    variant = permute._with_flags(source, "/O2", ("/O1", "/Ox"))
    assert variant.startswith(metadata)
    assert variant.count("// cl:") == 1
    assert variant.endswith("int body() { return 1; }\n")
    candidate = tmp_path / "candidate.cpp"
    candidate.write_text(variant, encoding="utf-8")
    flags = permute.build.source_extra_flags(candidate)
    assert "-O2" in flags and "-O1" not in flags
    assert all(flag in flags for flag in ("-Ob1", "-G7", "-Oy-", "-Iinclude-dir"))


def test_flag_variants_drop_late_directive_toggles():
    metadata = "// symbol\n" + "// bank history\n" * 16
    body = "int body() { return 1; }\n"
    source = metadata + "// cl: /O1 /Ob1 /G7 /Oy- /Iinclude-dir\n" + body
    variants = list(permute._flag_variants(source))
    assert all(variant.startswith(metadata) and variant.endswith(body) for variant in variants)
    assert all(variant.count("// cl:") == 1 for variant in variants)
    directives = [next(line for line in variant.splitlines() if line.startswith("// cl:")).split()[2:]
                  for variant in variants]
    assert any("/Ob1" not in flags for flags in directives)
    assert any("/Oy-" not in flags for flags in directives)
    assert all("/Iinclude-dir" in flags for flags in directives)


def test_flag_search_changes_first_effective_directive_only():
    metadata = "// symbol\n" + "// bank history\n" * 16
    source = metadata + "// cl: /O1 /G7\n// cl: /O1 /G6\nint body() { return 1; }\n"
    variant = permute._with_flags(source, "/O2", ("/O1",))
    assert variant == metadata + "// cl: /G7 /O2\n// cl: /O1 /G6\nint body() { return 1; }\n"


def test_flag_mutation_reads_past_bank_metadata():
    class FlagOnlyRng:
        def choice(self, choices):
            return "flag" if "flag" in choices else "/Op"

        def random(self):
            return 0.0

    metadata = "// symbol\n" + "// bank history\n" * 16
    source = metadata + "// cl: /O1 /G7\nint body() { return 1; }\n"
    variant, kind = permute.mutate(source, FlagOnlyRng())
    assert kind == "flag"
    assert variant == metadata + "// cl: /O1 /G7 /Op\nint body() { return 1; }\n"


def test_flag_mutation_leaves_ignored_later_directive_untouched():
    class FlagSwapRng:
        def choice(self, choices):
            return "flag" if "flag" in choices else choices[0]

        def random(self):
            return 0.9

    metadata = "// symbol\n" + "// bank history\n" * 16
    source = (metadata + "// cl: /Iinclude-dir\n// cl: " + permute.FLAG_SWAPS[0][0]
              + "\nint body() { return 1; }\n")
    assert permute.mutate(source, FlagSwapRng()) == (source, None)


def test_flag_variants_leave_ignored_later_directive_untouched():
    metadata = "// symbol\n" + "// bank history\n" * 16
    ignored = "// cl: /O1 /Ob1 /Oy-"
    source = metadata + "// cl: /O1 /G7\n" + ignored + "\nint body() { return 1; }\n"
    for variant in permute._flag_variants(source):
        directives = [line for line in variant.splitlines() if line.startswith("// cl:")]
        assert len(directives) == 2 and directives[1] == ignored
