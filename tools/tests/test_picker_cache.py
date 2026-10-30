"""tools/picker_cache.py and the picker paths built on it: a cache hit returns what the
compute returned, a changed input (tracked, untracked, absent then present) misses, a
second worktree of the clone shares the entries, and the lazy, prefetched pick draws
exactly what building every queue first draws."""
import argparse
import json
import random
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import claims  # noqa: E402
import next_work  # noqa: E402
import picker_cache  # noqa: E402
import re_log  # noqa: E402
import tu_evidence  # noqa: E402
import tu_skeleton  # noqa: E402


def git(root, *args):
    return subprocess.run(["git", "-C", str(root), *args], check=True, capture_output=True, text=True).stdout


@pytest.fixture
def repo(tmp_path, monkeypatch):
    root = tmp_path / "repo"
    root.mkdir()
    git(root, "init", "-q", "-b", "master")
    git(root, "config", "user.email", "t@example.com")
    git(root, "config", "user.name", "t")
    (root / ".gitignore").write_text("build/\n")
    (root / "reverse").mkdir()
    (root / "reverse" / "input.txt").write_text("one\n")
    git(root, "add", ".")
    git(root, "commit", "-q", "-m", "base")
    monkeypatch.setenv("BFME_PICKER_CACHE", str(tmp_path / "cache"))     # also enables it under pytest
    monkeypatch.delenv("BFME_PICKER_CACHE_SALT", raising=False)
    picker_cache.reset()
    yield root
    picker_cache.reset()


def counting(fn):
    calls = []

    def compute():
        calls.append(1)
        return fn()
    compute.calls = calls
    return compute


def memo(root, compute, kind="k"):
    picker_cache.reset()                     # a new process: the tree state is read again
    return picker_cache.memo(kind, compute, root=root)


def test_a_hit_returns_the_computed_value_without_computing(repo):
    compute = counting(lambda: {"items": [{"a": 1, "b": None}], "note": "n"})
    first = memo(repo, compute)
    assert memo(repo, compute) == first == {"items": [{"a": 1, "b": None}], "note": "n"}
    assert len(compute.calls) == 1


def test_a_changed_tracked_file_misses(repo):
    compute = counting(lambda: (repo / "reverse" / "input.txt").read_text())
    assert memo(repo, compute) == "one\n"
    (repo / "reverse" / "input.txt").write_text("two\n")
    assert memo(repo, compute) == "two\n"
    (repo / "reverse" / "input.txt").write_text("one\n")                   # back to HEAD: the first entry
    assert memo(repo, compute) == "one\n" and len(compute.calls) == 2


def test_a_new_untracked_file_or_commit_misses(repo):
    compute = counting(lambda: sorted(p.name for p in (repo / "reverse").iterdir()))
    memo(repo, compute)
    (repo / "reverse" / "new.txt").write_text("x")
    assert memo(repo, compute) == ["input.txt", "new.txt"]
    git(repo, "add", ".")
    git(repo, "commit", "-q", "-m", "more")
    memo(repo, compute)
    assert len(compute.calls) == 3


def test_a_recorded_ignored_input_that_changes_misses(repo):
    out = repo / "build" / "report.json"
    out.parent.mkdir()
    out.write_text("[1]")
    compute = counting(lambda: json.loads(out.read_text()))
    assert memo(repo, compute) == [1]
    assert memo(repo, compute) == [1] and len(compute.calls) == 1
    out.write_text("[2]")
    assert memo(repo, compute) == [2] and len(compute.calls) == 2


def test_an_absent_ignored_input_that_appears_misses(repo):
    out = repo / "build" / "queue.json"
    compute = counting(lambda: json.loads(out.read_text()) if out.exists() else [])
    assert memo(repo, compute) == []
    assert memo(repo, compute) == [] and len(compute.calls) == 1
    out.parent.mkdir()
    out.write_text('["boot"]')
    assert memo(repo, compute) == ["boot"] and len(compute.calls) == 2


def test_another_worktree_of_the_clone_shares_the_entry(repo, tmp_path):
    out = repo / "build" / "report.json"
    out.parent.mkdir()
    out.write_text("[1]")
    compute = counting(lambda: [(repo / "reverse" / "input.txt").read_text()])
    memo(repo, compute)
    other = tmp_path / "other"
    git(repo, "worktree", "add", "-q", "--detach", str(other), "HEAD")
    again = counting(lambda: [(other / "reverse" / "input.txt").read_text()])
    assert memo(other, again) == ["one\n"] and not again.calls
    (other / "reverse" / "input.txt").write_text("edited\n")                # its own dirty tree misses
    assert memo(other, again) == ["edited\n"] and len(again.calls) == 1


