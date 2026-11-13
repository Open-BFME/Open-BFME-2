// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX-
// ?Rva0033A3F4Lookup@@YAHABVAsciiString@@@Z @0x0033A3F4 60B
// Evidence: callers in PlayerTemplateStore 0x001FD391 plus 0x001FD238 0x0043A834;
// returns 5 for "Goblins" (0x80EBCC) else index into 7-entry table at 0x00DBE9B0 via compareNoCase else 7.
#include "ascii_string.h"


// g_rva0033A3F4Table: the retail string table at VA 0xdbe9b0, NULL-terminated (32 bytes): retail's 0xdbe9cc
// after the seven names is 0. This lookup's not-found value 7 indexes it (GetRankIcon formats it as
// "(null)"), and findNameIndex (GapBodiesGE09.cpp) walks to it.
const char *g_rva0033A3F4Table[8] = {
	"Men",
	"Elves",
	"Dwarves",
	"Isengard",
	"Mordor",
	"Wild",
	"Neutral",
	0,
};

int Rva0033A3F4Lookup(const AsciiString &name)
{
	if (name.compare("Goblins") == 0)
		return 5;
	for (int i = 0; i < 7; ++i)
	{
		if (((const StringBase<char> &)name).compareNoCase(g_rva0033A3F4Table[i]) == 0)
			return i;
	}
	return 7;
}
