# RankInfo.cpp TU merge: remaining donor blockers

Seat claude2, 2026-11-05. TU: Code/GameEngine/Source/GameLogic/System/RankInfo.cpp.
`tu_skeleton.py --merge ... --dry-run` still rejects three donors. Nothing was merged or committed
except name votes.

- RankInfoCtor.cpp (ctor 0x0020010B, operator=): the seed declares
  `class __declspec(novtable) RankInfo` because retail's dtor 0x00200236 stores no vptr (target fact,
  verified by removing novtable: the seed's dtor then emits a vptr store and fails). The ctor stores
  vftable 0xBE26E0, so it needs RankInfo without novtable. One TU cannot hold both views as they stand.
  This is the same shape as DominateEnemySpecialPowerModuleData's header blocker. Next step: find how
  retail's dtor loses the store (an inline/empty base dtor, or the dtor defined through a different class)
  before merging.
- RankInfoParse.cpp: built `/GX- /Oi-` and redefines operator new/delete through bfmealloc. Its EH
  flags conflict with the seed's, so it stays a separate unit until those flags are reconciled.
- Rva0022CA74Slot9.cpp (0x002000A4, 51 B, `?rva002000A4@RankInfoStore@@UAEXXZ`): it is the only
  feasible donor. Its private `RankInfoStore` view has a vptr only, while the seed's derives from
  SubsystemInterface. Vtable 0x00BE2704 slot 9 (+0x24) is SubsystemInterface::reset (structural
  inference, hint grade), and the body matches BFME1/ZH `RankInfoStore::reset`'s statement shape. ZH's
  compiled body is 134 B with no placement, and BFME1 has no EA evidence, so no canonical basis exists.
  The inferred vote `reset` and the reviewer's `purgeOverrides` disagree (pending in
  reverse/name_votes.csv). Once `reset` lands: declare `virtual void reset();` in the seed's
  RankInfoStore (which fills the runtime survey's __purecall slot 9), copy the seed's begin/end
  specializations into Slot9 verbatim, then merge.
