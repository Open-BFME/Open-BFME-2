### LINK-160: dropping PartTheHeavensUpdate.cpp's link-wide alternatename unresolved 23 linked units' update slot (2026-10-30, seat halilkkaya-lk8)

Status: 17 units repaired; 6 remain (needs identity work or another seat's file).
`6e9a7c16cc` (after census 2c21184e84) removed PartTheHeavensUpdate.cpp's
`/alternatename:?update@UpdateModuleInterface@@UAEXXZ=?update@PartTheHeavensUpdate@@...`
as dead. It was not dead: 24 other census-linked units' private
`UpdateModuleInterface { virtual void update(); }` views make their update-interface
vftable (slot 0) name `?update@UpdateModuleInterface@@UAEXXZ`, which only that
link-wide alias resolved. Current-object `link_check` over the 25 referencing
units: 1 links, LINKED 17,456 -> 858 B (a 16,598 B loss waiting for the next census).
Retail fills each class's update-interface table slot 0 with its own update
(data-ledger table addresses read from retail: e.g. 0x0084B83C ->
`?update@DozerAIUpdate@@UAE?AW4UpdateSleepTime@@XZ` 0x00489800). Fix in 17 files:
the view's interface declares `virtual UpdateSleepTime update() = 0` and the class
declares its rowed `UpdateSleepTime update()` override, so each table names the
retail row (no alias, no new hatch). Verified: `./build.sh` 149/149 rows over the 17
files; scoped DIR32 OK (106 symbols); `link_check` over the 25 units 858 ->
16,104 B (18 link). Still unresolved: GettingBuiltBehaviorCtor/Dtor.cpp (slot 0
0x00454DF9 is rowed `?update@GettingBuiltBehaviorUpdateReceiver@@QAE...`),
RebuildHoleBehaviorDtor.cpp (0x00483645 `?update@Rva00483645@@QAEHXZ`),
WallHubBehaviorCtor.cpp (0x004A6563 `?Rva004A6563Get@@YAHXZ`, a folded constant
getter), AISpecialPowerUpdateDtor.cpp (0x004B327F `?update@Rva004B327F@@QAEHXZ`),
FireWeaponWhenDeadBehavior.cpp (0x00482BB9 `?update@Rva00482BB9@@QAEHXZ`): each needs
the row respelled as the class's virtual update (a signature change). 
GiantBirdAIUpdateCtor_GiantBirdAIUpdate.cpp (518 B) takes the same two-line fix
(`?update@GiantBirdAIUpdate@@UAE?AW4UpdateSleepTime@@XZ` is rowed) but is held by
a TU-merge seat. 2026-10-30 (Noro420): GiantBirdAIUpdateCtor_GiantBirdAIUpdate.cpp
took that fix (interface `virtual UpdateSleepTime update() = 0`, class declares the
rowed `update()`); `./build.sh` 6/6 rows; `link_check` 0 -> 518 B (LINKS). Census
confirmation pending. Pattern: before removing a link-wide alternatename, grep every
object for its source name, not only the defining unit.
Same pattern, second case: `14810fae7b` replaced FXParticleSystem.cpp's
`?v1@DefaultAlphaModuleInfo/DefaultColorModuleInfo@FXParticleSystem@@UAEXXZ`
aliases with real `LoadPostProcess` rows (0x000B3FD0), but the two ctor thunks
(`DefaultAlphaModuleInfoCtorThunk.cpp` 70 B, `DefaultColorModuleInfoCtorThunk.cpp`
92 B, both census-linked) still named `v1` in their vftables: unresolved, and
their copies then differed from FXParticleSystem.cpp's. The thunks' views now
declare `LoadPostProcess` in that slot; both tables equal the first copy.
`./build.sh` 6/6; scoped DIR32 OK; `link_check` 0 -> 162 B for the thunks
(FXParticleSystem.cpp 5,650 B unchanged). A sweep of all 49 alternatename source
names removed on master since census 2c21184e84 against current objects finds no
other unprovided reference except yasinschroeder's in-flight STLport 4.6 string
chain, whose helpers (`find_if`, `find_end`, `__find_first_of`) are provided by
units outside this preview (inconclusive, not a confirmed loss).

2026-10-30 (halilkkaya-rn1): `rename.py function --virtual` now respells a row
non-virtual -> virtual on retail vtable evidence (docs/naming.md). It does not
clear the remaining LINK-160 rows: each slot is real, but it belongs to another
class than the row's (`--virtual --dry-run`: 0x00454DF9's table 0x00C40434 is
GettingBuiltBehavior's, not GettingBuiltBehaviorUpdateReceiver's; 0x00483645 ->
0x00C49A68 RebuildHoleBehavior; 0x004B327F -> 0x00C56D50 AISpecialPowerUpdate;
0x00482BB9 -> 0x00C496E8 FireWeaponWhenDeadBehavior; 0x004A6563 is a free
function), and the placeholders also return `int` where the table wants
`UpdateSleepTime`. Remaining prerequisite: class identity (merge each placeholder
or receiver class into the module class) plus the return type, then the
two-line view fix above. MultiplayerSettings (re_attempts 97401) passes the
evidence gate (??_G in slot 0 of 0x00C191B8, installed by its ctor; ??1 called by
it) but its files are held by a TU merge; its Dtor view keeps SubsystemInterface
as a +0 member, so a bare `virtual` would add a vptr and fail bytes.

