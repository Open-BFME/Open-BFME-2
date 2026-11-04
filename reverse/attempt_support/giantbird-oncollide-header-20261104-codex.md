# GiantBird collision header adoption, 2026-11-04

Inspected revision: `519ec17c54`.
Scope: `Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/GiantBirdAIUpdateOnCollide.cpp`, retail RVA `0x003698CD`, 238 bytes.

The consolidation picker claimed the GiantBird TU and its eight donors. The
current view planner reports canonical-header prerequisites for AIUpdateInterface
and AICommandInterface, in addition to independent Object, GiantBirdAIUpdate,
and ThingTemplateView layout conflicts. The collision donor used private AI
interfaces, including the obsolete parameterless command slot. It now includes
`GameLogic/Module/AIUpdate.h`; its derived class keeps the existing inline
state-machine accessor, projecting the canonical AIStateMachine pointer to the
already adopted StateMachine view. The field remains at +0x30; no header changed.

Verification:
- `./build.sh` before and after: 1/1 matched, 238 bytes; string, float and import checks pass.
- `find_declared_unmatched.py`: all defined functions already matched.
- `header_adopt_lane.py accept --class AIUpdateInterface` and then
  `--class AICommandInterface`: PASS, each retired its one header-queue row.
- `link_check.py --prepare-current`: strict reusable provider receipt obtained.
- `link_check.py` on the source: LINKS, LINKED 238 -> 238 bytes, prediction
  against census 2026-11-03 20:03 at `8661f15284`. No census or headline change claimed.

This removes two header prerequisites, not the remaining multi-class merge
conflicts. Source-layout survey: `name_lane.py consolidate --under
Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/` found the retail path
at image RVA `0x00816DD8`; it does not itself authorize a merge.
