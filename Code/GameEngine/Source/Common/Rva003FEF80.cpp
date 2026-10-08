// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /MD /EHsc
// ?Rva003FEF80SetPalantirMultiplier@@YA_NM@Z @0x003FEF80 174B: Apt Palantir resource multiplier display via static AsciiString key plus float-gated Unicode format/set plus bfmeSetText. Evidence: calls StringBase ctor 0x00037BA0 plus atexit plus UnicodeString format 0x006CB5D0 plus StringBase set 0x0000565D plus bfmeSetText pin 0x00225301 plus release 0x00036E70; same shape as rowed Rva003FF02EPowerCap 0x003FF02E.
#include "ascii_string.h"
#include "unicode_string.h"

extern unsigned int g_Va00E02EDC;
extern float g_Va00BBB8D8;
extern const unsigned short g_00BC26DC[];

class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &, const UnicodeString &, bool);
};

class Rva00222A8BTarget
{
public:
	void bfmeSetText(const AsciiString &, const UnicodeString &, bool);
};

extern Rva00222A8BTarget *TheRva00222A8BTarget;

bool __cdecl Rva003FEF80SetPalantirMultiplier(float value)
{
	static AsciiString s_key("APT:PalantirResourceMultiplier");
	UnicodeString str;
	if (value != g_Va00BBB8D8)
	{
		str.format(L"x%g", value);
	}
	else
	{
		str.set(g_00BC26DC);
	}
	((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(s_key, str, false);
	return true;
}
