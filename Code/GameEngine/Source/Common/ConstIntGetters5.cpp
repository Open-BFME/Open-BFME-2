// stlport
// Cold-slice B8-imm32 const-int returners without vtable carriage (twin-free TU).
//
// Same 6-byte shape as ConstIntGetters4.cpp (mov eax,<IMM32> / ret) but for
// bodies with no .rdata vtable slot, no direct callers and no branch sources:
// each follows a ret-imm (C2-04-00) and is an unclaimed leaf, so the opaque
// address-derived name witnesses only the address and the returned constant.
// Kept in a fresh TU so this batch does not contend with the hot
// ConstIntGetters4 appends on origin/master. No // cl: line (defaults match
// the frameless 6-byte shape).

// ?Rva00062A52Get@@YAHXZ @ 0x00062a52 (6B): returns 0x0000ffff.
// Follows a ret-4 (prev C2-04-00), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00062A52Get(void)
{
	return 0x0000ffff;
}

// ?Rva0028C77DGet@@YAHXZ @ 0x0028c77d (6B): returns 0x0000009a.
// Follows a ret-4 (prev C2-04-00), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0028C77DGet(void)
{
	return 0x0000009a;
}

// ?Rva004CFAE5Get@@YAHXZ @ 0x004cfae5 (6B): returns 0x00010000.
// Follows a ret-4 (prev C2-04-00), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva004CFAE5Get(void)
{
	return 0x00010000;
}

// ?Rva00007450Get@@YAHXZ @ 0x00007450 (6B): returns -2.
// int3-padded both sides, no direct callers. Opaque address-derived name.
int Rva00007450Get(void)
{
	return -2;
}

// ?Rva00018080Get@@YAHXZ @ 0x00018080 (6B): returns INT_MIN.
// int3-padded both sides, no direct callers. Opaque address-derived name.
int Rva00018080Get(void)
{
	return (int)0x80000000;
}

// ?Rva00018610Get@@YAHXZ @ 0x00018610 (6B): returns INT_MAX.
// int3-padded both sides, no direct callers. Opaque address-derived name.
int Rva00018610Get(void)
{
	return 0x7fffffff;
}

// ?Rva00019B50Get@@YAHXZ @ 0x00019b50 (6B): returns 0x7ffffffe.
// int3-padded both sides, no direct callers. Opaque address-derived name.
int Rva00019B50Get(void)
{
	return 0x7ffffffe;
}

// ?Rva000454EDGet@@YAHXZ @ 0x000454ed (6B): returns 0x0000024f.
// Follows an idiv helper tail. No direct callers. Opaque address-derived
// name.
int Rva000454EDGet(void)
{
	return 0x0000024f;
}

// ?Rva0024A8D6Get@@YAHXZ @ 0x0024a8d6 (6B): returns 132.
// Follows an SEH epilogue plus leave plus ret. No direct callers.
// Opaque address-derived name.
int Rva0024A8D6Get(void)
{
	return 132;
}

// ?Rva0024B43DGet@@YAHXZ @ 0x0024b43d (6B): returns 135.
// Follows an SEH epilogue plus leave plus ret. No direct callers.
// Opaque address-derived name.
int Rva0024B43DGet(void)
{
	return 135;
}

// ?Rva0024B507Get@@YAHXZ @ 0x0024b507 (6B): returns 142.
// Follows an SEH epilogue plus leave plus ret. No direct callers.
// Opaque address-derived name.
int Rva0024B507Get(void)
{
	return 142;
}

// ?Rva0024C32DGet@@YAHXZ @ 0x0024c32d (6B): returns 133.
// Follows an SEH epilogue plus leave plus ret. No direct callers.
// Opaque address-derived name.
int Rva0024C32DGet(void)
{
	return 133;
}

// ?Rva0024C775Get@@YAHXZ @ 0x0024c775 (6B): returns 8192.
// Follows an SEH epilogue plus leave plus ret. No direct callers.
// Opaque address-derived name.
int Rva0024C775Get(void)
{
	return 8192;
}

// ?Rva0024D51CGet@@YAHXZ @ 0x0024d51c (6B): returns 2048.
// Follows an SEH epilogue plus leave plus ret. No direct callers.
// Opaque address-derived name.
int Rva0024D51CGet(void)
{
	return 2048;
}

