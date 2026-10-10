// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
//
// ?DispatchSpyEvent@LuaScriptEngine@@QAEXHPAX00@Z
// retail 0x00334860..0x00334A38 (472 bytes, ret 16).
// LuaScriptEngine::DispatchSpyEvent: the sibling of DispatchEvent (0x00334634)
// that spies on another object's event. Same event-name lookup in the AI's
// event table (+0x220 of the Object's AI at +0x258), Lua global call with two
// object tables and up to three typed event parameters, but no lua_State
// test, no single-step key guard (a set flag bit 0 on the Object, +0x438,
// makes it return), integer pushes for real and bool parameters, and the
// Lua stack restored after the call instead of a spy callback. Body shape
// follows DispatchEvent and Open-BFME-1's Rva002E5A70LuaEventDispatch donor
// (raw-byte Object access keeps the AI in ECX). Callees: 0x0033280B event
// table lookup and 0x00334003 object-table push, both pinned address names.

#include "ascii_string.h"

struct lua_State;
struct BfmeQ1039;
class Object;

extern "C" int lua_gettop(lua_State *L);
extern "C" void lua_getglobal(lua_State *L, const char *name);
extern "C" int lua_type(lua_State *L, int index);
extern "C" void lua_settop(lua_State *L, int index);
extern "C" void lua_call(lua_State *L, int arguments, int results);

extern void bfmeGo1039E(BfmeQ1039 *q, int value);
void __cdecl bfmeLogMsg574(const char *message);

extern void *g_00E01DC0;	// the Lua state while single-stepping

#include "../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

// The AI's event table (+0x220): key -> Lua function name.
class Rva0033280B
{
public:
	const AsciiString &find(int key, bool *debugStep);
};

struct EventData
{
	float m_real;			// +0x00
	bool m_boolean;		// +0x04
	ObjectID m_object;	// +0x08
	AsciiString m_string;	// +0x0C
	int m_kind;			// +0x10
	int m_pad14;
};

struct EventParameters
{
	int m_pad00[2];
	EventData m_event[3];	// +0x08
};

class LuaScriptEngine
{
public:
	void DispatchSpyEvent(int key, void *object, void *spy, void *parameters);
	void rva00334003(lua_State *state, Object *object);

private:
	unsigned char m_pad00[0x0c];
	lua_State *m_luaState;				// +0x0C
	unsigned char m_pad10[0xc4];
	int m_depth;						// +0xD4
};

void LuaScriptEngine::DispatchSpyEvent(int key, void *object, void *spy, void *parameters)
{
	if (m_depth > 10)
		return;

	int top = lua_gettop(m_luaState);
	g_00E01DC0 = 0;

	char *objectBytes = (char *)object;
	void *eventSource = *(void **)(objectBytes + 0x258);
	if (eventSource == 0)
		return;

	if ((objectBytes[0x438] & 1) != 0)
		return;

	Rva0033280B *table = *(Rva0033280B **)((char *)eventSource + 0x220);
	if (table == 0)
		return;

	bool debugStep;
	AsciiString name(table->find(key, &debugStep));
	if (name.isEmpty())
		return;

	lua_getglobal(m_luaState, name.str());
	if (lua_type(m_luaState, 1) != 5)
	{
		AsciiString error;
		if (lua_type(m_luaState, 1) == 1)
			error = " is not defined.";
		else
			error = " is not a lua function.";
		return;
	}

	rva00334003(m_luaState, (Object *)object);
	rva00334003(m_luaState, (Object *)spy);
	int count = 2;
	EventParameters *events = (EventParameters *)parameters;
	for (int i = 0; i < 3; ++i)
	{
		switch (events->m_event[i].m_kind)
		{
		case 1:
		{
			float real = events->m_event[i].m_real;
			bfmeGo1039E((BfmeQ1039 *)m_luaState, (int)real);
			++count;
			break;
		}
		case 2:
		{
			bool flag = events->m_event[i].m_boolean;
			bfmeGo1039E((BfmeQ1039 *)m_luaState, flag != 0);
			++count;
			break;
		}
		case 3:
			rva00334003(m_luaState, TheGameLogic->findObjectByID(events->m_event[i].m_object));
			++count;
			break;
		default:
			i = 3;
			break;
		}
	}

	if (debugStep)
		g_00E01DC0 = m_luaState;
	++m_depth;
	lua_call(m_luaState, count, 0);
	lua_settop(m_luaState, top);
	--m_depth;

	if (g_00E01DC0 && m_depth == 0)
	{
		bfmeLogMsg574("Stepping out of LUA function - step disabled.\n");
		g_00E01DC0 = 0;
	}
}
