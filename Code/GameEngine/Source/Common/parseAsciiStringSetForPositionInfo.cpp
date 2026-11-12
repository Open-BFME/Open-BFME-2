// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?parseAsciiStringSetForPositionInfo@@YAXPAX00@Z @0x0059E8A1 127B.
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

#include "../../Include/Common/PlayerPosition.h"

#include "../../Include/Common/INI/INI.h"

// ?parseAsciiStringSetForPositionInfo@@YAXPAX00@Z
void parseAsciiStringSetForPositionInfo(void *ini, void *unused, void *store)
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
