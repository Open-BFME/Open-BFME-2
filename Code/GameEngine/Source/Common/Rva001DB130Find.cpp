// cl: /Ob0
//
// Ported from Open-BFME-1 GameEngine/Source/Common/Rva001DB130Find.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?find@Rva001DB130@@QAEPAURva001DB130Node@@H@Z 0x004DE549 (26B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).

struct Rva001DB130Node
{
	char pad[0x0C];
	int m_0C;
	Rva001DB130Node *m_10;
};

class Rva001DB130
{
	Rva001DB130Node *m_00;
	Rva001DB130Node *m_04;

public:
	Rva001DB130Node *find(int v);
};

Rva001DB130Node *Rva001DB130::find(int v)
{
	Rva001DB130Node *p = m_04;
	m_00 = p;
	if (!p)
		return 0;
	do
	{
		if (p->m_0C == v)
			return p;
		p = p->m_10;
	} while (p);
	return 0;
}
