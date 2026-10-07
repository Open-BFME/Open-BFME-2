// cl: /O1 /DNDEBUG /MD /GX /ICode/GameEngine/Source/Common /ICode/Libraries/Include/Lib
//
// StealthUpdate logic bodies between retail 0x00373D5E and 0x003758A8, the
// stretch Zero Hour's StealthUpdate.cpp (GeneralsMD GameLogic/Object/Update)
// compiles to and BFME 2 reshaped. The member offsets are the ones the rowed
// StealthUpdate constructor (StealthUpdateCtor.cpp) and xfer establish; the
// module data fields are named from the field parse table at 0x00C18210.
typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
#define NULL 0

#include "GameLogicObjectLookupView.h"
#include "Coord3D.h"

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

class Player
{
public:
	Bool isPlayerActive() const { return ((BfmeMemberRV *)this)->bfmeAskRV(); }
	Int getPlayerIndex() const { return m_playerIndex; }
	Team *getDefaultTeam() const { return m_defaultTeam; }
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
private:
	char m_pad44[0x304 - 0x44];
	Team *m_team; // +0x304
	char m_pad308[0x438 - 0x308];
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
	char m_pad00[0x30];
	Bool m_teamDisguised; // +0x30 DisguisesAsTeam
	char m_pad31[0x56 - 0x31];
	Bool m_detectedByFriendliesOnly; // +0x56 DetectedByFriendliesOnly
	char m_pad57;
	UnsignedInt m_disguiseTransitionFrames; // +0x58 DisguiseTransitionTime
	UnsignedInt m_disguiseRevealTransitionFrames; // +0x5C DisguiseRevealTransitionTime
};

class StealthUpdate : public UpdateModule
{
public:
	void rva00373D5E();
	Bool rva00373F59(const Coord3D *pos, const Coord3D *ownerPos);
	Bool rva003742B1();
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
