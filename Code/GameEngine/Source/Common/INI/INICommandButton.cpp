// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /GX /Ireference/shims/bfme2_ascii
// ?parseCommandButtonDefinition@ControlBar@@SAXPAVINI@@@Z @0x001DAF81 255B.
// Target identity: WB 0x00AC2A00 names ControlBar::parseCommandButtonDefinition
// in INICommandButton.cpp. Native block registration 0x007AD0B7 binds this parser
// to CommandButton. The complete native boundary ends at 0x001DB080.
// Donor: Open-BFME-1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f,
// game/GameEngine/Source/Common/INI/INICommandButton.cpp; compiling the clean
// donor under BFME2 settings placed no bodies. Its find/create/override structure
// is retained, with target load type 5 reload and duplicate-body discard paths.
// Target bytes establish load type +0x08, override byte +0x08, link +0x0C,
// node size 0x2CC, and field-table VA 0x00C15468. Callees not independently named
// remain address-derived; this file reuses their existing verified owners.
// Shared AsciiString supplies constructor and releaseBuffer ownership. The
// temporary's inline cleanup view calls the existing 368B node destructor;
// its member contents are not reconstructed or claimed here.

#include "ascii_string.h"
typedef void (*FieldParseProc)(class INI *, void *, void *, const void *);
#include "../../../Include/Common/INI/FieldParse.h"
class INI {
public:
 const char *getNextToken(const char *separators=0);
 void initFromINI(void *,const FieldParse*);
 char pad[8]; int loadType;
};
class Rva0035BB4B { public: Rva0035BB4B(); virtual ~Rva0035BB4B(); };
class Rva0031AB1ENode {
public:
 // Construction through the rowed CommandButton ctor 0x0035BB4B (??0Rva0035BB4B).
 __declspec(dllimport) __forceinline Rva0031AB1ENode() { ((Rva0035BB4B*)this)->Rva0035BB4B::Rva0035BB4B(); }
 unsigned char bytes[0x2CC];
 // Cleanup through the existing owned CommandButton destructor ABI.
 ~Rva0031AB1ENode() { ((Rva0035BB4B*)this)->Rva0035BB4B::~Rva0035BB4B(); }
};
class Rva0031BE07 {
public:
 void *rva0031BE07(const StringBase<char>&);
};
class Rva0031AB1EOwner {
public:
 Rva0031AB1ENode *rva0031AB1E(const AsciiString*);
};
class Rva0031BF1B {
public:
 void rva0031BF1B(class ModuleData*);
};
class Rva0031EB96 {
public:
 Rva0031AB1ENode *rva0031EB96(Rva0031AB1ENode*);
};

