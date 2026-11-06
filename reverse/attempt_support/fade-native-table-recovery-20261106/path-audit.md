# Planned FadeInTextRender consolidation path audit

Read-only audit, 2026-11-06. Inspected HEAD:
`80a5fcac13b4906bb56219e48618d78932cd855c`. The separate verifier correction
`de265d68a8` is already published. This report does not apply or approve the
source merge; its exact accepted donor set remains pending the normal guard.

## Planned moves

Both sources are to be absorbed into
`Code/GameEngine/Source/Common/FadeInTextRender.cpp`:

1. `Code/GameEngine/Source/Common/Rva0059675ADtor.cpp`
2. `Code/GameEngine/Source/GameLogic/SkirmishAI/AIEconomyBuilder/rva00596908Rva00596908Farm.cpp`

The destination keeps its path. No directory is deleted or renamed. The second
donor crosses source regions into the approved destination; new destination
compiler, include and object receipts are required. No original EA path is
changed or newly claimed by this audit.

## Audit scope

Combined case-insensitive searches covered both full donor paths, basenames
with and without `.cpp`, and encoded object-derived names. Active scopes:
`tools/`, `.githooks/`, `.github/`, `Code/` including include directives,
`reverse/` registers and queues, `docs/` including `docs/doxygen/`, `vendor/`,
and all root build/configuration/document files. Hidden/ignored files in those
named scopes were included. Historical attempts and logs were inventoried
separately. The audit did not traverse `build/` worktrees, `.git/`, baselines or
reference checkouts.

No donor-specific active tool, hook, workflow, source/header include, root build
configuration, vendor file, doxygen source input, glob or directory-derived
consumer needs an independent edit. Existing generic directory scans retain
their directories. The root must rerun the batch audit if another source-path
change or affected active consumer is added before publishing.

## Live ownership and provenance transfers

The supported `tu_skeleton.py` merge should perform these exact transfers:

| Registry/input | Current donor references | Required treatment |
| --- | --- | --- |
| `reverse/functions.csv` source cells | Dtor: 7 rows / 182 bytes. Draw: 3 rows / 499 bytes. Total: 10 rows / 681 bytes. | Repoint all ten source cells to the destination, preserving names, extents, status and evidence. |
| `reverse/functions.csv` fold proof | One exact `fold-proof=Code/GameEngine/Source/Common/Rva0059675ADtor.cpp` token on `??1Rva0059675ABase@@UAE@XZ` at `596686`. | Transfer the proof token to the actual merged emitter using `repoint_fold_proofs`. |
| `reverse/tu_map.csv` source cells | Six Dtor-owned mapped addresses plus three draw-owned addresses. | Repoint nine source cells only. Preserve approved destination, confidence and evidence; do not regenerate the map. |
| `reverse/name_basis.csv` source cells | Three draw records: `Anim2DCallView::m_template`, `Anim2DCallView::m_alpha`, `FadeInTextRender::rva00596908::textWidth`. | Transfer source provenance so rename/revert resolves the surviving owner; retain agreement evidence and spellings. |
| Destination `// tu-skeleton:` comments | Nine placeholders name the donors. | Normal composition consumes/replaces them. Absorbed-fragment provenance comments may retain old paths afterwards. |

The seven-byte complete base destructor is an existing ICF alias. Its first
address identity remains the Disp0 setter in `Disp0DwordImmSetters.cpp`; that
identity's `tu_map.csv` source cell at `596686` must not be reassigned merely
because the alias moves. Its alias function source and fold-proof token do
follow the merged emitter.

`tu_skeleton.repoint_all` already handles `rename.PATH_COLUMNS`, naming-basis
source cells, exact fold-proof tokens in functions and pins, and doxygen INPUTs.
Its report refresh handles header scope and Microsoft-header queues. No missing
active registry support was found.

## Protected debt, headers, hatches and pins

No reference to either donor was found in:

