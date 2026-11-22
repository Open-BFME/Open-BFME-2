# Rva007F1DE0 / Q3Make FESL request family: five bridged primary tables

Inspected on 2026-11-22 at `bc69d386995` after `next_work.py --claim` served the
link-cycle bridge `??_7Rva007F1DE0Object@@6BRva007F1DE0BaseA@@@` (0x008E23AC) in
`Code/GameEngine/Source/GameNetwork/Rva007F1DE0DerivedCtors.cpp`. No source was changed.

## Findings (target facts)

- `Rva007F1DE0DerivedCtors.cpp` emits five classes (ctors 0x0065E910, 0x0065F170,
  0x0065FA60, 0x00667330, 0x00668650) whose primary tables declare one slot,
  `primary()`, bound by five `/alternatename` hatches to the slot-0 deleting
  destructors (`??_GGen007F2120`, `Gen007F2E30`, `Gen007F33E0`, `Gen007FBAF0`,
  `Gen007F1BF0`, all in `Code/Libraries/Source/DirtySock/Y2ScalarDeleters.cpp`).
- `Code/GameEngine/Source/Common/Q3MakeDerivedFamily.cpp` emits the same five retail
  tables (0x008E23AC, 0x008E25A8, 0x008E2768, 0x008E3538, 0x008E3788) under other
  class names (`Rva0065EC70Object`, `Rva007F2E60Object`, `Rva007F3410Object`,
  `Rva007FBB20Object`, `Rva007FCF80Object`; bases `Q3MakeBaseA/B`). Each pair is one
  retail class: e.g. ctor 0x0065E910 and factory 0x0065EC70 (`new`) both install
  0x008E23AC. The two units hold private duplicate copies of the same hierarchy.
- The tables have 5, 13, 6, 26 and 25 slots (75 targets). Slot 0 is always the
  deleting destructor; the other targets are rowed matched, mostly as non-virtual
  members or free `__stdcall` functions of placeholder classes in 28 files (table
  below). Several are `YG` free functions taking the message object first; a
  `__thiscall` virtual that never reads `ecx` has the same bytes, so the ledger
  spellings do not prove the original declarations.

## Why blocked

Retiring the bridge needs the slot bodies declared as the virtuals of one class per
table: (a) unify each duplicate class pair behind one shared declaration (canonical
header) used by both units, (b) respell each slot row with `rename.py` as a virtual
member of that class, and (c) move each row only into its approved unit in a fresh
`tu_map.csv`. A second name on the existing rows would be a pin or alias hatch. This
is multi-session structural work across 28 files, not a single repair.

## Suggested order

1. Smallest table first (0x008E23AC, 5 slots): unify `Rva007F1DE0Object` with
   `Rva0065EC70Object` behind one header, declare slots 1-4, respell rows 0x00656A30,
   0x0065E9C0, 0x0065EA80 and 0x0065E930 as its virtuals (check each body's use of
   `ecx` against `__thiscall`), and drop that table's `/alternatename`.
2. Repeat per table. 0x00656A30 sits in seven tables (VA 0x00CE107C family), so it
   belongs to a common base, not to one derived class.

## Slot owners (from reverse/vtable_bridge_queue.tsv)

### ??_7Rva007F1DE0Object@@6BRva007F1DE0BaseA@@@ at 0x008E23AC (5 slots)

| Slot | Retail RVA | Ledger owner (file) |
|---|---|---|
| 0 | 0x0065EC40 | `??_GGen007F2120@@UAEPAXI@Z` (Y2ScalarDeleters.cpp) |
| 1 | 0x00656A30 | `?rva00656A30@Rva00656A30@@QAEHXZ` (VslotSmallBodiesAH.cpp) |
| 2 | 0x0065E9C0 | `?lookup@Rva007F1EA0@@QAEPAURva007E9A50Entry@@PAVRva007E8810Message@@@Z` (Rva007E9A50Lookups.cpp) |
| 3 | 0x0065EA80 | `?buildRequest@Rva007F1F60Feedback@@QAEXPAVRva007E8810Message@@HPBURva007F2010TargetId@@H_JPBDHPBURva007F2080ChatLog@@H3@Z` (V2FeslFeedbackRequest.cpp) |
| 4 | 0x0065E930 | `?bfmeGoVJF@@YGXPAVBfmeMsgVJF@@PAUFeslUserId@@H@Z` (BfmeConv1384.cpp) |

