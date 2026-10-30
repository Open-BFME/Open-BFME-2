// cl: -O1 -arch:SSE -G7 /I. /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
#include "Code/GameEngine/Include/GameLogic/ScriptActionsBFME2.h"
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?doNamedEnableCameraFading@ScriptActions@@IAEXPAVParameter@@PAX@Z @ 0x003BBD02 (55B).
// Free-function wrapper: looks up Object via TheScriptEngine getUnitNamed
// Parameter row 0x003588E7 then double getDrawable Thing row 0x005508E2
// null-guarded then Drawable walk rva00273686 row 0x00273686 with void arg.
// Layout from callers plus sibling doNamedEnableStealth; ret 8 stdcall with
// Parameter plus void. Global g_Va009FE16C used by 14 TUs.
class Parameter;
#include "../../../Include/GameClient/DrawableBFME2.h"
class Object : public Thing {
};
#include "../../../Include/GameLogic/ScriptEngine.h"
extern class ScriptEngine *TheScriptEngine;



void ScriptActions::doNamedEnableCameraFading(Parameter *parameter, bool arg)
{
    Object *obj = TheScriptEngine->getUnitNamed(parameter);
    if (!obj)
        return;
    if (!obj->getDrawable())
        return;
    obj->getDrawable()->rva00273686(arg);
}