* `reverse/gate_baseline.txt`, `code_identity_baseline.tsv`,
  `data_check_baseline.txt`, `hatch_baseline.tsv`, `flag_overrides.csv`,
  `data_ledger.csv`, or `eh_baseline.csv`;
* `reverse/header_queue.tsv`, `ms_header_queue.tsv`, `dx_migration_queue.tsv`,
  `stlport_trial.csv`, or `name_data_requests.csv`;
* `reverse/body_owners.csv`, `data_rows.csv`, `symbols.csv`,
  `pin_consistency_baseline.csv`, `exit_link_blockers.tsv`,
  `unclaimed_sources_whitelist.txt`, or `docs/doxygen/sources.cfg`.

Thus no donor-specific protected-debt/header/hatch/pin key transfer or debt
retirement is identified. The one live fold proof is the function-row token
listed above. The ordinary merge still recomputes transfers and refreshed
reports at application time; this audit grants no exemption from those checks.

## Intentional historical and measurement references

| Location | Classification and treatment |
| --- | --- |
| `reverse/link_status.csv` | Published census retains Dtor `linked=no` / one wrongly selected provider and draw `linked=yes`. Preserve until the scheduled census updates it. A merge cannot hand-edit these measured results. |
| `reverse/vtable_bridge_queue.tsv` | Current queue header names real link `1a5f4a11143f74be71ff30bc940004ba91068d04`. Two rows for base table `870A5C` and derived table `870A70` already name the surviving destination in the main source field, but embedded evidence names the old Dtor ledger owner/object. Preserve this measured JSON; the next real link decides whether selection/refusals clear. |
| `reverse/name_votes.csv`, `reverse/name_agreed.csv` | Dated votes and agreement transitions encode donor paths inside immutable naming keys. Preserve these original vote/agreement identities and hashes. Move the active `name_basis.csv` source cells, not the historical voting keys. Old blocked or landed applications do not authorize new source edits at vanished paths. |
| `reverse/re_attempts.log` | Historical landings, failed naming/reconstruction and merge verdicts. Preserve the original paths and add a new verdict through the owning logger only if needed. |
| `docs/linking_obstacles/link-133-icf-twin-rows-moved-objects-ahead-in-link-order-so-their-wrong.md` | The dated blocked composition mentions the draw donor. Keep its historical statement; append the actual merge result/current evidence and remaining selection/runtime boundary in the repair commit. Do not globally replace old names. |
| Existing source `// tu-skeleton:` and absorbed-fragment comments | Planner inputs before merging, provenance afterwards. They are not includes or executable path consumers. |

Historical attempt artifacts containing donor references:

* `reverse/attempt_support/fade-consolidation-20261106-c07-seat2.md`
* `reverse/attempt_support/fade-assets-link-20261018/paired-proof.json`
* `reverse/attempt_support/fade-loadassets-link-20261018/` receipts and README
* `reverse/attempt_support/fade-load-assets-link-20261018/` README/object proof
* `reverse/attempt_support/fireweapon-primary-link-20261030/consumer-receipt-inventory.json`
* `reverse/attempt_support/fade-native-table-tool-blocker-20261106/` review,
  README and private proof/script
* `reverse/attempt_support/fade-native-table-recovery-20261106/` private/normal
  before-state proof and its reproduction script

These record the paths that existed when inspected. No active tool/workflow
invocation of those donor-specific artifact paths was found. Preserve them;
new merged-destination proof belongs alongside the new merge evidence rather
than rewriting old source snapshots.

## Remaining root verification

This is a tooling/path/debt audit only. The root still needs the supported
approved merge, the final donor-set check, new destination build and frozen-file
checks, exact EH/data/ledger/ownership checks, current merge/link guard, and the
outgoing publication audit. Do not use pre-merge donor receipts as proof of the
merged object. In particular, this audit does not establish that the native
29-byte base deleting destructor wins, that either vtable is selected correctly,
or that an actual rebuilt image runs further. Keep those outcomes separate.
