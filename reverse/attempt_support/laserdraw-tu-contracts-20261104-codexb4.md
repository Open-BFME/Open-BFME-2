# LaserDraw composition reaches the shared virtual-table boundary

Inspected revision: `a80b34d8d3`, 2026-11-04. Scope:
`Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DLaserDraw.cpp`
and its constructor, draw, destructor and asset-reference-overflow donors.
The supported consolidation planner was refreshed after the source changes;
the merge rebuilt the stale TU map in memory. No map was committed.

## Published prerequisites

- `7cd2cf3b7a` gives the destructor the approved TU's typed vector shell.
- `a80b34d8d3` replaces the approved TU's padding at +0x0C through +0x1F
  with the secondary laser interface, line-array pointer and typed vector.
  Those positions are established by the existing retail constructor and
  destructor, rather than inferred from a donor path. It also makes the
  module-data cast explicit and supplies the TU-local inline DrawModule
  destructor needed by retail's laser teardown.

`./build.sh` verifies all 23 bodies across the approved TU (18) and destructor
(5), plus its one data row. The commit hook also reports four exact EH rows,
all five renumbered funclet pins verified, and passing string, float and
converged-data checks. `find_declared_unmatched.py` is clean for both files.

The ordinary `link_check.py` preview over both current objects says LINKS for
both, against census 2026-11-04 17:56 at `8c757ea0db`. This is a local preview,
not a new census measurement or a headline gain.

## Final ordinary merge trial

Command: `python3 tools/tu_skeleton.py --merge
Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DLaserDraw.cpp
--dry-run` (one command line).

The destructor composition now preserves all 23 baseline bodies and reaches
LinkGuard. Before the inline destructor definition, it called
`??1DrawModule@@MAE@XZ`; retail instead inlines that destructor and calls
`??1DrawableModule@@MAE@XZ`. Fixing this exposed the actual link boundary:

```text
comdat ??_7DrawModule@@6B@ (first)
breaks another unit's copy of ??_7W3DLaserDraw@@6BDrawModule@@@
```

This is the DrawModule family conflict already recorded in LINK-177: the
canonical 62-slot table disagrees with the kept private-view copy. LaserDraw
also has its constructor's short primary-table view to reconcile. The merge
accepted no donor, deleted no source and changed no ledger ownership.

Other donors retain separate blockers: the constructor redefines RefCountPtr
and ModuleData; the draw donor collides on Coord3D and AsciiString in the ZH
header world; the asset-reference overflow donor loses bytes under composition.
The existing DrawModule/DrawableModule/RTS3DScene header-queue entries remain;
no queue key or other debt was retired.

## Shadow findings and next step

The commit hook surfaced a divergent inline ModuleData destructor and three
data findings in the approved TU. A before/after scratch-object comparison
against the parent of `a80b34d8d3` confirms the ModuleData destructor retains
COMDAT digest `c88b6d4dab56` and size 7. Running data-check's fact extraction on
both scratch objects yields the same three findings, with no unread rows:
duplicate-def and wrong-name for `_DRAWABLE_FRAMES_PER_FLASH` at 0x009EBB68,
and wrong-name for the getModuleNameKey static guard at 0x009EBB64. No baseline
was changed. These findings predate this layout reconciliation.

Next: reconcile the shared DrawModule destructor/table contract and the laser
constructor's primary table before retrying this merge. Check all affected
COMDAT consumers together, including untouched siblings, as LINK-177 requires.
Do not suppress table emission or move the otherwise matching destructor past
the link guard. The current census has not confirmed any change from this pass.
