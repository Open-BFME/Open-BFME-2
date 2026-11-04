// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?rva00224A3F@Rva00224A3F@@QAEXPAVINI@@@Z, retail 0x00224A3F, 76B: init-once
// BlockParse for AptButtonTooltipMap then INI::initFromINI. Evidence: leaf
// caller 0x00224E0A, callees INI::initFromINI rowed, globals g_00DFE6D8 and
// theAptButtonTooltipMapBlockParse from packet, flags /O1 /arch:SSE /G7.
#include "ascii_string.h"

#include "../../Include/Common/INI/FieldParse.h"

class INI;

class Rva002241D6
{
public:
	void parseButtonMap(INI *ini);
};

// ?rva00224A31@@YAXPAVINI@@PAVRva002241D6@@@Z @0x00224A31 (14B)
void __declspec(noinline) rva00224A31(INI *ini, Rva002241D6 *inst)
{
	inst->parseButtonMap(ini);
}

struct BlockParse
{
	BlockParse *m_next;
	const char *m_name;
	void (*m_parse)(INI *);
	FieldParse m_fields[2];
};

void parseAptButtonTooltipMapDefinition(INI *ini);
// Whole native DBA1CC..DBA1F8 record: registration header and the two
// FieldParse entries. The lazy initializer below installs ButtonMap's
// callback; retail's initial callback/userData/offset words are all zero.
BlockParse theAptButtonTooltipMapBlockParse = {
	0, "AptButtonTooltipMap", parseAptButtonTooltipMapDefinition,
	{ { "ButtonMap", 0, 0, 0 }, { 0, 0, 0, 0 } }
};
int g_00DFE6D8;	// retail RVA 0x009FE6D8 (.bss), defined here

#include "../../Include/Common/INI/INI.h"

class Rva00224A3F
{
public:
	void __declspec(noinline) rva00224A3F(INI *ini);
};

void Rva00224A3F::rva00224A3F(INI *ini)
{
	if ((g_00DFE6D8 & 1) == 0)
	{
		g_00DFE6D8 |= 1;
		theAptButtonTooltipMapBlockParse.m_fields[0].parse = reinterpret_cast<INIFieldParseProc>(rva00224A31);
		theAptButtonTooltipMapBlockParse.m_fields[0].userData = 0;
		theAptButtonTooltipMapBlockParse.m_fields[0].offset = 0;
		theAptButtonTooltipMapBlockParse.m_fields[1].token = 0;
		theAptButtonTooltipMapBlockParse.m_fields[1].parse = 0;
		theAptButtonTooltipMapBlockParse.m_fields[1].userData = 0;
		theAptButtonTooltipMapBlockParse.m_fields[1].offset = 0;
	}
	ini->initFromINI(this, theAptButtonTooltipMapBlockParse.m_fields);
}

class Rva00224CDC;
Rva00224CDC *rva00224D80();

// ?parseAptButtonTooltipMapDefinition@@YAXPAVINI@@@Z @0x00224DFF (17B)
void parseAptButtonTooltipMapDefinition(INI *ini)
{
	Rva00224A3F *p = reinterpret_cast<Rva00224A3F *>(rva00224D80());
	p->rva00224A3F(ini);
}