### ??_7Rva007F2680Object@@6BRva007F1DE0BaseA@@@ at 0x008E25A8 (13 slots)

| Slot | Retail RVA | Ledger owner (file) |
|---|---|---|
| 0 | 0x0065F910 | `??_GGen007F2E30@@UAEPAXI@Z` (Y2ScalarDeleters.cpp) |
| 1 | 0x00656A30 | `?rva00656A30@Rva00656A30@@QAEHXZ` (VslotSmallBodiesAH.cpp) |
| 2 | 0x0065F850 | `?lookup@Rva007F2D70@@QAEPAURva007E9A50Entry@@PAVRva007E8810Message@@@Z` (Rva007E9A50Lookups.cpp) |
| 3 | 0x0065F190 | `?bfmeSetupPair_007F26A0@@YGXPAUBfmeSetupRecord@@H@Z` (Bfme5SetupPairs.cpp) |
| 4 | 0x0065F1D0 | `?bfmeSetupPair_0065F1D0@@YGXPAUBfmeSetupRecord@@H@Z` (Bfme5SetupPairs.cpp) |
| 5 | 0x0065F210 | `?bfmeSetupPair_0065F210@@YGXPAUBfmeSetupRecord@@H@Z` (Bfme5SetupPairs.cpp) |
| 6 | 0x0065F250 | `?bfmeGoVIU@@YGXPAVFeslMessage@@PAX11@Z` (BfmeConv1378.cpp) |
| 7 | 0x0065F2B0 | `?buildRva007F27C0@@YGXPAVRva007E8810Message@@PBDPBURankUser@@H@Z` (Rva007F2350StatsCursor.cpp) |
| 8 | 0x0065F4E0 | `?bfmeGoVIR@BfmeThingVIR@@QAEXPAVBfmeMsgVIR@@PBUBfmeOwnerVIR@@PBQBDHHH@Z` (BfmeConv1377.cpp) |
| 9 | 0x0065F600 | `?bfmeGoVIS@BfmeThingVIS@@QAEXPAVBfmeMsgVIR@@PBUBfmeOwnerVIR@@PBQBDHHH@Z` (BfmeConv1377.cpp) |
| 10 | 0x0065F660 | `?Rva007F2B70@@YGXPAVRva007E8810Message@@PBDHHHHH@Z` (V2FeslTxnRequests.cpp) |
| 11 | 0x0065F700 | `?rva007F2C10Serialize@@YGXPAURva007F2C10Msg@@HHHHHHPAHH@Z` (Rva007F2C10RankSerialize.cpp) |
| 12 | 0x0065F800 | `?Rva007F2D10@@YGXPAVRva007E8810Message@@PBDH@Z` (V2FeslTxnRequests.cpp) |

### ??_7Rva007F2F80Object@@6BRva007F1DE0BaseA@@@ at 0x008E2768 (6 slots)

| Slot | Retail RVA | Ledger owner (file) |
|---|---|---|
| 0 | 0x0065FEB0 | `??_GGen007F33E0@@UAEPAXI@Z` (Y2ScalarDeleters.cpp) |
| 1 | 0x00656A30 | `?rva00656A30@Rva00656A30@@QAEHXZ` (VslotSmallBodiesAH.cpp) |
| 2 | 0x0065FDF0 | `?lookup@Rva007F3320@@QAEPAURva007E9A50Entry@@PAVRva007E8810Message@@@Z` (Rva007E9A50Lookups.cpp) |
| 3 | 0x0065FA80 | `?Rva007F2FA0@@YGXPAVRva007E8810Message@@PBURva007F2FA0Owner@@PBDPBURva007F2FA0Value@@IH@Z` (Rva007F2FA0RecordRequest.cpp) |
| 4 | 0x0065FBD0 | `?Rva007F30F0@@YGXPAVRva007E8810Message@@PBURva007F30F0Owner@@PBD@Z` (V2FeslTxnRequests.cpp) |
| 5 | 0x0065FC50 | `?Rva007F3170@@YGXPAVRva007E8810Message@@PBURva007F3170Owner@@PBDPBURva007F3170Value@@IHPBQBDI@Z` (Rva007F3170RecordRequest.cpp) |

