# Parser-binding base slots: pure virtual fix

Landed 2026-11-17 in `319ea79cd8` (on `e92cd90588`): declared
`BfmeParserBindingBaseVE::bfmeSlot0` and `bfmeSlot1` pure in the ten
constructor units that emit the base table, plus the shared provider
`Code/GameEngine/Source/Common/System/BfmeDataChunkParserBinding.cpp`.
The base table now holds retail's `__purecall` slots instead of unresolved
`?bfmeSlot0` / `?bfmeSlot1`, while the derived `BfmeParserBindingVE` keeps
its real overrides. All 11 units remain byte-identical and `link_check`
now reports each linked, with preview gains of roughly 8.7 KB.

## Remaining family members

These were tried with the same two-line change and reverted:

- `Code/GameEngine/Source/GameClient/MapUtilLoadMap.cpp` — compile failure:
  the unit instantiates `Rva00300419 positions(...)` on the stack, so pure
  base slots make that derived class abstract. Needs concrete overrides (real
  slot bodies) or a local concrete base, not a pure declaration.
- `Code/GameEngine/Source/GameLogic/Map/SidesListParseCastleTemplateMaps.cpp`
  — builds, but `link_check` rejects the COMDAT first copy of
  `??_7BfmeParserBindingBaseVE@@6B@`: this unit's inline-destructor class view
  emits a different table from the first copy in link order. Still fails after
  `link_check.py --update-index` at `319ea79cd8`.
- `Code/GameEngine/Source/GameLogic/Map/SidesList.cpp` — same COMDAT first-copy
  rejection (checked before the index refresh; likely the same class-view
  issue).
- `Code/GameEngine/Source/GameLogic/Map/SidesListDataChunks.cpp` — data rows
  fail: this unit's hand-built/expected vtable data row no longer matches the
  pure-slot table.
- `Code/GameEngineDevice/Source/W3DDevice/GameClient/WorldHeightMapParse.cpp`
  — data rows fail for the same vtable-data reason.

## Next step

One canonical `BfmeParserBindingBaseVE` header with a single out-of-line
destructor and one table view, adopted across the family, would let the
remaining units use the same table. That is header/class reconciliation work;
until then, keep the pure declarations only in the constructor-only units
where the build and link both pass.

## Resolution: the base table is two slots (2026-11-18)

Retail's base table at `0x007C9574` is 8 bytes: `{??_G (0x004AD930, ICF with
??_GDataChunkParser), __purecall (0x0043B810)}`; `0x007C957C` already starts
`Rva000ABD56`'s table. The data ledger also gives 8 bytes for every derived
table (`Rva00300419` 0x00807484, `BfmeParserBindingVE` 0x007C9584,
`Rva000AEF42` 0x007C95D0, `Rva003085FB` 0x00807EE8, `Rva003B3417` 0x0081F400).
So the family is a virtual destructor plus one parse slot; the
inline-destructor views declared three (dtor, `bfmeSlot0`, `bfmeSlot1`).

The four units whose views emit `??_7BfmeParserBindingBaseVE@@6B@`
(WorldHeightMapParse, MapUtilLoadMap, SidesListParseCastleTemplateMaps,
SidesListDataChunks) now drop `bfmeSlot0`, make `bfmeSlot1` pure, and declare
`bfmeSlot1` on each derived class so stack-built objects stay concrete. All
four emit the same 8-byte table, 153/153 functions match, and `link_check` of
the four together links three (was one); SidesListDataChunks still fails only
on its pre-existing `?getCharAt@?$StringBase@D@@QBEDH@Z` selection. The
novtable units, where `bfmeSlot0` stands for the dtor slot, are unchanged.
