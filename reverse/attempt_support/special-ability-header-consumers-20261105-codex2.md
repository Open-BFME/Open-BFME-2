# SpecialAbilityUpdateModuleData consumer adoption, 2026-11-05

Inspected revision: `898e88e98f63ff50974f036d0cf00481ff6ca473`. Claim owner: `yasinschroeder-codex2`.

Three scalar consumers replace their private layout-only ModuleData views with
`Code/GameEngine/Include/GameLogic/Module/SpecialAbilityUpdateModuleData.h`:
`SpecialAbilityUpdateInitiateIntent.cpp`,
`SpecialAbilityUpdateIsWithinStartAbilityRange.cpp`, and
`SpecialAbilityUpdateRun.cpp`, all under
`Code/GameEngine/Source/GameLogic/Object/Update/`.

Target facts: the removed views contain fields only, no methods or data definitions.
Their accessed offsets map to the existing canonical header, including +0x70,
+0xB7, +0xB8, +0xBC and +0xC5, and the update consumer's +0x38/+0x44/+0x48,
+0x50/+0x78/+0xA0/+0xA4/+0xAE/+0xB4/+0xB5/+0xC6. Only accesses through
module-data pointers change spelling; identically named fields in other classes
remain untouched. No donor identity or new semantic name is asserted.

The nine-file automatic adoption trial restored all rejected candidates. Three
consumers needed scoped access substitutions because the automatic token renamer
refused ambiguous other-owner fields, comma expressions, or include discovery.
The six remaining queue entries are retained: two derived constructors write an
explicit vtable field that the canonical polymorphic base does not expose;
DockUpdate still declares its own ModuleData base; and the constructor, main
SpecialAbilityUpdate unit and trigger-effect unit use owning reference wrappers
instead of the canonical raw pointers. Those lifetime/hierarchy differences must
be reconciled against constructor/destructor and unwind evidence before retrying.

Verification:

- `find_declared_unmatched.py` passes all three sources before and after.
- `./build.sh` passes all 21 matched rows before and after, including the four
  funclet rows with renumbered labels; string, float and import checks pass.
- `link_check.py` ordinary combined preview against census `f44cbcf5b0`
  (2026-11-05 15:19) gives three LINKS, preserving 555 + 943 + 2340 = 3838
  authored bytes. This is a preview, with no new census or game-run claim.
- External definitions, read directly from original and final COFF symbol tables,
  are unchanged in every unit (5, 22 and 28 definitions respectively). There is
  no removed inline provider, data definition or linker alias.
- One `header_adopt_lane.py accept --class SpecialAbilityUpdateModuleData`
  invocation over the three sources passes and retires exactly three queue rows.
- `check_csv.py` and `git diff --check` pass.

Acceptance output:

```text
PASS Code/GameEngine/Source/GameLogic/Object/Update/SpecialAbilityUpdateInitiateIntent.cpp
  PASS Code/GameEngine/Source/GameLogic/Object/Update/SpecialAbilityUpdateIsWithinStartAbilityRange.cpp
  PASS Code/GameEngine/Source/GameLogic/Object/Update/SpecialAbilityUpdateRun.cpp
  retired 3 row(s) from reverse/header_queue.tsv; commit it with the adoption
```
