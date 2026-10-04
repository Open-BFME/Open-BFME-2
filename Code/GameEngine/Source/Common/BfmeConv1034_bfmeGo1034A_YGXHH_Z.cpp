// cl: /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Open-BFME5 conversions.

class BfmeSubA1034
{
public:
	void bfmeAdd1034(int b);
};

struct BfmeX1034
{
	char m_bfmePad[4];
	BfmeSubA1034 m_bfmeSub;
};

BfmeX1034 * __stdcall bfmeFind1034(int a, int n);

void __stdcall bfmeGo1034A(int a, int b)
{
	BfmeX1034 *x = bfmeFind1034(a, 0);

	if (x != 0)
		x->m_bfmeSub.bfmeAdd1034(b);
}
