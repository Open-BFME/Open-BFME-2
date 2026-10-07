// cl: /O1 /DNDEBUG /MD /GX /arch:SSE /ICode/GameEngine/Source/Common /ICode/Libraries/Include/Lib /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include
//
// StealthUpdate logic bodies between retail 0x00373D15 and 0x003758A8, the
// stretch Zero Hour's StealthUpdate.cpp (GeneralsMD GameLogic/Object/Update)
// compiles to and BFME 2 reshaped. The member offsets are the ones the rowed
// StealthUpdate constructor (StealthUpdateCtor.cpp) and xfer establish; the
// module data fields are named from the field parse table at 0x00C18210.
typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
#define NULL 0
#define TRUE 1
#define FALSE 0

#include "GameLogicObjectLookupView.h"
#include "Coord3D.h"
#include "PartitionRangeQueryCallView.h"
#include "ascii_string.h"
#include "unicode_string.h"
#include "Common/BfmeAudioEventPrefix136.h"

class Thing;
class ModuleData;
class Team;
class ThingTemplate;

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL,
	ALLIES
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_STEALTHED = 0x0F,
	OBJECT_STATUS_DETECTED = 0x11,
	OBJECT_STATUS_CAN_STEALTH = 0x12
};

enum StealthLookType
{
	STEALTHLOOK_NONE,
	STEALTHLOOK_VISIBLE_FRIENDLY,
	STEALTHLOOK_DISGUISED_ENEMY,
	STEALTHLOOK_VISIBLE_DETECTED,
	STEALTHLOOK_VISIBLE_FRIENDLY_DETECTED,
	STEALTHLOOK_INVISIBLE
};

class Drawable
{
public:
	Bool isSelected() const { return m_selected; }
private:
	char m_pad00[0x43C];
	Bool m_selected; // +0x43C
	char m_pad43D[0x440 - 0x43D];
public:
	Bool m_440;
};

class ControlBar
{
public:
	void markUIDirty() { m_UIDirty = true; }
private:
	char m_pad00[0x28];
	Bool m_UIDirty; // +0x28
};

extern ControlBar *TheControlBar;

class Team
{
public:
	Relationship getRelationship(const Team *that) const;
};

// Player::isPlayerActive (0x002AA231), rowed under an address-derived name.
class BfmeMemberRV
{
public:
	bool bfmeAskRV();
};

class Object;
class Player
{
public:
	Bool isPlayerActive() const { return ((BfmeMemberRV *)this)->bfmeAskRV(); }
	Int getPlayerIndex() const { return m_playerIndex; }
	Team *getDefaultTeam() const { return m_defaultTeam; }
	Relationship getRelationship(const Team *that) const;
	Relationship getRelationship(const Object *that) const;
	Int iterateObjects(Int (*func)(Object *, void *), void *userData) const;
private:
	char m_pad00[0x54];
	Int m_playerIndex; // +0x54
	char m_pad58[0x2EC - 0x58];
	Team *m_defaultTeam; // +0x2EC
};

class Thing
{
public:
	Drawable *getDrawable() const;
	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_pos; }
private:
	void *m_vtable;
	const ThingTemplate *m_template; // +0x04
	char m_pad08[0x38 - 0x08];
	Coord3D m_pos; // +0x38
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Module;

// The first 23 slots of ToggleHiddenSpecialAbilityUpdate's vftable
// 0x00C552D8; slot 23 is the row named turnOff (0x004AE2D0).
template <int N> class StealthUpdateSlots : public StealthUpdateSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class StealthUpdateSlots<0>
{
};

class ToggleHiddenSpecialAbilityUpdate : public StealthUpdateSlots<23>
{
public:
	virtual void turnOff() = 0; // slot 23
	virtual void turnOn() = 0; // slot 24
	virtual UnsignedInt rva0021914D() const = 0; // slot 25: the +0x88 frame turnOn stamps
};


// Object's body module (+0x254): slots 15 and 16 are Zero Hour's
// getLastDamageInfo and getLastDamageTimestamp.
struct DamageInfo
{
	char m_pad00[0x10];
	Int m_damageType; // +0x10
	char m_pad14[0x20 - 0x14];
	Real m_amount; // +0x20
};

