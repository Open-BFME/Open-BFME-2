# ShareExperienceBehavior canonical module hierarchy

Base: `9b63406115`. The default picker claimed `class:Module`; the edited
file scope is also claimed. The registered headers supply the existing
primary fields: Module data at +4 and ObjectModule owner at +8. The old local
`Module` contained both fields. This unit now derives ShareExperienceBehavior
from ObjectModule, includes both canonical headers, and explicitly casts the
inherited opaque module-data pointer to its existing partial data view.
No shared header or new donor implementation is involved. The remaining
secondary interface views are partial; no complete class layout is claimed.

## Verification

- Normal builds pass all 15 function rows, both literals and three floating
  constants. All three EH graphs are EXACT. The frozen-file scan passes.
- Strict `link_check.py --prepare-current` verifies 15/15 with reusable
  receipts. Ordinary preview retains LINKS and 840 authored bytes against
  index `12b9e7a7c0` (2026-10-30 10:11). This predicts preserved coverage;
  no census-linked gain is claimed.
- All 48 external COMDAT name/digest/size fingerprints, 89 external symbol
  records, and complete relocation roots/edges are identical before/after.
  The digest comparison includes relocation identity. No new provider or
  vftable is emitted and no pin, data row, identity or source path changes.
- `header_adopt_lane.py accept --class Module` passes and retires its one
  `reverse/header_queue.tsv` row through the owning tool.

The original bird-state candidate's prior protected-access blocker was read
and not retried. Its unrelated state cannot call Module's protected data
query; this unit can access inherited data as a member. Other Module queue
items and ShareExperience constructor/secondary-interface reconciliation
remain separate prerequisites.

## Outgoing source-path audit after rebase

The complete pending path-change batch was re-audited after rebasing onto
`be3a127ff1`: the two absorbed donors are PropagandaTowerBehaviorXfer.cpp
and stlport_vector_bfmeassignrecord32_erase.cpp. The search covered full paths,
basenames and the repository's active tooling, hooks, workflows, Code includes,
configuration, registries and docs. No active consumer still names either
removed source. Sixteen remaining hits are composition provenance comments,
historical census link_status rows and historical attempt evidence. Their
original spellings are retained. Core ledger/map repointing remains with the
original merge commits. The Microsoft-header queue rebase conflict retained
both upstream's unrelated W3DTankDraw entry and the refreshed FXShaderRenderer
entry; no debt was silently removed. Full verification and outgoing
link-audit limits are recorded below.

Scratch evidence: `build/share-experience-module-20261030-codexb5/` contains
the original source/object, object comparison, path-consumer search and logs.

## Consumer-audit limit

The scoped staged-tree audit exits 2, INCONCLUSIVE: index `12b9e7a7c0`
predates the base and affected consumer
`Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a current
receipt. Full affected-consumer selection/loss checks and census confirmation
remain pending. Carry this primary hierarchy and its affected consumers into
the next scheduled census. The ordinary 840-byte preview and identical object
facts do not replace that wider verification. The normal publication hook
retains its outgoing-batch verdict.

## Full gate after rebase

`./build.sh` exits 0: FULL GATE OK, every check green. It recompiles 652
translation units and verifies 99,014/99,014 function rows across 20,183 source
files, 31,537 literals plus 2,247 empty-string references, 9,116 floating
literals, 6,425 named imports, DIR32 identities, pin consistency, the module
registry, source claims, all 2,246 data rows and the no-op patch. This full
gate also covers the retained Microsoft-header queue conflict resolution
and the complete pending batch at this checkout.

## Publication rebase follow-up

The first commit passed its normal hook, then runner publication rebased the
batch onto `9aaf6f9384`. The refreshed FXShaderRenderer Microsoft-header queue
entry conflicted with upstream's newly appended XferSaveAsText entry. Both
entries were retained, alongside the earlier W3DTankDraw entry. No queue key
was retired by that resolution. `check_csv.py` passes with 99,014 function
rows, 9,393 symbols and 2,246 data rows. AGENTS.md did not change.

The source-path consumer audit was repeated immediately before publication
on the rebased batch. Its 18 hits are the previous 16 provenance/history
references plus two references in this handoff; none is an active consumer.
No tooling compatibility change is required.

The new `./build.sh` full gate exits 0: every check green, 99,014/99,014
function rows across 20,175 source files, all 2,246 data rows, all reference
and structural checks, and the no-op patch. The eight-file source-count
reduction between full gates belongs to upstream consolidation. This run
covers the second queue-conflict resolution and the whole rebased batch.
Its log is `build/share-experience-module-20261030-codexb5/full-gate-rebased.log`.

The next publication attempt met another queue append conflict when rebasing
onto `4d6c1d7693`. The GlobalLanguage entry and all earlier entries are
retained. The refreshed FXShaderRenderer row is restored to its original
position before W3DTaint, avoiding repeated conflicts at the append point;
its fields are unchanged. The ledger check passes, and the final path audit
has the same 18 provenance/history hits (census row numbers changed).
AGENTS.md is unchanged. The two full gates above remain evidence for their
stated bases; the normal runner publication hook owns verification of this
final rebased batch before landing. No extra final-base full-gate or
consumer-audit pass is claimed.
