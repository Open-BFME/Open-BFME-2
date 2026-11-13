// cl: /ICode/Libraries/Include/Lib /Ireference/shims/bfme2_ascii /O1 /Ob2 /EHsc /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
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
#include "Coord3D.h"
#include "../../../Libraries/Include/Lib/Region3D.h"
typedef _STL::list<Coord3D> Coord3DList;
class WaypointMap : public _STL::map<AsciiString,Coord3D> { public: int numStartSpots; };
#include "../../Include/Common/PlayerPosition.h"
struct MapPlayers { PlayerPosition items[8]; };
#include "../../Include/GameClient/MapMetaData.h"
// The canonical header keeps the STL members opaque; this TU's typed views.
static inline WaypointMap &waypointsOf(MapMetaData &md) { return reinterpret_cast<WaypointMap &>(md.field38); }
static inline Coord3DList &supplyOf(MapMetaData &md) { return reinterpret_cast<Coord3DList &>(md.field48); }
static inline Coord3DList &techOf(MapMetaData &md) { return reinterpret_cast<Coord3DList &>(md.field4C); }
static inline MapPlayers &playersOf(MapMetaData &md) { return reinterpret_cast<MapPlayers &>(md.field54); }
struct BfmeInnerSX { unsigned char m_bfmeRawSX[12]; };
struct BfmeKeySX { char a,b,c,pad; int team; BfmeInnerSX factions; };
int __cdecl bfmeEqualSX(const BfmeKeySX &,const BfmeKeySX &);
#include "../../Include/Common/GlobalData.h"
extern GlobalData *TheWritableGlobalData;
class FileSystem;
extern FileSystem *TheFileSystem;
#include "../../Include/GameClient/Rva003006C4.h"
#include "../../Include/Common/Rva00300D7A.h"
AsciiString AsciiStringToQuotedPrintable(AsciiString);
AsciiString UnicodeStringToQuotedPrintable(UnicodeString);
#include "../../Include/GameClient/MapCache.h"
static __forceinline void appendCharacter(AsciiString &dst,char c)
{ ((StringBase<char> *)&dst)->concat(&c,1); }
void MapCache::writeCacheINI(bool userDir)
{
    AsciiString mapDir;
    if (!userDir || TheWritableGlobalData->field0AB5)
        mapDir = ((Rva00300489 *)this)->Rva00300489::getMapDir();
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
    const char *no = "no"; const char *yes = "yes";
    MapCache::iterator it = begin();
    MapMetaData md;
    while (it != end()) {
        if (it->first.startsWithNoCase(mapDir.str())) {
            md = it->second;
            fprintf(fp,"\nMapCache %s\n",AsciiStringToQuotedPrintable(it->first.str()).str());
            fprintf(fp,"  fileSize = %u\n",md.m_filesize);
            fprintf(fp,"  fileCRC = %u\n",md.m_CRC);
            fprintf(fp,"  timestampLo = %d\n",md.field30);
            fprintf(fp,"  timestampHi = %d\n",md.field34);
            fprintf(fp,"  isOfficial = %s\n",md.m_isOfficial ? yes : no);
            fprintf(fp,"  isMultiplayer = %s\n",md.m_isMultiplayer ? yes : no);
            // Keep the last label selection explicit: VC7.1 then retains
            // retail's shared "no" register across all three map flags.
            {
                const char *scenarioLabel = no;
                if (md.m_isScenarioMP) scenarioLabel = yes;
                fprintf(fp,"  isScenarioMP = %s\n",scenarioLabel);
            }
            fprintf(fp,"  numPlayers = %d\n",md.m_numPlayers);
            fprintf(fp,"  extentMin = X:%2.2f Y:%2.2f Z:%2.2f\n",md.m_extent.lo.x,md.m_extent.lo.y,md.m_extent.lo.z);
            fprintf(fp,"  extentMax = X:%2.2f Y:%2.2f Z:%2.2f\n",md.m_extent.hi.x,md.m_extent.hi.y,md.m_extent.hi.z);
            fprintf(fp,"  displayName = %s\n",UnicodeStringToQuotedPrintable(md.m_displayName).str());
            fprintf(fp,"  description = %s\n",UnicodeStringToQuotedPrintable(md.m_description).str());
            Coord3D pos;
            WaypointMap::iterator itw = waypointsOf(md).begin();
            while (itw != waypointsOf(md).end()) {
                pos = itw->second;
                fprintf(fp,"  %s = X:%2.2f Y:%2.2f Z:%2.2f\n",itw->first.str(),pos.x,pos.y,pos.z);
                ++itw;
            }
            Coord3DList::iterator itc3d = techOf(md).begin();
            while (itc3d._M_node != techOf(md).end()._M_node) {
                pos = *itc3d;
                fprintf(fp,"  techPosition = X:%2.2f Y:%2.2f Z:%2.2f\n",pos.x,pos.y,pos.z);
                itc3d++;
            }
            itc3d = supplyOf(md).begin();
            while (itc3d._M_node != supplyOf(md).end()._M_node) {
                pos = *itc3d;
                fprintf(fp,"  supplyPosition = X:%2.2f Y:%2.2f Z:%2.2f\n",pos.x,pos.y,pos.z);
                itc3d++;
            }
            const PlayerPosition *position=playersOf(md).items;
            for (int i=0;i<8;++i,++position) {
                static PlayerPosition defaults;
                if (!(unsigned char)bfmeEqualSX(*(const BfmeKeySX *)position,*(const BfmeKeySX *)&defaults)) {
                fprintf(fp,"  PlayerPosition %d\n",i+1);
                fprintf(fp,"    Human = %s\n",position->human ? "Yes" : "No");
                // Preserve the native cursor at the computer flag rather than loadAIScripts.
                // The same-valued conditional preserves the native field1 cursor.
                fprintf(fp,"    Computer = %s\n",(position->computer ? position->computer : position->computer) ? "Yes" : "No");
                fprintf(fp,"    LoadAIScripts = %s\n",position->loadAIScripts ? "Yes" : "No");
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
