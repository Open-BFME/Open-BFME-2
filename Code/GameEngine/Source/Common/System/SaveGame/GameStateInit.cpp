// cl: /O1 /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata
// BFME1 GameStateInit.cpp at revision1281192f682ce6f29b8f06b7daea4b5e8fdfbb24
// and ZH GameState.cpp provide the subsystem registration semantics.
// Target2DE641/2137 independently proves all54 token/provider/kind triples,
// null-preserving Snapshot base adjustment+12 and final flag byte+E18.
// Kinds3/4 retain numeric names; their meaning is not inferred from donors.
// The prefix below preserves only the native12-byte base adjustment, not a
// complete SubsystemInterface layout. Snapshot uses its canonical header.
// Named pointer declarations retain the current providers' decorated types;
// casts claim only the Snapshot relationship observed here, not those types'
// complete layouts. Five pointers lacked defined current ledger providers:
// target reads their slots at VA E030D8/E02F3C/DFE750/E01EDC/E01E18 and their
// initial image dwords are zero. Address-derived names retain that uncertainty.
// Singleton getters retain their rowed address-derived identities; calls in
// this initializer reach their proven thunks43CCC2 and4E4312. Both five-byte jumps are pinned to their rowed bodies.
#include "ascii_string.h"
#include "Common/Snapshot.h"
class SnapshotSubsystemPrefix { public: virtual ~SnapshotSubsystemPrefix(); private: char opaque04[8]; };
class SnapshotSubsystemView : public SnapshotSubsystemPrefix, public Snapshot {};
enum SnapshotType { SNAPSHOT_SAVELOAD=0, SNAPSHOT_DEEPCRC_LOGICONLY=1, SNAPSHOT_NATIVE3=3, SNAPSHOT_NATIVE4=4 };
class GameState : public SnapshotSubsystemPrefix, public Snapshot {
public: virtual void init();
private: void addSnapshotBlock(AsciiString, Snapshot *, SnapshotType); char opaque10[0xE08]; bool m_isInLoadGame;
};
void *Rva0043CCC2GetRoute(); void *Rva004E4312GetRoute();
#pragma comment(linker, "/alternatename:?Rva0043CCC2GetRoute@@YAPAXXZ=?Rva0043C9B3Get@@YAPAXXZ")
#pragma comment(linker, "/alternatename:?Rva004E4312GetRoute@@YAPAXXZ=?Rva004E4179Get@@YAPAXXZ")
class Rva002BA8F1Logic; extern Rva002BA8F1Logic *g_009FEF10;
class AudioManager; extern AudioManager *TheAudio;
class GameState; extern GameState *TheGameState;
struct Rva0023D607Holder; extern Rva0023D607Holder *g_Rva0023D607Holder;
class Rva002D3627Host; extern Rva002D3627Host *TheRva002D3627Host;
void *g_Va00E030D8 = 0;
class TerrainLogic; extern TerrainLogic *TheTerrainLogic;
class TeamFactory; extern TeamFactory *TheTeamFactory;
class PlayerList; extern PlayerList *ThePlayerList;
class GameLogic; extern GameLogic *TheGameLogic;
class Radar; extern Radar *TheRadar;
class ScriptEngine; extern ScriptEngine *TheScriptEngine;
class SidesList; extern SidesList *TheSidesList;
class View; extern View *TheTacticalView;
class ClientFrameSubsystem; extern ClientFrameSubsystem *TheGameClient;
class InGameUI; extern InGameUI *TheInGameUI;
class PartitionManager; extern PartitionManager *ThePartitionManager;
class PartitionManager; extern PartitionManager *TheShroudManager;
extern void *g_Va00DFE754;
class ParticleSystemManager; extern ParticleSystemManager *TheParticleSystemManager;
class G00DFF080Obj; extern G00DFF080Obj *g_00DFF080;
class GhostObjectManager; extern GhostObjectManager *TheGhostObjectManager;
void *g_Va00E02F3C = 0;
void *g_Va00DFE750 = 0;
class GlobalWeatherSystem; extern GlobalWeatherSystem *TheGlobalWeatherSystem;
class Rva002A8F24; extern Rva002A8F24 *g_00DFEEF8;
void *g_Va00E01EDC = 0;
void *g_Va00E01E18 = 0;
struct Rva0039B95FHolder; extern Rva0039B95FHolder *g_00E031E8;
class Rva00285D34; extern Rva00285D34 *g_00DFEC68;
void GameState::init()
{
    addSnapshotBlock("CHUNK_LivingWorldLogic", (Snapshot *)(SnapshotSubsystemView *)g_009FEF10, (SnapshotType)0);
    addSnapshotBlock("CHUNK_Audio", (Snapshot *)(SnapshotSubsystemView *)TheAudio, (SnapshotType)0);
    addSnapshotBlock("CHUNK_GameState", (Snapshot *)(SnapshotSubsystemView *)TheGameState, (SnapshotType)0);
    addSnapshotBlock("CHUNK_Campaign", (Snapshot *)g_Rva0023D607Holder, (SnapshotType)0);
    addSnapshotBlock("CHUNK_Palantir", (Snapshot *)(SnapshotSubsystemView *)TheRva002D3627Host, (SnapshotType)0);
    addSnapshotBlock("CHUNK_GameStateMap", (Snapshot *)(SnapshotSubsystemView *)g_Va00E030D8, (SnapshotType)0);
    addSnapshotBlock("CHUNK_TerrainLogic", (Snapshot *)TheTerrainLogic, (SnapshotType)0);
    addSnapshotBlock("CHUNK_TeamFactory", (Snapshot *)(SnapshotSubsystemView *)TheTeamFactory, (SnapshotType)0);
    addSnapshotBlock("CHUNK_Players", (Snapshot *)(SnapshotSubsystemView *)ThePlayerList, (SnapshotType)0);
    addSnapshotBlock("CHUNK_GameLogic", (Snapshot *)(SnapshotSubsystemView *)TheGameLogic, (SnapshotType)0);
    addSnapshotBlock("CHUNK_Radar", (Snapshot *)TheRadar, (SnapshotType)0);
    addSnapshotBlock("CHUNK_ScriptEngine", (Snapshot *)(SnapshotSubsystemView *)TheScriptEngine, (SnapshotType)0);
    addSnapshotBlock("CHUNK_SidesList", (Snapshot *)(SnapshotSubsystemView *)TheSidesList, (SnapshotType)0);
    addSnapshotBlock("CHUNK_TacticalView", (Snapshot *)TheTacticalView, (SnapshotType)0);
    addSnapshotBlock("CHUNK_GameClient", (Snapshot *)(SnapshotSubsystemView *)TheGameClient, (SnapshotType)0);
    addSnapshotBlock("CHUNK_InGameUI", (Snapshot *)(SnapshotSubsystemView *)TheInGameUI, (SnapshotType)0);
    addSnapshotBlock("CHUNK_Partition", (Snapshot *)(SnapshotSubsystemView *)ThePartitionManager, (SnapshotType)0);
    addSnapshotBlock("CHUNK_Shroud", (Snapshot *)(SnapshotSubsystemView *)TheShroudManager, (SnapshotType)0);
    addSnapshotBlock("CHUNK_Collision", (Snapshot *)(SnapshotSubsystemView *)g_Va00DFE754, (SnapshotType)0);
    addSnapshotBlock("CHUNK_ParticleSystem", (Snapshot *)(SnapshotSubsystemView *)TheParticleSystemManager, (SnapshotType)0);
    addSnapshotBlock("CHUNK_TerrainVisual", (Snapshot *)g_00DFF080, (SnapshotType)0);
    addSnapshotBlock("CHUNK_GhostObject", (Snapshot *)TheGhostObjectManager, (SnapshotType)0);
    addSnapshotBlock("CHUNK_VictorySystem", (Snapshot *)(SnapshotSubsystemView *)g_Va00E02F3C, (SnapshotType)0);
    addSnapshotBlock("CHUNK_TaintManager", (Snapshot *)(SnapshotSubsystemView *)g_Va00DFE750, (SnapshotType)0);
    addSnapshotBlock("CHUNK_WeatherSystem", (Snapshot *)(SnapshotSubsystemView *)TheGlobalWeatherSystem, (SnapshotType)0);
    addSnapshotBlock("CHUNK_SkirmishAISystem", (Snapshot *)(SnapshotSubsystemView *)g_00DFEEF8, (SnapshotType)0);
    addSnapshotBlock("CHUNK_MineshaftPortalNetworkManager", (Snapshot *)(SnapshotSubsystemView *)g_Va00E01EDC, (SnapshotType)0);
    addSnapshotBlock("CHUNK_AiOrdersManager", (Snapshot *)(SnapshotSubsystemView *)g_Va00E01E18, (SnapshotType)0);
    addSnapshotBlock("CHUNK_SpellStore", (Snapshot *)Rva0043CCC2GetRoute(), (SnapshotType)0);
    addSnapshotBlock("CHUNK_ObjectivesMenu", (Snapshot *)Rva004E4312GetRoute(), (SnapshotType)0);
    addSnapshotBlock("CHUNK_MissionObjectives", (Snapshot *)(SnapshotSubsystemView *)g_00E031E8, (SnapshotType)0);
    addSnapshotBlock("CHUNK_FireLogicSystem", (Snapshot *)(SnapshotSubsystemView *)g_00DFEC68, (SnapshotType)0);
    addSnapshotBlock("CHUNK_TeamFactory", (Snapshot *)(SnapshotSubsystemView *)TheTeamFactory, (SnapshotType)1);
    addSnapshotBlock("CHUNK_Players", (Snapshot *)(SnapshotSubsystemView *)ThePlayerList, (SnapshotType)1);
    addSnapshotBlock("CHUNK_GameLogic", (Snapshot *)(SnapshotSubsystemView *)TheGameLogic, (SnapshotType)1);
    addSnapshotBlock("CHUNK_ScriptEngine", (Snapshot *)(SnapshotSubsystemView *)TheScriptEngine, (SnapshotType)1);
    addSnapshotBlock("CHUNK_SidesList", (Snapshot *)(SnapshotSubsystemView *)TheSidesList, (SnapshotType)1);
    addSnapshotBlock("CHUNK_Partition", (Snapshot *)(SnapshotSubsystemView *)ThePartitionManager, (SnapshotType)1);
    addSnapshotBlock("CHUNK_Shroud", (Snapshot *)(SnapshotSubsystemView *)TheShroudManager, (SnapshotType)1);
    addSnapshotBlock("CHUNK_Collision", (Snapshot *)(SnapshotSubsystemView *)g_Va00DFE754, (SnapshotType)1);
    addSnapshotBlock("CHUNK_SkirmishAISystem", (Snapshot *)(SnapshotSubsystemView *)g_00DFEEF8, (SnapshotType)1);
    addSnapshotBlock("CHUNK_LivingWorldLogic", (Snapshot *)(SnapshotSubsystemView *)g_009FEF10, (SnapshotType)3);
    addSnapshotBlock("CHUNK_Audio", (Snapshot *)(SnapshotSubsystemView *)TheAudio, (SnapshotType)3);
    addSnapshotBlock("CHUNK_GameState", (Snapshot *)(SnapshotSubsystemView *)TheGameState, (SnapshotType)3);
    addSnapshotBlock("CHUNK_Campaign", (Snapshot *)g_Rva0023D607Holder, (SnapshotType)3);
    addSnapshotBlock("CHUNK_Palantir", (Snapshot *)(SnapshotSubsystemView *)TheRva002D3627Host, (SnapshotType)3);
    addSnapshotBlock("CHUNK_GameStateMap", (Snapshot *)(SnapshotSubsystemView *)g_Va00E030D8, (SnapshotType)3);
    addSnapshotBlock("CHUNK_GameLogic", (Snapshot *)(SnapshotSubsystemView *)TheGameLogic, (SnapshotType)3);
    addSnapshotBlock("CHUNK_LivingWorldLogic", (Snapshot *)(SnapshotSubsystemView *)g_009FEF10, (SnapshotType)4);
    addSnapshotBlock("CHUNK_Audio", (Snapshot *)(SnapshotSubsystemView *)TheAudio, (SnapshotType)4);
    addSnapshotBlock("CHUNK_GameState", (Snapshot *)(SnapshotSubsystemView *)TheGameState, (SnapshotType)4);
    addSnapshotBlock("CHUNK_Campaign", (Snapshot *)g_Rva0023D607Holder, (SnapshotType)4);
    addSnapshotBlock("CHUNK_GameStateMap", (Snapshot *)(SnapshotSubsystemView *)g_Va00E030D8, (SnapshotType)4);
    addSnapshotBlock("CHUNK_GameLogic", (Snapshot *)(SnapshotSubsystemView *)TheGameLogic, (SnapshotType)4);
    m_isInLoadGame = false;
}
