// cl: /DNDEBUG /MD
//
// INI block-parse registration initializers. BFME replaced Zero Hour's
// theTypeTable array with 12-byte BlockParse nodes { next, token, parse } that
// link themselves into theBlockParseList (VA 0x00DDF578; the matched
// BlockParse ctor 0x0004147D and findBlockParse walk it). The node's token and
// parse pointer are constant-initialized in .data, so each registration's
// dynamic initializer is only the link: node.next = head; head = &node
// (21 bytes). Retail holds 130 such initializers from 0x007ABBF6; each node
// name below is its token, read from the string its +4 slot points at. Each is
// really the .text$yc initializer of a file-scope `BlockParse node(token,
// parse);` with an inline constructor, so it belongs to the unit that defines
// the node (LINK-236). Attributed nodes move to their unit with the registering
// constructor and are rowed there as `_$E<n>`; the rest keep an honest
// address name here until their unit is clear.

typedef void (*INIBlockParse)( class INI *ini );

struct BlockParse
{
	BlockParse *next;
	const char *token;
	INIBlockParse parse;
};

extern BlockParse *theBlockParseList;
// Owned here: the registration initializers below link their nodes into it;
// retail .data starts it at 0.
BlockParse *theBlockParseList = 0;

// Callback declarations retain the existing matched names and cdecl ABI.
// These static-only class declarations assert no instance layout.
class INI;
void Rva000B3FD0AptFreeSound();
void parseMusicTrackDefinition(INI *);
void parseAudioEventDefinition(INI *);
void parseDialogDefinition(INI *);
void parseAmbientStreamDefinition(INI *);
void parseStreamedSoundDefinition(INI *);
void parseAerialPathfindNoFlyZoneDefinition(INI *);
void Rva00202BB2Parse(INI *);
void parseLivingWorldMapInfoDefinition(INI *);
void Rva0021376BParse(INI *);
void parseCloudEffectDefinition(INI *);
void parsePlayerAITypeDefinition(INI *);
void parseInGameNotificationBoxDefinition(INI *);
void parseSkirmishAIDataDefinition(INI *);
void parseAIDozerAssignmentDefinition(INI *);
void parseLivingWorldBuildingDefinition(INI *);
void parseLivingWorldPlayerTemplateDefinition(INI *);
void parseFireDefinition(INI *);
void parseLivingWorldRegionEffectsDefinition(INI *);
void parseLivingWorldArmyIconDefinition(INI *);
void Rva003FD7CEParse(INI *);
void parseLivingWorldBuildingIconDefinition(INI *);
void parseLivingWorldBuildPlotIconDefinition(INI *);
void parseLivingWorldPlayerArmyDefinition(INI *);
void parseAutoResolveHandicapLevelDefinition(INI *);
void parseAutoResolveReinforcementScheduleDefinition(INI *);
void parseCrowdResponseDefinition(INI *);
void parseHouseColorDefinition(INI *);
void parseAutoResolveLeadershipDefinition(INI *);
void parseAutoResolveBodyDefinition(INI *);
void parseAutoResolveCombatChainDefinition(INI *);
void parseAutoResolveWeaponDefinition(INI *);
void parseAIBaseDefinition(INI *);
void parseMeshNameMatchesDefinition(INI *);
void parseLivingWorldAITemplateDefinition(INI *);
void iniParseWaterTexturesDefinition(INI *);
void parseAnimationSoundClientBehaviorGlobalSetting(INI *);
void parseAudioLowMHz(INI *);
void parseDebugCommandMap(INI *);
void parseFireEffect(INI *);
void parseGlowEffect(INI *);
void parseReallyLowMHz(INI *);
void parseRingEffect(INI *);
void parseShadowMapBlock(INI *);
void parseSubsystemLegendDefinition(INI *);
void parseCloudBreakEffectDefinition(INI *);
void parseFormationAssistantDefinition(INI *);
namespace StrategicHUD { void ParseSettings(INI *); }
class ArmyDefinitionManager
{
public:
	static void parseArmyDefinition(INI *);
};
class AudioEventInfo
{
public:
	static void parseMultisoundDefinition(INI *);
};
#include "../../../Include/GameClient/ControlBar.h"
class CrateSystem
{
public:
	static void parseCrateTemplateDefinition(INI *);
};
class DamageFXStore
{
public:
	static void parseDamageFXDefinition(INI *);
};
class EmotionNuggetTemplate
{
public:
	static void friend_parseEmotionNugget(INI *);
};
#include "../../../Include/GameClient/Eva.h"
#include "../../../Include/Common/GlobalData.h"
#include "../../../Include/Common/INI/INI.h"
class LargeGroupAudio
{
public:
	static void parseLargeGroupAudioMapDefinition(INI *);
	static void parseLargeGroupAudioUnusedKnownKeysDefinition(INI *);
};
class LightPointSystem
{
public:
	static void friend_parseLightPointLevelDefinition(INI *);
};
class LivingWorldAutoResolveArmorStore
{
public:
	static void parseArmorDefinition(INI *);
};
class LivingWorldAutoResolveResourceBonusScheduleStore
{
public:
	static void parseLivingWorldAutoResolveResourceBonusBlock(INI *);
};
class LivingWorldAutoResolveSciencePurchasePointBonusScheduleStore
{
public:
	static void parseLivingWorldAutoResolveSciencePurchasePointBonusBlock(INI *);
};
class LivingWorldCampaign
{
public:
	static void ParseLivingWorldCampaignBlock(INI *);
};
class LivingWorldSound
{
public:
	static void ParseSound(INI *);
};
class MetaMap
{
public:
	static void parseMetaMap(INI *);
};
class Rva00425F10
{
public:
	static void parseStanceTemplateDefinition(INI *);
};
class SpecialPowerStore
{
public:
	static void parseSpecialPowerDefinition(INI *);
};
#include "../../../Include/Common/Upgrade.h"
#include "../../../Include/GameLogic/WeaponStore.h"
// ControlBarResizer points to the shared one-byte RET at 0x000B3FD0.
// Reuse an existing cdecl owner without assigning a recovered callback name.
// The Apt tooltip node keeps its existing 44-byte owner in Rva00224A3F.cpp.