### ??_7Rva007FAE20Object@@6BRva007F1DE0BaseA@@@ at 0x008E3538 (26 slots)

| Slot | Retail RVA | Ledger owner (file) |
|---|---|---|
| 0 | 0x00668000 | `??_GGen007FBAF0@@UAEPAXI@Z` (Y2ScalarDeleters.cpp) |
| 1 | 0x00667FB0 | `?rva00667FB0@Rva00667FB0@@QAEHXZ` (GapBodiesSeat5B.cpp) |
| 2 | 0x00667FC0 | `?findEntry@Rva007FBAB0Codec@@UAEPAURva007FCF10Entry@@PAURva007FCF10Message@@@Z` (Rva007FCF10DescriptorLookups.cpp) |
| 3 | 0x006673F0 | `?Rva007FAEE0@@YGXPAVRva007E8810Message@@PBD11111@Z` (Y4FeslBuddyRequests3.cpp) |
| 4 | 0x00667350 | `?Rva007FAE40@@YGXPAVRva007E8810Message@@PBD1111@Z` (Y4FeslBuddyRequests3.cpp) |
| 5 | 0x006674A0 | `?Rva007FAF90@@YGXPAVRva007E8810Message@@@Z` (Y4FeslSimpleRequests.cpp) |
| 6 | 0x006674C0 | `?Rva007FAFB0@@YGXPAVRva007E8810Message@@PBD11_NH@Z` (Y4FeslBuddyRequests3.cpp) |
| 7 | 0x00667590 | `?Rva007FB080@@YGXPAVRva007E8810Message@@PBD@Z` (Y4FeslBuddyRequests.cpp) |
| 8 | 0x006675C0 | `?Rva007FB0B0@@YGXPAVRva007E8810Message@@PBD@Z` (Y4FeslBuddyRequests.cpp) |
| 9 | 0x006675F0 | `?Rva007FB0E0@@YGXPAVRva007E8810Message@@PBDH11H1111@Z` (Y4FeslPresenceRequest.cpp) |
| 10 | 0x00667770 | `?Rva007FB260@@YGXPAVRva007E8810Message@@HPBD11_NH@Z` (Y4FeslBuddyRequests2.cpp) |
| 11 | 0x006678A0 | `?Rva007FB390@@YGXPAVRva007E8810Message@@PBD11_N@Z` (Y4FeslBuddyRequests.cpp) |
| 12 | 0x00667920 | `?Rva007FB410@@YGXPAVRva007E8810Message@@PBDH_N@Z` (Y4FeslBuddyRequests2.cpp) |
| 13 | 0x006679C0 | `?Rva007FB4B0@@YGXPAVRva007E8810Message@@PBD11@Z` (Y4FeslBuddyRequests.cpp) |
| 14 | 0x00667A20 | `?Rva007FB510@@YGXPAVRva007E8810Message@@PBD@Z` (Y4FeslBuddyRequests.cpp) |
| 15 | 0x00667A60 | `?Rva007FB550@@YGXPAVRva007E8810Message@@HPBD11_N@Z` (Y4FeslBuddyRequests.cpp) |
| 16 | 0x00667B30 | `?Rva007FB620@@YGXPAVRva007E8810Message@@PBD11_N@Z` (Y4FeslBuddyRequests3.cpp) |
| 17 | 0x00667BE0 | `?Rva007FB6D0@@YGXPAVRva007E8810Message@@HPBD1_N2@Z` (Y4FeslBuddyRequests2.cpp) |
| 18 | 0x00667CC0 | `?Rva007FB7B0@@YGXPAVRva007E8810Message@@PBD11@Z` (Y4FeslBuddyRequests.cpp) |
| 19 | 0x00667D20 | `?Rva007FB810@@YGXPAVRva007E8810Message@@PBDH@Z` (Y4FeslBuddyRequests2.cpp) |
| 20 | 0x00667DA0 | `?Rva007FB890@@YGXPAVRva007E8810Message@@PBD1@Z` (Y4FeslBuddyRequests.cpp) |
| 21 | 0x00667DE0 | `?Rva007FB8D0@@YGXPAVRva007E8810Message@@HPBD11H@Z` (Y4FeslBuddyRequests2.cpp) |
| 22 | 0x00667E70 | `?Rva007FB960@@YGXPAVRva007E8810Message@@HPBD11H@Z` (Y4FeslBuddyRequests2.cpp) |
| 23 | 0x00667F00 | `?Rva007FB9F0@@YGXPAVRva007E8810Message@@PBD_N@Z` (Y4FeslBuddyRequests.cpp) |
| 24 | 0x00667F60 | `?Rva007FBA50@@YGXPAVRva007E8810Message@@@Z` (Y4FeslSimpleRequests.cpp) |
| 25 | 0x00667F80 | `?Rva007FBA70@@YGXPAVRva007E8810Message@@PAXH@Z` (Y4FeslSimpleRequests.cpp) |

