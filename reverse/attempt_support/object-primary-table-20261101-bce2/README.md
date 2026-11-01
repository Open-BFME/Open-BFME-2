# Object primary table needs native overrides, not just a base-header swap

Inspected source base `8c6bd6ae65d`; published index `0d24c60eef`,
2026-11-01 09:19. Default link picker served ObjectDestructor.cpp at
`0x00299CE4`. No game source, shared header, ledger, pin or queue is edited.

Normal verification passes all 17 destructor-unit rows, including the complete
962-byte parent at `0x00299CE4..0x0029A0A6`, its handler and compiler-owned
cleanup bodies. The owned data row passes too. Frozen-file checks pass.
The ordinary preview still fails only on `??_7Object@@6BThing@@@`, whose copy
differs from the indexed first provider in ObjectConstructor.cpp. No new
linking gain is claimed; the picker's 1,182-byte credit is not a measurement.

## Native table and current emitted tables

The primary install in the matched constructor/destructor points at native
RVA `0x007FC300` (VA `0x00BFC300`). The data ledger records a 32-byte table
and includes the Thing-base spelling among its names. Read its eight pointers
from retail, not from inferred declaration order:

| Slot | Native target RVA | Current known ownership / behavior |
| --- | --- | --- |
| 0 | 0x0028B569 | Object::calculateHeightAboveTerrain, 44 bytes |
| 1 | 0x0047A6A9 | return this, three-byte ICF body |
| 2 | 0x0047A6A9 | return this, three-byte ICF body |
| 3 | 0x000D43D0 | return null |
| 4 | 0x000D43D0 | return null |
| 5 | 0x00292D49 | Object::reactToTransformChange, existing 362-byte owners |
| 6 | 0x0028B193 | existing unnamed Object member, 65 bytes |
| 7 | 0x0029A10F | existing opaque scalar-deleting Object wrapper, 28 bytes |

The unchanged destructor's private Thing view emits only a four-byte table
containing `??_EObject@@MAEPAXI@Z` at slot zero. It is not retail's primary
table. The canonical Thing header is already adopted by the constructor;
fresh normal verification passes all 49 constructor-unit rows. Its current
primary table has eight slots, but still inherits Thing's default overrides:
slots 1/2 emit `33 c0 c3` (null), where native emits `8b c1 c3` (this), and
slot 5 names `__purecall`, where native calls the matched Object callback.
Its slot 0 names Thing's height calculation, and slot 6 names Thing's empty
placeholder. These facts are recorded separately from the row-byte verdict.

Thus matching the constructor's current table, or merely adopting Thing.h
in the destructor, does not establish native correctness. This is an existing
root-view/override reconstruction prerequisite, not a demonstrated regression
caused by this investigation. The earlier vector begin/end/clear suppression
remains in place and was not repeated or extended.

## Next repair and preservation

Reconcile the native primary override profile and provider identities across
constructor/destructor and the existing rowed callbacks. Keep the protected
destructor ABI, virtual-base layout, complete parent/EH graphs, owned data and
other secondary tables verified. Check the deleting-wrapper binding as part
of that work; no new name or equivalence for it is admitted here. Header
acceptance, affected-consumer selection and the next scheduled census must
decide their own scopes. No stub, alias, pin, table suppression or borrowed
base-default workaround is added.

`native-proof.json` binds the observations to source/object hashes and records
the current COFF table relocations plus local default-getter bytes. The two
normal build receipts and failing ordinary preview are adjacent. Full-game
linking, smoke tests and complete consumer closure are not established.
