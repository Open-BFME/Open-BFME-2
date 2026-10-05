// cl: /O1 /EHsc
//
// Retail 0x0002C621 (27B): ?bfmeMakePairEL@@YA?AUBfmePairEL@@ABVBfmeWordEL@@0@Z.
// Hidden-retptr __cdecl factory building the 8-byte BfmePairEL return buffer
// from two BfmeWordEL const refs. Retail is one EH-state init
// (and dword ptr [ebp-4],0) plus a single E8 to the shared two-StringBase
// pair ctor at 0x0002C4FD, then returns the hidden retbuf (leave; ret).
// Called twice from the rowed splitter
// ?Rva00194810@@YA?AUBfmePairEL@@ABVBfmeWordEL@@@Z at 0x0032ABDA
// (REL32 at 0x0032AC4D and 0x0032AC78, both decoding to 0x0002C621).
//
// BFME1 donor game/GameEngine/Source/Common/Bfme5TwoWordPairFactory.cpp
// (reference/open-bfme-1 @ 6583b3c1ff21db4a561285717028fdafc780b7db,
// verified fresh 2026-10-04T22:47:33Z) compiled /O1 /EHsc. BfmeWordEL takes
// the rowed split TU's 4-byte StringBase<char> view
// (Code/GameEngine/Source/GameLogic/Rva00194810Split_Rva0032abda.cpp,
// 0x0032ABDA 184B); BfmePairEL is two BfmeWordEL (8 bytes total).
// The donor defines the pair ctor inline; retail proves this factory
// forwards through the shared pair ctor instead (one E8, EH state stays 0
// in this frame), so the ctor is declared here and pinned to 0x0002C4FD in
// reverse/symbols.csv. Defining it here would inline two StringBase copies
// and lose the call. BfmeWordEL is layout-identical to StringBase<char>
// (single 4-byte payload, non-trivial copy), so the pinned body is the same
// bytes under the EL spelling, matching the existing
// ??0?$pair@VAsciiString@@V1@@ ICF-alias pin at that address.

// A four-byte view of the established word type. Member bodies are supplied by
// the existing splitter/string providers; this factory only calls the pair ctor.
// Keep the canonical StringBase template out of this TU rather than redeclaring it.
class BfmeWordEL
{
public:
    BfmeWordEL(const BfmeWordEL &other);
    BfmeWordEL(const BfmeWordEL &other, int start, int len);
    ~BfmeWordEL();
private:
    void *m_stringStorage;
};
typedef char BfmeWordELSizeCheck[sizeof(BfmeWordEL) == 4 ? 1 : -1];

struct BfmePairEL
{
	// Defined by the shared pair ctor at 0x0002C4FD (see header note);
	// declared here so the factory below encodes the same single call.
	BfmePairEL(const BfmeWordEL &firstValue, const BfmeWordEL &secondValue);

	BfmeWordEL first;
	BfmeWordEL second;
};

// ?bfmeMakePairEL@@YA?AUBfmePairEL@@ABVBfmeWordEL@@0@Z
BfmePairEL __cdecl bfmeMakePairEL(
	const BfmeWordEL &first,
	const BfmeWordEL &second)
{
	return BfmePairEL(first, second);
}
