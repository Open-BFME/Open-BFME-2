"""pin_admission.add_pins: the tool path for pins. A pin that passes the admission
rules is written and admitted in the hatch register, so the (enforced) register lets
it through; a refused pin writes nothing; a pin typed by hand next to it is still
refused by tools/hatch_counters.py --staged."""
import os
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
import hatch_counters  # noqa: E402
import pin_admission  # noqa: E402

LEDGER = ("name,export_rva,target_rva,target_size,source,status,notes\n"
          "?owner@@YAXXZ,,0x00001000,16,Code/a.cpp,matched,\n")


def git(root, *args):
    env = dict(os.environ, GIT_AUTHOR_NAME="t", GIT_COMMITTER_NAME="t", GIT_AUTHOR_EMAIL="",
               GIT_COMMITTER_EMAIL="")
    got = subprocess.run(["git", "-C", str(root), *args], capture_output=True, text=True, env=env)
    assert got.returncode == 0, got.stderr
    return got.stdout


@pytest.fixture
def tree(tmp_path, monkeypatch):
    (tmp_path / "reverse").mkdir()
    (tmp_path / "reverse/symbols.csv").write_bytes(b"name,address,notes\n?a@@YAXXZ,0x00001010,pin\n")
    (tmp_path / "reverse/functions.csv").write_text(LEDGER, newline="\n")
    git(tmp_path, "init", "-q")
    git(tmp_path, "config", "core.autocrlf", "false")
    monkeypatch.setattr(hatch_counters, "ROOT", tmp_path)
    git(tmp_path, "add", ".")
    hatch_counters.write(hatch_counters.tree_scan(), mode="enforce")
    git(tmp_path, "add", ".")
    git(tmp_path, "commit", "-qm", "init")
    monkeypatch.setattr(pin_admission, "ROOT", tmp_path)
    # .text 0x1000-0x9000 executable, .rdata 0x9000-0xA000 not
    monkeypatch.setattr(pin_admission, "image_layout",
                        lambda: (0xA000, [(0x1000, 0x9000, True), (0x9000, 0xA000, False)]))
    monkeypatch.setattr(pin_admission.build, "load_all_function_rows",
                        lambda: list(__import__("csv").DictReader(LEDGER.splitlines())))
    monkeypatch.chdir(tmp_path)
    return tmp_path


def staged(root):
    git(root, "add", ".")
    errors, _, hard = hatch_counters.check_staged()
    return errors + hard


def test_checked_pin_is_written_and_admitted(tree):
    assert pin_admission.add_pins([("?callee@@YAXXZ", "0x2000")], "callee of x") == []
    assert "?callee@@YAXXZ,0x00002000,callee of x\n" in (tree / "reverse/symbols.csv").read_text()
    assert "allow=" in (tree / "reverse/hatch_baseline.tsv").read_text()
    assert staged(tree) == []


def test_refused_pin_writes_nothing(tree):
    before = (tree / "reverse/symbols.csv").read_bytes(), (tree / "reverse/hatch_baseline.tsv").read_bytes()
    problems = pin_admission.add_pins([("?ok@@YAXXZ", "0x2000"), ("?data@@3HA", "0x9004")])
    assert problems and "not in an executable section" in problems[0]
    problems = pin_admission.add_pins([("?second@@YAXXZ", "0x1000")])
    assert problems and "already carries the real name" in problems[0]
    assert ((tree / "reverse/symbols.csv").read_bytes(), (tree / "reverse/hatch_baseline.tsv").read_bytes()) == before


def test_hand_pin_beside_a_tool_pin_is_refused(tree):
    assert pin_admission.add_pins([("?callee@@YAXXZ", "0x2000")]) == []
    with (tree / "reverse/symbols.csv").open("a", newline="\n") as handle:
        handle.write("?typed@@YAXXZ,0x00003000,by hand\n")
    problems = staged(tree)
    assert problems and any("0x00003000" in p for p in problems)
    assert not any("0x00002000" in p and "raised by hand" not in p for p in problems if "pin +" in p)


def test_two_tool_writes_in_one_commit_both_pass(tree):
    assert pin_admission.add_pins([("?one@@YAXXZ", "0x2000")]) == []
    assert pin_admission.add_pins([("?two@@YAXXZ", "0x3000")]) == []
    assert staged(tree) == []


