// cl: /DNDEBUG /MD /EHsc
// ?rva003360D2@BfmeObjectEventDispatch@@QAEXHPAXPAUBfmeDelayedLuaEventList@@@Z retail 0x003360D2 25B
// Forwards the event entry at +0x14 indexed by int (LuaScriptEngine's field14 table) to
// LuaScriptEngine::DispatchEvent 0x00334634 (rowed; same engine object) with object and event list.
// Evidence: same this as sibling rva00335FE1 dispatch loop; caller 0x00268AAA passes (2, [this+8], &DelayedLuaEventList).
// The dispatch 0x00334634 is the LuaScriptEngine::DispatchEvent row (this unit runs on the same engine).
class Object;
#include "../../../Include/GameLogic/LuaScriptEngine.h"
#include "../../../Include/GameLogic/Module/BfmeObjectEventDispatch.h"

void BfmeObjectEventDispatch::rva003360D2(int index, void *object, BfmeDelayedLuaEventList *eventList)
{
	LuaScriptEngine *engine = (LuaScriptEngine *)this;
	engine->DispatchEvent(&engine->field14[index].field00, (Object *)object, eventList);
}
