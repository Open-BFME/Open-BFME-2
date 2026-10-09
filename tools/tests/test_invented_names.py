"""invented_names.py: a new address-named global in a Code/ change is reported when
reverse/data_ledger.csv already has something usable at its address -- an external
owner (extern it), a compiler literal (use the literal) or a vtable (reach it through
its class); TU-local statics and provisional guesses are never suggested. The old and
new files are lexed whole, so comments (wherever their delimiters are) and strings are
not code, and names the file already used in code are not new. Unresolved names are
counted, and a hard wall-clock budget ends a run with a partial report. Report only:
--shadow always exits 0."""
import os
import subprocess
import sys
import threading
import time
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
TOOL = TOOLS / "invented_names.py"
sys.path.insert(0, str(TOOLS))
import invented_names as inv  # noqa: E402

LEDGER = """\
address,size,section,kind,name,source,status,names,defs,refs
0x007BAC1C,656,.rdata,string,??_C@_00CNPNBAHC@?$AA@,,literal,??_C@_00CNPNBAHC@?$AA@;?g_Rva0107301CEmptyString@@3QBDB;?g_bfmeAptDefaultTeamName@@3QBDB,1,10
0x007BB8D8,4,.rdata,float,__real@3f800000,,literal,?g_007BB8D8@@3MA;?g_Va00BBB8D8@@3MA;__real@3f800000;_g_bfmeDefaultBU@Code/GameEngine/Source/Common/Bfme/T_009F4FB0.cpp;_kZero@Code/GameEngine/Source/GameLogic/Object/Update/SpyVisionUpdateCtor.cpp,0,10
0x0081C780,4,.rdata,vtable,??_7Foo@@6B@,,literal,??_7Foo@@6B@;??_7Rva005F5C77Base0@@6B@;??_7Base@NS@@6B@,0,3
0x0087A630,4,.rdata,vtable,??_7Rva005F5C77Base0@@6B@,,literal,,0,1
0x009FE758,4,.data,global,?TheWritableGlobalData@@3PAVGlobalData@@A,Code/GameEngine/GameClient.cpp,provisional,?TheWritableGlobalData@@3PAVGlobalData@@A;?g_00DFE758@@3PAXA;?g_Va009FE758@@3PAXA;_TheGameLogic@Code/GameEngine/Other.cpp,2,5
0x00A02EEC,4,.data,global,?TheGameInfo@@3PAVGameInfo@@A,Code/GameEngine/GameInfo.cpp,owned,,1,3
0x00A1835C,4,.data,global,?spFrameStack@@3PAXA,Code/Libraries/Apt.cpp,provisional,?g_bfmeFrameStackAtE1835C@@3PAXA;?spFrameStack@@3PAXA,1,4
0x00A30000,4,.data,global,?g_bfmeGuessName@@3HA,,provisional,?g_bfmeGuessName@@3HA;?g_00E30000@@3HA;_sLocal@Code/x.cpp;?TheNullChr@?1??str@AsciiString@@QBEPBDXZ@4DB,1,2
"""
SRC = "Code/GameEngine/Source/a.cpp"


class Repo:
    def __init__(self, root):
        self.root = root
        self.git("init", "-q")
        self.write("reverse/data_ledger.csv", LEDGER)
        self.write(SRC, "// a\nint f() { return 0; }\n")
        self.git("add", "-A")
        self.git("commit", "-q", "-m", "base")

    def git(self, *args):
        env = dict(os.environ, GIT_AUTHOR_NAME="t", GIT_COMMITTER_NAME="t",
                   GIT_AUTHOR_EMAIL="t@example.com", GIT_COMMITTER_EMAIL="t@example.com")
        got = subprocess.run(["git", "-C", str(self.root), *args], capture_output=True, text=True, env=env)
        if got.returncode:
            raise AssertionError(got.stderr)
        return got.stdout.strip()

    def write(self, rel, text):
        path = self.root / rel
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text, newline="\n")

    def stage(self, rel, text):
        self.write(rel, text)
        self.git("add", "--", rel)

    def run(self, *args, env=None):
        return subprocess.run([sys.executable, str(TOOL), *args], cwd=self.root, capture_output=True, text=True,
                              env=env)


