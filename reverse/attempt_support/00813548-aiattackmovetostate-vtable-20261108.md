# 0x813548 `??_7AIAttackMoveToState@@6B@` bridge retirement — handoff

Landed: `rename.py class --fold Rva00345CAB --into AIAttackMoveToState`
(dtor 0x345CAB, `??_G` 0x349FF5, xfer 0x340E97 now carry the real class).

Retail table (slot:RVA): 0:349ff5 1:b3fd0 2:345cfa 3:340e97 4:34ec7b 5:34a011
6:353c8b 7:33f2d7 8:47a699 9:340f25 10-13:47a699 14:50b5c6 15:47a699 16:b3fd0
17:3441f7. Base `AIInternalMoveToState` table 0x810DE8; intermediate
`Rva0034005D` (ctor 0x34005D, table 0x811EB8, adds bool +0x4C; slots 4-6 rowed
as `AIMoveToState`, so likely `AIMoveToState`).

Remaining prerequisites, in order:
1. Base fold `rename.py class --fold Rva0033FF2B --into AIInternalMoveToState`
   is refused until these units adopt `GameLogic/AIInternalMoveToState.h` (or are
   passed `--prepared`): Rva00340461Xfer.cpp, TailJumpWrappers5B.cpp,
   Rva00340D1FDtor.cpp, Rva0033FF2BDtor.cpp, Rva00340BDCDtor.cpp,
   TailJumpWrappers5B_~Rva002563CE.cpp, W3DAptComponentView3D.cpp, AIStates.cpp.
   AIAttackMoveStateMachine.cpp and AIStateRva0034005DCtor.cpp also hold private
   `AIInternalMoveToState` copies.
2. Slot 2 0x345CFA (`?name@Rva00345CFANamed@@QBEPBDXZ`) -> `--to-class
   AIAttackMoveToState` as `GetSnapshotName` (precedent 0x33F565 AIDockState).
3. Slot 9 0x340F25 (`?rva00340F25@AIAttackMoveToState@@UBE_NXZ`) must be renamed
   to override State's slot 9 (`_bfme_state_slot9() const`).
4. Slot 14 0x50B5C6 needs a return-true override admitted via the ICF twin route
   (`fold-proof=`).
5. Both emitting units (AIStates.cpp dtor, AIAttackMoveStateMachine.cpp ctor
   0x34EBE8) need full views deriving AIInternalMoveToState -> Rva0034005D ->
   AIAttackMoveToState with every override declared.
