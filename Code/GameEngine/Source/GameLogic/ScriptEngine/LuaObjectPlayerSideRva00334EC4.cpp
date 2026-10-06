// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Lua ObjectPlayerSide 0x00334EC4 (106B) + ObjectTemplateName 0x00334FAB (98B),
// dedicated TU. Home TU Code/GameEngine/Source/GameLogic/ScriptEngine/
// LuaScriptBindingsLuaAO1.cpp is held by scale-20261005-5; this TU reuses its
// flags/externs with TU-scoped views, no shared-header edits, no new pins.
//
// Target facts (game.dat, read-only, capstone + seat-55-r7 research):
// - 0x334EC4 106B [0x334EC4,0x334F2E) ret C3, cdecl int f(lua_State*), returns 1,
//   saves esi/edi (56 57). Registration 0x3384A4: push 0x734EC4 + push [edi+0xC]
//   + call lua_pushcclosure (row 11102 @0x747640), then push 0xC0E734
//   ("ObjectPlayerSide") + push [edi+0xC] + call lua_setglobal (row 11142).
//   Body: Lookup (row 9652 @0x747190) + lua_type (row 11127 @0x7470A0) +
//   findObjectByID (row 5818 @0x49DC5, single call, enum ObjectID, map +0xB4) +
//   Team::getControllingPlayer (row 13658 @0x39D7CF, ecx=[obj+0x304]) +
//   pushstring (row 11130) or pushnil (row 11104). Data: TheGameLogic 0xDFE78C
//   extern, empty 0xBBAC1C NUL, holder [player+0x58] -> string ([holder]?+8:empty).
// - 0x334FAB 98B [0x334FAB,0x33500D) same prologue/returns. Registration 0x3384DD:
//   push 0x734FAB + push [edi+0xC] + call pushcclosure, then push 0xC0E700
//   ("ObjectTemplateName") + push [edi+0xC] + call setglobal. Body: Lookup +
//   lua_type + findObjectByID (single, same row) + pushstring/pushnil, NO middle
//   getControllingPlayer. Holder [[obj+0x04]+0x64] -> string ([holder]?+8:empty).
// - Chain 0x334EC4 -> 0x334F2E (banked reverse/attempts/0x00334f2e.cpp 0.75) -> 0x334FAB -> 0x33500D contiguous.
// Donor provenance (read-only, 6583b3c1):
// - reference/open-bfme-1/game/GameEngine/Source/GameLogic/ScriptEngine/
//   LuaScriptBindingsLuaA.cpp ObjectTestModelCondition lines 131-155 same
//   Lookup/type/findObjectByID/pushnil family shape (moderate repair, same
//   providers/ABI, new +0x304/+0x04/+0x64/+0x58 field logic). ObjectPlayerSide
//   itself BFME2-new (rg empty in BFME1 ScriptEngine). ObjectTemplateName has
//   BFME1 registration at LuaScriptEngineRegisterScriptFunctions.cpp line 155
//   via identical pushcclosure/setglobal idiom (j_ address BFME1-only).
// - BFME2 family TU LuaScriptBindingsLuaAO1.cpp rows 50955/50956 prove
//   /O2->/O1 migration + cdecl luaA shape places byte-exact in this family.
// - Object Team+0x304 view from Code/GameEngine/Source/GameLogic/Object/
//   ObjectGetControllingPlayer.cpp (team+0x304, genuine +0x304). Player +0x58
//   holder and ThingTemplate+0x04/+0x64 holder are target byte facts
//   ([eax+0x304], [eax+0x04]+0x64, +0x58, +8); semantic names hypothesis only.
// - GameLogic::findObjectByID retail 0x00049DC5 37B is
//   Code/GameEngine/Source/GameLogic/GameLogicFindObjectByID.cpp with
//   enum ObjectID { INVALID_OBJECT_ID=0 } and map at this+0xB4 (retail B4).
//   This TU uses that enum spelling (W4ObjectID mangling), NOT typedef int
//   with pad 0xB0 (B0 alias in ObjectEnterUncontrollable...). Genuine provider.
// - Rva00990030Lookup retail 0x00747190 52B is
//   Code/GameEngine/Source/Common/Rva00990030RecordLookup.cpp with
//   Rva00990030Range* (genuine), NOT lua_State* alias. This TU uses Range*
//   with (Rva00990030Range*)state cast, as in ObjectCountNearbyEnemies.cpp
//   and ObjectBroadcastEvent.cpp (both /O1, both matched).
// All callees rowed (9652/11127/5818/13658/11130/11104), no new symbols.csv pin.
// No canonical header (GameLogic/Object/Team/Player have no canonical entry;
// AsciiString canonical avoided via holder struct with void*).

struct lua_State;
extern "C" int lua_type( lua_State *state, int index );
extern "C" void lua_pushnil( lua_State *state );
extern "C" void lua_pushstring( lua_State *state, const char *str );
struct Rva00990030Range;
unsigned Rva00990030Lookup( Rva00990030Range *range, int index );

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class Object;
class Player;
class Team;

struct BfmeSideHolder
{
	void *m_data;
};

class Player
{
private:
	unsigned char m_pad00[ 0x58 ]; // +0x00..0x58

public:
	BfmeSideHolder m_side58; // +0x58 target fact, AsciiString-compatible 4B
};

class Team
{
public:
	Player *getControllingPlayer() const; // row 13658 @0x39D7CF
};

class Object
{
private:
	unsigned char m_pad00[ 0x04 ]; // +0x00 vtable slot

public:
	void *m_p04; // +0x04 target fact (ThingTemplate* for template-name path)

private:
	unsigned char m_pad08[ 0x304 - 0x08 ]; // +0x08..0x304

public:
	Team *m_team304; // +0x304 target fact (Team* for player-side path)
};

class GameLogic
{
public:
	Object *findObjectByID( ObjectID id ); // row 5818 @0x49DC5, enum W4ObjectID
};

extern GameLogic *TheGameLogic;

// ?Rva00334EC4@@YAHPAUlua_State@@@Z (Lua ObjectPlayerSide binding)
int Rva00334EC4( lua_State *state )
{
	unsigned id = Rva00990030Lookup( (Rva00990030Range *)state, 1 );
	if( !id && lua_type( state, 1 ) != 1 )
		goto fail;
	Object *object = TheGameLogic->findObjectByID( (ObjectID)id );
	if( object )
	{
		Team *team = object->m_team304;
		Player *player = team->getControllingPlayer();
		BfmeSideHolder *holder = &player->m_side58;
		const char *side = holder->m_data ?
			(const char *)holder->m_data + 8 : "";
		lua_pushstring( state, side );
		return 1;
	}
fail:
	lua_pushnil( state );
	return 1;
}

// ?Rva00334FAB@@YAHPAUlua_State@@@Z (Lua ObjectTemplateName binding)
int Rva00334FAB( lua_State *state )
{
	unsigned id = Rva00990030Lookup( (Rva00990030Range *)state, 1 );
	if( !id && lua_type( state, 1 ) != 1 )
		goto fail;
	Object *object = TheGameLogic->findObjectByID( (ObjectID)id );
	if( object )
	{
		BfmeSideHolder *holder = (BfmeSideHolder *)( (char *)object->m_p04 + 0x64 );
		const char *name = holder->m_data ?
			(const char *)holder->m_data + 8 : "";
		lua_pushstring( state, name );
		return 1;
	}
fail:
	lua_pushnil( state );
	return 1;
}