// ?Rva0024DCDDGet@@YAHXZ @ 0x0024dcdd (6B): returns 256.
// Follows an SEH epilogue plus leave plus ret. No direct callers.
// Opaque address-derived name.
int Rva0024DCDDGet(void)
{
	return 256;
}

// ?Rva0024DCE3Get@@YAHXZ @ 0x0024dce3 (6B): returns 257.
// Abuts the twin getter above. No direct callers. Opaque
// address-derived name.
int Rva0024DCE3Get(void)
{
	return 257;
}

// ?Rva0024FB41Get@@YAHXZ @ 0x0024fb41 (6B): returns 513.
// Follows an SEH epilogue plus leave plus ret. No direct callers.
// Opaque address-derived name.
int Rva0024FB41Get(void)
{
	return 513;
}

// ?Rva00250722Get@@YAHXZ @ 0x00250722 (6B): returns 140.
// Follows an SEH epilogue plus leave plus ret. No direct callers.
// Opaque address-derived name.
int Rva00250722Get(void)
{
	return 140;
}

// ?Rva002507ECGet@@YAHXZ @ 0x002507ec (6B): returns 131.
// Follows an SEH epilogue plus leave plus ret. No direct callers.
// Opaque address-derived name.
int Rva002507ECGet(void)
{
	return 131;
}

// ?Rva00252165Get@@YAHXZ @ 0x00252165 (6B): returns 273.
// Follows an SEH epilogue plus leave plus ret. No direct callers.
// Opaque address-derived name.
int Rva00252165Get(void)
{
	return 273;
}

// ?Rva00285B54Get@@YAHXZ @ 0x00285b54 (6B): returns 4095.
// Follows a lea plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva00285B54Get(void)
{
	return 4095;
}

// ?Rva00285B5AGet@@YAHXZ @ 0x00285b5a (6B): returns 1023.
// Abuts the twin getter above. No direct callers. Opaque
// address-derived name.
int Rva00285B5AGet(void)
{
	return 1023;
}

// ?Rva00285B60Get@@YAHXZ @ 0x00285b60 (6B): returns 255.
// Abuts the twin getter above. No direct callers. Opaque
// address-derived name.
int Rva00285B60Get(void)
{
	return 255;
}

// ?Rva002AA2C9Get@@YAHXZ @ 0x002aa2c9 (6B): returns 218.
// Follows an idiv helper tail. No direct callers. Opaque
// address-derived name.
int Rva002AA2C9Get(void)
{
	return 218;
}

// ?Rva0041F286Get@@YAHXZ @ 0x0041f286 (6B): returns 0x00c3b000.
// Follows an x87-load plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva0041F286Get(void)
{
	return 0x00c3b000;
}

// ?Rva004D949FGet@@YAHXZ @ 0x004d949f (6B): returns INT_MIN.
// Follows a byte-store plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva004D949FGet(void)
{
	return (int)0x80000000;
}

// ?Rva00619FF0Get@@YAHXZ @ 0x00619ff0 (6B): returns -17.
// Follows a ret-12 plus int3 run. No direct callers. Opaque
// address-derived name.
int Rva00619FF0Get(void)
{
	return -17;
}

// ?Rva00620170Get@@YAHXZ @ 0x00620170 (6B): returns 32.
// Follows a sar plus ret plus int3 run. No direct callers. Opaque
// address-derived name.
int Rva00620170Get(void)
{
	return 32;
}

// The table addresses below have owned definitions in the data ledger.
// Keep each getter's address-derived identity; no return type is inferred.
extern const char *const ModelConditionNames[];
extern const char *BodyStateNames[];
extern const char *VeterancyLevelNames[];
extern const char *SpecialPowerNames[];
extern const char *g_Va00DD263CNames[];
extern const char *EmotionNames[];
struct FieldParse;
extern const FieldParse g_00C64D60[];

// ?Rva0004546DGet@@YAHXZ @ 0x0004546d (6B): returns 0x00dbaa98.
// Follows a ret-4 (prev C2-04-00), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0004546DGet(void)
{
	return (int)&ModelConditionNames;
}

// ?Rva000454CEGet@@YAHXZ @ 0x000454ce (6B): returns 0x00da5f30.
// Follows a tiny mov-al returner. No direct callers.
// Opaque address-derived name.
int Rva000454CEGet(void)
{
	return (int)&BodyStateNames;
}

