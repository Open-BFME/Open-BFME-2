# Projected-shadow consolidation trial

Target: `Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DProjectedShadow.cpp` at `e064f13279` (the trial started before the two cleanup/handoff commits).

`name_lane.py consolidate --under Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/` produced the planner snapshot. `find_declared_unmatched.py` reported all defined functions matched. The supported `tu_skeleton.py --merge <target> --dry-run` was polled, then interrupted after approximately 20 minutes without a completed report. This is an **unverified trial**, not a merge rejection or a passing link check. No donors moved, no rows changed and the tool removed its temporary source.

During the trial, the verified stale Region3D allowance removal changed the source tree and hatch register; `name_lane.py consolidate --check build/consolidation` consequently reported that snapshot stale. Regenerate it before any future application.

The separate read-only `tu_views.py <target> --dry-run` reported existing base/layout conflicts: W3DShadowTexture's base clauses differ, Rva007B1380's donor member at offset zero overlaps the destination base, and ShadowBoundsCall has no measured CodeView layout. These diagnostics do not establish a compilable merge. The prior consolidation handoff in `reverse/re_attempts.log` (search `tu-merge:` and this target) remains the starting point; no prerequisite is claimed repaired here.
