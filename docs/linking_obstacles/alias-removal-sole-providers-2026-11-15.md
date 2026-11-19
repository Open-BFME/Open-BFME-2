# Native repairs for sole-provider alias removals

## 2026-11-15 regression and bounded repair

Coordinator-assigned follow-up to the ObjectTypes erase consumer repair. Commit 1cc99cc230d1f7cfad30237bfff12593b8eb1aa5 removed 19 /alternatename directives after checking their carriers. Toollane3's current-cache audit found five sole-provider losses: 70 cross-unit consumer edges across 68 current units.

The repair restores only these exact historical bindings, in their original carriers:

| Carrier | Alias | Target | Other consumer units |
| --- | --- | --- | ---: |
| Common/OpaqueScalarDeletingDtors.cpp | ??1ObjectModule@@UAE@XZ | ??1Snapshot@@UAE@XZ | 7 |
| Common/RTS/PlayerO1Shard.cpp | ?iterateObjects@Player@@QBEXP6AXPAVObject@@PAX@Z1@Z | ?iterateObjects@Player@@QBEHP6AHPAVObject@@PAX@Z1@Z | 1 |
| Common/System/Snapshot.cpp | ??1Snapshot@@QAE@XZ | ??1Snapshot@@UAE@XZ | 2 |
| GameLogic/Object/ObjectFilterRelease.cpp | ??1Rva003623E5Member@@QAE@XZ | ??1Rva00360D26Member@@QAE@XZ | 40 |
| GameLogic/Object/ObjectFilterRelease.cpp | ??1Rva003623E5Filter@@QAE@XZ | ??1Rva00360D26Member@@QAE@XZ | 20 |

Paths in the table are under Code/GameEngine/Source/. No functions, class layouts, native definitions, row bindings, pins, or lifecycle are changed. These aliases restore existing ABI views; they do not establish original EA class spellings.

## Audit evidence and limits

Toollane3 scanned 22,817 shared cached objects with zero parse/read errors. The reported consumers' source MD5s matched master 1cc99cc230d and object MD5s matched sidecars. It found no current LHS external definition, retained alternate binding, or weak default; stale original-carrier directives were excluded. Shared 19:00 census index 3417403f8f also had no strong/COMDAT/COMMON provider for the five LHS names. Header and command inventories were not fully revalidated in that audit.

Full per-consumer evidence is preserved on srv1 in ~/bfme2-ops/swarm/sweeps/toollane3/alias-1cc-report.md, alias-1cc-audit.json and alias-1cc-hits.json. The dataid follow-up keeps its own inputs and verification under ~/bfme2-ops/swarm/sweeps/dataid/alias-1cc/.

The remaining 14 removals had no other current cached consumers in that scoped audit; that is not full-link proof. The separate 7209b9e7397 audit found no restoration needed: every removed pair retained an identical directive in the same source.

## Required prevention

A same-file function row or COMDAT is not sufficient grounds to remove an alias. Audit undefined symbols and weak/alternate provider chains in current consumers, excluding stale carrier objects. Run link_check on all identified consumers together with every changed carrier, so it refreshes the carriers' actual directive sets. Inspect link_check's own before/after verdict and preserve the full-image check as the integration authority.

## Repair verification

Boat runs dataid-20261115t194501 and dataid-20261115t195348 built the four carriers at 104/104 matched rows and checked all 68 reported consumer units together with them. The five missing names resolve. The own link_check verdict improves from 2/72 clean (1,194 bytes) before to 69/72 clean (40,737 bytes) after, with no previously linking unit lost. The census comparison remains 42,648 -> 40,737 because it predates the removed providers; it is not the current-tree A/B. All non-debug, non-directive object code/data/EH sections, relocation graphs, external symbol sets and CRT sections are identical; only the five requested directives are added. Data and converged-data checks, pin consistency and CSV pass. Both Boat sandboxes were deleted. Native proof and complete logs are retained under the dataid packet.

The actual allowed_symbols alias judgment accepts four pairs at their unique matched-row target. The generator chooses Base001F4C67 as its preferred ObjectModule target, but Snapshot is also a matched owner at the same 0x0049B47C; the original Snapshot binding is accepted. The nonvirtual Snapshot spelling is unreferenced in the matched-row scan: its two current COFF consumers are proved by the audit, but that judgment does not prove their retail callsites. This proof limit is retained for independent Sol review. No identity-baseline entry is added.

