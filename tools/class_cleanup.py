"""Unused private-class discovery/application, served by class_views --unused.

Discovery is not verification. Cache the existing conservative pruner's result
by source contents, current reachable macro tokens and implementation version.
Application takes fresh file claims and retains normal byte/data checks plus
an exact comparison of compiled runtime contents and bindings.
"""
import collections
import copy
import hashlib
import json
import struct
import subprocess
import sys
import time
from pathlib import Path

import claims
import class_layouts
import picker_cache
import tu_skeleton

ROOT = Path(__file__).resolve().parents[1]
RESULTS = picker_cache.FileMemo("unused-private-classes", [__file__, tu_skeleton.__file__, class_layouts.__file__])
POTENTIAL = picker_cache.FileMemo("unused-private-class-potential", RESULTS.code)
MAX_BATCH = 25


def source_path(source, root):
    path = (Path(root) / source).resolve()
    if not path.is_relative_to((Path(root) / "Code").resolve()):
        raise ValueError(f"not a Code source: {source}")
    return path


def prepare(source, root=ROOT, refresh=False):
    """Current proposal and its original/desired bytes; None for a safe no-op."""
    raw = source_path(source, root).read_bytes()
    text = raw.decode("latin-1")
    considered = []
    def possible():
        considered.append(True)
        return tu_skeleton.prune_unused_classes(text, source, Path(root), macros=set()) != text
    # Macro protection can only retain additional declarations. If even an
    # empty protection set removes nothing, no include scan is necessary.
    potential = possible() if refresh else POTENTIAL.get(picker_cache.text_key(text), possible)
    if not potential:
        return None, bool(considered)
    # This dependency must be read afresh even on negative cache hits: a header
    # macro can turn a previously unused declaration into a required one.
    macros = tu_skeleton.extern_macro_tokens(text, source, Path(root))
    key = picker_cache.text_key(text) + ":" + hashlib.sha256(
        json.dumps(None if macros is None else sorted(macros)).encode()).hexdigest()
    computed = []
    def compute():
        computed.append(True)
        after = tu_skeleton.prune_unused_classes(text, source, Path(root), macros=macros) if macros is not None else text
        if after == text:
            return None
        removed = sorted(set(class_layouts.class_bodies(text)) - set(class_layouts.class_bodies(after)))
        return {"after": after, "removed": removed}
    result = compute() if refresh else RESULTS.get(key, compute)
    if result is None:
        return None, bool(computed)
    after = result["after"].encode("latin-1")
    return {"source": source, "sha256": hashlib.sha256(raw).hexdigest(),
            "removed": result["removed"], "removed_count": len(result["removed"]),
            "removed_bytes": len(raw) - len(after), "_before": raw, "_after": after}, bool(computed)


def ranked_sources(under="Code", files=None, root=ROOT):
    """Cheap textual ranking only; the real pruner still decides every removal."""
    root = Path(root)
    under = under.replace("\\", "/").rstrip("/")
    source_path(under + "/_" if under == "Code" else under, root)
    eligible = {r["source"] for r in picker_cache.ledger_rows(root / "reverse/functions.csv")
                if r.get("status") == "matched" and r.get("source", "").lower().endswith((".cpp", ".c"))
                and not r["source"].startswith(("Code/gen_asm/", "Code/gen_small/"))
                and (r["source"] == under or r["source"].startswith(under + "/"))}
    if files is not None:
        selected = list(dict.fromkeys(files))
        if set(selected) - eligible:
            raise ValueError("not matched authored sources in scope: " + ", ".join(sorted(set(selected) - eligible)))
        return selected
    done = subprocess.run(["git", "grep", "-z", "-c", "-E", r"(class|struct)[[:space:]]+[A-Za-z_]", "--", under],
                          cwd=root, capture_output=True)
    if done.returncode not in (0, 1):
        raise RuntimeError(done.stderr.decode(errors="replace"))
    ranked, pos = [], 0
    while pos < len(done.stdout):
        end = done.stdout.index(b"\0", pos)
        source = done.stdout[pos:end].decode("utf-8", errors="surrogateescape")
        pos = done.stdout.index(b"\n", end)
        count = int(done.stdout[end + 1:pos])
        pos += 1
        if source in eligible:
            ranked.append((-count, source))
    return [source for _, source in sorted(ranked)]


