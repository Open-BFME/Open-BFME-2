// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// Split from INIBfmeBlockParsers.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
// BFME 2 INI block parsers that are reached only through the block-parse
// registrations (Rva007ABBF6BlockParseInits.cpp lists each token with its
// parse address), so Ghidra never started a function at any of them and they
// sat as unclaimed bytes between rowed neighbours. Each is the small
// "initFromINI the subsystem singleton against its field table" shape of
// Zero Hour's INI::parse*Definition. The tokens are target facts read from the
// registrations; the original function names are not known, so the bodies keep
// address names, and the singletons and tables use the data ledger's names
// where it has one.
#include "ascii_string.h"

typedef int Int;
typedef bool Bool;

class INI;
typedef void (*FieldParseProc)(INI *ini, void *instance, void *store, const void *userData);
#include "../../../Include/Common/INI/FieldParse.h"

#include "../../../Include/Common/INI/INI.h"

// 0x00215C38 (16B): "PlayerAIType" (registration VA 0x00DB9B74). Forwards the
// INI to ThePlayerAITypeSet (0x00DFE31C) through its unrowed member 0x00215B14
// (thiscall, ret 4, builds a 0x24-byte entry on the stack).
class PlayerAITypeSet
{
public:
	void rva00215B14(INI *ini);
};

extern PlayerAITypeSet *ThePlayerAITypeSet;

void parsePlayerAITypeDefinition(INI *ini)
{
	ThePlayerAITypeSet->rva00215B14(ini);
}

// 0x00221012 (21B): "ArmySummaryDescription" (registration VA 0x00DBA184).
// No null check: initFromINI the object at 0x00DFE490 against VA 0x00BE6B2C.
extern void *g_00DFE490;
extern const FieldParse ArmySummaryDescriptionFields[];

void parseArmySummaryDescriptionDefinition(INI *ini)
{
	ini->initFromINI(g_00DFE490, ArmySummaryDescriptionFields);
}

// 0x0022232E (21B): "InGameNotificationBox" (registration VA 0x00DBA19C).
// No null check: initFromINI the object at 0x00DFE4C4 against VA 0x00BE6CE0.
// The notification-type holder at 0x009FE4C4 (defined in Rva002220DCInit.cpp,
// the data ledger's name for it); its first word is the store pointer.
class Rva00575674;
extern Rva00575674 g_00DFE4C4;
extern const FieldParse InGameNotificationBoxFields[];

void parseInGameNotificationBoxDefinition(INI *ini)
{
	ini->initFromINI(*(void **)&g_00DFE4C4, InGameNotificationBoxFields);
}

// 0x002859A8 (25B): "FireLogicSystem" (registration VA 0x00DBB758). Skips
// when the singleton at 0x00DFEC68 is null, else initFromINI it against
// VA 0x00BFB620.
class Rva002872BA;
extern Rva002872BA *TheTriggerManager;
extern const FieldParse FireLogicSystemFields[];

void parseFireLogicSystemDefinition(INI *ini)
{
	if (TheTriggerManager)
		ini->initFromINI(TheTriggerManager, FireLogicSystemFields);
}

// 0x002A8A31 (24B): "SkirmishAIData" (registration VA 0x00DBBC28). No null
// check: initFromINI the +0x10 member of the singleton at 0x00DFEEF8 against
// VA 0x00BFDA50.
#include "../../../Include/GameLogic/Rva002A8F24.h"

extern Rva002A8F24 *TheSkirmishAIManager;
extern const FieldParse SkirmishAIDataFields[];

void parseSkirmishAIDataDefinition(INI *ini)
{
	ini->initFromINI(TheSkirmishAIManager->m_pad10, SkirmishAIDataFields);
}

// 0x00210F64 (40B): "LivingWorldMapInfo" (registration VA 0x00DB9A2C). Skips
// without TheLivingWorldManager, else initFromINI its +0x14 member against
// VA 0x00BE4560 and sets the +0x1C4 flag.
class LivingWorldManager
{
public:
	char m_unreconstructed_00[0x14];
	char m_mapInfo[0x1B0];
	Bool m_mapInfoParsed;
};

extern LivingWorldManager *TheLivingWorldManager;
extern const FieldParse LivingWorldMapInfoFields[];

void parseLivingWorldMapInfoDefinition(INI *ini)
{
	if (TheLivingWorldManager)
	{
		ini->initFromINI(TheLivingWorldManager->m_mapInfo, LivingWorldMapInfoFields);
		TheLivingWorldManager->m_mapInfoParsed = true;
	}
}

