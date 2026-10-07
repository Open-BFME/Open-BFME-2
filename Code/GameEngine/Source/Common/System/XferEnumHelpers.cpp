// cl: /Ireference/shims/bfme2_ascii

// Labelled-enum transfer helpers: each one moves a 4-byte enum through the
// text-mode Xfer's slot-37 XferEnum virtual with its field-name label (the
// label strings live in .rdata next to neighbouring enum labels). The bodies
// are free cdecl functions taking (Xfer*, value*) with no other dependencies,
// so all helpers share this TU. The Xfer declaration below is Xfer.cpp's
// model verbatim so the XferEnum call lands on the shipped slot.

enum SlotState
{
	SLOT_OPEN = 0,
	SLOT_CLOSED = 1,
	SLOT_EASY_AI = 2,
	SLOT_MED_AI = 3,
	SLOT_BRUTAL_AI = 4,
	SLOT_AI_5 = 5,
	SLOT_PLAYER = 6
};

enum ObjectID
{
	INVALID_ID = 0
};

struct Coord3DBase
{
	float x;
	float y;
	float z;
};

struct ICoord3D
{
	int x;
	int y;
	int z;
};

#include "../../../../Libraries/Include/Lib/Coord2D.h"

struct ICoord2D
{
	int x;
	int y;
};

struct Region3D
{
	Coord3DBase lo;
	Coord3DBase hi;
};

struct IRegion3D
{
	ICoord3D lo;
	ICoord3D hi;
};

struct Region2D
{
	Coord2D lo;
	Coord2D hi;
};

struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;
};

struct RealRange
{
	float lo;
	float hi;
};

struct RGBColor
{
	float red;
	float green;
	float blue;
};

struct RGBAColorReal
{
	float red;
	float green;
	float blue;
	float alpha;
};

struct RGBAColorInt
{
	unsigned int red;
	unsigned int green;
	unsigned int blue;
	unsigned int alpha;
};

class Xfer;

class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void crc(Xfer *xfer) = 0;
	virtual void loadPostProcess() = 0;
	virtual void xfer(Xfer *xfer) = 0;
};

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;

class Xfer
{
public:
	class Version;

	Xfer();
	virtual ~Xfer();

	void Version1();

	// Slot order proven by GameSlot::xfer's two guards: slot 1 (0x04) runs
	// the original-info save-off (true on load), slot 4 (0x10) skips the
	// whole body (true in light-CRC mode). Xfer.cpp lists IsStoring first,
	// which its folded mode-predicate rows cannot distinguish; the guards
	// here can, so this TU uses the BFME1 Xfer.h order.
	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;

	virtual void v5() = 0;
	virtual void v6() = 0;
	virtual void v7() = 0;

	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(PooledString &value);
	virtual Xfer &operator==(Coord3DBase &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);

	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);

protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};

// ?XferSlotState@@YAXPAVXfer@@PAW4SlotState@@@Z
// Retail 0x003FF0B4 (24B): sole caller is GameSlot::xfer at 0x003FF649,
// passing &m_state with the "SlotState" label for the text-dump Xfer.
void XferSlotState(Xfer *xfer, SlotState *state)
{
	xfer->XferEnum("SlotState", state, 4);
}

// ?XferLivingWorldPlayerID@@YAXPAVXfer@@PAH@Z
// Retail 0x002034C4 (24B): shared helper used by 19 callers (team, player
// and slot xfer methods), moving a 4-byte Living World player ID through
// XferEnum with the "LivingWorldPlayerID" label.
void XferLivingWorldPlayerID(Xfer *xfer, int *playerID)
{
	xfer->XferEnum("LivingWorldPlayerID", playerID, 4);
}

// Retail 0x003060B2 (24B): labelled-enum helper moving a 4-byte ObjectID
// through XferEnum with the "ObjectID" label (string at 0x00807CC8 next to
// DrawableID). 40+ callers including FoundationAIUpdate::xfer at 0x00455141
// passing &m_28.
void XferObjectID(Xfer *xfer, ObjectID *objectID)
{
	xfer->XferEnum("ObjectID", objectID, 4);
}

