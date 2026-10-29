# AIStates CRT header cleanup

Base: `2ede5f876a`, 2026-10-29. Source:
`Code/GameEngine/Source/GameLogic/AI/AIStates.cpp`.

The Microsoft-header picker claimed the file for its local `fprintf(void *,
const char *, ...)` declaration. The unit now includes the toolchain's real
`<stdio.h>`, and its three logging paths cast the existing opaque stream to
`FILE *`. The unit-level `/D_CRTIMP=` preserves its direct `_fprintf` thunk
reference under `/MD`; no local CRT prototype remains. This switch also reaches
the unit's existing math headers, so the complete object comparison below is
required evidence for the scoped change.

Verification:

- Before and after `./build.sh`: 8/8 function rows, seven string literals and
  fourteen compiler float literals pass. No named-import rows are present.
- `find_declared_unmatched.py` passes before and after.
- `link_census.object_facts` compares the saved pre-edit object with the freshly
  built object: all 65 COMDAT name/digest/size records, eight strong definitions,
  78 undefined names and zero weak externals are identical. `_fprintf` remains
  the only fprintf external. This establishes preservation of the existing
  call bindings as well as emitted inline/helper definitions.
- `link_check.py --prepare-current` passes for this explicit source with strict
  reusable receipts; it changes no census/index/status.
- Ordinary `link_check.py` reports LINKS, retaining 4,714 authored bytes against
  index `85f6b7f40c` (2026-10-29 15:08). The unreferenced StateMachine idle-state
  and Coord3D vector diagnostics remain outside the blocking scope.
- The Microsoft-header scan reports zero local Microsoft declarations. Its
  `refresh_queue` API removes just this file's one-definition queue entry,
  preserving all unrelated records. `check_csv.py` passes.

The staged-tree `link_batch_audit.py` is INCONCLUSIVE: the index predates the
base and affected consumer
`Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a current
receipt. Carry that consumer and this provider into the next scheduled census.
No new census linking gain or consumer-wide clearance is claimed.

The original default link pick was `Rva004E0D67Dtor.cpp` (LINK-024). Inspection
confirmed the already-recorded class identity prerequisite: the supported
class rename cannot combine the existing LivingWorldBuilding spelling with
its placeholder destructor view. No source trial or new rename was attempted,
and both the body and file claims were released before selecting this cleanup.
