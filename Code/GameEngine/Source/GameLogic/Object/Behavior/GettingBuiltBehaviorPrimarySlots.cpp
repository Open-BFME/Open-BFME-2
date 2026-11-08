// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
//
// GettingBuiltBehavior primary-vtable (0x00C404FC) slot 5, retail 0x004534F5
// (194 bytes), installed by the matched ctor 0x004542FA: onObjectCreated, the
// slot-5 name of 17 of 19 named sibling module tables (AIUpdateInterface,
// BoneFXUpdate, BattlePlanUpdate, ActivateModuleSpecialPower, ...).
//
// With an Object: the module data names a template by its +0x14 string, or,
// when its +0x1C flag is set and the controlling Player's +0x34 object has
// its +0x1BC flag, by its +0x18 string (ThingFactory::findTemplate 0x002D06CA).
// Slot 4 of the +0x20 interface runs with true when the Object's template
// carries bit 29 of its +0x11C word, or bit 28 of its +0x118 word and the
// named template is missing or carries either bit. Then an Object with
// status 0x57 hands true to slot 24 of what Object::rva0028BC58 (0) finds.
// The three findTemplate calls (one per branch) tail-merge into retail's
// single call site; a ternary on the name gives lea/push instead.

#include "ascii_string.h"

class Player;

#include "../../../../Include/Common/ThingTemplate.h"

static inline unsigned int rva004534F5TestA(const ThingTemplate *thingTemplate)
{
	return thingTemplate->m_kindof[5] & 0x20000000;
}

static inline unsigned int rva004534F5TestB(const ThingTemplate *thingTemplate)
{
	return thingTemplate->m_kindof[4] & 0x10000000;
}

// ThingFactory::findTemplate (0x002D06CA) is rowed as ThingFactory::rva002D06CA.
#include "../../../../Include/Common/ThingFactory.h"
class ThingFactory;
static inline const ThingTemplate *rva004534F5Find(ThingFactory *thingFactory, const AsciiString &name)
{
	return ((ThingFactory *)thingFactory)->findTemplate(name);
}

extern ThingFactory *TheThingFactory;

enum ObjectStatusTypes
{
	OBJECT_STATUS_NONE = 0
};

template <int N> class Rva004534F5Slots : public Rva004534F5Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva004534F5Slots<1>
{
public:
	virtual void gap(char (*)[1]) = 0;
};

// What Object::rva0028BC58 (0) hands back: slot 24 runs on it with true.
class Rva004534F5Module : public Rva004534F5Slots<24>
{
public:
	virtual void rva004534F5Slot24(bool flag) = 0;
};

#include "../../../../Include/Common/PlayerTemplate.h"
#include "../../../../Include/Common/Player.h"

#include "../object.h"

#include "../../../../Include/GameLogic/Module/GettingBuiltBehaviorModuleData.h"

class GettingBuiltBehaviorInterface : public Rva004534F5Slots<4>
{
public:
	virtual void rva00453652(int a1) = 0;
};

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"
#include "../../../../Include/GameLogic/Module/UpdateModule.h"

class GettingBuiltBehavior : public UpdateModule, public GettingBuiltBehaviorInterface
{
public:
	virtual void rva00453652(int a1);
	virtual void onObjectCreated();
};

void GettingBuiltBehavior::onObjectCreated()
{
	Object *obj = m_object;
	if (!obj)
		return;
	const ThingTemplate *named = 0;
	const GettingBuiltBehaviorModuleData *data = static_cast<const GettingBuiltBehaviorModuleData *>(m_moduleData);
	if (data)
	{
		if (data->m_testFaction)
		{
			Player *player = obj->getControllingPlayer();
			if (player)
			{
				bool alt = player->m_playerTemplate ? player->m_playerTemplate->m_isEvil : false;
				if (alt)
					named = rva004534F5Find(TheThingFactory, data->m_evilWorkerName);
				else
					named = rva004534F5Find(TheThingFactory, data->m_workerName);
			}
		}
		else
			named = rva004534F5Find(TheThingFactory, data->m_workerName);
	}
	const ThingTemplate *thingTemplate = obj->m_template;
	if (rva004534F5TestA(thingTemplate) || (rva004534F5TestB(thingTemplate) && (!named || rva004534F5TestA(named) || rva004534F5TestB(named))))
		rva00453652(1);
	Object *me = m_object;
	if (me->testStatus((ObjectStatusTypes)0x57))
	{
		Rva004534F5Module *module = (Rva004534F5Module *)me->rva0028BC58(0);
		if (module)
			module->rva004534F5Slot24(true);
	}
}
