# GroupOrder TU merge, 2026-11-04

Prerequisite: [Snapshot reconciliation](grouporder-snapshot-reconciliation-20261104.md),
now published as 75f27867f6 after fleet rebasing. This operation uses the supported
`tu_skeleton.py --merge Code/GameEngine/Source/GameLogic/AI/GroupOrder.cpp`.
Its current in-memory map approves 12 code rows. It absorbs GroupOrderCtor.cpp
and GroupOrderCopyCtor.cpp, preserving the seed's 13 total ledger rows (including
the existing companion row) and deleting two source files. GroupOrderHolderCtor.cpp
stays separate: composition rejects its second explicit
`_Vector_base<ScienceType, allocator<ScienceType> >` destructor with VC7.1 C2995.
Next reconcile that specialization against the seed's verified game-free wrapper
in a separate byte/link-verified change before retrying the holder merge.

Verification and ownership audit:

- Normal `./build.sh GroupOrder.cpp`: 13/13 exact, one data row exact, existing
  unwind label verified through parent EH data; no literal/import findings.
- `tu_views.py GroupOrder.cpp --dry-run`: GroupOrder already shared across the
  destination and remaining holder; no additional class extraction required.
- `find_declared_unmatched.py` passes for the destination and AiOrdersManager.
- Current-object link previews: destination LINKS 783 authored bytes; remaining
  holder LINKS 156. Together these preserve the four old units' 939 bytes.
  AiOrdersManager, which references the transferred counter, keeps LINKS 1314.
  Index f12552d0a7, 2026-11-04 20:47. These are local predictions, not census gains.
- check_csv passes: 99,452 functions, 9,328 symbols, 2,268 data rows.
- The merger transfers the copy constructor's one data_ledger/data_rows owner
  and its address_global hatch key to the destination, preserving totals. No
  baseline debt is retired, no alias removed and no new hatch introduced.
- Exact source-path searches find no gate/data/code-identity baseline entries
  or header/ms-header queue rows for these four GroupOrder sources. The merger
  invokes the header-queue transfer and ms-header refresh owners. No queue edits
  result. The two tu_map changes only repoint source columns; approvals and
  routing evidence remain unchanged, with no regenerated map committed.

Tooling compatibility audit covers both deleted basenames and paths across the
entire pending source-move batch (only these two donors; preceding reconciliation
and other handed-over commits have no source moves). Combined searches covered
tools, hooks, workflows, Code, docs, reverse, build scripts and project/config
files. Active path-keyed owners are repointed by the merger. AiOrdersManager's
provider comment now names GroupOrder.cpp; its 15/15 rows and two EH labels pass
normal build verification. There are no source includes or tool hardcodes to
update. Remaining old paths are source provenance comments, the historical
link_status census, deleted_rows explanations, a blocked name_agreed evidence
record, re_attempts and earlier attempt evidence; retain them as history.

The source-layout report was read before composition. It supplies no original
BFME path evidence for these shards and its unresolved/protected-register flags
do not approve a merge. Current-map approval and the merger's compile/byte/link
guards authorize this limited composition. No claim of donor source recovery,
new byte coverage, real-link progress or runtime validation is made.
