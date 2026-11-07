// cl: /DNDEBUG /MD
//
// SpecialPower-side ModuleData::buildFieldParse procs.
//
// ?buildFieldParse@SpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x00493207 (17 bytes): the shared SpecialPower base table at
// (unsigned int)&g_00C4E628 (SpecialPowerTemplate, UpdateModuleStartsAttack, StartsPaused,
// InitiateSound, ReEnableAntiCategory, AntiCategory, AntiFX,
// AttributeModifier and siblings). Twenty-one same-family ModuleData procs
// (0x4C238D through 0x4C89CF, including Devastate below) open with
// push dword ptr [esp+4] + call here, proving the base identity; the table
// prefix matches the in-tree SpecialPowerModuleData declaration field for
// field. Registered with MultiIniFieldParse::add (rowed at 0x2BC6E).

class MultiIniFieldParse;

struct FieldParse;
extern const int g_emptyFieldParseTable[4];

#include "../../../../Include/Common/INI/FieldParse.h"

#include "../../../../Include/Common/INI/INI.h"

// The FieldParse tables of the procs below, read from retail: every token, parser,
// userData and offset is retail's. They were 1-byte zero placeholders, so in a
// linked game each special power's INI block met an empty table. The parsers are
// the matched rows at retail's pointers.
void Rva003393DFParse(INI *ini, void *instance, void *store, const void *userData);
void iniParseObjectFilter(INI *ini, void *instance, void *store, const void *userData);
void Rva00492F6AParse(INI *ini, void *instance, void *store, const void *userData);
void Rva002C8C06Parse(INI *ini, void *instance, void *store, const void *userData);
void Rva002567EAParse(INI *ini, void *instance, void *store, const void *userData);
void Rva00438176Parse(INI *ini, void *instance, void *store, const void *userData);
void Rva004C7E09_ParseUpgradeName(INI *ini, void *instance, void *store, const void *userData);
extern "C" {
void __identifier("?parseFromINI@Rva0049B8A0@@SAXPAVINI@@PAX1PBX@Z")();
}
extern const char *TheOCLCreateLocTypeNames[];

