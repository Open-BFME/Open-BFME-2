// ?writeCacheINI@MapCache@@AAEX_N@Z
// partial score=0.99 date=2026-10-08
// cl: /Ireference/shims/bfme2_ascii /O1 /Ob2 /EHsc /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Reference semantics: ZH GeneralsMD GameClient/MapUtil.cpp writeCacheINI.
// BFME1 reference checkout dae380faa5f6fa536eec8d6ebbe877321d4cb51d.
// Target identity: WB writeCacheINI at C59880, MapUtil.cpp:703; retail
// 303409..3039E8. Target adds wide fopen, descriptions and player positions.
// MapMetaData's 256-byte layout is cross-checked by rowed assignment30328D
// and copy3039E8. Unknown wordF4 is deliberately uninterpreted.
#include <stdio.h>
#include <list>
#include <map>
#include <set>
#include "ascii_string.h"
#include "unicode_string.h"
#include "../../../Libraries/Include/Lib/Coord3D.h"
struct Region3D { Coord3D lo,hi; };
typedef _STL::list<Coord3D> Coord3DList;
class WaypointMap : public _STL::map<AsciiString,Coord3D> { public: int numStartSpots; };
struct PlayerPosition { bool human,computer,loadAIScripts; int forceTeam; _STL::set<AsciiString> factions; PlayerPosition(); ~PlayerPosition(); };
struct MapPlayers { PlayerPosition items[8]; };
class MapMetaData {
public:
    UnicodeString displayName,description; Region3D extent; int numPlayers;
    bool isMultiplayer,isScenarioMP,isOfficial;
    unsigned int filesize,crc,timestampLo,timestampHi;
    WaypointMap waypoints; Coord3DList supplyPositions,techPositions;
    AsciiString fileName; MapPlayers players; unsigned int wordF4;
    UnicodeString cachedDisplayName,cachedDescription;
    MapMetaData(); ~MapMetaData(); MapMetaData &operator=(const MapMetaData &);
};
typedef char SizeCheck[sizeof(MapMetaData)==0x100?1:-1];
struct BfmeInnerSX { unsigned char m_bfmeRawSX[12]; };
struct BfmeKeySX { char a,b,c,pad; int team; BfmeInnerSX factions; };
int __cdecl bfmeEqualSX(const BfmeKeySX &,const BfmeKeySX &);
class GlobalData { public: char opaque[0xAB5]; bool buildMapCache; };
extern GlobalData *TheWritableGlobalData;
class FileSystem;
extern FileSystem *TheFileSystem;
class Rva003006C4 { public: bool rva003006C4(const AsciiString &); };
class Rva00300489 { public: virtual AsciiString rva00300489() const; };
class Rva00300D7A : public Rva00300489 { public: AsciiString rva00300D7A(); };
AsciiString AsciiStringToQuotedPrintable(AsciiString);
AsciiString UnicodeStringToQuotedPrintable(UnicodeString);
class MapCache : public _STL::map<AsciiString,MapMetaData> {
    void writeCacheINI(bool);
};
static __forceinline void appendCharacter(AsciiString &dst,char c)
{ ((StringBase<char> *)&dst)->concat(&c,1); }
void MapCache::writeCacheINI(bool userDir)
{
    AsciiString mapDir;
    if (!userDir || TheWritableGlobalData->buildMapCache)
        mapDir = ((Rva00300489 *)this)->Rva00300489::rva00300489();
    else
        mapDir = ((Rva00300D7A *)this)->rva00300D7A();
    AsciiString filepath = mapDir;
    appendCharacter(filepath,'\\');
    ((Rva003006C4 *)TheFileSystem)->rva003006C4(mapDir);
    filepath.concat("MapCache.ini");
    UnicodeString unicodePath(filepath);
    FILE *fp = _wfopen((const wchar_t *)unicodePath.str(),L"w");
    if (fp == 0) return;
    fprintf(fp,"; FILE: %s /////////////////////////////////////////////////////////////\n",filepath.str());
    fprintf(fp,"; This INI file is auto-generated - do not modify\n");
    fprintf(fp,"; /////////////////////////////////////////////////////////////////////////////\n");
    mapDir.toLower();
    MapCache::iterator it = begin();
    MapMetaData md;
    while (it != end()) {
        if (it->first.startsWithNoCase(mapDir.str())) {
            md = it->second;
            fprintf(fp,"\nMapCache %s\n",AsciiStringToQuotedPrintable(it->first.str()).str());
            fprintf(fp,"  fileSize = %u\n",md.filesize);
            fprintf(fp,"  fileCRC = %u\n",md.crc);
            fprintf(fp,"  timestampLo = %d\n",md.timestampLo);
            fprintf(fp,"  timestampHi = %d\n",md.timestampHi);
            fprintf(fp,"  isOfficial = %s\n",md.isOfficial ? "yes" : "no");
            fprintf(fp,"  isMultiplayer = %s\n",md.isMultiplayer ? "yes" : "no");
            fprintf(fp,"  isScenarioMP = %s\n",md.isScenarioMP ? "yes" : "no");
            fprintf(fp,"  numPlayers = %d\n",md.numPlayers);
            fprintf(fp,"  extentMin = X:%2.2f Y:%2.2f Z:%2.2f\n",md.extent.lo.x,md.extent.lo.y,md.extent.lo.z);
            fprintf(fp,"  extentMax = X:%2.2f Y:%2.2f Z:%2.2f\n",md.extent.hi.x,md.extent.hi.y,md.extent.hi.z);
            fprintf(fp,"  displayName = %s\n",UnicodeStringToQuotedPrintable(md.displayName).str());
            fprintf(fp,"  description = %s\n",UnicodeStringToQuotedPrintable(md.description).str());
            Coord3D pos;
            WaypointMap::iterator itw = md.waypoints.begin();
            while (itw != md.waypoints.end()) {
                pos = itw->second;
                fprintf(fp,"  %s = X:%2.2f Y:%2.2f Z:%2.2f\n",itw->first.str(),pos.x,pos.y,pos.z);
                ++itw;
            }
            Coord3DList::iterator itc3d = md.techPositions.begin();
            while (itc3d != md.techPositions.end()) {
                pos = *itc3d;
                fprintf(fp,"  techPosition = X:%2.2f Y:%2.2f Z:%2.2f\n",pos.x,pos.y,pos.z);
                itc3d++;
            }
            itc3d = md.supplyPositions.begin();
            while (itc3d != md.supplyPositions.end()) {
                pos = *itc3d;
                fprintf(fp,"  supplyPosition = X:%2.2f Y:%2.2f Z:%2.2f\n",pos.x,pos.y,pos.z);
                itc3d++;
            }
            const PlayerPosition *position=md.players.items;
            for (int i=0;i<8;++i,++position) {
                static PlayerPosition defaults;
                if (!(unsigned char)bfmeEqualSX(*(const BfmeKeySX *)position,*(const BfmeKeySX *)&defaults)) {
                fprintf(fp,"  PlayerPosition %d\n",i+1);
                fprintf(fp,"    Human = %s\n",position->human ? "yes" : "no");
                fprintf(fp,"    Computer = %s\n",position->computer ? "yes" : "no");
                fprintf(fp,"    LoadAIScripts = %s\n",position->loadAIScripts ? "yes" : "no");
                fprintf(fp,"    ForcePlayerTeam = %d\n",position->forceTeam);
                if (!position->factions.empty()) {
                    fprintf(fp,"    AllowedFactions =");
                    _STL::set<AsciiString>::const_iterator faction=position->factions.begin();
                    while (faction != position->factions.end()) {
                        fprintf(fp," %s",faction->str());
                        ++faction;
                    }
                    fprintf(fp,"\n");
                }
                fprintf(fp,"  END\n");
                }
            }
            fprintf(fp,"END\n\n");
        }
        ++it;
    }
    fclose(fp);
}
