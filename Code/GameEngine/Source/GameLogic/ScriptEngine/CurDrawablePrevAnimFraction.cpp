// cl: /MD /GX
//
// CurDrawablePrevAnimFraction (0x00332DDC, 61B): the Lua callback the
// registration at 0x00335F26 pushes with lua_pushcclosure (nargs 0) and the
// lua_setglobal right after it names CurDrawablePrevAnimFraction
// (string at VA 0x00C0E160). Same CurDrawable family as Bearing/Distance/
// Height/Transition siblings: global Lua state at VA 0x00E01DBC with drawable
// link at +0x9C. Retail reads a float at drawable+0x10 when the link is
// non-null, defaults to 0.0f when null, pushes it with lua_pushnumber and
// returns 1 (no nil fallback, unlike Height/Distance/Bearing).
struct lua_State;
extern "C" void lua_pushnumber(lua_State *state, double value);

struct LuaDrawableLink
{
	char m_pad000[0x10];
	float m_prevAnimFraction;	// +0x10 retail-measured; semantic (prev anim fraction) inferred from Lua name only
};

struct LuaDrawableState
{
	char m_drawablePad[0x9C];
	LuaDrawableLink *m_drawable;	// +0x9C
};
class LuaScriptEngine;
extern LuaScriptEngine *TheLuaScriptEngine;

// ?CurDrawablePrevAnimFraction@@YAHPAUlua_State@@@Z
int CurDrawablePrevAnimFraction(lua_State *state)
{
	float frac = 0.0f;
	LuaDrawableLink *drawable = reinterpret_cast<LuaDrawableState *>(TheLuaScriptEngine)->m_drawable;
	if (drawable != 0) {
		frac = drawable->m_prevAnimFraction;
	}
	lua_pushnumber(state, frac);
	return 1;
}
