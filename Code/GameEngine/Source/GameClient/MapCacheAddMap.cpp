// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
// Semantic donor: GeneralsMD GameClient/MapUtil.cpp MapCache::addMap.
// Native304E64..30529C and WB C5BDA0 independently establish the cache/size/CRC
// path and map parse. BFME2 additionally fills player metadata, scenario flag,
// and localized description. Its filename fallback strips spaces before the
// extension into "$Map:" and "Map:" + "/Desc" keys. Metadata's 256-byte layout
// comes from the already verified target constructor/copy/assignment/GUI users.
// Generic map subscript retains its existing opaque provider spelling.
#include <map>
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base
// wrapper (_List_iterator_base::operator!=, retail's copy is 0x006CFE40).
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}
#include <set>
#include <string.h>
#include "ascii_string.h"
#include "unicode_string.h"
#include "../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../reference/shims/bfme_coord3d_construct_link/coord3d_construct_link.h"

// __malloc_alloc<0> allocate/deallocate otherwise instantiate per-TU
// COMDATs (one byte shape per TU malloc/free wiring); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t __n)
{ void *__r = malloc(__n); if (!__r) __r = _S_oom_malloc(__n); return __r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}

namespace _STL {
template<class T,class L,class R> static inline bool operator!=(const _Rb_tree_iterator<T,L>&a,const _Rb_tree_iterator<T,R>&b) {return a._M_node!=b._M_node;}
}
bool operator<(const AsciiString &,const AsciiString &);
namespace _STL {template<> struct less<AsciiString> { bool operator()(const AsciiString&a,const AsciiString&b)const{return a<b;} };}