// 0x00417A94 (36B): "HouseColor" (registration VA 0x00DC822C). Skips without
// TheHouseColorSystem (0x00E030A0), else initFromINI it against VA 0x00C3A600
// and tail-calls its no-argument member 0x00417A6B.
// 0x00417A6B (41B), the HouseColor parser's tail callee: hands the C strings
// of the +0x10 and +0x0C AsciiStrings (empty string 0x00BBAC1C when unset)
// to the unrowed cdecl 0x00136B5E, which null-checks both arguments.
void Rva00136B5E(const char *first, const char *second);

class HouseColorSystem
{
public:
	void rva00417A6B();

private:
	char m_unreconstructed_00[0x0C];
	AsciiString m_0c;
	AsciiString m_10;
};


extern HouseColorSystem *TheHouseColorSystem;
extern const FieldParse HouseColorFields[];

void parseHouseColorDefinition(INI *ini)
{
	if (TheHouseColorSystem)
	{
		ini->initFromINI(TheHouseColorSystem, HouseColorFields);
		TheHouseColorSystem->rva00417A6B();
	}
}

// 0x00289265 (136B): "ExperienceScalarTable" (registration VA 0x00DBB898).
// Skips without TheExperienceLevelSystem (0x00DFECC4), else reads the table
// name with getNextToken(0), news a 0x10-byte table through its rowed
// constructor 0x00288BBA, initFromINI's it against VA 0x00BFB820 and hands
// it to the system through the rowed forwarder 0x00289218 (the same
// forwarder LivingWorldCampaign's parser uses).
class ModuleData;

#include "../../../Include/Common/Rva00289218.h"

class Rva00288BBA
{
public:
	Rva00288BBA(const AsciiString &name);

private:
	char m_unreconstructed_00[0x10];
};

class ExperienceLevelSystem;
extern ExperienceLevelSystem *TheExperienceLevelSystem;
extern const FieldParse ExperienceScalarTableFields[];

void parseExperienceScalarTableDefinition(INI *ini)
{
	if (TheExperienceLevelSystem == 0)
		return;

	AsciiString name(ini->getNextToken(0));
	Rva00288BBA *table = new Rva00288BBA(name);
	ini->initFromINI(table, ExperienceScalarTableFields);
	((Rva00289218 *)TheExperienceLevelSystem)->rva00289218((const ModuleData *)table);
}

// 0x00200FE3 (129B): "AerialPathfindNoFlyZone" (registration VA 0x00DB9558).
// Reads "TriggerArea" and looks the area up through TheTerrainLogic's
// virtual at +0x9C (by const reference), reads "Height" with scanReal, and
// when the area exists hands it and the height to TheAerialPathfinder through
// the rowed 0x00375BFF (unsigned int, float).
class PolygonTrigger;

#include "../../../Include/GameLogic/TerrainLogic.h"

class AerialPathfinder;
extern TerrainLogic *TheTerrainLogic;
extern AerialPathfinder *TheAerialPathfinder;
void parseAerialPathfindNoFlyZoneDefinition(INI *ini);


// 0x0040C32B (25B): "AwardSystem" (registration VA 0x00DC1D9C). Skips when
// the object at 0x00E02F74 is null, else initFromINI it against VA 0x00C39410.
class Rva0040AAD5;
extern Rva0040AAD5 *TheAwardSystemManager;
extern const FieldParse AwardSystemFields[];

void parseAwardSystemDefinition(INI *ini)
{
	if (TheAwardSystemManager)
		ini->initFromINI(TheAwardSystemManager, AwardSystemFields);
}

// 0x0040F0F0 (31B): "LivingWorldPlayerArmy" (registration VA 0x00DC1F68).
// Skips without TheCampaignManager (0x00E02D6C), else initFromINI the entry
// its rowed member 0x003B93BC returns against VA 0x00C39538.
struct BfmePod104;

class Rva003B93BC
{
public:
	BfmePod104 *rva003B93BC();
};

class Rva00E02D6C;
extern Rva00E02D6C *TheCampaignManager;
extern const FieldParse LivingWorldPlayerArmyFields[];

void parseLivingWorldPlayerArmyDefinition(INI *ini)
{
	if (TheCampaignManager)
	{
		BfmePod104 *army = ((Rva003B93BC *)TheCampaignManager)->rva003B93BC();
		ini->initFromINI(army, LivingWorldPlayerArmyFields);
	}
}

