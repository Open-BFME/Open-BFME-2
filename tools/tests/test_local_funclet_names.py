"""Compiler-local EH labels may repeat across TUs, never external identities."""
import csv
import io
import sys
from pathlib import Path
from types import SimpleNamespace

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import add_match
import add_match_batch
import build
import check_csv
import ledger_io

HEADER = check_csv.FUNCTIONS_HEADER
NOTES = "gen-funclet;parent=?parent@@YAXXZ"


def row(source="Code/a.cpp", name="$L1893", notes=NOTES):
    return {"name": name, "source": source, "notes": notes}


def ledger(*rows):
    result = io.StringIO()
    writer = csv.writer(result, lineterminator="\n")
    writer.writerow(HEADER.split(","))
    for index, item in enumerate(rows):
        writer.writerow([item["name"], "", hex(0x1000 + index * 0x20), 8,
                         item["source"], "matched", item["notes"]])
    return result.getvalue().encode()


def test_local_labels_in_different_sources_have_distinct_ledger_identities():
    problems = []
    check_csv.check_functions(ledger(row(), row("Code/b.cpp")), problems,
                              {"Code/a.cpp", "Code/b.cpp"}, b"")
    assert problems == []


@pytest.mark.parametrize("second", [
    row(), row("Code\\a.cpp"), row("Code/b.cpp", notes="gen-funclet"),
    row("Code/b.cpp", notes="parent=?parent@@YAXXZ"),
    row("Code/b.cpp", notes=NOTES + ";object-symbol=$L1"),
    row("Code/gen_asm/b.cpp"), row("Code/gen_small/b.cpp"),
    row("Code/b.cpp", notes=NOTES + ";parent=?other@@YAXXZ"),
])
def test_unproven_or_same_source_duplicates_remain_refused(second):
    problems = []
    check_csv.check_functions(ledger(row(), second), problems,
                              {"Code/a.cpp", second["source"]}, b"")
    assert any("claims two addresses" in problem for problem in problems)


def test_external_names_remain_global_even_with_funclet_notes():
    assert ledger_io.same_function_name(row(name="?real@@YAXXZ"),
                                       row("Code/b.cpp", name="?real@@YAXXZ"))


def test_local_label_does_not_resolve_an_external_call(tmp_path, monkeypatch):
    monkeypatch.setattr(build, "build_call_thunks", lambda: {})
    monkeypatch.setattr(build, "load_all_function_rows", lambda: [
        dict(row(), target_rva="0x1000"),
        dict(row("Code/b.cpp"), target_rva="0x2000"),
        dict(row(name="?real@@YAXXZ", notes=""), target_rva="0x3000")])
    pins = tmp_path / "symbols.csv"
    pins.write_text("name,address,notes\n$L1893,0x4000,local fixture\n")
    monkeypatch.setattr(build, "SYMBOLS", pins)
    assert build.load_symbol_map() == {"?real@@YAXXZ": [0x3000]}


def test_both_repeated_labels_require_proof_and_ledger_changes_invalidate_cache(tmp_path, monkeypatch):
    (tmp_path / "reverse").mkdir()
    path = tmp_path / "reverse/functions.csv"
    monkeypatch.setattr(build, "ROOT", tmp_path)
    path.write_bytes(ledger(row()))
    assert not build.scoped_funclet_collision(row())
    path.write_bytes(ledger(row(), row("Code/b.cpp")))
    assert build.scoped_funclet_collision(row())
    assert build.scoped_funclet_collision(row("Code/b.cpp"))
    assert not build.scoped_funclet_collision(row(name="?real@@YAXXZ"))


@pytest.fixture
def admission(tmp_path, monkeypatch):
    (tmp_path / "reverse").mkdir()
    (tmp_path / "Code").mkdir()
    for source in ("a", "b"):
        (tmp_path / f"Code/{source}.cpp").write_text("// fixture\n")
    (tmp_path / "build.sh").write_text("fixture")
    (tmp_path / "reverse/functions.csv").write_bytes(ledger(row()))
    calls = []
    monkeypatch.setattr(add_match.subprocess, "run", lambda *args, **kwargs: (
        calls.append(args[0]), SimpleNamespace(returncode=0))[1])
    monkeypatch.setenv("BFME_CLAIMS", "off")
    return tmp_path, calls


