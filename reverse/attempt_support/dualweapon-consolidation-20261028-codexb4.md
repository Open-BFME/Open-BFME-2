# DualWeaponBehavior consolidation, 2026-10-28

Seat: yasinschroeder-codexb4. Inspected base: `4a0da02819`.
Destination: `Code/GameEngine/Source/GameLogic/Object/Behavior/DualWeaponBehavior.cpp`.

The picker claims the destination and two whole-file donors. The scoped
consolidation planner preserves unresolved routing because the committed TU
map is stale; no original BFME 2 path is asserted from donor names. The
supported skeleton rebuilds current assignments in memory and approves 13
rows for this TU, including its destructor, constructor, update, module-data
constructor, pool key, transfer and compiler EH rows. The name getter and
parser remain in two mixed sources. No regenerated TU assignments are committed.

The initial merge accepts no donor: the seed lacks UpdateModule::xfer and
DualWeaponBehavior::getModuleNameKey declarations. The view planner reports
conflicting UpdateModule base clauses, UpdateModuleInterface slot names and
DualWeaponBehavior inheritance. These findings remain explicit prerequisites;
no whole-class reconciliation is claimed.

## Transfer declaration prerequisite

The seed now forward-declares Xfer and declares the existing nonvirtual
UpdateModule::xfer(Xfer*) method. Its signature is the matched transfer
provider/caller contract already used by Common/Rva0045ADC1Xfer.cpp. No fields,
virtual slots, implementations or bindings change. The pool-key interface is
left untouched.

All three originals pass normal byte verification (11 rows); strict receipt
preparation succeeds for all three. After the declaration the seed retains
all seven rows, its floating literal and the EXACT constructor EH graph. The
frozen-file check passes. All 25 external COMDAT byte-and-symbolic-relocation
digests, 25 external definitions and unresolved external names equal the saved
original object. No ledgers, pins, shared headers or source paths change in
this prerequisite.

The ordinary preview index is `d92e7e6635` (2026-10-28 15:58). The destination
is absent from that census and has no ordinary preview verdict; the merge
must use its bounded link guard for the census-linked donors. This is not
proof of destination linking or consumer coverage. Census confirmation and
any measured linking gain remain unclaimed.

Both whole-file donors preview LINKS against that index: transfer retains
75 linked bytes and pool key retains 68. These are baseline predictions,
not census measurements.
