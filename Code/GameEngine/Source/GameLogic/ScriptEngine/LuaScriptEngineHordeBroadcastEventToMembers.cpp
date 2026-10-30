// cl: /O1 /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfmelist
// stlport
//
// ?HordeBroadcastEventToMembers@LuaScriptEngine@@SAHPAUlua_State@@@Z, retail
// 0x00335A61 (295 bytes). Lua callback: resolves the object (argument 1), its
// +0x250 interface's horde interface (slot 31), looks the event named by
// argument 2 up in TheLuaScriptEngine and sends it to every member the horde
// lists (slot 67 fills a list), with the delayed-event argument of argument 3.
// Registered by 0x003383F1; shape after the ObjectBroadcastEventTo* callbacks.
#include <list>
#include "../../Common/GameLogicObjectLookupView.h"
#include "../../../Include/GameLogic/ContainmentListView.h"
namespace _STL {
template<> _List_base<Rva0036ADF9Element,allocator<Rva0036ADF9Element> >::_List_base(const allocator<Rva0036ADF9Element>&);
template<> _List_base<Rva0036ADF9Element,allocator<Rva0036ADF9Element> >::~_List_base();
}

struct Rva00990030Range;
unsigned Rva00990030Lookup(Rva00990030Range *range, int index);	// 0x00747190

struct lua_State;
extern "C" const char *lua_tostring(lua_State *state, int index);
extern GameLogic *TheGameLogic;

enum NameKeyType { NAMEKEY_INVALID = 0 };