BlockParse theAudioSettingsBlockParse = { 0, "AudioSettings", INI::parseAudioSettingsDefinition };	// VA 0x00DB3A08 "AudioSettings", parse 0x0004171A
BlockParse theShadowMapBlockParse = { 0, "ShadowMap", parseShadowMapBlock };	// VA 0x00DB4488 "ShadowMap", parse 0x0007BE1E
BlockParse theLoadSubsystemBlockParse = { 0, "LoadSubsystem", parseSubsystemLegendDefinition };	// VA 0x00DB7034 "LoadSubsystem", parse 0x001B4E07
BlockParse theBridgeBlockParse = { 0, "Bridge", INI::parseTerrainBridgeDefinition };	// VA 0x00DB8B8C "Bridge", parse 0x001DAEB8
BlockParse theCommandSetBlockParse = { 0, "CommandSet", ControlBar::parseCommandSetDefinition };	// VA 0x00DB8C50 "CommandSet", parse 0x0031EC03
BlockParse theControlBarSchemeBlockParse = { 0, "ControlBarScheme", INI::parseControlBarSchemeDefinition };	// VA 0x00DB8C80 "ControlBarScheme", parse 0x001DB68C
BlockParse theControlBarResizerBlockParse = { 0, "ControlBarResizer", (INIBlockParse)Rva000B3FD0AptFreeSound };	// VA 0x00DB8CB0 "ControlBarResizer", parse 0x000B3FD0
BlockParse theCrateDataBlockParse = { 0, "CrateData", CrateSystem::parseCrateTemplateDefinition };	// VA 0x00DB8CBC "CrateData", parse 0x0035CFEA
BlockParse theWindowTransitionBlockParse = { 0, "WindowTransition", INI::parseWindowTransitions };	// VA 0x00DB8CEC "WindowTransition", parse 0x001DC66F
BlockParse theDamageFXBlockParse = { 0, "DamageFX", DamageFXStore::parseDamageFXDefinition };	// VA 0x00DB8D1C "DamageFX", parse 0x00360B0F
BlockParse theGameDataBlockParse = { 0, "GameData", GlobalData::parseGameDataDefinition };	// VA 0x00DB8DF4 "GameData", parse 0x00237AB1
BlockParse theFXParticleSystemBlockParse = { 0, "FXParticleSystem", INI::parseParticleSystemDefinition };	// VA 0x00DB938C "FXParticleSystem", parse 0x001FD0B4
BlockParse theSpecialPowerBlockParse = { 0, "SpecialPower", SpecialPowerStore::parseSpecialPowerDefinition };	// VA 0x00DB94A4 "SpecialPower", parse 0x003B15D6
BlockParse theShellMenuSchemeBlockParse = { 0, "ShellMenuScheme", INI::parseShellMenuSchemeDefinition };	// VA 0x00DB94D4 "ShellMenuScheme", parse 0x00200984
BlockParse theUpgradeBlockParse = { 0, "Upgrade", UpgradeCenter::parseUpgradeDefinition };	// VA 0x00DB94F8 "Upgrade", parse 0x0026FA05
BlockParse theAerialPathfindNoFlyZoneBlockParse = { 0, "AerialPathfindNoFlyZone", parseAerialPathfindNoFlyZoneDefinition };	// VA 0x00DB9558 "AerialPathfindNoFlyZone", parse 0x00200FE3
BlockParse theWeatherBlockParse = { 0, "Weather", INI::parseWeatherDefinition };	// VA 0x00DB9588 "Weather", parse 0x0020187A
BlockParse theWeaponBlockParse = { 0, "Weapon", WeaponStore::parseWeaponTemplateDefinition };	// VA 0x00DB95B8 "Weapon", parse 0x002CE102
BlockParse theHeaderTemplateBlockParse = { 0, "HeaderTemplate", INI::parseHeaderTemplateDefinition };	// VA 0x00DB95C4 "HeaderTemplate", parse 0x00201CAF
BlockParse theGlowEffectBlockParse = { 0, "GlowEffect", parseGlowEffect };	// VA 0x00DB9858 "GlowEffect", parse 0x00309FB3
BlockParse theRingEffectBlockParse = { 0, "RingEffect", parseRingEffect };	// VA 0x00DB9864 "RingEffect", parse 0x00309FFD
BlockParse theFireEffectBlockParse = { 0, "FireEffect", parseFireEffect };	// VA 0x00DB9870 "FireEffect", parse 0x0030A040
BlockParse theLivingWorldObjectBlockParse = { 0, "LivingWorldObject", Rva0021376BParse };	// VA 0x00DB9A20 "LivingWorldObject", parse 0x0021376B
BlockParse theLivingWorldMapInfoBlockParse = { 0, "LivingWorldMapInfo", parseLivingWorldMapInfoDefinition };	// VA 0x00DB9A2C "LivingWorldMapInfo", parse 0x00210F64
BlockParse theCloudEffectBlockParse = { 0, "CloudEffect", parseCloudEffectDefinition };	// VA 0x00DB9B68 "CloudEffect", parse 0x0021526C
BlockParse thePlayerAITypeBlockParse = { 0, "PlayerAIType", parsePlayerAITypeDefinition };	// VA 0x00DB9B74 "PlayerAIType", parse 0x00215C38
BlockParse theStrategicHUDBlockParse = { 0, "StrategicHUD", StrategicHUD::ParseSettings };	// VA 0x00DBA190 "StrategicHUD", parse 0x0022157B
BlockParse theInGameNotificationBoxBlockParse = { 0, "InGameNotificationBox", parseInGameNotificationBoxDefinition };	// VA 0x00DBA19C "InGameNotificationBox", parse 0x0022232E
extern BlockParse theAptButtonTooltipMapBlockParse;	// VA 0x00DBA1CC "AptButtonTooltipMap", parse 0x00224DFF
BlockParse theAIDozerAssignmentBlockParse = { 0, "AIDozerAssignment", parseAIDozerAssignmentDefinition };	// VA 0x00DBBC1C "AIDozerAssignment", parse 0x002A92F2
BlockParse theSkirmishAIDataBlockParse = { 0, "SkirmishAIData", parseSkirmishAIDataDefinition };	// VA 0x00DBBC28 "SkirmishAIData", parse 0x002A8A31
BlockParse theLivingWorldBuildingBlockParse = { 0, "LivingWorldBuilding", parseLivingWorldBuildingDefinition };	// VA 0x00DBD078 "LivingWorldBuilding", parse 0x002E048C
BlockParse theLivingWorldPlayerTemplateBlockParse = { 0, "LivingWorldPlayerTemplate", parseLivingWorldPlayerTemplateDefinition };	// VA 0x00DBD0A8 "LivingWorldPlayerTemplate", parse 0x002E2386
BlockParse theFireBlockParse = { 0, "Fire", parseFireDefinition };	// VA 0x00DBD9AC "Fire", parse 0x0030AFFB
BlockParse theCloudBreakEffectBlockParse = { 0, "CloudBreakEffect", parseCloudBreakEffectDefinition };	// VA 0x00DBE4D0 "CloudBreakEffect", parse 0x00318ABB
BlockParse theLivingWorldRegionEffectsBlockParse = { 0, "LivingWorldRegionEffects", parseLivingWorldRegionEffectsDefinition };	// VA 0x00DC14B8 "LivingWorldRegionEffects", parse 0x003EF467
BlockParse theLivingWorldArmyIconBlockParse = { 0, "LivingWorldArmyIcon", parseLivingWorldArmyIconDefinition };	// VA 0x00DC177C "LivingWorldArmyIcon", parse 0x003F9EDF
BlockParse theLivingWorldSoundBlockParse = { 0, "LivingWorldSound", LivingWorldSound::ParseSound };	// VA 0x00DC17EC "LivingWorldSound", parse 0x003FB07D
BlockParse theLivingWorldAnimObjectBlockParse = { 0, "LivingWorldAnimObject", Rva003FD7CEParse };	// VA 0x00DC18EC "LivingWorldAnimObject", parse 0x003FD7CE
BlockParse theLivingWorldBuildingIconBlockParse = { 0, "LivingWorldBuildingIcon", parseLivingWorldBuildingIconDefinition };	// VA 0x00DC1AB4 "LivingWorldBuildingIcon", parse 0x00402B19
BlockParse theLivingWorldBuildPlotIconBlockParse = { 0, "LivingWorldBuildPlotIcon", parseLivingWorldBuildPlotIconDefinition };	// VA 0x00DC1B04 "LivingWorldBuildPlotIcon", parse 0x00402E30
BlockParse theLivingWorldPlayerArmyBlockParse = { 0, "LivingWorldPlayerArmy", parseLivingWorldPlayerArmyDefinition };	// VA 0x00DC1F68 "LivingWorldPlayerArmy", parse 0x0040F0F0
BlockParse theAutoResolveHandicapLevelBlockParse = { 0, "AutoResolveHandicapLevel", parseAutoResolveHandicapLevelDefinition };	// VA 0x00DC2044 "AutoResolveHandicapLevel", parse 0x0041355D
BlockParse theLivingWorldAutoResolveSciencePurchasePointBonusBlockParse = { 0, "LivingWorldAutoResolveSciencePurchasePointBonus", LivingWorldAutoResolveSciencePurchasePointBonusScheduleStore::parseLivingWorldAutoResolveSciencePurchasePointBonusBlock };	// VA 0x00DC2050 "LivingWorldAutoResolveSciencePurchasePointBonus", parse 0x00413B4D
BlockParse theAutoResolveReinforcementScheduleBlockParse = { 0, "AutoResolveReinforcementSchedule", parseAutoResolveReinforcementScheduleDefinition };	// VA 0x00DC205C "AutoResolveReinforcementSchedule", parse 0x00413D58
BlockParse theLivingWorldAutoResolveResourceBonusBlockParse = { 0, "LivingWorldAutoResolveResourceBonus", LivingWorldAutoResolveResourceBonusScheduleStore::parseLivingWorldAutoResolveResourceBonusBlock };	// VA 0x00DC2068 "LivingWorldAutoResolveResourceBonus", parse 0x0041428F
BlockParse theCrowdResponseBlockParse = { 0, "CrowdResponse", parseCrowdResponseDefinition };	// VA 0x00DC20E0 "CrowdResponse", parse 0x00415D33
BlockParse theHouseColorBlockParse = { 0, "HouseColor", parseHouseColorDefinition };	// VA 0x00DC822C "HouseColor", parse 0x00417A94
BlockParse theAutoResolveLeadershipBlockParse = { 0, "AutoResolveLeadership", parseAutoResolveLeadershipDefinition };	// VA 0x00DC8238 "AutoResolveLeadership", parse 0x004183AC
BlockParse theAutoResolveBodyBlockParse = { 0, "AutoResolveBody", parseAutoResolveBodyDefinition };	// VA 0x00DC8244 "AutoResolveBody", parse 0x00418AC6
BlockParse theAutoResolveCombatChainBlockParse = { 0, "AutoResolveCombatChain", parseAutoResolveCombatChainDefinition };	// VA 0x00DC8250 "AutoResolveCombatChain", parse 0x004193E5
BlockParse theAutoResolveWeaponBlockParse = { 0, "AutoResolveWeapon", parseAutoResolveWeaponDefinition };	// VA 0x00DC825C "AutoResolveWeapon", parse 0x0041999F
BlockParse theAIBaseBlockParse = { 0, "AIBase", parseAIBaseDefinition };	// VA 0x00DC83F4 "AIBase", parse 0x0041EC73
BlockParse theArmyDefinitionBlockParse = { 0, "ArmyDefinition", ArmyDefinitionManager::parseArmyDefinition };	// VA 0x00DC8424 "ArmyDefinition", parse 0x0041F871
BlockParse theMeshNameMatchesBlockParse = { 0, "MeshNameMatches", parseMeshNameMatchesDefinition };	// VA 0x00DC8430 "MeshNameMatches", parse 0x0041FD3D
BlockParse theLivingWorldAITemplateBlockParse = { 0, "LivingWorldAITemplate", parseLivingWorldAITemplateDefinition };	// VA 0x00DC8478 "LivingWorldAITemplate", parse 0x00420A29
BlockParse theLightPointLevelBlockParse = { 0, "LightPointLevel", LightPointSystem::friend_parseLightPointLevelDefinition };	// VA 0x00DC84C4 "LightPointLevel", parse 0x00421572
BlockParse theFormationAssistantBlockParse = { 0, "FormationAssistant", parseFormationAssistantDefinition };	// VA 0x00DC84F8 "FormationAssistant", parse 0x00425B90
BlockParse theStanceTemplateBlockParse = { 0, "StanceTemplate", Rva00425F10::parseStanceTemplateDefinition };	// VA 0x00DC8540 "StanceTemplate", parse 0x00426203
BlockParse theEmotionNuggetBlockParse = { 0, "EmotionNugget", EmotionNuggetTemplate::friend_parseEmotionNugget };	// VA 0x00DC8570 "EmotionNugget", parse 0x004DCAE4
BlockParse theAutoResolveArmorBlockParse = { 0, "AutoResolveArmor", LivingWorldAutoResolveArmorStore::parseArmorDefinition };	// VA 0x00DC85E8 "AutoResolveArmor", parse 0x00427392

