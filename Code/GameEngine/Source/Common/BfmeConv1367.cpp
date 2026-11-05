// cl: /MD
// Open-BFME5 conversions.

struct BfmeLuaVHR;

extern "C" const char *__cdecl luaL_check_lstr(BfmeLuaVHR *L, int n, unsigned *len);
extern "C" void __cdecl lua_pushnil(BfmeLuaVHR *L);
extern "C" void __cdecl lua_pushnumber(BfmeLuaVHR *L, double v);
extern "C" void __cdecl lua_pushstring(BfmeLuaVHR *L, const char *s);
extern "C" void __cdecl lua_pushusertag(BfmeLuaVHR *L, void *u, int tag);

// BFME1 declares these as bfmeRemoveVHR/bfmeRenameVHS; retail game.dat
// reaches the real CRT imports (msvcr71!remove @0xBBA3FC,
// msvcr71!rename @0xBBA718), so declare the true import names here.
#include <stdio.h>

int __cdecl bfmeGoVHR(BfmeLuaVHR *luaState)
{
	if (remove(luaL_check_lstr(luaState, 1, 0)) == 0)
	{
		lua_pushusertag(luaState, 0, 0);
		return 1;
	}
	lua_pushnil(luaState);
	lua_pushstring(luaState, "generic I/O error");
	lua_pushnumber(luaState, -1.0);
	return 3;
}


int __cdecl osRename(BfmeLuaVHR *luaState)
{
	if (rename(luaL_check_lstr(luaState, 1, 0), luaL_check_lstr(luaState, 2, 0)) == 0)
	{
		lua_pushusertag(luaState, 0, 0);
		return 1;
	}
	lua_pushnil(luaState);
	lua_pushstring(luaState, "generic I/O error");
	lua_pushnumber(luaState, -1.0);
	return 3;
}
