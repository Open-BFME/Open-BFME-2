// cl: /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Open-BFME5 conversions.

class BfmeG1037
{
public:
	void bfmeDo1037(int b, int c);
};

BfmeG1037 * __stdcall bfmeFind1037F(int a);

void __stdcall bfmeGo1037F(int a, int b, int c)
{
	BfmeG1037 *g = bfmeFind1037F(a);

	if (g != 0)
		g->bfmeDo1037(b, c);
}