struct Rva007ABBF6BlockParseInits
{
	static void rva007ABBF6();
	static void rva007ABFE3();
	static void rva007ACFBB();
	static void rva007AD0A2();
	static void rva007AD120();
	static void rva007AD135();
	static void rva007AD14A();
	static void rva007AD15F();
	static void rva007AD174();
	static void rva007AD189();
	static void rva007AD270();
	static void rva007AD521();
	static void rva007AD60C();
	static void rva007AD621();
	static void rva007AD660();
	static void rva007AD69F();
	static void rva007AD6B4();
	static void rva007AD6C9();
	static void rva007AD6DE();
	static void rva007AD85A();
	static void rva007AD86F();
	static void rva007AD884();
	static void rva007AD939();
	static void rva007AD94E();
	static void rva007AD9E8();
	static void rva007AD9FD();
	static void rva007ADB4C();
	static void rva007ADB6D();
	static void rva007ADB92();
	static void rva007AE15A();
	static void rva007AE16F();
	static void rva007AE489();
	static void rva007AE4AE();
	static void rva007AE7CA();
	static void rva007AE963();
	static void rva007AFC11();
	static void rva007AFC56();
	static void rva007AFCB4();
	static void rva007AFCE3();
	static void rva007AFD4C();
	static void rva007AFD61();
	static void rva007AFE97();
	static void rva007AFFBC();
	static void rva007AFFD1();
	static void rva007AFFE6();
	static void rva007AFFFB();
	static void rva007B003F();
	static void rva007B0088();
	static void rva007B009D();
	static void rva007B00B2();
	static void rva007B00C7();
	static void rva007B00DC();
	static void rva007B01D3();
	static void rva007B01E8();
	static void rva007B01FD();
	static void rva007B022C();
	static void rva007B026B();
	static void rva007B02F6();
	static void rva007B033F();
	static void rva007B0354();
	static void rva007B03B2();
};

