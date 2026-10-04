// cl: /O1
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/Common/Bfme5TinyFifteen.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// bfmeCopySecond 0x00309E6B (20B). Callee addresses are read off retail's call
// sites (reverse/symbols.csv). Only the placed bodies are carried; the donor's
// other definitions are omitted.
// Three more tiny ones: a product of two globals and an argument, a value two
// hops away with minus one as the fallback, and another table copied between
// two globals.

extern float g_bfmeFirstCF;					// retail 0x012B5628
extern float g_bfmeSecondCF;


class BfmeLinkCF
{
public:
	int m_bfmeTag;						// +0x00
	int m_bfmeNext;						// +0x04
};

class Gen_0028EF10
{
public:
	int bfmeValue(void) const;

private:
	char m_bfmeHead[0x8C];					// +0x00
	BfmeLinkCF *m_bfmeLink;					// +0x8C
};


extern "C" void * __cdecl memcpy(void *destination, const void *source, unsigned int bytes);

#pragma intrinsic(memcpy)

extern int g_bfmeSrcCF[22];					// retail 0x012B5100
extern int g_bfmeDstCF[22];					// retail 0x012B5158

// ?bfmeCopySecond@@YAXXZ
void __cdecl bfmeCopySecond(void)
{
	memcpy(g_bfmeDstCF, g_bfmeSrcCF, sizeof(g_bfmeDstCF));
}
