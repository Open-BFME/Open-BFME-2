// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /MD /EHsc
// ?Rva003FEE43SetPlayerRank@@YA_NH@Z @0x003FEE43 136B: Apt PlayerRank display via static AsciiString key plus Unicode format plus bfmeSetText. Evidence: calls StringBase ctor 0x00037BA0 plus atexit plus UnicodeString format 0x006CB5D0 plus bfmeSetText pin 0x00225301 plus release 0x00036E70; same shape as rowed Rva003FF02EPowerCap 0x003FF02E.
#include "ascii_string.h"
#include "unicode_string.h"

extern unsigned int g_Va00E02ECC;
extern const unsigned short g_Va007C9260[];

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

bool __cdecl Rva003FEE43SetPlayerRank(int rank)
{
	static AsciiString s_key("APT:PlayerRank");
	UnicodeString str;
	str.format(g_Va007C9260, rank);
	((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(s_key, str, false);
	return true;
}

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:?g_Va007C9260@@3QBGB=??_C@_15KNBIKKIN@?$AA?$CF?$AAd?$AA?$AA@")
