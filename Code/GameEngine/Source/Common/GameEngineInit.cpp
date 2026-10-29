// cl: /O1 /DNDEBUG /MD /EHsc /G7 /arch:SSE /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2 /D_STLP_USE_STATIC_LIB
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
// stlport46
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#define _STLP_BFME_LOWER_BOUND_EXTERN  // call retail's one __lower_bound<const size_t*> (vendor/stlport/stl/_hashtable.c)
#include <map>
#include <hash_map>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "ascii_string.h"
#include "unicode_string.h"

// map/set<unsigned> internals otherwise instantiate the less<unsigned>::operator()
// COMDAT (one byte shape per TU flags); a declaration-only specialization
// stops this TU emitting its copy so callers bind the kept copy.
// Plain (non-dllimport) form: no __imp_ reference is emitted.
namespace _STL {
template <> bool less<unsigned>::operator()(const unsigned &a, const unsigned &b) const;
}

#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::_Vector_base(allocator<void *> const &); }
namespace _STL { template <> vector<void *, allocator<void *> >::vector(allocator<void *> const &); }
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::~_Vector_base(); }
namespace _STL { template <> vector<void *, allocator<void *> >::~vector(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_clear(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_fill_insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_insert_overflow(void **, void *const &, __true_type const &, unsigned int, bool); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_set(void **, void **, void **); }
namespace _STL { template <> void ** allocator<void *>::allocate(unsigned int, void const *); }
namespace _STL { template <> unsigned int vector<void *, allocator<void *> >::capacity() const; }
namespace _STL { template <> void vector<void *, allocator<void *> >::insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::reserve(unsigned int); }
namespace _STL { template <> allocator<void *>::~allocator(); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@U?$_Hashtable_node@U?$pair@$$CBHURva001D9651Element@@@_STL@@@_STL@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva001D9651Element;
namespace _STL { template <> void allocator<_Hashtable_node<pair<int const ,Rva001D9651Element> > >::deallocate(_Hashtable_node<pair<int const ,Rva001D9651Element> > *,unsigned int); }
// Suppress this TU's non-retail copy of ??1?$vector@PAVObject@@V?$allocator@PAVObject@@@_STL@@@_STL@@QAE@XZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class Object;
namespace _STL { template <> vector<Object *,allocator<Object *> >::~vector(); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@U?$_Hashtable_node@U?$pair@$$CBW4NameKeyType@@VArmorTemplate@@@_ST:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
enum NameKeyType; class ArmorTemplate;
namespace _STL { template <> void allocator<_Hashtable_node<pair<NameKeyType const ,ArmorTemplate> > >::deallocate(_Hashtable_node<pair<NameKeyType const ,ArmorTemplate> > *,unsigned int); }
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@PAVObject@@@_STL@@QBEXPAPAVObject@@I@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class Object;
namespace _STL { template <> void allocator<Object *>::deallocate(Object **, size_t); }
// Suppress this TU's non-retail copy of ??1?$_Vector_base@PAVObject@@V?$allocator@PAVObject@@@_STL@@@_STL@@QAE@XZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class Object;
namespace _STL { template <> _Vector_base<Object *, allocator<Object *> >::~_Vector_base(); }

// vector<void*> begin/end otherwise instantiate per-TU COMDATs (one byte
// shape per TU flags); explicit dllimport+forceinline specializations take
// those calls inline so this TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void **vector<void*>::begin()
{ return _M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void*>::end()
{ return _M_finish; }
template <> __declspec(dllimport) __forceinline
size_t vector<void*>::size() const
{ return size_t(this->_M_finish - this->_M_start); }
template <> __declspec(dllimport) __forceinline
void *&vector<void*>::operator[](size_t __n)
{ return *(begin() + __n); }
}

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

#define BFME2_SPLINE_INLINE_CTOR
#include "spline_service.h"
#undef BFME2_SPLINE_INLINE_CTOR

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
class Rva001E7270Store;
class Rva001E72B4 { public: Rva001E72B4(); char m_data[0x24]; };
class SpecialPowerStore { public: SpecialPowerStore(); char m_data[0x1c]; };
class DamageFXStore;
class Rva00360BB8Store;
class ArmorStore { public: ArmorStore(); char m_data[0x20]; };
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

// Use the existing map lifetime providers without emitting their helper copies.
namespace _STL {
template <> hash_map<int, Rva001D9651Element>::hash_map();
template <> hash_map<int, Rva001D9651Element>::~hash_map();
template <> void hashtable<pair<const int, Rva001D9651Element>, int, hash<int>, _Select1st<pair<const int, Rva001D9651Element> >, equal_to<int>, allocator<pair<const int, Rva001D9651Element> > >::clear();
}
typedef std::hash_map<NameKeyType, ArmorTemplate, rts::hash<NameKeyType>,
	std::equal_to<NameKeyType> > ArmorTemplateMap;
namespace _STL {
template <> void hashtable<pair<const NameKeyType, ArmorTemplate>, NameKeyType, rts::hash<NameKeyType>, _Select1st<pair<const NameKeyType, ArmorTemplate> >, equal_to<NameKeyType>, allocator<pair<const NameKeyType, ArmorTemplate> > >::clear();
}
class Object;
class Rva001D9670Store : public SubsystemInterface
{
public:
	Rva001D9670Store();
	virtual ~Rva001D9670Store();
	virtual void init() {}
	virtual bool vslot04(int reason);
	virtual bool vslot05();
	virtual void reset() {}
	virtual void update() {}

private:
	Rva001D9651Map m_mapStorage;
	std::vector<Object *> m_ready;
	std::vector<Object *> m_pending;
};
class BuildAssistant { public: BuildAssistant(); char m_data[0x28]; };
class Rva0022A809Subsystem { public: Rva0022A809Subsystem(); char m_data[0x24]; };
class Rva0022A87ESubsystem;
class Rva00427311 { public: Rva00427311(); char m_data[0x20]; };
class Rva0022A8F3Subsystem { public: Rva0022A8F3Subsystem(); char m_data[0x20]; };
class Rva0022A968Subsystem { public: Rva0022A968Subsystem(); char m_data[0x20]; };
class Rva0022A9DDSubsystem { public: Rva0022A9DDSubsystem(); char m_data[0x20]; };
class Rva0022AA52Subsystem { public: Rva0022AA52Subsystem(); char m_data[0x20]; };
class Rva0022AAC7Subsystem;
class Rva004134AE { public: Rva004134AE(); char m_data[0x18]; };
class Rva0022AB3CSubsystem;
class Rva00426713 { public: Rva00426713(); char m_data[0x14]; };
class EmotionSystem { public: EmotionSystem(); char m_data[0x30]; };
class ThingTemplate;
class ThingFactory;
class Rva0022AC9BSubsystem;
class Rva00425F10 { public: Rva00425F10(); char m_data[0x18]; };
class Rva0022AD10Subsystem;
class Rva00425CE2 { public: Rva00425CE2(); char m_data[0x38]; };
class Rva0022AD85Subsystem;
class Rva00355B61 { public: Rva00355B61(); char m_data[0x38]; };
class Rva0022ADFASubsystem;
class Rva00421242 { public: Rva00421242(); char m_data[0x18]; };
class ExperienceLevelSystem { public: ExperienceLevelSystem(); char m_data[0x34]; };
class Rva0022AEE4Subsystem;
class DelayedExperienceLevelGrantSystem { public: DelayedExperienceLevelGrantSystem(); char m_data[0x18]; };
class Rva0022AF59Subsystem;
class Rva0022AFCESubsystem;
class Rva002E1F42 { public: Rva002E1F42(); char m_data[0x18]; };
class Rva0022B043Subsystem;
class Rva004209CC { public: Rva004209CC(); char m_data[0x18]; };
class Rva0022B0B8Subsystem { public: Rva0022B0B8Subsystem(); char m_data[0x20]; };
class Rva0022B12DSubsystem { public: Rva0022B12DSubsystem(); char m_data[0x2d8]; };
class Rva0022B1A2Subsystem;
class LivingWorldLogic { public: LivingWorldLogic(); char m_data[0x17c]; };
class GameClient;
class Rva0022B28CSubsystem;
class Rva001ED41B { public: Rva001ED41B(); char m_data[0x20]; };
class AI { public: AI(); char m_data[0x24]; };
class AerialPathfinder { public: AerialPathfinder(); char m_data[0x14]; };

class Rva0022B46BSubsystem;
class Rva0022CA95 { public: Rva0022CA95(); char m_data[0x24]; };
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
class Rva0041FB13 { public: Rva0041FB13(); char m_data[0x24]; };
class Rva0022BADCSubsystem;
class Rva003B923B { public: Rva003B923B(); char m_data[0x30]; };
class VictorySystem { public: VictorySystem(); char m_data[0x140]; };
class Rva0022BBC6Subsystem;
class FireLogicSystem { public: FireLogicSystem(); char m_data[0xa0]; };
class Rva0022BC3BSubsystem;
class MineshaftPortalNetworkManager { public: MineshaftPortalNetworkManager(); char m_data[0x1c]; };
class Rva0022BCB0Subsystem;
class Rva002A8F24 { public: Rva002A8F24(); char m_data[0x944]; };
class Rva0022BD25Subsystem { public: Rva0022BD25Subsystem(); char m_data[0x20]; };
class Rva0022BD9ASubsystem { public: Rva0022BD9ASubsystem(); char m_data[0x34]; };
class Rva0022BE0FSubsystem { public: Rva0022BE0FSubsystem(); char m_data[0x20]; };
class Rva0022BE84Subsystem;
class Rva0041E4A3 { public: Rva0041E4A3(); char m_data[0x18]; };
class ActionManager { public: ActionManager(); char m_data[0xc]; };
class GameStateMap { public: GameStateMap(); char m_data[0x10]; };
class GameState { public: GameState(); char m_data[0xe1c]; };
class GameResultsInterface;
class Rva0022C0CDSubsystem { public: Rva0022C0CDSubsystem(); char m_data[0x38]; };
class Rva0022C142Subsystem;
class AwardSystemManager { public: AwardSystemManager(); char m_data[0x24]; };
class Rva0022C1B7Subsystem;
class CreateAHeroManager { public: CreateAHeroManager(); char m_data[0x1f4]; };
class Rva0022C22CSubsystem;
class Rva0041497D { public: Rva0041497D(); char m_data[0x1c]; };
class Rva0022C2A1Subsystem;
class Rva0022CD78 { public: Rva0022CD78(); char m_data[0x2c]; };
class Rva0022C316Subsystem;
class Rva0022DE6B { public: Rva0022DE6B(); char m_data[0x18]; };
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
extern class FunctionLexicon *TheFunctionLexicon;
extern ModuleFactory *TheModuleFactory;
extern class MessageStream *TheMessageStream;
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
class BuildAssistant;
extern BuildAssistant *TheBuildAssistant;
// VA 0x00E0307C (RVA 0x00A0307C, retail's zero-filled .data tail): the slot is
// already defined in Common/CrowdResponseBlockParse.cpp, the unit that parses the
// crowd-response blocks; the initSubsystem call below only assigns it.
extern Rva0022A809Subsystem *TheCrowdResponseStore;
extern class LivingWorldAutoResolveArmorStore *TheLivingWorldAutoResolveArmorStore;
extern class Rva0041811D *TheLivingWorldAutoResolveWeaponStore;
extern class Rva0041811D *TheLivingWorldAutoResolveBodyStore;
extern class Rva0041811D *TheLivingWorldAutoResolveLeadershipStore;
extern class Rva0041811D *TheLivingWorldAutoResolveCombatChainStore;
extern struct HandicapStore *TheLivingWorldAutoResolveHandicapStore;
extern struct Rva0039B95FHolder *TheMissionObjectiveTracker;
extern EmotionSystem *TheEmotionSystem;
extern class ThingFactory *TheThingFactory;
extern class Rva00425F10 *TheStancesStore;
extern Rva0022AD10Subsystem *TheFormationAssistant;
extern class AiOrdersManager *TheAiOrdersManager;
extern class Rva00421520 *TheLightPointSystem;
extern ExperienceLevelSystem *TheExperienceLevelSystem;
class DelayedExperienceLevelGrantSystem;
extern DelayedExperienceLevelGrantSystem *TheDelayedExperienceLevelGrantSystem;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
extern class Rva002E18C3Lookup *TheLivingWorldPlayerTemplateStore;
extern class Rva002E18C3Lookup *TheLivingWorldAITemplateStore;
extern class Rva003EF328 *TheLivingWorldRegionEffectsManagerStore;
extern class LivingWorldManager *TheLivingWorldManager;
extern class LivingWorldLogic *TheLivingWorldLogic;
// TheGameClient is only an alias of the owned global TheGameClient (ledger names column); this unit reads the owner through its own view type.
extern class GameClient *TheGameClient;
#define TheGameClient (*(class ClientFrameSubsystem * *)&TheGameClient)
extern class LinearCampaignManager *TheLinearCampaignManager;
extern AI *TheAI;
extern AerialPathfinder *TheAerialPathfinder;
Rva0022B3F6Subsystem *TheSplineService = 0;
// TheAttributeModifierStore is only an alias of the owned global TheAttributeModifierStore (ledger names column); this unit reads the owner through its own view type.
extern class AttributeModifierStore *TheAttributeModifierStore;
#define TheAttributeModifierStore (*(Rva0022B46BSubsystem * *)&TheAttributeModifierStore)
extern BfmeTaintManager *TheTaintManager;
extern ScriptEngine *TheScriptEngine;
extern LuaScriptEngine *TheLuaScriptEngine;
extern TeamFactory *TheTeamFactory;
extern CrateSystem *TheCrateSystem;
extern PlayerList *ThePlayerList;
extern GameLogic *TheGameLogic;
class RecorderClass; extern RecorderClass *TheRecorder;
extern Radar *TheRadar;
extern class VictoryConditionsInterface *TheVictoryConditions;
class MetaMap;
extern MetaMap *TheMetaMap;
extern HouseColorSystem *TheHouseColorSystem;
extern Rva0041FB13 *TheMeshInstancingManager;
extern class Rva00E02D6C *TheCampaignManager;
class VictorySystem;
extern VictorySystem *TheVictorySystem;
extern class Rva002872BA *TheTriggerManager;
extern void *TheMineshaftPortalNetworkManager;
extern class Rva002A8F24 *TheSkirmishAIManager;
extern Rva0022BD25Subsystem *TheArmyDefinitionManager;
// TheBaseTemplateLibrary (0x00A03124): registered below by name; retail .data starts it at 0.
class Rva0022BD9ASubsystem;
Rva0022BD9ASubsystem *TheBaseTemplateLibrary = 0;
extern class ThreatFinderManager *TheThreatFinderManager;
extern struct Rva005055DESrc *TheAITargetHeuristicLibrary;
extern ActionManager *TheActionManager;
extern void *TheGameStateMap;
extern GameState *TheGameState;
extern GameResultsInterface *TheGameResultsQueue;
extern class Rva0022C0CDSubsystem *TheLivingWorldBuildingTemplateStore;
extern class Rva0040AAD5 *TheAwardSystemManager;
// TheHeroManager is only an alias of the owned global TheCreateAHeroManager (ledger names column); this unit reads the owner through its own view type.
extern class CreateAHeroManager *TheCreateAHeroManager;
#define TheHeroManager (*(class Rva0021A54A * *)&TheCreateAHeroManager)
extern Rva0022C22CSubsystem *TheScoredKillEvaAnnouncerController;
extern void *TheLivingWorldAutoResolveReinforcementScheduleStore;
extern Rva0022C316Subsystem *TheLivingWorldAutoResolveResourceBonusScheduleStore;
extern Rva0022C38BSubsystem *TheLivingWorldAutoResolveSciencePurchasePointBonusScheduleStore;

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
// Bind the close calls to the existing whole 45-byte provider at RVA 0x0060C8CD.
class Gen009D6DD0 { public: void bfmeClose(); };

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
extern bool TheLiteCRC;

class Rva0033076E { public: Rva0033076E(); char m_data[0x1C]; };
class CameraAnimationList;
extern CameraAnimationList *TheCameraAnimationList;

// Scoped object retail builds around TheThingFactory's init with the
// four-character code 'init' (ctor 0x00030980, dtor 0x000309B0).
class Rva000309B0
{
public:
	Rva000309B0(UnsignedInt tag);
	~Rva000309B0();
private:
	void *m_previous;
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
	void enterGame();
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
class SkirmishGameInfo; extern SkirmishGameInfo *TheSkirmishGameInfo;

class RecorderClass { public: Bool playbackFile(UnicodeString filename); };

class Rva0022C1B7Subsystem;
class CreateAHeroCRC { public: UnsignedInt getCRC(); };

class Watchdog { public: virtual void slot0(); virtual void start(); };
Watchdog *createWatchdog(Int a, Int b, Int c);
extern class BfmeDfe6e4 *theBfmeDfe6e4;
extern bool BFME2WatchdogEnabled;

class Rva00077710Value
{
public:
	Rva00077710Value() {}
	Rva00077710Value(const Rva00077710Value &that) { m_b = that.m_b; }
	void rva0022D189(Int value);
	Bool operator!=(const Rva00077710Value &other) const;		// 0x0022CF4C
	Rva00077710Value *rva0022D89D(Rva00077710Value &result);	// 0x0022D89D
	Int m_a;
	Int m_b;
};
Int Rva0022CC0EHook(Int a, Int b);
void Rva0002BBC9Update();
void Rva00419CC8Init();
void Rva00419BFAInit();
void HideControlBar(Bool immediate);
extern int BfmeClientFramesPerSecond;
extern int BfmeLogicFramesPerSecond;

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

// GameEngine: the one declaration shared with the destructor units (same vtable).
#include "GameEngineVtableView.h"

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

// Retail 0x0022DA66 (195 B): the GameEngine constructor. Zero/one field
// defaults, a 1 ms timer period, then every slot of the +0x18 table is cleared
// by walking the obfuscated index from the first slot (setter 0x0022D189) to
// its encoded end value 0xE0092DC0 through the rowed operators 0x0022CF4C /
// 0x0022D89D. Retail returns the first slot by value into the loop variable;
// the copy constructor copies only +4 and, with first/slot sharing one home,
// remains as the self-copy `mov eax,[slot+4]; mov [slot+4],eax`. The volatile
// store keeps that self-copy (a plain one is deleted). The constant equal-arm
// wrap of the loop condition is the other half: it re-pairs the expression
// temps so the frame has retail's three 8-byte homes. Layout and names of
// +0x11..+0x40 are address-derived (not independently proven).
extern "C" __declspec(dllimport) unsigned int __stdcall timeBeginPeriod(unsigned int period);

GameEngine::GameEngine()
{
	m_maxFPS = 0;
	m_quitting = false;
	m_11 = false;
	m_14 = 0;
	m_34 = 0;
	m_38 = 1;
	m_3C = 0.0f;
	m_40 = false;
	m_44 = 1.0f;
	m_48 = 0.0f;
	m_4C = 0;
	m_50 = 0;
	m_54 = 0;
	m_58 = 0.0f;
	m_5C = 0;
	timeBeginPeriod(1);
	Rva00077710Value slot;
	slot.rva0022D189(0);
	*(volatile Int *)&slot.m_b = slot.m_b;
	Rva00077710Value end;
	end.m_b = (Int)0xE0092DC0;
	while ((1 ? (slot != end) : (slot != end)))
	{
		m_18[Rva0022CC0EHook(slot.m_b, slot.m_b)] = 0;
		Rva00077710Value next;
		slot.rva0022D89D(next);
	}
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
		if ((reinterpret_cast<unsigned char&>(TheDeepCRC)) || (reinterpret_cast<unsigned char&>(TheLiteCRC)))
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
		initSubsystem(TheFunctionLexicon, "TheFunctionLexicon", createFunctionLexicon(), 0);
		initSubsystem(TheModuleFactory, "TheModuleFactory", createModuleFactory(), 0);
		initSubsystem(TheMessageStream, "TheMessageStream", createMessageStream(), 0);
		initSubsystem(TheSidesList, "TheSidesList", new SidesList, 0);
		initSubsystem(TheCaveSystem, "TheCaveSystem", new CaveSystem, 0);
		initSubsystem(TheRankInfoStore, "TheRankInfoStore", new RankInfoStore, (Xfer *)&xferCRC);
		initSubsystem(ThePlayerAITypeSet, "ThePlayerAITypeSet", new PlayerAITypeSet, 0);
		initSubsystem(ThePlayerTemplateStore, "ThePlayerTemplateStore", new PlayerTemplateStore, (Xfer *)&xferCRC);
		TheCameraAnimationList = (CameraAnimationList *)new Rva0033076E;
		initSubsystem(TheParticleSystemManager, "TheFXParticleSystemManager", createParticleSystemManager(), 0);
		initSubsystem(TheFXListStore, "TheFXListStore", new FXListStore, (Xfer *)&xferCRC);
		initSubsystem(TheWeaponStore, "TheWeaponStore", new WeaponStore, (Xfer *)&xferCRC);
		initSubsystem(TheObjectCreationListStore, "TheObjectCreationListStore", new ObjectCreationListStore, (Xfer *)&xferCRC);
		initSubsystem(TheLocomotorStore, "TheLocomotorStore", (LocomotorStore *)(Rva001E7270Store *)new Rva001E72B4, (Xfer *)&xferCRC);
		initSubsystem(TheSpecialPowerStore, "TheSpecialPowerStore", new SpecialPowerStore, (Xfer *)&xferCRC);
		initSubsystem(TheDamageFXStore, "TheDamageFXStore", (DamageFXStore *)(Rva00360BB8Store *)new ArmorStore, (Xfer *)&xferCRC);
		initSubsystem(TheArmorStore, "TheArmorStore", (ArmorStore *)new Rva001D9670Store, (Xfer *)&xferCRC);
		initSubsystem(TheBuildAssistant, "TheBuildAssistant", new BuildAssistant, 0);
		initSubsystem(TheCrowdResponseStore, "TheCrowdResponseStore", new Rva0022A809Subsystem, 0);
		initSubsystem((reinterpret_cast<Rva0022A87ESubsystem *&>(TheLivingWorldAutoResolveArmorStore)), "TheLivingWorldAutoResolveArmorStore", (Rva0022A87ESubsystem *)new Rva00427311, (Xfer *)&xferCRC);
		initSubsystem((reinterpret_cast<Rva0022A8F3Subsystem *&>(TheLivingWorldAutoResolveWeaponStore)), "TheLivingWorldAutoResolveWeaponStore", new Rva0022A8F3Subsystem, (Xfer *)&xferCRC);
		initSubsystem((reinterpret_cast<Rva0022A968Subsystem *&>(TheLivingWorldAutoResolveBodyStore)), "TheLivingWorldAutoResolveBodyStore", new Rva0022A968Subsystem, (Xfer *)&xferCRC);
		initSubsystem((reinterpret_cast<Rva0022A9DDSubsystem *&>(TheLivingWorldAutoResolveLeadershipStore)), "TheLivingWorldAutoResolveLeadershipStore", new Rva0022A9DDSubsystem, (Xfer *)&xferCRC);
		initSubsystem((reinterpret_cast<Rva0022AA52Subsystem *&>(TheLivingWorldAutoResolveCombatChainStore)), "TheLivingWorldAutoResolveCombatChainStore", new Rva0022AA52Subsystem, (Xfer *)&xferCRC);
		initSubsystem((reinterpret_cast<Rva0022AAC7Subsystem *&>(TheLivingWorldAutoResolveHandicapStore)), "TheLivingWorldAutoResolveHandicapStore", (Rva0022AAC7Subsystem *)new Rva004134AE, (Xfer *)&xferCRC);
		initSubsystem((reinterpret_cast<Rva0022AB3CSubsystem *&>(TheMissionObjectiveTracker)), "TheMissionObjectiveTracker", (Rva0022AB3CSubsystem *)new Rva00426713, (Xfer *)&xferCRC);
		initSubsystem(TheEmotionSystem, "TheEmotionSystem", new EmotionSystem, 0);
		{
		Rva000309B0 initScope('init');
		initSubsystem((reinterpret_cast<ThingFactory *&>(TheThingFactory)), "TheThingFactory", createThingFactory(), (Xfer *)&xferCRC);
		}
		initSubsystem((reinterpret_cast<Rva0022AC9BSubsystem *&>(TheStancesStore)), "TheStancesStore", (Rva0022AC9BSubsystem *)new Rva00425F10, 0);
		initSubsystem(TheFormationAssistant, "TheFormationAssistant", (Rva0022AD10Subsystem *)new Rva00425CE2, 0);
		initSubsystem((reinterpret_cast<Rva0022AD85Subsystem *&>(TheAiOrdersManager)), "TheAiOrdersManager", (Rva0022AD85Subsystem *)new Rva00355B61, 0);
		initSubsystem((reinterpret_cast<Rva0022ADFASubsystem *&>(TheLightPointSystem)), "TheLightPointSystem", (Rva0022ADFASubsystem *)new Rva00421242, (Xfer *)&xferCRC);
		initSubsystem((reinterpret_cast<ExperienceLevelSystem *&>(TheExperienceLevelSystem)), "TheExperienceLevelSystem", new ExperienceLevelSystem, (Xfer *)&xferCRC);
		initSubsystem(reinterpret_cast<Rva0022AEE4Subsystem *&>(TheDelayedExperienceLevelGrantSystem), "TheDelayedExperienceLevelGrantSystem", (Rva0022AEE4Subsystem *)new DelayedExperienceLevelGrantSystem, 0);
		initSubsystem((reinterpret_cast<Rva0022AF59Subsystem *&>(g_bfmeAptWindowManager)), "TheAptPlayer", createAptPlayer(), 0);
		initSubsystem((reinterpret_cast<Rva0022AFCESubsystem *&>(TheLivingWorldPlayerTemplateStore)), "TheLivingWorldPlayerTemplateStore", (Rva0022AFCESubsystem *)new Rva002E1F42, (Xfer *)&xferCRC);
		initSubsystem((reinterpret_cast<Rva0022B043Subsystem *&>(TheLivingWorldAITemplateStore)), "TheLivingWorldAITemplateStore", (Rva0022B043Subsystem *)new Rva004209CC, (Xfer *)&xferCRC);
		initSubsystem((reinterpret_cast<Rva0022B0B8Subsystem *&>(TheLivingWorldRegionEffectsManagerStore)), "TheLivingWorldRegionEffectsManagerStore", new Rva0022B0B8Subsystem, 0);
		initSubsystem((reinterpret_cast<Rva0022B12DSubsystem *&>(TheLivingWorldManager)), "TheLivingWorldManager", new Rva0022B12DSubsystem, 0);
		initSubsystem((reinterpret_cast<Rva0022B1A2Subsystem *&>(TheLivingWorldLogic)), "TheLivingWorldLogic", (Rva0022B1A2Subsystem *)new LivingWorldLogic, (Xfer *)&xferCRC);
		initSubsystem((reinterpret_cast<GameClient *&>(TheGameClient)), "TheGameClient", createGameClient(), 0);
		initSubsystem((reinterpret_cast<Rva0022B28CSubsystem *&>(TheLinearCampaignManager)), "TheLinearCampaignManager", (Rva0022B28CSubsystem *)new Rva001ED41B, (Xfer *)&xferCRC);
		initSubsystem(TheAI, "TheAI", new AI, (Xfer *)&xferCRC);
		initSubsystem(TheAerialPathfinder, "TheAerialPathfinder", new AerialPathfinder, (Xfer *)&xferCRC);
		initSubsystem(TheSplineService, "TheSplineService", new Rva0022B3F6Subsystem, (Xfer *)&xferCRC);
		initSubsystem(TheAttributeModifierStore, "TheAttributeModifierStore", (Rva0022B46BSubsystem *)new Rva0022CA95, (Xfer *)&xferCRC);
		initSubsystem((reinterpret_cast<Rva0022B4E0Subsystem *&>(TheTaintManager)), "TheTaintManager", (Rva0022B4E0Subsystem *)new BfmeTaintManager, 0);
		initSubsystem(TheScriptEngine, "TheScriptEngine", new ScriptEngine, 0);
		initSubsystem(TheLuaScriptEngine, "TheLuaScriptEngine", new LuaScriptEngine, 0);
		initSubsystem(TheTeamFactory, "TheTeamFactory", new TeamFactory, 0);
		initSubsystem(TheCrateSystem, "TheCrateSystem", new CrateSystem, (Xfer *)&xferCRC);
		initSubsystem(ThePlayerList, "ThePlayerList", new PlayerList, 0);
		initSubsystem(TheGameLogic, "TheGameLogic", createGameLogic(), 0);
		initSubsystem(TheRecorder, "TheRecorder", createRecorder(), 0);
		initSubsystem(TheRadar, "TheRadar", createRadar(), 0);
		initSubsystem(TheVictoryConditions, "TheVictoryConditions", Rva00420353CreateVictoryConditions(), 0);
		initSubsystem(TheMetaMap, "TheMetaMap", new MetaMap, 0);
		initSubsystem(TheHouseColorSystem, "TheHouseColorSystem", new HouseColorSystem, 0);
		initSubsystem(TheMeshInstancingManager, "TheMeshInstancingManager", new Rva0041FB13, 0);
		initSubsystem((reinterpret_cast<Rva0022BADCSubsystem *&>(TheCampaignManager)), "TheLivingWorldCampaignManager", (Rva0022BADCSubsystem *)new Rva003B923B, 0);
		initSubsystem((reinterpret_cast<VictorySystem *&>(TheVictorySystem)), "TheVictorySystem", new VictorySystem, 0);
		initSubsystem((reinterpret_cast<Rva0022BBC6Subsystem *&>(TheTriggerManager)), "TheFireLogicSystem", (Rva0022BBC6Subsystem *)new FireLogicSystem, 0);
		initSubsystem((reinterpret_cast<Rva0022BC3BSubsystem *&>(TheMineshaftPortalNetworkManager)), "TheMineshaftPortalNetworkManager", (Rva0022BC3BSubsystem *)new MineshaftPortalNetworkManager, 0);
		initSubsystem((reinterpret_cast<Rva0022BCB0Subsystem *&>(TheSkirmishAIManager)), "TheSkirmishAIManager", (Rva0022BCB0Subsystem *)new Rva002A8F24, 0);
		initSubsystem(TheArmyDefinitionManager, "TheArmyDefinitionManager", new Rva0022BD25Subsystem, 0);
		initSubsystem(TheBaseTemplateLibrary, "TheBaseTemplateLibrary", new Rva0022BD9ASubsystem, 0);
		initSubsystem((reinterpret_cast<Rva0022BE0FSubsystem *&>(TheThreatFinderManager)), "TheThreatFinderManager", new Rva0022BE0FSubsystem, 0);
		initSubsystem((reinterpret_cast<Rva0022BE84Subsystem *&>(TheAITargetHeuristicLibrary)), "TheAITargetHeuristicLibrary", (Rva0022BE84Subsystem *)new Rva0041E4A3, 0);
		ini.loadFile("CommandMap.ini", INI_LOAD_OVERWRITE, 0);
		initSubsystem(TheActionManager, "TheActionManager", new ActionManager, 0);
		initSubsystem((reinterpret_cast<GameStateMap *&>(TheGameStateMap)), "TheGameStateMap", new GameStateMap, 0);
		initSubsystem(TheGameState, "TheGameState", new GameState, 0);
		initSubsystem(TheGameResultsQueue, "TheGameResultsQueue", Rva0041AA6FCreateGameResults(), 0);
		initSubsystem((reinterpret_cast<Rva0022C0CDSubsystem *&>(TheLivingWorldBuildingTemplateStore)), "TheLivingWorldBuildingTemplateStore", new Rva0022C0CDSubsystem, (Xfer *)&xferCRC);
		initSubsystem((reinterpret_cast<Rva0022C142Subsystem *&>(TheAwardSystemManager)), "TheAwardSystemManager", (Rva0022C142Subsystem *)new AwardSystemManager, 0);
		initSubsystem((reinterpret_cast<Rva0022C1B7Subsystem *&>(TheHeroManager)), "TheCreateAHeroManager", (Rva0022C1B7Subsystem *)new CreateAHeroManager, (Xfer *)&xferCRC);
		initSubsystem(TheScoredKillEvaAnnouncerController, "TheScoredKillEvaAnnouncerController", (Rva0022C22CSubsystem *)new Rva0041497D, (Xfer *)&xferCRC);
		initSubsystem((reinterpret_cast<Rva0022C2A1Subsystem *&>(TheLivingWorldAutoResolveReinforcementScheduleStore)), "TheLivingWorldAutoResolveReinforcementScheduleStore", (Rva0022C2A1Subsystem *)new Rva0022CD78, (Xfer *)&xferCRC);
		initSubsystem(TheLivingWorldAutoResolveResourceBonusScheduleStore, "TheLivingWorldAutoResolveResourceBonusScheduleStore", (Rva0022C316Subsystem *)new Rva0022DE6B, (Xfer *)&xferCRC);
		initSubsystem(TheLivingWorldAutoResolveSciencePurchasePointBonusScheduleStore, "TheLivingWorldAutoResolveSciencePurchasePointBonusScheduleStore", new Rva0022C38BSubsystem, (Xfer *)&xferCRC);

		((Gen009D6DD0 *)&xferCRC)->bfmeClose();
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
			((StringBase<char> &)(fname)).toLower();
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
						if (!(*(GameInfo * *)&TheSkirmishGameInfo))
							(*(GameInfo * *)&TheSkirmishGameInfo) = new SkirmishGameInfo;
						(*(GameInfo * *)&TheSkirmishGameInfo)->init();
						GameSlot *first = (*(GameInfo * *)&TheSkirmishGameInfo)->getSlot(0);
						(*(GameInfo * *)&TheSkirmishGameInfo)->m_38 = first->m_38;
						(*(GameInfo * *)&TheSkirmishGameInfo)->m_3C = first->m_3C;
						(*(GameInfo * *)&TheSkirmishGameInfo)->reset();
						(*(GameInfo * *)&TheSkirmishGameInfo)->enterGame();
						(*(GameInfo * *)&TheSkirmishGameInfo)->setSeed(time(0));
						(*(GameInfo * *)&TheSkirmishGameInfo)->setMap(TheGlobalData->m_initialFile);
						(*(GameInfo * *)&TheSkirmishGameInfo)->setMapCRC(md->m_CRC);
						(*(GameInfo * *)&TheSkirmishGameInfo)->setMapSize(md->m_filesize);
						GameSlot slot;
						slot.m_name = UnicodeString(L"Test");
						GameSlotConnectInfo info;
						info.m_a = 0;
						info.m_b = 0;
						slot.setState(SLOT_PLAYER, UnicodeString(L"Test"), &info);
						(*(GameInfo * *)&TheSkirmishGameInfo)->setSlot(0, slot);
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
			((StringBase<char> &)(lowerName)).toLower();
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
	catch (INIException &iNIException)
	{
		const char *failure = iNIException.mFailureMessage;
		if (failure)
		{
			_bfme_debugRecordCallsite(1);
			theDebug->crashBegin();
			put(put(theDebug->stream(0, 0, 0), "\n\n"), iNIException.mFailureMessage)->finish(1);
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
	m_38 = BfmeClientFramesPerSecond / BfmeLogicFramesPerSecond;
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

// Native global DFDC8C is registered as TheLinearCampaignManager by22F3A1.
// Existing helper facades carry their historical names; those names do not
// establish a terrain identity for this campaign-manager data access.

unsigned int ComputeCRC(const unsigned char *buf, unsigned int len, unsigned int crc);
void Rva00600777Set(char *dir);

struct CommandLineParam
{
	const char *name;
	int (__cdecl *func)(char **args, int remainingArgc);
};
int parseNoShellMap(char *args[], int remainingArgc);
int parseMod(char *args[], int remainingArgc);
int parseNoAudio(char *args[], int remainingArgc);
int parseXRes(char *args[], int remainingArgc);
int parseYRes(char *args[], int remainingArgc);
int parseWin(char *args[], int remainingArgc);
int parseScriptDebug2(char *args[], int remainingArgc);
int parseScriptDebugLite(char *args[], int remainingArgc);
int parseFullVersion(char *args[], int remainingArgc);
int parsePreferLocalFiles(char *args[], int remainingArgc);
int parseWatchdog(char *args[], int remainingArgc);
int parseNoWatchdog(char *args[], int remainingArgc);
int parseRif(char *args[], int remainingArgc);
int parseFile(char *args[], int remainingArgc);
int parseResumeGame(char *args[], int remainingArgc);
int parseRandomSeed(char *args[], int remainingArgc);

extern const CommandLineParam g_commandLineParams[16] =
{
	{ "-noshellmap", parseNoShellMap },
	{ "-mod", parseMod },
	{ "-noaudio", parseNoAudio },
	{ "-xres", parseXRes },
	{ "-yres", parseYRes },
	{ "-win", parseWin },
	{ "-scriptDebug2", parseScriptDebug2 },
	{ "-scriptDebugLite", parseScriptDebugLite },
	{ "-fullVersion", parseFullVersion },
	{ "-preferLocalFiles", parsePreferLocalFiles },
	{ "-Watchdog", parseWatchdog },
	{ "-noWatchdog", parseNoWatchdog },
	{ "-rif", parseRif },
	{ "-file", parseFile },
	{ "-resumeGame", parseResumeGame },
	{ "-randomSeed", parseRandomSeed }
};
extern unsigned int BFME2CommandFlags;

class ArchiveFile;
class LocalFileSystem
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual int loadBigFile(const char *path, int mode);
};
extern LocalFileSystem *TheLocalFileSystem;

static __declspec(noinline) void rva003B9D78(unsigned int count, int argc, char **argv, const CommandLineParam *table)
{
	int arg = 1;
	unsigned int param;
	bool found;

	while (arg < argc)
	{
		found = false;
		for (param = 0; !found && param < count; ++param)
		{
			int len = strlen(table[param].name);
			int len2 = strlen(argv[arg]);
			if (argv[arg][0] == (char)0x96)
				argv[arg][0] = '-';
			if (len2 == len && !_strnicmp(argv[arg], table[param].name, len))
			{
				arg += table[param].func(argv + arg, argc - arg);
				found = true;
			}
		}
		if (!found)
			arg++;
	}
}

void parseCommandLine(Int argc, char *argv[])
{
	rva003B9D78(16, argc, argv, g_commandLineParams);
	AsciiString &modBig = *reinterpret_cast<AsciiString *>(reinterpret_cast<char *>(TheWritableGlobalData) + 0xd3c);
	if (!modBig.isEmpty())
	{
		TheLocalFileSystem->loadBigFile(modBig.str(), 1);
	}
	AsciiString &modDir = *reinterpret_cast<AsciiString *>(reinterpret_cast<char *>(TheWritableGlobalData) + 0xd38);
	if (!modDir.isEmpty())
	{
		Rva00600777Set(const_cast<char *>(modDir.str()));
	}
	unsigned int crc = ComputeCRC(reinterpret_cast<const unsigned char *>(&BFME2CommandFlags), 0x18, 0);
	*reinterpret_cast<unsigned int *>(reinterpret_cast<char *>(TheWritableGlobalData) + 0xb38) = crc;
}
