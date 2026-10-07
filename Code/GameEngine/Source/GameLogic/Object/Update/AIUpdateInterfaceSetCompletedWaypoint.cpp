// cl: /DNDEBUG /MD /EHsc
// ?setCompletedWaypoint@AIUpdateInterface@@QAEXPBVWaypoint@@@Z retail 0x00268AAA 85B
// Stores the completed waypoint at +0x13C then forwards event 2 with object at +0x08
// through the global dispatch at VA 0x00E01DBC via rowed rva003360D2 with a stack
// BfmeDelayedLuaEventList. Evidence: pin name gives class and signature; callers
// in AIFollowWaypointPathExactState::onExit and AIWander/AIPanic updates; same
// BfmeDelayedLuaEventList pin pattern as sibling rva00335FE1; chain from 0x003360D2.
class Waypoint;

struct BfmeDelayedLuaEvent
{
	unsigned char m_data[0x18];
};

struct BfmeDelayedLuaEventList
{
	BfmeDelayedLuaEventList();
	~BfmeDelayedLuaEventList();
	void *m_vtable;
	BfmeDelayedLuaEvent m_events[3];
};

class BfmeObjectEventDispatch
{
public:
	void rva003360D2(int index, void *object, BfmeDelayedLuaEventList *eventList);
};

class LuaScriptEngine;
extern LuaScriptEngine *TheLuaScriptEngine;

class AIUpdateInterface
{
public:
	void setCompletedWaypoint(const Waypoint *wp);
private:
	char m_pad0[8];
	void *m_object;
	char m_pad1[0x13C - 0x0C];
	const Waypoint *m_completed;
};

void AIUpdateInterface::setCompletedWaypoint(const Waypoint *wp)
{
	m_completed = wp;
	BfmeDelayedLuaEventList list;
	void *object = m_object;
	reinterpret_cast<BfmeObjectEventDispatch *>(TheLuaScriptEngine)->rva003360D2(2, object, &list);
}
