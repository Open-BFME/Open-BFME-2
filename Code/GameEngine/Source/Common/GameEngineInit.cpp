// cl: /O1 /DNDEBUG /MD /EHsc /G7 /arch:SSE /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB
// GameEngine::init, retail 0x0022E2E4..0x0023054C (8808 bytes).
// Identity: GameEngine vtable VA 0x00BE7188 slot 14; Zero Hour GameEngine::init
// provides the semantic structure. BFME2's subsystem names, allocation sizes,
// globals, virtual slots, map/replay startup and timing calls come from retail.
// Global declarations bind to the existing data-ledger owners. Typed reference
// casts below provide this body's retail-proven subsystem views of those slots;
// they do not create extra globals or assert the ledger's provisional type names.
// Unknown subsystem identities and unrecovered fields keep address/offset names.
// The three catch funclets are included in this complete boundary.
//
// VC7.1 must see the already recovered rva0022D189 setter definition in this
// TU. A declaration alone pessimistically keeps the timing object's address
// escaped and gives it a separate stack slot: 18 byte differences. Visibility
// of the actual setter (one hook call, write to +4, no escaped this pointer)
// restores retail's frame and sharing with expired catch/connection locals.
// This remains C++ with ordinary lifetimes, not an explicit storage overlay.
// stlport
#include <map>
#include <hash_map>
#include <vector>
#include "ascii_string.h"
#include "unicode_string.h"

bool operator<(const AsciiString &left, const AsciiString &right);
namespace _STL {
template <> struct less<AsciiString> {
    bool operator()(const AsciiString &left, const AsciiString &right) const { return left < right; }
};
}

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
// The native startup bindings below differ from donor-placement names already
// in the ledger: LocomotorStore ctor 0x22078E; ArmorStore ctor 0x360BB8;
// createVictoryConditions 0x41DFB; GameResults factory 0x551B28. Their existing
// names are not proof those are this call's targets. Keep these allocation and
// factory entry points address-named until that earlier identity work is
// reconciled. The registration roles and native target RVAs here are direct
// target evidence; no extra address is appended to those conflicting names.
class LocomotorStore;
class Rva001E7270Store { public: Rva001E7270Store(); char m_data[0x24]; };
class SpecialPowerStore { public: SpecialPowerStore(); char m_data[0x1c]; };
class DamageFXStore;
class Rva00360BB8Store { public: Rva00360BB8Store(); char m_data[0x20]; };
class ArmorStore;
enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};
namespace rts
{
template <typename T> struct hash;
template <> struct hash<NameKeyType>
{
	size_t operator()(const NameKeyType &value) const { return (size_t)value; }
};
}
class ArmorTemplate { char m_data[0x98]; };
struct Rva001D9651Element { char m_data[1]; };
typedef std::hash_map<int, Rva001D9651Element> Rva001D9651Map;
typedef std::hash_map<NameKeyType, ArmorTemplate, rts::hash<NameKeyType>,
	std::equal_to<NameKeyType> > ArmorTemplateMap;
