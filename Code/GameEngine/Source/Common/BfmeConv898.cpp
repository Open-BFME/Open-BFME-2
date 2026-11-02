// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Open-BFME5 conversions.
struct BfmeSubGE
{
	int m_bfmeA;
	int m_bfmeB;
	int m_bfmeC;
};

struct ScriptGroupLink;
struct BfmeNodeZK;

// LINK: 0x3B7DAC / 0x3B84C9 are rowed as ScriptList::takeGroups / takeScripts; bfmeOneGE / bfmeTwoGE
// were the address-derived spellings of those two calls on the same receiver.
#include "../../Include/GameLogic/ScriptList.h"

class Rva003B3ECBOwner
{
public:
	void rva003B3ECB();
};

class BfmeThingGE
{
public:
	void bfmeGoGE(BfmeSubGE *d);
	void rva003B40CB();
	void rva003B89A7(BfmeSubGE *d);
	int m_bfmeA;
	int m_bfmeB;
	int m_bfmeC;
	Rva003B3ECBOwner m_sub0C;
	char m_pad10[0x20 - sizeof(Rva003B3ECBOwner)];
	Rva003B3ECBOwner m_sub2C;
};

void BfmeThingGE::bfmeGoGE(BfmeSubGE *d)
{
	((ScriptList *)this)->takeGroups((ScriptList *)d, (ScriptGroupLink **)&d->m_bfmeB, (ScriptGroupLink **)&m_bfmeB);
	((ScriptList *)this)->takeScripts((ScriptList *)d, (BfmeNodeZK **)&d->m_bfmeC, (BfmeNodeZK **)&m_bfmeC);
}

void BfmeThingGE::rva003B40CB()
{
	m_sub0C.rva003B3ECB();
	m_sub2C.rva003B3ECB();
}

void BfmeThingGE::rva003B89A7(BfmeSubGE *d)
{
	reinterpret_cast<ScriptList *>(this)->swap(reinterpret_cast<ScriptList *>(d));
	rva003B40CB();
	bfmeGoGE(d);
}


