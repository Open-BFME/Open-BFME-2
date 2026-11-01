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

enum ObjectID; class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
	Object *newObject(const ThingTemplate *tmplate, Team *team, const CreateMask *mask, ObjectID b);
};

extern ThingFactory *TheThingFactory;

class Player
{
public:
	Team *getDefaultTeam() { return m_defaultTeam; }
	// LINK: same-body helper under a TU-unique name (identical inlined
	// bytes). This TU's getDefaultTeam copy is not retail's; the call below
	// inlines it but still emits the loser COMDAT. Rebinding there emits only
	// this unique (trivially kept) copy. No flags touched.
	Team *bfme_default_team() { return m_defaultTeam; }

private:
	unsigned char m_pad000[0x2EC];
	Team *m_defaultTeam; // +0x2EC
};

#include "../../../../Include/GameLogic/Module/ContainModule.h"

#include "../object.h"

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
		Object *payload = TheThingFactory->newObject(rosterTemplate, object->getControllingPlayer()->bfme_default_team(), &mask, (ObjectID)0);
		if (object->getContain() && object->getContain()->isValidContainerFor(payload, true, 0))
			object->getContain()->addToContain(payload);
	}
}
