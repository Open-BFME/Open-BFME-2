// cl: /DNDEBUG /MD /EHsc
// ?rva003360D2@BfmeObjectEventDispatch@@QAEXHPAXPAUBfmeDelayedLuaEventList@@@Z retail 0x003360D2 25B
// Forwards slot at +0x14 indexed by int to rowed invoke pin 0x00334634 with object and event list.
// Evidence: same this as sibling rva00335FE1 dispatch loop; caller 0x00268AAA passes (2, [this+8], &DelayedLuaEventList).
struct BfmeDelayedLuaEventList;

struct BfmeEventSlot8
{
	void *a;
	void *b;
};

class BfmeObjectEventDispatch
{
public:
	void invoke(void *event, void *object, BfmeDelayedLuaEventList *eventList);
	void rva003360D2(int index, void *object, BfmeDelayedLuaEventList *eventList);
private:
	char m_pad0[0x14];
	BfmeEventSlot8 m_slots[1];
};

void BfmeObjectEventDispatch::rva003360D2(int index, void *object, BfmeDelayedLuaEventList *eventList)
{
	invoke(&m_slots[index], object, eventList);
}
