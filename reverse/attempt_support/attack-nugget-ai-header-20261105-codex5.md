# AttackNugget canonical AI interfaces

Inspected revision: `983951fcc1`. Scope:
`Code/GameEngine/Source/GameLogic/Object/AttackNuggetCreate.cpp`.

The ObjectCreationList merge dry run listed AICommandInterface and
AIUpdateInterface as this donor's header prerequisites. The donor privately
declared AIUpdateInterface as only an AICommandInterface base and added a
non-retail inline helper to AICommandInterface. Canonical AIUpdate.h instead
declares the full update module and its command-interface subobject.

The repair includes canonical AIUpdate.h and removes both private declarations.
The existing inline command expansion is now a static, forced-inline helper
receiving AICommandInterface explicitly. The caller still passes container
+0x20, the command-interface address used by the matched retail body; it no
longer calls that address an entire AIUpdateInterface. The out-of-line
AICommandInterface::aiAttackPosition provider is unchanged.

Verification:

- `./build.sh Code/GameEngine/Source/GameLogic/Object/AttackNuggetCreate.cpp`:
  **4/4 exact**, including both parent-bound cleanup funclets; string, float
  and import reference checks pass. Compiler label renumbering is resolved
  through the existing parent EH data.
- `find_declared_unmatched.py` before and after: all definitions already matched.
- `header_adopt_lane.py accept --class AICommandInterface ...` and
  `--class AIUpdateInterface ...`: both PASS; each retires its own header-queue
  row. No other debt keys are removed.
- `link_check.py` with census/index `c95fcfcfcd` (2026-11-05 05:17): **LINKS**,
  LINKED **272 -> 272 bytes** for this source. This is a bounded preview, not
  a new census or linking gain.

The completed initial TU dry run accepted zero donors. It still reported the
seed's stale-index reference to Rva0076B063ClearFlag and the existing class and
include prerequisites documented in LINK-488. That run began before this
header repair; it is not a post-repair merge verdict. No source path moved,
and this change does not claim to clear LINK-488.