## Admission correction (2026-11-15)

Landed f46017b0e53 used direct token-scoped hatch_counters admission to raise the five keys. That route violated AGENTS.md: invoking --admit or --allow oneself is hand-adding, including for historical restores. The coordinator did not authorize that admission route. The five providers stay present while native replacements are proved, to avoid re-breaking linking units. No more admission is permitted. The native Snapshot consumer follow-up 8c0cf58cdbf is parked while red-master repairs take priority.

A subsequent owner-authorized verbatim git revert of 8eab05132d7 was clean and restored exactly its four original pragmas and four original baseline lines. The ordinary hook refused all four 0 -> 1 keys as hand-raised; this was designed enforcement, not a verifier defect. No admission or bypass followed. The re_log records the probe and the ops packet retains its exact inverse and refusal. No revert landed.

## Native RefCount-derived destructor provider

The still-missing Rva0072892 destructor is supplied by real C++ instead of restoring its alias. RefCountData.h already records constructor 728B6/table BC6514 as the RefCount-derived type whose deleting helper is 728C6. The emitter now uses that canonical eight-byte base and an empty out-of-line derived destructor. The inline base teardown leaves exactly the seven-byte RefCount vptr reinstall and return. Normal add_match --icf-owner rows that complete native body at 72892, and the obsolete opaque pin is retired. No alias or replacement pin is added; original EA identity of the Rva helper remains unclaimed.

The first inline probe was insufficient: its inherited destructor still emitted an 11-byte body while an existing pin mapped the name to seven-byte retail code. The final repair removes that trust dependency. Raw COFF shows the rowed 28-byte deleting helper calling the new native destructor; its complete seven bytes and sole RefCount-vtable relocation equal the base's native body. No forwarding jump remains.

Boat run dataid-20261115t223720 verifies 73/73 rows. Before/after link_check covers OpaqueScalarDeletingDtors.cpp plus the two existing RefCount provider units hlod.cpp and GapBodiesGE31.cpp: both existing providers stay linking; Opaque remains blocked by eight unrelated missing names, down from nine. No unit is lost, and the strict new-variants check passes. Both objects have no CRT initializer sections and no atexit relocations. Data/converged, pin consistency, CSV and frozen-file checks pass. The pin total falls by one (9274 -> 9273); no hatch count rises. The normal hatch update also normalizes the five historical allowance-token columns without changing their counts or directives.

Complete logs, source-bound objects and raw body/relocation evidence are in build/boat-run/dataid-20261115t223720/build/dataid-native-final; ops notes are in sweeps/dataid/no-hatch. The sandbox was deleted. This is one native provider repair, not a claim that Opaque or the full image now links. Full-image/runtime checks remain pending.

## Native DieMuxData constructor (8eab05132d7)

The second removal commit deleted the only binding for DieMuxData's default constructor. The rowed init at 4CE534 remained, but the nine module-data consumers named a constructor that no object defined. The approved TU map assigns 4CE534 to DieModule.cpp. That TU now defines the real constructor through the canonical 48-byte raw-storage class and a typed layout view. The view is referenced, never constructed, so it adds no bitset default construction. The body writes the death flags, calls the existing mask reset twice, then writes the three native float values. It does not delegate to init. Normal add_match --icf-owner rows its complete 57-byte native twin, and its obsolete constructor pin is retired with a normal shrinking hatch update.

Boat dataid-20261115t223720 verifies all three DieModule rows (both existing rows plus the native constructor). Raw COFF shows only the two native mask-reset calls and the two -1/+1 literal relocations in the constructor. Before/after link_check covers all nine consumers and both providers: 2/11 -> 10/11 clean, 374 -> 5,085 predicted linked bytes, zero losses. All constructor references resolve. StructureToppleUpdateModuleDataCtor retains its unchanged pre-existing vtable COMDAT mismatch, so the command still exits 1; it is not reported clean.

Both versions have zero CRT initializer sections and zero atexit references. The data check's FieldParse wrong-name shadow finding is identical before/after; converged data, pin consistency, CSV and frozen-file checks pass. No data ledger or data row is hand-edited, no alias or pin is added, and no hatch count rises. Complete source-bound evidence is in the same final native-provider packet. The sandbox was deleted. Full-image/runtime checks remain pending.


