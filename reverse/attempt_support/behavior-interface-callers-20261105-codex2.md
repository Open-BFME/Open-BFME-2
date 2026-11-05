# BehaviorModule caller header adoption

Inspected revision: `285a631864`. Scope: `ScriptActionsModuleQuery.cpp` and
`GameLogicDestroyObject.cpp`; the class-header picker selected the
BehaviorModuleInterface cohort. Both files now include the existing canonical
`GameLogic/Module/BehaviorModule.h` instead of their private BehaviorModule and
BehaviorModuleInterface declarations.

Target facts already recorded in the sources: ScriptActions' cave-index caller
dispatches through interface slot 16, and GameLogic's destruction loop through
slot 6. Both interface subobjects are at module +0x0C. The canonical numbered
slots return `void *`; explicit casts preserve the existing consumer views.
The destruction loop uses a base reference conversion to retain the original
non-null subobject adjustment. No new slot name or shared-header change is
inferred from these consumers.

Verification:

- Before and after, `./build.sh` on the two full paths passes all 3/3 function
  rows, string, float and import checks. Declared-unmatched checks pass.
- `link_census.object_symbols` on saved before and current objects finds
  identical external definition and reference sets, weak externals,
  alternatenames and forced includes in each unit. No definition or alias is
  removed, so no external provider is lost. Neither object emits a module
  vtable. Their COMDAT name/digest/size maps are identical as well (4 and 9
  copies respectively).
- Before and after, `link_check.py` on both paths reports 2/2 LINKS with
  277 -> 277 scoped linked bytes (ScriptActions 84, GameLogic 193), using the
  published index at `f44cbcf5b0`, 2026-11-05 15:19 UTC. This is a preview,
  not a new census or real-link result.
- One `header_adopt_lane.py accept --class BehaviorModuleInterface` over the
  entire selected eight-file cohort passes these two files and retires exactly
  their two queue rows. The other six retain their prerequisites and queue rows.
- One `header_adopt_lane.py accept --class BehaviorModule` over both changed
  files passes and retires their two related queue rows. Four header-debt rows
  leave through the owning acceptance tool in total.

The automatic adoption trial reproduced recorded cohort failures and retained
no changes. Constructor/interface-provider prerequisites documented in the
existing canonical-module caller entries remain outside this repair. Source
paths, ledger identities and shared headers are unchanged.
