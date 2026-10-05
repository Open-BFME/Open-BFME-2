// ??0Rva004E2382@@QAE@ABV0@@Z
// partial score=0.96 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD
// Target4E2C66..4E2CB9 copy83: native Construct4E2F27 feeds32B records.
// Default ctor4E2382 and dtor4E2941 establish the existing opaque owner.
// Native copy calls StringBase narrow copy365F0 at0 then copies word4,
// invokes a12B tree-prefix copy4E1FE4 at8 and a12B vector copy4E1D4E at14.
// The old default view's set<AsciiString>/BfmeE16 names are not asserted.
// Tree165 remains unrowed. Vector71 is a complete existing provider with
// an RVA-copy alias; neither provider name proves an original payload type.
#include "ascii_string.h"
class Rva004E1FE4TreeCopyView {
public: Rva004E1FE4TreeCopyView(const Rva004E1FE4TreeCopyView&);~Rva004E1FE4TreeCopyView();
private: unsigned char prefix[12];
};
class Rva004E1D4EVectorCopyView {
public: Rva004E1D4EVectorCopyView(const Rva004E1D4EVectorCopyView&);
private: unsigned char prefix[12];
};
class Rva004E2382 {
public: Rva004E2382(const Rva004E2382&);
private: AsciiString string00;int unknown04;Rva004E1FE4TreeCopyView tree08;Rva004E1D4EVectorCopyView vector14;
};
Rva004E2382::Rva004E2382(const Rva004E2382& other):string00(other.string00),unknown04(other.unknown04),tree08(other.tree08),vector14(other.vector14) {}