// The field tables these parsers hand initFromINI (retail .rdata, decoded from
// the image): keyword strings, rowed callbacks and offsets, each closed by a
// null entry except SkirmishAIDataFields, whose 19 entries run straight into
// a float literal in retail. Callbacks with other signatures are cast to the
// field-parse type.
void Rva00285FA9Parse(INI *ini, void *instance, void *store, const void *userData);
void iniParseObjectFilter(INI *ini, void *instance, void *store, const void *userData);
namespace _STL
{
template <class T> class allocator;
template <class T, class A> class vector;
}
struct BfmeStringRecord0022074B;
void Rva00220FC4Parse(INI *ini, void *instance,
	_STL::vector<BfmeStringRecord0022074B, _STL::allocator<BfmeStringRecord0022074B> > *store);
void parseObjectAwardDefinition(INI *ini);
void Rva00222278Parse(INI *ini, void *instance);
void parseEyeTowerDefinition(INI *ini);
class AwardSystemManager
{
public:
	static void parseThingStat(INI *ini, void *instance, void *store, const void *userData);
};
#include "../../../Include/GameLogic/ArmySummary.h"

// retail .rdata 0x007E6B2C (2 entries + terminator)
extern const FieldParse ArmySummaryDescriptionFields[] =
{
	{ "HeroFilter", iniParseObjectFilter, 0, 0xC },
	{ "UnitCategory", (FieldParseProc)Rva00220FC4Parse, 0, 0x10 },
	{ 0, 0, 0, 0 }
};

// retail .rdata 0x007E6CE0 (4 entries + terminator)
extern const FieldParse InGameNotificationBoxFields[] =
{
	{ "DefaultOpenAudio", INI::Rva00221714_ParseDefaultOpenAudio, 0, 0x0 },
	{ "DefaultMessageFont", INI::Rva0022175F_ParseDefaultMessageFont, 0, 0x0 },
	{ "DefaultMessageColor", INI::Rva002216A6_ParseDefaultMessageColor, 0, 0x0 },
	{ "NotificationType", (FieldParseProc)Rva00222278Parse, 0, 0x0 },
	{ 0, 0, 0, 0 }
};

// retail .rdata 0x007FB620 (3 entries + terminator)
extern const FieldParse FireLogicSystemFields[] =
{
	{ "MaxCellsBurning", INI::parseInt, 0, 0x90 },
	{ "FuelRegenerationRate", INI::parseInt, 0, 0x94 },
	{ "TerrainCellType", Rva00285FA9Parse, 0, 0x0 },
	{ 0, 0, 0, 0 }
};

// retail .rdata 0x007FDA50 (19 entries, no terminator)
extern const FieldParse SkirmishAIDataFields[] =
{
	{ "CombatChainDefinition", INI::Rva002A8945_ParseCombatChainDefinition, 0, 0x0 },
	{ "BrutalDifficultyCheats", INI::Rva002A898A_ParseBrutalDifficultyCheats, 0, 0x0 },
	{ "DifficultyTuning", INI::Rva002A89D2_ParseDifficultyTuning, 0, 0x0 },
	{ "DisableBaseBuilding", INI::parseBool, 0, 0x848 },
	{ "DisableEconomyBuilding", INI::parseBool, 0, 0x849 },
	{ "DisableUnitBuilding", INI::parseBool, 0, 0x84A },
	{ "DisableScienceUpgrading", INI::parseBool, 0, 0x84B },
	{ "DisableUnitUpgrading", INI::parseBool, 0, 0x84C },
	{ "DisableTacticalAI", INI::parseBool, 0, 0x84D },
	{ "DisableTeamBuilding", INI::parseBool, 0, 0x84E },
	{ "DisableWallBuilding", INI::parseBool, 0, 0x84F },
	{ "MakeAllSkirmishSidesAIControlled", INI::parseBool, 0, 0x850 },
	{ "AnyTypeTemplateDisabledSlots", INI::Rva004E8EFF_ParseDisabledSlots, 0, 0x854 },
	{ "TeamIdleCheckRadius", INI::parseReal, 0, 0x860 },
	{ "TeamTimeUntilConsideredIdle", INI::parseReal, 0, 0x864 },
	{ "DefenseTreeNodeRadius", INI::parseReal, 0, 0x868 },
	{ "TimeBetweenEnemyChangeLO", INI::parseReal, 0, 0x86C },
	{ "TimeBetweenEnemyChangeHI", INI::parseReal, 0, 0x870 },
	{ "DefaultTargetThreatRadius", INI::parseReal, 0, 0x874 },
};

