// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /arch:SSE
// InGameHeroSelectInterface.cpp -- InGameHeroSelectInterface::Impl members
// recovered from WorldBuilder leads (reverse/wb_name_leads.csv): WB's debug
// build names the function and asserts a valid hero id and template; retail
// supplies the bytes and skips missing heroes instead.
//
// Target evidence: the Impl reaches its hero list through the object at
// +0x10 (an STLport list at +0x10 there); each entry holds the hero's
// ObjectID (+0x00 of the payload) and its flash countdown (+0x08). The hero
// template's name is at ThingTemplate+0x64.
#include "ascii_string.h"

typedef int Int;

enum ObjectID {};

class ThingTemplate
{
public:
	unsigned char m_pad00[0x64];
	AsciiString m_name;				// +0x64
};

class Drawable;

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	Drawable *getDrawable() const;			// 0x005508E2

private:
	void *m_vtbl;
	const ThingTemplate *m_template;		// +0x04
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);		// 0x00049DC5
};

extern GameLogic *TheGameLogic;

// IsBuilderOnScreen's view of the tactical view (VA 0x00DFEA3C, a View*):
// the slot +0x120 screen test takes a world position and a 1.0 scale.
struct Coord3D;
typedef float Real;
typedef bool Bool;

class Drawable
{
public:
	const Coord3D *getPosition() const;		// 0x002763E6
};

class View
{
public:
#define HERO_VIEW_SLOT(n) virtual void slot##n();
	HERO_VIEW_SLOT(00) HERO_VIEW_SLOT(01) HERO_VIEW_SLOT(02) HERO_VIEW_SLOT(03)
	HERO_VIEW_SLOT(04) HERO_VIEW_SLOT(05) HERO_VIEW_SLOT(06) HERO_VIEW_SLOT(07)
	HERO_VIEW_SLOT(08) HERO_VIEW_SLOT(09) HERO_VIEW_SLOT(10) HERO_VIEW_SLOT(11)
	HERO_VIEW_SLOT(12) HERO_VIEW_SLOT(13) HERO_VIEW_SLOT(14) HERO_VIEW_SLOT(15)
	HERO_VIEW_SLOT(16) HERO_VIEW_SLOT(17) HERO_VIEW_SLOT(18) HERO_VIEW_SLOT(19)
	HERO_VIEW_SLOT(20) HERO_VIEW_SLOT(21) HERO_VIEW_SLOT(22) HERO_VIEW_SLOT(23)
	HERO_VIEW_SLOT(24) HERO_VIEW_SLOT(25) HERO_VIEW_SLOT(26) HERO_VIEW_SLOT(27)
	HERO_VIEW_SLOT(28) HERO_VIEW_SLOT(29) HERO_VIEW_SLOT(30) HERO_VIEW_SLOT(31)
	HERO_VIEW_SLOT(32) HERO_VIEW_SLOT(33) HERO_VIEW_SLOT(34) HERO_VIEW_SLOT(35)
	HERO_VIEW_SLOT(36) HERO_VIEW_SLOT(37) HERO_VIEW_SLOT(38) HERO_VIEW_SLOT(39)
	HERO_VIEW_SLOT(40) HERO_VIEW_SLOT(41) HERO_VIEW_SLOT(42) HERO_VIEW_SLOT(43)
	HERO_VIEW_SLOT(44) HERO_VIEW_SLOT(45) HERO_VIEW_SLOT(46) HERO_VIEW_SLOT(47)
	HERO_VIEW_SLOT(48) HERO_VIEW_SLOT(49) HERO_VIEW_SLOT(50) HERO_VIEW_SLOT(51)
	HERO_VIEW_SLOT(52) HERO_VIEW_SLOT(53) HERO_VIEW_SLOT(54) HERO_VIEW_SLOT(55)
	HERO_VIEW_SLOT(56) HERO_VIEW_SLOT(57) HERO_VIEW_SLOT(58) HERO_VIEW_SLOT(59)
	HERO_VIEW_SLOT(60) HERO_VIEW_SLOT(61) HERO_VIEW_SLOT(62) HERO_VIEW_SLOT(63)
	HERO_VIEW_SLOT(64) HERO_VIEW_SLOT(65) HERO_VIEW_SLOT(66) HERO_VIEW_SLOT(67)
	HERO_VIEW_SLOT(68) HERO_VIEW_SLOT(69) HERO_VIEW_SLOT(70) HERO_VIEW_SLOT(71)
#undef HERO_VIEW_SLOT
	virtual Bool isPointOnScreen(const Coord3D *pos, Real scale);	// +0x120, unnamed in WB
};

extern View *TheTacticalView;

struct HeroButtonInfo
{
	ObjectID m_heroID;				// +0x00
	Int m_unknown04;
	Int m_flashFrames;				// +0x08
};

// STLport list<HeroButtonInfo> view: the list holds its header node.
struct HeroButtonNode
{
	HeroButtonNode *m_next;
	HeroButtonNode *m_prev;
	HeroButtonInfo m_data;
};

struct HeroButtonList
{
	HeroButtonNode *begin() const { return m_header->m_next; }
	HeroButtonNode *end() const { return m_header; }

	HeroButtonNode *m_header;
};

struct HeroSelectData
{
	unsigned char m_pad00[0x10];
	HeroButtonList m_heroButtons;			// +0x10
};

class InGameHeroSelectInterface
{
public:
	class Impl
	{
	public:
		void FlashHeroButton(const AsciiString &templateName, Int frames);
		Bool IsBuilderOnScreen(const Object *builder);

	private:
		unsigned char m_pad00[0x10];
		HeroSelectData *m_data;			// +0x10
	};
};

// InGameHeroSelectInterface::Impl::FlashHeroButton, retail 0x00525E07:
// raise the flash countdown of every hero button whose hero has the given
// template name.
void InGameHeroSelectInterface::Impl::FlashHeroButton(const AsciiString &templateName, Int frames)
{
	HeroButtonList &list = m_data->m_heroButtons;
	for (HeroButtonNode *it = list.begin(); it != list.end(); it = it->m_next)
	{
		Object *hero = TheGameLogic->findObjectByID(it->m_data.m_heroID);
		if (hero == 0)
			continue;
		if (hero->getTemplate()->m_name.compare(templateName) != 0)
			continue;
		if (frames > it->m_data.m_flashFrames)
			it->m_data.m_flashFrames = frames;
	}
}

// InGameHeroSelectInterface::Impl::IsBuilderOnScreen, retail 0x00525040 (47
// bytes): WB asserts the builder and its drawable exist; the tactical view
// tests the drawable's position at scale 1.
Bool InGameHeroSelectInterface::Impl::IsBuilderOnScreen(const Object *builder)
{
	return TheTacticalView->isPointOnScreen(builder->getDrawable()->getPosition(), 1.0f);
}
