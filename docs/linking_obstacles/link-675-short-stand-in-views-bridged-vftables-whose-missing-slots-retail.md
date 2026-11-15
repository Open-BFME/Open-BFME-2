### LINK-675: short stand-in views: bridged vftables whose missing slots retail and the ledger already spell

Status: Open. Updated: 2026-11-14; inspected revision: 898aef3d714 (measure), repair on top of it.

Evidence / affected units: `tools/vtable_bridge.plan` at 898aef3d714 lists 3,275 bridged tables with
49,017 retail slots and 37,328 mismatching source slots. Classifying every mismatch by what the compiled
table holds there: **28,792 are slots the installing unit's private view never declares** (the compiled
table is shorter than retail's); the rest hold another symbol. Classifying every retail slot by the ledger
name at its target: 20,767 a virtual member, 9,663 an adjustor thunk, 2,196 `__purecall`, 948 a deleting
destructor (68% of the slots: the declaration is already spelled by a mangled name or needs none), 7,263
a member rowed non-virtual, 4,067 a plain `??1`, 3,078 under a placeholder name, 606 a free function.
By table: 420 have every slot rowed as a real virtual, thunk or pure; 298 more with placeholder names;
1,030 lack one or two slots; 1,527 lack three or more. Of the 718 fully rowed tables, 17 primary and 10
secondary tables hold only the table's own class, 29 are all pure, 245 hold exactly one other class
(a stand-in name for that class or for a class derived from it without overrides).

Completed: `BfmeBaseCC` (retail vftable VA 0x00BC64B0, ten slots: `__purecall`, the deleting destructor
at 0x000723C7, eight `__purecall`). Both private views (`BfmeOwnerCC.cpp`,
`InlineDtorDeletingDtorsC01.cpp`) declared the destructor only, so the compiled table was one slot long.
Both now declare the ten slots in retail order (`slot00`, the destructor, `slot08`..`slot24`, pure).
`./build.sh` on both units: 53/53 matched; `link_check.py` on the two units and the two units that store
the table by name (`Rva0081C2F0Set.cpp`, `Disp0DwordImmSettersAddr.cpp`): 4 of 4 link, LINKED 1,457 ->
1,457; bridge plan before/after: `??_7BfmeBaseCC@@6B@` leaves the bridge (3,275 -> 3,274 bridged, 2,271 ->
2,272 correct, mismatching slots 37,328 -> 37,317), refusals identical, no name newly undefined or
multiply defined.

Method (reusable): for a table whose retail slots are `__purecall` or rowed as virtuals of the table's
own class, the declaration list is a function of retail's slot order: pure slots become
`virtual void slotNN() = 0` (NN the hex slot offset, the spelling the canonical headers use), a rowed
slot the declaration its mangled name spells. **Every unit that declares the class must take the same
list**: changing one copy alone makes `link_check.py` report `comdat ??_7Class@@6B@ differs from the
first copy` and the unit's census bytes drop to 0 (measured here: 120 -> 0 with one copy changed, 120 ->
120 with both).

Remaining / next check: the 245 one-other-class tables need the stand-in to derive from (or fold into)
the class that owns the slots; a derived class of an abstract view stays bridged until its own overrides
are declared (`??_7BfmeOwnerCC@@6B@`, 13 slots, shares VA 0x00BC64D8 with `??_7W3DVideoBuffer@@6B@`, went
13 -> 12 mismatching). Only 36 slots in 27 tables are the misnamed-override shape (a body rowed as
`Watchdog::start` in the slot of `ThreadClass::Execute`).

Clearance: `??_7BfmeBaseCC@@6B@` only, by the bridge plan and `link_check.py` at the commit that adds this
entry.

Census confirmation: awaiting; the census does not count bridged tables.