class BodyModuleInterface : public StealthUpdateSlots<15>
{
public:
	virtual const DamageInfo *getLastDamageInfo() const = 0; // slot 15
	virtual UnsignedInt getLastDamageTimestamp() const = 0; // slot 16
};

// The contain interface Object::rva0028C197 returns; slot 59 is unnamed.
struct ContainedItemsView;
class ContainModuleInterface : public StealthUpdateSlots<59>
{
public:
	virtual Bool rvaSlot59() = 0;
	virtual void gap60() = 0;
	virtual void gap61() = 0;
	virtual void gap62() = 0;
	virtual void gap63() = 0;
	virtual void gap64() = 0;
	virtual void gap65() = 0;
	virtual void rvaSlot66(ContainedItemsView *out) = 0;
};

class Weapon
{
public:
	UnsignedInt getLastShotFrame() const { return m_lastFireFrame; }
private:
	char m_pad00[0x2C];
	UnsignedInt m_lastFireFrame; // +0x2C
};

enum WeaponSlotType
{
	PRIMARY_WEAPON,
	SECONDARY_WEAPON,
	TERTIARY_WEAPON
};

class WeaponSet
{
public:
	Weapon *getWeaponInWeaponSlot(WeaponSlotType wslot) const;
};

// KindOf bits by the retail name table at 0x00DBBE18.
enum KindOfType
{
	KINDOF_TREE = 0x5E,
	KINDOF_CAN_SHOOT_OVER_WALLS = 0xD6
};

enum ObjectScriptStatusBit
{
	OBJECT_STATUS_SCRIPT_UNSTEALTHED = 0x08
};

class UpgradeTemplate;

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};
extern UpgradeCenter *TheUpgradeCenter;

// TheTerrainLogic's query 0x0027F108, rowed under an address-derived class.
class BfmeThingCME
{
public:
	Int rva0027F108(void *pos, Real radius, Int a, Int b);
};
class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;

// BFME 2's partition filters (the view AIPlayerIsLocationSafe.cpp documents).
class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *link(Rva000421C8 *next); // 0x00625790
	Rva000421C8 *m_next;
};

class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();
private:
	unsigned char m_bytes[28];
};

struct Rva00045411BitSet
{
	Rva00045411BitSet(int unused, int bit); // 0x00045411
	unsigned int m_bits[7];
};

template <int N> class BitFlags;
extern BitFlags<116> KINDOFMASK_NONE;

// vftable 0x00BC2908: accept what has every kind of the first mask and none
// of the second.
class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b) throw();
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};

// vftable 0x00BFAD10: not effectively dead (ZH's PartitionFilterAlive).
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

extern PartitionManager *ThePartitionManager;

// STLport vector<AsciiString> as the module data holds it.
struct AsciiStringVector
{
	const AsciiString *begin() const { return m_start; }
	const AsciiString *end() const { return m_finish; }
	UnsignedInt size() const { return m_finish - m_start; }
	AsciiString *m_start;
	AsciiString *m_finish;
	AsciiString *m_endOfStorage;
};


class AIUpdateInterface
{
public:
	void rva00262FFF();
};

// The range test 0x0028F326, pinned under an address-derived class.
class Rva0028F326Owner
{
public:
	unsigned char rva0028F326(UnsignedInt victim, Real range);
};

class PlayerList
{
public:
	Player *getLocalPlayer() const { return m_local; }
	Int getPlayerCount() const { return m_playerCount; }
	Player *getNthPlayer(Int i);
private:
	char m_pad00[0x10];
	Player *m_local; // +0x10
	Int m_playerCount; // +0x14
};
extern PlayerList *ThePlayerList;

enum RadarEventType
{
	RADAR_EVENT_STEALTH_DISCOVERED = 8,
	RADAR_EVENT_STEALTH_NEUTRALIZED = 9
};

class Radar
{
public:
	void createEvent(const Coord3D *pos, RadarEventType type, Real secondsToLive = 4.0f);
};
extern Radar *TheRadar;

struct MiscAudio
{
	char m_pad00[0x30];
	OpaqueRefElement4 m_stealthDiscoveredSound; // +0x30
	OpaqueRefElement4 m_stealthNeutralizedSound; // +0x34
};

