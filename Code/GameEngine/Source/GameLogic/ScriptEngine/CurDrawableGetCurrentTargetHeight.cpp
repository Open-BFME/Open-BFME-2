// cl: /MD /GX
//
// CurDrawableGetCurrentTargetHeight (0x00332D29, 76B): the Lua callback the
// registration at 0x00335EEC pushes with lua_pushcclosure (nargs 0) and the
// lua_setglobal right after it names CurDrawableGetCurrentTargetHeight
// (cstr at RVA 0x0080E1A0, VA 0x00C0E1A0; neighbor 0x0080E1C4 names Distance
// and 0x0080E17C names Bearing from the same ScriptEngine folder).
// Ported from Open-BFME-1's
// GameLogic/ScriptEngine/CurDrawableGetCurrentTargetHeight.cpp (donor
// revision 6583b3c1ff21db4a561285717028fdafc780b7db): the same drawable
// (+0x9C in BFME2, +0x78 in BFME1) / owner (+0x0C) / target (+0xFC)
// null-guard chain and the same pushnumber-or-pushnil return-1 idiom, keeping
// the donor's repeated owner->m_target reads with no caching local (the add
// eax,0xFC idiom, per the Bearing/Distance siblings). Single-return nested
// if/else: retail shares one xor/inc/ret tail reached by jmp from the number
// arm, unlike the donor's early return. Payload is targetHeight minus
// currentHeight (both float): retail fld [eax+0x394] / fsub [eax+0x40].

struct lua_State;
extern "C" void lua_pushnumber(lua_State *state, double value);
extern "C" void lua_pushnil(lua_State *state);

class Object
{
public:
	char m_pad00[0x40];
	float m_currentHeight; // +0x40 (matches donor +0x40; 4B float per fld/fsub)
	char m_pad44[0x394 - 0x40 - 4];
	// +0x394 payload height: semantic identity (target height) inferred from
	// the (target-minus-current) subtraction contract, not independently proven.
	float m_targetHeight; // +0x394 (BFME2 growth vs donor +0x2B0)
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

// ?CurDrawableGetCurrentTargetHeight@@YAHPAUlua_State@@@Z
int CurDrawableGetCurrentTargetHeight(lua_State *state)
{
	LuaDrawableLink *drawable = reinterpret_cast<LuaDrawableState *>(TheLuaScriptEngine)->m_drawable;
	if (drawable != 0) {
		LuaTargetOwner *owner = drawable->m_owner;
		if (owner != 0) {
			if (owner->m_target != 0) {
				lua_pushnumber(state, owner->m_target->m_targetHeight - owner->m_target->m_currentHeight);
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
