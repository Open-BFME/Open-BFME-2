# AIUpgrade consolidation recheck, 2026-10-30

Base: `1f26b04a7b`. The default picker claimed Common/AIUpgrade.cpp and its
three whole-file donors. All four pass find_declared_unmatched.py. No source
edits or moves were made.

`tu_skeleton.py --merge Code/GameEngine/Source/Common/AIUpgrade.cpp --dry-run`
accepts no donor. AIUpgradeBuild.cpp and AIUpgrade_getCostPerTick.cpp fail
with C2600 for the seed constructor. AIUpgrade_DoXfer.cpp fails the census
link guard on duplicate `??1AIUpgrade@@UAE@XZ` and changed
`??_7AIUpgrade@@6B@`. All four inputs are reported census-linked.

`tu_views.py ... --dry-run` reports conflicting AIUpgrade base clauses:
the build donor has none, while seed, cost and transfer use Rva0055B0CC.
Its suggested field/method union does not establish the full native virtual
interface or destructor ownership. The 2026-10-29 obstacle's prerequisite
therefore remains; no fresh trial repeats its known vtable failure.

The required Common/ consolidation planner was started alongside the merge
dry run. It refused to write a snapshot because Code/ changed during its
scan (the dry run creates temporary source files). That result is not TU
approval. Run these operations sequentially when retrying; no stale planner
report was used to authorize a move.

BFME1 freshness: fetched official master, obtaining
`1474d4c870ba25b77b9d411618dd31146adf1326`. The repository-pinned checkout
remained `337e4b48e8f295f74bdd1155ad2b6dd848b63c32`. The ignored success stamp
still names `4fa9d591` from 2026-10-26. Old/new full BFME2 byte verification
has not been completed, so the checkout, submodule pointer and success stamp
were not advanced. No donor body or layout was imported in this pass.

No source-file, matching, census or ownership gain is claimed. Scope claims
were released after the investigation. t=8min model=gpt-6.1-sol.