// Retail 0x0045ED66 (24B): labelled-enum helper moving a 4-byte stances value
// through XferEnum with the "StancesEnum" label. Callers include
// StancesBehavior::xfer at 0x0045EDC8 passing &m_30 (rowed int at +0x30).
void XferStancesEnum(Xfer *xfer, int *stances)
{
	xfer->XferEnum("StancesEnum", stances, 4);
}

// Retail 0x00305F92 (24B): labelled-enum helper moving a 4-byte distribution
// type through XferEnum with the "GameClientRandomVariable::DistributionType"
// label (string at 0x00807BBC). Sole caller is FUN_00706183 at 0x003061E7.
void XferDistributionType(Xfer *xfer, int *value)
{
	xfer->XferEnum("GameClientRandomVariable::DistributionType", value, 4);
}

// Retail 0x0030600A (24B): labelled-enum helper moving a 4-byte particle
// system ID through XferEnum with the "ParticleSystemID" label (string at
// 0x00807C4C). Callers include BoneFXUpdate::xfer at 0x00487CD4/0x00487D1A.
void XferParticleSystemID(Xfer *xfer, int *value)
{
	xfer->XferEnum("ParticleSystemID", value, 4);
}

// ?XferParticleShaderType@@YAXPAVXfer@@PAH@Z
// Retail 0x00306052 (24B): labelled-enum helper moving a 4-byte particle
// shader type through XferEnum with the "ParticleShaderType" label (string at
// 0x00807C88). Callers include DoXfer bodies at 0x001F4F99 0x005628B4
// 0x005628E1 0x0056290E.
void XferParticleShaderType(Xfer *xfer, int *value)
{
	xfer->XferEnum("ParticleShaderType", value, 4);
}

// Retail 0x00306082 (24B): labelled-enum helper moving a 4-byte rotation type
// through XferEnum with the "RotationType" label (string at 0x00807CA8).
// Callers include DoXfer bodies at 0x0055F6DB 0x0055F7D1 0x00562226 0x0056233E.
void XferRotationType(Xfer *xfer, int *value)
{
	xfer->XferEnum("RotationType", value, 4);
}

// Retail 0x00305BD2 (24B): labelled-enum helper with the "ModelConditionFlagType"
// label (string at 0x0080796C).
void XferModelConditionFlagType(Xfer *xfer, int *value)
{
	xfer->XferEnum("ModelConditionFlagType", value, 4);
}

// Retail 0x00305BEA (24B): labelled-enum helper with the "GameDifficulty"
// label (string at 0x00807984).
void XferGameDifficulty(Xfer *xfer, int *value)
{
	xfer->XferEnum("GameDifficulty", value, 4);
}

// Retail 0x00305C02 (24B): labelled-enum helper with the "CommandSourceType"
// label (string at 0x00807994).
void XferCommandSourceType(Xfer *xfer, int *value)
{
	xfer->XferEnum("CommandSourceType", value, 4);
}

// Retail 0x00305C1A (24B): labelled-enum helper with the "WhichTurretType"
// label (string at 0x008079A8).
void XferWhichTurretType(Xfer *xfer, int *value)
{
	xfer->XferEnum("WhichTurretType", value, 4);
}

// Retail 0x00305C32 (24B): labelled-enum helper with the "Relationship"
// label (string at 0x008079B8).
void XferRelationship(Xfer *xfer, int *value)
{
	xfer->XferEnum("Relationship", value, 4);
}

// Retail 0x00305C4A (24B): labelled-enum helper with the "FormationID"
// label (string at 0x008079C8).
void XferFormationID(Xfer *xfer, int *value)
{
	xfer->XferEnum("FormationID", value, 4);
}

// Retail 0x00305C62 (24B): labelled-enum helper with the "WaypointID"
// label (string at 0x008079D4).
void XferWaypointID(Xfer *xfer, int *value)
{
	xfer->XferEnum("WaypointID", value, 4);
}

