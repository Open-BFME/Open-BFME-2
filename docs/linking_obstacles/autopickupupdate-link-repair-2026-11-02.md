### AutoPickUpUpdate link repair (2026-11-02)

`AutoPickUpUpdate.cpp` (2,013B) unresolved `?crc@UpdateModule@@MAEXPAVXfer@@@Z` and COMDAT conflicts `??_7AutoPickUpUpdate@@6BAutoPickUpUpdateInterface@@@` / `??_7AutoPickUpUpdate@@6BObjectModule@@@` resolved:
1. Defined `BFME_SNAPSHOT_NAME_SLOT` before `ObjectModule.h` in `AutoPickUpUpdate.cpp` so that `Snapshot.h` correctly declares `GetSnapshotName` instead of `crc`, eliminating the unresolved symbol.
2. Reconciled `AutoPickUpUpdateDtor.cpp` to match `AutoPickUpUpdate.cpp`'s canonical 3-slot `AutoPickUpUpdateInterface` and `UpdateModule` hierarchy, resolving the COMDAT differences.
Verification: `tools/build.py` 29/29 matched; `tools/link_check.py` LINKS 0 -> 2,013 bytes in `AutoPickUpUpdate.cpp` and preserves 60 bytes in `AutoPickUpUpdateDtor.cpp` (total 2,073 bytes).

AutoPickUp follow-up (2026-11-03): the already-repaired paired cohort passes
29 current rows and retains its2,073-byte LINKS preview. Canonical filter-base
adoption preserves all27 source rows, EH4 and130 providers; main owning
acceptance retires one header entry. No new census gain is claimed.
[Header adoption and scope](../../reverse/attempt_support/autopickup-headers-20261103/README.md).

AutoPickUp inherited-module follow-up: the actual BehaviorModule dependency
is now explicit after UpdateModule. Main paired29-row checks and four owning
acceptances pass, retiring the three source ancestor keys and the destructor
interface key. No shared header or executable body changes.

AutoPickUp INI follow-up replaces the complete private prefix with its
canonical header while retaining the same inline separator getter. Current
29-row checks and owning acceptance pass; one INI entry retires. Private
27-row/EH4/130-provider identity is unchanged.

AutoPickUp containment follow-up adopts the complete canonical interface and
its existing getContainCount at slot69 in all four calls. Normal29-row checks
and owning acceptance pass, retiring the last of seven served header entries.
The final main object retains all130 provider bytes, relocations, COFF properties
and symbol routes from control; the paired LINKS preview stays2,073 bytes.
No new census gain is inferred. GUI push379efc587f still had one missing receipt
(GadgetTextEntrySetText) in the older-index broad audit; carry that scope into
the next scheduled census.