def test_an_edited_submodule_file_misses(repo, tmp_path):
    donor = tmp_path / "donor"
    donor.mkdir()
    git(donor, "init", "-q", "-b", "master")
    git(donor, "config", "user.email", "t@example.com")
    git(donor, "config", "user.name", "t")
    (donor / "donor.cpp").write_text("one\n")
    git(donor, "add", ".")
    git(donor, "commit", "-q", "-m", "donor")
    git(repo, "-c", "protocol.file.allow=always", "submodule", "add", "-q", str(donor), "reference/sub")
    git(repo, "commit", "-q", "-m", "submodule")
    compute = counting(lambda: (repo / "reference" / "sub" / "donor.cpp").read_text())
    assert memo(repo, compute) == "one\n"
    (repo / "reference" / "sub" / "donor.cpp").write_text("two\n")      # edited, not committed
    assert memo(repo, compute) == "two\n" and len(compute.calls) == 2


def test_a_shared_report_under_the_git_directory_misses_when_it_changes(repo, monkeypatch):
    # the primary checkout's cache lives in .git/: merge_all's decisions there are an input
    cache = repo / ".git" / "bfme-picker-cache"
    monkeypatch.setenv("BFME_PICKER_CACHE", str(cache))
    report = cache / "merge_all" / "decisions.json"
    report.parent.mkdir(parents=True)
    report.write_text("[]")
    compute = counting(lambda: report.read_text())
    assert memo(repo, compute) == "[]"
    report.write_text('[{"tu": "x"}]')
    assert memo(repo, compute) == '[{"tu": "x"}]' and len(compute.calls) == 2


def test_an_exception_stores_nothing(repo):
    def red():
        raise SystemExit(2)
    with pytest.raises(SystemExit):
        memo(repo, red)
    assert memo(repo, lambda: "green") == "green"


def test_peek_and_put(repo):
    picker_cache.reset()
    assert picker_cache.peek("check", root=repo) == (False, None)
    picker_cache.put("check", "OK line", root=repo)
    picker_cache.reset()
    assert picker_cache.peek("check", root=repo) == (True, "OK line")
    (repo / "reverse" / "input.txt").write_text("two\n")
    picker_cache.reset()
    assert picker_cache.peek("check", root=repo) == (False, None)


def test_off_and_pytest_without_a_directory_compute_directly(repo, monkeypatch):
    compute = counting(lambda: 1)
    monkeypatch.setenv("BFME_PICKER_CACHE", "off")
    memo(repo, compute)
    memo(repo, compute)
    monkeypatch.delenv("BFME_PICKER_CACHE")
    memo(repo, compute)
    assert len(compute.calls) == 3


def test_old_entries_are_pruned(repo, monkeypatch):
    monkeypatch.setattr(picker_cache, "KEEP", 3)
    for n in range(6):
        picker_cache.keyed("pruned", [n], lambda n=n: n)
    assert len(list((picker_cache.cache_dir(str(repo)) / "memo" / "pruned").glob("*.json"))) == 3


def test_stamped_follows_the_file_content(repo):
    path = repo / "reverse" / "input.txt"
    parse = counting(lambda: path.read_text().upper())
    assert picker_cache.stamped(path, lambda p: parse(), "s") == "ONE\n"
    assert picker_cache.stamped(path, lambda p: parse(), "s") == "ONE\n" and len(parse.calls) == 1
    path.write_text("two\n")
    assert picker_cache.stamped(path, lambda p: parse(), "s") == "TWO\n" and len(parse.calls) == 2


def test_blob_key_names_only_clean_tracked_files_in_a_read_only_run(repo, monkeypatch):
    monkeypatch.setattr(picker_cache, "READ_ONLY", False)
    picker_cache.reset()
    assert picker_cache.blob_key("reverse/input.txt", repo) is None
    monkeypatch.setattr(picker_cache, "READ_ONLY", True)
    picker_cache.reset()
    blob = git(repo, "rev-parse", "HEAD:reverse/input.txt").strip()
    assert picker_cache.blob_key("reverse/input.txt", repo).startswith(blob + ":")
    (repo / "reverse" / "input.txt").write_text("dirty\n")
    picker_cache.reset()
    assert picker_cache.blob_key("reverse/input.txt", repo) is None
    assert picker_cache.blob_key("reverse/absent.txt", repo) is None