def discover(under="Code", files=None, scan_limit=350, root=ROOT):
    started = time.perf_counter()
    sources = ranked_sources(under, files, root)
    if scan_limit:
        sources = sources[:scan_limit]
    candidates, computed, hits = [], 0, 0
    for source in sources:
        proposal, fresh = prepare(source, root)
        computed += fresh
        hits += not fresh
        if proposal:
            candidates.append(proposal)
    candidates.sort(key=lambda p: (-p["removed_count"], -p["removed_bytes"], p["source"]))
    RESULTS.save()
    POTENTIAL.save()
    return {"candidates": candidates, "scanned": len(sources), "computed": computed,
            "cache_hits": hits, "cache": str(picker_cache.cache_dir(str(root))),
            "discovery_seconds": time.perf_counter() - started}


def runtime_graph(obj):
    """All non-debug COFF bytes/relocations, providers, weak defaults and COMDAT policies."""
    build = class_layouts.build_module()
    obj = Path(obj)
    stat = obj.stat()
    data, sections, symbols = build._object_layout(str(obj), stat.st_mtime_ns, stat.st_size)
    kept = [i + 1 for i, section in enumerate(sections) if not section["name"].startswith(".debug")]
    indices = {v: i for i, v in enumerate(kept)}
    selections, weak, external = {}, {}, {}
    table, count = struct.unpack_from("<II", data, 8)
    i = 0
    while i < count:
        offset = table + i * 18
        symbol = symbols[i]
        aux = data[offset + 17]
        section = symbol["section"]
        if symbol["storage"] == 105:
            if not aux:
                raise ValueError("weak external has no auxiliary record")
            target, kind = struct.unpack_from("<II", data, offset + 18)
            weak[symbol["name"]] = [symbols[target]["name"], kind]
        if section in indices:
            if symbol["storage"] == 2:
                external[symbol["name"]] = [indices[section], symbol["value"], symbol["type"]]
            if symbol["storage"] == 3 and symbol["type"] == 0 and aux and symbol["name"] == sections[section - 1]["name"]:
                selection = data[offset + 32]
                associated = struct.unpack_from("<H", data, offset + 30)[0]
                selections[indices[section]] = [selection, indices.get(associated) if selection == 5 else None]
        i += 1 + aux
    result = []
    for index in kept:
        section = sections[index - 1]
        if section["reloc_count"] == 65535:
            raise ValueError("overflow relocation table requires a dedicated reader")
        relocs = []
        for j in range(section["reloc_count"]):
            offset, target_index, kind = struct.unpack_from("<IIH", data, section["reloc_pointer"] + j * 10)
            target = symbols[target_index]
            target_section = target["section"]
            if target_section in indices:
                binding = ["defined", indices[target_section], target["value"]]
                if target["storage"] == 2:
                    binding.append(target["name"])
            elif target_section == 0:
                binding = ["external", target["name"], target["storage"], target["type"]]
            elif target_section < 0:
                binding = ["special", target_section, target["name"], target["value"]]
            else:
                raise ValueError("runtime reference into a debug section")
            relocs.append([offset, kind, binding])
        raw = data[section["raw_pointer"]:section["raw_pointer"] + section["raw_size"]] if section["raw_pointer"] else b""
        result.append({"name": section["name"], "size": section["raw_size"],
                       "characteristics": section["characteristics"], "sha256": hashlib.sha256(raw).hexdigest(),
                       "relocs": relocs, "comdat": selections.get(indices[index])})
    return {"sections": result, "extern_definitions": external, "weak": weak}


