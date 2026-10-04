// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Lua binding bodies ported from Open-BFME-1's
// GameLogic/ScriptEngine/LuaScriptBindingsLuaA.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way both bodies place uniquely on unclaimed game.dat .text by masked
// whole-.text search, and ./build.sh reproduces them byte for byte:
// ObjectDispatchEvent 0x0033594A (279B) and the object-describe binding
// 0x00334DDF (114B; the donor's address-derived name is re-keyed to its BFME 2
// address). Callee addresses are read off retail's call sites; several callee
// names are the donor's own address-derived or view names. Only these bodies
// are carried.
// Open-BFME7: Lua script bindings lane "luaA" (cdecl int f(lua_State*)).
// Address-derived names where the real ZH identity is unknown.

struct lua_State;
extern "C" int lua_gettop( lua_State *state );
extern "C" int lua_type( lua_State *state, int index );
extern "C" const char *lua_tostring( lua_State *state, int index );
extern "C" void lua_pushnil( lua_State *state );

unsigned Rva00990030Lookup( lua_State *range, int index );

extern "C" char _bfmeString10CF498[];

struct Coord3D
{
	float x, y, z;
};

class Rva002E9F70CommandIface
{
public:
	void j_000186e7( int arg );
};

class BfmeAI956
{
public:
	int bfmeKind956( void );
	bool j_0004a057( void );
	void j_000486fd( void );

	char m_unreconstructed00[ 0x20 ];
	Rva002E9F70CommandIface m_cmdAt20;
};

struct Rva002E5FF0Field23C
{
	char m_unreconstructed00[ 4 ];
	void *m_field4;
};

class ThingTemplate;

class Object
{
public:
	bool getAttributeModifierBonus( int type, float *bonus ) const;

	void *m_vftable;
	ThingTemplate *m_thingTemplate;
	char m_unreconstructed08[ 0x1F8 ];
	void *m_at200;
	BfmeAI956 *m_ai;
	void *m_at208;
	char m_unreconstructed20c[ 0x23c - 0x20c ];
	Rva002E5FF0Field23C *m_team;
};

class GameLogic
{
public:
	Object *findObjectByID( int id );
};

extern GameLogic *TheGameLogic;

int GetGameLogicRandomValue( int lo, int hi, const char *file, int line );

struct BfmeQ1039;
void bfmeGo1039E( BfmeQ1039 *q, int v );


extern "C" void lua_pushstring( lua_State *state, const char *str );
extern "C" const char g_bfmeEmptyAscii[];

struct Rva002E5FF0Str
{
	void *m_data;
};

extern Rva002E5FF0Str Rva01336E50Str;


int bfmeLookup_001c62b0( void *name );


class Rva002E9F70Vtbl94
{
public:
	virtual void v0( void ) {}
	virtual void v1( void ) {}
	virtual void v2( void ) {}
	virtual void v3( void ) {}
	virtual void v4( void ) {}
	virtual void v5( void ) {}
	virtual void v6( void ) {}
	virtual void v7( void ) {}
	virtual void v8( void ) {}
	virtual void v9( void ) {}
	virtual void v10( void ) {}
	virtual void v11( void ) {}
	virtual void v12( void ) {}
	virtual void v13( void ) {}
	virtual void v14( void ) {}
	virtual void v15( void ) {}
	virtual void v16( void ) {}
	virtual void v17( void ) {}
	virtual void v18( void ) {}
	virtual void v19( void ) {}
	virtual void v20( void ) {}
	virtual void v21( void ) {}
	virtual void v22( void ) {}
	virtual void v23( void ) {}
	virtual void v24( void ) {}
	virtual void v25( void ) {}
	virtual void v26( void ) {}
	virtual void v27( void ) {}
	virtual void v28( void ) {}
	virtual void v29( void ) {}
	virtual void v30( void ) {}
	virtual void v31( void ) {}
	virtual void v32( void ) {}
	virtual void v33( void ) {}
	virtual void v34( void ) {}
	virtual void v35( void ) {}
	virtual void v36( void ) {}
	virtual void v37call( bool arg ) {}
};


// class-gate: allow AsciiString the donor's out-of-line dtor/op= view over a StringBase<char> base whose C-string ctor retail calls at 0x00037BA0 (AsciiString's own const char * ctor, 0x0000654A, only forwards to it); dtor and op= are called at 0x00036410 and 0x000366F0, and both placed bodies are byte-exact under it
template <typename T>
class StringBase
{
public:
	StringBase() { m_data = 0; }
	StringBase( const T *text );

	void *m_data;
};

class AsciiString : public StringBase<char>
{
public:
	AsciiString() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	~AsciiString();
	AsciiString &operator=( const AsciiString &text );
	const char *str() const
	{
		return m_data ? (const char *)m_data + 8 : g_bfmeEmptyAscii;
	}

};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	void *m_vftable;
	Overridable *m_nextOverride;
	Overridable *getFinalOverride();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