class AudioManager
{
public:
#define AUDIO_SLOT(n) virtual void slot##n();
	AUDIO_SLOT(0) AUDIO_SLOT(1) AUDIO_SLOT(2) AUDIO_SLOT(3) AUDIO_SLOT(4)
	AUDIO_SLOT(5) AUDIO_SLOT(6) AUDIO_SLOT(7) AUDIO_SLOT(8) AUDIO_SLOT(9)
	AUDIO_SLOT(10) AUDIO_SLOT(11) AUDIO_SLOT(12) AUDIO_SLOT(13) AUDIO_SLOT(14)
	AUDIO_SLOT(15) AUDIO_SLOT(16) AUDIO_SLOT(17) AUDIO_SLOT(18) AUDIO_SLOT(19)
	AUDIO_SLOT(20) AUDIO_SLOT(21) AUDIO_SLOT(22) AUDIO_SLOT(23) AUDIO_SLOT(24)
	virtual UnsignedInt addAudioEvent(const BfmeAudioEventPrefix136 *event);
	AUDIO_SLOT(26) AUDIO_SLOT(27) AUDIO_SLOT(28) AUDIO_SLOT(29)
	AUDIO_SLOT(30) AUDIO_SLOT(31) AUDIO_SLOT(32) AUDIO_SLOT(33) AUDIO_SLOT(34)
	AUDIO_SLOT(35) AUDIO_SLOT(36) AUDIO_SLOT(37) AUDIO_SLOT(38) AUDIO_SLOT(39)
	AUDIO_SLOT(40) AUDIO_SLOT(41) AUDIO_SLOT(42) AUDIO_SLOT(43) AUDIO_SLOT(44)
	AUDIO_SLOT(45) AUDIO_SLOT(46) AUDIO_SLOT(47) AUDIO_SLOT(48) AUDIO_SLOT(49)
	AUDIO_SLOT(50) AUDIO_SLOT(51) AUDIO_SLOT(52) AUDIO_SLOT(53) AUDIO_SLOT(54)
	AUDIO_SLOT(55) AUDIO_SLOT(56) AUDIO_SLOT(57) AUDIO_SLOT(58) AUDIO_SLOT(59)
	AUDIO_SLOT(60) AUDIO_SLOT(61) AUDIO_SLOT(62) AUDIO_SLOT(63) AUDIO_SLOT(64)
	AUDIO_SLOT(65) AUDIO_SLOT(66) AUDIO_SLOT(67) AUDIO_SLOT(68) AUDIO_SLOT(69)
	AUDIO_SLOT(70) AUDIO_SLOT(71) AUDIO_SLOT(72) AUDIO_SLOT(73) AUDIO_SLOT(74)
	AUDIO_SLOT(75) AUDIO_SLOT(76) AUDIO_SLOT(77)
	virtual const MiscAudio *getMiscAudio();
#undef AUDIO_SLOT
};
extern AudioManager *TheAudio;

// AudioEventRTS::setPlayerIndex (+0x6C), rowed under an address-derived name.
class Rva0033F15DDwordSlot
{
public:
	void set(int value);
};

class Eva
{
public:
	void reportEvaEvent(Int event, const Coord3D *pos, Int flag); // 0x001DE2DA
};
extern Eva *TheEva;

class GameTextInterface : public StealthUpdateSlots<15>
{
public:
	virtual UnicodeString fetch(const char *label, Bool *exists = 0) = 0; // slot 15
};
extern GameTextInterface *TheGameText;

class InGameUI : public StealthUpdateSlots<16>
{
public:
	virtual void message(UnicodeString format, ...); // slot 16
};
extern InGameUI *TheInGameUI;

// The status setter 0x003743CF, rowed under an address-derived name.
class Rva003743CF
{
public:
	void rva003743CF(void *status, Bool set);
};

// The 0x00373EEC detection-expiry update, rowed under an address-derived name.
class Rva00373EEC
{
public:
	void rva00373EEC(UnsignedInt numFrames);
};

struct ObjectListNode
{
	ObjectListNode *m_next;
	ObjectListNode *m_prev;
	Object *m_data;
};

struct ObjectList
{
	ObjectListNode *m_node;
};

struct ContainedItemsView
{
	void *m_0;
	ObjectList *m_list;
};

class StealthUpdate;
// Object::getStealth (0x0028F4BC), rowed under an address-derived name.
class Rva00373EC6;

