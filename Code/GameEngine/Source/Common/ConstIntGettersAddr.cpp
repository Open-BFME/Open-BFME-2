// The members of the ConstIntGetters.cpp family whose constant is an image address
// no unit defines yet, split out so the rest of the family links; each moves
// back once its target has a definition to name.
//
// B8-imm32 const-int returners: six-byte free functions with one shape:
//
//     mov eax,<IMM32> / ret
//
// Each stands on a CC-island (int3 before and after) with no Ghidra entry
// (dead emissions) and is carried in several .rdata vtable slots, so the
// address is a genuine shared virtual implementation whose class identity
// is not witnessed anywhere. Rows are named for their own address with the
// proven return value, following Rva0073B660False.cpp and the Disp family
// (address-derived names, identity unrecoverable from 6 bytes).
// No // cl: line (defaults match the frameless 6-byte shape).

typedef void (*FieldParseProc)(class INI *, void *, void *, const void *);
struct FieldParse { const char *token; FieldParseProc parse; const void *userData; int offset; };

struct LookupListRec { const char *name; int value; };
extern const LookupListRec TheWeaponSlotTypeNamesLookupList[];

// Parser procs the tables below name; each is a rowed code owner.
extern "C" {
void __identifier("?Rva000B9468Parse@@YAXPAVINI@@PAX1PBX@Z")();
void __identifier("?Rva000CF713Parse@@YAXPAVINI@@PAVRva000CF713Owner@@@Z")();
void __identifier("?Rva000CF873Parse@@YAXPAVINI@@PAX1PBX@Z")();
void __identifier("?Rva001DEE74Parse@@YAXPAVINI@@PAX1PBX@Z")();
void __identifier("?Rva002567EAParse@@YAXPAVINI@@PAX1PBX@Z")();
void __identifier("?Rva002C8C06Parse@@YAXPAVINI@@PAX1PBX@Z")();
void __identifier("?Rva00338E52_ParseEnvelope@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?Rva003393DFParse@@YAXPAVINI@@PAX1PBX@Z")();
void __identifier("?Rva003393F7Parse@@YAXPAVINI@@PAX1PBX@Z")();
void __identifier("?Rva00415B91Parse@@YAXPAVINI@@PAX1PBX@Z")();
void __identifier("?Rva00464081ParseMask@@YAXPAVINI@@PAX1PBX@Z")();
void __identifier("?Rva00468908Parse@@YAXPAVINI@@PAX1PBX@Z")();
void __identifier("?iniParseAnim@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?dup_002F0F7@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?iniParseDefaultRule@RespawnUpdate@@SAXPAVINI@@PAX1PBX@Z")();
void __identifier("?iniParseNewRuleForLevel@RespawnUpdate@@SAXPAVINI@@PAX1PBX@Z")();
void __identifier("?iniParseObjectFilter@@YAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseAngularVelocityReal@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseAsciiStringVector@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseAsciiStringVectorAppend@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseBannerCarrierPosition@@YAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseColorInt@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseCoord2D@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseCoord3D@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseDurationReal@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseDurationUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseFXList@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseFXList@StructureCollapseUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseFromINI@Rva003B1017@@SAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseGameClientRandomVariable@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseHordeContainComboHorde@@YAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseHordeContainRankSets@@YAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseHordeContainRanksThatStopAdvance@@YAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseHordeContainSplitResult@@YAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseIndexList@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseLink@DynamicPortalBehaviourData@@SAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseLookupList@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseMeleeBehavior@HordeContainModuleData@@SAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseOCL@StructureCollapseUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parsePercentToReal@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseRGBColor@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseRGBColorKeyframe@ParticleSystemTemplate@@SAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseRandomKeyframe@ParticleSystemTemplate@@SAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseRankInfo@HordeContainModuleData@@SAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseScience@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseWayPoint@DynamicPortalBehaviourData@@SAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseWeaponTemplate@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?rva00467DE6@@YAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseInitialCrew@SiegeEngineContainModuleData@@SAXPAVINI@@PAX1PBX@Z")();
void __identifier("?Rva004CA798Parse@@YAXPAVINI@@PAX1@Z")();
void __identifier("?parsePositiveNonZeroReal@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseLodOptions@W3DModelDrawModuleData@@SAXPAVINI@@PAX1PBX@Z")();
}

extern const char *TheLocomotorSetNames[];

extern const int g_emptyFieldParseTable[4];
#pragma comment(linker, "/alternatename:?opaqueCall@Rva00507552@@SAPAXXZ=?Rva00507552Get@@YAHXZ")
#pragma comment(linker, "/alternatename:?opaqueCall@Rva005088C8@@SAPAXXZ=?Rva005088C8Get@@YAHXZ")


// ?Rva00309E4BGet@@YAHXZ @ 0x00309E4B (6B): returns 0x00DBD7DC.
// Follows the rep-movsd table copier at 0x309E30 (9 dwords
// 0xDBD7B8->0xDBD7DC, ret at 0x309E4A) and returns the filled table's
// address; a larger push-style function starts at 0x309E51. 28 direct E8
// callers, Ghidra-6, no branch sources. The value is carried as a plain
// integer literal (no relocation slot exists here), so no pin is needed.
// Opaque address-derived name.
int Rva00309E4BGet(void)
{
	return 0x00DBD7DC;
}

// ?Rva00309E65Get@@YAHXZ @ 0x00309E65 (6B): returns 0x00DBD860.
// Same copier/getter pair shape as 0x309E4B (rep movsd into 0xDBD860,
// ret at 0x309E64, larger function follows at 0x309E6B). 13 direct E8
// callers, Ghidra-6, no branch sources. Opaque address-derived name.
int Rva00309E65Get(void)
{
	return 0x00DBD860;
}

// ?Rva00309E7FGet@@YAHXZ @ 0x00309E7F (6B): returns 0x00DBD918.
// Third copier/getter pair in the run (rep movsd into 0xDBD918, ret at
// 0x309E7E). 11 direct E8 callers, Ghidra-6, no branch sources.
// Opaque address-derived name.
int Rva00309E7FGet(void)
{
	return 0x00DBD918;
}


// ?Rva00510D87Get@@YAHXZ @ 0x00510D87 (6B): returns 0x006D1E55.
// Follows an SEH leave/ret (0x510D85-86) with a sub/cmp-style function
// after. 7 .rdata refs, no direct callers, no branch sources.
// Opaque address-derived name.


// ?Rva0056DD52Get@@YAHXZ @ 0x0056DD52 (6B): returns 0x00DC2884. Opens a
// contiguous triple (52/58/5E, each B8-6 back to back) after an indirect
// call + leave/ret. 2 direct E8 callers, Ghidra-6. Opaque name.
int Rva0056DD52Get(void)
{
	return 0x00DC2884;
}

// ?Rva0056DD58Get@@YAHXZ @ 0x0056DD58 (6B): returns 0x00DC2D10. Middle
// of the triple. 4 direct E8 callers, Ghidra-6. Opaque name.
int Rva0056DD58Get(void)
{
	return 0x00DC2D10;
}

// ?Rva0056DD5EGet@@YAHXZ @ 0x0056DD5E (6B): returns 0x00DC4B60. Closes
// the triple (a mov-style function follows). 4 direct E8 callers,
// Ghidra-6. Opaque name.
int Rva0056DD5EGet(void)
{
	return 0x00DC4B60;
}

// ?Rva003EFE9AGet@@YAHXZ @ 0x003EFE9A (6B): returns 0x00DC34A4.
// Prev C3 with a movzx-style function after. 4 direct E8 callers,
// Ghidra-6, no branch sources. Opaque name.
int Rva003EFE9AGet(void)
{
	return 0x00DC34A4;
}

// ?Rva0056B767Get@@YAHXZ @ 0x0056B767 (6B): returns 0x00C6BB18.
// Prev leave/ret with a test-and-style function after. 3 direct E8
// callers, no Ghidra entry (dead emission), no branch sources.
// Opaque name.
// ?Rva000A8F58Get@@YAHXZ @ 0x000A8F58 (6B): returns 0x00DB4CF0. Opens a
// contiguous pair (58/F0 then 5E/F8, 8 apart) after a ret-4. Tail-jumped
// from thunk 0x62972, 1 direct E8 caller, Ghidra-6. Opaque name.
int Rva000A8F58Get(void)
{
	return 0x00DB4CF0;
}

