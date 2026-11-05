# Subsystem System TU consolidation

Prerequisite: the canonical list-storage patch initially committed as beaf5f4ddf
and transported onto the current base as fb0997b337. The runner's publisher
performed that rebase; the patch was not amended. The refreshed planner snapshot
passes `name_lane.py consolidate --check build/consolidation`.

`tu_skeleton.py --merge Code/GameEngine/Source/Common/System/SubsystemInterface.cpp`
reused its successful dry-run plan, absorbed all five eligible donors and removed
five source files. No separate notification donor edit was necessary: the seed's
canonical header adoption also resolved the prior declaration-order conflict.
The tool rebuilt stale TU assignments in memory. The committed tu_map change only
repoints 12 existing source fields; it does not regenerate approvals or evidence.
The mixed Libraries/Source/subsystem/SubsystemInterface.cpp remains untouched.

The merge repointed 14 functions.csv rows, one data_rows.csv owner and six
name_basis.csv records. No data/identity debt keys existed on these five donors;
no key was retired. The tool refreshed the header and Microsoft-header queues;
neither needed a change. Fold proofs still refer to the existing destination TU.
All current sources are tracked. Existing hatch/debt counts remain unchanged.

Verification:

- `./build.sh` final TU: 30/30 ledger rows exact (the composition plan reports
  29 nonduplicate bodies), one data row exact, two constructor folds proven,
  two literals plus two empty-string references verified.
- `find_declared_unmatched.py`: all defined functions matched.
- `eh_verify.py`: all four parent EH records exact, zero missing/nonexact.
- `data_check.py`: zero shadow findings.
- `check_csv.py`, `tu_ownership.py --staged` and `pin_consistency.py --check` pass.
- `link_check.py --prepare-current` produced a strict receipt for the final TU.
  Preview linkage is clean for all 1,607 bytes: the six premerge units total
  1,607 as well. The displayed seed-only census before figure is 630; the
  increase to 1,607 is composition, not a census coverage gain.
- The shadow code-identity checker reports the same two Vector_base constructor
  bindings at 0x00211E58 as the prerequisite patch. The byte gate separately
  proves both complete constructor folds and resolved callees. No new constructor
  identity or shadow-baseline allowance is added by the merge.

Tooling compatibility audit: current consolidation delta against its prerequisite
patch, all five deleted paths and basenames searched together across tools,
hooks, workflows, Code, reverse and docs. No active tool, hook, workflow or
source include depends on a deleted donor. Updated the two doxygen reader-guide
references to the loader. Remaining matches are generated `from` comments,
the preexisting Libraries TU's location comment, historical attempt/naming/claim
records, the census-owned link_status.csv, and the archived class-contract
snapshot. The snapshot's owning-tool refresh found zero private views after
canonical adoption and an undecided size; its trial output was reverted rather
than replacing historical layout evidence with an empty-view contract.

Batch link audit exits 2, not a clean result:

```
link batch audit: INCONCLUSIVE baseline: index at c95fcfcfcd, outgoing base HEAD; findings below are provisional since-index changes
link batch audit: INCONCLUSIVE: 99 source object(s) lack current receipts; first: Code/GameEngine/Source/Common/AttributeModifierStore.cpp
```

The merged provider's explicit preview is clean. The wider consumer and selected
COMDAT comparison remains unverified beyond the available strict receipts;
carry it into the next scheduled census, including the earlier unreceipted
0CreateAHeroManager21FE49.cpp consumer. No nightly, real-link cycle or smoke
runner was started and no whole-game link or census gain is claimed.
