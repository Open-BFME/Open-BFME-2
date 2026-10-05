#!/usr/bin/env python3
"""Opt-in, read-only discovery from accepted anonymous checkpoint boundaries.

No identities, ledger rows, seeds, or canonical inventory updates are generated.
Integrity/decoding is checked in full before selection, even with --entry.
Historical entry/CFG proofs are recorded evidence, not re-proved here. Published
body claims are conservatively withheld even if expired: reading remote refs
needs no fetch or local writes. Unknown claim extents protect their address;
known checkpoint/ledger/inventory extents protect their recorded ranges too.
"""
import argparse
from bisect import bisect_left
from collections import Counter
from contextlib import redirect_stdout
import csv
import hashlib
import io
import json
import os
from pathlib import Path
import subprocess
import sys
import time

ROOT = Path(__file__).resolve().parents[1]
DEFAULT_CHECKPOINT = ROOT / "reverse/boundary-checkpoints/2026-09-27"


def sha256(path):
    with path.open("rb") as stream:
        return hashlib.file_digest(stream, "sha256").hexdigest()


def require(condition, message):
    if not condition:
        raise ValueError(message)


def segments(record):
    result = tuple((int(low, 16), int(high, 16)) for low, high in record["ranges"])
    require(bool(result), "Empty checkpoint body")
    require(all(low < high for low, high in result), "Invalid checkpoint segment")
    require(all(left[1] <= right[0] for left, right in zip(result, result[1:])),
            "Checkpoint segments must be ordered and disjoint")
    entry = int(record["entry"], 16)
    require(any(low <= entry < high for low, high in result), "Entry outside segments")
    require(sum(high - low for low, high in result) == record["body_bytes"],
            "Checkpoint body byte count differs from segments")
    return result


def direct_evidence(record):
    evidence = record.get("entry_evidence", {})
    return evidence if evidence.get("kind") == "direct call" else {}


class Windows:
    """Merged query windows; retain only intersecting rows from streamed CSVs."""
    def __init__(self, intervals):
        merged = []
        for low, high in sorted(intervals):
            if merged and low <= merged[-1][1]:
                merged[-1] = (merged[-1][0], max(high, merged[-1][1]))
            else:
                merged.append((low, high))
        self.ranges = merged
        self.ends = [high for _, high in merged]

    def intersects(self, low, high):
        index = bisect_left(self.ends, low + 1)
        return index < len(self.ranges) and self.ranges[index][0] < high


def stream_rows(path, windows, ledger=False):
    """Do not materialize the large ledger/inventory; labels stay source labels."""
    retained = []
    csv.field_size_limit(10_000_000)
    with path.open(encoding="utf-8", newline="") as stream:
        reader = csv.DictReader(stream)
        needed = ({"target_rva", "target_size", "source", "status", "name"}
                  if ledger else {"rva", "size", "name"})
        require(needed <= set(reader.fieldnames or []), f"Invalid CSV header: {path}")
        for row in reader:
            low = int(row["target_rva" if ledger else "rva"], 16)
            size = int(row["target_size" if ledger else "size"] or "0")
            require(size >= 0, f"Negative body size in {path}")
            # Zero-size declarations still protect their exact start.
            high = low + max(size, 1)
            if windows.intersects(low, high):
                retained.append({"low": low, "high": high, "size": size,
                                 "label": row["name"],
                                 "source": row.get("source"),
                                 "status": row.get("status")})
    return retained


def overlaps(body, row):
    return any(low < row["high"] and row["low"] < high for low, high in body)


def classify(record, ledger, inventory, claimed_ranges):
    body, entry = segments(record), int(record["entry"], 16)
    hit = [row for row in ledger if overlaps(body, row)]
    if hit:
        exact = (len(body) == 1 and all((row["low"], row["high"]) == body[0]
                 and row["low"] == entry and row["status"] == "matched" for row in hit))
        return "already_matched" if exact else "ledger_partial_or_interior_overlap"
    if any(low < end and start < high for low, high in body
           for start, end in claimed_ranges):
        return "published_claim_overlap"
    for row in inventory:
        if row["low"] == entry:
            # CSV size is insufficient to corroborate a noncontiguous extent.
            if len(body) != 1 or (row["low"], row["high"]) != body[0]:
                return "ghidra_conflicting_or_unproven_extent"
        elif overlaps(body, row):
            return "ghidra_partial_or_interior_overlap"
    return None