def test_an_edit_between_two_tool_writes_keeps_both_admissions(tree):
    assert pin_admission.add_pins([("?one@@YAXXZ", "0x2000")]) == []
    pins = tree / "reverse/symbols.csv"
    pins.write_bytes(pins.read_bytes().replace(b",pin\n", b",pin; renoted by another tool\n"))
    assert pin_admission.add_pins([("?two@@YAXXZ", "0x3000")]) == []
    assert hatch_counters.ungranted("reverse/symbols.csv") == {}
    assert staged(tree) == []


def test_hand_pin_between_two_tool_writes_is_still_refused(tree, capsys):
    assert pin_admission.add_pins([("?one@@YAXXZ", "0x2000")]) == []
    with (tree / "reverse/symbols.csv").open("a", newline="\n") as handle:
        handle.write("?typed@@YAXXZ,0x00004000,by hand\n")
    assert pin_admission.add_pins([("?two@@YAXXZ", "0x3000")]) == []
    assert "note: 1 other pin address(es)" in capsys.readouterr().err   # the hand pin, and said so
    assert set(hatch_counters.ungranted("reverse/symbols.csv")) == {("pin", "reverse/symbols.csv", "0x00004000")}
    problems = staged(tree)
    assert any("0x00004000" in p for p in problems)
    assert not any("0x00002000" in p or "0x00003000" in p for p in problems)


def _stamp(tree, address):
    return [line for line in (tree / "reverse/hatch_baseline.tsv").read_text().splitlines()
            if f"\t{address}\t" in line][0].split("allow=")[1]


@pytest.mark.parametrize("stamp", ["neighbour", "0" * 40])
def test_hand_pin_behind_a_hex_stamped_typed_line_is_still_refused(tree, stamp, capsys):
    # A typed register line with a blob-shaped stamp -- copied from the tool's own line, or
    # forged -- is not an admission, and the next --add must not turn it into one.
    assert pin_admission.add_pins([("?one@@YAXXZ", "0x2000")]) == []
    stamp = _stamp(tree, "0x00002000") if stamp == "neighbour" else stamp
    with (tree / "reverse/symbols.csv").open("a", newline="\n") as handle:
        handle.write("?typed@@YAXXZ,0x00004000,by hand\n")
    with (tree / "reverse/hatch_baseline.tsv").open("a", newline="\n") as handle:
        handle.write(f"pin\treverse/symbols.csv\t0x00004000\t1\tallow={stamp}\n")
    assert any("0x00004000" in p for p in staged(tree))                 # refused before the call
    assert pin_admission.add_pins([("?two@@YAXXZ", "0x3000")]) == []
    err = capsys.readouterr().err
    assert "kept pin in reverse/symbols.csv: 0x00002000 at 1" in err
    assert "NOT KEPT pin in reverse/symbols.csv: 0x00004000" in err and "note: 1 other pin address(es)" in err
    assert set(hatch_counters.ungranted("reverse/symbols.csv")) == {("pin", "reverse/symbols.csv", "0x00004000")}
    problems = staged(tree)                                             # and still refused after it
    assert any("0x00004000" in p for p in problems)
    assert not any("0x00002000" in p or "0x00003000" in p for p in problems)


def test_pin_renamed_at_an_admitted_address_is_refused_after_the_next_add(tree):
    assert pin_admission.add_pins([("?one@@YAXXZ", "0x2000")]) == []
    pins = tree / "reverse/symbols.csv"
    pins.write_bytes(pins.read_bytes().replace(b"?one@@YAXXZ,0x00002000", b"?unchecked@@YAXXZ,0x00002000"))
    assert pin_admission.add_pins([("?two@@YAXXZ", "0x3000")]) == []
    problems = staged(tree)
    assert any("0x00002000" in p for p in problems) and not any("0x00003000" in p for p in problems)