class Object : public Thing
{
public:
	bool testStatus(ObjectStatusTypes bit) const;
	Module *findModule(NameKeyType key) const;
	Player *getControllingPlayer() const;
	Rva00373EC6 *rva0028F4BC();
	Object *rva002931F5(bool flag);
	StealthUpdate *getStealth() const { return (StealthUpdate *)((Object *)this)->rva0028F4BC(); }
	Bool isEffectivelyDead() const { return (m_privateStatus & 1) != 0; }
	Team *getTeam() const { return m_team; }
	Bool isKindOf(KindOfType t) const;
	Bool rva0028C1CC() const;
	Real rva0028AC7D() const;
	void *rva0028C197() const;
	Bool rva00290D2B(const UpgradeTemplate *upgrade) const;
	BodyModuleInterface *getBodyModule() const { return m_body; }
	Weapon *getWeaponInWeaponSlot(WeaponSlotType wslot) const { return m_weaponSet.getWeaponInWeaponSlot(wslot); }
	Bool testScriptStatusBit(ObjectScriptStatusBit bit) const { return (m_scriptStatus & bit) != 0; }
	ObjectID getID() const { return m_id; }
	AIUpdateInterface *getAI() const { return m_ai; }
private:
	char m_pad44[0x74 - 0x44];
	ObjectID m_id; // +0x74
	char m_pad78[0x254 - 0x78];
	BodyModuleInterface *m_body; // +0x254
	AIUpdateInterface *m_ai; // +0x258
	char m_pad25C[0x304 - 0x25C];
	Team *m_team; // +0x304
	char m_pad308[0x330 - 0x308];
	WeaponSet m_weaponSet; // +0x330
	char m_pad331[0x437 - 0x331];
	unsigned char m_scriptStatus; // +0x437
	unsigned char m_privateStatus; // +0x438
};

// The manager at TheGameLogic+0x178 and its call 0x00439E0C, pinned under an
// address-derived name.
class Rva00439E0C
{
public:
	void rva00439E0C(Object *obj, Int a, Int b, Int c);
};

extern GameLogic *TheGameLogic;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

class ModuleData;

class ObjectModule
{
public:
	virtual ~ObjectModule();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

class BehaviorModuleInterface
{
public:
	virtual void getBody();
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
protected:
	Object *getObject() const { return m_object; }
	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);
private:
	UnsignedInt m_nextCallFrameAndPhase; // +0x14
	Int m_indexInLogic; // +0x18
	Int m_reserved1C; // +0x1C
};

class StealthUpdateModuleData
{
public:
	char m_pad00[0x0C];
	UnsignedInt m_stealthLevel; // +0x0C StealthForbiddenConditions
	char m_pad10[0x20 - 0x10];
	Real m_stealthSpeed; // +0x20 MoveThresholdSpeed
	char m_pad24[0x30 - 0x24];
	Bool m_teamDisguised; // +0x30 DisguisesAsTeam
	char m_pad31[0x38 - 0x31];
	Bool m_orderIdleEnemiesToAttackMeUponReveal; // +0x38 OrderIdleEnemiesToAttackMeUponReveal
	char m_pad39[0x55 - 0x39];
	Bool m_innateStealth; // +0x55 InnateStealth
	Bool m_detectedByFriendliesOnly; // +0x56 DetectedByFriendliesOnly
	char m_pad57;
	UnsignedInt m_disguiseTransitionFrames; // +0x58 DisguiseTransitionTime
	UnsignedInt m_disguiseRevealTransitionFrames; // +0x5C DisguiseRevealTransitionTime
	char m_pad60[0x74 - 0x60];
	AsciiStringVector m_removeTerrainRestrictionOnUpgrade; // +0x74 RemoveTerrainRestrictionOnUpgrade
	char m_pad80[0xA4 - 0x80];
	Int m_evaEventDetectedEnemy; // +0xA4 EvaEventDetectedEnemy
	Int m_evaEventDetectedAlly; // +0xA8 EvaEventDetectedAlly
	Int m_evaEventDetectedOwner; // +0xAC EvaEventDetectedOwner
};