@pytest.fixture
def repo(tmp_path):
    return Repo(tmp_path)


def test_new_bare_name_for_a_named_global_is_reported(repo):
    repo.stage(SRC, "// a\nextern void *g_00DFE758;\nint f() { return g_00DFE758 != 0; }\n")
    got = repo.run("--staged")
    assert got.returncode == 1, got.stderr
    # TheGameLogic is a TU-local static of Other.cpp: not usable here, so not suggested
    assert (f"{SRC}:2 invents g_00DFE758 for 0x009FE758; the tree already calls it "
            "TheWritableGlobalData: extern it or include its header") in got.stderr
    assert "TheGameLogic" not in got.stderr
    assert got.stderr.count(" invents ") == 1          # once per (file, name), at its first line


def test_shadow_never_refuses(repo):
    repo.stage(SRC, "// a\nextern void *g_00DFE758;\nint f() { return 0; }\n")
    got = repo.run("--staged", "--shadow")
    assert got.returncode == 0
    assert "shadow" in got.stderr and "invents g_00DFE758" in got.stderr


@pytest.mark.parametrize("name", ["g_Va00E02EEC", "g_Rva00A02EEC", "g_Rva00E02EEC", "g_00E02EEC", "DAT_00E02EEC"])
def test_va_and_rva_spellings_resolve(repo, name):
    if name.startswith("DAT_"):
        name = "g_" + name           # the hatch counts g_...DAT_<hex>
    repo.stage(SRC, f"// a\nextern int {name};\nint f() {{ return {name}; }}\n")
    got = repo.run("--staged")
    assert f"invents {name} for 0x00A02EEC; the tree already calls it TheGameInfo" in got.stderr


def test_name_the_ledger_binds_resolves_where_it_is_bound(repo):
    # 0x0107301C spells no ledger address; the ledger binds the name to 0x007BAC1C, which
    # holds the empty string literal (g_bfmeAptDefaultTeamName there is only a guess)
    repo.stage(SRC, "// a\nextern const char *g_Rva0107301CEmptyString;\nint f() { return 0; }\n")
    got = repo.run("--staged")
    assert ("invents g_Rva0107301CEmptyString for 0x007BAC1C, which is the string literal \"\" "
            "(??_C@_00CNPNBAHC@?$AA@): use the literal") in got.stderr
    assert "g_bfmeAptDefaultTeamName" not in got.stderr and "extern" not in got.stderr


def test_ledger_bound_invented_name_without_g_prefix(repo):
    repo.stage(SRC, "// a\nextern void *g_bfmeFrameStackAtE1835C;\nint f() { return 0; }\n")
    got = repo.run("--staged")
    assert "invents g_bfmeFrameStackAtE1835C for 0x00A1835C; the tree already calls it spFrameStack" in got.stderr


def test_a_literal_address_says_use_the_literal(repo):
    # review: g_Va00BBB8D8 is 0x007BB8D8, __real@3f800000; g_bfmeDefaultBU and kZero there
    # are TU-local statics, so the advice is the literal 1.0f, never `extern kZero`.
    # 0x0087A630 holds only the vftable of an address-named class: nothing to report.
    repo.stage(SRC, "// a\nextern float g_Va00BBB8D8;\nextern const void *const g_00C7A630[];\n"
                    "int f() { return 0; }\n")
    got = repo.run("--staged")
    assert got.returncode == 1, got.stderr
    assert (f"{SRC}:2 invents g_Va00BBB8D8 for 0x007BB8D8, which is the float literal 1.0f "
            "(__real@3f800000): use the literal") in got.stderr
    assert "kZero" not in got.stderr and "g_bfmeDefaultBU" not in got.stderr
    assert "extern it" not in got.stderr and "Write the literal itself" in got.stderr
    assert "g_00C7A630" not in got.stderr