#include "../../../Include/GameClient/ControlBar.h"
extern ControlBar *TheControlBar;
struct LookupListRec { const char *name; int value; };
// The retail name list at RVA 0x009BFB68 (32 names and the null terminator).
extern const char *const g_00DBFB68[33] = { "NEED_TARGET_ENEMY_OBJECT", "NEED_TARGET_NEUTRAL_OBJECT", "NEED_TARGET_ALLY_OBJECT", "NO_PLAY_UNIT_SPECIFIC_SOUND_FOR_AUTO_ABILITY", "ALLOW_SHRUBBERY_TARGET", "NEED_TARGET_POS", "NEED_UPGRADE", "NEED_SPECIAL_POWER_SCIENCE", "OK_FOR_MULTI_SELECT", "CONTEXTMODE_COMMAND", "CHECK_LIKE", "NEEDS_CASTLE_KINDOF", "ATTACK_OBJECTS_POSITION", "OPTION_ONE", "OPTION_TWO", "OPTION_THREE", "NOT_QUEUEABLE", "SINGLE_USE_COMMAND", "---DO-NOT-USE---", "SCRIPT_ONLY", "OK_FOR_MULTI_EXECUTE", "ALLOW_ROCK_TARGET", "HIDE_WHILE_DISABLED", "TOGGLE_IMAGE_ON_WEAPON", "TOGGLE_IMAGE_ON_WEAPONSET", "TOGGLE_IMAGE_ON_FORMATION", "MOUNTED_ONLY", "UNMOUNTED_ONLY", "NONPRESSABLE", "AUTO_ABILITY_TRIGGERED", "ON_GROUND_ONLY", "CANCELABLE", 0 };
extern const LookupListRec TheWeaponSlotTypeNamesLookupList[];
// The retail lookup list at RVA 0x00815430 (6 names and the null terminator).
extern const LookupListRec CommandButtonMappedBorderTypeNames[7] = { { "NONE", 0 }, { "BUILD", 1 }, { "UPGRADE", 2 }, { "ACTION", 3 }, { "SYSTEM", 4 }, { "ALTERED", 5 }, { 0, 0 } };
extern "C" {
void __identifier("?parseCommand@CommandButton@@SAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseBitString32@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseThingTemplate@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseUpgradeTemplate@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?Rva00339A13_ParseUpgradeKeyList@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseAsciiStringVector@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseLookupList@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?Rva002C8C06Parse@@YAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseScienceVector@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseSpecialPowerTemplate@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?rva0035AED4@@YAXPAVINI@@PAX1PBX@Z")();
void __identifier("?Rva0033A1CE_ParseSoundList@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?Rva0035AECFParse@@YAXPAVINI@@PAX1PBX@Z")();
void __identifier("?Rva002567EAParse@@YAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?Rva000B9468Parse@@YAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseStances@@YAXPAVINI@@PAX1PBX@Z")();
void __identifier("?Rva0026F28BParse@@YAXPAVINI@@PAXPAI@Z")();
}
// The retail table at 0x00815468: 54 entries and the null terminator; every parser is a rowed code owner.
extern const FieldParse g_00C15468[55] = {
	{ "Command", (FieldParseProc)&__identifier("?parseCommand@CommandButton@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x14 },
	{ "Options", (FieldParseProc)&__identifier("?parseBitString32@INI@@SAXPAV1@PAX1PBX@Z"), g_00DBFB68, 0x1C },
	{ "Object", (FieldParseProc)&__identifier("?parseThingTemplate@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x20 },
	{ "Upgrade", (FieldParseProc)&__identifier("?parseUpgradeTemplate@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x24 },
	{ "NeededUpgrade", (FieldParseProc)&__identifier("?Rva00339A13_ParseUpgradeKeyList@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x28 },
	{ "NeededUpgradeAny", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x34 },
	{ "BuildUpgrades", (FieldParseProc)&__identifier("?parseAsciiStringVector@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x38 },
	{ "WeaponSlot", (FieldParseProc)&__identifier("?parseLookupList@INI@@SAXPAV1@PAX1PBX@Z"), TheWeaponSlotTypeNamesLookupList, 0x80 },
	{ "WeaponSlotToggle1", (FieldParseProc)&__identifier("?parseLookupList@INI@@SAXPAV1@PAX1PBX@Z"), TheWeaponSlotTypeNamesLookupList, 0x84 },
	{ "WeaponSlotToggle2", (FieldParseProc)&__identifier("?parseLookupList@INI@@SAXPAV1@PAX1PBX@Z"), TheWeaponSlotTypeNamesLookupList, 0x88 },
	{ "WeaponSlotToggle3", (FieldParseProc)&__identifier("?parseLookupList@INI@@SAXPAV1@PAX1PBX@Z"), TheWeaponSlotTypeNamesLookupList, 0x8C },
	{ "FlagsUsedForToggle", (FieldParseProc)&__identifier("?Rva002C8C06Parse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x90 },
	{ "MaxShotsToFire", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xA0 },
	{ "Science", (FieldParseProc)&__identifier("?parseScienceVector@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xA4 },
	{ "SpecialPower", (FieldParseProc)&__identifier("?parseSpecialPowerTemplate@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x44 },
	{ "ToggleButtonName", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x48 },
	{ "TextLabel", (FieldParseProc)&__identifier("?parseAsciiStringVector@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x58 },
	{ "DescriptLabel", (FieldParseProc)&__identifier("?parseAsciiStringVector@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x64 },
	{ "PurchasedLabel", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x70 },
	{ "ConflictingLabel", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x74 },
	{ "LacksPrerequisiteLabel", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x78 },
	{ "ButtonImage", (FieldParseProc)&__identifier("?parseAsciiStringVector@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xB4 },
	{ "CursorName", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x50 },
	{ "InvalidCursorName", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x54 },
	{ "ButtonBorderType", (FieldParseProc)&__identifier("?parseLookupList@INI@@SAXPAV1@PAX1PBX@Z"), CommandButtonMappedBorderTypeNames, 0xB0 },
	{ "RadiusCursorType", (FieldParseProc)&__identifier("?rva0035AED4@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x4C },
	{ "UnitSpecificSound", (FieldParseProc)&__identifier("?Rva0033A1CE_ParseSoundList@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xC8 },
	{ "SetAutoAbilityUnitSound", (FieldParseProc)&__identifier("?Rva0033A1CE_ParseSoundList@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xD4 },
	{ "UnsetAutoAbilityUnitSound", (FieldParseProc)&__identifier("?Rva0033A1CE_ParseSoundList@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xE0 },
	{ "DoubleClick", (FieldParseProc)&__identifier("?Rva0035AECFParse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x100 },
	{ "Radial", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x101 },
	{ "ShowProductionCount", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x104 },
	{ "InPalantir", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x102 },
	{ "IsClickable", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x105 },
	{ "ShowButton", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x106 },
	{ "RequireLevel", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x108 },
	{ "RequiresValidContainer", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x107 },
	{ "AutoAbility", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x10C },
	{ "AffectsKindOf", (FieldParseProc)&__identifier("?Rva002567EAParse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x110 },
	{ "TriggerWhenReady", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x12C },
	{ "PresetRange", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x130 },
	{ "AutoDelay", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x134 },
	{ "NeedDamagedTarget", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x138 },
	{ "AutoAbilityDisallowedOnModelCondition", (FieldParseProc)&__identifier("?Rva000B9468Parse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x13C },
	{ "CommandTrigger", (FieldParseProc)&__identifier("?parseAsciiStringVector@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x188 },
	{ "EnableOnModelCondition", (FieldParseProc)&__identifier("?Rva000B9468Parse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x194 },
	{ "DisableOnModelCondition", (FieldParseProc)&__identifier("?Rva000B9468Parse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x1E0 },
	{ "CommandRangeStart", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x22C },
	{ "CommandRangeCount", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x230 },
	{ "Stances", (FieldParseProc)&__identifier("?parseStances@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x234 },
	{ "CreateAHeroUIPrerequisiteButtonName", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x240 },
	{ "CreateAHeroUIMinimumLevel", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x244 },
	{ "CreateAHeroUIIconImageName", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x248 },
	{ "CreateAHeroUIAllowableUpgrades", (FieldParseProc)&__identifier("?Rva0026F28BParse@@YAXPAVINI@@PAXPAI@Z"), 0, 0x24C },
	{ 0, 0, 0, 0 }
};
void ControlBar::parseCommandButtonDefinition(INI *ini) {
 AsciiString name(ini->getNextToken());
 Rva0031AB1ENode *button=(Rva0031AB1ENode*)((Rva0031BE07*)TheControlBar)->rva0031BE07(*(StringBase<char>*)&name);
 if(!button) {
  button=((Rva0031AB1EOwner*)TheControlBar)->rva0031AB1E(&name);
  if(ini->loadType==2) button->bytes[8]=1;
 } else if(ini->loadType==5) {
  if(button->bytes[8]) TheControlBar->rva0031AB77SetFlag();
  ((Rva0031BF1B*)TheControlBar)->rva0031BF1B((ModuleData*)button);
  button=((Rva0031AB1EOwner*)TheControlBar)->rva0031AB1E(&name);
  *(int*)(button->bytes+12)=0;
 } else if(ini->loadType==2) {
  button=((Rva0031EB96*)TheControlBar)->rva0031EB96(button);
 } else {
  Rva0031AB1ENode ignored;
  ini->initFromINI(&ignored,g_00C15468);
  return;
 }
 ini->initFromINI(button,g_00C15468);
}

// INI block registration. BFME's INI keeps its block types on a list of
// 12-byte BlockParse nodes; each unit links its own nodes onto
// theBlockParseList from a file-scope object whose inline constructor does the
// link. MSVC 7.1 builds token and parse in .data, so each node's .text$yc
// initializer is only the 21-byte link (retail .CRT$XCU 0x007AD0B7,
// node 0x00DB8BBC).
typedef void (*INIBlockParse)( INI *ini );
extern struct BlockParse *theBlockParseList;
struct BlockParse
{
	BlockParse *next;
	const char *token;
	INIBlockParse parse;

	BlockParse( const char *token, INIBlockParse parse ) : next(theBlockParseList), token(token), parse(parse)
	{
		theBlockParseList = this;
	}
};

BlockParse theCommandButtonBlockParse( "CommandButton", ControlBar::parseCommandButtonDefinition );
