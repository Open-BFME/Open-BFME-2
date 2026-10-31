# AptScriptColour: reconcile the GC declarations, then absorb the clean donor

Base `2f86780fee`; selected by `next_work.py --claim --json` after the
normal ledger check. Both file scopes were reserved before editing.
Qwen and other local inference models were not started.

## Prior blocker and the prerequisite repair

The planner was run for `Code/Libraries/Source/Apt/AptObject/` and its
packet reviewed. The approved map is rebuilt in memory when stale; no
regenerated map is committed. Read the earlier log entries and
`consolidation-shard1-20261027.md`: the clean donor
`Code/GameEngine/Source/Common/Rva006F2C50Siblings.cpp` lacked the
`AptObject::DestroyGCPointers` declaration in the seed. The same absent-member
error was reproduced before editing; the three mixed-file splits are not retried.

Native `006F2C23` directly calls the existing `AptObject::RegisterReferences`
forwarder `0070DFD0 -> 006DCC00`; native `006F2C69` tail-jumps to the existing
`AptObject::DestroyGCPointers` forwarder `0070DFE0 -> 006DE150`. These are
qualified calls on the unchanged receiver, not dispatch through the partial
`AptObject` declarations' apparent slot zero. The existing
`AptScriptFunction.h` and `AptFactoryConstructors.cpp` corroborate both
signatures; neither shared input is edited.

The preceding declaration-repair commit gives both call views identical bodyless
declarations. It does not assert a full class layout or virtual-slot order.
Both 45/30-byte functions, their complete relocations and the two external
code definitions are unchanged. The normal two-source gate, frozen checks,
zero-finding shadow data check and strict preparation pass. No definition,
pin, alias, helper, canonical-header register or baseline is added.

## Supported merge and proof

The supported `tu_skeleton.py --merge ... --dry-run` then accepts the seed
and its one clean donor under `/MD`; LinkGuard protects both census-linked
units. The application uses the same owning tool and removes the donor.
It repoints one `functions.csv` source and one existing `tu_map.csv` source
cell; it does not change a map assignment, confidence or evidence. No data
row or protected-register key moves. One source file is removed.

The final normal build passes 2/2 rows in the merged file, no new unmatched
definitions, and strict preparation. Both external code definitions are
byte-and-relocation identical to the union of the original two objects;
none is removed or added. This also preserves the member at +20, Release
through +4, mark dispatch through +34, the existing getter and setter, and
the two qualified base forwarders. These two functions have no EH graphs.

The bounded preview at `3c7a254a38` (2026-10-31 13:43) reports LINKS/75 bytes
for the merged file versus its old 45. The other 30 already belonged to the
linked donor, so the cohort conserves 75 -> 75 bytes. This is a source-file
reduction, not new matched or census-linked coverage. Broader outgoing
consumer/selection verification and the scheduled census remain separate.

## Path consumers and remaining work

The active path-consumer search across tracked files finds no tool, hook,
workflow, include or build/config dependency on the removed basename/path.
The owning tool updates the core source columns. Remaining old-path mentions
are its provenance comment in the merged source, the committed census
`reverse/link_status.csv`, historical attempt log and the earlier handoff.
They are retained honestly; the census and history are not hand-edited.
The publication audit below records its exact range and limitations.

The three mixed donors still remain: `AptFactoryConstructors.cpp` has copied
helper/hatch constraints, `Rva006D6470Derived.cpp` needs selected destructor
and vtable context, and `BfmeConv1082.cpp` needs coherent data ownership for
its split. This merge clears only the previously missing declaration for the
clean donor. It proves neither a full class reconciliation nor runtime success.

Original objects/sources, native disassembly, planner, builds, strict receipts,
merge logs and actual-object comparisons are retained under ignored
`build/continuation-no-qwen-20261031-153050` and the corresponding create-only
diagnostic directory at `W:/OpenBFME/diagnostics/`.

## Prepublication consumer audit

`link_batch_audit.py --base 2f86780fee --tip f28ac70be` with a NUL-delimited
verified-source file reports INCONCLUSIVE, exit 2. Index `3c7a254a38` predates
that outgoing base, and affected consumer
`Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a current
receipt. No proven loss is reported by that incomplete audit; it supplies no
full loss clearance. Carry this consumer and the selected providers of the
moved GC function into the next scheduled census. The publisher's hook will
audit the final outgoing range again after rebase.