def matched_callers(record, ledger):
    """Only explicit recorded caller entries with matched current ledger bodies."""
    evidence = direct_evidence(record)
    entries = {int(value, 16) for value in evidence.get("source_entries", [])}
    sites = {int(value, 16) for value in evidence.get("source_rvas", [])}
    result = []
    for row in ledger:
        if row["status"] != "matched" or row["low"] not in entries:
            continue
        calls = sorted(site for site in sites if row["low"] <= site < row["high"])
        if calls:
            result.append({"caller_rva": hex(row["low"]),
                           "call_site_rvas": [hex(site) for site in calls],
                           "ledger_source": row["source"], "ledger_label": row["label"],
                           "basis": "recorded direct call from a currently matched ledger body; "
                                    "identity lead only, not callee semantic proof"})
    return sorted(result, key=lambda caller: (int(caller["caller_rva"], 16),
                                             caller["ledger_label"]))


def expand_claims(addresses, records, ledger, inventory):
    ranges = [(address, address + 1) for address in addresses]
    for record in records:
        if int(record["entry"], 16) in addresses:
            ranges.extend(segments(record))
    for row in ledger + inventory:
        if row["low"] in addresses:
            ranges.append((row["low"], row["high"]))
    return Windows(ranges).ranges


def git(*args):
    return subprocess.run(["git", *args], cwd=ROOT, check=True,
                          capture_output=True, text=True, timeout=30).stdout.strip()


def published_claims():
    """No fetch, claim creation, expiry guesses, or network-failure fallback."""
    namespace = os.environ.get("BFME_CLAIM_NS")
    if not namespace:
        config = subprocess.run(["git", "config", "--get", "bfme.claimNamespace"],
                                cwd=ROOT, capture_output=True, text=True, timeout=10)
        require(config.returncode in (0, 1), "Cannot read claim namespace")
        namespace = config.stdout.strip() or "refs/claims/"
    remote = os.environ.get("BFME_CLAIM_REMOTE", "origin")
    mirror = subprocess.run(["git", "config", "--get", "bfme.claimMirror"],
                            cwd=ROOT, capture_output=True, text=True, timeout=10)
    require(mirror.returncode in (0, 1), "Cannot read claim mirror")
    queries = [(remote, namespace)]
    if mirror.stdout.strip():
        queries.append((mirror.stdout.strip(), "refs/claims/"))
    addresses, receipts = set(), []
    for remote, prefix in queries:
        text = git("ls-remote", "--refs", remote, prefix + "*")
        receipts.append({"remote": remote, "namespace": prefix,
                         "refs_sha256": hashlib.sha256(text.encode()).hexdigest()})
        for line in text.splitlines():
            _, ref = line.split("\t")
            suffix = ref[len(prefix):]
            if suffix.startswith("0x"):
                addresses.add(int(suffix, 16))
    return addresses, receipts


def load_records(directory):
    records = []
    with (directory / "validated-entries.jsonl").open("rb") as stream:
        for number, line in enumerate(stream, 1):
            record = json.loads(line)
            segments(record)
            records.append((record, {"record_line": number,
                                     "record_sha256": hashlib.sha256(line).hexdigest()}))
    return records


def integrity_check(directory, baseline_ranges=None):
    # Import only the supported checker; never compile or write the object cache.
    import check_boundary_checkpoint
    output = io.StringIO()
    start = time.monotonic()
    with redirect_stdout(output):
        check_boundary_checkpoint.check(directory, baseline_ranges)
    return {"seconds": round(time.monotonic() - start, 6),
            "checker": "tools/check_boundary_checkpoint.py",
            "checker_sha256": sha256(ROOT / "tools/check_boundary_checkpoint.py"),
            "result": output.getvalue().strip(),
            "semantic_cfg_proofs": "historical recorded evidence; not rerun",
            "original_map_overlap": "checked" if baseline_ranges else "not checked"}


