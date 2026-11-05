# Current consumer receipts and header verification prerequisites

Inspected revision `852317db9e51d8e7cc7e72f5841d11d0ba2f3471`. The current batch retires verified existing header keys.
The separate audit below rechecks the six DieModuleInterface sources from the previous
publication at the current revision. The six explicit provider receipt checks pass.

The explicit prepare-current check verifies 24/24 rows and records a reusable
receipt for 0CreateAHeroManager21FE49.cpp, the consumer missing in the previous audit.

Current scoped audit output

```text
link batch audit: INCONCLUSIVE baseline: index at 984a4cdc4d, outgoing base 852317db9e51d8e7cc7e72f5841d11d0ba2f3471; findings below are provisional since-index changes
link batch audit: INCONCLUSIVE: affected consumer lacks current receipt: Code/GameEngine/Source/Common/AIBaseBuilder.cpp
```

Carry the remaining affected-consumer scope into the next scheduled census.
The dated baseline and the current compiler inputs differ.

## Restored candidates

- `Code/GameEngine/Source/GameLogic/Object/Die/CreateObjectDie.cpp`. The complete native object comparison passes, but the owning acceptance refuses the dated link prediction. The original build verifies 39 functions and two data rows. Check the provider context with a fresh census before trying again.
- `Code/GameEngine/Source/Common/parseAutoResolveBodyDefinition.cpp`. The header also supplies the host and record family. The source documents that its private views preserve the native folded destructor calls. In the single-view trial, the Rva0041890FRecord reference fails to resolve (C3861). The restored build verifies four functions and one data row. Reconcile the whole family and its destructor bindings before retrying.

The previously blocked UpdateModuleInterface candidate was skipped before editing.

## Protected preparation scope

The DX8 device guard trial remained unpublished. The normal prepare-current tool
classifies its VP6-related path as protected. The candidate commit was dropped
from the outgoing series. The source and header key remain on their original state.

```text
link_check: protected decoder source cannot be prepared: Code/GameEngine/Source/Common/Rva007E3C20Vp6StreamDtor.cpp
```



## Scoped consumer recheck, 2026-11-05, second follow-up

Inspected revision `7dc4b67c8e26610c09218ebb9e47ccfab9a71afd`. The previously missing AIBaseBuilder.cpp
receipt now passes 27/27 function rows and one data row. The six previously
published DieModuleInterface units and the CreateAHero consumer together pass
76/76 function rows with current strict receipts.

The same-head audit of the six affected providers reports:

```text
link batch audit: INCONCLUSIVE baseline: index at 984a4cdc4d, outgoing base 7dc4b67c8e26610c09218ebb9e47ccfab9a71afd; findings below are provisional since-index changes
link batch audit: INCONCLUSIVE: affected consumer lacks current receipt: Code/GameEngine/Source/Common/AIBuildable.cpp
```

Carry AIBuildable.cpp and the rest of the affected consumer scope into the
next scheduled census. The older index still limits the closure verdict.
