// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD
// GarrisonContain::onObjectCreated, retail 0x004787B0 (160 bytes):
// ?onObjectCreated@GarrisonContain@@UAEXXZ
// Identity (target): WorldBuilder's debug GarrisonContain.cpp
// GarrisonContain::onObjectCreated; retail follows Zero Hour's body and
// callee order: ThingFactory::findTemplate on the initial roster's template
// name, then per roster entry Object::getControllingPlayer (its default
// team, Player +0x2EC), ThingFactory::newObject (0x002D0A23) and the
// object's contain module's isValidContainerFor / addToContain (slots
// 0x98 / 0x9C).
// BFME 2 deltas (target): nothing at all without a positive roster count;
// newObject takes a zeroed 16-byte creation mask and false; the contain
// module is Object +0x250. Layout (target): module data +0x04 with the
// roster template name at +0xA4 and count at +0xA8; object +0x08.
#include <string.h>
#include "ascii_string.h"

class Object;
class Team;
class ThingTemplate;

struct CreateMask
{
	unsigned int m_bits[4];
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
	Object *newObject(const ThingTemplate *tmplate, Team *team, const CreateMask *mask, bool b);
};

extern ThingFactory *TheThingFactory;

class Player
{
public:
	Team *getDefaultTeam() { return m_defaultTeam; }

private:
	unsigned char m_pad000[0x2EC];
	Team *m_defaultTeam; // +0x2EC
};

class ContainModuleInterface
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
	virtual void v36(); virtual void v37();
	virtual bool isValidContainerFor(const Object *obj, bool checkCapacity, int flags); // slot 0x98
	virtual void addToContain(Object *obj); // slot 0x9C
};

class Object
{
public:
	Player *getControllingPlayer() const;
	ContainModuleInterface *getContain() const { return m_contain; }

private:
	unsigned char m_pad000[0x250];
	ContainModuleInterface *m_contain; // +0x250
};

struct InitialRoster
{
	AsciiString templateName; // +0xA4
	int count; // +0xA8
};

struct GarrisonContainModuleData
{
	unsigned char m_pad00[0xA4];
	InitialRoster m_initialRoster; // +0xA4
};

class GarrisonContain
{
public:
	virtual void onObjectCreated();

private:
	const GarrisonContainModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

void GarrisonContain::onObjectCreated()
{
	const GarrisonContainModuleData *self = m_moduleData;
	int count = self->m_initialRoster.count;
	if (count <= 0)
		return;
	const ThingTemplate *rosterTemplate = TheThingFactory->findTemplate(self->m_initialRoster.templateName);
	Object *object = m_object;

	for (int i = 0; i < count; i++)
	{
		// We are creating a garrison that comes with an initial roster, so add it now!
		CreateMask mask;
		memset(&mask, 0, sizeof(mask));
		Object *payload = TheThingFactory->newObject(rosterTemplate, object->getControllingPlayer()->getDefaultTeam(), &mask, false);
		if (object->getContain() && object->getContain()->isValidContainerFor(payload, true, 0))
			object->getContain()->addToContain(payload);
	}
}