// retail .rdata 0x007E4560 (90 entries + terminator)
extern const FieldParse LivingWorldMapInfoFields[] =
{
	{ "MapObject", INI::parseAsciiString, 0, 0x0 },
	{ "NumWorldTiles", INI::parseInt, 0, 0x4 },
	{ "CloudBorderSubObject", INI::parseAsciiString, 0, 0x180 },
	{ "TextLayerSubObject", INI::parseAsciiString, 0, 0x184 },
	{ "Center", INI::parseCoord2D, 0, 0x8 },
	{ "Extent", INI::parseCoord2D, 0, 0x10 },
	{ "AptCenter", INI::parseCoord2D, 0, 0x18 },
	{ "AptZoom", INI::parseReal, 0, 0x20 },
	{ "AptPitch", INI::parseReal, 0, 0x24 },
	{ "EmbersPartSys", INI::parseAsciiString, 0, 0x34 },
	{ "CloudPos", INI::parseCoord3D, 0, 0x28 },
	{ "Ambient", INI::parseRGBColor, 0, 0x38 },
	{ "SunDir", INI::parseCoord2D, 0, 0x44 },
	{ "SunRGB", INI::parseRGBColor, 0, 0x4C },
	{ "Accent1Dir", INI::parseCoord2D, 0, 0x58 },
	{ "Accent1RGB", INI::parseRGBColor, 0, 0x60 },
	{ "Accent2Dir", INI::parseCoord2D, 0, 0x6C },
	{ "Accent2RGB", INI::parseRGBColor, 0, 0x74 },
	{ "MenBanner", INI::parseAsciiString, 0, 0x80 },
	{ "ElvesBanner", INI::parseAsciiString, 0, 0x84 },
	{ "DwarvesBanner", INI::parseAsciiString, 0, 0x88 },
	{ "IsengardBanner", INI::parseAsciiString, 0, 0x8C },
	{ "MordorBanner", INI::parseAsciiString, 0, 0x90 },
	{ "WildBanner", INI::parseAsciiString, 0, 0x94 },
	{ "NeutralBanner", INI::parseAsciiString, 0, 0x98 },
	{ "MenAnts", INI::parseAsciiString, 0, 0x9C },
	{ "ElvesAnts", INI::parseAsciiString, 0, 0xA0 },
	{ "DwarvesAnts", INI::parseAsciiString, 0, 0xA4 },
	{ "IsengardAnts", INI::parseAsciiString, 0, 0xA8 },
	{ "MordorAnts", INI::parseAsciiString, 0, 0xAC },
	{ "WildAnts", INI::parseAsciiString, 0, 0xB0 },
	{ "NeutralAnts", INI::parseAsciiString, 0, 0xB4 },
	{ "BattleMarker", INI::parseAsciiString, 0, 0xB8 },
	{ "PalantirMarker", INI::parseAsciiString, 0, 0xBC },
	{ "RegionAwardDisputeMarker", INI::parseAsciiString, 0, 0xC0 },
	{ "BattleMarkerCreatedSound", INI::parseAudioEventRTS, 0, 0x14C },
	{ "EnterMapSound", INI::parseAudioEventRTS, 0, 0x150 },
	{ "BannerScaleSpeed", INI::parseReal, 0, 0xC4 },
	{ "BannerMaxScale", INI::parseReal, 0, 0xC8 },
	{ "BannerTiltAngle", INI::parseReal, 0, 0xCC },
	{ "BannerHeight", INI::parseReal, 0, 0xD0 },
	{ "ArmyHeight", INI::parseReal, 0, 0xD4 },
	{ "BeaconHeight", INI::parseReal, 0, 0xD8 },
	{ "HeroArmyIconDiameter", INI::parseReal, 0, 0xE0 },
	{ "NumPointsPerArmyLine", INI::parseUnsignedInt, 0, 0xE4 },
	{ "ArmyLineHeightBias", INI::parseReal, 0, 0xE8 },
	{ "ArmyLineWidth", INI::parseReal, 0, 0xEC },
	{ "ArmyLineColorAttacking", INI::parseRGBColor, 0, 0xF0 },
	{ "ArmyLineColorNeutral", INI::parseRGBColor, 0, 0xFC },
	{ "ArmyLineColorAllied", INI::parseRGBColor, 0, 0x108 },
	{ "ArmyLineTextureName", INI::parseAsciiString, 0, 0x114 },
	{ "AnimRays", INI::parseAsciiString, 0, 0x118 },
	{ "AnimRaysPartSys", INI::parseAsciiString, 0, 0x11C },
	{ "AnimRaysPartSysOffset", INI::parseCoord3D, 0, 0x120 },
	{ "AnimRaysColor", INI::parseRGBColor, 0, 0x12C },
	{ "AnimRaysColorScale", INI::parseReal, 0, 0x138 },
	{ "AnimRaysEffectShells", INI::parseInt, 0, 0x13C },
	{ "AnimRaysEffectDiameter", INI::parseInt, 0, 0x140 },
	{ "AnimRaysEffectLifetime", INI::parseInt, 0, 0x144 },
	{ "AnimRaysCreateSound", INI::parseAudioEventRTS, 0, 0x148 },
	{ "AnimCloud", INI::parseAsciiString, 0, 0x154 },
	{ "AnimCloudPartSys", INI::parseAsciiString, 0, 0x158 },
	{ "NumAnimClouds", INI::parseInt, 0, 0x15C },
	{ "AnimCloudLifetime", INI::parseInt, 0, 0x178 },
	{ "AnimCloudRegionMin", INI::parseCoord3D, 0, 0x160 },
	{ "AnimCloudRegionMax", INI::parseCoord3D, 0, 0x16C },
	{ "MordorCloud", INI::parseAsciiString, 0, 0x17C },
	{ "CloudGrowthPos", INI::parseCoord3D, 0, 0x194 },
	{ "CloudGrowthRate", INI::parseInt, 0, 0x1A0 },
	{ "CloudInitialSize", INI::parseReal, 0, 0x1A4 },
	{ "CloudGrowthSize", INI::parseReal, 0, 0x1AC },
	{ "CloudInitialOpacity", INI::parseReal, 0, 0x1A8 },
	{ "CameraBoundX", INI::parseReal, 0, 0x1B4 },
	{ "CameraBoundY", INI::parseReal, 0, 0x1B8 },
	{ "ClickScrollThreshold", INI::parseInt, 0, 0x1CC },
	{ "MouseWheelZoomPerTick", INI::parseReal, 0, 0x1BC },
	{ "MouseWheelZoomDampenFactor", INI::parseReal, 0, 0x1C0 },
	{ "AutoScrollSpeed", INI::parseReal, 0, 0x1C4 },
	{ "MaxAutoScrollTime", INI::parseReal, 0, 0x1C8 },
	{ "ShadowColor", INI::parseColorInt, 0, 0x1D0 },
	{ "EnableMapShadows", INI::parseBool, 0, 0x1EC },
	{ "AddShadowSubObject", INI::parseAsciiStringVectorAppend, 0, 0x188 },
	{ "DefaultArmyMoveSpeed", INI::parseReal, 0, 0xDC },
	{ "ArmySelectedFadeInStart", INI::parseInt, 0, 0x1D4 },
	{ "ArmySelectedFadeInEnd", INI::parseInt, 0, 0x1D8 },
	{ "ArmySelectedFadeOutStart", INI::parseInt, 0, 0x1DC },
	{ "ArmySelectedFadeOutEnd", INI::parseInt, 0, 0x1E0 },
	{ "ArmyHilightedFadeInTime", INI::parseInt, 0, 0x1E4 },
	{ "ArmyHilightedFadeOutTime", INI::parseInt, 0, 0x1E8 },
	{ "EyeTower", (FieldParseProc)parseEyeTowerDefinition, 0, 0x0 },
	{ 0, 0, 0, 0 }
};

