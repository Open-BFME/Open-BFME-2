// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
//
// ?onContaining@RiderChangeContain@@UAEXPAVObject@@_N@Z, retail 0x0047E5D4
// (507 bytes): slot 39 of the RiderChangeContain contain-interface vftable
// 0x00847834 (this = RiderChangeContain+0x20, so the object is this-0x18 and
// the module data this-0x1C).  Zero Hour RiderChangeContain::onContaining is
// the body (WorldBuilder twin 0x011B1270, callgraph lead): mark containing,
// move a selected rider's selection to the container, find the rider among
// the eight RiderInfo slots at +0x1B8 and apply its model condition, weapon
// set flag, status, command set and locomotor set, mark a stealthed
// container as detected, hand the experience over, then chain to the base
// onContaining (rowed 0x0047BA10).  BFME2 differences read from retail: a
// non-allied rider goes straight to the base, the rider itself gets status
// 0x28, and the detection also goes to TheGameLogic's +0x178 manager.

#include "ascii_string.h"
#include "../../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_RIDER_CONTAINED = 0x28
};

enum WeaponSetType;
class Player;

template <int N> class Rva0047E5D4Slots : public Rva0047E5D4Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]);
};
template <> class Rva0047E5D4Slots<0>
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

struct ObjectStatusMask
{
	ObjectStatusMask *Rva0023DA79(int base, ObjectStatusTypes status, bool on);	// 0x0023DA79
	unsigned int m_words[4];
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

class MessageStream : public Rva0047E5D4Slots<18>
{
public:
	virtual GameMessage *appendMessage(int type);	// +0x48
};
extern MessageStream *TheMessageStream;

class InGameUI : public Rva0047E5D4Slots<66>
{
public:
	virtual void selectDrawable(Drawable *draw);	// +0x108
	virtual void rva0047E5D4Slot67(); virtual void rva0047E5D4Slot68(); virtual void rva0047E5D4Slot69();
	virtual void rva0047E5D4Slot70(); virtual void rva0047E5D4Slot71(); virtual void rva0047E5D4Slot72();
	virtual void rva0047E5D4Slot73(); virtual void rva0047E5D4Slot74(); virtual void rva0047E5D4Slot75();
	virtual void rva0047E5D4Slot76(); virtual void rva0047E5D4Slot77(); virtual void rva0047E5D4Slot78();
	virtual void rva0047E5D4Slot79(); virtual void rva0047E5D4Slot80(); virtual void rva0047E5D4Slot81();
	virtual void rva0047E5D4Slot82(); virtual void rva0047E5D4Slot83(); virtual void rva0047E5D4Slot84();
	virtual void rva0047E5D4Slot85(); virtual void rva0047E5D4Slot86(); virtual void rva0047E5D4Slot87();
	virtual void rva0047E5D4Slot88(); virtual void rva0047E5D4Slot89(); virtual void rva0047E5D4Slot90();
	virtual void rva0047E5D4Slot91(); virtual void rva0047E5D4Slot92(); virtual void rva0047E5D4Slot93();
	virtual void rva0047E5D4Slot94(); virtual void rva0047E5D4Slot95(); virtual void rva0047E5D4Slot96();
	virtual void rva0047E5D4Slot97(); virtual void rva0047E5D4Slot98(); virtual void rva0047E5D4Slot99();
	virtual void rva0047E5D4Slot100(); virtual void rva0047E5D4Slot101(); virtual void rva0047E5D4Slot102();
	virtual void setDisplayedMaxWarning(bool show);	// +0x19C
};
extern InGameUI *TheInGameUI;

class ControlBar
{
public:
	void markUIDirty() { m_UIDirty = true; }
private:
	char m_pad00[0x28];
	bool m_UIDirty;	// +0x28
};
extern ControlBar *TheControlBar;

// AIUpdateInterface: slot 142 (+0x238) chooses the locomotor set.
class AIUpdateInterface : public Rva0047E5D4Slots<142>
{
public:
	virtual void chooseLocomotorSet(int set);
};

class Rva00373EC6
{
public:
	void rva0037446E(int, int, int, int);	// 0x0037446E StealthUpdate::markAsDetected
};

class Rva00439E0C
{
public:
	void rva00439E0C(Object *obj, int, int, int);	// 0x00439E0C
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
	void rva0028AE6D();	// model-condition change notifier
	void setWeaponSetFlag(WeaponSetType wst);	// 0x00290963
	void Rva0028CDEB(ObjectStatusMask *mask);	// 0x0028CDEB
	void setStatus(ObjectStatusTypes status, bool set);	// 0x0023DB0E
	void setCommandSetStringOverride(const AsciiString &str);	// 0x0029336F
	bool rva002943B2(const Player *player);	// 0x002943B2
	Rva00373EC6 *rva0028F4BC();	// 0x0028F4BC stealth module

