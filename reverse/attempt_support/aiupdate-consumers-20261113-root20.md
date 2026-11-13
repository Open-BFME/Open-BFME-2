# Fixed-header AIUpdateInterface consumer adoption

Seven consumers replace their private AIUpdateInterface declarations with the
existing native header. AIUpdate.h, its base headers, contracts, flags, pins and
ledger rows are unchanged. No AIUpdate or derived vtable is newly emitted.

The script construction action uses the existing primary slot 126 `construct`
and its typed template argument. The exact-waypoint action keeps the rowed
three-argument helper, including its 0x7fffffff argument, on the command base
at +0x20. Sequential-script processing reads canonical byte +0x3CA and writes
the existing opaque tracker storage at +0x3DA, without naming that byte's meaning.

The scripted-model draw consumer selects AIUpdate's supported Snapshot mode
before Geometry and keeps the state-machine position read at +0x24. Truck draw
keeps its existing path and locomotor receiver views through canonical accessors.
Waypoint rendering preserves the signed interpretation of +0x194 and calls its
existing state-machine helper rather than substituting a different wrapper.
Horde melee passes the surface-mask word at AI+0x1DC through the established
pathfinder ABI; it does not pass the address of the embedded locomotor set.

## Verification

- The original eleven-file cohort passes 482 function rows and 27 data rows.
- The seven adopted sources pass 34 function rows and one data row.
- All 165 external COMDATs common to the seven original and adopted sources
  retain their contents and relocation identities. Four shared-header accessors
  plus Truck's Object::getAI return-type respelling replace seven obsolete
  prefix-view helpers. There are no added or changed vtables. The accompanying
  JSON enumerates these differences.
- The three restored failed-trial files remain identical to HEAD. The fourth
  blocked source, GameLogicInit, has no retained edit. Restored GameLogic passes
  all 172 rows and four data rows.

Strict receipts pass for all seven sources. The unchanged owning acceptance
test passes each source and retires seven queue entries. The explicit scoped
preview preserves 11861 linked bytes against the historical aa7acf764d index
(2026-11-12 19:19); this is not a current whole-image closure measurement.
The four remaining prerequisites and rejected trials are recorded in
[the handoff](aiupdate-prerequisites-20261113-root20.md).

The latest authoritative real-link evidence remains run 43414575861 at
10efe4859ee37651bd6b7fdcc15d915325c9b9fa: 37 unresolved, zero duplicates,
no image, 469 initializer bridges and 3331 vtable bridges (50310 slots).
These caller adoptions establish no current whole-image or runtime result.
