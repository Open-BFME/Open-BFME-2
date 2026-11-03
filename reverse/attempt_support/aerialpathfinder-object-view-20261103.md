# AerialPathfinder Object-view reconciliation, 2026-11-03

Inspected source: `d8af1ec58ab0eccfd34ccf03c7957c98238c0abe`.
Census index: `8661f15284`, 2026-11-03 20:03 UTC; `link_check.py --fetch-index`
confirmed the published index is the same revision. These are local previews,
not a new census or a real-link result.

## Verified source change

`Code/GameEngine/Source/GameLogic/AI/AerialPathfinder.cpp` used a private Object
prefix while `AerialPathfinderComputePath.cpp` included `GameLogic/Object/object.h`.
The first merge dry run failed because the shared Object definition has no `ai`
or `geometry` members under those spellings. The retained cleanup replaces the
private definition with that existing shared header. It uses its public fields:
`m_ai` +0x258, `m_geometryInfo` +0xA8, `m_id` +0x74, and inherited
`m_template` +4, `m_cachedPos` +0x38, `m_cachedAngle` +0x44. Existing local
AerialAI and GeometryInfo views interpret their storage. No new type name,
layout, pin, alias, ledger row or hatch is introduced.

These offsets are target facts already recorded by object.h and the matched
function comments. This is declaration reconciliation, with no new recovery
claim for original field names or the provisional AI/AerialPathfinder TU path.
The supported consolidation planner was run under `Code/GameEngine/Source/GameLogic/AI/`;
it reported unresolved routing in its stale-map snapshot and include/context
review prerequisites. No planner hint was used as TU approval. The merge tool
rebuilt current approval in memory (12 approved rows, no mixed/refused donor).
No TU map was committed or move applied.

`./build.sh Code/GameEngine/Source/GameLogic/AI/AerialPathfinder.cpp` passes
before and after: five function rows, one global data row, seven float literals;
the EH parent graph resolves the renumbered funclet label. The source's
`find_declared_unmatched.py` check passes before and after. The donor's check
also passes. The two existing absent-from-retail inline wrappers remain intact.

Both files pass combined `link_check.py`: 2/2 link, unchanged 3,278 predicted
linked bytes (1,138 + 2,140). The declaration change needs no register transfer:
source paths, row ownership, identity/data debt, header-queue ownership and fold
proofs remain unchanged. Existing GeometryInfo, Rva000421C8 and ThingTemplate
header-queue items remain unresolved; no debt retirement is claimed.

## Remaining merge refusal

After this cleanup, `tu_skeleton.py --merge .../AI/AerialPathfinder.cpp --dry-run`
gets beyond the compile failure and reaches its link guard. It still accepts
no donor: moving the donor earlier would select a different
`??0Id@ProfileHighLevel@@QAE@XZ` COMDAT. Inspection through
`link_census.comdat_section_bodies` finds identical six-byte `8bc1832000c3`
bodies in the original donor and the candidate object
(`build/tu_skeleton/6f7e53cd9d124a72.obj`). The combined standalone preview
calls this an unreferenced six-byte variant of the majority nine-byte body.
That diagnostic alone does not authorize moving it or bypassing the guard.

Next: check the guard's treatment of this unreferenced helper against the census,
or reconcile its inline-constructor emission in a separately verified change.
Do not repeat the unchanged merge trial. No reconstructed nonmatching body
remains in Code; both original units remain.

## Verification output

### Before cleanup

```text
Source claims: OK (1 sources, scoped byte-verified)
Data rows: OK (1 row(s) byte-verified)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Funclet pins: 1 row(s) verified past a renumbered $L label
    $L688 (Code/GameEngine/Source/GameLogic/AI/AerialPathfinder.cpp): $L688 was renumbered; verified parent EH data places $L1732 at 0x0077EAAF
Functions: OK 5/5 matched across 1 source file(s)
String-ref verify: OK (0 literals + 0 empty-string refs verified, 0 baselined, 0 unverified/skipped)
Float-ref verify: OK (7 compiler literals verified)
Import-ref verify: OK (0 named imports verified)
```

### After cleanup

```text
Source claims: OK (1 sources, scoped byte-verified)
Data rows: OK (1 row(s) byte-verified)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Funclet pins: 1 row(s) verified past a renumbered $L label
    $L688 (Code/GameEngine/Source/GameLogic/AI/AerialPathfinder.cpp): $L688 was renumbered; verified parent EH data places $L3276 at 0x0077EAAF
Functions: OK 5/5 matched across 1 source file(s)
String-ref verify: OK (0 literals + 0 empty-string refs verified, 0 baselined, 0 unverified/skipped)
Float-ref verify: OK (7 compiler literals verified)
Import-ref verify: OK (0 named imports verified)
```

### Combined link preview

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngine/Source/GameLogic/AI/AerialPathfinder.cpp: LINKS  LINKED 1,138 -> 1,138 bytes (census 2026-11-03 20:03 at 8661f15284; file's own bytes 1,138)
Code/GameEngine/Source/GameLogic/AI/AerialPathfinderComputePath.cpp: LINKS  LINKED 2,140 -> 2,140 bytes (census 2026-11-03 20:03 at 8661f15284; file's own bytes 2,140)
  diagnostic  ??0Id@ProfileHighLevel@@QAE@XZ  (codegen-like: 6 bytes against the majority copy's 9; unreferenced, not a blocker)
link_check: 2 of 2 link cleanly; LINKED 3,278 -> 3,278 bytes (6.8s)
```

### Initial merge trial

```text
tu: Code/GameEngine/Source/GameLogic/AI/AerialPathfinder.cpp
approved: 12
mixed: {}
refused: {}
accepted: []
rejected: {'Code/GameEngine/Source/GameLogic/AI/AerialPathfinderComputePath.cpp': "compile: Code\\GameEngine\\Source\\GameLogic\\AI\\.AerialPathfinder.fdeac67e52087430.tu_skeleton.cpp(193) : error C2039: 'ai' : is not a member of 'Object' | Code\\GameEngine\\Source\\GameLogic\\AI\\.AerialPathfinder.fdeac67e52087430.tu_skeleton.cpp(194) : error C2039: 'geometry' : is not a member of 'Object' | Code\\G"}
adopt_first: {'Code/GameEngine/Source/GameLogic/AI/AerialPathfinder.cpp': ['GeometryInfo', 'Rva000421C8', 'ThingTemplate']}
link_guard: census-linked: Code/GameEngine/Source/GameLogic/AI/AerialPathfinder.cpp, Code/GameEngine/Source/GameLogic/AI/AerialPathfinderComputePath.cpp
blocked: no verified merge of two or more donors
```

### Merge after reconciliation

```text
tu: Code/GameEngine/Source/GameLogic/AI/AerialPathfinder.cpp
approved: 12
mixed: {}
refused: {}
accepted: []
rejected: {'Code/GameEngine/Source/GameLogic/AI/AerialPathfinderComputePath.cpp': "link: Code/GameEngine/Source/GameLogic/AI/AerialPathfinderComputePath.cpp links at the census; the merged object would not: breaks another unit's copy of ??0Id@ProfileHighLevel@@QAE@XZ"}
adopt_first: {'Code/GameEngine/Source/GameLogic/AI/AerialPathfinder.cpp': ['GeometryInfo', 'Rva000421C8', 'ThingTemplate']}
link_guard: census-linked: Code/GameEngine/Source/GameLogic/AI/AerialPathfinder.cpp, Code/GameEngine/Source/GameLogic/AI/AerialPathfinderComputePath.cpp
blocked: no verified merge of two or more donors
```

