// cl: /Ireference/shims/bfme2_ascii /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport

// ?rva001FE70F@Rva001FE70F@@QAEXPAVINI@@@Z, RVA 0x001FE70F, 99B. Unlock lane:
// MultiIniFieldParse at ebp-0x84 via rowed ctor 0x0002BAA0, add rowed
// 0x0002BC6E of g_00BE2070 with 0 then Rva003B0E57Get (0x00C1DB18) with
// 0x154, then INI::initFromINIMulti pin 0x0002D7A8 with this and parse,
// then AsciiString copy from +0x18 to +0x154 via rowed StringBase set
// 0x000366F0. Callers 0x001FF079 0x001FF092 0x001FF0E8 in 0x001FEFEC.
// Owner unproven so honest-address class Rva001FE70F.
#include "ascii_string.h"

struct FieldParse;
extern const struct FieldParse g_00BE2070[];

class MultiIniFieldParse
{
	const void *m_fieldParse[16];
	unsigned m_extraOffset[16];
	int m_count;

public:
	MultiIniFieldParse();
	void add(const FieldParse *fields, unsigned extraOffset);
};

class INI
{
public:
	void initFromINIMulti(void *what, const MultiIniFieldParse &parseTableList);
};

int __cdecl Rva003B0E57Get(void);

class Rva001FE70F
{
public:
	void rva001FE70F(class INI *ini);

private:
	char m_pad00[0x18];
	AsciiString m_18;
	char m_pad1C[0x138];
	AsciiString m_154;
};

void Rva001FE70F::rva001FE70F(class INI *ini)
{
	MultiIniFieldParse parse;
	parse.add(g_00BE2070, 0);
	parse.add((const FieldParse *)Rva003B0E57Get(), 0x154);
	ini->initFromINIMulti(this, parse);
	m_154.set(m_18);
}
