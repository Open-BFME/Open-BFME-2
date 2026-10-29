# HeightMap optimization hatch cleanup

Inspected base `722e87427f3411f9210c79778d7ca4a99582a8cd`, 2026-10-29.
The default picker claimed HeightMap.cpp for its 107 authored bytes. The
published index `85f6b7f40c` (15:08) still reports 35 unresolved references,
including the ZH-shaped DX8 buffer constructors, terrain interfaces and shader
manager APIs. This agrees with the assigned W3D dependency audit in the obstacle
register: these are retained port-context dependencies, not proven missing
native bodies. The six matched rows are five RenderObjClass flag setters and
RTS3DScene::getCustomPassMode, not the unrowed terrain methods.

The two optimization pragmas around multilist.h are redundant under the TU's
existing `/O1` setting. Removing them preserves all 230 external COMDAT
name/digest/size tuples, 27 exclusive definitions, 146 undefined references,
one weak alias and the empty COMMON set. No provider or binding changes.
The comparison assigns a constant truth verdict: equality proves the emitted
facts are unchanged, not that every inline copy matches retail. Object hashes,
comparison hashes and counts are in the adjacent
[receipt](heightmap-optimize-20261029-codex.json).

Checks:

- `./build.sh Code/GameEngineDevice/Source/W3DDevice/GameClient/HeightMap.cpp`
  passes 6/6 before and after; literal, float and import checks pass.
- `find_declared_unmatched.py` passes before and after with the same 35
  registered unclaimed definitions.
- `link_check.py --prepare-current` passes with strict reusable receipts.
- Ordinary before/after preview retains 0 linking authored bytes and the same
  35 unresolved references against `85f6b7f40c`.
- The hatch register loses only the two HeightMap pragma keys. The owning
  `--update` also found unrelated stale present-unmatched keys; those unrelated
  changes were excluded from this commit.

The terrain class/header and native provider contracts remain prerequisites
for a link repair. Preserve matched inline emission while reconciling those
contracts. Carry this provider and its affected consumers into the next normal
census; no census gain or consumer-wide clearance is claimed.