def test_add_fails_loudly_and_restores_when_the_register_does_not_grant(tree, monkeypatch):
    assert pin_admission.add_pins([("?one@@YAXXZ", "0x2000")]) == []
    pins, register = tree / "reverse/symbols.csv", tree / "reverse/hatch_baseline.tsv"
    # another tool's edit: the first admission's stamp now names an older blob
    pins.write_bytes(pins.read_bytes().replace(b",pin\n", b",pin; renoted by another tool\n"))
    before = pins.read_bytes(), register.read_bytes()
    real = hatch_counters.admit
    # an admit() that writes nothing: the pin just added is not granted
    monkeypatch.setattr(hatch_counters, "admit", lambda *a, **k: {"admitted": [], "kept": [], "refused": []})
    problems = pin_admission.add_pins([("?two@@YAXXZ", "0x3000")])
    assert any("HATCH REGISTER DOES NOT GRANT pin 0x00003000" in p for p in problems)
    assert (pins.read_bytes(), register.read_bytes()) == before

    # an admit() that resets the earlier admission to HEAD (the old defect) is caught too
    def resetting(*args, **kwargs):
        got = real(*args, **kwargs)
        register.write_text("".join(line for line in register.read_text().splitlines(True)
                                    if "0x00002000" not in line), newline="\n")
        return got
    monkeypatch.setattr(hatch_counters, "admit", resetting)
    problems = pin_admission.add_pins([("?two@@YAXXZ", "0x3000")])
    assert problems == [p for p in problems if "pin 0x00002000" in p and "admitted before this call" in p]
    assert len(problems) == 1
    assert (pins.read_bytes(), register.read_bytes()) == before
    monkeypatch.setattr(hatch_counters, "admit", real)               # the real admit() keeps it
    assert pin_admission.add_pins([("?two@@YAXXZ", "0x3000")]) == []
    assert staged(tree) == []


def test_repeat_of_an_existing_pin_is_a_no_op(tree):
    before = (tree / "reverse/symbols.csv").read_bytes()
    assert pin_admission.add_pins([("?a@@YAXXZ", "0x1010")]) == []
    assert (tree / "reverse/symbols.csv").read_bytes() == before


def test_the_enforced_commit_gate_passes_the_tool_path_and_says_what_to_do_otherwise(tree, capsys):
    assert "# mode: enforce" in (tree / "reverse/hatch_baseline.tsv").read_text()
    assert pin_admission.add_pins([("?callee@@YAXXZ", "0x2000")]) == []
    git(tree, "add", ".")
    assert hatch_counters.main(["--staged"]) == 0                       # the hook's own call
    with (tree / "reverse/symbols.csv").open("a", newline="\n") as handle:
        handle.write("?typed@@YAXXZ,0x00003000,by hand\n")
    git(tree, "add", ".")
    capsys.readouterr()
    assert hatch_counters.main(["--staged"]) == 1
    err = capsys.readouterr().err
    assert "REFUSED" in err and "pin +1 in reverse/symbols.csv: 0x00003000" in err
    assert "tools/pin_admission.py --add NAME 0xRVA" in err             # the way in it names


# ---------------------------------------------------------------- export aliases (--alias)

KEY_GUARD = "?$S128@?1??GetValue@?$K@$00@@CAPBDXZ@4IA"
OUR_GUARD = "?$S3@?1??GetValue@?$K@$00@@CAPBDXZ@4IA"
S22 = "?$S22@?1??GetValue@?$DefaultModuleKey@$05@FXParticleSystem@@CAPBDXZ@4IA"    # in ZERO_WORD_EXPORTS
WIDE = "?$S30@?1??GetValue@?$K@$09@@CAPBDXZ@4IA"
GUARDED = "?$S41@?1??GetValue@?$K@$0C@@CAPBDXZ@4IA"
THIRD = "?$S50@?1??GetValue@?$K@$0E@@CAPBDXZ@4IA"
EXPORTS = ("ordinal,rva,target_rva,section,kind,name\n"
           f"1,0x00A029F0,,.data,data,{KEY_GUARD}\n"
           f"2,0x00A0609C,,.data,data,{S22}\n"
           "3,0x00A02C88,,.data,data,?KEY@?$T@$00@@2ABQBDB\n"
           "4,0x00A03000,,.data,data,?$S5@?1??GetValue@?$K@$01@@CAPBDXZ@4IA\n"
           "5,0x00A03004,,.data,data,?owned@@3HA\n"
           "6,0x00A03008,,.data,data,?nobody@@3HA\n"
           f"8,0x00A03010,,.data,data,{WIDE}\n"
           f"9,0x00A03018,,.data,data,{GUARDED}\n"
           f"10,0x00A0301C,,.data,data,{THIRD}\n")
