"""invented_names.py: a new address-named global on an added Code/ line is reported when
reverse/data_ledger.csv already has a real name at its address; literals, invented
names, comments, names the file already held and other files are not. Report only:
--shadow always exits 0."""
import os
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
TOOL = TOOLS / "invented_names.py"
sys.path.insert(0, str(TOOLS))
import invented_names as inv  # noqa: E402

LEDGER = """\
address,size,section,kind,name,source,status,names,defs,refs
0x007BAC1C,656,.rdata,string,??_C@_00CNPNBAHC@?$AA@,,literal,??_C@_00CNPNBAHC@?$AA@;?g_Rva0107301CEmptyString@@3QBDB;?g_bfmeAptDefaultTeamName@@3QBDB,1,10
0x007BB8D8,4,.rdata,float,__real@3f800000,,literal,?g_007BB8D8@@3MA;?g_Va00BBB8D8@@3MA;__real@3f800000,0,10
0x0081C780,4,.rdata,vtable,??_7Foo@@6B@,,literal,??_7Foo@@6B@;??_7Rva005F5C77Base0@@6B@;??_7Base@NS@@6B@,0,3
0x0087A630,4,.rdata,vtable,??_7Rva005F5C77Base0@@6B@,,literal,,0,1
0x009FE758,4,.data,global,?TheWritableGlobalData@@3PAVGlobalData@@A,Code/GameEngine/GameClient.cpp,provisional,?TheWritableGlobalData@@3PAVGlobalData@@A;?g_00DFE758@@3PAXA;?g_Va009FE758@@3PAXA;_TheGameLogic@Code/GameEngine/Other.cpp,2,5
0x00A02EEC,4,.data,global,?TheGameInfo@@3PAVGameInfo@@A,Code/GameEngine/GameInfo.cpp,owned,,1,3
0x00A1835C,4,.data,global,?spFrameStack@@3PAXA,Code/Libraries/Apt.cpp,provisional,?g_bfmeFrameStackAtE1835C@@3PAXA;?spFrameStack@@3PAXA,1,4
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

    def run(self, *args):
        return subprocess.run([sys.executable, str(TOOL), *args], cwd=self.root, capture_output=True, text=True)


@pytest.fixture
def repo(tmp_path):
    return Repo(tmp_path)


def test_new_bare_name_for_a_named_global_is_reported(repo):
    repo.stage(SRC, "// a\nextern void *g_00DFE758;\nint f() { return g_00DFE758 != 0; }\n")
    got = repo.run("--staged")
    assert got.returncode == 1, got.stderr
    assert (f"{SRC}:2 invents g_00DFE758 for 0x009FE758; the tree already calls it "
            "TheWritableGlobalData, TheGameLogic (static, Other.cpp)") in got.stderr
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
    # 0x0107301C spells no ledger address; the ledger binds the name to 0x007BAC1C
    repo.stage(SRC, "// a\nextern const char *g_Rva0107301CEmptyString;\nint f() { return 0; }\n")
    got = repo.run("--staged")
    assert ("invents g_Rva0107301CEmptyString for 0x007BAC1C; the tree already calls it "
            "g_bfmeAptDefaultTeamName") in got.stderr


def test_ledger_bound_invented_name_without_g_prefix(repo):
    repo.stage(SRC, "// a\nextern void *g_bfmeFrameStackAtE1835C;\nint f() { return 0; }\n")
    got = repo.run("--staged")
    assert "invents g_bfmeFrameStackAtE1835C for 0x00A1835C; the tree already calls it spFrameStack" in got.stderr


def test_literals_and_invented_names_are_not_real(repo):
    # 0x007BB8D8 holds only a float literal and invented names; 0x0087A630 only the
    # vftable of an address-named class
    repo.stage(SRC, "// a\nextern float g_Va00BBB8D8;\nextern const void *const g_00C7A630[];\n"
                    "int f() { return 0; }\n")
    got = repo.run("--staged")
    assert got.returncode == 0 and got.stderr == ""


def test_vtables_count_as_real(repo):
    repo.stage(SRC, "// a\nextern const void *const g_00C1C780[];\nint f() { return 0; }\n")
    got = repo.run("--staged")
    assert ("invents g_00C1C780 for 0x0081C780; the tree already calls it "
            "Foo::`vftable', NS::Base::`vftable'\n") in got.stderr


def test_comments_strings_and_unknown_addresses_are_ignored(repo):
    repo.stage(SRC, "// a\n// g_00DFE758 is TheWritableGlobalData\n"
                    "const char *s = \"g_00DFE758\";\n"
                    "/* g_Va00E02EEC\n"
                    "   g_Va00E02EEC */\n"
                    " * g_00DFE758 inside a doc comment\n"
                    "extern int g_00ABCDEF;          // no ledger row there\n"
                    "int f() { return 0; }\n")
    got = repo.run("--staged")
    assert got.returncode == 0 and got.stderr == "", got.stderr


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
    for symbol in ("?g_Va00BBB8D8@@3MA", "?Foo@Bar@@2HA", "_c_name", "??_7Foo@@6B@"):
        assert inv.identifier(symbol) == data_ledger.identifier(symbol)


def test_pre_commit_calls_it_in_shadow():
    hook = (TOOLS.parent / ".githooks" / "pre-commit").read_text(encoding="utf-8")
    call = [line for line in hook.splitlines() if "tools/invented_names.py" in line and not line.startswith("#")]
    assert len(call) == 1 and "--staged --shadow" in call[0] and "|| echo" in call[0]
