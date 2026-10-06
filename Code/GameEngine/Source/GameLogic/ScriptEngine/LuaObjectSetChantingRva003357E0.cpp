// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Isolated Lua chanting binding (113B): ObjectSetChanting 0x003357E0.
// Reference-guided port of Open-BFME-1's
// game/GameEngine/Source/GameLogic/ScriptEngine/LuaScriptBindingsLuaA.cpp
// ObjectSetChanting (donor revision 6583b3c1ff21db4a561285717028fdafc780b7db, donor flags plus /O1).
// TARGET FACTS (retail call-site decode in-lane, preserved from seat-5 r14):
// - registration at 0x33860F pushes 0x7357E0 + lua_pushcclosure 0x747640 +
//   literal VA 0xC0E5E8 'ObjectSetChanting' + lua_setglobal 0x747920.
// - body is Lua cdecl (lua_gettop cmp2/jl return-0 lane, return-1 lane).
// - provider is rowed 0x00291080 Object::rva00291080 (this seat, 55B exact)
//   reached via REL32 at 0x735845 decoding to VA 0x691080 (sole open callee).
// DONOR FACTS CARRIED ONLY: control shape + Lua cdecl return lanes +
// lookup/findObject sequences from BFME1 LuaScriptBindingsLuaA.cpp ObjectSetChanting.
// Nothing about +0x274/+0x115/0x35 provider internals, Range layouts,
// ObjectID spelling, or TheGameLogic resolution is donor-carried.
// INFERENCE (to verify by build): BFME2 enum ObjectID + Range-pointer casts
// preserve bytes per Enraged 0x3358D9 precedent (same 113B envelope).
// No virtuals, no invented implementations, no shared-header edits.

struct lua_State;
extern "C" int lua_gettop( lua_State *state );
extern "C" int lua_type( lua_State *state, int index );

struct Rva00990030Range;
unsigned Rva00990030Lookup( Rva00990030Range *range, int index );

struct Rva00990210Range;
unsigned Rva00990210Lookup( Rva00990210Range *range, int index );

class Object
{
public:
	void rva00291080( bool flag );
};

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class GameLogic
{
public:
	Object *findObjectByID( ObjectID id );
};

extern GameLogic *TheGameLogic;

// ?ObjectSetChanting@@YAHPAUlua_State@@@Z
// Retail 0x003357E0 113B. Identity proven by registration at 0x0033860F
// (push 0x7357E0 + lua_pushcclosure 0x747640 + literal 0xC0E5E8
// 'ObjectSetChanting' + lua_setglobal 0x747920); providers are all rowed
// (lua_gettop/lua_type/lookups/findObjectByID/rva00291080).
int ObjectSetChanting( lua_State *state )
{
	if( lua_gettop( state ) < 2 )
		return 0;
	unsigned id = Rva00990030Lookup( (Rva00990030Range *)state, 1 );
	if( !id && lua_type( state, 1 ) != 1 )
		return 0;
	Object *object = TheGameLogic->findObjectByID( (ObjectID)id );
	if( !object )
		return 0;
	bool flag = Rva00990210Lookup( (Rva00990210Range *)state, 2 ) != 0;
	object->rva00291080( flag );
	return 1;
}
