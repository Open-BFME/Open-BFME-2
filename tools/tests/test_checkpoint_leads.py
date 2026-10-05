"""Focused checkpoint discovery tests; synthetic retail, no builds or real claims."""
import csv
import hashlib
import json
from pathlib import Path
import sys

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import checkpoint_leads as leads
import check_boundary_checkpoint as checker


def record(entry="0x1000", ranges=None, evidence=None):
    ranges = ranges or [["0x1000", "0x1010"]]
    return {"entry": entry, "ranges": ranges,
            "body_bytes": sum(int(high, 16) - int(low, 16) for low, high in ranges),
            "batch": 1, "issues": [], "exits": [[ranges[-1][1], "recorded exit"]],
            "entry_evidence": evidence or {"kind": "code-pointer table", "source_rvas": ["0x3000"]},
            "retail_body_sha256": "filled by fixture"}


def row(low, high, status="matched", source="Code/Caller.cpp"):
    return {"low": low, "high": high, "size": high - low,
            "status": status, "source": source, "label": "Caller::method"}


def direct(entry="0x1000", sites=None):
    return record(entry, [[entry, hex(int(entry, 16) + 16)]],
                  {"entry": entry, "kind": "direct call", "source_entries": ["0x2000"],
                   "source_rvas": sites or ["0x2004"]})


@pytest.fixture
def checkpoint(tmp_path, monkeypatch):
    directory = tmp_path / "checkpoint"
    directory.mkdir()
    image = b"\x90" * 0x4000
    image_path = tmp_path / "image"
    image_path.write_bytes(image)
    monkeypatch.setattr(checker.build, "exe_image", lambda: (image, [
        {"rva": 0, "size": len(image), "raw_size": len(image), "raw_pointer": 0}]))
    monkeypatch.setattr(leads, "git", lambda *args: "a" * 40)
    monkeypatch.setattr(leads, "published_claims", lambda: (set(), []))
    ledger = tmp_path / "ledger.csv"
    inventory = tmp_path / "inventory.csv"

    def write(records, ledger_rows=(), inventory_rows=()):
        export, seeds = [], []
        for r in records:
            body = b"".join(image[low:high] for low, high in leads.segments(r))
            r["retail_body_sha256"] = hashlib.sha256(body).hexdigest()
            export.extend((int(r["entry"], 16), low, high) for low, high in leads.segments(r))
            seeds.append(f"{r['entry']}\t0\tboundary_rva_{int(r['entry'], 16):08x}\n")
        (directory / "validated-entries.jsonl").write_text(
            "".join(json.dumps(r) + "\n" for r in records))
        (directory / "seeds.tsv").write_text("".join(seeds))
        (directory / "batches.json").write_text('{"1": "historical evidence"}')
        (directory / "ranges.tsv").write_text(
            "entry_rva\tstart_rva\tend_exclusive\n" +
            "".join(f"{entry:#x}\t{low:#x}\t{high:#x}\n" for entry, low, high in sorted(export)))
        manifest = {"schema_version": 1, "baseline_sha256": hashlib.sha256(image).hexdigest(),
                    "text_start": "0x1000", "text_end_exclusive": "0x4000",
                    "added_entries": len(records), "added_ranges": len(export),
                    "added_body_bytes": sum(r["body_bytes"] for r in records),
                    "files": {p.name: leads.sha256(p) for p in directory.iterdir()
                              if p.name != "manifest.json"}}
        (directory / "manifest.json").write_text(json.dumps(manifest))
        with ledger.open("w", newline="") as stream:
            writer = csv.writer(stream)
            writer.writerow(["name", "target_rva", "target_size", "source", "status"])
            writer.writerows(ledger_rows)
        with inventory.open("w", newline="") as stream:
            writer = csv.writer(stream)
            writer.writerow(["rva", "size", "name"])
            writer.writerows(inventory_rows)
        return directory, ledger, inventory
    return write


def test_split_body_math_and_entry_is_not_segment_start(checkpoint):
    r = record("0x1010", [["0x1000", "0x1020"], ["0x1080", "0x1090"]])
    result = leads.discover(*checkpoint([r]))
    lead = result["leads"][0]
    assert lead["entry_rva"] == "0x1010"
    assert lead["segments"] == r["ranges"]
    assert lead["body_bytes"] == 48
    assert lead["bounding_span"] == {"start_rva": "0x1000", "end_exclusive": "0x1090", "bytes": 144}
    assert lead["exits"] == r["exits"]
    assert lead["provenance"]["batch"] == 1
    assert len(lead["provenance"]["record_sha256"]) == 64
    assert lead["retail_body_sha256"] == r["retail_body_sha256"]
    with pytest.raises(ValueError, match="segment starts are not entries"):
        leads.discover(*checkpoint([r]), entry=0x1080)
    with pytest.raises(ValueError, match="segment starts are not entries"):
        leads.discover(*checkpoint([r]), entry=0x1000)