// ?Rva000A8F5EGet@@YAHXZ @ 0x000A8F5E (6B): returns 0x00DB4CF8. Closes
// the pair. Tail-jumped from thunk 0x62977, 2 direct E8 callers,
// Ghidra-6. Opaque name.
int Rva000A8F5EGet(void)
{
	return 0x00DB4CF8;
}


// ?Rva00433B18Get@@YAHXZ @ 0x00433B18 (6B): returns 0x00E032DC.
// Follows a leave/ret (0x433B16-17) with a push-style function after.
// 1 direct E8 caller (0x23B65A), no Ghidra entry (dead emission), no
// branch sources. Opaque address-derived name.
int Rva00433B18Get(void)
{
	return 0x00E032DC;
}


// ?Rva00226140Get@@YAHXZ @ 0x00226140 (6B): returns 0x00DC2274.
// Follows a ret-8 (0x22613D-3F) with a frame-style function after.
// 4 direct E8 callers (0x2264D9/0x2265AE/0x226684/0x226759, all nearby),
// Ghidra-6, no branch sources. Opaque address-derived name.
int Rva00226140Get(void)
{
	return 0x00DC2274;
}

// ?Rva00434091Get@@YAHXZ @ 0x00434091 (6B): returns 0x00DC5170.
// Follows a ret-8 (0x43408E-90) with a mov-style function after.
// 4 direct E8 callers (0x43456E/0x434647/0x434721/0x4347FA, all nearby),
// Ghidra-6, no branch sources. Opaque address-derived name.
int Rva00434091Get(void)
{
	return 0x00DC5170;
}


// ?Rva0056B7DEGet@@YAHXZ @ 0x0056B7DE (6B): returns 0x00C6D690.
// Follows a ret-4 (0x56B7DB-DD) with a B8-imm/call function after.
// 3 direct E8 callers (0x56B71B/0x56BEAF/0x56BFD2), no Ghidra entry
// (dead emission), no branch sources. Opaque address-derived name.
int Rva0056B7DEGet(void)
{
	return 0x00C6D690;
}

// ?Rva000EF29AGet@@YAHXZ @ 0x000EF29A (6B): returns 0x00544558.
// Follows a ret-16 (0xEF297-9C) with a push-style function after.
// Carried by 6 .rdata slots, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva000EF29AGet(void)
{
	return 0x00544558;
}


// ?Rva00517F2BGet@@YAHXZ @ 0x00517F2B (6B): returns 0x006D2025.
// Follows a leave/ret (0x517F29-2A) with a B8-imm/call function after
// (0x517F31). Carried at 0x866444, no direct callers, no branch
// sources. Opaque address-derived name.


// ?Rva0051BF27Get@@YAHXZ @ 0x0051BF27 (6B): returns 0x006D2099.
// Follows a pop/ret (0x51BF25-26) with a lea-style function after.
// Carried at 0x866C74, no direct callers, no branch sources.
// Opaque address-derived name.


// ?Rva0051D772Get@@YAHXZ @ 0x0051D772 (6B): returns 0x006D210D.
// Follows an add-esp/ret (0x51D76F-71) with a frame-style function
// after. Carried at 0x866FC8, no direct callers, no branch sources.
// Opaque address-derived name.


// ?Rva00655114Get@@YAHXZ @ 0x00655114 (6B): returns 1. Follows a
// pop-ebp/ret (0x65510F-13) with a mov-style function after. Carried
// at 0x8E0B54, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva00655114Get(void)
{
	return 1;
}


// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.

// FXParticleSystem default-parser tables, defined here (this unit already
// absorbs image-address debt) so FXParticleSystemDefaultParsers.cpp links.
// Each is the exact retail bytes: 16-byte FieldParse entries plus the zero
// terminator, read from game.dat. Referenced by name from the parser TU.

