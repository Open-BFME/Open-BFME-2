// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// ?Rva003BB1FFAttack@ScriptActions@@QAEXPAVParameter@@ABVAsciiString@@@Z, retail 0x003BB1FF, 52 bytes.
// Set AI attack priority info for named unit.
// Evidence: leaf lane; callees getUnitNamed getAttackInfo; caller 0x003CB30C.
class Parameter;
class AsciiString;
class AttackPriorityInfo;
class AIUpdateInterface
{
public:
	char m_pad00[0x70];
	const AttackPriorityInfo *m_info70;
};
class Object
{
public:
	char m_pad00[0x258];
	AIUpdateInterface *m_ai258;
};
#include "../../../Include/GameLogic/ScriptEngine.h"
extern class ScriptEngine *TheScriptEngine;
void ScriptActions::Rva003BB1FFAttack(Parameter *unit, const AsciiString &infoName)
{
	Object *obj = TheScriptEngine->getUnitNamed(unit);
	if (obj == 0)
		return;
	AIUpdateInterface *ai = obj->m_ai258;
	if (ai == 0)
		return;
	ai->m_info70 = TheScriptEngine->getAttackInfo(infoName);
}