def test_file_memo_round_trips_and_merges(repo, tmp_path):
    code = tmp_path / "code.py"
    code.write_text("v1")
    one = picker_cache.FileMemo("fm", [code])
    assert one.get("k1", lambda: ["A"]) == ["A"]
    two = picker_cache.FileMemo("fm", [code])
    assert two.get("k2", lambda: ["B"]) == ["B"]
    one.save()
    two.save()
    three = picker_cache.FileMemo("fm", [code])
    assert three.get("k1", lambda: pytest.fail("k1 lost")) == ["A"]
    assert three.get("k2", lambda: pytest.fail("k2 lost")) == ["B"]
    code.write_text("v2")                                                   # new code: a new store
    assert picker_cache.FileMemo("fm", [code]).get("k1", lambda: ["C"]) == ["C"]


# ---- the algorithms made faster return what they returned

def naive_inside_other(spans, rva, key):
    for lo, hi, k in spans:
        if lo > rva:
            break
        if k != key and lo < rva < hi:
            return k
    return None


def test_span_index_agrees_with_inside_other():
    rng = random.Random(7)
    for _ in range(200):
        spans = sorted((lo, lo + rng.randrange(0, 60), rng.choice("abcd"))
                       for lo in (rng.randrange(0, 400) for _ in range(rng.randrange(0, 30))))
        index = tu_evidence.SpanIndex(spans)
        for rva in range(-5, 470, 3):
            key = rng.choice("abcd")
            assert index.other(rva, key) == naive_inside_other(spans, rva, key)                 == tu_evidence.inside_other(spans, rva, key)
        shuffled = spans[::-1]                                            # unsorted: the plain scan
        assert [tu_evidence.inside_other(shuffled, rva, "a") for rva in range(0, 470, 7)] ==             [naive_inside_other(shuffled, rva, "a") for rva in range(0, 470, 7)]


def test_void_retraction_matches_the_quadratic_rule(tmp_path, monkeypatch):
    rng = random.Random(3)
    lines, rows = [], []
    for _ in range(400):
        symbol, rva = rng.choice("ABC"), rng.choice((0x401000, 0x402000, None))
        status = rng.choice(("void", "blocked", "no-match", "attempted"))
        lines.append("\t".join([symbol, "" if rva is None else f"0x{rva:08X}", "10", status, "e"]))
        rows.append((symbol, status, rva))
    log = tmp_path / "re_attempts.log"
    log.write_text("\n".join(lines) + "\n")
    live = [True] * len(rows)                                              # the old O(n^2) loop
    for index, (symbol, status, rva) in enumerate(rows):
        if status == "void":
            live[index] = False
            for earlier in range(index):
                if rows[earlier][0] == symbol and rows[earlier][2] == rva:
                    live[earlier] = False
    want = {}
    for keep, (symbol, status, rva) in zip(live, rows):
        if keep:
            want.setdefault(symbol, {})[rva] = status
    re_log._reset()
    monkeypatch.setattr(re_log, "RE_ATTEMPTS", log)
    try:
        re_log._load()
        assert re_log._BY_BOUNDARY == want
    finally:
        re_log._reset()


def test_queue_puts_held_scopes_last_like_before(monkeypatch):
    entries = [{"tu": f"Code/T{i}.cpp", "removes": r, "rows": w, "mixed": 0, "refused": 0,
                "keys": [claims.key_of(f"file:Code/T{i}.cpp"), 0x401000 + i]}
               for i, (r, w) in enumerate([(3, 9), (5, 1), (3, 9), (1, 4), (5, 7)])]
    held = {claims.key_of("file:Code/T1.cpp"), 0x401003}
    monkeypatch.setattr(tu_skeleton.claims, "_blocking_records", lambda root=None: iter([{k: {} for k in held}]))
    got = tu_skeleton.queue(entries=entries)
    want = sorted(({**{k: v for k, v in e.items() if k != "keys"}, "held": bool(set(e["keys"]) & held)}
                   for e in entries), key=lambda d: (d["held"], -d["removes"], -d["rows"], d["tu"]))
    assert got == want and [d["held"] for d in got] == [False, False, False, True, True]


# ---- the lazy, prefetched pick draws what building everything first draws

