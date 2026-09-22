// Single-function extraction from BFME1 BfmeConv678.cpp.
//
// Retail 0x00323DCE is BFME1's ?bfmeGoDEB (BfmeConv678.cpp) verbatim: find
// the DEB sub-object, return its color at +0xC8, else 0x00FFFFFF. Part of a
// five-body color-getter run (twin-rowed DEA at 0x00323D9D and GadgetSlider
// Enabled at 0x00323D86 alongside); the FindDEB call resolves through the
// existing ?bfmeFindDEB pin at 0x003140C8. BFME1 original at 0x004B6970.

struct BfmeSubDEB
{
	unsigned char m_bfmeHead[0xc8];
	unsigned int m_bfmeColor;
};

class BfmeThingDEB
{
public:
	BfmeSubDEB *bfmeFindDEB();
};

unsigned int bfmeGoDEB(BfmeThingDEB *a)
{
	BfmeSubDEB *s = a->bfmeFindDEB();
	if (s != 0)
		return s->m_bfmeColor;
	return 0x00FFFFFF;
}
