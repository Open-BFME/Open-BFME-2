// cl: /Ob0
//
// Ported from Open-BFME-1 GameEngine/Source/Common/Rva002687D0Eq.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?eq@Rva002687D0@@QBE_NH@Z 0x0049323D (20B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).

struct Rva002687D0Inner
{
	int m_00;
	int m_04;
	int m_08;
};

struct Rva002687D0Sub
{
	Rva002687D0Inner *m_holder;
};

class Rva002687D0
{
public:
	bool eq(int a) const;
};

bool Rva002687D0::eq(int a) const
{
	return ((const Rva002687D0Sub *)((const char *)this - 0x0C))->m_holder->m_08 == a;
}