def test_only_statics_and_guesses_is_nothing_to_suggest(repo):
    # 0x00A30000: a TU-local static, a function-local static and a bfme guess
    repo.stage(SRC, "// a\nextern int g_00E30000;\nint f() { return g_00E30000; }\n")
    got = repo.run("--staged")
    assert got.returncode == 0 and got.stderr == "", got.stderr


def test_alternatives_are_classified():
    assert inv.classify("?TheWritableGlobalData@@3PAVGlobalData@@A", None) == "owner"
    assert inv.classify("__imp__CreateFileA@28", None) == "owner"
    assert inv.classify("__real@3f800000", None) == "literal"
    assert inv.classify("??_C@_00CNPNBAHC@?$AA@", None) == "literal"
    assert inv.classify("??_7Foo@@6B@", None) == "vtable"
    assert inv.classify("??_R4Foo@@6B@", None) == "vtable"
    assert inv.classify("_kZero", "Code/x.cpp") == "static"
    assert inv.classify("?TheNullChr@?1??str@AsciiString@@QBEPBDXZ@4DB", None) == "static"
    assert inv.classify("?g_bfmeDefaultBU@@3MA", None) == "guess"
    assert inv.classify("?g_BfmeRender2DZ@@3MA", None) == "guess"
    assert inv.classify("?bfmeSetProjectionDepthBias@@YAXM@Z", None) == "guess"
    assert inv.classify("?g_Va00BBB8D8@@3MA", None) is None
    assert inv.literal_text("__real@3f000000") == "the float literal 0.5f (__real@3f000000)"
    assert inv.literal_text("__real@3ff0000000000000") == "the double literal 1.0 (__real@3ff0000000000000)"
    assert inv.literal_text("??_C@_03KJOFHJLG@abc?$AA@") == 'the string literal "abc" (??_C@_03KJOFHJLG@abc?$AA@)'


def test_vtables_are_reached_through_their_class(repo):
    repo.stage(SRC, "// a\nextern const void *const g_00C1C780[];\nint f() { return 0; }\n")
    got = repo.run("--staged")
    assert ("invents g_00C1C780 for 0x0081C780, which is Foo::`vftable', NS::Base::`vftable': reach it "
            "through its class, not an extern name\n") in got.stderr


def test_comments_strings_and_unknown_addresses_are_ignored(repo):
    repo.stage(SRC, "// a\n// g_00DFE758 is TheWritableGlobalData\n"
                    "const char *s = \"g_00DFE758\";\n"
                    "/* g_Va00E02EEC\n"
                    " * g_00DFE758 inside a doc comment\n"
                    "   g_Va00E02EEC */\n"
                    "extern int g_00ABCDEF;          // no ledger row there\n"
                    "int f() { return 0; }\n")
    got = repo.run("--staged")
    assert got.returncode == 0, got.stderr
    assert " invents " not in got.stderr
    # an address-named global the ledger cannot place is counted, not passed over
    assert ("not checked: 1 new address-named global(s) whose name spells no data-ledger address "
            "(g_00ABCDEF): unresolved") in got.stderr


def test_misleading_hex_names_are_counted_unresolved(repo):
    # review: g_Rva003ADEBF_v8 names a local of the function at 0x003ADEBF, not the data
    repo.stage(SRC, "// a\nstatic int g_Rva003ADEBF_v8;\nint f() { return g_Rva003ADEBF_v8; }\n")
    got = repo.run("--staged", "--shadow")
    assert got.returncode == 0
    assert "not checked: 1 new address-named global(s)" in got.stderr and "g_Rva003ADEBF_v8" in got.stderr


def test_comment_line_added_inside_an_existing_block_comment(repo):
    # review: the hunk holds only the added line, not the /* that opens its comment
    repo.stage(SRC, "// a\n/*\n   notes\n*/\nint f() { return 0; }\n")
    repo.git("commit", "-q", "-m", "notes")
    repo.stage(SRC, "// a\n/*\n   notes\n   g_00DFE758 is TheWritableGlobalData\n*/\nint f() { return 0; }\n")
    got = repo.run("--staged")
    assert got.returncode == 0 and got.stderr == "", got.stderr