class StealthUpdate : public UpdateModule
{
public:
	UnsignedInt getStealthLevel() const;
	StealthUpdate *rva00373D28(Object *obj);
	void rva00373D5E();
	Bool rva00373F59(const Coord3D *pos, const Coord3D *ownerPos);
	Bool rva003742B1();
	void markAsDetected(UnsignedInt numFrames, Int feedback, Object *detector, Bool throughContainer);
	StealthLookType calcStealthedStatusForPlayer(const Object *obj, const Player *player);
	void disguiseAsObject(const Object *target);
	Bool canDisguise() const { return getStealthUpdateModuleData()->m_teamDisguised; }
	Bool isDisguised() const { return m_disguiseAsTemplate != NULL; }
	Int getDisguisedPlayerIndex() const { return m_disguiseAsPlayerIndex; }
	const ThingTemplate *getDisguisedTemplate() { return m_disguiseAsTemplate; }
private:
	const StealthUpdateModuleData *getStealthUpdateModuleData() const { return (const StealthUpdateModuleData *)m_moduleData; }

	UnsignedInt m_stealthAllowedFrame; // +0x20
	UnsignedInt m_detectionExpiresFrame; // +0x24
	UnsignedInt m_framesGranted; // +0x28
	Int m_2c; // +0x2C
	Bool m_enabled; // +0x30
	Bool m_31;
	Bool m_32;
	Bool m_33;
	Bool m_34;
	Int m_disguiseAsPlayerIndex; // +0x38
	const ThingTemplate *m_disguiseAsTemplate; // +0x3C
	UnsignedInt m_disguiseTransitionFrames; // +0x40
	Bool m_disguiseHalfpointReached; // +0x44
	Bool m_transitioningToDisguise; // +0x45
	Bool m_disguised; // +0x46
	Bool m_47;
};

// ?getStealthLevel@StealthUpdate@@QBEIXZ @0x00373D15
// The +0x2C override when set (non-negative), else the module data's
// StealthForbiddenConditions.
UnsignedInt StealthUpdate::getStealthLevel() const
{
	return m_2c >= 0 ? m_2c : getStealthUpdateModuleData()->m_stealthLevel;
}

// ?rva00373D28@StealthUpdate@@QAEPAV1@PAVObject@@@Z @0x00373D28
StealthUpdate *StealthUpdate::rva00373D28(Object *obj)
{
	Object *rider = obj->rva002931F5(false);
	if (rider != NULL)
		return rider->getStealth();
	return NULL;
}

// ?rva00373D5E@StealthUpdate@@QAEXXZ @0x00373D5E
// Turns off the owner's ToggleHiddenSpecialAbilityUpdate (found by its cached
// name key) through slot 23; update() calls it when stealth drops.
void StealthUpdate::rva00373D5E()
{
	Object *obj = getObject();
	static NameKeyType key_ToggleHiddenSpecialAbilityUpdate = TheNameKeyGenerator->nameToKey("ToggleHiddenSpecialAbilityUpdate");
	ToggleHiddenSpecialAbilityUpdate *toggle = (ToggleHiddenSpecialAbilityUpdate *)obj->findModule(key_ToggleHiddenSpecialAbilityUpdate);
	if (toggle)
		toggle->turnOff();
}

// ?setWakeupIfInRange@@YAHPAVObject@@PAX@Z @0x00373DBE
// Player::iterateObjects callback: wakes an idle AI that can see the
// revealed object (userData) so it attacks.
Int setWakeupIfInRange(Object *obj, void *userData)
{
	AIUpdateInterface *ai = obj->getAI();
	if (ai && ((Rva0028F326Owner *)obj)->rva0028F326((UnsignedInt)userData, -1.0f))
		ai->rva00262FFF();
	return 1;
}

