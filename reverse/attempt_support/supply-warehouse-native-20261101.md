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
