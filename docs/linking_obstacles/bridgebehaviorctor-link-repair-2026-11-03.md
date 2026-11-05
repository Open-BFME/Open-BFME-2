### BridgeBehaviorCtor link repair (2026-11-03)

`BridgeBehaviorCtor.cpp` (196B) unresolved symbol `??_7BridgeBehavior@@6BMiBase1@@@` resolved:
Adopted the real multiple inheritance hierarchy matching `BridgeBehaviorDtor.cpp` (`UpdateModule`, `BridgeBehaviorInterface`, `DamageModuleInterface`, `DieModuleInterface`) and its virtual methods. This lets the compiler generate native vtable stores and emit/resolve matching secondary vtables, eliminating the unresolvable fake `MiBase1` extern, manual pointer stores, and the `_vtbl_00C40818` `/alternatename` hatch.
Verification: `build.sh` 3/3 functions and 1 data row matched; `link_check.py` LINKS 0 -> 196 bytes.


2026-11-05 follow-up. BridgeBehaviorDtor.cpp and five other units adopt the shared DieModuleInterface header with unchanged native object contents. The six strict provider receipts pass. The broader affected-consumer audit remains inconclusive, so carry this scope into the next scheduled census. [Published verification and remaining consumer evidence](../../reverse/attempt_support/diemoduleinterface-outgoing-link-audit-20261105-1425.md).