// ?disguiseAsObject@StealthUpdate@@QAEXPBVObject@@@Z @0x00373DF0
void StealthUpdate::disguiseAsObject(const Object *target)
{
	Object *self = getObject();
	const StealthUpdateModuleData *data = getStealthUpdateModuleData();
	if (target && target->getControllingPlayer())
	{
		StealthUpdate *stealth = target->getStealth();
		if (stealth && stealth->getDisguisedTemplate())
		{
			m_disguiseAsTemplate = stealth->getDisguisedTemplate();
			m_disguiseAsPlayerIndex = stealth->getDisguisedPlayerIndex();
		}
		else
		{
			m_disguiseAsTemplate = target->getTemplate();
			m_disguiseAsPlayerIndex = target->getControllingPlayer()->getPlayerIndex();
		}

		m_enabled = true;
		m_transitioningToDisguise = true; //Means we are gaining disguise over time.
		m_disguiseTransitionFrames = data->m_disguiseTransitionFrames;
		m_disguiseHalfpointReached = false;

		//Wake up so I can process!
		setWakeFrame(getObject(), UPDATE_SLEEP_NONE);

		TheGameLogic->getManager178()->rva00439E0C(getObject(), 0, 0, 1);
	}
	else if (m_disguised)
	{
		m_disguiseAsTemplate = NULL;
		m_disguiseAsPlayerIndex = 0;
		m_disguiseTransitionFrames = data->m_disguiseRevealTransitionFrames;
		m_transitioningToDisguise = false; //Means we are losing the disguise over time.
		m_disguiseHalfpointReached = false;
	}

	Drawable *draw = self->getDrawable();
	if (draw && draw->isSelected())
	{
		TheControlBar->markUIDirty();
	}
}

// ?rva00373F59@StealthUpdate@@QAE_NPBUCoord3D@@0@Z @0x00373F59
Bool StealthUpdate::rva00373F59(const Coord3D *pos, const Coord3D *ownerPos)
{
	Object *self = getObject();
	UnsignedInt flags = getStealthLevel();

	if (!self->testStatus(OBJECT_STATUS_CAN_STEALTH))
		return FALSE;
	if (!getStealthUpdateModuleData()->m_innateStealth && !self->testStatus(OBJECT_STATUS_STEALTHED))
		return FALSE;
	if ((flags & 0x100) && self->isKindOf(KINDOF_CAN_SHOOT_OVER_WALLS))
		return FALSE;

	if (flags & 0x1000)
	{
		BodyModuleInterface *body = self->getBodyModule();
		if (body)
		{
			static NameKeyType key_ToggleHiddenSpecialAbilityUpdate = TheNameKeyGenerator->nameToKey("ToggleHiddenSpecialAbilityUpdate");
			ToggleHiddenSpecialAbilityUpdate *toggle = (ToggleHiddenSpecialAbilityUpdate *)self->findModule(key_ToggleHiddenSpecialAbilityUpdate);
			if (toggle == NULL || body->getLastDamageTimestamp() >= toggle->rva0021914D())
			{
				const DamageInfo *info = body->getLastDamageInfo();
				if (info && info->m_amount != 0.0f && info->m_damageType != 7)
					return FALSE;
			}
		}
	}

	if ((flags & 1) && self->rva0028C1CC())
		return FALSE;
	if ((flags & 4) && self->testStatus((ObjectStatusTypes)0x18))
		return FALSE;

	if ((flags & 0xF8) && self->rva0028C1CC())
	{
		if ((flags & 0xF8) == 0xF8)
			return FALSE;

		Weapon *weapon;
		UnsignedInt lastFrame = TheGameLogic->getFrame() - 1;
		if (flags & 0x08)
		{
			weapon = self->getWeaponInWeaponSlot(PRIMARY_WEAPON);
			if (weapon && weapon->getLastShotFrame() >= lastFrame)
				return FALSE;
		}
		if (flags & 0x10)
		{
			weapon = self->getWeaponInWeaponSlot(SECONDARY_WEAPON);
			if (weapon && weapon->getLastShotFrame() >= lastFrame)
				return FALSE;
		}
		if (flags & 0x20)
		{
			weapon = self->getWeaponInWeaponSlot(TERTIARY_WEAPON);
			if (weapon && weapon->getLastShotFrame() >= lastFrame)
				return FALSE;
		}
		if (flags & 0x40)
		{
			weapon = self->getWeaponInWeaponSlot((WeaponSlotType)3);
			if (weapon && weapon->getLastShotFrame() >= lastFrame)
				return FALSE;
		}
		if (flags & 0x80)
		{
			weapon = self->getWeaponInWeaponSlot((WeaponSlotType)4);
			if (weapon && weapon->getLastShotFrame() >= lastFrame)
				return FALSE;
		}
	}

	if ((flags & 2) && self->rva0028AC7D() > getStealthUpdateModuleData()->m_stealthSpeed)
		return FALSE;

	if (flags & 0x800)
	{
		Object *containedBy = self->rva002931F5(false);
		if (containedBy)
		{
			ContainModuleInterface *contain = (ContainModuleInterface *)containedBy->rva0028C197();
			if (contain && contain->rvaSlot59())
				return FALSE;
		}
	}

	if (self->testScriptStatusBit(OBJECT_STATUS_SCRIPT_UNSTEALTHED))
		return FALSE;

	if (flags & 0x200)
	{
		Object *tree = ThePartitionManager->getClosestObject(pos, 50.0f, 0,
			Rva0026119DFilter().link(&Rva0004584D(*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, KINDOF_TREE),
				*(const BfmeFixedStorage0004543D *)&KINDOFMASK_NONE)));
		if (tree == NULL || tree->isEffectivelyDead())
		{
			if (((BfmeThingCME *)TheTerrainLogic)->rva0027F108((void *)pos, 50.0f, 1, 0) == 0)
			{
				const StealthUpdateModuleData *data = getStealthUpdateModuleData();
				if (data->m_removeTerrainRestrictionOnUpgrade.size() == 0)
					return FALSE;
				for (const AsciiString *it = data->m_removeTerrainRestrictionOnUpgrade.begin();
					it != data->m_removeTerrainRestrictionOnUpgrade.end(); ++it)
				{
					if (!self->rva00290D2B(TheUpgradeCenter->findUpgrade(*it)))
						return FALSE;
				}
			}
		}
	}

	if (flags & 0x400)
	{
		StealthUpdate *ownerStealth = rva00373D28(self);
		if (ownerStealth != this)
		{
			if (ownerStealth == NULL || !ownerStealth->rva00373F59(ownerPos, ownerPos))
				return FALSE;
		}
	}

	return TRUE;
}

