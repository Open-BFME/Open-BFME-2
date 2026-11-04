// cl: /MD
// Open-BFME5 conversions.

struct BfmeLuaVHR;

struct BfmeTagVIF
{
	char m_bfmePad[8];
	int m_bfme08;
};

extern "C" const char *luaL_check_lstr(BfmeLuaVHR *L, int n, unsigned *len);
extern "C" void lua_pushnil(BfmeLuaVHR *L);
extern "C" void lua_pushnumber(BfmeLuaVHR *L, double v);
extern "C" void lua_pushstring(BfmeLuaVHR *L, const char *s);
extern "C" void lua_pushusertag(BfmeLuaVHR *L, void *u, int tag);
extern "C" void *lua_touserdata(BfmeLuaVHR *L, int n);
extern "C" void lua_settop(BfmeLuaVHR *L, int n);

#include <stdio.h>

int __cdecl io_open(BfmeLuaVHR *L)
{
	BfmeTagVIF *tag = (BfmeTagVIF *)lua_touserdata(L, -1);
	lua_settop(L, -2);
	void *fp = fopen(luaL_check_lstr(L, 1, 0), luaL_check_lstr(L, 2, 0));
	if (fp)
	{
		lua_pushusertag(L, fp, tag->m_bfme08);
		return 1;
	}
	lua_pushnil(L);
	lua_pushstring(L, "generic I/O error");
	lua_pushnumber(L, -1.0);
	return 3;
}
