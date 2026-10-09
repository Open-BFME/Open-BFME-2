// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// BF1 f989 Rva000C1E50MapCacheDefinition.cpp semantic donor. BFME2 native
// 5350BA..535403, field tableC68AE8 and owned reader/member bodies prove
// layouts and calls. BFME2 additionally checks an official map's file.
#include <list>
#include <map>
#include <set>
#include "ascii_string.h"
#include "unicode_string.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
bool operator<(const AsciiString&,const AsciiString&);
struct Region3D {Coord3D lo,hi;};
struct PlayerPosition {unsigned char human,computer,loadAIScripts;int forceTeam;_STL::set<AsciiString> factions;};
struct MapPlayers {PlayerPosition items[8];MapPlayers&operator=(const MapPlayers&);};
class WaypointMap:public _STL::map<AsciiString,Coord3D> {public:int numStartSpots;};
class MapMetaData {public:MapMetaData();~MapMetaData();MapMetaData&operator=(const MapMetaData&);
 UnicodeString displayName,description;Region3D extent;int numPlayers;
 unsigned char isMultiplayer,isScenarioMP,isOfficial;
 unsigned filesize,crc,timestampLo,timestampHi;
 WaypointMap waypoints;_STL::list<Coord3D> supplyPositions,techPositions;
 AsciiString fileName;MapPlayers players;unsigned wordF4;
 UnicodeString cachedDisplayName,cachedDescription;
};
class INI;
struct FieldParse {const char*name;void(*parse)(INI*,void*,void*,const void*);const void*user;unsigned offset;};
class Rva00534E13 {public:Rva00534E13();~Rva00534E13();
 Region3D extent;int numPlayers;unsigned char multiplayer,scenarioMP;
 AsciiString displayName,nameTag;unsigned char official;
 unsigned timestampLo,timestampHi,filesize,crc;Coord3D waypoints[8],camera;
 _STL::list<Coord3D> supplyPositions,techPositions;MapPlayers players;
 static const FieldParse fieldTable[];
};
struct TreeHintPayload003012F0 {unsigned a,b,c;};
typedef _STL::map<AsciiString,TreeHintPayload003012F0> CoordMapProvider;
typedef _STL::_Rb_tree<AsciiString,_STL::pair<const AsciiString,Coord3D>,_STL::_Select1st<_STL::pair<const AsciiString,Coord3D> >,_STL::less<AsciiString>,_STL::allocator<_STL::pair<const AsciiString,Coord3D> > > WaypointTree;
namespace _STL {
template<> TreeHintPayload003012F0 &CoordMapProvider::operator[](const AsciiString&);
template<> void WaypointTree::clear();
template<> void list<Coord3D>::push_front(const Coord3D&);
}
class Rva00304DC7Record {char body[256];};
class Rva00304DC7Map {public:Rva00304DC7Record&operator[](const AsciiString&);};
class MapCache;
extern MapCache *TheMapCache;
enum NameKeyType {NAMEKEY_INVALID};
class NameKeyGenerator {public:const AsciiString&keyToName(NameKeyType);};
extern NameKeyGenerator *TheNameKeyGenerator;
class StaticNameKey {public:NameKeyType key()const;};
extern const StaticNameKey TheKey_InitialCameraPosition;
class FileSystem {public:bool doesFileExist(const char*)const;};
extern FileSystem *TheFileSystem;
AsciiString QuotedPrintableToAsciiString(AsciiString);
UnicodeString QuotedPrintableToUnicodeString(AsciiString);
class INI {public:const char*getNextToken(const char*);void initFromINI(void*,const FieldParse*);static void parseMapCacheDefinition(INI*);
 static void parseBool(INI*,void*,void*,const void*);
 static void parseInt(INI*,void*,void*,const void*);
 static void parseUnsignedInt(INI*,void*,void*,const void*);
 static void parseCoord3D(INI*,void*,void*,const void*);
 static void parseAsciiString(INI*,void*,void*,const void*);};