Applied by the same rule (unattended worker; each commit carries its measurement):
- 2026-11-14 `PropagandaTowerBehaviorIface` (VA 0x00C1C780): 1 slots (1 pure, 0 rowed virtual, 0 destructor), 2 view(s): `PropagandaTowerBehavior.cpp`, `PropagandaTowerBehaviorConstructor.cpp`.
- 2026-11-14 `Rva00577936` (VA 0x00C6E9E8): 5 slots (3 pure, 1 rowed virtual, 1 destructor), 5 view(s): `MemberBaseDtorsB01.cpp`, `Rva000AD6F4Members.cpp`, `Rva00577936Ctor.cpp`, `Rva005F8388.cpp`, `Rva005F86C3Constructor.cpp`.
- 2026-11-14 `DelayedUpgradeUpdateInterface` (VA 0x00C6FFFC): 2 slots (2 pure, 0 rowed virtual, 0 destructor), 1 view(s): `DelayedWeaponSetUpgradeUpdate.cpp`.
- 2026-11-14 `Rva004C9994` (VA 0x00C5EBEC): 2 slots (0 pure, 0 rowed virtual, 0 destructor, 2 folded trivial body), 1 view(s): `RvaSmallVtableCtors.cpp`.
- 2026-11-14 `Rva0056775B` (VA 0x00C6CE84): 2 slots (0 pure, 0 rowed virtual, 0 destructor, 2 folded trivial body), 1 view(s): `RvaSmallVtableCtors.cpp`.
- 2026-11-14 `Rva0057A3A9` (VA 0x00C6EE20): 2 slots (0 pure, 0 rowed virtual, 0 destructor, 2 folded trivial body), 1 view(s): `RvaSmallVtableCtors.cpp`.
- 2026-11-14 `Rva00468A46` (VA 0x00C44890): 3 slots (1 pure, 0 rowed virtual, 1 destructor, 1 folded trivial body), 1 view(s): `InlineDtorDeletingDtors1.cpp`.
- 2026-11-14 `Rva005CB243` (VA 0x00C74CA4): 3 slots (1 pure, 0 rowed virtual, 1 destructor, 1 folded trivial body), 1 view(s): `InlineDtorDeletingDtors1.cpp`.
- 2026-11-14 `Rva005743AE` (VA 0x00C6E350): 4 slots (0 pure, 0 rowed virtual, 0 destructor, 4 folded trivial body), 1 view(s): `RvaSmallVtableCtors.cpp`.
- 2026-11-14 `Rva00782CB0` (VA 0x00BC93C8): 5 slots (1 pure, 0 rowed virtual, 1 destructor, 3 folded trivial body), 1 view(s): `Rva00785140HandleDestructor.cpp`.
- 2026-11-14 `Rva000A8EF6` (VA 0x00BC93DC): 5 slots (1 pure, 0 rowed virtual, 1 destructor, 3 folded trivial body), 1 view(s): `InlineDtorDeletingDtorsC01.cpp`.
- 2026-11-14 `Rva005E3994` (VA 0x00C77BE8): 5 slots (0 pure, 0 rowed virtual, 0 destructor, 5 folded trivial body), 1 view(s): `RvaSmallVtableCtors.cpp`.
- 2026-11-14 `Rva005CC93A` (VA 0x00C77E7C): 7 slots (0 pure, 0 rowed virtual, 0 destructor, 7 folded trivial body), 1 view(s): `RvaSmallVtableCtors.cpp`.
- 2026-11-14 `Rva005E9FA4` (VA 0x00C780F4): 8 slots (0 pure, 0 rowed virtual, 1 destructor, 7 folded trivial body), 1 view(s): `InlineDtorDeletingDtors1.cpp`.
- 2026-11-14 `Rva004CE267` (VA 0x00C5FE1C): 10 slots (9 pure, 0 rowed virtual, 0 destructor, 1 folded trivial body), 1 view(s): `RvaSmallVtableCtors.cpp`.
- 2026-11-14 `Rva00488AC0` (VA 0x00C4B788): 32 slots (31 pure, 0 rowed virtual, 0 destructor, 1 folded trivial body), 1 view(s): `RvaSmallVtableCtors.cpp`.
- 2026-11-14 `Rva00381D78` (VA 0x00C19230): 99 slots (97 pure, 0 rowed virtual, 1 destructor, 1 folded trivial body), 1 view(s): `InlineDtorDeletingDtorsC01.cpp`.
- 2026-11-14 `Rva00468AE3` (VA 0x00C448B8): 155 slots (152 pure, 0 rowed virtual, 0 destructor, 3 folded trivial body), 1 view(s): `RvaSmallVtableCtors.cpp`.
- 2026-11-14 `Rva004318C6` (VA 0x00C3C970): 3 slots (0 pure, 0 rowed virtual, 1 destructor, 2 folded trivial body), 2 view(s): `RvaSmallVtableCtors.cpp`, `VslotSmallBodiesAR.cpp`.
- 2026-11-14 `Rva005E567D` (VA 0x00C77D30): 5 slots (2 pure, 0 rowed virtual, 1 destructor, 2 folded trivial body), 2 view(s): `GapBodiesGE05.cpp`, `InlineDtorDeletingDtors1.cpp`.
- 2026-11-14 `Rva005753E9` (VA 0x00C6E5C4): 11 slots (0 pure, 0 rowed virtual, 1 destructor, 10 folded trivial body), 2 view(s): `InlineDtorDeletingDtors1.cpp`, `Rva00575F38Dtor.cpp`.
- 2026-11-14 `ClickReactionBehaviorIface` (VA 0x00BE2B78): 3 slots (3 pure, 0 rowed virtual, 0 destructor, 0 folded trivial body), 1 view(s): `ClickReactionBehaviorView.h`.
- 2026-11-14 `SiegeDockingBehaviorSecondaryBase` (VA 0x00C4EF80): 4 slots (4 pure, 0 rowed virtual, 0 destructor, 0 folded trivial body), 3 view(s): `SiegeDockingBehaviorDtor.cpp`, `SiegeDockingBehaviorView.h`, `SiegeDockingBehaviorXfer.cpp`.
- 2026-11-14 `Rva005FF912` (VA 0x00C7A530): 6 slots (0 pure, 0 rowed virtual, 1 destructor, 5 folded trivial body), 1 view(s): `BattlePromptMovieClipView.h`.
- 2026-11-14 `Rva002AAD77` (VA 0x00BFDC60): 3 slots (0 pure, 0 rowed virtual, 0 destructor, 0 folded trivial body), 1 view(s): `RvaSmallVtableCtors.cpp`.
- 2026-11-14 `Rva0059B060` (VA 0x00C70E60): 3 slots (0 pure, 0 rowed virtual, 0 destructor, 0 folded trivial body), 1 view(s): `RvaSmallVtableCtors.cpp`.
- 2026-11-14 `Base003F8ED6` (VA 0x00C37298): 15 slots (0 pure, 0 rowed virtual, 1 destructor, 14 folded trivial body), 2 view(s): `Rva003F8ED6.cpp`, `Rva003F8ED6Ctor.cpp`.
- 2026-11-15 `Rva005CBA04` (VA 0x00C74DB8): 17 slots (0 pure, 0 rowed virtual, 1 destructor, 15 folded trivial body), 2 view(s): `Rva005CBA04.h`, `Rva005E5A38Ctor.cpp`.
- 2026-11-15 `Rva0065E8D0` (VA 0x00CE2368): 5 slots (4 pure, 0 rowed virtual, 0 destructor, 0 folded trivial body), 1 view(s): `RvaSmallVtableCtors.cpp`.
- 2026-11-15 `Rva000F5ACB` (VA 0x00BCF1C8): 4 slots (1 pure, 0 rowed virtual, 0 destructor, 2 folded trivial body), 1 view(s): `RvaSmallVtableCtors.cpp`.
- 2026-11-15 `Rva0059EB66` (VA 0x00C711BC): 3 slots (0 pure, 0 rowed virtual, 0 destructor, 2 folded trivial body), 1 view(s): `RvaSmallVtableCtors.cpp`.
- 2026-11-15 `Rva006560B0` (VA 0x00CE0FB8): 3 slots (2 pure, 0 rowed virtual, 0 destructor, 0 folded trivial body), 1 view(s): `RvaSmallVtableCtors.cpp`.
- 2026-11-15 `Rva006ED020` (VA 0x00CEC9CC): 3 slots (0 pure, 0 rowed virtual, 1 destructor, 1 folded trivial body), 1 view(s): `AptCharacter.cpp`.
- 2026-11-15 `Rva0020E38B` (VA 0x00BE4318): 2 slots (1 pure, 0 rowed virtual, 0 destructor, 0 folded trivial body), 1 view(s): `RvaSmallVtableCtors.cpp`.
- 2026-11-15 `Rva005CFB8A` (VA 0x00C75284): 2 slots (0 pure, 0 rowed virtual, 0 destructor, 1 folded trivial body), 1 view(s): `RvaSmallVtableCtors.cpp`.
- 2026-11-15 `Gen008030A0` (VA 0x00CE3ED4): 2 slots (0 pure, 0 rowed virtual, 1 destructor, 0 folded trivial body), 1 view(s): `Y2ScalarDeleters.cpp`.
- 2026-11-15 `Rva000B2E0B` (VA 0x00BC9B78): 49 slots (32 pure, 0 rowed virtual, 0 destructor, 15 folded trivial body), 1 view(s): `RvaSmallVtableCtors.cpp`.
- 2026-11-15 `Rva005748A4` (VA 0x00C6E430): 26 slots (0 pure, 0 rowed virtual, 0 destructor, 24 folded trivial body), 1 view(s): `RvaSmallVtableCtors.cpp`.
- 2026-11-15 `Rva004444D2` (VA 0x00C3E020): 23 slots (19 pure, 0 rowed virtual, 1 destructor, 1 folded trivial body), 2 view(s): `Rva004444D2.h`, `AptLanLobby.cpp`.
- 2026-11-15 `Rva0046249E` (VA 0x00C430B4): 12 slots (7 pure, 0 rowed virtual, 0 destructor, 3 folded trivial body), 1 view(s): `RvaSmallVtableCtors.cpp`.
- 2026-11-15 `ContainIface30` (VA 0x00C430B4): 12 slots (7 pure, 0 rowed virtual, 0 destructor, 3 folded trivial body), 2 view(s): `OpenContainCtor.cpp`, `OpenContainDtorRva00464692.cpp`.
- 2026-11-15 `SpawnB4` (VA 0x00C430B4): 12 slots (7 pure, 0 rowed virtual, 0 destructor, 3 folded trivial body), 1 view(s): `SpawnPointProductionExitUpdate.cpp`.
- 2026-11-15 `Rva005EA00D` (VA 0x00C78154): 8 slots (0 pure, 0 rowed virtual, 0 destructor, 6 folded trivial body), 1 view(s): `GapBodiesGE09.cpp`.
- 2026-11-15 `Rva000F6320` (VA 0x00BCF1E8): 7 slots (3 pure, 0 rowed virtual, 0 destructor, 2 folded trivial body), 1 view(s): `RvaSmallVtableCtors.cpp`.
- 2026-11-15 `Rva0056778A` (VA 0x00C6CEB4): 6 slots (4 pure, 0 rowed virtual, 0 destructor, 0 folded trivial body), 1 view(s): `RvaSmallVtableCtors.cpp`.
- 2026-11-15 `Rva003674CA` (VA 0x00BF8FE4): 3 slots (0 pure, 0 rowed virtual, 0 destructor, 1 folded trivial body), 1 view(s): `GapBodiesGE08.cpp`.
- 2026-11-15 `Rva0033F9DC` (VA 0x00C11A5C): 3 slots (0 pure, 0 rowed virtual, 0 destructor, 1 folded trivial body), 1 view(s): `GapBodiesGE04.cpp`.
- 2026-11-15 `Rva00468A63` (VA 0x00C4489C): 3 slots (0 pure, 0 rowed virtual, 0 destructor, 1 folded trivial body), 1 view(s): `RvaSmallVtableCtors.cpp`.
- 2026-11-15 `Rva00468AA3` (VA 0x00C448A8): 3 slots (0 pure, 0 rowed virtual, 0 destructor, 1 folded trivial body), 1 view(s): `RvaSmallVtableCtors.cpp`.
- 2026-11-15 `Rva0048FF77` (VA 0x00C4D040): 3 slots (0 pure, 0 rowed virtual, 0 destructor, 1 folded trivial body), 1 view(s): `GapBodiesGE09.cpp`.
- 2026-11-15 `Rva004BB391` (VA 0x00C59EA8): 3 slots (0 pure, 0 rowed virtual, 0 destructor, 1 folded trivial body), 1 view(s): `Rva0040C92DVtableCtors.cpp`.
- 2026-11-15 `Rva0025559B` (VA 0x00BF36C0): 31 slots (0 pure, 0 rowed virtual, 0 destructor, 28 folded trivial body), 1 view(s): `AsciiStringFoldDeleters.cpp`.
- 2026-11-15 `Rva0025558E` (VA 0x00BF3740): 31 slots (0 pure, 0 rowed virtual, 0 destructor, 28 folded trivial body), 1 view(s): `AsciiStringFoldDeleters.cpp`.
- 2026-11-15 `Rva004BDCA3` (VA 0x00C5AEB8): 31 slots (0 pure, 0 rowed virtual, 0 destructor, 28 folded trivial body), 1 view(s): `RvaSmallVtableCtors.cpp`.
- 2026-11-15 `Rva006655D0` (VA 0x00CE3194): 10 slots (6 pure, 0 rowed virtual, 0 destructor, 1 folded trivial body), 1 view(s): `RvaSmallVtableCtors.cpp`.
- 2026-11-15 `Rva00306A36` (VA 0x00C07DD8): 9 slots (1 pure, 0 rowed virtual, 0 destructor, 5 folded trivial body), 1 view(s): `RvaSmallVtableCtors.cpp`.
- 2026-11-15 `Rva003FDD38` (VA 0x00C37E18): 6 slots (0 pure, 0 rowed virtual, 0 destructor, 3 folded trivial body), 1 view(s): `RvaSmallVtableCtors.cpp`.
- 2026-11-15 `Rva000F5B56` (VA 0x00BCF1D8): 4 slots (0 pure, 0 rowed virtual, 0 destructor, 1 folded trivial body), 1 view(s): `RvaSmallVtableCtors.cpp`.
- 2026-11-15 `Rva0020E86A` (VA 0x00BE4340): 4 slots (0 pure, 0 rowed virtual, 0 destructor, 1 folded trivial body), 1 view(s): `RvaSmallVtableCtors.cpp`.
- 2026-11-15 `Rva002AA39B` (VA 0x00BFDC48): 4 slots (0 pure, 0 rowed virtual, 0 destructor, 1 folded trivial body), 1 view(s): `RvaSmallVtableCtors.cpp`.
- 2026-11-15 `Rva005E9390` (VA 0x00C1D134): 4 slots (0 pure, 0 rowed virtual, 0 destructor, 1 folded trivial body), 1 view(s): `V3PolyCopyCtorsO1.cpp`.
- 2026-11-15 `Rva005E95C0` (VA 0x00C1D1A4): 4 slots (0 pure, 0 rowed virtual, 0 destructor, 1 folded trivial body), 2 view(s): `Rva005EA590CopyCtor.cpp`, `V3PolyCopyCtorsO1.cpp`.
- 2026-11-15 `Rva003ADE98` (VA 0x00C1D1F4): 4 slots (0 pure, 0 rowed virtual, 0 destructor, 1 folded trivial body), 2 view(s): `Rva003ADE98.h`, `V3PolyCopyCtors.cpp`.
- 2026-11-15 `Rva004E1780` (VA 0x00C61B78): 4 slots (0 pure, 0 rowed virtual, 0 destructor, 1 folded trivial body), 1 view(s): `RvaSmallVtableCtors.cpp`.
- 2026-11-15 `Rva004FF334` (VA 0x00C63B40): 4 slots (0 pure, 0 rowed virtual, 0 destructor, 1 folded trivial body), 1 view(s): `RvaSmallVtableCtors.cpp`.
- 2026-11-15 `ShdDefFactoryClass` (VA 0x00C7C584): 15 slots (9 pure, 0 rowed virtual, 1 destructor, 1 folded trivial body), 1 view(s): `ShdDefFactoryClassDelete.cpp`.
- 2026-11-15 `Rva003FE1BF` (VA 0x00C37E30): 6 slots (0 pure, 0 rowed virtual, 0 destructor, 2 folded trivial body), 1 view(s): `RvaSmallVtableCtors.cpp`.
- 2026-11-15 `Rva0052B106` (VA 0x00C685C8): 6 slots (0 pure, 0 rowed virtual, 0 destructor, 2 folded trivial body), 1 view(s): `RvaSmallVtableCtors.cpp`.
- 2026-11-15 `Rva0059E08F` (VA 0x00C70F6C): 6 slots (0 pure, 0 rowed virtual, 0 destructor, 2 folded trivial body), 1 view(s): `GapBodiesSeat5A.cpp`.
- 2026-11-15 `Rva007F0080Owner` (VA 0x00CE1DFC): 6 slots (0 pure, 0 rowed virtual, 0 destructor, 2 folded trivial body), 1 view(s): `Rva007F0080DefaultPointers.cpp`.
- 2026-11-15 `Rva000FDDAF` (VA 0x00BCF440): 7 slots (0 pure, 0 rowed virtual, 0 destructor, 2 folded trivial body), 1 view(s): `RvaSmallVtableCtors.cpp`.
- 2026-11-15 `Rva000F6490` (VA 0x00BCF204): 7 slots (0 pure, 0 rowed virtual, 0 destructor, 1 folded trivial body), 1 view(s): `RvaSmallVtableCtors.cpp`.
- 2026-11-15 `Rva00538C5F` (VA 0x00C39608): 9 slots (0 pure, 0 rowed virtual, 1 destructor, 0 folded trivial body), 2 view(s): `AsciiStringFoldDeleters.cpp`, `AptWindowLayout.cpp`.
- 2026-11-15 `Rva005E9F92` (VA 0x00C780F4): 8 slots (0 pure, 0 rowed virtual, 1 destructor, 7 folded trivial body), 1 view(s): `RvaSmallVtableCtors.cpp`.
- 2026-11-15 `Rva006672F0` (VA 0x00CE34D0): 26 slots (25 pure, 0 rowed virtual, 0 destructor, 0 folded trivial body), 1 view(s): `RvaSmallVtableCtors.cpp`.
- 2026-11-15 `Rva00668610` (VA 0x00CE36D8): 25 slots (24 pure, 0 rowed virtual, 0 destructor, 0 folded trivial body), 1 view(s): `RvaSmallVtableCtors.cpp`.
- 2026-11-15 `Rva006562A0` (VA 0x00CE0FC8): 22 slots (21 pure, 0 rowed virtual, 0 destructor, 0 folded trivial body), 1 view(s): `RvaSmallVtableCtors.cpp`.












































































