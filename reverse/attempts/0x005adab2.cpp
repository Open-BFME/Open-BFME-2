// ?rva005ADAB2@Rva005ADA40@@QAEXXZ
// partial score=0.97 date=2026-10-05
// ?rva005ADAB2@Rva005ADA40@@QAEXXZ
// partial score=0.97 date=2026-10-04
// cl: /O1 /MD /GX /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /arch:SSE /Ireference/shims/bfme2_ascii
// stlport
//
// The 0x2C-byte elements the skirmish-AI object Rva00506B74 owns in its +0x0C
// vector (Rva00506B74Tactic.cpp builds them with operator new and this ctor,
// deletes them, and calls their pinned members). Layout from the ctor:
//   +0x00 vector of owned Rva005DCE08 (non-virtual dtor 0x005DCE08)
//   +0x0C the element's index, +0x10 cleared, +0x14 the owner
//   +0x18 Coord3D and +0x24 float, both zeroed
//   +0x28 an owned polymorphic object
//
//   0x005AD9FF  ctor (index, owner)
//   0x005ADA40  dtor: delete every item, ::delete the +0x28 object, free
//               the vector
//   0x005AD9C0  the first item hit (0x005DCC86) by the argument
//   0x005AD964  whether the owner's start position is not yet among
//               TheSkirmishAIManager's +0x864 list
//   0x005ADC63  update: retire the +0x28 object once done (0x004E9378), or
//               start one (0x005ADAB2); then update every item
#include <vector>
#include <list>
#include "ascii_string.h"

struct Coord3DBase
{
	float x;
	float y;
	float z;
};

struct Coord3D : public Coord3DBase
{
	void zero() { x = 0.0f; y = 0.0f; z = 0.0f; }
};

class Rva005AD9C0Hit;

class Rva005DCE08
{
public:
	~Rva005DCE08();
	Rva005AD9C0Hit *rva005DCC86(void *arg);
	void rva005DCCFB();
};

class Rva004E9378
{
public:
	bool rva004E9378();
};

class Rva00506FE9Hit
{
public:
	void rva0055ADBA(void *owner);
};

class GameSlot
{
public:
	char m_pad00[0x10];
	int m_10;		// +0x10, the slot's start position index
	char m_pad14[0x18 - 0x14];
	int m_18;		// +0x18, the slot's player template index
};

struct Rva00506C82Arg;
GameSlot *__cdecl Rva00506C82Find(const Rva00506C82Arg *arg);

struct Rva002A8AB1Record;

class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *owner);
	char m_pad000[0x864];
	_STL::vector<int> m_usedStarts;	// +0x864
};
extern Rva002A8F24 *g_00DFEEF8;

class Rva005ADA40Owned
{
public:
	virtual ~Rva005ADA40Owned();
};

enum ObjectID
{
	INVALID_ID = 0
};

class Object
{
public:
	char m_pad00[0x38];
	Coord3D m_pos;		// +0x38
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;

class PlayerTemplate
{
public:
	char m_pad00[0x44];
	AsciiString m_side;	// +0x44
};

class PlayerTemplateStore
{
public:
	const PlayerTemplate *getNthPlayerTemplate(int which) const;
};
extern PlayerTemplateStore *ThePlayerTemplateStore;

class ThingTemplate;

class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *key);
};
extern Rva002D06CA *TheThingFactory;

class Rva001DB720Predicate
{
public:
	bool accepts(ThingTemplate *tmpl);
};

class Rva005AD9E6
{
public:
	unsigned int rva005AD9E6();
private:
	void *m_head;
};

struct Rva002A8AB1Target
{
	char m_pad00[0x20];
	int m_20;		// +0x20
};

struct Rva002A8AB1Record
{
	char m_pad000[0x140];
	Rva005AD9E6 m_140;			// +0x140
	_STL::list<ObjectID> m_144;		// +0x144
	char m_pad148[0x160 - 0x148];
	Rva002A8AB1Target *m_160;		// +0x160
	char m_pad164[0x16C - 0x164];
	int m_16C;				// +0x16C
};

class Rva00573A00
{
public:
	void rva00573A00(const Coord3D *point);
};

class Rva00573E7C
{
public:
	Rva00573E7C();
	virtual ~Rva00573E7C();
	virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
	virtual void v5();
	virtual void start(void *owner, int a);	// slot 6
	virtual void run(int a);		// slot 7
	int m_04;		// +0x04
	char m_pad08[0x0C - 8];
	AsciiString m_name;	// +0x0C
	char m_pad10[0x21 - 0x10];
	bool m_21;		// +0x21
	char m_pad22[0x40 - 0x22];
	Coord3D m_point;	// +0x40
	float m_angle;		// +0x4C
	char m_pad50[0x60 - 0x50];
};