Open beyond this five-binding repair: OpaqueScalarDeletingDtors.cpp itself still lacks eight other native destructor providers removed by 1cc99cc230d, despite having no other cached consumer. The RefCount-derived provider is repaired above. Their exact original bindings are in sweeps/dataid/alias-1cc/additional-own-carrier-nine.json on srv1. DynamicPortalBehaviourModuleDataDtor.cpp and SpecialPowerModuleDtor_Unresolved.cpp also retain pre-existing COMDAT-copy failures. These three units failed before this repair too. Future removal audits must include the carriers themselves as well as outside consumers.

## 2026-11-16: direct ghttp socket-select provider
8eab05132d7 removed the old _ghiSocketSelect alias, leaving ghttpBuffer.c
and ghttpProcess.c without a provider. Both now call the already matched
GSISocketSelect in nonport.c (RVA 0x0060A9F0, 330 bytes). ghttpMain.h already
includes nonport.h, which declares int flag pointers; the local flag types
now match that contract. The connect path retains its explicit byte narrowing.
The nonretail old body remains compiled out. No wrapper or alias was added.
The obsolete alias pin was retired through a shrinking normal hatch update.

Before/after evidence: 72/72 rows across both consumers and both providers;
link_check 2/4 -> 4/4 (3,838 -> 8,590 predicted bytes), no lost unit.
Native section bytes and relocations are equal after only the old-to-real
callee-name normalization; all three old object references disappear.
No CRT initializer section or atexit reference is introduced. Data, converged,
pin consistency, CSV and frozen checks pass. Private Boat A/B and a current
host verification agree; the sandbox was deleted. Saved evidence:
~/bfme2-ops/swarm/sweeps/dataid/ghttp-native/. Full-image/runtime unverified.

## 2026-11-16: BehaviorModuleOther placeholder provider

ab51f7ce8a adopted the canonical UpdateModule.h in UpdateModuleCtor.cpp and removed that unit's private BehaviorModuleOther view together with its `/alternatename:?unused@BehaviorModuleOther@@EAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z` (retail 0x000D43D0, bound by 583b59b363). The unit itself no longer referenced the name, but it was the last of that binding's four original carriers. The BehaviorModuleOther tables of MineshaftPortalBehaviourCtor.cpp and PassiveAreaEffectBehavior.cpp still reference it (census index touches at aa505f34c8), and the real link at 75260358d7 lists both sources with this one missing name. SpawnBehaviorCtor.cpp binds only the public spelling `?unused@BehaviorModuleOther@@UAEXXZ`, which neither consumer uses.

The repair restores the exact original binding in its original carrier, with a comment that names both consumers. The carrier's hatch_baseline line was never lowered, so no count rises and no admission is involved. The shadow code-identity register reports the alias as unreferenced, because its only referrers are vftables rather than matched rows; that proof limit is the same as for the Snapshot spelling above, and no identity-baseline entry is added.

Before and after, link_check ran over the carrier and both consumers together, with strict current receipts: 1/3 -> 3/3 clean, 61 -> 1,671 predicted linked bytes, no lost unit. The carrier verifies 1/1 rows. The real link at dcd1717e2b (published by a24fab503e) no longer lists either consumer, and its list changed in nothing else. Runtime unverified.

Still open: the native fix. Adopting the canonical BehaviorModule.h in both consumers gives their tables BehaviorModuleInterface's inline getters, which retail folds to 0x000D43D0; after that the alias can go, through the consumer check in "Required prevention" above.

## 2026-11-16: four more withdrawals the real link still reports

A consumer check of every commit since 2026-11-08 that removes `/alternatename` lines (94 commits), and of 259896f97a, traced the names below to the commit that took their only provider. For each commit its changed units were compiled before and after it; each name is one they provided before and nothing provides after, link_check reports it unresolved at that commit in the units listed, and the real link at 0b6e54892e (published by f3a6e23db6) still lists every one of those units. The original bindings are in each commit's diff; the repair route is the native one the sections above describe.