class Object;
class Rva001D9670Store : public SubsystemInterface
{
public:
	Rva001D9670Store();

private:
	Rva001D9651Map m_mapStorage;
	std::vector<Object *> m_ready;
	std::vector<Object *> m_pending;
};
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
extern class Rva00DFF024Registry *TheRva00DFF024Registry;
extern ModuleFactory *TheModuleFactory;
extern class MessageStream *MessageStreamSubsystem;
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
extern class Rva00A027B8 *g_00A027B8;
extern Rva0022A809Subsystem *TheCrowdResponseStore;
extern class LivingWorldAutoResolveArmorStore *TheLivingWorldAutoResolveArmorStore;
extern class Rva0041811D *g_Va00E030C0;
extern class Rva0041811D *g_Va00E030B0;
extern class Rva0041811D *g_Va00E030A8;
extern class Rva0041811D *g_Va00E030B8;
extern struct HandicapStore *g_00E03040;
extern struct Rva0039B95FHolder *g_00E031E8;
extern EmotionSystem *TheEmotionSystem;
extern class Rva002D06CA *TheThingFactory;
extern class Rva00425F10 *TheStancesStore;
extern Rva0022AD10Subsystem *TheFormationAssistant;
extern class AiOrdersManager *TheAiOrdersManager;
extern class Rva00421520 *g_00E03158;
extern class Rva00288CFA *g_00DFECC4;
extern Rva0022AEE4Subsystem *TheDelayedExperienceLevelGrantSystem;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
extern class Rva002E18C3Lookup *Va00DFF0B0Lookup;
extern class Rva002E18C3Lookup *Va00E03140Lookup;
extern class Rva003EF328 *g_00E02E60;
extern class LivingWorldManager *TheLivingWorldManager;
extern class LivingWorldLogic *TheLivingWorldLogic;
extern class ClientFrameSubsystem *TheGameClient;
extern class W3DTerrainVisual *TheTerrainVisual;
extern AI *TheAI;
extern AerialPathfinder *TheAerialPathfinder;
extern Rva0022B3F6Subsystem *TheSplineService;
extern Rva0022B46BSubsystem *TheAttributeModifierStore;
extern void *g_Va00DFE750;
extern ScriptEngine *TheScriptEngine;
extern LuaScriptEngine *TheLuaScriptEngine;
extern TeamFactory *TheTeamFactory;
extern CrateSystem *TheCrateSystem;
extern PlayerList *ThePlayerList;
extern GameLogic *TheGameLogic;
extern struct Bfme939Helper *g_bfme939Helper;
extern Radar *TheRadar;
extern struct UnknownE03138 *g_00E03138;
extern class MetaMap *g_00DFDBF8;
extern HouseColorSystem *TheHouseColorSystem;
extern Rva0022BA67Subsystem *TheMeshInstancingManager;
extern class Rva00E02D6C *TheCampaignManager;
extern void *g_Va00E02F3C;
extern class Rva002872BA *TheTriggerManager;
extern void *g_Va00E01EDC;
extern class Rva002A8F24 *g_00DFEEF8;
extern Rva0022BD25Subsystem *TheArmyDefinitionManager;
extern class Rva0022BD9ASubsystem *g_00E03124;
extern class Rva003ED2A3Manager *g_manager;
extern struct Rva005055DESrc *g_00E0311C;
extern ActionManager *TheActionManager;
extern void *g_Va00E030D8;
extern GameState *TheGameState;
extern GameResultsInterface *TheGameResultsQueue;
extern int g_00DFF09C;
extern class Rva0040AAD5 *g_00E02F74;
extern class Rva0021A54A *TheHeroManager;
extern Rva0022C22CSubsystem *TheScoredKillEvaAnnouncerController;
extern void *g_00E03064;
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

class Rva001B4EAB { public: void rva001B4EAB(); };

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
extern class Rva00A00958Obj *g_Rva00A00958;

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
extern "C" void *theLogicRandomLogFile;
extern bool TheDeepCRC;
extern bool g_bfmeDoneAPB;

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
	char m_30[0x100 - 0x30];
};

enum SlotState { SLOT_PLAYER = 6 };
struct GameSlotConnectInfo { public: Int m_a; short m_b; };

