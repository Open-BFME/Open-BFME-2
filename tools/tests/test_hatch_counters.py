"""hatch_counters.py: the escape-hatch register only shrinks by hand; growth needs a
tool allowance tied to the staged blob; a 2x jump in 24 h freezes allowances until a
Verifier-Change lift; the retail inventories are tool-owned."""
import collections
import os
import shutil
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
import hatch_counters as hc  # noqa: E402

DAY = 24 * 3600
T0 = 1_900_000_000          # fixture clock: commits are dated relative to this

LAYOUTS = {
    "bfme2": {"src": "Code/GameEngine/a.cpp", "src2": "Code/GameEngine/b.cpp", "rev": "reverse",
              "base": "reverse/hatch_baseline.tsv"},
    "bfme1": {"src": "game/GameEngine/a.cpp", "src2": "game/GameEngine/b.cpp", "rev": "targets/game/reverse",
              "base": "targets/game/reverse/hatch_baseline.tsv"},
}

SOURCE = """\
#include "x.h"
#pragma optimize("", off)
//#pragma optimize("s", on)
#pragma comment(linker, "/alternatename:?f@@YAXXZ=?g@@YAXXZ")
// ?Foo::bar present-unmatched
// class-gate: allow AsciiString caller view
extern int g_Va00A1B2C3;
__declspec(selectany) int s_x = 1;
void f() { __asm { __emit 0x90 } g_Va00A1B2C3 = 1; }
"""

STUB_INVENTORY = '''
def verify_staged(paths):
    import subprocess
    errs = []
    for p in paths:
        got = subprocess.run(["git", "show", ":" + p], capture_output=True, text=True).stdout
        if got != "generated\\n":
            errs.append(p + " edited by hand")
    return errs
'''


class Repo:
    def __init__(self, root, layout):
        self.root, self.lay = root, LAYOUTS[layout]

    def git(self, *args, when=T0, check=True):
        env = dict(os.environ, GIT_AUTHOR_NAME="t", GIT_COMMITTER_NAME="t", GIT_AUTHOR_EMAIL="",
                   GIT_COMMITTER_EMAIL="", GIT_AUTHOR_DATE="@%d +0000" % when,
                   GIT_COMMITTER_DATE="@%d +0000" % when)
        got = subprocess.run(["git", "-C", str(self.root), *args], capture_output=True, text=True, env=env)
        if check and got.returncode:
            raise AssertionError(got.stderr)
        return got.stdout

    def write(self, rel, text):
        p = self.root / rel
        p.parent.mkdir(parents=True, exist_ok=True)
        p.write_text(text, newline="\n")

    def read(self, rel):
        return (self.root / rel).read_text()

    def tool(self, *args, now=T0 + 60):
        env = dict(os.environ, HATCH_NOW=str(now))
        env.pop("HATCH_ROOT", None)
        return subprocess.run([sys.executable, str(self.root / "tools/hatch_counters.py"), *args],
                              cwd=self.root, capture_output=True, text=True, env=env)

    def commit(self, msg="x", when=T0, paths=None):
        self.git("add", "--", *(paths or ["."]))
        self.git("commit", "-q", "--allow-empty", "-m", msg, when=when)


@pytest.fixture(params=sorted(LAYOUTS))
def repo(tmp_path, request):
    r = Repo(tmp_path, request.param)
    r.git("init", "-q")
    (tmp_path / "tools").mkdir()
    shutil.copy(TOOLS / "hatch_counters.py", tmp_path / "tools")
    (tmp_path / "tools" / "retail_inventory.py").write_text(STUB_INVENTORY)
    r.write(r.lay["src"], SOURCE)
    r.write(r.lay["rev"] + "/symbols.csv", "name,address,notes\n?a@@3HA,0x00001000,pin\n")
    r.write(r.lay["rev"] + "/functions.csv",
            "name,export_rva,target_rva,target_size,source,status,notes\n"
            "?f@@YAXXZ,,0x00002000,5,%s,matched,gen-alias;object-symbol=?f@@YAXXZ\n" % r.lay["src"])
    r.git("add", ".")
    assert r.tool("--write-baseline").returncode == 0
    r.commit("init", when=T0 - 2 * DAY)
    return r


def staged(repo, now=T0 + 60):
    return repo.tool("--staged", now=now)


def test_scan_counts_each_hatch_and_skips_commented_code():
    got = hc.scan("Code/a.cpp", SOURCE)
    assert {k[0] for k in got} == {"pragma_optimize", "alternatename", "present_unmatched", "class_gate_allow",
                                   "address_global", "selectany", "emit"}
    assert got[("address_global", "Code/a.cpp", "g_Va00A1B2C3")] == 2
    assert got[("pragma_optimize", "Code/a.cpp", '"",off')] == 1        # the //#pragma line is not counted
    assert hc.scan("Code/d.asm", "  db 55h, 8Bh, 0ECh ; c\n  db 'ab', 0\n") == {("asm_bytes", "Code/d.asm", "*"): 6}


def test_baseline_parse_takes_lowest_duplicate_and_round_trips():
    text = "emit\tCode/a.cpp\t*\t5\nemit\tCode/a.cpp\t*\t3\npin\tr/s.csv\tx@1\t1\tallow=abc\n"
    counts, allow = hc.parse(text)
    assert counts[("emit", "Code/a.cpp", "*")] == 3 and allow == {("pin", "r/s.csv", "x@1"): "abc"}
    assert hc.parse(hc.render(counts, allow)) == (counts, allow)


# ---- negative controls: correct work passes

def test_unrelated_and_shrinking_commits_pass(repo):
    repo.write(repo.lay["src2"], "int clean() { return 0; }\n")
    repo.git("add", ".")
    assert staged(repo).returncode == 0
    repo.write(repo.lay["src"], SOURCE.replace("__emit 0x90 ", ""))
    repo.git("add", ".")
    got = staged(repo)
    assert got.returncode == 0 and "down to 0" in got.stderr          # slack is noted, not refused


def test_tightening_the_register_passes(repo):
    repo.write(repo.lay["src"], SOURCE.replace("__emit 0x90 ", ""))
    assert repo.tool("--update").returncode == 0
    assert "\temit\t" not in "\t" + repo.read(repo.lay["base"])
    repo.git("add", ".")
    assert staged(repo).returncode == 0


def test_move_between_files_via_update_passes(repo):
    repo.git("mv", repo.lay["src"], repo.lay["src2"])
    assert staged(repo).returncode == 1                                   # moved without the register
    assert repo.tool("--update").returncode == 0                          # totals unchanged: a move
    repo.git("add", ".")
    assert staged(repo).returncode == 0


# ---- positive controls: each of these passed before this gate existed

@pytest.mark.parametrize("line", [
    "void h() { __asm { __emit 0x90 } }\n",
    '#pragma comment(linker, "/alternatename:?h@@YAXXZ=?g@@YAXXZ")\n',
    "#pragma optimize(\"gsy\", on)\n",
    "__declspec(selectany) int s_y = 2;\n",
    "int g_Rva00ABCDEFThing;\n",
    "// ?Baz::qux present-unmatched\n",
    "// class-gate: allow Thing because\n",
])
def test_new_occurrence_is_refused(repo, line):
    repo.write(repo.lay["src"], SOURCE + line)
    repo.git("add", ".")
    got = staged(repo)
    assert got.returncode == 1 and "escape hatches grew" in got.stderr


