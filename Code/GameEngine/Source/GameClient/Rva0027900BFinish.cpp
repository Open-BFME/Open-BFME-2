// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?rva0027900B@@YA_NPAD@Z @0x0027900B 105B: static (internal-linkage) helper,
// NOT a thiscall member. The sole call site 0x0027916A sets the object pointer
// in EAX (`mov eax,edi; call`), which MSVC only does for an internal-linkage
// function whose call sites it can see -- exactly the Lua `_currentpc`/`_ZNAME`
// shape in this tree. Modeled as a static free function taking the object byte
// pointer; an in-TU scaffold caller supplies the visible call site that makes
// the compiler pick the EAX convention.
//
// PlayerTemplateStore lookup: match +0x6C string via rowed StringBase compare
// (0x000069D6) against each template +0x18 then return the +0x1BC flag.
// Callees rowed getNthPlayerTemplate 0x001FD3C6, ThePlayerTemplateStore.

#include "ascii_string.h"

class PlayerTemplate
{
public:
	char m_pad[0x18];
	AsciiString m_name18;
	char m_pad2[0x1BC - 0x18 - 4];
	bool m_flag1BC;
};

class PlayerTemplateStore
{
public:
	const PlayerTemplate *getNthPlayerTemplate(int i) const;
private:
	char m_pad[0xC];
public:
	int m_minC;
	int m_max10;
};

extern PlayerTemplateStore *ThePlayerTemplateStore;

struct BaseWithString
{
	char m_pad[0x6C];
	AsciiString m_str6C;
};

// ?rva0027900B@@YA_NPAD@Z
static bool rva0027900B(char *self)
{
	BaseWithString *base = *(BaseWithString **)(self + 4);
	const StringBase<char> *needle = 0;
	if (base != 0)
	{
		needle = (const StringBase<char> *)&base->m_str6C;
		for (int i = 0; i < (ThePlayerTemplateStore->m_max10 - ThePlayerTemplateStore->m_minC) / 0x1DC; ++i)
		{
			const PlayerTemplate *pt = ThePlayerTemplateStore->getNthPlayerTemplate(i);
			if (pt == 0)
				continue;
			if (needle->compare(*(const StringBase<char> *)&pt->m_name18) == 0)
				return pt->m_flag1BC;
		}
	}
	return false;
}

// ?rva00279074@Rva00279074Host@@QAEXXZ @0x00279074 371B: the Drawable
// veterancy pass (switch 0x002796D9 case 2 on the Drawable, pinned under this
// host name). The real call site of the static helper above (0x0027916A,
// `mov eax,edi; call`), which replaces the former codegen scaffold caller.
// With a live object (Object::rva002931BA false) that has an experience
// tracker (+0x264) and passes TheWritableGlobalData's +0xEB8 filter the
// tracker's level (0x0039AC0C) must be valid in TheExperienceLevelSystem
// with rank above 1 and (when its required experience is at most 1) a valid
// next level. The icon pair comes from the helper above; a KindOf 0x2000
// object draws through its +0x250 module's slot 31 object (slot 70 else 68
// then Thing::getDrawable) and an object whose +0x274 rider has KindOf
// 0x2000 draws nothing; otherwise this drawable draws
// (Drawable::drawVeterancy 0x00277DB4 with the flag and the rank).
class Player;
class Object;

class Rva2225E0Filter
{
public:
	bool accepts(Object *obj, Player *player);
};

struct GlobalDataVeterancyView
{
	char m_pad[0xEB8];
	Rva2225E0Filter m_veterancyFilter; // +0xEB8
};
class GlobalData;
extern GlobalData *TheWritableGlobalData;

class ExperienceLevelNode;
class ExperienceLevelList;
class ExperienceLevelIterator
{
public:
	ExperienceLevelIterator() {}
	ExperienceLevelIterator(const ExperienceLevelIterator &that) : m_node(that.m_node) {}

	ExperienceLevelNode *m_node;
};

struct ExperienceLevelHandle
{
	ExperienceLevelHandle() {}
	ExperienceLevelHandle(const ExperienceLevelHandle &that) : m_list(that.m_list), m_iter(that.m_iter) {}