def invoke(root, monkeypatch, source="Code/b.cpp", *extra):
    monkeypatch.setattr(sys, "argv", ["add_match.py", "$L1893", "0x2000", "8",
                                     source, "--notes", NOTES, "--root", str(root), *extra])
    add_match.main()


def test_single_admission_accepts_local_label_and_still_runs_byte_gate(admission, monkeypatch):
    root, calls = admission
    invoke(root, monkeypatch)
    assert len(add_match.parse_ledger((root / "reverse/functions.csv").read_bytes())) == 2
    assert len(calls) == 1 and calls[0][-1] == "Code/b.cpp"


def test_single_admission_refuses_same_tu_label(admission, monkeypatch):
    root, calls = admission
    with pytest.raises(SystemExit):
        invoke(root, monkeypatch, "Code/a.cpp")
    assert calls == []


def test_replacement_selects_only_the_requested_tu(admission, monkeypatch):
    root, calls = admission
    invoke(root, monkeypatch)
    invoke(root, monkeypatch, "Code/b.cpp", "--replace-existing")
    rows = add_match.parse_ledger((root / "reverse/functions.csv").read_bytes())
    assert [(item["source"], item["rva"]) for item in rows] == [
        ("Code/a.cpp", 0x1000), ("Code/b.cpp", 0x2000)]
    assert len(calls) == 2


def test_admission_rolls_back_if_parent_byte_gate_refuses(admission, monkeypatch):
    root, _ = admission
    original = (root / "reverse/functions.csv").read_bytes()
    monkeypatch.setattr(add_match.subprocess, "run", lambda *a, **k: SimpleNamespace(returncode=1))
    with pytest.raises(SystemExit):
        invoke(root, monkeypatch)
    assert (root / "reverse/functions.csv").read_bytes() == original


def test_batch_admission_uses_same_tu_scope(admission, monkeypatch):
    root, calls = admission
    manifest = root / "rows.csv"
    manifest.write_text(f"$L1893,0x2000,8,Code/b.cpp,{NOTES}\n")
    monkeypatch.setattr(sys, "argv", ["add_match_batch.py", str(manifest), "--root", str(root)])
    add_match_batch.main()
    assert len(calls) == 1


def test_batch_refuses_duplicate_labels_within_one_tu(admission, monkeypatch):
    root, calls = admission
    manifest = root / "rows.csv"
    manifest.write_text(f"$L1893,0x2000,8,Code/b.cpp,{NOTES}\n"
                        f"$L1893,0x3000,8,Code/b.cpp,{NOTES}\n")
    monkeypatch.setattr(sys, "argv", ["add_match_batch.py", str(manifest), "--root", str(root)])
    with pytest.raises(SystemExit):
        add_match_batch.main()
    assert calls == []


def test_local_names_do_not_relax_range_ownership():
    raw = ledger(row(), row("Code/b.cpp")).replace(b"0x1020", b"0x1004")
    problems = []
    check_csv.check_functions(raw, problems, {"Code/a.cpp", "Code/b.cpp"}, b"")
    assert any("overlap" in problem for problem in problems)


# ---------------------------------------------------------------------------
# The refusal has to teach the scoping rule, because the bare one-name message
# sent 140 workers to reverse/re_attempts.log instead. Every record in that
# cluster has peers that ARE proven labels, so the collision they hit was about
# their own notes; the message that named --replace-existing was pointing at the
# other TU's claim.

def hint(**over):
    identity = {"name": "$L1893", "source": "Code/b.cpp", "notes": NOTES}
    identity.update(over)
    return add_match.local_label_hint(identity, [row()])


def test_a_scoped_label_against_scoped_peers_gets_no_hint():
    """Nothing to explain: this one lands, which the admission test proves."""
    assert hint() is None


def test_a_same_source_duplicate_gets_no_hint():
    """A real duplicate, not a scoping question -- keep the plain refusal."""
    assert add_match.local_label_hint(
        {"name": "$L1893", "source": "Code/a.cpp", "notes": NOTES}, [row()]) is None


