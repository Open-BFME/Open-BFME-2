// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// Retail RVA 0x003C9311, 82 bytes.
// ?doUnitIdleForFramecount@ScriptActions@@IAEXABVAsciiString@@H_N@Z
// BFME1 donor reference/open-bfme-1/game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp doUnitIdleForFramecount
// BFME2 deltas: bool seconds param with factor at 0x00DBA4E4 selecting setSequentialTimer frames like doUnitGuardForFramecount sibling.
// Evidence: rowed getUnitNamed 0x003588E7 plus AsciiString pin, rowed aiIdle 0x001E8A38, rowed setSequentialTimer Object overload 0x00203FCF.
// TheScriptEngine at 0x00DFE16C. AIUpdateInterface at Object+0x258 with command at +0x20. Caller at 0x003CE271.
extern int BfmeLogicFramesPerSecond;

#include "ascii_string.h"

enum CommandSourceType { CMD_FROM_SCRIPT = 1 };

#include "../../../Include/GameLogic/Module/AIUpdate.h"

#include "../Object/object.h"

#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

class ScriptActions
{
protected:
	void doUnitIdleForFramecount(const AsciiString &unitName, int framecount, bool seconds);
};

void ScriptActions::doUnitIdleForFramecount(const AsciiString &unitName, int framecount, bool seconds)
{
	Object *object = TheScriptEngine->getUnitNamed(unitName);
	if (!object)
		return;
	AIUpdateInterface *ai = object->getAIUpdateInterface();
	if (!ai)
		return;
	ai->aiIdle(CMD_FROM_SCRIPT);
	if (seconds)
		TheScriptEngine->setSequentialTimer(object, framecount * BfmeLogicFramesPerSecond);
	else
		TheScriptEngine->setSequentialTimer(object, framecount);
}
