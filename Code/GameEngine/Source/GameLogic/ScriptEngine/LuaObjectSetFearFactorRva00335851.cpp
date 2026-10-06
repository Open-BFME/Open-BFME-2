// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Isolated Lua FearFactor binding (136B): ObjectSetFearFactor 0x00335851.
// TARGET FACTS (retail decode in-lane this seat):
// - registration at 0x33862A pushes 0x735851 + lua_pushcclosure 0x747640 +
//   literal VA 0xC0E5D4 'ObjectSetFearFactor' + lua_setglobal 0x747920.
// - body is Lua cdecl (lua_gettop cmp2/jl return-0 lane, return-1 lane via xor+inc).
// - calls decode to rowed VAs: lua_gettop 0xB46F30, Lookup 0xB47190,
//   lua_type 0xB470A0, findObjectByID 0x449DC5, lua_tonumber 0xB47320,
//   __ftol2 0xA29228. All providers rowed verbatim (no pins).
// - float field at object+0x1AC via cvttss2si/cmp/mov/lea-jg/cvtsi2ss/movss
//   max-int-then-float shape (retail F30F2C08 394DFC 894DF8 8D4DFC 7F03 8D4DF8
//   F30F2A01 F30F1100 at body+0x67..0x7D).
// DONOR FACTS CARRIED ONLY: none for FearFactor (BFME1 LuaA has no FearFactor;
// sibling /O1+/arch:SSE Lua binding shapes only). Offsets/ABI are target retail.
// INFERENCE (to verify by build): max via const-int-reference ternary preserves
// the retail lea/jg address-select shape per docs/matching.md reference-ternary
// pattern; (int)lua_tonumber + (int)*factor + (float)picked give the SSE converts.
// No private AsciiString, no raw aliases, no shared-header edits.

struct lua_State;
extern "C" int lua_gettop( lua_State *state );
extern "C" int lua_type( lua_State *state, int index );
extern "C" double lua_tonumber( lua_State *state, int index );

struct Rva00990030Range;
unsigned Rva00990030Lookup( Rva00990030Range *range, int index );

class Object
{
public:
	void *m_unreconstructed00;
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

// ?ObjectSetFearFactor@@YAHPAUlua_State@@@Z
// Retail 0x00335851 136B. Identity proven by registration at 0x0033862A
// (push 0x735851 + lua_pushcclosure 0x747640 + literal 0xC0E5D4
// 'ObjectSetFearFactor' + lua_setglobal 0x747920).
int ObjectSetFearFactor( lua_State *state )
{
	if( lua_gettop( state ) < 2 )
		return 0;
	unsigned id = Rva00990030Lookup( (Rva00990030Range *)state, 1 );
	if( !id && lua_type( state, 1 ) != 1 )
		return 0;
	Object *object = TheGameLogic->findObjectByID( (ObjectID)id );
	if( !object )
		return 0;
	int value = (int)lua_tonumber( state, 2 );
	float *factor = (float *)( (char *)object + 0x1ac );
	int cur = (int)*factor;
	const int &picked = value > cur ? value : cur;
	*factor = (float)picked;
	return 1;
}