// ?rva003742B1@StealthUpdate@@QAE_NXZ @0x003742B1
// BFME 2's allowedToStealth entry: tests the stealth rules at the owner's
// position and at the position of the object it stealths through (rowed
// Object::rva002931F5), or at its own position twice when there is none.
Bool StealthUpdate::rva003742B1()
{
	Object *stealthOwner = getObject()->rva002931F5(false);
	if (stealthOwner == NULL)
		return rva00373F59(getObject()->getPosition(), getObject()->getPosition());
	return rva00373F59(getObject()->getPosition(), stealthOwner->getPosition());
}

// ?calcStealthedStatusForPlayer@StealthUpdate@@QAE?AW4StealthLookType@@PBVObject@@PBVPlayer@@@Z @0x003742E3
StealthLookType StealthUpdate::calcStealthedStatusForPlayer(const Object *obj, const Player *player)
{
	if (obj->isEffectivelyDead())
		return STEALTHLOOK_NONE;

	if (obj->testStatus(OBJECT_STATUS_STEALTHED))
	{
		const Team *team = obj->getTeam();
		Relationship r = team ? team->getRelationship(player->getDefaultTeam()) : NEUTRAL;
		if (!player->isPlayerActive())
			r = ALLIES;

		const StealthUpdateModuleData *data = getStealthUpdateModuleData();
		if (data->m_teamDisguised)
		{
			if (r != ALLIES && isDisguised())
				return STEALTHLOOK_DISGUISED_ENEMY;
			else
				return STEALTHLOOK_NONE;
		}

		if (obj->testStatus(OBJECT_STATUS_DETECTED))
		{
			if (data->m_detectedByFriendliesOnly)
				return STEALTHLOOK_NONE;
			if (r == ALLIES)
				return STEALTHLOOK_VISIBLE_FRIENDLY_DETECTED;
			else
				return STEALTHLOOK_VISIBLE_DETECTED;
		}
		else
		{
			if (r == ALLIES)
				return STEALTHLOOK_VISIBLE_FRIENDLY;
			else
				return STEALTHLOOK_INVISIBLE;
		}
	}
	else
	{
		return STEALTHLOOK_NONE;
	}
}

