### LINK-068: removing DieModule's unrowed field parser removes a live provider

Status: Blocked on field-parser consumer/provider reconciliation. Updated: 2026-10-26; inspected revision: `896af216804e`.
Evidence / affected units: `DieModule.cpp` retains undefined `BitFlags<45>::s_bitNameList` and `INI::scanIndexList` through the unrowed port's parsing code. `InstantDeathBehavior.cpp` currently LINKS by referencing that port's static `DieMuxData::getFieldParse`.
Completed: both a minimal bitset-only cleanup and a narrower removal of the port's field-parser definition were tried and fully reversed. The narrow trial makes DieModule preview clean but stops emitting its matched `_Base_bitset<2>::_S_maskbit` row and makes InstantDeathBehavior unresolved. The restored source passes 1/1 and restores that consumer's 34-byte LINKS result. Raw evidence: `build/link-worker-20261026-w2/die-consumers-before2.log`, `die-parser-preview2.log`, `die-parser-build.log`, `die-restored-preview.log` and `die-restored-build.log`.
Remaining / next check: reconcile the native field-parser provider and all actual callers together before removing the port; retain explicit ownership of the bitset row. This seat stops on the demonstrated linking-consumer regression and retains no DieModule edit.
**2026-10-29 recheck, seat dd-14, index `85f6b7f40c`:** retail's provider side is now
known. `DieMuxData::getFieldParse` (RVA 0x4CE52E, `mov eax, offset 0x00C5FFA0; ret`)
returns the table at VA 0x00C5FFA0, whose six entries are DeathTypes ->
`?parseDeathTypeFlags@INI@@SAXPAV1@PAX1PBX@Z` (offset 0x0), ExemptStatus and
RequiredStatus -> `?parseFromINI@Rva003B1017@@SAXPAVINI@@PAX1PBX@Z` at 0x003B1327
(offsets 0x4 and 0x14), DamageAmountRequired -> `?parseReal@INI@@SAXPAV1@PAX1PBX@Z`
(0x24) and MinKillerAngle/MaxKillerAngle -> `?parseAngleReal@INI@@SAXPAV1@PAX1PBX@Z`
(0x28/0x2c). The port's four entries are ZH-shaped: it has VeterancyLevels, which
retail's table does not, and it binds ExemptStatus/RequiredStatus to ZH's inline
`BitFlags<45>::parseFromINI`. Trial (reverted): declaring `Rva003B1017`'s rowed
forwarder in the unit and binding those two slots to it compiles and is the retail
parser pair, but `./build.sh` then reports `_S_maskbit` not found in the object, so
the matched 13-byte row 0x004D051E is emitted only by that ZH inline - LINK-068's
coupling, reproduced with the retail table as evidence. Next: reconstruct the
retail table (six entries above) and find the retail-honest BitFlags<45> use in this
TU, or rehome the bitset row to a unit that already emits an identical copy, then
retire the port. No source edit, clearance or census gain is retained.
Clearance: pending. Census confirmation: not claimed.

**2026-10-30 dd-63 target-grouping pilot (base `92cfd28721`):** Grouped the 961
current `Code/gen_small` funclets by their retail relocation target: 328 targets,
of which 383 blocked rows name a missing callee, 90 resolve to a different body
and 101 lack a same-source parent EH location. Five targets were investigated on
boat with the supported tools. None of the five could land a proven identity.
`0x0007BB16` (15 rows, one name, one parent) is the near miss: the parent's
`??1FXParameter@?A0x4437e226@@QAE@XZ` compiles to a 5-byte tail jump to
`??1Rva0007BB16Record@@QAE@XZ`, which the object does not define, while retail's
0x0007BB16 body is the 53-byte record teardown. The pin was admitted only
because the owner name is an address placeholder, and the repoint byte gate
passed with the thunk in place; the check that catches it is the compiled
callee's body length, which the fold proof does not run for a placeholder-owned
address. The pin and all 15 repoints were reverted after that check.
The other four are source-shape blockers, not missing pins: `0x0010F149`'s
`??1ThingRef@@QAE@XZ` compiles to 37 B against retail's 12 B and the fold proof
refused the pin; `0x000AD6F4`'s parent dtor calls an out-of-line `clear()`, so
it compiles to a wrapper; `0x0049B47C` is a per-class vtable-store fold whose
DIR32 differs by owner; `0x0007FAB3`'s
`vector<PlayerAITypeEntry>::~vector` is declared out-of-line in both parents, so
no object defines the name. `0x0048BA39` was left alone (claimed by
yasinschroeder-claudec3). An anonymous-namespace callee also moves: the older
evidence names `?A0xa2308712` where the current object emits `?A0x4437e226`, so
recompile the parent before spending a pin on one. Next: for a target whose
compiled callee is a thunk, make the callee's body visible or inline in the
parent so the emitted body is retail's, then pin with `fold-proof=` and repoint.
No row was moved and no census gain is claimed.