@pytest.mark.parametrize("body,reason", [
    (row(0x1000, 0x1010), "already_matched"),
    (row(0x1000, 0x1008), "ledger_partial_or_interior_overlap"),
    (row(0xff0, 0x1008), "ledger_partial_or_interior_overlap"),
    (row(0x1008, 0x100c), "ledger_partial_or_interior_overlap"),
    (row(0x1000, 0x1010, "unmatched"), "ledger_partial_or_interior_overlap"),
])
def test_ledger_exact_partial_and_interior(body, reason):
    assert leads.classify(record(), [body], [], []) == reason


@pytest.mark.parametrize("body,reason", [
    (row(0x1000, 0x1010), None),
    (row(0x1000, 0x1020), "ghidra_conflicting_or_unproven_extent"),
    (row(0xff0, 0x1008), "ghidra_partial_or_interior_overlap"),
    (row(0x1008, 0x1010), "ghidra_partial_or_interior_overlap"),
])
def test_inventory_exact_conflicting_and_interior(body, reason):
    assert leads.classify(record(), [], [body], []) == reason


def test_split_inventory_sum_is_not_extent():
    r = record("0x1000", [["0x1000", "0x1010"], ["0x1080", "0x1090"]])
    assert leads.classify(r, [], [row(0x1000, 0x1020)], []) == "ghidra_conflicting_or_unproven_extent"
    # A body solely in a split body's hole is not claimed by that split body.
    assert leads.classify(r, [], [row(0x1040, 0x1050)], []) is None


def test_claim_range_before_entry_and_segment_claim():
    r = record("0x1010", [["0x1000", "0x1020"], ["0x1080", "0x1090"]])
    assert leads.classify(r, [], [], [(0xff0, 0x1001)]) == "published_claim_overlap"
    assert leads.classify(r, [], [], [(0x1088, 0x1089)]) == "published_claim_overlap"
    assert leads.classify(r, [], [], [(0x1040, 0x1050)]) is None
    expanded = leads.expand_claims({0x1010}, [r], [], [])
    assert expanded == [(0x1000, 0x1020), (0x1080, 0x1090)]


def test_unclaimed_caller_ground_and_callback_do_not_promote():
    assert leads.matched_callers(direct(), []) == []
    assert leads.matched_callers(direct(), [row(0x2000, 0x2010, "unmatched")]) == []
    assert leads.matched_callers(direct(sites=["0x2050"]), [row(0x2000, 0x2010)]) == []
    callback = record(evidence={"kind": "callback constructor argument",
                                "source_entries": ["0x2000"], "source_rvas": ["0x2004"]})
    assert leads.matched_callers(callback, [row(0x2000, 0x2010)]) == []


def test_valid_anonymous_direct_call_priority_and_stream_filter(checkpoint):
    args = checkpoint([record(), direct("0x1100")],
                      [("Caller", "0x2000", 16, "Code/Caller.cpp", "matched"),
                       ("Irrelevant", "0x3500", 16, "Code/Other.cpp", "matched")])
    result = leads.discover(*args, limit=1)
    assert result["eligible_entries"] == 2
    assert len(result["leads"]) == 1
    lead = result["leads"][0]
    assert lead["entry_rva"] == "0x1100"
    assert lead["identity"] == "anonymous"
    assert lead["matched_direct_callers"][0]["caller_rva"] == "0x2000"
    assert lead["matched_direct_callers"][0]["ledger_source"] == "Code/Caller.cpp"
    assert result["retail_byte_gain"] == 0
    assert result["integrity"]["original_map_overlap"] == "not checked"
    assert leads.stream_rows(args[1], leads.Windows([(0x2004, 0x2005)]), True) == [
        {"low": 0x2000, "high": 0x2010, "size": 16, "label": "Caller",
         "source": "Code/Caller.cpp", "status": "matched"}]


def test_corrupt_records_withhold_output(checkpoint):
    args = checkpoint([record()])
    path = args[0] / "validated-entries.jsonl"
    path.write_text(path.read_text().replace('"batch": 1', '"batch": 2'))
    with pytest.raises(ValueError, match="Artifact hash mismatch"):
        leads.discover(*args)


def test_corrupt_image_withhold_output(checkpoint, monkeypatch):
    args = checkpoint([record()])
    image, sections = checker.build.exe_image()
    monkeypatch.setattr(checker.build, "exe_image", lambda: (b"\xcc" + image[1:], sections))
    with pytest.raises(ValueError, match="Retail image hash mismatch"):
        leads.discover(*args)


def test_bad_shape_with_updated_artifact_hash_is_rejected(checkpoint):
    args = checkpoint([record()])
    path = args[0] / "validated-entries.jsonl"
    data = json.loads(path.read_text())
    data["body_bytes"] += 1
    path.write_text(json.dumps(data) + "\n")
    manifest_path = args[0] / "manifest.json"
    manifest = json.loads(manifest_path.read_text())
    manifest["files"][path.name] = leads.sha256(path)
    manifest_path.write_text(json.dumps(manifest))
    with pytest.raises(ValueError, match="Size mismatch"):
        leads.discover(*args)


