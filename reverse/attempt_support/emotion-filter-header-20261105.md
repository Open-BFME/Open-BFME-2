# EmotionTrackerUpdate nested-filter header adoption, 2026-11-05

Inspected revision: `975a6036d4`. Claim owner: `yasinschroeder-codexb5`.
Census index: `3a95b274a2`, 2026-11-04 22:40; refreshed with
`python3 tools/link_check.py --fetch-index` (18,108 objects imported).

## Retained repair

`Code/GameEngine/Source/GameLogic/Object/Update/Rva004B0FEBCtor.cpp`
includes the existing canonical `EmotionTrackerUpdate.h` instead of declaring
an eight-byte prefix and an object pointer. The nested filter constructor reads
`EmotionTrackerUpdate::m_object`, inherited from canonical ObjectModule at +8.
The nested class can access that protected member. This preserves the target
pointer load without a second class layout or any new provider, pin or hatch.
The separate Object and TauntPointFilter views remain as before.

The automatic adopter refused its token rename because `object` is also a
TauntPointFilter field. The retained edit changes only the qualified receiver
access, leaving the filter's own `object` member untouched.

## Verification

- `./build.sh Code/GameEngine/Source/GameLogic/Object/Update/Rva004B0FEBCtor.cpp`
  passes 5/5 rows before and after the change, with string/float/import checks
  clean. The funclet label is renumbered from `$L1988` to `$L2492`; the existing
  parent-EH verification still places it at retail RVA `0x0078E7C3`.
- The original object's ordinary preview is LINKS, 240 -> 240 authored bytes.
- `header_adopt_lane.py accept --class EmotionTrackerUpdate` on the changed
  source passes its byte/structural/link-preservation checks and retires exactly
  one header-queue entry. No census increase is claimed.
- `find_declared_unmatched.py` reports all defined functions already matched
  before and after. No source paths, ledger rows, shared headers or aliases move.

The original source/object were saved under untracked
`build/emotion-filter-header-20261105/` for this trial.

## Other selected consumers: unchanged

The supported automatic adoption trial retained none of the six selected
sources; the filter was then repaired directly as above. The other five sources
remain byte-for-byte unchanged:

| Source under Code/GameEngine/Source/ | Blocker / next prerequisite |
| --- | --- |
| Common/Thing/ModuleFactoryInit.cpp | Module redefinition from canonical Module.h; reconcile the factory's existing module base declarations first. |
| GameLogic/Object/Update/EmotionTrackerUpdate.cpp | `nuggets` at +0x90 is a 12-byte vector, while the canonical header exposes three raw pointers; reconcile the member interface and selected providers. |
| GameLogic/Object/Update/EmotionTrackerUpdateCtor.cpp | Same 12-byte vector prerequisite for `m_emotions`, including its construction and EH lifetime. |
| GameLogic/Object/Update/EmotionTrackerUpdateDtor.cpp | Same 12-byte member prerequisite for `m_emotions`, including holder destruction and free. |
| GameLogic/Object/Update/EmotionTrackerUpdate_update.cpp | Same 12-byte vector prerequisite for `nuggets` and its iteration interface. |

Do not retry those automatic swaps before their stated prerequisites change.
The wider derived-class/provider reconciliation and scheduled census remain
open; this repair establishes one consumer's header-debt retirement only.
