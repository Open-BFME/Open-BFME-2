// ?getDefaultMap@@YA?AVAsciiString@@_N@Z @ 0x0030582D 204B
// Retail sorts filtered metadata pointers and returns the selected filename.
// The 0x00302459 collector is recovered in this translation unit.
// cl: /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
#define free bfmeUnusedCRTFree
#include <cstdlib>
#undef free
void free(void *);
#include <vector>
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#include <algorithm>
#include "ascii_string.h"

class MapMetaData
{
public:
	char unknown00[0x50];
	AsciiString m_fileName;
	char unknown54[0x100 - 0x54];
};

class MapCache : public _STL::map<AsciiString, MapMetaData>
{
public:
	void updateCache();
};

extern MapCache *TheMapCache;

struct Rva00300021Argument
{
	char unknown00[0x24];
	bool byte24, byte25, byte26;
};

class Rva00300021Flags
{
public:
	unsigned int flags;
	bool test(const Rva00300021Argument *) const;
};

#pragma optimize("s", on)
void rva00302459(unsigned int flags, _STL::vector<MapMetaData *> *out)
{
	if (!(flags & 0x40))
		out->clear();
	MapCache::const_iterator last = TheMapCache->end();
	MapCache::const_iterator it = TheMapCache->begin();
	Rva00300021Flags predicate = { flags };
	if (it != last)
	{
		do
		{
			if (predicate.test(reinterpret_cast<const Rva00300021Argument *>(&it->second)))
			{
				MapMetaData *md = const_cast<MapMetaData *>(&it->second);
				out->push_back(md);
			}
			++it;
		} while (it != TheMapCache->end());
	}
}
#pragma optimize("", on)

struct Rva0030145CCmp
{
	bool operator()(MapMetaData *, MapMetaData *) const;
};

#pragma optimize("t", off)
#pragma optimize("s", on)
AsciiString getDefaultMap(bool isMultiplayer)
{
	if (!TheMapCache)
		return AsciiString::TheEmptyString;
	TheMapCache->updateCache();
	unsigned int flags = (isMultiplayer ? 8 : 4) | 1;
	_STL::vector<MapMetaData *> maps;
	rva00302459(flags, &maps);
	_STL::sort(maps.begin(), maps.end(), Rva0030145CCmp());
	if (maps.size() != 0)
		return maps.front()->m_fileName;
	return AsciiString::TheEmptyString;
}
#pragma optimize("", on)
