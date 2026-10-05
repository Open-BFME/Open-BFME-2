// cl: /Ireference/shims/bfme2_ascii /O1 /GX /DNDEBUG /MD
//
// ?Rva004DBFF1Parse@@YAXPAVINI@@PAX1PBX@Z, retail 0x004DBFF1 (145B): the
// SkirmishAIHeuristic FieldParse proc (row 0x00BFA878, store +0x98). The
// next token is read as an AsciiString and matched, by AsciiString compare
// against each of the four names at VA 0x00DCFC24, to its index; -1 is stored
// when nothing matches. Name address-derived.

#include "ascii_string.h"

#define NULL 0

class INI
{
public:
	AsciiString getNextAsciiString();
};

extern const char *g_00DCFC24[];

// AsciiString view whose text compare is declared nonthrowing, so the
// temporary needs no unwind state (retail registers none); the spelling
// resolves to the rowed StringBase<char>::compare(const char *) at 0x000069B1.
class Rva004DBFF1Name : public AsciiString
{
public:
	Rva004DBFF1Name(const char *s) : AsciiString(s) {}
	int compareText(const char *text) const throw();
};

static inline int Rva004DBFF1Index(const char *name)
{
	int result = -1;
	if (name)
	{
		for (int i = 0; i < 4; ++i)
		{
			if (Rva004DBFF1Name(g_00DCFC24[i]).compareText(name) == 0)
			{
				result = i;
				break;
			}
		}
	}
	return result;
}

// ?Rva004DBFF1Parse@@YAXPAVINI@@PAX1PBX@Z
void Rva004DBFF1Parse(INI *ini, void *, void *store, const void *)
{
	*(int *)store = Rva004DBFF1Index(ini->getNextAsciiString().str());
}
