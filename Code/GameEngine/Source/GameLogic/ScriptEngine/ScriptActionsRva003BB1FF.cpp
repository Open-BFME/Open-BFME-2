// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// ?Rva003BB1FFAttack@ScriptActions@@QAEXPAVParameter@@ABVAsciiString@@@Z, retail 0x003BB1FF, 52 bytes.
// Set AI attack priority info for named unit.
// Evidence: leaf lane; callees getUnitNamed getAttackInfo; caller 0x003CB30C.
class Parameter;
class AsciiString;
class AttackPriorityInfo;
#include "../../../Include/GameLogic/Module/AIUpdate.h"
#include "../Object/object.h"
#include "../../../Include/GameLogic/ScriptEngine.h"
extern class ScriptEngine *TheScriptEngine;
void ScriptActions::Rva003BB1FFAttack(Parameter *unit, const AsciiString &infoName)
{
	Object *obj = TheScriptEngine->getUnitNamed(unit);
	if (obj == 0)
		return;
	AIUpdateInterface *ai = obj->m_ai;
	if (ai == 0)
		return;
	ai->m_attackInfo = TheScriptEngine->getAttackInfo(infoName);
}