class Rva005ADA40
{
public:
	Rva005ADA40(unsigned int index, void *owner);
	~Rva005ADA40();
	Rva005AD9C0Hit *rva005AD9C0(void *arg);
	bool rva005AD964();
	void rva005ADAB2();
	void rva005ADC63();
private:
	_STL::vector<Rva005DCE08 *> m_items;	// +0x00
	unsigned int m_index;			// +0x0C
	int m_10;				// +0x10
	void *m_owner;				// +0x14
	Coord3D m_point;			// +0x18
	float m_angle;				// +0x24
	Rva00573E7C *m_owned;			// +0x28
};

Rva005ADA40::Rva005ADA40(unsigned int index, void *owner)
{
	m_10 = 0;
	m_index = index;
	m_owner = owner;
	m_point.zero();
	m_owned = 0;
	m_angle = 0.0f;
}

Rva005ADA40::~Rva005ADA40()
{
	for (Rva005DCE08 **it = m_items.begin(); it != m_items.end(); ++it)
		delete *it;
	if (m_owned) {
		::delete m_owned;
		m_owned = 0;
	}
}

Rva005AD9C0Hit *Rva005ADA40::rva005AD9C0(void *arg)
{
	Rva005AD9C0Hit *hit = 0;
	for (Rva005DCE08 **it = m_items.begin(); it != m_items.end(); ++it) {
		hit = (*it)->rva005DCC86(arg);
		if (hit)
			break;
	}
	return hit;
}

void Rva005ADA40::rva005ADC63()
{
	Rva00573E7C *owned = m_owned;
	if (owned) {
		if (((Rva004E9378 *)owned)->rva004E9378()) {
			((Rva00506FE9Hit *)owned)->rva0055ADBA(m_owner);
			::delete m_owned;
			m_owned = 0;
		}
	} else {
		rva005ADAB2();
	}
	for (Rva005DCE08 **it = m_items.begin(); it != m_items.end(); ++it)
		(*it)->rva005DCCFB();
}

bool Rva005ADA40::rva005AD964()
{
	GameSlot *slot = Rva00506C82Find((const Rva00506C82Arg *)m_owner);
	if (slot) {
		int start = slot->m_10 + 1;
		_STL::vector<int> &used = g_00DFEEF8->m_usedStarts;
		int *end = used.end();
		for (int *it = used.begin(); it != end; ++it) {
			if (*it == start)
				return false;
		}
	}
	return true;
}

void Rva005ADA40::rva005ADAB2()
{
	GameSlot *slot = Rva00506C82Find((const Rva00506C82Arg *)m_owner);
	const AsciiString &side = ThePlayerTemplateStore->getNthPlayerTemplate(slot->m_18)->m_side;
	ThingTemplate *tmpl = (ThingTemplate *)TheThingFactory->rva002D06CA(&side);
	if (!((Rva001DB720Predicate *)m_owner)->accepts(tmpl))
		return;
	Rva002A8AB1Record *record = g_00DFEEF8->rva002A8AB1(m_owner);
	int count = record->m_16C;
	if (count < 1)
		return;
	if (record->m_140.rva005AD9E6() <= 0)
		return;
	if (m_owned && !((Rva004E9378 *)m_owned)->rva004E9378())
		return;
	bool clear = true;
	_STL::list<ObjectID>::iterator end = record->m_144.end();
	for (_STL::list<ObjectID>::iterator it = record->m_144.begin(); it != end; ++it) {
		if (!clear)
			break;
		Object *obj = TheGameLogic->findObjectByID(*it);
		if (obj) {
			float dx = m_point.x - obj->m_pos.x;
			float dy = m_point.y - obj->m_pos.y;
			if (dx * dx + dy * dy <= 350.0f * 350.0f)
				clear = false;
		}
	}
	if (!clear)
		return;
	if (!m_owned) {
		m_owned = new Rva00573E7C;
		m_owned->m_point = m_point;
		Coord3D zero;
		zero.zero();
		((Rva00573A00 *)m_owned)->rva00573A00(&zero);
		m_owned->m_04 = record->m_160->m_20;
		m_owned->m_angle = m_angle;
		m_owned->m_name = side;
		m_owned->m_21 = true;
	}
	m_owned->run(0);
	m_owned->start(m_owner, 0);
}
