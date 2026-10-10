// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
//
// ?onRemoving@RiderChangeContain@@UAEXPAVObject@@@Z, retail 0x0047E7CF
// (599 bytes): slot 40 of the RiderChangeContain contain-interface vftable
// 0x00847834 (VA 0x008478D4), right after onContaining 0x0047E5D4 in slot 39
// (this = RiderChangeContain+0x20: the object is this-0x18 and the module
// data this-0x1C). Zero Hour RiderChangeContain::onRemoving is the body
// (WorldBuilder twin 0x011B1720, callgraph lead): a dying bike destroys the
// rider, otherwise the base onRemoving runs, the rider's RiderInfo slot
// clears its model condition, weapon set flag and status and hands the
// experience back, and a bike not being re-ridden moves the selection to
// the rider and scuttles itself. BFME2 differences read from retail: a
// non-allied rider goes straight to the base onRemoving (rowed 0x0047BB3B)
// the dead-bike check is gated by the module data byte +0x280 and the base
// call no longer waits on a created payload.

#include "ascii_string.h"
#include "../../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

enum WeaponSetType;
class Player;

template <int N> class Rva0047E7CFSlots : public Rva0047E7CFSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]);
};
template <> class Rva0047E7CFSlots<0>
{
};

class ModelConditionFlags
{
public:
	unsigned int test(unsigned int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(unsigned int bit)
	{
		m_words[bit >> 5] |= (1U << (bit & 0x1f));
	}
private:
	unsigned int m_words[19];
};

// A model-condition mask; 0x001E4912 clears it and sets two bits.
class Rva001E4912
{
public:
	Rva001E4912 *rva001E4912(int base, unsigned int bit1, unsigned int bit2);	// 0x001E4912
private:
	unsigned int m_words[19];
};

// ObjectStatusMaskType as Object::setStatus 0x0028CDEB takes it; 0x0023DA79
// clears it and sets one bit.
class Rva00346BC0
{
protected:
	unsigned int m_words[4];
};

class Rva0023DA79 : public Rva00346BC0
{
public:
	Rva0023DA79 *rva0023DA79(int base, int bit);	// 0x0023DA79
};

class ThingTemplate
{
public:
	bool isEquivalentTo(const ThingTemplate *tmpl) const;	// 0x0033BB04
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);	// 0x002D06CA
};
extern ThingFactory *TheThingFactory;

class Drawable
{
public:
	bool isSelected() const { return m_selected; }
private:
	char m_pad000[0x43C];
	bool m_selected;	// +0x43C
};

class GameMessage
{
public:
	void appendBooleanArgument(bool arg);	// 0x0030F963
	void appendObjectIDArgument(ObjectID id);	// 0x0030F979
};

class MessageStream : public Rva0047E7CFSlots<18>
{
public:
	virtual GameMessage *appendMessage(int type);	// +0x48
};
extern MessageStream *TheMessageStream;

class InGameUI : public Rva0047E7CFSlots<66>
{
public:
	virtual void selectDrawable(Drawable *draw);	// +0x108
	virtual void deselectDrawable(Drawable *draw);	// +0x10C
	virtual void rva0047E7CFSlot68(); virtual void rva0047E7CFSlot69();
	virtual void rva0047E7CFSlot70(); virtual void rva0047E7CFSlot71(); virtual void rva0047E7CFSlot72();
	virtual void rva0047E7CFSlot73(); virtual void rva0047E7CFSlot74(); virtual void rva0047E7CFSlot75();
	virtual void rva0047E7CFSlot76(); virtual void rva0047E7CFSlot77(); virtual void rva0047E7CFSlot78();
	virtual void rva0047E7CFSlot79(); virtual void rva0047E7CFSlot80(); virtual void rva0047E7CFSlot81();
	virtual void rva0047E7CFSlot82(); virtual void rva0047E7CFSlot83(); virtual void rva0047E7CFSlot84();
	virtual void rva0047E7CFSlot85(); virtual void rva0047E7CFSlot86(); virtual void rva0047E7CFSlot87();
	virtual void rva0047E7CFSlot88(); virtual void rva0047E7CFSlot89(); virtual void rva0047E7CFSlot90();
	virtual void rva0047E7CFSlot91(); virtual void rva0047E7CFSlot92(); virtual void rva0047E7CFSlot93();
	virtual void rva0047E7CFSlot94(); virtual void rva0047E7CFSlot95(); virtual void rva0047E7CFSlot96();
	virtual void rva0047E7CFSlot97(); virtual void rva0047E7CFSlot98(); virtual void rva0047E7CFSlot99();
	virtual void rva0047E7CFSlot100(); virtual void rva0047E7CFSlot101(); virtual void rva0047E7CFSlot102();
	virtual void setDisplayedMaxWarning(bool show);	// +0x19C
};
extern InGameUI *TheInGameUI;

