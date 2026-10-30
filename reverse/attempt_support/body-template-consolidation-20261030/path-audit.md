# Body-template publication path audit — 2026-10-30

Final rebased follow-up: base `7ef5f05dc2`, prerequisite `fdd0f23715`, merge
`9d99f91d9a` before its documentation-only amendment. The outgoing range retires
only the same donor, and the repeated whole-tree old-path scan finds the same
history/proof/census/provenance references. Fresh strict provider/caller checks
cover 58 rows; all seven EH graphs are EXACT and all three preview LINKS. The
broader audit remains INCONCLUSIVE on the older `ccafe54d1d` index and the missing
current CreateAHeroManager consumer receipt; see the handoff for its scope.

Result: **no active consumer or protected-register correction identified.**
This is a read-only path audit, not a byte, EH, link or census receipt.

## Actual outgoing scope

- Recorded UTC: 2026-10-30T16:26:45.749314+00:00
- Recorded HEAD: f66fbbcf7bec9f1c7b446eb652f228499671ab57
- Recorded local origin/master: 1305b5f4735029b25cb21b20b6e77ced9f423c13
- Merge base: 6725fecfe0ac90ac601598051920ebfa32e448c8
- Committed outgoing scope: merge-base..HEAD; staged merge audited separately.
- The direct origin/master..HEAD tree comparison is not used to classify
  outgoing additions/deletions when branches have diverged.
- Staged diff SHA-256: 752bef3c4e36cca9d1788d8ddda6c3daaea5f90ca52a7bf22e327b9986a65ccc
- The committed outgoing range contains the verified declaration prerequisite:
  two existing body-template sources, obstacle notes and
  prerequisite evidence. It contains no source retirement or rename.
- Exactly one source retires in the staged merge:

| Retired donor | Destination |
|---|---|
| Code/Libraries/Source/WWVegas/WWLib/LivingWorldAutoResolveBodyTemplate_getRegenRateForLevel.cpp | Code/Libraries/Source/WWVegas/WWLib/LivingWorldAutoResolveBodyTemplate.cpp |

The donor is absent and destination exists. The approved grouping remains
provisional N; neither this audit nor the consolidation proves an original
retail filename.

## Consumer scan

A combined case-insensitive old-basename scan covered tools, .githooks, .github,
Code, reference/shims, reverse, docs and every root-level file. Additional searches
covered the class/method names and library-directory/path derivation patterns.

No active old-path include, build/configuration entry, tooling hard-code,
workflow, hook or directory/glob assumption requires correction. In particular,
the merge preserves the public method names and callable ABIs. Current source
callers in Common/Rva0059ADB9.cpp and
GameLogic/System/LivingWorld/AutoResolve/LivingWorldAutoResolveBattle.cpp refer
to those symbols, not to the donor filename.

## Ledgers, registers and queues

- functions.csv repoints exactly the existing 58-byte getRegenRateForLevel row,
  RVA 0x004185AA, to the destination. Its decorated name, extent, status and notes
  are unchanged. Existing getHitpointsForLevel remains RVA 0x00418573 / 55B.
- tu_map.csv changes exactly the 0x004185AA SOURCE column. Approved destination,
  N evidence, provisional status and extent stay unchanged. No regenerated map
  is staged.
- No removed-source key occurs in code_identity_baseline.tsv,
  data_check_baseline.txt, gate_baseline.txt or flag_overrides.csv.
- No removed-source reference occurs in data_rows.csv, body_owners.csv,
  symbols.csv fold proofs, pin-consistency baseline, deleted_rows.csv or
  docs/doxygen/sources.cfg.
- Header and MS-header queues contain neither affected source, and no queued
  owner/path entry requires a transfer. The affected class has no canonical registration.
  Existing standard-map include context remains part of normal merged checks.
- The destination retains its existing address_global hatch:
  g_Va00BBB8D8, count 2. The absorbed donor has no registered hatch key.
  The counter tool left hatch_baseline.tsv unchanged, confirmed in the staged
  diff. No debt retirement, new pin, new global definition or identity claim is
  inferred from the merge.
