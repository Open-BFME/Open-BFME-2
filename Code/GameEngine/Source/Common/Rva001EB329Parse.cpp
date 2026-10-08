// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva001EB329@Rva001EB329@@QAEXPAVINI@@@Z, retail 0x001EB329, 89 bytes.
// __thiscall INI parse validator: initFromINI(this) via rowed 0x0002DE78 and table
// g_00BDF0E8, then if map string at +4 isEmpty (rowed StringBase 0x00001E2F) throw
// INIException code 3 with retail literal using mission string at +0 as t ? t+8
// : g_Rva0107301CEmptyString. Throw idiom (ctor 0x0002F681 plus CxxThrow plus
// throwinfo anchor) from Rva004135CDParse. Evidence: leaf lane, caller 0x001ED326,
// prev Rva001EB2CCMapPath and next Rva001EB3A6BoundsCheck share flags.
#include "ascii_string.h"

struct FieldParse;

class INI
{
public:
	void initFromINI(void *what, const FieldParse *table);
};

extern const FieldParse g_00BDF0E8;

struct INIException
{
	char *mFailureMessage;
	int mErrorCode;
	INIException(int argCount, const char *format, ...);
};

extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);
struct Rva001EB329ThrowInfoAnchor { int a; int b; int c; int d; };
static const Rva001EB329ThrowInfoAnchor rva001EB329ThrowInfoAnchor = { 0, 0, 0, 0 };

class Rva001EB329
{
public:
	void rva001EB329(INI *ini);
private:
	AsciiString m_missionName;
	AsciiString m_mapName;
};

void Rva001EB329::rva001EB329(INI *ini)
{
	ini->initFromINI(this, &g_00BDF0E8);
	if (((const StringBase<char> *)&m_mapName)->isEmpty())
	{
		char *t = *(char **)this;
		const char *s = t ? t + 8 : "";
		INIException exc(3, "Campaign missions must have a Map. %s does not", s);
		_CxxThrowException(&exc, (const _s__ThrowInfo *)&rva001EB329ThrowInfoAnchor); __assume(0);
	}
}
