// cl: /DNDEBUG /MD
//
// INI block-parse registration initializers. BFME replaced Zero Hour's
// theTypeTable array with 12-byte BlockParse nodes { next, token, parse } that
// link themselves into theBlockParseList (VA 0x00DDF578; the matched
// BlockParse ctor 0x0004147D and findBlockParse walk it). The node's token and
// parse pointer are constant-initialized in .data, so each registration's
// dynamic initializer is only the link: node.next = head; head = &node
// (21 bytes). Retail holds 130 such initializers from 0x007ABBF6; each node
// name below is its token, read from the string its +4 slot points at. The
// owning units are not recovered (most sit in one contiguous run, the INI
// unit's own table), so each initializer keeps an honest address name.

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
void parseScriptAction(INI *);
void parseScriptCondition(INI *);
void parseLivingWorldRegionCampaignDefinition(INI *);
void parseLivingWorldMapInfoDefinition(INI *);
void Rva0021376BParse(INI *);
void parseCloudEffectDefinition(INI *);
void parsePlayerAITypeDefinition(INI *);
void parseArmySummaryDescriptionDefinition(INI *);
void parseInGameNotificationBoxDefinition(INI *);
void parseFireLogicSystemDefinition(INI *);
void parseExperienceScalarTableDefinition(INI *);
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
void parseAwardSystemDefinition(INI *);
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
void iniParseEnvironmentSkyboxTextureDefinition(INI *);
void iniParseFactionVictoryDefinition(INI *);
void iniParseVictorySystemDefinition(INI *);
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
void parseFontSubstitutionDefinition(INI *);
void parseCloudBreakEffectDefinition(INI *);
void parseFormationAssistantDefinition(INI *);
namespace StrategicHUD { void ParseSettings(INI *); }
class ArmorStore
{
public:
	static void parseArmorDefinition(INI *);
};
class ArmyDefinitionManager
{
public:
	static void parseArmyDefinition(INI *);
};
class AttributeModifierStore
{
public:
	static void parseModifierListDefinition(INI *);
};
class AudioEventInfo
{
public:
	static void parseMultisoundDefinition(INI *);
};
class BannerUI
{
public:
	static void ParseBannerTypeInfo(INI *);
};
class ControlBar
{
public:
	static void parseCommandButtonDefinition(INI *);
	static void parseCommandSetDefinition(INI *);
};
class CrateSystem
{
public:
	static void parseCrateTemplateDefinition(INI *);
};
class CreateAHeroManager
{
public:
	static void iniParseCreateAHeroSystem(INI *);
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
class Eva
{
public:
	static void iniParseEvaEventForwardReference(INI *);
	static void iniParseNewEvaEvent(INI *);
	static void iniParsePredefinedEvaEvent(INI *);
};
class ExperienceLevelStore
{
public:
	static void friend_parseExperienceLevelDefinition(INI *);
};
class FXListStore
{
public:
	static void parseFXListDefinition(INI *);
};
class FontLibrary
{
public:
	static void ParseFontDefaultSettings(INI *);
};
class GlobalData
{
public:
	static void parseGameDataDefinition(INI *);
};
class GlobalWeatherSystem
{
public:
	static void parseWeatherData(INI *);
};
class INI
{
public:
	static void parseAIDataDefinition(INI *);
	static void parseAudioLODDefinition(INI *);
	static void parseAudioSettingsDefinition(INI *);
	static void parseBenchProfile(INI *);
	static void parseChildObjectDefinition(INI *);
	static void parseControlBarSchemeDefinition(INI *);
	static void parseDrawGroupNumberDefinition(INI *);
	static void parseHeaderTemplateDefinition(INI *);
	static void parseLODPreset(INI *);
	static void parseLanguageDefinition(INI *);
	static void parseMappedImageDefinition(INI *);
	static void parseMiscAudio(INI *);
	static void parseMiscEvaData(INI *);
	static void parseMouseCursorDefinition(INI *);
	static void parseMouseDefinition(INI *);
	static void parseMultiplayerColorDefinition(INI *);
	static void parseMultiplayerSettingsDefinition(INI *);
	static void parseObjectDefinition(INI *);
	static void parseObjectReskinDefinition(INI *);
	static void parseOnlineChatColorDefinition(INI *);
	static void parseParticleSystemDefinition(INI *);
	static void parseShellMenuSchemeDefinition(INI *);
	static void parseStaticGameLODDefinition(INI *);
	static void parseTerrainBridgeDefinition(INI *);
	static void parseTerrainDefinition(INI *);
	static void parseTerrainRoadDefinition(INI *);
	static void parseWaterSettingDefinition(INI *);
	static void parseWaterTransparencyDefinition(INI *);
	static void parseWeatherDefinition(INI *);
	static void parseWindowTransitions(INI *);
};
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
class LinearCampaignManager
{
public:
	static void parseLinearCampaignIniBlock(INI *);
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
class LocomotorStore
{
public:
	static void parseLocomotorTemplateDefinition(INI *);
};
class MetaMap
{
public:
	static void parseMetaMap(INI *);
};
class MissionObjectiveTracker
{
public:
	static void ParseMapMissionObjective(INI *);
};
class ObjectCreationListStore
{
public:
	static void parseObjectCreationListDefinition(INI *);
};
class PlayerTemplateStore
{
public:
	static void parsePlayerTemplateDefinition(INI *);
};
class RankInfoStore
{
public:
	static void friend_parseRankDefinition(INI *);
};
class Rva00425F10
{
public:
	static void parseStanceTemplateDefinition(INI *);
};
class ScienceStore
{
public:
	static void friend_parseScienceDefinition(INI *);
};
class ScoredKillEvaAnnouncerController
{
public:
	static void iniParseScoredKillEvaAnnouncerBlock(INI *);
};
class SpecialPowerStore
{
public:
	static void parseSpecialPowerDefinition(INI *);
};
class UpgradeCenter
{
public:
	static void parseUpgradeDefinition(INI *);
};
class WeaponStore
{
public:
	static void parseWeaponTemplateDefinition(INI *);
};
// ControlBarResizer points to the shared one-byte RET at 0x000B3FD0.
// Reuse an existing cdecl owner without assigning a recovered callback name.
// The Apt tooltip node keeps its existing 44-byte owner in Rva00224A3F.cpp.

BlockParse theAudioSettingsBlockParse = { 0, "AudioSettings", INI::parseAudioSettingsDefinition };	// VA 0x00DB3A08 "AudioSettings", parse 0x0004171A
BlockParse theShadowMapBlockParse = { 0, "ShadowMap", parseShadowMapBlock };	// VA 0x00DB4488 "ShadowMap", parse 0x0007BE1E
BlockParse theLoadSubsystemBlockParse = { 0, "LoadSubsystem", parseSubsystemLegendDefinition };	// VA 0x00DB7034 "LoadSubsystem", parse 0x001B4E07
BlockParse theAIDataBlockParse = { 0, "AIData", INI::parseAIDataDefinition };	// VA 0x00DB8934 "AIData", parse 0x001D8E7A
BlockParse theArmorBlockParse = { 0, "Armor", ArmorStore::parseArmorDefinition };	// VA 0x00DB8A74 "Armor", parse 0x001D9484
BlockParse theMusicTrackBlockParse = { 0, "MusicTrack", parseMusicTrackDefinition };	// VA 0x00DB8B08 "MusicTrack", parse 0x001DA980
BlockParse theAudioEventBlockParse = { 0, "AudioEvent", parseAudioEventDefinition };	// VA 0x00DB8B14 "AudioEvent", parse 0x001DA9CA
BlockParse theDialogEventBlockParse = { 0, "DialogEvent", parseDialogDefinition };	// VA 0x00DB8B20 "DialogEvent", parse 0x001DAA14
BlockParse theAmbientStreamBlockParse = { 0, "AmbientStream", parseAmbientStreamDefinition };	// VA 0x00DB8B2C "AmbientStream", parse 0x001DAA5E
BlockParse theStreamedSoundBlockParse = { 0, "StreamedSound", parseStreamedSoundDefinition };	// VA 0x00DB8B38 "StreamedSound", parse 0x001DAAA8
BlockParse theMultisoundBlockParse = { 0, "Multisound", AudioEventInfo::parseMultisoundDefinition };	// VA 0x00DB8B44 "Multisound", parse 0x001DA4DE
BlockParse theBridgeBlockParse = { 0, "Bridge", INI::parseTerrainBridgeDefinition };	// VA 0x00DB8B8C "Bridge", parse 0x001DAEB8
BlockParse theCommandButtonBlockParse = { 0, "CommandButton", ControlBar::parseCommandButtonDefinition };	// VA 0x00DB8BBC "CommandButton", parse 0x001DAF81
BlockParse theCommandMapBlockParse = { 0, "CommandMap", MetaMap::parseMetaMap };	// VA 0x00DB8C14 "CommandMap", parse 0x001DB5A2
BlockParse theDebugCommandMapBlockParse = { 0, "DebugCommandMap", parseDebugCommandMap };	// VA 0x00DB8C20 "DebugCommandMap", parse 0x001DB4CF
BlockParse theCommandSetBlockParse = { 0, "CommandSet", ControlBar::parseCommandSetDefinition };	// VA 0x00DB8C50 "CommandSet", parse 0x0031EC03
BlockParse theControlBarSchemeBlockParse = { 0, "ControlBarScheme", INI::parseControlBarSchemeDefinition };	// VA 0x00DB8C80 "ControlBarScheme", parse 0x001DB68C
BlockParse theControlBarResizerBlockParse = { 0, "ControlBarResizer", (INIBlockParse)Rva000B3FD0AptFreeSound };	// VA 0x00DB8CB0 "ControlBarResizer", parse 0x000B3FD0
BlockParse theCrateDataBlockParse = { 0, "CrateData", CrateSystem::parseCrateTemplateDefinition };	// VA 0x00DB8CBC "CrateData", parse 0x0035CFEA
BlockParse theWindowTransitionBlockParse = { 0, "WindowTransition", INI::parseWindowTransitions };	// VA 0x00DB8CEC "WindowTransition", parse 0x001DC66F
BlockParse theDamageFXBlockParse = { 0, "DamageFX", DamageFXStore::parseDamageFXDefinition };	// VA 0x00DB8D1C "DamageFX", parse 0x00360B0F
BlockParse theDrawGroupInfoBlockParse = { 0, "DrawGroupInfo", INI::parseDrawGroupNumberDefinition };	// VA 0x00DB8D28 "DrawGroupInfo", parse 0x001DCC9F
BlockParse thePredefinedEvaEventBlockParse = { 0, "PredefinedEvaEvent", Eva::iniParsePredefinedEvaEvent };	// VA 0x00DB8D70 "PredefinedEvaEvent", parse 0x001DEA96
BlockParse theNewEvaEventBlockParse = { 0, "NewEvaEvent", Eva::iniParseNewEvaEvent };	// VA 0x00DB8D7C "NewEvaEvent", parse 0x001DF42D
BlockParse theEvaEventForwardReferenceBlockParse = { 0, "EvaEventForwardReference", Eva::iniParseEvaEventForwardReference };	// VA 0x00DB8D88 "EvaEventForwardReference", parse 0x001DF6A8
BlockParse theMiscEvaDataBlockParse = { 0, "MiscEvaData", INI::parseMiscEvaData };	// VA 0x00DB8D94 "MiscEvaData", parse 0x001DCFE5
BlockParse theFXListBlockParse = { 0, "FXList", FXListStore::parseFXListDefinition };	// VA 0x00DB8DDC "FXList", parse 0x001E2CAE
BlockParse theGameDataBlockParse = { 0, "GameData", GlobalData::parseGameDataDefinition };	// VA 0x00DB8DF4 "GameData", parse 0x00237AB1
BlockParse theLocomotorBlockParse = { 0, "Locomotor", LocomotorStore::parseLocomotorTemplateDefinition };	// VA 0x00DB8F84 "Locomotor", parse 0x001E8A94
BlockParse theLanguageBlockParse = { 0, "Language", INI::parseLanguageDefinition };	// VA 0x00DB8F98 "Language", parse 0x001EA3F4
BlockParse theLinearCampaignBlockParse = { 0, "LinearCampaign", LinearCampaignManager::parseLinearCampaignIniBlock };	// VA 0x00DB8FE0 "LinearCampaign", parse 0x001ED580
BlockParse theMappedImageBlockParse = { 0, "MappedImage", INI::parseMappedImageDefinition };	// VA 0x00DB9004 "MappedImage", parse 0x001ED63C
BlockParse theMiscAudioBlockParse = { 0, "MiscAudio", INI::parseMiscAudio };	// VA 0x00DB9010 "MiscAudio", parse 0x001ED6EE
BlockParse theMouseCursorBlockParse = { 0, "MouseCursor", INI::parseMouseCursorDefinition };	// VA 0x00DB9138 "MouseCursor", parse 0x001EF2CB
BlockParse theMouseBlockParse = { 0, "Mouse", INI::parseMouseDefinition };	// VA 0x00DB9144 "Mouse", parse 0x001EE050
BlockParse theMultiplayerSettingsBlockParse = { 0, "MultiplayerSettings", INI::parseMultiplayerSettingsDefinition };	// VA 0x00DB9150 "MultiplayerSettings", parse 0x001EF367
BlockParse theMultiplayerColorBlockParse = { 0, "MultiplayerColor", INI::parseMultiplayerColorDefinition };	// VA 0x00DB915C "MultiplayerColor", parse 0x001EF3BF
BlockParse theOnlineChatColorsBlockParse = { 0, "OnlineChatColors", INI::parseOnlineChatColorDefinition };	// VA 0x00DB918C "OnlineChatColors", parse 0x001EF471
BlockParse theObjectBlockParse = { 0, "Object", INI::parseObjectDefinition };	// VA 0x00DB9248 "Object", parse 0x001EFFC6
BlockParse theObjectReskinBlockParse = { 0, "ObjectReskin", INI::parseObjectReskinDefinition };	// VA 0x00DB9254 "ObjectReskin", parse 0x001F0016
BlockParse theChildObjectBlockParse = { 0, "ChildObject", INI::parseChildObjectDefinition };	// VA 0x00DB9260 "ChildObject", parse 0x001F008C
BlockParse theObjectCreationListBlockParse = { 0, "ObjectCreationList", ObjectCreationListStore::parseObjectCreationListDefinition };	// VA 0x00DB9344 "ObjectCreationList", parse 0x001F0C0B
BlockParse theFXParticleSystemBlockParse = { 0, "FXParticleSystem", INI::parseParticleSystemDefinition };	// VA 0x00DB938C "FXParticleSystem", parse 0x001FD0B4
BlockParse thePlayerTemplateBlockParse = { 0, "PlayerTemplate", PlayerTemplateStore::parsePlayerTemplateDefinition };	// VA 0x00DB93BC "PlayerTemplate", parse 0x001FEFEC
BlockParse theRoadBlockParse = { 0, "Road", INI::parseTerrainRoadDefinition };	// VA 0x00DB9404 "Road", parse 0x001FF288
BlockParse theScienceBlockParse = { 0, "Science", ScienceStore::friend_parseScienceDefinition };	// VA 0x00DB9434 "Science", parse 0x001FFF3A
BlockParse theRankBlockParse = { 0, "Rank", RankInfoStore::friend_parseRankDefinition };	// VA 0x00DB947C "Rank", parse 0x0020038E
BlockParse theSpecialPowerBlockParse = { 0, "SpecialPower", SpecialPowerStore::parseSpecialPowerDefinition };	// VA 0x00DB94A4 "SpecialPower", parse 0x003B15D6
BlockParse theShellMenuSchemeBlockParse = { 0, "ShellMenuScheme", INI::parseShellMenuSchemeDefinition };	// VA 0x00DB94D4 "ShellMenuScheme", parse 0x00200984
BlockParse theTerrainBlockParse = { 0, "Terrain", INI::parseTerrainDefinition };	// VA 0x00DB94E0 "Terrain", parse 0x00200A65
BlockParse theWaterTextureListBlockParse = { 0, "WaterTextureList", iniParseWaterTexturesDefinition };	// VA 0x00DB94EC "WaterTextureList", parse 0x00200AEA
BlockParse theUpgradeBlockParse = { 0, "Upgrade", UpgradeCenter::parseUpgradeDefinition };	// VA 0x00DB94F8 "Upgrade", parse 0x0026FA05
BlockParse theWaterSetBlockParse = { 0, "WaterSet", INI::parseWaterSettingDefinition };	// VA 0x00DB9504 "WaterSet", parse 0x00200BEB
BlockParse theWaterTransparencyBlockParse = { 0, "WaterTransparency", INI::parseWaterTransparencyDefinition };	// VA 0x00DB9510 "WaterTransparency", parse 0x00200EE4
BlockParse theAerialPathfindNoFlyZoneBlockParse = { 0, "AerialPathfindNoFlyZone", parseAerialPathfindNoFlyZoneDefinition };	// VA 0x00DB9558 "AerialPathfindNoFlyZone", parse 0x00200FE3
BlockParse theWeatherBlockParse = { 0, "Weather", INI::parseWeatherDefinition };	// VA 0x00DB9588 "Weather", parse 0x0020187A
BlockParse theWeaponBlockParse = { 0, "Weapon", WeaponStore::parseWeaponTemplateDefinition };	// VA 0x00DB95B8 "Weapon", parse 0x002CE102
BlockParse theHeaderTemplateBlockParse = { 0, "HeaderTemplate", INI::parseHeaderTemplateDefinition };	// VA 0x00DB95C4 "HeaderTemplate", parse 0x00201CAF
BlockParse theReallyLowMHzBlockParse = { 0, "ReallyLowMHz", parseReallyLowMHz };	// VA 0x00DB9740 "ReallyLowMHz", parse 0x00201E56
BlockParse theAudioLowMHzBlockParse = { 0, "AudioLowMHz", parseAudioLowMHz };	// VA 0x00DB974C "AudioLowMHz", parse 0x00201E81
BlockParse theBenchProfileBlockParse = { 0, "BenchProfile", INI::parseBenchProfile };	// VA 0x00DB9758 "BenchProfile", parse 0x002026D4
BlockParse theLODPresetBlockParse = { 0, "LODPreset", INI::parseLODPreset };	// VA 0x00DB9764 "LODPreset", parse 0x00202E23
BlockParse theStaticGameLODBlockParse = { 0, "StaticGameLOD", Rva00202BB2Parse };	// VA 0x00DB9770 "StaticGameLOD", parse 0x00202BB2
BlockParse theDynamicGameLODBlockParse = { 0, "DynamicGameLOD", INI::parseStaticGameLODDefinition };	// VA 0x00DB977C "DynamicGameLOD", parse 0x00202F05
BlockParse theAudioLODBlockParse = { 0, "AudioLOD", INI::parseAudioLODDefinition };	// VA 0x00DB9788 "AudioLOD", parse 0x00202F8A
BlockParse theScriptActionBlockParse = { 0, "ScriptAction", parseScriptAction };	// VA 0x00DB97D0 "ScriptAction", parse 0x00206DFF
BlockParse theScriptConditionBlockParse = { 0, "ScriptCondition", parseScriptCondition };	// VA 0x00DB97DC "ScriptCondition", parse 0x00206E63
BlockParse theSkyboxTextureSetBlockParse = { 0, "SkyboxTextureSet", iniParseEnvironmentSkyboxTextureDefinition };	// VA 0x00DB984C "SkyboxTextureSet", parse 0x0020D6F5
BlockParse theGlowEffectBlockParse = { 0, "GlowEffect", parseGlowEffect };	// VA 0x00DB9858 "GlowEffect", parse 0x00309FB3
BlockParse theRingEffectBlockParse = { 0, "RingEffect", parseRingEffect };	// VA 0x00DB9864 "RingEffect", parse 0x00309FFD
BlockParse theFireEffectBlockParse = { 0, "FireEffect", parseFireEffect };	// VA 0x00DB9870 "FireEffect", parse 0x0030A040
BlockParse theLargeGroupAudioMapBlockParse = { 0, "LargeGroupAudioMap", LargeGroupAudio::parseLargeGroupAudioMapDefinition };	// VA 0x00DB98A0 "LargeGroupAudioMap", parse 0x0020E027
BlockParse theLargeGroupAudioUnusedKnownKeysBlockParse = { 0, "LargeGroupAudioUnusedKnownKeys", LargeGroupAudio::parseLargeGroupAudioUnusedKnownKeysDefinition };	// VA 0x00DB98AC "LargeGroupAudioUnusedKnownKeys", parse 0x0020DE03
BlockParse theLivingWorldRegionCampaignBlockParse = { 0, "LivingWorldRegionCampaign", parseLivingWorldRegionCampaignDefinition };	// VA 0x00DB993C "LivingWorldRegionCampaign", parse 0x00210A14
BlockParse theLivingWorldObjectBlockParse = { 0, "LivingWorldObject", Rva0021376BParse };	// VA 0x00DB9A20 "LivingWorldObject", parse 0x0021376B
BlockParse theLivingWorldMapInfoBlockParse = { 0, "LivingWorldMapInfo", parseLivingWorldMapInfoDefinition };	// VA 0x00DB9A2C "LivingWorldMapInfo", parse 0x00210F64
BlockParse theModifierListBlockParse = { 0, "ModifierList", AttributeModifierStore::parseModifierListDefinition };	// VA 0x00DB9AD0 "ModifierList", parse 0x00214C4E
BlockParse theCloudEffectBlockParse = { 0, "CloudEffect", parseCloudEffectDefinition };	// VA 0x00DB9B68 "CloudEffect", parse 0x0021526C
BlockParse thePlayerAITypeBlockParse = { 0, "PlayerAIType", parsePlayerAITypeDefinition };	// VA 0x00DB9B74 "PlayerAIType", parse 0x00215C38
BlockParse theVictorySystemDataBlockParse = { 0, "VictorySystemData", iniParseVictorySystemDefinition };	// VA 0x00DB9BA4 "VictorySystemData", parse 0x00215C54
BlockParse theFactionVictoryDataBlockParse = { 0, "FactionVictoryData", iniParseFactionVictoryDefinition };	// VA 0x00DB9BB0 "FactionVictoryData", parse 0x00215D0B
BlockParse theBannerTypeBlockParse = { 0, "BannerType", BannerUI::ParseBannerTypeInfo };	// VA 0x00DB9BF8 "BannerType", parse 0x00217194
BlockParse theFontDefaultSettingsBlockParse = { 0, "FontDefaultSettings", FontLibrary::ParseFontDefaultSettings };	// VA 0x00DB9C04 "FontDefaultSettings", parse 0x00218C82
BlockParse theFontSubstitutionBlockParse = { 0, "FontSubstitution", parseFontSubstitutionDefinition };	// VA 0x00DB9C10 "FontSubstitution", parse 0x00219005
BlockParse theCreateAHeroSystemBlockParse = { 0, "CreateAHeroSystem", CreateAHeroManager::iniParseCreateAHeroSystem };	// VA 0x00DB9D38 "CreateAHeroSystem", parse 0x0022044C
BlockParse theArmySummaryDescriptionBlockParse = { 0, "ArmySummaryDescription", parseArmySummaryDescriptionDefinition };	// VA 0x00DBA184 "ArmySummaryDescription", parse 0x00221012
BlockParse theStrategicHUDBlockParse = { 0, "StrategicHUD", StrategicHUD::ParseSettings };	// VA 0x00DBA190 "StrategicHUD", parse 0x0022157B
BlockParse theInGameNotificationBoxBlockParse = { 0, "InGameNotificationBox", parseInGameNotificationBoxDefinition };	// VA 0x00DBA19C "InGameNotificationBox", parse 0x0022232E
extern BlockParse theAptButtonTooltipMapBlockParse;	// VA 0x00DBA1CC "AptButtonTooltipMap", parse 0x00224DFF
BlockParse theFireLogicSystemBlockParse = { 0, "FireLogicSystem", parseFireLogicSystemDefinition };	// VA 0x00DBB758 "FireLogicSystem", parse 0x002859A8
BlockParse theExperienceLevelBlockParse = { 0, "ExperienceLevel", ExperienceLevelStore::friend_parseExperienceLevelDefinition };	// VA 0x00DBB88C "ExperienceLevel", parse 0x0028A294
BlockParse theExperienceScalarTableBlockParse = { 0, "ExperienceScalarTable", parseExperienceScalarTableDefinition };	// VA 0x00DBB898 "ExperienceScalarTable", parse 0x00289265
BlockParse theAIDozerAssignmentBlockParse = { 0, "AIDozerAssignment", parseAIDozerAssignmentDefinition };	// VA 0x00DBBC1C "AIDozerAssignment", parse 0x002A92F2
BlockParse theSkirmishAIDataBlockParse = { 0, "SkirmishAIData", parseSkirmishAIDataDefinition };	// VA 0x00DBBC28 "SkirmishAIData", parse 0x002A8A31
BlockParse theLivingWorldBuildingBlockParse = { 0, "LivingWorldBuilding", parseLivingWorldBuildingDefinition };	// VA 0x00DBD078 "LivingWorldBuilding", parse 0x002E048C
BlockParse theLivingWorldPlayerTemplateBlockParse = { 0, "LivingWorldPlayerTemplate", parseLivingWorldPlayerTemplateDefinition };	// VA 0x00DBD0A8 "LivingWorldPlayerTemplate", parse 0x002E2386
BlockParse theFireBlockParse = { 0, "Fire", parseFireDefinition };	// VA 0x00DBD9AC "Fire", parse 0x0030AFFB
BlockParse theWeatherDataBlockParse = { 0, "WeatherData", GlobalWeatherSystem::parseWeatherData };	// VA 0x00DBE4C4 "WeatherData", parse 0x0031842A
BlockParse theCloudBreakEffectBlockParse = { 0, "CloudBreakEffect", parseCloudBreakEffectDefinition };	// VA 0x00DBE4D0 "CloudBreakEffect", parse 0x00318ABB
BlockParse theLivingWorldRegionEffectsBlockParse = { 0, "LivingWorldRegionEffects", parseLivingWorldRegionEffectsDefinition };	// VA 0x00DC14B8 "LivingWorldRegionEffects", parse 0x003EF467
BlockParse theLivingWorldArmyIconBlockParse = { 0, "LivingWorldArmyIcon", parseLivingWorldArmyIconDefinition };	// VA 0x00DC177C "LivingWorldArmyIcon", parse 0x003F9EDF
BlockParse theLivingWorldSoundBlockParse = { 0, "LivingWorldSound", LivingWorldSound::ParseSound };	// VA 0x00DC17EC "LivingWorldSound", parse 0x003FB07D
BlockParse theLivingWorldAnimObjectBlockParse = { 0, "LivingWorldAnimObject", Rva003FD7CEParse };	// VA 0x00DC18EC "LivingWorldAnimObject", parse 0x003FD7CE
BlockParse theLivingWorldBuildingIconBlockParse = { 0, "LivingWorldBuildingIcon", parseLivingWorldBuildingIconDefinition };	// VA 0x00DC1AB4 "LivingWorldBuildingIcon", parse 0x00402B19
BlockParse theLivingWorldBuildPlotIconBlockParse = { 0, "LivingWorldBuildPlotIcon", parseLivingWorldBuildPlotIconDefinition };	// VA 0x00DC1B04 "LivingWorldBuildPlotIcon", parse 0x00402E30
BlockParse theAwardSystemBlockParse = { 0, "AwardSystem", parseAwardSystemDefinition };	// VA 0x00DC1D9C "AwardSystem", parse 0x0040C32B
BlockParse theLivingWorldPlayerArmyBlockParse = { 0, "LivingWorldPlayerArmy", parseLivingWorldPlayerArmyDefinition };	// VA 0x00DC1F68 "LivingWorldPlayerArmy", parse 0x0040F0F0
BlockParse theAutoResolveHandicapLevelBlockParse = { 0, "AutoResolveHandicapLevel", parseAutoResolveHandicapLevelDefinition };	// VA 0x00DC2044 "AutoResolveHandicapLevel", parse 0x0041355D
BlockParse theLivingWorldAutoResolveSciencePurchasePointBonusBlockParse = { 0, "LivingWorldAutoResolveSciencePurchasePointBonus", LivingWorldAutoResolveSciencePurchasePointBonusScheduleStore::parseLivingWorldAutoResolveSciencePurchasePointBonusBlock };	// VA 0x00DC2050 "LivingWorldAutoResolveSciencePurchasePointBonus", parse 0x00413B4D
BlockParse theAutoResolveReinforcementScheduleBlockParse = { 0, "AutoResolveReinforcementSchedule", parseAutoResolveReinforcementScheduleDefinition };	// VA 0x00DC205C "AutoResolveReinforcementSchedule", parse 0x00413D58
BlockParse theLivingWorldAutoResolveResourceBonusBlockParse = { 0, "LivingWorldAutoResolveResourceBonus", LivingWorldAutoResolveResourceBonusScheduleStore::parseLivingWorldAutoResolveResourceBonusBlock };	// VA 0x00DC2068 "LivingWorldAutoResolveResourceBonus", parse 0x0041428F
BlockParse theScoredKillEvaAnnouncerBlockParse = { 0, "ScoredKillEvaAnnouncer", ScoredKillEvaAnnouncerController::iniParseScoredKillEvaAnnouncerBlock };	// VA 0x00DC20B0 "ScoredKillEvaAnnouncer", parse 0x00414F85
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
BlockParse theMissionObjectiveListBlockParse = { 0, "MissionObjectiveList", MissionObjectiveTracker::ParseMapMissionObjective };	// VA 0x00DC85B8 "MissionObjectiveList", parse 0x00426D14
BlockParse theAutoResolveArmorBlockParse = { 0, "AutoResolveArmor", LivingWorldAutoResolveArmorStore::parseArmorDefinition };	// VA 0x00DC85E8 "AutoResolveArmor", parse 0x00427392
BlockParse theAnimationSoundClientBehaviorGlobalSettingBlockParse = { 0, "AnimationSoundClientBehaviorGlobalSetting", parseAnimationSoundClientBehaviorGlobalSetting };	// VA 0x00DC8990 "AnimationSoundClientBehaviorGlobalSetting", parse 0x004330EE
BlockParse theLivingWorldCampaignBlockParse = { 0, "LivingWorldCampaign", LivingWorldCampaign::ParseLivingWorldCampaignBlock };	// VA 0x00DD19A0 "LivingWorldCampaign", parse 0x0052D04E

struct Rva007ABBF6BlockParseInits
{
	static void rva007ABBF6();
	static void rva007ABFE3();
	static void rva007ACFBB();
	static void rva007ACFD0();
	static void rva007ACFF5();
	static void rva007AD024();
	static void rva007AD039();
	static void rva007AD04E();
	static void rva007AD063();
	static void rva007AD078();
	static void rva007AD08D();
	static void rva007AD0A2();
	static void rva007AD0B7();
	static void rva007AD0DC();
	static void rva007AD0F1();
	static void rva007AD120();
	static void rva007AD135();
	static void rva007AD14A();
	static void rva007AD15F();
	static void rva007AD174();
	static void rva007AD189();
	static void rva007AD19E();
	static void rva007AD1C3();
	static void rva007AD1D8();
	static void rva007AD1ED();
	static void rva007AD202();
	static void rva007AD241();
	static void rva007AD270();
	static void rva007AD2EF();
	static void rva007AD31E();
	static void rva007AD333();
	static void rva007AD37C();
	static void rva007AD391();
	static void rva007AD3B6();
	static void rva007AD3CB();
	static void rva007AD3FA();
	static void rva007AD40F();
	static void rva007AD424();
	static void rva007AD463();
	static void rva007AD478();
	static void rva007AD48D();
	static void rva007AD4CC();
	static void rva007AD521();
	static void rva007AD550();
	static void rva007AD57F();
	static void rva007AD594();
	static void rva007AD5DD();
	static void rva007AD60C();
	static void rva007AD621();
	static void rva007AD636();
	static void rva007AD64B();
	static void rva007AD660();
	static void rva007AD675();
	static void rva007AD68A();
	static void rva007AD69F();
	static void rva007AD6B4();
	static void rva007AD6C9();
	static void rva007AD6DE();
	static void rva007AD703();
	static void rva007AD718();
	static void rva007AD72D();
	static void rva007AD742();
	static void rva007AD757();
	static void rva007AD76C();
	static void rva007AD781();
	static void rva007AD801();
	static void rva007AD816();
	static void rva007AD845();
	static void rva007AD85A();
	static void rva007AD86F();
	static void rva007AD884();
	static void rva007AD8B6();
	static void rva007AD8CB();
	static void rva007AD8FA();
	static void rva007AD939();
	static void rva007AD94E();
	static void rva007AD98D();
	static void rva007AD9E8();
	static void rva007AD9FD();
	static void rva007ADA12();
	static void rva007ADA27();
	static void rva007ADA4C();
	static void rva007ADA7B();
	static void rva007ADA90();
	static void rva007ADAD2();
	static void rva007ADB1D();
	static void rva007ADB4C();
	static void rva007ADB6D();
	static void rva007ADB92();
	static void rva007ADFCA();
	static void rva007ADFEF();
	static void rva007AE004();
	static void rva007AE15A();
	static void rva007AE16F();
	static void rva007AE489();
	static void rva007AE4AE();
	static void rva007AE7CA();
	static void rva007AE908();
	static void rva007AE963();
	static void rva007AFC11();
	static void rva007AFC56();
	static void rva007AFCB4();
	static void rva007AFCE3();
	static void rva007AFD4C();
	static void rva007AFD61();
	static void rva007AFE2E();
	static void rva007AFE97();
	static void rva007AFFBC();
	static void rva007AFFD1();
	static void rva007AFFE6();
	static void rva007AFFFB();
	static void rva007B0010();
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
	static void rva007B0383();
	static void rva007B03B2();
	static void rva007B058F();
	static void rva007B3A0D();
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
// ?rva007ACFD0@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007ACFD0 (21B): "AIData"
BLOCK_PARSE_INIT( rva007ACFD0, theAIDataBlockParse )
// ?rva007ACFF5@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007ACFF5 (21B): "Armor"
BLOCK_PARSE_INIT( rva007ACFF5, theArmorBlockParse )
// ?rva007AD024@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD024 (21B): "MusicTrack"
BLOCK_PARSE_INIT( rva007AD024, theMusicTrackBlockParse )
// ?rva007AD039@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD039 (21B): "AudioEvent"
BLOCK_PARSE_INIT( rva007AD039, theAudioEventBlockParse )
// ?rva007AD04E@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD04E (21B): "DialogEvent"
BLOCK_PARSE_INIT( rva007AD04E, theDialogEventBlockParse )
// ?rva007AD063@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD063 (21B): "AmbientStream"
BLOCK_PARSE_INIT( rva007AD063, theAmbientStreamBlockParse )
// ?rva007AD078@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD078 (21B): "StreamedSound"
BLOCK_PARSE_INIT( rva007AD078, theStreamedSoundBlockParse )
// ?rva007AD08D@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD08D (21B): "Multisound"
BLOCK_PARSE_INIT( rva007AD08D, theMultisoundBlockParse )
// ?rva007AD0A2@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD0A2 (21B): "Bridge"
BLOCK_PARSE_INIT( rva007AD0A2, theBridgeBlockParse )
// ?rva007AD0B7@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD0B7 (21B): "CommandButton"
BLOCK_PARSE_INIT( rva007AD0B7, theCommandButtonBlockParse )
// ?rva007AD0DC@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD0DC (21B): "CommandMap"
BLOCK_PARSE_INIT( rva007AD0DC, theCommandMapBlockParse )
// ?rva007AD0F1@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD0F1 (21B): "DebugCommandMap"
BLOCK_PARSE_INIT( rva007AD0F1, theDebugCommandMapBlockParse )
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
// ?rva007AD19E@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD19E (21B): "DrawGroupInfo"
BLOCK_PARSE_INIT( rva007AD19E, theDrawGroupInfoBlockParse )
// ?rva007AD1C3@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD1C3 (21B): "PredefinedEvaEvent"
BLOCK_PARSE_INIT( rva007AD1C3, thePredefinedEvaEventBlockParse )
// ?rva007AD1D8@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD1D8 (21B): "NewEvaEvent"
BLOCK_PARSE_INIT( rva007AD1D8, theNewEvaEventBlockParse )
// ?rva007AD1ED@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD1ED (21B): "EvaEventForwardReference"
BLOCK_PARSE_INIT( rva007AD1ED, theEvaEventForwardReferenceBlockParse )
// ?rva007AD202@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD202 (21B): "MiscEvaData"
BLOCK_PARSE_INIT( rva007AD202, theMiscEvaDataBlockParse )
// ?rva007AD241@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD241 (21B): "FXList"
BLOCK_PARSE_INIT( rva007AD241, theFXListBlockParse )
// ?rva007AD270@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD270 (21B): "GameData"
BLOCK_PARSE_INIT( rva007AD270, theGameDataBlockParse )
// ?rva007AD2EF@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD2EF (21B): "Locomotor"
BLOCK_PARSE_INIT( rva007AD2EF, theLocomotorBlockParse )
// ?rva007AD31E@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD31E (21B): "Language"
BLOCK_PARSE_INIT( rva007AD31E, theLanguageBlockParse )
// ?rva007AD333@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD333 (21B): "LinearCampaign"
BLOCK_PARSE_INIT( rva007AD333, theLinearCampaignBlockParse )
// ?rva007AD37C@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD37C (21B): "MappedImage"
BLOCK_PARSE_INIT( rva007AD37C, theMappedImageBlockParse )
// ?rva007AD391@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD391 (21B): "MiscAudio"
BLOCK_PARSE_INIT( rva007AD391, theMiscAudioBlockParse )
// ?rva007AD3B6@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD3B6 (21B): "MouseCursor"
BLOCK_PARSE_INIT( rva007AD3B6, theMouseCursorBlockParse )
// ?rva007AD3CB@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD3CB (21B): "Mouse"
BLOCK_PARSE_INIT( rva007AD3CB, theMouseBlockParse )
// ?rva007AD3FA@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD3FA (21B): "MultiplayerSettings"
BLOCK_PARSE_INIT( rva007AD3FA, theMultiplayerSettingsBlockParse )
// ?rva007AD40F@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD40F (21B): "MultiplayerColor"
BLOCK_PARSE_INIT( rva007AD40F, theMultiplayerColorBlockParse )
// ?rva007AD424@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD424 (21B): "OnlineChatColors"
BLOCK_PARSE_INIT( rva007AD424, theOnlineChatColorsBlockParse )
// ?rva007AD463@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD463 (21B): "Object"
BLOCK_PARSE_INIT( rva007AD463, theObjectBlockParse )
// ?rva007AD478@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD478 (21B): "ObjectReskin"
BLOCK_PARSE_INIT( rva007AD478, theObjectReskinBlockParse )
// ?rva007AD48D@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD48D (21B): "ChildObject"
BLOCK_PARSE_INIT( rva007AD48D, theChildObjectBlockParse )
// ?rva007AD4CC@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD4CC (21B): "ObjectCreationList"
BLOCK_PARSE_INIT( rva007AD4CC, theObjectCreationListBlockParse )
// ?rva007AD521@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD521 (21B): "FXParticleSystem"
BLOCK_PARSE_INIT( rva007AD521, theFXParticleSystemBlockParse )
// ?rva007AD550@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD550 (21B): "PlayerTemplate"
BLOCK_PARSE_INIT( rva007AD550, thePlayerTemplateBlockParse )
// ?rva007AD57F@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD57F (21B): "Road"
BLOCK_PARSE_INIT( rva007AD57F, theRoadBlockParse )
// ?rva007AD594@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD594 (21B): "Science"
BLOCK_PARSE_INIT( rva007AD594, theScienceBlockParse )
// ?rva007AD5DD@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD5DD (21B): "Rank"
BLOCK_PARSE_INIT( rva007AD5DD, theRankBlockParse )
// ?rva007AD60C@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD60C (21B): "SpecialPower"
BLOCK_PARSE_INIT( rva007AD60C, theSpecialPowerBlockParse )
// ?rva007AD621@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD621 (21B): "ShellMenuScheme"
BLOCK_PARSE_INIT( rva007AD621, theShellMenuSchemeBlockParse )
// ?rva007AD636@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD636 (21B): "Terrain"
BLOCK_PARSE_INIT( rva007AD636, theTerrainBlockParse )
// ?rva007AD64B@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD64B (21B): "WaterTextureList"
BLOCK_PARSE_INIT( rva007AD64B, theWaterTextureListBlockParse )
// ?rva007AD660@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD660 (21B): "Upgrade"
BLOCK_PARSE_INIT( rva007AD660, theUpgradeBlockParse )
// ?rva007AD675@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD675 (21B): "WaterSet"
BLOCK_PARSE_INIT( rva007AD675, theWaterSetBlockParse )
// ?rva007AD68A@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD68A (21B): "WaterTransparency"
BLOCK_PARSE_INIT( rva007AD68A, theWaterTransparencyBlockParse )
// ?rva007AD69F@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD69F (21B): "AerialPathfindNoFlyZone"
BLOCK_PARSE_INIT( rva007AD69F, theAerialPathfindNoFlyZoneBlockParse )
// ?rva007AD6B4@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD6B4 (21B): "Weather"
BLOCK_PARSE_INIT( rva007AD6B4, theWeatherBlockParse )
// ?rva007AD6C9@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD6C9 (21B): "Weapon"
BLOCK_PARSE_INIT( rva007AD6C9, theWeaponBlockParse )
// ?rva007AD6DE@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD6DE (21B): "HeaderTemplate"
BLOCK_PARSE_INIT( rva007AD6DE, theHeaderTemplateBlockParse )
// ?rva007AD703@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD703 (21B): "ReallyLowMHz"
BLOCK_PARSE_INIT( rva007AD703, theReallyLowMHzBlockParse )
// ?rva007AD718@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD718 (21B): "AudioLowMHz"
BLOCK_PARSE_INIT( rva007AD718, theAudioLowMHzBlockParse )
// ?rva007AD72D@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD72D (21B): "BenchProfile"
BLOCK_PARSE_INIT( rva007AD72D, theBenchProfileBlockParse )
// ?rva007AD742@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD742 (21B): "LODPreset"
BLOCK_PARSE_INIT( rva007AD742, theLODPresetBlockParse )
// ?rva007AD757@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD757 (21B): "StaticGameLOD"
BLOCK_PARSE_INIT( rva007AD757, theStaticGameLODBlockParse )
// ?rva007AD76C@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD76C (21B): "DynamicGameLOD"
BLOCK_PARSE_INIT( rva007AD76C, theDynamicGameLODBlockParse )
// ?rva007AD781@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD781 (21B): "AudioLOD"
BLOCK_PARSE_INIT( rva007AD781, theAudioLODBlockParse )
// ?rva007AD801@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD801 (21B): "ScriptAction"
BLOCK_PARSE_INIT( rva007AD801, theScriptActionBlockParse )
// ?rva007AD816@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD816 (21B): "ScriptCondition"
BLOCK_PARSE_INIT( rva007AD816, theScriptConditionBlockParse )
// ?rva007AD845@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD845 (21B): "SkyboxTextureSet"
BLOCK_PARSE_INIT( rva007AD845, theSkyboxTextureSetBlockParse )
// ?rva007AD85A@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD85A (21B): "GlowEffect"
BLOCK_PARSE_INIT( rva007AD85A, theGlowEffectBlockParse )
// ?rva007AD86F@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD86F (21B): "RingEffect"
BLOCK_PARSE_INIT( rva007AD86F, theRingEffectBlockParse )
// ?rva007AD884@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD884 (21B): "FireEffect"
BLOCK_PARSE_INIT( rva007AD884, theFireEffectBlockParse )
// ?rva007AD8B6@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD8B6 (21B): "LargeGroupAudioMap"
BLOCK_PARSE_INIT( rva007AD8B6, theLargeGroupAudioMapBlockParse )
// ?rva007AD8CB@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD8CB (21B): "LargeGroupAudioUnusedKnownKeys"
BLOCK_PARSE_INIT( rva007AD8CB, theLargeGroupAudioUnusedKnownKeysBlockParse )
// ?rva007AD8FA@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD8FA (21B): "LivingWorldRegionCampaign"
BLOCK_PARSE_INIT( rva007AD8FA, theLivingWorldRegionCampaignBlockParse )
// ?rva007AD939@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD939 (21B): "LivingWorldObject"
BLOCK_PARSE_INIT( rva007AD939, theLivingWorldObjectBlockParse )
// ?rva007AD94E@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD94E (21B): "LivingWorldMapInfo"
BLOCK_PARSE_INIT( rva007AD94E, theLivingWorldMapInfoBlockParse )
// ?rva007AD98D@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD98D (21B): "ModifierList"
BLOCK_PARSE_INIT( rva007AD98D, theModifierListBlockParse )
// ?rva007AD9E8@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD9E8 (21B): "CloudEffect"
BLOCK_PARSE_INIT( rva007AD9E8, theCloudEffectBlockParse )
// ?rva007AD9FD@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AD9FD (21B): "PlayerAIType"
BLOCK_PARSE_INIT( rva007AD9FD, thePlayerAITypeBlockParse )
// ?rva007ADA12@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007ADA12 (21B): "VictorySystemData"
BLOCK_PARSE_INIT( rva007ADA12, theVictorySystemDataBlockParse )
// ?rva007ADA27@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007ADA27 (21B): "FactionVictoryData"
BLOCK_PARSE_INIT( rva007ADA27, theFactionVictoryDataBlockParse )
// ?rva007ADA4C@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007ADA4C (21B): "BannerType"
BLOCK_PARSE_INIT( rva007ADA4C, theBannerTypeBlockParse )
// ?rva007ADA7B@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007ADA7B (21B): "FontDefaultSettings"
BLOCK_PARSE_INIT( rva007ADA7B, theFontDefaultSettingsBlockParse )
// ?rva007ADA90@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007ADA90 (21B): "FontSubstitution"
BLOCK_PARSE_INIT( rva007ADA90, theFontSubstitutionBlockParse )
// ?rva007ADAD2@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007ADAD2 (21B): "CreateAHeroSystem"
BLOCK_PARSE_INIT( rva007ADAD2, theCreateAHeroSystemBlockParse )
// ?rva007ADB1D@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007ADB1D (21B): "ArmySummaryDescription"
BLOCK_PARSE_INIT( rva007ADB1D, theArmySummaryDescriptionBlockParse )
// ?rva007ADB4C@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007ADB4C (21B): "StrategicHUD"
BLOCK_PARSE_INIT( rva007ADB4C, theStrategicHUDBlockParse )
// ?rva007ADB6D@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007ADB6D (21B): "InGameNotificationBox"
BLOCK_PARSE_INIT( rva007ADB6D, theInGameNotificationBoxBlockParse )
// ?rva007ADB92@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007ADB92 (21B): "AptButtonTooltipMap"
BLOCK_PARSE_INIT( rva007ADB92, theAptButtonTooltipMapBlockParse )
// ?rva007ADFCA@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007ADFCA (21B): "FireLogicSystem"
BLOCK_PARSE_INIT( rva007ADFCA, theFireLogicSystemBlockParse )
// ?rva007ADFEF@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007ADFEF (21B): "ExperienceLevel"
BLOCK_PARSE_INIT( rva007ADFEF, theExperienceLevelBlockParse )
// ?rva007AE004@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AE004 (21B): "ExperienceScalarTable"
BLOCK_PARSE_INIT( rva007AE004, theExperienceScalarTableBlockParse )
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
// ?rva007AE908@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AE908 (21B): "WeatherData"
BLOCK_PARSE_INIT( rva007AE908, theWeatherDataBlockParse )
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
// ?rva007AFE2E@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007AFE2E (21B): "AwardSystem"
BLOCK_PARSE_INIT( rva007AFE2E, theAwardSystemBlockParse )
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
// ?rva007B0010@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007B0010 (21B): "ScoredKillEvaAnnouncer"
BLOCK_PARSE_INIT( rva007B0010, theScoredKillEvaAnnouncerBlockParse )
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
// ?rva007B0383@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007B0383 (21B): "MissionObjectiveList"
BLOCK_PARSE_INIT( rva007B0383, theMissionObjectiveListBlockParse )
// ?rva007B03B2@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007B03B2 (21B): "AutoResolveArmor"
BLOCK_PARSE_INIT( rva007B03B2, theAutoResolveArmorBlockParse )
// ?rva007B058F@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007B058F (21B): "AnimationSoundClientBehaviorGlobalSetting"
BLOCK_PARSE_INIT( rva007B058F, theAnimationSoundClientBehaviorGlobalSettingBlockParse )
// ?rva007B3A0D@Rva007ABBF6BlockParseInits@@SAXXZ @ 0x007B3A0D (21B): "LivingWorldCampaign"
BLOCK_PARSE_INIT( rva007B3A0D, theLivingWorldCampaignBlockParse )