def test_new_pin_and_alias_row_are_refused(repo):
    repo.write(repo.lay["rev"] + "/symbols.csv", repo.read(repo.lay["rev"] + "/symbols.csv") + "?b@@3HA,0x00001004,\n")
    repo.git("add", ".")
    assert "pin +1" in staged(repo).stderr
    repo.git("reset", "-q")
    repo.write(repo.lay["rev"] + "/functions.csv", repo.read(repo.lay["rev"] + "/functions.csv")
               + "?g@@YAXXZ,,0x00002000,5,x.cpp,matched,object-symbol=?f@@YAXXZ\n")
    repo.git("add", ".")
    assert "object_symbol +1" in staged(repo).stderr


def test_hand_raised_register_line_is_refused(repo):
    repo.write(repo.lay["src"], SOURCE + "void h() { __asm { __emit 0x90 } }\n")
    base = repo.read(repo.lay["base"]).replace("\t*\t1\n", "\t*\t2\n")
    repo.write(repo.lay["base"], base)
    repo.git("add", ".")
    got = staged(repo)
    assert got.returncode == 1 and "raised by hand" in got.stderr


def test_lowered_line_is_reverified(repo):
    base = repo.read(repo.lay["base"])
    repo.write(repo.lay["base"], "\n".join(l for l in base.splitlines() if not l.startswith("emit\t")) + "\n")
    repo.git("add", ".")
    got = staged(repo)
    assert got.returncode == 1 and "emit +1" in got.stderr                # the occurrence is still there


def test_tool_allowance_admits_growth_bound_to_the_staged_blob(repo):
    repo.write(repo.lay["src"], SOURCE + "void h() { __asm { __emit 0x90 } }\n")
    assert repo.tool("--update").returncode != 0                          # growth needs --allow
    assert repo.tool("--allow", repo.lay["src"], "--reason", "x87 shape the compiler cannot emit").returncode == 0
    repo.git("add", ".")
    assert staged(repo).returncode == 0
    repo.write(repo.lay["src"], SOURCE + "void h() { __asm { __emit 0x90 } }\nint more;\n")
    repo.git("add", repo.lay["src"])                                      # content changed after --allow
    got = staged(repo)
    assert got.returncode == 1 and "raised by hand" in got.stderr


def test_inventory_files_are_tool_owned(repo):
    inv = repo.lay["rev"] + "/retail_inventory/"
    repo.write(inv + "fold_list.csv", "generated\n")
    repo.git("add", ".")
    assert staged(repo).returncode == 0
    repo.write(inv + "fold_list.csv", "generated\nforged row\n")
    repo.git("add", ".")
    got = staged(repo)
    assert got.returncode == 1 and "edited by hand" in got.stderr


# ---- anomaly freeze

def _allow_emits(repo, n, when, msg="allow", tool_now=None):
    repo.write(repo.lay["src"], repo.read(repo.lay["src"]) + "void e%d() { __asm { %s } }\n"
               % (when, " ".join(["__emit 0x90"] * n)))
    got = repo.tool("--allow", repo.lay["src"], "--reason", "fixture growth step", now=tool_now or when + 1)
    if got.returncode == 0 and tool_now is None:
        repo.commit(msg, when=when)
    return got


def test_freeze_after_doubling_and_lift(repo):
    assert _allow_emits(repo, 9, T0 - 30 * 3600).returncode == 0       # emit total 10, 30 h ago
    assert _allow_emits(repo, 8, T0 - 3600).returncode == 0            # 18 <= 2 x 10: still fine
    got = _allow_emits(repo, 5, T0)                                     # 23 > 20: frozen
    assert got.returncode != 0 and "frozen" in got.stderr
    # an allowance written before the jump (no reference yet) is still refused by the gate now
    assert repo.tool("--allow", repo.lay["src"], "--reason", "fixture growth step", now=T0 - 60 * 3600).returncode == 0
    repo.git("add", ".")
    assert "FROZEN" in staged(repo, now=T0 + 60).stderr
    repo.git("reset", "-q", "--hard", "HEAD")
    repo.commit("Lift\n\nVerifier-Change: hatch-freeze-lift emit vetted the x87 batch", when=T0 + 10)
    assert _allow_emits(repo, 5, T0 + 20).returncode == 0              # reference is now the lift (18)
    assert _allow_emits(repo, 20, T0 + 30).returncode != 0             # 43 > 2 x 18: frozen again


def test_no_history_means_no_freeze(repo):
    assert hc.frozen("emit", 100, {}) is False
    assert hc.frozen("emit", 4, {"emit": 0}) is False                  # below FREEZE_MIN
    assert hc.frozen("emit", 21, {"emit": 10}) is True


def test_register_cannot_be_deleted_or_introduced_wrong(repo):
    repo.git("rm", "-q", "--cached", repo.lay["base"])
    got = staged(repo)
    assert got.returncode == 1 and "deleted" in got.stderr
    repo.git("reset", "-q", "--hard", "HEAD")
    first = Repo(repo.root / "intro", "bfme2")                         # a tree that introduces the register
    (repo.root / "intro").mkdir()
    first.git("init", "-q")
    (first.root / "tools").mkdir(parents=True)
    shutil.copy(TOOLS / "hatch_counters.py", first.root / "tools")
    first.write("Code/a.cpp", SOURCE)
    first.write("reverse/hatch_baseline.tsv", "emit\tCode/a.cpp\t*\t1\n")   # understates the tree
    first.git("add", ".")
    got = staged(first)
    assert got.returncode == 1 and "does not match the tree" in got.stderr
    assert first.tool("--write-baseline").returncode == 1                # refuses: a register exists
    (first.root / "reverse/hatch_baseline.tsv").unlink()
    assert first.tool("--write-baseline").returncode == 0
    first.git("add", ".")
    assert staged(first).returncode == 0


def _set_mode(repo, mode):
    base = repo.read(repo.lay["base"])
    repo.write(repo.lay["base"], base.replace("# mode: enforce", "# mode: " + mode).replace(
        "# mode: shadow", "# mode: " + mode))


def test_shadow_mode_reports_growth_without_refusing(repo):
    base = repo.read(repo.lay["base"])
    repo.write(repo.lay["base"], base.replace("# mode: enforce", "# mode: shadow"))
    repo.git("add", ".")
    assert "may not go back" in staged(repo).stderr                    # the fixture register says enforce
    _shadow_register(repo)
    repo.write(repo.lay["src"], SOURCE + "void h() { __asm { __emit 0x90 } }\n")
    repo.git("add", ".")
    got = staged(repo)
    assert got.returncode == 0 and "SHADOW (not enforced): emit +1" in got.stderr


def test_mode_may_go_shadow_to_enforce_but_not_back(repo):
    assert "# mode: enforce" in repo.read(repo.lay["base"])
    _set_mode(repo, "shadow")
    repo.git("add", ".")
    got = staged(repo)
    assert got.returncode == 1 and "may not go back to shadow" in got.stderr
    repo.git("reset", "-q", "--hard", "HEAD")
    _shadow_register(repo)
    _set_mode(repo, "enforce")
    repo.git("add", ".")
    assert staged(repo).returncode == 0