**WallHub provider follow-up (2026-10-30):** the remaining constructor view now
uses a pure typed update interface and an ordinary inline sleep-forever override.
The complete emitted six-byte body equals native `004A6563`, and native table
`0084B1E0` slot zero independently binds it. The existing constant-getter row
stays unchanged; no pin, row, alias or hatch is added. The other three table
bindings are unchanged, all three constructor/cleanup rows and the parent EH
graph remain exact. Strict three-provider preparation passes 104/104 rows and
the preview retains 3/3 LINKS against `e1f7c1dd18`, clearing WallHub 0 -> 154
authored bytes while both providers are unchanged. Broader consumer selection
and census confirmation remain pending; the other listed units retain their
separate prerequisites. [Native and actual-object evidence](../../reverse/attempt_support/wallhub-update-provider-20261030/readme.md).

MultiplayerSettings's separate implicit-virtual lifetime repair is already
published at `acab09b4e1`: all six rows and 151 bytes are preserved in the
approved TU, the two obsolete lifetime views are removed, and their claims
are released. The earlier dry-run view above is retained as history; the
native constructor-table and complete EH evidence are in its existing handoff.

**Placeholder update rows re-rowed (2026-10-30, seat halilkkaya-lk9).**
Census diff 2c21184e84 -> e1f7c1dd18 (`reverse/link_status.csv` at
`028f4f9ea3` and `541ef26a32`): 282 units left the linked set. 245 are
deleted sources whose matched rows (54,296 B) all sit in census-linked units
at e1f7c1dd18, so they are TU merges, not losses. The other 37 (50,708 B by
row size) are real losses. Against current objects (index 2026-10-30 15:43
at `ccafe54d1d`), 33 of them link again: this entry's 17 units and FX thunks,
GiantBird, WallHub, LINK-161 (build queue), LINK-162/163 (Thai builder,
monetary strings), LINK-164 (downloader) and the wide-deallocator selection
in `dc24521e86` (PeerThread 18,622 B and the GameSpy/StlSweep units). Three
more link after the two commits below, and RebuildHoleBehaviorDtor.cpp stays
blocked. rn1's class-identity prerequisite is met by a hand re-row, the
`PoisonedBehavior::update` precedent (deleted_rows: `?rva00483133@Rva00482E96`).
A placeholder `?update@RvaX@@QAEHXZ` or receiver class at a class's +0x10
update-table slot is that class's override. MSVC compiles an override of a
function introduced in the +0x10 base with this at that subobject, so the
defining unit can declare the UpdateModule layout (vptrs +0/+0x0C/+0x10,
module data +4, object +8) and the member. The body keeps its bytes, with
member names instead of `this-0x10` arithmetic. Two codegen traps came up:
member access through an inline `getObject()` keeps retail's argument order,
and converting this to a secondary base adds a null test (keep an address
cast). Rename the row by hand with a tombstone, then make the two-line view
fix in the consumers.
- `?update@Rva004B327F@@QAEHXZ` -> `?update@AISpecialPowerUpdate@@UAE?AW4UpdateSleepTime@@XZ`
  (table 0x00C56D50 slot 0; WB callgraph lead agrees). `./build.sh` 10/10;
  scoped DIR32 OK; `link_check` 463 -> 586 B (AISpecialPowerUpdateDtor.cpp
  0 -> 123).
