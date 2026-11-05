# AIUpdateInterface temporary-state header adoption

Inspected revision: `30b94b9156ced5a91159ad02bdeddcb60bada74a`.

Three units under `Code/GameEngine/Source/GameLogic/Object/Update/` now
include the existing `Module/AIUpdate.h` and `AIStateMachineClass.h` headers:

| Unit | RVA | Verified bytes |
| --- | --- | ---: |
| AIUpdateInterface_rva00263298.cpp | 0x00263298 | 27 |
| AIUpdateInterface_rva002632B3.cpp | 0x002632B3 | 20 |
| AIUpdateInterface_rva002632C7.cpp | 0x002632C7 | 26 |

The queued failure was conversion from the canonical AIStateMachine pointer
to a private Machine/MiniMachine pointer. The sources now use the canonical
AIUpdateInterface::m_stateMachine, AIStateMachine::m_temporaryState and
m_temporaryStateFramEnd fields directly. The notifier also uses the canonical
State::m_id and calls setTemporaryState without a receiver cast. The private
AIUpdateInterface, Machine, MiniMachine and RetState declarations disappear.
No shared header, symbol, pin, function row or source path changes.

Target facts: the existing rowed bodies read the machine pointer at +0x30,
temporary-state pointer at machine+0x50 and frame limit at machine+0x54; the
notifier reads the state ID at +4. The existing canonical headers document
these offsets from retail constructors and accesses. Those declarations and
the exact byte checks justify this consumed surface; no new donor identity
or recovered function name is asserted. The C7 source comment now agrees
with its existing ledger extent of 26 bytes.

Verification:

- `./build.sh` on the three paths passes before and after: 3/3 functions,
  73 bytes, with string, float and import reference checks passing.
- `find_declared_unmatched.py` passes before and after for all three paths.
- `header_adopt_lane.py accept --class AIUpdateInterface` passes all three
  units and retires exactly their three rows from `reverse/header_queue.tsv`.
- The explicit current-object `link_check.py` preview reports LINKS for all
  three: 27 -> 27, 20 -> 20 and 26 -> 26 bytes. Its census index is
  `c95fcfcfcd`, measured 2026-11-05 05:17. Fetching a newer published index
  returned HTTP 504; these results use the available local index and do not
  assert current-master census closure.
- `git diff --check` passes.

Scope: three header-debt rows retired, with preview-linked bytes preserved.
Other AIUpdateInterface queue entries and the wider module-chain obstacles
remain open. No new census-linked bytes or game smoke result is claimed.
