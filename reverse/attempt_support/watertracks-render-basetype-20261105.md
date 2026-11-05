# WaterTracks render include prerequisite

Inspected 2026-11-05 at `1d123cff0d`; owner `yasinschroeder-codex5`.

The approved `W3DWaterTracks.cpp` merge has two eligible donors:
`WaterTracksObjRender.cpp` and `WaterTracksRenderSystemFlush_Flush.cpp`.
Both dry runs accepted zero donors. No files moved and no ledger rows changed.

## Completed prerequisite

The render donor included Zero Hour's `Lib/BaseType.h`, although it uses only
`Coord3D` and the primitive aliases `Int`, `Real` and `Bool` from that header.
Replace that include with the project's canonical `Coord3D.h` and the identical
`int`, `float` and `bool` aliases. This avoids the initial `Coord3D`/geometry
redefinitions when composing the donor with the seed's include world.

Verification:

- `./build.sh Code/GameEngineDevice/Source/W3DDevice/GameClient/Water/WaterTracksObjRender.cpp`
  before and after: 1/1 ledger bodies exact (2,413 bytes), 11/11 compiler float
  constants exact, all defined functions already matched.
- Saved the original object and compared `tools/class_cleanup.py`'s
  `runtime_graph` results with `same_runtime`: true. All 29 non-debug sections,
  28 external providers, relocation targets, weak bindings and COMDAT policies
  are equivalent under section renumbering. Whole-object hashes differ because
  debug/source metadata changes; runtime equivalence is the relevant check.
- `python3 tools/link_check.py` for the changed source: LINKS, 2,409 -> 2,409
  census-linked bytes. This is a preview against the published 2026-11-05
  05:17 census at `c95fcfcfcd`, not a new census or headline gain.
- The post-change `tu_skeleton.py --merge .../W3DWaterTracks.cpp --dry-run`
  passed the original render include collision and stopped at `m_waveDir`
  missing from the retained seed class. Both donors remain rejected.
- No gate-baseline, identity, data, header-queue or hatch keys were retired.
  No linker aliases or providers were removed. `git diff --check` passed.

## Remaining consolidation prerequisites

`tu_views.py .../W3DWaterTracks.cpp --dry-run --class WaterTracksObj` reports
that the render donor's `m_unmodelled00` starts at +0 while the seed has an
implicit vfptr, so own data starts at +4. Reconcile the object views on proven
offsets and the bounds/texture member dependencies before rerunning the merge;
renaming fields alone will not repair this structural mismatch.

The flush donor still fails composition at `TextureClass` and the graphics
`statistics.h` header world. Its canonical `WaterTracksRenderSystem` adoption
belongs to the header lane. The earlier handoff
[`watertracks-unused-cleanup-20261104.md`](watertracks-unused-cleanup-20261104.md)
also records the bounds dependency failure; this pass did not repeat or claim
to solve it.

All three sources are census-linked, so their provider/link guard must remain
enabled for any later merge. No completed TU recovery is claimed by this
prerequisite change. No matching linking-obstacle entry was found for these
units, and no new unresolved linker symbol was encountered in this pass.
