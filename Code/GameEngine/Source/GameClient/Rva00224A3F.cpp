// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?rva00224A3F@Rva00224A3F@@QAEXPAVINI@@@Z, retail 0x00224A3F, 76B: init-once
// BlockParse for AptButtonTooltipMap then INI::initFromINI. Evidence: leaf
// caller 0x00224E0A, callees INI::initFromINI rowed, globals g_00DFE6D8 and
// theAptButtonTooltipMapBlockParse from packet, flags /O1 /arch:SSE /G7.
#include "ascii_string.h"

struct FieldParse
{
	void *m_x00;
};

void rva00224A31();

struct BlockParse
{
	unsigned char m_pad00[0xC];
	FieldParse m_field;
	void (*m_func)();
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
};

extern BlockParse theAptButtonTooltipMapBlockParse;
extern int g_00DFE6D8;

class INI
{
public:
	void initFromINI(void *what, const FieldParse *parseTable);
};

class Rva00224A3F
{
public:
	void rva00224A3F(INI *ini);
};

void Rva00224A3F::rva00224A3F(INI *ini)
{
	if ((g_00DFE6D8 & 1) == 0)
	{
		g_00DFE6D8 |= 1;
		theAptButtonTooltipMapBlockParse.m_func = rva00224A31;
		theAptButtonTooltipMapBlockParse.m_14 = 0;
		theAptButtonTooltipMapBlockParse.m_18 = 0;
		theAptButtonTooltipMapBlockParse.m_1C = 0;
		theAptButtonTooltipMapBlockParse.m_20 = 0;
		theAptButtonTooltipMapBlockParse.m_24 = 0;
		theAptButtonTooltipMapBlockParse.m_28 = 0;
	}
	ini->initFromINI(this, &theAptButtonTooltipMapBlockParse.m_field);
}
