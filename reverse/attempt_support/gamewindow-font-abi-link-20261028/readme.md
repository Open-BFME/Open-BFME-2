# GameWindow font ABI and native table boundary

Inspected revision: 8ce068f96d72eb8d157ec3866dc3abf0eda53710. Model: GPT-6.

Native GameWindow table VA C0BBCC contains exactly eleven slots (44 bytes).
C0BBF8 begins the independently rowed input-route table: its constructor31454D
and destructor3148E6 both select that address. It starts with deleting
destructor3149EA, then link31455E and unlink314581. Thus those words are not
a twelfth GameWindow slot. The font dispatcher313D73 is absent from the
complete eleven-slot table; all recovered font callers explicitly qualify
the GameWindow call. EA's older GameWindow header declares the font method
virtual, which is donor evidence rather than the BFME 2 target ABI.

## Repair

The existing named method winSetFont is nonvirtual in the two table emitters,
two other private callers and the project-owned gamewindow shim. The combo
font TU selects that already-used project shim instead of the older donor
GameWindow header. Its body and the other callers are unchanged. The old UAE
row is tombstoned; add_match normally admits the same complete121-byte
function under its correct QAE signature, without a pin or object-symbol.
This is ABI correction of the same named function, not a name recovery.

Both table emitters also bind the already-rowed GameWindow::input and
GameWindow::tooltip in native slots1 and4 instead of purecall. The existing
provider is W3DGadgetWindowDrawSlots.cpp; it is verified jointly, not edited.
No source path, compiler optimization, global, data row or hatch register changes.

## Verification

Normal add_match passes all56 main-TU rows. The six direct units pass106/106;
with the unchanged existing callback provider, all156/156 rows pass, including
209 literal references. Both emitted tables now have44 bytes and the correct
slot1/4 symbol references. Frozen-file preflight passes for all six direct units.
Header reach is bounded to66 ledger sources by the normal header_dependents
tool; the normal commit hook must verify that complete reach before landing.

The before-preview already links all six direct units, retaining13351 authored
nonpadding bytes against index73061d9452 (2026-10-27 14:34). Its printed historical
13102-to-13351 comparison predates this repair and is not a gain. The joint
after-preview includes the unchanged callback provider:7/7 LINKS with14418
authored bytes, preserving the six-source13351-byte scope. No incremental
census-linked bytes, unique matched bytes or image ownership gain is claimed.

## Remaining boundary

This repairs table width, the font-call ABI and two existing callback bindings;
it does not recover the complete native data object. Slots2,6,8,9,10 remain
modeled pure despite native non-pure targets. Slot7 is genuinely pure. The
remaining native targets are recorded in table-proof.json. Keep their identity and
class-contract work separate; a clean ordinary preview is not retail vtable
byte verification or whole-image closure. The existing indexed loss audit also
lacks complete consumer metadata, so whole-batch closure requires a current
census. No full link cycle or nightly/smoke runner was launched.

The official BFME1 upstream was fetched at2eb9ecaeead6c05e79d5306ea95bae227e4fe794.
The checkout and committed pointer stay at the verified E744 input. The earlier
native old/new control recorded DIR32 failures; latest upstream is unqualified,
not a new passed comparison. No freshness success stamp was written.
