"""reverse/symbols.csv has to carry ONE line terminator, and who enforces it.

symbols.csv is `merge=union` and its rows are pins that several tools legitimately
re-emit. A line differing from its twin only by a `\\r` is a DISTINCT line to the
union driver, so the same pin lands twice and every later merge compounds it.
Open-BFME-2 therefore requires canonical LF in both ledgers.

Every writer must reject a non-LF file before appending. The writers are tested
here alongside check_csv (the commit gate) and dedup_csv (the repair tool), so a
new entry point cannot preserve a legacy terminator into a commit the gate then
rejects.
"""
import importlib.util
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

HEADER = "name,address,notes"
PIN_A = "?alpha@@YAXXZ,0x00401000,"
PIN_B = "?beta@@YAXXZ,0x00402000,"


def _load(name):
    if name not in sys.modules:
        spec = importlib.util.spec_from_file_location(name, TOOLS / f"{name}.py")
        module = importlib.util.module_from_spec(spec)
        sys.modules[name] = module
        spec.loader.exec_module(module)
    return sys.modules[name]


check_csv = _load("check_csv")
dedup_csv = _load("dedup_csv")
ledger_io = _load("ledger_io")
add_match = _load("add_match")


def symbols(*lines, eol="\r\n"):
    return (eol.join([HEADER, *lines]) + eol).encode("utf-8")


# --------------------------------------------------------------------------
# check_csv: the commit that mixes the file is the one that fails
# --------------------------------------------------------------------------

def test_a_uniform_lf_symbols_file_is_fine():
    problems = []
    check_csv.check_symbols(symbols(PIN_A, PIN_B, eol="\n"), problems)
    assert problems == []


def test_a_uniform_crlf_symbols_file_is_rejected():
    problems = []
    check_csv.check_symbols(symbols(PIN_A, PIN_B), problems)
    assert any("must use LF" in problem for problem in problems), problems


def test_one_lf_pin_in_a_crlf_file_is_reported_with_its_line_number():
    """The live case: a hand-appended pin at the tail blocked every land."""
    raw = symbols(PIN_A) + (PIN_B + "\n").encode("utf-8")
    problems = []
    check_csv.check_symbols(raw, problems)
    assert len(problems) == 1, problems
    assert "line 3" in problems[0], problems[0]
    assert "union" in problems[0].lower(), "say why a stray \\r matters, not just that it is there"


def test_the_mixing_is_reported_whichever_terminator_is_the_odd_one():
    raw = symbols(PIN_A, eol="\n") + (PIN_B + "\r\n").encode("utf-8")
    problems = []
    check_csv.check_symbols(raw, problems)
    assert len(problems) == 1 and "line 3" in problems[0], problems


def test_the_terminator_check_does_not_mask_the_other_symbols_checks():
    raw = symbols("?alpha@@YAXXZ,0x00401000,") + b"?alpha@@YAXXZ,0x00401000,\n"
    problems = []
    check_csv.check_symbols(raw, problems)
    assert any("exact duplicate" in p for p in problems), problems


def test_shipped_union_ledgers_are_canonical_lf_or_empty():
    reverse = TOOLS.parent / "reverse"
    for name in ("functions.csv", "symbols.csv", "deleted_rows.csv"):
        assert set(ledger_io.terminator_census((reverse / name).read_bytes())) == {b"\n"}
    assert (reverse / "re_attempts.log").read_bytes() == b""


@pytest.mark.parametrize("label", ["deleted_rows.csv", "re_attempts.log"])
def test_check_csv_rejects_crlf_in_auxiliary_union_ledgers(label):
    problems = []
    check_csv.check_lf_ledger(b"header\r\n", label, problems)
    assert len(problems) == 1 and "must use LF" in problems[0]


def test_check_functions_rejects_mixed_terminators():
    raw = ("name,export_rva,target_rva,target_size,source,status,notes\n"
           "?f@@YAXXZ,,0x00401000,16,Code/GameEngine/f.cpp,matched,\r\n").encode()
    problems = []
    check_csv.check_functions(raw, problems, {"Code/GameEngine/f.cpp"})
    assert any("must use LF" in problem for problem in problems), problems


@pytest.mark.parametrize("tool", [
    "add_match.py", "add_match_batch.py", "gen_dump.py", "gen_small.py",
    "gen_uw.py", "land_ambiguous.py", "land_wave.py", "locate.py",
    "merge_cluster.py", "zh_sweep.py",
])
def test_every_active_functions_writer_requires_lf(tool):
    text = (TOOLS / tool).read_text(encoding="utf-8")
    assert "lf_terminator" in text or "line_terminator" in text, tool


