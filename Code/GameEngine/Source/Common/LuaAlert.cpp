// cl: /Ireference/shims/bfme2_ascii /EHsc
// ?_ALERT@@YAHPAUlua_State@@@Z @0x003333D1 83B: Lua _ALERT building AsciiString "LUA Alert: " plus lua_tostring(L 1); evidence pinned name and rowed callees lua_tostring StringBase ctor concat releaseBuffer
#include "ascii_string.h"

struct lua_State;
extern "C" const char *__cdecl lua_tostring(struct lua_State *L, int idx);

int __cdecl _ALERT(struct lua_State *L)
{
	const char *p = lua_tostring(L, 1);
	AsciiString s("LUA Alert: ");
	if (p)
		s += p;
	return 0;
}
