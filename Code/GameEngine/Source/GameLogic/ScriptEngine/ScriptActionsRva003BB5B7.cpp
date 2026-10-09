// cl: /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BB5B7Do@@YGXPAVParameter@@HPAURGBColor@@@Z @0x003BB5B7 103B: free stdcall Parameter+int+color to Drawable stores.
// Target evidence: ScriptEngine::getUnitNamed 0x003588E7 then Thing::getDrawable 0x005508E2 then v<=0 guard then g_Va00DBA4E4*v/g_00E02D9C then RGBColor::getAsInt 0x00004EA7 vs Object::getIndicatorColor 0x0028B026 then Drawable+0x168+0x16c ret 0xc; caller 0x003CBB2E.
class Parameter;
class Drawable
{
public:
	char m_pad[0x168];
	int m_168;
	int m_16c;
};
class Thing
{
public:
	Drawable *getDrawable() const;
};
struct RGBColor
{
	int getAsInt() const;
};
class Object
{
public:
	int getIndicatorColor() const;
};
class Team;
class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *);
	Team *getTeamNamed(AsciiString name, bool exact);
};
extern class ScriptEngine *TheScriptEngine;
extern int g_Va00DBA4E4;
extern int g_00E02D9C;
// One shared read of each legacy rate declaration; both flash actions use
// these inline accessors rather than repeating the address-derived spelling.
inline int LogicFrameRate() { return g_Va00DBA4E4; }
inline int DrawableFlashFramePeriod() { return g_00E02D9C; }
void __stdcall Rva003BB5B7Do(Parameter *p, int v, RGBColor *c)
{
	Object *o = TheScriptEngine->getUnitNamed(p);
	if (!o)
		return;
	Drawable *d = ((Thing *)o)->getDrawable();
	if (!d)
		return;
	if (v <= 0)
		return;
	int scaled = LogicFrameRate() * v / DrawableFlashFramePeriod();
	int color;
	if (c == 0)
		color = o->getIndicatorColor();
	else
		color = c->getAsInt();
	d->m_168 = scaled;
	d->m_16c = color;
}

// ZH ScriptActions::doTeamFlash supplies the whole algorithm, including the
// null member guard after the iterator predicate. Native 3BFF50/156B proves
// RET12 and the same two rate globals and Drawable fields as the single-unit
// sibling above. Global spellings are inherited address placeholders.
template<class OBJCLASS>
class DLINK_ITERATOR
{
private:
    OBJCLASS *m_cur;
    unsigned char m_targetAbiState[20];
public:
    void advance();
    bool done() const { return m_cur == 0; }
    OBJCLASS *cur() const { return m_cur; }
};
class Team
{
public:
    bool hasAnyObjects(bool ignoreBuildings);
    DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
};
void __stdcall Rva003BFF50Do(const AsciiString *teamName, int seconds, RGBColor *colorOverride)
{
    Team *team = TheScriptEngine->getTeamNamed(*teamName, false);
    if (team == 0 || !team->hasAnyObjects(false))
        return;
    DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList();
    while (!iter.done())
    {
        Object *nextObj = iter.cur();
        Object *obj = nextObj;
        if (!obj)
            break;
        iter.advance();
        Drawable *draw = reinterpret_cast<Thing *>(obj)->getDrawable();
        if (!draw)
            break;
        int frames = LogicFrameRate() * seconds;
        int count = frames / DrawableFlashFramePeriod();
        int flashy = colorOverride == 0 ? obj->getIndicatorColor() : colorOverride->getAsInt();
        draw->m_16c = flashy;
        draw->m_168 = count;
    }
}