// Retail VA 0x00C6B988: Alpha1..Alpha8 plus terminator (144B).
extern const FieldParse s_fxpsAlphaTable[9] = {
    { "Alpha1", (FieldParseProc)&__identifier("?parseRandomKeyframe@ParticleSystemTemplate@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xC },
    { "Alpha2", (FieldParseProc)&__identifier("?parseRandomKeyframe@ParticleSystemTemplate@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x1C },
    { "Alpha3", (FieldParseProc)&__identifier("?parseRandomKeyframe@ParticleSystemTemplate@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x2C },
    { "Alpha4", (FieldParseProc)&__identifier("?parseRandomKeyframe@ParticleSystemTemplate@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x3C },
    { "Alpha5", (FieldParseProc)&__identifier("?parseRandomKeyframe@ParticleSystemTemplate@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x4C },
    { "Alpha6", (FieldParseProc)&__identifier("?parseRandomKeyframe@ParticleSystemTemplate@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x5C },
    { "Alpha7", (FieldParseProc)&__identifier("?parseRandomKeyframe@ParticleSystemTemplate@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x6C },
    { "Alpha8", (FieldParseProc)&__identifier("?parseRandomKeyframe@ParticleSystemTemplate@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x7C },
    { 0, 0, 0, 0 },
};

// Retail VA 0x00C6C4A0: SizeRate..AngularDampingXY plus terminator (160B).
extern const int s_fxpsSizeAngleTable[40] = {
    0x00BE189C, 0x00738A9D, 0x00000000, 0x0000000C,
    0x00BE188C, 0x00738A9D, 0x00000000, 0x00000018,
    0x00C6C498, 0x00738A9D, 0x00000000, 0x00000024,
    0x00C6C488, 0x00738A9D, 0x00000000, 0x00000030,
    0x00C6C478, 0x00738A9D, 0x00000000, 0x0000003C,
    0x00C6C46C, 0x0042EC4E, 0x00C1B6D8, 0x00000048,
    0x00C6C464, 0x00738A9D, 0x00000000, 0x0000004C,
    0x00C6C454, 0x00738A9D, 0x00000000, 0x00000058,
    0x00C6C440, 0x00738A9D, 0x00000000, 0x00000064,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

// Retail VA 0x00C6C3E0: Gravity..ParticlesAttachToBone plus terminator (96B).
extern const FieldParse s_fxpsPhysicsTable[6] = {
    { "Gravity", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x18 },
    { "VelocityDamping", (FieldParseProc)&__identifier("?parseGameClientRandomVariable@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x1C },
    { "DriftVelocity", (FieldParseProc)&__identifier("?parseCoord3D@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xC },
    { "Swirly", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x28 },
    { "ParticlesAttachToBone", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x29 },
    { 0, 0, 0, 0 },
};

// Retail VA 0x00C6BA58: Color1..Color8 plus ColorScale plus terminator (160B).
extern const FieldParse s_fxpsColorTable[10] = {
    { "Color1", (FieldParseProc)&__identifier("?parseRGBColorKeyframe@ParticleSystemTemplate@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xC },
    { "Color2", (FieldParseProc)&__identifier("?parseRGBColorKeyframe@ParticleSystemTemplate@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x1C },
    { "Color3", (FieldParseProc)&__identifier("?parseRGBColorKeyframe@ParticleSystemTemplate@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x2C },
    { "Color4", (FieldParseProc)&__identifier("?parseRGBColorKeyframe@ParticleSystemTemplate@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x3C },
    { "Color5", (FieldParseProc)&__identifier("?parseRGBColorKeyframe@ParticleSystemTemplate@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x4C },
    { "Color6", (FieldParseProc)&__identifier("?parseRGBColorKeyframe@ParticleSystemTemplate@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x5C },
    { "Color7", (FieldParseProc)&__identifier("?parseRGBColorKeyframe@ParticleSystemTemplate@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x6C },
    { "Color8", (FieldParseProc)&__identifier("?parseRGBColorKeyframe@ParticleSystemTemplate@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x7C },
    { "ColorScale", (FieldParseProc)&__identifier("?parseGameClientRandomVariable@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x8C },
    { 0, 0, 0, 0 },
};

// LK2 link batch: FieldParse tables named by the BuildFieldParse TUs that
// reference them (all bytes read from game.dat, terminators per ZH {0,0,0,0}
// convention; two tables carry no terminator and are defined to their last
// valid entry). This unit already absorbs image-address debt; its link state
// is unchanged. The parser TUs link by naming these instead of casting VAs.
// Retail VA 0x00bcb3c8: 57 entries + terminator (928B).
extern const int s_modelDrawFieldTable[232] = {
    0x00BCB3B0, 0x00738BBD, 0x00000000, 0x00000054,
    0x00BCB39C, 0x0042EFC0, 0x00000000, 0x00000058,
    0x00BCB38C, 0x0042EFC0, 0x00000000, 0x0000005C,
    0x00BCB378, 0x00738BBD, 0x00000000, 0x00000060,
    0x00BCB360, 0x0042E850, 0x00000000, 0x00000068,
    0x00BCB348, 0x0042E850, 0x00000000, 0x0000006B,
    0x00BCB338, 0x0042EC4E, 0x00DB960C, 0x00000064,
    0x00BCB314, 0x0042EB38, 0x00DBC284, 0x00000050,
    0x00BCB2F8, 0x004C8914, 0x00000001, 0x00000000,
    0x00BCB2E4, 0x004C8914, 0x00000000, 0x00000000,
    0x00BCB2D0, 0x004C9146, 0x00000001, 0x00000000,
    0x00BCB2C0, 0x004C9146, 0x00000002, 0x00000000,
    0x00BCB2B0, 0x004C9146, 0x00000000, 0x00000000,
    0x00BCB2A4, 0x004B6E5A, 0x00000000, 0x0000003C,
    0x00BCB294, 0x0042E896, 0x00000000, 0x00000030,
    0x00BCB278, 0x004B6E5A, 0x00000000, 0x00000040,
    0x00BCB25C, 0x004B9468, 0x00000000, 0x000000BC,
    0x00BCB248, 0x004C4BAE, 0x00000000, 0x00000000,
    0x00BCB234, 0x0042E850, 0x00000000, 0x000000B8,
    0x00BCB228, 0x0042E850, 0x00000000, 0x00000069,
    0x00BCB210, 0x0042E850, 0x00000000, 0x0000006A,
    0x00BCB200, 0x004C855C, 0x00000000, 0x00000000,
    0x00BCB1E0, 0x0042E850, 0x00000000, 0x00000088,
    0x00BCB1D0, 0x004C3C59, 0x00000000, 0x00000000,
    0x00BCB1C4, 0x004C8748, 0x00000000, 0x00000000,
    0x00BCB1A0, 0x0042E850, 0x00000000, 0x00000108,
    0x00BCB18C, 0x0042F11E, 0x00000000, 0x00000044,
    0x00BCB178, 0x0042F11E, 0x00000000, 0x00000048,
    0x00BCB16C, 0x0042F11E, 0x00000000, 0x00000114,
    0x00BCB160, 0x0042F11E, 0x00000000, 0x00000118,
    0x00BCB154, 0x004C39F5, 0x00000000, 0x0000011C,
    0x00BCB144, 0x0042F11E, 0x00000000, 0x0000010C,
    0x00BCB134, 0x0042F11E, 0x00000000, 0x00000110,
    0x00BCB128, 0x0042E850, 0x00000000, 0x00000128,
    0x00BCB118, 0x0042E850, 0x00000000, 0x00000129,
    0x00BCB0FC, 0x0042E850, 0x00000000, 0x0000012A,
    0x00BCB0E8, 0x0042E850, 0x00000000, 0x0000012B,
    0x00BCB0D0, 0x0042EFC0, 0x00000000, 0x0000012C,
    0x00BCB0B8, 0x0042EFC0, 0x00000000, 0x00000130,
    0x00BCB0A4, 0x0042E850, 0x00000000, 0x00000134,
    0x00BCB090, 0x0042E850, 0x00000000, 0x00000135,
    0x00BCB074, 0x0042E850, 0x00000000, 0x00000136,
    0x00BCB05C, 0x0042E850, 0x00000000, 0x00000137,
    0x00BCB048, 0x0042E850, 0x00000000, 0x00000138,
    0x00BCB034, 0x0042E850, 0x00000000, 0x00000139,
    0x00BCB024, 0x0042F5BA, 0x00000000, 0x0000013C,
    0x00BCB010, 0x0042F11E, 0x00000000, 0x00000014,
    0x00BCAFF4, 0x0042EFDC, 0x00000000, 0x00000144,
    0x00BCAFD8, 0x0042EFDC, 0x00000000, 0x00000148,
    0x00BCAFBC, 0x0042F1BA, 0x00000000, 0x0000014C,
    0x00BCAFA0, 0x0042EF56, 0x00000000, 0x00000158,
    0x00BCAF90, 0x00738B30, 0x00000000, 0x00000150,
    0x00BCAF7C, 0x0042E850, 0x00000000, 0x00000154,
    0x00BCAF64, 0x0042E850, 0x00000000, 0x0000015C,
    0x00BCAF54, 0x0042E850, 0x00000000, 0x0000015D,
    0x00BCAF40, 0x0042E850, 0x00000000, 0x0000015E,
    0x00BCAF30, 0x0042E850, 0x00000000, 0x0000015F,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

// Retail VA 0x00bcb840: 16 entries + terminator (272B).
extern const FieldParse s_laserDrawFieldTable[17] = {
    { "NumBeams", (FieldParseProc)&__identifier("?parseUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x20 },
    { "InnerBeamWidth", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x10 },
    { "OuterBeamWidth", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x14 },
    { "InnerColor", (FieldParseProc)&__identifier("?parseColorInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x8 },
    { "OuterColor", (FieldParseProc)&__identifier("?parseColorInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xC },
    { "MaxIntensityLifetime", (FieldParseProc)&__identifier("?parseDurationUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x24 },
    { "FadeLifetime", (FieldParseProc)&__identifier("?parseDurationUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x28 },
    { "Texture", (FieldParseProc)&__identifier("?parseAsciiStringVectorAppend@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x2C },
    { "ScrollRate", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x18 },
    { "Tile", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x1C },
    { "Segments", (FieldParseProc)&__identifier("?parseUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x38 },
    { "ArcHeight", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x3C },
    { "SegmentOverlapRatio", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x40 },
    { "TilingScalar", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x44 },
    { "FanWidth", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x48 },
    { "Envelope", (FieldParseProc)&__identifier("?Rva00338E52_ParseEnvelope@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x4C },
    { 0, 0, 0, 0 },
};

// Retail VA 0x00bcd918: 10 entries (no terminator) (160B).
extern const FieldParse s_lightDrawFieldTable[10] = {
    { "Ambient", (FieldParseProc)&__identifier("?parseRGBColor@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x8 },
    { "Diffuse", (FieldParseProc)&__identifier("?parseRGBColor@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x14 },
    { "Specular", (FieldParseProc)&__identifier("?parseRGBColor@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x20 },
    { "Radius", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x2C },
    { "Intensity", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x30 },
    { "FlickerAmplitude", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x34 },
    { "FlickerFrequency", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x38 },
    { "PulseAmplitude", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x3C },
    { "PulseFrequency", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x40 },
    { "AttachToBoneInAnotherModule", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x44 },
};

// Retail VA 0x00c5f064: 2 entries + terminator (48B).
extern const FieldParse s_animSoundFieldTable[3] = {
    { "AnimationSound", (FieldParseProc)&__identifier("?Rva004CA798Parse@@YAXPAVINI@@PAX1@Z"), 0, 0x0 },
    { "MaxUpdateRangeCap", (FieldParseProc)&__identifier("?parsePositiveNonZeroReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x14 },
    { 0, 0, 0, 0 },
};

// Retail VA 0x00c5a7a8: 11 entries + terminator (192B).
extern const FieldParse CrateCollideTable[12] = {
    { "RequiredKindOf", (FieldParseProc)&__identifier("?Rva002567EAParse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x8 },
    { "ForbiddenKindOf", (FieldParseProc)&__identifier("?Rva002567EAParse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x24 },
    { "ForbidOwnerPlayer", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x40 },
    { "BuildingPickup", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x41 },
    { "HumanOnly", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x42 },
    { "PickupScience", (FieldParseProc)&__identifier("?parseScience@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x44 },
    { "ExecuteFX", (FieldParseProc)&__identifier("?parseFXList@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x48 },
    { "ExecuteAnimation", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x4C },
    { "ExecuteAnimationTime", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x50 },
    { "ExecuteAnimationZRise", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x54 },
    { "ExecuteAnimationFades", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x58 },
    { 0, 0, 0, 0 },
};

// Retail VA 0x00c5a4a8: 16 entries + terminator (272B).
extern const int AODCrushCollideTable[68] = {
    0x00C5A498, 0x00738A09, 0x00000000, 0x00000008,
    0x00C5A480, 0x00738A6F, 0x00000000, 0x0000000C,
    0x00C5A470, 0x00738A09, 0x00000000, 0x00000010,
    0x00C5A454, 0x00738A6F, 0x00000000, 0x00000014,
    0x00C5A448, 0x00738A09, 0x00000000, 0x00000018,
    0x00C5A430, 0x00738A6F, 0x00000000, 0x0000001C,
    0x00C03E1C, 0x0042EFC0, 0x00000000, 0x00000028,
    0x00C015C8, 0x0042EC4E, 0x00DCD4D0, 0x00000020,
    0x00C015BC, 0x0042EC4E, 0x00DCD550, 0x00000024,
    0x00C5A420, 0x0042EFC0, 0x00000000, 0x00000038,
    0x00C5A40C, 0x0042EC4E, 0x00DCD4D0, 0x00000030,
    0x00C5A3F8, 0x0042EC4E, 0x00DCD550, 0x00000034,
    0x00C5A3EC, 0x0042EFC0, 0x00000000, 0x00000044,
    0x00C5A3DC, 0x0042EC4E, 0x00DCD4D0, 0x0000003C,
    0x00C5A3CC, 0x0042EC4E, 0x00DCD550, 0x00000040,
    0x00C3F700, 0x00761CA5, 0x00000000, 0x0000002C,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

// Retail VA 0x00befabc: 1 entries + terminator (32B).
extern const FieldParse s_moneyCrateFieldTable[2] = {
    { "MoneyProvided", (FieldParseProc)&__identifier("?parseUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x5C },
    { 0, 0, 0, 0 },
};

// Retail VA 0x00befb60: 4 entries + terminator (80B).
extern const FieldParse s_veterancyCrateFieldTable[5] = {
    { "EffectRange", (FieldParseProc)&__identifier("?parseUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x5C },
    { "AddsOwnerVeterancy", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x60 },
    { "IsPilot", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x61 },
    { "AffectsUpToLevel", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x64 },
    { 0, 0, 0, 0 },
};

// Retail VA 0x00bf9378: 19 entries + terminator (320B).
extern const int s_transportAiFieldTable[80] = {
    0x00BCA7FC, 0x006623C1, 0x00000000, 0x00000014,
    0x00BF9368, 0x0042F11E, 0x00000000, 0x00000044,
    0x00BF934C, 0x0042EB38, 0x00DBB4C4, 0x0000001C,
    0x00BF9338, 0x0042EFC0, 0x00000000, 0x00000020,
    0x00BF932C, 0x0042E850, 0x00000000, 0x00000024,
    0x00BF9318, 0x00738B30, 0x00000000, 0x00000018,
    0x00BF9300, 0x0042E850, 0x00000000, 0x00000025,
    0x00BF92E0, 0x0042EFC0, 0x00000000, 0x00000028,
    0x00BF92D0, 0x0042F11E, 0x00000000, 0x0000002C,
    0x00BF92C0, 0x00738B30, 0x00000000, 0x00000034,
    0x00BF92B0, 0x00738B30, 0x00000000, 0x00000030,
    0x00BF92A4, 0x00738B30, 0x00000000, 0x00000038,
    0x00BF928C, 0x0042E850, 0x00000000, 0x0000003C,
    0x00BF9278, 0x00738B30, 0x00000000, 0x00000040,
    0x00BF9258, 0x00738B30, 0x00000000, 0x00000048,
    0x00BF9244, 0x0042EC4E, 0x00DBB4F0, 0x00000050,
    0x00BF922C, 0x0042EFC0, 0x00000000, 0x0000004C,
    0x00BF9214, 0x0042E896, 0x00000000, 0x00000058,
    0x00BF9204, 0x0042E850, 0x00000000, 0x00000054,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

// Retail VA 0x00bef4b0: 8 entries + terminator (144B).
extern const FieldParse s_supplyTruckAiFieldTable[9] = {
    { "MaxBoxes", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x64 },
    { "SupplyCenterActionDelay", (FieldParseProc)&__identifier("?parseDurationUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x68 },
    { "SupplyWarehouseActionDelay", (FieldParseProc)&__identifier("?parseDurationUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x6C },
    { "SupplyWarehouseScanDistance", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x70 },
    { "HarvestTrees", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x74 },
    { "HarvestActivationRange", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x78 },
    { "HarvestPreparationTime", (FieldParseProc)&__identifier("?parseDurationUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x7C },
    { "HarvestActionTime", (FieldParseProc)&__identifier("?parseDurationUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x80 },
    { 0, 0, 0, 0 },
};

// Retail VA 0x00beecb0: 7 entries + terminator (128B).
extern const FieldParse s_deployStyleFieldTable[8] = {
    { "UnpackTime", (FieldParseProc)&__identifier("?parseDurationUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x64 },
    { "PackTime", (FieldParseProc)&__identifier("?parseDurationUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x68 },
    { "ResetTurretBeforePacking", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x6C },
    { "TurretsFunctionOnlyWhenDeployed", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x6D },
    { "TurretsMustCenterBeforePacking", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x6E },
    { "MustDeployToAttack", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x6F },
    { "DeployedAttributeModifier", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x70 },
    { 0, 0, 0, 0 },
};

// Retail VA 0x00beed74: 2 entries + terminator (48B).
extern const FieldParse s_assaultTransportFieldTable[3] = {
    { "MembersGetHealedAtLifeRatio", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x64 },
    { "ClearRangeRequiredToContinueAttackMove", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x68 },
    { 0, 0, 0, 0 },
};

// Retail VA 0x00beeb88: 7 entries + terminator (128B).
extern const FieldParse s_animalAiFieldTable[8] = {
    { "FleeRange", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x64 },
    { "FleeDistance", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x68 },
    { "WanderPercentage", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x6C },
    { "MaxWanderDistance", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x70 },
    { "MaxWanderRadius", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x74 },
    { "UpdateTimer", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x78 },
    { "AfraidOfCastles", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x7C },
    { 0, 0, 0, 0 },
};

// Retail VA 0x00bef580: 4 entries + terminator (80B).
extern const FieldParse s_wanderAiFieldTable[5] = {
    { "WildBeast", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x64 },
    { "ConditionForEntry", (FieldParseProc)&__identifier("?iniParseAnim@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x68 },
    { "Selectable", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x6C },
    { "WanderDistance", (FieldParseProc)&__identifier("?parseUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x70 },
    { 0, 0, 0, 0 },
};

// Retail VA 0x00c561d0: 14 entries + terminator (240B).
extern const FieldParse s_respawnFieldTable[15] = {
    { "DeathAnim", (FieldParseProc)&__identifier("?Rva000B9468Parse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0xC },
    { "DeathFX", (FieldParseProc)&__identifier("?parseFXList@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xF0 },
    { "DeathAnimationTime", (FieldParseProc)&__identifier("?parseDurationUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xFC },
    { "InitialSpawnAnim", (FieldParseProc)&__identifier("?Rva000B9468Parse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0xA4 },
    { "InitialSpawnFX", (FieldParseProc)&__identifier("?parseFXList@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xF8 },
    { "InitialSpawnAnimationTime", (FieldParseProc)&__identifier("?parseDurationUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x104 },
    { "RespawnAnim", (FieldParseProc)&__identifier("?Rva000B9468Parse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x58 },
    { "RespawnFX", (FieldParseProc)&__identifier("?parseFXList@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xF4 },
    { "RespawnAnimationTime", (FieldParseProc)&__identifier("?parseDurationUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x100 },
    { "AutoRespawnAtObjectFilter", (FieldParseProc)&__identifier("?iniParseObjectFilter@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x8 },
    { "RespawnRules", (FieldParseProc)&__identifier("?iniParseDefaultRule@RespawnUpdate@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x10C },
    { "RespawnEntry", (FieldParseProc)&__identifier("?iniParseNewRuleForLevel@RespawnUpdate@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x10C },
    { "ButtonImage", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x118 },
    { "RespawnAsTemplate", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x11C },
    { 0, 0, 0, 0 },
};

// Retail VA 0x00c42a38: 12 entries + terminator (208B).
extern const FieldParse s_dynamicPortalFieldTable[13] = {
    { "BonePrefix", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x11C },
    { "NumberOfBones", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x118 },
    { "WayPoint", (FieldParseProc)&__identifier("?parseWayPoint@DynamicPortalBehaviourData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x120 },
    { "Link", (FieldParseProc)&__identifier("?parseLink@DynamicPortalBehaviourData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x12C },
    { "WallBoundsMesh", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x138 },
    { "GenerateNow", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x13C },
    { "AboveWall", (FieldParseProc)&__identifier("?parseUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x140 },
    { "TopAttackPos", (FieldParseProc)&__identifier("?parseCoord3D@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x144 },
    { "TopAttackRadius", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x150 },
    { "AllowEnemies", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x13D },
    { "ActivationDelaySeconds", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x154 },
    { "ObjectFilter", (FieldParseProc)&__identifier("?iniParseObjectFilter@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x158 },
    { 0, 0, 0, 0 },
};

// Retail VA 0x00c52790: 11 entries + terminator (192B).
extern const FieldParse s_structureCollapseFieldTable[12] = {
    { "MinCollapseDelay", (FieldParseProc)&__identifier("?parseDurationUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x38 },
    { "MaxCollapseDelay", (FieldParseProc)&__identifier("?parseDurationUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x3C },
    { "MinBurstDelay", (FieldParseProc)&__identifier("?parseDurationUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x40 },
    { "MaxBurstDelay", (FieldParseProc)&__identifier("?parseDurationUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x44 },
    { "CollapseDamping", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x4C },
    { "MaxShudder", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x50 },
    { "BigBurstFrequency", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x48 },
    { "OCL", (FieldParseProc)&__identifier("?parseOCL@StructureCollapseUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x0 },
    { "FXList", (FieldParseProc)&__identifier("?parseFXList@StructureCollapseUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x0 },
    { "DestroyObjectWhenDone", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xF4 },
    { "CollapseHeight", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xF8 },
    { 0, 0, 0, 0 },
};

// Retail VA 0x00c44648: 33 entries + terminator (544B).
extern const FieldParse s_transportContainFieldTable[34] = {
    { "Slots", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x98 },
    { "ScatterNearbyOnExit", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x13E },
    { "OrientLikeContainerOnExit", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x13F },
    { "GoAggressiveOnExit", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x140 },
    { "ResetMoodCheckTimeOnExit", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x141 },
    { "DestroyRidersWhoAreNotFreeToExit", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x142 },
    { "ExitBone", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xA0 },
    { "ExitPitchRate", (FieldParseProc)&__identifier("?parseAngularVelocityReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x9C },
    { "InitialPayload", (FieldParseProc)&__identifier("?rva00467DE6@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x0 },
    { "HealthRegen%PerSec", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xA8 },
    { "ExitDelay", (FieldParseProc)&__identifier("?parseDurationUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xAC },
    { "TypeOneForWeaponSet", (FieldParseProc)&__identifier("?Rva002567EAParse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0xB0 },
    { "TypeTwoForWeaponSet", (FieldParseProc)&__identifier("?Rva002567EAParse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0xCC },
    { "TypeOneForWeaponState", (FieldParseProc)&__identifier("?Rva002567EAParse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0xE8 },
    { "TypeTwoForWeaponState", (FieldParseProc)&__identifier("?Rva002567EAParse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x104 },
    { "TypeThreeForWeaponState", (FieldParseProc)&__identifier("?Rva002567EAParse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x120 },
    { "ForceOrientationContainer", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x13C },
    { "CanGrabStructure", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x13D },
    { "GrabWeapon", (FieldParseProc)&__identifier("?parseWeaponTemplate@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x144 },
    { "FireGrabWeaponOnVictim", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x148 },
    { "ConditionForEntry", (FieldParseProc)&__identifier("?iniParseAnim@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x14C },
    { "ShouldThrowOutPassengers", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x150 },
    { "ThrowOutPassengersDelay", (FieldParseProc)&__identifier("?parseDurationUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x154 },
    { "ThrowOutPassengersVelocity", (FieldParseProc)&__identifier("?parseCoord3D@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x158 },
    { "ThrowOutPassengersLandingWarhead", (FieldParseProc)&__identifier("?parseWeaponTemplate@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x164 },
    { "FadeFilter", (FieldParseProc)&__identifier("?iniParseObjectFilter@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x168 },
    { "FadePassengerOnEnter", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x16C },
    { "FadePassengerOnExit", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x16D },
    { "EnterFadeTime", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x170 },
    { "ExitFadeTime", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x174 },
    { "FadeReverse", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x178 },
    { "ReleaseSnappyness", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x17C },
    { "UpgradeCreationTrigger", (FieldParseProc)&__identifier("?Rva00468908Parse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x0 },
    { 0, 0, 0, 0 },
};

// Retail VA 0x00c487f8: 3 entries + terminator (64B).
extern const FieldParse s_slaughterHordeFieldTable[4] = {
    { "CashBackPercent", (FieldParseProc)&__identifier("?parsePercentToReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xD4 },
    { "CanAlwaysEnter", (FieldParseProc)&__identifier("?iniParseObjectFilter@@YAXPAVINI@@PAX1PBX@Z"), 0, 0xD8 },
    { "StatusRequiredForCanAlwaysEnter", (FieldParseProc)&__identifier("?parseFromINI@Rva003B1017@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xDC },
    { 0, 0, 0, 0 },
};

// Retail VA 0x00c45530: 39 entries + terminator (640B).
extern const FieldParse s_hordeContainFieldTable[40] = {
    { "ThisFormationIsTheMainFormation", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x1D8 },
    { "RankInfo", (FieldParseProc)&__identifier("?parseRankInfo@HordeContainModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x18C },
    { "RanksThatStopAdvance", (FieldParseProc)&__identifier("?parseHordeContainRanksThatStopAdvance@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x1B4 },
    { "RanksToReleaseWhenAttacking", (FieldParseProc)&__identifier("?parseHordeContainRankSets@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x1B8 },
    { "RanksToJustFreeWhenAttacking", (FieldParseProc)&__identifier("?parseHordeContainRankSets@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x1C4 },
    { "ComboHorde", (FieldParseProc)&__identifier("?parseHordeContainComboHorde@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x198 },
    { "AlternateFormation", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x1B0 },
    { "RandomOffset", (FieldParseProc)&__identifier("?parseCoord2D@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x1D0 },
    { "LeaderPosition", (FieldParseProc)&__identifier("?parseCoord3D@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x200 },
    { "LeadersAllowed", (FieldParseProc)&__identifier("?parseAsciiStringVector@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x1F4 },
    { "BannerCarrierPosition", (FieldParseProc)&__identifier("?parseBannerCarrierPosition@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x20C },
    { "BannerCarriersAllowed", (FieldParseProc)&__identifier("?parseAsciiStringVector@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x218 },
    { "LeaderRank", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x208 },
    { "BackUpMinDelayTime", (FieldParseProc)&__identifier("?parseDurationUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x1DC },
    { "BackUpMaxDelayTime", (FieldParseProc)&__identifier("?parseDurationUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x1E0 },
    { "BackUpMinDistance", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x1E4 },
    { "BackUpMaxDistance", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x1E8 },
    { "BackupPercentage", (FieldParseProc)&__identifier("?parsePercentToReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x1EC },
    { "CowerRadius", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x1F0 },
    { "AttributeModifiers", (FieldParseProc)&__identifier("?parseAsciiStringVector@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x224 },
    { "IsPorcupineFormation", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x230 },
    { "ForcedLocomotorSet", (FieldParseProc)&__identifier("?parseIndexList@INI@@SAXPAV1@PAX1PBX@Z"), TheLocomotorSetNames, 0x234 },
    { "MachineAllowed", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x238 },
    { "MachineType", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x23C },
    { "UseSlowHordeMovement", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x240 },
    { "SplitHorde", (FieldParseProc)&__identifier("?parseHordeContainSplitResult@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x1A4 },
    { "MeleeAttackLeashDistance", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x244 },
    { "EvaEventLastMemberDeath", (FieldParseProc)&__identifier("?Rva001DEE74Parse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x248 },
    { "RankSplit", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x24C },
    { "SplitHordeNumber", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x250 },
    { "NotComboFormation", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x254 },
    { "UseMarchingAnims", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x255 },
    { "FrontAngle", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x25C },
    { "FlankedDelay", (FieldParseProc)&__identifier("?parseDurationUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x260 },
    { "FlankedDuration", (FieldParseProc)&__identifier("?parseDurationUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x264 },
    { "MeleeBehavior", (FieldParseProc)&__identifier("?parseMeleeBehavior@HordeContainModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x258 },
    { "MinimumHordeSize", (FieldParseProc)&__identifier("?parseUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x268 },
    { "VisionRearOverride", (FieldParseProc)&__identifier("?parsePercentToReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x26C },
    { "VisionSideOverride", (FieldParseProc)&__identifier("?parsePercentToReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x270 },
    { 0, 0, 0, 0 },
};

// Retail VA 0x00bef620: 12 entries + terminator (208B).
extern const FieldParse s_workerAiFieldTable[13] = {
    { "MaxBoxes", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x64 },
    { "RepairHealthPercentPerSecond", (FieldParseProc)&__identifier("?parsePercentToReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x68 },
    { "BoredTime", (FieldParseProc)&__identifier("?parseDurationReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x6C },
    { "BoredRange", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x70 },
    { "SupplyCenterActionDelay", (FieldParseProc)&__identifier("?parseDurationUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x74 },
    { "SupplyWarehouseActionDelay", (FieldParseProc)&__identifier("?parseDurationUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x78 },
    { "SupplyWarehouseScanDistance", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x7C },
    { "HarvestTrees", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x80 },
    { "SuppliesDepletedVoice", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x90 },
    { "HarvestActivationRange", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x84 },
    { "HarvestPreparationTime", (FieldParseProc)&__identifier("?parseDurationUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x88 },
    { "HarvestActionTime", (FieldParseProc)&__identifier("?parseDurationUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x8C },
    { 0, 0, 0, 0 },
};

// Retail VA 0x00c46ec8: 7 entries + terminator (128B).
extern const FieldParse s_siegeEngineFieldTable[8] = {
    { "CrewFilter", (FieldParseProc)&__identifier("?iniParseObjectFilter@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x18C },
    { "CrewMax", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x190 },
    { "InitialCrew", (FieldParseProc)&__identifier("?parseInitialCrew@SiegeEngineContainModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x0 },
    { "SpeedPercentPerCrew", (FieldParseProc)&__identifier("?parsePercentToReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x19C },
    { "CrewAllowedToFire", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x1A0 },
    { "ObjectStatusOfCrew", (FieldParseProc)&__identifier("?Rva00464081ParseMask@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x1A4 },
    { "TransferSelection", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x1B4 },
    { 0, 0, 0, 0 },
};

// Retail VA 0x00c48890: 4 entries + terminator (80B).
extern const FieldParse s_citadelSlaughterFieldTable[5] = {
    { "StatusForRingEntry", (FieldParseProc)&__identifier("?parseFromINI@Rva003B1017@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xEC },
    { "UpgradeForRingEntry", (FieldParseProc)&__identifier("?parseAsciiStringVector@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x100 },
    { "ObjectToDestroyForRingEntry", (FieldParseProc)&__identifier("?iniParseObjectFilter@@YAXPAVINI@@PAX1PBX@Z"), 0, 0xFC },
    { "FXForRingEntry", (FieldParseProc)&__identifier("?parseFXList@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x10C },
    { 0, 0, 0, 0 },
};

// Retail VA 0x00c4e8b0: 4 entries + terminator (80B).
extern const FieldParse s_weaponModeFieldTable[5] = {
    { "Duration", (FieldParseProc)&__identifier("?parseDurationUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x1C },
    { "AttributeModifier", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x18 },
    { "LockWeaponSlot", (FieldParseProc)&__identifier("?parseLookupList@INI@@SAXPAV1@PAX1PBX@Z"), TheWeaponSlotTypeNamesLookupList, 0x20 },
    { "WeaponSetFlags", (FieldParseProc)&__identifier("?Rva002C8C06Parse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x24 },
    { 0, 0, 0, 0 },
};

// Retail VA 0x00c47208: 6 entries (no terminator) (96B).
extern const FieldParse s_hordeSiegeEngineFieldTable[6] = {
    { "CrewFilter", (FieldParseProc)&__identifier("?iniParseObjectFilter@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x18C },
    { "CrewMax", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x190 },
    { "InitialCrew", (FieldParseProc)&__identifier("?parseInitialCrew@SiegeEngineContainModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x0 },
    { "SpeedPercentPerCrew", (FieldParseProc)&__identifier("?parsePercentToReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x19C },
    { "CrewAllowedToFire", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x1A0 },
    { "ObjectStatusOfCrew", (FieldParseProc)&__identifier("?Rva00464081ParseMask@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x1A4 },
};

// Retail VA 0x00bc6b80: 1 entries + terminator (32B).
extern const FieldParse s_hordeModelDrawFieldTable[2] = {
    { "LodOptions", (FieldParseProc)&__identifier("?parseLodOptions@W3DModelDrawModuleData@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x0 },
    { 0, 0, 0, 0 },
};

// Retail VA 0x00c3a304: 2 entries + terminator (48B).
extern const FieldParse s_crowdResponseFieldTable[3] = {
    { "Weight", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x4 },
    { "Threshold", (FieldParseProc)&__identifier("?Rva00415B91Parse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x8 },
    { 0, 0, 0, 0 },
};

// Retail VA 0x00c0dc20: 13 entries + terminator (224B).
extern const int s_radiusDecalFieldTable[56] = {
    0x00BCA9B0, 0x0042F11E, 0x00000000, 0x00000000,
    0x00C0DC14, 0x0042F11E, 0x00000000, 0x00000004,
    0x00C0DC0C, 0x0042EB38, 0x00DBE6F0, 0x00000008,
    0x00C0DC00, 0x0042F1BA, 0x00000000, 0x0000000C,
    0x00C0DBF4, 0x0042F1BA, 0x00000000, 0x00000010,
    0x00C0DBE0, 0x0042EFC0, 0x00000000, 0x00000014,
    0x00C0DBCC, 0x0042EFC0, 0x00000000, 0x0000002C,
    0x00BCDB38, 0x0042F3FE, 0x00000000, 0x00000018,
    0x00C0DBB0, 0x0042E850, 0x00000000, 0x0000001C,
    0x00C0DBA4, 0x0042EFC0, 0x00000000, 0x00000024,
    0x00C0DB98, 0x0042EFC0, 0x00000000, 0x00000020,
    0x00C0DB84, 0x0042EF72, 0x00000000, 0x00000028,
    0x00C0DB70, 0x0042EFC0, 0x00000000, 0x00000030,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

// Retail VA 0x00c100c0: 56 entries + terminator (912B).
extern const FieldParse s_rva0033A8FCFieldTableB[57] = {
    { "VoiceSelect", (FieldParseProc)&__identifier("?Rva003393DFParse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x0 },
    { "VoiceSelectUnderConstruction", (FieldParseProc)&__identifier("?Rva003393DFParse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x8 },
    { "VoiceSelectBattle", (FieldParseProc)&__identifier("?Rva003393DFParse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x10 },
    { "VoiceMove", (FieldParseProc)&__identifier("?Rva003393DFParse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x18 },
    { "VoiceMoveToHigherGround", (FieldParseProc)&__identifier("?Rva003393DFParse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x20 },
    { "VoiceMoveOverWalls", (FieldParseProc)&__identifier("?Rva003393DFParse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x28 },
    { "VoiceAttack", (FieldParseProc)&__identifier("?Rva003393DFParse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x30 },
    { "VoiceAttackCharge", (FieldParseProc)&__identifier("?Rva003393DFParse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x38 },
    { "VoiceFear", (FieldParseProc)&__identifier("?Rva003393DFParse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x40 },
    { "VoiceCreated", (FieldParseProc)&__identifier("?Rva003393DFParse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x48 },
    { "VoiceTaskComplete", (FieldParseProc)&__identifier("?Rva003393DFParse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x50 },
    { "VoiceDefect", (FieldParseProc)&__identifier("?Rva003393DFParse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x58 },
    { "VoiceAttackAir", (FieldParseProc)&__identifier("?Rva003393DFParse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x60 },
    { "VoiceGuard", (FieldParseProc)&__identifier("?Rva003393DFParse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x68 },
    { "VoiceAlert", (FieldParseProc)&__identifier("?Rva003393DFParse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x70 },
    { "VoiceFullyCreated", (FieldParseProc)&__identifier("?Rva003393DFParse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x78 },
    { "VoiceRetreatToCastle", (FieldParseProc)&__identifier("?Rva003393DFParse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x80 },
    { "VoiceMoveToCamp", (FieldParseProc)&__identifier("?Rva003393DFParse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x88 },
    { "VoiceAttackStructure", (FieldParseProc)&__identifier("?Rva003393DFParse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x90 },
    { "VoiceAttackMachine", (FieldParseProc)&__identifier("?Rva003393DFParse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x98 },
    { "VoiceMoveWhileAttacking", (FieldParseProc)&__identifier("?Rva003393DFParse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0xA0 },
    { "VoiceCombineWithHorde", (FieldParseProc)&__identifier("?Rva003393DFParse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0xA8 },
    { "VoiceEnterStateAttack", (FieldParseProc)&__identifier("?Rva003393DFParse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0xB0 },
    { "VoiceEnterStateAttackCharge", (FieldParseProc)&__identifier("?Rva003393DFParse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0xB8 },
    { "VoiceEnterStateAttackAir", (FieldParseProc)&__identifier("?Rva003393DFParse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0xC0 },
    { "VoiceEnterStateAttackStructure", (FieldParseProc)&__identifier("?Rva003393DFParse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0xC8 },
    { "VoiceEnterStateAttackMachine", (FieldParseProc)&__identifier("?Rva003393DFParse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0xD0 },
    { "VoiceEnterStateMove", (FieldParseProc)&__identifier("?Rva003393DFParse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0xD8 },
    { "VoiceEnterStateMoveToHigherGround", (FieldParseProc)&__identifier("?Rva003393DFParse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0xE0 },
    { "VoiceEnterStateMoveOverWalls", (FieldParseProc)&__identifier("?Rva003393DFParse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0xE8 },
    { "VoiceEnterStateRetreatToCastle", (FieldParseProc)&__identifier("?Rva003393DFParse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0xF0 },
    { "VoiceEnterStateMoveToCamp", (FieldParseProc)&__identifier("?Rva003393DFParse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0xF8 },
    { "VoiceEnterStateMoveWhileAttacking", (FieldParseProc)&__identifier("?Rva003393DFParse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x100 },
    { "SoundMoveStart", (FieldParseProc)&__identifier("?Rva003393F7Parse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x108 },
    { "SoundMoveStartDamaged", (FieldParseProc)&__identifier("?Rva003393F7Parse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x110 },
    { "SoundMoveLoop", (FieldParseProc)&__identifier("?Rva003393F7Parse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x118 },
    { "SoundMoveLoopDamaged", (FieldParseProc)&__identifier("?Rva003393F7Parse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x120 },
    { "SoundAmbient", (FieldParseProc)&__identifier("?Rva003393F7Parse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x128 },
    { "SoundAmbientDamaged", (FieldParseProc)&__identifier("?Rva003393F7Parse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x130 },
    { "SoundAmbientReallyDamaged", (FieldParseProc)&__identifier("?Rva003393F7Parse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x138 },
    { "SoundAmbientRubble", (FieldParseProc)&__identifier("?Rva003393F7Parse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x140 },
    { "SoundAmbientBattle", (FieldParseProc)&__identifier("?Rva003393F7Parse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x148 },
    { "SoundStealthOn", (FieldParseProc)&__identifier("?Rva003393F7Parse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x150 },
    { "SoundStealthOff", (FieldParseProc)&__identifier("?Rva003393F7Parse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x158 },
    { "SoundCreated", (FieldParseProc)&__identifier("?Rva003393F7Parse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x160 },
    { "SoundOnDamaged", (FieldParseProc)&__identifier("?Rva003393F7Parse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x168 },
    { "SoundOnReallyDamaged", (FieldParseProc)&__identifier("?Rva003393F7Parse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x170 },
    { "SoundEnter", (FieldParseProc)&__identifier("?Rva003393F7Parse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x178 },
    { "SoundExit", (FieldParseProc)&__identifier("?Rva003393F7Parse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x180 },
    { "SoundPromotedVeteran", (FieldParseProc)&__identifier("?Rva003393F7Parse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x188 },
    { "SoundPromotedElite", (FieldParseProc)&__identifier("?Rva003393F7Parse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x190 },
    { "SoundPromotedHero", (FieldParseProc)&__identifier("?Rva003393F7Parse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x198 },
    { "SoundFallingFromPlane", (FieldParseProc)&__identifier("?Rva003393F7Parse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x1A0 },
    { "SoundImpact", (FieldParseProc)&__identifier("?Rva003393F7Parse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x1A8 },
    { "SoundImpactCyclonic", (FieldParseProc)&__identifier("?Rva003393F7Parse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x1B0 },
    { "SoundCrushing", (FieldParseProc)&__identifier("?Rva003393F7Parse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x1B8 },
    { 0, 0, 0, 0 },
};

// Retail VA 0x00c4c0c0: 4 entries + terminator (80B).
extern const FieldParse s_fireWeaponNuggetFieldTableA[5] = {
    { "WeaponName", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x0 },
    { "FireDelay", (FieldParseProc)&__identifier("?parseDurationUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x4 },
    { "OneShot", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x8 },
    { "Offset", (FieldParseProc)&__identifier("?parseCoord3D@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xC },
    { 0, 0, 0, 0 },
};

// Retail VA 0x00c51380: 6 entries + terminator (112B).
extern const FieldParse s_fireWeaponNuggetFieldTableB[7] = {
    { "RequiredUpgrade", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x0 },
    { "ModifierFilter", (FieldParseProc)&__identifier("?iniParseObjectFilter@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x4 },
    { "CostMultiplier", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x8 },
    { "TimeMultiplier", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xC },
    { "HeroPurchase", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x10 },
    { "HeroRevive", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x11 },
    { 0, 0, 0, 0 },
};

// Retail VA 0x00bcd6b0: 6 entries + terminator (112B).
extern const FieldParse s_floorDrawFieldTable[7] = {
    { "StaticModelLODMode", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x1C },
    { "ForceToBack", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x1D },
    { "StartHidden", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x1E },
    { "FloorFadeRateOnObjectDeath", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x20 },
    { "WeatherTexture", (FieldParseProc)&__identifier("?Rva000CF873Parse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x10 },
    { "HideIfModelConditions", (FieldParseProc)&__identifier("?Rva000CF713Parse@@YAXPAVINI@@PAVRva000CF713Owner@@@Z"), 0, 0x0 },
    { 0, 0, 0, 0 },
};

// Retail string at VA 0x00CE7AA8 ("GeometryType"): referenced by
// Rva006BD490RawDispatch as a const-void pointer argument.
extern const char s_geometryTypeString[] = "GeometryType";

// LK2 round 2: FieldParse tables already named by their user TUs (kept here
// in the debt absorber so the users link). Exact retail bytes.
// Retail VA 0x00bc16e8: 74 entries (1200B).
extern const FieldParse g_00BC16E8[75] = {
    { "UseDigital", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x54 },
    { "UseMidi", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x55 },
    { "OutputRate", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x58 },
    { "OutputBits", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x5C },
    { "OutputChannels", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x60 },
    { "SampleCount2D", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x64 },
    { "SampleCount3D", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x68 },
    { "StreamCount", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x6C },
    { "MixaheadLatency", (FieldParseProc)&__identifier("?parseUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x84 },
    { "MixaheadLatencyDuringMovies", (FieldParseProc)&__identifier("?parseUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x88 },
    { "LoopBufferLengthMS", (FieldParseProc)&__identifier("?parseUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x8C },
    { "LoopBufferCallbackCallsPerBufferLength", (FieldParseProc)&__identifier("?parseUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x90 },
    { "AutomaticSubtitleDurationMS", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x94 },
    { "AutomaticSubtitleWindowWidth", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x98 },
    { "AutomaticSubtitleLines", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x9C },
    { "AutomaticSubtitleWindowColor", (FieldParseProc)&__identifier("?parseColorInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xA0 },
    { "AutomaticSubtitleTextColor", (FieldParseProc)&__identifier("?parseColorInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xA4 },
    { "ForceResetTimeSeconds", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xA8 },
    { "EmergencyResetTimeSeconds", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xAC },
    { "SuppressOcclusion", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xBC },
    { "MinOcclusion", (FieldParseProc)&__identifier("?parsePercentToReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xC0 },
    { "MillisecondsPriorToPlayingToReadSoundFile", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xB4 },
    { "MinSampleVolume", (FieldParseProc)&__identifier("?parsePercentToReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xB8 },
    { "PositionDeltaForReverbRecheck", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xB0 },
    { "GlobalMinRange", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x70 },
    { "GlobalMaxRange", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x74 },
    { "TimeToFadeAudio", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x78 },
    { "AmbientStreamHysteresisVolume", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x7C },
    { "AudioFootprintInBytes", (FieldParseProc)&__identifier("?parseUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x80 },
    { "GlobalPaddedCellReverbMultiplier", (FieldParseProc)&__identifier("?parsePercentToReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xC8 },
    { "GlobalRoomReverbMultiplier", (FieldParseProc)&__identifier("?parsePercentToReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xCC },
    { "GlobalBathroomReverbMultiplier", (FieldParseProc)&__identifier("?parsePercentToReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xD0 },
    { "GlobalLivingRoomReverbMultiplier", (FieldParseProc)&__identifier("?parsePercentToReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xD4 },
    { "GlobalStoneRoomReverbMultiplier", (FieldParseProc)&__identifier("?parsePercentToReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xD8 },
    { "GlobalAuditoriumReverbMultiplier", (FieldParseProc)&__identifier("?parsePercentToReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xDC },
    { "GlobalConcertHallReverbMultiplier", (FieldParseProc)&__identifier("?parsePercentToReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xE0 },
    { "GlobalCaveReverbMultiplier", (FieldParseProc)&__identifier("?parsePercentToReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xE4 },
    { "GlobalArenaReverbMultiplier", (FieldParseProc)&__identifier("?parsePercentToReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xE8 },
    { "GlobalHangarReverbMultiplier", (FieldParseProc)&__identifier("?parsePercentToReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xEC },
    { "GlobalCarpetedHallwayReverbMultiplier", (FieldParseProc)&__identifier("?parsePercentToReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xF0 },
    { "GlobalHallwayReverbMultiplier", (FieldParseProc)&__identifier("?parsePercentToReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xF4 },
    { "GlobalStoneCorridorReverbMultiplier", (FieldParseProc)&__identifier("?parsePercentToReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xF8 },
    { "GlobalAlleyReverbMultiplier", (FieldParseProc)&__identifier("?parsePercentToReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xFC },
    { "GlobalForestReverbMultiplier", (FieldParseProc)&__identifier("?parsePercentToReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x100 },
    { "GlobalCityReverbMultiplier", (FieldParseProc)&__identifier("?parsePercentToReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x104 },
    { "GlobalMountainsReverbMultiplier", (FieldParseProc)&__identifier("?parsePercentToReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x108 },
    { "GlobalQuarryReverbMultiplier", (FieldParseProc)&__identifier("?parsePercentToReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x10C },
    { "GlobalPlainReverbMultiplier", (FieldParseProc)&__identifier("?parsePercentToReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x110 },
    { "GlobalParkingLotReverbMultiplier", (FieldParseProc)&__identifier("?parsePercentToReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x114 },
    { "GlobalSewerPipeReverbMultiplier", (FieldParseProc)&__identifier("?parsePercentToReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x118 },
    { "GlobalUnderwaterReverbMultiplier", (FieldParseProc)&__identifier("?parsePercentToReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x11C },
    { "GlobalDruggedReverbMultiplier", (FieldParseProc)&__identifier("?parsePercentToReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x120 },
    { "GlobalDizzyReverbMultiplier", (FieldParseProc)&__identifier("?parsePercentToReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x124 },
    { "GlobalPsychoticReverbMultiplier", (FieldParseProc)&__identifier("?parsePercentToReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x128 },
    { "MicrophonePreferredFractionCameraToGround", (FieldParseProc)&__identifier("?parsePercentToReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x12C },
    { "MicrophonePullTowardsTerrainLookAtPointPercent", (FieldParseProc)&__identifier("?parsePercentToReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x144 },
    { "MicrophoneMinDistanceToCamera", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x134 },
    { "MicrophoneMaxDistanceToCamera", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x13C },
    { "ZoomMinDistance", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x148 },
    { "ZoomMaxDistance", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x150 },
    { "ZoomSoundVolumePercentageAmount", (FieldParseProc)&__identifier("?parsePercentToReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x158 },
    { "ZoomFadeDistanceForMaxEffect", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x15C },
    { "ZoomFadeZeroEffectEdgeLength", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x164 },
    { "ZoomFadeFullEffectEdgeLength", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x16C },
    { "LivingWorldMicrophonePreferredFractionCameraToGround", (FieldParseProc)&__identifier("?parsePercentToReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x174 },
    { "LivingWorldMicrophoneMinDistanceToCamera", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x17C },
    { "LivingWorldMicrophoneMaxDistanceToCamera", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x184 },
    { "LivingWorldZoomMinDistance", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x190 },
    { "LivingWorldZoomMaxDistance", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x198 },
    { "LivingWorldMicrophonePullTowardsTerrainLookAtPointPercent", (FieldParseProc)&__identifier("?parsePercentToReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x18C },
    { "LivingWorldZoomSoundVolumePercentageAmount", (FieldParseProc)&__identifier("?parsePercentToReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x1A0 },
    { "LivingWorldZoomFadeDistanceForMaxEffect", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x1A4 },
    { "LivingWorldZoomFadeZeroEffectEdgeLength", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x1AC },
    { "LivingWorldZoomFadeFullEffectEdgeLength", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x1B4 },
    { 0, 0, 0, 0 },
};

// Retail VA 0x00c61c68: 3 entries (64B).
extern const FieldParse g_00C61C68[4] = {
    { "DelayFromActStart", (FieldParseProc)&__identifier("?dup_002F0F7@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x4 },
    { "Sound", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x8 },
    { "SummaryEvent", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xC },
    { 0, 0, 0, 0 },
};

// Retail VA 0x007FD7C0: Side/Unit plus no terminator (string data follows);
// 32B exact. Named by Rva002A92F2Parse.cpp.
extern const FieldParse AIDozerAssignmentFields[2] = {
    { "Side", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x0 },
    { "Unit", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x4 },
};
