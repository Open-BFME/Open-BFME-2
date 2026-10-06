// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Lua ObjectForbidPlayerCommands 0x00334D16 (72B), dedicated TU. Home TU
// Code/GameEngine/Source/GameLogic/ScriptEngine/LuaScriptBindingsLuaAO1.cpp
// supplies compatible compiler flags and extern declarations with
// TU-scoped views, no shared-header edits, no new pins.
//
// Target facts (game.dat, read-only, capstone):
// - 0x334D16 72B [0x334D16,0x334D5E) ret C3, cdecl int f(lua_State*),
//   returns 0 (xor eax,eax), saves esi only (push esi at 0x734D37).
//   Registration 0x338795: push 0x734D16 + push 0xC0E48C
//   ("ObjectForbidPlayerCommands") + call lua_pushcclosure (row 11102
//   @0x747640) then setglobal (row 11142 @0x747920), same idiom as
//   EC4 0x3384A4 / FAB 0x3384DD / 3500D 0x3384F8.
//   Body: Rva00990030Lookup (row 9652 @0x747190, index 1) +
//   GameLogic::findObjectByID (row 5818 @0x49DC5, single call, enum
//   ObjectID, map +0xB4) + Rva00990210Lookup (row 9638 @0x747370,
//   index 2) + byte store. No lua_type / lua_gettop / lua_tostring /
//   AsciiString / EH prolog (starts push 1, not mov eax cookie).
//   Data: TheGameLogic 0xDFE78C extern single load; Object+0x258
//   AIUpdate* (retail [eax+0x258], same slot as ScriptActions AI+0x258
//   family); AIUpdate+0x3C5 Bool (retail [esi+0x3C5], same byte as
//   AIUpdateInterfacePrivateCommands.cpp m_bfmeIgnorePlayerCommands).
// - Chain 0x334C9F (119B) -> 0x334D16 (72B) -> 0x334D5E contiguous,
//   previous ret at 0x734D15, our ret at 0x734D5D, next mov at 0x734D5E.
// Donor provenance (read-only, 6583b3c1):
// - BFME1 LuaScriptBindingsLuaA.cpp ObjectTestModelCondition family shape
//   (Lookup/find/second-Lookup/flag) as moderate-repair guide; BFME2 deltas
//   (+0x258 AI slot, +0x3C5 forbid byte, Range*/enum spellings, /O1 cdecl
//   luaA shape) are target facts.
// - BFME2 family TU LuaScriptBindingsLuaAO1.cpp rows 50955/50956 prove
//   /O2->/O1 migration + cdecl luaA shape places byte-exact in this family.
// - EC4/FAB TU LuaObjectPlayerSideRva00334EC4.cpp (106B/98B, same flags,
//   same Range*/enum/TheGameLogic spellings) proves the Range* cast and
//   W4ObjectID mangling place byte-exact for Lookup/find in /O1.
// - Object AI+0x258 from ScriptActions_doNamedAttackArea.cpp /
//   Rva003C8A95Do.cpp (AIUpdateInterface* at +0x258, target fact).
// - AIUpdate+0x3C5 from AIUpdateInterfacePrivateCommands.cpp
//   (m_bfmeIgnorePlayerCommands at +0x3C5, target fact; semantic name
//   hypothesis only, layout is retail-proven).
// All callees rowed (9652/5818/9638), no new symbols.csv pin.
// The AI receiver view is opaque; native evidence identifies its interface slot.
// Independent review: normal-restart/luna-review-lua72-r3.json; native registration
// and exact interval corroborated separately from the BFME1 source guide.

struct lua_State;
struct Rva00990030Range;
unsigned Rva00990030Lookup( Rva00990030Range *range, int index );
struct Rva00990210Range;
unsigned Rva00990210Lookup( Rva00990210Range *range, int index );

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class Rva00334D16AIView
{
private:
	unsigned char m_pad00[ 0x3C5 ]; // +0x00..0x3C5

public:
	bool m_forbid3C5; // +0x3C5 target fact, Bool byte store
};

class Object
{
private:
	unsigned char m_pad00[ 0x258 ]; // +0x00..0x258

public:
	Rva00334D16AIView *m_ai258; // +0x258 target fact, AIUpdateInterface*
};

class GameLogic
{
public:
	Object *findObjectByID( ObjectID id ); // row 5818 @0x49DC5, enum W4ObjectID
};

extern GameLogic *TheGameLogic;

// ?Rva00334D16@@YAHPAUlua_State@@@Z (Lua ObjectForbidPlayerCommands binding)
int Rva00334D16( lua_State *state )
{
	unsigned id = Rva00990030Lookup( (Rva00990030Range *)state, 1 );
	if( !id )
		return 0;
	Object *object = TheGameLogic->findObjectByID( (ObjectID)id );
	if( !object )
		return 0;
	Rva00334D16AIView *ai = object->m_ai258;
	if( !ai )
		return 0;
	unsigned v = Rva00990210Lookup( (Rva00990210Range *)state, 2 );
	ai->m_forbid3C5 = ( v != 0 );
	return 0;
}
