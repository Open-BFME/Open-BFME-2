// ?init@GameEngine@@UAEXHQAPAD@Z
// partial score=0.998 date=2026-10-06
// cl: /O1 /DNDEBUG /MD /EHsc /G7 /arch:SSE /Ireference/shims/bfme2_ascii
// BANKED NEAR MISS: GameEngine::init(Int argc, char *argv[]), retail 0x0022E2E4, 8808 bytes
// (0x0022E2E4..0x0023054C, `ret 8`; the three catch funclets sit mid-body at
// 0x00230215..0x0023044F and the post-try continuation is 0x00230450..0x0023054C;
// Ghidra's 7985-byte FUN_0062e2e4 stops at the funclets). GameEngine vtable
// 0x00BE7188 slot 14.
//
// State: compiled body is 8808/8808 bytes with every instruction aligned; 18
// bytes differ, all frame displacements. Retail places the post-try obfuscated
// value (Rva00077710Value at [ebp-0x1C], m_b read once into esi) in the slot it
// shares with GameSlotConnectInfo and the catch(ErrorCode) strings; this VC7.1
// never lets a post-try local overlap a catch handler's named locals (probed:
// any catch local blocks the share, under /EHsc /EHs /EHa /GX /G6 /G7 /O2), so
// it gets its own 8 bytes below xferCRC: frame 0xA90 vs 0xA88, INI -0xA9C vs
// -0xA94, GameSlot -0x220 vs -0x218. Ruled out: block, forceinline helper,
// function-scope declaration, ctor/reference-bound temporaries, class size.
//
// Structure (Zero Hour GameEngine::init with BFME 2's subsystem list): try {
// INI; m_maxFPS=45; SubsystemInterfaceList; NameKeyGenerator; two CommandLists;
// BFMECRCWriter xferCRC(true); 90 initSubsystem calls (table in
// build-side blocks.py: T names follow the rowed initSubsystem<T> instantiations
// in Libraries/Source/subsystem/SubsystemInterface.cpp); CRC; audio setOn x5;
// MapCache; .map/.rep start-up through TheSkirmishGameInfo; _EA_RTS_HEADLESS;
// shell map check } catch (ErrorCode) / catch (INIException&) / catch (...);
// then intro flag, frame timing, resetAll, HideControlBar, watchdog.
// The INIException branch needs the inline stream helper `put` (retail loads
// e.mFailureMessage into a register for compare and push).
//
// To land after the frame is solved: ~55 callee names (most subsystem ctors at
// unnamed or address-named owners, admissible as pins) plus ICF rows for four
// folds: 0x0047A69C `ret 4` (SubsystemInterfaceList::addSubsystem), 0x000B3FD0
// `ret` (empty argc/argv call), 0x001F34BA (GameInfo::init = reset(), owner
// ??_9@$BCI@AE), 0x003FF328 (GameInfo::setSeed, m_seed +0x50, owner
// Pathfinder::setIgnoreObstacleID); and an owner rename at 0x00360BB8 (rowed
// ??0ArmorStore@@QAE@XZ but called for TheDamageFXStore; TheArmorStore's ctor is
// 0x001D9670).
#include "ascii_string.h"
#include "unicode_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
class Xfer;
class GameMessage { public: void appendIntegerArgument(Int arg); };

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	void setName(AsciiString name);
protected:
	unsigned int m_04;
	unsigned int m_08;
};

template <class SUBSYSTEM> void initSubsystem(SUBSYSTEM *&sysref, AsciiString name, SUBSYSTEM *sys, Xfer *pXfer, const char *path1 = 0, const char *path2 = 0, const char *dirpath = 0);