def discover(directory, ledger_path, inventory_path, limit=10, entry=None,
             baseline_ranges=None):
    require(1 <= limit <= 100, "--limit must be between 1 and 100")
    directory = directory.resolve()
    head = git("rev-parse", "HEAD")
    manifest_path = directory / "manifest.json"
    initial_manifest = json.loads(manifest_path.read_text(encoding="utf-8"))
    required_files = {"validated-entries.jsonl", "ranges.tsv", "seeds.tsv", "batches.json"}
    require(required_files <= set(initial_manifest["files"]),
            "Checkpoint manifest omits required evidence artifact hashes")
    require(all(Path(name).name == name for name in initial_manifest["files"]),
            "Manifest paths must be simple filenames")
    paths = {"manifest": manifest_path,
             "records": directory / "validated-entries.jsonl",
             "ledger": ledger_path, "inventory": inventory_path}
    paths.update({"artifact:" + name: directory / name
                  for name in initial_manifest["files"]})
    # Hash all inputs before and after: fail if another seat changes them mid-run.
    digests = {key: sha256(path) for key, path in paths.items()}
    checked = integrity_check(directory, baseline_ranges)
    manifest = json.loads(paths["manifest"].read_text(encoding="utf-8"))
    all_records = load_records(directory)
    selected = [(record, receipt) for record, receipt in all_records
                if entry is None or int(record["entry"], 16) == entry]
    require(bool(selected), "Requested entry is absent (segment starts are not entries)")
    windows = Windows([interval for record, _ in selected for interval in segments(record)] +
                      [(int(site, 16), int(site, 16) + 1) for record, _ in selected
                       for site in direct_evidence(record).get("source_rvas", [])] +
                      [(int(start, 16), int(start, 16) + 1) for record, _ in selected
                       for start in direct_evidence(record).get("source_entries", [])])
    ledger = stream_rows(ledger_path, windows, ledger=True)
    inventory = stream_rows(inventory_path, windows)
    addresses, claim_receipts = published_claims()
    claims = expand_claims(addresses, [r for r, _ in all_records], ledger, inventory)
    leads, withheld = [], Counter()
    selected_reason = None
    for record, receipt in selected:
        reason = classify(record, ledger, inventory, claims)
        if reason:
            withheld[reason] += 1
            selected_reason = reason
            continue
        body = segments(record)
        callers = matched_callers(record, ledger)
        leads.append({"entry_rva": record["entry"], "identity": "anonymous",
                      "segments": record["ranges"], "body_bytes": record["body_bytes"],
                      "bounding_span": {"start_rva": hex(body[0][0]),
                                        "end_exclusive": hex(body[-1][1]),
                                        "bytes": body[-1][1] - body[0][0]},
                      "exits": record["exits"],
                      "retail_body_sha256": record["retail_body_sha256"],
                      "provenance": {"source": str(paths["records"]),
                                     "source_sha256": digests["records"],
                                     "batch_source": str(directory / "batches.json"),
                                     "batch_source_sha256": digests["artifact:batches.json"],
                                     "manifest_sha256": digests["manifest"],
                                     "batch": record["batch"], **receipt,
                                     "recorded_evidence": {key: value for key, value in record.items()
                                         if key in ("entry_evidence", "evidence", "evidence_rvas",
                                                    "kind", "registrations", "tail_evidence")}},
                      "matched_direct_callers": callers,
                      "priority": "matched_direct_caller" if callers else "anonymous_boundary",
                      "inventory_labels": [row["label"] for row in inventory
                                           if row["low"] == int(record["entry"], 16)],
                      "identity_caution": "Checkpoint evidence establishes historical target "
                                          "boundaries/references; source and inventory labels "
                                          "do not establish this callee's name or semantics."})
    leads.sort(key=lambda lead: (not bool(lead["matched_direct_callers"]),
                                 int(lead["entry_rva"], 16)))
    require(head == git("rev-parse", "HEAD"), "HEAD changed during discovery; retry")
    require(digests == {key: sha256(path) for key, path in paths.items()},
            "Inputs changed during discovery; retry")
    return {"head": head, "input_sha256": digests,
            "checkpoint_artifact_sha256": manifest["files"],
            "image_sha256": manifest["baseline_sha256"], "integrity": checked,
            "filtered_csv_rows": {"ledger": len(ledger), "inventory": len(inventory)},
            "claims": {"policy": "all published body refs withheld, including expired refs; "
                                  "unknown extents protect their RVA only", "receipts": claim_receipts},
            "selected_entries": len(selected), "eligible_entries": len(leads),
            "withheld": dict(sorted(withheld.items())),
            "entry_withheld_reason": selected_reason if entry is not None else None,
            "leads": leads[:limit], "retail_byte_gain": 0,
            "scope": "Discovery only; no identities, semantic proofs, or ledger rows generated."}


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--checkpoint", type=Path, default=DEFAULT_CHECKPOINT)
    parser.add_argument("--limit", type=int, default=10, help="Maximum leads, 1..100 (default 10)")
    parser.add_argument("--entry", type=lambda value: int(value, 16), help="Exact entry RVA only")
    parser.add_argument("--baseline-ranges", type=Path,
                        help="Optional original range export; existing checker verifies its hash")
    args = parser.parse_args(argv)
    try:
        result = discover(args.checkpoint, ROOT / "reverse/functions.csv",
                          ROOT / "reverse/ghidra_functions.csv", args.limit, args.entry,
                          args.baseline_ranges)
    except (OSError, ValueError, KeyError, TypeError, ImportError, subprocess.SubprocessError) as exc:
        print(f"checkpoint_leads: refusing output: {exc}", file=sys.stderr)
        return 1
    print(json.dumps(result, indent=2))
    return 0


if __name__ == "__main__":
    sys.exit(main())