Correction (2026-11-14, inspected 90f2c095cd): the "9,663 an adjustor thunk" and "68% of the slots" figures above
are wrong. The classifier read free functions at shared bodies (for example `?ControlBarInput@@YA...` at
0x000D43D0, the folded `xor eax,eax; ret`) as members with a thunk access letter. By bytes (`sub ecx,N; jmp`) 574
slots are adjustor thunks; the share of slots whose declaration is already spelled is well below 68%. The 28,792
missing-slot count and the per-table method are unaffected.

Shared trivial bodies (2026-11-14): 4,467 own slots of the measured primary tables point at ICF-folded bodies (385
addresses; `33 C0 C3`, `32 C0 C3`, `C3`, `C2 04 00`, `B0 01 C3` cover most). Method: the view declares the slot
inline with the body those bytes compile from (`C2 04 00` -> `virtual void slotNN(int) {}`) and the class's name
for it is rowed at the folded address with `tools/add_match.py NAME RVA SIZE UNIT --icf-owner <an existing row
there>`. First case: `Rva0057434D` (VA 0x00C6E360, one slot at 0x0047A69C): `./build.sh` 201/201, `link_check.py`
LINKS 3,046 -> 3,049, bridge plan 3,265 -> 3,264 bridged with refusals identical and nothing newly undefined.
A body rowed as a member of a placeholder class cannot be moved the same way: `rename.py function --to-class`
refuses a class without a registered header and a `name_lane.py` slot approval.