- `?update@GettingBuiltBehaviorUpdateReceiver@@QAE...` -> `?update@GettingBuiltBehavior@@UAE?AW4UpdateSleepTime@@XZ`
  (table 0x00C40434 slot 0, installed by ctor 0x004542FA and dtor 0x0045448F).
  `./build.sh` 7/7; scoped DIR32 OK; `link_check` 2,994 -> 3,324 B
  (GettingBuiltBehaviorCtor.cpp 0 -> 188, Dtor 0 -> 142). Check
  GettingBuiltBehavior.cpp together with Disp8LeaNegSbbGetters.cpp: the
  15:43 index predates `9db79eae97`'s split and reports a stale duplicate
  `?get@Rva004543A9LeaNegSbbField@@UBEHXZ`.
- Still blocked: RebuildHoleBehaviorDtor.cpp (227 B). Its slot 0 body
  `?update@Rva00483645@@QAEHXZ` (0x00483645, table 0x00C49A68) lives in
  RebuildHoleBehavior.cpp, whose RebuildHoleBehavior view has no vptr. Its
  ctor 0x00483271 stores the five tables as explicit members (TU-local
  dummies plus the folded data-ledger names
  `??_7SecondaryModuleBase@FXParticleSystem@@6B@` (0x00C1C780) and
  `??_7BfmeCtorVirtualBase001B3A20@@6B@`), so the class cannot declare a
  virtual override. 0x00483645 has no approved TU, so the body cannot move
  either. Prerequisite: give RebuildHoleBehavior.cpp the dtor unit's
  real-vptr class view and a real ctor. Its interface bases' own-table
  stores (retail +0x20/+0x24 before the member zeroing) must keep the folded
  data-ledger names, then the re-row above applies.
  2026-10-31 (Noro420): Resolved. Declaring `__declspec(novtable)` on the
  `RebuildHoleBehavior` prefix/interface view in `RebuildHoleBehavior.cpp`
  places `UpdateModuleInterface` at `+0x10` without disturbing `0x00483271`'s
  two-phase vptr store order or emitting duplicate COMDAT vftables, so
  `0x00483645` re-rows cleanly as
  `?update@RebuildHoleBehavior@@UAE?AW4UpdateSleepTime@@XZ` (tombstoned in
  `reverse/deleted_rows.csv`) and `RebuildHoleBehaviorDtor.cpp` binds it via
  `virtual UpdateSleepTime update() = 0` on `UpdateModuleInterface` with zero
  new hatches. Verified: `./build.sh` 12/12 rows across both files;
  `data_check --enforce` 0 findings; `link_check` 12/12 `RebuildHole*` units
  `LINKS`, `2,860 -> 3,087 B` (`RebuildHoleBehavior.cpp` `1,198 -> 1,198 B`,
  `RebuildHoleBehaviorDtor.cpp` `0 -> 227 B`; census confirmation pending).