### ??_7Rva007FC150Object@@6BRva007F1DE0BaseA@@@ at 0x008E3788 (25 slots)

| Slot | Retail RVA | Ledger owner (file) |
|---|---|---|
| 0 | 0x00669450 | `??_GGen007F1BF0@@UAEPAXI@Z` (Y2ScalarDeleters.cpp) |
| 1 | 0x00669400 | `?rva00669400@Rva00669400@@QAEHXZ` (VslotSmallBodiesAN.cpp) |
| 2 | 0x00669410 | `?rva00669410@Rva00669410@@QAEPAURva00669410Entry@@PBURva00669410Arg@@@Z` (VslotSmallBodiesQ.cpp) |
| 3 | 0x00668670 | `?Rva007FC170@@YGXPAVRva007E8810Message@@PBD111@Z` (Y4FeslBuddyRequests.cpp) |
| 4 | 0x00668710 | `?Rva007FC210@@YGXPAVRva007E8810Message@@PBD11@Z` (Y4FeslBuddyRequests.cpp) |
| 5 | 0x00668770 | `?Rva007FC270@@YGXPAVRva007E8810Message@@@Z` (Y4FeslSimpleRequests.cpp) |
| 6 | 0x00668790 | `?Rva007FC290@@YGXPAVRva007E8810Message@@_N11HPBUFeslAttributeFilter@@IPBD333@Z` (Y4FeslGameListRequest.cpp) |
| 7 | 0x006688B0 | `?Rva007FC3B0@@YGXPAVRva007E8810Message@@H_N11HPBUFeslAttributeFilter@@IPBD3HH33@Z` (Y4FeslGameListRequest.cpp) |
| 8 | 0x00668A10 | `?Rva007FC510@@YGXPAVRva007E8810Message@@HH@Z` (Y4FeslBuddyRequests.cpp) |
| 9 | 0x00668A50 | `?Rva007FC550@@YGXPAVRva007E8810Message@@HH_NPBDHH2PBURva007FC550Attribute@@IPBURva007FC550Reservation@@IH22@Z` (Rva007FC550Request.cpp) |
| 10 | 0x00668D10 | `?Rva007FC810@@YGXPAVRva007E8810Message@@PBDPBURva007FC810Attribute@@HH@Z` (Y4FeslAttributeRequest.cpp) |
| 11 | 0x00668DF0 | `?Rva007FC8F0@@YGXPAVRva007E8810Message@@PBURva007FC810Attribute@@H@Z` (Y4FeslAttributeRequests.cpp) |
| 12 | 0x00668E90 | `?Rva007FC990@@YGXPAVRva007E8810Message@@HPBURva007FC810Attribute@@H@Z` (Y4FeslAttributeRequestPid.cpp) |
| 13 | 0x00668F40 | `?Rva007FCA40@@YGXPAVRva007E8810Message@@_N@Z` (Y4FeslBuddyRequests.cpp) |
| 14 | 0x00668F70 | `?Rva007FCA70@@YGXPAVRva007E8810Message@@HHH@Z` (Y4FeslBuddyRequests.cpp) |
| 15 | 0x00668FD0 | `?Rva007FCAD0@@YGXPAVRva007E8810Message@@HH@Z` (Y4FeslBuddyRequests.cpp) |
| 16 | 0x00669010 | `?Rva007FCB10@@YGXPAVRva007E8810Message@@_NHH@Z` (Y4FeslAttributeRequests.cpp) |
| 17 | 0x006690A0 | `?Rva007FCBA0@@YGXPAVRva007E8810Message@@HPBURva007FC810Attribute@@H@Z` (Y4FeslAttributeRequestPid.cpp) |
| 18 | 0x00669150 | `?Rva007FCC50@@YGXPAVRva007E8810Message@@H@Z` (Y4FeslBuddyRequests.cpp) |
| 19 | 0x00669180 | `?Rva007FCC80@@YGXPAVRva007E8810Message@@@Z` (Y4FeslSimpleRequests.cpp) |
| 20 | 0x006691A0 | `?Rva007FCCA0@@YGXPAVRva007E8810Message@@@Z` (Y4FeslSimpleRequests.cpp) |
| 21 | 0x006691C0 | `?Rva007FCCC0@@YGXPAVRva007E8810Message@@HHHHPBD@Z` (Y4FeslAttributeRequests.cpp) |
| 22 | 0x006692A0 | `?Rva007FCDA0ReserveRequest@@YGXPAVRva007E8810Message@@PB_JIHH@Z` (Rva007FCDA0ReserveRequest.cpp) |
| 23 | 0x00669370 | `?Rva007FCE70@@YGXPAVRva007E8810Message@@H@Z` (Y4FeslBuddyRequests.cpp) |
| 24 | 0x006693A0 | `?Rva007FCEA0@@YGXPAVRva007E8810Message@@PBD1H@Z` (Y4FeslBuddyRequests.cpp) |

