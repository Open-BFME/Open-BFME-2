# SupplyWarehouseDockUpdate native seed reconciliation

Base: `1a7b67c6a1c596257f61f76fed7dd6b1e7b2741a`. Seat: halilkkaya-codex.
No pushes or maintainer-only measurement runners.

## Target facts

Retail constructor 004A7DEA calls DockUpdate 0058A290 and installs
00853790/+0, 00851B20/+0C, 00851D68/+10 and 00853740/+20.
It copies ModuleData+10 to the boxes field +88. Factory allocation is 8C.
Destructor 004A7D55 restores the same four tables. The primary table has
13 entries, the behavior interface 47, update interface 3 and dock
interface 20. Slot 0 is deleting destructor 004A7E27. The name table
entry is 004A7D75; slot 4 is the existing key body 004A7DA5.

`rename.py class --fold Rva004A7D55 --into SupplyWarehouseDockUpdate`
proves the class identity from the constructor/destructor table stores,
the table's recorded real class name and its deleting destructor. This
is target evidence; no donor name inference is needed for this fold.
Five function rows and their callers are respelled together, and the old
rows are tombstoned by the tool. The script caller stays in its own TU.

## Donor facts and remaining structural work

The ZH header supplies the docking interface vocabulary. Its snapshot
CRC slot, destructor access, module-data layout and several callees do
not describe BFME 2. Native slot ownership must be reconciled before
replacing that include chain. No pure slot may replace a concrete native
entry. The action body receives the +20 dock interface; its +68 count is
the owner's +88 boxes field. Its current independent placeholder owner
and the name/key getter spellings remain prerequisites.

The approved in-memory TU plan has six eligible files, three mixed files
and 15 approved rows. The mixed destructor/name/parser owners stay out
of a mechanical merge. The catalogue was generated with
`name_lane.py consolidate --under Code/GameEngine/Source/GameLogic/Object/Update/DockUpdate/`.

## Verification

After all six earlier purecall commits appeared on origin/master, rebase
completed and worktree_setup prepare selected reference pin
131fb8ff0a515c504313ac10ec87c929d71cf214. Incremental full build passed
99277/99277 functions and all gates.

Before repair, the seed is 0/217 linking bytes with seven unresolved
names and two COMDAT losers. Six inspected donor units retain 730 B.
The fold byte gate passes 13/13 rows across all five changed source files,
and find_declared_unmatched is clean. The same five objects preview
LINKS, 517 -> 517 B, against index 86db074988 (14:31), whose census
blocker snapshot is 39dfbbdb50 (12:39). These are bounded predictions;
no current whole-image census or runtime result is asserted.

Local raw receipts: build/link_seed_pass/incremental-build.log,
warehouse-before-link.log, warehouse-fold-apply.log, fold-link.log.

## Native-view xfer adoption

The TU-scoped native header records the four target interfaces and +88
boxes field. It declares concrete derived overrides for all native
entries; getter/action provider reconciliation is still pending. Only the
xfer donor adopts it at this step, so no new vftable emitter is asserted.
Its complete 42-byte row stays exact and its ordinary preview retains
42 -> 42 B. Frozen declaration check is clean. No header-queue key owns
this source. Scratch trials and receipts use build/link_seed_pass/.

## Native key-slot owner

004A7DA5 is reconciled from the static rva004A7DA5 placeholder to
`SupplyWarehouseDockUpdate::getModuleNameKey() const`. The existing
canonical Module contract and Object::findModule's slot-10 dispatch fix
this already-named virtual; the warehouse table itself points directly to
this body. Its static local caches the class literal. This is an ABI/owner
correction; identifier-only rename.py cannot express static-to-virtual.
The function and its EH handler are tombstoned and both EH rows' parent
identity is carried. All 3/3 rows remain exact; the EH graph is EXACT.
The source adopts canonical NameKeyGenerator with the native warehouse
header; no private generator view or new pin/alias remains. Its ordinary
preview retains 79 -> 79 B and the seed remains blocked at this step.
The generated data_ledger's two local-static symbol descriptions remain
stale until its supported regeneration; their addresses are unchanged.

The key correction is coupled with a narrow declaration-only change in
the seed macro. The initial strong definition collided with the seed's
existing inline copy; making the new definition inline alone failed to
emit it. The final pair keeps the real out-of-line provider and removes
only the seed's competing key body/static guard. Both constructors and
setDockCrippled remain exact: paired byte gate 6/6, key LINKS 79 -> 79 B,
seed unchanged U7/L2 and 0 -> 0 B. No rejected inline-only trial remains.

## Created-slot donor

004A7E43 adopts the native header and canonical Thing getter. Its slot-5
identity binds the existing Module::onObjectCreated contract. The old row
is tombstoned. The seed's competing unrowed body is removed in the same
change; no outside consumer requires that copy. Paired byte check 4/4
and frozen checks pass; the real 36-byte provider previews LINKS again.
The standalone preview uses the old census seed and reports an expected
duplicate; the paired current preview removes it. Include all changed
providers together for subsequent previews, especially the renamed key.
One present-unmatched counter can tighten in the separate hatch commit.

## Snapshot-name owner

The six-byte literal getter at 004A7D75 now belongs to the warehouse
class with Snapshot's protected virtual GetSnapshotName profile. The
returned module literal and ctor-owned table slot 2 establish its owner
and inherited contract. The mixed getter TU stays in place; only one
macro invocation changes, with the old row tombstoned. All its rows and
its existing linking bytes remain verified. No alias or new body is added.

## Dock callback owner

00589722 is reconciled to DockUpdate::onDockReached using slot 10 of
the ctor-owned +20 docking interface. Its two-object condition-82/83
transition and the existing docking declaration agree. The native header
replaces the fabricated primary/interface classes; the body stays the
same. All three mixed-source rows pass, frozen checks are clean and the
unit retains 290 -> 290 predicted linking bytes. The old row is tombstoned.
The name-getter verdict's 90-row typo is also explicitly retracted with
re_log.py and replaced by its actual 101/101, 605-byte receipt.
