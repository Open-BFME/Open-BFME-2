// cl: /Ob0
//
// Ported from Open-BFME-1 GameEngine/Source/Common/Rva000C8D80Copy.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?copy@Rva000C8D80@@QBEDPAURva000C8D80Vec@@@Z 0x002A98B6 (20B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).

struct Rva000C8D80Vec
{
	int x;
	int y;
	int z;
};

class Rva000C8D80
{
	char m_lead[0x34];
	Rva000C8D80Vec m_pos;
	char m_40;

public:
	char copy(Rva000C8D80Vec *dst) const;
};

char Rva000C8D80::copy(Rva000C8D80Vec *dst) const
{
	*dst = m_pos;
	return m_40;
}