DATA_LEDGER = ("address,size,section,kind,name,source,status,names,defs,refs\n"
               f"0x00A029F0,4,.data,global,{OUR_GUARD},Code/d.cpp,owned,,0,2\n"
               "0x00A0609C,4,.data,global,?keyGuardCopy@@3IA,Code/d.cpp,owned,,0,0\n"
               "0x00A02C88,4,.data,global,?s_key@?$T@$00@@2ABQBDB,Code/m.cpp,owned,,0,2\n"
               "0x00A03000,4,.data,global,?$S9@?1??GetValue@?$K@$02@@CAPBDXZ@4IA,Code/d.cpp,owned,,0,2\n"
               "0x00A03004,4,.data,global,?owned@@3HA,Code/d.cpp,owned,,0,1\n"
               "0x00A03010,8,.data,global,?wideCopy@@3_JA,Code/d.cpp,owned,,0,0\n"
               "0x00A03018,4,.data,global,?$S2@?1??GetValue@?$K@$0D@@CAPBDXZ@4IA,Code/d.cpp,owned,,0,0\n"
               "0x00A0301C,4,.data,global,?thirdCopy@@3IA,Code/d.cpp,owned,,0,0\n")


@pytest.fixture
def atree(tree, monkeypatch):
    (tree / "reverse/exports.csv").write_text(EXPORTS, newline="\n")
    (tree / "reverse/data_ledger.csv").write_text(DATA_LEDGER, newline="\n")
    git(tree, "add", ".")
    git(tree, "commit", "-qm", "alias inputs")
    monkeypatch.setattr(pin_admission, "retail_bytes", lambda rva, size: bytes(size))
    monkeypatch.setattr(pin_admission, "retail_references", lambda rva: 0)
    return tree


def aliases(tree):
    path = tree / "reverse/export_aliases.csv"
    return path.read_text() if path.exists() else None


def test_a_guard_alias_is_written_admitted_and_passes_both_gates(atree):
    assert pin_admission.add_aliases([(KEY_GUARD, OUR_GUARD)], "LINK-584 owner option 1") == []
    assert aliases(atree) == f"export,target,notes\n{KEY_GUARD},{OUR_GUARD},LINK-584 owner option 1\n"
    assert f"export_alias\treverse/export_aliases.csv\t{KEY_GUARD}\t1\tallow=" in \
        (atree / "reverse/hatch_baseline.tsv").read_text()
    assert staged(atree) == []
    assert pin_admission.judge_aliases("", aliases(atree)) == []


def test_a_listed_zero_word_export_may_be_answered_by_a_named_word(atree):
    assert pin_admission.add_aliases([(S22, "?keyGuardCopy@@3IA")]) == []
    assert "retail-scan: no word names VA 0x00E0609C or its bytes; 4 zero bytes" in aliases(atree)
    assert staged(atree) == []


def test_a_third_guard_export_with_an_unnamed_zero_word_is_refused(atree):
    # Zero, 4 bytes, no retail word names it, a named word owns it: a scan proves no non-use, so only
    # the reviewed ZERO_WORD_EXPORTS may take this route.
    problems = pin_admission.add_aliases([(THIRD, "?thirdCopy@@3IA")])
    assert problems and "ZERO_WORD_EXPORTS" in problems[0]
    assert aliases(atree) is None


@pytest.mark.parametrize("export,target,refs", [
    (S22, "?keyGuardCopy@@3IA", 1),                                    # a retail word names it
    (WIDE, "?wideCopy@@3_JA", 0),                                      # not a 4-byte word
    (GUARDED, "?$S2@?1??GetValue@?$K@$0D@@CAPBDXZ@4IA", 0),            # answered by another guard
])
def test_a_listed_zero_word_export_still_needs_the_scan_a_word_and_no_guard(atree, monkeypatch,
                                                                            export, target, refs):
    monkeypatch.setitem(pin_admission.ZERO_WORD_EXPORTS, WIDE, 0x00A03010)
    monkeypatch.setitem(pin_admission.ZERO_WORD_EXPORTS, GUARDED, 0x00A03018)
    monkeypatch.setattr(pin_admission, "retail_references", lambda rva: refs)
    problems = pin_admission.add_aliases([(export, target)])
    assert problems and "only a guard of the same local static" in problems[0]
    assert aliases(atree) is None


