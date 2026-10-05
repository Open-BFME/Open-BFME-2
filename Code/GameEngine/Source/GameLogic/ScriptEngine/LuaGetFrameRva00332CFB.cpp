// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Lua GetFrame binding 0x00332CFB (46B), dedicated safe TU.
// Home TU Code/GameEngine/Source/GameLogic/ScriptEngine/LuaScriptBindingsLuaAO1.cpp
// is held by another seat; this TU reuses its flags/externs verbatim with
// TU-scoped compatible views, no shared-header edits, no new pins.
//
// Target facts (game.dat, read-only):
// - entry 0x332CFB, 46B, ret C3, cdecl int f(lua_State*), returns 1.
// - registration 0x338357: push 0x732CFB + push [edi+0xC] + call lua_pushcclosure
//   (row 11102 @0x747640), then push 0xC0E308 ("GetFrame") + push [edi+0xC]
//   + call lua_setglobal (row 11142 @0x747920). Verified by capstone decode.
// - body: mov eax,[0xDFE78C] (TheGameLogic) + mov eax,[eax+0x40] (frame)
//   + fild/fadd-2^32-bias at 0xBCFA18/fstp + lua_pushnumber (row 11105 @0x747570).
// - float pool RVA 0x7CFA18 reads 2^32 double (00 00 00 00 00 00 F0 41 LE).
// - literal RVA 0x80E308 reads "GetFrame" NUL.
// Donor provenance (read-only, 6583b3c1):
// - reference/open-bfme-1/game/GameEngine/Source/GameLogic/ScriptEngine/
//   LuaScriptEngineRegisterScriptFunctions.cpp lines 128-131 registers GetFrame
//   via identical pushcclosure/setglobal pair (BFME1 j_ address never a target).
// - BFME2 family TU LuaScriptBindingsLuaAO1.cpp rows 50955/50956 prove
//   /O2->/O1 migration + cdecl luaA shape places byte-exact in this family.
// - GameLogic frame +0x40 UnsignedInt view from proven sibling
//   Code/GameEngine/Source/GameLogic/System/GameLogicAwakenUpdate.cpp
//   (frame+0x40, TheGameLogic 0x00DFE78C). Unsigned explains fild+bias shape;
//   signed would emit bare fild/fstp with no fadd.
// All callees rowed, TheGameLogic extern kept, pool is compiler literal.
// No new symbols.csv pin, no baseline change.

struct lua_State;
extern "C" void lua_pushnumber( lua_State *state, double value );

typedef unsigned int UnsignedInt;

class GameLogic
{
private:
	unsigned char m_pad00[ 0x40 ]; // +0x00..0x40

public:
	UnsignedInt m_frame; // +0x40 target fact, unsigned (bias conversion proves)
};

extern GameLogic *TheGameLogic;

// ?GetFrame@@YAHPAUlua_State@@@Z
int GetFrame( lua_State *state )
{
	UnsignedInt frame = TheGameLogic->m_frame;
	lua_pushnumber( state, (double)frame );
	return 1;
}
