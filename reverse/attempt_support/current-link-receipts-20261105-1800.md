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


## AICowerState and repaired-blocker recheck at 899300899b

AICowerState_onEnter.cpp now has a strict reusable receipt for its matched
157-byte onEnter body. The same six sources were submitted to the current
native audit at `899300899b8f2538979f86c7578ac9cb17360682`.

```text
link batch audit: INCONCLUSIVE baseline: index at f44cbcf5b0, outgoing base 899300899b8f2538979f86c7578ac9cb17360682; findings below are provisional since-index changes
link batch audit: INCONCLUSIVE: 5 source object(s) lack current receipts; first: Code/GameEngine/Source/Common/VslotSmallBodiesE.cpp
```

Census prediction for two repaired entries from the earlier real-link list.

```text
Code/GameEngine/Source/GameClient/GameClient.cpp: LINKS  LINKED 5 -> 5 bytes (census 2026-11-05 15:19 at f44cbcf5b0; file's own bytes 5)
Code/GameEngine/Source/GameLogic/Object/Damage/BoneFXDamage.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-05 15:19 at f44cbcf5b0; file's own bytes 322)
link_check: 1 of 2 link cleanly; LINKED 5 -> 5 bytes (5.4s)
```

The six audit sources, BoneFXDamage.cpp and its two provider files then passed the current preparation gate, 70 of 70 matched functions with strict reusable receipts. The previous census-only BoneFXDamage result uses the older object definitions. The refreshed cohort audit now reaches a different affected consumer.

```text
link batch audit: INCONCLUSIVE baseline: index at f44cbcf5b0, outgoing base 178ff71e7505a42ebce54fd99bf7ab222e6c4c34; findings below are provisional since-index changes
link batch audit: INCONCLUSIVE: affected consumer lacks current receipt: Code/GameEngine/Source/Common/AIBaseBuilder.cpp
```
