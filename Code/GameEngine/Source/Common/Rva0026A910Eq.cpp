// cl: /Ob0
//
// Ported from Open-BFME-1 GameEngine/Source/Common/Rva0026A910Eq.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?eq@Rva0026A910@@QBE_NH@Z 0x0058911A (20B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).

struct Rva0026A910Inner
{
	int m_00;
	int m_04;
	int m_08;
};

struct Rva0026A910Sub
{
	Rva0026A910Inner *m_holder;
};

class Rva0026A910
{
public:
	bool eq(int a) const;
};

bool Rva0026A910::eq(int a) const
{
	return ((const Rva0026A910Sub *)((const char *)this - 0x20))->m_holder->m_08 == a;
}
