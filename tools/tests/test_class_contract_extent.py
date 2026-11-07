"""A size smaller than the object retail builds is queued, whatever decided it.

`retail_layout.py` already compares its `sizeof` fact against the bytes the
constructors write (`extent_lower_bound`) and records a conflict. That check
only fires when retail's operator-new gave a sizeof at all. A size the private
views voted on, or one taken from the Zero Hour header, is settled later in
`class_contract.decide()` and never meets it - which is how 66 contracts came to
record a size their own evidence rules out.

Queueing is not free: `header_adopt_lane` refuses to generate a canonical header
from a contract with any undecided attribute. So this needs two independent
facts, not one. The ctor-write extent is an inference from `this`-relative
writes, and a single mis-attributed write would block a class on its own; 28 of
the 66 rest on it alone and are left alone here. The other 38 are contradicted
twice, by the writes and by an allocation retail actually makes, and the two
agree with each other - Team records 60 while retail allocates 0x13c and its
constructor writes 297, and the canonical header asserts sizeof(Team) == 0x13c.

Even then it is queued, never imposed: two facts can show the recorded size is
wrong without settling which of them is the sizeof.
"""
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import class_contract as contract


def size_items(queue):
    return [q for q in queue if q.get("attribute") == "size"]


@pytest.fixture
def decide(monkeypatch):
    """Run decide() over stubbed evidence: no compiler, no ledger, no toolchain."""
    def run(view_size, *, writes=None, allocates=(), sizeof=None, zh_size=None):
        facts = {}
        if writes is not None:
            facts["extent_lower_bound"] = {"value": writes, "kind": "inference",
                                           "rule": "retail-ctor-writes"}
        if allocates:
            facts["allocation_observed"] = {"value": {"%#x" % a: 1 for a in allocates},
                                            "kind": "inference"}
        if sizeof is not None:
            facts["sizeof"] = {"value": sizeof}
        monkeypatch.setattr(contract, "ledger_rows", lambda: [])
        monkeypatch.setattr(contract, "census", lambda name, rows=None: ["Code/A.cpp"])
        monkeypatch.setattr(contract, "views", lambda name, sources, jobs: (
            {"Code/A.cpp": {"size": view_size, "key": "struct", "fields": [], "bases": [],
                            "vslots": {}}},
            {"Code/A.cpp": {}}))
        monkeypatch.setattr(contract, "flatten", lambda *a, **k: [])
        monkeypatch.setattr(contract, "zh_layout", lambda name, builder: (
            {"layout": {"size": zh_size, "key": "struct", "bases": []}, "every": {}}
            if zh_size else None))
        monkeypatch.setattr(contract, "retail_access", lambda *a: {})
        monkeypatch.setattr(contract, "witnesses", lambda name: {})
        monkeypatch.setattr(contract, "retail_vtable", lambda *a: {})
        monkeypatch.setattr(contract, "retail_layout", lambda *a: {"facts": facts})
        monkeypatch.setattr(contract, "retail_bases", lambda *a: None)
        monkeypatch.setattr(contract, "export_key",
                            lambda name: __import__("collections").Counter())
        import class_layouts
        monkeypatch.setattr(class_layouts, "build_module", lambda: object())
        return contract.decide("Widget", sources=["Code/A.cpp"], jobs=1)
    return run


def test_two_facts_against_a_voted_size_are_queued(decide):
    """The Team shape: records 60, retail allocates 0x13c, the ctor writes 297."""
    got = decide(60, writes=297, allocates=[0x13c])
    items = size_items(got["queue"])
    assert items, "a size below both facts must be queued"
    assert set(items[0]["candidates"]) == {"60", "297", "316"}
    assert "constructor" in items[0]["why"] and "allocation" in items[0]["why"]
    assert got["size"] == 60, "the facts are inferences: they must not overwrite the size"
    assert got["size_by"] == "majority", "nor restate which rule decided"


def test_the_zh_rule_reaches_the_same_contradiction(decide):
    got = decide(192, writes=193, allocates=[0xc4], zh_size=192)
    assert got["size_by"] == "zh"
    assert size_items(got["queue"]), "the check must not be limited to the voting path"


def test_the_ctor_write_inference_alone_does_not_block(decide):
    """28 of the 66 rest on this one fact; a mis-attributed write must not block a class."""
    got = decide(1124, writes=119280)
    assert got["size"] == 1124
    assert not size_items(got["queue"])


def test_an_allocation_alone_does_not_block(decide):
    got = decide(60, allocates=[0x13c])
    assert not size_items(got["queue"])


def test_an_allocation_no_larger_than_the_size_does_not_corroborate(decide):
    """A derived object's allocation can be smaller; only a larger one contradicts."""
    got = decide(320, writes=400, allocates=[0x80])
    assert not size_items(got["queue"])


def test_a_size_that_covers_both_facts_is_not_queued(decide):
    got = decide(320, writes=297, allocates=[0x13c])
    assert got["size"] == 320
    assert not size_items(got["queue"])


def test_a_size_exactly_at_the_write_bound_is_not_queued(decide):
    """`reach` is offset + width, so a size equal to it holds every written byte."""
    got = decide(297, writes=297, allocates=[0x13c])
    assert not size_items(got["queue"])


def test_no_facts_recorded_means_no_new_queue_item(decide):
    assert not size_items(decide(60)["queue"])


def test_retails_own_sizeof_still_outranks_the_vote(decide):
    got = decide(60, sizeof=316)
    assert got["size"] == 316 and got["size_by"] == "retail-new"
