# Coord3D atomic key-migration receipt audit

2026-11-07, stable HEAD `50a776d8b4deafcb6c9ce990f8d622f2b5a948af`.
Read current AGENTS.md. No claims, network, builds, tracked edits or workers.
`audit.py` and `cohort.json` hold the bounded method and per-source results.
The function/pin/data ledgers and canonical header hashes stayed unchanged.

## Bounded cohort result

The canonical Coord3D.h remains `struct`. Its basename graph is **not** its
actual definition-selected migration cohort:

| Evidence | Sources |
| --- | ---: |
| header_dependents basename graph, ledger-backed | 3,370 |
| Receipts record the exact canonical header path | 2,570 |
| Exact canonical input, receipt current by source/dependency hashes | 2,063 |
| Of those, canonical Coord3D.h is the first definition-guard provider | **2,003** |
| Of those, a companion wins the shared guard | **60** |
| Basename-graph sources with stale/missing receipts | **599** |
| Basename-graph sources with current receipts excluding the exact header | 708 |

The 60 companion-selected units divide into CtorView43, Inline15 and
DerivedView2. The canonical file is still a recorded input there, so a normal
header verification gate may reach them; **changing only its class-key does
not change their selected Coord3D definition**. Updating companion keys is a
different, expanded migration. Eight other current canonical-input sources
also record a companion, but canonical Coord3D.h occurs first and wins.

The 599 unknowns include507 stale receipts that previously listed the exact
canonical path and92 other missing/stale cases. Do not exclude them from a
safe planning envelope based on old include lists. The audit establishes a
confirmed lower bound plus unknowns, not a complete minimal atomic transaction.
Code/data symbol consumers and the pin/fold-proof admissions remain separate
closure requirements owned by root.

## Function/pin/data populations

Current narrow name inventory: **1,111 supported function-name changes plus
6 unsupported rows**, **85 pins**, **3 data rows**, no converged-data name
change. The function records have522 distinct owners:

| Current owner evidence | Sources |
| --- | ---: |
| Selected canonical Coord3D.h | 344 |
| Selected known companion: CtorView40 / Inline9 / DerivedView1 | 50 |
| Current noncanonical seed definition, excluding companions | 18 |
| Current source-local private definition | 2 |
| Current receipt excludes canonical; no complete definition found | 18 |
| Stale/missing receipt, selection unknown | 90 |

The two current private-definition owners are
`GameLogic/Pathfinder/PathfinderAttackView.cpp` and
`GameLogic/Object/Weapon_bfmeGetLOSVictimPos.cpp`, under
Code/GameEngine/Source/. The JSON retains every exact seed-header path and
source definition location. Textual definitions are not confused with
current receipt evidence when a receipt is stale.

The85 pins have no source field. Matching their RVA to current matched rows
gives56 single-source candidates and29 multi-source candidate sets; **no pin
is ownerless by that lookup**. The56 classify as canonical24, seed2, private2,
current-no-definition16 and stale/missing12. The29 multiple-source sets are
not29 resolved owners: ICF aliases bring unrelated sources into the same RVA.
The union of all provider candidates plus direct function/data owners is922
sources; **that is not a proposed atomic C++ cohort**. Exact candidates and
their independent receipt states are retained per pin in cohort.json.

Of the three data rows, GeometryContactOrigin in
Common/System/GeometryInfoCollidesWith.cpp has a current canonical-selected
receipt. The two BfmeFollowSavedPosition/BfmeFollowSavedOffset23E8 rows share
W3DView.cpp, whose receipt is stale; its current definition selection is not
established by this audit.

## The six unsupported rows

| Rows | Current owner / selected definition | Consequence |
| --- | --- | --- |
| 7B9AE0 local geometry destructor | Common/Rva009F66F0.cpp; current receipt, BF1 game/Libraries/Source/WWVegas/WWMath/coord.h, no canonical input | Outside a direct canonical-header-only rekey; remains relevant to a global private/seed migration. |
| 7B7D27,7B7D31,7B7D3B rally statics | GameLogic/System/GameLogicDispatchDoSetRallyPoint.cpp; stale receipt previously included canonical | Potential canonical blockers. The recorded Drawable.h hash differs. Current source directly includes canonical Coord3D.h, corroborating the lead but not repairing the stale receipt. |
| 48963C Dozer adjustor | GameLogic/Object/Update/AIUpdate/DozerAIUpdateCtor.cpp; current receipt, **CtorView selected** | Not rekeyed by changing only canonical Coord3D.h. It becomes a real unsupported-row blocker when CtorView's key also changes. |
| 4AA3A0 Worker adjustor | GameLogic/Object/Update/AIUpdate/WorkerAIUpdateCtor.cpp; current receipt, **canonical selected** | A direct canonical-header key migration blocker. |

Dozer is a concrete guard trap: it includes Coord3DCtorView.h at source
line183; that companion defines CANONICAL_COORD3D_H and its own struct. Its
receipt lists CtorView before canonical Coord3D.h, so the latter's definition
is suppressed. Worker directly includes canonical Coord3D.h at line148 and
records no companion. These are different cases despite both receipts listing
the canonical filename.

Snapshot.cpp has a current exact canonical input and no competing recorded
definition. It is in the canonical-selected group, consistent with root's
private class-key compiler proof.

## Evidence boundaries

Used header_dependents.scan/graph/dependents at HEAD, its exact receipt_path
mapping and receipts API, and streaming narrow ledger filters. Source universe
contains17,965 recorded owners;3,704 sources needed receipt classification.
No full function ledger was loaded into memory. Receipts are resolved by full
normalized path, not basename; stale paths are kept only as historical leads.

Guard selection uses receipt dictionary encounter order plus the known shared
CANONICAL_COORD3D_H guard. Normal `_write_deps_sidecar` records first
/showIncludes encounter; current bundle export/import preserves that order.
Source include order and companion contents corroborate the Dozer/Worker
distinction. This is not a fresh preprocessor run.

“Current” means the header_dependents API's source and recorded-dependency
hash checks against the clean HEAD inputs. It does **not** claim a fresh
compiler proof, command/profile fingerprint validation or census-grade
negative include-search inventory. A missing/stale receipt cannot prove
exclusion; a current receipt is evidence of the recorded compile's input and
guard ordering, not that every future compiler environment resolves identically.
The canonical-selected list, companion-selected classifications, unknown
envelope, six unsupported rows and pin ambiguity are all explicit in cohort.json.

Root's planned handoff/release can cite these bounded counts and prerequisites.
No migration or background work was started.
