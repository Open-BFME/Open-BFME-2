// cl: /O1
//
// Ported from Open-BFME-1 Libraries/Source/Lua/luaB_debug.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   _io_debug 0x00333E42 (25B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
// EA's replacement for Lua 4.0.1's stdin-based io_debug callback.

struct lua_State;

extern void __cdecl bfmeLogMsg574(const char *message);
extern int __cdecl bfmeNotify2_574(void *state, void *parameter);

extern "C" int __cdecl io_debug(lua_State *state)
{
	bfmeLogMsg574(
		"\nEntering LUA debug mode.  Type ? for help, 'cont' to exit debug mode\n");
	return bfmeNotify2_574(state, 0);
}
