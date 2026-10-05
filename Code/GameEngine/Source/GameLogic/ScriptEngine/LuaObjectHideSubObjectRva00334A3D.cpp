// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Lua ObjectHideSubObject 0x00334A3D (182B), dedicated TU. Home TU
// Code/GameEngine/Source/GameLogic/ScriptEngine/LuaScriptBindingsLuaAO1.cpp
// is held by scale-20261005-5; this TU reuses its flags/externs with
// TU-scoped views, no shared-header edits, no new pins.
//
// Target facts (game.dat, read-only, capstone):
// - 0x334A3D 182B [0x334A3D,0x334AF3) ret C3, cdecl int f(lua_State*),
//   returns 0 (xor eax,eax), EH prolog (mov eax 0xB7C14C + call rowed
//   __EH_prolog 0x629188) for the AsciiString local at [ebp-0x10]
//   (state [ebp-4] cleared 0 after ctor, or-ed -1 before dtor).
//   Registration 0x33870B: push 0x734A3D + push 0xC0E51C
//   ("ObjectHideSubObject", read from game.dat rdata) + call
//   lua_pushcclosure (row 11102 @0x747640) then push 0xC0E51C +
//   setglobal (row 11142 @0x747920), same idiom as EC4 0x3384A4 /
//   FAB 0x3384DD / D16 0x338795. Next registration 0x338726 pushes
//   0x734AF3 (ObjectHideSubObjectPermanently), so the range is
//   contiguous [0x334A3D,0x334AF3).
//   Body: lua_gettop (row 11098 @0x746F30, !=3 fail) +
//   Rva00990030Lookup (row 9652 @0x747190, index 1, id==0+type check) +
//   lua_type (row 11127 @0x7470A0, index 1, !=1 fail) +
//   GameLogic::findObjectByID (row 5818 @0x49DC5, single TheGameLogic
//   0xDFE78C load, enum ObjectID, null fail) + lua_tostring (row 11137
//   @0x7473B0, index 2) + AsciiString ctor (row 1235 @0x37BA0) +
//   Rva00990210Lookup (row 9638 @0x747370, index 3, ==0 bool via
//   neg/sbb/inc) + Object::getDrawable (pin 6310 @0x5508E2, unchecked,
//   outer-call args pre-pushed) + Drawable::rva002724FD (row 38152
//   @0x2724FD, EHMM uchar spelling via provider alias) + AsciiString
//   dtor (pin 554 @0x36410). No lua_gettop/getglobal/AsciiString
//   beyond these; floats 0.0f/0.0f via fldz/fstp.
// Donor provenance (read-only, 6583b3c1):
// - reference/open-bfme-1/game/GameEngine/Source/GameLogic/ScriptEngine/
//   ObjectHideSubObject.cpp (direct donor, same name/registration) as
//   compatible guide; BFME2 deltas (Range*/enum spellings, /O1 cdecl
//   luaA shape, direct rva002724FD call instead of S4Sink union+j_
//   thunk, (name,hide,0,0.0f,0.0f) floats instead of (name,hide,0,0,0))
//   are target facts.
// - BFME2 family TUs LuaObjectPlayerSideRva00334EC4.cpp (106B/98B) and
//   LuaObjectForbidPlayerCommandsRva00334D16.cpp (72B, same flags,
//   same Range*/enum/TheGameLogic spellings) prove the Lookup/type/
//   find idiom places byte-exact under /O1.
// - Drawable::rva002724FD (AsciiString&,uchar,int,float,float) decl and
//   (byte,1,0.0f,0.0f) float shape after Rva00496CA8Broadcast.cpp
//   (mov-cl byte observation, provider alias EHMM->HHMM); here the byte
//   is (Lookup==0) bool, same 1-byte representation as donor bool.
// - Object::getDrawable const decl after ScriptActionsRva003BBD02.cpp
//   (pin 6310 @0x5508E2, ICF twin of rowed BuildListInfo getter).
// All 9 callees rowed/pinned, no new symbols.csv pin.
// No canonical header (GameLogic/Object/Drawable/AsciiString have no
// canonical entry; AsciiString via bfme2_ascii shim, /I FIRST).
#include "ascii_string.h"

struct lua_State;
extern "C" int lua_gettop( lua_State *state );
extern "C" int lua_type( lua_State *state, int index );
extern "C" const char *lua_tostring( lua_State *state, int index );
struct Rva00990030Range;
unsigned Rva00990030Lookup( Rva00990030Range *range, int index );
struct Rva00990210Range;
unsigned Rva00990210Lookup( Rva00990210Range *range, int index );

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class Drawable
{
public:
	void rva002724FD( const AsciiString &a, unsigned char b, int c, float d, float e );
};

class Object
{
public:
	Drawable *getDrawable() const;
};

class GameLogic
{
public:
	Object *findObjectByID( ObjectID id ); // row 5818 @0x49DC5, enum W4ObjectID
};

extern GameLogic *TheGameLogic;

// ?Rva00334A3D@@YAHPAUlua_State@@@Z (Lua ObjectHideSubObject binding)
int Rva00334A3D( lua_State *state )
{
	unsigned id;
	Object *object;
	if( lua_gettop( state ) != 3
		|| ( ( id = Rva00990030Lookup( (Rva00990030Range *)state, 1 ) ) == 0
			&& lua_type( state, 1 ) != 1 )
		|| ( object = TheGameLogic->findObjectByID( (ObjectID)id ) ) == 0 )
		return 0;
	{
		AsciiString name( lua_tostring( state, 2 ) );
		object->getDrawable()->rva002724FD( name,
			Rva00990210Lookup( (Rva00990210Range *)state, 3 ) == 0, 0, 0.0f, 0.0f );
	}
	return 0;
}
