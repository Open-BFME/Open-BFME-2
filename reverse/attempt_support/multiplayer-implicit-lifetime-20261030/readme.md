# MultiplayerSettings implicit virtual lifetime

Started from published master `2b0dc49029`; BFME 1 verified reference
`1d5131d3f193cdf01a99da66ccd6828639585650`. Model GPT-6.

## Native contract and prerequisite

Constructor `003811D8/159` installs table VA `00C191B8`; slot zero selects
`00381277/28`. The independently rowed SubsystemSlot destructor dispatches
through that slot. The complete `00381293/83` destructor is consequently
virtual despite omitting a derived-vptr restore: ordinary compiler generation
of an implicit destructor reproduces that behavior. The old QAE qualification
and composed-base interpretation are contradicted by these target facts.

The constructor now uses the approved seed's existing complete subsystem
interface header, including its fourteen native virtual slots and empty
MultiplayerSettings init/reset/update overrides. This is donor reconciliation
against an existing shared header, not adoption of the separately registered
data-oriented canonical header. No new private SubsystemInterface definition,
header edit or allow hatch is introduced.

Use the real STL map with declaration-only constructor and tree-destructor
specializations. The implicit map teardown inlines to the native tree call
`0038103F`; the compiler still emits the five-byte map cleanup required by EH
at `0038119D`. Merely deleting the class's explicit destructor declaration while
retaining the private map shell calls the latter in the complete destructor,
which is the wrong call site. The stock template view fixes that distinction.

Private field names align with the seed and verified INI field offsets:
the unknown word at +10 receives 0x2710; the countdown field at +14 is zeroed.
Their physical addresses and the constructor's bytes are unchanged.

## Verification and remaining work

Private whole-body probes reproduce constructor 159, implicit UAE destructor
83 and UAE deleting destructor 28 with every call resolved and no masking.
Both EH-bearing parents are EXACT. The emitted primary table is 56 bytes;
its fourteen slot operations match retail. Slot zero uses the compiler's
ordinary vector-deleting/scalar-deleting weak relationship, not a manual alias.
The full shared header's existing leaf methods reproduce their native slots.

The applied constructor prerequisite passes strict normal preparation, frozen
definition checks and ordinary preview LINKS, 0 -> 159 authored bytes against
index `12b9e7a7c0` (2026-10-30 10:11). This is a bounded preview, not a census
or full-consumer claim. No other matched source or ledger has changed yet.

All three parent RVAs are approved for
`Code/GameEngine/Source/Common/MultiplayerSettings.cpp`. The supported planner
was read; regenerate its snapshot after this source edit before using it for
composition. Perform any merge through `tu_skeleton.py`, and audit all changed
path consumers before publication.

Correct the old real-name QAE admissions through separately reviewable withdrawal
and normal readmission, rather than a fabricated naming basis or symbol alias.
Preserve the entire destructor companion set: `0077F308/8`, `0077F310/11`,
`0077F31B/11`, `0077F326/10`. Bind new cleanup labels to their verified UAE
parent graph; no parent or placement is inferred from adjacency. The merge tool
supports companions following their approved same-file parent. Restore all
withdrawn coverage before publishing the batch.