	ExperienceLevelList *m_list;
	ExperienceLevelIterator m_iter;
};

class ExperienceLevelStore
{
public:
	int GetLevelRank(ExperienceLevelHandle levelHandle) const;
	int GetRequiredExperience(ExperienceLevelHandle levelHandle) const;
	ExperienceLevelHandle GetNextLevel(ExperienceLevelHandle levelHandle) const;
	bool IsValid(ExperienceLevelHandle levelHandle) const;
};
class ExperienceLevelSystem;
extern ExperienceLevelSystem *TheExperienceLevelSystem;

class ExperienceTracker
{
public:
	ExperienceLevelHandle rva0039AC0C() const;
};

class Drawable;
class Thing
{
public:
	Drawable *getDrawable() const;
};

class Rva00279074Contained
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51();
	virtual void slot52(); virtual void slot53(); virtual void slot54(); virtual void slot55();
	virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
	virtual void slot60(); virtual void slot61(); virtual void slot62(); virtual void slot63();
	virtual void slot64(); virtual void slot65(); virtual void slot66(); virtual void slot67();
	virtual Thing *slot68(); // +0x110
	virtual void slot69();
	virtual Thing *slot70(); // +0x118
};

class Rva00279074Module
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30();
	virtual Rva00279074Contained *slot31(); // +0x7C
};

struct Rva00279074Template
{
	char m_pad[0x114];
	unsigned int m_kindOf114; // +0x114
};

class Object
{
public:
	bool rva002931BA();
	Rva00279074Module *getContain() const { return m_250; }
	const Rva00279074Template *getTemplate() const { return m_template; }

	void *m_vtbl;
	const Rva00279074Template *m_template; // +0x04
	char m_pad08[0x250 - 0x08];
	Rva00279074Module *m_250; // +0x250
	char m_pad254[0x264 - 0x254];
	ExperienceTracker *m_experience; // +0x264
	char m_pad268[0x274 - 0x268];
	Object *m_274; // +0x274
};

class Drawable
{
public:
	void drawVeterancy(bool flag, int level);
};

class Rva00279074Host
{
public:
	void rva00279074();

private:
	char m_pad[0xFC];
	Object *m_object; // +0xFC
};

void Rva00279074Host::rva00279074()
{
	Object *obj = m_object;
	if (obj == 0)
		return;
	if (obj->rva002931BA())
		return;
	if (obj->m_experience == 0)
		return;
	if (!reinterpret_cast<GlobalDataVeterancyView *>(TheWritableGlobalData)->m_veterancyFilter.accepts(obj, 0))
		return;

	ExperienceLevelHandle level = obj->m_experience->rva0039AC0C();
	if (!reinterpret_cast<ExperienceLevelStore *>(TheExperienceLevelSystem)->IsValid(level))
		return;
	int rank = reinterpret_cast<ExperienceLevelStore *>(TheExperienceLevelSystem)->GetLevelRank(level);
	if (rank <= 1)
		return;
	if (reinterpret_cast<ExperienceLevelStore *>(TheExperienceLevelSystem)->GetRequiredExperience(level) <= 1)
	{
		if (!reinterpret_cast<ExperienceLevelStore *>(TheExperienceLevelSystem)->IsValid(
				reinterpret_cast<ExperienceLevelStore *>(TheExperienceLevelSystem)->GetNextLevel(level)))
			return;
	}

	bool flag = rva0027900B((char *)this);
	Drawable *draw;
	if ((obj->getTemplate()->m_kindOf114 & 0x2000) && obj->getContain() != 0)
	{
		Rva00279074Contained *contained = obj->getContain()->slot31();
		if (contained == 0)
			return;
		Thing *thing = contained->slot70();
		if (thing == 0)
		{
			thing = contained->slot68();
			if (thing == 0)
				return;
		}
		draw = thing->getDrawable();
	}
	else
	{
		Object *rider = obj->m_274;
		if (rider != 0 && (rider->getTemplate()->m_kindOf114 & 0x2000))
			return;
		draw = reinterpret_cast<Drawable *>(this);
	}
	if (draw != 0)
		draw->drawVeterancy(flag, rank);
}
