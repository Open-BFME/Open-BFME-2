# BoneFXDamage shared-contract repair verification

Inspected tree: `05fbaef1d02d3d58454585285ae160cac29781c0`, 2026-11-05.
No BoneFXDamage or provider source was changed in this verification pass.

`./build.sh Code/GameEngine/Source/GameLogic/Object/Damage/BoneFXDamage.cpp`
passes all 9/9 rows, three string references, and both renumbered funclets
through their parent EH data. `find_declared_unmatched.py` reports all defined
functions matched.

The downloaded index is the 2026-11-05 15:19 census at `f44cbcf5b0`.
An ordinary `link_check.py` still lists the old missing BoneFXDamage destructor
and DamageModule loadPostProcess/xfer providers. This snapshot is not evidence
that the later repairs failed.

The required current-provider check was:

```text
python3 tools/link_check.py --refresh Code/GameEngine/Source/GameLogic/Object/Damage/BoneFXDamage.cpp
Object store: 1339 of 3145 stale TU(s) restored
link_check: recompiled 3,145 stale ledger object(s) and replaced their census definitions
link_check: replaced the census definitions of 32 object(s) rebuilt since the census
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngine/Source/GameLogic/Object/Damage/BoneFXDamage.cpp: LINKS  LINKED 0 -> 322 bytes (census 2026-11-05 15:19 at f44cbcf5b0; file's own bytes 322)
link_check: 1 of 1 link cleanly; LINKED 0 -> 322 bytes (381.3s)
```

Refresh updates providers in memory for that invocation; it does not publish a
new index. An ordinary invocation after the runner's rebase still reports the
same three old missing names. The BoneFXDamage, DamageModule and destructor
provider sources are unchanged between the inspected tree and `87dc2a12bc`.

Scope of clearance: LINK-113's imported Snapshot-contract/missing-provider
obstacle in BoneFXDamage.cpp, in the current-provider preview. This confirms
the existing repairs recorded in the GameLogic/GameNetwork blocker handoff.
It claims neither a new real link nor census gains nor complete vtable/data
identity recovery. The getModuleNameKey placeholder and other previously
recorded table identity work remain outside this clearance.
