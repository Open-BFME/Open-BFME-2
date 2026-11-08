# StrafeAreaUpdate constructor base adoption, 2026-11-08

Inspected base: 4e99290287 plus its publication receipt. Related obstacles:
LINK-514 (dummy/manual installers) and LINK-168 (BehaviorModule interfaces).
The served table is `_vtbl_00C1B164`, a correct 52-byte, 13-slot hand-built
primary table. Its strong-definition bridge refusal is not repaired here.

The constructor now includes canonical Module/UpdateModule.h instead of a
private registered UpdateModule copy. The canonical base has the same proven
0x20-byte extent. Existing explicit primary, +0x0C and +0x10 table writes are
retained through pointer views, with the same table referents and member stores.
The declaration-only destructor, wake call and store scheduling remain exact.

Normal build verifies both owned rows (129-byte constructor and 10-byte EH
handler), the complete 52-byte data row and one EXACT parent exception graph.
The source remains unfrozen. Private verification is 2/2 with no errors;
its one external COMDAT fact is unchanged, no provider is added or removed,
and LinkGuard reports no new obstacle. Strict preparation supplies a reusable
receipt. Preview against eba83a23be (2026-11-08 14:08) remains LINKS/139 bytes.
The supported header_adopt_lane accept command passes and retires exactly
this source's UpdateModule queue row. No pins, data rows, paths or baseline
exceptions change.

The array must remain until the class is reconciled: StrafeAreaUpdate.cpp
contains a canonical-base Rva003A4CAE xfer view and a separate flat
StrafeAreaUpdate getter/helper view. The mixed Rva0024A797Derived.cpp destructor
provider has a short primary table on private bases. Merely binding this
constructor to that table would replace 13 correct slots with a short table.
A direct placeholder-class fold also collides with the existing class
definition. Prepare one complete class and its xfer/name/destructor/secondary
interfaces before replacing the manual table; preserve every other provider
in the mixed destructor TU. No full-link, table retirement or runtime clearance
is claimed by this prerequisite.
