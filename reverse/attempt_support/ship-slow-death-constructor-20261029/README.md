# ShipSlowDeathBehavior constructor composition prerequisite

Inspected 2026-10-29 at `5eb27ead8e99f0e6bd5016e961176ba6ec7f6208`.
The default picker claimed the TU and its remaining complete constructor donor.
The Behavior naming planner reports two files, nine rows, compiler-context and
placement checks, and path-keyed data-ledger entries. The supported merge
rebuilds the stale TU map in memory: 11 approved rows, two mixed sources left
apart, and the constructor rejected with C2511. Earlier handoffs only tested
composition; this pass tested a real shared-view constructor.

## Target evidence and trials

Retail 0x0045E9AA..0x0045E9F4 is 74 bytes, RET 8. It calls the existing
SlowDeathBehavior constructor at 0x0045D4B4, installs five tables at object
+0/+0C/+10/+20/+24, and zeroes floats +50/+54/+58. The existing shared view
already has this multiple-inheritance layout and these float members.

The trial adds the two constructor declarations to that view and replaces
five dummy table stores with the compiler's normal constructor stores.
ModuleData must be declared as a class, not a struct: its existing struct
spelling produces PBUModuleData instead of the ledger's PBVModuleData.
With that correction, both units retain all nine exact function rows, two
string references, three float literals and the parent-owned funclet.

The initial shared-view trial synthesizes a wrong UpdateModule destructor
and leaves BehaviorModuleInterface::slot0 unresolved. Declaring the existing
base and derived destructors removes the wrong destructor emission but leaves
two unresolved references: ShipSlowDeathBehavior::~ShipSlowDeathBehavior and
BehaviorModuleInterface::slot0. The final trial and receipts are stored in
[shared-view.patch](shared-view.patch), [byte-check.txt](byte-check.txt), and
[link-preview.txt](link-preview.txt).

Ordinary link preview against index `85f6b7f40c` (2026-10-29 15:08) changes the
constructor from 74 to zero authored linked bytes while the TU retains 833.
The index predates the inspected revision; this is a bounded preview, not a
census result. The original sources were restored, recompiled (9/9 exact),
and rechecked: both preview LINKS, 907 -> 907 bytes. The frozen-file check
passes. No Code, ledger, map, debt, queue or source-path change remains.

## Remaining prerequisite

Do not retry a text-only merge or land the byte-exact patch by itself.
The native destructor at 0x0045EA3F and deleting destructor at 0x0045ED2F
remain owned by Rva0045EA3F in Common/Rva0045D39EDerived.cpp; their base
0x0045D39E is Rva0045D39E in Common/Rva0024A797Grandchildren.cpp. Reconcile
these existing identities and complete the native virtual interfaces as a
provider cohort before moving the constructor.

The primary retail table at VA 0x00C423FC contains 13 slots. The shared view
only declares the accessed prefix, so resolving the two reported symbols
alone would not prove the emitted table correct. The secondary tables are
0x00C42DA8, 0x00C423F0, 0x00C42030 and 0x00C423E0; their slot contracts also
need target verification. Existing placeholder names are owner facts, not
proof of the original method names. No donor path or naming inference is
used as target placement evidence.

No file reduction, debt retirement, linking gain or census clearance is claimed.