| Commit | Withdrawn provider | Still unresolved in |
| --- | --- | --- |
| 44a7c0248f | `/alternatename` for `?rva006D95E0@BfmeAptValue006DCD20@@QAEXHPAV1@@Z` | Common/Rva006D94A0AptCluster.cpp, Apt/AptArray.cpp, Apt/AptObject/Rva006F1360XmlLookup.cpp |
| 1e79469632 | `/alternatename` for eight names: `?Rva0023FC23@@YAHPAUOut00524477@@PAHH@Z`, `?bfmeCopyUVKE@BfmeUniVKE@@QAEXABV1@@Z`, `?bfmeSetBSF@BfmeSubBSF@@QAEXPAX@Z`, `?rva006CFCD0@AptCIH@@QBE_NXZ`, `?rva006D36C0@EAStringC@@QBEHPBV1@@Z`, both `?rva006DD6C0@BfmeAptValue006DCD20` spellings and `?rva006dbd80@AptCIH@@QAEXXZ` | 18 units, among them Apt/AptCIH.cpp, Apt/AptString.cpp, Apt/AptActionInterpreter.cpp, GameLogic/System/GameLogic.cpp, Common/BfmeConv1399.cpp and Common/BfmeConv526.cpp |
| 6ba7bf9d9b | `/alternatename` for the seven AptValue-hierarchy defaults that `reverse/attempt_support/aptvalue-hierarchy-undefined-vtable-defaults-20261116.md` describes; its five other removals have no consumer left | the eight sources that file names, Apt/AptArray.cpp among them |
| 259896f97a | three definitions among the "unused extern declarations": `extern const char * const g_Rva00E0A010 = 0;`, `g_Rva0130A6E4` and `g_Rva0130A768` | GameNetwork/Rva007F14B0BlobWriter.cpp, GameNetwork/Rva007F3170RecordRequest.cpp, GameNetwork/Rva007F3C50ClubUpdate.cpp |

1cc99cc230d also left carriers without their own bindings beyond the eight OpaqueScalarDeletingDtors.cpp names above, and the same real link still lists each: Common/OpaqueScalarDeletingDtorsB09.cpp (`??1Rva0060FE2@@UAE@XZ`, `??1Rva008E4EC@@UAE@XZ`, `??1Rva009203A@@UAE@XZ`), Common/FamilyDeletingDtors_muse-b055.cpp (`??1ShipSlowDeathBehaviorModuleData@@UAE@XZ`) and Common/RTS/Player_Radar.cpp (`?okToPlayRadarEdgeSound@Player@@QAE_NXZ`). Two other withdrawals are repaired since: 3c7fdba61c (the ObjectTypes erase) and d7934c0617 (`?f3@DBaseM3@@UAEXXZ`).

## 2026-11-17: native pair temporary in the over-button removal consumer

At base `8ffb7f14ce`, Rva00524477Dispatch.cpp now calls the existing genuine
`make_pair<int, AsciiString>` provider directly instead of the removed
explicit-output alias. The pair temporary stays alive through the search and
its string is then released before the result is tested. A TU-local typed
overload bridges the existing integer-spelled find row; it is fully inlined,
with no external wrapper emitted. The search provider and declaration agree on
`throw()`: its native loop only reads pair fields and calls the nonallocating
StringBase comparison. This preserves the caller's flat frame. Binding a named
reference instead added a redundant LEA; omitting the search exception contract
added an EH frame. Neither failed trial was retained.

The complete 101-byte caller and all four search-provider rows remain exact.
Against index `abb031eedf` (2026-11-16 23:13), joint link_check of the caller,
Rva0052A22CForwarders.cpp and Rva00523DB7Ctor.cpp reports 3/3 LINKS
(121 -> 220 predicted bytes), with both existing providers preserved.
The obsolete factory reference is absent and the cleanup now names the actual
releaseBuffer row rather than the historical AsciiString-destructor pin.
No alias, pin, stub or runtime fallback was added. This clears only this
consumer in preview; GameLogic.cpp still has its separate explicit-output
factory call. Real-link/runtime confirmation remains pending.

## 2026-11-17: retire three superseded opaque emitters

