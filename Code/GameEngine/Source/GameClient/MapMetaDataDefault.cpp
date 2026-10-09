// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// BFME1 MapMetaData_ctor.cpp at6c1e0b51 semantic donor. Native3031D3..30328D
// is the BFME2 186-byte constructor for a256B record; named copy/assignment/GUI fields prove
// the layout. The12-byte tree-header initializer reuses its existing opaque
// in-image constructor owner; its concrete string/coordinate domain is not
// being renamed onto the folded generic tree-header body.
#include <list>
#include <set>
#include "ascii_string.h"
#include "unicode_string.h"
#include "../../../Libraries/Include/Lib/Coord3D.h"
struct Region3D {Coord3D lo,hi;};
class Rva0029B63A {public:Rva0029B63A();private:char header[12];};
class WaypointMap:private Rva0029B63A {public:
 __forceinline WaypointMap():numStartSpots(0){}
 ~WaypointMap();int numStartSpots;
};
struct PlayerPosition {unsigned char human,computer,loadAIScripts;int forceTeam;_STL::set<AsciiString> factions;PlayerPosition();~PlayerPosition();};
struct MapPlayers {__declspec(noinline) MapPlayers();PlayerPosition items[8];};
MapPlayers::MapPlayers(){}
class MapMetaData {public:MapMetaData();~MapMetaData();
 UnicodeString displayName,description;volatile Region3D extent;int numPlayers;
 unsigned char isMultiplayer,isScenarioMP,isOfficial;
 unsigned filesize,crc,timestampLo,timestampHi;
 WaypointMap waypoints;_STL::list<Coord3D> supplyPositions,techPositions;
 AsciiString fileName;MapPlayers players;unsigned wordF4;
 UnicodeString cachedDisplayName,cachedDescription;
};
typedef char VerifyMapMetadata256[(sizeof(MapMetaData)==256)?1:-1];
// Volatile extent and the final scoped reference retain six scalar stores
// ahead of the timestamp stores, as independently required by native3031D3.
MapMetaData::MapMetaData():numPlayers(0),isMultiplayer(0),isScenarioMP(0),isOfficial(0),filesize(0),crc(0),wordF4(0)
{
 extent.lo.x=0.0f;extent.lo.y=0.0f;extent.lo.z=0.0f;
 extent.hi.x=0.0f;extent.hi.y=0.0f;{volatile Coord3D &hi=extent.hi;hi.z=0.0f;}
 timestampHi=0;timestampLo=0;
}