Stand-ins for a class that is already right (2026-11-14): 239 bridged primary tables share their retail address with
a table that is correct under another class name P. Reading each stand-in X's layout from the compiler
(`tools/class_layouts.compile_layouts`, sizeof P from its contract or from a unit that holds P): 127 are root views
whose bytes below sizeof P hold only fillers or nothing, 72 derive from another class, 15 have named fields there,
9 are smaller than P. Method for the 127: X derives from P's real definition (its registered header) and declares no
virtual of its own; the compiler's layout before and after must agree (size, base offsets, every kept field).
First case: `Rva0056B218B2` (VA 0x00C3702C, five slots, the table of `LivingWorldBattleListener`): both views
(`Rva0056B218Constructor.cpp`, `Rva0056B218Dtor.cpp`) declared an empty virtual destructor; they now derive from
`LivingWorldBattleListener`. Layout: 4 bytes, base at +0, no slot of its own; the derived `Rva0056B218` keeps its
bases at +0 and +20. `./build.sh` 5/5; `link_check.py` 2 of 2, LINKED 270 -> 274; bridge plan 3,271 -> 3,270 bridged,
mismatching slots 37,308 -> 37,300, refusals identical.

Derived from the class whose table they share (unattended worker; layout read from the compiler before and after):
- 2026-11-14 `Rva0056B2DDB2` (VA 0x00C3702C, 5 slots) from `LivingWorldBattleListener`: `Rva0056B2DDConstructor.cpp`, `Rva0056B2DDDtor.cpp`.
- 2026-11-14 `Rva000E59D3Base` (VA 0x00BBB554, 4 slots) from `Snapshot`: `Rva000E59D3Dtor.cpp`, `W3DFloorBuffer.cpp`.
- 2026-11-14 `W3DTreeDrawModuleDataBase` (VA 0x00BBB554, 4 slots) from `Snapshot`: `W3DTreeDraw.cpp`.
- 2026-11-14 `Rva001E7087Base` (VA 0x00BBB554, 4 slots) from `Snapshot`: `Locomotor.cpp`.
- 2026-11-14 `SecondBase005D2111` (VA 0x00C3702C, 5 slots) from `LivingWorldBattleListener`: `Rva00576FD3Permuted.cpp`, `StrategicInGameUIPlanRetreatChecklistItem.cpp`.
- 2026-11-14 `Rva005D06CBB2` (VA 0x00C62A14, 3 slots) from `LivingWorldAutoResolveEventObserver`: `Rva005D0C87Ctor.cpp`, `Rva005D06CBDtor.cpp`, `Rva005D0B5ECtor.cpp`, `StrategicInGameUIBattleResolver.cpp`.
- 2026-11-15 `Base0_005770F7` (VA 0x00BDBA74, 2 slots) from `Base0_00576C4B`: `Rva005770F7Dtor.cpp`.
- 2026-11-15 `Rva005EDFF8` (VA 0x00C62A14, 3 slots) from `LivingWorldAutoResolveEventObserver`: `Rva005EB2E7Dtor.cpp`.
- 2026-11-15 `BfmeCacheBZAMiddleBase` (VA 0x00CE0FB4, 1 slots) from `Q3MakeBaseB`: `BfmeMakeBZA.cpp`.
- 2026-11-15 `Rva005D073ASecondBase` (VA 0x00C62A14, 3 slots) from `LivingWorldAutoResolveEventObserver`: `Rva005D073ADtor.cpp`, `Rva005D0BDDCtor.cpp`.
- 2026-11-15 `Rva0044BE39Base` (VA 0x00BC6F20, 1 slots) from `ImplBase`: `Rva0044BE39Dtor.cpp`.
- 2026-11-15 `Rva005E8AAFBase` (VA 0x00BC6F20, 1 slots) from `ImplBase`: `Rva005E8AAFDtor.cpp`.