def test_block_comment_state_does_not_leak_across_hunks(repo):
    # review: an added /* closed by an unchanged line hid a real declaration in a later hunk
    body = ["int v%d;\n" % i for i in range(30)]
    body[3] = "int closer; */\n"
    repo.stage(SRC, "".join(body))
    repo.git("commit", "-q", "-m", "body")
    body.insert(3, "/* opened here, closed on the next, unchanged line\n")
    body.insert(25, "extern void *g_00DFE758;\n")
    repo.stage(SRC, "".join(body))
    got = repo.run("--staged")
    assert f"{SRC}:26 invents g_00DFE758 for 0x009FE758" in got.stderr, got.stderr


def test_an_old_comment_does_not_hide_a_new_declaration(repo):
    # review: the old file mentioned the name in a comment only; the new one declares it
    repo.stage(SRC, "// a\n// g_00DFE758 was the old name of TheWritableGlobalData\nint f() { return 0; }\n")
    repo.git("commit", "-q", "-m", "comment")
    repo.stage(SRC, "// a\n// g_00DFE758 was the old name of TheWritableGlobalData\n"
                    "extern void *g_00DFE758;\nint f() { return 0; }\n")
    got = repo.run("--staged")
    assert f"{SRC}:3 invents g_00DFE758 for 0x009FE758" in got.stderr, got.stderr


def test_name_the_file_already_held_is_not_new(repo):
    repo.stage(SRC, "// a\nextern void *g_00DFE758;\nint f() { return 0; }\n")
    repo.git("commit", "-q", "-m", "invent")
    repo.stage(SRC, "// a\nextern void *g_00DFE758;\nint f() { return 0; }\nint g() { return g_00DFE758 != 0; }\n")
    got = repo.run("--staged")
    assert got.returncode == 0 and got.stderr == ""


def test_only_code_sources(repo):
    repo.stage("tools/x.py", "g_00DFE758 = 1\n")
    repo.stage("Code/masm_dumps/x.asm", "extern g_00DFE758:dword\n")
    repo.stage("Other/a.cpp", "extern void *g_00DFE758;\n")
    got = repo.run("--staged")
    assert got.returncode == 0 and got.stderr == ""


def test_line_numbers_follow_the_hunk(repo):
    body = "".join(f"int v{i};\n" for i in range(20))
    repo.stage(SRC, body)
    repo.git("commit", "-q", "-m", "body")
    lines = body.splitlines(keepends=True)
    lines.insert(12, "extern int g_Va00E02EEC;\n")
    repo.stage(SRC, "".join(lines))
    got = repo.run("--staged")
    assert f"{SRC}:13 invents g_Va00E02EEC" in got.stderr


def test_many_names_in_a_large_file_are_lexed_once(repo):
    # review: 500 added names against a 3.23 MB file took 54.7 s, one scan of the old
    # file per name; each file is now lexed once
    filler = "".join("int filler_%06d = %d; // comment %d\n" % (i, i, i) for i in range(60000))
    repo.stage(SRC, filler)
    repo.git("commit", "-q", "-m", "large")
    added = "".join("extern int g_Va%08X;\n" % (0x00B00000 + 4 * i) for i in range(500))
    repo.stage(SRC, filler + added + "extern void *g_00DFE758;\n")
    t0 = time.monotonic()
    got = repo.run("--staged", "--shadow")
    assert "partial" not in got.stderr, got.stderr
    assert "invents g_00DFE758 for 0x009FE758" in got.stderr
    assert "not checked: 500 new address-named global(s)" in got.stderr
    assert time.monotonic() - t0 < 10


