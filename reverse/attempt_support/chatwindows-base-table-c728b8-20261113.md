# Bridged tables 0x00C6FFFC / 0x00C728B8 (chat-window base class): state and next steps (2026-11-13)

Served as vtable-bridge `??_7Rva005AFE3FBase@@6B@` in
Code/GameEngine/Source/GameClient/GUI/ChatWindowsInGame.cpp.

## Landed (d388d35e69)

- ed55387a83 retracted `??_GRva005AFEDBRecord@@QAEPAXI@Z` (a one-byte record destroyed through an
  explicit `_STL::_Destroy` instantiation) with a tombstone, and removed the record from the unit.
- 428d52a1ab rowed 0x005AFEDB as `??_GRva005AFE3F@@UAEPAXI@Z`, which the unit already emitted
  (add_match verified, 28 B). Unit 28/28 matched; link_check LINKS 1,873 -> 1,873.

## Target facts (game.dat words; names from functions.csv)

- 0x00C6FFFC, 2 slots: `__purecall` x2. The destructor 0x005AFE3F restores it inline; the
  constructor 0x005AFE86's unwind reaches 0x0057C03B, rowed `~CategoryModuleClass<0>`, which
  restores the same table (an ICF fold of the interface's own destructor).
- 0x00C728B8, 6 slots (stored by ctor 0x005AFE86 and dtor 0x005AFE3F): 0x005AFD89
  `?rva005AFD89@Rva005AFE86@@UAEXHPB...`, 0x005AFCEC `?rva005AFCEC@Rva005AFCEC@@QAEXH@Z`,
  0x005AFEDB `??_GRva005AFE3F`, `__purecall`, `__purecall`, 0x0047A69C (shared `ret 4`).
- Derived 0x00C75B2C (`??_7Rva005D583C`): same slots 0/1, own `??_G` 0x005D58A8, slot 3
  `__purecall`, slot 4 0x005D57EB, slot 5 0x005D5F86 `showPlayerTooltip@Rva005D5F86`.
  0x00C75B44 / 0x00C75B5C differ only in slot 3: `?PopulatePlayerList@ChatWindowsOnlineRoom@@UAE_NXZ`
  0x005D6AA4 / `...@ChatWindowsOnlineBuddy@@...` 0x005D6C94. So slot 3 is the pure
  PopulatePlayerList and slot 5 the tooltip hook; the class at 0x00C728B8 is their abstract base.
- Other derived tables by ledger name: 0x00C7287C (`Rva005AF9EF` / `Rva005AFA03`), 0x00C75AC4
  (`Rva005D5095Base` / `Rva005D50D8`); each is a ctor placeholder and a dtor placeholder.

Inference, not a target fact: constructor 0x005AFE86 zeroes through +0x20, so the class is 0x24
bytes; the dtor unit's 20-byte view is short.

## Why the fold does not go through yet

`rename.py class --fold Rva005AFE86 --into Rva005AFE3F --dry-run`: refused, ChatWindowsInGame.cpp
would declare the class twice (its `Rva005AFE86` view holds slot 0's method, its `Rva005AFE3F` view
the destructor). The prepared route needs both names' views to agree on layout before the fold, in
every unit: ChatWindowsInGame.cpp, Rva005AFE86Ctor.cpp (no vptr: a hand-stored `m_vtable` over an
empty base), Rva005D583CCtor.cpp (the same view plus three hand-written 6-slot arrays),
SingleBaseCtors.cpp and Rva005AFE3FDerived.cpp (destructor-only view).

## Order that follows

1. One layout for the class in those five units: an interface base with the two pure slots and an
   inline non-virtual destructor (twin row at 0x0057C03B with `fold-proof=`), then slots 0/1
   overrides, the virtual destructor, two pure slots, and an inline `ret 4` slot 5 (twin row at
   0x0047A69C). The ctor unit then stores the table the compiler emits instead of `m_vtable`.
   The class's table names resolve only after steps 2-3, so 1-3 are one push.
2. `class --fold Rva005AFE86 --into Rva005AFE3F` with the units prepared.
3. `function --to-class Rva005AFE3F --new rva005AFCEC` for 0x005AFCEC (VslotSmallBodiesAE.cpp).
4. The same for the derived pairs, then replace Rva005D583CCtor.cpp's hand-written arrays with
   compiled tables. `PopulatePlayerList` / `showPlayerTooltip` are already spelled on derived rows.

Not checked: any build of step 1; whether `--to-class` accepts 0x005AFCEC with eight tables holding
it; the real link.
