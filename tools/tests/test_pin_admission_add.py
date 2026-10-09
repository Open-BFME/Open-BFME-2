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