// ?Rva002532CEGet@@YAHXZ @ 0x002532ce (6B): returns 0x00dbaa40.
// Follows an SEH epilogue plus leave plus ret. No direct callers.
// Opaque address-derived name.
int Rva002532CEGet(void)
{
	return (int)&VeterancyLevelNames;
}

// ?Rva003B0FA6Get@@YAHXZ @ 0x003b0fa6 (6B): returns 0x00dc0b40.
// Follows a leave plus ret-4 tail. No direct callers. Opaque
// address-derived name.
int Rva003B0FA6Get(void)
{
	return (int)&SpecialPowerNames;
}

// ?Rva003B31C1Get@@YAHXZ @ 0x003b31c1 (6B): returns 0x00dd263c.
// Follows a pop plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva003B31C1Get(void)
{
	return (int)&g_Va00DD263CNames;
}

// ?Rva003B321BGet@@YAHXZ @ 0x003b321b (6B): returns 0x00dba9c8.
// Follows a pop plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva003B321BGet(void)
{
	return (int)&EmotionNames;
}

// ?Rva0050B5C9Get@@YAHXZ @ 0x0050b5c9 (6B): returns 0x00c64d60.
// Follows a mov-al plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva0050B5C9Get(void)
{
	return (int)&g_00C64D60;
}


// The two field-table addresses below now have named providers. These
// data-only declarations make no claim about either manager instance layout.
// BF1 575ba2b uses the same named-table declaration pattern in
// Rva000C25F0Get.cpp and the related field-table getter units.
struct FieldParse;
class MultiplayerSettings { public: static const FieldParse m_multiplayerSettingsFieldParseTable[]; };
class ShellMenuSchemeManager { public: static const FieldParse m_shellMenuSchemeFieldParseTable[]; };

// ?Rva001EF361Get@@YAHXZ @ 0x001ef361 (6B): returns 0x00c18fb0.
// Follows a ret-4 (prev C2-04-00), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva001EF361Get(void)
{
	return reinterpret_cast<int>(MultiplayerSettings::m_multiplayerSettingsFieldParseTable);
}

// ?Rva0020049BGet@@YAHXZ @ 0x0020049b (6B): returns 0x00be29ec.
// Follows a leave plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva0020049BGet(void)
{
	return reinterpret_cast<int>(ShellMenuSchemeManager::m_shellMenuSchemeFieldParseTable);
}

// Moved back from ConstIntGetters5Addr.cpp: their constants now name the globals the
// ledger defines there (declaration-only views; no layout is asserted).
extern const FieldParse TheFXListFieldParse[];
extern const FieldParse CombatChainDefinitionFieldParse[];
extern const FieldParse BrutalDifficultyCheatsFieldParse[];
extern const FieldParse DifficultyTuningFieldParse[];
extern const FieldParse BfmeBonusForLevelFieldTable[];
extern const FieldParse Rva00418AC6FieldParseTable[];
extern const FieldParse shockWaveFieldParse[];
extern const FieldParse g_00C3BC20[];
class Rva00534E13
{
public:
    static const FieldParse fieldTable[];
};
class WaterSetting
{
public:
    static const FieldParse m_waterSettingFieldParseTable[];
};
struct SaveDate;
extern SaveDate BfmeINIReadTimestamp;
struct _GUID;
extern _GUID g_bfmeIidTSA;
class Dict;
class MapObject
{
public:
    static Dict TheWorldDict;
};

// ?Rva001DFAA0Get@@YAHXZ @ 0x001dfaa0 (6B): returns 0x00bdc720.
// Follows a ret-4 (prev C2-04-00), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva001DFAA0Get(void)
{
	return (int)TheFXListFieldParse;
}

// ?Rva002A8922Get@@YAHXZ @ 0x002a8922 (6B): returns 0x00bfd804.
// Follows a ret-4 (prev C2-04-00), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva002A8922Get(void)
{
	return (int)CombatChainDefinitionFieldParse;
}

// ?Rva002A893FGet@@YAHXZ @ 0x002a893f (6B): returns 0x00bfd85c.
// Follows a near ret (BrutalDifficultyCheats ctor tail), no .rdata vtable
// slot, no direct callers, no branch sources. Opaque address-derived name.
// The constant is the BrutalDifficultyCheats sub-table also pushed as an
// immediate by the rowed parser at 0x002a898a.
int Rva002A893FGet(void)
{
	return (int)BrutalDifficultyCheatsFieldParse;
}

