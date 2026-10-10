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

// DelayedLuaEventList: ctor 0x000B6D8B and virtual dtor 0x000B6DD2 (slot 0 of its
// vftable 0x007C9CF0 is the scalar deleting dtor 0x000B6E0C); the vptr is the +0 word.
// BfmeDelayedLuaEventList is only the parameter tag of the 0x003360D2 row.
struct BfmeDelayedLuaEventList;
struct DelayedLuaEventList
{
	DelayedLuaEventList();
	virtual ~DelayedLuaEventList();
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
	DelayedLuaEventList list;
	void *object = m_object;
	reinterpret_cast<BfmeObjectEventDispatch *>(TheLuaScriptEngine)->rva003360D2(2, object, (BfmeDelayedLuaEventList *)&list);
}
