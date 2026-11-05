# TU approval: ResourceEntryOwner.cpp (0x004E7B0C..0x004E7F22), 2026-11-05

Served by `next_work.py` (TU approval, unanchored): 14 rows at 0x004E7B0C..0x004E7CB5
are `proposed` (K/C) in provisional TU `Code/GameEngine/Source/GameClient/ResourceEntryOwner.cpp`.
Nothing was changed. Evidence for the next seat:

Target facts
- 0x004E7E3A (`ResourceEntryOwner::rva004E7E3A`) builds a callback whose slot is
  0x004E81DE, which calls 0x004E7FCA `TerrainResourceClaimFeedback::Impl::updateClaimedDecalForClaimant`.
- Ctor 0x004E7D72: parent+0, int+4, AsciiString+8, list+0C, map+10, member+1C;
  0x004E7CEF decrements +4 and clears at <= 0.
- 0x004E7B0C / 0x004E7D16 / 0x004E7D1D / 0x004E7F22 load the object at +0 and forward
  (a pImpl outer class); 0x004E7B0C and 0x004E7D1D are reached from
  TerrainResourceClientBehavior slots 17/18 (create/removeSelectionFeedback).
- 0x004E7B13/7BAF/7BD8/7C52/7D29 (Rva004E7B13) and 0x004E7C1C/7C8A (Rva004E7C1C) are
  STLport map/list instantiations; symbols.csv already folds ClaimedDecal list
  erase/insert onto 0x004E7B6E/0x004E7B49.

Donor facts (WorldBuilder, hints only)
- wb_members.csv: `TerrainResourceClaimFeedback::Impl::m_showCount` at +4 (assert in Impl::show).
- wb_name_leads.csv: 0x004E7A85 -> `TerrainResourceClaimFeedback::Impl::show` (callgraph, 2.0);
  0x004E7FCA -> updateClaimedDecalForClaimant; both in `Gui/TerrainResourceClaimFeedback.cpp`.

Inference
- `ResourceEntryOwner` = `TerrainResourceClaimFeedback::Impl`; the retail TU is very likely
  `GameClient/GUI/TerrainResourceClaimFeedback.cpp` (0x004E7A85..0x004E81FE).

Why approval is not reachable by renaming alone
- No row in the range has F/Z/S (retail strips asserts; the class is BFME-only).
- W cannot anchor: both lead rows' names come from the lead (`wb_self`).
- `tu_map.demangle` matches only `?m@Class@@`; a nested `?m@Impl@TerrainResourceClaimFeedback@@`
  yields no class, so no N hint. Renaming ResourceEntryOwner to the real nested class removes
  the N rows that now hold 17 rows provisionally approved.
- Provisional approval through outer-class forwarders (`TerrainResourceClaimFeedback::show`, ...)
  would need their sources under `GameClient/GUI/` (N = dirname(source)/Class.cpp), and rows
  may move only into an already approved unit.

Next step: a tooling change (nested-class N hint keyed on the outer class, validated by
`tu_map.py --holdout`), then rename the forwarders and the Impl class together.