// ?markAsDetected@StealthUpdate@@QAEXIHPAVObject@@_N@Z @0x0037446E
void StealthUpdate::markAsDetected(UnsignedInt numFrames, Int feedback, Object *detector, Bool throughContainer)
{
	Object *self = getObject();
	const StealthUpdateModuleData *data = getStealthUpdateModuleData();
	Drawable *draw = self->getDrawable();

	if (!self->testStatus(OBJECT_STATUS_DETECTED))
	{
		if (throughContainer)
		{
			Object *rider = self->rva002931F5(false);
			if (rider && ((getStealthLevel() & 0x400) || rider == self))
			{
				ContainModuleInterface *contain = (ContainModuleInterface *)rider->rva0028C197();
				if (contain == NULL)
					return;
				StealthUpdate *riderStealth = rider->getStealth();
				if (riderStealth)
					riderStealth->markAsDetected(numFrames, feedback, detector, false);
				ContainedItemsView items;
				contain->rvaSlot66(&items);
				for (ObjectListNode *it = items.m_list->m_node->m_next; it != items.m_list->m_node; it = it->m_next)
				{
					StealthUpdate *stealth = it->m_data->getStealth();
					if (stealth)
						stealth->markAsDetected(numFrames, feedback, detector, false);
				}
				return;
			}
		}

		{
			ObjectStatusTypes status = OBJECT_STATUS_DETECTED;
			((Rva003743CF *)this)->rva003743CF(&status, true);
		}

		Player *thisPlayer = self->getControllingPlayer();

		//If we are disguised, remove the disguise permanently!
		if (isDisguised())
			disguiseAsObject(NULL);

		if (data->m_orderIdleEnemiesToAttackMeUponReveal)
		{
			Int numPlayers = ThePlayerList->getPlayerCount();
			for (Int n = 0; n < numPlayers; ++n)
			{
				Player *player = ThePlayerList->getNthPlayer(n);
				if (!player)
					continue;
				if (player->getRelationship(thisPlayer->getDefaultTeam()) != ENEMIES)
					continue;
				player->iterateObjects(setWakeupIfInRange, self);
			}
		}

		if (draw && feedback)
		{
			if (ThePlayerList->getLocalPlayer() == self->getControllingPlayer())
			{
				if (feedback == 2)
				{
					TheRadar->createEvent(self->getPosition(), RADAR_EVENT_STEALTH_NEUTRALIZED);
					BfmeAudioEventPrefix136 neutralizedSound(TheAudio->getMiscAudio()->m_stealthNeutralizedSound, self->getID());
					((Rva0033F15DDwordSlot *)&neutralizedSound)->set(ThePlayerList->getLocalPlayer()->getPlayerIndex());
					TheAudio->addAudioEvent(&neutralizedSound);
					TheInGameUI->message(TheGameText->fetch("MESSAGE:StealthNeutralized"));
					TheEva->reportEvaEvent(data->m_evaEventDetectedOwner, self->getPosition(), 0);
				}
			}
			else if (ThePlayerList->getLocalPlayer()->getRelationship(self) != ALLIES)
			{
				if (!draw->m_440)
				{
					TheRadar->createEvent(self->getPosition(), RADAR_EVENT_STEALTH_DISCOVERED);
					if (detector)
					{
						BfmeAudioEventPrefix136 discoveredSound(TheAudio->getMiscAudio()->m_stealthDiscoveredSound, detector->getID());
						((Rva0033F15DDwordSlot *)&discoveredSound)->set(ThePlayerList->getLocalPlayer()->getPlayerIndex());
						TheAudio->addAudioEvent(&discoveredSound);
						TheInGameUI->message(TheGameText->fetch("MESSAGE:StealthDiscovered"));
						TheEva->reportEvaEvent(data->m_evaEventDetectedEnemy, detector->getPosition(), (Int)self->getPosition());
					}
				}
			}
			else if (feedback == 2)
			{
				BfmeAudioEventPrefix136 discoveredSound(TheAudio->getMiscAudio()->m_stealthDiscoveredSound, self->getID());
				((Rva0033F15DDwordSlot *)&discoveredSound)->set(ThePlayerList->getLocalPlayer()->getPlayerIndex());
				TheAudio->addAudioEvent(&discoveredSound);
				TheEva->reportEvaEvent(data->m_evaEventDetectedAlly, self->getPosition(), 0);
			}
		}
	}

	((Rva00373EEC *)this)->rva00373EEC(numFrames);
}
