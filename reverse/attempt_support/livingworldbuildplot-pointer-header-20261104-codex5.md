# LivingWorldBuildPlot pointer-holder prerequisite

Inspected revision: `f50864c77d179cff2078067954336d51aea7f0aa`. Owner: `yasinschroeder-codex5`.

The default picker selected TU consolidation of
`Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldBuildPlot.cpp`.
All four claimed source files passed the declared-unmatched check before edits.
The consolidation planner was run for `Code/GameEngine/Source/GameLogic/System/LivingWorld/`;
its current packet reports mixed routing, compiler-setting differences and
canonical-header prerequisites. The merge tool rebuilt the stale TU map in
memory; no map or source path was changed.

## Verified prerequisite repair

Replace the seed's private `Rva000AD6F4` body with its registered header.
The registered holder stores `void *`, so explicitly cast its pointer to the
existing `Rva004E0B60` pointee view at the single method call. This preserves
the holder's identity without asserting a new pointee type in the shared header.
No names, pins, aliases, ownership rows or hatch counts change.

Both the original and resulting TU pass `./build.sh` with **14/14** matched
rows, including the two compiler funclets resolved through parent EH data.
The resulting declaration check passes.
`header_adopt_lane.py accept --class Rva000AD6F4` reports PASS and retires
exactly this source's queue row. Other header-queue entries remain.
Code/data debt registers contain no matching source key to transfer or retire;
the existing Snapshot hatch remains unchanged.

The scoped naming packet for the complete inspected `Rva004FC470::rva004FC470`
function inventories two bindings. Native child proposal, parent preview/review
and scoped application retain `flag` (domain meaning uncertain) and `result`
(already clear), with no source rename.

## Current-object link preview

This is a scoped prediction, not a new census or real-link measurement.

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldBuildPlot.cpp: LINKS  LINKED 676 -> 676 bytes (census 2026-11-04 16:16 at 2f0cb97f52; file's own bytes 676)
link_check: 1 of 1 link cleanly; LINKED 676 -> 676 bytes (5.2s)
```

## Remaining consolidation prerequisites

The new dry run still accepts no donor, and writes no source/ledger changes.
The destructor donor now reaches the differing base classes: its cast to
`_STL::vector<ObjectID>` cannot compile against the seed's
`Rva00330757Member` base. The transfer donor now reaches `DoXfer` missing from
the seed's class view (`xfer` occupies its corresponding surface). The constructor
donor still fails without a quoted compiler diagnostic. Do not infer virtual-slot
identity or change a base from this compiler output alone.
`tu_views.py --dry-run --no-merge-check` reports the other immediate conflict:
`Rva004FC320Listener` slot 0 is `notify(void*)` in the seed but `slot0()` in the
destructor donor. Other eligible noncanonical views are already shared; the
registered classes require header-lane work. Reconcile those class/base/slot
contracts before another merge trial. The 2026-10 prior TU attempt in
`re_attempts.log` already reported the `DoXfer` surface conflict; this pass does
not claim a newly discovered regression.

Exact post-repair trial:

```text
tu: Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldBuildPlot.cpp
approved: 42
mixed: {'Code/GameEngine/Source/Common/OpaqueScalarDeletingDtorsB11.cpp': 18, 'Code/GameEngine/Source/Common/Rva004FA738ListenerWalks.cpp': 14}
refused: {}
accepted: []
rejected: {'Code/GameEngine/Source/Common/Rva004FC4D1Dtor.cpp': "compile: Code\\GameEngine\\Source\\GameLogic\\System\\LivingWorld\\.LivingWorldBuildPlot.1b1f9b23f9bda6f7.tu_skeleton.cpp(480) : error C2440: 'static_cast' : cannot convert from 'LivingWorldBuildPlot *const ' to '_STL::vector<_Tp> *' | Code\\GameEngine\\Source\\GameLogic\\System\\LivingWorld\\.LivingWorldBuildPlot.1b1f9", 'Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldBuildPlotDoXfer.cpp': "compile: Code\\GameEngine\\Source\\GameLogic\\System\\LivingWorld\\.LivingWorldBuildPlot.ce35dc78b1909987.tu_skeleton.cpp(525) : error C2039: 'DoXfer' : is not a member of 'LivingWorldBuildPlot' | Code\\GameEngine\\Source\\GameLogic\\System\\LivingWorld\\.LivingWorldBuildPlot.ce35dc78b1909987.tu_skeleton.cpp(529) : erro", 'Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldBuildPlot_Unresolved.cpp': 'compile: '}
adopt_first: {'Code/GameEngine/Source/Common/Rva004FC4D1Dtor.cpp': ['LivingWorldBuildPlot', 'LivingWorldLogic'], 'Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldBuildPlot.cpp': ['LivingWorldBuildPlot', 'LivingWorldBuilding', 'LivingWorldRegion', 'Rva00575674'], 'Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldBuildPlotDoXfer.cpp': ['LivingWorldBuildPlot', 'LivingWorldBuilding', 'LivingWorldLogic', 'Rva00575674'], 'Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldBuildPlot_Unresolved.cpp': ['LivingWorldBuildPlot', 'LivingWorldRegion', 'Rva00575674']}
link_guard: census-linked: Code/GameEngine/Source/Common/Rva004FC4D1Dtor.cpp, Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldBuildPlot.cpp, Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldBuildPlotDoXfer.cpp, Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldBuildPlot_Unresolved.cpp
blocked: no verified merge of two or more donors
reconcile_classes: ['LivingWorldBuildPlotIcon', 'Rva003F1BD3TemplateView', 'Rva004FC320List', 'Rva004FC320Listener']
reconcile: python3 tools/tu_views.py Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldBuildPlot.cpp --dry-run, then without --dry-run: the donors declare their own views of LivingWorldBuildPlotIcon, Rva003F1BD3TemplateView, Rva004FC320List, Rva004FC320Listener (docs/consolidation.md, "Workflow per TU", step 4)
```

No files were consolidated and no linked-byte gain is claimed. This change's
measured progress is one retired header-queue row with matched coverage retained.
No source-path move occurred, so the outgoing tooling path-consumer audit is
inapplicable. Existing linking-obstacle entries were searched by unit and
symbols; none of their Snapshot, building-constructor or client-funclet causes
is resolved or changed by this holder-only adoption.