def test_a_mode_line_dropped_then_shadow_is_refused_at_each_step(repo):
    # Commit 1 deletes the line (read as enforce); commit 2 claims shadow with a hand pin.
    base = repo.read(repo.lay["base"])
    pins = repo.lay["rev"] + "/symbols.csv"
    repo.write(repo.lay["base"], base.replace("# mode: enforce\n", ""))
    repo.git("add", ".")
    got = staged(repo)
    assert got.returncode == 1 and "line may not be removed" in got.stderr
    repo.commit("line dropped (the hook skipped)", when=T0 - 60)
    repo.write(repo.lay["base"], base.replace("# mode: enforce", "# mode: shadow"))
    repo.write(pins, repo.read(pins) + "?typed@@3HA,0x00003000,by hand\n")
    repo.git("add", ".")
    got = staged(repo)                                     # a parent with no line is enforced
    assert got.returncode == 1 and "may not go back to shadow" in got.stderr
    assert "pin +1 in %s: 0x00003000" % pins in got.stderr and "REFUSED" in got.stderr
    # the refused downgrade is judged as enforced, and says so: no shadow banner above it
    assert "SHADOW (not enforced)" not in got.stderr and "NOT refused" not in got.stderr


def test_a_shadow_register_may_not_be_deleted_either(repo):
    _shadow_register(repo)
    repo.git("rm", "-q", "--cached", repo.lay["base"])
    got = staged(repo)
    assert got.returncode == 1 and "deleted" in got.stderr


# ---- scoped tool allowance (admit): what pin/alias writers call after their own checks

def admit(repo, path, *args):
    return repo.tool("--admit", path, "--reason", "checked by the writing tool", *args)


def test_admit_admits_only_the_named_tokens(repo):
    pins = repo.lay["rev"] + "/symbols.csv"
    repo.write(pins, repo.read(pins) + "?b@@3HA,0x00001004,tool\n?c@@3HA,0x00001008,hand\n")
    got = admit(repo, pins, "--tokens", "0x00001004")
    assert got.returncode == 1 and "0x00001008" in got.stderr               # the hand pin is not admitted
    repo.git("add", ".")
    got = staged(repo)
    assert got.returncode == 1 and "pin +1" in got.stderr and "0x00001008" in got.stderr
    assert "0x00001004" not in got.stderr                                     # the tool pin passes
    repo.write(pins, repo.read(pins).replace("?c@@3HA,0x00001008,hand\n", ""))
    repo.git("add", ".")
    got = staged(repo)
    assert got.returncode == 1 and "raised by hand" in got.stderr              # blob moved after admit
    assert admit(repo, pins, "--tokens", "0x00001004").returncode == 0
    repo.git("add", ".")
    assert staged(repo).returncode == 0


def test_admit_restamps_an_earlier_tool_allowance_in_the_same_file(repo):
    pins = repo.lay["rev"] + "/symbols.csv"
    sys.path.insert(0, str(repo.root / "tools"))
    repo.write(pins, repo.read(pins) + "?b@@3HA,0x00001004,tool\n")
    assert admit(repo, pins, "--tokens", "0x00001004").returncode == 0
    before = repo.git("hash-object", pins).strip()
    repo.write(pins, repo.read(pins) + "?d@@3HA,0x0000100C,tool\n")
    env = dict(os.environ, HATCH_ROOT=str(repo.root), HATCH_NOW=str(T0 + 60))
    code = ("import sys; sys.path.insert(0, 'tools'); import hatch_counters as h; "
            "r = h.admit(%r, 'second tool write', {'0x0000100C'}, before=%r); "
            "sys.exit(1 if r['refused'] else 0)" % (pins, before))
    assert subprocess.run([sys.executable, "-c", code], cwd=repo.root, env=env).returncode == 0
    repo.git("add", ".")
    assert staged(repo).returncode == 0                                       # both pins carry the new blob


def _pin_lines(repo, pins):
    """{address: (count, stamp)} of the register's pin lines for PINS."""
    out = {}
    for line in repo.read(repo.lay["base"]).splitlines():
        cells = line.split("\t")
        if len(cells) >= 4 and cells[0] == "pin" and cells[1] == pins:
            out[cells[2]] = (int(cells[3]), cells[4][6:] if len(cells) > 4 else None)
    return out


def test_admissions_accumulate_across_an_edit_between_two_admits(repo):
    # The edit between the calls changed symbols.csv's blob, and the second admit reset the
    # first's line to HEAD's count: 319 pin lines went in unadmitted across four commits.
    pins = repo.lay["rev"] + "/symbols.csv"
    repo.write(pins, repo.read(pins) + "?b@@3HA,0x00001004,tool\n")
    assert admit(repo, pins, "--tokens", "0x00001004").returncode == 0
    repo.write(pins, repo.read(pins).replace(",pin\n", ",pin; renoted by another tool\n"))
    repo.write(pins, repo.read(pins) + "?d@@3HA,0x0000100C,tool\n")
    got = admit(repo, pins, "--tokens", "0x0000100C")
    assert got.returncode == 0, got.stderr
    blob = repo.git("hash-object", pins).strip()
    lines = _pin_lines(repo, pins)
    assert lines["0x00001004"] == (1, blob) and lines["0x0000100C"] == (1, blob)
    repo.git("add", ".")
    got = staged(repo)
    assert got.returncode == 0 and "pin +" not in got.stderr, got.stderr


def _tool_stamp(repo, pins, address):
    return _pin_lines(repo, pins)[address][1]


@pytest.mark.parametrize("stamp", ["typed-by-hand", "0" * 40, "neighbour"])
def test_a_hand_pin_between_two_admits_is_still_reported(repo, stamp):
    pins = repo.lay["rev"] + "/symbols.csv"
    repo.write(pins, repo.read(pins) + "?b@@3HA,0x00001004,tool\n")
    assert admit(repo, pins, "--tokens", "0x00001004").returncode == 0
    if stamp == "neighbour":                     # a real tool stamp, copied from the line above it
        stamp = _tool_stamp(repo, pins, "0x00001004")
    # by hand: a new address, and a second name on the address the first call admitted ...
    repo.write(pins, repo.read(pins) + "?c@@3HA,0x00001008,hand\n?e@@3HA,0x00001004,hand\n")
    # ... and register lines typed for them: one added, one raised to the file's count
    repo.write(repo.lay["base"], repo.read(repo.lay["base"]).replace(
        "pin\t%s\t0x00001004\t1\t" % pins, "pin\t%s\t0x00001004\t2\t" % pins)
        + "pin\t%s\t0x00001008\t1\tallow=%s\n" % (pins, stamp))
    repo.write(pins, repo.read(pins) + "?d@@3HA,0x0000100C,tool\n")
    got = admit(repo, pins, "--tokens", "0x0000100C")
    assert got.returncode == 1 and "0x00001008" in got.stderr and "0x00001004" in got.stderr
    assert "kept pin in %s: 0x00001004 at 1" % pins in got.stderr     # the admission, said so
    assert "NOT KEPT pin in %s: 0x00001008: register line 1 -> 0" % pins in got.stderr
    assert "NOT KEPT pin in %s: 0x00001004: register line 2 -> 1" % pins in got.stderr
    lines = _pin_lines(repo, pins)
    assert lines["0x00001004"][0] == 1 and "0x00001008" not in lines  # what the first call saw
    repo.git("add", ".")
    got = staged(repo)
    assert got.returncode == 1
    assert "pin +1 in %s: 0x00001008 (register grants 0)" % pins in got.stderr
    assert "pin +1 in %s: 0x00001004 (register grants 1)" % pins in got.stderr
    assert "0x0000100C" not in got.stderr


