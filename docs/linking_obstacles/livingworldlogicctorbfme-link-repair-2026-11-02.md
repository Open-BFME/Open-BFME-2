### LivingWorldLogicCtorBfme link repair (2026-11-02)

`LivingWorldLogicCtorBfme.cpp` (815B) unresolved `?event5_2@LivingWorldLogic@@UAEXHHH@Z` resolved:
Dropped the undeclared/unrowed `virtual void event5_2(int,int,int);` declaration from the `LivingWorldLogic` class view so slot 2 of `LivingWorldPlayerObserver` binds the base inline default (identical to slot 0 `event5_0`), eliminating the unresolved reference while maintaining the exact 14-slot primary table.
Verification: `tools/build.py` 26/26 matched; `tools/link_check.py` LINKS 0 -> 815 bytes in `LivingWorldLogicCtorBfme.cpp` and preserves clean links in `LivingWorldLogicDtorRva002B964F.cpp` (717B), `LivingWorldLogic.cpp` (20,092B), `LivingWorldLogicPlayerObserverRva002BA3F2.cpp` (1,278B), `Common/LivingWorldLogic.cpp` (380B) and `OpaqueScalarDeletingDtorsB05.cpp` (748B), bringing total linked bytes across the cohort from 22,498 to 24,030 (+1,532 bytes).
