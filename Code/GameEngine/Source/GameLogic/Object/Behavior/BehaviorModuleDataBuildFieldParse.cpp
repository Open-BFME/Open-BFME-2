// cl: /DNDEBUG /MD
// Behavior ModuleData registration stubs and their complete retail FieldParse tables.
// Each 17-byte stub registers one table through MultiIniFieldParse::add.
// Factory callers establish the owning class names; table tokens, callbacks,
// user data and byte offsets below are read from retail, not inferred layouts.
// m_fieldParse and m_optionNames are descriptive source member names.
class INI;
typedef void (*INIFieldParseProc)(INI *, void *, void *, const void *);
#include "../../../../Include/Common/INI/FieldParse.h"
#include "../../../../Include/Common/INI/INI.h"
void Rva001DEE74Parse(INI *, void *, void *, const void *);
void iniParseObjectFilter(INI *, void *, void *, const void *);


class PhysicsBehaviorModuleData
{
public:
    static void buildFieldParse(MultiIniFieldParse &parse);
    static const FieldParse m_fieldParse[];
};

#include "../../../../Include/GameLogic/Module/GateOpenAndCloseBehaviorModuleData.h"

class RunOffMapBehaviorModuleData
{
public:
    static void buildFieldParse(MultiIniFieldParse &parse);
    static const FieldParse m_fieldParse[];
};

class OathbreakersFadeAwayBehaviorModuleData
{
public:
    static void buildFieldParse(MultiIniFieldParse &parse);
    static const FieldParse m_fieldParse[];
};

class SlaveWatcherBehaviorModuleData
{
public:
    static void buildFieldParse(MultiIniFieldParse &parse);
    static const FieldParse m_fieldParse[];
};

class DualWeaponBehaviorModuleData
{
public:
    static void buildFieldParse(MultiIniFieldParse &parse);
    static const FieldParse m_fieldParse[];
};

class AimWeaponBehaviorModuleData
{
public:
    static void buildFieldParse(MultiIniFieldParse &parse);
    static const FieldParse m_fieldParse[];
};

class ShareExperienceBehaviorModuleData
{
public:
    static void buildFieldParse(MultiIniFieldParse &parse);
    static const FieldParse m_fieldParse[];
};

class RampageBehaviorModuleData
{
public:
    static void buildFieldParse(MultiIniFieldParse &parse);
    static const FieldParse m_fieldParse[];
};

#include "../../../../Include/GameLogic/Module/WallHubBehaviorModuleData.h"

class BridgeBehaviorModuleData
{
public:
    static void buildFieldParse(MultiIniFieldParse &parse);
    static const FieldParse m_fieldParse[];
    static void parseFX(INI *, void *, void *, const void *);
    static void parseOCL(INI *, void *, void *, const void *);
};

class HitReactionBehaviorModuleData
{
public:
    static void buildFieldParse(MultiIniFieldParse &parse);
    static const FieldParse m_fieldParse[];
};

#include "../../../../Include/GameLogic/Module/ClickReactionBehaviorModuleData.h"

class CastleMemberBehaviorModuleData
{
public:
    static void buildFieldParse(MultiIniFieldParse &parse);
    static const FieldParse m_fieldParse[];
};

class BuildingBehaviorModuleData
{
public:
    static void buildFieldParse(MultiIniFieldParse &parse);
    static const FieldParse m_fieldParse[];
};

// Retail VA 0x00DC9090: complete bit-name list used by WallHub Options.
const char *WallHubBehaviorModuleData::m_optionNames[] =
{
    "NEED_TARGET_ENEMY_OBJECT",
    "NEED_TARGET_NEUTRAL_OBJECT",
    "NEED_TARGET_ALLY_OBJECT",
    "NO_PLAY_UNIT_SPECIFIC_SOUND_FOR_AUTO_ABILITY",
    "ALLOW_SHRUBBERY_TARGET",
    "NEED_TARGET_POS",
    "NEED_UPGRADE",
    "NEED_SPECIAL_POWER_SCIENCE",
    "OK_FOR_MULTI_SELECT",
    "CONTEXTMODE_COMMAND",
    "CHECK_LIKE",
    "NEEDS_CASTLE_KINDOF",
    "ATTACK_OBJECTS_POSITION",
    "OPTION_ONE",
    "OPTION_TWO",
    "OPTION_THREE",
    "NOT_QUEUEABLE",
    "SINGLE_USE_COMMAND",
    "---DO-NOT-USE---",
    "SCRIPT_ONLY",
    "OK_FOR_MULTI_EXECUTE",
    "ALLOW_ROCK_TARGET",
    "HIDE_WHILE_DISABLED",
    "TOGGLE_IMAGE_ON_WEAPON",
    "TOGGLE_IMAGE_ON_WEAPONSET",
    "TOGGLE_IMAGE_ON_FORMATION",
    "MOUNTED_ONLY",
    "UNMOUNTED_ONLY",
    "NONPRESSABLE",
    "AUTO_ABILITY_TRIGGERED",
    "ON_GROUND_ONLY",
    "CANCELABLE",
    0,
};