Real classes completed across their units (unattended worker; layout read from the compiler before and after):
- 2026-11-15 `Rva004444EBObject` (VA 0x00C3D490, 2 slots, 1 under it, base `Rva0007DF07`): `VslotSmallBodiesR.cpp`.

Derived from the class whose table they share (unattended worker; layout read from the compiler before and after):
- 2026-11-15 `Rva005CF07EListener` (VA 0x00C77F44, 4 slots) from `LivingWorldBuildingObserver`: `ThrowingNewHelpers.cpp`.
Derived from the class whose table they share (unattended worker; layout read from the compiler before and after):
- 2026-11-15 `Base005CEFD3` (VA 0x00BFDF68, 4 slots) from `LivingWorldRegionObserver`: `Rva005CEFD3Dtor.cpp`.
**2026-11-15, ancalgonn-swarm-waste: W3DTreeDrawModuleDataBase's table after `9761e893cde` holds the data ledger
refresh.** The 2026-11-15 refresh (attempt 1, report `report-20261115T000812Z.json`) was held on one loss: the
regenerated `reverse/data_ledger.csv` drops `??_7W3DTreeDrawModuleDataBase@@6B@` from the folded names of row
0x007BB554, leaving it neither bridged nor correct (`names_bridged_or_correct` 5518 -> 5517). The row's main name
stays `??_7Snapshot@@6B@`. Retail's 4-slot table there is Snapshot's own: slot 0 is `??_ESnapshot@@UAEPAXI@Z`
(0x00001750, 74 bytes), and slots 1-3 are `__purecall`. Master's ledger lists W3DTreeDrawModuleDataBase among the
row's folded names, and `~W3DTreeDrawModuleDataBase` is rowed at Snapshot's destructor 0x0049B47C with a fold proof.
Since this unit's change, W3DTreeDraw.obj's `??_7W3DTreeDrawModuleDataBase@@6B@` matches Snapshot's table except
for slot 0, which references `??_EW3DTreeDrawModuleDataBase@@UAEPAXI@Z`. The object only weakly defines that name
(`nm`: `w`), falling back to the scalar `??_GW3DTreeDrawModuleDataBase@@UAEPAXI@Z` it does define, as cl 7.1 does
when nothing array-deletes the class. A fold pin of `??_EW3DTreeDrawModuleDataBase@@UAEPAXI@Z` onto 0x00001750 was
refused by `tools/pin_admission.py --add` (pin_consistency clean before; nothing written):
"0x00001750 already carries the real name ??_ESnapshot@@UAEPAXI@Z ... no ICF fold proof: W3DTreeDraw.cpp: symbol
not found in object". That refusal is correct: the object has no vector-deleting body to prove against retail's.
Retail does use this table for the class. `??1W3DTreeDrawModuleData@@UAE@XZ` (rowed, W3DTreeDraw.cpp) restores the
base vptr with VA 0x00BBB554, which is RVA 0x007BB554, at 0x000CECF5. So in retail, W3DTreeDrawModuleDataBase's
table is Snapshot's, including slot 0 at the vector deleting body 0x00001750. Master's ledger name is the right
one, and the regeneration's loss is real.
The inspected W3DTreeDraw.obj has only a weak vector-deleting destructor symbol, falling back to its defined scalar
deleting destructor. It provides no vector-deleting body for pin admission to compare with retail RVA 0x00001750, so
this fold-pin attempt was correctly refused. This establishes the current object's limitation; it does not
establish that a source change cannot reproduce retail's fold.
Disposition (swarm coordinator, 2026-11-15): one line in the ledger job's `loss_exceptions.tsv` accepts this loss.
It covers row 0x007BB554 and the lost name, lists the row's 11 other names, and is bound to master's ledger blob
`b1800c77ea9b`. The line records the evidence above, so the 36 stale-name gains can publish. Like every exception
line, it lapses on any change to master's ledger. A future regeneration can record the name again if current
matched-object relocation evidence binds it to RVA 0x007BB554; restoring bridge coverage also requires the
regenerated bridge plan to accept it.
Flattened stand-ins respelled over their real base (unattended worker; classes with several vftables whose stand-in used fake side bases to place the vptrs):
- 2026-11-15 `Rva00589079Derived.cpp` over `UpdateModule`: 3 classes in 5 unit(s); 4 took another view's virtual declarations.
- 2026-11-15 `CostModifierUpgrade.cpp` over `UpgradeModule`: 1 classes in 1 unit(s); 0 took another view's virtual declarations.
Measured structure of the bridge and what each evidence proves (2026-11-15, master 565145b59d4: 3,231 bridged
tables, 36,708 mismatching slots):
- Kinds of mismatching slot over every bridged table: the compiled table is shorter than retail's 28,057 (76%);
  compiled pure where retail has a body 3,496; a compiled name the ledger does not row while retail's target is
  rowed under another name 2,938; a compiled name rowed at another address 1,286; an unrowed deleting-destructor
  name 1,057. 388 tables had only unrowed compiled names: those need no declaration change, only a row
  (`tools/add_match.py --icf-owner`, or `--replace-rva` where a `gen-*` placeholder owns the address), and the
  tool accepts the row only when the compiled body is retail's body at that address.
