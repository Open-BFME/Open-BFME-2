// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2 -Ireference/open-bfme-1/game/GameEngine/Source/Common /Ireference/shims/bfmealloc /Ireference/shims/bfmelist -Ireference/open-bfme-1/game/GameEngine/Source/GameLogic/ScriptEngine
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
class Object;

extern "C" int lua_gettop(lua_State *L);
extern "C" void lua_getglobal(lua_State *L, const char *name);
extern "C" int lua_type(lua_State *L, int index);
extern "C" void lua_settop(lua_State *L, int index);
extern "C" void lua_call(lua_State *L, int arguments, int results);

extern "C" void __cdecl bfmeGo1039E(lua_State *L, int b);
void __cdecl bfmeLogMsg574(const char *message);

// Shared with the console provider at retail VA 0x00E01DC0.
extern void *g_activeObj12F0610;	// the Lua state while single-stepping

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

// +0x0C
typedef unsigned char Bool;
#include <stdlib.h>
#include "subsystem_interface.h"
struct lua_State;
class Object;
class BfmeLexEAN;
class XmlNameSlotList;
struct LuaDrawableLink;
struct Rva003378D0
{
	~Rva003378D0();
	char m_pad[12];
};

template <class T> struct Rva00337AA8Buf
{
	void *m_ptr;
	~Rva00337AA8Buf()
	{
		if (m_ptr != 0)
			free(m_ptr);
	}
};
class LuaScriptEngine : public SubsystemInterface
{
public:
	LuaScriptEngine();
	virtual ~LuaScriptEngine();
 virtual void init();
 virtual void reset();
 virtual void update() {}
 virtual void slot14() {}
 virtual const char *GetSnapshotName() const; virtual void DoXfer(Xfer *);

 void ExecuteChunk(char *buff, int size, const AsciiString &chunk);
 void LoadScripts(const char *filename);
 void DispatchEvent(int *key, Object *object, void *parameters);
 void DispatchSpyEvent(int key, void *object, void *spy, void *parameters);
 void PushObjectTable(lua_State *state, Object *object);
 static int ObjectDescription(lua_State *state);
 static int ObjectModifyUpgrade(lua_State *state, bool grant);
 static int HordeBroadcastEventToMembers(lua_State *state);
 void ProcessEventsElement(BfmeLexEAN *parser);
 void ProcessInternalEvent(XmlNameSlotList *xml);
 void rva002E9AA0ParseObjectStatusEvent(BfmeLexEAN *parser);
 void ProcessScriptedEvent(XmlNameSlotList *xml);
 void rva002E9680ParseModelConditionEvent(BfmeLexEAN *parser);
 void ProcessSageElement(BfmeLexEAN *parser);
 void ProcessEventList(BfmeLexEAN *parser);
 void LoadXML(const char *filename, bool keepOpen);
 void rva003387DC(const AsciiString &mapName);
 void rva00338317RegisterScriptFunctions();
private:
	lua_State *m_luaState;
	lua_State *m_lua10;
	char m_pad14[0x9C - 0x14];
public:
	LuaDrawableLink *m_drawable;
private:
	Rva00337AA8Buf<void> m_bufA0;
	char m_padA4[0xAC - 0xA4];
	bool m_flagAC; char m_padAD[3];
	Rva003378D0 m_vecB0;
	Rva00337AA8Buf<void> m_bufBC;
	char m_padC0[0xC8 - 0xC0];
	// C8 is explicitly released by the dtor body; BC/A0 are automatic.
	void *m_bufC8; void *m_endCC, *m_limitD0;
 int m_depth; // +0xD4
 unsigned char m_keepOpen; // +0xD8
 char m_padD9[3];
 int m_singleStepKey; // +0xDC
};

void LuaScriptEngine::DispatchSpyEvent(int key, void *object, void *spy, void *parameters)
{
	if (m_depth > 10)
		return;

	int top = lua_gettop(m_luaState);
	g_activeObj12F0610 = 0;

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

	PushObjectTable(m_luaState, (Object *)object);
	PushObjectTable(m_luaState, (Object *)spy);
	int count = 2;
	EventParameters *events = (EventParameters *)parameters;
	for (int i = 0; i < 3; ++i)
	{
		switch (events->m_event[i].m_kind)
		{
		case 1:
		{
			float real = events->m_event[i].m_real;
			bfmeGo1039E(m_luaState, (int)real);
			++count;
			break;
		}
		case 2:
		{
			bool flag = events->m_event[i].m_boolean;
			bfmeGo1039E(m_luaState, flag != 0);
			++count;
			break;
		}
		case 3:
			PushObjectTable(m_luaState, TheGameLogic->findObjectByID(events->m_event[i].m_object));
			++count;
			break;
		default:
			i = 3;
			break;
		}
	}

	if (debugStep)
		g_activeObj12F0610 = m_luaState;
	++m_depth;
	lua_call(m_luaState, count, 0);
	lua_settop(m_luaState, top);
	--m_depth;

	if (g_activeObj12F0610 && m_depth == 0)
	{
		bfmeLogMsg574("Stepping out of LUA function - step disabled.\n");
		g_activeObj12F0610 = 0;
	}
}
