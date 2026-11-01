// cl: /Ireference/shims/bfme2_ascii /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport

// ?rva001FE70F@Rva001FE70F@@QAEXPAVINI@@@Z, RVA 0x001FE70F, 99B. Unlock lane:
// MultiIniFieldParse at ebp-0x84 via rowed ctor 0x0002BAA0, add rowed
// 0x0002BC6E of g_00BE2070 with 0 then Rva003B0E57Get (0x00C1DB18) with
// 0x154, then INI::initFromINIMulti pin 0x0002D7A8 with this and parse,
// then AsciiString copy from +0x18 to +0x154 via rowed StringBase set
// 0x000366F0. Callers 0x001FF079 0x001FF092 0x001FF0E8 in 0x001FEFEC.
// Owner unproven so honest-address class Rva001FE70F.
#include "ascii_string.h"

typedef void (*FieldParseProc)(class INI *, void *, void *, const void *);
#include "../../../Include/Common/INI/FieldParse.h"
extern "C" {
void __identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseAndTranslateLabel@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseStartMoney@PlayerTemplate@@SAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseRGBColor@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseCoord3D@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseAsciiStringVectorAppend@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseProductionCostChange@PlayerTemplate@@KAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseProductionTimeChange@PlayerTemplate@@KAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseProductionVeterancyLevel@PlayerTemplate@@KAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseScienceVector@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseAsciiStringVector@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?iniParseObjectFilter@@YAXPAVINI@@PAX1PBX@Z")();
void __identifier("?Rva001FDD33_ParseResourceModifierValues@INI@@SAXPAV1@PAX1PBX@Z")();
}
// The retail table at 0x007E2070: 61 entries and the null terminator; every parser is a rowed code owner.
extern const FieldParse g_00BE2070[62] = {
	{ "Side", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x18 },
	{ "PlayableSide", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x151 },
	{ "DisplayName", (FieldParseProc)&__identifier("?parseAndTranslateLabel@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x14 },
	{ "StartMoney", (FieldParseProc)&__identifier("?parseStartMoney@PlayerTemplate@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x2C },
	{ "PreferredColor", (FieldParseProc)&__identifier("?parseRGBColor@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x38 },
	{ "StartingBuilding", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x44 },
	{ "StartingUnit0", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x48 },
	{ "StartingUnit1", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x4C },
	{ "StartingUnit2", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x50 },
	{ "StartingUnit3", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x54 },
	{ "StartingUnit4", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x58 },
	{ "StartingUnit5", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x5C },
	{ "StartingUnit6", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x60 },
	{ "StartingUnit7", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x64 },
	{ "StartingUnit8", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x68 },
	{ "StartingUnit9", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x6C },
	{ "StartingUnitOffset0", (FieldParseProc)&__identifier("?parseCoord3D@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x70 },
	{ "StartingUnitOffset1", (FieldParseProc)&__identifier("?parseCoord3D@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x7C },
	{ "StartingUnitOffset2", (FieldParseProc)&__identifier("?parseCoord3D@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x88 },
	{ "StartingUnitOffset3", (FieldParseProc)&__identifier("?parseCoord3D@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x94 },
	{ "StartingUnitOffset4", (FieldParseProc)&__identifier("?parseCoord3D@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xA0 },
	{ "StartingUnitOffset5", (FieldParseProc)&__identifier("?parseCoord3D@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xAC },
	{ "StartingUnitOffset6", (FieldParseProc)&__identifier("?parseCoord3D@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xB8 },
	{ "StartingUnitOffset7", (FieldParseProc)&__identifier("?parseCoord3D@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xC4 },
	{ "StartingUnitOffset8", (FieldParseProc)&__identifier("?parseCoord3D@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xD0 },
	{ "StartingUnitOffset9", (FieldParseProc)&__identifier("?parseCoord3D@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xDC },
	{ "StartingUnitTacticalWOTR", (FieldParseProc)&__identifier("?parseAsciiStringVectorAppend@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xE8 },
	{ "ProductionCostChange", (FieldParseProc)&__identifier("?parseProductionCostChange@PlayerTemplate@@KAXPAVINI@@PAX1PBX@Z"), 0, 0x0 },
	{ "ProductionTimeChange", (FieldParseProc)&__identifier("?parseProductionTimeChange@PlayerTemplate@@KAXPAVINI@@PAX1PBX@Z"), 0, 0x0 },
	{ "ProductionVeterancyLevel", (FieldParseProc)&__identifier("?parseProductionVeterancyLevel@PlayerTemplate@@KAXPAVINI@@PAX1PBX@Z"), 0, 0x0 },
	{ "IntrinsicSciences", (FieldParseProc)&__identifier("?parseScienceVector@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x120 },
	{ "IntrinsicSciencesMP", (FieldParseProc)&__identifier("?parseScienceVector@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x12C },
	{ "PurchaseScienceCommandSet", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x138 },
	{ "PurchaseScienceCommandSetMP", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x13C },
	{ "SpecialPowerShortcutCommandSet", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x140 },
	{ "SpecialPowerShortcutWinName", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x144 },
	{ "SpecialPowerShortcutButtonCount", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x148 },
	{ "IsObserver", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x150 },
	{ "ScoreScreenImage", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x164 },
	{ "LoadScreenImage", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x168 },
	{ "LoadScreenMusic", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x14C },
	{ "HeadWaterMark", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x16C },
	{ "FlagWaterMark", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x170 },
	{ "EnabledImage", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x174 },
	{ "SideIconImage", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x178 },
	{ "BeaconName", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x17C },
	{ "LightPointsUpSound", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x1A4 },
	{ "ObjectiveAddedSound", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x1A8 },
	{ "ObjectiveCompletedSound", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x1AC },
	{ "InitialUpgrades", (FieldParseProc)&__identifier("?parseAsciiStringVector@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x180 },
	{ "DefaultPlayerAIType", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x1B0 },
	{ "SpellBook", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x1B4 },
	{ "SpellBookMp", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x1B8 },
	{ "Evil", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x1BC },
	{ "BuildableHeroesMP", (FieldParseProc)&__identifier("?parseAsciiStringVector@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x18C },
	{ "BuildableRingHeroesMP", (FieldParseProc)&__identifier("?parseAsciiStringVector@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x198 },
	{ "SpellStoreCurrentPowerLabel", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x1C0 },
	{ "SpellStoreMaximumPowerLabel", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x1C4 },
	{ "ResourceModifierObjectFilter", (FieldParseProc)&__identifier("?iniParseObjectFilter@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x1C8 },
	{ "ResourceModifierValues", (FieldParseProc)&__identifier("?Rva001FDD33_ParseResourceModifierValues@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x1CC },
	{ "MultiSelectionPortrait", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x1D8 },
	{ 0, 0, 0, 0 }
};


#include "../../../Include/Common/INI/INI.h"

int __cdecl Rva003B0E57Get(void);

class Rva001FE70F
{
public:
	void rva001FE70F(class INI *ini);

private:
	char m_pad00[0x18];
	AsciiString m_side;
	char m_pad1C[0x138];
	AsciiString m_154;
};

void Rva001FE70F::rva001FE70F(class INI *ini)
{
	MultiIniFieldParse parse;
	parse.add(g_00BE2070, 0);
	parse.add((const FieldParse *)Rva003B0E57Get(), 0x154);
	ini->initFromINIMulti(this, parse);
	((StringBase<char> &)(m_154)).set((const StringBase<char> &)(m_side));
}