class SubsystemLegend { public: SubsystemLegend(); char m_data[0x10]; };
class GlobalData { public: GlobalData(); char m_data[0x1254]; };
class GlobalLanguage { public: GlobalLanguage(); char m_data[0x13c]; };
class GameTextInterface;
class AudioManager;
class Eva { public: Eva(); char m_data[0x98]; };
class ScienceStore { public: ScienceStore(); char m_data[0x24]; };
class UpgradeCenter { public: UpgradeCenter(); char m_data[0x24]; };
class MultiplayerSettings { public: MultiplayerSettings(); char m_data[0xc4]; };
class TerrainTypeCollection { public: TerrainTypeCollection(); char m_data[0x10]; };
class TerrainRoadCollection { public: TerrainRoadCollection(); char m_data[0x14]; };
class GlobalWeatherSystem { public: GlobalWeatherSystem(); char m_data[0x5c]; };
class FunctionLexicon;
class ModuleFactory;
class MessageStream;
class SidesList { public: SidesList(); char m_data[0x11b0]; };
class CaveSystem { public: CaveSystem(); char m_data[0x1c]; };
class RankInfoStore { public: RankInfoStore(); char m_data[0x18]; };
class PlayerAITypeSet { public: PlayerAITypeSet(); char m_data[0x18]; };
class PlayerTemplateStore { public: PlayerTemplateStore(); char m_data[0x28]; };
class ParticleSystemManager;
class FXListStore { public: FXListStore(); char m_data[0x2c]; };
class WeaponStore { public: WeaponStore(); char m_data[0x24]; };
class ObjectCreationListStore { public: ObjectCreationListStore(); char m_data[0x30]; };
class LocomotorStore { public: LocomotorStore(); char m_data[0x24]; };
class SpecialPowerStore { public: SpecialPowerStore(); char m_data[0x1c]; };
class DamageFXStore { public: DamageFXStore(); char m_data[0x20]; };
class ArmorStore { public: ArmorStore(); char m_data[0x38]; };
class BuildAssistant { public: BuildAssistant(); char m_data[0x28]; };
class Rva0022A809Subsystem { public: Rva0022A809Subsystem(); char m_data[0x24]; };
class Rva0022A87ESubsystem { public: Rva0022A87ESubsystem(); char m_data[0x20]; };
class Rva0022A8F3Subsystem { public: Rva0022A8F3Subsystem(); char m_data[0x20]; };
class Rva0022A968Subsystem { public: Rva0022A968Subsystem(); char m_data[0x20]; };
class Rva0022A9DDSubsystem { public: Rva0022A9DDSubsystem(); char m_data[0x20]; };
class Rva0022AA52Subsystem { public: Rva0022AA52Subsystem(); char m_data[0x20]; };
class Rva0022AAC7Subsystem { public: Rva0022AAC7Subsystem(); char m_data[0x18]; };
class Rva0022AB3CSubsystem { public: Rva0022AB3CSubsystem(); char m_data[0x14]; };
class EmotionSystem { public: EmotionSystem(); char m_data[0x30]; };
class ThingFactory;
class Rva0022AC9BSubsystem { public: Rva0022AC9BSubsystem(); char m_data[0x18]; };
class Rva0022AD10Subsystem { public: Rva0022AD10Subsystem(); char m_data[0x38]; };
class Rva0022AD85Subsystem { public: Rva0022AD85Subsystem(); char m_data[0x38]; };
class Rva0022ADFASubsystem { public: Rva0022ADFASubsystem(); char m_data[0x18]; };
class ExperienceLevelSystem { public: ExperienceLevelSystem(); char m_data[0x34]; };
class Rva0022AEE4Subsystem { public: Rva0022AEE4Subsystem(); char m_data[0x18]; };
class Rva0022AF59Subsystem;
class Rva0022AFCESubsystem { public: Rva0022AFCESubsystem(); char m_data[0x18]; };
class Rva0022B043Subsystem { public: Rva0022B043Subsystem(); char m_data[0x18]; };
class Rva0022B0B8Subsystem { public: Rva0022B0B8Subsystem(); char m_data[0x20]; };
class Rva0022B12DSubsystem { public: Rva0022B12DSubsystem(); char m_data[0x2d8]; };
class Rva0022B1A2Subsystem { public: Rva0022B1A2Subsystem(); char m_data[0x17c]; };
class GameClient;
class Rva0022B28CSubsystem { public: Rva0022B28CSubsystem(); char m_data[0x20]; };
class AI { public: AI(); char m_data[0x24]; };
class AerialPathfinder { public: AerialPathfinder(); char m_data[0x14]; };
class Rva0022B3F6Subsystem : public SubsystemInterface { public: Rva0022B3F6Subsystem() {} virtual ~Rva0022B3F6Subsystem(); };
class Rva0022B46BSubsystem { public: Rva0022B46BSubsystem(); char m_data[0x24]; };
class Rva0022B4E0Subsystem;
class BfmeTaintManager { public: BfmeTaintManager(); char m_data[0x14]; };
class ScriptEngine { public: ScriptEngine(); char m_data[0x1a500]; };
class LuaScriptEngine { public: LuaScriptEngine(); char m_data[0xe0]; };
class TeamFactory { public: TeamFactory(); char m_data[0xc4]; };
class CrateSystem { public: CrateSystem(); char m_data[0x18]; };
class PlayerList { public: PlayerList(); char m_data[0x68]; };
class GameLogic;
class RecorderClass;
class Radar;
class VictoryConditionsInterface;
class MetaMap { public: MetaMap(); char m_data[0x10]; };
class HouseColorSystem { public: HouseColorSystem(); char m_data[0x14]; };
class Rva0022BA67Subsystem { public: Rva0022BA67Subsystem(); char m_data[0x24]; };
class Rva0022BADCSubsystem { public: Rva0022BADCSubsystem(); char m_data[0x30]; };
class VictorySystem { public: VictorySystem(); char m_data[0x140]; };
class Rva0022BBC6Subsystem { public: Rva0022BBC6Subsystem(); char m_data[0xa0]; };
class Rva0022BC3BSubsystem { public: Rva0022BC3BSubsystem(); char m_data[0x1c]; };
class Rva0022BCB0Subsystem { public: Rva0022BCB0Subsystem(); char m_data[0x944]; };
class Rva0022BD25Subsystem { public: Rva0022BD25Subsystem(); char m_data[0x20]; };
class Rva0022BD9ASubsystem { public: Rva0022BD9ASubsystem(); char m_data[0x34]; };
class Rva0022BE0FSubsystem { public: Rva0022BE0FSubsystem(); char m_data[0x20]; };
class Rva0022BE84Subsystem { public: Rva0022BE84Subsystem(); char m_data[0x18]; };
class ActionManager { public: ActionManager(); char m_data[0xc]; };
class GameStateMap { public: GameStateMap(); char m_data[0x10]; };
class GameState { public: GameState(); char m_data[0xe1c]; };
class GameResultsInterface;
class Rva0022C0CDSubsystem { public: Rva0022C0CDSubsystem(); char m_data[0x38]; };
class Rva0022C142Subsystem { public: Rva0022C142Subsystem(); char m_data[0x24]; };
class Rva0022C1B7Subsystem { public: Rva0022C1B7Subsystem(); char m_data[0x1f4]; };
class Rva0022C22CSubsystem { public: Rva0022C22CSubsystem(); char m_data[0x1c]; };
class Rva0022C2A1Subsystem { public: Rva0022C2A1Subsystem(); char m_data[0x2c]; };
class Rva0022C316Subsystem { public: Rva0022C316Subsystem(); char m_data[0x18]; };
class Rva0022C38BSubsystem { public: Rva0022C38BSubsystem(); char m_data[0x18]; };

