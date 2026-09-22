// Single-function extraction from BFME1 BfmeConv679.cpp.
//
// Retail 0x00323E02 is BFME1's ?bfmeGoDEC (BfmeConv679.cpp) verbatim: find
// the DEC sub-object, return its color at +0x134, else 0x00FFFFFF. Part of
// the color-getter run (DEA/DEB/GadgetSlider siblings alongside); the
// FindDEC call resolves through the existing ?bfmeFindDEC pin at 0x003140C8.
// BFME1 original at 0x004B69B0.

struct BfmeSubDEC
{
	unsigned char m_bfmeHead[0x134];
	unsigned int m_bfmeColor;
};

class BfmeThingDEC
{
public:
	BfmeSubDEC *bfmeFindDEC();
};

unsigned int bfmeGoDEC(BfmeThingDEC *a)
{
	BfmeSubDEC *s = a->bfmeFindDEC();
	if (s != 0)
		return s->m_bfmeColor;
	return 0x00FFFFFF;
}
