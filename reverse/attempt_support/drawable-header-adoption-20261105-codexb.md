# Drawable header adoption, 2026-11-05

Inspected source revision: `5b8658ce6860f34a9f6e12a6dcf75434ccab300a`.
Scope: the 25-file Drawable cohort served by the header picker, held under
`class:Drawable` by `yasinschroeder-codexb`.

## Completed

`DrawableHealthBarGate.cpp` now includes the registered Drawable header instead
of defining a private class. Both selected-state tests use canonical
`isSelected()`. The ID load remains inline through canonical `m_id`, before the
UI virtual call: canonical `getID()` is out of line, and moving the load after
the call changes register allocation. Neither form matched; loading the ID into
a local before the call restores the retail body. No header or pin changed.

`./build.sh Code/GameEngine/Source/GameClient/DrawableHealthBarGate.cpp` passes
the 472-byte row at RVA `0x0027601B`, including string, float and import checks.
`find_declared_unmatched.py` reports all defined functions already matched.

The following six files already included the canonical header. Their existing
queue diagnostics were stale; no source changes were needed:

- `DrawableIconAnchorPosition.cpp`
- `DrawablePhysicsXformHugeFourLegs.cpp`
- `DrawablePhysicsXformTreads.cpp`
- `DrawablePhysicsXformWheels.cpp`
- `DrawableSetInstanceMatrix.cpp`
- `Drawable_rva00272AD5.cpp`

All seven files passed `header_adopt_lane.py accept --class Drawable` (the six
unchanged files together, then HealthBarGate). The owning tool retired seven
rows from `reverse/header_queue.tsv`, after structural, byte and per-unit link
checks. `check_csv.py` passes: 99,458 functions, 9,319 symbols, 2,268 data rows.

## Link preview

An ordinary `link_check.py` of all seven final files used the published index
from `2026-11-05 05:17`, revision `c95fcfcfcd`. Every object was dependency-cache
current; every unit reports LINKS and retains its census-linked bytes:

| File stem | Bytes before / after |
| --- | --- |
| DrawableHealthBarGate | 472 / 472 |
| DrawableIconAnchorPosition | 160 / 160 |
| DrawablePhysicsXformHugeFourLegs | 1,565 / 1,565 |
| DrawablePhysicsXformTreads | 912 / 912 |
| DrawablePhysicsXformWheels | 2,151 / 2,151 |
| DrawableSetInstanceMatrix | 601 / 601 |
| Drawable_rva00272AD5 | 231 / 231 |

Total preview: 6,092 / 6,092 bytes. This is a retirement guard, not a new
census, real link or runtime measurement.

## Remaining cohort prerequisites

The mechanical adoption tool restored every rejected trial. The other 18
files retain their queue rows and original sources. Most require canonical
field coverage or a reconciliation of opaque private spans: health-bar region
`+0x460`, listener/module/interface storage, recent references, condition bits,
and several raw ranges. Vtable-at-zero private views also need reconciliation
with the inherited canonical declaration. LockDirtyStuff additionally declares
a static counter absent from the shared header; avoid a blind include swap.

`Drawable_rva0023998E.cpp` is separately implicated by the existing GameClient
header attempt: its receiver may be GameClient storage, so establish ownership
before extending Drawable to accommodate that private view. These failed swaps
provide no new layout or donor-name evidence. Next work should resolve the
specific field/receiver prerequisite before repeating the mechanical trial.
