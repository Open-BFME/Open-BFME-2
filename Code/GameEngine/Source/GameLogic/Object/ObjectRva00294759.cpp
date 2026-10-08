// cl: /Ireference/shims/bfme2_ascii
// ?rva00294759@Rva00294759@@QAEXH@Z @0x00294759 79B
// Unlock: __thiscall ret 4 with int param; this+0x264 is ExperienceTracker
// (m_24 at +0x24 compared to param); rowed rva0029439D 0x0029439D twice plus
// virtual slot 0xc4 loop esi times; pin rva0039B4EC 0x0039B4EC (int bool bool).
// Evidence: callers 0x002947CE 0x002952D5 0x003C7E99; prev ObjectRva002943B2
// /O1 /G7; next StlportListInsertFootprints /O1.
#include "ascii_string.h"

class Image;
class Team;
class ThingTemplate;
class Object;

// The template's KindOf bits sit at +0x108; bit 190 (byte +0x11F, 0x40)
// marks a create-a-hero unit.
struct ObjectPortraitTemplateView
{
	unsigned char m_pad[0x11F];
	unsigned char m_11F;
};

// 0x0033BC53: null-guarded template portrait lookup for an object.
const Image *Rva0033BC53Get(ThingTemplate *tmpl, void *obj);

// The +0x4B4 module (rowed 0x0028F4BC): +0x3C names a template to show.
class Rva00373EC6
{
public:
	char m_pad[0x3C];
	ThingTemplate *m_3C;
};

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

class Player
{
public:
	Relationship getRelationship(const Team *that) const;
};

// Rowed 0x002A7DD0 runs on ThePlayerList and returns its negated
// local-player query as an int.
class Rva002A7DD0
{
public:
	int rva002A7DD0();
};

// ThePlayerList: +0x10 is the local player.
class PlayerList
{
public:
	Player *getLocalPlayer() { return m_local; }

	char m_pad[0x10];
	Player *m_local;
};
extern PlayerList *ThePlayerList;

class CreateAHeroData
{
public:
	char m_pad[0x138];
	const Image *m_portrait; // +0x138
};

class CreateAHeroManager
{
public:
	CreateAHeroData *rva002197A6(int key);
};
extern CreateAHeroManager *TheCreateAHeroManager;

// Interface slot 21 of the rowed 0x0029439D lookup returns another object.
class ObjectPortraitSource
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20();
	virtual Object *v21(); // vslot 0x54
};

class Object
{
public:
	void *rva0029439D();
	void rva00293275(AsciiString s);
	Rva00373EC6 *rva0028F4BC();
	ThingTemplate *rva002911B7();
	const Image *getObjectSelectedPortraitImage();
	ThingTemplate *getTemplate() const { return m_template; }
	Team *getTeam() const { return m_team; }

	char m_pad00[4];
	ThingTemplate *m_template; // +0x04
	char m_pad08[0x74 - 0x08];
	int m_74; // +0x74, the create-a-hero key
	char m_pad78[0x304 - 0x78];
	Team *m_team; // +0x304
};

// Retail 0x002946AB, 174 bytes (WorldBuilder's
// Object::getObjectSelectedPortraitImage, Object.cpp): a portrait borrowed
// from the 0x0029439D source's object first; a create-a-hero unit shows its
// module's +0x3C template when the list query allows and the local player
// is its enemy, else the hero entry's portrait; otherwise the template
// 0x002911B7 picks (the same module test) or the object's own.
const Image *Object::getObjectSelectedPortraitImage()
{
	ObjectPortraitSource *source = (ObjectPortraitSource *)rva0029439D();
	if (source)
	{
		Object *obj = source->v21();
		if (obj)
			return Rva0033BC53Get(obj->getTemplate(), obj);
	}
	if (((ObjectPortraitTemplateView *)m_template)->m_11F & 0x40)
	{
		Rva00373EC6 *module = rva0028F4BC();
		if (module && module->m_3C != 0 && !(unsigned char)((Rva002A7DD0 *)ThePlayerList)->rva002A7DD0()
			&& ThePlayerList->getLocalPlayer()->getRelationship(getTeam()) == ENEMIES)
		{
			ThingTemplate *tmpl = module->m_3C;
			if (tmpl)
				return Rva0033BC53Get(tmpl, this);
		}
		CreateAHeroData *hero = TheCreateAHeroManager->rva002197A6(m_74);
		if (hero && hero->m_portrait)
			return hero->m_portrait;
	}
	ThingTemplate *tmpl = rva002911B7();
	if (!tmpl)
		tmpl = m_template;
	return Rva0033BC53Get(tmpl, this);
}

class ExperienceTracker
{
public:
	bool rva0039B4EC(int a, bool b, bool c);
	char m_pad[0x24];
	int m_24;
};

struct V49Holder
{
	virtual void f00();
	virtual void f01();
	virtual void f02();
	virtual void f03();
	virtual void f04();
	virtual void f05();
	virtual void f06();
	virtual void f07();
	virtual void f08();
	virtual void f09();
	virtual void f10();
	virtual void f11();
	virtual void f12();
	virtual void f13();
	virtual void f14();
	virtual void f15();
	virtual void f16();
	virtual void f17();
	virtual void f18();
	virtual void f19();
	virtual void f20();
	virtual void f21();
	virtual void f22();
	virtual void f23();
	virtual void f24();
	virtual void f25();
	virtual void f26();
	virtual void f27();
	virtual void f28();
	virtual void f29();
	virtual void f30();
	virtual void f31();
	virtual void f32();
	virtual void f33();
	virtual void f34();
	virtual void f35();
	virtual void f36();
	virtual void f37();
	virtual void f38();
	virtual void f39();
	virtual void f40();
	virtual void f41();
	virtual void f42();
	virtual void f43();
	virtual void f44();
	virtual void f45();
	virtual void f46();
	virtual void f47();
	virtual void f48();
	virtual void f49();
};

class Rva00294759
{
public:
	void rva00294759(int param);
	void rva002947A8();
private:
	char m_pad[0x264];
	ExperienceTracker *m_exp;
	char m_pad268[0x494 - 0x268];
	AsciiString m_494;
	int m_498;
};

void Rva00294759::rva00294759(int param)
{
	ExperienceTracker *exp = m_exp;
	if (exp == 0)
		return;
	if (exp->m_24 == param)
		return;
	int diff = param - exp->m_24;
	exp->rva0039B4EC(diff, false, false);
	Object *o = (Object *)((Object *)this)->rva0029439D();
	if (o == 0)
		return;
	if (diff <= 0)
		return;
	for (;;) {
		void *p = ((Object *)this)->rva0029439D();
		((V49Holder *)p)->f49();
		if (--diff == 0)
			break;
	}
}

// ?rva002947A8@Rva00294759@@QAEXXZ @0x002947A8 46B chain from 0x00294759.
// Thiscall no args; AsciiString at +0x494 via rowed rva00293275 then int at
// +0x498 via just-landed rva00294759. Evidence: caller 0x0039F269.
void Rva00294759::rva002947A8()
{
	((Object *)this)->rva00293275(m_494);
	rva00294759(m_498);
}