def test_a_pin_renamed_at_an_admitted_address_is_reported(repo):
    # The register keys a pin by address. Renaming the admitted pin by hand keeps the count, so
    # a count alone would carry the grant over to a name nothing checked.
    pins = repo.lay["rev"] + "/symbols.csv"
    repo.write(pins, repo.read(pins) + "?one@@3HA,0x00001004,tool\n")
    assert admit(repo, pins, "--tokens", "0x00001004").returncode == 0
    repo.write(pins, repo.read(pins).replace("?one@@3HA,0x00001004", "?unchecked@@3HA,0x00001004"))
    repo.write(pins, repo.read(pins) + "?two@@3HA,0x0000100C,tool\n")
    got = admit(repo, pins, "--tokens", "0x0000100C")
    assert got.returncode == 1 and "NOT KEPT pin in %s: 0x00001004" % pins in got.stderr
    repo.git("add", ".")
    got = staged(repo)
    assert got.returncode == 1 and "pin +1 in %s: 0x00001004 (register grants 0)" % pins in got.stderr
    repo.write(pins, repo.read(pins).replace("?unchecked@@3HA,0x00001004", "?one@@3HA,0x00001004"))
    assert admit(repo, pins, "--tokens", "0x00001004").returncode == 0    # re-admitted by its tool
    repo.git("add", ".")
    assert staged(repo).returncode == 0


def test_a_typed_line_for_a_hand_pin_the_admitted_blob_carries_is_refused(repo):
    # The hand pin is in the very blob the first admission stamped, and the typed line copies
    # that stamp: only a record of what the admission granted tells the two lines apart.
    pins = repo.lay["rev"] + "/symbols.csv"
    repo.write(pins, repo.read(pins) + "?c@@3HA,0x00001008,hand\n?b@@3HA,0x00001004,tool\n")
    assert admit(repo, pins, "--tokens", "0x00001004").returncode == 1        # 0x00001008 refused
    stamp = _tool_stamp(repo, pins, "0x00001004")
    repo.write(repo.lay["base"], repo.read(repo.lay["base"]) + "pin\t%s\t0x00001008\t1\tallow=%s\n" % (pins, stamp))
    repo.write(pins, repo.read(pins).replace(",tool\n", ",tool; renoted\n") + "?d@@3HA,0x0000100C,tool\n")
    got = admit(repo, pins, "--tokens", "0x0000100C")
    assert "kept pin in %s: 0x00001004" % pins in got.stderr and "NOT KEPT pin in %s: 0x00001008" % pins in got.stderr
    repo.git("add", ".")
    got = staged(repo)
    assert got.returncode == 1 and "pin +1 in %s: 0x00001008 (register grants 0)" % pins in got.stderr
    assert "0x00001004" not in got.stderr and "0x0000100C" not in got.stderr


def test_the_admission_record_is_scoped_to_head(repo):
    pins = repo.lay["rev"] + "/symbols.csv"
    repo.write(pins, repo.read(pins) + "?b@@3HA,0x00001004,tool\n")
    assert admit(repo, pins, "--tokens", "0x00001004").returncode == 0
    repo.write(repo.lay["src2"], "int unrelated;\n")
    repo.commit("another working change", paths=[repo.lay["src2"]])    # HEAD moves under it
    repo.write(pins, repo.read(pins).replace(",pin\n", ",pin; renoted\n") + "?d@@3HA,0x0000100C,tool\n")
    got = admit(repo, pins, "--tokens", "0x0000100C")
    assert "NOT KEPT pin in %s: 0x00001004: register line 1 -> 0" % pins in got.stderr


def test_no_admission_exceeds_what_the_file_carries(repo):
    pins = repo.lay["rev"] + "/symbols.csv"
    repo.write(pins, repo.read(pins) + "?b@@3HA,0x00001004,tool\n?b2@@3HA,0x00001004,tool\n"
               "?f@@3HA,0x00001010,tool\n")
    assert admit(repo, pins, "--tokens", "0x00001004", "0x00001010").returncode == 0
    assert _pin_lines(repo, pins)["0x00001004"][0] == 2
    # pins retired between the calls: the earlier grants follow the file down, never past it
    repo.write(pins, repo.read(pins).replace("?b2@@3HA,0x00001004,tool\n", "")
               .replace("?f@@3HA,0x00001010,tool\n", ""))
    repo.write(pins, repo.read(pins) + "?d@@3HA,0x0000100C,tool\n")
    assert admit(repo, pins, "--tokens", "0x0000100C").returncode == 0
    lines = _pin_lines(repo, pins)
    assert lines["0x00001004"][0] == 1 and "0x00001010" not in lines and lines["0x0000100C"][0] == 1
    carried = collections.Counter(line.split(",")[1] for line in repo.read(pins).splitlines()[1:])
    assert all(n <= carried[address] for address, (n, _) in lines.items())
    repo.git("add", ".")
    assert staged(repo).returncode == 0


def test_shadow_banner_frames_what_the_commit_adds_and_tags_what_head_carries(repo):
    _shadow_register(repo)
    _drift(repo)                                                   # HEAD carries an unadmitted 0x00001004
    pins = repo.lay["rev"] + "/symbols.csv"
    repo.write(pins, repo.read(pins) + "?e@@3HA,0x00001010,hand\n")
    repo.git("add", pins)
    note = repo.root / "hatch-note.txt"
    got = repo.tool("--staged", "--note-file", str(note))
    assert got.returncode == 0                                     # shadow still never refuses
    banner = got.stderr[got.stderr.index("THIS COMMIT ADDS"):]
    assert "THIS COMMIT ADDS UNADMITTED ESCAPE HATCHES (pin +1)" in banner
    assert "SHADOW (not enforced): pin +1 in %s: 0x00001010 (register grants 0)\n" % pins in banner
    assert "0x00001004" not in banner
    assert "0x00001004 (register grants 0) [already in HEAD]" in got.stderr
    assert "0x00001010" in note.read_text() and "0x00001004" not in note.read_text()
    note.unlink()
    repo.git("reset", "-q", "--hard", "HEAD")
    repo.write(pins, repo.read(pins).replace(",pin\n", ",pin; renoted\n"))
    repo.git("add", pins)                                          # touches the file, adds nothing
    got = repo.tool("--staged", "--note-file", str(note))
    assert got.returncode == 0 and "[already in HEAD]" in got.stderr
    assert "THIS COMMIT ADDS" not in got.stderr and not note.exists()


