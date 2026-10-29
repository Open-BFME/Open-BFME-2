"""repair_queue.decision_items: the header tier serves run --all's decision queue."""
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import repair_queue  # noqa: E402

RECORDS = [
    {"class": "Small", "kind": "undecided", "detail": "decide size of Small", "merge_donors": 4,
     "attributes": [{"attribute": "size", "candidates": {"8": 2, "12": 3}}], "contract": "reverse/class_contracts/Small.json",
     "header": "Code/Include/Small.h", "resume": "python3 tools/header_adopt_lane.py run --all --only Small"},
    {"class": "Big", "kind": "slot-undeclarable", "detail": "1 slot(s) cannot be declared: slot2 f(): spellings tie",
     "merge_donors": 90, "attributes": [{"attribute": "slot2", "why": "slot2 f(): spellings tie"}]},
    {"class": "Busy", "kind": "claimed", "detail": "class:Busy is held by seat-3", "merge_donors": 500},
    {"class": "Kid", "kind": "base-unheadered", "detail": "adopt the base header(s) first: Parent", "merge_donors": 70},
    {"class": "Done", "kind": "undecided", "detail": "decide slot1 of Done", "merge_donors": 900},
]


def test_decisions_are_served_ranked_by_donors_with_their_evidence():
    items = repair_queue.decision_items(RECORDS, canon={"Done": "Code/Done.h"})
    assert [i["class"] for i in items] == ["Big", "Small"]          # claimed, waiting and registered skipped
    small = items[1]
    assert small["check"] == "class-header-decide" and small["tier"] == "header"
    assert small["why"].startswith("decide size of Small") and "12 x3, 8 x2" in small["why"]
    assert small["claim"] == ["class:Small", "file:Code/Include/Small.h"]
    assert "--only Small" in small["start"] and "never guess" in small["start"]
    assert items[0]["merge_donors"] == 90 and "spellings tie" in items[0]["why"]


def test_empty_queue_serves_nothing():
    assert repair_queue.decision_items([], canon={}) == []
