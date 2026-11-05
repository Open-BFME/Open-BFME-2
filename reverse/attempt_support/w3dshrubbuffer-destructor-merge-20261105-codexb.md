# W3DShrubBuffer destructor merge: debt-transfer false reject

After the separately verified view reconciliation in `1ffd76fe17`,
`tu_skeleton.py --merge` accepted the seed and `Rva000E9BACDtor.cpp`.
The trial absorbed the latter's five rows into
`Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShrubBuffer.cpp`,
removing one source file. The commit-msg hook then refused the debt accounting,
so the entire uncommitted merge was reverted. No source-file reduction is
claimed. The published prerequisite remains intact. No matched row or byte
extent was added or removed.
The tool rebuilt TU assignments in memory; the committed map diff only
repoints five source columns, without changing assignments or approvals.

Verification of the rejected composition:

- `./build.sh` on the resulting TU: 31/31 rows match. Nine existing funclet
  pins resolve through the parent EH graphs despite compiler-label changes.
  Five literals, seven empty-string references, fifteen float references,
  and four named imports verify.
- `eh_verify.py`: all three parents' EH graphs are EXACT.
- `check_csv.py` passes; `find_declared_unmatched.py` finds no unmatched body.
- `data_check.py`: zero findings. Neither source had data-identity or
  code-identity baseline keys to transfer or retire.
- `link_check.py`: destination LINKS with 5,539 linking bytes. Before the
  move, the seed and donor predicted 5,430 + 109 bytes. These are previews
  against census 2026-11-05 05:17 (`c95fcfcfcd`), not a new census or gain.
  The supported merge's LinkGuard accepted the composition and affected
  provider/consumer bindings.
- The header-queue row for the donor was transferred by the merge tool,
  retaining its RVAs and pending canonical-adoption verdict. The existing
  destination rows remain. The Microsoft-header queue was refreshed by the
  tool and did not change. No header debt was retired. These queue transfers
  were reverted along with the merge after the refusal.
- The hatch updater left the register unchanged; all four existing link-wide
  aliases remain. No alias removal, pin addition, or debt retirement is claimed.

The shadow identity check still reports the unwind row at `0x007636EA`
calling `??1Rva0008B470@@QAE@XZ` where retail calls the five-byte wrapper
at `0x0008B4CD`, plus a divergent `Matrix3D::operator[]` COMDAT. Both were
reported before this merge too. The byte/EH checks and link preview above
do not retire those identity findings. A future identity pass should use
the wrapper's current owner (`W3DView.cpp`) and inspect selected COMDATs.

The six other rejected donors were left untouched. AddTreeType, addShrub, DoXfer
and RemoveShrubsForConstruction need the canonical and private buffer fields
reconciled; loadShrubsInVertexAndIndexBuffers and Rva000E8365 also encounter
duplicate RefCountClass declarations. Other mixed owners remain outside this
merge. LINK-184 concerns the separate canonical-header include-closure
problem; this consolidation does not clear it.

Path-consumer audit: reviewed the complete outgoing batch from
`dbde7dbe3be16481b2c8d6f2f9577bc322f6b7ce` through the rejected staged merge,
including the earlier GiantBirdAIUpdateOnCollide.cpp absorption. Searched
both removed basenames across tools, hooks, workflows, source/includes,
configuration, docs, ledgers and registers. No active build/include consumer
needs either old path. Remaining mentions are historical attempt evidence,
source-origin comments, historical obstacle text, and census-owned
`reverse/link_status.csv` records. Census records were not rewritten by hand.
The trial's function ledger, source-column map and header queue used surviving
owners. Those changes were reverted. No tooling consumer change was required.

## Reproduced refusal and next step

`repair_queue.verify_missing_debt` refused:

    Rva000E9BACDtor.cpp: vanished unit (W3DShrubBuffer) needs a transfer, deleted_rows coverage or per-key Debt-Retired trailer

The full source paths have the common
`Code/GameEngineDevice/Source/W3DDevice/GameClient/` prefix. The staged
header-queue diff replaced the donor's source with W3DShrubBuffer.cpp while
preserving the class and the four listed RVAs (`0x000E9BAC`, `0x007636E2`,
`0x007636EA`, `0x007636F8`). The destination already had a row for the same
class, listing its different RVAs. The tool retained both rows.

The checker reduces queue rows to `(class, source)` sets and tests only pairs
newly added against HEAD (`_debt_transferred`, header branch). Consequently,
the real transfer to this already queued destination has no newly added pair.
All five ledger rows followed the donor to the destination, but that evidence
cannot reach `_debt_follows` because the added-pair set is empty.

No check, register, or exception trailer was changed to evade this refusal.
The failed commit created no commit. `re_log.py` retracts the premature
consolidation landed verdict and records this false reject. A tooling pass
should reproduce the collision, distinguish preserved transferred RVAs from
an unrelated old destination row, and add a regression test without weakening
the old-duplicate protection. Then retry the supported merge; its view
prerequisite is already published as `1ffd76fe17`.