class AsciiString;
class NameKeyGenerator
{
public:
	NameKeyType nameToKey( const char *name );
	NameKeyType nameToKey(const AsciiString &name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class Rva001BDA20
{
public:
	void rva00331842(lua_State *state, int index);	// 0x00331842
};

struct BfmeDispatchDelayedLuaEvent
{
	unsigned char m_data[0x18];
};

struct DelayedLuaEventList
{
	DelayedLuaEventList();	// 0x000B6D8B
	virtual ~DelayedLuaEventList();	// 0x000B6DD2
	BfmeDispatchDelayedLuaEvent m_events[3];
};

class Rva00332E60
{
public:
	void *rva00333918( int key );
	void *rva0033321B(int key); // 0x0033321B
};

class LuaScriptEngine
{
public:
	static int HordeBroadcastEventToMembers(lua_State *state);
	void DispatchEvent(int *event, Object *obj, void *args);	// 0x00334634
};
extern LuaScriptEngine *TheLuaScriptEngine;

class HordeContainInterface
{
public:
#define HORDE_SLOT(n) virtual void hordeSlot##n();
	HORDE_SLOT(0) HORDE_SLOT(1) HORDE_SLOT(2) HORDE_SLOT(3) HORDE_SLOT(4)
	HORDE_SLOT(5) HORDE_SLOT(6) HORDE_SLOT(7) HORDE_SLOT(8) HORDE_SLOT(9)
	HORDE_SLOT(10) HORDE_SLOT(11) HORDE_SLOT(12) HORDE_SLOT(13) HORDE_SLOT(14)
	HORDE_SLOT(15) HORDE_SLOT(16) HORDE_SLOT(17) HORDE_SLOT(18) HORDE_SLOT(19)
	HORDE_SLOT(20) HORDE_SLOT(21) HORDE_SLOT(22) HORDE_SLOT(23) HORDE_SLOT(24)
	HORDE_SLOT(25) HORDE_SLOT(26) HORDE_SLOT(27) HORDE_SLOT(28) HORDE_SLOT(29)
	HORDE_SLOT(30) HORDE_SLOT(31) HORDE_SLOT(32) HORDE_SLOT(33) HORDE_SLOT(34)
	HORDE_SLOT(35) HORDE_SLOT(36) HORDE_SLOT(37) HORDE_SLOT(38) HORDE_SLOT(39)
	HORDE_SLOT(40) HORDE_SLOT(41) HORDE_SLOT(42) HORDE_SLOT(43) HORDE_SLOT(44)
	HORDE_SLOT(45) HORDE_SLOT(46) HORDE_SLOT(47) HORDE_SLOT(48) HORDE_SLOT(49)
	HORDE_SLOT(50) HORDE_SLOT(51) HORDE_SLOT(52) HORDE_SLOT(53) HORDE_SLOT(54)
	HORDE_SLOT(55) HORDE_SLOT(56) HORDE_SLOT(57) HORDE_SLOT(58) HORDE_SLOT(59)
	HORDE_SLOT(60) HORDE_SLOT(61) HORDE_SLOT(62) HORDE_SLOT(63) HORDE_SLOT(64)
	HORDE_SLOT(65) HORDE_SLOT(66)
#undef HORDE_SLOT
	virtual void getMemberIDs(ContainmentList *members);	// slot 67 (+0x10C)
};

class ContainModuleInterface
{
public:
#define CONTAIN_SLOT(n) virtual void containSlot##n();
	CONTAIN_SLOT(0) CONTAIN_SLOT(1) CONTAIN_SLOT(2) CONTAIN_SLOT(3) CONTAIN_SLOT(4)
	CONTAIN_SLOT(5) CONTAIN_SLOT(6) CONTAIN_SLOT(7) CONTAIN_SLOT(8) CONTAIN_SLOT(9)
	CONTAIN_SLOT(10) CONTAIN_SLOT(11) CONTAIN_SLOT(12) CONTAIN_SLOT(13) CONTAIN_SLOT(14)
	CONTAIN_SLOT(15) CONTAIN_SLOT(16) CONTAIN_SLOT(17) CONTAIN_SLOT(18) CONTAIN_SLOT(19)
	CONTAIN_SLOT(20) CONTAIN_SLOT(21) CONTAIN_SLOT(22) CONTAIN_SLOT(23) CONTAIN_SLOT(24)
	CONTAIN_SLOT(25) CONTAIN_SLOT(26) CONTAIN_SLOT(27) CONTAIN_SLOT(28) CONTAIN_SLOT(29)
	CONTAIN_SLOT(30)
#undef CONTAIN_SLOT
	virtual HordeContainInterface *getHordeContainInterface();	// slot 31 (+0x7C)
};

class Object
{
public:
	// Keep the native +0x250 load inline; omit the competing legacy getter.
	__declspec(dllimport) __forceinline ContainModuleInterface *getContain() const { return m_contain; }
private:
	unsigned char m_pad000[0x250];
	ContainModuleInterface *m_contain;	// +0x250
};

int LuaScriptEngine::HordeBroadcastEventToMembers(lua_State *state)
{
	unsigned objectID = Rva00990030Lookup((Rva00990030Range *)state, 1);
	if (!objectID)
		return 0;
	Object *object = TheGameLogic->findObjectByID((ObjectID)objectID);
	if (!object)
		return 0;
	ContainModuleInterface *contain = object->getContain();
	if (!contain)
		return 0;
	HordeContainInterface *horde = contain->getHordeContainInterface();
	if (!horde)
		return 0;

	DelayedLuaEventList eventList;
	const char *eventName = lua_tostring(state, 2);
	if (!eventName)
		return 0;
	void *event = reinterpret_cast<Rva00332E60 *>(TheLuaScriptEngine)->rva00333918(TheNameKeyGenerator->nameToKey(eventName));
	if (!event)
		return 0;
	reinterpret_cast<Rva001BDA20 *>(&eventList.m_events[0])->rva00331842(state, 3);
	ContainmentList members;
	horde->getMemberIDs(&members);
	ContainmentList::iterator end = members.end();
	// Compare the public node identities directly, preserving the inlined walk
	// without emitting this TU's non-retail iterator-comparison COMDAT.
	for (ContainmentList::iterator it = members.begin(); it._M_node != end._M_node; ++it) {
		Object *member = (Object *)containmentFirstWord(*it);
		TheLuaScriptEngine->DispatchEvent((int *)event, member, &eventList);
	}
	return 0;
}
