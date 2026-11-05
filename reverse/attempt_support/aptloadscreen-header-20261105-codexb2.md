# AptLoadScreen: two consumers adopt the canonical header

Inspected `8b681de717`, 2026-11-05. Claimed `class:AptLoadScreen` and both
changed source files. The header itself is unchanged.

`AptLoadScreenInit.cpp` now includes `GameClient/AptLoadScreen.h` instead of
declaring its own five-slot, baseless class. The game pointer and row/slot arrays
use canonical offsets +0x88, +0x90 and +0xB0. The embedded preview call uses a
view of canonical `field18` at +0x18; no lifecycle or preview identity is
asserted. `GameLogicInit.cpp` includes the same header instead of a private
0xD4-byte allocation-only class. The canonical extent assertion preserves that
allocation size and the constructor call keeps its existing identity.

Before and after:

- `./build.sh` on these two sources passes 234/234 matched rows, six data
  rows, 152 funclets, three emitted STLport constructor folds, 108 string
  literals plus 13 empty-string references, seven floats and 15 imports.
  The before build's cache output omitted the unchanged data-row summary;
  the after build explicitly verifies all six.
- `find_declared_unmatched.py` passes separately for each source.
- Ordinary `link_check.py` on the two-source cohort reports both LINKS:
  2,059 and 28,401 census-linked bytes, unchanged before/after, against
  `f44cbcf5b0` (2026-11-05 15:19). These are predictions against that census,
  not a new census or a real-link/runtime result.
- `header_adopt_lane.py accept --class AptLoadScreen` on the cohort returns
  PASS for both and retires exactly their two rows from `header_queue.tsv`.
- `git diff --check` passes. No ledger identity, pin, alias, shared-header,
  source-path, data-debt or code-identity register change is made.

The other two queued consumers were inspected and left intact. The constructor
contains a typed `AptMapPreview` subobject with automatic initialization and EH
cleanup; the destructor contains a typed `Rva0057E3DB` with automatic teardown.
The canonical header intentionally leaves the +0x18 representation as bytes
pending conflicting lifecycle identities. Their adoption needs lifecycle and
vtable reconciliation with byte/EH/link verification; a field-name substitution
alone cannot preserve automatic subobject cleanup. Their queue rows remain.
No TU merge or file-count reduction is claimed.