// Retail VA 0x00C4E628: 35 fields and the zero sentinel.
extern const FieldParse g_00C4E628[] = {
	{ "SpecialPowerTemplate", &INI::parseSpecialPowerTemplate, 0, 0x8 },
	{ "UpdateModuleStartsAttack", &INI::parseBool, 0, 0xC },
	{ "StartsPaused", &INI::parseBool, 0, 0xD },
	{ "InitiateSound", &Rva003393DFParse, 0, 0x10 },
	{ "ReEnableAntiCategory", &INI::parseBool, 0, 0x42 },
	{ "AntiCategory", (INIFieldParseProc)&__identifier("?parseFromINI@Rva0049B8A0@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x34 },
	{ "AntiFX", &INI::parseFXList, 0, 0x4C },
	{ "AttributeModifier", &INI::parseAsciiString, 0, 0x18 },
	{ "AttributeModifierRange", &INI::parseReal, 0, 0x1C },
	{ "AttributeModifierAffectsSelf", &INI::parseBool, 0, 0x20 },
	{ "AttributeModifierAffects", &iniParseObjectFilter, 0, 0x24 },
	{ "AttributeModifierFX", &INI::parseFXList, 0, 0x28 },
	{ "AttributeModifierWeatherBased", &INI::parseBool, 0, 0x2C },
	{ "WeatherDuration", &INI::parseDurationUnsignedInt, 0, 0x30 },
	{ "RequirementsFilterMPSkirmish", &iniParseObjectFilter, 0, 0x38 },
	{ "RequirementsFilterStrategic", &iniParseObjectFilter, 0, 0x3C },
	{ "TargetEnemy", &INI::parseBool, 0, 0x40 },
	{ "TargetAllSides", &INI::parseBool, 0, 0x41 },
	{ "InitiateFX", &INI::parseFXList, 0, 0x44 },
	{ "TriggerFX", &INI::parseFXList, 0, 0x48 },
	{ "SetModelCondition", &INI::iniParseAnim, 0, 0x50 },
	{ "SetModelConditionTime", &INI::parseReal, 0, 0x54 },
	{ "GiveLevels", &INI::parseInt, 0, 0x58 },
	{ "DisableDuringAnimDuration", &INI::parseBool, 0, 0x5C },
	{ "IdleWhenStartingPower", &INI::parseBool, 0, 0x5D },
	{ "AffectGood", &INI::parseBool, 0, 0x5E },
	{ "AffectEvil", &INI::parseBool, 0, 0x5F },
	{ "AffectAllies", &INI::parseBool, 0, 0x60 },
	{ "AvailableAtStart", &INI::parseBool, 0, 0x61 },
	{ "ChangeWeather", &Rva00492F6AParse, 0, 0x64 },
	{ "AdjustVictim", &INI::parseBool, 0, 0x68 },
	{ "OnTriggerRechargeSpecialPower", &INI::parseAsciiString, 0, 0x6C },
	{ "BurnDecayModifier", &INI::parseUnsignedInt, 0, 0x70 },
	{ "UseDistanceFromCommandCenter", &INI::parseBool, 0, 0x74 },
	{ "DistanceFromCommandCenter", &INI::parseReal, 0, 0x78 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C5E3D0: 5 fields and the zero sentinel.
extern const FieldParse g_00C5E3D0[] = {
	{ "Radius", &INI::parseReal, 0, 0x7C },
	{ "FX", &INI::parseFXList, 0, 0x80 },
	{ "TreeValueMultiplier", &INI::parsePercentToReal, 0, 0x84 },
	{ "TreeValueTotalCap", &INI::parseReal, 0, 0x88 },
	{ "FireWeapon", &INI::parseAsciiString, 0, 0x8C },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C5C724: 2 fields and the zero sentinel.
extern const FieldParse g_00C5C724[] = {
	{ "UpgradeMoneyAmount", &INI::Rva004C2918_ParseUpgradeMoneyAmount, 0, 0x7C },
	{ "MoneyAmount", &INI::parseInt, 0, 0x88 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C5D018: 6 fields and the zero sentinel.
extern const FieldParse g_00C5D018[] = {
	{ "ElvenGroveObject", &INI::parseAsciiString, 0, 0x88 },
	{ "ElvenNumObjects", &INI::parseInt, 0, 0x8C },
	{ "ElvenWoodObject", &INI::Rva004C3F48_ParseNamedReal, 0, 0x0 },
	{ "ElvenWoodRadius", &INI::parseReal, 0, 0x90 },
	{ "ElvenWoodFX", &INI::parseFXList, 0, 0x94 },
	{ "ElvenWoodOCL", &INI::parseObjectCreationList, 0, 0x98 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C5D0F0: 5 fields and the zero sentinel.
extern const FieldParse g_00C5D0F0[] = {
	{ "FlagsUsedForToggle", &Rva002C8C06Parse, 0, 0x7C },
	{ "ToggleOnSleepFrames", &INI::parseInt, 0, 0x8C },
	{ "ToggleOffSleepFrames", &INI::parseInt, 0, 0x90 },
	{ "ToggleOnAttributeModifier", &INI::parseAsciiString, 0, 0x94 },
	{ "ToggleOffAttributeModifier", &INI::parseAsciiString, 0, 0x98 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C5C764: 1 fields and the zero sentinel.
extern const FieldParse g_00C5C764[] = {
	{ "FatCursorRadius", &INI::parseReal, 0, 0x7C },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C5DDE4: 1 fields and the zero sentinel.
extern const FieldParse g_00C5DDE4[] = {
	{ "StopPowerTemplate", &INI::parseSpecialPowerTemplate, 0, 0x7C },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C5D378: 4 fields and the zero sentinel.
extern const FieldParse g_00C5D378[] = {
	{ "CloudBreakRadius", &INI::parseReal, 0, 0x7C },
	{ "CloudBreakFX", &INI::parseFXList, 0, 0x80 },
	{ "SunbeamObject", &INI::parseAsciiString, 0, 0x84 },
	{ "ObjectSpacing", &INI::parseReal, 0, 0x88 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C5E298: 6 fields and the zero sentinel.
extern const FieldParse g_00C5E298[] = {
	{ "HealAmount", &INI::parseReal, 0, 0x7C },
	{ "HealAsPercent", &INI::parseBool, 0, 0x80 },
	{ "HealAffects", &Rva002567EAParse, 0, 0x88 },
	{ "HealRadius", &INI::parseReal, 0, 0x84 },
	{ "HealFX", &INI::parseFXList, 0, 0xA4 },
	{ "HealOCL", &INI::parseObjectCreationList, 0, 0xA8 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C5D518: 4 fields and the zero sentinel.
extern const FieldParse g_00C5D518[] = {
	{ "TaintObject", &INI::parseAsciiString, 0, 0x7C },
	{ "TaintRadius", &INI::parseReal, 0, 0x80 },
	{ "TaintFX", &INI::parseFXList, 0, 0x84 },
	{ "TaintOCL", &INI::parseObjectCreationList, 0, 0x88 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C5C468: 4 fields and the zero sentinel.
extern const FieldParse g_00C5C468[] = {
	{ "InvisibilityNugget", &Rva00438176Parse, 0, 0x7C },
	{ "BroadcastRadius", &INI::parseReal, 0, 0x134 },
	{ "ObjectFilter", &iniParseObjectFilter, 0, 0x138 },
	{ "Duration", &INI::parseDurationUnsignedInt, 0, 0x13C },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C5D6C0: 3 fields and the zero sentinel.
extern const FieldParse g_00C5D6C0[] = {
	{ "FreezingRainRadius", &INI::parseReal, 0, 0x7C },
	{ "FreezingRainFX", &INI::parseFXList, 0, 0x80 },
	{ "BurnRateModifier", &INI::parseInt, 0, 0x84 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C5D7BC: 2 fields and the zero sentinel.
extern const FieldParse g_00C5D7BC[] = {
	{ "DarknessRadius", &INI::parseReal, 0, 0x7C },
	{ "DarknessFX", &INI::parseFXList, 0, 0x80 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C5D8A8: 2 fields and the zero sentinel.
extern const FieldParse g_00C5D8A8[] = {
	{ "GrabRadius", &INI::parseReal, 0, 0x7C },
	{ "AllowTree", &INI::parseBool, 0, 0x80 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C5CDC0: 5 fields and the zero sentinel.
extern const FieldParse g_00C5CDC0[] = {
	{ "UpgradeOCL", &INI::Rva004C381C_ParseUpgradeOCL, 0, 0x7C },
	{ "OCL", &INI::parseObjectCreationList, 0, 0x88 },
	{ "CreateLocation", &INI::parseIndexList, TheOCLCreateLocTypeNames, 0x8C },
	{ "UpgradeName", &INI::Rva004C3859_ParseUpgradeName, 0, 0x90 },
	{ "NearestSecondaryObjectFilter", &iniParseObjectFilter, 0, 0x9C },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C5C9A0: 3 fields and the zero sentinel.
extern const FieldParse g_00C5C9A0[] = {
	{ "NumberOfFrames", &INI::parseInt, 0, 0x7C },
	{ "SpeedMulitplier", &INI::parseReal, 0, 0x80 },
	{ "Type", &INI::parseAsciiStringVector, 0, 0x84 },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C5E23C: 1 fields and the zero sentinel.
extern const FieldParse g_00C5E23C[] = {
	{ "UpgradeName", &Rva004C7E09_ParseUpgradeName, 0, 0x7C },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C5D27C: 1 fields and the zero sentinel.
extern const FieldParse g_00C5D27C[] = {
	{ "BountyPercent", &INI::parseReal, 0, 0x7C },
	{ 0, 0, 0, 0 }
};
// Retail VA 0x00C5E6E4: 1 fields and the zero sentinel.
extern const FieldParse g_00C5E6E4[] = {
	{ "ScanRange", &INI::parseReal, 0, 0x7C },
	{ 0, 0, 0, 0 }
};

#include "../../../../Include/GameLogic/Module/SpecialPowerModuleData.h"

void SpecialPowerModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>((unsigned int)&g_00C4E628), 0);
}

class DevastateSpecialPowerModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@DevastateSpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x004C81C8 (27 bytes): base-table call above plus the Devastate
// table at (unsigned int)&g_00C5E3D0 (Radius, FX, TreeValueMultiplier, TreeValueTotalCap,
// FireWeapon at +0x7C through +0x8C). Four of five fields match BFME1's
// DevastateSpecialPower table verbatim (Radius, FX, TreeValueMultiplier,
// TreeValueTotalCap); BFME2 appends FireWeapon. The owning factory at
// 0x00252653 pushes this proc's VA.
void DevastateSpecialPowerModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialPowerModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>((unsigned int)&g_00C5E3D0), 0);
}

#include "../../../../Include/GameLogic/Module/CashHackSpecialPowerModuleData.h"

// ?buildFieldParse@CashHackSpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x004C2955 (27 bytes): base-table call above plus the CashHack
// table at (unsigned int)&g_00C5C724 (UpgradeMoneyAmount at +0x7C, MoneyAmount at +0x88).
// Both fields match BFME1's CashHackSpecialPower table verbatim
// (UpgradeMoneyAmount, MoneyAmount). The owning factory at 0x00251957
// pushes this proc's VA.
void CashHackSpecialPowerModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialPowerModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>((unsigned int)&g_00C5C724), 0);
}

class ElvenWoodSpecialPowerModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@ElvenWoodSpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x004C3FC2 (27 bytes): base-table call above plus the ElvenWood
// table at (unsigned int)&g_00C5D018 (ElvenGroveObject at +0x88, ElvenNumObjects at +0x8C,
// ElvenWoodRadius at +0x90, ElvenWoodFX at +0x94, ElvenWoodOCL at +0x98).
// The ElvenWoodSpecialPower pool key at 0x4C3943 sits in the same cluster.
// The owning factory at 0x00251CB4 pushes this proc's VA.
void ElvenWoodSpecialPowerModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialPowerModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>((unsigned int)&g_00C5D018), 0);
}

class WeaponChangeSpecialPowerModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@WeaponChangeSpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x004C3FDD (27 bytes): base-table call above plus the Scavenger
// table at (unsigned int)&g_00C5D0F0 (FlagsUsedForToggle at +0x7C, ToggleOnSleepFrames at
// +0x8C, ToggleOffSleepFrames at +0x90, ToggleOnAttributeModifier at +0x94,
// ToggleOffAttributeModifier at +0x98). The ScavengerSpecialPower pool key
// at 0x4C4387 plus the name getter at 0x4C4381 sit in the same cluster
// (ElvenWood precedent). The owning factory at 0x00251D40 pushes this
// proc's VA.
void WeaponChangeSpecialPowerModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialPowerModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>((unsigned int)&g_00C5D0F0), 0);
}

class DefectorSpecialPowerModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@DefectorSpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x004C2970 (27 bytes): base-table call above plus the Defector
// table at (unsigned int)&g_00C5C764 (FatCursorRadius at +0x7C, the sole field; BFME1's
// DefectorSpecialPowerModuleData table holds exactly this field). The
// DefectorSpecialPower pool key at 0x4C29D3 sits in the same cluster
// (ElvenWood precedent). The owning factory at 0x002519E3 pushes this
// proc's VA (unique image-wide).
void DefectorSpecialPowerModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialPowerModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>((unsigned int)&g_00C5C764), 0);
}

class StopSpecialPowerModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void StopSpecialPowerModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialPowerModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>((unsigned int)&g_00C5DDE4), 0);
}

class CloudBreakSpecialPowerModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void CloudBreakSpecialPowerModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialPowerModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>((unsigned int)&g_00C5D378), 0);
}

class PlayerHealSpecialPowerModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@PlayerHealSpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x004C7E63 (27 bytes): base-table call above plus the PlayerHeal
// table at (unsigned int)&g_00C5E298 (HealAmount at +0x7C, HealAsPercent at +0x80,
// HealRadius at +0x84, HealAffects at +0x88, HealFX at +0xA4, HealOCL at
// +0xA8). The PlayerHealSpecialPower pool key at 0x4C7EFB sits in the same
// cluster (ElvenWood precedent) beside the BFME1 PlayerHealSpecialPower
// files. The owning factory at 0x002525C7 pushes this proc's VA (unique
// image-wide).
void PlayerHealSpecialPowerModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialPowerModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>((unsigned int)&g_00C5E298), 0);
}

class TaintSpecialPowerModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@TaintSpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x004C487B (27 bytes): base-table call above plus the Taint table
// at (unsigned int)&g_00C5D518 (TaintObject at +0x7C, TaintRadius at +0x80, TaintFX at
// +0x84, TaintOCL at +0x88). The TaintSpecialPower pool key at 0x4C48DF
// sits in the same cluster (ElvenWood precedent). The owning factory at
// 0x00251EE4 pushes this proc's VA (unique image-wide).
void TaintSpecialPowerModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialPowerModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>((unsigned int)&g_00C5D518), 0);
}

class InvisibilitySpecialPowerModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@InvisibilitySpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x004C2389 (27 bytes): base-table call above plus the table at
// (unsigned int)&g_00C5C468 (InvisibilityNugget at +0x7C plus BroadcastRadius at +0x134
// plus ObjectFilter at +0x138 plus Duration at +0x13C). Identity:
// ModuleFactory registers factory 0x002518CB -- which calls ctor 0x4C244D
// and pushes this proc's VA -- under "InvisibilitySpecialPower"; formerly
// misnamed MobNexusContainModuleData by analogy with the HealContain
// precedent rather than direct registration evidence.
void InvisibilitySpecialPowerModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialPowerModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>((unsigned int)&g_00C5C468), 0);
}

class FreezingRainSpecialPowerModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@FreezingRainSpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x004C4B86 (27 bytes): base-table call above plus the FreezingRain
// table at (unsigned int)&g_00C5D6C0 (FreezingRainRadius at +0x7C plus FreezingRainFX at
// +0x80 plus BurnRateModifier at +0x84). The rowed factory at 0x00251F70
// calls the rowed ctor at 0x4C4D71 and pushes this proc's VA (unique
// image-wide). Row supersedes the pin.
void FreezingRainSpecialPowerModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialPowerModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>((unsigned int)&g_00C5D6C0), 0);
}

class DarknessSpecialPowerModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@DarknessSpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x004C4D9E (27 bytes): base-table call above plus the Darkness
// table at (unsigned int)&g_00C5D7BC (DarknessRadius at +0x7C plus DarknessFX at +0x80).
// The rowed factory at 0x00251FFC calls the rowed ctor at 0x4C4F63 and
// pushes this proc's VA (unique image-wide); the pool key at 0x4C4E02 names
// the class. Row supersedes the pin.
void DarknessSpecialPowerModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialPowerModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>((unsigned int)&g_00C5D7BC), 0);
}

class GrabPassengerSpecialPowerModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@GrabPassengerSpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x004C4F89 (27 bytes): base-table call above plus the Grab table
// at (unsigned int)&g_00C5D8A8 (GrabRadius at +0x7C plus AllowTree at +0x80). The rowed
// factory at 0x00252088 calls the rowed ctor at 0x4C5421 and pushes this
// proc's VA (unique image-wide); the pool key at 0x4C4FCE names the class.
// Row supersedes the pin.
void GrabPassengerSpecialPowerModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialPowerModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>((unsigned int)&g_00C5D8A8), 0);
}

class OCLSpecialPowerModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@OCLSpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x004C3898 (27 bytes): base-table call above plus the OCL table at
// (unsigned int)&g_00C5CDC0. The owning factory at 0x00251B8A pushes this proc's VA (unique
// image-wide); ModuleFactory registers it under "OCLSpecialPower".
// Row supersedes the pin.
void OCLSpecialPowerModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialPowerModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>((unsigned int)&g_00C5CDC0), 0);
}

class ProductionSpeedBonusModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@ProductionSpeedBonusModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x004C2EDA (27 bytes): base-table call above plus the
// ProductionSpeedBonus table at (unsigned int)&g_00C5C9A0. The owning factory pushes this
// proc's VA; ModuleFactory registers it under "ProductionSpeedBonus".
// The ProductionSpeedBonus pool key at 0x4C2F25 sits beside the ctor at
// 0x4C2FE6. Row supersedes the pin.
void ProductionSpeedBonusModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialPowerModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>((unsigned int)&g_00C5C9A0), 0);
}

class PlayerUpgradeSpecialPowerModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@PlayerUpgradeSpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x004C7E48 (27 bytes): base-table call above plus the PlayerUpgrade
// table at (unsigned int)&g_00C5E23C. The owning factory pushes this proc's VA;
// ModuleFactory registers it under "PlayerUpgradeSpecialPower".
// The PlayerUpgradeSpecialPower pool key at 0x4C7C4C sits beside the ctor at
// 0x4C7D68. Row supersedes the pin.
void PlayerUpgradeSpecialPowerModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialPowerModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>((unsigned int)&g_00C5E23C), 0);
}

class ScavengerSpecialPowerModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@ScavengerSpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x004C4338 (27 bytes): base-table call above plus the Scavenger
// table at (unsigned int)&g_00C5D27C (BountyPercent at +0x7C the sole field). The owning
// factory at 0x00251DCC pushes this proc's VA (unique image-wide);
// ModuleFactory registers it under "ScavengerSpecialPower". The Scavenger
// module ctor at 0x4C4353 plus the name getter at 0x4C4381 plus the pool key
// at 0x4C43BC sit in the same cluster. Row supersedes the pin.
void ScavengerSpecialPowerModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialPowerModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>((unsigned int)&g_00C5D27C), 0);
}

class CombineHordeSpecialPowerModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@CombineHordeSpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x004C87A9 (27 bytes): base-table call above plus the CombineHorde
// table at (unsigned int)&g_00C5E6E4 (ScanRange at +0x7C the sole field). The owning
// factory at 0x002527F1 pushes this proc's VA (unique image-wide);
// ModuleFactory registers it under "CombineHordeSpecialPower".
// Row supersedes the pin.
void CombineHordeSpecialPowerModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialPowerModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>((unsigned int)&g_00C5E6E4), 0);
}

// ?ManTheWallsSpecialPowerParse_2526DF@@YAXAAVMultiIniFieldParse@@@Z
// retail 0x004C856F 5B: forwards to SpecialPower base 0x00493207.
// Owning factory 0x002526DF pushes VA; ModuleFactory registers ManTheWalls.
// LINK BONUS for ModuleDataFriendNewFactories.
void ManTheWallsSpecialPowerParse_2526DF(MultiIniFieldParse &parse)
{
	SpecialPowerModuleData::buildFieldParse(parse);
}

// ?HordeDispatchSpecialPowerParse_25287D@@YAXAAVMultiIniFieldParse@@@Z
// retail 0x004C89CB 27B: base-table call plus empty table at 0x00C6BB18.
// Owning factory 0x0025287D pushes VA; ModuleFactory registers HordeDispatch.
// Same bytes as UntamedAllegiance and Repair; LINK BONUS for ModuleDataFriendNewFactories.
void HordeDispatchSpecialPowerParse_25287D(MultiIniFieldParse &parse)
{
	SpecialPowerModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(g_emptyFieldParseTable), 0);
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
