// cl: /Ireference/shims/bfme2_ascii /MD /GX
//
// CurDrawableSetTransitionAnimState (0x003331DB, 64B): the Lua callback the
// registration at 0x00335F40 pushes with lua_pushcclosure (nargs 0) and the
// lua_setglobal right after it names CurDrawableSetTransitionAnimState
// (cstr at RVA 0x0080E13C, VA 0x00C0E13C; same CurDrawable registration block
// as Bearing 0x333182 / Distance 0x333125 / Height 0x332D29).
// Ported from Open-BFME-1's
// GameLogic/ScriptEngine/LuaCurDrawableSetTransitionAnimState.cpp (donor
// revision 6583b3c1ff21db4a561285717028fdafc780b7db): the same drawable
// (+0x9C in BFME2, +0x78 in BFME1) null-guard plus lua_gettop>0 guard, then
// AsciiString::set(lua_tostring(state,1)) on the drawable+0x04 slot.
// Single-return: retail shares one xor/ret tail (return 0), unlike the
// donor's early return. Providers rowed: lua_gettop/lua_tostring (lapi.c),
// AsciiString::set folding to rowed StringBase<char>::set 0x000055F5 (no new
// pin).

struct lua_State;
extern "C" int lua_gettop(lua_State *state);
extern "C" const char *lua_tostring(lua_State *state, int index);

// Canonical AsciiString (one-pointer, 4B): set(const char*) aliases the
// rowed StringBase<char>::set at 0x000055F5 via the header's alternatename
// (no private copy, per class_gate; layout +0x04 unchanged).
#include "ascii_string.h"

struct LuaTargetOwner;

struct LuaDrawableLink
{
	char m_pad00[0x04];
	AsciiString m_transitionAnimState; // +0x04 (retail add ecx,4)
	char m_pad08[0x04];
	LuaTargetOwner *m_owner; // +0x0C (matches donor; untouched here)
};

struct LuaDrawableState
{
	char m_drawablePad[0x9C];
	LuaDrawableLink *m_drawable;	// +0x9C
};
class LuaScriptEngine;
extern LuaScriptEngine *TheLuaScriptEngine;

// ?CurDrawableSetTransitionAnimState@@YAHPAUlua_State@@@Z
int CurDrawableSetTransitionAnimState(lua_State *state)
{
	if (reinterpret_cast<LuaDrawableState *>(TheLuaScriptEngine)->m_drawable != 0) {
		if (lua_gettop(state) > 0) {
			reinterpret_cast<LuaDrawableState *>(TheLuaScriptEngine)->m_drawable->m_transitionAnimState.set(lua_tostring(state, 1));
		}
	}
	return 0;
}