// Retail VA 0x00C19DE8, including the null terminator.
const FieldParse PhysicsBehaviorModuleData::m_fieldParse[] =
{
    { "TumbleRandomly", INI::parseBool, 0, 0x40 },
    { "AllowBouncing", INI::parseBool, 0, 0x58 },
    { "KillWhenRestingOnGround", INI::parseBool, 0, 0x59 },
    { "GravityMult", INI::parseReal, 0, 0x4C },
    { "OrientToFlightPath", INI::parseBool, 0, 0x41 },
    { "ShockStunnedTimeLow", INI::parseDurationUnsignedInt, 0, 0x18 },
    { "ShockStunnedTimeHigh", INI::parseDurationUnsignedInt, 0, 0x1C },
    { "ShockStandingTime", INI::parseDurationUnsignedInt, 0, 0x20 },
    { "FirstHeight", INI::parseReal, 0, 0x08 },
    { "SecondHeight", INI::parseReal, 0, 0x0C },
    { "FirstPercentIndent", INI::parsePercentToReal, 0, 0x10 },
    { "SecondPercentIndent", INI::parsePercentToReal, 0, 0x14 },
    { "BounceCount", INI::parseInt, 0, 0x24 },
    { "BounceFirstHeight", INI::parseReal, 0, 0x2C },
    { "BounceSecondHeight", INI::parseReal, 0, 0x30 },
    { "BounceFirstPercentIndent", INI::parsePercentToReal, 0, 0x34 },
    { "BounceSecondPercentIndent", INI::parsePercentToReal, 0, 0x38 },
    { "GroundHitFX", INI::parseFXList, 0, 0x50 },
    { "GroundBounceFX", INI::parseFXList, 0, 0x54 },
    { "IgnoreTerrainHeight", INI::parseBool, 0, 0x42 },
    { "FirstPercentHeight", INI::parsePercentToReal, 0, 0x44 },
    { "SecondPercentHeight", INI::parsePercentToReal, 0, 0x48 },
    { "CurveFlattenMinDist", INI::parseReal, 0, 0x3C },
    { 0, 0, 0, 0x00 },
};

void PhysicsBehaviorModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
    parse.add(m_fieldParse, 0);
}

// Retail VA 0x00BF19F8, including the null terminator.
const FieldParse GateOpenAndCloseBehaviorModuleData::m_fieldParse[] =
{
    { "OpenByDefault", INI::parseBool, 0, 0x08 },
    { "ResetTimeInMilliseconds", INI::parseDurationUnsignedInt, 0, 0x0C },
    { "PercentOpenForPathing", INI::parseUnsignedInt, 0, 0x10 },
    { "Proxy", INI::parseAsciiString, 0, 0x14 },
    { "RepelCollidingUnits", INI::parseBool, 0, 0x18 },
    { "GeometryForOpen", INI::parseAsciiStringVectorAppend, 0, 0x2C },
    { "GeometryForClosed", INI::parseAsciiStringVectorAppend, 0, 0x38 },
    { "SoundOpeningGateLoop", INI::parseAudioEventRTS, 0, 0x1C },
    { "SoundFinishedOpeningGate", INI::parseAudioEventRTS, 0, 0x20 },
    { "SoundClosingGateLoop", INI::parseAudioEventRTS, 0, 0x24 },
    { "SoundFinishedClosingGate", INI::parseAudioEventRTS, 0, 0x28 },
    { "TimeBeforePlayingOpenSound", INI::parseDurationUnsignedInt, 0, 0x44 },
    { "TimeBeforePlayingClosedSound", INI::parseDurationUnsignedInt, 0, 0x48 },
    { 0, 0, 0, 0x00 },
};

void GateOpenAndCloseBehaviorModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
    parse.add(m_fieldParse, 0);
}

// Retail VA 0x00C42F70, including the null terminator.
const FieldParse RunOffMapBehaviorModuleData::m_fieldParse[] =
{
    { "RunToLocation", INI::parseCoord2D, 0, 0x08 },
    { "RequiresSpecificTrigger", INI::parseBool, 0, 0x10 },
    { "RunOffMapWaypointName", INI::parseAsciiString, 0, 0x14 },
    { "DieOnMap", INI::parseBool, 0, 0x18 },
    { 0, 0, 0, 0x00 },
};

void RunOffMapBehaviorModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
    parse.add(m_fieldParse, 0);
}

// Retail VA 0x00C592CC, including the null terminator.
const FieldParse OathbreakersFadeAwayBehaviorModuleData::m_fieldParse[] =
{
    { "FadeOutTime", INI::parseDurationUnsignedInt, 0, 0x08 },
    { 0, 0, 0, 0x00 },
};

void OathbreakersFadeAwayBehaviorModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
    parse.add(m_fieldParse, 0);
}

// Retail VA 0x00C4A208, including the null terminator.
const FieldParse SlaveWatcherBehaviorModuleData::m_fieldParse[] =
{
    { "RemoveUpgrade", INI::parseAsciiString, 0, 0x0C },
    { "GrantUpgrade", INI::parseAsciiString, 0, 0x08 },
    { "ShareUpgrades", INI::parseBool, 0, 0x10 },
    { "LetSlaveLive", INI::parseBool, 0, 0x11 },
    { 0, 0, 0, 0x00 },
};

void SlaveWatcherBehaviorModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
    parse.add(m_fieldParse, 0);
}

// Retail VA 0x00C41858, including the null terminator.
const FieldParse DualWeaponBehaviorModuleData::m_fieldParse[] =
{
    { "SwitchWeaponOnCloseRangeDistance", INI::parseReal, 0, 0x08 },
    { "UseCloseRangeWhileMounted", INI::parseBool, 0, 0x0C },
    { "MinimumSwitchTime", INI::parseDurationUnsignedInt, 0, 0x10 },
    { "UseHordeRangeWeapon", INI::parseBool, 0, 0x14 },
    { "UseRealVictimRange", INI::parseBool, 0, 0x15 },
    { 0, 0, 0, 0x00 },
};

void DualWeaponBehaviorModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
    parse.add(m_fieldParse, 0);
}

// Retail VA 0x00C41948, including the null terminator.
const FieldParse AimWeaponBehaviorModuleData::m_fieldParse[] =
{
    { "AimLowThreshold", INI::parseReal, 0, 0x08 },
    { "AimHighThreshold", INI::parseReal, 0, 0x0C },
    { "AimNearDistance", INI::parseReal, 0, 0x10 },
    { "AimFarDistance", INI::parseReal, 0, 0x14 },
    { 0, 0, 0, 0x00 },
};

void AimWeaponBehaviorModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
    parse.add(m_fieldParse, 0);
}

// Retail VA 0x00C48740, including the null terminator.
const FieldParse ShareExperienceBehaviorModuleData::m_fieldParse[] =
{
    { "Radius", INI::parseReal, 0, 0x08 },
    { "DropOff", INI::parseReal, 0, 0x0C },
    { "Percentage", INI::parseReal, 0, 0x10 },
    { "ObjectFilter", iniParseObjectFilter, 0, 0x14 },
    { 0, 0, 0, 0x00 },
};

void ShareExperienceBehaviorModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
    parse.add(m_fieldParse, 0);
}

// Retail VA 0x00C40E78, including the null terminator.
const FieldParse RampageBehaviorModuleData::m_fieldParse[] =
{
    { "RampageHealthThreshold", INI::parseReal, 0, 0x14 },
    { "RampageLifeTimer", INI::parseInt, 0, 0x18 },
    { "RampageAngryLifeTimer", INI::parseInt, 0, 0x1C },
    { "RampageResetTimer", INI::parseInt, 0, 0x20 },
    { "RampageEnemyCheckRange", INI::parseReal, 0, 0x24 },
    { "RampageEnemyThreshold", INI::parseInt, 0, 0x28 },
    { "RequiredUpgrade", INI::parseAsciiStringVector, 0, 0x08 },
    { 0, 0, 0, 0x00 },
};

void RampageBehaviorModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
    parse.add(m_fieldParse, 0);
}