def test_admit_shrinks_and_leaves_other_files_alone(repo):
    repo.write(repo.lay["src"], SOURCE.replace("__emit 0x90 ", ""))
    other = repo.read(repo.lay["base"])
    assert admit(repo, repo.lay["src"]).returncode == 0
    after = repo.read(repo.lay["base"])
    assert "\temit\t" not in "\t" + after
    assert [l for l in other.splitlines() if repo.lay["src"] not in l] == \
           [l for l in after.splitlines() if repo.lay["src"] not in l]
    repo.git("add", ".")
    assert staged(repo).returncode == 0


def test_admit_respects_the_freeze(repo):
    repo.write(repo.lay["src"], SOURCE + "void h() { __asm { __emit 0x90 } }\n" * 12)
    got = admit(repo, repo.lay["src"])
    assert got.returncode != 0 and "frozen" in got.stderr


# ---- reseed (rule 7): a drifted shadow register is rewritten from the tree, once

def _shadow_register(repo):
    """The fixture register as a committed `# mode: shadow` one (committed without the gate,
    which refuses enforce -> shadow: the register as it stood before the flip)."""
    repo.write(repo.lay["base"], repo.read(repo.lay["base"]).replace("# mode: enforce", "# mode: shadow"))
    repo.commit("shadow", when=T0 - DAY + 1)


def _drift(repo):
    """What master did in shadow: hatches grew and shrank in commits the register never saw."""
    repo.write(repo.lay["src"], SOURCE.replace("__emit 0x90 ", "") + "#pragma optimize(\"gsy\", on)\n")
    repo.write(repo.lay["src2"], "void h() { __asm { __emit 0x90 __emit 0x90 } }\n")
    pins = repo.lay["rev"] + "/symbols.csv"
    repo.write(pins, repo.read(pins) + "?b@@3HA,0x00001004,\n")
    repo.commit("drift", when=T0 - 3600)


def test_reseed_makes_a_drifted_shadow_register_match_and_still_reports_new_growth(repo):
    _shadow_register(repo)
    _drift(repo)
    repo.write(repo.lay["src"], repo.read(repo.lay["src"]) + "int clean;\n")
    repo.git("add", repo.lay["src"])                               # the drift is reported on any touch
    assert "SHADOW (not enforced): pragma_optimize +1" in staged(repo).stderr
    got = repo.tool("--reseed")
    assert got.returncode == 0 and "reseeded" in got.stdout
    text = repo.read(repo.lay["base"])
    assert "# mode: shadow" in text and "allow=" not in text
    assert "emit\t%s\t*\t2\n" % repo.lay["src2"] in text and "\temit\t%s\t" % repo.lay["src"] not in text
    repo.git("add", ".")
    got = staged(repo)                                             # the reseed commit itself is clean
    assert got.returncode == 0 and "SHADOW" not in got.stderr and "reseeded from the staged tree" in got.stderr
    repo.commit("Reseed\n\nVerifier-Change: hatch-reseed fixture drift", when=T0)
    assert repo.tool("--report").stdout.count("\n") == len(hc.HATCHES) + 1
    for line in repo.tool("--report").stdout.splitlines()[1:]:     # register == tree for every hatch
        _, reg, tree = line.split()
        assert reg == tree
    repo.write(repo.lay["src2"], repo.read(repo.lay["src2"]) + "void k() { __asm { __emit 0x90 } }\n")
    repo.git("add", ".")
    got = staged(repo)                                             # a hatch added after the reseed: reported
    assert got.returncode == 0 and "SHADOW (not enforced): emit +1" in got.stderr
    _set_mode(repo, "enforce")                                     # and refused once enforced
    repo.git("add", ".")
    got = staged(repo)
    assert got.returncode == 1 and "emit +1" in got.stderr and "escape hatches grew" in got.stderr


def test_reseed_staged_with_extra_growth_is_judged_line_by_line(repo):
    _shadow_register(repo)
    _drift(repo)
    assert repo.tool("--reseed").returncode == 0
    repo.write(repo.lay["src2"], repo.read(repo.lay["src2"]) + "void k() { __asm { __emit 0x90 } }\n")
    repo.git("add", ".")                                           # register no longer equals the staged tree
    got = staged(repo)
    assert "reseeded from the staged tree" not in got.stderr and "SHADOW (not enforced): emit +1" in got.stderr
    assert "raised by hand" in got.stderr                          # the reseed's raised lines are named too


def test_reseed_is_refused_for_an_enforced_or_missing_register(repo):
    _drift(repo)
    before = repo.read(repo.lay["base"])
    got = repo.tool("--reseed")
    assert got.returncode != 0 and "never reseeded" in got.stderr
    assert repo.read(repo.lay["base"]) == before
    (repo.root / repo.lay["base"]).unlink()
    got = repo.tool("--reseed")
    assert got.returncode != 0 and "--write-baseline" in got.stderr


# ---- enforcement (the flip): what an enforced register refuses, allows and credits

ALT = '#pragma comment(linker, "/alternatename:?%s@@YAXXZ=?g@@YAXXZ")\n'


def test_enforce_refuses_a_new_alternatename_in_a_file_at_its_limit(repo):
    assert "# mode: enforce" in repo.read(repo.lay["base"])           # the fixture register is enforced
    assert "alternatename\t%s\t?f@@YAXXZ\t1\n" % repo.lay["src"] in repo.read(repo.lay["base"])
    repo.write(repo.lay["src"], SOURCE + ALT % "h")
    repo.git("add", ".")
    got = staged(repo)
    assert got.returncode == 1 and "REFUSED" in got.stderr and "escape hatches grew" in got.stderr
    assert "alternatename +1 in %s: ?h@@YAXXZ (register grants 0)" % repo.lay["src"] in got.stderr
    assert "tools/name_globals.py" in got.stderr and "--alternatenames" in got.stderr   # what to do
    assert "pin_admission.py --add" not in got.stderr                  # only the hatches it names
    # an admission typed into the register by hand is refused too
    repo.write(repo.lay["base"], repo.read(repo.lay["base"]).replace(
        "alternatename\t%s\t?f@@YAXXZ\t1\n" % repo.lay["src"],
        "alternatename\t%s\t?f@@YAXXZ\t1\nalternatename\t%s\t?h@@YAXXZ\t1\n" % (repo.lay["src"], repo.lay["src"])))
    repo.git("add", ".")
    got = staged(repo)
    assert got.returncode == 1 and "raised by hand" in got.stderr and "git checkout HEAD --" in got.stderr


def test_enforce_allows_and_credits_a_decrease(repo):
    repo.write(repo.lay["src"], SOURCE.replace(ALT % "f", ""))
    repo.git("add", ".")
    got = staged(repo)                                                 # register untouched: slack, noted
    assert got.returncode == 0 and "is down to 0 (register says 1)" in got.stderr
    assert repo.tool("--update").returncode == 0                       # the register follows it down
    repo.git("add", ".")
    got = staged(repo)
    assert got.returncode == 0 and "credited: alternatename register total 1 -> 0 (-1)" in got.stderr
    repo.commit("drop the alias\n\nVerifier-Change: hatch register lowered by --update", when=T0)
    repo.write(repo.lay["src"], repo.read(repo.lay["src"]) + ALT % "f")
    repo.git("add", ".")
    assert staged(repo).returncode == 1                                # and it does not come back


