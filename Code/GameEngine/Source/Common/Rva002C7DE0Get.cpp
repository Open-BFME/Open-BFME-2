// cl: /Ob0
//
// Ported from Open-BFME-1 GameEngine/Source/Common/Rva002C7DE0Get.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?get@Rva002C7DE0@@QAEEPAURva002C7DE0Blk@@@Z 0x004A9BB7 (26B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).

struct Rva002C7DE0Blk
{
	int a;
	int b;
	int c;
};

class Rva002C7DE0
{
	char pad[0xC0];
	Rva002C7DE0Blk m_C0;
	unsigned char m_CC;

public:
	unsigned char get(Rva002C7DE0Blk *out);
};

unsigned char Rva002C7DE0::get(Rva002C7DE0Blk *out)
{
	*out = m_C0;
	return m_CC;
}
