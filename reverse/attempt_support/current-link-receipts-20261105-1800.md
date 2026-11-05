# Current link receipt and die module consolidation checks

AIBuildable.cpp passes 20 of 20 matched functions, the compiler's two float
references and the exception handling label pins. The eight explicit source
preparations together pass 103 of 103 matched functions. The receipt
preparation refreshes the scoped build evidence.

The six-source same-head audit at `babe36570dde18d174497cf49b6594fa5bfa53fd` uses the
published index from 2026-11-05 05:17 at `c95fcfcfcd`. Its closure verdict
is inconclusive. The index predates the audited head and the next affected
consumer without a current receipt is
`Code/GameEngine/Source/Common/AICowerState_onEnter.cpp`.

The CreateCrateDie dry run rejects the donor after a conflicting BitFlags
declaration. The RebuildHoleExposeDie dry run finds a missing constructor
declaration in one view and an object byte difference in another. The native
planner reports separate class-view reconciliation for both targets. These
checks leave the source layout intact.
