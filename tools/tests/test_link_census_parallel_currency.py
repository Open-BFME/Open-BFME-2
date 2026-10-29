"""stale_objects splits the receipt check across BUILD_POOL processes: same answer, same order."""
import concurrent.futures
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import link_census as census  # noqa: E402


class InlinePool:
    """ProcessPoolExecutor's map, run in this process (the fakes below stay patched)."""
    def __init__(self, workers):
        self.workers = workers

    def __enter__(self):
        return self

    def __exit__(self, *exc):
        return False

    def map(self, fn, parts):
        return [fn(part) for part in parts]


@pytest.fixture
def objects(monkeypatch):
    present = [Path(f"o{i:04d}.obj") for i in range(500)]
    sources = {obj: Path(f"s{i:04d}.cpp") for i, obj in enumerate(present) if i % 50}  # every 50th: a lib member
    stale = {obj for i, obj in enumerate(present) if i % 7 == 3}

    def current(source, obj, *, inventory_cache=None, allow_fresh=True):
        assert not allow_fresh
        inventory_cache.setdefault(f"dir{int(obj.stem[1:]) % 5}", "digest")
        return obj not in stale
    monkeypatch.setattr(census, "object_current", current)
    monkeypatch.setattr(census, "input_receipts", lambda: None)
    monkeypatch.setattr(census.build, "_inventory_cache_still_current", lambda cache: True)
    monkeypatch.setattr(concurrent.futures, "ProcessPoolExecutor", InlinePool)
    return present, sources, stale


def test_split_check_gives_the_single_pass_answer_in_order(objects, monkeypatch):
    present, sources, stale = objects
    monkeypatch.setenv("BUILD_POOL", "1")
    serial = census.stale_objects(present, sources)
    monkeypatch.setenv("BUILD_POOL", "8")
    assert census.stale_objects(present, sources) == serial
    assert serial == [obj for obj in present if obj in stale and obj in sources]


def test_shares_that_saw_a_directory_differently_refuse(objects, monkeypatch):
    present, sources, _ = objects
    seen = []

    def current(source, obj, *, inventory_cache=None, allow_fresh=True):
        if not inventory_cache:
            seen.append(obj)
            inventory_cache["dir"] = f"digest {len(seen)}"  # each share snapshots another listing
        return True
    monkeypatch.setattr(census, "object_current", current)
    monkeypatch.setenv("BUILD_POOL", "8")
    with pytest.raises(SystemExit, match="include search directories changed"):
        census.stale_objects(present, sources)