class Queues:
    def __init__(self, tmp_path, queues):
        self.ROOT, self.queues = tmp_path, queues
        self.DEBT_QUEUES = {n: (f"{n}.txt", lambda n=n: (list(queues.get(n, [])), n))
                            for n in ("data", "header", "identity")}
        for n in self.DEBT_QUEUES:
            (tmp_path / f"{n}.txt").write_text("")
        self.STRUCTURAL_QUEUES = {n: (lambda n=n: (list(queues.get(n, [])), n)) for n in next_work.STRUCTURAL_TIERS}
        self.STRUCTURAL_QUEUES["consolidate"] = lambda: self.consolidation_items()

    def all_repair_items(self):
        return list(self.queues.get("repair", []))

    def link_items(self):
        return list(self.queues.get("link", [])), "link"

    def consolidation_pure(self):
        return list(self.queues.get("consolidate", []))

    def consolidation_items(self, pure=None):
        return (self.consolidation_pure() if pure is None else pure), "consolidate"


def item(tier, name, size):
    return {"tier": tier, "function": name, "source": f"Code/{name}.cpp", "target_rva": "", "size": size,
            "count": size, "credit_note": "", "why": "w", "pass_test": "t", "claim": [f"file:Code/{name}.cpp"]}


@pytest.mark.parametrize("seed", range(12))
def test_a_lazy_prefetched_pick_equals_building_every_queue_first(tmp_path, monkeypatch, seed):
    monkeypatch.setenv("BFME_TIER_TUNING", "off")
    monkeypatch.setattr(next_work.re_log, "is_dead_end", lambda *a, **k: False)
    monkeypatch.setattr(next_work, "annotate_attempts", lambda pool: pool)
    monkeypatch.setattr(next_work.wb_context, "lead", lambda rva: None)
    monkeypatch.setattr(claims, "lock_records", lambda root=None: {})
    monkeypatch.setattr(claims, "lock_keys", lambda keys, root=None, records=None: set(keys))
    monkeypatch.setattr(claims, "work_keys", lambda rva=None, source=None, cls=None, root=None:
                        {claims.file_key(source)} if source else set())
    rng = random.Random(seed)
    queues = {name: [item(name, f"{name}{i}", rng.randrange(1, 900)) for i in range(rng.randrange(0, 4))]
              for name in next_work.DEBT_TIERS if name != "repair" and rng.random() < 0.6}
    busy = {claims.file_key(f"Code/{name}0.cpp") for name in queues if rng.random() < 0.4}
    args = argparse.Namespace(shard=None, include_logged=False, claim=False)
    monkeypatch.setattr(next_work, "repair_queue", Queues(tmp_path, queues), raising=False)
    order = next_work.debt_order(random.Random(seed))

    def pick(eager):
        monkeypatch.setattr(next_work, "BUILT", [])
        monkeypatch.setattr(next_work, "_DEBT", {})
        monkeypatch.setattr(next_work, "_PREFETCH", {})
        monkeypatch.setattr(next_work, "SKIPPED", [])
        draws = random.Random(seed * 31)
        monkeypatch.setattr(next_work.secrets, "randbelow", lambda n: draws.randrange(n))
        if eager:
            for name in next_work.DEBT_TIERS:
                next_work.build_debt(name)
            next_work.BUILT.clear()
        else:
            next_work.prefetch_debt(order, warm=False)
        got = next_work.pick_debt(order, args, set(busy))
        return got["name"], got["candidate"], got["tried"], next_work.BUILT if not eager else None

    lazy_name, lazy_candidate, lazy_tried, built = pick(eager=False)
    eager_name, eager_candidate, eager_tried, _ = pick(eager=True)
    assert (lazy_name, lazy_candidate, lazy_tried) == (eager_name, eager_candidate, eager_tried)
    assert built == order[:len(built)]                                     # built in the draw's order only


# ---- the rebuilt TU map and LinkGuard's link rank, shared by their inputs

def test_a_run_leaves_no_prefetch_behind(monkeypatch):
    monkeypatch.setattr(sys, "argv", ["next_work.py", "--tier", "dx"])
    monkeypatch.setattr(next_work, "check_ledger", lambda: "ledger healthy")
    monkeypatch.setattr(next_work, "serve_dx", lambda args: next_work._PREFETCH.update(stale=object()))
    next_work.main()
    assert next_work._PREFETCH == {} and next_work._LEDGER_CHECK == {} and picker_cache.READ_ONLY is False