// ?Rva002A88BBGet@@YAHXZ @ 0x002a88bb (6B): returns 0x00bfd768.
// Abuts the probability parser at 0x002a8845 (ends +118) and a twin getter
// below. Opaque address-derived name. The constant is the DifficultyTuning
// sub-table also pushed as an immediate by the rowed parser at 0x002a89d2.
int Rva002A88BBGet(void)
{
	return (int)DifficultyTuningFieldParse;
}

// ?Rva00417AE3Get@@YAHXZ @ 0x00417ae3 (6B): returns 0x00c3a658.
// Follows an SSE-store plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva00417AE3Get(void)
{
	return (int)BfmeBonusForLevelFieldTable;
}

// ?Rva004186DAGet@@YAHXZ @ 0x004186da (6B): returns 0x00c3a8b0.
// Follows a leave plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva004186DAGet(void)
{
	return (int)Rva00418AC6FieldParseTable;
}

// ?Rva00509DA5Get@@YAHXZ @ 0x00509da5 (6B): returns 0x00c64810.
// Follows a leave plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva00509DA5Get(void)
{
	return (int)shockWaveFieldParse;
}

// ?Rva00420965Get@@YAHXZ @ 0x00420965 (6B): returns 0x00c3bc20.
// Follows a ret-4 (prev C2-04-00), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00420965Get(void)
{
	return (int)g_00C3BC20;
}

// ?Rva00534B22Get@@YAHXZ @ 0x00534b22 (6B): returns 0x00c68ae8.
// Follows a ret-4 (prev C2-04-00), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00534B22Get(void)
{
	return (int)Rva00534E13::fieldTable;
}

// ?Rva00200BB4Get@@YAHXZ @ 0x00200bb4 (6B): returns 0x00c07fe0.
// Follows a leave plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva00200BB4Get(void)
{
	return (int)WaterSetting::m_waterSettingFieldParseTable;
}

// ?Rva0002BBC3Get@@YAHXZ @ 0x0002bbc3 (6B): returns 0x00ddf5b8.
// Follows a ret tail, next function starts with mov ecx plus call.
// No direct callers. Opaque address-derived name.
int Rva0002BBC3Get(void)
{
	return (int)&BfmeINIReadTimestamp;
}

// ?Rva00176E30Get@@YAHXZ @ 0x00176e30 (6B): returns 0x00bd4e3c.
// int3-padded both sides, no direct callers. Opaque address-derived name.
int Rva00176E30Get(void)
{
	return (int)&g_bfmeIidTSA;
}

// ?Rva0008514EGet@@YAHXZ @ 0x0008514e (6B): returns 0x00e00944.
// Follows a ret tail. No direct callers. Opaque address-derived name.
int Rva0008514EGet(void)
{
	return (int)&MapObject::TheWorldDict;
}

// Also moved back: the terrain bridge field table TerrainRoads.cpp defines.
class TerrainRoadType
{
public:
    static const FieldParse m_terrainBridgeFieldParseTable[];
};

// ?Rva001DAEB2Get@@YAHXZ @ 0x001daeb2 (6B): returns 0x00c03a28.
// Preceded by int3 padding. No direct callers. Opaque address-derived name.
int Rva001DAEB2Get(void)
{
	return (int)TerrainRoadType::m_terrainBridgeFieldParseTable;
}

// Named address targets let these getters rejoin their linking family.
// These declarations name existing field tables without asserting instance
// layouts. Native six-byte getters independently supply each table address.
struct FieldParse;
class LivingWorldRegionEffectsManager {
public:
    static FieldParse s_parseTable[];
};
class RingEffect {
public:
    static const FieldParse m_fieldParseTable[];
};
class CreditsManager {
public:
    static const FieldParse m_creditsFieldParseTable[];
};
extern const FieldParse AIDozerAssignmentFields[];

#include "../GameClient/GUI/HeaderTemplateView.h"
extern unsigned int g_Va00E04544;
extern "C" const FieldParse VictorySystemFieldParse[];
extern "C" const FieldParse FactionVictoryFieldParse[];

// ?Rva00016AC0Get@@YAHXZ @ 0x00016ac0 (6B): returns 0x00bbbddc.
// int3-padded both sides, no direct callers. Opaque address-derived name.
int Rva00016AC0Get(void)
{
	return (int)" ";
}

