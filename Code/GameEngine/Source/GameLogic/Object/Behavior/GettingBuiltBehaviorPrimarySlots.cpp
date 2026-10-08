// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
//
// GettingBuiltBehavior primary-vtable (0x00C404FC) slot 5, retail 0x004534F5
// (194 bytes), installed by the matched ctor 0x004542FA. Method identity is
// not established; named by address like GettingBuiltBehaviorIfaceSlots.cpp.
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

class ThingTemplate
{
public:
	unsigned char m_pad000[0x118];
	unsigned int m_118; // +0x118
	unsigned int m_11C; // +0x11C
};

static inline unsigned int rva004534F5TestA(const ThingTemplate *t)
{
	return t->m_11C & 0x20000000;
}

static inline unsigned int rva004534F5TestB(const ThingTemplate *t)
{
	return t->m_118 & 0x10000000;
}

// ThingFactory::findTemplate (0x002D06CA) is rowed as Rva002D06CA::rva002D06CA.
class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *name);
};
class ThingFactory;
static inline const ThingTemplate *rva004534F5Find(ThingFactory *f, const AsciiString &name)
{
	return (const ThingTemplate *)((Rva002D06CA *)f)->rva002D06CA(&name);
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

struct Rva004534F5PlayerPart
{
	unsigned char m_pad000[0x1BC];
	bool m_1BC; // +0x1BC
};

class Player
{
public:
	unsigned char m_pad00[0x34];
	Rva004534F5PlayerPart *m_34; // +0x34
};

class Object
{
public:
	Player *getControllingPlayer() const;
	bool testStatus(ObjectStatusTypes bit) const;
	void *rva0028BC58(int which);
	unsigned char m_pad000[0x04];
	const ThingTemplate *m_template; // +0x04
};

struct GettingBuiltBehaviorModuleData
{
	unsigned char m_pad00[0x14];
	AsciiString m_14; // +0x14
	AsciiString m_18; // +0x18
	bool m_1C; // +0x1C
};

class GettingBuiltBehaviorInterface : public Rva004534F5Slots<4>
{
public:
	virtual void rva00453652(int a1) = 0;
};

class BehaviorModule
{
public:
	virtual ~BehaviorModule();
protected:
	const GettingBuiltBehaviorModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
	unsigned char m_pad0C[0x20 - 0x0C];
};

class GettingBuiltBehavior : public BehaviorModule, public GettingBuiltBehaviorInterface
{
public:
	virtual void rva00453652(int a1);
	virtual void rva004534F5();
};

void GettingBuiltBehavior::rva004534F5()
{
	Object *obj = m_object;
	if (!obj)
		return;
	const ThingTemplate *named = 0;
	const GettingBuiltBehaviorModuleData *data = m_moduleData;
	if (data)
	{
		if (data->m_1C)
		{
			Player *player = obj->getControllingPlayer();
			if (player)
			{
				bool alt = player->m_34 ? player->m_34->m_1BC : false;
				if (alt)
					named = rva004534F5Find(TheThingFactory, data->m_18);
				else
					named = rva004534F5Find(TheThingFactory, data->m_14);
			}
		}
		else
			named = rva004534F5Find(TheThingFactory, data->m_14);
	}
	const ThingTemplate *tmpl = obj->m_template;
	if (rva004534F5TestA(tmpl) || (rva004534F5TestB(tmpl) && (!named || rva004534F5TestA(named) || rva004534F5TestB(named))))
		rva00453652(1);
	Object *me = m_object;
	if (me->testStatus((ObjectStatusTypes)0x57))
	{
		Rva004534F5Module *module = (Rva004534F5Module *)me->rva0028BC58(0);
		if (module)
			module->rva004534F5Slot24(true);
	}
}