class PlayerList
{
public:
	Player *getLocalPlayer() { return m_local; }
private:
	char m_pad00[0x10];
	Player *m_local;	// +0x10
};
extern PlayerList *ThePlayerList;

class AIUpdateInterface
{
public:
	bool isMoving() const;	// 0x00264688
};

// Experience tracker views at Object+0x264 (rowed and pinned spellings).
class Rva0039ACA4
{
public:
	void rva0039ACA4(const Rva0039ACA4 *from);	// 0x0039ACA4
};

class Rva003BD306Target
{
public:
	void rva0039B3D1(float experience, bool provideFeedback);	// 0x0039B3D1
};

class Object
{
public:
	Relationship getRelationship(const Object *that) const;	// 0x0028D156
	Drawable *getDrawable() const;	// 0x005508E2
	Player *getControllingPlayer() const;	// 0x0028AFA9
	void rva0028AE6D();	// model-condition change notifier
	void rva001E42F2(const int *flags);	// 0x001E42F2 clears model conditions
	void clearWeaponSetFlag(WeaponSetType wst);	// 0x00290A10
	void rva0028CDEB(const Rva00346BC0 &status, bool set);	// 0x0028CDEB
	void clearStatus(const Rva00346BC0 &status) { rva0028CDEB(status, false); }

	const ThingTemplate *getTemplate() const { return m_template; }
	ObjectID getID() const { return m_id; }
	AIUpdateInterface *getAI() { return m_ai; }
	bool isEffectivelyDead() const { return (m_438 & 1) != 0; }
	void *getExperienceTracker() { return m_experienceTracker; }
	// Inlined at its call sites; the out-of-line body is the matched row in
	// AIInternalMoveToStateOnExit.cpp, so this view must not emit a copy.
	__declspec(dllimport) __forceinline void setModelConditionState(unsigned int mc)
	{
		if (m_modelConditionFlags.test(mc) == 0)
		{
			m_modelConditionFlags.set(mc);
			rva0028AE6D();
		}
	}
private:
	void *m_vtable;
	const ThingTemplate *m_template;	// +0x04
	char m_pad008[0x74 - 0x08];
	ObjectID m_id;	// +0x74
	char m_pad078[0x10C - 0x78];
	ModelConditionFlags m_modelConditionFlags;	// +0x10C
	char m_pad158[0x258 - 0x158];
	AIUpdateInterface *m_ai;	// +0x258
	char m_pad25C[0x264 - 0x25C];
	void *m_experienceTracker;	// +0x264
	char m_pad268[0x438 - 0x268];
	unsigned char m_438;	// +0x438
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_UNSELECTABLE = 3,
	OBJECT_STATUS_IMMOBILE = 0x31
};

struct RiderInfo
{
	AsciiString m_templateName;	// +0x00
	int m_weaponSetFlag;	// +0x04
	int m_modelConditionFlagType;	// +0x08
	int m_objectStatusType;	// +0x0C
	AsciiString m_commandSet;	// +0x10
	int m_locomotorSetType;	// +0x14
};

enum
{
	MAX_RIDERS = 8
};

enum
{
	MODELCONDITION_DOOR_1_CLOSING = 0x16
};

class RiderChangeContainModuleData
{
public:
	char m_pad000[0x1B8];
	RiderInfo m_riders[MAX_RIDERS];	// +0x1B8
	char m_pad278[0x27C - 0x278];
	unsigned int m_scuttleState;	// +0x27C
	bool m_280;	// +0x280
};

