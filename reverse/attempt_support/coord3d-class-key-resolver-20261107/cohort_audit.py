"""Read-only receipt/classification audit. No compile or build-cache mutation."""
import sys
sys.dont_write_bytecode = True
import collections
import csv
import hashlib
import json
import os
import subprocess
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import header_adopt_lane as hal
import header_dependents as hd

OUT = Path(__file__).resolve().parent
CANONICAL = "Code/Libraries/Include/Lib/Coord3D.h"
START = time.time()


def git(*args):
    return subprocess.check_output(["git", *args], cwd=ROOT).decode("utf-8", "replace").strip()


def digest(path):
    try:
        return hashlib.md5(Path(path).read_bytes()).hexdigest()
    except OSError:
        return None


def dep_identity(dep):
    p = Path(dep)
    p = p if p.is_absolute() else ROOT / p
    return os.path.normcase(os.path.normpath(str(p.absolute()))).replace("\\", "/").lower()


canonical_abs = dep_identity(CANONICAL)
head = git("rev-parse", "HEAD")
watched = ["reverse/functions.csv", "reverse/symbols.csv", "reverse/data_rows.csv",
           "reverse/data_converged.csv", CANONICAL]
hashes = {p: digest(ROOT / p) for p in watched}
dirty = {hd.norm(p) for p in git("diff", "--name-only", "HEAD", "--").splitlines() if p}
universe = set()
functions, pins, data, converged = [], [], [], []


def key_state(name):
    if "Coord3D" not in name:
        return None, None
    try:
        new = hal.rekey_symbol(name, "Coord3D", "U")
        return ("rename", new) if new != name else ("unchanged", None)
    except (ValueError, IndexError) as e:
        return "unsupported", f"{type(e).__name__}: {e}"


with (ROOT / "reverse/functions.csv").open(newline="", encoding="utf-8-sig") as f:
    for row in csv.DictReader(f):
        if row.get("source"):
            universe.add(row["source"])
        state, value = key_state(row["name"])
        if state in ("rename", "unsupported"):
            functions.append({"name": row["name"], "source": row["source"],
                              "rva": row["target_rva"], "state": state,
                              "new_or_error": value})
for leaf, output in [("symbols.csv", pins), ("data_rows.csv", data),
                     ("data_converged.csv", converged)]:
    with (ROOT / "reverse" / leaf).open(newline="", encoding="utf-8-sig") as f:
        for row in csv.DictReader(f):
            if leaf == "data_rows.csv" and row.get("source"):
                universe.add(row["source"])
            state, value = key_state(row["name"])
            if state in ("rename", "unsupported"):
                output.append({**row, "state": state, "new_or_error": value})
pin_rvas = {int(p["address"], 0) for p in pins}
providers = collections.defaultdict(set)
with (ROOT / "reverse/functions.csv").open(newline="", encoding="utf-8-sig") as f:
    for row in csv.DictReader(f):
        try:
            at = int(row["target_rva"], 0)
        except ValueError:
            continue
        if at in pin_rvas and row.get("status") == "matched" and row.get("source"):
            providers[at].add(row["source"])
for p in pins:
    p["source_candidates"] = sorted(providers[int(p["address"], 0)])

print("inventory", len(functions), "function", len(pins), "pin", len(data), "data", flush=True)
edges, macro = hd.scan(head)
broad = hd.dependents([CANONICAL], hd.graph(edges), macro) & universe
print("basename graph", len(broad), "ledger sources; reading receipts", flush=True)

# Keep only actual paths/metadata, not function ledgers. A missing normal
# receipt is unknown; it is not evidence that a source excludes the header.
raw = {}
raw_canonical = set()
for source in sorted(universe):
    try:
        meta = json.loads(hd.receipt_path(source).read_text(encoding="utf-8"))
    except (OSError, ValueError):
        continue
    if not isinstance(meta, dict) or not isinstance(meta.get("deps"), dict):
        continue
    raw[source] = meta
    if any(dep_identity(d) == canonical_abs for d in meta["deps"]):
        raw_canonical.add(source)
relevant = {r["source"] for r in functions + data if r.get("source")}
relevant |= {s for p in pins for s in p["source_candidates"]}
wanted = broad | relevant | raw_canonical
recorded = hd.receipts(wanted, dirty)
print("receipt API finished", len(wanted), "sources", flush=True)

definition_cache = {}


def definition(path):
    key = dep_identity(str(path))
    if key in definition_cache:
        return definition_cache[key]
    try:
        blob = Path(path).read_bytes()
    except OSError:
        definition_cache[key] = None
        return None
    if b"Coord3D" not in blob:
        definition_cache[key] = None
        return None
    span = hal.body_span(blob.decode("latin-1"), "Coord3D")
    found = None if span is None else {"path": str(path), "key": span[2],
                                      "line": blob[:span[0]].count(b"\n") + 1}
    definition_cache[key] = found
    return found


