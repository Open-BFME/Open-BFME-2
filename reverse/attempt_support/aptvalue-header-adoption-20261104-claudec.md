# AptValue header adoption, Apt action-queue/GC units (2026-11-04, claudec)

Accepted (header_adopt_lane.py accept PASS, 8 header-queue rows retired):
Rva006E2EE0AptCIH, Rva006E3230Validate, Rva006F6A50Cluster, Rva006F6E00Cluster,
Rva006FB120InputDispatch (direct include added; they already reached AptValue.h
through AptCIHClass.h), Rva006E34D0Mark, Rva006E3810FrontEnqueue,
Rva006E4FF0Cluster (private views replaced; slot calls renamed to AddRef,
Release and vslot13).

Not accepted: Code/Libraries/Source/Apt/Rva006FC1D0Ctor.cpp.

- Target facts: ctor 0x006FC1D0/0x006FC240 inline the Rva006D6360 base
  (ledger: ??0AptValueWithHash@@QAE@W4AptVirtualFunctionTable_Indices@@H@Z
  symbol at 0x006D6360), call 0x006DCCC0, and the state-0 unwind funclets
  uw_007aa290/uw_007aa298 call 0x006D6340 (??1BfmeAptValue006DCD20 /
  ??1AptValueGC gen-alias).
- Tried: drop the private `AptValue` and `BfmeAptValue006DCD20 : AptValue`
  views and base Rva006D6360 on canonical BfmeAptValue006DCD20.h (field04 at
  +4 keeps the layout). Bytes: 6/6 exact, funclets verified.
- Refused by link_check: LINKED 244 -> 0. ??_7Rva006D6360@@6B@ now names 12
  BfmeAptValue006DCD20 virtuals with no provider (AddRef, Release, ForceDelete,
  GetNativeHashVirtual, ContainsNativeHashVirtual, getHasClass, setHasClass,
  objectMemberLookup, objectMemberSet, vslot09, vslot10, DestroyGCPointers),
  and its COMDAT differs from the copy in Rva006D6360Ctor.cpp.
- Why the first adopt attempt failed (uw_007aa2a0): including AptValue.h under
  the private `BfmeAptValue006DCD20 : AptValue` view adds a second dword
  (field04 plus the private m_flags), shifting every later field by 4.
- Inference: Rva006D6360's vtable is a shared COMDAT across at least
  Rva006D6360Ctor.cpp, Rva006FC1D0Ctor.cpp, Rva006DA4D0Finish.cpp,
  AptTextFormat.cpp, AptCharacter.cpp, Rva00709C10Cluster.cpp,
  Rva006F1360Dtor.cpp, Rva006ECFC0Siblings.cpp and Rva00711380Cluster.cpp, all
  with the same private two-slot AptValue view. It must change in all of them
  at once, on an AptValue -> AptValueGC (0x006D6340 dtor) -> AptValueWithHash
  (0x006D6360) chain whose virtuals resolve to the rowed AptValue providers.
