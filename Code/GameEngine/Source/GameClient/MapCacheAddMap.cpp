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
#include <set>
#include <string.h>
#include "ascii_string.h"
#include "unicode_string.h"
#include "../../../Libraries/Include/Lib/Coord3D.h"

namespace _STL {
template<class T,class L,class R> static inline bool operator!=(const _Rb_tree_iterator<T,L>&a,const _Rb_tree_iterator<T,R>&b) {return a._M_node!=b._M_node;}
}
bool operator<(const AsciiString &,const AsciiString &);
namespace _STL {template<> struct less<AsciiString> { bool operator()(const AsciiString&a,const AsciiString&b)const{return a<b;} };}

struct Region3D {Coord3D lo,hi;};
class WaypointMap : public _STL::map<AsciiString,Coord3D> {public: void update(); int numStartSpots;};
struct PlayerPosition { unsigned char human,computer,loadAIScripts; int forceTeam; _STL::set<AsciiString> factions; };
struct MapPlayers { PlayerPosition items[8]; };
class MapMetaData {
public:
    MapMetaData(); ~MapMetaData(); MapMetaData &operator=(const MapMetaData &);
    UnicodeString displayName,description; Region3D extent; int numPlayers;
    unsigned char isMultiplayer,isScenarioMP,isOfficial;
    unsigned filesize,crc,timestampLo,timestampHi;
    WaypointMap waypoints; _STL::list<Coord3D> supplyPositions,techPositions;
    AsciiString fileName; MapPlayers players; unsigned wordF4;
    UnicodeString cachedDisplayName,cachedDescription;
};
typedef char CheckMetadata256[(sizeof(MapMetaData)==256)?1:-1];
class Rva00304DC7Record { char data[256]; };
class Rva00304DC7Map { public: Rva00304DC7Record &operator[](const AsciiString &); };
struct FileInfo {unsigned sizeHigh,sizeLow,timestampHigh,timestampLow;};
class MapCache : public _STL::map<AsciiString,MapMetaData> {
public: bool addMap(AsciiString dirName,AsciiString fname,FileInfo *info,bool official);
private:
    __forceinline MapMetaData &record(const AsciiString &key) {
        return reinterpret_cast<MapMetaData &>(reinterpret_cast<Rva00304DC7Map *>(this)->operator[](key));
    }
};
enum NameKeyType;
class StaticNameKey {public:mutable int key;const char *name;};
class Rva00148F5ECache {public:NameKeyType get();};
extern const StaticNameKey TheKey_isScenarioMultiplayer,TheKey_mapName,TheKey_mapDescription;
static __forceinline int key(const StaticNameKey &k) {return (int)reinterpret_cast<Rva00148F5ECache *>(const_cast<StaticNameKey *>(&k))->get();}
class Dict {public:bool getBool(int,bool *)const;AsciiString getAsciiString(int,bool *)const;};
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
    lowerFname.toLower();
    iterator it=find(lowerFname);
    MapMetaData md;
    unsigned filesize=info->sizeLow;
    if (it!=end()) {
        md=it->second;
        if (md.filesize==filesize && md.crc!=0) return false;
    }
    loadMap(fname,&md);
    md.fileName=lowerFname;
    md.filesize=filesize;
    md.isOfficial=official;
    md.waypoints.update();
    md.numPlayers=md.waypoints.numStartSpots;
    md.isMultiplayer=md.numPlayers>=2;
    if (strstr(md.fileName.str(),"\\map sps ")) md.isMultiplayer=false;
    md.timestampHi=info->timestampHigh;
    md.timestampLo=info->timestampLow;
    md.supplyPositions=m_supplyPositions;
    md.techPositions=m_techPositions;
    md.crc=calcCRC(dirName,fname);
    bool exists=false;
    md.isScenarioMP=worldDict.getBool(key(TheKey_isScenarioMultiplayer),&exists);
    if (!exists) md.isScenarioMP=false;
    AsciiString name=worldDict.getAsciiString(key(TheKey_mapName),&exists);
    if (exists && !name.isEmpty()) md.displayName.translate(name);
    else {
        AsciiString leaf=fname.reverseFind('\\')+1;
        const char *p=leaf.str();
        AsciiString tag("$Map:");
        for (; *p; ++p) {
            if (*p=='.') break;
            if (*p!=' ') {
                char ch=*p;
                reinterpret_cast<StringBase<char> *>(&tag)->concat(&ch,1);
            }
        }
        md.displayName.translate(tag);
    }
    AsciiString description=worldDict.getAsciiString(key(TheKey_mapDescription),&exists);
    if (exists && !description.isEmpty()) md.description.translate(description);
    else {
        AsciiString leaf=fname.reverseFind('\\')+1;
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
        md.description.translate(tag);
    }
    md.extent.lo.x=0.0f;md.extent.lo.y=0.0f;
    md.extent.hi.x=m_mapDX*10.0f;md.extent.hi.y=m_mapDY*10.0f;
    md.extent.lo.z=0.0f;md.extent.hi.z=0.0f;
    record(lowerFname)=md;
    for (WaypointMap::iterator waypoint=md.waypoints.begin();waypoint!=md.waypoints.end();++waypoint) {}
    resetMap();
    return true;
}
