# W3DView consolidation trial and receiver-view prerequisite

Inspected revision: `8f21ac2162`; owner: `yasinschroeder-codexb5`.
Scope: `Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DView.cpp`
and its 43 whole-file donor candidates, claimed before investigation.

## Supported trial

`tu_skeleton.py --merge Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DView.cpp --dry-run`
completed after approximately 38 minutes with exit 2:
`accepted: []`, `blocked: no verified merge of two or more donors`.
There were 18 mixed sources and two refused sources; none moved.
The current seed alone passes 45 matched function rows, 11 data rows,
one string literal, four float literals and two funclet pins.

The completed trial supersedes the interrupted October trial's unknown
outcome, but does not establish a verified merge. Representative boundaries:

- Coord3D/Region3D, AsciiString and ParabolicEase redefinitions prevent
  compilation of multiple donors with the seed.
- W3DView private views omit members used by other donors; the fade setter
  also encounters protected ScreenCrossFadeFilter fields.
- CameraPathAnglesBFME2.cpp, Rva0008B5B5VectorReserve.cpp and
  StlportVectorOverflow0008B503.cpp fail byte verification in the trial.
- StlportVectorReserve0008B5B5.cpp fails the existing link guard: the merged
  object would lose the census-linked unit through the retail COMDAT
  `??$_M_allocate_and_copy@PAURva0008DE1CElement@@@?$vector@URva0008DE1CElement@@V?$allocator@URva0008DE1CElement@@@_STL@@@_STL@@IAEPAURva0008DE1CElement@@IPAU2@0@Z`.

The supported `name_lane.py consolidate --under Code/GameEngineDevice/Source/W3DDevice/GameClient/`
planner and its snapshot currency check pass with no missing inputs.
Its W3DView investigation group has 44 files and 43 potential removals,
but is unverified. CameraPathAngles has an internal-linkage/pragma/include
review boundary. Its original-placement evidence is a stale-map interval
and a WorldBuilder pairing hint, with W3DView.cpp the sole alternative;
these hints independently approve neither a merge nor a new TU placement.
No TU-map update or source move is part of this change.

## Applied prerequisite

The compiler-layout-backed `tu_views.py` report found one compatible class
whose declarations still differed: Rva00089510. The angle body declared
an empty receiver while W3DViewRva0008A2EF.cpp already declared its existing
Rva000869CF base. Include that base's existing canonical header in the
angle unit, then apply:

```
python3 tools/tu_views.py Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DView.cpp --class Rva00089510 --no-merge-check
```

Both files now carry the same receiver declaration. The tool verified its
planned layout, normal byte builds, no new unrowed definitions, and unchanged
external definitions/references. Its 0x24CC extent is the existing caller
view's extent, not newly established retail layout evidence. No donor name
or retail inheritance recovery is claimed. The full merge was not repeated
after this declaration-only prerequisite, so no acceptance gain is claimed.

Final checks:

- `./build.sh` on both changed files: 3/3 matched rows, four compiler float
  literals, no skipped literals or named imports.
- `find_declared_unmatched.py` on both files: all definitions already matched.
- `class_cleanup.runtime_graph` before/after for CameraPathAngles: exact
  runtime equality, including all 17 non-debug sections, relocations,
  COMDAT policies and 14 external definitions; no weak bindings.
- Census-only and current-object link previews both report 328 -> 328 bytes
  for CameraPathAngles and 1,140 -> 1,140 for W3DViewRva0008A2EF, against
  census 2026-11-04 07:28 at `a62ac1c10b`. These previews are not a new census.
- Scoped register search found 50 header-queue and 24 hatch lines, with no
  data, code-identity or MS-header keys. All register ownership and hatch
  lines remain unchanged; no source is deleted and no alias is removed.

Next work: reconcile a specific compiler rejection above using the owning
header/private-view lane before another exhaustive trial; retain the COMDAT
link guard. No source-file, linked-byte or debt headline gain is claimed.