	const ThingTemplate *getTemplate() const { return m_template; }
	ObjectID getID() const { return m_id; }
	AIUpdateInterface *getAI() { return m_ai; }
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

class RiderChangeContainModuleData
{
public:
	char m_pad000[0x1B8];
	RiderInfo m_riders[MAX_RIDERS];	// +0x1B8
};

class Rva0047E5D4Module
{
public:
	virtual void rva0047E5D4Module0();
protected:
	const RiderChangeContainModuleData *m_moduleData;	// +0x04
	Object *m_object;	// +0x08
	char m_pad0C[0x20 - 0x0C];
};

// Contain interface entered at +0x20 (slot 39 is onContaining); the base
// onContaining at 0x0047BA10 is rowed under this address-named view with the
// same receiver.
class Rva0047BA10 : public Rva0047E5D4Slots<39>
{
public:
	virtual void onContaining(Object *rider, bool wasSelected) = 0;	// slot 39
	void rva0047BA10(Object *rider, bool wasSelected);
};

class RiderChangeContain : public Rva0047E5D4Module, public Rva0047BA10
{
public:
	virtual void onContaining(Object *rider, bool wasSelected);

private:
	Object *getObject() const { return m_object; }
	const RiderChangeContainModuleData *getRiderChangeContainModuleData() const { return m_moduleData; }
	char m_pad24[0x144 - 0x24];
	bool m_containing;	// +0x144
};

void RiderChangeContain::onContaining(Object *rider, bool wasSelected)
{
	Object *obj = getObject();
	if (obj->getRelationship(rider) != ALLIES)
	{
		rva0047BA10(rider, wasSelected);
		return;
	}

	m_containing = true;

	Drawable *containDraw = getObject()->getDrawable();
	if (containDraw && wasSelected && !containDraw->isSelected())
	{
		GameMessage *teamMsg = TheMessageStream->appendMessage(0x3E9);
		teamMsg->appendBooleanArgument(false);
		teamMsg->appendObjectIDArgument(getObject()->getID());
		TheInGameUI->selectDrawable(containDraw);
		TheInGameUI->setDisplayedMaxWarning(false);
	}

	const RiderChangeContainModuleData *data = getRiderChangeContainModuleData();
	for (int i = 0; i < MAX_RIDERS; i++)
	{
		const ThingTemplate *thing = TheThingFactory->findTemplate(data->m_riders[i].m_templateName);
		if (thing->isEquivalentTo(rider->getTemplate()))
		{
			obj->setModelConditionState(data->m_riders[i].m_modelConditionFlagType);
			obj->setWeaponSetFlag((WeaponSetType)data->m_riders[i].m_weaponSetFlag);
			ObjectStatusMask mask;
			obj->Rva0028CDEB(mask.Rva0023DA79(0, (ObjectStatusTypes)data->m_riders[i].m_objectStatusType, true));
			rider->setStatus(OBJECT_STATUS_RIDER_CONTAINED, true);
			obj->setCommandSetStringOverride(data->m_riders[i].m_commandSet);
			TheControlBar->markUIDirty();

			AIUpdateInterface *ai = obj->getAI();
			if (ai)
				ai->chooseLocomotorSet(data->m_riders[i].m_locomotorSetType);

			if (obj->rva002943B2(0))
			{
				Rva00373EC6 *stealth = obj->rva0028F4BC();
				if (stealth)
					stealth->rva0037446E(0, 1, 0, 1);
			}
			TheGameLogic->getManager178()->rva00439E0C(obj, 0, 0, 1);

			Rva0039ACA4 *bikeTracker = (Rva0039ACA4 *)obj->getExperienceTracker();
			Rva003BD306Target *riderTracker = (Rva003BD306Target *)rider->getExperienceTracker();
			bikeTracker->rva0039ACA4((const Rva0039ACA4 *)rider);
			riderTracker->rva0039B3D1(0.0f, true);
			break;
		}
	}

	rva0047BA10(rider, wasSelected);
	m_containing = false;
}