def stale_reason(source, meta, current):
    if current:
        return []
    if meta is None:
        return ["missing-or-unreadable-receipt"]
    reasons = []
    if meta.get("path") != source:
        reasons.append("receipt-source-path-mismatch")
    if hd.norm(source) in dirty:
        reasons.append("source-dirty-versus-HEAD")
    if meta.get("source") != digest(ROOT / source):
        reasons.append("source-hash-mismatch")
    for dep, expected in meta.get("deps", {}).items():
        p = Path(dep)
        p = p if p.is_absolute() else ROOT / p
        if not Path(dep).is_absolute() and hd.norm(dep) in dirty:
            reasons.append("dirty-dependency:" + dep)
        if expected is None or expected != digest(p):
            reasons.append("dependency-hash-mismatch:" + dep)
        if len(reasons) >= 5:
            break
    return reasons or ["receipt-API-rejected-schema-or-input"]


sources = {}
detail_sources = relevant | raw_canonical
for source in sorted(wanted):
    current, paths = recorded[source]
    meta = raw.get(source)
    canon = any(dep_identity(d) == canonical_abs for d in paths)
    info = {"receipt_current": current, "receipt_path": str(hd.receipt_path(source)),
            "recorded_canonical": canon, "in_basename_graph": source in broad,
            "has_key_record": source in relevant}
    if source in detail_sources:
        srcdef = definition(ROOT / source)
        depdefs = []
        if meta:
            for dep in meta.get("deps", {}):
                p = Path(dep)
                p = p if p.is_absolute() else ROOT / p
                if dep_identity(dep) == canonical_abs:
                    continue
                found = definition(p)
                if found:
                    depdefs.append(found)
        info.update(source_definition=srcdef, other_recorded_definitions=depdefs,
                    stale_reasons=stale_reason(source, meta, current),
                    object_exists=Path(str(hd.receipt_path(source)).removesuffix(".deps.json") + ".obj").exists())
        if current and canon:
            info["classification"] = "current-canonical-input"
            if srcdef or depdefs:
                info["definition_selection_warning"] = "canonical plus another textual definition; selected guard/scope not established"
        elif current and srcdef:
            info["classification"] = "current-private-source-definition"
        elif current and depdefs:
            info["classification"] = "current-noncanonical-seed-definition"
        elif current:
            info["classification"] = "current-no-canonical-or-definition-evidence"
        else:
            info["classification"] = "unknown-stale-or-missing-receipt"
    else:
        info["classification"] = ("current-canonical-input" if current and canon else
                                  "current-excludes-canonical" if current else
                                  "unknown-stale-or-missing-receipt")
    sources[source] = info

unsupported = [r for r in functions if r["state"] == "unsupported"]
current_canonical = sorted(s for s, x in sources.items() if x["receipt_current"] and x["recorded_canonical"])
unknown_broad = sorted(s for s in broad if not sources[s]["receipt_current"])
summary = {
    "HEAD": head, "ending_HEAD": git("rev-parse", "HEAD"),
    "input_hashes": hashes,
    "watched_inputs_unchanged": all(digest(ROOT / p) == h for p, h in hashes.items()),
    "seconds": round(time.time() - START, 2), "ledger_source_universe": len(universe),
    "function_records": dict(collections.Counter(r["state"] for r in functions)),
    "pin_records": dict(collections.Counter(r["state"] for r in pins)),
    "data_records": dict(collections.Counter(r["state"] for r in data)),
    "converged_records": dict(collections.Counter(r["state"] for r in converged)),
    "relevant_sources": len(relevant), "basename_graph_sources": len(broad),
    "raw_receipt_canonical_sources": len(raw_canonical),
    "current_canonical_sources": len(current_canonical),
    "current_canonical_outside_graph": [s for s in current_canonical if s not in broad],
    "unknown_basename_graph_sources": len(unknown_broad),
    "relevant_classification": dict(collections.Counter(sources[s]["classification"] for s in relevant)),
    "pin_ownerless": sum(not p["source_candidates"] for p in pins),
    "pin_multiple_source_candidates": sum(len(p["source_candidates"]) > 1 for p in pins),
}
result = {"summary": summary, "functions": functions, "pins": pins, "data": data,
          "converged": converged, "unsupported": unsupported, "sources": sources,
          "current_canonical_sources": current_canonical,
          "unknown_basename_graph_sources": unknown_broad}
(OUT / "cohort.json").write_text(json.dumps(result, indent=2), encoding="utf-8")
print(json.dumps(summary, indent=2), flush=True)
for row in unsupported:
    print("UNSUPPORTED", row["rva"], row["source"], json.dumps(sources[row["source"]]), flush=True)
