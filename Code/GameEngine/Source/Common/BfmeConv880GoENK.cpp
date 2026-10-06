// cl: /DNDEBUG /MD
// Retail RVA 0x00324992, 21 bytes.
// bfmeGoENK, the ENK sub-object byte setter.
// Ported from Open-BFME-1 BfmeConv880.cpp; the set byte is m_bfmeC at +0x11
// of the ENK sub-object fetched through bfmeGetENK (folded getter alias at
// 0x005C4ACD, same slot as the other bfmeGet/bfmeFind pins). Dedicated TU;
// the TU defines only this body.

typedef int Int;
typedef bool Bool;
typedef short Short;

struct BfmeSubENK
{
	unsigned char m_bfmeHead[0x11];
	char m_bfmeC;
};

class BfmeObjENK
{
public:
	BfmeSubENK *bfmeGetENK();
};

void bfmeGoENK(BfmeObjENK *o, char v)
{
	if (o)
	{
		BfmeSubENK *s = o->bfmeGetENK();
		s->m_bfmeC = v;
	}
}