// ?Rva003EE72EGet@@YAHXZ @ 0x003ee72e (6B): returns 0x00dc14c8.
// Follows a ret-4 (prev C2-04-00), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva003EE72EGet(void)
{
	return reinterpret_cast<int>(LivingWorldRegionEffectsManager::s_parseTable);
}

// ?Rva00309E24Get@@YAHXZ @ 0x00309e24 (6B): returns 0x00c08400.
// Abuts the twin getter above. No direct callers. Opaque
// address-derived name.
int Rva00309E24Get(void)
{
	return reinterpret_cast<int>(RingEffect::m_fieldParseTable);
}

// ?Rva005B729FGet@@YAHXZ @ 0x005b729f (6B): returns 0x00c737e8.
// Follows a leave plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva005B729FGet(void)
{
	return reinterpret_cast<int>(CreditsManager::m_creditsFieldParseTable);
}

// ?Rva002A88C1Get@@YAHXZ @ 0x002a88c1 (6B): returns 0x00bfd7c0.
// Abuts the twin getter above and the CombatChainEntry ctor at 0x002a88c7.
// Opaque address-derived name. The constant is a sub-table VA in the same
// 0xBFD7xx family as the tuning table.
int Rva002A88C1Get(void)
{
	return reinterpret_cast<int>(AIDozerAssignmentFields);
}

// ?Rva004FF2EEGet@@YAHXZ @ 0x004ff2ee (6B): returns 0x00e04544.
// Follows a ret-4 (prev C2-04-00), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva004FF2EEGet(void)
{
	return reinterpret_cast<int>(&g_Va00E04544);
}

// ?Rva00201992Get@@YAHXZ @ 0x00201992 (6B): returns 0x00be3098.
// Preceded by int3 padding. No direct callers. Opaque address-derived name.
int Rva00201992Get(void)
{
	return reinterpret_cast<int>(HeaderTemplateManager::m_headerFieldParseTable);
}

// ?Rva00215C48Get@@YAHXZ @ 0x00215c48 (6B): returns 0x00c387c0.
// Follows a call plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva00215C48Get(void)
{
	return reinterpret_cast<int>(VictorySystemFieldParse);
}

// ?Rva00215C4EGet@@YAHXZ @ 0x00215c4e (6B): returns 0x00c38760.
// Abuts the twin getter above. No direct callers. Opaque
// address-derived name.
int Rva00215C4EGet(void)
{
	return reinterpret_cast<int>(FactionVictoryFieldParse);
}

// These field tables now have verified data owners. The class declarations
// name only static data; no instance layout or original getter identity is
// inferred. Keep the existing opaque integer-return ABI for these leaf bodies.
class GlowEffect { public: static const FieldParse m_fieldParseTable[]; };
class CrateTemplate { public: static const FieldParse TheCrateTemplateFieldParseTable[]; };
class DrawGroupInfo { public: static const FieldParse s_fieldParseTable[]; };
class TerrainType { public: static const FieldParse m_terrainTypeFieldParseTable[]; };
extern const FieldParse g_00C15468[];
extern const FieldParse g_00BFA6E8[];
extern const FieldParse g_00C00B48[];

// ?Rva001DAF77Get@@YAHXZ @ 0x001daf77 (6B): returns 0x00c15468.
// Follows an SEH epilogue plus leave plus ret. No direct callers.
// Opaque address-derived name.
int Rva001DAF77Get(void)
{
	return reinterpret_cast<int>(g_00C15468);
}

// ?Rva001DCC3FGet@@YAHXZ @ 0x001dcc3f (6B): returns 0x00bdbe10.
// Follows a leave plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva001DCC3FGet(void)
{
	return reinterpret_cast<int>(DrawGroupInfo::s_fieldParseTable);
}

// ?Rva002009F5Get@@YAHXZ @ 0x002009f5 (6B): returns 0x00c0c3a8.
// Follows a leave plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva002009F5Get(void)
{
	return reinterpret_cast<int>(TerrainType::m_terrainTypeFieldParseTable);
}

// ?Rva0026EDB1Get@@YAHXZ @ 0x0026edb1 (6B): returns 0x00bfa6e8.
// Follows a ret-4 (prev C2-04-00), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0026EDB1Get(void)
{
	return reinterpret_cast<int>(g_00BFA6E8);
}