// Retail 0x00305D0A (24B): labelled-enum helper with the "PathfindLayerEnum"
// label (string at 0x00807A20).
void XferPathfindLayerEnum(Xfer *xfer, int *value)
{
	xfer->XferEnum("PathfindLayerEnum", value, 4);
}

// Retail 0x00305D3A (24B): labelled-enum helper with the "RadarEventType"
// label (string at 0x00807A40).
void XferRadarEventType(Xfer *xfer, int *value)
{
	xfer->XferEnum("RadarEventType", value, 4);
}

// Retail 0x00305DCA (24B): labelled-enum helper with the "TurretTargetType"
// label (string at 0x00807AA0).
void XferTurretTargetType(Xfer *xfer, int *value)
{
	xfer->XferEnum("TurretTargetType", value, 4);
}

// Retail 0x00305DFA (24B): labelled-enum helper with the "ScaffoldTargetMotion"
// label (string at 0x00807AD0).
void XferScaffoldTargetMotion(Xfer *xfer, int *value)
{
	xfer->XferEnum("ScaffoldTargetMotion", value, 4);
}

// Retail 0x00305E12 (24B): labelled-enum helper with the "BodyDamageType"
// label (string at 0x00807AE8).
void XferBodyDamageType(Xfer *xfer, int *value)
{
	xfer->XferEnum("BodyDamageType", value, 4);
}

// Retail 0x00305CF2 (24B): labelled-enum helper with the "WeaponSlotType"
// label.
void XferWeaponSlotType(Xfer *xfer, int *value)
{
	xfer->XferEnum("WeaponSlotType", value, 4);
}

// Retail 0x00305D22 (24B): labelled-enum helper with the "OrderMode" label.
void XferOrderMode(Xfer *xfer, int *value)
{
	xfer->XferEnum("OrderMode", value, 4);
}

// Retail 0x00305D52 (24B): labelled-enum helper with the "SaveFileType" label.
void XferSaveFileType(Xfer *xfer, int *value)
{
	xfer->XferEnum("SaveFileType", value, 4);
}

// Retail 0x00305D6A (24B): labelled-enum helper with the "BuildableStatus" label.
void XferBuildableStatus(Xfer *xfer, int *value)
{
	xfer->XferEnum("BuildableStatus", value, 4);
}

// Retail 0x00305D82 (24B): labelled-enum helper with the "WeaponStatus" label.
void XferWeaponStatus(Xfer *xfer, int *value)
{
	xfer->XferEnum("WeaponStatus", value, 4);
}

// Retail 0x00305D9A (24B): labelled-enum helper with the "AttitudeType" label.
void XferAttitudeType(Xfer *xfer, int *value)
{
	xfer->XferEnum("AttitudeType", value, 4);
}

// Retail 0x00305DB2 (24B): labelled-enum helper with the "AICommandType" label.
void XferAICommandType(Xfer *xfer, int *value)
{
	xfer->XferEnum("AICommandType", value, 4);
}

// Retail 0x00305E2A (24B): labelled-enum helper with the "BodySideDestroyedType"
// label.
void XferBodySideDestroyedType(Xfer *xfer, int *value)
{
	xfer->XferEnum("BodySideDestroyedType", value, 4);
}

// Retail 0x00305E42 (24B): labelled-enum helper with the "LocomotorSetType" label.
void XferLocomotorSetType(Xfer *xfer, int *value)
{
	xfer->XferEnum("LocomotorSetType", value, 4);
}

// Retail 0x00305E5A (24B): labelled-enum helper with the "GuardTargetType" label.
void XferGuardTargetType(Xfer *xfer, int *value)
{
	xfer->XferEnum("GuardTargetType", value, 4);
}

// Retail 0x00305E72 (24B): labelled-enum helper with the "FlammabilityStatusType"
// label.
void XferFlammabilityStatusType(Xfer *xfer, int *value)
{
	xfer->XferEnum("FlammabilityStatusType", value, 4);
}

