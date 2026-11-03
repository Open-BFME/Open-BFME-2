# Bounded GeneralAllocator identity/provider review (2026-11-03)

Read-only tracked tree; no builds, claims or network. Main supplied HEAD8661f15284. Saved index is23b85ddde5 /2026-11-03 18:36, so this is bounded consumer evidence, not a new census.

## Name/signature transition

- docs/naming.md936..955 permits a hand rename when rename.py cannot express a signature change. Replace only a placeholder; cite canonical evidence in commit and re_log; update caller views; tombstone the exact old(name,RVA); leave name_basis.csv alone. This bool member -> destructor transition changes scope/return/special-member decoration, so plain rename.py identifier mode does not express it.
- Class spelling is independent retail evidence: reverse/exports.csv1452..1453 spell PAVGeneralAllocator@Allocator@EA in the two MemoryPool allocator exports. Header registration alone is not the evidence source.
- Destructor role is independent target lifetime evidence: complete derived93B body normal call6C3D08 ->34D00, plus unwind funclet7A7CF0 ->34D00; native34D00 is the whole5B jump to33D50. GeneralAllocator.h already records nonvirtuality and the correct thunk address. This supports a genuine destructor wrapper over existing bool shutdown, not changing shutdown's return ABI or asserting that the309B bool method itself is the destructor.
- Old placeholder34D00 has no pin, name_basis entry, tombstone or code user beyond its own class/definition in this bounded search. Keep the existing source path: current TU map has no approved home for either34D00 or33D50.

## Pin-removal and hidden consumer audit

See bounded-consumer-audit.json and review-index.json. In the retained published index:
- True destructor ??1GeneralAllocator@Allocator@EA@@QAE@XZ has zero definitions. Exactly one object touches it: Common/Rva006C3CC0Cluster. It is a retained root (normal/EH references), not merely an uninstantiated declaration.
- No alternate mapping, weak/default reference, imported spelling or extra COMDAT edge involving that exact destructor exists. Per-object reference roots include /INCLUDE:/EXPORT: directives by link_census.object_references; scanning those roots/edges likewise finds only Cluster.
- Old34D00 name is touched only by its own provider; no consumer object references it.
- Correct bool shutdown name ?rva00033D50@GeneralAllocator@Allocator@EA@@QAE_NXZ is defined in System/Rva00033D50Shutdown and touched by that provider, VslotSmallBodiesAJ, Rva006C21C0 and Rva006C38D0Cluster. Preserve it and those direct native33D50 routes.
- Obsolete derived-class bool pin ?rva00033D50@Rva006C1F60@@QAE_NXZ has no index touches/definitions; it is separate legacy debt and need not expand this patch.
- Therefore no retained caller was found that genuinely calls native33D50 under the destructor spelling. Removing the misaddressed destructor pin does not retarget any direct bool shutdown call. Root's fresh byte/EH/provider/consumer and outgoing batch audit remain the deciding current-input checks.

## Existing member wrapper boundary

Cluster's inline ~Rva006C17B0 wrapper calls rva006C17B0(true,false). Native10B6C21B0 is already rowed as ordinary ?rva006C21B0@Rva006C17B0@@QAEXXZ in Rva006C17B0.cpp, with existing destructor-name pin to6C21B0. The present-unmatched annotation is for the differently decorated inline destructor definition, not a claim that the physical10B body is missing. Its prose saying no ledger row is historical/stale, but do not change the marker, add alias, rename that10B wrapper or widen this work. Keep its emitted lifetime and binding unchanged.

Canonical header adoption in Cluster must retain member+684: base510 plus pad174. Header queue447ish GeneralAllocator entry must retire only through header_adopt_lane accept after root's verification. The separate Rva006C1F60 queue still has member-surface prerequisites; no blanket header clearance is implied.

Root reports private18/18 provider and4/4 Cluster exact, EH exact, no other emitted byte/properties/routes changed; reviewer did not rerun compilation. Existing LINK-006 paragraph already records the destructor/thunk discrepancy and should receive only this scope's completed evidence and remaining prerequisites.
