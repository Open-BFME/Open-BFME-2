// cl: /MD /GX
#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../Common/GameLogicObjectLookupView.h"
class ThingTemplate;
class Player;
class Drawable;
class SpecialPowerModuleInterface;
enum SpecialPowerType { SPECIAL_POWER_TYPE_UNKNOWN = 0 };
enum DrawableID { INVALID_DRAWABLE_ID = 0 };
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

// +0x10 retail-measured; semantic (prev anim fraction) inferred from Lua name only
struct LuaDrawableLink
{
	AsciiString m_previousAnimationState;	// +0x00
	AsciiString m_transitionAnimState;	// +0x04
	AsciiString m_previousAnimation;	// +0x08
	Drawable *m_drawable;	// +0x0C
	float m_prevAnimFraction;	// +0x10
	unsigned char m_allowToContinue;	// +0x14
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
