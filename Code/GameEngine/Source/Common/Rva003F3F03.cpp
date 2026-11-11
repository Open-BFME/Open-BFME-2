// cl: /O1 /MD
//
// ?rva003F3F03@Rva003F3F03@@QAEXPAVINI@@@Z @0x003F3F03 36B.
// INI-load tail: run the rowed INI::initFromINI at 0x002DE78 over this with
// the FieldParse table at 0x00C36560 (defined below), then run the two
// unclaimed no-arg members at 0x003F2F24 and 0x003F3B4F (range-19 target).
// Evidence: retail push esi / mov esi,ecx / mov ecx,[esp+8] /
// push &Rva003F3F03Table / push esi / call 0x002DE78 / mov ecx,esi /
// call 0x003F2F24 / mov ecx,esi / call 0x003F3B4F / pop esi / ret 4.
class INI;
typedef void (*FieldParseProc)(INI *ini, void *instance, void *store, const void *userData);
#include "../../Include/Common/INI/FieldParse.h"

#include "../../Include/Common/INI/INI.h"

// The callbacks of the table below, all rowed; two have other signatures and
// are cast to the field-parse type.
void parseConnection(INI *ini, void *instance, void *store, const void *userData);
void Rva003F25DF(void *ini, void *instance, void *store, void *userData);
#include "../../Include/GameLogic/LivingWorldRegion.h"

// The field table this unit hands initFromINI: 49 keywords (MapName ..
// FortressDisplayDescription) with retail's callbacks and offsets, then the
// null entry.
extern const FieldParse Rva003F3F03Table[] =
{
	{ "MapName", INI::parseAsciiString, 0, 0x18 },
	{ "MapMatchPlayerWorldToMap", (FieldParseProc)Rva003F25DF, 0, 0x1C },
	{ "DelayCarryoverSpawningOf", INI::parseAsciiStringVectorAppend, 0, 0x28 },
	{ "DisplayName", INI::parseAsciiString, 0, 0x38 },
	{ "DisplayDescription", INI::parseAsciiString, 0, 0x3C },
	{ "ConqueredNotice", INI::parseAsciiString, 0, 0x34 },
	{ "MovieNameFirstTime", INI::parseAsciiString, 0, 0x40 },
	{ "MovieNameRepeat", INI::parseAsciiString, 0, 0x44 },
	{ "SkirmishStillImage", INI::parseAsciiString, 0, 0x48 },
	{ "SkirmishVoiceTrack", INI::parseAudioEventRTS, 0, 0x4C },
	{ "SkirmishMusicTrack", INI::parseAudioEventRTS, 0, 0x50 },
	{ "SubObject", INI::parseAsciiString, 0, 0x54 },
	{ "StrategicValue", INI::parseInt, 0, 0x58 },
	{ "RegionBonus", INI::Rva003F156F_ParseRegionBonus, 0, 0x5C },
	{ "ConnectsTo", INI::Rva003F341E_ParseConnections, 0, 0x60 },
	{ "Connection", parseConnection, 0, 0x60 },
	{ "OnWinActSubroutine", INI::parseAsciiString, 0, 0x6C },
	{ "RegionPortrait", INI::parseAsciiString, 0, 0x70 },
	{ "ArmyPlacementPos", INI::Rva002F592_ParseArmyPlacementPos, 0, 0x74 },
	{ "UnpackCamps", INI::parseBool, 0, 0x88 },
	{ "CustomCenterPoint", INI::parseBool, 0, 0x89 },
	{ "CenterPoint", INI::parseCoord2D, 0, 0x80 },
	{ "ArmyBonus", INI::parseInt, 0, 0x94 },
	{ "LegendaryBonus", INI::parseInt, 0, 0x98 },
	{ "ResourceBonus", INI::parseInt, 0, 0x90 },
	{ "AttackBonus", INI::parseInt, 0, 0x9C },
	{ "DefenseBonus", INI::parseInt, 0, 0xA0 },
	{ "ExperienceBonus", INI::parseInt, 0, 0xA4 },
	{ "EndOfCampaign", INI::parseBool, 0, 0xA8 },
	{ "MapIsCampaignMap", INI::parseBool, 0, 0xA9 },
	{ "LoseCampaignIfLoseMap", INI::parseBool, 0, 0xAA },
	{ "DisplayActNum", INI::parseInt, 0, 0xAC },
	{ "CustomUIPopupPoint", INI::parseBool, 0, 0xAB },
	{ "UIPopupPoint", INI::parseCoord2D, 0, 0xB0 },
	{ "DifficultyText", INI::parseAsciiString, 0, 0xB8 },
	{ "OnEnterGiveUpgrade", INI::Rva003F1FD0_ParseGiveUpgrade, 0, 0xBC },
	{ "OnVictoryGiveUpgrade", INI::Rva003F2033_ParseOnVictoryGiveUpgrade, 0, 0xC8 },
	{ "OnVictoryRemoveUpgrade", INI::Rva003F1FD0_ParseGiveUpgrade, 0, 0xD4 },
	{ "OwnedByPlayer", INI::parseAsciiString, 0, 0xE0 },
	{ "HeroArmySpot", INI::Rva002F592_ParseArmyPlacementPos, 0, 0xE4 },
	{ "GarrisonArmySpot", INI::Rva002F592_ParseArmyPlacementPos, 0, 0xF0 },
	{ "BuildingSpot", INI::Rva002F592_ParseArmyPlacementPos, 0, 0xFC },
	{ "CPLimit", INI::parseInt, 0, 0x108 },
	{ "AllyCPLimit", INI::parseInt, 0, 0x10C },
	{ "RestrictBuildings", (FieldParseProc)LivingWorldRegion::ModuleData::BuildingRestriction::ParseINI, 0, 0x0 },
	{ "CreateAutoFort", INI::parseBool, 0, 0x11C },
	{ "FortressPortrait", INI::parseAsciiString, 0, 0x120 },
	{ "FortressDisplayName", INI::parseAsciiString, 0, 0x124 },
	{ "FortressDisplayDescription", INI::parseAsciiString, 0, 0x128 },
	{ 0, 0, 0, 0 }
};

#include "../../Include/Common/Rva003F3F27.h"
class Rva003F3F03
{
public:
	void rva003F3F03(INI *ini);
	void rva003F2F24();
	/* the rowed Rva003F3F27::rva003F3B4F */ __declspec(dllimport) __forceinline void rva003F3B4F() { ((Rva003F3F27 *)this)->rva003F3B4F(); }
};

void Rva003F3F03::rva003F3F03(INI *ini)
{
	ini->initFromINI(this, Rva003F3F03Table);
	rva003F2F24();
	rva003F3B4F();
}