def test_gen_dump_retract_validates_and_rolls_back_both_ledgers():
    text = (TOOLS / "gen_dump.py").read_text(encoding="utf-8")
    retract = text.split("def retract(sha):", 1)[1].split("\ndef main():", 1)[0]
    assert retract.count("lf_terminator") == 2
    assert "LOCK_FILE" in retract and "DELETED.write_bytes(deleted_raw)" in retract


def test_locate_validates_both_ledgers_before_its_first_append():
    text = (TOOLS / "locate.py").read_text(encoding="utf-8")
    emit = text.split("if args.emit and rows:", 1)[1]
    assert emit.index("symbols_eol =") < emit.index('build.FUNCTIONS.open("ab")')
    assert "build.FUNCTIONS.write_bytes(functions_raw)" in emit


def test_add_match_replace_rva_keeps_the_ledger_lf(tmp_path, monkeypatch):
    source = tmp_path / "Code" / "GameEngine" / "f.cpp"
    source.parent.mkdir(parents=True)
    source.write_text("void f() {}\n", encoding="utf-8", newline="\n")
    reverse = tmp_path / "reverse"
    reverse.mkdir()
    ledger = reverse / "functions.csv"
    ledger.write_bytes(
        b"name,export_rva,target_rva,target_size,source,status,notes\n"
        b"?d_00401000@@YAXXZ,,0x00401000,5,Code/gen_asm/d.asm,matched,gen-dump\n")
    monkeypatch.setattr(sys, "argv", [
        "add_match.py", "?f@@YAXXZ", "0x00401000", "5",
        "Code/GameEngine/f.cpp", "--replace-rva", "0x00401000",
        "--no-verify", "--root", str(tmp_path)])

    add_match.main()

    raw = ledger.read_bytes()
    assert b"\r" not in raw
    assert b"?d_00401000@@YAXXZ" not in raw
    assert b"?f@@YAXXZ" in raw


# --------------------------------------------------------------------------
# dedup_csv: the repair tool, which used to be a second way to break it
# --------------------------------------------------------------------------

def test_dedup_normalizes_a_crlf_symbols_file_to_lf(tmp_path):
    path = tmp_path / "symbols.csv"
    path.write_bytes(symbols(PIN_B, PIN_A))
    dedup_csv.dedup_symbols(path)
    assert set(t for _, t in ledger_io.split_records(path.read_bytes())) == {b"\n"}


def test_dedup_keeps_an_lf_file_lf(tmp_path):
    path = tmp_path / "symbols.csv"
    path.write_bytes(symbols(PIN_B, PIN_A, eol="\n"))
    dedup_csv.dedup_symbols(path)
    assert set(t for _, t in ledger_io.split_records(path.read_bytes())) == {b"\n"}


def test_dedup_normalizes_a_mixed_symbols_file_to_lf(tmp_path, capsys):
    path = tmp_path / "symbols.csv"
    path.write_bytes(symbols(PIN_A) + (PIN_B + "\n").encode("utf-8"))
    dedup_csv.dedup_symbols(path)
    assert set(t for _, t in ledger_io.split_records(path.read_bytes())) == {b"\n"}
    assert "rewritten to lf" in capsys.readouterr().out.lower()


def test_dedup_still_collapses_duplicate_pins(tmp_path):
    path = tmp_path / "symbols.csv"
    path.write_bytes(symbols(PIN_A, PIN_A, PIN_B))
    before, after = dedup_csv.dedup_symbols(path)
    assert (before, after) == (3, 2)


# --------------------------------------------------------------------------
# dedup_csv over functions.csv: the same defect, at 60x the scale
# --------------------------------------------------------------------------

FN_HEADER = "name,export_rva,target_rva,target_size,source,status,notes"
SRC = "Code/GameEngine/Source/Common/Thing.cpp"
ROW_A = f"?a@Thing@@QAEXXZ,,0x00401000,16,{SRC},matched,"
ROW_B = f"?b@Thing@@QAEXXZ,,0x00402000,16,{SRC},matched,"


def functions(*rows_with_terms):
    out = FN_HEADER.encode() + b"\r\n"
    for row, term in rows_with_terms:
        out += row.encode() + term
    return out