extern SubsystemLegend *TheSubsystemLegend;
extern GlobalData *TheWritableGlobalData;
extern GlobalLanguage *TheGlobalLanguageData;
extern GameTextInterface *TheGameText;
extern AudioManager *TheAudio;
extern Eva *TheEva;
extern ScienceStore *TheScienceStore;
extern UpgradeCenter *TheUpgradeCenter;
extern MultiplayerSettings *TheMultiplayerSettings;
extern TerrainTypeCollection *TheTerrainTypes;
extern TerrainRoadCollection *TheTerrainRoads;
extern GlobalWeatherSystem *TheGlobalWeatherSystem;
extern FunctionLexicon *TheFunctionLexicon;
extern ModuleFactory *TheModuleFactory;
extern MessageStream *TheMessageStream;
extern SidesList *TheSidesList;
extern CaveSystem *TheCaveSystem;
extern RankInfoStore *TheRankInfoStore;
extern PlayerAITypeSet *ThePlayerAITypeSet;
extern PlayerTemplateStore *ThePlayerTemplateStore;
extern ParticleSystemManager *TheParticleSystemManager;
extern FXListStore *TheFXListStore;
extern WeaponStore *TheWeaponStore;
extern ObjectCreationListStore *TheObjectCreationListStore;
extern LocomotorStore *TheLocomotorStore;
extern SpecialPowerStore *TheSpecialPowerStore;
extern DamageFXStore *TheDamageFXStore;
extern ArmorStore *TheArmorStore;
extern BuildAssistant *TheBuildAssistant;
extern Rva0022A809Subsystem *TheCrowdResponseStore;
extern Rva0022A87ESubsystem *TheLivingWorldAutoResolveArmorStore;
extern Rva0022A8F3Subsystem *TheLivingWorldAutoResolveWeaponStore;
extern Rva0022A968Subsystem *TheLivingWorldAutoResolveBodyStore;
extern Rva0022A9DDSubsystem *TheLivingWorldAutoResolveLeadershipStore;
extern Rva0022AA52Subsystem *TheLivingWorldAutoResolveCombatChainStore;
extern Rva0022AAC7Subsystem *TheLivingWorldAutoResolveHandicapStore;
extern Rva0022AB3CSubsystem *TheMissionObjectiveTracker;
extern EmotionSystem *TheEmotionSystem;
extern ThingFactory *TheThingFactory;
extern Rva0022AC9BSubsystem *TheStancesStore;
extern Rva0022AD10Subsystem *TheFormationAssistant;
extern Rva0022AD85Subsystem *TheAiOrdersManager;
extern Rva0022ADFASubsystem *TheLightPointSystem;
extern ExperienceLevelSystem *TheExperienceLevelSystem;
extern Rva0022AEE4Subsystem *TheDelayedExperienceLevelGrantSystem;
extern Rva0022AF59Subsystem *TheAptPlayer;
extern Rva0022AFCESubsystem *TheLivingWorldPlayerTemplateStore;
extern Rva0022B043Subsystem *TheLivingWorldAITemplateStore;
extern Rva0022B0B8Subsystem *TheLivingWorldRegionEffectsManagerStore;
extern Rva0022B12DSubsystem *TheLivingWorldManager;
extern Rva0022B1A2Subsystem *TheLivingWorldLogic;
extern GameClient *TheGameClient;
extern Rva0022B28CSubsystem *TheLinearCampaignManager;
extern AI *TheAI;
extern AerialPathfinder *TheAerialPathfinder;
extern Rva0022B3F6Subsystem *TheSplineService;
extern Rva0022B46BSubsystem *TheAttributeModifierStore;
extern Rva0022B4E0Subsystem *TheTaintManager;
extern ScriptEngine *TheScriptEngine;
extern LuaScriptEngine *TheLuaScriptEngine;
extern TeamFactory *TheTeamFactory;
extern CrateSystem *TheCrateSystem;
extern PlayerList *ThePlayerList;
extern GameLogic *TheGameLogic;
extern RecorderClass *TheRecorder;
extern Radar *TheRadar;
extern VictoryConditionsInterface *TheVictoryConditions;
extern MetaMap *TheMetaMap;
extern HouseColorSystem *TheHouseColorSystem;
extern Rva0022BA67Subsystem *TheMeshInstancingManager;
extern Rva0022BADCSubsystem *TheLivingWorldCampaignManager;
extern VictorySystem *TheVictorySystem;
extern Rva0022BBC6Subsystem *TheFireLogicSystem;
extern Rva0022BC3BSubsystem *TheMineshaftPortalNetworkManager;
extern Rva0022BCB0Subsystem *TheSkirmishAIManager;
extern Rva0022BD25Subsystem *TheArmyDefinitionManager;
extern Rva0022BD9ASubsystem *TheBaseTemplateLibrary;
extern Rva0022BE0FSubsystem *TheThreatFinderManager;
extern Rva0022BE84Subsystem *TheAITargetHeuristicLibrary;
extern ActionManager *TheActionManager;
extern GameStateMap *TheGameStateMap;
extern GameState *TheGameState;
extern GameResultsInterface *TheGameResultsQueue;
extern Rva0022C0CDSubsystem *TheLivingWorldBuildingTemplateStore;
extern Rva0022C142Subsystem *TheAwardSystemManager;
extern Rva0022C1B7Subsystem *TheCreateAHeroManager;
extern Rva0022C22CSubsystem *TheScoredKillEvaAnnouncerController;
extern Rva0022C2A1Subsystem *TheLivingWorldAutoResolveReinforcementScheduleStore;
extern Rva0022C316Subsystem *TheLivingWorldAutoResolveResourceBonusScheduleStore;
extern Rva0022C38BSubsystem *TheLivingWorldAutoResolveSciencePurchasePointBonusScheduleStore;

extern "C" __declspec(dllimport) char *__cdecl getenv(const char *name);
extern "C" __declspec(dllimport) long __cdecl time(long *timer);
extern "C" __declspec(dllimport) __declspec(noreturn) void __cdecl _exit(int status);
extern "C" __declspec(dllimport) int __stdcall MessageBoxA(void *hwnd, const char *text, const char *caption, unsigned int type);
extern "C" __declspec(dllimport) int __stdcall MessageBoxW(void *hwnd, const unsigned short *text, const unsigned short *caption, unsigned int type);
extern "C" __declspec(dllimport) int __stdcall SetWindowPos(void *hwnd, void *after, int x, int y, int cx, int cy, unsigned int flags);
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

#define VSLOTS4(p) virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3();
#define VSLOTS16(p) VSLOTS4(p##0) VSLOTS4(p##1) VSLOTS4(p##2) VSLOTS4(p##3)

enum INILoadType { INI_LOAD_INVALID, INI_LOAD_OVERWRITE, INI_LOAD_CREATE_OVERRIDES, INI_LOAD_MULTIFILE };

class INI
{
public:
	INI();
	~INI();
	unsigned char loadFile(AsciiString filename, INILoadType loadType, Xfer *pXfer);
private:
	char m_data[0x87C];
};

// BFME 2's CRC writer over the block-writer base whose destructor retail
// rows as XferSave (0x0060D0B3); full at +0x40, crc at +0x44.
class XferSave
{
public:
	XferSave();
	virtual ~XferSave();
	void close();
protected:
	char m_04[0x3C];
};

class BFMECRCWriter : public XferSave
{
public:
	BFMECRCWriter(bool full);
	bool m_full;				// +0x40
	UnsignedInt m_crc;			// +0x44
};

class SubsystemInterfaceList
{
public:
	SubsystemInterfaceList();
	void addSubsystem(SubsystemInterface *sys);
	void postProcessLoadAll();
	void resetAll();
	void rva001B4EAB();
	char m_00[0x24];
	Xfer *m_xfer;				// +0x24
};
extern SubsystemInterfaceList *TheSubsystemList;

