### LINK-114: FireWeaponWhenDeadBehavior primary views omit different native slots
Status: Blocked on complete primary-interface reconciliation. Updated: 2026-10-27; inspected revision: a0b82f68445de8ab0254437ef7e97332ce48cfb0.
Evidence / affected units: `FireWeaponWhenDeadBehavior.cpp` retains L1 while current `Rva00589079Derived.cpp` and `FireWeaponWhenDeadBehaviorPoolKey.cpp` preview LINKS against index `bf3dd31211`. Both primary vptr relocations now name `??_7FireWeaponWhenDeadBehavior@@6BObjectModule@@@` and reach native table 0x008497B4: constructor 0x00482D80 body offset 55 and destructor 0x00482E96 body offset 2. The earlier UpdateModule-versus-ObjectModule naming collision is no longer the current difference. The constructor emits 20 bytes (five slots); the destructor provider emits 16 (four slots). Native has 13 slots, including getModuleNameKey at slot 4 (0x00482E51), four empty hooks at slots 5 through 8, a two-argument return at slot 9, null-return hooks at slots 10 and 11, and getUpdatePhase at slot 12 (0x0022C4CB).

2026-11-03 consolidation: `FireWeaponWhenDeadBehaviorPoolKey.cpp` and the TU's existing source were merged into `FireWeaponWhenDeadBehavior.cpp`; 7/7 matched rows build and byte-verify, and LinkGuard retained the census-linked units. This does not resolve the native vtable-slot mismatch above. Recheck the selected vtable provider and consumers in a new census after additional reconciliation.

2026-11-03 batch audit: `tools/link_batch_audit.py --base origin/master --tip HEAD` was inconclusive (index at `8661f15284`); five source objects lacked current receipts, first `Rva00589079Derived.cpp`. Carry this provider/consumer comparison forward to the next census; no selected-provider conclusion is established by this audit.
Completed: all four constructor-unit rows pass byte verification; current objects and native pointers were checked against the prior 2026-10-23 handoffs. No slot-only trial was repeated and no source change is retained. The existing provider row 0x00482E4B is still spelled `Rva00482E4BGet`, reached through the existing s02 alias; Snapshot-name ownership is a naming lead that must be resolved without adding another alias.
Remaining / next check: reconcile the complete shared primary contract in both existing views, including the real slot owners, while preserving all three derived families in `Rva00589079Derived.cpp`. Adding only the missing pool-key slot would make the two short copies agree without supplying the eight remaining native slots. Recheck the constructor, destructor provider and pool-key unit together after that repair.
Clearance: pending.
Census confirmation: not claimed.

**2026-10-30 primary-table repair (base `190db05cc6c2`):** both existing views now emit the native thirteen-slot primary contract. Removing the constructor's unused BuffManager include prevents its capitalized Snapshot context from creating two extra slots. The destructor view uses the registered ObjectModule header, both views carry the native Behavior slots 10/11 and existing Update phase slot 12, and the six-byte getter is readmitted as the Snapshot member after its own placeholder-retraction commit. The obsolete s02 alias is retired. Independent COFF proofs bind both vptr stores to 0x008497B4, verify every primary slot, and preserve all twelve raw code bodies; only an existing Update xfer twin spelling and FuncInfo label numbering change. Strict fourteen-source preparation passes 429/429 rows and seven EXACT EH graphs, including the other destructor families. All fourteen sources preview LINKS (21,445 authored bytes), with the constructor 0 -> 209 B and no cohort loss. This clears the primary-table disagreement in that current-provider preview; secondary-interface recovery and wider/census confirmation remain separate. ObjectModule queue retirement is still blocked solely by the isolated old-index preview lacking the new getter provider; the queue is retained pending a supported index refresh. No census gain claimed. [Full native proof and scope](../../reverse/attempt_support/fireweapon-primary-link-20261030/readme.md).

**2026-10-31 revalidation (base `fec332c7aaad`):** 436/436 direct-cohort rows,
all twelve original bodies, both thirteen-slot primary tables and seven EH
graphs pass. The newer census index `7300bffea9` exposes a remaining secondary
Update contract: native 0x008496E8 has slots 0x00482BB9 / 0x004DF396 /
0x0044DF8D, while the constructor emits one unresolved generic void update.
Current preview is 13/14 LINKS; constructor stays 0 -> 0, superseding the old
+209 prediction. Reconcile the existing row owners/signatures rather than
restoring that placeholder. The changed-pair batch audit is INCONCLUSIVE at
AIBuildable.cpp; full inventory has 591 consumers and 538 missing current local
receipts. CreateAHeroManager's receipt now passes 24/24. Keep the primary repair
scope separate from secondary recovery and carry wider selection/loss checks
into the scheduled census. No measured gain or full closure is claimed.

**2026-10-31 Update provider follow-up (base `941fe7fcbcfe`):** the existing
0x00482BB9/34 row is separately retracted and readmitted as the actual virtual
FireWeaponWhenDeadBehavior::update returning UpdateSleepTime, at its unchanged
owner path. The constructor emits all three native Update slots, including the
complete 26-byte all-disabled mask override and existing wake member. The opaque
destructor view now overrides the real update slot directly, removing its f2
alias; its two other secondary slots remain unrecovered. Both primary tables
retain all thirteen native slots. Strict direct preparation passes 453/453 rows
across seventeen sources and seven EXACT EH graphs; all seventeen preview LINKS
against 7300bffea9, with the constructor now 0 -> 209 B. No other since-index
growth is credited. The retraction hook additionally verifies 13,162 functions
in 687 source scopes. Wider batch audit and census confirmation remain open;
no measured gain is claimed. [Native proof and remaining scope](../../reverse/attempt_support/fireweapon-update-link-20261031/readme.md).

Publication audit at `22d24b8a3831`: INCONCLUSIVE against the older 7300bffea9
index; AIBuildable.cpp lacks a current local receipt. Direct scope remains
17/17 LINKS with 453/453 rows and seven EXACT EH checks. Carry the changed
provider scope and that consumer into the next scheduled census; the wider
verdict is unverified, not clean.

2026-11-04: onDie now adopts canonical UpgradeMux; 310/310 bytes and its existing LINKS preview are preserved, and accept retires one header row. Merge still blocked; seed UpdateModule adoption now passes a read-only trial but its class is peer-held, with Player adoption and the +0x2C member views still prerequisites. [Current repair and merge handoff](../../reverse/attempt_support/fireweapon-upgrademux-adoption-20261104-codexb5.md).