- 1,465 of the bridged tables are named `??_7C@@6B<Base>@@` (classes with several vftables). Their missing slots
  come from stand-in bases: 650 classes in 434 units are "flattened" (`class X : public <one-vptr stand-in of the
  base>, public <fake side bases that only place the other vptrs>`, written to reproduce destructor bytes). Such a
  view cannot emit retail's tables. Where the real base has a registered header with the same subobjects at the
  same offsets, the class can be respelled over it alone (side bases inside sizeof(real base) are placers; those
  past it are real further bases) and every row still byte-matches; all based views of the class must then
  declare the same virtual list (and each virtual its retail access, which is part of the mangled name) or the
  link sees differing COMDAT copies of one table.
- Destructor evidence, and its limit. A deleting destructor ends by leaving the table of the class whose
  destructor runs last (`call D` with D = `mov [ecx], T; ret`, or the store inlined). When T is not the table the
  slot sits in, the slot's class DERIVES from the class of T. It does not show whether the class has a destructor
  of its own: an empty destructor with the base's inlined compiles to the same `store T; ret`, and retail folds
  those of sibling classes to one address (`??1RefCountClass` is at 0x00072892 while 23 derived destructors sit
  folded at 0x00724510 with the same bytes). A `??1X` row at an address that stores the base's table is therefore
  a legitimate reconstruction, not a mis-rowed destructor. The commit that declared Rva004444EBObject's slots over
  Rva0007DF07 says the class "has no destructor body of its own": read that as the reconstruction's choice
  (retail's bytes are the same either way), not as a retail fact.
- A bridged name whose retail table is also compiled correctly under another name (541 names) is a second, stale
  spelling of that class. Where the stale class has no row under its name it can become another name of the
  correct class; `rename.py class --fold` refuses most of the rest for reasons that are not defects.
- Real vector deleting destructors. In 99 bridged tables retail's destructor slot holds a real `??_E` (flag bit
  2 selects the `eh vector destructor iterator` path), directly or behind an adjustor thunk, while the unit that
  emits the table compiles `??_E` only as a weak alias of the scalar `??_G`; in 33 of them that slot was the
  table's only mismatch. The remedy is the anchor XferVectorDeletingDtor.cpp and VectorDeletingDtorsV07.cpp
  already use, placed in the table's own unit: an `absent-from-retail` function that names the destructor
  directly (`p->C::__vecDelDtor(3)`), with `<new>` included where retail's array path frees through operator
  delete[]. The emitted body is then rowed at retail's address by `tools/add_match.py --icf-owner` (derived
  classes with a trivial destructor fold with their base's, e.g. onto `??_ESnapshot` at 0x00001750). A second
  spelling of the class in a VectorDeletingDtors batch unit does not help the table: its slot names the
  class's own `??_E`.
