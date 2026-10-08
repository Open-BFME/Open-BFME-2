// cl: /O1 /Ireference/shims/bfme2_ascii /Ireference/shims/ini_bfme2 /Ireference/shims/subsystem_bfme2 /Ireference/shims/moduledata /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/open-bfme-1/Code/GameEngine/Source/Common/System /Ireference/open-bfme-1/Code/GameEngine/Include /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
// stlport
//
// BFME's SubsystemInterface, built against the native headers. The ZH-tree port
// in SubsystemInterface.cpp keeps ZH's behaviour (its dtor unregisters from
// TheSubsystemList); BFME's is empty — 0x009A1A40 is just "restore the vptr,
// then tail-jump to destroy m_name", which only comes out of an empty body and
// an out-of-line AsciiString dtor.
//
// The base vtable is at 0x01141640 and has nine slots. SubsystemLegend overrides
// 0/1/4/5 and inherits 2/3/6/7/8, which is how those five were ruled out of
// SubsystemLegend.cpp's membership.
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

#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include "PreRTS.h"
#include "subsystem_interface.h"
#include "subsystem_legend.h"
#include "Common/INI/INI.h"
#include "game_engine_subsystems.h"
#include "Common/Snapshot.h"

SubsystemInterfaceList *TheSubsystemList;		// BFME1 0x0134C6C8

// Retail 0x001B4E63 (rowed under a placeholder name): vptr, m_name's null
// buffer at +0x08, then the +0x04 byte cleared in the body.
SubsystemInterface::SubsystemInterface()
{
	m_flag = FALSE;
}

SubsystemInterface::~SubsystemInterface()
{
}

// ?getName@SubsystemInterface@@QAE?AVAsciiString@@XZ present-unmatched
AsciiString SubsystemInterface::getName(void)
{
	return m_name;
}

// ?loadIniFilesFromLegend@SubsystemInterface@@UAE_NXZ present-unmatched
// Vtable slot 2, inherited by every subsystem in the game. This is the whole
// point of SubsystemLegend: a subsystem looks itself up by name and loads the
// INI files and directories its "LoadSubsystem" block lists. The Bool it returns
// tells SubsystemInterfaceList::initSubsystem whether the legend supplied
// anything — if it did, the hard-coded paths GameEngine::init passed are skipped.
Bool SubsystemInterface::loadIniFilesFromLegend()
{
	if (!TheSubsystemLegend)
		return FALSE;

	// Declared before the lookup, not after: retail's xor bl,bl lands ahead of
	// the getName call, which only happens if the local is live by then.
	Bool loadedAny = FALSE;

	SubsystemLegendEntry *entry = TheSubsystemLegend->findEntry(getName());
	if (!entry)
		return FALSE;

	INI ini;

	// The xfer goes through a local rather than being written inline as the call
	// argument. That is what retail's register allocation says: it holds
	// TheSubsystemList->m_xfer in eax across both loops, which only happens when
	// the load is its own statement.
	for (AsciiString *f = entry->m_initFile.begin(); f != entry->m_initFile.end(); ++f)
	{
		Xfer *xfer = TheSubsystemList->m_xfer;
		loadedAny = TRUE;
		ini.loadFile(*f, INI_LOAD_OVERWRITE, xfer);
	}

	for (AsciiString *d = entry->m_initPath.begin(); d != entry->m_initPath.end(); ++d)
	{
		Xfer *xfer = TheSubsystemList->m_xfer;
		loadedAny = TRUE;
		ini.loadDirectory(*d, true, INI_LOAD_OVERWRITE, xfer, 0);
	}

	return loadedAny;
}

// ?initSubsystem@SubsystemInterfaceList@@QAEXPAVSubsystemInterface@@PAXPBD22PAVXfer@@VAsciiString@@@Z
// Name it, init it, then give the legend first refusal: if the subsystem's
// "LoadSubsystem" block supplied any files, the hard-coded paths GameEngine::init
// passed are skipped entirely. That precedence is the interesting part for anyone
// editing SubsystemLegend.ini.
void SubsystemInterfaceList::initSubsystem(SubsystemInterface *sys, void *slot, const char *path1,
										   const char *path2, const char *dirpath, Xfer *pXfer,
										   AsciiString name)
{
	sys->setName(name);
	sys->init();

	Bool loadedFromLegend = sys->loadIniFilesFromLegend();

	m_subsystems.push_back(std::make_pair(sys, slot));

	if (!loadedFromLegend)
	{
		INI ini;
		if (path1)
			ini.loadFile(path1, INI_LOAD_OVERWRITE, pXfer);
		if (path2)
			ini.loadFile(path2, INI_LOAD_OVERWRITE, pXfer);
		if (dirpath)
			ini.loadDirectory(dirpath, true, INI_LOAD_OVERWRITE, pXfer, 0);
	}
}

