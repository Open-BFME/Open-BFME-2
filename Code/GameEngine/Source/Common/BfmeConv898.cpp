// cl: /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Open-BFME5 conversions.
struct BfmeSubGE
{
	int m_bfmeA;
	int m_bfmeB;
	int m_bfmeC;
};

class BfmeThingGE
{
public:
	void bfmeGoGE(BfmeSubGE *d);
	void bfmeOneGE(BfmeSubGE *d, int *x, int *y);
	void bfmeTwoGE(BfmeSubGE *d, int *x, int *y);
	int m_bfmeA;
	int m_bfmeB;
	int m_bfmeC;
};

void BfmeThingGE::bfmeGoGE(BfmeSubGE *d)
{
	bfmeOneGE(d, &d->m_bfmeB, &m_bfmeB);
	bfmeTwoGE(d, &d->m_bfmeC, &m_bfmeC);
}
