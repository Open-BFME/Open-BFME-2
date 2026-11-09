### LINK-011: provisional base classes and vtable mismatches in GameEngine subsystems and triggers

**Status: Repair landed / awaiting verification. Updated: 2026-10-25.**

- **Evidence / scope:** several GameEngine units used provisional `Rva...Base` classes
  that declared non-pure virtual functions (`unused()`, `~Class()`) without definitions,
  causing unresolvable vtable and destructor symbol references. In `PolygonTriggerCtor.cpp`,
  a secondary base declared `secondarySlot()` non-pure while `Rva002E3EB8Permuted` declared
  it pure virtual `slot() = 0`. In `Rva003BBAF0Ctor_Rva003FD199.cpp`, `BfmeBaseVNH` vtable
  `??_7BfmeBaseVNH@@6B@` was referenced without being defined. Total scope: 297 authored bytes
  across 4 units.
- **Completed:**
  - `SpecialPowerStore.cpp` (37 B): adopted canonical `SubsystemInterface` directly.
  - `EmotionSystem.cpp` (59 B): adopted canonical `SubsystemInterface` directly.
  - `PolygonTriggerCtor.cpp` (157 B): replaced ad-hoc secondary base with `Rva002E3EB8Base`
    declaring pure virtual `slot() = 0`.
  - `Rva003BBAF0Ctor_Rva003FD199.cpp` (44 B): defined `BfmeBaseVNH` vtable symbol (updated 2026-11-09: replaced the strong 8-pointer zeroed `??_7BfmeBaseVNH@@6B@` definition with an extern reference to the `SELECT_ANY` compiler table `??_7Rva002B3092@@6B@` from `GapBodiesGE01.cpp` at `0x007FE008`, clearing the real-link `strong-definition` vtable bridge refusal while keeping `link_check` 44 -> 44 B).
  - Verification: `./build.sh` byte-matches all 4 units (5/5 rows); `tools/link_check.py`
    confirms all 4 link cleanly (`LINKED 0 -> 297` bytes).
- **Remaining / next check:** await confirmation in the maintainer's next link census run.
- **Clearance / census confirmation:** cleared in ordinary-preview scope; census confirmation pending.
- **Recorder `Rva0037BBED` (2026-10-26):** `Rva0037BCC4DeferredCtorCRC.cpp` (157 B) lost
  `??_7Rva0037BBED@@6B@` to the 1-slot copies in `OpaqueScalarDeletingDtorsB07.cpp` and
  `Rva0037BBEDDtor.cpp`; all three now declare retail slots 0..1 (dtor, `init` at 0x0037B326).
  Its CRC-queue calls bind to the ledger's ICF owners `FXList::addFXNugget` (0x0037D097) and
  `FXList::rva0037BD64` through casts. `link_check.py`: 3 of 3 link, `LINKED 1,017 -> 1,174`.
  Retail vtable 0x00C18828 has 14 slots, slots 2..13 folded foreign bodies; no copy reproduces
  them yet. Census confirmation pending.
  - 2026-10-27: the three `Rva0037BCC4*.cpp` files, `RecorderCopyCurrentRecording.cpp` and
    `Rva0037D55EGet.cpp` are absorbed into `Recorder.cpp` (132/132; `tu_skeleton --merge`
    link guard census-linked). Until the next census, a plain `link_check.py Recorder.cpp`
    lists every absorbed symbol as `duplicate` against the deleted donors' census objects;
    that is index staleness, not a new obstacle.

**InGameUI product table prerequisite (2026-10-26, inspected `2a45addda1806342ac5c52757f63be902dcd428e`; index `d1f046749a`):** `Rva0008EF3FProductCtor_Unresolved.cpp` retains the undefined destructor and `InGameUI::slot11` through `slot59`. Native tables installed by its exact constructor are at VA `0x00BC7A88`, `0x00BC7A78` and `0x00BC7A64`. The primary table's slot 0 points to the rowed deleting destructor at RVA `0x0008F379`, named `Rva008F00D` in `Rva0008F00DDtor.cpp`; the secondary Snapshot table names the real InGameUI load/xfer methods and a separately named getter. The actual slot targets and current row homes are recorded in `build/link-worker-w5-c136/native-refs.log` and `native-target-owners.json`. These facts require a coherent class identity and table contract; declaring the non-pure slots pure would invent different tables. No class or member was renamed, no pin was added, and the unit remains blocked. Next check: reconcile the product, destructor and base interface views with all native slots before changing this constructor's declarations. Census confirmation is not claimed.

**InGameUI product table update (2026-11-09):** the constructor's three strong copies at VA `0x00BC7A88`, `0x00BC7A78` and `0x00BC7A64` were removed; it now stores the `??_7Rva008F00D@@6BInGameUI{Primary,Second,Third}@@@` compiler tables `Rva0008F00DDtor.cpp` emits (bound in `reverse/data_ledger.csv`). Those tables are still short (one placeholder slot each, bound by `/alternatename`), so the class-identity and full-slot prerequisite above is unchanged. Evidence: `./build.sh` matched; `link_check` 4/4 LINKS with the destructor and the BattlePlanUpdate pair.
