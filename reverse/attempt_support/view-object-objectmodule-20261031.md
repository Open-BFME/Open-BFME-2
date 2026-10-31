# Special-power view-object canonical ObjectModule adoption

Base `277f1f4d4e59b1d14bfc48c151ddbd423114aeae`. The initial Xfer and
DeployStyle constructor picks have unchanged documented prerequisites; no
old failed compiler experiment is repeated. Work stays within the separately
claimed SpecialPowerModuleCreateViewObject unit and ObjectModule class scope.

Include the existing `Common/ObjectModule.h` instead of the private class.
Use its inherited `Module::getModuleData` and `ObjectModule::getObject`
at the existing read sites. No shared header, ledger, pin, alias, compiler
setting or static-guard/data-owner name changes. The remaining derived view
is partial: no complete original inheritance/layout or new constructor/vtable
provider is claimed.

## Direct before/after evidence

All four rows pass normal verification, including the complete 358-byte
parent, both parent-owned cleanup actions and its EH handler. The complete
EH graph is EXACT before and after. All ten retained external code bodies
and their relocation names are identical, including the main function and
the data-access wrapper. The only two removed code definitions are the old
ObjectModule-specific `bfme_module_data` and `bfme_object` getters; the two
added definitions are the canonical getters. Each of these old/new getter
definitions has only `.debug$F` incoming references in the checked object.
A narrow source search finds no remaining `bfme_module_data` use; the other
`bfme_object` uses are different drawable views, not this removed const
ObjectModule member. Full affected-consumer selection is separate.

The complete native parent also independently witnesses the canonical storage:
`00493861` reads module data at receiver +4 and `004938FC` reads Object at +8.

The earlier log entry 96262 reports an S1 -> S2 guard-name problem. It is not
reproduced by this source-only variant: both objects keep the identical full
S1 guard and key_DeletionUpdate local names, and all main-body relocations
are identical. Before/after shadow data checks both report zero findings.
No claim is made about the reason the old, differently generated trial failed.
The first local include-path typo is corrected before judging the adoption;
it is a setup failure, not evidence against the header or native body.

Strict one-source preparation succeeds. The owning `header_adopt_lane accept`
passes and retires exactly this one ObjectModule header-queue row. No new
matched bytes are recovered. The original bounded preview retains LINKS/368
authored bytes against published index `3c7a254a38` (2026-10-31 13:43); the
final source and outgoing consumer audit retain their separate currency limits.
Other ObjectModule and Xfer keys remain open.

The prepublication batch audit at base `277f1f4d4e` is INCONCLUSIVE: published
index `3c7a254a38` predates that base and the affected unchanged consumer
`Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a current
receipt. Carry it, the removed getter names and canonical getter selection
into the next scheduled census. A later publisher rebase does not turn this
single-source acceptance into full affected-consumer loss clearance.

Qwen only checked the reported old/new guard evidence, without tools or
editing access, using four CPU threads with CUDA hidden. Its answer correctly
states that the old guard failure is not reproduced and other consumers are
not proved. Host object, row, EH, data, strict and acceptance checks establish
the results; no Qwen-generated source is used. Raw controls and logs are saved
in the create-only `continuation-20261031-1514` run and hashed at handoff.