// Native C68AE8 is exactly24 entries plus sentinel. Offsets below are
// read from target data rather than inferred from the reference table.
void Rva00534BAFParse(INI*,void*,void*,const void*);
void Rva00534BDCParse(INI*,void*,void*,const void*);
void Rva00535087Parse(INI*,void*,void*,const void*);
const FieldParse Rva00534E13::fieldTable[]={
 {"isOfficial",INI::parseBool,0,0x28},
 {"isMultiplayer",INI::parseBool,0,0x1C},
 {"isScenarioMP",INI::parseBool,0,0x1D},
 {"extentMin",INI::parseCoord3D,0,0},
 {"extentMax",INI::parseCoord3D,0,0xC},
 {"numPlayers",INI::parseInt,0,0x18},
 {"fileSize",INI::parseUnsignedInt,0,0x34},
 {"fileCRC",INI::parseUnsignedInt,0,0x38},
 {"timestampLo",INI::parseInt,0,0x2C},
 {"timestampHi",INI::parseInt,0,0x30},
 {"displayName",INI::parseAsciiString,0,0x20},
 {"description",INI::parseAsciiString,0,0x24},
 {"supplyPosition",Rva00534BAFParse,0,0},
 {"techPosition",Rva00534BDCParse,0,0},
 {"Player_1_Start",INI::parseCoord3D,0,0x3C},
 {"Player_2_Start",INI::parseCoord3D,0,0x48},
 {"Player_3_Start",INI::parseCoord3D,0,0x54},
 {"Player_4_Start",INI::parseCoord3D,0,0x60},
 {"Player_5_Start",INI::parseCoord3D,0,0x6C},
 {"Player_6_Start",INI::parseCoord3D,0,0x78},
 {"Player_7_Start",INI::parseCoord3D,0,0x84},
 {"Player_8_Start",INI::parseCoord3D,0,0x90},
 {"InitialCameraPosition",INI::parseCoord3D,0,0x9C},
 {"PlayerPosition",Rva00535087Parse,0,0},
 {0,0,0,0}
};
struct StringDataView {int refs;unsigned short length,capacity;};
void INI::parseMapCacheDefinition(INI *ini)
{
 AsciiString name;Rva00534E13 mdr;MapMetaData md;
 const char *c=ini->getNextToken(" \n\r\t");
 ((StringBase<char>*)&name)->set(c);
 name=QuotedPrintableToAsciiString(name);
 md.waypoints.clear();
 ini->initFromINI(&mdr,mdr.fieldTable);
 md.extent=mdr.extent;
 md.isOfficial=mdr.official!=0;md.isMultiplayer=mdr.multiplayer!=0;
 md.isScenarioMP=mdr.scenarioMP;md.numPlayers=mdr.numPlayers;
 md.filesize=mdr.filesize;md.crc=mdr.crc;
 md.timestampLo=mdr.timestampLo;md.timestampHi=mdr.timestampHi;
 reinterpret_cast<Coord3D&>((*reinterpret_cast<CoordMapProvider*>(&md.waypoints))[TheNameKeyGenerator->keyToName(TheKey_InitialCameraPosition.key())])=mdr.camera;
 md.displayName=QuotedPrintableToUnicodeString(mdr.displayName);
 md.description=QuotedPrintableToUnicodeString(mdr.nameTag);
 AsciiString startingCamName;
 for(int i=0;i<md.numPlayers;++i) {
  startingCamName.format("Player_%d_Start",i+1);
  reinterpret_cast<Coord3D&>((*reinterpret_cast<CoordMapProvider*>(&md.waypoints))[startingCamName])=mdr.waypoints[i];
 }
 _STL::list<Coord3D>::iterator it=mdr.supplyPositions.begin();
 while(it!=mdr.supplyPositions.end()){md.supplyPositions.push_front(*it);it++;}
 it=mdr.techPositions.begin();
 while(it!=mdr.techPositions.end()){md.techPositions.push_front(*it);it++;}
 md.players=mdr.players;
 const StringDataView *display=*reinterpret_cast<const StringDataView*const*>(&md.displayName);
 if(TheMapCache && display && display->length) {
  AsciiString lowerName=name;lowerName.toLower();md.fileName=lowerName;
  if(!md.isOfficial || TheFileSystem->doesFileExist(md.fileName.str()))
   reinterpret_cast<MapMetaData&>((*reinterpret_cast<Rva00304DC7Map*>(TheMapCache))[lowerName])=md;
 }
}
typedef char MetadataSize[sizeof(MapMetaData)==256?1:-1];
typedef char ReaderSize[sizeof(Rva00534E13)==0x150?1:-1];
