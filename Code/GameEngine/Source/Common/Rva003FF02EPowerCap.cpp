// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /MD /EHsc
// ?Rva003FF02EPowerCap@@YAXH@Z @0x003FF02E 134B
// Static AsciiString key APT:PlayerPowerCap via rowed StringBase ctor 0x00037BA0 plus atexit,
// Unicode value via format 0x006CB5D0 on extern format string 0x007C9260,
// then bfmeSetText pin 0x00225301 on global 0x009FE4CC with false, release 0x00036E70.
// Evidence: literal 0x0083814C, static guard 0x00A02EE0, caller 0x002D69A4;
// precedent Rva00517048Chat.cpp local key plus bfmeSetText false, Rva005FDF1CApt.cpp flags.
template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#include "ascii_string.h"


#include "unicode_string.h"

class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &, const UnicodeString &, bool);
};

extern BfmeAptWindowManager *g_bfmeAptWindowManager;
extern const unsigned short g_Va007C9260[];

void __cdecl Rva003FF02EPowerCap(int cap)
{
	static AsciiString s_key("APT:PlayerPowerCap");
	UnicodeString value;
	value.format(g_Va007C9260, cap);
	g_bfmeAptWindowManager->bfmeSetText(s_key, value, false);
}

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:?g_Va007C9260@@3QBGB=??_C@_15KNBIKKIN@?$AA?$CF?$AAd?$AA?$AA@")
