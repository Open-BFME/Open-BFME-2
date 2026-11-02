// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata
// BFME1 GameStateInit.cpp at revision1281192f682ce6f29b8f06b7daea4b5e8fdfbb24
// and ZH GameState.cpp provide the subsystem registration semantics.
// Target2DE641/2137 independently proves all54 token/provider/kind triples,
// null-preserving Snapshot base adjustment+12 and final flag byte+E18.
// Kinds3/4 retain numeric names; their meaning is not inferred from donors.
// The prefix below preserves only the native12-byte base adjustment, not a
// complete SubsystemInterface layout. Snapshot uses its canonical header.
// Named pointer declarations retain the current providers' decorated types;
// casts claim only the Snapshot relationship observed here, not those types'
// complete layouts. Four pointers lack defined current ledger providers:
// target reads their slots at VA E030D8/E02F3C/E01EDC/E01E18 and their
// initial image dwords are zero. The AI-order slot also has an independently
// proven registration name; the other address-derived names retain uncertainty.
// Singleton getters retain their rowed address-derived identities; calls in
// this initializer reach their proven thunks43CCC2 and4E4312. Both five-byte jumps are pinned to their rowed bodies.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
#include "ascii_string.h"
#include "Common/Snapshot.h"
class SnapshotSubsystemPrefix { public: virtual ~SnapshotSubsystemPrefix(); private: char opaque04[8]; };
class SnapshotSubsystemView : public SnapshotSubsystemPrefix, public Snapshot {};
enum SnapshotType { SNAPSHOT_SAVELOAD=0, SNAPSHOT_DEEPCRC_LOGICONLY=1, SNAPSHOT_NATIVE3=3, SNAPSHOT_NATIVE4=4 };
#include "../../../../Include/Common/GameState.h"
void *Rva0043CCC2Get(); void *Rva004E4312GetRoute();
class Rva002BA8F1Logic; 
class AudioManager; extern AudioManager *TheAudio;
class GameState; extern GameState *TheGameState;
struct Rva0023D607Holder; class LinearCampaignManager; extern LinearCampaignManager *TheLinearCampaignManager;
class RadarWindowOverrideSource; extern RadarWindowOverrideSource *theRadarWindowOverrideSource;
void *TheGameStateMap = 0;
class TerrainLogic; extern TerrainLogic *TheTerrainLogic;
class TeamFactory; extern TeamFactory *TheTeamFactory;
class PlayerList; extern PlayerList *ThePlayerList;
class GameLogic; extern GameLogic *TheGameLogic;
class Radar; extern Radar *TheRadar;
class ScriptEngine; extern ScriptEngine *TheScriptEngine;
class SidesList; extern SidesList *TheSidesList;
class View; extern View *TheTacticalView;
class ClientFrameSubsystem; class GameClient; extern GameClient *TheGameClient;
class InGameUI; extern InGameUI *TheInGameUI;
class PartitionManager; extern PartitionManager *ThePartitionManager;
class PartitionManager; extern PartitionManager *TheShroudManager;
class CollisionManager;
extern CollisionManager *TheCollisionManager;
class ParticleSystemManager; extern ParticleSystemManager *TheParticleSystemManager;
class G00DFF080Obj; extern G00DFF080Obj *TheTerrainVisual;
class GhostObjectManager; extern GhostObjectManager *TheGhostObjectManager;
class VictorySystem;
VictorySystem *TheVictorySystem = 0;
class BfmeTaintManager; extern BfmeTaintManager *TheTaintManager;
class GlobalWeatherSystem; extern GlobalWeatherSystem *TheGlobalWeatherSystem;
class Rva002A8F24; extern Rva002A8F24 *TheSkirmishAIManager;
void *TheMineshaftPortalNetworkManager = 0;
// Target initialization registers "TheAiOrdersManager" at VA 0x00E01E18.
// Reuse this existing zero slot under that proven subsystem name.
class AiOrdersManager;
AiOrdersManager *TheAiOrdersManager = 0;
struct Rva0039B95FHolder; extern Rva0039B95FHolder *TheMissionObjectiveTracker;
class Rva00285D34; class Rva002872BA; extern Rva002872BA *TheTriggerManager;
void GameState::init()
{
    addSnapshotBlock("CHUNK_LivingWorldLogic", (Snapshot *)(SnapshotSubsystemView *)(*(Rva002BA8F1Logic **)&TheLivingWorldLogic), (SnapshotType)0);
    addSnapshotBlock("CHUNK_Audio", (Snapshot *)(SnapshotSubsystemView *)TheAudio, (SnapshotType)0);
    addSnapshotBlock("CHUNK_GameState", (Snapshot *)(SnapshotSubsystemView *)TheGameState, (SnapshotType)0);
    addSnapshotBlock("CHUNK_Campaign", (Snapshot *)TheLinearCampaignManager, (SnapshotType)0);
    addSnapshotBlock("CHUNK_Palantir", (Snapshot *)(SnapshotSubsystemView *)theRadarWindowOverrideSource, (SnapshotType)0);
    addSnapshotBlock("CHUNK_GameStateMap", (Snapshot *)(SnapshotSubsystemView *)TheGameStateMap, (SnapshotType)0);
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
    addSnapshotBlock("CHUNK_Collision", (Snapshot *)(SnapshotSubsystemView *)TheCollisionManager, (SnapshotType)0);
    addSnapshotBlock("CHUNK_ParticleSystem", (Snapshot *)(SnapshotSubsystemView *)TheParticleSystemManager, (SnapshotType)0);
    addSnapshotBlock("CHUNK_TerrainVisual", (Snapshot *)TheTerrainVisual, (SnapshotType)0);
    addSnapshotBlock("CHUNK_GhostObject", (Snapshot *)TheGhostObjectManager, (SnapshotType)0);
    addSnapshotBlock("CHUNK_VictorySystem", (Snapshot *)(SnapshotSubsystemView *)TheVictorySystem, (SnapshotType)0);
    addSnapshotBlock("CHUNK_TaintManager", (Snapshot *)(SnapshotSubsystemView *)TheTaintManager, (SnapshotType)0);
    addSnapshotBlock("CHUNK_WeatherSystem", (Snapshot *)(SnapshotSubsystemView *)TheGlobalWeatherSystem, (SnapshotType)0);
    addSnapshotBlock("CHUNK_SkirmishAISystem", (Snapshot *)(SnapshotSubsystemView *)TheSkirmishAIManager, (SnapshotType)0);
    addSnapshotBlock("CHUNK_MineshaftPortalNetworkManager", (Snapshot *)(SnapshotSubsystemView *)TheMineshaftPortalNetworkManager, (SnapshotType)0);
    addSnapshotBlock("CHUNK_AiOrdersManager", (Snapshot *)(SnapshotSubsystemView *)TheAiOrdersManager, (SnapshotType)0);
    addSnapshotBlock("CHUNK_SpellStore", (Snapshot *)Rva0043CCC2Get(), (SnapshotType)0);
    addSnapshotBlock("CHUNK_ObjectivesMenu", (Snapshot *)Rva004E4312GetRoute(), (SnapshotType)0);
    addSnapshotBlock("CHUNK_MissionObjectives", (Snapshot *)(SnapshotSubsystemView *)TheMissionObjectiveTracker, (SnapshotType)0);
    addSnapshotBlock("CHUNK_FireLogicSystem", (Snapshot *)(SnapshotSubsystemView *)TheTriggerManager, (SnapshotType)0);
    addSnapshotBlock("CHUNK_TeamFactory", (Snapshot *)(SnapshotSubsystemView *)TheTeamFactory, (SnapshotType)1);
    addSnapshotBlock("CHUNK_Players", (Snapshot *)(SnapshotSubsystemView *)ThePlayerList, (SnapshotType)1);
    addSnapshotBlock("CHUNK_GameLogic", (Snapshot *)(SnapshotSubsystemView *)TheGameLogic, (SnapshotType)1);
    addSnapshotBlock("CHUNK_ScriptEngine", (Snapshot *)(SnapshotSubsystemView *)TheScriptEngine, (SnapshotType)1);
    addSnapshotBlock("CHUNK_SidesList", (Snapshot *)(SnapshotSubsystemView *)TheSidesList, (SnapshotType)1);
    addSnapshotBlock("CHUNK_Partition", (Snapshot *)(SnapshotSubsystemView *)ThePartitionManager, (SnapshotType)1);
    addSnapshotBlock("CHUNK_Shroud", (Snapshot *)(SnapshotSubsystemView *)TheShroudManager, (SnapshotType)1);
    addSnapshotBlock("CHUNK_Collision", (Snapshot *)(SnapshotSubsystemView *)TheCollisionManager, (SnapshotType)1);
    addSnapshotBlock("CHUNK_SkirmishAISystem", (Snapshot *)(SnapshotSubsystemView *)TheSkirmishAIManager, (SnapshotType)1);
    addSnapshotBlock("CHUNK_LivingWorldLogic", (Snapshot *)(SnapshotSubsystemView *)(*(Rva002BA8F1Logic **)&TheLivingWorldLogic), (SnapshotType)3);
    addSnapshotBlock("CHUNK_Audio", (Snapshot *)(SnapshotSubsystemView *)TheAudio, (SnapshotType)3);
    addSnapshotBlock("CHUNK_GameState", (Snapshot *)(SnapshotSubsystemView *)TheGameState, (SnapshotType)3);
    addSnapshotBlock("CHUNK_Campaign", (Snapshot *)TheLinearCampaignManager, (SnapshotType)3);
    addSnapshotBlock("CHUNK_Palantir", (Snapshot *)(SnapshotSubsystemView *)theRadarWindowOverrideSource, (SnapshotType)3);
    addSnapshotBlock("CHUNK_GameStateMap", (Snapshot *)(SnapshotSubsystemView *)TheGameStateMap, (SnapshotType)3);
    addSnapshotBlock("CHUNK_GameLogic", (Snapshot *)(SnapshotSubsystemView *)TheGameLogic, (SnapshotType)3);
    addSnapshotBlock("CHUNK_LivingWorldLogic", (Snapshot *)(SnapshotSubsystemView *)(*(Rva002BA8F1Logic **)&TheLivingWorldLogic), (SnapshotType)4);
    addSnapshotBlock("CHUNK_Audio", (Snapshot *)(SnapshotSubsystemView *)TheAudio, (SnapshotType)4);
    addSnapshotBlock("CHUNK_GameState", (Snapshot *)(SnapshotSubsystemView *)TheGameState, (SnapshotType)4);
    addSnapshotBlock("CHUNK_Campaign", (Snapshot *)TheLinearCampaignManager, (SnapshotType)4);
    addSnapshotBlock("CHUNK_GameStateMap", (Snapshot *)(SnapshotSubsystemView *)TheGameStateMap, (SnapshotType)4);
    addSnapshotBlock("CHUNK_GameLogic", (Snapshot *)(SnapshotSubsystemView *)TheGameLogic, (SnapshotType)4);
    m_isInLoadGame = false;
}