def same_runtime(before, after):
    """Exact equality under a bijective renumbering of externally named sections."""
    if before == after:
        return True
    if len(before["sections"]) != len(after["sections"]):
        return False
    def anchors(graph):
        groups = collections.defaultdict(list)
        for name, (section, offset, kind) in graph["extern_definitions"].items():
            groups[section].append((name, offset, kind))
        return {i: tuple(sorted(names)) for i, names in groups.items()}
    old, new = anchors(before), anchors(after)
    old_keys = {key: i for i, key in old.items()}
    if len(old_keys) != len(old) or set(old.values()) != set(new.values()):
        return False
    mapping = {i: old_keys[key] for i, key in new.items()}
    for i in range(len(after["sections"])):
        mapping.setdefault(i, i)  # anonymous sections must retain their positions
    if set(mapping.values()) != set(range(len(before["sections"]))):
        return False
    normalized = copy.deepcopy(after)
    for value in normalized["extern_definitions"].values():
        value[0] = mapping[value[0]]
    reordered = [None] * len(normalized["sections"])
    for index, section in enumerate(normalized["sections"]):
        for _, _, target in section["relocs"]:
            if target[0] == "defined":
                target[1] = mapping[target[1]]
        if section["comdat"] and section["comdat"][1] is not None:
            section["comdat"][1] = mapping[section["comdat"][1]]
        reordered[mapping[index]] = section
    normalized["sections"] = reordered
    return normalized == before


def verify(sources):
    import header_adopt_lane
    return header_adopt_lane.gate_many(sources)


def snapshot(source):
    return runtime_graph(class_layouts.build_module().obj_path(source))


def frozen(sources, root):
    if not sources:
        return {}
    done = subprocess.run([sys.executable, "tools/find_declared_unmatched.py", "--fail", *sources],
                          cwd=root, capture_output=True, text=True, errors="replace")
    text = (done.stdout + done.stderr).replace("\\", "/")
    if not done.returncode:
        return {}
    found = {s: text for s in sources if any(line.startswith(s + ":") for line in text.splitlines())}
    if not found:
        raise RuntimeError("declaration check failed without a per-source verdict: " + text)
    return found


