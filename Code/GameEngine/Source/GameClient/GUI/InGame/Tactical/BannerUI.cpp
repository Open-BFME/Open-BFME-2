// cl: /G7 /arch:SSE /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
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


struct Rva0041534BIter {void *m_node;void *m_table;};
class Rva00056F61 {
public:
 __declspec(nothrow) Rva0041534BIter rva0041534B(const AsciiString *);
 __declspec(nothrow) void *rva00056F61(const AsciiString *);
 void *unused;void **begin,**end,**capacity;unsigned count;
};

class BannerUI
{
public:
	static void ParseBannerTypeInfo(INI *ini);
 const AsciiString &GetBannerIconImageName(const AsciiString &key);
private:
 unsigned char m_pad00[0x0C];
 Rva00056F61 m_types;
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

// WB B6E990 names GetBannerIconImageName. Native216F3B..216F91 RET4
// looks up the type table at+C, retries BannerMen, then returns string+10
// in the node or TheEmptyString. The reference interface is inferred from
// that stable returned string and pointer-equivalent native argument ABI.
const AsciiString &BannerUI::GetBannerIconImageName(const AsciiString &key) {
 Rva0041534BIter it=m_types.rva0041534B(&key);
 void *node=it.m_node;
 if(!node) {
  {
   AsciiString fallback("BannerMen");
   node=m_types.rva00056F61(&fallback);
   // Retail retains this owner update in the exposed iterator slot before
   // releasing the temporary fallback key; its node result stays separate.
   it.m_table=&m_types;
  }
  if(!node)return AsciiString::TheEmptyString;
 }
 return *(const AsciiString*)((char*)node+0x10);
}
