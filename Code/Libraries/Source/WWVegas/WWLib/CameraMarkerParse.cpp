// cl: /Ireference/shims/bfme2_ascii /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /EHsc
// stlport
// ?Rva000D06C6Parse@@YAXPAVINI@@PAX1PBX@Z @0x000D06C6 96B
// Evidence: chain from push_back 0x000D068F; locals int at [ebp-0x14] plus AsciiString at [ebp-0x10] form 8B CameraMarker; parseIndexList with g_00DBE974 then parseAsciiString with 0 then vector push_back; EH_prolog scope.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>
#include "ascii_string.h"

class INI
{
public:
	static void parseIndexList(INI *ini, void *instance, void *store, const void *userData);
	static void parseAsciiString(INI *ini, void *instance, void *store, const void *userData);
};

class CameraMarker
{
public:
	int m_index;
	AsciiString m_name;
};

extern const void *const g_00DBE974[];

void __cdecl Rva000D06C6Parse(INI *ini, void *instance, void *store, const void * /*userData*/)
{
	CameraMarker marker;
	INI::parseIndexList(ini, instance, &marker.m_index, g_00DBE974);
	INI::parseAsciiString(ini, instance, &marker.m_name, 0);
	((_STL::vector<CameraMarker> *)store)->push_back(marker);
}

// ?Rva000CF873Parse@@YAXPAVINI@@PAX1PBX@Z @0x000CF873 96B: the same parse for the
// other WeatherTexture field (FieldParse entry at VA 0x00BCD6F0, beside
// FloorFadeRateOnObjectDeath and HideIfModelConditions; 0x000D06C6 fills the
// entry at 0x00BCDBC0). Its vector's rowed push_back 0x000CF83C carries the
// element name Rva000CF83CElement, laid out as the same index plus name.
struct Rva000CF83CElement
{
	int m_index;
	AsciiString m_name;
};
void __cdecl Rva000CF873Parse(INI *ini, void *instance, void *store, const void * /*userData*/)
{
	Rva000CF83CElement marker;
	INI::parseIndexList(ini, instance, &marker.m_index, g_00DBE974);
	INI::parseAsciiString(ini, instance, &marker.m_name, 0);
	((_STL::vector<Rva000CF83CElement> *)store)->push_back(marker);
}