- Rows a slot name waits for. A compiled body equal to retail's outside relocations is still refused when a
  function it references has no row: the verifier resolves a call (REL32) or a pushed function address (DIR32,
  the destructor handed to the vector iterator) only to a bound name. Rowing those first, each at the address
  retail's body references at the same offset, unblocks the slot name; the same holds for an adjustor thunk,
  whose jump target must be rowed before the thunk. Of 77 failed alias candidates, 30 names were of this kind;
  52 names had a body of another size than retail's (not aliases at all).
- Stripping a unit's private stand-in of a real base changes the tables of every class of that unit deriving
  from it, so every unit holding a view of such a class has to take the real header in the same change (49
  distinct closures over the 150 convertible units: 35 of at most 5 units, 7 of 6 to 11, 7 of 16 to 40). Views
  of one class may each declare overrides the others lack; an override's slot is its base's, so the views can
  take the union of their overrides in any order, while a virtual new to the class fixes the order and cannot
  be merged that way.
Parked (coordinator, 2026-11-15): the unused table name
`??_7Rva000E59D3Base@@6B@` at RVA 0x007BB554 remains in the ledger. The intermediate
Snapshot-derived view survives in Rva000E59D3Dtor.cpp and W3DFloorBuffer.cpp; its
destructor is fold-proven at 0x0049B47C. The supported class-fold dry run refuses
the ten third class names sharing this table. No fold bypass or ledger erasure
is approved. The ops refresh's reviewed master-covered exception rule makes
this pre-existing uncovered name harmless to that refresh; it retires no identity
debt. Revisit only with a supported reconciliation route.
Second day of the unattended table work (2026-11-15, master 85e8ba2544: 3,160 bridged names over about 2,400
retail tables, 35,063 mismatching slots), what was measured and what is exhausted:
- Unrowed compiled slot names are drained. A read-only prefilter compares the compiled body of every such name
  with retail's bytes at the slot target (same size, equal outside relocations) and a second pass drops a name
  whose callee cannot itself be rowed. About 230 commits rowed the survivors; 61 names still pass and are held
  by claims or the judge (a row that makes another table newly bridged is refused).
