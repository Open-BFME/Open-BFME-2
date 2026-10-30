# XferSave private-view consolidation prerequisites

Base: `758c0e2412`. Claimed scope: the seed
`Code/GameEngine/Source/Common/System/XferSave.cpp` and its six clean donors.
BFME 1's verified freshness stamp was under 72 hours old at selection.

The picker selected this approved TU. The naming planner's original-path and
structural packet was read before editing; its routing/compiler/declaration
warnings are investigation leads, not approval. `tu_skeleton.py --merge
--dry-run` rebuilt its map in memory and found 55 approved rows, nine mixed
sources and one refused vendored source. It accepted no donor. No map, row,
pin, source path or register key is changed here.

## Retained cleanup

`tu_views.py` now gives the seed and the name writer identical exception and
stream declarations. The table helper no longer carries unused ModuleData,
stream, exception or XferSave declarations. The block writer loses its unused
iterator, finder and insertion-helper views.

The seed, name writer and table helper share the same 16-byte private finder
view: the seed compiler layout's integer at +0 and bucket view at +4. The
helpers receive the complete existing bucket definition before this member
can be stored by value. This is agreement between reconstruction views, not
proof of a recovered retail class name or a complete hash_map layout.

The finder retains the helpers' existing `throw()` call contract. A first
tool plan supplied only an incomplete bucket declaration and was restored
after C2079. Supplying its definition allowed compilation, but dropping
`throw()` changed caller/EH code and three rows failed; the tool restored that
plan too. Adding `throw()` to the seed declaration and definition preserves
its 15 rows and lets the final shared view verify. No changed function body
from either rejected trial remains.

Removing the block writer's node view also removed its string `npos` COMDAT.
That view is retained, with a comment, to preserve the existing data provider.
Its other unused table views can be removed independently.

## Verification

- The seven-source cohort passes `./build.sh`: 28/28 rows, including funclets
  verified through their parents' EH data after local-label renumbering.
  The final node-view retention also passes the block writer's own build.
- `link_check.py --prepare-current` prepares the four explicit edited
  providers and byte-verifies all 22 of their rows with strict reusable
  receipts. The object comparisons below also pass after this preparation.
- A refreshed final consolidation snapshot passes its input/output currency
  check. It still reports an investigation group, not an approved merge.
- `find_declared_unmatched.py` passes the edited files. The seed's existing
  unclaimed-definition note remains; no new marker or exemption was added.
- `eh_verify.py`: four EXACT EH graphs, no missing objects or baseline cases.
- Enforced converged-data check: four sources, eleven addresses, no second
  names or unjudged rows. `check_csv.py` passes.
- Saved pre-edit objects versus final objects have identical COMDAT
  name/digest/size triples, external name/definition/storage/value records,
  relocation roots and dependency edge sets:

| Source (short name) | COMDATs | External records | Roots | Edge sets |
| --- | ---: | ---: | ---: | ---: |
| System/XferSave.cpp | 61 | 80 | 16 | 53 |
| System/rva0060D2E9Rva0060D2E9Farm.cpp | 26 | 40 | 12 | 25 |
| WWLib/Rva0060D269.cpp | 8 | 15 | 8 | 7 |
| xfer/XferSaveBlocks.cpp | 6 | 13 | 5 | 5 |

Before/after ordinary previews against index `85f6b7f40c` (2026-10-29 15:08)
both retain six of seven linking units and 1,877 authored bytes in that scope.
The untouched constructor retains its two opaque-element destructor blockers
and zero linking bytes. These are preview comparisons, not a new census.

The staged-tree batch audit remains INCONCLUSIVE after strict preparation:
index `85f6b7f40c` predates the base, and affected consumer
`Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a current
receipt. Carry this edited-provider/consumer scope into the next normal
census. Identical scoped objects do not establish consumer-wide selection.

## Ownership and remaining work

The edited paths have no identity, data or hatch register keys to transfer or
retire. The Xfer header-adoption row on the untouched `XferSaveOpen.cpp`
remains; none of these four paths has an MS-header queue row. No files moved,
so there is no source-path consumer migration in this batch. The complete
object comparisons above preserve the edited providers and their bindings.

The initial merge trial still supplies these prerequisites; this cleanup is
not a later successful composition trial:

- Reconcile XferSave's constructor base/member identities and the existing
  clear/node provider family; preserve the earlier constructor handoff.
- Resolve the seed/donor `_STL::free` include-context conflict, node fields and
  iterator constructor spelling. The helper's file-scope `key` token prevents
  a blind node-field rewrite.
- Reconcile the open writer's vector begin specialization and FXList layout,
  and adopt its canonical Xfer header through its queue.
- Investigate the 21-byte bucket-number donor's composition byte mismatch;
  preserve LINK066's member-only explicit instantiation.
- Split mixed sources through the supported lane before merging their rows.

No source-file, linked-byte, ownership or registered-debt improvement is
claimed. The final shared views are a separately verified prerequisite for a
future `tu_skeleton.py` merge.
