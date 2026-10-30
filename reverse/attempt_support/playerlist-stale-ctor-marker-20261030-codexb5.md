# PlayerList stale constructor exemption and consolidation handoff

Base: `112d98e320`. Owner: `yasinschroeder-codexb5`, 2026-10-30.

The default picker claimed PlayerList.cpp and its eleven clean donor files.
The current ledger already owns the complete 136-byte constructor at
`0x002A7F80`, plus its EH rows, in PlayerListCtorBFME2.cpp. PlayerList.cpp has
no constructor definition, so its constructor exemption was stale. Replace
that marker with an ordinary owner comment and retire its one hatch key using
`hatch_counters.py --update`. Also correct the newGame owner comment:
`0x002A8008` is already rowed, 766 bytes, in PlayerList_getNthPlayer.cpp.
These are existing owners, not newly recovered bodies or regressions.

## Verification of the cleanup

- Before and after `./build.sh Code/GameEngine/Source/Common/RTS/PlayerList*.cpp`:
  57/57 function rows, one data row, four strings and 21 funclet pins pass.
- `find_declared_unmatched.py` passes on the same twelve files. The seed's
  reported unclaimed definitions fall from five to four when the stale
  constructor marker disappears; the getNthPlayer fragment retains its one
  existing exemption. This does not close the remaining unrowed bodies.
- Saved verified before objects versus final objects have identical external
  COMDAT names/digests/sizes, external symbol entries, roots and reference
  graphs for every file. The seed retains 553 external COMDAT entries and
  569 external symbol entries. The strict rebuild also preserves these facts.
- `link_check.py --prepare-current` on the twelve explicit sources passes:
  one strict compile, eleven current objects, then the ordinary gate reuses
  all twelve objects and verifies all 57 rows. Census/index/status stay intact.
- The final baseline diff removes only the constructor's key. The whole-tree
  update also found an unrelated already-unused BodyModule grant; that hunk
  was restored to HEAD rather than included in this scoped change.

Local receipts are `build/codexb5-playerlist-{before-build,after-build,
prepare-after,object-proof-final,unmatched-after}.txt` and the saved objects
and JSON facts under `build/codexb5-playerlist-objects/`.

The staged-tree link audit is INCONCLUSIVE: index `85f6b7f40c` predates the
base, and affected consumer Common/0CreateAHeroManager21FE49.cpp lacks a
current receipt. No affected-consumer closure or census gain is claimed.
Carry the PlayerList scope and this consumer into the next scheduled census.
Receipt: `build/codexb5-playerlist-batch-audit.txt`, exit 2.

## Consolidation remains open

`name_lane.py consolidate --under Code/GameEngine/Source/Common/RTS/` completed
on stable inputs; its final `--check build/consolidation` passes. The PlayerList
packet lists twelve sources, data ownership, internal linkage, pragma/include
context, path-keyed registers and unrowed definitions. The committed TU map is
stale; tu_skeleton rebuilds it in memory. No map regeneration is committed and
the planner's donor hints are not placement approval.

`tu_views.py .../PlayerList.cpp --dry-run` completes without applying changes.
Its CodeView-derived findings describe the current reconstructions:

- Player views disagree, including an explicitly padded 0x3B0 view and the
  constructor file's 0x758 view. Reconcile from retail evidence before sharing
  declarations; a same-sized pointer field alone proves no type identity.
- PlayerList constructor/destructor views inherit SubsystemInterface and
  Snapshot; several other views have no base clause.
- SidesInfo embeds Dict at +4 with conflicting extents, +4..+5 and +4..+8.
  The Dict superset is only a mechanical plan, not a verified prerequisite fix.
- No file's CodeView lays out PointGroupClass, so that view has no layout proof.

The ordinary merge dry-run was interrupted after about nineteen minutes during
accretion, exit 130, with no final accepted-set verdict. It wrote no lasting
source/ledger change. An initial planner scan and provider-preparation run
refused moving inputs while the merger created temporary Code files. Both
were rerun successfully after the probe stopped. No merge is inferred from
that unfinished run. The earlier completed Xfer/C1001 trial remains recorded
in [the canonical-Xfer handoff](consolidation-playerlist-xfer-prerequisite-20261026-codex.md).

The official BFME 1 fetch shows upstream `40e7327e50d7`; the checkout and gitlink
remain the verified `efb2b2a27078`. The unchanged snapshot's blocked full-gate
refresh is documented in the preceding CopyProtection handoff. No freshness
stamp, reference pin, body name, class, source path or provider binding changes.

Result: one stale hatch key retired; source-file, TU-approval and census gains
are zero. Resolve the class-view and compiler prerequisites before another
broad merge probe.