- 3,160 bridged names cover far fewer classes than it looks: 923 names share their retail table with another
  bridged name and 529 with a name that is already compiled correctly. Most of those pairs are NOT one class
  under two names: the linker folded the identical tables of different classes, and `rename.py class --fold`
  rightly refuses them (each name's destructor installs its own table, both have constructor rows, a third name
  exists). Only a stand-in that has no ledger row at all can become `typedef Real StandIn;` (done where the
  layouts of the unit's other classes do not move).
- A class view that changes must change in every unit that emits the class's table, or of a table derived from
  it. f5d27a753c (2026-11-14) changed one view and cost AptShapeContainer.cpp its link until 2c5fc2bb9e6. The
  worker and the landing script now link-check, before and after, every unit whose object defines a `??_7`
  symbol that an edited unit defines.
- Root classes, partial rule: every retail slot the ledger can name is written into the views (a rowed virtual
  of the class, the destructor, a pure slot, a folded trivial body inline with an alias row); a slot whose body
  is rowed under a name that is not the class's to take is held as the view has it, or as the pure placeholder
  `slotNN`. Of 1,640 primary tables only 108 can be planned (833 views have bases, 269 declare no virtual, 232
  have no nameable slot), and most attempts on those fail honestly: a held slot made pure turns a derived class
  the unit instantiates abstract, or a twin spelling of the base in another unit makes a derived table differ.
- Derived classes: a slot compiled `__purecall` whose retail body is a rowed virtual of the same class only
  lacks the override's declaration in the unit that emits the table; it is added from the mangled name where a
  visible base declares a virtual of that name, and refused when a table of the class grows (the declaration
  was a new virtual, not an override).
- What is left needs one of two things no script here supplies. (1) Slot names: an override must carry its base
  slot's identifier, but each body was rowed under its own address-named identifier; of 3,364 compiled-pure
  slots 2,033 hold a body rowed under another name. (2) The real base in the unit: 902 compiled-pure slots hold
  a trivial retail body that the real interface (BehaviorModuleInterface and its like) defines inline, while
  the unit's private stand-in declares it pure; rowing 47 per-class overrides would make the bytes right and
  the source wrong, so that was not done. Both are the canonical-header lane's work (reverse/header_queue.tsv:
  1,111 of its 8,921 queued units fail on a private field with no canonical field at its offset and size).
