"""reverse/data_rows.csv starts header-only, and with it nothing changes.

The byte gate (build.py), the ledger check (check_csv.py) and the census
(link_census.py; see test_link_census_data_sources.py) read data rows the way
Open-BFME-1 does. These tests hold the port to its promise: with the empty
ledger every one of them behaves exactly as it did with no ledger at all, and
a data row, once one exists, is counted and verified.
"""
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build  # noqa: E402
import check_csv  # noqa: E402
import data_rows  # noqa: E402

HEADER_ONLY = (data_rows.HEADER + "\n").encode()
_LOAD = data_rows.load


def use_ledger(monkeypatch, path):
    """Point data_rows at `path`: DATA_ROWS, and load(), whose default argument
    is bound to DATA_ROWS at import (as in Open-BFME-1)."""
    monkeypatch.setattr(data_rows, "DATA_ROWS", path)
    monkeypatch.setattr(data_rows, "load", lambda path=path: _LOAD(path))


def data_row(source, name="?g@@3HA", address="0x00403000"):
    return ",".join([name, address, "va", "4", ".data", source, "matched", "ZH defines it", "m"])


def ledger_file(tmp_path, *rows):
    path = tmp_path / "data_rows.csv"
    path.write_bytes(HEADER_ONLY + "".join(r + "\n" for r in rows).encode())
    return path


def test_the_committed_ledger_is_header_only_and_clean():
    raw = data_rows.DATA_ROWS.read_bytes()
    assert raw == HEADER_ONLY
    problems = []
    assert data_rows.check(raw, problems) == 0  # against retail game.dat's own sections
    assert problems == []
    assert data_rows.load() == []
    assert data_rows.main(["--check"]) == 0


# --------------------------------------------------------------------------- check_csv

def _check_csv_run(monkeypatch, capsys, ledger_path):
    monkeypatch.setattr(check_csv, "DATA_ROWS", ledger_path)
    monkeypatch.setattr(sys, "argv", ["check_csv.py"])
    try:
        check_csv.main()
        code = 0
    except SystemExit as exc:
        code = exc.code
    captured = capsys.readouterr()
    return code, captured.out, captured.err


def test_check_csv_says_the_same_with_the_empty_ledger_as_without_one(monkeypatch, capsys, tmp_path):
    without = _check_csv_run(monkeypatch, capsys, tmp_path / "absent.csv")
    with_empty = _check_csv_run(monkeypatch, capsys, data_rows.DATA_ROWS)
    assert with_empty == without
    assert "data_rows.csv" not in with_empty[1] + with_empty[2]


def _orphans(monkeypatch, data_raw):
    functions = (check_csv.FUNCTIONS_HEADER + "\n"
                 "f,,0x00001000,5,Code/a.cpp,matched,\n").encode()
    monkeypatch.setattr(check_csv, "read_ledger", lambda path, spec: functions)
    monkeypatch.setattr(check_csv, "known_sources",
                        lambda spec: {"Code/a.cpp", "Code/b.cpp", "Code/c.cpp"})
    monkeypatch.setattr(check_csv, "ORPHAN_BASELINE", 1)
    problems = []
    return check_csv.check_orphans(None, problems, data_raw=data_raw), problems


def test_check_csv_orphans_count_a_data_only_source_as_owned(monkeypatch):
    assert _orphans(monkeypatch, HEADER_ONLY) == _orphans(monkeypatch, b"")
    count, problems = _orphans(monkeypatch, HEADER_ONLY)
    assert count == 2 and "Code/b.cpp, Code/c.cpp" in problems[0]
    count, problems = _orphans(monkeypatch, HEADER_ONLY + (data_row("Code/b.cpp") + "\n").encode())
    assert count == 1 and problems == []


def test_check_csv_checks_data_row_integrity(monkeypatch, capsys, tmp_path):
    bad = ledger_file(tmp_path, data_row("game/G.cpp"))
    code, _, err = _check_csv_run(monkeypatch, capsys, bad)
    assert code == 1 and "source must be a Code/ .c/.cpp file" in err
    crlf = tmp_path / "crlf.csv"
    crlf.write_bytes(HEADER_ONLY.replace(b"\n", b"\r\n"))
    code, _, err = _check_csv_run(monkeypatch, capsys, crlf)
    assert code == 1 and "data_rows.csv must use LF" in err


# --------------------------------------------------------------------------- build.py

def _claims(tmp_path, monkeypatch, ledger_path):
    (tmp_path / "Code").mkdir(exist_ok=True)
    for name in ("a.cpp", "b.cpp"):
        (tmp_path / "Code" / name).write_text("// fixture\n")
    monkeypatch.setattr(build, "ROOT", tmp_path)
    monkeypatch.setattr(build, "load_function_rows", lambda: [{"name": "f", "source": "Code/a.cpp"}])
    monkeypatch.setattr(build, "load_unclaimed_sources", lambda: set())
    use_ledger(monkeypatch, ledger_path)
    try:
        build.verify_source_claims()
        return 0
    except SystemExit as exc:
        return exc.code