public:
	char m_pad08[ 0x18 ];
	AsciiString m_name;
};


AsciiString DescribeObject( const Object *object );

// ?Rva00334DDFObjectDescribe@@YAHPAUlua_State@@@Z
int Rva00334DDFObjectDescribe( lua_State *state )
{
	unsigned id = Rva00990030Lookup( state, 1 );
	if( !id && lua_type( state, 1 ) != 1 )
	{
		lua_pushnil( state );
		return 1;
	}
	Object *object = TheGameLogic->findObjectByID( id );
	AsciiString result = DescribeObject( object );
	lua_pushstring( state, result.m_data ? (const char *)result.m_data + 8 : g_bfmeEmptyAscii );
	return 1;
}

unsigned Rva00990210Lookup( lua_State *range, int index );

class Rva002E6B70Object : public Object
{
public:
	// The retail call is through ILT RVA 0x0001E33F to body RVA 0x001C1EA0.
	// Its public Object method name is not recovered; the body references the
	// EnragedBehavior module literal, so retain an address-derived ABI view.
	void Rva001E33FSetBool( bool flag );
};


class Rva002E6A00Object : public Object
{
public:
	// The retail call is through ILT RVA 0x0001ED6C to body RVA 0x001CF8F0.
	// The public Object method name is not recovered; retain an address-derived
	// ABI view for the ObjectSetChanting binding.
	void Rva001ED6CSetBool( bool flag );
};


typedef unsigned NameKeyType;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey( const char *name );
};

extern NameKeyGenerator *TheNameKeyGenerator;

struct BfmeDelayedLuaEvent
{
	unsigned char m_data[0x18];
};

struct BfmeDelayedLuaEventList
{
	BfmeDelayedLuaEventList();
	~BfmeDelayedLuaEventList();

	void *m_vtable;
	BfmeDelayedLuaEvent m_events[3];
};

struct BfmeDispatchDelayedLuaEvent
{
	void *m_vtable;
	float m_number;
	unsigned char m_boolean;
	unsigned char m_padding[3];
	unsigned m_objectID;
	AsciiString m_string;
	unsigned m_type;
};

struct LuaDrawableState
{
	unsigned char m_data[0x78];
};

extern LuaDrawableState *g_rva00A01DBCLuaState;

struct BfmeCallJ63
{
	void *invoke( void *event );
};

struct BfmeObjectEventDispatch
{
	// The second argument is an Object pointer here.  Retail's dispatcher
	// consumes its +0x204 module field; the horde sibling supplies the same
	// slot from its member-pointer list.
	void invoke( void *event, void *object, BfmeDelayedLuaEventList *eventList );
};

// In BFME 1 the binding registration pairs ObjectDispatchEvent with a thunk
// that jumps directly to this body.  The body uses
// the delayed-event list's established three-record layout: record zero is an
// object-ID value (type 3), and record one is a copied string (type 4).
// ?ObjectDispatchEvent@@YAHPAUlua_State@@@Z
int ObjectDispatchEvent( lua_State *state )
{
	unsigned objectID = Rva00990030Lookup( state, 1 );
	if( !objectID && lua_type( state, 1 ) != 1 )
		return 0;
	Object *object = TheGameLogic->findObjectByID( objectID );
	if( !object )
		return 0;

	BfmeDelayedLuaEventList eventList;
	unsigned eventID = Rva00990030Lookup( state, 2 );
	if( !eventID && lua_type( state, 1 ) != 1 )
		return 0;
	const char *eventName = lua_tostring( state, 3 );
	if( !eventName )
		return 0;

	NameKeyType eventKey = TheNameKeyGenerator->nameToKey( eventName );
	void *eventData = reinterpret_cast<BfmeCallJ63 *>(g_rva00A01DBCLuaState)->invoke(
		(void *)eventKey);
	if( eventData )
	{
		const char *text = lua_tostring( state, 4 );
		BfmeDispatchDelayedLuaEvent *events =
			reinterpret_cast<BfmeDispatchDelayedLuaEvent *>( &eventList.m_events[0] );
		events[0].m_objectID = eventID;
		events[0].m_type = 3;
		{
			AsciiString value( text );
			events[1].m_string = value;
			events[1].m_type = 4;
		}
		reinterpret_cast<BfmeObjectEventDispatch *>(g_rva00A01DBCLuaState)->invoke(
			eventData, object, &eventList);
	}

	return 0;
}

extern "C" void lua_pushnumber( lua_State *state, double value );

#pragma intrinsic( _ReadWriteBarrier )
extern "C" void _ReadWriteBarrier( void );

class LuaScriptEngine;
extern LuaScriptEngine *TheLuaScriptEngine;
extern double g_bfmeSubB3;

