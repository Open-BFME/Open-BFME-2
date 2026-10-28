// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?newOverride@WeaponStore@@QAEPAVWeaponTemplate@@PAV2@@Z, retail 0x002CE063
// (159 bytes).
// Identity (target): WorldBuilder's debug Weapon.cpp:1996
// WeaponStore::newOverride calls operator new, the WeaponTemplate
// constructor (0x002CD169) and copy assignment (0x002CD67C), then the
// template vector's erase and push_back, as retail does.
// Donor (BFME 1 / Zero Hour WeaponStore::newOverride): a new template copied
// from the given one, chained to it as its next template (+0x04). BFME 2
// deltas (target): no override of an override (flag +0x160, set on the new
// one), and the store's template vector (+0x0C) swaps the entry with the
// same name key (+0x0C) for the new template. The 0x180-byte allocation
// and its constructor stand for newInstance(WeaponTemplate).
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
#include "ascii_string.h"

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

typedef void (*FieldParseProc)(class INI *, void *, void *, const void *);
struct FieldParse { const char *token; FieldParseProc parse; const void *userData; int offset; };
// Retail Weapon FieldParse table; its original linker symbol is unestablished.
// The retail name list at RVA 0x009BC64C (4 names and the null terminator).
extern const char *const TheWeaponPrefireNames[5] = { "PER_SHOT", "PER_ATTACK", "PER_CLIP", "PER_POSITION", 0 };
// The retail name list at RVA 0x009BC63C (3 names and the null terminator).
extern const char *const TheWeaponReloadNames[4] = { "YES", "NO", "RETURN_TO_BASE", 0 };
// The retail name list at RVA 0x009BC660 (10 names and the null terminator).
extern const char *const TheWeaponAffectsMaskNames[11] = { "SELF", "ALLIES", "ENEMIES", "NEUTRALS", "SUICIDE", "NOT_SIMILAR", "NOT_AIRBORNE", "PROJECTILES", "SAME_HEIGHT_ONLY", "MINES", 0 };
// The retail name list at RVA 0x009BC68C (11 names and the null terminator).
extern const char *const TheWeaponCollideMaskNames[12] = { "ALLIES", "ENEMIES", "NEUTRAL", "STRUCTURES", "SHRUBBERY", "PROJECTILES", "WALLS", "SMALL_MISSILES", "BALLISTIC_MISSILES", "CONTROLLED_STRUCTURES", "MONSTERS", 0 };
// The retail name list at RVA 0x009BC49C (3 names and the null terminator).
extern const char *const g_00DBC49C[4] = { "NONE", "CATAPULT_ROCK", "TREBUCHET_ROCK", 0 };
struct LookupListRec { const char *name; int value; };
// The retail lookup list at RVA 0x009BC530 (15 names and the null terminator).
extern const LookupListRec g_00DBC530[16] = { { "FORCE", 12426360 }, { "SLASH", 12426344 }, { "SIEGE", 12426324 }, { "FLAME", 12426308 }, { "UNRESISTABLE", 12426284 }, { "PENALTY", 12426268 }, { "TOPPLING", 12426244 }, { "PASSENGER", 12426224 }, { "CHOP", 12426208 }, { "SPECIALIST", 12426188 }, { "HERO_RANGED", 12426164 }, { "UNDEFINED", 12426136 }, { "CAVALRY", 12426112 }, { "POISON", 0 }, { "NORMAL", 12426080 }, { 0, 0 } };
// The retail name list at RVA 0x009BC5B0 (24 names and the null terminator).
extern const char *const TheDeathNames[25] = { "NORMAL", "NONE", "CRUSHED", "BURNED", "EXPLODED", "POISONED", "TOPPLED", "FLOODED", "SUICIDED", "LASERED", "DETONATED", "SPLATTED", "POISONED_BETA", "EXTRA_2", "EXTRA_3", "EXTRA_4", "EXTRA_5", "EXTRA_6", "EXTRA_7", "EXTRA_8", "KNOCKBACK", "SUPERNATURAL", "FADED", "SLAUGHTERED", 0 };
// The retail lookup list at RVA 0x009BC4B0 (15 names and the null terminator).
extern const LookupListRec g_00DBC4B0[16] = { { "SWORD_SLASH", 12591160 }, { "REFLECTED", 12591140 }, { "EVIL_ARROW_PIERCE", 12591108 }, { "BIG_ROCK", 12591084 }, { "FLAME", 12426224 }, { "BALROG_SWORD", 12591056 }, { "ELECTRIC", 12591032 }, { "STRUCTURAL", 12591020 }, { "BOLT", 12591004 }, { "MAGIC2", 12590988 }, { "FIRE1", 12590972 }, { "FIRE3", 12590956 }, { "SPARKS2", 12590940 }, { "EARTH2", 12426104 }, { "TORNADO", 12426152 }, { 0, 0 } };
extern "C" {
void __identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseAngleReal@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseVelocityReal@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseDurationUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseAllVetLevelsFXList@@YAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseFXList@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseAllVetLevelsPSys@@YAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parsePerVetLevelFXList@@YAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parsePerVetLevelPSys@@YAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?iniParseObjectFilter@@YAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parsePercentToReal@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?Rva003393DFParse@@YAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseIndexList@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseBitString32@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseBitInInt32@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseShotDelay@WeaponTemplate@@SAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseClipReloadTime@WeaponTemplate@@SAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseScatterTarget@WeaponTemplate@@CAXPAVINI@@PAX1PBX@Z")();
void __identifier("?Rva002CE849Parse@@YAXPAVINI@@PAX@Z")();
void __identifier("?Rva002CA88BParse@@YAXPAX0@Z")();
void __identifier("?parseDamageNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z")();
void __identifier("?parseClearNuggets@@YAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseDamageFieldNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z")();
void __identifier("?parseWeaponOCLNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z")();
void __identifier("?parseProjectileNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z")();
void __identifier("?parseMetaImpactNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z")();
void __identifier("?parseHordeAttackNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z")();
void __identifier("?parseSpawnAndFadeNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z")();
void __identifier("?parseGrabNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z")();
void __identifier("?parseAttributeModifierNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z")();
void __identifier("?parseSpecialModelConditionNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z")();
void __identifier("?parseParalyzeNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z")();
void __identifier("?parseLuaEventNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z")();
void __identifier("?parseFireLogicNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z")();
void __identifier("?parseSlaveAttackNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z")();
void __identifier("?parseDamageContainedNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z")();
void __identifier("?parseDOTNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z")();
void __identifier("?parseOpenGateNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z")();
void __identifier("?parseEmotionWeaponNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z")();
void __identifier("?parseStealMoneyNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z")();
}
// The retail table at 0x00800B48: 124 entries and the null terminator; every parser is a rowed code owner.
extern const FieldParse g_00C00B48[125] = {
	{ "AttackRange", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x14 },
	{ "MinimumAttackRange", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x18 },
	{ "RangeBonusMinHeight", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x1C },
	{ "RangeBonus", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x20 },
	{ "RangeBonusPerFoot", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x24 },
	{ "RequestAssistRange", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x28 },
	{ "AcceptableAimDelta", (FieldParseProc)&__identifier("?parseAngleReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x2C },
	{ "AimDirection", (FieldParseProc)&__identifier("?parseAngleReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x30 },
	{ "ScatterRadius", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x34 },
	{ "ScatterTargetScalar", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x38 },
	{ "ScatterRadiusVsInfantry", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x14C },
	{ "ScatterIndependently", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x3C },
	{ "DisableScatterForTargetsOnWall", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x3D },
	{ "WeaponSpeed", (FieldParseProc)&__identifier("?parseVelocityReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x68 },
	{ "MinWeaponSpeed", (FieldParseProc)&__identifier("?parseVelocityReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x6C },
	{ "MaxWeaponSpeed", (FieldParseProc)&__identifier("?parseVelocityReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x70 },
	{ "ScaleWeaponSpeed", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x74 },
	{ "CanBeDodged", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x75 },
	{ "IdleAfterFiringDelay", (FieldParseProc)&__identifier("?parseDurationUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x78 },
	{ "HoldAfterFiringDelay", (FieldParseProc)&__identifier("?parseDurationUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x7C },
	{ "HoldDuringReload", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x80 },
	{ "CanFireWhileMoving", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x81 },
	{ "CanFireWhileCharging", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x82 },
	{ "CanSwoop", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x83 },
	{ "WeaponRecoil", (FieldParseProc)&__identifier("?parseAngleReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x84 },
	{ "MinTargetPitch", (FieldParseProc)&__identifier("?parseAngleReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x88 },
	{ "MaxTargetPitch", (FieldParseProc)&__identifier("?parseAngleReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x8C },
	{ "PreferredTargetBone", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x90 },
	{ "FireSound", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xC8 },
	{ "FireSoundLoopTime", (FieldParseProc)&__identifier("?parseDurationUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xCC },
	{ "FireFX", (FieldParseProc)&__identifier("?parseAllVetLevelsFXList@@YAXPAVINI@@PAX1PBX@Z"), 0, 0xA4 },
	{ "FireFlankFX", (FieldParseProc)&__identifier("?parseFXList@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xB4 },
	{ "PreAttackFX", (FieldParseProc)&__identifier("?parseAllVetLevelsFXList@@YAXPAVINI@@PAX1PBX@Z"), 0, 0xB8 },
	{ "ProjectileExhaust", (FieldParseProc)&__identifier("?parseAllVetLevelsPSys@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x94 },
	{ "VeterancyFireFX", (FieldParseProc)&__identifier("?parsePerVetLevelFXList@@YAXPAVINI@@PAX1PBX@Z"), 0, 0xA4 },
	{ "VeterancyProjectileExhaust", (FieldParseProc)&__identifier("?parsePerVetLevelPSys@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x94 },
	{ "ClipSize", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xE4 },
	{ "ContinuousFireOne", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xF8 },
	{ "ContinuousFireTwo", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xFC },
	{ "ContinuousFireCoast", (FieldParseProc)&__identifier("?parseDurationUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x100 },
	{ "AutoReloadWhenIdle", (FieldParseProc)&__identifier("?parseDurationUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x104 },
	{ "ShotsPerBarrel", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x108 },
	{ "DamageDealtAtSelfPosition", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x11C },
	{ "ProjectileFilterInContainer", (FieldParseProc)&__identifier("?iniParseObjectFilter@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x120 },
	{ "ProjectileSelf", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x124 },
	{ "MeleeWeapon", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x125 },
	{ "ChaseWeapon", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x126 },
	{ "LeechRangeWeapon", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x130 },
	{ "HitStoredTarget", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x131 },
	{ "CapableOfFollowingWaypoints", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x132 },
	{ "ShowsAmmoPips", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x133 },
	{ "AllowAttackGarrisonedBldgs", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x134 },
	{ "PlayFXWhenStealthed", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x135 },
	{ "FiringDuration", (FieldParseProc)&__identifier("?parseDurationUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x144 },
	{ "ContinueAttackRange", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x148 },
	{ "SuspendFXDelay", (FieldParseProc)&__identifier("?parseDurationUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x150 },
	{ "IgnoreLinearFirstTarget", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x154 },
	{ "ForceDisplayPercentReady", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x155 },
	{ "IsAimingWeapon", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x156 },
	{ "NoVictimNeeded", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x16B },
	{ "RotatingTurret", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x16C },
	{ "HitPercentage", (FieldParseProc)&__identifier("?parsePercentToReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x158 },
	{ "HitPassengerPercentage", (FieldParseProc)&__identifier("?parsePercentToReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x15C },
	{ "PreAttackDelay", (FieldParseProc)&__identifier("?parseDurationUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x138 },
	{ "PreAttackRandomAmount", (FieldParseProc)&__identifier("?parseDurationUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x13C },
	{ "PassengerProportionalAttack", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x140 },
	{ "MaxAttackPassengers", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x141 },
	{ "FinishAttackOnceStarted", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x161 },
	{ "OverrideVoiceAttackSound", (FieldParseProc)&__identifier("?Rva003393DFParse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0xD0 },
	{ "OverrideVoiceEnterStateAttackSound", (FieldParseProc)&__identifier("?Rva003393DFParse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0xD8 },
	{ "RestrictedHeightRange", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x164 },
	{ "CannotTargetCastleVictims", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x168 },
	{ "RequireFollowThru", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x169 },
	{ "ShareTimers", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x16A },
	{ "ShouldPlayUnderAttackEvaEvent", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x16D },
	{ "InstantLoadClipOnActivate", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x16E },
	{ "LockWhenUsing", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x16F },
	{ "BombardType", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x170 },
	{ "UseInnateAttributes", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x171 },
	{ "PreAttackType", (FieldParseProc)&__identifier("?parseIndexList@INI@@SAXPAV1@PAX1PBX@Z"), TheWeaponPrefireNames, 0x12C },
	{ "AutoReloadsClip", (FieldParseProc)&__identifier("?parseIndexList@INI@@SAXPAV1@PAX1PBX@Z"), TheWeaponReloadNames, 0x128 },
	{ "RadiusDamageAffects", (FieldParseProc)&__identifier("?parseBitString32@INI@@SAXPAV1@PAX1PBX@Z"), TheWeaponAffectsMaskNames, 0x110 },
	{ "ProjectileCollidesWith", (FieldParseProc)&__identifier("?parseBitString32@INI@@SAXPAV1@PAX1PBX@Z"), TheWeaponCollideMaskNames, 0x118 },
	{ "FXTrigger", (FieldParseProc)&__identifier("?parseIndexList@INI@@SAXPAV1@PAX1PBX@Z"), g_00DBC49C, 0x10 },
	{ "DamageType", (FieldParseProc)&__identifier("?parseIndexList@INI@@SAXPAV1@PAX1PBX@Z"), g_00DBC530, 0x58 },
	{ "DeathType", (FieldParseProc)&__identifier("?parseIndexList@INI@@SAXPAV1@PAX1PBX@Z"), TheDeathNames, 0x5C },
	{ "DamageFXType", (FieldParseProc)&__identifier("?parseIndexList@INI@@SAXPAV1@PAX1PBX@Z"), g_00DBC4B0, 0x60 },
	{ "DamageSubType", (FieldParseProc)&__identifier("?parseIndexList@INI@@SAXPAV1@PAX1PBX@Z"), g_00DBC4B0, 0x64 },
	{ "AntiAirborneVehicle", (FieldParseProc)&__identifier("?parseBitInInt32@INI@@SAXPAV1@PAX1PBX@Z"), (const void *)1, 0x10C },
	{ "AntiGround", (FieldParseProc)&__identifier("?parseBitInInt32@INI@@SAXPAV1@PAX1PBX@Z"), (const void *)2, 0x10C },
	{ "AntiProjectile", (FieldParseProc)&__identifier("?parseBitInInt32@INI@@SAXPAV1@PAX1PBX@Z"), (const void *)4, 0x10C },
	{ "AntiSmallMissile", (FieldParseProc)&__identifier("?parseBitInInt32@INI@@SAXPAV1@PAX1PBX@Z"), (const void *)8, 0x10C },
	{ "AntiMine", (FieldParseProc)&__identifier("?parseBitInInt32@INI@@SAXPAV1@PAX1PBX@Z"), (const void *)16, 0x10C },
	{ "AntiParachute", (FieldParseProc)&__identifier("?parseBitInInt32@INI@@SAXPAV1@PAX1PBX@Z"), (const void *)128, 0x10C },
	{ "AntiAirborneInfantry", (FieldParseProc)&__identifier("?parseBitInInt32@INI@@SAXPAV1@PAX1PBX@Z"), (const void *)32, 0x10C },
	{ "AntiAirborneMonster", (FieldParseProc)&__identifier("?parseBitInInt32@INI@@SAXPAV1@PAX1PBX@Z"), (const void *)512, 0x10C },
	{ "AntiBallisticMissile", (FieldParseProc)&__identifier("?parseBitInInt32@INI@@SAXPAV1@PAX1PBX@Z"), (const void *)64, 0x10C },
	{ "AntiStructure", (FieldParseProc)&__identifier("?parseBitInInt32@INI@@SAXPAV1@PAX1PBX@Z"), (const void *)256, 0x10C },
	{ "ProjectileStreamName", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x178 },
	{ "DelayBetweenShots", (FieldParseProc)&__identifier("?parseShotDelay@WeaponTemplate@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x0 },
	{ "ClipReloadTime", (FieldParseProc)&__identifier("?parseClipReloadTime@WeaponTemplate@@SAXPAVINI@@PAX1PBX@Z"), 0, 0x0 },
	{ "ScatterTarget", (FieldParseProc)&__identifier("?parseScatterTarget@WeaponTemplate@@CAXPAVINI@@PAX1PBX@Z"), 0, 0x0 },
	{ "LinearTarget", (FieldParseProc)&__identifier("?Rva002CE849Parse@@YAXPAVINI@@PAX@Z"), 0, 0x0 },
	{ "WeaponBonus", (FieldParseProc)&__identifier("?Rva002CA88BParse@@YAXPAX0@Z"), 0, 0x0 },
	{ "DamageNugget", (FieldParseProc)&__identifier("?parseDamageNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z"), 0, 0x0 },
	{ "ClearNuggets", (FieldParseProc)&__identifier("?parseClearNuggets@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x0 },
	{ "DamageFieldNugget", (FieldParseProc)&__identifier("?parseDamageFieldNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z"), 0, 0x0 },
	{ "WeaponOCLNugget", (FieldParseProc)&__identifier("?parseWeaponOCLNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z"), 0, 0x0 },
	{ "ProjectileNugget", (FieldParseProc)&__identifier("?parseProjectileNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z"), 0, 0x0 },
	{ "MetaImpactNugget", (FieldParseProc)&__identifier("?parseMetaImpactNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z"), 0, 0x0 },
	{ "HordeAttackNugget", (FieldParseProc)&__identifier("?parseHordeAttackNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z"), 0, 0x0 },
	{ "SpawnAndFadeNugget", (FieldParseProc)&__identifier("?parseSpawnAndFadeNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z"), 0, 0x0 },
	{ "GrabNugget", (FieldParseProc)&__identifier("?parseGrabNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z"), 0, 0x0 },
	{ "AttributeModifierNugget", (FieldParseProc)&__identifier("?parseAttributeModifierNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z"), 0, 0x0 },
	{ "SpecialModelConditionNugget", (FieldParseProc)&__identifier("?parseSpecialModelConditionNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z"), 0, 0x0 },
	{ "ParalyzeNugget", (FieldParseProc)&__identifier("?parseParalyzeNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z"), 0, 0x0 },
	{ "LuaEventNugget", (FieldParseProc)&__identifier("?parseLuaEventNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z"), 0, 0x0 },
	{ "FireLogicNugget", (FieldParseProc)&__identifier("?parseFireLogicNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z"), 0, 0x0 },
	{ "SlaveAttackNugget", (FieldParseProc)&__identifier("?parseSlaveAttackNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z"), 0, 0x0 },
	{ "DamageContainedNugget", (FieldParseProc)&__identifier("?parseDamageContainedNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z"), 0, 0x0 },
	{ "DOTNugget", (FieldParseProc)&__identifier("?parseDOTNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z"), 0, 0x0 },
	{ "OpenGateNugget", (FieldParseProc)&__identifier("?parseOpenGateNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z"), 0, 0x0 },
	{ "EmotionWeaponNugget", (FieldParseProc)&__identifier("?parseEmotionWeaponNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z"), 0, 0x0 },
	{ "StealMoneyNugget", (FieldParseProc)&__identifier("?parseStealMoneyNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z"), 0, 0x0 },
	{ 0, 0, 0, 0 }
};
enum INILoadType;
// Target-only INI view: the retail parser reads its load type at +0x08.
// This declaration does not assert the size or the other fields of INI.
class INI
{
public:
    const char *getNextToken(const char *seps = 0);
    void initFromINI(void *object, const FieldParse *fields);
    __declspec(dllimport) __forceinline INILoadType getLoadType() const { return m_loadType; }
private:
    unsigned char m_pad00[8];
    INILoadType m_loadType;
};

class NameKeyGenerator
{
public:
    NameKeyType nameToKey(const AsciiString &name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class WeaponTemplate
{
    friend class WeaponStore;
public:
	WeaponTemplate();
	WeaponTemplate &operator=(const WeaponTemplate &that);

	NameKeyType getNameKey() const { return m_nameKey; }
	bool isOverride() const { return m_isOverride; }
	void friend_setNextTemplate(WeaponTemplate *next) { m_nextTemplate = next; }
	void friend_setIsOverride() { m_isOverride = true; }

private:
	unsigned char m_pad000[0x04];
	WeaponTemplate *m_nextTemplate; // +0x04
	AsciiString m_name; // +0x08
	NameKeyType m_nameKey; // +0x0C
	unsigned char m_pad010[0x160 - 0x10];
	bool m_isOverride; // +0x160
    unsigned char m_pad161[0x174 - 0x161];
    mutable int m_retired; // +0x174
    unsigned char m_pad178[0x180 - 0x178];
};

typedef _STL::vector<WeaponTemplate *, _STL::allocator<WeaponTemplate *> > WeaponTemplateVector;

// The constructor retail runs on the 0x180-byte block (0x002CD169) is rowed
// as Rva002CD4A6's; weapon.cpp's Zero Hour WeaponTemplate() is not that body.
class Rva002CD4A6
{
public:
	Rva002CD4A6();
private:
	unsigned char m_bytes[0x180];
};

class WeaponStore
{
public:
	WeaponTemplate *newOverride(WeaponTemplate *weaponTemplate);
    void rva002CDB0E(const WeaponTemplate *weaponTemplate);
    static void parseWeaponTemplateDefinition(INI *ini);

protected:
    WeaponTemplate *findWeaponTemplatePrivate(NameKeyType key) const;
    WeaponTemplate *newWeaponTemplate(const AsciiString &name);

private:
	unsigned char m_pad00[0x0C];
	WeaponTemplateVector m_weaponTemplateVector; // +0x0C
    _STL::vector<const WeaponTemplate *> m_retiredTemplates; // +0x18
};

WeaponTemplate *WeaponStore::newOverride(WeaponTemplate *weaponTemplate)
{
	if (weaponTemplate == 0)
		return 0;
	if (weaponTemplate->isOverride())
		return 0;

	WeaponTemplate *wt = reinterpret_cast<WeaponTemplate *>(new Rva002CD4A6);
	*wt = *weaponTemplate;
	wt->friend_setNextTemplate(weaponTemplate);
	wt->friend_setIsOverride();

	NameKeyType key = wt->getNameKey();
	for (WeaponTemplateVector::iterator it = m_weaponTemplateVector.begin(); it != m_weaponTemplateVector.end(); ++it)
	{
		if ((*it)->getNameKey() == key)
		{
			m_weaponTemplateVector.erase(it);
			break;
		}
	}
	m_weaponTemplateVector.push_back(wt);
	return wt;
}

// Target: retail 0x002CADBE is the complete 60-byte key search; the mapped
// WorldBuilder Weapon.cpp body indexes the vector at +0x0C and compares the
// template key at +0x0C. WeaponStore callers establish the receiver and role.
// Name, protected access and mutable return follow Zero Hour Weapon.h/source.
// Keep the genuine STLport size/index operations: a hand-written pointer range
// hoists the count and differs from retail's loop-bottom recomputation.
WeaponTemplate *WeaponStore::findWeaponTemplatePrivate(NameKeyType key) const
{
    for (int i = 0; i < m_weaponTemplateVector.size(); ++i)
        if (m_weaponTemplateVector[i]->getNameKey() == key)
            return m_weaponTemplateVector[i];
    return 0;
}

// Retail 0x002CD5FC: complete 128-byte creator. The mapped WB Weapon.cpp body
// proves the 0x180 allocation, constructor, name at +0x08, key at +0x0C and
// vector at store+0x0C. Both retail parser call sites pass their live string by
// reference; they emit no by-value string copy or cleanup. Zero Hour supplies
// the creator's purpose and member sequence; these layouts and ABI are target
// facts. Donor reviewed: reference/open-bfme-1 at ba7ddda7e8f26116
// (Zero Hour Weapon.cpp/Weapon.h). isEmpty uses retail's shared StringBase thunk.
WeaponTemplate *WeaponStore::newWeaponTemplate(const AsciiString &name)
{
    if (((const StringBase<char> *)&name)->isEmpty())
        return 0;
    WeaponTemplate *wt = reinterpret_cast<WeaponTemplate *>(new Rva002CD4A6);
    wt->m_name = name;
    wt->m_nameKey = TheNameKeyGenerator->nameToKey(name);
    m_weaponTemplateVector.push_back(wt);
    return wt;
}

// Complete 69-byte helper formerly assigned to Weapon/ModuleData. Target WB
// parser bb475a and retail 0x002CE160 pass TheWeaponStore and the selected
// WeaponTemplate. The helper moves that template from the +0x0C active vector
// to +0x18 and sets its +0x174 flag, which the parser clears on its replacement.
// Receiver, argument and fields are target facts; the original method name is
// still unknown, so retain the RVA spelling rather than invent a semantic name.
void WeaponStore::rva002CDB0E(const WeaponTemplate *weaponTemplate)
{
    if (!weaponTemplate)
        return;
    WeaponTemplate **finish = m_weaponTemplateVector.end();
    for (WeaponTemplate **it = m_weaponTemplateVector.begin(); it != finish; ++it)
    {
        if (weaponTemplate == *it)
        {
            weaponTemplate->m_retired = 1;
            m_weaponTemplateVector.erase(it);
            m_retiredTemplates.push_back(weaponTemplate);
            return;
        }
    }
}

extern WeaponStore *TheWeaponStore;
// Target identity: the INI Weapon block, mapped WB Weapon.cpp:2151 and its
// complete 170-byte retail handler agree on lookup/create/override dispatch.
// BFME 2 also handles numeric load type 5 by moving the old template aside;
// its original enum label is not established here. The parser retains its
// store receiver across the lookup because the exact helper is visible above.
// 0x00C00B48 is retail's descriptor input: independently decoded as 124
// 16-byte FieldParse records followed by an all-zero terminator at 0x00C01308.
// This function owns no descriptor data; the existing table is its input.
void WeaponStore::parseWeaponTemplateDefinition(INI *ini)
{
    AsciiString name;
    name.set(ini->getNextToken());
    WeaponTemplate *weapon = TheWeaponStore->findWeaponTemplatePrivate(TheNameKeyGenerator->nameToKey(name));
    if (weapon)
    {
        if (ini->getLoadType() == 2)
            weapon = TheWeaponStore->newOverride(weapon);
        else if (ini->getLoadType() == 5)
        {
            TheWeaponStore->rva002CDB0E(weapon);
            weapon = TheWeaponStore->newWeaponTemplate(name);
            weapon->m_retired = 0;
        }
        else
            return;
    }
    else
        weapon = TheWeaponStore->newWeaponTemplate(name);
    ini->initFromINI(weapon, g_00C00B48);
}
