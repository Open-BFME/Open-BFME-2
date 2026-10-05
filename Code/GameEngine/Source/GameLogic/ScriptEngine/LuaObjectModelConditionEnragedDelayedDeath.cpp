// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Isolated Lua object-state bindings packet (358B): ObjectTestModelCondition
// 0x0033500D (130B), ObjectSetEnragedState 0x003358D9 (113B),
// ObjectSetDelayedDeath 0x003353A9 (115B).
// Reference-guided ports of Open-BFME-1's
// game/GameEngine/Source/GameLogic/ScriptEngine/LuaScriptBindingsLuaA.cpp
// (donor revision 6583b3c1ff21db4a561285717028fdafc780b7db, donor flags plus /O1).
// TARGET FACTS (retail call-site decode in-lane, preserved from seat-5 r5/r6/r9/r10):
// - registrations at 0x3384F8 (TestMC), 0x338647 (Enraged), 0x3386ED (DelayedDeath)
//   each push body RVA + lua_pushcclosure 0x747640 + literal name + lua_setglobal 0x747920.
// - TestMC uses rowed 0xB42CA BitFlags<304>::getSingleBitFromName and retail +0x10C word base.
// - Enraged calls rowed 0x28EBDA Object::rva0028EBDA (classcast mov ecx,esi shape).
// - DelayedDeath uses contain at object+0x254 via v37 slot 0x94 (retail FF9094000000).
// DONOR FACTS CARRIED ONLY: control shapes + Lua cdecl return lanes + lookup/findObject
// sequences from BFME1 LuaScriptBindingsLuaA.cpp. Nothing about +0x10C/+0x254 offsets,
// BitFlags/ObjectID spelling, Range layouts, or TheGameLogic resolution is donor-carried.
// INFERENCE (verified by build): BFME2 enum ObjectID + Range-pointer casts preserve bytes.
// This clean TU avoids the home TU's private AsciiString (registered canonical class)
// and its other missing providers (DescribeObject, delayed-list, dispatch invoke,
// unsigned nameToKey, _g_bfmeEmptyAscii). No raw aliases: Range/enum manglings verbatim
// to rowed providers 9652/9638/5818. No shared-header edits.

struct lua_State;
extern "C" int lua_gettop( lua_State *state );
extern "C" int lua_type( lua_State *state, int index );
extern "C" const char *lua_tostring( lua_State *state, int index );
extern "C" void lua_pushnil( lua_State *state );

struct Rva00990030Range;
unsigned Rva00990030Lookup( Rva00990030Range *range, int index );

struct Rva00990210Range;
unsigned Rva00990210Lookup( Rva00990210Range *range, int index );

class Object
{
public:
	void rva0028EBDA( bool flag );
};

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class GameLogic
{
public:
	Object *findObjectByID( ObjectID id );
};

extern GameLogic *TheGameLogic;

struct BfmeQ1039;
void bfmeGo1039E( BfmeQ1039 *q, int v );

// Opaque virtual prefix: declarations preserve the observed slot without
// inventing implementations for the unreconstructed methods.
class Rva002E9F70Vtbl94
{
public:
	virtual void v0( void ) = 0;
	virtual void v1( void ) = 0;
	virtual void v2( void ) = 0;
	virtual void v3( void ) = 0;
	virtual void v4( void ) = 0;
	virtual void v5( void ) = 0;
	virtual void v6( void ) = 0;
	virtual void v7( void ) = 0;
	virtual void v8( void ) = 0;
	virtual void v9( void ) = 0;
	virtual void v10( void ) = 0;
	virtual void v11( void ) = 0;
	virtual void v12( void ) = 0;
	virtual void v13( void ) = 0;
	virtual void v14( void ) = 0;
	virtual void v15( void ) = 0;
	virtual void v16( void ) = 0;
	virtual void v17( void ) = 0;
	virtual void v18( void ) = 0;
	virtual void v19( void ) = 0;
	virtual void v20( void ) = 0;
	virtual void v21( void ) = 0;
	virtual void v22( void ) = 0;
	virtual void v23( void ) = 0;
	virtual void v24( void ) = 0;
	virtual void v25( void ) = 0;
	virtual void v26( void ) = 0;
	virtual void v27( void ) = 0;
	virtual void v28( void ) = 0;
	virtual void v29( void ) = 0;
	virtual void v30( void ) = 0;
	virtual void v31( void ) = 0;
	virtual void v32( void ) = 0;
	virtual void v33( void ) = 0;
	virtual void v34( void ) = 0;
	virtual void v35( void ) = 0;
	virtual void v36( void ) = 0;
	virtual void v37call( bool arg ) = 0;
};

#include <stddef.h>