#define BLOCK_PARSE_INIT(init, node) \
	void Rva007ABBF6BlockParseInits::init() \
	{ \
		node.next = theBlockParseList; \
		theBlockParseList = &node; \
	}

// ?rva007ABBF6@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007ABBF6 (21B): "AudioSettings"
BLOCK_PARSE_INIT( rva007ABBF6, theAudioSettingsBlockParse )
// ?rva007ABFE3@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007ABFE3 (21B): "ShadowMap"
BLOCK_PARSE_INIT( rva007ABFE3, theShadowMapBlockParse )
// ?rva007ACFBB@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007ACFBB (21B): "LoadSubsystem"
BLOCK_PARSE_INIT( rva007ACFBB, theLoadSubsystemBlockParse )
// ?rva007AD0A2@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD0A2 (21B): "Bridge"
BLOCK_PARSE_INIT( rva007AD0A2, theBridgeBlockParse )
// ?rva007AD120@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD120 (21B): "CommandSet"
BLOCK_PARSE_INIT( rva007AD120, theCommandSetBlockParse )
// ?rva007AD135@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD135 (21B): "ControlBarScheme"
BLOCK_PARSE_INIT( rva007AD135, theControlBarSchemeBlockParse )
// ?rva007AD14A@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD14A (21B): "ControlBarResizer"
BLOCK_PARSE_INIT( rva007AD14A, theControlBarResizerBlockParse )
// ?rva007AD15F@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD15F (21B): "CrateData"
BLOCK_PARSE_INIT( rva007AD15F, theCrateDataBlockParse )
// ?rva007AD174@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD174 (21B): "WindowTransition"
BLOCK_PARSE_INIT( rva007AD174, theWindowTransitionBlockParse )
// ?rva007AD189@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD189 (21B): "DamageFX"
BLOCK_PARSE_INIT( rva007AD189, theDamageFXBlockParse )
// ?rva007AD270@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD270 (21B): "GameData"
BLOCK_PARSE_INIT( rva007AD270, theGameDataBlockParse )
// ?rva007AD521@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD521 (21B): "FXParticleSystem"
BLOCK_PARSE_INIT( rva007AD521, theFXParticleSystemBlockParse )
// ?rva007AD60C@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD60C (21B): "SpecialPower"
BLOCK_PARSE_INIT( rva007AD60C, theSpecialPowerBlockParse )
// ?rva007AD621@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD621 (21B): "ShellMenuScheme"
BLOCK_PARSE_INIT( rva007AD621, theShellMenuSchemeBlockParse )
// ?rva007AD660@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD660 (21B): "Upgrade"
BLOCK_PARSE_INIT( rva007AD660, theUpgradeBlockParse )
// ?rva007AD69F@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD69F (21B): "AerialPathfindNoFlyZone"
BLOCK_PARSE_INIT( rva007AD69F, theAerialPathfindNoFlyZoneBlockParse )
// ?rva007AD6B4@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD6B4 (21B): "Weather"
BLOCK_PARSE_INIT( rva007AD6B4, theWeatherBlockParse )
// ?rva007AD6C9@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD6C9 (21B): "Weapon"
BLOCK_PARSE_INIT( rva007AD6C9, theWeaponBlockParse )
// ?rva007AD6DE@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD6DE (21B): "HeaderTemplate"
BLOCK_PARSE_INIT( rva007AD6DE, theHeaderTemplateBlockParse )
// ?rva007AD85A@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD85A (21B): "GlowEffect"
BLOCK_PARSE_INIT( rva007AD85A, theGlowEffectBlockParse )
// ?rva007AD86F@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD86F (21B): "RingEffect"
BLOCK_PARSE_INIT( rva007AD86F, theRingEffectBlockParse )
// ?rva007AD884@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD884 (21B): "FireEffect"
BLOCK_PARSE_INIT( rva007AD884, theFireEffectBlockParse )
// ?rva007AD939@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD939 (21B): "LivingWorldObject"
BLOCK_PARSE_INIT( rva007AD939, theLivingWorldObjectBlockParse )
// ?rva007AD94E@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD94E (21B): "LivingWorldMapInfo"
BLOCK_PARSE_INIT( rva007AD94E, theLivingWorldMapInfoBlockParse )
// ?rva007AD9E8@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD9E8 (21B): "CloudEffect"
BLOCK_PARSE_INIT( rva007AD9E8, theCloudEffectBlockParse )
// ?rva007AD9FD@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD9FD (21B): "PlayerAIType"
BLOCK_PARSE_INIT( rva007AD9FD, thePlayerAITypeBlockParse )
// ?rva007ADB4C@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007ADB4C (21B): "StrategicHUD"
BLOCK_PARSE_INIT( rva007ADB4C, theStrategicHUDBlockParse )
// ?rva007ADB6D@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007ADB6D (21B): "InGameNotificationBox"
BLOCK_PARSE_INIT( rva007ADB6D, theInGameNotificationBoxBlockParse )
// ?rva007ADB92@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007ADB92 (21B): "AptButtonTooltipMap"
BLOCK_PARSE_INIT( rva007ADB92, theAptButtonTooltipMapBlockParse )
// ?rva007AE15A@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AE15A (21B): "AIDozerAssignment"
BLOCK_PARSE_INIT( rva007AE15A, theAIDozerAssignmentBlockParse )
// ?rva007AE16F@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AE16F (21B): "SkirmishAIData"
BLOCK_PARSE_INIT( rva007AE16F, theSkirmishAIDataBlockParse )
// ?rva007AE489@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AE489 (21B): "LivingWorldBuilding"
BLOCK_PARSE_INIT( rva007AE489, theLivingWorldBuildingBlockParse )
// ?rva007AE4AE@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AE4AE (21B): "LivingWorldPlayerTemplate"
BLOCK_PARSE_INIT( rva007AE4AE, theLivingWorldPlayerTemplateBlockParse )
// ?rva007AE7CA@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AE7CA (21B): "Fire"
BLOCK_PARSE_INIT( rva007AE7CA, theFireBlockParse )
// ?rva007AE963@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AE963 (21B): "CloudBreakEffect"
BLOCK_PARSE_INIT( rva007AE963, theCloudBreakEffectBlockParse )
// ?rva007AFC11@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AFC11 (21B): "LivingWorldRegionEffects"
BLOCK_PARSE_INIT( rva007AFC11, theLivingWorldRegionEffectsBlockParse )
// ?rva007AFC56@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AFC56 (21B): "LivingWorldArmyIcon"
BLOCK_PARSE_INIT( rva007AFC56, theLivingWorldArmyIconBlockParse )
// ?rva007AFCB4@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AFCB4 (21B): "LivingWorldSound"
BLOCK_PARSE_INIT( rva007AFCB4, theLivingWorldSoundBlockParse )
// ?rva007AFCE3@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AFCE3 (21B): "LivingWorldAnimObject"
BLOCK_PARSE_INIT( rva007AFCE3, theLivingWorldAnimObjectBlockParse )
// ?rva007AFD4C@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AFD4C (21B): "LivingWorldBuildingIcon"
BLOCK_PARSE_INIT( rva007AFD4C, theLivingWorldBuildingIconBlockParse )
// ?rva007AFD61@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AFD61 (21B): "LivingWorldBuildPlotIcon"
BLOCK_PARSE_INIT( rva007AFD61, theLivingWorldBuildPlotIconBlockParse )
// ?rva007AFE97@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AFE97 (21B): "LivingWorldPlayerArmy"
BLOCK_PARSE_INIT( rva007AFE97, theLivingWorldPlayerArmyBlockParse )
// ?rva007AFFBC@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AFFBC (21B): "AutoResolveHandicapLevel"
BLOCK_PARSE_INIT( rva007AFFBC, theAutoResolveHandicapLevelBlockParse )
// ?rva007AFFD1@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AFFD1 (21B): "LivingWorldAutoResolveSciencePurchasePointBonus"
BLOCK_PARSE_INIT( rva007AFFD1, theLivingWorldAutoResolveSciencePurchasePointBonusBlockParse )
// ?rva007AFFE6@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AFFE6 (21B): "AutoResolveReinforcementSchedule"
BLOCK_PARSE_INIT( rva007AFFE6, theAutoResolveReinforcementScheduleBlockParse )
// ?rva007AFFFB@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AFFFB (21B): "LivingWorldAutoResolveResourceBonus"
BLOCK_PARSE_INIT( rva007AFFFB, theLivingWorldAutoResolveResourceBonusBlockParse )
// ?rva007B003F@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007B003F (21B): "CrowdResponse"
BLOCK_PARSE_INIT( rva007B003F, theCrowdResponseBlockParse )
// ?rva007B0088@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007B0088 (21B): "HouseColor"
BLOCK_PARSE_INIT( rva007B0088, theHouseColorBlockParse )
// ?rva007B009D@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007B009D (21B): "AutoResolveLeadership"
BLOCK_PARSE_INIT( rva007B009D, theAutoResolveLeadershipBlockParse )
// ?rva007B00B2@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007B00B2 (21B): "AutoResolveBody"
BLOCK_PARSE_INIT( rva007B00B2, theAutoResolveBodyBlockParse )
// ?rva007B00C7@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007B00C7 (21B): "AutoResolveCombatChain"
BLOCK_PARSE_INIT( rva007B00C7, theAutoResolveCombatChainBlockParse )
// ?rva007B00DC@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007B00DC (21B): "AutoResolveWeapon"
BLOCK_PARSE_INIT( rva007B00DC, theAutoResolveWeaponBlockParse )
// ?rva007B01D3@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007B01D3 (21B): "AIBase"
BLOCK_PARSE_INIT( rva007B01D3, theAIBaseBlockParse )
// ?rva007B01E8@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007B01E8 (21B): "ArmyDefinition"
BLOCK_PARSE_INIT( rva007B01E8, theArmyDefinitionBlockParse )
// ?rva007B01FD@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007B01FD (21B): "MeshNameMatches"
BLOCK_PARSE_INIT( rva007B01FD, theMeshNameMatchesBlockParse )
// ?rva007B022C@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007B022C (21B): "LivingWorldAITemplate"
BLOCK_PARSE_INIT( rva007B022C, theLivingWorldAITemplateBlockParse )
// ?rva007B026B@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007B026B (21B): "LightPointLevel"
BLOCK_PARSE_INIT( rva007B026B, theLightPointLevelBlockParse )
// ?rva007B02F6@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007B02F6 (21B): "FormationAssistant"
BLOCK_PARSE_INIT( rva007B02F6, theFormationAssistantBlockParse )
// ?rva007B033F@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007B033F (21B): "StanceTemplate"
BLOCK_PARSE_INIT( rva007B033F, theStanceTemplateBlockParse )
// ?rva007B0354@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007B0354 (21B): "EmotionNugget"
BLOCK_PARSE_INIT( rva007B0354, theEmotionNuggetBlockParse )
// ?rva007B03B2@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007B03B2 (21B): "AutoResolveArmor"
BLOCK_PARSE_INIT( rva007B03B2, theAutoResolveArmorBlockParse )
