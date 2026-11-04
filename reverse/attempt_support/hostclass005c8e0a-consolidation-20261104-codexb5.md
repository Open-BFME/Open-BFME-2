# HostClass005C8E0A consolidation handoff

Source revision: `2885696542`. No source or ledger edits were applied.
`name_lane.py consolidate --under Code/GameEngine/Source/Common/` produced a
current snapshot (subsequent `--check` passed). Its original-path packets leave
these sources unresolved, with no alternatives and quoted-include review
required. They do not prove an original BFME path. The current in-memory TU map
used by `tu_skeleton.py` approves a provisional HostClass005C8E0A group, with
30 approved rows, one mixed source and two refused sources.

`find_declared_unmatched.py` accepts the seed and all four proposed donors.
`tu_views.py --dry-run` finds matching HostClass005C8E0A, TargetObj005C8DBF and
LargeGroupAudioGridCell views; BfmePoolHolder has no emitted CodeView layout.
None of the five sources keys a header queue, Microsoft-header queue, identity,
data-check, hatch or flag-override entry in the current registers.

Dry-run results:

- Accepted seed: `Common/HostClass005C8E0A.cpp`.
- Accepted donors: `Common/HostClass005C8E2C.cpp`,
  `Common/HostClass005C8F17.cpp`, and
  `GameLogic/LargeGroupAudio/Rva005C902AWeight.cpp`.
- Rejected donor: `Common/Rva005C8FBD.cpp` (`bytes`).
- The chosen composition preserves 14 rows. No private-view repair was applied.
- Ordinary premerge preview against census `3a8028f34e` (2026-11-04 11:27)
  reports all four accepted units LINKS, retaining 557/557 authored bytes.
  The seed has two unused allocator-copy diagnostics, explicitly nonblocking.

Application was refused before writing: another worker holds RVA `0x0007FAB3`,
the ICF-folded Holder38FBD destructor row in the rejected Rva005C8FBD donor.
No claim bypass, forced release, manual merge or map edit was attempted.

Next: after the conflicting scope is free, rerun the supported merge under a
fresh claim. Its chosen composition should remove three source files; the
fourth donor still needs its own byte-preserving reconciliation. Recheck current
map/index/inputs. Complete path-consumer, queue, data, EH and link audits on the
actual applied merge before publishing. No source-file or census gain is claimed.