def test_a_stale_map_rebuild_is_read_back_by_its_input_fingerprint(tmp_path, monkeypatch):
    import types
    import tu_map
    monkeypatch.setenv("BFME_PICKER_CACHE", str(tmp_path / "cache"))
    layout = types.SimpleNamespace(root=tmp_path, fingerprint=tmp_path / "tu_map.fingerprint",
                                   out=tmp_path / "tu_map.csv", reverse="reverse", zh_problem=lambda: None)
    inputs = ["aaa  reverse/functions.csv\n# a note\n"]
    monkeypatch.setattr(tu_map, "fingerprint", lambda layout, kind=None: inputs[0])
    build = counting(lambda: [{"rva": 0x1000, "tu": "Code/A.cpp", "size": 4}])
    monkeypatch.setattr(tu_map, "build", lambda layout: build())
    rows, stale = tu_map.current_rows(layout)
    assert rows == [{"rva": "4096", "tu": "Code/A.cpp", "size": "4"}] and stale
    assert tu_map.current_rows(layout)[0] == rows and len(build.calls) == 1   # same inputs: read back
    inputs[0] = "bbb  reverse/functions.csv\n"
    tu_map.current_rows(layout)
    assert len(build.calls) == 2                                          # an input changed: rebuilt
    layout.fingerprint.write_text(inputs[0])                              # fresh: the committed map
    layout.out.write_text("rva,tu\n0x2000,Code/B.cpp\n")
    assert tu_map.current_rows(layout) == ([{"rva": "0x2000", "tu": "Code/B.cpp"}], [])
    assert len(build.calls) == 2


def test_a_stale_map_is_never_rebuilt_without_the_zh_tree(tmp_path, monkeypatch):
    """Without the ZH tree a rebuild has no Z or S evidence and approves TUs the real map does
    not: a seat whose submodule was not prepared served 165 of 696 dead merges from one
    (2026-10-29). The rebuild refuses, and the picker skips the map's queues saying why."""
    import types
    import repair_queue
    import tu_map
    import tu_skeleton
    monkeypatch.setenv("BFME_PICKER_CACHE", str(tmp_path / "cache"))
    layout = types.SimpleNamespace(root=tmp_path, fingerprint=tmp_path / "tu_map.fingerprint",
                                   out=tmp_path / "tu_map.csv", reverse="reverse",
                                   zh_problem=lambda: "no ZH tree at reference/x")
    monkeypatch.setattr(tu_map, "fingerprint", lambda layout, kind=None: "aaa  reverse/functions.csv\n")
    monkeypatch.setattr(tu_map, "build", lambda layout: pytest.fail("rebuilt without the ZH tree"))
    with pytest.raises(RuntimeError, match="no ZH tree at reference/x.*worktree_setup.py prepare"):
        tu_map.current_rows(layout)
    layout.fingerprint.write_text("aaa  reverse/functions.csv\n")          # fresh: the committed map serves
    layout.out.write_text("rva,tu\n0x2000,Code/B.cpp\n")
    assert tu_map.current_rows(layout) == ([{"rva": "0x2000", "tu": "Code/B.cpp"}], [])
    layout.fingerprint.write_text("bbb  reverse/functions.csv\n")
    monkeypatch.setattr(tu_skeleton, "LAYOUT", layout)
    monkeypatch.setattr(tu_skeleton, "_CACHE", {})
    monkeypatch.setattr(repair_queue, "ROOT", tmp_path)
    (tmp_path / "reverse").mkdir()
    (tmp_path / repair_queue.TU_MAP).write_text("rva,tu\n")
    for name, builder in (("consolidation", repair_queue.consolidation_items),
                          ("TU-approval", repair_queue.tu_approval_items),
                          ("TU-evidence", repair_queue.tu_evidence_items)):
        items, note = builder()
        assert items == [] and note.startswith(f"{name} queue skipped:") and "no ZH tree" in note


def test_link_rank_is_shared_per_ledger_content(tmp_path, monkeypatch):
    import data_rows
    import link_check
    monkeypatch.setenv("BFME_PICKER_CACHE", str(tmp_path / "cache"))
    data = tmp_path / "data_rows.csv"
    data.write_text("name\n")
    monkeypatch.setattr(data_rows, "DATA_ROWS", data)
    rank = counting(lambda: {"a.obj": 0, "b.obj": 1})
    monkeypatch.setattr(link_check, "link_rank", lambda rows: rank())
    assert tu_skeleton.link_rank([]) == {"a.obj": 0, "b.obj": 1}
    assert tu_skeleton.link_rank([]) == {"a.obj": 0, "b.obj": 1} and len(rank.calls) == 1
    data.write_text("name\nx\n")
    tu_skeleton.link_rank([])
    assert len(rank.calls) == 2


