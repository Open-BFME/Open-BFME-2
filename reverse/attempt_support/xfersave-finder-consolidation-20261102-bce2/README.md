# XferSave finder consolidated after the shared fold became available

Base: `0b27baa36db`. The preceding cleanup restores STLport's primary string
destructor; this merge uses `tu_skeleton.py --merge` with normal claims, the
current in-memory TU map, byte verification and the source-move link guard.
It absorbs only `Code/Libraries/Source/WWVegas/WWLib/Rva0060D269.cpp` into
`Code/GameEngine/Source/Common/System/XferSave.cpp`: one fewer source file.
All three function/EH rows and the existing pair-destructor fold-proof path
move together. Only those three source cells change in the committed TU map;
no regenerated assignment/evidence map is committed. No name or address changes.

## Verification

Control seed/finder: 22/22. Final merged TU: 22/22, strict current receipts,
three EXACT EH graphs, no newly unmatched definition. Pin consistency passes;
the existing pair destructor remains the native 14-byte fold at 7FAB3.
Ordinary preview against the 2026-11-02 08:35 index at 984a4cdc4d reports
LINKS and 1,294 authored bytes in the merged owner (1,156 seed + 138 finder).
This is preserved coverage, not 138 newly linked census bytes.

The pre-merge objects have 159 and eight external COMDATs; the result has
162 unique names. 159 retained copies have identical byte/relocation digests;
no name disappears and no new name is emitted. Three unrowed list helpers
(insert, resize and size constructor) grow seven bytes each: the existing
donor force-inline base destructor replaces an outlined call with a null
check/free of the same first string field. Disassembly is retained. The
bounded index overlay keeps their owner XferSave before/after, with no retail
verdict; this is not a claim that those unrowed copies are byte-exact retail.
The ordinary source-move guard accepts the resulting provider selection.
Complete current-object consumer closure still needs the outgoing batch audit
and the next scheduled census; see the audit receipt and update below.

## Register and tooling path audit

Audited the complete outgoing source-path batch: the one finder absorption.
The donor/seed have no entries in the code/data-identity registers, data
ledger/rows, header/ms-header queues, hatch baseline, flag override register
or body-owner registry. The owning merge tool refreshes header/ms-header
queues; it changes no register key or compiler-flag override. There is no
registered debt retirement and no hatch growth. The tool repoints the three
function rows, three existing TU-map source cells and sole fold-proof pin.

A combined search covers tools, hooks, workflows, all Code source/includes,
root build/configuration files, docs and reverse registries. No active tool,
source include, glob or build configuration consumes the deleted path. Its
remaining references are historical attempt/re_log evidence, the prior
census link_status row, and the merged source's provenance comment. They are
retained honestly, not repointed as current evidence. No consumer update is
needed. Original EA path evidence remains unchanged.

## Remaining prerequisites

Seven clean donors remain rejected: constructor template duplication, writer
allocator specialization, block-writer class interface, open-writer template
and canonical Xfer adoption, deleting-destructor bytes, bucket-helper bytes,
and deque provider selection. Six mixed files and the vendored/SDK-refused
fragment are untouched. The constructor's actual element-identity and owner
rename cascade remains open. No further donor work is included in this batch.

## Outgoing audit limitation

After refreshing the three directly affected consumer/provider objects
(30/30 rows, strict receipts), the batch audit remains INCONCLUSIVE. The
published index 984a4cdc4d predates base 0b27baa36db, and affected consumer
`Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a current
receipt. Carry the merged XferSave, retired finder, three refreshed consumers
and this affected-consumer closure into the next scheduled census. This
batch claims one source file removed, no census/ownership/new-C++ gain and
no full consumer-closure result. The separate source-move guard and ordinary
merged preview pass; neither substitutes for the missing census scope.
