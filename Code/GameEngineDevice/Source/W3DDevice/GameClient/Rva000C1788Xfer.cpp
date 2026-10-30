// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// stlport
//
// Renderable/water-area state snapshot, retail 0x000C1788 (347 B, EH, RET4).
// The +0x44 object supplies a string through vtable +0x18, a no-arg call at
// +0x50 and a 12-float block at +0x18; the +0x104 object (when set) supplies a
// string through +8 and the +0x108 scalar. The chain arg->+0x7C / node->+0x6C /
// Rva003062FEXfer / node->+0x6C / node->+0x70 serialises the pair through the
// StringBase temporaries.
#include <stl/_algobase.h>
#include "ascii_string.h"


class XferNode1
{
public:
	virtual void xfernode10();
	virtual void xfernode11();
	virtual const char *b02();
	virtual void xfernode13();
	virtual void xfernode14();
	virtual void xfernode15();
	virtual const char *b06();
	virtual void xfernode17();
	virtual void xfernode18();
	virtual void xfernode19();
	virtual void xfernode110();
	virtual void xfernode111();
	virtual void xfernode112();
	virtual void xfernode113();
	virtual void xfernode114();
	virtual void xfernode115();
	virtual void xfernode116();
	virtual void xfernode117();
	virtual void xfernode118();
	virtual void xfernode119();
	virtual void b20();
	virtual void xfernode121();
	virtual void xfernode122();
	virtual void xfernode123();
	virtual void xfernode124();
	virtual void xfernode125();
	virtual void xfernode126();
};


class Rva000BFDFE { public: void rva000C0386(); };

class Rva000C1788
{
public:
	void rva000C1788(void *xfer);
private:
	char m_pad00[0x44];
	XferNode1 *m_44;		// +0x44
	char m_pad48[0x104 - 0x48];
	XferNode1 *m_104;		// +0x104
	float m_108;			// +0x108
};

// The +0x6C/+0x70/+0x7C Xfer slots used here (AsciiString, Real, Int); each
// returns the Xfer for chaining.
class XferChain
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26();
	virtual XferChain *xferAsciiString(AsciiString *value);	// +0x6C
	virtual XferChain *xferReal(float *value);			// +0x70
	virtual void s29(); virtual void s30();
	virtual XferChain *xferInt(int *value);			// +0x7C
};
// Retail 0x003062FE (rowed Xfer *Rva003062FEXfer(Xfer *, float *)) returns
// the chained Xfer, and this caller continues the chain from it.
class Xfer;
Xfer *Rva003062FEXfer(Xfer *xfer, float *vals);

void Rva000C1788::rva000C1788(void *xfer)
{
	if (m_44 == 0)
		return;
	((Rva000BFDFE *)((char *)this - 0xc))->rva000C0386();
	int flag = 1;
	AsciiString s18(m_44->b06());
	XferNode1 *source = m_44;
	source->b20();
	float block[12];
	const float *srcf = (const float *)((char *)source + 0x18);
	block[0] = srcf[0]; block[1] = srcf[1]; block[2] = srcf[2]; block[3] = srcf[3];
	block[4] = srcf[4]; block[5] = srcf[5]; block[6] = srcf[6]; block[7] = srcf[7];
	block[8] = srcf[8]; block[9] = srcf[9]; block[10] = srcf[10]; block[11] = srcf[11];
	AsciiString s10;
	float value = 0.0f;
	if (m_104 != 0)
	{
		s10.set(m_104->b02());
		value = m_108;
	}
	((XferChain *)Rva003062FEXfer((Xfer *)((XferChain *)xfer)->xferInt(&flag)->xferAsciiString(&s18), block))
		->xferAsciiString(&s10)->xferReal(&value);
}
