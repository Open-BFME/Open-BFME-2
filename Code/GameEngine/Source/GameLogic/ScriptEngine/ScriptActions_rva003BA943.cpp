// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ScriptActions::rva003BA943, retail 0x003BA943 (44B): the unit resolved
// from its parameter by the rowed getUnitNamed hands the flag to its
// drawable (pinned Object::getDrawable 0x005508E2) through the Drawable
// method 0x002785FB (stores the flag at +0x448; pinned from this call).
#include "../../../Include/GameClient/Drawable.h"

#include "../Object/object.h"

class Parameter;

#include "../../../Include/GameLogic/ScriptEngine.h"
extern class ScriptEngine *TheScriptEngine;

class ScriptActions
{
protected:
    void rva003BA943(Parameter *pUnit, bool flag);
};

void ScriptActions::rva003BA943(Parameter *pUnit, bool flag)
{
    Object *obj = TheScriptEngine->getUnitNamed(pUnit);
    if (!obj)
        return;
    Drawable *draw = obj->getDrawable();
    if (!draw)
        return;
    draw->rva002785FB(flag);
}

// BFME 1 donor ba7ddda7: game/GameEngine/Source/Common/BfmeHelper760.cpp
// guides the team-color/upgrade refresh sequence. Target 3BA83F..3BA89A proves
// a complete 91-byte cdecl body, integer return 1, direct drawable getter,
// GlobalData time-of-day at 134 and Drawable vcall 34. The existing void pin
// was inferred only from a caller that discards the result; corrected here.
// Radar callee 2D7FAE is independently rowed under its opaque owner name;
// no stronger original method identity is claimed. Slot 34 remains unnamed.
#include "../../../Include/Common/Rva002D7FAEOwner.h"
class Radar;
extern Radar *TheRadar;
#include "../../../Include/Common/GlobalData.h"
extern GlobalData *TheWritableGlobalData;
int __cdecl rva003BA83F(void *value,int unused) {
if(value) {
Object *object=(Object*)value;
((Rva002D7FAEOwner*)TheRadar)->rva002D7FAE(object);
object->updateUpgradeModules();
Drawable *drawable=object->getDrawable();
if(drawable) {
if(TheWritableGlobalData->m_timeOfDay==4)
 drawable->setIndicatorColor(object->getNightIndicatorColor());
else drawable->setIndicatorColor(object->getIndicatorColor());
drawable->rva00271095();
}
}
return 1;
}
