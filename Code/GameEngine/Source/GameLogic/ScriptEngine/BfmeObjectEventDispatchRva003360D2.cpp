// cl: /DNDEBUG /MD /EHsc
// ?rva003360D2@BfmeObjectEventDispatch@@QAEXHPAXPAUBfmeDelayedLuaEventList@@@Z retail 0x003360D2 25B
// Forwards slot at +0x14 indexed by int to LuaScriptEngine::DispatchEvent 0x00334634 (rowed;
// same engine object) with object and event list.
// Evidence: same this as sibling rva00335FE1 dispatch loop; caller 0x00268AAA passes (2, [this+8], &DelayedLuaEventList).
struct BfmeDelayedLuaEventList;
// The dispatch 0x00334634 is the LuaScriptEngine::DispatchEvent row (this unit runs on the same engine).
class Object;
class LuaScriptEngine
{
public:
	void DispatchEvent(int *event, Object *object, void *eventList);
};


struct BfmeEventSlot8
{
	void *a;
	void *b;
};

class BfmeObjectEventDispatch
{
public:
	void rva003360D2(int index, void *object, BfmeDelayedLuaEventList *eventList);
private:
	char m_pad0[0x14];
	BfmeEventSlot8 m_slots[1];
};

void BfmeObjectEventDispatch::rva003360D2(int index, void *object, BfmeDelayedLuaEventList *eventList)
{
	((LuaScriptEngine *)this)->DispatchEvent((int *)&m_slots[index], (Object *)object, eventList);
}
