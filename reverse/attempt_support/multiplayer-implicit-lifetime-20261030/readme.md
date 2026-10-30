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
withdrawn coverage before publishing the separate lifetime-correction batch.

## Supported constructor composition

After the separately committed prerequisite, regenerate and recheck the
consolidation snapshot. The supported dry run and actual merge accept only the
seed and constructor donor. All sixteen existing rows and the seed's data row
verify, four owned EH graphs are EXACT, and frozen-definition preflight passes.
The constructor file is absorbed and its one approved row repointed by the tool;
the TU-map edit is only that source-column repoint, not a regenerated map.
The tool refreshes the destination's header and Microsoft-header queues; neither
requires a staged queue change. No relevant identity or data debt keys name the
constructor donor. The seed's four existing optimization hatches stay unchanged.
An unrelated stale RTS marker removed by the global counter refresh is retained,
so this batch claims no unrelated debt retirement.

The actual merged object also emits all three native lifetime bodies exactly,
fully resolved, and both parent EH graphs remain EXACT. Its deleting-destructor
weak pair is the compiler-generated `??_E...UAE -> ??_G...UAE` relationship.
The UAE destructor graph independently binds `$L7591/$L7592/$L7593` to
`0077F308/0077F310/0077F31B` in this object; rederive those associations after
any relevant compile rather than relying on the label numbers.

Other donors are retained: the STLport-family sources and color pair have
template/allocator composition errors; the old destructor view redefines the
subsystem interface and has the incorrect lifetime qualification; the standalone
deleting wrapper also fails composition. The name lookup donor's merge changes
a selected tree-iterator increment copy and is refused by the link guard.
Three mixed files remain intact. These are separate prerequisites, not a claim
that the whole retail TU has been recovered. The ready constructor move publishes
after its own complete path-consumer audit. The lifetime correction then follows
as a separate batch that restores all withdrawn coverage before publication.

## Constructor-move publication audit

The outgoing path set is the constructor donor absorbed into the approved seed;
no other source path moves in this batch. Combined case-insensitive path and
basename searches cover tools, hooks, workflows, Code includes, shared shims,
build/configuration files, documentation and reverse registries. No active ledger,
register, queue or fold proof still names the removed source. The source's
`from` marker, prior obstacle reports, attempt evidence and measured census row
are intentional history, preserved. The checklist links this historical census
source to its current owner.

The one active tooling consumer was a live name-dependent regression test. It now
derives the constructor's source from the ledger instead of silently skipping
after a path move. That actual regression passes: normal bytes verify, and
removing the called base-constructor identity still fails verification.
The source's stale ownership comment is corrected too.

Strict preparation covers 404 rows and three data rows in the seed, native map,
tree cleanup, subsystem provider and direct INI caller. All five preview LINKS
for 23,244 authored bytes, and 187 EH graphs are EXACT. The seed contains 746
authored bytes; only the constructor's 159-byte improvement belongs to this
repair, not the printed historical 296-byte difference. The other 137 bytes
were already present in the current seed before this batch.

The shadow AsciiString clear-binding finding in the pre-existing color
constructor remains separate. An independently compiled pre-merge source has
identical caller bytes and symbolic relocations; neither object defines that
external clear helper. No new provider is introduced for it and no retirement is
claimed. [Control](inherited-binding-control.json).
[Actual object probes](actual-lifetime-probes.json) record strict receipt/hash,
all three native lifetime bodies, their exact EH graphs and parent-bound cleanup
locations. The unrowed lifetime probes are explicitly distinguished from ledger
admissions. No new pin, alias, header, hatch or canonical-header adoption occurs.

The batch audit initially lacks current GameEngineInit and coord2d consumers.
Their explicit strict preparation passes another 154 rows and one data row,
including 111 literals, five empty references, twelve floats and nine imports.
The combined seven prepared sources therefore cover 558 rows and four data
rows. The repeated audit remains **INCONCLUSIVE** on the older index and the
broader affected `Common/0CreateAHeroManager21FE49.cpp` consumer without a
current receipt. Carry the complete moved-provider/consumer scope into the next
scheduled census; this is not a clean full-image loss or selection verdict.

## Reviewable lifetime withdrawal

The constructor prerequisite and supported move are accepted at `33564ef244`.
The following separate batch withdraws the two incorrect QAE lifetime rows and
their four compiler companions with tombstones: six rows, 151 bytes in total.
The two obsolete source views contain no other row or external wrapper consumer
and are removed. No pin or protected-register key names either view. Stale
unmerged-lifetime comments in the approved seed are removed; executable C++ is
unchanged. All sixteen retained rows and the data row verify and frozen-source
preflight passes. The actual correct virtual lifetimes are already emitted
byte-exactly by the approved seed; restore their complete parent-derived cleanup
set through normal admission before publishing this temporary withdrawal.