// retail .rdata 0x0083A600 (2 entries + terminator)
extern const FieldParse HouseColorFields[] =
{
	{ "BaseTexture", INI::parseAsciiString, 0, 0x10 },
	{ "HouseTexture", INI::parseAsciiString, 0, 0xC },
	{ 0, 0, 0, 0 }
};

// retail .rdata 0x007FB820 (1 entry + terminator)
extern const FieldParse ExperienceScalarTableFields[] =
{
	{ "Scalars", INI::Rva00289228_ParseRealList, 0, 0x0 },
	{ 0, 0, 0, 0 }
};

// retail .rdata 0x00839410 (2 entries + terminator)
extern const FieldParse AwardSystemFields[] =
{
	{ "ObjectAward", (FieldParseProc)parseObjectAwardDefinition, 0, 0x0 },
	{ "ThingStat", AwardSystemManager::parseThingStat, 0, 0x0 },
	{ 0, 0, 0, 0 }
};

// retail .rdata 0x00839538 (6 entries + terminator)
extern const FieldParse LivingWorldPlayerArmyFields[] =
{
	{ "Name", INI::parseAsciiString, 0, 0x18 },
	{ "DisplayNameTag", INI::parseAsciiString, 0, 0x64 },
	{ "Color", INI::parseRGBColor, 0, 0x24 },
	{ "NightColor", INI::parseRGBColor, 0, 0x28 },
	{ "ArmyEntry", ArmySummary::parseArmyEntry, 0, 0x0 },
	{ "SurvivalThreshhold", INI::parseInt, 0, 0x60 },
	{ 0, 0, 0, 0 }
};
