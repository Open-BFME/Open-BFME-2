// ?rva00333F37@LuaDrawableState@@QAEXPAVObject@@@Z
// partial score=0.9 date=2026-10-07
// cl: /Ireference/shims/bfme2_ascii /O1 /GX
#include "ascii_string.h"

struct lua_State;
struct Rva00990030Range;
struct BfmeStateUPC;
struct Rva00333374IdOwner;

extern "C" void __cdecl lua_settop(lua_State *L, int idx);
extern "C" int __cdecl lua_gettop(lua_State *L);
extern "C" void __cdecl lua_getglobal(lua_State *L, const char *name);
extern "C" void __cdecl lua_setglobal(lua_State *L, const char *name);
extern "C" int __cdecl lua_type(lua_State *L, int idx);
extern "C" void __cdecl lua_pushnil(lua_State *L);
unsigned int Rva00990030Lookup(Rva00990030Range *L, int idx);	// 0x00747190
void bfmeGoUPC(BfmeStateUPC *L, int value);			// 0x007478E0
AsciiString Rva00333374Get(const Rva00333374IdOwner *obj);	// 0x00333374

enum { LUA_TNIL = 1 };

class ThingTemplate
{
public:
	unsigned char m_pad[0x630];
	bool m_x630;					// +0x630
};

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	int getID() const { return m_id; }
	void *getX258() const { return m_x258; }

private:
	void *m_vtbl;
	const ThingTemplate *m_template;		// +0x04
	unsigned char m_pad08[0x74 - 8];
	int m_id;					// +0x74
	unsigned char m_pad78[0x258 - 0x78];
	void *m_x258;					// +0x258
};

static inline AsciiString objectGlobalName(const Object *obj)
{
	return Rva00333374Get((const Rva00333374IdOwner *)obj);
}

class LuaDrawableState
{
public:
	void rva00333E5B(Object *obj);
	void rva00333F37(Object *obj);
	void rva00334003(lua_State *L, Object *obj);

private:
	unsigned char m_pad00[0xC];
	lua_State *m_lua;				// +0x0C
	lua_State *m_x10;				// +0x10
};

void LuaDrawableState::rva00333E5B(Object *obj)
{
	if (obj->getX258() == 0 && !obj->getTemplate()->m_x630)
		return;
	lua_settop(m_x10, 0);
	AsciiString name = objectGlobalName(obj);
	int id = obj->getID();
	lua_getglobal(m_lua, name.str());
	if (lua_type(m_lua, 1) != LUA_TNIL && (unsigned int)id == Rva00990030Lookup((Rva00990030Range *)m_lua, 1))
	{
		lua_settop(m_lua, -2);
	}
	else
	{
		lua_settop(m_lua, -2);
		bfmeGoUPC((BfmeStateUPC *)m_lua, id);
		lua_setglobal(m_lua, name.str());
	}
}

void LuaDrawableState::rva00333F37(Object *obj)
{
	if (m_lua == 0)
		return;
	lua_settop(m_x10, 0);
	AsciiString name = objectGlobalName(obj);
	int id = obj->getID();
	lua_getglobal(m_lua, name.str());
	if (lua_type(m_lua, 1) != LUA_TNIL && (unsigned int)id == Rva00990030Lookup((Rva00990030Range *)m_lua, 1))
	{
		lua_settop(m_lua, -2);
		lua_pushnil(m_lua);
		lua_setglobal(m_lua, name.str());
	}
	else
	{
		lua_settop(m_lua, -2);
	}
}

void LuaDrawableState::rva00334003(lua_State *L, Object *obj)
{
	if (obj == 0)
	{
		lua_pushnil(m_lua);
		return;
	}
	AsciiString name = objectGlobalName(obj);
	int id = obj->getID();
	lua_getglobal(m_lua, name.str());
	int top = lua_gettop(L);
	if (lua_type(m_lua, top) == LUA_TNIL || Rva00990030Lookup((Rva00990030Range *)m_lua, top) != (unsigned int)id)
	{
		lua_settop(m_lua, top);
		lua_pushnil(m_lua);
	}
}