class NameKeyGenerator
{
public:
	NameKeyGenerator();
	virtual void slot0();
	virtual void init();
	char m_data[0x2BF80];
};
extern NameKeyGenerator *TheNameKeyGenerator;

class CommandList
{
public:
	CommandList();
	virtual void slot0();
	virtual void init();
	char m_data[0x10];
};
extern CommandList *TheCommandList;
extern CommandList *g_Va00E00958CommandList;

class FileSystem;
extern FileSystem *TheFileSystem;
class Rva0060061A { public: void rva006006D9(void *p); };

class GameLODManager
{
public:
	GameLODManager();
	void init(Int level);
	char m_data[0x17F8];
};
extern GameLODManager *TheGameLODManager;

class Rva002CEC0A { public: Rva002CEC0A(); char m_data[0x10]; };
extern void *g_00DFEFF0;
extern unsigned char g_Rva00A02D86;
extern unsigned char g_Rva00A02D87;

class Rva0033076E { public: Rva0033076E(); char m_data[0x1C]; };
extern Rva0033076E *g_Va00E01DB0;

// Scoped object retail builds around TheThingFactory's init with the
// four-character code 'init' (ctor 0x00030980, dtor 0x000309B0).
class Rva000309B0
{
public:
	Rva000309B0(UnsignedInt tag);
	~Rva000309B0();
private:
	UnsignedInt m_tag;
};

class GlobalDataView
{
public:
	char m_000[0x28];
	Int m_framesPerSecondLimit;		// +0x28
	char m_02C[0x99C - 0x2C];
	Bool m_audioOn;					// +0x99C
	Bool m_musicOn;					// +0x99D
	Bool m_soundsOn;				// +0x99E
	Bool m_sounds3DOn;				// +0x99F
	Bool m_speechOn;				// +0x9A0
	Bool m_9A1;						// +0x9A1
	char m_9A2[0x9AC - 0x9A2];
	Bool m_9AC;						// +0x9AC
	char m_9AD[0xAB5 - 0x9AD];
	Bool m_buildMapCache;			// +0xAB5
	char m_AB6[0xABC - 0xAB6];
	AsciiString m_initialFile;		// +0xABC
	AsciiString m_pendingFile;		// +0xAC0
	char m_AC4[1];
	Bool m_AC5;						// +0xAC5
	char m_AC6[0xAEC - 0xAC6];
	AsciiString m_shellMapName;		// +0xAEC
	Bool m_shellMapOn;				// +0xAF0
	char m_AF1[1];
	Bool m_playIntro;				// +0xAF2
	Bool m_afterIntro;				// +0xAF3
	char m_AF4[0xB04 - 0xAF4];
	UnsignedInt m_iniCRC;			// +0xB04
	char m_B08[0xD36 - 0xB08];
	Bool m_D36;						// +0xD36
};
#define TheGlobalData ((GlobalDataView *)TheWritableGlobalData)

class AudioManager
{
public:
	VSLOTS16(a0) VSLOTS16(a1) VSLOTS16(a2) VSLOTS4(a30) VSLOTS4(a31)
	virtual void a320();
	virtual void setOn(Bool turnOn, Int whichToAffect);	// slot 57 (+0xE4)
	VSLOTS16(a4)
	virtual void a50(); virtual void a51(); virtual void a52(); virtual void a53(); virtual void a54(); virtual void a55(); virtual void a56(); virtual void a57(); virtual void a58();
	virtual Bool isMusicAlreadyLoaded();					// slot 83 (+0x14C)
};

class MessageStream
{
public:
	VSLOTS16(m0)
	virtual void m10(); virtual void m11();
	virtual GameMessage *appendMessage(Int type);			// slot 18 (+0x48)
};

class MapMetaData
{
public:
	char m_00[0x24];
	Bool m_isMultiplayer;		// +0x24
	char m_25[3];
	UnsignedInt m_filesize;		// +0x28
	UnsignedInt m_CRC;			// +0x2C
};

class GameSlotConnectInfo { public: Int m_a; short m_b; };

class GameSlot
{
public:
	GameSlot();
	GameSlot(const GameSlot &that);
	virtual ~GameSlot();
	void setState(Int state, UnicodeString name, const GameSlotConnectInfo *info);
	char m_04[0x2C];
	UnicodeString m_name;		// +0x30
	char m_34[4];
	Int m_38;					// +0x38
	Int m_3C;					// +0x3C
	char m_40[0x1AC - 0x40];
};

class GameInfo
{
public:
	VSLOTS4(g0) VSLOTS4(g1)
	virtual void g20(); virtual void g21();
	virtual void reset();		// slot 10 (+0x28)
	void init();
	GameSlot *getSlot(Int index);
	void rva003FF268();
	void setSeed(Int seed);
	void setMap(AsciiString mapName);
	void setMapCRC(UnsignedInt mapCRC);
	void setMapSize(UnsignedInt mapSize);
	void setSlot(Int index, GameSlot slot);
	char m_04[0x34];
	Int m_38;					// +0x38
	Int m_3C;					// +0x3C
};
class SkirmishGameInfo : public GameInfo { public: SkirmishGameInfo(); char m_data[0xE3C - sizeof(GameInfo)]; };
extern GameInfo *TheSkirmishGameInfo;

class RecorderClass { public: Bool playbackFile(UnicodeString filename); };

class Rva0022C1B7Subsystem;
class CreateAHeroCRC { public: UnsignedInt getCRC(); };

class Watchdog { public: virtual void slot0(); virtual void start(); };
Watchdog *createWatchdog(Int a, Int b, Int c);
extern Watchdog *theBfmeDfe6e4;
extern bool BFME2WatchdogEnabled;

class Rva00077710Value { public: void rva0022D189(Int value); Int m_a; Int m_b; };
Int Rva0022CC0EHook(Int a, Int b);
void Rva0002BBC9Update();
void Rva00419CC8Init();
void Rva00419BFAInit();
void HideControlBar(Bool immediate);
extern Int g_009BA4E8;
extern Int g_Va00DBA4E4;