#include "../../../Libraries/Include/Lib/Region3D.h"
// bfme link decl-only begin
namespace _STL { template <> _List_node<Coord3D> * list<Coord3D, allocator<Coord3D> >::_M_create_node(Coord3D const &); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?erase@?$list@UCoord3D@@V?$allocator@UCoord3D@@@_STL@@@_STL@@QAE?AU?$_List_iterator@UCoord:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Coord3D;
namespace _STL { template <> _List_iterator<Coord3D,_Nonconst_traits<Coord3D> > list<Coord3D,allocator<Coord3D> >::erase(_List_iterator<Coord3D,_Nonconst_traits<Coord3D> >); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@U?$_List_node@UCoord3D@@@_STL@@@_STL@@QBEXPAU?$_List_node@UCoord3D:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Coord3D;
namespace _STL { template <> void allocator<_List_node<Coord3D> >::deallocate(_List_node<Coord3D> *,unsigned int) const; }
class WaypointMap : public _STL::map<AsciiString,Coord3D> {public: void update(); int numStartSpots;};
#include "../../Include/Common/PlayerPosition.h"
struct MapPlayers { PlayerPosition items[8]; };
#include "../../Include/GameClient/MapMetaData.h"
// The canonical header keeps the STL members opaque; this TU's typed views.
static inline WaypointMap &waypointsOf(MapMetaData &md) { return reinterpret_cast<WaypointMap &>(md.field38); }
static inline _STL::list<Coord3D> &supplyOf(MapMetaData &md) { return reinterpret_cast<_STL::list<Coord3D> &>(md.field48); }
static inline _STL::list<Coord3D> &techOf(MapMetaData &md) { return reinterpret_cast<_STL::list<Coord3D> &>(md.field4C); }
typedef char CheckMetadata256[(sizeof(MapMetaData)==256)?1:-1];
class Rva00304DC7Record { char data[256]; };
class Rva00304DC7Map { public: Rva00304DC7Record &operator[](const AsciiString &); };
#include "../../Include/Common/FileInfo.h"
#include "../../Include/GameClient/MapCache.h"
static __forceinline MapMetaData &record(MapCache *cache,const AsciiString &key) {
    return reinterpret_cast<MapMetaData &>(reinterpret_cast<Rva00304DC7Map *>(cache)->operator[](key));
}
enum NameKeyType;
class StaticNameKey {public:mutable int key;const char *name;};
class Rva00148F5ECache {public:NameKeyType get();};
extern const StaticNameKey TheKey_isScenarioMultiplayer,TheKey_mapName,TheKey_mapDescription;
const StaticNameKey TheKey_isScenarioMultiplayer = { 0, "isScenarioMultiplayer" };
const StaticNameKey TheKey_mapDescription = { 0, "mapDescription" };
static __forceinline int key(const StaticNameKey &k) {return (int)reinterpret_cast<Rva00148F5ECache *>(const_cast<StaticNameKey *>(&k))->get();}
#include "../../Include/Common/Dict.h"
extern "C" Dict worldDict;
extern "C" _STL::list<Coord3D> m_supplyPositions,m_techPositions;
extern "C" int m_mapDX,m_mapDY;
bool loadMap(AsciiString,void *);
unsigned calcCRC(AsciiString,AsciiString);
void resetMap();

bool MapCache::addMap(AsciiString dirName,AsciiString fname,FileInfo *info,bool official)
{
    if (!info) return false;
    AsciiString lowerFname;
    lowerFname=fname;
    ((StringBase<char> &)(lowerFname)).toLower();
    iterator it=find(lowerFname);
    MapMetaData md;
    unsigned filesize=info->sizeLow;
    if (it!=end()) {
        md=it->second;
        if (md.m_filesize==filesize && md.m_CRC!=0) return false;
    }
    loadMap(fname,&md);
    md.m_fileName=lowerFname;
    md.m_filesize=filesize;
    md.m_isOfficial=official;
    waypointsOf(md).update();
    md.m_numPlayers=waypointsOf(md).numStartSpots;
    md.m_isMultiplayer=md.m_numPlayers>=2;
    if (strstr(md.m_fileName.str(),"\\map sps ")) md.m_isMultiplayer=false;
    md.field34=info->timestampHigh;
    md.field30=info->timestampLow;
    supplyOf(md)=m_supplyPositions;
    techOf(md)=m_techPositions;
    md.m_CRC=calcCRC(dirName,fname);
    bool exists=false;
    md.m_isScenarioMP=worldDict.getBool(key(TheKey_isScenarioMultiplayer),&exists);
    if (!exists) md.m_isScenarioMP=false;
    AsciiString name=worldDict.getAsciiString(key(TheKey_mapName),&exists);
    if (exists && !name.isEmpty()) md.m_displayName.translate(name);
    else {
        AsciiString leaf=((const StringBase<char> &)(fname)).reverseFind('\\')+1;
        const char *p=leaf.str();
        AsciiString tag("$Map:");
        for (; *p; ++p) {
            if (*p=='.') break;
            if (*p!=' ') {
                char ch=*p;
                reinterpret_cast<StringBase<char> *>(&tag)->concat(&ch,1);
            }
        }
        md.m_displayName.translate(tag);
    }
    AsciiString description=worldDict.getAsciiString(key(TheKey_mapDescription),&exists);
    if (exists && !description.isEmpty()) md.m_description.translate(description);
    else {
        AsciiString leaf=((const StringBase<char> &)(fname)).reverseFind('\\')+1;
        const char *p=leaf.str();
        AsciiString tag("Map:");
        for (; *p; ++p) {
            if (*p=='.') break;
            if (*p!=' ') {
                char ch=*p;
                reinterpret_cast<StringBase<char> *>(&tag)->concat(&ch,1);
            }
        }
        reinterpret_cast<StringBase<char> *>(&tag)->concat("/Desc");
        md.m_description.translate(tag);
    }
    md.m_extent.lo.x=0.0f;md.m_extent.lo.y=0.0f;
    md.m_extent.hi.x=m_mapDX*10.0f;md.m_extent.hi.y=m_mapDY*10.0f;
    md.m_extent.lo.z=0.0f;md.m_extent.hi.z=0.0f;
    record(this,lowerFname)=md;
    for (WaypointMap::iterator waypoint=waypointsOf(md).begin();waypoint!=waypointsOf(md).end();++waypoint) {}
    resetMap();
    return true;
}
