# IngameNoticeDisplay consolidation

Inspected base: `d453af1733`, 2026-10-30. The supported picker claimed
`Code/GameEngine/Source/Common/Bfme/IngameNoticeDisplay.cpp` and its sole
whole-file donor, `IngameNoticeDisplay_reset.cpp` in the same directory.

## Prerequisite

The supported merge dry run rejected reset because its private class used
different field names and omitted the seed's SubsystemInterface base. The
donor now includes the canonical base header and uses the seed's declaration
and field names. The descriptor store retains its existing offset view through
a cast; no descriptor layout or recovered field name is claimed.

The original two sources pass `./build.sh`: 22 function rows and two data rows.
Both preview LINKS against census index `85f6b7f40c` (2026-10-29 15:08), for
628 and 68 authored bytes respectively. After reconciliation reset still
matches its complete 68-byte body. Its two normalized COMDAT fingerprints
(`538e0d467efe` for reset, `218cde81ae4c` for for_each), definitions, external
references and weak/include records are unchanged. The base header contributes
seven AsciiString aliases already present in the destination's object.
Declared-unmatched checks pass before and after the edit.

The pre-edit naming planner covered Common/Bfme. Both sources are unresolved
with no alternative destination. The seed flags pragma/include context and
the data/hatch registers; the reset donor has no planner blockers. The
WorldBuilder/BFME1 GUI path is a lead, not target placement proof. Placement
comes from the supported merger's current in-memory TU map, not that planner
hint or the stale committed map. Three mixed sources remain outside this move:
Rva004E5A24Ctor.cpp, Rva004E5A78Method.cpp and GameClient/GUI/IngameNoticeDisplay.cpp.

Neither whole-file source owns a header-queue, Microsoft-header-queue,
code-identity or data-check-baseline key. The separate mixed GUI source's
iswspace header debt remains outside this scope. The destination already owns
two linker-alias hatches and its data-ledger entries; no debt is retired here.

## Applied merge and verification

Prerequisite publication rebased onto `bd28601b65`; the seed source was
unchanged. The refreshed naming survey is current before the merge and flags
the donor's new quoted include. It resolves to the same canonical header as
the seed. The supported dry run accepts both inputs with no rejected donors;
its link guard preserves both census-linked units. `tu_skeleton.py --merge`
then removes the reset donor and moves only its source column in functions.csv
and tu_map.csv. The approved TU name is provisional; no original retail path
is newly proved, and no whole-map regeneration is committed.

The destination passes strict `link_check.py --prepare-current`: all 22
function rows, two data rows and the two renumbered funclets verify. Both EH
graphs are EXACT. Declared-unmatched and CSV checks pass (99,011 functions,
9,415 symbols, 2,237 data rows). Staged TU ownership passes. The enforced
converged-data check reports 11 addresses, zero second names and zero unjudged
rows. The destination's Microsoft-header scan is clean. The merger refreshes
both header queues without changing either; all protected registers, hatch
totals and data owners remain unchanged.

All 29 normalized COMDAT fingerprints (bytes and relocation identities), 33
definitions, 14 external dependencies after subtracting internal definitions,
weak records, aliases and include directives equal the original object union.
The duplicate for_each copy becomes one identical copy, and the destructor's
reset dependency resolves inside the combined TU. No provider or dependency
is added or lost. This bounded comparison does not establish a census result.

## Complete outgoing path audit

The outgoing work has one source-path move: reset is absorbed into the existing
IngameNoticeDisplay TU. The prerequisite has no path moves. Combined searches
cover the donor's full path/basename and Common/Bfme directory consumers in
tools, hooks, workflows, Code includes, build/configuration inputs, docs and
active ledgers/registers. No active consumer needs an update. Remaining old
mentions are the TU's provenance comment, historical link_status.csv,
name_basis.csv and attempt evidence. The committed map changes only the moved
row's source; source includes, data owners, fold proofs and queues retain their
current owners. New strict compiler receipts are prepared at the destination.

The publication fetch advances upstream from `bd28601b65` to `cf1a010231`.
There are no intervening tool/hook/workflow or seed-source changes. The donor
change is this prerequisite, landed as `4915242746`. The shared StringBase
header adds an opt-in public default-constructor switch whose default preserves
the previous declaration; the publisher must verify after rebasing as usual.

## Link boundary

Ordinary preview of the destination reports a duplicate reset because saved
index `85f6b7f40c` retains the absorbed donor. It does not overlay the source
removal. The supported merge guard accounts for both original inputs and
accepts their composition. The batch audit is INCONCLUSIVE on the older index
and a missing current receipt for affected consumer
`Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp`. Carry that
consumer and this provider/removal into the next scheduled census. Broader
consumer closure and a new census verdict remain unverified; no linked-byte
gain is claimed. One source file is removed with all matched coverage kept.
