# _com_error: correct native RTTI table refused by bridge policy

Root recovery seat, 2026-11-09, base 5ec18855f9. The default picker served
Code/Libraries/Source/COM/_com_error.cpp for `unsupported-selection` at
table RVA 008E0B48. The complete file and canonical ComError.h were read.
Normal and strict preparation both pass all nine code rows (2,036 bytes)
and eleven import references. The declared-unmatched check is clean.
No source, flags, header, ledger or verifier was changed.

The compiler emits one eight-byte read-only COMDAT with selection 6
(LARGEST): an RTTI complete-object-locator relocation at offset zero, then
`??_7_com_error@@6B@` at offset four. Its only slot is weak E, with the
compiler record defaulting to the rowed G destructor at native 00654D80.
The ordinary target resolver accepts that owner, and the normal positive
slot predicate returns true. The downloaded index c885072a48 lists only
this object's copy of the table, and the runtime archives add no copy.

Retail independently has the same RTTI-prefixed shape: VA 00CE0B44 points
to locator RVA 008F5020; its signature, offset and construction displacement
are zero, and its type descriptor spells `.?AV_com_error@@`. The table at
00CE0B48 points to the exact 58-byte scalar deleting destructor. The next
dword is zero, outside the one-slot table. This proof establishes the prefix
role and positive slot, not every byte of the entire RTTI graph.

The bounded planner refuses this otherwise correct table before its
already-correct check because it accepts only SELECT_ANY copies. It would
also refuse the prefixed shape for generation; generating a replacement is
unnecessary here. This is recorded as a `false-reject vtable_bridge` lead
for a separate tooling pass. It is distinct from the type_info case, which
has an additional potentially extracted archive copy and an unproven
provider boundary. Do not drop /GR, erase the native RTTI prefix or change
the source merely to satisfy the generated-copy admission rule.

`proof.json` records all nine verified code identities, object hash, current
table/weak records, native locator/type facts, the one indexed copy and the
unaltered planner refusal. A future checker correction must distinguish
already-correct native tables from safe generation, preserve selection and
provider checks, and retain the existing adversarial rejection tests. A
fresh real image is still needed to clear the published queue. No game,
census, byte-coverage or source-cleanup gain is claimed by this investigation.