class GameSlot
{
public:
	GameSlot();
	GameSlot(const GameSlot &that);
	virtual ~GameSlot();
	void setState(SlotState state, UnicodeString name, const GameSlotConnectInfo *info);
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
extern class BfmeDfe6e4 *theBfmeDfe6e4;
extern bool BFME2WatchdogEnabled;

class Rva00077710Value { public: void rva0022D189(Int value); Int m_a; Int m_b; };
Int Rva0022CC0EHook(Int a, Int b);
void Rva0002BBC9Update();
void Rva00419CC8Init();
void Rva00419BFAInit();
void HideControlBar(Bool immediate);
extern Int g_009BA4E8;
extern int g_Va00DBA4E4;

void Rva000B3FD0(Int argc, char *argv[]);
void InitRandom();
AsciiString GetRegistryLanguage();
void Rva00600665Set(char *language);
void parseCommandLine(Int argc, char *argv[]);
GameTextInterface *CreateGameTextInterface();
RecorderClass *createRecorder();
VictoryConditionsInterface *Rva00420353CreateVictoryConditions();
class GameResultsInterface;
GameResultsInterface *Rva0041AA6FCreateGameResults();

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
class MapCache : public _STL::map<AsciiString, MapMetaData>
{
public:
    MapCache();
    void updateCache();
    const MapMetaData *findMap(AsciiString mapName);
private:
    char m_0C[0x18];
};
extern MapCache *TheMapCache;




Int Rva0022CB5CHook(Int a, Int b);
 void Rva00077710Value::rva0022D189(Int value) { m_b = Rva0022CB5CHook(value, value); }

// ?GameEngine::initTiming absent-from-retail (inlined into init)
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

// Target evidence: Ghidra boundary 0x001D9670..0x001D96EB (124 bytes); the
// constructor calls the 12-byte SubsystemInterface body at +0, the rowed map
// constructor at +0x0C, stores VA 0x00BD9CB0, then constructs and clears the
// pointer-vector slots at +0x20/+0x2C. The member model follows that
// order; the map constructor type is a rowed byte-equivalent view and does not
// assert the target's mapped type. Constructor and element names stay address-derived.
Rva001D9670Store::Rva001D9670Store()
{
	((ArmorTemplateMap *)&m_mapStorage)->clear();
	m_ready.clear();
	m_pending.clear();
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
		(reinterpret_cast<CommandList *&>(g_Rva00A00958)) = new CommandList;
		(reinterpret_cast<CommandList *&>(g_Rva00A00958))->init();

		BFMECRCWriter xferCRC(true);
		TheSubsystemList->m_xfer = (Xfer *)&xferCRC;

		initSubsystem(TheSubsystemLegend, "TheSubsystemLegend", new SubsystemLegend, 0);
		ini.loadFile("Data\\INI\\Default\\SubsystemLegend.ini", INI_LOAD_OVERWRITE, 0);
		initSubsystem(TheWritableGlobalData, "TheWritableGlobalData", new GlobalData, 0);
		parseCommandLine(argc, argv);
		if ((reinterpret_cast<unsigned char&>(TheDeepCRC)) || (reinterpret_cast<unsigned char&>(g_bfmeDoneAPB)))
			theLogicRandomLogFile = new Rva002CEC0A;
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
		initSubsystem((reinterpret_cast<FunctionLexicon *&>(TheRva00DFF024Registry)), "TheFunctionLexicon", createFunctionLexicon(), 0);
		initSubsystem(TheModuleFactory, "TheModuleFactory", createModuleFactory(), 0);
		initSubsystem(MessageStreamSubsystem, "TheMessageStream", createMessageStream(), 0);
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
		initSubsystem(TheLocomotorStore, "TheLocomotorStore", (LocomotorStore *)new Rva001E7270Store, (Xfer *)&xferCRC);
		initSubsystem(TheSpecialPowerStore, "TheSpecialPowerStore", new SpecialPowerStore, (Xfer *)&xferCRC);
		initSubsystem(TheDamageFXStore, "TheDamageFXStore", (DamageFXStore *)new Rva00360BB8Store, (Xfer *)&xferCRC);
		initSubsystem(TheArmorStore, "TheArmorStore", (ArmorStore *)new Rva001D9670Store, (Xfer *)&xferCRC);
		initSubsystem((reinterpret_cast<BuildAssistant *&>(g_00A027B8)), "TheBuildAssistant", new BuildAssistant, 0);
		initSubsystem(TheCrowdResponseStore, "TheCrowdResponseStore", new Rva0022A809Subsystem, 0);
		initSubsystem((reinterpret_cast<Rva0022A87ESubsystem *&>(TheLivingWorldAutoResolveArmorStore)), "TheLivingWorldAutoResolveArmorStore", new Rva0022A87ESubsystem, (Xfer *)&xferCRC);
		initSubsystem((reinterpret_cast<Rva0022A8F3Subsystem *&>(g_Va00E030C0)), "TheLivingWorldAutoResolveWeaponStore", new Rva0022A8F3Subsystem, (Xfer *)&xferCRC);
		initSubsystem((reinterpret_cast<Rva0022A968Subsystem *&>(g_Va00E030B0)), "TheLivingWorldAutoResolveBodyStore", new Rva0022A968Subsystem, (Xfer *)&xferCRC);
		initSubsystem((reinterpret_cast<Rva0022A9DDSubsystem *&>(g_Va00E030A8)), "TheLivingWorldAutoResolveLeadershipStore", new Rva0022A9DDSubsystem, (Xfer *)&xferCRC);
		initSubsystem((reinterpret_cast<Rva0022AA52Subsystem *&>(g_Va00E030B8)), "TheLivingWorldAutoResolveCombatChainStore", new Rva0022AA52Subsystem, (Xfer *)&xferCRC);
		initSubsystem((reinterpret_cast<Rva0022AAC7Subsystem *&>(g_00E03040)), "TheLivingWorldAutoResolveHandicapStore", new Rva0022AAC7Subsystem, (Xfer *)&xferCRC);
		initSubsystem((reinterpret_cast<Rva0022AB3CSubsystem *&>(g_00E031E8)), "TheMissionObjectiveTracker", new Rva0022AB3CSubsystem, (Xfer *)&xferCRC);
		initSubsystem(TheEmotionSystem, "TheEmotionSystem", new EmotionSystem, 0);
		{
		Rva000309B0 initScope('init');
		initSubsystem((reinterpret_cast<ThingFactory *&>(TheThingFactory)), "TheThingFactory", createThingFactory(), (Xfer *)&xferCRC);
		}
		initSubsystem((reinterpret_cast<Rva0022AC9BSubsystem *&>(TheStancesStore)), "TheStancesStore", new Rva0022AC9BSubsystem, 0);
		initSubsystem(TheFormationAssistant, "TheFormationAssistant", new Rva0022AD10Subsystem, 0);
		initSubsystem((reinterpret_cast<Rva0022AD85Subsystem *&>(TheAiOrdersManager)), "TheAiOrdersManager", new Rva0022AD85Subsystem, 0);
		initSubsystem((reinterpret_cast<Rva0022ADFASubsystem *&>(g_00E03158)), "TheLightPointSystem", new Rva0022ADFASubsystem, (Xfer *)&xferCRC);
		initSubsystem((reinterpret_cast<ExperienceLevelSystem *&>(g_00DFECC4)), "TheExperienceLevelSystem", new ExperienceLevelSystem, (Xfer *)&xferCRC);
		initSubsystem(TheDelayedExperienceLevelGrantSystem, "TheDelayedExperienceLevelGrantSystem", new Rva0022AEE4Subsystem, 0);
		initSubsystem((reinterpret_cast<Rva0022AF59Subsystem *&>(g_bfmeAptWindowManager)), "TheAptPlayer", createAptPlayer(), 0);
		initSubsystem((reinterpret_cast<Rva0022AFCESubsystem *&>(Va00DFF0B0Lookup)), "TheLivingWorldPlayerTemplateStore", new Rva0022AFCESubsystem, (Xfer *)&xferCRC);
		initSubsystem((reinterpret_cast<Rva0022B043Subsystem *&>(Va00E03140Lookup)), "TheLivingWorldAITemplateStore", new Rva0022B043Subsystem, (Xfer *)&xferCRC);
		initSubsystem((reinterpret_cast<Rva0022B0B8Subsystem *&>(g_00E02E60)), "TheLivingWorldRegionEffectsManagerStore", new Rva0022B0B8Subsystem, 0);
		initSubsystem((reinterpret_cast<Rva0022B12DSubsystem *&>(TheLivingWorldManager)), "TheLivingWorldManager", new Rva0022B12DSubsystem, 0);
		initSubsystem((reinterpret_cast<Rva0022B1A2Subsystem *&>(TheLivingWorldLogic)), "TheLivingWorldLogic", new Rva0022B1A2Subsystem, (Xfer *)&xferCRC);
		initSubsystem((reinterpret_cast<GameClient *&>(TheGameClient)), "TheGameClient", createGameClient(), 0);
		initSubsystem((reinterpret_cast<Rva0022B28CSubsystem *&>(TheTerrainVisual)), "TheLinearCampaignManager", new Rva0022B28CSubsystem, (Xfer *)&xferCRC);
		initSubsystem(TheAI, "TheAI", new AI, (Xfer *)&xferCRC);
		initSubsystem(TheAerialPathfinder, "TheAerialPathfinder", new AerialPathfinder, (Xfer *)&xferCRC);
		initSubsystem(TheSplineService, "TheSplineService", new Rva0022B3F6Subsystem, (Xfer *)&xferCRC);
		initSubsystem(TheAttributeModifierStore, "TheAttributeModifierStore", new Rva0022B46BSubsystem, (Xfer *)&xferCRC);
		initSubsystem((reinterpret_cast<Rva0022B4E0Subsystem *&>(g_Va00DFE750)), "TheTaintManager", (Rva0022B4E0Subsystem *)new BfmeTaintManager, 0);
		initSubsystem(TheScriptEngine, "TheScriptEngine", new ScriptEngine, 0);
		initSubsystem(TheLuaScriptEngine, "TheLuaScriptEngine", new LuaScriptEngine, 0);
		initSubsystem(TheTeamFactory, "TheTeamFactory", new TeamFactory, 0);
		initSubsystem(TheCrateSystem, "TheCrateSystem", new CrateSystem, (Xfer *)&xferCRC);
		initSubsystem(ThePlayerList, "ThePlayerList", new PlayerList, 0);
		initSubsystem(TheGameLogic, "TheGameLogic", createGameLogic(), 0);
		initSubsystem((reinterpret_cast<RecorderClass *&>(g_bfme939Helper)), "TheRecorder", createRecorder(), 0);
		initSubsystem(TheRadar, "TheRadar", createRadar(), 0);
		initSubsystem((reinterpret_cast<VictoryConditionsInterface *&>(g_00E03138)), "TheVictoryConditions", Rva00420353CreateVictoryConditions(), 0);
		initSubsystem(g_00DFDBF8, "TheMetaMap", new MetaMap, 0);
		initSubsystem(TheHouseColorSystem, "TheHouseColorSystem", new HouseColorSystem, 0);
		initSubsystem(TheMeshInstancingManager, "TheMeshInstancingManager", new Rva0022BA67Subsystem, 0);
		initSubsystem((reinterpret_cast<Rva0022BADCSubsystem *&>(TheCampaignManager)), "TheLivingWorldCampaignManager", new Rva0022BADCSubsystem, 0);
		initSubsystem((reinterpret_cast<VictorySystem *&>(g_Va00E02F3C)), "TheVictorySystem", new VictorySystem, 0);
		initSubsystem((reinterpret_cast<Rva0022BBC6Subsystem *&>(TheTriggerManager)), "TheFireLogicSystem", new Rva0022BBC6Subsystem, 0);
		initSubsystem((reinterpret_cast<Rva0022BC3BSubsystem *&>(g_Va00E01EDC)), "TheMineshaftPortalNetworkManager", new Rva0022BC3BSubsystem, 0);
		initSubsystem((reinterpret_cast<Rva0022BCB0Subsystem *&>(g_00DFEEF8)), "TheSkirmishAIManager", new Rva0022BCB0Subsystem, 0);
		initSubsystem(TheArmyDefinitionManager, "TheArmyDefinitionManager", new Rva0022BD25Subsystem, 0);
		initSubsystem(g_00E03124, "TheBaseTemplateLibrary", new Rva0022BD9ASubsystem, 0);
		initSubsystem((reinterpret_cast<Rva0022BE0FSubsystem *&>(g_manager)), "TheThreatFinderManager", new Rva0022BE0FSubsystem, 0);
		initSubsystem((reinterpret_cast<Rva0022BE84Subsystem *&>(g_00E0311C)), "TheAITargetHeuristicLibrary", new Rva0022BE84Subsystem, 0);
		ini.loadFile("CommandMap.ini", INI_LOAD_OVERWRITE, 0);
		initSubsystem(TheActionManager, "TheActionManager", new ActionManager, 0);
		initSubsystem((reinterpret_cast<GameStateMap *&>(g_Va00E030D8)), "TheGameStateMap", new GameStateMap, 0);
		initSubsystem(TheGameState, "TheGameState", new GameState, 0);
		initSubsystem(TheGameResultsQueue, "TheGameResultsQueue", Rva0041AA6FCreateGameResults(), 0);
		initSubsystem((reinterpret_cast<Rva0022C0CDSubsystem *&>(g_00DFF09C)), "TheLivingWorldBuildingTemplateStore", new Rva0022C0CDSubsystem, (Xfer *)&xferCRC);
		initSubsystem((reinterpret_cast<Rva0022C142Subsystem *&>(g_00E02F74)), "TheAwardSystemManager", new Rva0022C142Subsystem, 0);
		initSubsystem((reinterpret_cast<Rva0022C1B7Subsystem *&>(TheHeroManager)), "TheCreateAHeroManager", new Rva0022C1B7Subsystem, (Xfer *)&xferCRC);
		initSubsystem(TheScoredKillEvaAnnouncerController, "TheScoredKillEvaAnnouncerController", new Rva0022C22CSubsystem, (Xfer *)&xferCRC);
		initSubsystem((reinterpret_cast<Rva0022C2A1Subsystem *&>(g_00E03064)), "TheLivingWorldAutoResolveReinforcementScheduleStore", new Rva0022C2A1Subsystem, (Xfer *)&xferCRC);
		initSubsystem(TheLivingWorldAutoResolveResourceBonusScheduleStore, "TheLivingWorldAutoResolveResourceBonusScheduleStore", new Rva0022C316Subsystem, (Xfer *)&xferCRC);
		initSubsystem(TheLivingWorldAutoResolveSciencePurchasePointBonusScheduleStore, "TheLivingWorldAutoResolveSciencePurchasePointBonusScheduleStore", new Rva0022C38BSubsystem, (Xfer *)&xferCRC);

		xferCRC.close();
		TheSubsystemList->m_xfer = 0;
		TheGlobalData->m_iniCRC = xferCRC.m_crc;
		TheGlobalData->m_iniCRC += ((CreateAHeroCRC *)(reinterpret_cast<Rva0022C1B7Subsystem *&>(TheHeroManager)))->getCRC();
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
					GameMessage *msg = MessageStreamSubsystem->appendMessage(0x1E);
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
						slot.setState(SLOT_PLAYER, UnicodeString(L"Test"), &info);
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
				(reinterpret_cast<RecorderClass *&>(g_bfme939Helper))->playbackFile(UnicodeString(fname));
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
			MapCache::iterator it = TheMapCache->find(lowerName);
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
		((Rva001B4EAB *)TheSubsystemList)->rva001B4EAB();
	if (BFME2WatchdogEnabled)
		(reinterpret_cast<Watchdog *&>(theBfmeDfe6e4)) = createWatchdog(300, 10, 10);
	if ((reinterpret_cast<Watchdog *&>(theBfmeDfe6e4)))
		(reinterpret_cast<Watchdog *&>(theBfmeDfe6e4))->start();
	initTiming();
	m_54 = timeGetTime();
	Rva0002BBC9Update();
}
