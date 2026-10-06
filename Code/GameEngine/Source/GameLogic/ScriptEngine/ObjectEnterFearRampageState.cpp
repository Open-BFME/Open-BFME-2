// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Two adjacent Lua object-state callbacks: ObjectEnterFearState 0x00337092
// (153B) and ObjectEnterRampageState 0x0033712B (134B).
// TARGET FACTS: each body is named by its registration (Fear 0x00338554,
// Rampage 0x003385E1), lua_pushcclosure
// (row @0x00747640) of the body's address followed by lua_setglobal (row
// @0x00747920) of the name string. Both resolve objects with the rowed
// Rva00990030Lookup / lua_type / findObjectByID sequence, then drive the
// object's AIUpdateInterface (Object +0x258) through the rowed command
// helpers on its +0x20 command interface: 0x00336B23 (object, source) and
// 0x00336B88 (source). Rampage first refuses an object whose physics
// (Object +0x25C) has its +0x5C flag set, calls slot 0x94 of the body module
// (Object +0x254) with 1, and leaves a temporary AI state through the rowed
// 0x002632C7 / 0x002632E1 pair.
// DONOR FACTS: Open-BFME-1 (6583b3c1) registers both names but holds no
// body; the body-module slot 0x94 view is the one ObjectSetDelayedDeath's
// TU (LuaObjectModelConditionEnragedDelayedDeath.cpp) already calls.
// Nothing here names the +0x3C4 AI flag or the physics +0x5C flag.

struct lua_State;
extern "C" int lua_type( lua_State *state, int index );

struct Rva00990030Range;
unsigned Rva00990030Lookup( Rva00990030Range *range, int index );

struct Rva00990210Range;
unsigned Rva00990210Lookup( Rva00990210Range *range, int index );

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1
};

class Rva00336B23
{
public:
	void rva00336B23( void *obj, CommandSourceType cmdSource );
};

class Rva00336B88
{
public:
	void rva00336B88( CommandSourceType cmdSource );
};

// Retail returns the predicate in al (the caller tests al); the row keeps
// the int spelling, so the byte view truncates rather than converting.
class AIUpdateInterface
{
public:
	int rva002632C7( void ) const;
	void rva002632E1( void );
	unsigned char rva002632C7Bool( void ) const { return (unsigned char)rva002632C7(); }

	char m_pad00[0x20];
	char m_commandInterface[0x3C4 - 0x20];	// +0x20, this of the command helpers
	bool m_flag3C4;	// +0x3C4, set from Fear's third argument
};

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

class PhysicsBehavior
{
public:
	char m_pad00[0x5C];
	bool m_5C;	// +0x5C
};

class Object
{
public:
	char m_pad000[0x254];
	Rva002E9F70Vtbl94 *m_body;	// +0x254
	AIUpdateInterface *m_ai;	// +0x258
	PhysicsBehavior *m_physics;	// +0x25C
};

class GameLogic
{
public:
	Object *findObjectByID( ObjectID id );
};

extern GameLogic *TheGameLogic;

// ?ObjectEnterFearState@@YAHPAUlua_State@@@Z
int ObjectEnterFearState( lua_State *state )
{
	unsigned id = Rva00990030Lookup( (Rva00990030Range *)state, 1 );
	if( !id && lua_type( state, 1 ) != 1 )
		return 0;
	Object *object = TheGameLogic->findObjectByID( (ObjectID)id );
	if( !object )
		return 0;
	unsigned sourceID = Rva00990030Lookup( (Rva00990030Range *)state, 2 );
	// Retail checks argument 1 again here, not argument 2.
	if( !sourceID && lua_type( state, 1 ) != 1 )
		return 0;
	Object *source = TheGameLogic->findObjectByID( (ObjectID)sourceID );
	if( !source )
		return 0;
	bool flag = Rva00990210Lookup( (Rva00990210Range *)state, 3 ) != 0;
	AIUpdateInterface *ai = object->m_ai;
	if( ai )
	{
		((Rva00336B23 *)ai->m_commandInterface)->rva00336B23( source, CMD_FROM_SCRIPT );
		ai->m_flag3C4 = flag;
	}
	return 0;
}

// ?ObjectEnterRampageState@@YAHPAUlua_State@@@Z
int ObjectEnterRampageState( lua_State *state )
{
	unsigned id = Rva00990030Lookup( (Rva00990030Range *)state, 1 );
	if( !id && lua_type( state, 1 ) != 1 )
		return 0;
	Object *object = TheGameLogic->findObjectByID( (ObjectID)id );
	if( !object )
		return 0;
	PhysicsBehavior *physics = object->m_physics;
	if( physics && physics->m_5C )
		return 0;
	Rva002E9F70Vtbl94 *body = object->m_body;
	if( !body )
		return 0;
	body->v37call( true );
	AIUpdateInterface *ai = object->m_ai;
	if( ai )
	{
		if( ai->rva002632C7Bool() )
			ai->rva002632E1();
		((Rva00336B88 *)ai->m_commandInterface)->rva00336B88( CMD_FROM_SCRIPT );
	}
	return 0;
}