// ?Rva002C8E5AGet@@YAHXZ @ 0x002c8e5a (6B): returns 0x00c00b48.
// Follows an and-store plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva002C8E5AGet(void)
{
	return reinterpret_cast<int>(g_00C00B48);
}

// ?Rva00309E1EGet@@YAHXZ @ 0x00309e1e (6B): returns 0x00c08350.
// Follows byte-store plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva00309E1EGet(void)
{
	return reinterpret_cast<int>(GlowEffect::m_fieldParseTable);
}

// ?Rva0035C959Get@@YAHXZ @ 0x0035c959 (6B): returns 0x00c162a0.
// Follows a pop plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva0035C959Get(void)
{
	return reinterpret_cast<int>(CrateTemplate::TheCrateTemplateFieldParseTable);
}

// Field-parse tables the getters below return; each provider unit defines it.
extern "C" const FieldParse __identifier("?m_gameWindowTransitionsFieldParseTable@GameWindowTransitionsHandler@@0QBUFieldParse@@B")[];
extern const FieldParse FXNuggetFieldParse[];
extern const FieldParse LocomotorTemplateFields[];
extern const FieldParse Rva00210A14FieldParseTable[];
extern const FieldParse SkirmishAIDataFields[];
extern "C" const FieldParse __identifier("?s_anim2DFieldParseTable@Anim2DTemplate@@1QBUFieldParse@@B")[];
extern const FieldParse g_00C1045C[];
extern "C" const FieldParse __identifier("?m_specialPowerFieldParse@SpecialPowerTemplate@@0QBUFieldParse@@B")[];
extern const FieldParse carryoverUnitFieldParse[];
extern const FieldParse g_00C3B050[];
extern const FieldParse TheArmyDefinitionFields[];

// ?Rva001DBA71Get@@YAHXZ @ 0x001dba71 (6B): returns 0x00bdbbcc.
// Follows an al-returner tail. No direct callers. Opaque address-derived
// name.
int Rva001DBA71Get(void)
{
	return reinterpret_cast<int>(__identifier("?m_gameWindowTransitionsFieldParseTable@GameWindowTransitionsHandler@@0QBUFieldParse@@B"));
}

// ?Rva001DFAB9Get@@YAHXZ @ 0x001dfab9 (6B): returns 0x00bdca18.
// Follows a setne-al returner tail. No direct callers. Opaque
// address-derived name.
int Rva001DFAB9Get(void)
{
	return reinterpret_cast<int>(FXNuggetFieldParse);
}

// ?Rva001E392EGet@@YAHXZ @ 0x001e392e (6B): returns 0x00bde2f8.
// Follows a store plus pop plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva001E392EGet(void)
{
	return reinterpret_cast<int>(LocomotorTemplateFields);
}

// ?Rva0020E2F2Get@@YAHXZ @ 0x0020e2f2 (6B): returns 0x00be4120.
// Follows an al-returner tail. No direct callers. Opaque
// address-derived name.
int Rva0020E2F2Get(void)
{
	return reinterpret_cast<int>(Rva00210A14FieldParseTable);
}

// ?Rva002A8A0FGet@@YAHXZ @ 0x002a8a0f (6B): returns 0x00bfda50.
// Follows the BrutalDifficultyCheats parser tail. No direct callers.
// Opaque address-derived name. The constant is the table at 0x7fda50.
int Rva002A8A0FGet(void)
{
	return reinterpret_cast<int>(SkirmishAIDataFields);
}

// ?Rva002D6AEFGet@@YAHXZ @ 0x002d6aef (6B): returns 0x00c031f0.
// Follows a word-load plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva002D6AEFGet(void)
{
	return reinterpret_cast<int>(__identifier("?s_anim2DFieldParseTable@Anim2DTemplate@@1QBUFieldParse@@B"));
}

// ?Rva0033A507Get@@YAHXZ @ 0x0033a507 (6B): returns 0x00c1045c.
// Follows an or-store plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva0033A507Get(void)
{
	return reinterpret_cast<int>(g_00C1045C);
}

// ?Rva003B0FA0Get@@YAHXZ @ 0x003b0fa0 (6B): returns 0x00dc0e78.
// Follows a ret-4 (prev C2-04-00), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva003B0FA0Get(void)
{
	return reinterpret_cast<int>(__identifier("?m_specialPowerFieldParse@SpecialPowerTemplate@@0QBUFieldParse@@B"));
}