def _code_identity(repo, mode):
    """Commit a code-identity register in MODE: rule 8 reads it at HEAD and in the index."""
    repo.write(repo.lay["rev"] + "/code_identity_baseline.tsv", "# Wrong code bindings\n# mode: %s\n" % mode)
    repo.commit("code identity " + mode, when=T0 - DAY)


def test_a_respelled_alias_is_judged_per_token_until_code_identity_is_enforced(repo):
    # Nothing judges the added /alternatename while code_identity_gate is in shadow, so a real
    # alias traded for an arbitrary one at the same count is a new hatch, not a respelling.
    ci = repo.lay["rev"] + "/code_identity_baseline.tsv"
    swap = SOURCE.replace("?f@@YAXXZ=?g@@YAXXZ", "?anything@@YAXXZ=?whatever@@YAXXZ")
    for step in ("no register", "shadow", "flip staged only"):
        if step == "shadow":
            _code_identity(repo, "shadow")
        if step == "flip staged only":                             # HEAD's is still shadow
            repo.write(ci, repo.read(ci).replace("shadow", "enforce"))
        repo.write(repo.lay["src"], swap)
        repo.git("add", ".")
        got = staged(repo)
        assert got.returncode == 1, step
        assert "alternatename +1 in %s: ?anything@@YAXXZ (register grants 0)" % repo.lay["src"] in got.stderr
        repo.git("reset", "-q", "--hard", "HEAD")
    _code_identity(repo, "enforce")
    repo.write(repo.lay["src"], swap)
    repo.git("add", ".")
    got = staged(repo)
    assert got.returncode == 0 and "respelled (?anything@@YAXXZ)" in got.stderr


def test_a_move_and_a_respelling_cannot_spend_one_occurrence(repo):
    # A:f, B:y becomes A:y, B:f+y: each line change alone is a move or a respelling, but the
    # alternatename total goes 2 -> 3.
    a, b = repo.lay["src"], repo.lay["src2"]
    repo.write(b, ALT % "y")
    assert repo.tool("--allow", b, "--reason", "fixture: a second unit's alias").returncode == 0
    repo.commit("B:y", when=T0 - DAY)
    _code_identity(repo, "enforce")                                # respellings are per file
    repo.write(a, SOURCE.replace("?f@@YAXXZ=", "?y@@YAXXZ="))
    repo.write(b, ALT % "y" + ALT % "f")
    assert repo.tool("--update").returncode != 0                   # growth needs --allow
    repo.write(repo.lay["base"], repo.read(repo.lay["base"]).replace(
        "alternatename\t%s\t?f@@YAXXZ\t1\n" % a,
        "alternatename\t%s\t?y@@YAXXZ\t1\nalternatename\t%s\t?f@@YAXXZ\t1\n" % (a, b)))
    repo.git("add", ".")
    got = staged(repo)
    assert got.returncode == 1 and "register line raised by hand: alternatename" in got.stderr


def test_register_growth_matches_each_old_occurrence_once(monkeypatch):
    k = lambda path, token, hatch="alternatename": (hatch, path, token)       # noqa: E731
    monkeypatch.setitem(hc.STATE, "respellable", hc.RESPELLABLE)
    assert hc.register_growth({k("A", "x"): 1}, {k("B", "x"): 1}) == []                    # a move
    assert hc.register_growth({k("A", "x"): 1}, {k("A", "y"): 1}) == []                    # a respelling
    old = {k("A", "x"): 1, k("B", "y"): 1}
    assert hc.register_growth(old, {k("A", "y"): 1, k("B", "x"): 1, k("B", "y"): 1}) != []
    # both at once, each occurrence spent once: B:x moves to A:x, A:x respells to A:y
    assert hc.register_growth({k("B", "x"): 1, k("A", "x"): 1}, {k("A", "x"): 1, k("A", "y"): 1}) == []
    # an admitted key explains its own raise (2 -> 3 with one admission is no growth) ...
    assert hc.register_growth(old, {k("A", "y"): 1, k("B", "x"): 1, k("B", "y"): 1}, admitted={k("A", "y")}) == []
    # ... and what is left over lands on a key nothing admitted
    left = hc.register_growth({k("A", "x"): 1}, {k("A", "y"): 1, k("A", "z"): 1, k("A", "w"): 1},
                              admitted={k("A", "y")})
    assert len(left) == 1 and k("A", "y") not in left
    big = {k("A", "*", "asm_bytes"): 5000}                                           # moved in bulk
    assert hc.register_growth(big, {k("B", "*", "asm_bytes"): 5000}) == []
    assert hc.register_growth(big, {k("B", "*", "asm_bytes"): 5001}) == [k("B", "*", "asm_bytes")]
    monkeypatch.setitem(hc.STATE, "respellable", frozenset())                      # code identity in shadow
    assert hc.register_growth({k("A", "x"): 1}, {k("A", "y"): 1}) == [k("A", "y")]


LEDGER = ("address,size,section,kind,name,source,status,names,defs,refs\n"
          "0x00A09FA4,4,.data,global,?g_Va0130A588@@3PAVT@@A,Code/x.cpp,provisional,"
          "?g_Va00E09FA4@@3HA;?g_Va0130A588@@3PAVT@@A,1,2\n")


def test_register_growth_rebinds_a_ledger_alias_to_its_owner_only(monkeypatch):
    # rule 10: the data ledger's alias spelling at an address respells to the owner, one for one,
    # in the same file, and never the other way round
    k = lambda path, token: ("address_global", path, token)                # noqa: E731
    monkeypatch.setitem(hc.STATE, "ledger_respell", {"g_Va0130A588": frozenset({"g_Va00E09FA4"})})
    assert hc.register_growth({k("A", "g_Va00E09FA4"): 3, k("A", "g_Va0130A588"): 1},
                              {k("A", "g_Va0130A588"): 2}) == []
    assert hc.register_growth({k("A", "g_Va00E09FA4"): 1}, {k("A", "g_Va0130A588"): 2}) == [k("A", "g_Va0130A588")]
    assert hc.register_growth({k("B", "g_Va00E09FA4"): 1}, {k("A", "g_Va0130A588"): 1}) != []     # other file
    assert hc.register_growth({k("A", "g_Va0130A588"): 1}, {k("A", "g_Va00E09FA4"): 1}) != []     # owner -> alias
    assert hc.register_growth({k("A", "g_Va00E09FA4"): 1}, {k("A", "g_Va00DEAD00"): 1}) != []     # not its owner