def test_dedup_functions_normalizes_every_survivor_to_lf(tmp_path):
    """The BFME2 repair tool canonicalizes even when no duplicate collapses."""
    path = tmp_path / "functions.csv"
    path.write_bytes(functions((ROW_B, b"\r\r\n"), (ROW_A, b"\n")))
    assert dedup_csv.dedup_functions(path) == (2, 2)
    kept = ledger_io.split_records(path.read_bytes())[1:]
    assert [payload.decode() for payload, _ in kept] == [ROW_B, ROW_A]
    assert {term for _, term in kept} == {b"\n"}


def test_dedup_functions_still_collapses_and_canonicalizes_the_survivor(tmp_path):
    path = tmp_path / "functions.csv"
    path.write_bytes(functions((ROW_B, b"\r\r\n"), (ROW_A, b"\n"), (ROW_A, b"\r\n")))
    assert dedup_csv.dedup_functions(path) == (3, 2)
    kept = ledger_io.split_records(path.read_bytes())[1:]
    assert [payload.decode() for payload, _ in kept] == [ROW_A, ROW_B]
    assert {term for _, term in kept} == {b"\n"}


def test_dedup_functions_still_refuses_a_two_source_tie(tmp_path):
    path = tmp_path / "functions.csv"
    other = ROW_A.replace(SRC, "Code/GameEngine/Source/Common/Other.cpp")
    path.write_bytes(functions((ROW_A, b"\r\n"), (other, b"\r\n")))
    before = path.read_bytes()
    with pytest.raises(SystemExit) as exc:
        dedup_csv.dedup_functions(path)
    assert exc.value.code == 1
    assert path.read_bytes() == before


def test_add_match_rewrite_key_accepts_lowercase_csv_hex():
    """CSV hex spelling must not make --replace-existing leave its row behind."""
    fields = ["?assign@Thing@@QAEAAV1@ABV1@@Z", "", "0x005d5ae0", "60",
              SRC, "matched", ""]
    assert add_match.ledger_key(fields) == (fields[0], 0x005D5AE0)


# --------------------------------------------------------------------------
# ledger_io: one implementation of "which terminator", two policies over it
# --------------------------------------------------------------------------

def test_uniform_terminator_names_the_file_and_the_repair():
    with pytest.raises(SystemExit) as exc:
        ledger_io.uniform_terminator(symbols(PIN_A) + b"x,0x1,\n", "symbols.csv")
    assert "symbols.csv" in str(exc.value) and "dedup_csv" in str(exc.value)


def test_uniform_terminator_returns_the_one_the_file_uses():
    assert ledger_io.uniform_terminator(symbols(PIN_A), "symbols.csv") == b"\r\n"
    assert ledger_io.uniform_terminator(symbols(PIN_A, eol="\n"), "symbols.csv") == b"\n"


def test_gen_small_still_asks_the_same_question():
    """land_wave and gen_small both call it; there must be exactly one answer."""
    assert _load("gen_small").line_terminator is ledger_io.lf_terminator


# Anything that opens symbols.csv for writing, however it spells it. This
# census makes adding a writer require an explicit canonical-LF decision here.
WRITE = ("SYMBOLS.open(\"a", "rewrite_lines(SYMBOLS", "symbols.csv\").write",
         "dedup_symbols")


def symbols_writers():
    return sorted(path.name for path in TOOLS.glob("*.py")
                  if any(mark in path.read_text(encoding="utf-8") for mark in WRITE))


def test_the_set_of_symbols_writers_is_the_one_this_file_reasons_about():
    """A new writer must not appear without deciding this question.

    zh_sweep is the sixth, and it appends for the one case land_wave refuses:
    a callee already pinned at another address, called again from a site whose
    own target is proven byte-equal. It answers this file's question the same
    way — gen_small.line_terminator, which is ledger_io.lf_terminator.
    """
    assert symbols_writers() == ["dedup_csv.py", "gen_small.py", "gen_uw.py",
                                 "land_wave.py", "locate.py",
                                 "zh_sweep.py"], symbols_writers()


@pytest.mark.parametrize("tool", ["dedup_csv.py", "gen_small.py", "gen_uw.py",
                                  "land_wave.py", "locate.py", "zh_sweep.py"])
def test_a_symbols_writer_takes_the_terminator_from_the_file(tool):
    text = (TOOLS / tool).read_text(encoding="utf-8")
    assert "lf_terminator" in text or "line_terminator" in text or \
        "CANONICAL_EOL" in text, (
            f"{tool}: the symbols.csv write must require canonical LF")
