# Castle parser native base-table consumer

Target facts: table RVA 007C9574 has two entries, 000AD930 and 0003B810.
The latter is __purecall; the former is the deleting destructor. The derived
Rva00300419 table at 00807484 has entries 0041E6F3 and 00300481.
The existing consumer footprint does not establish the original full class.

Repair is limited to SidesListParseCastleTemplateMaps.cpp (parent 0032F84F,
its handler and seven unwind rows). It uses the same external-table restore
pattern as the existing constructor/provider. The inline destructor preserves
the token read before the vptr store, then unregisters that token.

Verification:
- Official build: 9/9; 439-byte parent, handler and seven unwind rows.
- EH: one EXACT graph, no missing object.
- Provider-inclusive scoped link preview: consumer plus
  System/BfmeDataChunkParserBinding.cpp and Rva003B241AForwarder.cpp,
  3/3 clean; providers 51/18 bytes unchanged, consumer 0 -> 447 bytes.
- New COMDAT variants, unmatched definitions and whitespace checks pass.
- COFF before/after: only removed definitions are the base ??_7 and ??_G;
  no added definitions; every shared external definition has unchanged raw
  section bytes. Both undefined base-slot symbols disappear. Native base-table
  relocations remain in the parent and cleanup. Neither object has CRT sections.
- Local evidence: build/decal-diagnostic/castle-parser-trial/{before,after}.obj
  and the saved baseline source. Census 0534e78db3 is stale; no global-link or
  menu/skirmish/selection success claimed.

Rebase disposition: upstream b902765169 supersedes this local trial with a
single pure base parser slot and derived override, retaining the ordinary
inline destructor and all nine rows. The rebased source contains that upstream
structural repair; the novtable/manual-store trial above is historical evidence.
Next: reverify the integrated consumers and measure the full population, then
test Windows menu, skirmish and selection.