// Retail 0x00305E8A (24B): labelled-enum helper with the "DeployStateTypes" label.
void XferDeployStateTypes(Xfer *xfer, int *value)
{
	xfer->XferEnum("DeployStateTypes", value, 4);
}

// Retail 0x00305EA2 (24B): labelled-enum helper with the
// "DeployStyleAIUpdate::CommandResultTypes" label (string at 0x00807B60).
// Callers in unclaimed DeployStyleAIUpdate xfer at 0x0048E746/0x0048E770.
void XferCommandResultTypes(Xfer *xfer, int *value)
{
	xfer->XferEnum("DeployStyleAIUpdate::CommandResultTypes", value, 4);
}

// Retail 0x00305EBA (24B): labelled-enum helper with the "DamageFXType"
// label (string at 0x008015AC).
void XferDamageFXType(Xfer *xfer, int *value)
{
	xfer->XferEnum("DamageFXType", value, 4);
}

// Retail 0x00305ED2 (24B): labelled-enum helper with the "DamageType"
// label (string at 0x008015C8).
void XferDamageType(Xfer *xfer, int *value)
{
	xfer->XferEnum("DamageType", value, 4);
}

// Retail 0x00305EEA (24B): labelled-enum helper with the "DamageSubType"
// label (string at 0x0080159C).
void XferDamageSubType(Xfer *xfer, int *value)
{
	xfer->XferEnum("DamageSubType", value, 4);
}

// Retail 0x00305F02 (24B): labelled-enum helper with the "DeathType"
// label (string at 0x008015BC).
void XferDeathType(Xfer *xfer, int *value)
{
	xfer->XferEnum("DeathType", value, 4);
}

// Retail 0x00305F1A (24B): labelled-enum helper with the "StealthLookType"
// label (string at 0x00807B88).
void XferStealthLookType(Xfer *xfer, int *value)
{
	xfer->XferEnum("StealthLookType", value, 4);
}

// Retail 0x00305F4A (24B): labelled-enum helper with the "FXTrigger"
// label (string at 0x007C9E60).
void XferFXTrigger(Xfer *xfer, int *value)
{
	xfer->XferEnum("FXTrigger", value, 4);
}

// Retail 0x00305F7A (24B): labelled-enum helper with the "ShadowType"
// label (string at 0x00807BB0).
void XferShadowType(Xfer *xfer, int *value)
{
	xfer->XferEnum("ShadowType", value, 4);
}

// Retail 0x00305FAA (24B): labelled-enum helper with the "GlobalWeatherType"
// label (string at 0x00807BE8).
void XferGlobalWeatherType(Xfer *xfer, int *value)
{
	xfer->XferEnum("GlobalWeatherType", value, 4);
}

// Retail 0x00305FC2 (24B): labelled-enum helper with the
// "GlobalWeatherAffectsType" label (string at 0x00807BFC).
void XferGlobalWeatherAffectsType(Xfer *xfer, int *value)
{
	xfer->XferEnum("GlobalWeatherAffectsType", value, 4);
}

// Retail 0x00305FDA (24B): labelled-enum helper with the
// "AttributeModifierCategoryType" label (string at 0x00807C18).
void XferAttributeModifierCategoryType(Xfer *xfer, int *value)
{
	xfer->XferEnum("AttributeModifierCategoryType", value, 4);
}

// Retail 0x00305FF2 (24B): labelled-enum helper with the "INVISIBILITYTYPE"
// label (string at 0x00807C38).
void XferInvisibilityType(Xfer *xfer, int *value)
{
	xfer->XferEnum("INVISIBILITYTYPE", value, 4);
}

// Retail 0x0030609A (24B): labelled-enum helper moving a 4-byte bridge tower
// type through XferEnum with the "BridgeTowerType" label (string at
// 0x00807CB8 between RotationType and ObjectID). Sole caller is
// BridgeTowerBehavior::xfer at 0x004587CD passing &m_20.
void XferBridgeTowerType(Xfer *xfer, int *value)
{
	xfer->XferEnum("BridgeTowerType", value, 4);
}