// Retail VA 0x00C3FED8, including the null terminator.
const FieldParse WallHubBehaviorModuleData::m_fieldParse[] =
{
    { "SegmentTemplateName", INI::parseAsciiStringVectorAppend, 0, 0x08 },
    { "DefaultSegmentTemplateName", INI::parseAsciiString, 0, 0x18 },
    { "HubCapTemplateName", INI::parseAsciiString, 0, 0x14 },
    { "CliffCapTemplateName", INI::parseAsciiString, 0, 0x1C },
    { "ShoreCapTemplateName", INI::parseAsciiString, 0, 0x20 },
    { "BorderCapTemplateName", INI::parseAsciiString, 0, 0x24 },
    { "ElevatedSegmentTemplateName", INI::parseAsciiString, 0, 0x28 },
    { "StaggeredBuildFactor", INI::parseInt, 0, 0x38 },
    { "BuilderRadius", INI::parseReal, 0, 0x2C },
    { "MaxBuildoutDistance", INI::parseReal, 0, 0x30 },
    { "Options", INI::parseBitString32, WallHubBehaviorModuleData::m_optionNames, 0x34 },
    { 0, 0, 0, 0x00 },
};

void WallHubBehaviorModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
    parse.add(m_fieldParse, 0);
}

// Retail VA 0x00C40B20, including the null terminator.
const FieldParse BridgeBehaviorModuleData::m_fieldParse[] =
{
    { "LateralScaffoldSpeed", INI::parseVelocityReal, 0, 0x08 },
    { "VerticalScaffoldSpeed", INI::parseVelocityReal, 0, 0x0C },
    { "BridgeDieFX", BridgeBehaviorModuleData::parseFX, 0, 0x10 },
    { "BridgeDieOCL", BridgeBehaviorModuleData::parseOCL, 0, 0x14 },
    { 0, 0, 0, 0x00 },
};

void BridgeBehaviorModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
    parse.add(m_fieldParse, 0);
}

// Retail VA 0x00C410F0, including the null terminator.
const FieldParse HitReactionBehaviorModuleData::m_fieldParse[] =
{
    { "HitReactionLifeTimer1", INI::parseDurationUnsignedInt, 0, 0x08 },
    { "HitReactionLifeTimer2", INI::parseDurationUnsignedInt, 0, 0x0C },
    { "HitReactionLifeTimer3", INI::parseDurationUnsignedInt, 0, 0x10 },
    { "HitReactionThreshold1", INI::parseReal, 0, 0x14 },
    { "HitReactionThreshold2", INI::parseReal, 0, 0x18 },
    { "HitReactionThreshold3", INI::parseReal, 0, 0x1C },
    { "FastHitsResetReaction", INI::parseBool, 0, 0x20 },
    { "HitsParalyze", INI::parseBool, 0, 0x21 },
    { 0, 0, 0, 0x00 },
};

void HitReactionBehaviorModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
    parse.add(m_fieldParse, 0);
}

// Retail VA 0x00C412F8, including the null terminator.
const FieldParse ClickReactionBehaviorModuleData::m_fieldParse[] =
{
    { "ClickReactionTimer", INI::parseInt, 0, 0x08 },
    { "ReactionFrames1", INI::parseInt, 0, 0x0C },
    { "ReactionFrames2", INI::parseInt, 0, 0x10 },
    { "ReactionFrames3", INI::parseInt, 0, 0x14 },
    { "ReactionFrames4", INI::parseInt, 0, 0x18 },
    { "ReactionFrames5", INI::parseInt, 0, 0x1C },
    { 0, 0, 0, 0x00 },
};

void ClickReactionBehaviorModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
    parse.add(m_fieldParse, 0);
}

// Retail VA 0x00C1A310, including the null terminator.
const FieldParse CastleMemberBehaviorModuleData::m_fieldParse[] =
{
    { "CampDestroyedOwnerEvaEvent", Rva001DEE74Parse, 0, 0x08 },
    { "CampDestroyedAllyEvaEvent", Rva001DEE74Parse, 0, 0x0C },
    { "CampDestroyedAttackerEvaEvent", Rva001DEE74Parse, 0, 0x10 },
    { "BeingBuiltSound", INI::parseAudioEventRTS, 0, 0x14 },
    { "StoreUpgradePrice", INI::parseBool, 0, 0x18 },
    { "CountsForEvaCastleBreached", INI::parseBool, 0, 0x19 },
    { 0, 0, 0, 0x00 },
};

void CastleMemberBehaviorModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
    parse.add(m_fieldParse, 0);
}

// Retail VA 0x00C40748, including the null terminator.
const FieldParse BuildingBehaviorModuleData::m_fieldParse[] =
{
    { "NightWindowName", INI::parseAsciiStringVector, 0, 0x08 },
    { "FireWindowName", INI::parseAsciiStringVector, 0, 0x14 },
    { "GlowWindowName", INI::parseAsciiStringVector, 0, 0x20 },
    { "FireName", INI::parseAsciiStringVector, 0, 0x2C },
    { 0, 0, 0, 0x00 },
};

void BuildingBehaviorModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
    parse.add(m_fieldParse, 0);
}
