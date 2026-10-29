# AptKey TU approval investigation

Inspected 2026-10-29 at `9e675abd9d1e`. The picker claimed
`file:Code/Libraries/Source/Apt/AptObject/AptKey.cpp` for nine proposed rows.
The consolidation planner for `Code/Libraries/Source/Apt/AptObject/` reports
`AptMiscObjects.cpp` as a candidate for the object-member lookup, with
placement needing corroboration. Its report is a lead, not an approval.

The current map assigns six named code rows to the inferred AptKey.cpp at
0x006E8B40, 0x006E8BC0, 0x006E8C80, 0x006EA560, 0x006EA5C0 and
0x006EACC0. Three intervening code rows follow by contiguity. All nine are
proposed and marked noncontiguous. Between them, the game-image path at
0x006E9580 anchors `Code/Libraries/Source/Apt/AptMiscObjects.cpp`; its
approved rows include the LoadVars, Math, Mouse and Error cluster. WorldBuilder
pairs 0x006EACC0 with `AptKey::objectMemberLookup` and that same path, but the
existing recovery log used the WorldBuilder identity, so this is not an
independent naming anchor. These are target path evidence, a separate
WorldBuilder lead, and map inference respectively.

The AptKey named span is 0x2180 bytes (0x006E8B40 to 0x006EACC0), exceeding
`tu_map.py`'s 0x2000 `UNION_SPAN` for interleaving. The current rule therefore
cannot merge the naming cluster into the anchored AptMiscObjects cluster.
Raising the limit for this case alone or repointing rows by hand would not
establish placement. Investigate a general rule using independent evidence and
held-out precision, or find an existing promoted target-side signal that
reaches the code rows. Then rebuild the map in memory and rerun the plan.

`tu_skeleton.py --plan` on the claimed path reports 16 approved parent-linked
EH rows in two donor files, but none of the nine proposed code rows; this is
not the picker's pass condition. No source or ledger change, TU approval,
linking improvement or census gain is claimed. No merge was attempted.
