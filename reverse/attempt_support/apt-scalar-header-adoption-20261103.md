# Apt collector and scalar-pool header adoption

Inspected source revision: `950ca57fb939b7f224e8384ec528e17eec23d38c`.

`AptGC.cpp` now includes the existing AptValue, AptBoolean and AptInteger
headers instead of its three private declarations. Its former `unused9` and
`unused13` calls use the existing header's `DeleteThis` and `vslot13` slots.
`AptScalarClearPoolsBFME2.cpp` adopts AptBoolean and AptInteger and reads their
existing `field08_next` union members. The separate AptFloat view is unchanged.

Target facts: the headers document the native fifteen-slot AptValue table,
the collector's slot identities and the scalar pools' four-byte links at +8.
The changes reuse those declarations; they introduce no new names, layout
claims, pins or linker aliases. No donor source was consulted for this change.

Verification:

- `./build.sh Code/Libraries/Source/Apt/AptGC.cpp
  Code/Libraries/Source/Apt/AptValue/AptScalarClearPoolsBFME2.cpp`: 4/4 matched;
  three string literals verified; float/import checks passed.
- `header_adopt_lane.py accept --class AptBoolean` and `--class AptInteger`
  for both units passed and retired two rows each. `accept --class AptValue`
  for AptGC passed and retired one row. Five queue rows retired by the owning
  tool, with structural, byte and link checks.
- `find_declared_unmatched.py` for both units: all defined functions matched.
- `link_check.py` for both units, against census `8661f15284` of
  2026-11-03 20:03 UTC: AptGC LINKS, 345 -> 345 bytes; scalar pools LINKS,
  165 -> 165 bytes. Total 510 -> 510; preview only, no census gain claimed.

The other eight AptBoolean cohort units remain queued. A fresh automatic
adoption trial left them unchanged: interpreter data-row failure; constant
handlers' abstract AptArray; parse stream's line splice/trigraph guard;
duplicate AptValue definitions in AptMiscObjects, AptArrayConstructor and
AptKeyLookup; the Boolean factory's anonymous union; and built-in construction's
bitfields. These need separate reconciliations, not debt-row deletion.
