// cl: /Ob0
//
// Ported from Open-BFME-1 GameEngine/Source/Common/Rva002C56F0Copy.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?copy@Rva002C56F0@@QBEDPAURva002C56F0Vec@@@Z 0x004A6A44 (20B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).

struct Rva002C56F0Vec
{
	int x;
	int y;
	int z;
};

class Rva002C56F0
{
	char m_lead[0x0C];
	Rva002C56F0Vec m_pos;
	char m_18;

public:
	char copy(Rva002C56F0Vec *dst) const;
};

char Rva002C56F0::copy(Rva002C56F0Vec *dst) const
{
	*dst = m_pos;
	return m_18;
}
