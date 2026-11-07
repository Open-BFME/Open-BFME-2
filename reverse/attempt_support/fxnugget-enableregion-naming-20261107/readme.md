# FXNugget and EnableRegion record: naming evidence (held for the canonical-class rename tool)

Static-defects lane, 2026-11-07, base 61cf52f345. Two class identities the P16 FXList.cpp merge
(LINK-629, fxlist-cpp-unit-link-prerequisites-2026-10-31) needs named. No naming route covers them
today:
- `name_lane.py next` serves no key for a class with several definers.
- `rename.py class` refuses a class registered in reverse/canonical_classes.csv.

The Bridge-removal lane (seat6) is building the supported rename and reconcile. This file holds the
evidence for it. Target facts, donor facts and structural inferences are kept apart (AGENTS.md).

## 1. `Rva001DFEAABase` → `FXNugget` (registered: Code/GameEngine/Include/GameClient/Rva001DFEAABase.h)

Target facts (retail, RVAs):
- The ctor 0x001DFEAA stores the primary vftable VA 0x00BDC940. The dtor 0x001DFA48 stores the same table.
- Every FX nugget class (Sound, RayEffect, LightPulse, ViewShake, TerrainScorch, ParticleSystem,
  FXListAtBonePos and the rest) derives from it. Their ctors call 0x001DFEAA, then store their own type id
  at +4. For example, ParticleSystemFXNugget's ctor 0x001E0AEF stores 8.
- All 15 FX nugget parse callbacks (e.g. ParticleSystemFXNugget::parse 0x001E264F, call at +0x6A) append
  the new nugget through the list push_back at 0x0005548F. reverse/symbols.csv names that body
  `?push_back@?$list@PAVFXNugget@@V?$allocator@PAVFXNugget@@@_STL@@@_STL@@QAEXABQAVFXNugget@@@Z`
  ("FXList::addFXNugget append called by all 15 FX nugget parse callbacks").
- The row `?addFXNugget@FXList@@QAEXPAVFXNugget@@@Z` 0x0037D097 (FXListNuggetParse.cpp) takes `FXNugget *`.
- FXList::clear 0x001E11A6 walks the same list<FXNugget *> at FXList+4.

Donor facts:
- Zero Hour GeneralsMD `Code/GameEngine/Include/GameClient/FXList.h` line 73: `class FXNugget : public
  MemoryPoolObject`, the base of every FX nugget, held by FXList as `std::list<FXNugget*>`. BFME 1 keeps the
  name (the nugget ctor donors cite it).

Structural inference:
- The class whose ctor is 0x001DFEAA is the element type of FXList's nugget list. So it is FXList's
  `FXNugget`, and `Rva001DFEAABase` is a placeholder for it.
- Measured consequence (scratch, LINK-629): a unit spelling the list element `Rva001DFEAABase *` does not
  resolve the push_back callee. Spelled `FXNugget *`, it does (parse 0x001E264F: 124/124 bytes otherwise
  identical).

Member +4 (`m_04` in the canonical header; the donors spell it `m_nuggetType`):
- Target fact: each nugget ctor stores a per-class constant at +4 after the base ctor (ParticleSystem 8).
- Donor fact: BFME 1's FXNugget names the per-class nugget type field `m_nuggetType` (cited by the BFME 2
  ctor donors, e.g. ParticleSystemFXNuggetCtor.cpp: "nugget type 8").
- Effect: header_adopt_lane refuses every nugget-ctor adoption on this field ("m_nuggetType ... is not proven
  a member of Rva001DFEAABase"), so the member name unblocks A2 (8 donors).

## 2. The EnableRegion record (copy ctor 0x0052BD3A, vtable VA 0x00C61A20)

Target facts:
- 0x0052BD3A (31 B): `mov esi,ecx; mov [esi],0x00C61A20; lea ecx,[esi+4]; push src+4; call 0x000365F0
  (StringBase<char> copy ctor); mov eax,esi; ret 4`. That is the implicit copy ctor of an 8-byte
  `{vptr, AsciiString}` class: it copies every member, and here that is only the string.
- The vtable at 0x00C61A20 has one slot, `??_GRva004E156B` 0x004E1BC4, around the ICF-shared dtor 0x004E156B.
- The string "ParseEnableRegion::Invalid data passed in." follows the vtable at VA 0x00C61A24.
- Only caller of 0x0052BD3A: 0x0052C30F in the STLport _Construct 0x0052C2F3, which the vector growth path
  0x00565ACB uses.
- tu_map approves 0x0052BD3A for LivingWorldCampaign.cpp (C=0x0052BBF3..0x0052BD59).

Source fact (tree):
- SpawnArmy.cpp's ParseEnableRegion builds `Rva003B7BA0Record` (virtual dtor plus `AsciiString m_name`;
  FieldParse `Region` at +4, table at RVA 0x00861A50) and pushes it through the thunk 0x00566527, whose
  `FXList` spelling it calls "a callable view, not this record's identity".

Misnamed rows to respell onto the record class (re_attempts.log, identity-suspect, 2026-11-07):
- `??0FXList@@QAE@ABV0@@Z` 0x0052BD3A (FXList.cpp)
- `??$_Construct@VFXList@@V1@@_STL@@YAXPAVFXList@@ABV1@@Z` 0x0052C2F3 (stlport_construct_game_structs.cpp)
- `?_M_insert_overflow@?$vector@VFXList@@...` 0x00565ACB (FXListVectorInsertOverflow.cpp)

Name: no retail or donor string names the class. The parser's keyword is "Region" and its error string says
EnableRegion. A real name needs blind agreement. Until then the respell can target the existing placeholder
`Rva003B7BA0Record`. Respelling 0x0052BD3A leaves FXList.cpp with only the two STLport hashtable rows
(Harness lane) as blocking foreign rows.
