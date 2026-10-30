// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Rva000C3824_ParseTexturePair (retail 0x000C3824, 98 bytes). Reads two
// consecutive strings through the rowed parseAsciiString at 0x002F11E into
// the halves of a local 8-byte BfmeStringRecord000B94D2 (two AsciiStrings,
// inline zero-init), pushes the record through the rowed
// vector<BfmeStringRecord000B94D2>::push_back at 0x000C333B, then tears the
// record down through its dtor (pinned with its true struct name at
// 0x000B6CF1). Serves the Texture table entry. The record model mirrors the
// vector-allocate TU; the callback name stays address-derived.

#include "ascii_string.h"

struct BfmeStringRecord000B94D2
{
	AsciiString text0;
	AsciiString text1;
	~BfmeStringRecord000B94D2();
};

#include <vector>

namespace _STL
{
// Bind the append to the rowed record-vector worker.
template <> void vector<BfmeStringRecord000B94D2, allocator<BfmeStringRecord000B94D2> >::push_back(const BfmeStringRecord000B94D2 &value);
}

class INI
{
public:
	static void parseAsciiString(INI *ini, void *instance, void *store, const void *userData);
	static void Rva000C3824_ParseTexturePair(INI *ini, void *instance, void *store, const void *userData);
};

// ?Rva000C3824_ParseTexturePair@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva000C3824_ParseTexturePair(INI *ini, void *instance, void *store, const void *userData)
{
	BfmeStringRecord000B94D2 record;
	INI::parseAsciiString(ini, instance, &record.text0, userData);
	INI::parseAsciiString(ini, instance, &record.text1, userData);
	((_STL::vector<BfmeStringRecord000B94D2> *)store)->push_back(record);
}
