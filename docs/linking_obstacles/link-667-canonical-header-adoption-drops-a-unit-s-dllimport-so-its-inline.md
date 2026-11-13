### LINK-667: canonical header adoption drops a unit's `__declspec(dllimport)`, so its inline adapter is emitted under a retail-addressed name
Status: Repair committed / awaiting landing and census confirmation (one instance). Updated: 2026-11-13 (seat
halilkkaya-rg1); base `d605b7a1a05`, census index `16b6c8496e` (census `b25a313d87`).

**Problem.** Some units declare a member `__declspec(dllimport)` in their private view and give it a unit-local
`__forceinline` body: an inline function declared dllimport is expanded where it is called, and cl never emits an
out-of-line copy of it (the out-of-line copy is the "imported" one). When a canonical header replaces the view,
the declaration loses `dllimport` while the unit keeps its `__forceinline` definition. cl then emits that
definition as a COMDAT under the member's mangled name, even when every call is expanded and nothing references
it. If that name has a retail address (a `reverse/symbols.csv` entry or a pin), the census judges the COMDAT
against retail's body there, finds a different body, and the unit stops linking. The byte gate cannot see it:
every rowed body, including the caller, is unchanged.

**Instance.** "Register canonical Rva002CB35CObj, adopt it in 6 units" (`c60d73cdc88`, StarkillerHDX) replaced
pathfinder.cpp's view `class Rva002CB35CObj { __declspec(dllimport) Bool rva002CB35C(...); };` with the
generated header, which declares `bool rva002CB35C(...)`. pathfinder.cpp defines
`__forceinline Bool Rva002CB35CObj::rva002CB35C(...)` as a forwarder to `Weapon::isWithinAttackRange`, which
`Pathfinder::CheckForTarget` (0x002F2FA4) expands. After the adoption the object also defines a 39-byte COMDAT
`?rva002CB35C@Rva002CB35CObj@@QAE_NHPAX00MH@Z` (no relocation in the object references it). `symbols.csv` gives
that name 0x002CB35C, retail's 568-byte `Weapon::isWithinAttackRange`. The census index at `3159214f04` has no
definition of the name anywhere; the index at `16b6c8496e` has pathfinder.obj's copy, verdict `wrong`.
- pathfinder.cpp: census 2026-11-13 01:15 (`e5da954ea6`) "yes", 50,353 B; census 04:18 (`6e37424cf7`) "no"
  (comdat loser + wrong selected, the same symbol). This is almost all of the 50,560 B the 04:18 census lost.
- The commit was not in `e5da954ea6` and is in `6e37424cf7`. The other pathfinder.cpp commit in that range,
  "Register canonical PathfinderCostCellInfo in 6 units" (`a7019a1599b`), swaps `struct { Int x,y; }` for the
  same layout and changes nothing in the object.

**Repair.** "Call Weapon::isWithinAttackRange directly in Pathfinder::CheckForTarget" removes pathfinder.cpp's
forceinline definition (and its `absent-from-retail` marker) and casts the weapon in the one call site:
`((Weapon *)weapon)->isWithinAttackRange((Object *)obj, &pos, (Object *)a5, (const Coord3D *)a6, 10.0f, true)`.
No header, contract or ledger row changes. Object diff (objcmp, HEAD -> repair): 646 -> 645 symbols, the one
COMDAT removed, nothing changed (CheckForTarget's bytes and relocations included). `./build.sh` 120/120 exact.
link_check (`16b6c8496e`) over pathfinder.cpp, the other five units that include `Rva002CB35CObj.h`
(Rva002EC3CEProbe.cpp, which calls the name, and four Pathfinder units) and PathfinderConstructor.cpp: 7/7 LINKS,
LINKED 6,281 -> 56,634 B (pathfinder.cpp 0 -> 50,353, the other six unchanged).

**Scan.** Every `__declspec(dllimport)` member a commit since 2026-11-09 removed from a `Code/` view, excluding
CRT and Platform SDK declarations: Rva004F60AA (StlSweepW4Rva004F8C16.cpp), RefCountClass (two units),
Matrix4 (fxshadernamespacesas.cpp), BaseA (AIEconomyBuilder.cpp), isKindOf (ScriptConditions_evaluateTeamStateIs.cpp),
rva0057FFB9 (AptMpGameSetup.cpp), BehaviorModuleData (RampageBehavior.cpp,
FireWeaponWhenDeadBehaviorModuleDataCtor.cpp). Those nine units LINK at their census bytes (30,018 B). Eight
had their inline bodies in the class, and the bodies went with the view. AptMpGameSetup.cpp still defines
`Rva0057FD6E::rva0057FFB9` outside the class, but its header `GameClient/Rva0057FD6E.h` (hand-written, not
generated) keeps `__declspec(dllimport) __forceinline`, and the object defines no copy of it. Only pathfinder.cpp
lost the `dllimport` and kept a definition.

**Recipe.** When a unit defines an adopted class's member inline outside the class and its old view declared
that member `dllimport`, the adoption must not keep that definition. Call the real target at the call site, or
use a unit-local `static` helper. Compare the unit's object symbols before and after an adoption: a new COMDAT
under a name with a retail address is this regression.

**Tooling lead (not edited).** `header_adopt_lane.py apply` could refuse an adoption after which the unit's
object gains a COMDAT whose name has a retail address (`symbols.csv`, the ledger), the same way LINK-660 asks for
`??_7`/`??_G`.