def test_a_ledger_alias_rebound_to_its_owner_passes_and_nothing_else_does(repo):
    src, ledger = repo.lay["src"], repo.lay["rev"] + "/data_ledger.csv"
    alias = SOURCE.replace("g_Va00A1B2C3", "g_Va00E09FA4")
    repo.write(src, alias)
    assert repo.tool("--allow", src, "--reason", "fixture: the alias spelling").returncode == 0
    repo.commit("alias spelling", when=T0 - DAY)
    owner = alias.replace("extern int g_Va00E09FA4;", "class T; extern T *g_Va0130A588;").replace(
        "g_Va00E09FA4 = 1;", "g_Va0130A588 = 0;")
    repo.write(src, owner)
    assert repo.tool("--update").returncode != 0                       # no ledger at HEAD: new tokens
    repo.write(ledger, LEDGER)
    assert repo.tool("--update").returncode != 0                       # a staged-only ledger grants nothing
    repo.git("reset", "-q", "--hard", "HEAD")
    repo.write(ledger, LEDGER)
    repo.commit("ledger", when=T0 - DAY)
    repo.write(src, owner)
    assert repo.tool("--update").returncode == 0
    assert "address_global\t%s\tg_Va0130A588\t2" % src in repo.read(repo.lay["base"])
    repo.git("add", ".")
    got = staged(repo)
    assert got.returncode == 0 and "raised by hand" not in got.stderr, got.stderr
    repo.write(src, owner + "int g_Va0130A588b;\n")                 # a further address-named global is new
    repo.git("add", ".")
    assert "address_global +1" in staged(repo).stderr


def test_enforce_takes_a_respelled_alias_at_the_same_count(repo):
    # a rename respells the token; the file's count of the hatch is what may not rise
    _code_identity(repo, "enforce")
    repo.write(repo.lay["src"], SOURCE.replace("?f@@YAXXZ=", "?f2@@YAXXZ="))
    repo.git("add", ".")
    got = staged(repo)
    assert got.returncode == 0 and "respelled (?f2@@YAXXZ)" in got.stderr
    assert repo.tool("--update").returncode == 0                       # --update writes the respelling
    repo.git("add", ".")
    got = staged(repo)
    assert got.returncode == 0 and "raised by hand" not in got.stderr
    repo.write(repo.lay["src"], repo.read(repo.lay["src"]) + ALT % "h")   # a second alias still is new
    repo.git("add", ".")
    assert "alternatename +1" in staged(repo).stderr
    # a pin is keyed by address: trading one address for another is not a respelling
    repo.git("reset", "-q", "--hard", "HEAD")
    pins = repo.lay["rev"] + "/symbols.csv"
    repo.write(pins, repo.read(pins).replace("0x00001000", "0x00001004"))
    repo.git("add", ".")
    got = staged(repo)
    assert got.returncode == 1 and "pin +1 in %s: 0x00001004" % pins in got.stderr


EMIT = "void h%d() { __asm { __emit 0x90 } }\n"


def test_enforce_reports_inherited_drift_and_refuses_only_what_the_commit_adds(repo):
    # HEAD carries an __emit the register never granted (a commit that skipped the hook)
    repo.write(repo.lay["src"], SOURCE + EMIT % 1)
    repo.commit("unverified", when=T0 - 60)
    repo.write(repo.lay["src"], repo.read(repo.lay["src"]) + "int clean;\n")
    repo.git("add", ".")
    got = staged(repo)
    assert got.returncode == 0, got.stderr
    assert "inherited, not refused: emit +1 in %s" % repo.lay["src"] in got.stderr
    repo.write(repo.lay["src"], repo.read(repo.lay["src"]) + EMIT % 2)
    repo.git("add", ".")
    got = staged(repo)
    assert got.returncode == 1
    assert "emit +1 in %s: * (register grants 1; HEAD already carried 1 more)" % repo.lay["src"] in got.stderr
    # lowering a line below what the file carries is still refused, drift or not
    repo.git("reset", "-q", "--hard", "HEAD")
    repo.write(repo.lay["base"], repo.read(repo.lay["base"]).replace("emit\t%s\t*\t1\n" % repo.lay["src"], ""))
    repo.git("add", ".")
    got = staged(repo)                                                 # the line it lowered is refused
    assert got.returncode == 1 and "(register grants 0; HEAD already carried 1 more)" in got.stderr


def test_an_enforced_register_raised_to_the_tree_is_no_reseed(repo):
    # Rule 7 takes a register equal to the staged tree as a reseed only over a SHADOW parent.
    _drift(repo)                                                       # HEAD carries what nothing granted
    env = dict(os.environ, HATCH_ROOT=str(repo.root))
    code = ("import sys; sys.path.insert(0, 'tools'); import hatch_counters as h; "
            "h.write(h.tree_scan(index=True), mode='enforce')")
    subprocess.run([sys.executable, "-c", code], cwd=repo.root, env=env, check=True)
    repo.git("add", ".")
    got = staged(repo)
    assert got.returncode == 1 and "raised by hand" in got.stderr
    assert "reseeded from the staged tree" not in got.stderr


def test_reseed_refuses_while_heads_register_is_enforced(repo):
    _set_mode(repo, "shadow")                                          # only the working copy says shadow
    before = repo.read(repo.lay["base"])
    got = repo.tool("--reseed")
    assert got.returncode != 0 and "never reseeded" in got.stderr
    assert repo.read(repo.lay["base"]) == before


def test_compiler_label_aliases_are_no_hatch():
    ledger = ("name,export_rva,target_rva,target_size,source,status,notes\n"
              "uw_00792e1c,,0x00792E1C,8,Code/gen_small/uw_gen_001.cpp,matched,gen-funclet;object-symbol=$L8581\n"
              "??__Eg_x@@YAXXZ,,0x007AF8E3,9,Code/a.cpp,matched,object-symbol=_$E16\n"
              "?f@@YAXXZ,,0x00002000,5,Code/a.cpp,matched,gen-alias;object-symbol=?f@@YAXXZ\n"
              "?g@@YAXXZ,,0x00003000,5,Code/a.cpp,matched,object-symbol=?f@@YAXXZ\n"
              "?dup_00004000@@YAXXZ,,0x00004000,5,Code/a.cpp,matched,object-symbol=??1X@@QAE@XZ\n"
              # obj_sweep / wave_accounting write placeholder gen-alias rows without admit()
              "?dup_00005000@@YAXXZ,,0x00005000,5,Code/a.cpp,matched,gen-alias;object-symbol=?h@@YAXXZ;C++ alias\n"
              # an Rva<RVA> placeholder is still a link name the tree calls: a hatch
              "??1Rva005796FC@@QAE@XZ,,0x00006000,5,Code/a.cpp,matched,object-symbol=??1X@@QAE@XZ\n"
              "?f@?A0x12345678@@YAXXZ,,0x00007000,5,Code/a.cpp,matched,object-symbol=?f@?A0x9abcdef0@@YAXXZ\n"
              # a label inside a real name is no label
              "?k@@YAXXZ,,0x00008000,5,Code/a.cpp,matched,object-symbol=?a$L1b\n")
    led = hc.BASELINE.rsplit("/", 1)[0] + "/functions.csv"
    got = hc.scan(led, ledger)
    assert set(got) == {("object_symbol", led, a) for a in ("0x00003000", "0x00006000", "0x00008000")}
    assert set(hc.occurrences(led, ledger)) == set(got)


