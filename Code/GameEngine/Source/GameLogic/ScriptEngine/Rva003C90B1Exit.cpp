// cl: -O1 -arch:SSE -G7 -DNDEBUG -MD -EHsc -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
//
// ?Rva003C90B1Exit@ScriptActions@@QAEXPAVParameter@@@Z @0x003C90B1 44B: ScriptActions member helper
// resolving a unit via rowed getUnitNamed 0x003588E7 then issuing rowed aiExit
// 0x0036F39B with null object and script source. Evidence: caller 0x003CC1F4,
// Object+0x258 AIUpdateInterface, command +0x20.
class Parameter;
class Object;
enum CommandSourceType { CMD_FROM_SCRIPT = 1 };

#include "../../../Include/GameLogic/Module/AIUpdate.h"

#include "../Object/object.h"

#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;


void ScriptActions::Rva003C90B1Exit(Parameter *param)
{
	Object *obj = TheScriptEngine->getUnitNamed(param);
	if (!obj)
		return;
	AIUpdateInterface *ai = obj->getAI();
	if (!ai)
		return;
	ai->aiExit(0, CMD_FROM_SCRIPT);
}