def test_commit_and_range_modes(repo):
    base = repo.git("rev-parse", "HEAD")
    repo.stage("Code/GameEngine/Source/b.cpp", "extern int g_Va00E02EEC;\n")
    repo.git("commit", "-q", "-m", "invent b")
    tip = repo.git("rev-parse", "HEAD")
    got = repo.run("--commit", tip)
    assert got.returncode == 1 and "Code/GameEngine/Source/b.cpp:1 invents g_Va00E02EEC" in got.stderr
    got = repo.run("--range", base, tip, "--shadow")
    assert got.returncode == 0 and "invents g_Va00E02EEC" in got.stderr
    got = repo.run("--backtest", "5", "--ref", "HEAD")
    assert "would report: 1 commit(s)" in got.stdout
    # --commit judges that commit only, not the last one before it touching Code/
    repo.stage("notes.txt", "x\n")
    repo.git("commit", "-q", "-m", "notes")
    got = repo.run("--commit", "HEAD")
    assert got.returncode == 0 and got.stderr == ""


def test_budget_expiry_exits_0_with_a_partial_report(repo):
    repo.stage(SRC, "// a\nextern void *g_00DFE758;\n")
    env = dict(os.environ, BFME_SHADOW_BUDGET_S="0.000001")
    got = repo.run("--staged", env=env)                       # not --shadow: still exit 0
    assert got.returncode == 0
    assert "invented_names: partial: budget of 1e-06s exceeded after 0 of" in got.stderr


def test_budget_kills_hanging_git(tmp_path, monkeypatch, capsys):
    from test_replay_check import _kill, direct_children_dead, hanging_git
    monkeypatch.setattr(inv, "GIT", hanging_git(tmp_path))
    threads = threading.active_count()
    t0 = time.monotonic()
    code = inv.main(["--staged", "--ledger", str(tmp_path / "none.csv"), "--budget", "2"])
    assert code == 0 and time.monotonic() - t0 < 15
    assert "partial: budget of 2s exceeded after 0 of ? file(s)" in capsys.readouterr().err
    for pid in direct_children_dead(tmp_path):
        _kill(pid)
    assert threading.active_count() == threads


# review round 2: what the compiler's first phases do to the text

def test_raw_string_contents_are_not_code(repo):
    # a plain-string reading would end the literal at the inner quote and see the name
    repo.stage(SRC, '// a\nconst char *s = R"x( " g_00DFE758 " )" still )x";\nint f() { return 0; }\n')
    got = repo.run("--staged")
    assert got.returncode == 0 and got.stderr == "", got.stderr


def test_crlf_continued_line_comment_is_not_code(repo):
    repo.git("config", "core.autocrlf", "false")
    repo.stage(SRC, "// a\r\n// a note that runs on \\\r\n   g_00DFE758 is still the comment\r\nint f();\r\n")
    got = repo.run("--staged")
    assert got.returncode == 0 and got.stderr == "", got.stderr


def test_slash_spliced_to_slash_is_a_comment(repo):
    repo.stage(SRC, "// a\n/\\\n/ g_00DFE758 in a comment the splice opened\nint f();\n")
    got = repo.run("--staged")
    assert got.returncode == 0 and got.stderr == "", got.stderr


def test_spliced_identifier_is_found_at_its_first_line(repo):
    repo.stage(SRC, "// a\nextern void *g_00DF\\\nE758;\nint f();\n")
    got = repo.run("--staged")
    assert f"{SRC}:2 invents g_00DFE758 for 0x009FE758" in got.stderr, got.stderr


def test_line_numbers_count_spliced_lines(repo):
    repo.stage(SRC, "// a\n#define X 1 \\\n  + 2\nextern void *g_00DFE758;\n")
    got = repo.run("--staged")
    assert f"{SRC}:4 invents g_00DFE758 for 0x009FE758" in got.stderr, got.stderr