def test_the_gate_reads_the_ledger_at_the_commit_not_the_work_tree(atree):
    wrong = "?$S4@?1??GetValue@?$K@$00@@CAPBDXZ@4IA"
    (atree / "reverse/export_aliases.csv").write_text(f"export,target,notes\n{KEY_GUARD},{wrong},typed\n",
                                                      newline="\n")
    git(atree, "add", "reverse/export_aliases.csv")
    # unstaged: in the work tree WRONG would own the address
    (atree / "reverse/data_ledger.csv").write_text(DATA_LEDGER.replace(OUR_GUARD, wrong), newline="\n")
    problems = pin_admission.judge_alias_range("HEAD", "")
    assert problems and "is not the owner" in problems[0]


def test_a_word_retail_holds_nonzero_is_refused(atree, monkeypatch):
    monkeypatch.setattr(pin_admission, "retail_bytes", lambda rva, size: b"\x01" + bytes(size - 1))
    problems = pin_admission.add_aliases([(S22, "?keyGuardCopy@@3IA")])
    assert problems and "holds at zero" in problems[0]
    assert aliases(atree) is None


@pytest.mark.parametrize("export,target,why", [
    ("?invented@@3HA", OUR_GUARD, "not a retail export"),
    (KEY_GUARD, KEY_GUARD, "the export itself"),
    (KEY_GUARD, "?$S4@?1??GetValue@?$K@$00@@CAPBDXZ@4IA", "is not the owner"),     # right shape, wrong word
    ("?$S5@?1??GetValue@?$K@$01@@CAPBDXZ@4IA", "?$S9@?1??GetValue@?$K@$02@@CAPBDXZ@4IA",
     "only a guard of the same local static"),                                     # another static's guard
    ("?KEY@?$T@$00@@2ABQBDB", "?s_key@?$T@$00@@2ABQBDB", "only a guard of the same local static"),  # read: refs 2
    ("?owned@@3HA", "?other@@3HA", "already names 0x00A03004 by the export's own spelling"),
    ("?nobody@@3HA", "?ours@@3HA", "no reverse/data_ledger.csv row owns"),
])
def test_refused_aliases_write_nothing(atree, export, target, why):
    before = (atree / "reverse/hatch_baseline.tsv").read_bytes()
    problems = pin_admission.add_aliases([(export, target)])
    assert problems and why in problems[0], problems
    assert aliases(atree) is None
    assert (atree / "reverse/hatch_baseline.tsv").read_bytes() == before


def test_an_export_the_ledger_already_names_needs_no_alias(atree):
    (atree / "reverse/symbols.csv").write_text(f"name,address,notes\n{KEY_GUARD},0x00001010,x\n", newline="\n")
    problems = pin_admission.add_aliases([(KEY_GUARD, OUR_GUARD)])
    assert problems and "already names the export itself" in problems[0]


def test_one_export_aliased_once(atree):
    assert pin_admission.add_aliases([(KEY_GUARD, OUR_GUARD)]) == []
    problems = pin_admission.add_aliases([(KEY_GUARD, "?keyGuardCopy@@3IA")])
    assert problems and "already aliased" in problems[0]
    typed = aliases(atree) + f"{KEY_GUARD},?keyGuardCopy@@3IA,by hand\n"
    assert any("aliased more than once" in p for p in pin_admission.judge_aliases("", typed))


def test_a_typed_alias_is_refused_by_the_register_and_named(atree, capsys):
    (atree / "reverse/export_aliases.csv").write_text(
        f"export,target,notes\n{KEY_GUARD},{OUR_GUARD},by hand\n", newline="\n")
    git(atree, "add", ".")
    capsys.readouterr()
    assert hatch_counters.main(["--staged"]) == 1
    err = capsys.readouterr().err
    assert f"export_alias +1 in reverse/export_aliases.csv: {KEY_GUARD}" in err
    assert "tools/pin_admission.py --alias EXPORT TARGET" in err


def test_a_retargeted_alias_is_judged_again(atree):
    assert pin_admission.add_aliases([(KEY_GUARD, OUR_GUARD)]) == []
    git(atree, "add", ".")
    git(atree, "commit", "-qm", "admitted")
    wrong = aliases(atree).replace(OUR_GUARD, "?$S4@?1??GetValue@?$K@$00@@CAPBDXZ@4IA")
    problems = pin_admission.judge_aliases(aliases(atree), wrong)
    assert problems and "is not the owner" in problems[0]
    assert pin_admission.judge_aliases(aliases(atree), "export,target,notes\n") == []    # removal shrinks