def apply(candidates, limit=MAX_BATCH, root=ROOT):
    """Keep only individually verified, runtime-identical edits; never commit or push."""
    started = time.perf_counter()
    limit = min(limit, MAX_BATCH)
    keys = ["file:" + p["source"] for p in candidates]
    available = claims.claimable(keys, root=root)
    rejected = {p["source"]: "held by another worker" for p in candidates
                if available[claims.key_of("file:" + p["source"])]}
    picked = [p for p in candidates if p["source"] not in rejected][:limit]
    if not picked:
        return {"applied": [], "rejected": rejected, "apply_seconds": time.perf_counter() - started}
    sources = [p["source"] for p in picked]
    status = subprocess.run(["git", "status", "--porcelain=v1", "-z", "--", *sources],
                            cwd=root, check=True, capture_output=True, text=True).stdout
    dirty = {record[3:] for record in status.split("\0") if len(record) > 3}
    rejected.update({s: "source has existing staged or unstaged edits" for s in dirty})
    rejected.update(frozen([s for s in sources if s not in rejected], root))
    picked = [p for p in picked if p["source"] not in rejected]
    if not picked:
        return {"applied": [], "rejected": rejected, "apply_seconds": time.perf_counter() - started}
    acquired = claims.acquire(["file:" + p["source"] for p in picked], root=root, note="unused private class cleanup")
    expected = {claims.key_of("file:" + p["source"]) for p in picked}
    if acquired.refused or not expected.issubset(acquired.claimed):
        raise RuntimeError("claim race; no source changed: " + str(acquired.refused))
    fresh = set(acquired.claimed) - set(acquired.prior)
    originals, written, applied = {}, {}, []
    def restore(source):
        path = source_path(source, root)
        if path.read_bytes() != written[source]:
            raise RuntimeError("source changed during verification; preserving edits: " + source)
        path.write_bytes(originals[source])
        del written[source]
    try:
        ready = []
        for proposal in picked:
            source = proposal["source"]
            # Never authorize writes from a saved discovery result. Recompute
            # the exact conservative transformation for the selected files.
            current, _ = prepare(source, root, refresh=True)
            if not current or current["sha256"] != proposal["sha256"] or current["_after"] != proposal["_after"]:
                rejected[source] = "source or include/macro dependencies changed; rediscover"
            else:
                ready.append(current)
        baseline = verify([p["source"] for p in ready]) if ready else {}
        graphs = {}
        for proposal in ready:
            source = proposal["source"]
            if baseline.get(source, "missing byte verdict") is not None:
                rejected[source] = baseline.get(source) or "missing baseline byte verdict"
                continue
            graphs[source] = snapshot(source)
            originals[source] = proposal["_before"]
        for proposal in ready:
            source = proposal["source"]
            if source not in graphs:
                continue
            path = source_path(source, root)
            if path.read_bytes() != originals[source]:
                raise RuntimeError("source changed before apply: " + source)
            path.write_bytes(proposal["_after"])
            written[source] = proposal["_after"]
        checked = verify(list(written)) if written else {}
        declaration_errors = frozen([s for s in written if checked.get(s, "missing verdict") is None], root)
        for source in list(written):
            why = checked.get(source, "missing byte verdict") or declaration_errors.get(source)
            if not why and not same_runtime(graphs[source], snapshot(source)):
                why = "compiled runtime bytes, providers or bindings changed"
            if why:
                rejected[source] = why
                restore(source)
            else:
                applied.append(source)
        restored = [s for s in originals if s not in written]
        if restored:
            bad = verify(restored)
            if any(bad.get(s, "missing verdict") is not None for s in restored):
                raise RuntimeError("original-source restoration did not verify")
        return {"applied": applied, "rejected": rejected, "apply_seconds": time.perf_counter() - started}
    except BaseException:
        restore_errors = []
        for source in list(written):
            try:
                restore(source)
            except (OSError, RuntimeError) as error:
                restore_errors.append(str(error))
        restored = [s for s in originals if source_path(s, root).read_bytes() == originals[s]]
        if restored:
            verify(restored)
        if restore_errors:
            raise RuntimeError("; ".join(restore_errors))
        raise
    finally:
        kept = {claims.key_of("file:" + s) for s in written}
        unused = fresh - kept
        if unused:
            claims.release(sorted(unused, key=str), root=root)


def run(args):
    report = discover(args.under, args.files, args.scan_limit)
    if args.apply:
        report.update(apply(report["candidates"], args.top))
    public = {**report, "candidates": [{k: v for k, v in p.items() if not k.startswith("_")}
                                      for p in report["candidates"][:min(args.top, MAX_BATCH)]]}
    if args.json:
        path = Path(args.json)
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(json.dumps(public, indent=2) + "\n", encoding="utf-8")
    print(f"unused classes: {report['scanned']} sources checked, {len(report['candidates'])} candidates; "
          f"{report['computed']} computed, {report['cache_hits']} cached, {report['discovery_seconds']:.2f}s")
    for proposal in public["candidates"]:
        print(f"  {proposal['removed_count']:4} declarations  {proposal['source']}")
    if args.apply:
        print(f"applied {len(report['applied'])} source(s); "
              f"{len(report['rejected'])} refused/held; {report['apply_seconds']:.2f}s")
        for source, why in report["rejected"].items():
            print(f"  SKIP {source}: {why}")
        print("Review the diff and commit through the normal hooks; publish and release the file claims.")
    return 1 if args.apply and report.get("rejected") and not report.get("applied") else 0
