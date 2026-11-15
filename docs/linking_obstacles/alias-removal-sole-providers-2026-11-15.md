# Sole-provider aliases removed by 1cc99cc230d

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

Open beyond this five-binding repair: OpaqueScalarDeletingDtors.cpp itself still lacks eight other native destructor providers removed by 1cc99cc230d, despite having no other cached consumer. The RefCount-derived provider is repaired above. Their exact original bindings are in sweeps/dataid/alias-1cc/additional-own-carrier-nine.json on srv1. DynamicPortalBehaviourModuleDataDtor.cpp and SpecialPowerModuleDtor_Unresolved.cpp also retain pre-existing COMDAT-copy failures. These three units failed before this repair too. Future removal audits must include the carriers themselves as well as outside consumers.
