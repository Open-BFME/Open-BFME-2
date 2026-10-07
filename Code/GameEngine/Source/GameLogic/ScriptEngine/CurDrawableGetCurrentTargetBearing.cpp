// cl: /MD /GX
//
// CurDrawableGetCurrentTargetBearing (0x00333182, 89B): the Lua callback the
// registration at 0x00335F0B pushes with lua_pushcclosure (nargs 0) and the
// lua_setglobal right after it names CurDrawableGetCurrentTargetBearing
// (string at VA 0x00C0E17C). Ported from Open-BFME-1's
// GameLogic/ScriptEngine/CurDrawableGetCurrentTargetDistance.cpp and
// CurDrawableGetCurrentTargetHeight.cpp (donor revision
// 6583b3c1ff21db4a561285717028fdafc780b7db): the same drawable (+0x9C in
// BFME2, +0x78 in BFME1) / owner (+0x0C) / target (+0xFC) null-guard chain and
// the same pushnumber-or-pushnil return-1 idiom, keeping the donor's repeated
// owner->m_target reads. BFME2 is new here: the payload is the target's
// relative angle through pinned Object::GetRelativeAngle (0x000B4542) normalized
// with rowed normalizeAngle (0x00238954) instead of the donor's
// sqrt/difference.

struct lua_State;
extern "C" void lua_pushnumber(lua_State *state, double value);
extern "C" void lua_pushnil(lua_State *state);

float normalizeAngle(float angle);

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object
{
public:
	float GetRelativeAngle(const Coord3D *pos) const;
	char m_pad000[0x38C];
	Coord3D m_bearingPos;	// +0x38C
};

struct LuaTargetOwner
{
	char m_targetPad[0xFC];
	Object *m_target;	// +0xFC
};

struct LuaDrawableLink
{
	char m_ownerPad[0x0C];
	LuaTargetOwner *m_owner;	// +0x0C
};

struct LuaDrawableState
{
	char m_drawablePad[0x9C];
	LuaDrawableLink *m_drawable;	// +0x9C
};
class LuaScriptEngine;
extern LuaScriptEngine *TheLuaScriptEngine;

// ?CurDrawableGetCurrentTargetBearing@@YAHPAUlua_State@@@Z
int CurDrawableGetCurrentTargetBearing(lua_State *state)
{
	LuaDrawableLink *drawable = reinterpret_cast<LuaDrawableState *>(TheLuaScriptEngine)->m_drawable;
	if (drawable != 0) {
		LuaTargetOwner *owner = drawable->m_owner;
		if (owner != 0) {
			if (owner->m_target != 0) {
				lua_pushnumber(state, normalizeAngle(owner->m_target->GetRelativeAngle(&owner->m_target->m_bearingPos)));
			}
			else {
				lua_pushnil(state);
			}
		}
		else {
			lua_pushnil(state);
		}
	}
	else {
		lua_pushnil(state);
	}
	return 1;
}