// ?Rva0040C344Get@@YAHXZ @ 0x0040c344 (6B): returns 0x00c18d18.
// Follows a call plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva0040C344Get(void)
{
	return reinterpret_cast<int>(carryoverUnitFieldParse);
}

// ?Rva0041F310Get@@YAHXZ @ 0x0041f310 (6B): returns 0x00c3b050.
// Follows a ret-4 (prev C2-04-00), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0041F310Get(void)
{
	return reinterpret_cast<int>(g_00C3B050);
}

// ?Rva0041F71AGet@@YAHXZ @ 0x0041f71a (6B): returns 0x00c3b5e8.
// Follows a leave plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva0041F71AGet(void)
{
	return reinterpret_cast<int>(TheArmyDefinitionFields);
}

// Field-parse tables INIThinFieldParsers2.cpp defines; the getters below return them.
extern const FieldParse g_00C3A730[];
extern const FieldParse g_00C3A9A8[];
extern const FieldParse g_00C3AAC8[];
extern const FieldParse g_00CE43B0[];

// ?Rva00418060Get@@YAHXZ @ 0x00418060 (6B): returns 0x00c3a730.
// Follows a leave plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva00418060Get(void)
{
	return reinterpret_cast<int>(g_00C3A730);
}

// ?Rva0041901DGet@@YAHXZ @ 0x0041901d (6B): returns 0x00c3a9a8.
// Follows a leave plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva0041901DGet(void)
{
	return reinterpret_cast<int>(g_00C3A9A8);
}

// ?Rva00419663Get@@YAHXZ @ 0x00419663 (6B): returns 0x00c3aac8.
// Follows a leave plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva00419663Get(void)
{
	return reinterpret_cast<int>(g_00C3AAC8);
}

// ?Rva006882D0Get@@YAHXZ @ 0x006882d0 (6B): returns 0x00ce43b0.
// int3-padded both sides, no direct callers. Opaque address-derived name.
int Rva006882D0Get(void)
{
	return reinterpret_cast<int>(g_00CE43B0);
}

// The field-parse table parseAIBaseDefinition.cpp defines; the getter below returns it.
extern const FieldParse g_00C3AF18[];

// ?Rva0041E6B8Get@@YAHXZ @ 0x0041e6b8 (6B): returns 0x00c3af18.
// Follows a ret-4 (prev C2-04-00), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0041E6B8Get(void)
{
	return reinterpret_cast<int>(g_00C3AF18);
}

// Field-parse tables INIThinFieldParsers2.cpp defines; the getters below
// (moved from ConstIntGettersAddr.cpp) return them.
extern const FieldParse g_00BFC338[];
extern const FieldParse g_00CE4818[];
extern const FieldParse g_00C1DB18[];
extern const FieldParse g_00C36290[];
extern const FieldParse g_00C38658[];
extern const FieldParse g_00C5FEA0[];
extern const FieldParse g_00C5FFA0[];
extern const FieldParse g_00C63FD0[];
extern const FieldParse g_00C6CFD0[];

// ?Rva0008EFCCGet@@YAHXZ @ 0x0008EFCC (6B): returns 0x00BFC338.
// Follows a ret (0x8EFCB) with a B8-imm getter after. Carried at 0x7C7C08
// and 0x7FD590, no direct callers, no branch sources. The value is below
// the image base so it is a plain integer, not a pointer. Opaque name.
int Rva0008EFCCGet(void)
{
	return reinterpret_cast<int>(g_00BFC338);
}

// ?Rva000907A1Get@@YAHXZ @ 0x000907A1 (6B): returns 0x00CE4818.
// Follows a ret-12 (0x9079E-A0) with a push-style function after.
// Carried at 0x7C7F0C and 0x8E497C, no direct callers, no branch
// sources. Opaque address-derived name.
int Rva000907A1Get(void)
{
	return reinterpret_cast<int>(g_00CE4818);
}

// ?Rva003B0E57Get@@YAHXZ @ 0x003B0E57 (6B): returns 0x00C1DB18.
// Follows a ret-4 (0x3B0E54-56) with a mov/mov/ret getter after.
// 1 direct E8 caller (0x1FE73D), Ghidra-6, no branch sources.
// Opaque address-derived name.
int Rva003B0E57Get(void)
{
	return reinterpret_cast<int>(g_00C1DB18);
}