// TU-scoped BitFlags<304> view for ModelConditionFlags name lookup.
// Provider: 0x000B42CA ?getSingleBitFromName@?$BitFlags@$0BDA@@@SAHPBD@Z
// (Code/GameEngine/Source/Common/BitFlags304GetSingleBitFromName.cpp, matched).
// Minimal static-method view; no shared-header edit.
template <size_t NUMBITS>
class BitFlags
{
public:
	static int getSingleBitFromName( const char *token );
};

// ?ObjectTestModelCondition@@YAHPAUlua_State@@@Z
// Retail 0x0033500D 130B. Reference-guided port of BFME1
// LuaScriptBindingsLuaA.cpp ObjectTestModelCondition (6583b3c1) with
// target-evidence adaptations: helper is rowed 0x000B42CA
// BitFlags<304>::getSingleBitFromName (ModelConditionFlags-proven, not donor
// bfmeLookup_001c62b0) and ModelConditionFlags word base is retail +0x10c
// (donor +0x110). Identity proven by registration at 0x003384F8
// (push 0x73500D + lua_pushcclosure 0x747640 + literal 0xC0E6E4
// 'ObjectTestModelCondition' + lua_setglobal 0x747920); layout/providers
// read off retail call sites independently verified in this lane.
int ObjectTestModelCondition( lua_State *state )
{
	unsigned id = Rva00990030Lookup( (Rva00990030Range *)state, 1 );
	if( !id && lua_type( state, 1 ) != 1 )
	{
		lua_pushnil( state );
		return 1;
	}
	Object *object = TheGameLogic->findObjectByID( (ObjectID)id );
	if( object )
	{
		const char *name = lua_tostring( state, 2 );
		if( name )
		{
		int idx = BitFlags<304>::getSingleBitFromName( name );
		if( idx != -1 )
		{
			unsigned *bits = (unsigned *)( (char *)object + 0x10c );
			bool bit = ( bits[ (unsigned)idx >> 5 ] & ( 1u << ( idx & 0x1f ) ) ) != 0;
			bfmeGo1039E( (BfmeQ1039 *)state, bit );
			return 1;
		}
		}
	}
	lua_pushnil( state );
	return 1;
}

// ?ObjectSetEnragedState@@YAHPAUlua_State@@@Z
// Retail 0x003358D9 113B. Reference-guided port of BFME1
// LuaScriptBindingsLuaA.cpp ObjectSetEnragedState (6583b3c1) with
// target-evidence adaptation: provider is rowed 0x0028EBDA
// Object::rva0028EBDA (EnragedBehavior via TheNameKeyGenerator, matched
// ObjectRva0028EBDA.cpp) not donor ILT 0x0001E33F->0x001C1EA0.
// Identity proven by registration at 0x00338647
// (push 0x7358D9 + lua_pushcclosure 0x747640 + literal 0xC0E5BC
// 'ObjectSetEnragedState' + lua_setglobal 0x747920); layout/providers
// read off retail call sites independently verified in this lane.
int ObjectSetEnragedState( lua_State *state )
{
	if( lua_gettop( state ) < 2 )
		return 0;
	unsigned id = Rva00990030Lookup( (Rva00990030Range *)state, 1 );
	if( !id && lua_type( state, 1 ) != 1 )
		return 0;
	Object *object = TheGameLogic->findObjectByID( (ObjectID)id );
	if( !object )
		return 0;
	bool flag = Rva00990210Lookup( (Rva00990210Range *)state, 2 ) != 0;
	object->rva0028EBDA( flag );
	return 1;
}

// ?ObjectSetDelayedDeath@@YAHPAUlua_State@@@Z
// Retail 0x003353A9 115B. Reference-guided port of BFME1
// LuaScriptBindingsLuaA.cpp ObjectSetDelayedDeath (6583b3c1) with
// target-evidence adaptation: contain at +0x254 (donor +0x200) via v37
// slot 0x94 (Rva002E9F70Vtbl94::v37call in this TU). Identity proven by
// registration at 0x003386ED (push 0x7353A9 + lua_pushcclosure 0x747640 +
// literal 0xC0E530 'ObjectSetDelayedDeath' + lua_setglobal 0x747920);
// providers are all rowed (lua_gettop/lua_type/lookups/findObjectByID).
int ObjectSetDelayedDeath( lua_State *state )
{
	if( lua_gettop( state ) < 2 )
		return 0;
	unsigned id = Rva00990030Lookup( (Rva00990030Range *)state, 1 );
	if( !id && lua_type( state, 1 ) != 1 )
		return 0;
	Object *object = TheGameLogic->findObjectByID( (ObjectID)id );
	if( !object )
		return 0;
	bool delayed = Rva00990210Lookup( (Rva00990210Range *)state, 2 ) != 0;
	Rva002E9F70Vtbl94 *contain = *(Rva002E9F70Vtbl94 **)( (char *)object + 0x254 );
	if( !contain )
		return 0;
	contain->v37call( delayed );
	return 0;
}
