// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?findMap@MapCache@@QAEPBVMapMetaData@@VAsciiString@@@Z @0x003024BC 76B.
// Evidence: BFME1 donor MapUtil.cpp findMap plus ZH MapUtil.h MapCache decl
// (class MapCache : public std::map<AsciiString, MapMetaData>); retail callers
// at 0x002DC1AB (global 0x9FF12C map, result used as MapMetaData* for
// getBaseDisplayName 0x300AEA) and 0x0030406F plus the inline twin at
// 0x00303F12-0x00303F29 calling the same _M_find 0x1F8437 then MapMetaData
// copy 0x3039E8 from node+0x14; MapMetaData is the 256B record proven by
// MapMetaDataCopy.cpp SizeCheck, modeled here as opaque bytes.
#include <map>

typedef bool Bool;
typedef int Int;

template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

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

class MapMetaData
{
public:
	unsigned char opaque[0x100];
};

class MapCache : public _STL::map<AsciiString, MapMetaData>
{
public:
	const MapMetaData *findMap(AsciiString mapName);
};

// ?findMap@MapCache@@QAEPBVMapMetaData@@VAsciiString@@@Z
const MapMetaData *MapCache::findMap(AsciiString mapName)
{
	mapName.toLower();
	MapCache::iterator it = find(mapName);
	if (it == end())
		return 0;
	return &(it->second);
}