// Retail 0x00306022 (24B): labelled-enum helper with the "ParticleType"
// label (string at 0x00807C60). Caller is DoXfer at 0x001F4FA3.
void XferParticleType(Xfer *xfer, int *value)
{
	xfer->XferEnum("ParticleType", value, 4);
}

// Retail 0x0030603A (24B): labelled-enum helper with the "ParticlePriorityType"
// label (string at 0x00807C70).
void XferParticlePriorityType(Xfer *xfer, int *value)
{
	xfer->XferEnum("ParticlePriorityType", value, 4);
}

// Retail 0x0030606A (24B): labelled-enum helper with the "WindMotion"
// label (string at 0x00807C9C).
void XferWindMotion(Xfer *xfer, int *value)
{
	xfer->XferEnum("WindMotion", value, 4);
}

// Retail 0x003060CA (24B): labelled-enum helper with the "DrawableID"
// label (string at 0x00807CD4 next to ObjectID at 0x00807CC8).
void XferDrawableID(Xfer *xfer, int *value)
{
	xfer->XferEnum("DrawableID", value, 4);
}

// Retail 0x003060E2 (24B): labelled-enum helper with the "LivingWorldUniqueID"
// label (string at 0x00807CE0). Caller is FUN_006D9D7C at 0x002D9E50.
void XferLivingWorldUniqueID(Xfer *xfer, int *value)
{
	xfer->XferEnum("LivingWorldUniqueID", value, 4);
}

// Retail 0x003060FA (24B): labelled-enum helper with the "RespawnModeType"
// label (string at 0x00807CF4).
void XferRespawnModeType(Xfer *xfer, int *value)
{
	xfer->XferEnum("RespawnModeType", value, 4);
}

// Retail 0x00306112 (24B): labelled-enum helper with the "SiegeTypeEnum"
// label (string at 0x00807D04).
void XferSiegeTypeEnum(Xfer *xfer, int *value)
{
	xfer->XferEnum("SiegeTypeEnum", value, 4);
}

// Retail 0x00318D1E (24B): labelled-enum helper with the "LivingWorldArmyID"
// label (string at 0x0080C7F0). Callers include xfer bodies at 0x002B8D69
// 0x002B8DCA passing member pointers through XferEnum slot 37.
void XferLivingWorldArmyID(Xfer *xfer, int *value)
{
	xfer->XferEnum("LivingWorldArmyID", value, 4);
}

// Retail 0x00318D36 (24B): labelled-enum helper with the "ArmyIconSize"
// label (string at 0x0080C804). Caller is FUN_0071A6DB at 0x0031A88A.
void XferArmyIconSize(Xfer *xfer, int *value)
{
	xfer->XferEnum("ArmyIconSize", value, 4);
}

// Retail 0x002E05CA (24B): labelled-enum helper with the
// "LivingWorldRegionBonusRuleID" label (string at 0x00804700). Callers are the
// set xfer at 0x002E208A passing int values through XferEnum slot 37.
void XferLivingWorldRegionBonusRuleID(Xfer *xfer, int *value)
{
	xfer->XferEnum("LivingWorldRegionBonusRuleID", value, 4);
}

// Two version bytes, stored back to back: the retail Version1 body writes 1 to
// both of them in a four-byte stack slot before handing their address to the
// slot-10 transfer operator. Xfer.cpp's model verbatim.
class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef bool Bool;

// TU-scoped strings: 4-byte ref-counted handles, the MapMetaData TU pattern
// stripped to the layout (no methods, so no extra literals or code).
#include "ascii_string.h"


#include "unicode_string.h"

// The +0x64 member's own type is unidentified: its default constructor
// (retail 0x00229557) calls BFME2NativeNetwork::baseConstruct, its vtable
// (retail 0x00BE73E8) carries an empty slot-3 virtual, and GameSlot::xfer
// only ever invokes that slot. Model the proven four-virtual shape with the
// call at slot 3 and pad to the next accessed member (+0x1A4).
class BfmeSlotNetState
{
public:
	virtual ~BfmeSlotNetState();
	virtual void crc(Xfer *xfer);
	virtual void loadPostProcess();
	virtual void xfer(Xfer *xfer);

private:
	char m_pad[0x1A4 - 0x64 - 4];
};

