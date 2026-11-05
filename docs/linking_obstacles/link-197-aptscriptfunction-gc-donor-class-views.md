### LINK-197: AptScriptFunction GC donor needs compatible AptValue and receiver views

Status: Blocked. Updated: 2026-11-03; inspected revision: 7c99285f90.
Scope: AptObject/AptScriptFunction.cpp and Common/Rva00709C10Cluster.cpp, RVA 0x00709D80.
Completed: canonical AptValue adoption in the donor; owning acceptance retires one header-debt row, byte check passes, ordinary preview preserves LINKS 113 -> 113 bytes at index 8661f15284.
Remaining / next check: reconcile AptScriptFunction.h's private AptValue with the canonical header, then Rva00709B80's Rva006D6470Owner/Rva006D6360 base and method views; current tu_skeleton merge accepts no donor.
Clearance: donor header debt only; no merge, source-file reduction or census gain claimed.
Evidence: [scoped checks and rejected merge](../../reverse/attempt_support/apt-script-gc-donor-20261103-codex3/README.md).
Publication recovery: [upstream ID collision and correction](../../reverse/attempt_support/preparation-recovery-publication-20261104-codex3.md).
2026-11-04: the same shared-root conflict also blocks AptMiscObjects.cpp's AptCIH adoption; four other consumers now pass nine header acceptances and preserve their link previews ([evidence](../../reverse/attempt_support/aptcih-header-adoption-20261104.md)).
2026-11-04: shared-root reconciliation byte-matches 27/28 sources but AptActionInterpreter.cpp loses two rows to an esi/edi tie-break; reverted, next is removing that TU's private BfmeAptValue006DCD20 view ([evidence](../../reverse/attempt_support/aptvalue-root-reconcile-20261104.md)).
2026-11-04: Rva006FC1D0Ctor.cpp's AptValue adoption hits the same shared Rva006D6360 base: the vtable COMDAT is common to nine units and must be reconciled in all of them together ([evidence](../../reverse/attempt_support/aptvalue-header-adoption-20261104-claudec.md)).
2026-11-05: canonical AptValue.h now spells pure slots 12/13 `IsGarbageCollected`/`RegisterReferences` like AptScriptFunction.h (overriders and calls in 12 sources renamed; 95 dependents 1280/1280 matched); Rva006FBC90OwnerDtor.cpp's frame-stack vtable drops from 17 to retail's 15 slots and agrees with AptScriptFunction.cpp, which previews LINKS 0 -> 3,535. Still open: AptScriptFunction.h's private AptValue, and the slot-11/13 overriders rowed as `rva006FBC10`/`rva006FBC30` (retail 0x00CED880) need `DestroyGCPointers`/`RegisterReferences` names (inferred lane) before both views can name them.
