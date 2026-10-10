// ?HordeBroadcastEventToMembers@LuaScriptEngine@@SAHPAUlua_State@@@Z
// partial score=0.92 date=2026-10-10
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/GameEngine/Source/Common
// stlport
//
// ?HordeBroadcastEventToMembers@LuaScriptEngine@@SAHPAUlua_State@@@Z, retail
// 0x00335A61 (295B). WorldBuilder's LuaScriptEngine.cpp (va 0x00C09440) names
// this Lua callback LuaScriptEngine::HordeBroadcastEventToMembers. Body:
// Open-BFME-1 GameLogic/ScriptEngine/HordeBroadcastEventToMembers.cpp (donor
// revision 575ba2b04), re-laid onto BFME 2's rowed callees: the object lookup
// without a lua_type fallback, the contain interface at Object+0x250 whose
// slot 31 (+0x7C) returns the horde interface, the delayed-event list ctor
// 0x000B6D8B / dtor 0x000B6DD2, the event lookup 0x00333918 and per-member
// dispatch 0x00334634 on the global at VA 0x00E01DBC, and the first record
// filled by 0x00331842 (Rva001BDA20) from Lua argument 3. Retail asks the
// horde interface (slot 67, +0x10C) to fill a list<int> whose values are
// Object pointers.

#include <list>

struct lua_State;
extern "C" const char *lua_tostring( lua_State *state, int index );
unsigned Rva00990030Lookup( lua_State *range, int index );

#include "GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

typedef unsigned NameKeyType;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey( const char *name );
};
extern NameKeyGenerator *TheNameKeyGenerator;

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

// Retail 0x00331842: fills a delayed-event record from a Lua argument.
class Rva001BDA20
{
public:
	void rva00331842( lua_State *state, int index );
};

class LuaScriptEngine;
extern LuaScriptEngine *TheLuaScriptEngine;

struct BfmeCallJ63
{
	void *invoke( void *event );
};

struct BfmeObjectEventDispatch
{
	void invoke( void *event, void *object, BfmeDelayedLuaEventList *eventList );
};

#define SLOT(N) virtual int slot##N() = 0

class HordeContainInterface
{
public:
	SLOT(00); SLOT(01); SLOT(02); SLOT(03); SLOT(04); SLOT(05); SLOT(06); SLOT(07);
	SLOT(08); SLOT(09); SLOT(10); SLOT(11); SLOT(12); SLOT(13); SLOT(14); SLOT(15);
	SLOT(16); SLOT(17); SLOT(18); SLOT(19); SLOT(20); SLOT(21); SLOT(22); SLOT(23);
	SLOT(24); SLOT(25); SLOT(26); SLOT(27); SLOT(28); SLOT(29); SLOT(30); SLOT(31);
	SLOT(32); SLOT(33); SLOT(34); SLOT(35); SLOT(36); SLOT(37); SLOT(38); SLOT(39);
	SLOT(40); SLOT(41); SLOT(42); SLOT(43); SLOT(44); SLOT(45); SLOT(46); SLOT(47);
	SLOT(48); SLOT(49); SLOT(50); SLOT(51); SLOT(52); SLOT(53); SLOT(54); SLOT(55);
	SLOT(56); SLOT(57); SLOT(58); SLOT(59); SLOT(60); SLOT(61); SLOT(62); SLOT(63);
	SLOT(64); SLOT(65); SLOT(66);
	virtual void getMemberIDs( _STL::list<int> *memberIDs ) = 0;
};

class ContainModuleInterface
{
public:
	SLOT(00); SLOT(01); SLOT(02); SLOT(03); SLOT(04); SLOT(05); SLOT(06); SLOT(07);
	SLOT(08); SLOT(09); SLOT(10); SLOT(11); SLOT(12); SLOT(13); SLOT(14); SLOT(15);
	SLOT(16); SLOT(17); SLOT(18); SLOT(19); SLOT(20); SLOT(21); SLOT(22); SLOT(23);
	SLOT(24); SLOT(25); SLOT(26); SLOT(27); SLOT(28); SLOT(29); SLOT(30);
	virtual HordeContainInterface *getHordeContainInterface() = 0;
};

#undef SLOT

class Object
{
public:
	// Keep the native +0x250 load inline; omit the competing legacy getter.
	__declspec(dllimport) __forceinline ContainModuleInterface *getContain() const { return m_contain; }
	unsigned char m_unreconstructed00[0x250];
	ContainModuleInterface *m_contain;
};

// A list<int> node as the horde interface fills it: values are Object pointers.
struct MemberNode
{
	MemberNode *m_next;
	MemberNode *m_previous;
	void *m_value;
};

class LuaScriptEngine
{
public:
	static int HordeBroadcastEventToMembers( lua_State *state );
};

int LuaScriptEngine::HordeBroadcastEventToMembers( lua_State *state )
{
	unsigned objectID = Rva00990030Lookup( state, 1 );
	if( !objectID )
		return 0;

	Object *object = TheGameLogic->findObjectByID( (ObjectID)objectID );
	if( !object )
		return 0;
	ContainModuleInterface *contain = object->getContain();
	if( !contain )
		return 0;

	HordeContainInterface *horde = contain->getHordeContainInterface();
	if( horde )
	{
		BfmeDelayedLuaEventList eventList;
		const char *eventName = lua_tostring( state, 2 );
		if( !eventName )
			return 0;
		void *eventData = reinterpret_cast<BfmeCallJ63 *>( TheLuaScriptEngine )->invoke( (void *)TheNameKeyGenerator->nameToKey( eventName ) );
		if( eventData )
		{
			reinterpret_cast<Rva001BDA20 *>( &eventList.m_events[0] )->rva00331842( state, 3 );
			_STL::list<int> memberIDs;
			horde->getMemberIDs( &memberIDs );
			MemberNode *sentinel = *reinterpret_cast<MemberNode **>( &memberIDs );
			for( MemberNode *node = sentinel->m_next; node != sentinel; node = node->m_next )
			{
				void *member = node->m_value;
				reinterpret_cast<BfmeObjectEventDispatch *>( TheLuaScriptEngine )->invoke( eventData, member, &eventList );
			}
		}
	}

	return 0;
}
