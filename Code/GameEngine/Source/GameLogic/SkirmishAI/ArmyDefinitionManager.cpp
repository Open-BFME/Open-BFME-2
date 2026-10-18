// cl: /O1 /G7 /arch:SSE /Ob2 /MD /EHsc /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
// STLport 4.5.3 supplies the emitted hashtable and hash_map bodies.
// Native 41F871..41F8F4 and WB 1333640 identify the static INI parser.
// The native constructor 41F56F and destructor 41F760 establish the 224-byte
// ArmyDefinition and its leading AsciiString. The constructor performs only
// nonthrowing empty-header and scalar initialization; the parser has no EH guard.
// The caller stores NameKeyGenerator's NameKeyType and the allocated pointer in
// the manager's map at +0xC. Use the real typed STLport map, not another map's
// declarations. The two find wrappers inline as in retail; their _M_find body
// must independently prove the existing 47-byte fold before it is admitted.
// Keep the existing manager-global spelling used by GameEngineInit.cpp and cast
// its opaque subsystem pointer to this independently evidenced registry view.
// The callee at 41F369 has a proven thiscall/no-stack-argument ABI and normalizes
// the entry weights at +4/+8/+C. Its original method name remains unknown.
// The field-table name describes its ownership; its original EA name is unknown.
#include <hash_map>
#include "ascii_string.h"

class INI;
struct FieldParse {
    const char *name;
    void (__cdecl *parse)(INI *, void *, void *, const void *);
    const void *data;
    int offset;
};
class INI {
public:
    void initFromINI(void *, const FieldParse *);
    static void parseAsciiString(INI *, void *, void *, const void *);
    static void parseAsciiStringVector(INI *, void *, void *, const void *);
    static void parsePercentToReal(INI *, void *, void *, const void *);
    static void parseReal(INI *, void *, void *, const void *);
    static void parseInt(INI *, void *, void *, const void *);
    static void Rva0041F524_ParseArmyMember(INI *, void *, void *, const void *);
    static void Rva002C5E8F_ParseAITargetList(INI *, void *, void *, const void *);
    static void Rva004E8EFF_ParseDisabledSlots(INI *, void *, void *, const void *);
};
void Rva0041F316Parse(INI *, void *, void *, const void *);
void Rva0041F32DParse(INI *, void *, void *, const void *);
enum NameKeyType { NAMEKEY_INVALID=0, NAMEKEY_MAX=1<<23, FORCE_NAMEKEYTYPE_LONG=0x7fffffff };
namespace rts { template<class T> struct hash {
    size_t operator()(const T &key) const { return (size_t)key; }
}; }
class NameKeyGenerator { public: NameKeyType nameToKey(const AsciiString &); };
extern NameKeyGenerator *TheNameKeyGenerator;
class ArmyDefinition {
public:
    ArmyDefinition() throw();
    ~ArmyDefinition();
    void rva0041F369();
    AsciiString name;
    char opaque04[0xDC];
};
typedef _STL::hash_map<NameKeyType, ArmyDefinition *, rts::hash<NameKeyType>,
    _STL::equal_to<NameKeyType> > ArmyDefinitionMap;
typedef _STL::pair<const NameKeyType, ArmyDefinition *> ArmyDefinitionPair;
typedef _STL::hashtable<ArmyDefinitionPair, NameKeyType, rts::hash<NameKeyType>,
    _STL::_Select1st<ArmyDefinitionPair>, _STL::equal_to<NameKeyType>,
    _STL::allocator<ArmyDefinitionPair> > ArmyDefinitionTable;
namespace _STL {
// ?ArmyDefinitionTable::find absent-from-retail
// This header wrapper is fully inlined; there is no separate retail body.
template <> template <>
__forceinline ArmyDefinitionTable::const_iterator
ArmyDefinitionTable::find<NameKeyType>(const NameKeyType &key) const
{
    return const_iterator(_M_find(key), this);
}
// ?ArmyDefinitionMap::find absent-from-retail
// This header wrapper is fully inlined; there is no separate retail body.
template <>
__forceinline ArmyDefinitionMap::const_iterator
ArmyDefinitionMap::find(const NameKeyType &key) const
{
    return _M_ht.find(key);
}
}
struct ArmyDefinitionRegistryView {
    char opaque00[0xC];
    ArmyDefinitionMap definitions;
};
class Rva0022BD25Subsystem;
extern Rva0022BD25Subsystem *TheArmyDefinitionManager;
extern const FieldParse TheArmyDefinitionFields[];
class ArmyDefinitionManager {
public:
    static void parseArmyDefinition(INI *);
};