def test_an_external_name_gets_no_hint():
    assert add_match.local_label_hint(
        {"name": "?f@C@@QAEXXZ", "source": "Code/b.cpp", "notes": NOTES}, [row()]) is None


@pytest.mark.parametrize("over,wanted", [
    ({"notes": "parent=?parent@@YAXXZ"}, "`gen-funclet` token"),
    ({"notes": "gen-funclet"}, "`parent=<owner>`"),
    ({"notes": "gen-funclet;parent=?a@@YAXXZ;parent=?b@@YAXXZ"}, "found 2"),
    ({"notes": NOTES + ";object-symbol=$L1893"}, "object-symbol="),
    ({"source": "Code/gen_small/uw_gen_001.cpp"}, "generated tree"),
    ({"source": "reference/shims/x.cpp"}, "Code/**.cpp"),
])
def test_each_unmet_condition_is_named(over, wanted):
    message = hint(**over)
    assert message and wanted in message
    # never the advice that repoints the other TU's row
    assert "--replace-existing" in message and "do not reach for" in message


def test_an_unscoped_peer_is_identified_rather_than_blamed_on_the_notes():
    """The proposed row is fine; the row already holding the name is not."""
    message = add_match.local_label_hint(
        {"name": "$L1893", "source": "Code/b.cpp", "notes": NOTES},
        [{"name": "$L1893", "source": "Code/gen_small/uw_gen_001.cpp",
          "notes": NOTES + ";object-symbol=$L1893", "rva": 0x1000}])
    assert message and "already holding it is not itself a proven label" in message
    # names the source that needs the notes; the address is in the caller's line
    assert "Code/gen_small/uw_gen_001.cpp" in message
    assert "ledger_io.local_funclet" in message


def test_the_refusal_text_reaches_the_worker(admission, monkeypatch, capsys):
    """End to end: the admission that 140 records recorded, with the notes they
    were missing, now explains itself instead of suggesting --replace-existing."""
    root, calls = admission
    monkeypatch.setattr(sys, "argv", ["add_match.py", "$L1893", "0x2000", "8",
                                     "Code/b.cpp", "--notes", "parent=?parent@@YAXXZ",
                                     "--root", str(root)])
    with pytest.raises(SystemExit):
        add_match.main()
    error = capsys.readouterr().err
    assert "already in the ledger" in error and "`gen-funclet` token" in error
    assert "do not reach for --replace-existing" in error
    assert calls == []


def test_check_csv_duplicate_name_explains_a_label_collision():
    """check_csv reports the same collision add_match does, through the same
    rule, so it has to give the same explanation. 13 of the open check_csv
    false-reject records are $L labels whose peers are all already scoped.
    """
    # same label, two TUs, but the proposed row carries no scoping notes
    raw = ledger(row(), row("Code/b.cpp", notes=""))
    problems = []
    check_csv.check_functions(raw, problems, {"Code/a.cpp", "Code/b.cpp"}, b"")
    duplicate = [p for p in problems if "claims two addresses" in p]
    assert len(duplicate) == 1, problems
    assert "`gen-funclet` token" in duplicate[0]
    assert "One is wrong." not in duplicate[0]
    assert "0x00001000" in duplicate[0] and "0x00001020" in duplicate[0]


def test_check_csv_keeps_the_plain_message_for_an_external_name():
    raw = ledger(row(name="?f@C@@QAEXXZ", notes=""),
                 row("Code/b.cpp", name="?f@C@@QAEXXZ", notes=""))
    problems = []
    check_csv.check_functions(raw, problems, {"Code/a.cpp", "Code/b.cpp"}, b"")
    duplicate = [p for p in problems if "claims two addresses" in p]
    assert len(duplicate) == 1 and duplicate[0].endswith("One is wrong.")


def test_check_csv_still_accepts_two_properly_scoped_labels():
    raw = ledger(row(), row("Code/b.cpp"))
    problems = []
    check_csv.check_functions(raw, problems, {"Code/a.cpp", "Code/b.cpp"}, b"")
    assert not [p for p in problems if "claims two addresses" in p], problems
