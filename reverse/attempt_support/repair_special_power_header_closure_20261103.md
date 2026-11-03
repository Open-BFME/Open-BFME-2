# RepairSpecialPower header closure and audit follow-up, 2026-11-03

After the one-donor merge, `header_adopt_lane.py accept` independently passed
AICommandInterface, AIUpdateInterface and ThingTemplate on the surviving
`Code/GameEngine/Source/GameLogic/Object/SpecialPower/RepairSpecialPower.cpp`.
Each command retired its one transferred queue entry. No source or header edit
was needed: the donor already included the canonical definitions. Together with
the earlier BehaviorModule acceptance, this pass retires four header queue rows.

The normal scoped build was repeated after runner publication rebased the merge:
six of six rows exact, references verified, and the EH label renumbering accepted
through the parent's graph. The source reduction remains one file. The mixed
getter/destructor owners and existing destructor hatch remain out of scope.

The standalone affected-consumer audit was run against the three RepairSpecialPower
commits, base `22503b3ba1^`, tip `8a9a7ab039`, with the surviving source in its
NUL-delimited verified-source list. Its complete final output was:

```text
link batch audit: INCONCLUSIVE baseline: index at 8661f15284, outgoing base 22503b3ba1^; findings below are provisional since-index changes
link batch audit: INCONCLUSIVE: 1 source object(s) lack current receipts; first: Code/GameEngine/Source/GameLogic/Object/SpecialPower/RepairSpecialPower.cpp
```

Exit status was 2, including after the repeated scoped byte build. This is not
a clean affected-consumer verdict. `link_census.object_current` requires a strict
include-inventory receipt or the census's own witnessed compile; the scoped
builder's successful byte result alone does not establish that proof. The
separately recorded merged-object preview still predicts LINKS for its 223 census
bytes, but does not clear the broader audit. Carry this unit into the next
maintainer census/current-receipt audit, including consumers of moved providers;
no game smoke or census was started here. The old index also predates the
outgoing base. The publisher retains its normal pre-push batch audit.
