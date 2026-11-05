# TerrainLogic saved-work recovery, 2026-11-05

Inspected checkout `70d173d45a8007f9f76889de0b0854bdfbd623f0`.
Preparation was stopped while applying stash
`8c18d6d6dff956acfb1dea4b09f22e0310f19fc2` (phase `restoring`).
The backup ref and stash remain intact. `git cherry HEAD` reports all three
preserved commits equivalent to upstream; exact pairs are in `manifest.json`.
The stash contains twenty tracked edits and no saved untracked files.

## Reconciled scope

Eight available file scopes were claimed. Their saved private TerrainLogic
views are replaced with the canonical header. Call sites now select that
header's established virtual methods and argument types: slot 7 uses
`getLayerHeight`, slot 8 `getExtent`, slot 15 `isClearLineOfSight`, slot 34
`getWaypointByName`, and slot 43 `objectInteractsWithBridgeLayer`.
Integer layer accessors are explicitly converted to `PathfindLayerEnum`.
The goal-position helper uses canonical Region3D bounds. These are header
contract adaptations; the enclosing address-derived identities remain intact.
Target virtual-slot facts come from the canonical header's retail evidence;
no new donor-name or layout claim is made here.

`./build.sh` on the eight files passes 47/47 matched rows, all string and
float references, and source claims. `header_adopt_lane.py accept --class
TerrainLogic` passes every file, including its ordinary per-unit link
preservation check, and retires exactly eight TerrainLogic queue rows.
See `byte-verification.txt` and `header-acceptance.txt`. The initial missing
member / argument-type diagnostics are in `initial-diagnostics.txt`.
No census gain, real-link completion or class-wide clearance is claimed.

## Deferred saved edits

Twelve scopes were refused because another worker holds them; they were
restored to current HEAD without further source edits. Their original changes,
and the original pre-reconciliation changes for the accepted eight, are
preserved verbatim in `saved-edits.patch`, with its hash and all source paths
in `manifest.json`. Do not apply this patch wholesale: eight parts are already
recovered, and the remaining consumers need fresh claims and current-header
call-site reconciliation before normal byte/link/header acceptance.

The sole restore conflict was `HordeContainUpdatePosition.cpp`: upstream
already includes the canonical AI header, while the saved side includes the
canonical TerrainLogic header and retains an obsolete private AI view. Because
this scope is held, the file is restored to upstream and its TerrainLogic edit
remains saved. A later recovery should keep upstream's AI include and adopt
TerrainLogic without restoring that obsolete AI class. No source conflict
markers remain. Other workers' scopes and queue entries remain untouched.

No saved edit is discarded: eight are recovered and twelve are banked here.
The recovery creates no new task selection or source-path move.