// Native C3B5E8..C3B8C8: exactly 46 FieldParse records; the next object is a vtable.
extern const FieldParse TheArmyDefinitionFields[46] = {
    {"Side", INI::parseAsciiString, 0, 0x0},
    {"MustUseCommandPointPercentage_Phase1", INI::parsePercentToReal, 0, 0x10},
    {"MustUseCommandPointPercentage_Phase2", INI::parsePercentToReal, 0, 0x14},
    {"MustUseCommandPointPercentage_Phase3", INI::parsePercentToReal, 0, 0x18},
    {"DefaultUnitPriority", INI::parseReal, 0, 0x1C},
    {"FortressRebuildPriority", INI::parseReal, 0, 0x20},
    {"ArmyMemberDefinition", INI::Rva0041F524_ParseArmyMember, 0, 0x0},
    {"AIEconomyAssigment", Rva0041F316Parse, 0, 0x0},
    {"AIWallNodeAssignment", Rva0041F32DParse, 0, 0x0},
    {"MaxThreatForOpportunityTargets", INI::parseInt, 0, 0x2C},
    {"ValueToSetForMaxOnDefenseTeam", INI::parseInt, 0, 0x30},
    {"CombatChainSearchDepthForTeamRecruits_AttackTeams", INI::parseInt, 0, 0x34},
    {"CombatChainSearchDepthForTeamRecruits_DefenseTeams", INI::parseInt, 0, 0x38},
    {"CombatChainSearchDepthForTeamRecruits_ExploreTeams", INI::parseInt, 0, 0x3C},
    {"EconomyBuilderMinFarmsOwned", INI::parseInt, 0, 0x40},
    {"EconomyBuilderMinMoney", INI::parseInt, 0, 0x44},
    {"EconomyBuilderPerFarmValue", INI::parseInt, 0, 0x48},
    {"EconomyBuilderPerSecPriorityIncreaseBase", INI::parseReal, 0, 0x4C},
    {"EconomyBuilderMinTimeBetweenFarms_Rush", INI::parseReal, 0, 0x50},
    {"TacticalAITargets", INI::Rva002C5E8F_ParseAITargetList, 0, 0x54},
    {"MaxTeamsPerTarget", INI::Rva004E8EFF_ParseDisabledSlots, 0, 0x60},
    {"SecondsTillTargetsCanExpire", INI::parseReal, 0, 0x6C},
    {"ChanceForTargetToExpire", INI::parsePercentToReal, 0, 0x70},
    {"MaxBuildingsToBeDefensiveTarget_Small", INI::parseInt, 0, 0x74},
    {"MaxBuildingsToBeDefensiveTarget_Med", INI::parseInt, 0, 0x78},
    {"ChanceToUseAllUnitsForDefenseTarget_Small", INI::parsePercentToReal, 0, 0x7C},
    {"ChanceToUseAllUnitsForDefenseTarget_Med", INI::parsePercentToReal, 0, 0x80},
    {"ChanceToUseAllUnitsForDefenseTarget_Large", INI::parsePercentToReal, 0, 0x84},
    {"StructureRebuildPriorityModifier", INI::parsePercentToReal, 0, 0x88},
    {"HeroBuildOrder", INI::parseAsciiStringVector, 0, 0x8C},
    {"OffensiveBuildings", INI::parseAsciiStringVector, 0, 0x98},
    {"PhaseDuration_Rush", INI::parseReal, 0, 0xA4},
    {"PhaseDuration_MidGame", INI::parseReal, 0, 0xA8},
    {"PercentToSave_Rush", INI::parsePercentToReal, 0, 0xAC},
    {"PercentToSave_MidGame", INI::parsePercentToReal, 0, 0xB0},
    {"PercentToSave_EndGame", INI::parsePercentToReal, 0, 0xB4},
    {"LowUnitPriorityModifier_Rush", INI::parseReal, 0, 0xB8},
    {"LowUnitPriorityModifier_MidGame", INI::parseReal, 0, 0xBC},
    {"LowUnitPriorityModifier_EndGame", INI::parseReal, 0, 0xC0},
    {"ChanceForUnitsToUpgrade", INI::parsePercentToReal, 0, 0xC4},
    {"UpgradeSciencePriorityNormalLow", INI::parseReal, 0, 0xC8},
    {"UpgradeSciencePriorityNormalHigh", INI::parseReal, 0, 0xCC},
    {"UpgradeSciencePriorityImportantLow", INI::parseReal, 0, 0xD0},
    {"UpgradeSciencePriorityImportantHigh", INI::parseReal, 0, 0xD4},
    {"UnitUpgradePriorityLow", INI::parseReal, 0, 0xD8},
    {"UnitUpgradePriorityHigh", INI::parseReal, 0, 0xDC},
};
Rva0022BD25Subsystem *TheArmyDefinitionManager = 0;

void ArmyDefinitionManager::parseArmyDefinition(INI *ini)
{
    ArmyDefinition *definition = new ArmyDefinition;
    ini->initFromINI(definition, TheArmyDefinitionFields);
    NameKeyType key = TheNameKeyGenerator->nameToKey(definition->name);
    ArmyDefinitionMap &definitions =
        reinterpret_cast<ArmyDefinitionRegistryView *>(TheArmyDefinitionManager)->definitions;
    const ArmyDefinitionMap &lookup = definitions;
    if (lookup.find(key) == lookup.end()) {
        definitions[key] = definition;
        definition->rva0041F369();
    } else {
        if (definition) {
            definition->ArmyDefinition::~ArmyDefinition();
            ::operator delete(definition);
        }
    }
}