Owner files: {'Code/Libraries/Source/DirtySock/Y2ScalarDeleters.cpp': 5, 'Code/GameEngine/Source/Common/VslotSmallBodiesAH.cpp': 3, 'Code/GameEngine/Source/Common/Rva007E9A50Lookups.cpp': 3, 'Code/GameEngine/Source/GameNetwork/V2FeslFeedbackRequest.cpp': 1, 'Code/GameEngine/Source/Common/BfmeConv1384.cpp': 1, 'Code/GameEngine/Source/Common/Bfme5SetupPairs.cpp': 3, 'Code/GameEngine/Source/Common/BfmeConv1378.cpp': 1, 'Code/GameEngine/Source/GameNetwork/Rva007F2350StatsCursor.cpp': 1, 'Code/GameEngine/Source/Common/BfmeConv1377.cpp': 2, 'Code/GameEngine/Source/GameNetwork/V2FeslTxnRequests.cpp': 3, 'Code/GameEngine/Source/Common/Rva007F2C10RankSerialize.cpp': 1, 'Code/GameEngine/Source/GameNetwork/Rva007F2FA0RecordRequest.cpp': 1, 'Code/GameEngine/Source/GameNetwork/Rva007F3170RecordRequest.cpp': 1, 'Code/GameEngine/Source/Common/GapBodiesSeat5B.cpp': 1, 'Code/GameEngine/Source/GameNetwork/Rva007FCF10DescriptorLookups.cpp': 1, 'Code/GameEngine/Source/GameNetwork/Y4FeslBuddyRequests3.cpp': 4, 'Code/GameEngine/Source/GameNetwork/Y4FeslSimpleRequests.cpp': 6, 'Code/GameEngine/Source/GameNetwork/Y4FeslBuddyRequests.cpp': 18, 'Code/GameEngine/Source/GameNetwork/Y4FeslPresenceRequest.cpp': 1, 'Code/GameEngine/Source/GameNetwork/Y4FeslBuddyRequests2.cpp': 6, 'Code/GameEngine/Source/Common/VslotSmallBodiesAN.cpp': 1, 'Code/GameEngine/Source/Common/VslotSmallBodiesQ.cpp': 1, 'Code/GameEngine/Source/GameNetwork/Y4FeslGameListRequest.cpp': 2, 'Code/GameEngine/Source/GameNetwork/Rva007FC550Request.cpp': 1, 'Code/GameEngine/Source/GameNetwork/Y4FeslAttributeRequest.cpp': 1, 'Code/GameEngine/Source/GameNetwork/Y4FeslAttributeRequests.cpp': 3, 'Code/GameEngine/Source/GameNetwork/Y4FeslAttributeRequestPid.cpp': 2, 'Code/GameEngine/Source/GameNetwork/Rva007FCDA0ReserveRequest.cpp': 1}
