// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Open-BFME5 conversions.

class BfmeG1037
{
public:
	void bfmeDo1037(int b, bool c);
};

BfmeG1037 * __stdcall bfmeFind1037F(int a);

// WB 010C8450 saves the HordeContain receiver and forwards it to its
// module lookup. Retail caller 00473197 sets ECX=primary HordeContain.
// The retail provider never reads ECX, so its former donor free-function
// view reproduced the bytes but omitted the receiver setup in consumers.
// Native 00496EBC compares the final argument byte; WB010C8450 does
// byte loads too. The receiver-unused provider forwards this boolean home.
// Preserve the clean BF1 f98983a7d algorithm; no original name is established.
class HordeContain {
public:
 void rva00468E79(int a, int b, bool c);
};
void HordeContain::rva00468E79(int a, int b, bool c)
{
	BfmeG1037 *g = bfmeFind1037F(a);

	if (g != 0)
		g->bfmeDo1037(b, c);
}