def test_source_claims_are_unchanged_by_the_empty_ledger(tmp_path, monkeypatch, capsys):
    without = _claims(tmp_path, monkeypatch, tmp_path / "absent.csv"), capsys.readouterr().out
    with_empty = _claims(tmp_path, monkeypatch, ledger_file(tmp_path)), capsys.readouterr().out
    assert with_empty == without
    assert without[0] == 1 and "Code/b.cpp: ZERO matched rows" in without[1]


def test_a_data_row_owns_its_source_for_the_claims_check(tmp_path, monkeypatch, capsys):
    assert _claims(tmp_path, monkeypatch, ledger_file(tmp_path, data_row("Code/b.cpp"))) == 0
    assert "Source claims: OK" in capsys.readouterr().out


def _scoped(monkeypatch, ledger_path, only, function_rows):
    calls = []

    def record(name):
        return lambda *a, **k: calls.append((name, a, tuple(sorted(k.items()))))
    for name in ("ensure_case_shims", "ensure_reference_current", "verify_source_claims", "verify_functions",
                 "verify_string_refs", "verify_float_refs", "verify_import_refs"):
        monkeypatch.setattr(build, name, record(name))
    monkeypatch.setattr(build, "load_function_rows", lambda: function_rows)
    use_ledger(monkeypatch, ledger_path)
    monkeypatch.setattr(data_rows, "verify", record("data_rows.verify"))
    build.main(only)
    return calls


def test_a_scoped_build_is_unchanged_by_the_empty_ledger(tmp_path, monkeypatch):
    rows = [{"name": "f", "source": "Code/a.cpp"}]
    without = _scoped(monkeypatch, tmp_path / "absent.csv", ["Code/a.cpp"], rows)
    with_empty = _scoped(monkeypatch, ledger_file(tmp_path), ["Code/a.cpp"], rows)
    assert with_empty == without
    assert [name for name, _, _ in without] == [
        "ensure_case_shims", "ensure_reference_current", "verify_source_claims", "verify_functions",
        "verify_string_refs", "verify_float_refs", "verify_import_refs"]


def test_a_scoped_build_verifies_the_named_sources_data_rows(tmp_path, monkeypatch):
    path = ledger_file(tmp_path, data_row("Code/d.cpp"), data_row("Code/a.cpp", "?h@@3HA", "0x00403004"))
    rows = [{"name": "f", "source": "Code/a.cpp"}]
    data_only = _scoped(monkeypatch, path, ["Code/d.cpp"], rows)
    assert ("data_rows.verify", (), (("sources", ["Code/d.cpp"]),)) in data_only
    assert "verify_functions" not in [name for name, _, _ in data_only]  # a data-only TU owns no function
    both = _scoped(monkeypatch, path, ["Code/a.cpp"], rows)
    assert ("data_rows.verify", (), (("sources", ["Code/a.cpp"]),)) in both
    assert "verify_functions" in [name for name, _, _ in both]


def test_the_full_gate_runs_the_data_check_and_it_passes_on_the_empty_ledger(tmp_path, monkeypatch, capsys):
    import importlib
    gate = importlib.import_module("build")
    pin_consistency = importlib.import_module("pin_consistency")
    check_module_registry = importlib.import_module("check_module_registry")
    for module, name in ((gate, "ensure_case_shims"), (gate, "ensure_reference_current"),
                         (gate, "verify_baseline"), (gate, "verify_string_refs"), (gate, "verify_float_refs"),
                         (gate, "verify_import_refs"), (gate, "verify_dir32_consistency"),
                         (gate, "verify_source_claims"), (gate, "verify_noop_patch"),
                         (pin_consistency, "verify"), (check_module_registry, "verify")):
        monkeypatch.setattr(module, name, lambda *a, **k: None)
    monkeypatch.setattr(gate, "verify_functions", lambda *a, **k: ["patch"])
    monkeypatch.setattr(gate, "load_function_rows", lambda: [])
    use_ledger(monkeypatch, ledger_file(tmp_path))
    gate.main()
    out = capsys.readouterr().out
    assert "FULL GATE: OK" in out and "Data rows" not in out  # nothing to verify, nothing said
    # a row that does not verify reddens the gate, and the gate names it
    reloc_ledger = importlib.import_module("reloc_ledger")
    monkeypatch.setattr(reloc_ledger, "Image", lambda *a: object())
    monkeypatch.setattr(data_rows, "Resolver", lambda rows: (lambda name: set()))
    use_ledger(monkeypatch, ledger_file(tmp_path, data_row("Code/no_such_fixture.cpp")))
    with pytest.raises(SystemExit):
        gate.main()
    out = capsys.readouterr().out
    assert "Code/no_such_fixture.cpp is missing" in out
    assert "FULL GATE: FAIL" in out and "data rows" in out
