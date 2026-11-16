# f8bb: native ObjectCreationList call sites

f8bb682906e removed the sole alias for
?bfmeDoBPB@BfmeSubBPB@@QAEXPAX00@Z. The actual-image blocker list published
by9bde27ffb56 names BfmeConv506.cpp and ObjectCreationUpgrade.cpp.

Both consumers now call the existing rowed three-argument
ObjectCreationList::create directly, using ObjectCreationListClass.h.
The target is0x001F08D3,87 bytes, in ObjectCreationListRva001F0878.cpp.
The old opaque BfmeSubBPB pointer spelling remains in existing row signatures;
its unused synthetic method declaration is removed. The this value, three
pointer arguments and call ABI are preserved. No wrapper body is introduced.

Private before/after verification:26/26 rows across both consumers; both own
link_check verdicts LINKS,1564 predicted bytes retained; zero newly undefined
vtable references; staged hatch check passes. Fresh srv1 cached verification
on the landed APT base repeats the26 rows, both own LINKS and slot check.
The index is the once-fetched02:02 census at1300d9f970; predictions alone do
not establish the current image. Raw COFF separately confirms the old
undefined name in both before objects, absent from both after objects, and
the actual rowed create name referenced by both after objects.

Source paths, rows, provider, class header, pins and hatch baseline stay
unchanged. No alias, pin, compiler switch, gate hatch or admission is added.
The two consumer references are repaired; full-image/runtime validation
remains pending. The unrelated four-argument bfmeDoBUC removal is outside
this two-source change.

Evidence: ~/bfme2-ops/swarm/sweeps/slotnames/red-bpb-verification/,
red-bpb-native-symbol-proof.json and bpb-final/. Independent Sol review
is required before publication.
