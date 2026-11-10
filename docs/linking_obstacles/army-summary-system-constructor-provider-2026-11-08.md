# ArmySummarySystem constructor provider

Status: blocked on complete virtual surface (slots 1/2) and typed-vector/helper identity; slot-0 `/Oy-` deleting-destructor mismatch cleared pending real-link confirmation. Updated: 2026-11-10; inspected revision: 6df124bd9fc.

**2026-11-10 deleting-destructor alignment:** removed `/Oy-` from
`Code/GameEngine/Source/Common/Rva0040DB52Ctor.cpp`. The 98-byte constructor
`??0Rva0040DB52@@QAE@XZ` still matches (`8/8` matched across ctor/dtor/xfer,
`EH verify: 1 EXACT`, `0` new variants), and its compiler-emitted
`??_GRva0040DB52@@UAEPAXI@Z` is now the 28-byte `/O1` body (`0x60101020`), an
exact `vtable_bridge.comdat_body` byte-and-relocation twin of native owner
`Rva0040DB52Dtor.cpp` (`??_7Rva0040DB52@@6B@` `0x40301040` also twins `Dtor`).
Bounded 5-object `vtable_bridge.plan()` replay on `0x008394CC` over current
objects (`Rva0040DB52{Ctor,Dtor,Xfer}.cpp`, `coord2d.cpp`,
`ModuleNameGetters.cpp`) drops `refused_tables` `1 -> 0` and moves
`??_7Rva0040DB52@@6B@` to `bridged` (4 slots, `twin_target_slots=1`);
`link_check.py` over the 6-unit cohort (`Rva0040DB52*`,
`GameLogicDestructor.cpp`, `GameLogicInit.cpp`, `Rva00414932Dtor.cpp`) stays
`6/6 LINKS` (`29,724 -> 29,724` B). Remaining prerequisites: slot-1/2
non-pure virtuals (blocked on `ModuleNameGetters.cpp` hold / `Snapshot`
`loadPostProcess`), element-domain recovery for the two vectors, and next
real-link / census confirmation.

Rva0040DB52Ctor.cpp's 98-byte constructor passes normally. The table at
0x008394CC is named ArmySummarySystem by native getter 0x0040DBA3; this is
not the canonical ArmySummary class. As LINK-619 records, its /Oy- context
emits a 31-byte deleting destructor that precedes the 28-byte native owner
in Rva0040DB52Dtor.cpp. The constructor view also retains two pure slots
where native has the empty post-load callback and name getter.

A whole-file typed-vector trial is reverted: both byte and private link
checks reject it. The native 29-byte empty-base helper conflicts with the
known pointer-vector 15-byte helper, and new member typing changes scheduling.
Empty-vector construction/clear cannot establish element domain or stride.
Recover that evidence and reconcile helper identities before another type
trial; preserve the constructor's exact bytes and fix virtual/provider scope
together. No new flag hatch or abstract-destructor declaration is justified.

[Native boundary, retained row and rejected whole-file trial](../../reverse/attempt_support/army-summary-system-constructor-20261108/README.md).