- git diff --check --cached passed during the audit.

## Special naming-history entry

reverse/name_basis.csv row1674 is:

    kind=file
    old=Code/Libraries/Source/WWVegas/WWLib/Rva004185AALookup.cpp
    new=Code/Libraries/Source/WWVegas/WWLib/LivingWorldAutoResolveBodyTemplate_getRegenRateForLevel.cpp
    basis=inferred
    evidence=mechanical:?getRegenRateForLevel@LivingWorldAutoResolveBodyTemplate@@QAEMH@Z
    source=Code/Libraries/Source/WWVegas/WWLib/LivingWorldAutoResolveBodyTemplate_getRegenRateForLevel.cpp

This records the earlier filename rename; it does not define the current code
owner. Preserve its old/new spelling, basis, evidence and original source context.
It is not a source consumer that must be repointed merely because the fragment
has now been absorbed.

Tool evidence for this classification:

- tools/rename.py PATH_COLUMNS (line331) lists active file-rename source columns:
  functions, data rows, tu_map, body owners and the header queue. It does not
  include name_basis.csv.
- tu_skeleton.repoint_all (line3486) uses those columns, plus fold-proof tokens
  and doxygen inputs; that path-repointing function does not rewrite the naming-history record.
- rename.check_renames' file-kind branch checks that the original old path does
  not reappear or remain keyed in PATH_COLUMNS. It does not require the
  historical new/source path still to exist.
- Naming records are append-only history. An additional semantic filename rename
  has not been requested or admitted by this consolidation. Do not manufacture
  one, erase history, or relabel the earlier proof as if produced at the new TU.

If a future consumer needs live routing for a naming-history record, it must
follow current row ownership and the supported tools rather than treating this
historical source column as a current source registry.

## Other intentional old-path mentions

| Location | Classification |
|---|---|
| reverse/link_status.csv | Published historical census source record, retained for normal measurement refresh. |
| Destination // ---- from marker | Source provenance retained by the merge tool, not an active include. |
| reverse/attempt_support/body-template-consolidation-20261030/view-proof.json | Original prerequisite source/object evidence and hashes. |
| reverse/name_basis.csv | Historical filename-rename record described above. |

Generated scratch plans, object receipts and old census objects remain old
snapshots. They are not fresh verification for the merged destination.

## Verification boundary and publication

Root is collecting fresh merged strict/byte/provider proof. This audit did not
compile, run global checks, refresh queues, claim work, stage files or edit any
tracked input. It does not replace normal hooks.

The source move must retain both complete functions and compare provider/caller
bindings with the retired donor object removed from the selected census cohort.
Use the supported merge/link mechanisms; do not edit measured census records or
cached objects by hand. The intended headline change is one fewer source file
with 113 matched bytes and link coverage retained, not new byte recovery.

The printed Verifier-Change trailer can be retained as supplied by the merge
tool; it does not constitute debt retirement. Repeat the affected-path scan after
rebase only if a relevant move or consumer change joins the outgoing batch.

Only this untracked build Markdown file was written by the audit.

## Recorded committed outgoing changes

    M	Code/Libraries/Source/WWVegas/WWLib/LivingWorldAutoResolveBodyTemplate.cpp
    M	Code/Libraries/Source/WWVegas/WWLib/LivingWorldAutoResolveBodyTemplate_getRegenRateForLevel.cpp
    M	docs/linking_obstacles.md
    A	reverse/attempt_support/body-template-consolidation-20261030/readme.md
    A	reverse/attempt_support/body-template-consolidation-20261030/view-proof.json

## Recorded staged changes

    M	Code/Libraries/Source/WWVegas/WWLib/LivingWorldAutoResolveBodyTemplate.cpp
    D	Code/Libraries/Source/WWVegas/WWLib/LivingWorldAutoResolveBodyTemplate_getRegenRateForLevel.cpp
    M	reverse/functions.csv
    M	reverse/tu_map.csv