// BFME2 GameSlot layout: BFME1's LANGameSlot_copy.cpp donor shifted +8 past
// +0x10 (two inserted ints at +0x14/+0x20), then BFME2-only tail members.
// Every offset below is proven by retail: the xfer call sequence, the
// copy constructor at 0x002295D7 and the destructor at 0x002294FD.
class GameSlot
{
public:
	virtual void _bfme_gs0() = 0;
	virtual void _bfme_gs1() = 0;
	virtual void _bfme_gs2() = 0;
	virtual void xfer(Xfer *xfer);

	SlotState m_state;                  // +0x04
	Bool m_isAccepted;                  // +0x08
	Bool m_hasMap;                      // +0x09
	Bool m_isMuted;                     // +0x0A
	Int m_color;                        // +0x0C
	Int m_startPos;                     // +0x10
	Int m_bfme14;                       // +0x14 (BFME2-new int, xferred)
	Int m_playerTemplate;               // +0x18
	Int m_teamNumber;                   // +0x1C
	Int m_bfme20;                       // +0x20 (BFME2-new int, xferred)
	Int m_origColor;                    // +0x24
	Int m_origStartPos;                 // +0x28
	Int m_origPlayerTemplate;           // +0x2C
	UnicodeString m_name;           // +0x30 (donor BfmeWideSlotString)
	AsciiString m_ip;               // +0x34 (donor BfmeAsciiSlotString)
	UnsignedInt m_bfme38;               // +0x38 (copied, not xferred)
	UnsignedInt m_bfme3C;               // +0x3C (copied, not xferred)
	UnsignedInt m_bfme40;               // +0x40 (copied, not xferred)
	UnsignedInt m_bfme44;               // +0x44 (copied, not xferred)
	UnsignedByte m_bfme48;              // +0x48 (copied, not xferred)
	Int m_bfme4C;                       // +0x4C (Living World player ID)
	Int m_bfme50;                       // +0x50 (xferred via local when version >= 2)
	UnsignedInt m_bfme54;               // +0x54
	UnsignedInt m_bfme58;               // +0x58
	Int m_bfme5C;                       // +0x5C
	Bool m_bfme60;                      // +0x60
	BfmeSlotNetState m_netState;        // +0x64
	Bool m_bfme1A4;                     // +0x1A4
	AsciiString m_bfme1A8;          // +0x1A8
};

// ?xfer@GameSlot@@UAEXPAVXfer@@@Z
// Retail 0x003FF616 (384B): persists the slot through the Xfer virtuals
// (light-CRC guard, version {1,2}, labelled SlotState enum, original-info
// save-off on load, version-gated +0x50, member xfer at +0x64).
void GameSlot::xfer(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;

	Xfer::Version version(1, 2);
	*xfer == version;

	XferSlotState(xfer, &m_state);
	*xfer == m_isAccepted;
	*xfer == m_hasMap;
	*xfer == m_isMuted;
	*xfer == m_color;
	*xfer == m_startPos;
	*xfer == m_bfme14;
	*xfer == m_playerTemplate;
	*xfer == m_teamNumber;
	*xfer == m_bfme20;

	if (xfer->IsLoading())
	{
		m_origPlayerTemplate = m_playerTemplate;
		m_origStartPos = m_startPos;
		m_origColor = m_color;
	}

	*xfer == m_origColor;
	*xfer == m_origStartPos;
	*xfer == m_origPlayerTemplate;
	*xfer == m_name;
	*xfer == m_ip;
	XferLivingWorldPlayerID(xfer, &m_bfme4C);
	*xfer == m_bfme54;
	*xfer == m_bfme58;
	*xfer == m_bfme5C;
	*xfer == m_bfme60;

	if (version.m_minimum >= 2)
	{
		Int bfme50 = m_bfme50;
		*xfer == bfme50;
		m_bfme50 = bfme50;
	}

	m_netState.xfer(xfer);
	*xfer == m_bfme1A4;
	*xfer == m_bfme1A8;
}

