# AIGateUpdate vanished-source header-debt accounting

2026-11-05, codexb5.

The runner refused publication of the merge because the outgoing range both
retires the UpdateModule header-queue rows and removes the constructor and
destructor source paths. The source-present verdicts cannot be rerun against
those paths in the final tree. No debt checker was changed.

The original owning-lane acceptance passed for the seed, constructor and
destructor, retiring three queue rows before either donor disappeared:
[original owner verdict](../aigate-update-snapshot-20261105-codexb5/aigate-header-accept.log).
The subsequent supported approved-TU merge moved every donor row into
Code/GameEngine/Source/GameLogic/Object/Update/AIGateUpdate.cpp:

| Vanished source | Preserved RVAs |
| --- | --- |
| AIGateUpdateCtor.cpp | 0x004B08E8 |
| AIGateUpdateDtor.cpp | 0x004B0802, 0x004B0926, 0x0078E77E, 0x0078E786 |

The merged TU verifies all 13 ledger rows and both parent EH graphs; the
three link-wide aliases remain intact. See the
[merge and compatibility audit](../aigate-update-merge-20261105-codexb5/README.md).
A fresh owning-lane acceptance of UpdateModule in the merged TU also passes:
[current owner verdict](merged-header-accept.log). No additional queue row
was removed by this check.

The follow-up commit supplies one Debt-Retired explanation for each vanished
source's UpdateModule key, using AGENTS.md's exception for a source that
vanished. This accounts for completed owner acceptance followed by a verified
TU merge; it neither tombstones live rows nor invents a replacement debt row.
The broader link audit's pending consumer receipt and next-census confirmation
remain as recorded in the merge audit.
