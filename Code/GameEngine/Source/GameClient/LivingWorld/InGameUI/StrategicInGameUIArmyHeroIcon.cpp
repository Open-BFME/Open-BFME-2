// cl: /Ireference/shims/bfme2_ascii /O1 /Oy- /DNDEBUG /MD /EHsc
//
// StrategicInGameUI::ArmyHeroIcon (WorldBuilder
// StrategicInGameUIArmyHeroIcon.cpp names DoUpdate; the name is not
// confirmed by a retail string). Target facts for 0x005F42FF: an override
// reached through the virtual base at +0x14 (this - 0x14 is the icon, whose
// vbtable +4 locates the base whose rowed update 0x005F41AF it runs first);
// the icon's movie clip is at +0x0C and the hero record at +0x08. With a
// clip it replays the hero's +0xB8 flag (0x005FC70A) and +0xC4 byte
// (0x005FC71E); while the clip reports 0x005FC73B and the hero's template
// name (+0x04) is set and found by TheThingFactory, TheMouse shows the
// template's +0x5C4 tooltip (0x005F027D, WorldBuilder
// StrategicInGameUI::GetTooltipText) with no colour and full alpha.
// Member and base names follow WorldBuilder and the callees (inference).
#include "ascii_string.h"
#include "unicode_string.h"

// The clip's rowed setters and query (address-named views).
class Rva005FC70A
{
public:
	void rva005FC70A(unsigned char flag);
};
class Rva005FC71E
{
public:
	void rva005FC71E(unsigned char value);
};
class Rva005FC73BPtrChaseField
{
public:
	bool get() const;
};

class ArmyHeroIconMovieClip;

struct Rva005F42FFHero
{
	char m_pad00[0x04];
	AsciiString m_templateName; // +0x04
	char m_pad08[0xB8 - 0x08];
	int m_flagB8; // +0xB8
	char m_padBC[0xC4 - 0xBC];
	unsigned char m_byteC4; // +0xC4
};

struct Rva005F42FFTemplate
{
	char m_pad[0x5C4];
	int m_tooltip; // +0x5C4
};

class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *name);
};
class ThingFactory;
extern ThingFactory *TheThingFactory; // findTemplate viewed as the rowed 0x002D06CA

struct RGBColor;
class Mouse
{
public:
	void rva001EEA6D(UnicodeString text, int a, const RGBColor *color, float alpha);
};
extern Mouse *TheMouse;

namespace StrategicInGameUI {
UnicodeString __cdecl GetTooltipText(int id); // 0x005F027D (pinned)
}

// The virtual base: its update 0x005F41AF (rowed, address-named).
class Rva005F41AF
{
public:
	virtual void DoUpdate();
	void rva005F41AF();
};

namespace StrategicInGameUI {
class ArmyHeroIcon : public virtual Rva005F41AF
{
public:
	virtual void DoUpdate();

private:
	int m_04; // +0x04
	Rva005F42FFHero *m_hero; // +0x08
	ArmyHeroIconMovieClip *m_clip; // +0x0C
	int m_10; // +0x10
};
}

void StrategicInGameUI::ArmyHeroIcon::DoUpdate()
{
	Rva005F41AF::rva005F41AF();
	if (!m_clip)
		return;
	((Rva005FC70A *)m_clip)->rva005FC70A(m_hero->m_flagB8 != 0);
	unsigned char value = m_hero->m_byteC4;
	((Rva005FC71E *)m_clip)->rva005FC71E(value);
	if (!((Rva005FC73BPtrChaseField *)m_clip)->get())
		return;
	const AsciiString *name = &m_hero->m_templateName;
	if (((const StringBase<char> *)name)->isEmpty())
		return;
	Rva005F42FFTemplate *tmpl = (Rva005F42FFTemplate *)((Rva002D06CA *)TheThingFactory)->rva002D06CA(name);
	if (!tmpl)
		return;
	int tooltip = tmpl->m_tooltip;
	TheMouse->rva001EEA6D(StrategicInGameUI::GetTooltipText(tooltip), -1, 0, 1.0f);
}
