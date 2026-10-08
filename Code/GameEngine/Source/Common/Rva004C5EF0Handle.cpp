// cl: /DNDEBUG /MD /EHs-c-
//
// Ported from Open-BFME-1 GameEngine/Source/Common/Rva004C5EF0Handle.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?handle@Rva004C5EF0@@QAEXH@Z 0x0044BD5B (30B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).

// The callee is the rowed BfmeA1042N::bfmeGo1042D.
class BfmeA1042N
{
public:
	void bfmeGo1042D();
};

class BfmeSub939G
{
public:
	void bfmeCall939G();
	void *m_bfmeP;
};

class Rva004C5EF0
{
public:
	void handle(int msg);

	BfmeSub939G m_first;
	BfmeSub939G m_second;
};

void Rva004C5EF0::handle(int msg)
{
	if (msg == 2)
	{
		if (m_first.m_bfmeP)
			((BfmeA1042N *)&m_first)->bfmeGo1042D();
	}
	else if (msg == 3)
	{
		if (m_second.m_bfmeP)
			((BfmeA1042N *)&m_second)->bfmeGo1042D();
	}
}
