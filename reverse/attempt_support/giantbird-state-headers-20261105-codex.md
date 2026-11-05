# GiantBird state-machine header prerequisites, 2026-11-05

Inspected base: `4c1c2f261c`. Claimed the default picker's nine-file
`GiantBirdAIUpdate.cpp` consolidation scope.

## Source changes

- `GiantBirdAIUpdateCtor.cpp`: select `BFME_SNAPSHOT_NAME_SLOT` before
  ObjectModule first reads Snapshot, then include the canonical AIStateMachine
  header instead of its private 0x68-byte view. The old inclusion order selected
  pure `crc(Xfer *)`; the canonical state machine overrides the retail name
  getter, so that old selection prevented constructing the derived machine.
- `GiantBirdAIUpdatePrivateFollowPathAppend.cpp`: use canonical AIStateMachine
  and derive from canonical AIUpdateInterface. Its existing +0x30 state-machine
  pointer now comes from the base, and padding starts at the base's +0x3E4 end.
  Interpret canonical `field3C` as the existing verified vector<Coord3D> view;
  no shared header or class layout changes. Replace the synthetic 30-slot
  template hierarchy with canonical `privateFollowPath`, whose slot remains 30.

The slot names and offsets are existing canonical-header facts; the local path
vector interpretation is supported by the original matched body and retained
whole-body verification. This change supplies no new donor identity claims.

## Verification and debt

- Changed factory donor: `./build.sh` 2/2 matched.
- Changed append donor: `./build.sh` 4/4 matched, including both renumbered
  funclets verified from parent EH data. Declared-unmatched checks pass for both.
- `header_adopt_lane.py accept` passed and retired exactly these four queue
  entries through their owner workflow: AIStateMachine in both changed donors,
  UpdateModule in `GiantBirdAIUpdateCtor_GiantBirdAIUpdate.cpp`, and
  AIUpdateInterface in `GiantBirdAIUpdateXfer.cpp`. The latter two sources already
  included their canonical headers and needed no source edit.
- Current-object `link_check.py` on those four sources: 4/4 LINKS, unchanged
  1,351 predicted linked bytes (156 + 287 + 518 + 390). Index census:
  2026-11-05 05:17 at `c95fcfcfcd`. This is prediction, not a census gain.
- No source paths, ledger rows, pin identities or protected identity/data keys
  moved. No link-wide alias was removed.

## Initial merge trial and remaining work

The initial `tu_skeleton.py --merge .../GiantBirdAIUpdate.cpp --dry-run`
captured the pre-edit sources and accepted no donors. Its result is a baseline
diagnostic, not verification of the final sources. `tu_views.py --dry-run`
identified canonical-header work plus these independent conflicts:

- `GiantBirdAIUpdate` has opaque non-derived views in the append and waypoint
  donors; this repair resolves the append donor's base only.
- `Object` in DoLocomotor stores opaque bytes below the seed's Thing base.
- `ThingTemplateView` declares a byte at +0x108 in onCollide versus the seed's
  0x20-byte array at that offset.
- `Rva0026AFDAMember` constructors disagree on dllimport.

The seed also lacks donor method declarations (`onCollide`, `xfer`,
`privateFollowWaypointPath`), and merged constructor/append trials report an
AICommandType declaration-order error. The mixed Swoop donor stays untouched.
Next: reconcile the seed and one complete donor, then obtain a fresh guarded
merge trial. Source-file reduction is not claimed by this prerequisite repair.
