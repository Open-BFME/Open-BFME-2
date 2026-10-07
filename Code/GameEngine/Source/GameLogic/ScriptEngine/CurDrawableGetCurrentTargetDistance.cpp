// cl: /MD /GX
//
// CurDrawableGetCurrentTargetDistance (0x00333125, 93B): the Lua callback the
// registration at 0x00335ED2 pushes with lua_pushcclosure (nargs 0) and the
// lua_setglobal right after it names CurDrawableGetCurrentTargetDistance
// (cstr at RVA 0x0080E1C4, verified by pe read; neighbor 0x0080E17C names the
// adjacent Bearing sibling landed from the same ScriptEngine folder).
// Ported from Open-BFME-1's
// GameLogic/ScriptEngine/CurDrawableGetCurrentTargetDistance.cpp (donor
// revision 6583b3c1ff21db4a561285717028fdafc780b7db): the same drawable
// (+0x9C in BFME2, +0x78 in BFME1) / owner (+0x0C) / target (+0xFC)
// null-guard chain and the same sqrt-of-planar-distance pushnumber-or-pushnil
// return-1 idiom, keeping the donor's repeated owner->m_target reads with no
// caching local (the add eax,0xFC idiom folds to mov+test with a cached
// local under MSVC 7.1, per the Bearing sibling). Single-return nested
// if/else: retail shares one xor/inc/ret tail reached by jmp from the number
// arm, unlike the donor's early return.

struct lua_State;
extern "C" void lua_pushnumber(lua_State *state, double value);
extern "C" void lua_pushnil(lua_State *state);

// Real CRT sqrt ABI: math.h double sqrt(double) emits the rowed msvcr71
// import call at 0x0062921C (same as the PathDistance/Rva00263778 siblings).
#include <math.h>

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object
{
public:
	float rva002C97E8(const Coord3D *a, const Coord3D *b) const;

	char m_pad00[0x38];
	Coord3D m_position; // +0x38 (Object geometry position, per ObjectRva002C97E8.cpp)
	char m_pad44[0x38C - 0x38 - 12];
	// +0x38C payload position: semantic identity inferred from the
	// rva002C97E8 (target-minus-[+0x38]) call contract, not independently proven.
	Coord3D m_targetPos; // +0x38C
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

// ?CurDrawableGetCurrentTargetDistance@@YAHPAUlua_State@@@Z
int CurDrawableGetCurrentTargetDistance(lua_State *state)
{
	LuaDrawableLink *drawable = reinterpret_cast<LuaDrawableState *>(TheLuaScriptEngine)->m_drawable;
	if (drawable != 0) {
		LuaTargetOwner *owner = drawable->m_owner;
		if (owner != 0) {
			if (owner->m_target != 0) {
				lua_pushnumber(state, sqrt(owner->m_target->rva002C97E8(&owner->m_target->m_position, &owner->m_target->m_targetPos)));
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
