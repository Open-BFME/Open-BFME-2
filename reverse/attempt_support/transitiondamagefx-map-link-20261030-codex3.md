# TransitionDamageFX map-load cleanup provider

Base: `080799847f`, 2026-10-30. Source:
`Code/GameEngine/Source/GameLogic/Object/Damage/TransitionDamageFX_mapLoadPostProcess.cpp`.

The default picker served this unit's census COMDAT failure. Current ordinary
preview reproduced it: the unit's `_Vector_base<AsciiString>` destructor
differed from the first copy, retaining zero of its 339 authored bytes in that
preview. This is distinct from TransitionDamageFX.cpp's previously repaired
copy-constructor dependency in LINK-135.

The compiler-emitted eight-byte `Rva004BA1D0` destructor at `0x004BA1C8`
adds four to the receiver and jumps to the existing string-vector destructor
at `0x0002CC70`. Its own row and native callee verification establish that
binding. The local inline string-vector destructor was 57 bytes; the actual
rowed provider in `StlportAsciiStringVectorDtor.cpp` owns the complete 63-byte
body. A declaration-only specialization now uses that existing provider and
suppresses the local destructor and its buffer-cleanup dependencies. No names,
pins, ledger rows, flags or source paths change.

Checks:

- Normal build passes all five rows, the float reference and both parent-bound
  funclets. Frozen-source checks pass before and after. The parent's EH graph
  is EXACT 1, with no baseline exception.
- Strict preparation across this source, TransitionDamageFX.cpp and the existing
  string-vector destructor provider passes 36/36 rows with reusable receipts.
- All 13 retained external COMDAT name/digest/size records remain identical;
  neither the main body nor the eight-byte record destructor changes raw bytes.
  Thirteen cleanup COMDAT definitions disappear; none is added or changed.
  The string-vector destructor becomes the sole new undefined reference;
  releaseBuffer and imported free leave the undefined set. Weak bindings stay
  unchanged. Every removed name has other census copies, and this unit was
  first for none of them in the saved census order.
- Ordinary three-source preview reports 3/3 LINKS for 1,546 authored bytes
  (339 + 1,134 + 73), against index `6fe1089c24` (2026-10-30 04:25).
  These are preview results, not a new census gain.
- The staged-tree batch audit is INCONCLUSIVE (exit 2): the index predates
  the base and affected consumer `Common/AIBuildable.cpp` lacks a current
  receipt. Full consumer selection/loss verification remains open. Carry the
  repaired caller, destructor provider and affected consumers into the next
  scheduled census; no debt retirement or measured linking gain is claimed.

[Object comparison](transitiondamagefx-map-link-20261030-codex3.json).
Scratch objects and the local audit are under
`build/transitiondamagefx-map-link-20261030/`.
