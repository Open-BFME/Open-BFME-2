// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
//
// ?DispatchEvent@LuaScriptEngine@@QAEXPAHPAVObject@@PAX@Z
// retail 0x00334634..0x00334862 (556 bytes, ret 12).
// LuaScriptEngine::DispatchEvent: WorldBuilder's LuaScriptEngine.cpp
// (lines 586..663, va 0x00BFDB50) names it. It looks the event key up in the
// object's AI event table, finds the Lua global of that name and calls it with
// the object table and up to three event parameters, then lets the AI run its
// spies. Facts from retail: lua_State at +0x0C, call depth at +0xD4, the key
// the single-step flag compares with at +0xDC; the Object's AI at +0x258
// (event table at AI +0x220) and its flag byte at +0x438 (read through the
// Object's raw bytes, as the donor does: that is what keeps the AI in ECX).
// Body shape follows Open-BFME-1's Rva002E5A70LuaEventDispatch.cpp (donor
// revision 575ba2b04), re-laid onto BFME 2's offsets: this build adds the
// lua_State test, the string parameter kind, the Lua stack restore on the
// error path and the processSpies tail.
// Callee spellings follow their rows or pins: event-name lookup 0x0033280B /
// object-table push 0x00334003 (unrowed, address-named); g_00E01DC0 is the
// single-step Lua state. Event parameters are 24-byte records (float at +8,
// bool at +0xC, object id at +0x10, name at +0x14, kind tag at +0x18 with
// kinds 1 real / 2 bool / 3 object / 4 string, else end).

#include "ascii_string.h"

struct lua_State;
struct BfmeQ1039;
class Object;

extern "C" int lua_gettop(lua_State *L);
extern "C" void lua_getglobal(lua_State *L, const char *name);
extern "C" int lua_type(lua_State *L, int index);
extern "C" void lua_settop(lua_State *L, int index);
extern "C" void lua_call(lua_State *L, int arguments, int results);
extern "C" void lua_pushnumber(lua_State *L, double n);
extern "C" void lua_pushstring(lua_State *L, const char *s);

extern void bfmeGo1039E(BfmeQ1039 *q, int value);
void __cdecl bfmeLogMsg574(const char *message);

extern void *g_00E01DC0;	// the Lua state while single-stepping

#include "../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

class AIUpdateInterface
{
public:
	void processSpies(int key, void *argument2, void *argument3);
};

// The AI's event table (+0x220): key -> Lua function name.
class Rva0033280B
{
public:
	const AsciiString &rva0033280B(int key, bool *debugStep);
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
	void DispatchEvent(int *key, Object *object, void *parameters);
	void rva00334003(lua_State *state, Object *object);

private:
	unsigned char m_pad00[0x0c];
	lua_State *m_luaState;				// +0x0C
	unsigned char m_pad10[0xc4];
	int m_depth;						// +0xD4
	unsigned char m_padD8[4];
	int m_singleStepKey;				// +0xDC
};

void LuaScriptEngine::DispatchEvent(int *key, Object *object, void *parameters)
{
	if (m_luaState == 0)
		return;
	if (m_depth > 10)
		return;

	int top = lua_gettop(m_luaState);
	g_00E01DC0 = 0;

	char *objectBytes = (char *)object;
	void *eventSource = *(void **)(objectBytes + 0x258);
	if (eventSource == 0)
		return;

	if ((objectBytes[0x438] & 1) != 0) {
		int guardKey = *key;
		if (guardKey != m_singleStepKey)
			return;
	}

	Rva0033280B *table = *(Rva0033280B **)((char *)eventSource + 0x220);
	if (table == 0)
		return;

	int k = *key;
	bool debugStep;
	AsciiString name(table->rva0033280B(k, &debugStep));
	if (name.isEmpty())
		return;

	lua_getglobal(m_luaState, name.str());
	if (lua_type(m_luaState, -1) != 5)
	{
		AsciiString error;
		if (lua_type(m_luaState, -1) == 1)
			error = " is not defined.";
		else
			error = " is not a lua function.";
		lua_settop(m_luaState, top);
		return;
	}

	rva00334003(m_luaState, object);
	int count = 1;
	EventParameters *events = (EventParameters *)parameters;
	for (int i = 0; i < 3; ++i)
	{
		switch (events->m_event[i].m_kind)
		{
		case 1:
			lua_pushnumber(m_luaState, events->m_event[i].m_real);
			++count;
			break;
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
		case 4:
			lua_pushstring(m_luaState, events->m_event[i].m_string.str());
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
	--m_depth;

	if (g_00E01DC0 && m_depth == 0)
	{
		bfmeLogMsg574("Stepping out of LUA function - step disabled.\n");
		g_00E01DC0 = 0;
	}
	int k2 = *key;
	((AIUpdateInterface *)eventSource)->processSpies(k2, object, parameters);
}
