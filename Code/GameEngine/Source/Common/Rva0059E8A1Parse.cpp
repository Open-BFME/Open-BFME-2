// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?Rva0059E8A1Parse@@YAXPAX00@Z @0x0059E8A1 127B.
// Evidence: chain from PlayerPosition faction insert 0x3023B8 (now rowed);
// parses an INI ascii-vector via rowed 0x2F196 then inserts each element into
// the PlayerPosition set; null-guards on the store double-pointer; vector
// base 0x211E58 via existing AsciiString pin plus vector dtor 0x2CC70.
#include <set>
#include <vector>

#include "ascii_string.h"

bool operator<(const AsciiString &left, const AsciiString &right);

namespace _STL
{
template <> struct less<AsciiString>
{
	bool operator()(const AsciiString &left, const AsciiString &right) const
	{
		return left < right;
	}
};
}

struct PlayerPosition
{
	unsigned char human;
	unsigned char computer;
	unsigned char loadAIScripts;
	int forceTeam;
	_STL::set<AsciiString> factions;
	void rva003023B8(const AsciiString &name);
};

class INI
{
public:
	static void parseAsciiStringVector(INI *ini, void *instance, void *store, const void *userData);
};

// ?Rva0059E8A1Parse@@YAXPAX00@Z
void Rva0059E8A1Parse(void *ini, void *unused, void *store)
{
	if (!store)
		return;
	PlayerPosition *pos = *(PlayerPosition **)store;
	if (!pos)
		return;
	_STL::vector<AsciiString> names;
	INI::parseAsciiStringVector((INI *)ini, 0, &names, 0);
	for (unsigned int i = 0; i < names.size(); ++i)
		pos->rva003023B8(names[i]);
}
