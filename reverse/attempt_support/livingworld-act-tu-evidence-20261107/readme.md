# LivingWorld campaign Act family: TU evidence (2026-11-07)

Merge lane 2 (seat5), for P16 / LINK-629, at the orchestrator's request.
Inspected revision: 2e872048cd. Nothing in the map, ledger or sources was changed.
The map figures below come from `tu_map.build()` over the current inputs, in memory.

Question: tu_map approves the EnableRegion record chain for LivingWorldCampaign.cpp on C alone:
- record copy ctor 0x0052BD3A
- `_Construct<Record>` 0x0052C2F3
- `__uninitialized_copy` 0x0052C8EF
- `vector<Record>` copy ctor 0x0052CAC9

The only code that reaches that chain is the campaign Act family, which has no approved TU. Does the
Act family belong to LivingWorldCampaign.cpp, to Glo012F1024Item.cpp, or to something else?

## Answer

The family splits in two.

1. **The 0x0052D3F1..0x0052D83B run is LivingWorldCampaign.cpp's object.** It holds the
   Act copy ctor 0x0052D555, its `??_G` 0x0052D6A2, `_Construct<Act>` 0x0052D6BE,
   `__uninitialized_copy`/`fill_n` 0x0052D6EB/0x0052D71A, `_M_insert_overflow` 0x0052D742,
   `push_back` 0x0052D801, the forwarder 0x0052D83B, and the member-vector copy helpers
   0x0052D3F1, 0x0052D417 and 0x0052D477..0x0052D4F5.
   They are COMDATs that LivingWorldCampaign.cpp emits through a LivingWorldCampaign member at
   0x0052D83B, which pushes an Act into the campaign's act vector. The record chain's C approval
   for LivingWorldCampaign.cpp is therefore right: LivingWorldCampaign.obj emits it, through the
   Act copy ctor.
2. **The parser 0x00566D83 belongs to the Act class's own unit, not LivingWorldCampaign.cpp.**
   So do the Act ctor `(const AsciiString &)` 0x00566BF6 and the Act forwarder 0x00566D7B. That unit
   is the object spanning roughly 0x0056552C..0x00566E6B, which tu_map currently groups under the
   provisional name Glo012F1024Item.cpp; its real file name is unproven. The K proposal that puts
   the Act copy ctor 0x0052D555 and its `??_G` there is class grouping only, and tu_map's own
   implicit-copy rule says an implicit copy ctor is emitted wherever a copy is made.

## Target facts (retail bytes and tables)

All addresses are RVAs (image base 0x00400000).

- LivingWorldCampaign's field table is at 0x008688A8.
  `LivingWorldCampaign::parseLivingWorldCampaignBlock` 0x0052D04E (N-approved) uses it:
  `push 0x50; call` (allocate), calls the LivingWorldCampaign ctor 0x0052CF0F, then pushes the
  table and calls initFromINI 0x0002DE78. Its entries are:
  - `AddPlayer`: parse 0x002E1D22 (ParseLivingWorldPlayer)
  - `LocalPlayer`: +0x30
  - `Act`: parse 0x00566D83 (ParseLivingWorldCampaignAct)
  - `SecondsPerReinforcement`: +0x38 (the ctor stores 0xB4)
  - `IsScriptedCampaign`: +0x4C (the ctor clears the byte)
- The parser 0x00566D83:
  - builds an Act on the stack with the Act ctor (AsciiString) 0x00566BF6;
  - parses its fields with initFromINI 0x0002DE78;
  - calls 0x0052D83B with `ecx = [ebp+0x0C]`, the FieldParse instance, which is the LivingWorldCampaign;
  - destroys the Act with 0x0056616B.
- 0x0052D83B (8 B) is `add ecx,0x0C` and a jump to `push_back` 0x0052D801: a `void C::f(const Act &)`
  that pushes into a vector at `this+0x0C`. The parser calls it out of line. Its only caller is the parser.
- LivingWorldCampaign+0x0C is a vector of 0xB8-byte polymorphic elements:
  - the ctor 0x0052CF0F builds a vector at +0x0C (call 0x00211E58);
  - the dtor 0x0052CFB1 destroys it with 0x0052CA2D, which runs the range destroyer
    0x0052C24E -> 0x0052BCE7, a stride-0xB8 loop that calls vslot 0.
- `vector<Act>`'s elements are the same 0xB8 polymorphic objects:
  - `push_back` 0x0052D801 adds 0xB8; `_M_insert_overflow` 0x0052D742 divides by 0xB8;
  - its `_M_clear` is the ICF body 0x0052CAAB, which runs the same 0x0052C24E.
