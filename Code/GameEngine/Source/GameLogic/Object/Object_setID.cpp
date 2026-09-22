// cl: /O1 /DNDEBUG /DWIN32 /MD /EHsc
//
// Retail 0x0028B532 (55B). Object unique-ID assignment with lookup-table
// maintenance. Transferred from the BFME1 reconstruction (BFME1 0x001BEC70,
// 55B, same Object.cpp TU family); the DEBUG_ASSERTCRASH compiles out under
// /DNDEBUG. m_id lives at +0x74; TheGameLogic at retail 0x00DFE78C.

enum ObjectID
{
	INVALID_ID = 0
};

class Object;

class ObjectLookupMap
{
public:
	class Object **findSlot( int *id );
};

class GameLogic
{
public:
	void removeObjectFromLookupTable( Object *obj );
	void addObjectToLookupTable( Object *obj );

private:
	unsigned char m_pad[0xB4];	// +0x00..0xB4
	ObjectLookupMap m_lookup;	// +0xB4
};

extern GameLogic *TheGameLogic;

class Object
{
public:
	int getID() const;

protected:
	void setID( ObjectID id );

private:
	unsigned char m_pre[0x74];	// +0x00..0x74
	int m_id;			// +0x74
};

void Object::setID( ObjectID id )
{
	// if id hasn't changed do nothing
	if( m_id == id )
		return;

	// remove this objects previous id from the lookup table
	if( m_id != INVALID_ID )
		TheGameLogic->removeObjectFromLookupTable( this );

	// assign new id
	m_id = id;

	// add new id to lookup table
	if( id != INVALID_ID )
		TheGameLogic->addObjectToLookupTable( this );
}

void GameLogic::addObjectToLookupTable( Object *obj )
{
	if( obj == 0 )
		return;
	int id = *(int *)((char *)obj + 0x74);
	Object **slot = m_lookup.findSlot( &id );
	*slot = obj;
}
