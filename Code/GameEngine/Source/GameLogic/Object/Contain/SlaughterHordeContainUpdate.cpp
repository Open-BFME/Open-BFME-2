// cl: /DNDEBUG /MD
//
// SlaughterHordeContain::update and its two iterate callbacks.
//
// ?update@SlaughterHordeContain@@UAE?AW4UpdateSleepTime@@XZ, retail 0x00480E72, 40 bytes.
// Slot 0 of the +0x10 UpdateModuleInterface vftable 0x00C48A90 (this at
// +0x10, as in the rowed DeletionUpdate::update): walks the owner's
// contained objects (its contain module at Object+0x250, slot 68) with the
// first callback, then returns the base update (pinned
// GarrisonContain::update 0x00479643; CitadelSlaughterHordeContain's update
// tail-calls this one).
//
// ?rva00480E28@@YAXPAVObject@@PAX@Z, retail 0x00480E28, 74 bytes.
// For a contained object of kind-of bit 77 that contains objects itself,
// walks those twice (iterate flags 1 and 0x10) with the second callback.
//
// ?rva00480DF4@@YAXPAVObject@@PAX@Z, retail 0x00480DF4, 52 bytes.
// For an object with an AI (Object+0x258) not in AI state 0x38 or 0x0F (rowed
// AIUpdateInterface::rva00260DED), issues the rowed
// AICommandInterface::rva0036EBB8 at the walking contain's owner (command
// source 2).
//
// ?update@CitadelSlaughterHordeContain@@UAE?AW4UpdateSleepTime@@XZ, retail 0x00480FE2, 107 bytes.
// Slot 0 of CitadelSlaughterHordeContain's +0x10 vftable 0x00C48CB0: when the
// ObjectID at +0x9EC (the one its rowed xfer transfers) names a live object,
// orders that object's AI with the owner and the source its slot 143
// reports (rowed AICommandInterface::rva0037379B for kind-of bit 77, the
// rowed aiExit otherwise), clears the ID, then returns
// SlaughterHordeContain::update.
//
// Callback names are address names; their identities are not established.

#define SLOT08(a,b,c,d,e,f,g,h) virtual void a(); virtual void b(); virtual void c(); virtual void d(); virtual void e(); virtual void f(); virtual void g(); virtual void h();

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 0
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

enum KindOfType
{
	KINDOF_INVALID = -1
};

class Object;

typedef void (*ContainIterateFunc)(Object *obj, void *userData);

#include "../../../../Include/GameLogic/Module/ContainModule.h"

#include "../../../../Include/GameLogic/Module/AIUpdate.h"

class Rva0010CBits
{
public:
	unsigned int test(int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
private:
	unsigned int m_words[20];
};

#include "../../../Common/GameLogicObjectLookupView.h"

#include "../../../../Include/Common/ThingTemplate.h"
// isKindOf through the kindof bits from +0x10C.
static __forceinline unsigned int thingTemplateIsKindOf(const ThingTemplate *tmpl, KindOfType t) { return ((const Rva0010CBits *)(tmpl->m_kindof + 1))->test(t); }

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	ContainModuleInterface *getContain() const { return m_contain; }
	AIUpdateInterface *getAI() const { return m_ai; }
private:
	void *m_vtable;
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad008[0x250 - 0x08];
	ContainModuleInterface *m_contain; // +0x250
	unsigned char m_pad254[0x258 - 0x254];
	AIUpdateInterface *m_ai; // +0x258
};

// ?rva00480DF4@@YAXPAVObject@@PAX@Z @0x00480DF4
void rva00480DF4(Object *obj, void *userData)
{
	if (obj == 0)
		return;
	AIUpdateInterface *ai = obj->getAI();
	if (ai == 0)
		return;
	int state = ai->rva00260DED();
	if (state == 0x38 || state == 0x0F)
		return;
	ai->rva0036EBB8((Object *)userData, (CommandSourceType)2);
}

// ?rva00480E28@@YAXPAVObject@@PAX@Z @0x00480E28
void rva00480E28(Object *obj, void *userData)
{
	if (obj == 0)
		return;
	if (!thingTemplateIsKindOf(obj->getTemplate(), (KindOfType)77))
		return;
	ContainModuleInterface *contain = obj->getContain();
	if (contain == 0)
		return;
	contain->iterateContained(rva00480DF4, userData, 1);
	contain->iterateContained(rva00480DF4, userData, 0x10);
}

struct Iface00 { virtual void f00(); const void *m_moduleData; Object *m_object; };
struct Iface0C { virtual void f0C(); };
struct Iface10 { virtual UpdateSleepTime update() = 0; unsigned char m_pad[12]; };

class GarrisonContain : public Iface00, public Iface0C, public Iface10
{
public:
	virtual UpdateSleepTime update();
};

class HordeGarrisonContain : public GarrisonContain
{
};

class SlaughterHordeContain : public HordeGarrisonContain
{
public:
	virtual UpdateSleepTime update();
};

// ?update@SlaughterHordeContain@@UAE?AW4UpdateSleepTime@@XZ @0x00480E72
UpdateSleepTime SlaughterHordeContain::update()
{
	Object *obj = m_object;
	if (obj)
		obj->getContain()->iterateContained(rva00480E28, obj, 1);
	return GarrisonContain::update();
}


extern GameLogic *TheGameLogic;

class CitadelSlaughterHordeContainBody : public SlaughterHordeContain
{
	unsigned char m_pad20[0x9EC - 0x20];
};

class CitadelSlaughterHordeContain : public CitadelSlaughterHordeContainBody
{
public:
	virtual UpdateSleepTime update();
private:
	ObjectID m_9EC;
};

// ?update@CitadelSlaughterHordeContain@@UAE?AW4UpdateSleepTime@@XZ @0x00480FE2
UpdateSleepTime CitadelSlaughterHordeContain::update()
{
	if (m_9EC != INVALID_OBJECT_ID)
	{
		Object *other = TheGameLogic->findObjectByID(m_9EC);
		if (other)
		{
			Object *me = m_object;
			AIUpdateInterface *ai = other->getAI();
			if (thingTemplateIsKindOf(other->getTemplate(), (KindOfType)77))
				ai->rva0037379B(me, ai->vslot143());
			else
				ai->aiExit(me, ai->vslot143());
		}
		m_9EC = INVALID_OBJECT_ID;
	}
	return SlaughterHordeContain::update();
}
