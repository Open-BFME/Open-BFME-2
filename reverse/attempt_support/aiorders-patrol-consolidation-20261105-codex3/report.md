# AiOrdersManager patrol consolidation prerequisite

Base: `613be2873f`, 2026-11-05. Scope: the approved System/AiOrdersManager.cpp
TU and its sole remaining clean donor, AiOrdersManagerPatrol.cpp.

The evidence planner's original-path catalogue does not itself approve these
placements. `tu_skeleton --plan` rebuilds the stale map in memory and approves
14 rows in this TU; all 17 code rows in the two files must survive composition.
No regenerated TU map is committed.

The initial dry run reproduces the recorded C2460/C2065 ObjectID failure.
The seed declares its own enum before a later donor includes the existing
GameLogicObjectLookupView.h enum. Removing the duplicate during composition
leaves the seed's queue declarations before the surviving enum definition.
Including the existing header at the seed's first ObjectID use fixes that
ordering. Its INVALID_OBJECT_ID enumerator supplies the same zero value.

The next diagnostic exposes GroupOrder's two vector element spellings. The
patrol donor now uses the seed's ObjectID spelling and matching inline-only
accessor specializations. This is a shared provider view, not new evidence
of an original BFME source declaration. The target facts are the 32-bit IDs,
the vector at GroupOrder +4, and the exact compiled bodies.

Finally the seed adopts the unchanged canonical AiOrdersManager header. Its
existing map provider types remain in a local accessed-layout view at native
offsets +0x10/+0x24, as documented in the canonical header. No second global
or class definition is introduced. The remaining NameKeyGenerator private
provider view and its header debt are unchanged.

Verification:

- Baseline: 17/17 code rows across both sources (`before.txt`).
- Canonical seed: 15/15 rows, four string references and both renumbered EH
  funclet bindings pass (`canonical-bytes.txt`).
- Patrol donor: 2/2 rows pass (`patrol-bytes.txt`).
- `find_declared_unmatched.py` passes both sources.
- Owning `header_adopt_lane.py accept --class AiOrdersManager` passes and
  retires exactly one header queue row (`accept.txt`).
- Current-object preview preserves LINKS for 1,314 + 414 authored bytes
  against index c95fcfcfcd (`prepared-link.txt`); no census gain claimed.
- Supported merge dry run accepts both sources with no rejected donor,
  preserves 17 rows and passes the census-linked guard (`dry-run.txt`).

The prerequisite source changes are committed separately before applying the
supported merge. The merge must retain the remaining source's debt and run
the complete outgoing path-consumer audit before publication.