// ??$initSubsystem@VSubsystemLegend@@@@YAXAAPAVSubsystemLegend@@VAsciiString@@PAV0@PAVXfer@@PBD44@Z
// Force the SubsystemLegend instantiation retail carries at 0x00072DD0.
template void initSubsystem<SubsystemLegend>(SubsystemLegend *&, AsciiString, SubsystemLegend *,
											 Xfer *, const char *, const char *, const char *);

// The other instantiations GameEngine::init carries, one per subsystem, laid out
// consecutively from 0x00072DD0 at 192 bytes apiece.
template void initSubsystem<UpgradeCenter>(UpgradeCenter *&, AsciiString, UpgradeCenter *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<TerrainRoadCollection>(TerrainRoadCollection *&, AsciiString, TerrainRoadCollection *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<SidesList>(SidesList *&, AsciiString, SidesList *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<WeaponStore>(WeaponStore *&, AsciiString, WeaponStore *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<ObjectCreationListStore>(ObjectCreationListStore *&, AsciiString, ObjectCreationListStore *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<PlayerTemplateStore>(PlayerTemplateStore *&, AsciiString, PlayerTemplateStore *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<ArmorStore>(ArmorStore *&, AsciiString, ArmorStore *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<DamageFXStore>(DamageFXStore *&, AsciiString, DamageFXStore *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<AI>(AI *&, AsciiString, AI *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<TeamFactory>(TeamFactory *&, AsciiString, TeamFactory *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<CrateSystem>(CrateSystem *&, AsciiString, CrateSystem *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<PlayerList>(PlayerList *&, AsciiString, PlayerList *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<GameState>(GameState *&, AsciiString, GameState *, Xfer *, const char *, const char *, const char *);

// Named from the global each GameEngine::init registration site passes by
// reference -- see game_engine_subsystems.h for why that is proof.
template void initSubsystem<GlobalData>(GlobalData *&, AsciiString, GlobalData *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<AudioManager>(AudioManager *&, AsciiString, AudioManager *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<MultiplayerSettings>(MultiplayerSettings *&, AsciiString, MultiplayerSettings *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<FunctionLexicon>(FunctionLexicon *&, AsciiString, FunctionLexicon *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<MessageStream>(MessageStream *&, AsciiString, MessageStream *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<ParticleSystemManager>(ParticleSystemManager *&, AsciiString, ParticleSystemManager *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<FXListStore>(FXListStore *&, AsciiString, FXListStore *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<LocomotorStore>(LocomotorStore *&, AsciiString, LocomotorStore *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<SpecialPowerStore>(SpecialPowerStore *&, AsciiString, SpecialPowerStore *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<ThingFactory>(ThingFactory *&, AsciiString, ThingFactory *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<ScriptEngine>(ScriptEngine *&, AsciiString, ScriptEngine *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<GameLogic>(GameLogic *&, AsciiString, GameLogic *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<RecorderClass>(RecorderClass *&, AsciiString, RecorderClass *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<ActionManager>(ActionManager *&, AsciiString, ActionManager *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<ScienceStore>(ScienceStore *&, AsciiString, ScienceStore *, Xfer *, const char *, const char *, const char *);

// Named by tools/dump_subsystems.py -- see game_engine_subsystems.h.
template void initSubsystem<Eva>(Eva *&, AsciiString, Eva *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<TerrainTypeCollection>(TerrainTypeCollection *&, AsciiString, TerrainTypeCollection *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<ModuleFactory>(ModuleFactory *&, AsciiString, ModuleFactory *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<RankInfoStore>(RankInfoStore *&, AsciiString, RankInfoStore *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<MetaMap>(MetaMap *&, AsciiString, MetaMap *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<GameResultsInterface>(GameResultsInterface *&, AsciiString, GameResultsInterface *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<GameTextInterface>(GameTextInterface *&, AsciiString, GameTextInterface *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<CDManagerInterface>(CDManagerInterface *&, AsciiString, CDManagerInterface *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<BuildAssistant>(BuildAssistant *&, AsciiString, BuildAssistant *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<GameStateMap>(GameStateMap *&, AsciiString, GameStateMap *, Xfer *, const char *, const char *, const char *);

template void initSubsystem<GlobalLanguage>(GlobalLanguage *&, AsciiString, GlobalLanguage *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<CaveSystem>(CaveSystem *&, AsciiString, CaveSystem *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<GameClient>(GameClient *&, AsciiString, GameClient *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<VictoryConditionsInterface>(VictoryConditionsInterface *&, AsciiString, VictoryConditionsInterface *, Xfer *, const char *, const char *, const char *);

// ??$initSubsystem@VRadar@@@@YAXAAPAVRadar@@VAsciiString@@PAV0@PAVXfer@@PBD44@Z, retail 0x0022B888, 128 bytes.
// Between 0x0022B813 (RecorderClass) and 0x0022B908 (VictoryConditionsInterface).
// Evidence: GameEngine::init call site at 0x0022F6E9 pushes TheRadar literal 0x007E7B60 and global 0x009FF070;
// slot vtable 0x007E7384 sits between RecorderClass 0x007E7380 and VictoryConditionsInterface 0x007E7388;
// donor reference/open-bfme-1 Radar.h declares class Radar : public Snapshot, public SubsystemInterface.
// The second-base conversion emits sys ? sys+4 : 0, the 11-byte excess over the 117-byte single-base bodies.
class Radar : public Snapshot, public SubsystemInterface
{
};
template void initSubsystem<Radar>(Radar *&, AsciiString, Radar *, Xfer *, const char *, const char *, const char *);

// Convention-named from the registration-site "TheXxx" literal, not from a
// decorated symbol -- see the block at the end of game_engine_subsystems.h for
// what that is worth and why the two stronger routes produce nothing here.
// TheRadar is excluded: 167 bytes where these are all 154.
template void initSubsystem<GlobalWeatherSystem>(GlobalWeatherSystem *&, AsciiString, GlobalWeatherSystem *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<PlayerAITypeSet>(PlayerAITypeSet *&, AsciiString, PlayerAITypeSet *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<EmotionSystem>(EmotionSystem *&, AsciiString, EmotionSystem *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<LightPointSystem>(LightPointSystem *&, AsciiString, LightPointSystem *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<ExperienceLevelSystem>(ExperienceLevelSystem *&, AsciiString, ExperienceLevelSystem *, Xfer *, const char *, const char *, const char *);
// Opaque target identity for 0x0022C38B: the retail caller and the matched
// SubsystemInterfaceList::initSubsystem callee establish this generic
// registration helper, but not its concrete template parameter. This explicit
// AptPlayer instantiation is only the C++ emission type for the pointer-level
// sequence; it is not a BFME2 AptPlayer name claim.
template void initSubsystem<AptPlayer>(AptPlayer *&, AsciiString, AptPlayer *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<LivingWorldManager>(LivingWorldManager *&, AsciiString, LivingWorldManager *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<AerialPathfinder>(AerialPathfinder *&, AsciiString, AerialPathfinder *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<LivingWorldLogic>(LivingWorldLogic *&, AsciiString, LivingWorldLogic *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<SplineService>(SplineService *&, AsciiString, SplineService *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<AttributeModifierStore>(AttributeModifierStore *&, AsciiString, AttributeModifierStore *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<TaintManager>(TaintManager *&, AsciiString, TaintManager *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<LuaScriptEngine>(LuaScriptEngine *&, AsciiString, LuaScriptEngine *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<HouseColorSystem>(HouseColorSystem *&, AsciiString, HouseColorSystem *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<LivingWorldCampaignManager>(LivingWorldCampaignManager *&, AsciiString, LivingWorldCampaignManager *, Xfer *, const char *, const char *, const char *);
template void initSubsystem<VictorySystem>(VictorySystem *&, AsciiString, VictorySystem *, Xfer *, const char *, const char *, const char *);

// Retail keeps each slot's ctor out of line, just ahead of its deleting dtor.
// Explicit class instantiation emits it; the inlined copies in initSubsystem<T>
// are unaffected.
template class SubsystemSlot<SubsystemLegend>;
template class SubsystemSlot<GlobalData>;
template class SubsystemSlot<GlobalLanguage>;
template class SubsystemSlot<GameTextInterface>;
template class SubsystemSlot<AudioManager>;
template class SubsystemSlot<Eva>;
template class SubsystemSlot<ScienceStore>;
template class SubsystemSlot<UpgradeCenter>;
template class SubsystemSlot<MultiplayerSettings>;
template class SubsystemSlot<TerrainTypeCollection>;
template class SubsystemSlot<TerrainRoadCollection>;
template class SubsystemSlot<GlobalWeatherSystem>;
template class SubsystemSlot<FunctionLexicon>;
template class SubsystemSlot<ModuleFactory>;
template class SubsystemSlot<MessageStream>;
template class SubsystemSlot<SidesList>;
template class SubsystemSlot<CaveSystem>;
template class SubsystemSlot<RankInfoStore>;
template class SubsystemSlot<PlayerAITypeSet>;
template class SubsystemSlot<PlayerTemplateStore>;
template class SubsystemSlot<FXListStore>;
template class SubsystemSlot<WeaponStore>;
template class SubsystemSlot<ObjectCreationListStore>;
template class SubsystemSlot<LocomotorStore>;
template class SubsystemSlot<SpecialPowerStore>;
template class SubsystemSlot<DamageFXStore>;
template class SubsystemSlot<ArmorStore>;
template class SubsystemSlot<BuildAssistant>;
template class SubsystemSlot<EmotionSystem>;
template class SubsystemSlot<ThingFactory>;
template class SubsystemSlot<ExperienceLevelSystem>;
template class SubsystemSlot<AI>;
template class SubsystemSlot<AerialPathfinder>;
template class SubsystemSlot<ScriptEngine>;
template class SubsystemSlot<LuaScriptEngine>;
template class SubsystemSlot<TeamFactory>;
template class SubsystemSlot<CrateSystem>;
template class SubsystemSlot<PlayerList>;
template class SubsystemSlot<GameLogic>;
template class SubsystemSlot<RecorderClass>;
template class SubsystemSlot<VictoryConditionsInterface>;
template class SubsystemSlot<MetaMap>;
template class SubsystemSlot<HouseColorSystem>;
template class SubsystemSlot<VictorySystem>;
template class SubsystemSlot<ActionManager>;
template class SubsystemSlot<GameStateMap>;
template class SubsystemSlot<GameState>;

// Slots named from the matched initSubsystem<T> that installs their vtable
// (the inlined SubsystemSlot<T> ctor there stores it into the new slot):
// ParticleSystemManager 0xbe72d0 by 0x0022A3EC, Radar 0xbe7384 by 0x0022B888.
template class SubsystemSlot<ParticleSystemManager>;
template class SubsystemSlot<Radar>;
// GameClient: registration site 0x0022F35B pushes "TheGameClient", ZH declares
// extern GameClient *TheGameClient; initSubsystem at 0x0022B217 installs 0xbe734c.
// GameResultsInterface: site 0x0022FB5A pushes "TheGameResultsQueue", ZH declares
// extern GameResultsInterface *TheGameResultsQueue; 0x0022C058 installs 0xbe73c8.
template class SubsystemSlot<GameClient>;
template class SubsystemSlot<GameResultsInterface>;

// ---------------------------------------------------------------------------
// BFME 2-only registrations. Each GameEngine::init site pushes a "TheXxx"
// literal and a global, and calls its own initSubsystem<T>, whose inlined slot
// ctor installs the vtable of the SubsystemSlot<T> triple emitted beside the
// others. That ties the four bodies together, but nothing supplies the CLASS:
// neither donor declares these globals and no ledger row carries the names, and
// the literal names the variable, not the type (see game_engine_subsystems.h
// for the four times reading one off the other was wrong). So T is named after
// its initSubsystem address; rename it when the class turns up.
// Rva0022A809Subsystem: site 0x0022ED8D registers "TheCrowdResponseStore" (global 0x00A0307C); slot vtable 0xbe72f4.
class Rva0022A809Subsystem : public SubsystemInterface {};
template void initSubsystem<Rva0022A809Subsystem>(Rva0022A809Subsystem *&, AsciiString, Rva0022A809Subsystem *, Xfer *, const char *, const char *, const char *);
template class SubsystemSlot<Rva0022A809Subsystem>;
// Rva0022A87ESubsystem: site 0x0022EDD3 registers "TheLivingWorldAutoResolveArmorStore" (global 0x00A031F0); slot vtable 0xbe72f8.
class Rva0022A87ESubsystem : public SubsystemInterface {};
template void initSubsystem<Rva0022A87ESubsystem>(Rva0022A87ESubsystem *&, AsciiString, Rva0022A87ESubsystem *, Xfer *, const char *, const char *, const char *);
template class SubsystemSlot<Rva0022A87ESubsystem>;
// Rva0022A8F3Subsystem: site 0x0022EE19 registers "TheLivingWorldAutoResolveWeaponStore" (global 0x00A030C0); slot vtable 0xbe72fc.
class Rva0022A8F3Subsystem : public SubsystemInterface {};
template void initSubsystem<Rva0022A8F3Subsystem>(Rva0022A8F3Subsystem *&, AsciiString, Rva0022A8F3Subsystem *, Xfer *, const char *, const char *, const char *);
template class SubsystemSlot<Rva0022A8F3Subsystem>;
// Rva0022A968Subsystem: site 0x0022EE5F registers "TheLivingWorldAutoResolveBodyStore" (global 0x00A030B0); slot vtable 0xbe7300.
class Rva0022A968Subsystem : public SubsystemInterface {};
template void initSubsystem<Rva0022A968Subsystem>(Rva0022A968Subsystem *&, AsciiString, Rva0022A968Subsystem *, Xfer *, const char *, const char *, const char *);
template class SubsystemSlot<Rva0022A968Subsystem>;
// Rva0022A9DDSubsystem: site 0x0022EEA5 registers "TheLivingWorldAutoResolveLeadershipStore" (global 0x00A030A8); slot vtable 0xbe7304.
class Rva0022A9DDSubsystem : public SubsystemInterface {};
template void initSubsystem<Rva0022A9DDSubsystem>(Rva0022A9DDSubsystem *&, AsciiString, Rva0022A9DDSubsystem *, Xfer *, const char *, const char *, const char *);
template class SubsystemSlot<Rva0022A9DDSubsystem>;
// Rva0022AA52Subsystem: site 0x0022EEEB registers "TheLivingWorldAutoResolveCombatChainStore" (global 0x00A030B8); slot vtable 0xbe7308.
class Rva0022AA52Subsystem : public SubsystemInterface {};
template void initSubsystem<Rva0022AA52Subsystem>(Rva0022AA52Subsystem *&, AsciiString, Rva0022AA52Subsystem *, Xfer *, const char *, const char *, const char *);
template class SubsystemSlot<Rva0022AA52Subsystem>;
// Rva0022AAC7Subsystem: site 0x0022EF31 registers "TheLivingWorldAutoResolveHandicapStore" (global 0x00A03040); slot vtable 0xbe730c.
class Rva0022AAC7Subsystem : public SubsystemInterface {};
template void initSubsystem<Rva0022AAC7Subsystem>(Rva0022AAC7Subsystem *&, AsciiString, Rva0022AAC7Subsystem *, Xfer *, const char *, const char *, const char *);
template class SubsystemSlot<Rva0022AAC7Subsystem>;
// Rva0022AB3CSubsystem: site 0x0022EF78 registers "TheMissionObjectiveTracker" (global 0x00A031E8); slot vtable 0xbe7310.
class Rva0022AB3CSubsystem : public SubsystemInterface {};
template void initSubsystem<Rva0022AB3CSubsystem>(Rva0022AB3CSubsystem *&, AsciiString, Rva0022AB3CSubsystem *, Xfer *, const char *, const char *, const char *);
template class SubsystemSlot<Rva0022AB3CSubsystem>;
// Rva0022AC9BSubsystem: site 0x0022F04C registers "TheStancesStore" (global 0x00A031D4); slot vtable 0xbe731c.
class Rva0022AC9BSubsystem : public SubsystemInterface {};
template void initSubsystem<Rva0022AC9BSubsystem>(Rva0022AC9BSubsystem *&, AsciiString, Rva0022AC9BSubsystem *, Xfer *, const char *, const char *, const char *);
template class SubsystemSlot<Rva0022AC9BSubsystem>;
// Rva0022AD10Subsystem: site 0x0022F090 registers "TheFormationAssistant" (global 0x00A03160); slot vtable 0xbe7320.
class Rva0022AD10Subsystem : public SubsystemInterface {};
template void initSubsystem<Rva0022AD10Subsystem>(Rva0022AD10Subsystem *&, AsciiString, Rva0022AD10Subsystem *, Xfer *, const char *, const char *, const char *);
template class SubsystemSlot<Rva0022AD10Subsystem>;
// Rva0022AD85Subsystem: site 0x0022F0D4 registers "TheAiOrdersManager" (global 0x00A01E18); slot vtable 0xbe7324.
class Rva0022AD85Subsystem : public SubsystemInterface {};
template void initSubsystem<Rva0022AD85Subsystem>(Rva0022AD85Subsystem *&, AsciiString, Rva0022AD85Subsystem *, Xfer *, const char *, const char *, const char *);
template class SubsystemSlot<Rva0022AD85Subsystem>;
// Rva0022ADFASubsystem: site 0x0022F11A registers "TheLightPointSystem" (global 0x00A03158); slot vtable 0xbe7328.
class Rva0022ADFASubsystem : public SubsystemInterface {};
template void initSubsystem<Rva0022ADFASubsystem>(Rva0022ADFASubsystem *&, AsciiString, Rva0022ADFASubsystem *, Xfer *, const char *, const char *, const char *);
template class SubsystemSlot<Rva0022ADFASubsystem>;
// Rva0022AEE4Subsystem: site 0x0022F1A4 registers "TheDelayedExperienceLevelGrantSystem" (global 0x00A03144); slot vtable 0xbe7330.
class Rva0022AEE4Subsystem : public SubsystemInterface {};
template void initSubsystem<Rva0022AEE4Subsystem>(Rva0022AEE4Subsystem *&, AsciiString, Rva0022AEE4Subsystem *, Xfer *, const char *, const char *, const char *);
template class SubsystemSlot<Rva0022AEE4Subsystem>;
// Rva0022AF59Subsystem: site 0x0022F1D1 registers "TheAptPlayer" (global 0x009FE4CC); slot vtable 0xbe7334.
class Rva0022AF59Subsystem : public SubsystemInterface {};
template void initSubsystem<Rva0022AF59Subsystem>(Rva0022AF59Subsystem *&, AsciiString, Rva0022AF59Subsystem *, Xfer *, const char *, const char *, const char *);
template class SubsystemSlot<Rva0022AF59Subsystem>;
// Rva0022AFCESubsystem: site 0x0022F217 registers "TheLivingWorldPlayerTemplateStore" (global 0x009FF0B0); slot vtable 0xbe7338.
class Rva0022AFCESubsystem : public SubsystemInterface {};
template void initSubsystem<Rva0022AFCESubsystem>(Rva0022AFCESubsystem *&, AsciiString, Rva0022AFCESubsystem *, Xfer *, const char *, const char *, const char *);
template class SubsystemSlot<Rva0022AFCESubsystem>;
// Rva0022B043Subsystem: site 0x0022F25D registers "TheLivingWorldAITemplateStore" (global 0x00A03140); slot vtable 0xbe733c.
class Rva0022B043Subsystem : public SubsystemInterface {};
template void initSubsystem<Rva0022B043Subsystem>(Rva0022B043Subsystem *&, AsciiString, Rva0022B043Subsystem *, Xfer *, const char *, const char *, const char *);
template class SubsystemSlot<Rva0022B043Subsystem>;
// Rva0022B0B8Subsystem: site 0x0022F2A0 registers "TheLivingWorldRegionEffectsManagerStore" (global 0x00A02E60); slot vtable 0xbe7340.
class Rva0022B0B8Subsystem : public SubsystemInterface {};
template void initSubsystem<Rva0022B0B8Subsystem>(Rva0022B0B8Subsystem *&, AsciiString, Rva0022B0B8Subsystem *, Xfer *, const char *, const char *, const char *);
template class SubsystemSlot<Rva0022B0B8Subsystem>;
// Rva0022B12DSubsystem: site 0x0022F2E7 registers "TheLivingWorldManager" (global 0x009FE1C8); slot vtable 0xbe7344.
class Rva0022B12DSubsystem : public SubsystemInterface {};
template void initSubsystem<Rva0022B12DSubsystem>(Rva0022B12DSubsystem *&, AsciiString, Rva0022B12DSubsystem *, Xfer *, const char *, const char *, const char *);
template class SubsystemSlot<Rva0022B12DSubsystem>;
// Rva0022B1A2Subsystem: site 0x0022F331 registers "TheLivingWorldLogic" (global 0x009FEF10); slot vtable 0xbe7348.
class Rva0022B1A2Subsystem : public SubsystemInterface {};
template void initSubsystem<Rva0022B1A2Subsystem>(Rva0022B1A2Subsystem *&, AsciiString, Rva0022B1A2Subsystem *, Xfer *, const char *, const char *, const char *);
template class SubsystemSlot<Rva0022B1A2Subsystem>;
// Rva0022B28CSubsystem: site 0x0022F3A1 registers "TheLinearCampaignManager" (global 0x009FDC8C); slot vtable 0xbe7350.
class Rva0022B28CSubsystem : public Snapshot, public SubsystemInterface {};
template void initSubsystem<Rva0022B28CSubsystem>(Rva0022B28CSubsystem *&, AsciiString, Rva0022B28CSubsystem *, Xfer *, const char *, const char *, const char *);
template class SubsystemSlot<Rva0022B28CSubsystem>;
// Rva0022B3F6Subsystem: site 0x0022F47E registers "TheSplineService" (global 0x00A0095C); slot vtable 0xbe735c.
class Rva0022B3F6Subsystem : public SubsystemInterface {};
template void initSubsystem<Rva0022B3F6Subsystem>(Rva0022B3F6Subsystem *&, AsciiString, Rva0022B3F6Subsystem *, Xfer *, const char *, const char *, const char *);
template class SubsystemSlot<Rva0022B3F6Subsystem>;
// Rva0022B46BSubsystem: site 0x0022F4C5 registers "TheAttributeModifierStore" (global 0x009FE1D4); slot vtable 0xbe7360.
class Rva0022B46BSubsystem : public SubsystemInterface {};
template void initSubsystem<Rva0022B46BSubsystem>(Rva0022B46BSubsystem *&, AsciiString, Rva0022B46BSubsystem *, Xfer *, const char *, const char *, const char *);
template class SubsystemSlot<Rva0022B46BSubsystem>;
// Rva0022B4E0Subsystem: site 0x0022F509 registers "TheTaintManager" (global 0x009FE750); slot vtable 0xbe7364.
class Rva0022B4E0Subsystem : public SubsystemInterface {};
template void initSubsystem<Rva0022B4E0Subsystem>(Rva0022B4E0Subsystem *&, AsciiString, Rva0022B4E0Subsystem *, Xfer *, const char *, const char *, const char *);
template class SubsystemSlot<Rva0022B4E0Subsystem>;
// Rva0022BA67Subsystem: site 0x0022F7DC registers "TheMeshInstancingManager" (global 0x00A03134); slot vtable 0xbe7394.
class Rva0022BA67Subsystem : public SubsystemInterface {};
template void initSubsystem<Rva0022BA67Subsystem>(Rva0022BA67Subsystem *&, AsciiString, Rva0022BA67Subsystem *, Xfer *, const char *, const char *, const char *);
template class SubsystemSlot<Rva0022BA67Subsystem>;
// Rva0022BADCSubsystem: site 0x0022F820 registers "TheLivingWorldCampaignManager" (global 0x00A02D6C); slot vtable 0xbe7398.
class Rva0022BADCSubsystem : public SubsystemInterface {};
template void initSubsystem<Rva0022BADCSubsystem>(Rva0022BADCSubsystem *&, AsciiString, Rva0022BADCSubsystem *, Xfer *, const char *, const char *, const char *);
template class SubsystemSlot<Rva0022BADCSubsystem>;
// Rva0022BBC6Subsystem: site 0x0022F8AE registers "TheFireLogicSystem" (global 0x009FEC68); slot vtable 0xbe73a0.
class Rva0022BBC6Subsystem : public SubsystemInterface {};
template void initSubsystem<Rva0022BBC6Subsystem>(Rva0022BBC6Subsystem *&, AsciiString, Rva0022BBC6Subsystem *, Xfer *, const char *, const char *, const char *);
template class SubsystemSlot<Rva0022BBC6Subsystem>;
// Rva0022BC3BSubsystem: site 0x0022F8F2 registers "TheMineshaftPortalNetworkManager" (global 0x00A01EDC); slot vtable 0xbe73a4.
class Rva0022BC3BSubsystem : public SubsystemInterface {};
template void initSubsystem<Rva0022BC3BSubsystem>(Rva0022BC3BSubsystem *&, AsciiString, Rva0022BC3BSubsystem *, Xfer *, const char *, const char *, const char *);
template class SubsystemSlot<Rva0022BC3BSubsystem>;
// Rva0022BCB0Subsystem: site 0x0022F939 registers "TheSkirmishAIManager" (global 0x009FEEF8); slot vtable 0xbe73a8.
class Rva0022BCB0Subsystem : public SubsystemInterface {};
template void initSubsystem<Rva0022BCB0Subsystem>(Rva0022BCB0Subsystem *&, AsciiString, Rva0022BCB0Subsystem *, Xfer *, const char *, const char *, const char *);
template class SubsystemSlot<Rva0022BCB0Subsystem>;
// Rva0022BD25Subsystem: site 0x0022F97C registers "TheArmyDefinitionManager" (global 0x00A0312C); slot vtable 0xbe73ac.
class Rva0022BD25Subsystem : public SubsystemInterface {};
template void initSubsystem<Rva0022BD25Subsystem>(Rva0022BD25Subsystem *&, AsciiString, Rva0022BD25Subsystem *, Xfer *, const char *, const char *, const char *);
template class SubsystemSlot<Rva0022BD25Subsystem>;
// Rva0022BD9ASubsystem: site 0x0022F9C0 registers "TheBaseTemplateLibrary" (global 0x00A03124); slot vtable 0xbe73b0.
class Rva0022BD9ASubsystem : public SubsystemInterface {};
template void initSubsystem<Rva0022BD9ASubsystem>(Rva0022BD9ASubsystem *&, AsciiString, Rva0022BD9ASubsystem *, Xfer *, const char *, const char *, const char *);
template class SubsystemSlot<Rva0022BD9ASubsystem>;
// Rva0022BE0FSubsystem: site 0x0022FA03 registers "TheThreatFinderManager" (global 0x00A02E48); slot vtable 0xbe73b4.
class Rva0022BE0FSubsystem : public SubsystemInterface {};
template void initSubsystem<Rva0022BE0FSubsystem>(Rva0022BE0FSubsystem *&, AsciiString, Rva0022BE0FSubsystem *, Xfer *, const char *, const char *, const char *);
template class SubsystemSlot<Rva0022BE0FSubsystem>;
// Rva0022BE84Subsystem: site 0x0022FA46 registers "TheAITargetHeuristicLibrary" (global 0x00A0311C); slot vtable 0xbe73b8.
class Rva0022BE84Subsystem : public SubsystemInterface {};
template void initSubsystem<Rva0022BE84Subsystem>(Rva0022BE84Subsystem *&, AsciiString, Rva0022BE84Subsystem *, Xfer *, const char *, const char *, const char *);
template class SubsystemSlot<Rva0022BE84Subsystem>;
// Rva0022C0CDSubsystem: site 0x0022FBA1 registers "TheLivingWorldBuildingTemplateStore" (global 0x009FF09C); slot vtable 0xbe73cc.
class Rva0022C0CDSubsystem : public SubsystemInterface {};
template void initSubsystem<Rva0022C0CDSubsystem>(Rva0022C0CDSubsystem *&, AsciiString, Rva0022C0CDSubsystem *, Xfer *, const char *, const char *, const char *);
template class SubsystemSlot<Rva0022C0CDSubsystem>;
// Rva0022C142Subsystem: site 0x0022FBE5 registers "TheAwardSystemManager" (global 0x00A02F74); slot vtable 0xbe73d0.
class Rva0022C142Subsystem : public SubsystemInterface {};
template void initSubsystem<Rva0022C142Subsystem>(Rva0022C142Subsystem *&, AsciiString, Rva0022C142Subsystem *, Xfer *, const char *, const char *, const char *);
template class SubsystemSlot<Rva0022C142Subsystem>;
// Rva0022C1B7Subsystem: site 0x0022FC2F registers "TheCreateAHeroManager" (global 0x009FE344); slot vtable 0xbe73d4.
class Rva0022C1B7Subsystem : public SubsystemInterface {};
template void initSubsystem<Rva0022C1B7Subsystem>(Rva0022C1B7Subsystem *&, AsciiString, Rva0022C1B7Subsystem *, Xfer *, const char *, const char *, const char *);
template class SubsystemSlot<Rva0022C1B7Subsystem>;
// Rva0022C22CSubsystem: site 0x0022FC76 registers "TheScoredKillEvaAnnouncerController" (global 0x00A03074); slot vtable 0xbe73d8.
class Rva0022C22CSubsystem : public SubsystemInterface {};
template void initSubsystem<Rva0022C22CSubsystem>(Rva0022C22CSubsystem *&, AsciiString, Rva0022C22CSubsystem *, Xfer *, const char *, const char *, const char *);
template class SubsystemSlot<Rva0022C22CSubsystem>;
// Rva0022C2A1Subsystem: site 0x0022FCBD registers "TheLivingWorldAutoResolveReinforcementScheduleStore" (global 0x00A03064); slot vtable 0xbe73dc.
class Rva0022C2A1Subsystem : public SubsystemInterface {};
template void initSubsystem<Rva0022C2A1Subsystem>(Rva0022C2A1Subsystem *&, AsciiString, Rva0022C2A1Subsystem *, Xfer *, const char *, const char *, const char *);
template class SubsystemSlot<Rva0022C2A1Subsystem>;
// Rva0022C316Subsystem: site 0x0022FD03 registers "TheLivingWorldAutoResolveResourceBonusScheduleStore" (global 0x00A0306C); slot vtable 0xbe73e0.
class Rva0022C316Subsystem : public SubsystemInterface {};
template void initSubsystem<Rva0022C316Subsystem>(Rva0022C316Subsystem *&, AsciiString, Rva0022C316Subsystem *, Xfer *, const char *, const char *, const char *);
template class SubsystemSlot<Rva0022C316Subsystem>;