- Call chain from the table to the record:
  table `Act` -> 0x00566D83 -> 0x0052D83B -> `push_back` 0x0052D801 -> `_Construct` 0x0052D6BE
  -> Act copy ctor 0x0052D555 -> `vector<Record>` copy ctor 0x0052CAC9 -> 0x0052C8EF -> 0x0052C2F3
  -> 0x0052BD3A. Every caller of the forwarder, `push_back`, `_Construct<Act>` and the Act copy ctor lies
  in this chain (`callers_of.py`). The copy ctor's only caller is 0x0052D6BE, and the forwarder's is the parser.
- The Act copy ctor 0x0052D555 also calls the member-vector copy ctors 0x0052CB65, 0x0052CBC5,
  0x0052CC64, 0x0052C823, 0x0052CD81, 0x0052C867, 0x0052C8AB, 0x0052CE20 and 0x0052CE7D.
  All of them are already C-approved for LivingWorldCampaign.cpp.
- The Act unit's own templates stay beside it at 0x00565...0x00566...:
  `vector<Record>::push_back` 0x0056625E and `_M_insert_overflow` 0x00565ACB,
  `vector<Element>::_M_insert_overflow` 0x005665AC, and `vector<Rva004E32F2>::push_back` 0x00566BB4.
  Where they need a helper that the forwarder chain also uses, they call the 0x0052D... copy
  (0x005665AC -> 0x0052D3F1; 0x00566ACA -> 0x0052D4CF and 0x0052D4A2).
- The same pattern is already approved for the players. ParseLivingWorldPlayer 0x002E1D22 calls
  `LivingWorldCampaign::AddPlayer` 0x0052D394 (N-approved). AddPlayer's `push_back` chain
  (0x0052D116, 0x0052D31E) sits just before it and is C-approved.
- `tu_evidence.py --source` emits no signal for Rva0052D83B.cpp, LivingWorldCampaignAct.cpp,
  Rva0056616BCopyDeferred.cpp or Rva0052D6BE.cpp.

## Structural inference

- The MSVC linker keeps the copy of a COMDAT from the first object in link order that defines it,
  inside that object's contribution.
- The out-of-line forwarder and its whole `vector<Act>` chain sit between LivingWorldCampaign's
  last anchored row (AddPlayer 0x0052D394) and the next object, the PathfindCell rows at 0x0052D84C
  (S=AIPathfind.cpp, displaced; W=Pathfinder). So LivingWorldCampaign.obj defined them.
- The forwarder's `this` is the LivingWorldCampaign (the table and the +0x0C vector above). It is
  therefore a LivingWorldCampaign member defined in LivingWorldCampaign.cpp, the Act counterpart of
  AddPlayer.
- The parser is ~0x39000 bytes away, beside the Act's own non-inline ctor, so it is another object.

## What would make tu_map approve it (measured in memory, nothing written)

The only change needed is to respell 0x0052D83B from its placeholder class onto LivingWorldCampaign
(`?rva0052D83B@LivingWorldCampaign@@QAEXABURva0052D801Record@@@Z`; the identifier still needs a name).
The rebuilt map then changes 63 rows:

- **Gained:**
  - 14 code rows 0x0052D3F1..0x0052D83B become approved for LivingWorldCampaign.cpp (13 by C between
    0x0052D394 and 0x0052D83B; 0x0052D83B by U through its `Common/LivingWorldCampaign.cpp` N hint).
    That includes 0x0052D555, 0x0052D6A2, and 0x0052D477, which was K-proposed for SpawnArmy.cpp.
  - 4 funclets become newly approved (P).
  - 17 funclets of 0x0052D555 (0x00797244..0x007972F2) move from Glo012F1024Item.cpp to
    LivingWorldCampaign.cpp (P).
- **Lost:**
  - Class Rva0056616B now votes for two TUs, so the Act ctor 0x00566BF6 loses its only placement,
    the K proposal.
  - With it go 10 proposed C rows (0x00566A42..0x00566BEB) and 18 funclets of 0x00566BF6
    (0x00799F62..0x0079A010). Those funclets are approved today only as `p-group provisional`,
    which inherits a K-proposed parent.
- Supported route:
  - `rename.py function --respell` with an inferred basis (a naming approval), touching
    Rva0052D83B.cpp and the parser's declaration in LivingWorldCampaignAct.cpp.
  - `--to-class` (vftable slots only), `class --fold` (needs installing special members) and
    `canonical:iniblock` (block parse callbacks only) do not apply.

## Not established

- The real file name of the Act unit (Glo012F1024Item.cpp is a provisional hint) and anchors for
  0x00566BF6..0x00566E6B. The rows below them (0x00566E6C, Script_objectTypesFromParam) are a
  different object with no TU.
- The forwarder's identifier. No retail or donor string names it; "addAct" would be an inferred name
  and needs the naming lane.
- The 9-byte getter 0x0052D843 (`cmp [ecx+0x38],0`; +0x38 is SecondsPerReinforcement) is probably an
  inline LivingWorldCampaign getter, but nothing places it.
