# PartitionManager CRT math declarations and allocator binding

Inspected source base: `d8312347c8`. Claimed source:
`Code/Libraries/Source/partitionmanager/partitionmanager_impl.cpp`.

The picker served the old `wrong_selected2` link obstacle. Current source
already previews LINKS before this edit, consistent with LINK-151's repair;
this is header and helper-identity cleanup, not a newly recovered link.

Replace the local `ceil` and `floor` prototypes with the toolchain's `math.h`.
Both `stdlib.h` and `math.h` see imported `_CRTIMP` so their shared `atof`
declaration agrees. Scope the header's inline wrappers to this TU. Keep the
existing allocator macro and bind the FlightDeckInfo allocator specialization
explicitly to its existing `_STL::free` provider.

Target facts, checked in retail bytes:

- GetClosestObject, RVA `0x00628040`, extent 1,830 bytes: the indirect call
  at `0x00628220` is `FF 15 78 A5 BB 00` (`ceil` IAT VA `0x00BBA578`).
  Calls at `0x00628448` and `0x006284AC` use `FF 15 70 A5 BB 00`
  (`floor` IAT VA `0x00BBA570`). Header adoption preserves those imports.
- FlightDeckInfo vector growth, RVA `0x00627BC0`, extent 255 bytes: the
  direct call at `0x00627CA0` reaches RVA `0x00030830`, the GameMemory
  wrapper. The existing `?free@_STL@@YAXPAX@Z` pin names that provider.
  The old helper referenced `_free`, whose symbol pin instead names the
  CRT thunk at `0x00628F98`; using the existing wrapper removes that ambiguity.

These facts establish call targets, not new donor names or class layouts.
No row, pin, alias, class declaration, compiler flag or source path is added.

Verification:

- Before/after frozen-file checks pass. Final ordinary build and supported
  strict preparation each pass 13/13 rows, six float literals and three named
  imports. The existing funclet's compiler label renumbers, and its parent EH
  graph still verifies it at RVA `0x007A78B0`.
- The external COMDAT set remains exactly 93 names. All 93 retain identical
  body bytes and sizes; 89 retain identical fingerprints. The four changed
  fingerprints differ only by `_free` becoming `?free@_STL@@YAXPAX@Z`:
  the allocator and proxy deallocators, vector clear, and vector growth.
  The external symbol inventory only loses the undefined `_free`; weak
  aliases remain empty. Two new 20-byte math wrappers have storage class 3
  (TU-local), with no references to either. Scratch object snapshots and
  comparisons are in `build/partition-math-20261030-codexb4/`.
- The owning header scanner's scoped `refresh_queue` reduces this file from
  three findings to one, retiring both local CRT prototypes. The existing
  allocator macro remains unverified; three preexisting STLport include
  inventory notes remain. The file is not claimed header-clean.
- Final ordinary preview retains LINKS for this source, 2,620 -> 2,620 bytes,
  and FlightDeckInfoVectorInsertOverflow.cpp, 441 -> 441 bytes, against index
  `85f6b7f40c` (2026-10-29 15:08).

The seven-source outgoing batch audit exits 2, INCONCLUSIVE. Its index
predates outgoing base `3ff66d3dd92a`; two earlier batch source objects lack
current strict receipts, first `AptPlayerStatusDtor.cpp`. The current
PartitionManager source has its strict receipt. Full consumer selection/loss
verification remains unproven. Carry the batch and affected consumers into
the next scheduled census. No census-linking or image-ownership gain is claimed.