def test_missing_artifact_and_claim_failure_are_not_fallbacks(checkpoint, monkeypatch):
    args = checkpoint([record()])
    (args[0] / "batches.json").unlink()
    with pytest.raises(FileNotFoundError):
        leads.discover(*args)
    args = checkpoint([record()])
    def fail():
        raise ValueError("claims unavailable")
    monkeypatch.setattr(leads, "published_claims", fail)
    with pytest.raises(ValueError, match="claims unavailable"):
        leads.discover(*args)


@pytest.mark.parametrize("limit", [0, -1, 101])
def test_limit_bounded(checkpoint, limit):
    with pytest.raises(ValueError, match="--limit"):
        leads.discover(*checkpoint([record()]), limit=limit)


def test_reject_unordered_segments():
    with pytest.raises(ValueError, match="ordered and disjoint"):
        leads.segments(record("0x1000", [["0x1080", "0x1090"], ["0x1000", "0x1010"]]))


def test_required_artifact_hash_cannot_be_silently_omitted(checkpoint):
    args = checkpoint([record()])
    path = args[0] / "manifest.json"
    manifest = json.loads(path.read_text())
    del manifest["files"]["validated-entries.jsonl"]
    path.write_text(json.dumps(manifest))
    with pytest.raises(ValueError, match="omits required"):
        leads.discover(*args)


def test_entry_withheld_reports_claim_reason(checkpoint, monkeypatch):
    args = checkpoint([record()])
    monkeypatch.setattr(leads, "published_claims", lambda: ({0x1008}, []))
    result = leads.discover(*args, entry=0x1000)
    assert result["leads"] == []
    assert result["entry_withheld_reason"] == "published_claim_overlap"


def test_input_changed_during_discovery_refuses_output(checkpoint, monkeypatch):
    args = checkpoint([record()])
    def changing_claims():
        (args[0] / "batches.json").write_text("changed mid-run")
        return set(), []
    monkeypatch.setattr(leads, "published_claims", changing_claims)
    with pytest.raises(ValueError, match="Inputs changed"):
        leads.discover(*args)


def test_cli_integrity_failure_has_no_stdout(monkeypatch, capsys):
    def fail(*args):
        raise ValueError("Retail image hash mismatch")
    monkeypatch.setattr(leads, "discover", fail)
    assert leads.main(["--limit", "1"]) == 1
    captured = capsys.readouterr()
    assert captured.out == ""
    assert "refusing output: Retail image hash mismatch" in captured.err


def test_remote_claim_read_is_read_only_and_expired_refs_are_conservative(monkeypatch):
    import subprocess
    calls = []
    monkeypatch.setenv("BFME_CLAIM_NS", "refs/claims/")
    monkeypatch.setenv("BFME_CLAIM_REMOTE", "origin")
    monkeypatch.setattr(leads.subprocess, "run", lambda *args, **kwargs:
                        subprocess.CompletedProcess(args[0], 1, "", ""))
    def remote(*args):
        calls.append(args)
        return "deadbeef\trefs/claims/0x00001008\nbeefdead\trefs/claims/class/X"
    monkeypatch.setattr(leads, "git", remote)
    addresses, receipts = leads.published_claims()
    assert addresses == {0x1008}
    assert calls == [("ls-remote", "--refs", "origin", "refs/claims/*")]
    assert receipts[0]["remote"] == "origin"


def test_unknown_entry_does_not_select_containing_segment(checkpoint):
    args = checkpoint([record()])
    with pytest.raises(ValueError, match="Requested entry is absent"):
        leads.discover(*args, entry=0x1004)


def test_touching_ranges_do_not_overlap():
    assert leads.classify(record(), [row(0xff0, 0x1000), row(0x1010, 0x1020)], [], []) is None
    windows = leads.Windows([(0x1000, 0x1010), (0x1080, 0x1090)])
    assert not windows.intersects(0xff0, 0x1000)
    assert not windows.intersects(0x1010, 0x1080)
    assert windows.intersects(0xff0, 0x1001)


def test_record_receipt_hashes_exact_bytes_including_crlf(checkpoint):
    args = checkpoint([record()])
    path = args[0] / "validated-entries.jsonl"
    raw = path.read_bytes().replace(b"\n", b"\r\n")
    path.write_bytes(raw)
    manifest_path = args[0] / "manifest.json"
    manifest = json.loads(manifest_path.read_text())
    manifest["files"][path.name] = leads.sha256(path)
    manifest_path.write_text(json.dumps(manifest))
    result = leads.discover(*args)
    assert result["leads"][0]["provenance"]["record_sha256"] == hashlib.sha256(raw).hexdigest()