// Retail 0x0030612A (39B): free cdecl helper moving three consecutive floats
// through the float operator== (Xfer slot 28, 0x70), chaining the returned
// Xfer& as the next call's this. Callers pass 12-byte triples at e.g.
// +0x51264/+0x51270 (0x000E96B4), edi+0xF8 (0x0009AAFB) and four in a row at
// +0x04/+0x10/+0x1C/+0x28 (0x00271A0F).
void Rva0030612AXfer(Xfer *xfer, float *vals)
{
	(((*xfer == vals[0]) == vals[1]) == vals[2]);
}

// Retail 0x00306151 (50B): free cdecl helper moving four consecutive floats
// through the float operator== (Xfer slot 28, 0x70), chaining the returned
// Xfer& as the next call's this and returning the final Xfer* so the
// 0x003062FE triple-row caller can forward it in eax for its next call.
// Sibling of Rva0030612AXfer above (three floats); sole caller shape is
// 0x003062FE, which invokes it three times at +0x00/+0x10/+0x20
// (a 48-byte triple row).
Xfer *Rva00306151Xfer(Xfer *xfer, float *vals)
{
	return &(((((*xfer == vals[0]) == vals[1]) == vals[2]) == vals[3]));
}

// Retail 0x003062FE (41B): free cdecl helper moving twelve consecutive floats
// (a 48-byte triple row) through Rva00306151Xfer at +0x00/+0x10/+0x20.
// Callers pass edi+0x50 (0x000E5725), row triples in xfer bodies listed in the
// packet; evidence is the three E8 calls to 0x00306151 with the push/pop
// reuse shape (nested calls forward Xfer* in eax).
void Rva003062FEXfer(Xfer *xfer, float *vals)
{
	Rva00306151Xfer(Rva00306151Xfer(Rva00306151Xfer(xfer, vals), vals + 4), vals + 8);
}

// Fifteen more helpers of the XferSlotState shape: the same 24 bytes with their
// own field-name label, read from retail. Each is named after its label, as
// XferSlotState is; the enum each moves is not identified, so the value is
// passed as void *.

// ?XferAudioAffect@@YAXPAVXfer@@PAX@Z
// Retail 0x00050E81 (24B): label "AudioAffect".
void XferAudioAffect(Xfer *xfer, void *value)
{
	xfer->XferEnum("AudioAffect", value, 4);
}

// ?XferTimeOfDay@@YAXPAVXfer@@PAX@Z
// Retail 0x00305C7A (24B): label "TimeOfDay".
void XferTimeOfDay(Xfer *xfer, void *value)
{
	xfer->XferEnum("TimeOfDay", value, 4);
}

// ?XferWeather@@YAXPAVXfer@@PAX@Z
// Retail 0x00305C92 (24B): label "Weather".
void XferWeather(Xfer *xfer, void *value)
{
	xfer->XferEnum("Weather", value, 4);
}

// ?XferFactionType@@YAXPAVXfer@@PAX@Z
// Retail 0x00305CAA (24B): label "FactionType".
void XferFactionType(Xfer *xfer, void *value)
{
	xfer->XferEnum("FactionType", value, 4);
}

// ?XferLivingWorldObjectType@@YAXPAVXfer@@PAX@Z
// Retail 0x00305CC2 (24B): label "LivingWorldObjectType".
void XferLivingWorldObjectType(Xfer *xfer, void *value)
{
	xfer->XferEnum("LivingWorldObjectType", value, 4);
}

// ?XferScorches@@YAXPAVXfer@@PAX@Z
// Retail 0x00305CDA (24B): label "Scorches".
void XferScorches(Xfer *xfer, void *value)
{
	xfer->XferEnum("Scorches", value, 4);
}

