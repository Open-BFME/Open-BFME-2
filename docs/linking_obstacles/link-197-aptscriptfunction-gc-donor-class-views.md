### LINK-197: AptScriptFunction GC donor needs compatible AptValue and receiver views

**2026-11-21 shared-root repair.** `AptScriptFunction.h` uses the registered
`AptValue.h` declaration. Its two consumers of the storage word now use `field04`.
Giving the Date factory's existing `-1` default a local name preserved the retail
register allocation that had blocked the previous header trial. All 386 function
rows and eight data rows match across 18 dependents, with 66 exact unwind graphs.
The 18-object link preview preserves 40,328 bytes at index `76a04dbe10`.

The commit hook's shadow warning for the deleting destructor at `0x006DE320`
also describes the prior object. Both objects emit the same 35 bytes, with the
same `+0x4` REL32 to `??1Rva006DE320@@UAE@XZ`. That implicit destructor and the
rowed `??1Rva006DE350@@UAE@XZ` emit identical 51-byte bodies and five identical
relocations in both versions, including the same base vtable. The existing
pin's identity classification remains open. The GC donor still needs its receiver
and base views reconciled before a donor merge can pass.

Integration also reports divergent `??0Rva006DE350@@QAE@XZ` definitions in
shadow. The integrated and trial `AptValue` objects are byte-identical. The
receipt-bound parent object emits the same nine-byte constructor, vtable,
and complete and deleting destructor graph with identical relocations. An older
cached cohort already contains the three-byte definitions from other units.
The scoped preview records the divergence without a live reference or loss
of linked bytes.

2026-11-17 recheck: AptValue.cpp passes 35/35 baseline rows; all seven
intermediate defaults in the November 16 handoff are now landed, and both
root headers already name slots 12/13 consistently. The shared-header
duplicate remains. Claims for AptActionInterpreter.cpp and its previously
failing _createObject body were refused, so no broad header experiment was
repeated and no source was changed. See
[current prerequisite recheck](../../reverse/attempt_support/aptvalue-bridge-recheck-20261117.md).

Status: Blocked. Updated: 2026-11-03; inspected revision: 7c99285f90.
Scope: AptObject/AptScriptFunction.cpp and Common/Rva00709C10Cluster.cpp, RVA 0x00709D80.
Completed: canonical AptValue adoption in the donor; owning acceptance retires one header-debt row, byte check passes, ordinary preview preserves LINKS 113 -> 113 bytes at index 8661f15284.
Remaining / next check: reconcile AptScriptFunction.h's private AptValue with the canonical header, then Rva00709B80's Rva006D6470Owner/Rva006D6360 base and method views; current tu_skeleton merge accepts no donor.
Clearance: donor header debt only; no merge, source-file reduction or census gain claimed.
Evidence: [scoped checks and rejected merge](../../reverse/attempt_support/apt-script-gc-donor-20261103-codex3/README.md).

**2026-11-11, APT destructor at 0x006D6470.** On `86d46df848`, the
0x006D6360 base constructor builds AptNativeHash at +8 and the derived
constructor 0x006D6410 sets flags at +0x1C. The destructor now uses that
same 0x14-byte hash and calls its destructor at 0x0070A840. All four rows
byte-match. Together with the constructor and hash provider the link
preview preserves 3,990 bytes (index `60189f9ced`). The bridge at RVA
0x008EA264 remains open. The class-fold dry run for Rva006D6470Owner into
AptObject refuses the third table name, Rva006DE6C0. Trace that name's
installer before retrying the fold or updating the shared virtual slots.
The unwind funclet at 0x007A8830 now calls AptValueGC's destructor at
0x006D6340; the normal path inlines its tail call to AptValue at 0x006DE350.
The four-unit preview including Rva006FBC90OwnerDtor.cpp retains 4,193 bytes.
A full AptValue-header trial in the destructor alone matches all four rows
but loses 127 linked bytes because the constructor still emits a short table.

Publication recovery: [upstream ID collision and correction](../../reverse/attempt_support/preparation-recovery-publication-20261104-codex3.md).
2026-11-04: the same shared-root conflict also blocks AptMiscObjects.cpp's AptCIH adoption; four other consumers now pass nine header acceptances and preserve their link previews ([evidence](../../reverse/attempt_support/aptcih-header-adoption-20261104.md)).
2026-11-04: shared-root reconciliation byte-matches 27/28 sources but AptActionInterpreter.cpp loses two rows to an esi/edi tie-break; reverted, next is removing that TU's private BfmeAptValue006DCD20 view ([evidence](../../reverse/attempt_support/aptvalue-root-reconcile-20261104.md)).
2026-11-04: Rva006FC1D0Ctor.cpp's AptValue adoption hits the same shared Rva006D6360 base: the vtable COMDAT is common to nine units and must be reconciled in all of them together ([evidence](../../reverse/attempt_support/aptvalue-header-adoption-20261104-claudec.md)).
2026-11-05: canonical AptValue.h now spells pure slots 12/13 `IsGarbageCollected`/`RegisterReferences` like AptScriptFunction.h (overriders and calls in 12 sources renamed; 95 dependents 1280/1280 matched); Rva006FBC90OwnerDtor.cpp's frame-stack vtable drops from 17 to retail's 15 slots and agrees with AptScriptFunction.cpp, which previews LINKS 0 -> 3,535. Still open: AptScriptFunction.h's private AptValue, and the slot-11/13 overriders rowed as `rva006FBC10`/`rva006FBC30` (retail 0x00CED880) need `DestroyGCPointers`/`RegisterReferences` names (inferred lane) before both views can name them.
