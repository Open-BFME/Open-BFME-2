// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD
//
// TaintSpecialPower::addObject, retail 0x004C4940 (110B), from the WorldBuilder
// lead (TaintSpecialPower.cpp): create an object of the named template
// (ThingFactory::findTemplate, then ThingFactory::newObject with no team and a
// zeroed 16-byte create mask), place it at the position and give it the
// owning object's team (module +0x08 object, Object +0x304 team;
// Object::setTeam); returns the new object, or NULL without a template.
// The 0x004C45CF CloudBreakSpecialPower::addObject twin skips the team.

#include "ascii_string.h"
#include <string.h>

#include "../../../../../Libraries/Include/Lib/Coord3D.h"

class Team;
class ThingTemplate;

struct CreateMask
{
	unsigned int m_bits[4];
};

class Thing
{
public:
	void setPosition(const Coord3D *pos);
};

class Object : public Thing
{
public:
	void setTeam(Team *team);
	Team *getTeam() const { return m_team; }

private:
	unsigned char m_pad00[0x304];
	Team *m_team;
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
	Object *newObject(const ThingTemplate *tmplate, Team *team, const CreateMask *mask, bool b);
};
extern ThingFactory *TheThingFactory;

class TaintSpecialPower
{
public:
	Object *addObject(const Coord3D *pos, const AsciiString &templateName);
	Object *getObject() const { return m_object; }

private:
	void *m_vtbl;
	void *m_moduleData;
	Object *m_object;
};

Object *TaintSpecialPower::addObject(const Coord3D *pos, const AsciiString &templateName)
{
	const ThingTemplate *tmplate = TheThingFactory->findTemplate(templateName);
	if (tmplate)
	{
		CreateMask mask;
		memset(&mask, 0, sizeof(mask));
		Object *obj = TheThingFactory->newObject(tmplate, 0, &mask, false);
		if (obj)
		{
			obj->setPosition(pos);
			obj->setTeam(getObject()->getTeam());
		}
		return obj;
	}
	return 0;
}
