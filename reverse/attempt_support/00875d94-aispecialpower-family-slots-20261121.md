# 0x00875D94 / 0x00875E88: AISpecialPower family vtable bridges

Queue items `??_7Rva005D7531@@6B@` (0x00875D94) and `??_7Rva005D7C17@@6B@`
(0x00875E88) in `Code/GameEngine/Source/Common/Rva005D7D88Derived.cpp`. Neither
can retire by itself. About 40 bridged seven- and nine-slot tables between
0x00875AE0 and 0x00876494 share the same base chain, and that chain has to be
declared first.

## Target facts (retail bytes)

- Root table 0x0087091C, installed by ctor 0x0058AD4D (`Rva0058AD7A`,
  canonical header `Code/GameEngine/Include/Common/Rva0058AD7A.h`):
  [??_G 0x58AE36, 0x58AE53 (Xfer*, 99B), 0x58AD9F (9B), 0x910FB (folded),
  __purecall, 0x58AD81, __purecall].
- 0x58AD81 is rowed `?activate@AISpecialPower@@QAEXPAVObject@@@Z`, with a WB
  lead `AISpecialPower::` at that slot. So `Rva0058AD7A` is most likely
  `AISpecialPower`.
- Middle table 0x008786E8, installed by ctor 0x005EE2E6 (`Rva005EE30C`, not
  canonical): slots 0-6 = [??_G 0x5EE394, 0x58AE53, 0x58AD9F, 0x910FB,
  __purecall, 0x5EE2CF, __purecall]. Slot 5 overrides `activate`.
- Leaf tables (for example 0x00875EAC, `Rva005D7D88`, ctor 0x005D7D76) have
  slot 1 = 0x47A69C (ret 4), slot 4 = 0xB3FD0 (ret) and slot 6 = shouldActivate.
  0x00875D94 and 0x00875E88 derive from `Rva005D7D88` (ctors 0x005D751F and
  0x005D7C05 call 0x005D7D76) and override only slot 6: 0x5D75BE and 0x5D7C3E.

## Why it is blocked

- Slots 2, 3 and 5 belong to the base classes. Their rows carry opaque
  non-virtual names of other classes:
  - `?rva0058AD9F@Rva0058AD9F@@QAEHXZ` (VslotSmallBodiesAO.cpp)
  - `?rva0058AE53@Rva0058AE53@@QAEXPAVXfer@@@Z` (Rva00380200Getter.cpp)
  - `?activate@Rva005EE2CF@@QAEXPAVObject@@@Z` (VslotSmallBodiesT.cpp)
  - `?activate@AISpecialPower@@QAEXPAVObject@@@Z` (VslotSmallBodiesT.cpp)

  A private view cannot name them without a second real name on a named
  address. They need renames to virtual members of the real base classes.
- The root's canonical contract (`reverse/class_contracts/Rva0058AD7A.json`)
  declares only vslot 0, and its sizeof/vprobe typedefs are generated.
  Adding slots 1-6 is header-lane work.
- `rename.py class --fold Rva0058AD7A --into AISpecialPower` and
  `--merge-existing` were refused: the class is registered, so this needs a
  class-reconciliation commit. `canonical:wb` needs a
  `reverse/wb_name_leads.csv` row.
- `AISpellBookStructureBreaker` (canonical; its contract asserts no vptr) owns
  0x5D7D93, which is slot 6 of 0x00875EAC installed by 0x005D7D76. The
  AISpellBookBase.h notes tie that table to the spell-book object, so
  `Rva005D7D88` is probably `AISpellBookStructureBreaker`. Its no-vptr
  contract then conflicts with the retail table.

## Suggested order

1. Class reconciliation: `Rva0058AD7A` becomes `AISpecialPower`, and its
   contract gains vslots 1-6:
   - slot 1: xfer-like, Xfer*
   - slot 2: int()
   - slot 3: int(), folded 0x910FB
   - slot 4: pure
   - slot 5: activate(Object*)
   - slot 6: pure shouldActivate(Object*)
2. Rename the 0x58AE53, 0x58AD9F and 0x58AD81 rows to its virtuals, and add an
   ICF alias at 0x910FB. That retires 0x0087091C.
3. Make `Rva005EE30C` a canonical derived class with a slot-5 override
   (rename the 0x5EE2CF row).
4. For each leaf, declare the slot 1 and 4 overrides (ICF aliases at 0x47A69C
   and 0xB3FD0) and turn its slot-6 row into
   `?shouldActivate@<Leaf>@@UAE_NPAVObject@@@Z`, as
   AISpellBookEnshroudingMist and AISpellBookTreeKiller already are.
