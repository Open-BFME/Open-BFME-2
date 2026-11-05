// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// ?doRadarRefresh@ScriptActions@@QAEXXZ @0x003BC1A0 18B: script forwards TheTerrainLogic to TheRadar slot 0x10.
// Evidence: mov ecx,[0xDFF070]=TheRadar push [0xDFEC50]=TheTerrainLogic mov eax,[ecx] call [eax+0x10] ret; caller 0x003CC86C.
#include "../../../Include/Common/Radar.h"
extern TerrainLogic *TheTerrainLogic;

void ScriptActions::doRadarRefresh()
{
	TheRadar->refreshTerrain(TheTerrainLogic);
}
