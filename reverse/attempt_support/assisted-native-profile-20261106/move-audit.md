# AssistedTargetingUpdate constructor move: compatibility audit

Scope: the single pending absorption of
`Code/GameEngine/Source/GameLogic/Object/Update/AssistedTargetingUpdateCtor.cpp`
into `Code/GameEngine/Source/GameLogic/Object/Update/AssistedTargetingUpdate.cpp`.
The donor is absent and destination exists. No unrelated historical move was
audited. This is a current-tree audit; the parent supplies the outgoing range
and completes normal byte/EH/data/link verification.

**Remaining active broken consumers: none found.**

Searches were case-insensitive and covered the full old basename/stem (which
also catches full Windows/Unix and relative paths), old `.obj` basename and the
encoded object stem `^assisted^targeting^update^ctor`. Searched active `tools/`,
`.githooks/`, `.github/`, all `Code/` source/header/build configuration content,
`reverse/` registries/queues/baselines, and `docs/`. Searched remaining root
build/config/source-registry files and owned `reference/shims/` separately.
Build scratch/worktrees, vendor/reference inputs and `.git/` were excluded from
the broad search. Large function/symbol/TU/data ledgers were searched narrowly;
none was loaded wholesale. Doxygen/source-list and configuration consumers were
included in these scopes. No active tool derives a path from the old stem.

## Path-keyed ownership and proof inputs

No old source path remains in functions.csv, symbols.csv, deleted_rows.csv,
tu_map.csv, data_rows.csv, data_ledger.csv or data_converged.csv. Constructor
0x486E8D, its handler 0x78C165, and transfer 0x4DF81B now point to the destination.
No current fold-proof token refers to the absorbed constructor source; the
callback fold proofs continue to name their unchanged common/BattlePlan donors.

No old-path identity, gate, data-check, MS-header, hatch, unclaimed-source or
other protected baseline key remains. The UpdateModule header-queue entry is
correctly keyed to the destination, retaining its old m_vtable diagnostic as
queue history. Canonical acceptance/retirement remains available through
header_adopt_lane.py; this is not a broken consumer introduced by the move.
The unrelated AICommandInterface entry already names the destination.

Data-ledger literal/census aliases formerly qualifying `_s_dummy00` and
`_s_dummy10` with the donor path now qualify the destination. Their historical
symbol spellings are inventory, not active includes/build/provider requests.
Current native table/body verification is the parent's check; this audit does
not treat inventory strings as live emitted providers.

## Intentional old-path references

* `reverse/link_status.csv`: a measured census snapshot, not a current source
  registry. link_check.py explicitly forgets deleted source objects; leave the
  census record to its owning measurement workflow.
* `reverse/re_attempts.log`: historical landed/blocked attempts, including the
  recent callback prerequisite; preserve the recorded paths.
* `reverse/attempt_support/assisted-native-profile-20261106/`: proof.json and
  table-slot receipts identify the immutable constructor object/source that
  was actually inspected before the move. Preserve those historical hashes.
* Destination `// ---- from ...AssistedTargetingUpdateCtor.cpp`: merge provenance
  comment, not a compiler include or runtime filename.

No old-path raw EA filename string was found in the searched active sources or
owned shims. Such strings would be preserved rather than rewritten if present.

Only this untracked audit was written. No tracked file/index changes, builds,
claims, network operations or publication were performed by this review.
