# W3DShrubBuffer destructor consolidation

The supported merge trial absorbs `Rva000E9BACDtor.cpp` into
`Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShrubBuffer.cpp`.
It would remove one source file and carry five existing ledger rows without
adding matched bytes. The source/ledger/queue/map changes were restored before
committing this handoff: no source-file reduction is claimed. The earlier
view reconciliation is `1ffd76fe17`. The separate verifier fix `92fd91ae69`
locally resolves the header-transfer refusal recorded in
`w3dshrubbuffer-destructor-merge-20261105-codexb.md`.

Publication prerequisite: `.githooks/pre-push`'s `debt_registers_check` and
the runner publisher load `repair_queue.py` from the outgoing base. The fix
must therefore reach origin before the source move is queued. The publisher
currently reports master locked by the maintainers and retains the fix locally.
Do not bundle the merge behind it while origin still has the old checker.
After `92fd91ae69` lands, rerun the supported merge and its normal checks.

Verification of the reverted trial composition:

- `./build.sh` passes all 31 rows. Five literals, seven empty-string
  references, fifteen float references and four named imports verify.
  Renumbered funclet labels resolve through the exact parent EH graphs.
- `eh_verify.py`: EXACT 3, no baseline or missing-object cases.
- `check_csv.py`, `find_declared_unmatched.py`, `tu_ownership.py --staged`
  and the staged whitespace check pass.
- `data_check.py`: zero findings; converged enforcement reports zero second
  names and zero unjudged rows. Neither source has data or identity register
  keys to transfer or retire.
- The supported merge's LinkGuard accepts the composition, selected COMDATs,
  retained providers and affected consumers. `link_check.py` predicts LINKS
  with 5,539 bytes against census 2026-11-05 05:17 (`c95fcfcfcd`). This equals
  the seed's 5,430 plus the absorbed donor's 109; it is no census gain.
- The shadow identity check still reports the existing unwind binding at
  `0x007636EA` to `??1Rva0008B470@@QAE@XZ` instead of retail's wrapper at
  `0x0008B4CD`, and the existing divergent `Matrix3D::operator[]` COMDAT.
  The previous handoff records both before the merge. They remain open;
  byte/EH verification does not retire them.

The merge rebuilt assignments in memory. The trial TU-map diff only
repoints five source columns, retaining all assignments and approvals.
The donor's pending W3DShrubBuffer header-queue row and its four listed RVAs
moved intact to the destination alongside its existing row. The other header
rows remain, and the refreshed Microsoft-header queue is unchanged. No debt
is retired. The hatch updater leaves the register unchanged; all four
link-wide aliases remain.

The trial tooling compatibility audit covers the outgoing range from
`f0f6176eead83c4c8bb26f6e69e006fcca7a97a1` through `92fd91ae69` plus this
staged merge. Its only removed source path was `Rva000E9BACDtor.cpp`.
The basename search across tools, hooks, workflows, source/includes,
configuration, docs, ledgers and registers finds no active consumer needing
the old path. Remaining mentions are origin comments, historical attempt
evidence/logs and census-owned `reverse/link_status.csv`. Census records
are left to their owner. Trial function rows, map source columns and
header commands used the surviving TU; no tooling consumer change was needed.
All path moves and debt transfers were restored with the trial.

The six rejected donors remain unchanged. The vertex/index loader and
Rva000E8365 still conflict on RefCountClass; AddTreeType, addShrub, DoXfer
and RemoveShrubsForConstruction still need buffer-view reconciliation.
Mixed owners remain outside this merge. LINK-184's canonical-header
include-closure blocker and next step are unchanged.

The verifier fix's final combined repair-queue/exploit run passes 321 tests,
skips one and deselects the already reproduced missing-symbols.csv fixture
failure. All 18 new index/outgoing-tree transfer cases are included.