def test_added_line_splices_into_an_unchanged_line(repo):
    # review round 3: `extern void *benign\` became `extern void *g_00DF\` above the
    # unchanged line `E758;`; no added line held a 6-hex run, so no blob was read
    repo.stage(SRC, "// a\nextern void *benign\\\nE758;\nint f();\n")
    repo.git("commit", "-q", "-m", "benign")
    repo.stage(SRC, "// a\nextern void *g_00DF\\\nE758;\nint f();\n")
    got = repo.run("--staged")
    assert f"{SRC}:2 invents g_00DFE758 for 0x009FE758" in got.stderr, got.stderr


def test_unchanged_line_splices_into_an_added_line(repo):
    # the hunk boundary inside a splice: the unchanged line ends in a backslash
    repo.stage(SRC, "// a\nextern void *g_00DF\\\nXXXX;\nint f();\n")
    repo.git("commit", "-q", "-m", "odd")
    repo.stage(SRC, "// a\nextern void *g_00DF\\\nE758;\nint f();\n")
    got = repo.run("--staged")
    assert f"{SRC}:2 invents g_00DFE758 for 0x009FE758" in got.stderr, got.stderr


def test_removed_splice_uncomments_an_unchanged_line(repo):
    # a `//` comment continued onto the next line hid a declaration; the splice goes
    repo.stage(SRC, "// a\n// note \\\nextern void *g_00DFE758;\nint f();\n")
    repo.git("commit", "-q", "-m", "commented")
    repo.stage(SRC, "// a\n// note\nextern void *g_00DFE758;\nint f();\n")
    got = repo.run("--staged")
    assert f"{SRC}:3 invents g_00DFE758 for 0x009FE758" in got.stderr, got.stderr


def test_spliceless_change_without_hex_reads_no_blob(repo, monkeypatch):
    # the cheap path stays: nothing to read for an ordinary edit
    repo.stage(SRC, "// a\nint f() { return 1; }\n")
    calls = []
    run = inv.Budget.run

    def spy(self, args, input=None):
        calls.append(args)
        return run(self, args, input)

    monkeypatch.setattr(inv.Budget, "run", spy)
    monkeypatch.chdir(repo.root)
    assert inv.main(["--staged"]) == 0
    assert not [a for a in calls if "cat-file" in a]


def test_splice_keeps_offsets_and_lines():
    code, offsets, first = inv.code_tokens("a\r\nb\\\r\nc g_00DFE758 /* g_Va00E02EEC */\n")
    assert "g_00DFE758" in first and "g_Va00E02EEC" not in first
    at = first["g_00DFE758"]
    assert code.count("\n", 0, at) + inv.bisect.bisect_right(offsets, at) + 1 == 3


def test_missing_ledger_is_not_an_error(repo):
    repo.git("rm", "-q", "reverse/data_ledger.csv")
    repo.stage(SRC, "// a\nextern void *g_00DFE758;\n")
    got = repo.run("--staged", "--shadow")
    assert got.returncode == 0 and got.stderr == ""


def test_regexes_stay_in_step_with_their_owners():
    import data_ledger
    import hatch_counters
    assert inv.ADDR_GLOBAL is hatch_counters.ADDR_GLOBAL
    assert inv.INVENTED.pattern == data_ledger.INVENTED.pattern
    assert set(inv.LITERALS) <= {prefix for prefix, kind in data_ledger.EMITTED if kind in ("string", "wstring", "float")}
    assert {p for p in inv.VTABLE_RTTI if p != "??_8"} == {prefix for prefix, kind in data_ledger.EMITTED
                                                           if kind in ("vtable", "rtti")}
    for symbol in ("?g_Va00BBB8D8@@3MA", "?Foo@Bar@@2HA", "_c_name", "??_7Foo@@6B@"):
        assert inv.identifier(symbol) == data_ledger.identifier(symbol)


def test_pre_commit_calls_it_in_shadow():
    hook = (TOOLS.parent / ".githooks" / "pre-commit").read_text(encoding="utf-8")
    call = [line for line in hook.splitlines() if "tools/invented_names.py" in line and not line.startswith("#")]
    assert len(call) == 1 and "--staged --shadow" in call[0] and "|| echo" in call[0]