void Rva000B3FD0(Int argc, char *argv[]);
void InitRandom();
AsciiString GetRegistryLanguage();
void Rva00600665Set(char *language);
void parseCommandLine(Int argc, char *argv[]);
GameTextInterface *CreateGameTextInterface();
RecorderClass *createRecorder();
VictoryConditionsInterface *createVictoryConditions();
class GameResultsInterface { public: static GameResultsInterface *createNewGameResultsInterface(); };

class Debug
{
public:
	VSLOTS16(d0) VSLOTS4(d10) VSLOTS4(d11)
	virtual void crashBegin();					// slot 24 (+0x60)
	virtual void d25(); virtual void d26();
	virtual class DebugStream *stream(Int a, Int b, Int c);	// slot 27 (+0x6C)
};
class DebugStream
{
public:
	VSLOTS4(s0) VSLOTS4(s1) VSLOTS4(s2) virtual void s30(); virtual void s31();
	virtual DebugStream *write(const char *text);			// slot 14 (+0x38)
	virtual void s50(); virtual void s51(); virtual void s52(); virtual void s53();
	virtual void finish(Int flag);							// slot 19 (+0x4C)
};
extern Debug *theDebug;
void __cdecl _bfme_debugRecordCallsite(int kind);
extern void *ApplicationHWnd;
extern bool g_00DFE718;

class GameTextInterface
{
public:
	VSLOTS4(t0) VSLOTS4(t1) VSLOTS4(t2) virtual void t30(); virtual void t31();
	virtual UnicodeString fetch(const AsciiString &label, Bool *exists);	// slot 14 (+0x38)
};

struct INIException { char *mFailureMessage; };
enum ErrorCode { ERROR_INVALID_D3D = 0xDEAD0007 };

class GameEngine : public SubsystemInterface
{
public:
	VSLOTS4(s0) VSLOTS4(s1) VSLOTS4(s2)
	virtual void s30();
	virtual void init(Int argc, char *argv[]);					// slot 14
	virtual void s31(); virtual void s32(); virtual void s33();
	virtual void setFramesPerSecondLimit(Int fps);				// slot 18 (+0x48)
	virtual void s34();
	virtual void setQuitting(Bool quitting);					// slot 20 (+0x50)
	virtual void s35(); virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39(); virtual void s3A();
	virtual FileSystem *createFileSystem();						// +0x6C
	virtual GameLogic *createGameLogic();						// +0x70
	virtual GameClient *createGameClient();						// +0x74
	virtual MessageStream *createMessageStream();				// +0x78
	virtual ModuleFactory *createModuleFactory();				// +0x7C
	virtual ThingFactory *createThingFactory();					// +0x80
	virtual FunctionLexicon *createFunctionLexicon();			// +0x84
	virtual Radar *createRadar();								// +0x88
	virtual ParticleSystemManager *createParticleSystemManager();	// +0x8C
	virtual AudioManager *createAudioManager();					// +0x90
	virtual Rva0022AF59Subsystem *createAptPlayer();			// +0x94

	void initTiming();
	void initSubsystems(Int argc, char *argv[]);

	Int m_maxFPS;				// +0x0C
	Bool m_quitting;			// +0x10
	char m_11[0x34 - 0x11];
	Int m_34;					// +0x34
	Int m_38;					// +0x38
	char m_3C[0x44 - 0x3C];
	float m_44;					// +0x44
	float m_48;					// +0x48
	Int m_4C;					// +0x4C
	Int m_50;					// +0x50
	UnsignedInt m_54;			// +0x54
	float m_58;					// +0x58
	Int m_5C;					// +0x5C
};

class NetworkInterface;
extern NetworkInterface *TheNetwork;
class MapCacheNode;
class MapCache
{
public:
	MapCache();
	void updateCache();
	const MapMetaData *findMap(AsciiString mapName);
	MapCacheNode *find(const AsciiString &key);
	MapCacheNode *end() { return m_header; }
private:
	MapCacheNode *m_header;
	char m_04[0x20];
};
extern MapCache *TheMapCache;



__forceinline void GameEngine::initTiming()
{
	Rva00077710Value timing;
	timing.rva0022D189(0);
	Int value = timing.m_b;
	m_4C = Rva0022CC0EHook(value, value);
	m_58 = (float)Rva0022CC0EHook(value, value);
	m_50 = Rva0022CC0EHook(value, value);
	m_5C = Rva0022CC0EHook(value, value);
}

__forceinline DebugStream *put(DebugStream *stream, const char *text)
{
	return stream->write(text);
}

