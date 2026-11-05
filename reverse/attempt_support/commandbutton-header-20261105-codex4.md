# CommandButton header adoption, 2026-11-05

Inspected source revision: `10b5d79f48`. Claim owner: `yasinschroeder-codex4`.

Adopted the existing `GameClient/CommandButton.h` in:

- `Code/GameEngine/Source/Common/RTS/PlayerRva002AD1FD.cpp`
- `Code/GameEngine/Source/GameClient/InGameUICanSelectedObjectsDoAction.cpp`
- `Code/GameEngine/Source/GameClient/InGameUIFormationFinalize.cpp`
- `Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActionsAutoAbility.cpp`

The old views contained only fields and padding: no method body, data definition,
alias or other symbol provider was removed. No shared header changed. Replaced
accesses use the header's documented native offsets: command +0x14, options
+0x1C, special-power pointer +0x44, weapon slot +0x80 and auto-ability +0x10C.
The Player helper now retains the special-power pointer's const type instead of
passing it through `void *`. The weapon access uses the existing typed accessor.

Checks:

- `find_declared_unmatched.py` passes before and after for all four sources.
- `./build.sh` on the four sources: 9/9 functions match, including the generated
  funclet through parent EH data; string, float and import checks pass.
- One `header_adopt_lane.py accept --class CommandButton` over the full 14-file
  queued cohort accepts these four sources and retires exactly four rows. The
  other ten remain queued; none of their trial edits was retained.
- Combined `link_check.py` preview on the four sources, published index
  `f44cbcf5b0` (2026-11-05 15:19): 4/4 LINKS, 2,335 -> 2,335 census-linked bytes
  (93, 1,292, 688 and 262 respectively). This is a preview, not a new census or
  real-link measurement.
- `git diff --check` and `check_csv.py` pass.

Remaining cohort work needs container-view reconciliation, Overridable layout
reconciliation or methods missing from the canonical declaration. Those units
are unchanged; this clearance covers only the four field-only views above.