class Rva0047E7CFModule
{
public:
	virtual void rva0047E7CFModule0();
protected:
	const RiderChangeContainModuleData *m_moduleData;	// +0x04
	Object *m_object;	// +0x08
	char m_pad0C[0x20 - 0x0C];
};

// Contain interface entered at +0x20 (slot 39 onContaining, slot 40
// onRemoving); the base onRemoving at 0x0047BB3B is rowed under this
// address-named view with the same receiver.
class Rva0047BB3BOwner : public Rva0047E7CFSlots<39>
{
public:
	virtual void onContaining(Object *rider, bool wasSelected) = 0;	// slot 39
	virtual void onRemoving(Object *rider) = 0;	// slot 40
	void rva0047BB3B(Object *rider);
};

class RiderChangeContain : public Rva0047E7CFModule, public Rva0047BB3BOwner
{
public:
	virtual void onRemoving(Object *rider);

private:
	Object *getObject() const { return m_object; }
	const RiderChangeContainModuleData *getRiderChangeContainModuleData() const { return m_moduleData; }
	char m_pad24[0x140 - 0x24];
	unsigned int m_scuttledOnFrame;	// +0x140
	bool m_containing;	// +0x144
};

void RiderChangeContain::onRemoving(Object *rider)
{
	Object *bike = getObject();
	const RiderChangeContainModuleData *data = getRiderChangeContainModuleData();
	if (bike->getRelationship(rider) != ALLIES)
	{
		rva0047BB3B(rider);
		return;
	}

	if (data->m_280 && bike->isEffectivelyDead())
	{
		TheGameLogic->destroyObject(rider);
		return;
	}

	rva0047BB3B(rider);

	for (int i = 0; i < MAX_RIDERS; i++)
	{
		const ThingTemplate *thing = TheThingFactory->findTemplate(data->m_riders[i].m_templateName);
		if (thing->isEquivalentTo(rider->getTemplate()))
		{
			Rva001E4912 clearFlags;
			bike->rva001E42F2((const int *)clearFlags.rva001E4912(0, data->m_riders[i].m_modelConditionFlagType, MODELCONDITION_DOOR_1_CLOSING));
			bike->clearWeaponSetFlag((WeaponSetType)data->m_riders[i].m_weaponSetFlag);
			Rva0023DA79 status;
			bike->clearStatus(*status.rva0023DA79(0, data->m_riders[i].m_objectStatusType));

			if (rider->getControllingPlayer() != 0)
			{
				Rva0039ACA4 *riderTracker = (Rva0039ACA4 *)rider->getExperienceTracker();
				Rva003BD306Target *bikeTracker = (Rva003BD306Target *)bike->getExperienceTracker();
				riderTracker->rva0039ACA4((const Rva0039ACA4 *)rider);
				bikeTracker->rva0039B3D1(0.0f, true);
			}
			break;
		}
	}

	if (!m_containing)
	{
		Drawable *containDraw = bike->getDrawable();
		Drawable *riderDraw = rider->getDrawable();
		if (containDraw && riderDraw)
		{
			if (bike->getControllingPlayer() == ThePlayerList->getLocalPlayer() && containDraw->isSelected())
			{
				GameMessage *teamMsg = TheMessageStream->appendMessage(0x3E9);
				teamMsg->appendBooleanArgument(false);
				teamMsg->appendObjectIDArgument(rider->getID());
				TheInGameUI->selectDrawable(riderDraw);
				TheInGameUI->setDisplayedMaxWarning(false);

				teamMsg = TheMessageStream->appendMessage(0x3ED);
				teamMsg->appendObjectIDArgument(bike->getID());
				TheInGameUI->deselectDrawable(containDraw);
			}

			m_scuttledOnFrame = TheGameLogic->getFrame();
			Rva0023DA79 status;
			bike->rva0028CDEB(*status.rva0023DA79(0, OBJECT_STATUS_UNSELECTABLE), true);
			bike->setModelConditionState(data->m_scuttleState);
			if (!bike->getAI()->isMoving())
				bike->rva0028CDEB(*status.rva0023DA79(0, OBJECT_STATUS_IMMOBILE), true);
		}
	}
}
