// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?Rva0059F20BSet@@YAXHABVUnicodeString@@@Z @ 0x0059F20B (85B).
// Free Apt connecting-player name setter: formats local AsciiString with
// "APT:ConnectingPlayer%dName" (id+1) via rowed format 0x00038150, calls
// pin-only bfmeSetText 0x00225301 on global g_bfmeAptWindowManager with (tmp, unicode,
// false), releases tmp via rowed releaseBuffer 0x00036410. Callers
// 0x0059F275/0x0059F3C2.
//
// ?Rva0059F296Set@@YAXHABVUnicodeString@@@Z @ 0x0059F296 (85B).
// Sibling status setter with "APT:ConnectingPlayer%dStatus". Same rows/pin
// and global. Callers 0x0059F3EA/0x0059FB2D.
class UnicodeString;

#include "ascii_string.h"

class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &a, const UnicodeString &u, bool flag);
};

extern BfmeAptWindowManager *g_bfmeAptWindowManager;

void __cdecl Rva0059F20BSet(int id, const UnicodeString &u)
{
	AsciiString tmp;
	tmp.format("APT:ConnectingPlayer%dName", id + 1);
	g_bfmeAptWindowManager->bfmeSetText(tmp, u, false);
}

void __cdecl Rva0059F296Set(int id, const UnicodeString &u)
{
	AsciiString tmp;
	tmp.format("APT:ConnectingPlayer%dStatus", id + 1);
	g_bfmeAptWindowManager->bfmeSetText(tmp, u, false);
}


#include "unicode_string.h"

void __stdcall Rva0059F260Set(int id, UnicodeString u)
{
	Rva0059F20BSet(id, u);
}
