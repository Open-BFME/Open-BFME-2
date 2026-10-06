// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// BannerUI::ParseBannerTypeInfo, retail 0x00217194 (94B), from the WorldBuilder
// lead (BannerUI.cpp): an INI block parser that takes the banner type name
// token, finds or creates its info in the banner UI singleton's type table
// (g_00DFE32C +0x0C, 0x00216F91) and parses the block into it with the
// banner-type field table at 0x00BE5A50 (INI::initFromINI).
//
// Target facts: the type table, its lookup and the info record keep
// address-derived names; the field table is referenced by address.

#include "ascii_string.h"

struct FieldParse;

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	void initFromINI(void *what, const FieldParse *parseTable);
};

class Rva00217194Types
{
public:
	void *rva00216F91(const AsciiString &name);
};

class Rva00217194BannerUI
{
public:
	Rva00217194Types *getTypes() { return &m_types; }

private:
	unsigned char m_pad00[0x0C];
	Rva00217194Types m_types;
};
extern Rva00217194BannerUI *g_00DFE32C;

extern const FieldParse g_00BE5A50[];

class BannerUI
{
public:
	static void ParseBannerTypeInfo(INI *ini);
};

void BannerUI::ParseBannerTypeInfo(INI *ini)
{
	void *info;
	{
		AsciiString name(ini->getNextToken());
		info = g_00DFE32C->getTypes()->rva00216F91(name);
	}
	ini->initFromINI(info, g_00BE5A50);
}