// ?XferAimWeaponBehaviorAimType@@YAXPAVXfer@@PAX@Z
// Retail 0x00305DE2 (24B): label "AimWeaponBehavior::AimType".
void XferAimWeaponBehaviorAimType(Xfer *xfer, void *value)
{
	xfer->XferEnum("AimWeaponBehavior::AimType", value, 4);
}

// ?XferFXAction@@YAXPAVXfer@@PAX@Z
// Retail 0x00305F32 (24B): label "FXAction".
void XferFXAction(Xfer *xfer, void *value)
{
	xfer->XferEnum("FXAction", value, 4);
}

// ?XferFX_Types@@YAXPAVXfer@@PAX@Z
// Retail 0x00305F62 (24B): label "FX_Types".
void XferFX_Types(Xfer *xfer, void *value)
{
	xfer->XferEnum("FX_Types", value, 4);
}

// ?XferLivingWorldBattleResolutionType@@YAXPAVXfer@@PAX@Z
// Retail 0x003F3FB6 (24B): label "LivingWorldBattle::ResolutionType".
void XferLivingWorldBattleResolutionType(Xfer *xfer, void *value)
{
	xfer->XferEnum("LivingWorldBattle::ResolutionType", value, 4);
}

// ?XferLivingWorldBattleID@@YAXPAVXfer@@PAX@Z
// Retail 0x003F40BB (24B): label "LivingWorldBattleID".
void XferLivingWorldBattleID(Xfer *xfer, void *value)
{
	xfer->XferEnum("LivingWorldBattleID", value, 4);
}

// ?XferReinforcementState@@YAXPAVXfer@@PAX@Z
// Retail 0x0040C96D (24B): label "ReinforcementState".
void XferReinforcementState(Xfer *xfer, void *value)
{
	xfer->XferEnum("ReinforcementState", value, 4);
}

// ?XferRegionAwardDisputeDisputeType@@YAXPAVXfer@@PAX@Z
// Retail 0x004FBDDF (24B): label "RegionAwardDispute::DisputeType".
void XferRegionAwardDisputeDisputeType(Xfer *xfer, void *value)
{
	xfer->XferEnum("RegionAwardDispute::DisputeType", value, 4);
}

// ?XferLivingWorldBuildPlotID@@YAXPAVXfer@@PAX@Z
// Retail 0x004FC14B (24B): label "LivingWorldBuildPlotID".
void XferLivingWorldBuildPlotID(Xfer *xfer, void *value)
{
	xfer->XferEnum("LivingWorldBuildPlotID", value, 4);
}

// ?XferArmySummaryEntryID@@YAXPAVXfer@@PAX@Z
// Retail 0x0056D63B (24B): label "ArmySummaryEntryID".
void XferArmySummaryEntryID(Xfer *xfer, void *value)
{
	xfer->XferEnum("ArmySummaryEntryID", value, 4);
}

// ZH Xfer::xferKindOf (reference ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f)
// guides the save/name and load/name->single-bit branches. Target306419
// uses a free cdecl return, LightCRC enum dispatch, and no version prefix.
// These declarations use the existing 26-byte and 54-byte providers only.
enum KindOfType { KINDOF_INVALID = -1 };
class KindOfMaskType
{
public:
 static const char *getNameFromSingleBit(int bit);
};
template<int Bits> class BitFlags
{
public:
 static int getSingleBitFromName(const char *name);
};
Xfer *Rva00306419XferKindOf(Xfer *xfer, KindOfType *kind)
{
 if (xfer->IsLightCRC())
  xfer->XferEnum("KindOfType", kind, 4);
 else if (xfer->IsStoring())
 {
  AsciiString name(KindOfMaskType::getNameFromSingleBit((int)*kind));
  (*xfer) == name;
 }
 else
 {
  AsciiString name;
  (*xfer) == name;
  int bit = BitFlags<218>::getSingleBitFromName(name.str());
  if (bit != -1)
   *kind = (KindOfType)bit;
 }
 return xfer;
}
