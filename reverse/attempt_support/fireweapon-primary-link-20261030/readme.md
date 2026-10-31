# FireWeaponWhenDeadBehavior primary contract

Base 190db05cc6c213ba433cbfd180b5616fcf00a763; model GPT-6; lane=R;
budget=30m. Both source file claims were origin-confirmed before edits.

The twelve original rows pass in both the original and proposed source pair.
The proposed pair compiles identical thirteen-slot primary tables, checked
slot by slot against native 0x008497B4. Slots 0/1/3/4/12 retain existing
ledger owners; slot 0 uses the compiler's weak E-to-G fallback to the rowed
scalar deleting destructor. Slots 5-11 have complete inline leaf bodies equal
to native, including the two-argument RET8 and the two null getters. Slot 2
is the exact six-byte const member getter at 0x00482E4B. No new pins or aliases
are required. The ObjectModule base header is unchanged.

A stale, unused BuffManager header in the constructor unit selected capitalized
Snapshot slots before its actual base was read. That made loadPostProcess and
xfer extra virtual slots. Removing the unused include permits the existing
name-slot contract; both views then add the known Behavior primary slots 10/11
and existing UpdateModule getUpdatePhase slot 12. The destructor view adopts
the registered ObjectModule header. Its qualified base transfer needs the
existing nonvirtual BehaviorModule xfer spelling at 0x004C9C7D, while the new
base now makes the C++ declaration virtual. A local member-address view uses
that existing symbol with ObjectModule at offset zero. The target compiler
proves both pointer representations four bytes; its emitted call remains
byte- and relocation-identical. No inline assembler or fallback is added.

The existing free-function placeholder Rva00482E4BGet is the same native
slot-2 getter, not a second ICF function. Per add_match's real-claim rule it
must be retracted in its own reviewable commit before readmission with the
actual member signature. The first commit therefore removes that one six-byte
row/body, records its tombstone and removes the old s02 alternatename. The
matching member body and full interface repair are retained in scratch for
the following readmission commit. This intermediate retraction is not published
on its own. No original-source naming claim is derived from a trivial byte
match alone: the module constructor's primary vptr and native Snapshot slot
contract establish the containing class and callable interface.

The tested three-source preview is 3/3 LINKS, retaining the other two units
and changing the constructor from 0 to 209 authored preview bytes against
85f6b7f40c. This is a bounded prediction, not measured census credit. Other
secondary interfaces and the wider affected-consumer scope still require
normal audit and scheduled census confirmation. The other destructor families
must retain all existing row bytes and bindings.

## Member readmission and direct consumer verification

The required retraction is commit bad62c3aec. The following source stage
readmits exactly 0x00482E4B/6 under
`?GetSnapshotName@FireWeaponWhenDeadBehavior@@UBEPBDXZ` with add_match, not an
ICF alias. Total unique coverage is unchanged. Its normal source gate passes
4/4 rows, one string, one floating-point reference and the constructor's
parent-verified cleanup. Implementation time t=18 minutes, model=GPT-6,
lane=R, budget=30m; subsequent cohort verification and publication are separate.

The independent row proof preserves all twelve original raw bodies. It records
only the existing QAE-to-UAE UpdateModule xfer spelling at 0x0044DF9F and the
local FuncInfo label renumbering; the BehaviorModule call remains the original
QAE relocation. Seven EH graphs in the fourteen-source cohort are EXACT.
Strict preparation passes 429/429 rows, 314 literals, one empty-string reference
and one floating-point reference. The cohort includes both other destructor
families and their class-view users, the factory, Fire onDie/factory/pool-key
consumers and the changed pair. All fourteen ordinary previews LINKS, retaining
every previously linking unit and 21,445 authored bytes. Of changes from that
older census, only the constructor's 0 -> 209-byte prediction is this repair;
other growth since the census is unrelated and is not credited to this work.
No new measured census-linked bytes are claimed.

The optional ObjectModule queue retirement is still refused by its single-unit
preview: the old index lacks the newly named getter defined in the current
constructor unit. That isolated preview reports only this one unresolved name
and 311 -> 0 bytes; including the actual provider gives 311 -> 311. The queue
row is retained. A supported local provider-index refresh is the next check
before retrying retirement; no check, baseline or whitelist is relaxed. Wider
consumer selection and scheduled census confirmation remain pending.


## 2026-10-31 publication revalidation

The maintainer approved the explicit rebase and preservation of independent
document entries. The batch is rebased onto `fec332c7aaad`; both documents
retain all upstream entries. The two source files and their three base headers
are unchanged upstream; three direct consumers gained additional rows.
The current fourteen-source preparation passes 436/436 functions, 314 literals,
one empty-string reference and ten floating-point references. The required
ordinary build of the changed pair passes 12/12; the independent native primary
table and original-row proofs pass again, as do all seven EH graphs.

The newly published index at `7300bffea9` changes the earlier prediction:
**13/14 direct sources link; the constructor remains 0 -> 0**, with unresolved
`?update@UpdateModuleInterface@@UAEXXZ`. The earlier +209-byte prediction is
historical evidence against the older index, not a current gain. Native
0x008496E8 has three Update interface slots: 0x00482BB9, 0x004DF396 and
0x0044DF8D. The constructor currently emits only one slot under
`??_7FireWeaponWhenDeadBehavior@@6BUpdateModule@@@`. The existing row owners are
`Rva00482BB9::update` (34 bytes, currently nonvirtual int signature),
`Rva004DF396::getDisabledTypesToProcess` (26 bytes, all-disabled mask), and
`UpdateModule::rva0044DF8D` (18 bytes). Reconcile these actual owners and ABIs;
do not restore the removed generic update placeholder or add a pin. This is the
remaining secondary-contract prerequisite, separate from the verified primary
contract. No new secondary-interface source reconstruction was landed here.

The current batch audit is INCONCLUSIVE on AIBuildable.cpp's missing local
receipt. Its prior CreateAHeroManager missing receipt was repaired through the
supported preparation path, passing 24/24 rows. An inventory of the actual
two-source outgoing scope identifies 591 affected consumers, 538 without current
local receipts. This is not a complete consumer/loss verdict. Carry the changed
provider scope and that inventory into the next scheduled census. No broad
index refresh, census, nightly run or smoke run is started. The earlier broad
index refresh was interrupted and has no success receipt.

The official BFME-1 upstream check found `8a762b77f34e`, newer than the committed
verified pin `7a8a034afa7d`. Keep the committed pin for this bounded repair;
no successful freshness/update receipt is recorded for the newer unverified
revision. Full reference-update verification remains separate.

`rebased-verification.json` records real exit codes. This repair retires one
obsolete alias and fixes the primary table, but claims zero new unique matched
bytes and zero measured census-linked bytes. The ObjectModule queue stays open.