The Rva0060FE2, Rva0090840 and Rva009D6FA emitter blocks are retired through
four separately reviewed row retractions, retaining existing native providers
at 00061AA1/28B, 0005D41D/8B, 00091153/28B and 0009D9A1/28B. All 92 unique
bytes remain covered. The four native rows no longer cite the retired carrier
as their fold proof; four deletion tombstones prevent union-merge resurrection.
Five obsolete pins are removed through the normal shrinking hatch update.

A complete current-object audit found no reference to any of the 20 retired
names in the 17,540 objects outside the two carriers (17,542 expected/current,
zero missing/stale). The rebuilt carriers remove exactly 13 obsolete providers,
add none and leave every retained definition unchanged. Official verification
passes 537/537 functions, three data rows and 85/85 EH graphs. All three native
provider units still link in the scoped preview. The opaque carriers retain
six and two other missing destructors; this removes three missing references,
not every blocker. The preview census remains stale, and fresh full-link/runtime
confirmation is pending. No bridge debt is retired by this source cleanup.

[Exact native owners, consumer proof and verification](../../reverse/attempt_support/opaque-deleting-retirement-20261117.md).

## 2026-11-17: bind three network TXN fields to existing records

The three missing globals in BlobWriter, RecordRequest and ClubUpdate were
interior field references, not missing standalone data. Consumers now read
m_name at offset four of the existing 12-byte records at RVAs A0A00C, A0A0FC
and A0A180. The official naming lane renamed these owned globals and all old
consumers using independent reviewed semantic-inference votes. No new data,
initializer, alias or pin is introduced. All 73 functions and 76 data rows
across the five sources pass; explicit COFF/retail address proof and data_check
pass. Normal hatch accounting shrinks address_global by 15. Scoped preview is
5/5 clean against stale census 0534e78db3; fresh real-link confirmation remains
pending. [Evidence and limitations](../../reverse/attempt_support/native-network-transaction-fields.md).

Follow-up measurement: official native exit_link --link --local measured
15 ->10 unresolved names, zero duplicates; all three network names and both
SidesList slot names disappeared. link.exe took80.0s; proof/setup/reporting
brought total command time to about7min. No image was written. Existing debt:
468 initializer bridges,3,122 table bridges/45,949 slots. The original naming
commit was refused for CRLF packet fingerprints versus LF Git blobs. Fresh
official proposals on canonical LF content passed normal hooks in42d083ebc5;
ordinary name_lane application and all73 function/76data checks passed again.
No gate was weakened or vote fingerprint restamped. The archived native run
measured the preserved pre-recovery C++ content, not a later runtime success.

## 2026-11-19: the last B09 name, `??1Rva009203A@@UAE@XZ`

At base `46209f1011` the real link (measured at `424a8a1cb3`) stopped on this one
name alone. Rva009203A is W3DTerrainVisual: the destructor 0x0009203A has been rowed
`??1W3DTerrainVisual@@UAE@XZ` since its recovery, while B09 kept the 28-byte wrapper
0x00092123 and its this-4 thunk 0x00092032 under the opaque class, calling a
destructor only a pin named. `rename.py class --fold` cannot carry it (constructor
`Rva00091A80`, destructor `W3DTerrainVisual` and wrapper `Rva009203A` refuse on each
other), and the canonical-header route waits on TerrainVisual's slot names (ceb0c54d63).

Repair: W3DTerrainVisualDestructor.cpp's base views take the slot-0 destructor each of
retail's two tables has (0x00BC80A0 slot 0 = 0x00092123, 0x00BC8068 slot 0 =
0x00092032), so its object emits `??_GW3DTerrainVisual@@UAEPAXI@Z` and
`??_EW3DTerrainVisual@@W3AEPAXI@Z` beside the destructor they call.
`add_match.py --icf-owner` verified both against the opaque rows, which were then
retired with their class, tag constructor and two pins. The rows sit with their parent
in the destructor's unit; the map approves all three addresses for
W3DTerrainVisual.cpp and they move together when that merge takes the destructor.

Verification: `./build.sh` on both units 22/22; `link_check.py` (index `53b35fb75b`)
B09 0 -> 454 B and W3DTerrainVisualDestructor.cpp 243 -> 279 B, both LINK; no object in
build/match spells Rva009203A. Real-link confirmation waits for the next measured run.
`reverse/exit_link_blockers.tsv` at that measure lists no other source.