void GameEngine::init(Int argc, char *argv[])
{
	setName("GameEngine");
	try {
		Rva000B3FD0(argc, argv);
		INI ini;
		m_maxFPS = 45;

		TheSubsystemList = new SubsystemInterfaceList;
		TheSubsystemList->addSubsystem(this);
		InitRandom();
		Rva00600665Set((char *)GetRegistryLanguage().str());
		TheFileSystem = createFileSystem();
		((Rva0060061A *)TheFileSystem)->rva006006D9((void *)1);
		TheNameKeyGenerator = new NameKeyGenerator;
		TheNameKeyGenerator->init();
		TheCommandList = new CommandList;
		TheCommandList->init();
		g_Va00E00958CommandList = new CommandList;
		g_Va00E00958CommandList->init();

		BFMECRCWriter xferCRC(true);
		TheSubsystemList->m_xfer = (Xfer *)&xferCRC;

		initSubsystem(TheSubsystemLegend, "TheSubsystemLegend", new SubsystemLegend, 0);
		ini.loadFile("Data\\INI\\Default\\SubsystemLegend.ini", INI_LOAD_OVERWRITE, 0);
		initSubsystem(TheWritableGlobalData, "TheWritableGlobalData", new GlobalData, 0);
		parseCommandLine(argc, argv);
		if (g_Rva00A02D86 || g_Rva00A02D87)
			g_00DFEFF0 = new Rva002CEC0A;
		TheGameLODManager = new GameLODManager;
		TheGameLODManager->init(-1);
		ini.loadFile("Data\\INI\\Default\\Water.ini", INI_LOAD_OVERWRITE, (Xfer *)&xferCRC);
		ini.loadFile("Data\\INI\\Water.ini", INI_LOAD_OVERWRITE, (Xfer *)&xferCRC);
		ini.loadFile("Data\\INI\\Default\\Fire.ini", INI_LOAD_OVERWRITE, (Xfer *)&xferCRC);
		ini.loadFile("Data\\INI\\Fire.ini", INI_LOAD_OVERWRITE, (Xfer *)&xferCRC);
		ini.loadFile("Data\\INI\\Default\\Environment.ini", INI_LOAD_OVERWRITE, (Xfer *)&xferCRC);
		ini.loadFile("Data\\INI\\Environment.ini", INI_LOAD_OVERWRITE, (Xfer *)&xferCRC);
		initSubsystem(TheGlobalLanguageData, "TheGlobalLanguageData", new GlobalLanguage, 0);
		initSubsystem(TheGameText, "TheGameText", CreateGameTextInterface(), 0);
		initSubsystem(TheAudio, "TheAudio", createAudioManager(), 0);
		if (!TheAudio->isMusicAlreadyLoaded())
			setQuitting(true);
		initSubsystem(TheEva, "TheEva", new Eva, 0);
		initSubsystem(TheScienceStore, "TheScienceStore", new ScienceStore, (Xfer *)&xferCRC);
		initSubsystem(TheUpgradeCenter, "TheUpgradeCenter", new UpgradeCenter, (Xfer *)&xferCRC);
		initSubsystem(TheMultiplayerSettings, "TheMultiplayerSettings", new MultiplayerSettings, (Xfer *)&xferCRC);
		initSubsystem(TheTerrainTypes, "TheTerrainTypes", new TerrainTypeCollection, (Xfer *)&xferCRC);
		initSubsystem(TheTerrainRoads, "TheTerrainRoads", new TerrainRoadCollection, (Xfer *)&xferCRC);
		initSubsystem(TheGlobalWeatherSystem, "TheGlobalWeatherSystem", new GlobalWeatherSystem, 0);
		initSubsystem(TheFunctionLexicon, "TheFunctionLexicon", createFunctionLexicon(), 0);
		initSubsystem(TheModuleFactory, "TheModuleFactory", createModuleFactory(), 0);
		initSubsystem(TheMessageStream, "TheMessageStream", createMessageStream(), 0);
		initSubsystem(TheSidesList, "TheSidesList", new SidesList, 0);
		initSubsystem(TheCaveSystem, "TheCaveSystem", new CaveSystem, 0);
		initSubsystem(TheRankInfoStore, "TheRankInfoStore", new RankInfoStore, (Xfer *)&xferCRC);
		initSubsystem(ThePlayerAITypeSet, "ThePlayerAITypeSet", new PlayerAITypeSet, 0);
		initSubsystem(ThePlayerTemplateStore, "ThePlayerTemplateStore", new PlayerTemplateStore, (Xfer *)&xferCRC);
		g_Va00E01DB0 = new Rva0033076E;
		initSubsystem(TheParticleSystemManager, "TheFXParticleSystemManager", createParticleSystemManager(), 0);
		initSubsystem(TheFXListStore, "TheFXListStore", new FXListStore, (Xfer *)&xferCRC);
		initSubsystem(TheWeaponStore, "TheWeaponStore", new WeaponStore, (Xfer *)&xferCRC);
		initSubsystem(TheObjectCreationListStore, "TheObjectCreationListStore", new ObjectCreationListStore, (Xfer *)&xferCRC);
		initSubsystem(TheLocomotorStore, "TheLocomotorStore", new LocomotorStore, (Xfer *)&xferCRC);
		initSubsystem(TheSpecialPowerStore, "TheSpecialPowerStore", new SpecialPowerStore, (Xfer *)&xferCRC);
		initSubsystem(TheDamageFXStore, "TheDamageFXStore", new DamageFXStore, (Xfer *)&xferCRC);
		initSubsystem(TheArmorStore, "TheArmorStore", new ArmorStore, (Xfer *)&xferCRC);
		initSubsystem(TheBuildAssistant, "TheBuildAssistant", new BuildAssistant, 0);
		initSubsystem(TheCrowdResponseStore, "TheCrowdResponseStore", new Rva0022A809Subsystem, 0);
		initSubsystem(TheLivingWorldAutoResolveArmorStore, "TheLivingWorldAutoResolveArmorStore", new Rva0022A87ESubsystem, (Xfer *)&xferCRC);
		initSubsystem(TheLivingWorldAutoResolveWeaponStore, "TheLivingWorldAutoResolveWeaponStore", new Rva0022A8F3Subsystem, (Xfer *)&xferCRC);
		initSubsystem(TheLivingWorldAutoResolveBodyStore, "TheLivingWorldAutoResolveBodyStore", new Rva0022A968Subsystem, (Xfer *)&xferCRC);
		initSubsystem(TheLivingWorldAutoResolveLeadershipStore, "TheLivingWorldAutoResolveLeadershipStore", new Rva0022A9DDSubsystem, (Xfer *)&xferCRC);
		initSubsystem(TheLivingWorldAutoResolveCombatChainStore, "TheLivingWorldAutoResolveCombatChainStore", new Rva0022AA52Subsystem, (Xfer *)&xferCRC);
		initSubsystem(TheLivingWorldAutoResolveHandicapStore, "TheLivingWorldAutoResolveHandicapStore", new Rva0022AAC7Subsystem, (Xfer *)&xferCRC);
		initSubsystem(TheMissionObjectiveTracker, "TheMissionObjectiveTracker", new Rva0022AB3CSubsystem, (Xfer *)&xferCRC);
		initSubsystem(TheEmotionSystem, "TheEmotionSystem", new EmotionSystem, 0);
		{
		Rva000309B0 initScope('init');
		initSubsystem(TheThingFactory, "TheThingFactory", createThingFactory(), (Xfer *)&xferCRC);
		}
		initSubsystem(TheStancesStore, "TheStancesStore", new Rva0022AC9BSubsystem, 0);
		initSubsystem(TheFormationAssistant, "TheFormationAssistant", new Rva0022AD10Subsystem, 0);
		initSubsystem(TheAiOrdersManager, "TheAiOrdersManager", new Rva0022AD85Subsystem, 0);
		initSubsystem(TheLightPointSystem, "TheLightPointSystem", new Rva0022ADFASubsystem, (Xfer *)&xferCRC);
		initSubsystem(TheExperienceLevelSystem, "TheExperienceLevelSystem", new ExperienceLevelSystem, (Xfer *)&xferCRC);
		initSubsystem(TheDelayedExperienceLevelGrantSystem, "TheDelayedExperienceLevelGrantSystem", new Rva0022AEE4Subsystem, 0);
		initSubsystem(TheAptPlayer, "TheAptPlayer", createAptPlayer(), 0);
		initSubsystem(TheLivingWorldPlayerTemplateStore, "TheLivingWorldPlayerTemplateStore", new Rva0022AFCESubsystem, (Xfer *)&xferCRC);
		initSubsystem(TheLivingWorldAITemplateStore, "TheLivingWorldAITemplateStore", new Rva0022B043Subsystem, (Xfer *)&xferCRC);
		initSubsystem(TheLivingWorldRegionEffectsManagerStore, "TheLivingWorldRegionEffectsManagerStore", new Rva0022B0B8Subsystem, 0);
		initSubsystem(TheLivingWorldManager, "TheLivingWorldManager", new Rva0022B12DSubsystem, 0);
		initSubsystem(TheLivingWorldLogic, "TheLivingWorldLogic", new Rva0022B1A2Subsystem, (Xfer *)&xferCRC);
		initSubsystem(TheGameClient, "TheGameClient", createGameClient(), 0);
		initSubsystem(TheLinearCampaignManager, "TheLinearCampaignManager", new Rva0022B28CSubsystem, (Xfer *)&xferCRC);
		initSubsystem(TheAI, "TheAI", new AI, (Xfer *)&xferCRC);
		initSubsystem(TheAerialPathfinder, "TheAerialPathfinder", new AerialPathfinder, (Xfer *)&xferCRC);
		initSubsystem(TheSplineService, "TheSplineService", new Rva0022B3F6Subsystem, (Xfer *)&xferCRC);
		initSubsystem(TheAttributeModifierStore, "TheAttributeModifierStore", new Rva0022B46BSubsystem, (Xfer *)&xferCRC);
		initSubsystem(TheTaintManager, "TheTaintManager", (Rva0022B4E0Subsystem *)new BfmeTaintManager, 0);
		initSubsystem(TheScriptEngine, "TheScriptEngine", new ScriptEngine, 0);
		initSubsystem(TheLuaScriptEngine, "TheLuaScriptEngine", new LuaScriptEngine, 0);
		initSubsystem(TheTeamFactory, "TheTeamFactory", new TeamFactory, 0);
		initSubsystem(TheCrateSystem, "TheCrateSystem", new CrateSystem, (Xfer *)&xferCRC);
		initSubsystem(ThePlayerList, "ThePlayerList", new PlayerList, 0);
		initSubsystem(TheGameLogic, "TheGameLogic", createGameLogic(), 0);
		initSubsystem(TheRecorder, "TheRecorder", createRecorder(), 0);
		initSubsystem(TheRadar, "TheRadar", createRadar(), 0);
		initSubsystem(TheVictoryConditions, "TheVictoryConditions", createVictoryConditions(), 0);
		initSubsystem(TheMetaMap, "TheMetaMap", new MetaMap, 0);
		initSubsystem(TheHouseColorSystem, "TheHouseColorSystem", new HouseColorSystem, 0);
		initSubsystem(TheMeshInstancingManager, "TheMeshInstancingManager", new Rva0022BA67Subsystem, 0);
		initSubsystem(TheLivingWorldCampaignManager, "TheLivingWorldCampaignManager", new Rva0022BADCSubsystem, 0);
		initSubsystem(TheVictorySystem, "TheVictorySystem", new VictorySystem, 0);
		initSubsystem(TheFireLogicSystem, "TheFireLogicSystem", new Rva0022BBC6Subsystem, 0);
		initSubsystem(TheMineshaftPortalNetworkManager, "TheMineshaftPortalNetworkManager", new Rva0022BC3BSubsystem, 0);
		initSubsystem(TheSkirmishAIManager, "TheSkirmishAIManager", new Rva0022BCB0Subsystem, 0);
		initSubsystem(TheArmyDefinitionManager, "TheArmyDefinitionManager", new Rva0022BD25Subsystem, 0);
		initSubsystem(TheBaseTemplateLibrary, "TheBaseTemplateLibrary", new Rva0022BD9ASubsystem, 0);
		initSubsystem(TheThreatFinderManager, "TheThreatFinderManager", new Rva0022BE0FSubsystem, 0);
		initSubsystem(TheAITargetHeuristicLibrary, "TheAITargetHeuristicLibrary", new Rva0022BE84Subsystem, 0);
		ini.loadFile("CommandMap.ini", INI_LOAD_OVERWRITE, 0);
		initSubsystem(TheActionManager, "TheActionManager", new ActionManager, 0);
		initSubsystem(TheGameStateMap, "TheGameStateMap", new GameStateMap, 0);
		initSubsystem(TheGameState, "TheGameState", new GameState, 0);
		initSubsystem(TheGameResultsQueue, "TheGameResultsQueue", GameResultsInterface::createNewGameResultsInterface(), 0);
		initSubsystem(TheLivingWorldBuildingTemplateStore, "TheLivingWorldBuildingTemplateStore", new Rva0022C0CDSubsystem, (Xfer *)&xferCRC);
		initSubsystem(TheAwardSystemManager, "TheAwardSystemManager", new Rva0022C142Subsystem, 0);
		initSubsystem(TheCreateAHeroManager, "TheCreateAHeroManager", new Rva0022C1B7Subsystem, (Xfer *)&xferCRC);
		initSubsystem(TheScoredKillEvaAnnouncerController, "TheScoredKillEvaAnnouncerController", new Rva0022C22CSubsystem, (Xfer *)&xferCRC);
		initSubsystem(TheLivingWorldAutoResolveReinforcementScheduleStore, "TheLivingWorldAutoResolveReinforcementScheduleStore", new Rva0022C2A1Subsystem, (Xfer *)&xferCRC);
		initSubsystem(TheLivingWorldAutoResolveResourceBonusScheduleStore, "TheLivingWorldAutoResolveResourceBonusScheduleStore", new Rva0022C316Subsystem, (Xfer *)&xferCRC);
		initSubsystem(TheLivingWorldAutoResolveSciencePurchasePointBonusScheduleStore, "TheLivingWorldAutoResolveSciencePurchasePointBonusScheduleStore", new Rva0022C38BSubsystem, (Xfer *)&xferCRC);

		xferCRC.close();
		TheSubsystemList->m_xfer = 0;
		TheGlobalData->m_iniCRC = xferCRC.m_crc;
		TheGlobalData->m_iniCRC += ((CreateAHeroCRC *)TheCreateAHeroManager)->getCRC();
		TheSubsystemList->postProcessLoadAll();
		setFramesPerSecondLimit(TheGlobalData->m_framesPerSecondLimit);
		TheAudio->setOn(TheGlobalData->m_audioOn && TheGlobalData->m_musicOn, 1);
		TheAudio->setOn(TheGlobalData->m_audioOn && TheGlobalData->m_soundsOn, 2);
		TheAudio->setOn(TheGlobalData->m_audioOn && TheGlobalData->m_sounds3DOn, 4);
		TheAudio->setOn(TheGlobalData->m_audioOn && TheGlobalData->m_speechOn, 8);
		TheAudio->setOn(TheGlobalData->m_audioOn && TheGlobalData->m_9A1, 0x10);

		TheNetwork = 0;
		TheMapCache = new MapCache;
		TheMapCache->updateCache();
		if (TheGlobalData->m_buildMapCache)
			m_quitting = true;

		if (TheGlobalData->m_initialFile.isEmpty() == false)
		{
			AsciiString fname = TheGlobalData->m_initialFile;
			fname.toLower();
			if (fname.endsWithNoCase(".map"))
			{
				TheGlobalData->m_shellMapOn = false;
				TheGlobalData->m_playIntro = false;
				TheGlobalData->m_pendingFile = TheGlobalData->m_initialFile;
				if (!TheGlobalData->m_AC5)
				{
					const MapMetaData *md = 0;
					if (TheMapCache)
						md = TheMapCache->findMap(TheGlobalData->m_initialFile);
					GameMessage *msg = TheMessageStream->appendMessage(0x1E);
					if (md && md->m_isMultiplayer)
					{
						if (!TheSkirmishGameInfo)
							TheSkirmishGameInfo = new SkirmishGameInfo;
						TheSkirmishGameInfo->init();
						GameSlot *first = TheSkirmishGameInfo->getSlot(0);
						TheSkirmishGameInfo->m_38 = first->m_38;
						TheSkirmishGameInfo->m_3C = first->m_3C;
						TheSkirmishGameInfo->reset();
						TheSkirmishGameInfo->rva003FF268();
						TheSkirmishGameInfo->setSeed(time(0));
						TheSkirmishGameInfo->setMap(TheGlobalData->m_initialFile);
						TheSkirmishGameInfo->setMapCRC(md->m_CRC);
						TheSkirmishGameInfo->setMapSize(md->m_filesize);
						GameSlot slot;
						slot.m_name = UnicodeString(L"Test");
						GameSlotConnectInfo info;
						info.m_a = 0;
						info.m_b = 0;
						slot.setState(6, UnicodeString(L"Test"), &info);
						TheSkirmishGameInfo->setSlot(0, slot);
						msg->appendIntegerArgument(2);
					}
					else
					{
						msg->appendIntegerArgument(0);
					}
					msg->appendIntegerArgument(1);
					msg->appendIntegerArgument(0);
				}
			}
			else if (fname.endsWithNoCase(".rep"))
			{
				TheRecorder->playbackFile(UnicodeString(fname));
			}
		}

		if (getenv("_EA_RTS_HEADLESS"))
		{
			TheGlobalData->m_shellMapOn = false;
			TheGlobalData->m_playIntro = false;
			TheGlobalData->m_D36 = false;
		}

		if (TheMapCache && TheGlobalData->m_shellMapOn)
		{
			AsciiString lowerName = TheGlobalData->m_shellMapName;
			lowerName.toLower();
			MapCacheNode *it = TheMapCache->find(lowerName);
			if (it == TheMapCache->end())
				TheGlobalData->m_shellMapOn = false;
		}

		if (!TheGlobalData->m_playIntro)
			TheGlobalData->m_afterIntro = true;
		Rva00419CC8Init();
		Rva00419BFAInit();
	}
	catch (ErrorCode ec)
	{
		if (ec == ERROR_INVALID_D3D)
		{
			AsciiString prompt("ERROR:D3DFailurePrompt");
			AsciiString mesg("ERROR:D3DFailureMessage");
			if (TheGameText)
			{
				UnicodeString uprompt = TheGameText->fetch(prompt, 0);
				UnicodeString umesg = TheGameText->fetch(mesg, 0);
				if (g_00DFE718)
				{
					MessageBoxW(0, umesg.str(), uprompt.str(), 0x1010);
				}
				else
				{
					AsciiString aprompt;
					AsciiString amesg;
					aprompt.translate(uprompt);
					amesg.translate(umesg);
					SetWindowPos(ApplicationHWnd, (void *)-2, 0, 0, 0, 0, 3);
					MessageBoxA(0, amesg.str(), aprompt.str(), 0x2010);
				}
				_exit(1);
			}
			_bfme_debugRecordCallsite(1);
			theDebug->crashBegin();
			theDebug->stream(0, 0, 0)->write(mesg.str())->finish(1);
		}
	}
	catch (INIException &e)
	{
		const char *failure = e.mFailureMessage;
		if (failure)
		{
			_bfme_debugRecordCallsite(1);
			theDebug->crashBegin();
			put(put(theDebug->stream(0, 0, 0), "\n\n"), e.mFailureMessage)->finish(1);
		}
		else
		{
			_bfme_debugRecordCallsite(1);
			theDebug->crashBegin();
			theDebug->stream(0, 0, 0)->write("\n\nUncaught INI exception during initialization.")->finish(1);
		}
	}
	catch (...)
	{
		_bfme_debugRecordCallsite(1);
		theDebug->crashBegin();
		theDebug->stream(0, 0, 0)->write("Uncaught Exception during initialization.")->finish(1);
	}

	if (!TheGlobalData->m_playIntro)
		TheGlobalData->m_afterIntro = true;
	m_34 = 0;
	m_38 = g_009BA4E8 / g_Va00DBA4E4;
	m_48 = 0.0f;
	m_44 = (float)m_38;
	Rva00419CC8Init();
	TheSubsystemList->resetAll();
	HideControlBar(true);
	if (TheGlobalData->m_9AC)
		TheSubsystemList->rva001B4EAB();
	if (BFME2WatchdogEnabled)
		theBfmeDfe6e4 = createWatchdog(300, 10, 10);
	if (theBfmeDfe6e4)
		theBfmeDfe6e4->start();
	initTiming();
	m_54 = timeGetTime();
	Rva0002BBC9Update();
}
