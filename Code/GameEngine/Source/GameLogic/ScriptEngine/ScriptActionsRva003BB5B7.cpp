// stlport
// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD
#include "GameLogic/ScriptActionsBFME2.h"
#include "ascii_string.h"
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BB5B7Do@ScriptActions@@QAEXPAVParameter@@HPAURGBColor@@@Z @0x003BB5B7 103B: ScriptActions member Parameter+int+color to Drawable stores.
// Target evidence: ScriptEngine::getUnitNamed 0x003588E7 then Thing::getDrawable 0x005508E2 then v<=0 guard then BfmeLogicFramesPerSecond*v/g_00E02D9C then RGBColor::getAsInt 0x00004EA7 vs Object::getIndicatorColor 0x0028B026 then Drawable+0x168+0x16c ret 0xc; caller 0x003CBB2E.
class Parameter;
#include "../../../Include/GameClient/Drawable.h"
#include "../../Common/Thing/thing.h"
#include "../../../../Libraries/Include/Lib/RGBColor.h"
#include "../Object/object.h"
class Team;
#include "../../../Include/GameLogic/ScriptEngine.h"
extern class ScriptEngine *TheScriptEngine;
extern int BfmeLogicFramesPerSecond;
// Both flash actions divide by this unit's own Drawable.h copy of
// DRAWABLE_FRAMES_PER_FLASH: retail reads it at VA 0x00E02D9C (0x003BB5ED,
// 0x003BFFB7 idiv), the static this unit's .CRT$XCU entry 0x007AF85F builds, as
// Zero Hour's ScriptActions::doNamedFlash/doTeamFlash read theirs.
inline int LogicFrameRate() { return BfmeLogicFramesPerSecond; }
void ScriptActions::Rva003BB5B7Do(Parameter *p, int seconds, RGBColor *colorOverride)
{
	Object *o = TheScriptEngine->getUnitNamed(p);
	if (!o)
		return;
	Drawable *d = ((Thing *)o)->getDrawable();
	if (!d)
		return;
	if (seconds <= 0)
		return;
	int scaled = LogicFrameRate() * seconds / DRAWABLE_FRAMES_PER_FLASH;
	int color;
	if (colorOverride == 0)
		color = o->getIndicatorColor();
	else
		color = colorOverride->getAsInt();
	d->m_flashCount = scaled;
	d->m_flashColor = color;
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
#include "../../../Include/Common/TeamBFME2.h"
void ScriptActions::Rva003BFF50Do(const AsciiString *teamName, int seconds, RGBColor *colorOverride)
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
        int count = frames / DRAWABLE_FRAMES_PER_FLASH;
        int flashy = colorOverride == 0 ? obj->getIndicatorColor() : colorOverride->getAsInt();
        draw->m_flashColor = flashy;
        draw->m_flashCount = count;
    }
}

// Member ABI proved at each native executeAction3CA4BE call site: ECX=this.
// Canonical ScriptActions owner; address-derived verbs remain uncertain.
