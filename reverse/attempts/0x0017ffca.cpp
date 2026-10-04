// ??1Rva0017FFCA@@UAE@XZ
// partial score=1.0 date=2026-10-05
// cl: /O1 /MD /EHsc
// Banked byte-exact destructor body, not a linkable class reconstruction.
// Target: Ghidra17FFCA/89, deleting-dtor call180111, BD4F50 slot9;
// ctor17FF77 proves owned pointer+14/name+18/arguments+1C,+20.
// Rowed loader18012A establishes the HLOD catalog relation and HLodDef use.
// Base cleanup61ED80, owned HLodDef cleanup1A03C0, String release610A40.
// This minimal virtual view does NOT recover native's14-slot interface: its
// sole deleting-dtor slot conflicts with native slot9 and must be reconciled
// with the existing opaque deleting-dtor/constructor/catalog views before use.
// Native evidence proves offsets/calls; no original class name is asserted.
// Omitting the old invented EmptyBase removes the previous100-vs89 codegen wall.
class Rva009EB810TailBase {
public: virtual ~Rva009EB810TailBase();
private: unsigned char unknown04[0x10];
};
class StringClass {
public: ~StringClass() { Free_String(); }
private: void Free_String(); char *buffer;
};
class HLodDefClass { public: ~HLodDefClass(); };
class Rva0017FFCA : public Rva009EB810TailBase {
public: virtual ~Rva0017FFCA();
private: HLodDefClass *definition; StringClass name; int word1c,word20;
};
Rva0017FFCA::~Rva0017FFCA() { delete definition; }