PARITY_ROWS = [
    "uw_00792e1c,,0x00792E1C,8,a,matched,gen-funclet;object-symbol=$L8581",
    "??__Eg_x@@YAXXZ,,0x007AF8E3,9,a,matched,object-symbol=_$E16",
    "?f@@YAXXZ,,0x00002000,5,a,matched,gen-alias;object-symbol=?f@@YAXXZ",
    "?g@@YAXXZ,,0x00003000,5,a,matched,object-symbol=?f@@YAXXZ",
    "?dup_0000400A@@YAXXZ,,0x0000400A,5,a,matched,object-symbol=??1X@@QAE@XZ",
    "?dup_00005000@@YAXXZ,,0x00005000,5,a,matched,gen-alias;object-symbol=?h@@YAXXZ;C++ alias",
    "?f@?A0x12345678@@YAXXZ,,0x00007000,5,a,matched,object-symbol=?f@?A0x9abcdef0@@YAXXZ",
    "_ggetm_dup_huffdecode,,0x0068DC60,5,a,matched,object-symbol=_ggetm",
    # odd spellings: only an object-symbol= at the start or after `;` counts, its value stripped
    "?x@@YAXXZ,,0x9000,5,a,matched,x object-symbol=$L1;object-symbol=?realOther@@YAXXZ",
    "?x1@@YAXXZ,,0x9010,5,a,matched,x object-symbol=?realOther@@YAXXZ",
    "?x2@@YAXXZ,,0x9020,5,a,matched,object-symbol= ?x2@@YAXXZ ",
    "?x3@@YAXXZ,,0x9030,5,a,matched,gen-alias; object-symbol=?other@@YAXXZ",
    "?x4@@YAXXZ,,0x9040,5,a,matched,object-symbol=?other@@YAXXZ ;C++ alias",
    "?x5@@YAXXZ,,0x9050,5,a,matched,object-symbol=\t$L77\t",
    "?x6@@YAXXZ,,0x9060,5,a,matched,object-symbol=?a$L1b",
    " ?x7@@YAXXZ,,0x9070,5,a,matched,object-symbol=?x7@@YAXXZ",
]
# build.is_alias_row excuses a Gen_/Rva<RVA> placeholder name; hatch_counters counts it (rule 9)
GEN_ROWS = [
    "??1Rva005796FC@@QAE@XZ,,0x00006000,5,a,matched,object-symbol=??1X@@QAE@XZ",
    "?m@Gen_t_001db910_p4cd@@QAEXXZ,,0x00006100,5,a,matched,object-symbol=?n@@YAXXZ",
    "?rva006D95E0@BfmeAptValue006DCD20@@QAEXHPAV1@@Z,,0x6D95E0,5,a,matched,x;object-symbol=?set@AptArray@@QAEXHPAVAptValue@@@Z",
]


def test_alias_hatch_agrees_with_build_is_alias_row():
    """hatch_counters.alias_of mirrors build.is_alias_row without importing it (the hook copy
    of the tool runs standalone); the two must call the same rows plumbing, except that a
    Gen_/Rva placeholder name stays a hatch."""
    import csv
    import build
    for line in PARITY_ROWS + GEN_ROWS:
        cells = next(csv.reader([line]))
        row = {"name": cells[0], "target_rva": cells[2], "notes": cells[6]}
        gen = line in GEN_ROWS
        assert gen == bool(build.GEN_PLACEHOLDER_RE.search(cells[0])), line
        assert (hc.alias_of(cells) is not None) == (gen or build.is_alias_row(row)), line
        if hc.OBJECT_SYMBOL.search(cells[6]):
            assert build.ledger_object_symbol(row) == hc.OBJECT_SYMBOL.search(cells[6])[1].strip(), line
    expected = {"?g@@YAXXZ", "_ggetm_dup_huffdecode", "?x@@YAXXZ", "?x3@@YAXXZ", "?x4@@YAXXZ", "?x6@@YAXXZ", " ?x7@@YAXXZ"}
    assert {line.split(",")[0] for line in PARITY_ROWS if hc.alias_of(next(csv.reader([line])))} == expected


def _placeholder_audit():
    import csv
    with (TOOLS / "tests/fixtures/hatch_placeholder_aliases.tsv").open(encoding="utf-8", newline="") as f:
        return list(csv.DictReader(f, delimiter="\t"))


@pytest.mark.parametrize("row", _placeholder_audit(), ids=lambda row: row["rva"])
def test_each_of_the_51_placeholder_alias_verdicts(row):
    cells = [row["name"], "", row["rva"], "5", row["source"], "matched",
             "gen-alias; object-symbol=" + row["object_symbol"]]
    assert bool(hc.alias_of(cells)) == (row["verdict"] == "keep"), row["reason"]
    if row["verdict"] == "keep":
        assert hc.alias_of(cells) == row["object_symbol"]
    else:
        assert hc.DUP_PLACEHOLDER.fullmatch(row["name"])


def test_funclet_landing_passes_an_enforced_register(repo):
    led = repo.lay["rev"] + "/functions.csv"
    repo.write(led, repo.read(led) + "uw_00792e1c,,0x00792E1C,8,%s,matched,gen-funclet;object-symbol=$L8581\n"
               % repo.lay["src"])
    repo.git("add", ".")
    assert staged(repo).returncode == 0


def test_reseed_and_flip_land_as_one_commit(repo):
    _shadow_register(repo)
    _drift(repo)
    got = repo.tool("--reseed", "--mode", "enforce")
    assert got.returncode == 0 and "mode enforce" in got.stdout
    assert "# mode: enforce" in repo.read(repo.lay["base"])
    repo.git("add", ".")
    got = staged(repo)                                                 # parent shadow, register == tree
    assert got.returncode == 0 and "shadow -> ENFORCE" in got.stderr, got.stderr
    repo.commit("Flip\n\nVerifier-Change: hatch-reseed and enforce", when=T0)
    for line in repo.tool("--report").stdout.splitlines()[1:]:
        _, reg, tree = line.split()
        assert reg == tree
    assert "never reseeded" in repo.tool("--reseed").stderr            # one-way
    repo.write(repo.lay["src2"], repo.read(repo.lay["src2"]) + "void k() { __asm { __emit 0x90 } }\n")
    repo.git("add", ".")
    got = staged(repo)
    assert got.returncode == 1 and "emit +1" in got.stderr


def test_a_reseed_commit_may_not_add_hatches(repo):
    _shadow_register(repo)
    _drift(repo)
    repo.write(repo.lay["src2"], repo.read(repo.lay["src2"]) + "void k() { __asm { __emit 0x90 } }\n")
    repo.git("add", ".")
    assert repo.tool("--reseed", "--mode", "enforce").returncode == 0  # register == staged tree ...
    repo.git("add", ".")
    got = staged(repo)                                                 # ... but the commit adds an __emit
    assert got.returncode == 1 and "reseeded from the staged tree" not in got.stderr
    assert "raised by hand" in got.stderr


def test_reseed_writes_the_index_and_refuses_unstaged_files(repo):
    _shadow_register(repo)
    repo.write(repo.lay["src"], SOURCE + "void k() { __asm { __emit 0x90 } }\n")   # not staged
    got = repo.tool("--reseed")
    assert got.returncode != 0 and "differ from it" in got.stderr and repo.lay["src"] in got.stderr
