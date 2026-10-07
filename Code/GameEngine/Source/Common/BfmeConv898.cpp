// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Open-BFME5 conversions.
struct BfmeSubGE
{
	int m_bfmeA;
	int m_bfmeB;
	int m_bfmeC;
};

class ScriptList
{
public:
	void swap(ScriptList *other);
};

class BfmeThingGE
{
public:
	void bfmeGoGE(BfmeSubGE *d);
	void bfmeOneGE(BfmeSubGE *d, int *x, int *y);
	void bfmeTwoGE(BfmeSubGE *d, int *x, int *y);
	void rva003B40CB();
	void rva003B89A7(BfmeSubGE *d);
	int m_bfmeA;
	int m_bfmeB;
	int m_bfmeC;
};

void BfmeThingGE::bfmeGoGE(BfmeSubGE *d)
{
	bfmeOneGE(d, &d->m_bfmeB, &m_bfmeB);
	bfmeTwoGE(d, &d->m_bfmeC, &m_bfmeC);
}

void BfmeThingGE::rva003B89A7(BfmeSubGE *d)
{
	reinterpret_cast<ScriptList *>(this)->swap(reinterpret_cast<ScriptList *>(d));
	rva003B40CB();
	bfmeGoGE(d);
}