// ?Rva003EE6F7Get@@YAHXZ @ 0x003EE6F7 (6B): returns 0x00C36290.
// Follows a leave/ret (0x3EE6F5-56) with a mov-style function after.
// 1 direct E8 caller (0x20E1B8), no Ghidra entry (dead emission), no
// branch sources. Opaque address-derived name.
int Rva003EE6F7Get(void)
{
	return reinterpret_cast<int>(g_00C36290);
}

// ?Rva00404715Get@@YAHXZ @ 0x00404715 (6B): returns 0x00C38658.
// Prev leave/ret with a push-style function after. 2 direct E8 callers,
// no Ghidra entry (dead emission), no branch sources. Opaque name.
int Rva00404715Get(void)
{
	return reinterpret_cast<int>(g_00C38658);
}

// ?Rva004CE29DGet@@YAHXZ @ 0x004CE29D (6B): returns 0x00C5FEA0.
// Follows a ret-4 (0x4CE29A-9C) with a mov/mov/ret getter after. 41
// direct E8 callers (anchor-verified), Ghidra-6, no branch sources.
// The value sits 0x100 below landed Rva004CE52EGet's table. Opaque name.
int Rva004CE29DGet(void)
{
	return reinterpret_cast<int>(g_00C5FEA0);
}

// ?Rva004CE52EGet@@YAHXZ @ 0x004CE52E (6B): returns 0x00C5FFA0.
// Follows a neg/sbb/neg boolize tail (ret at 0x4CE52D) with a
// push-style function after. 20 direct E8 callers, Ghidra-6, no branch
// sources. Opaque address-derived name.
int Rva004CE52EGet(void)
{
	return reinterpret_cast<int>(g_00C5FFA0);
}

// ?Rva00507552Get@@YAHXZ @ 0x00507552 (6B): returns 0x00C63FD0.
// Follows a mov/mov/ret getter (ret at 0x507551) with a frame-style
// function after. 17 direct E8 callers, Ghidra-6, no branch sources.
// Opaque address-derived name.
int Rva00507552Get(void)
{
	return reinterpret_cast<int>(g_00C63FD0);
}

// ?Rva0056A983Get@@YAHXZ @ 0x0056A983 (6B): returns 0x00C6CFD0.
// Follows a leave/ret (0x56A981-82) with a cmp/jcc-style function after.
// 1 direct E8 caller (0x3EE5CE), no Ghidra entry (dead emission), no
// branch sources. Opaque address-derived name.
int Rva0056A983Get(void)
{
	return reinterpret_cast<int>(g_00C6CFD0);
}

// Rowed code owners whose entry addresses the two getters below return
// (AptComponents.cpp's 0x00410223 factory; LocomotorStore_newLocomotor.cpp's 0x005C9886).
extern "C" {
void __identifier("?createBinkGameWindow@@YGPAXPAX@Z")();
void __identifier("?rva005C9886@Rva005C9886@@QBEPAVRva005C96EB@@PAX@Z")();
}

// ?Rva0056D749Get@@YAHXZ @ 0x0056D749 (6B): returns 0x00810223.
// Follows a leave/ret (0x56D746-48) with a frame-style function after.
// Carried at 0x86DAE0, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva0056D749Get(void)
{
	return reinterpret_cast<int>(&__identifier("?createBinkGameWindow@@YGPAXPAX@Z"));
}

// ?Rva005C9880Get@@YAHXZ @ 0x005C9880 (6B): returns 0x009C9886.
// Follows a pop/ret (0x5C987E-7F) with a B8-imm/call function after
// (0x5C9886). Carried at 0x874B8C, no direct callers, no branch
// sources. Opaque address-derived name.
int Rva005C9880Get(void)
{
	return reinterpret_cast<int>(&__identifier("?rva005C9886@Rva005C9886@@QBEPAVRva005C96EB@@PAX@Z"));
}

// Field-parse table INIThinFieldParsers2.cpp defines; the getter below returns it.
extern const FieldParse g_00C64180[];

// ?Rva005088C8Get@@YAHXZ @ 0x005088C8 (6B): returns 0x00C64180.
// Follows a leave/ret (0x5088C6-87) with a push-style function after.
// 1 direct E8 caller (0x50B11D, anchor-decoded as a real call), Ghidra-6,
// no branch sources. Opaque address-derived name.
int Rva005088C8Get(void)
{
	return reinterpret_cast<int>(g_00C64180);
}
