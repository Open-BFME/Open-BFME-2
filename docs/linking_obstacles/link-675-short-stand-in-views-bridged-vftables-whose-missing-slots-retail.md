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
