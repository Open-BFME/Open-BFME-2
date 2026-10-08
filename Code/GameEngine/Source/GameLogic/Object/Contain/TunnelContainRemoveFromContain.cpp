// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Retail 0x0047DC88, 87B: TunnelContain::removeFromContain, entered through
// the contain interface at TunnelContain+0x20 (object this-0x18, primary
// vtable this-0x20).
// Body: Zero Hour's TunnelContain::removeFromContain (GeneralsMD GameEngine/
// Source/GameLogic/Object/Contain/TunnelContain.cpp) reshaped for BFME 2:
// the onRemoving/onRemovedFrom notifications are the inherited body
// 0x00479DCD (called on the same interface), then, with a controlling
// player, the object is removed from the player's tunnel tracker (+0x2E8)
// when primary slot 0x80 reports it or the tracker says it is contained
// (0x004F550A); TunnelTracker::removeFromContain is 0x004F54BF. The tracker
// methods are rowed with ObjectID parameters while retail passes the Object
// pointer, hence the casts.

typedef bool Bool;

enum ObjectID
{
	INVALID_ID = 0
};

class Object;

class TunnelTracker
{
public:
	Bool rva004F550A( ObjectID id );
	void removeFromContain( ObjectID id, int exposeStealthUnits );
};

class Player
{
public:
	TunnelTracker *getTunnelSystem() const { return m_tunnelSystem; }
	unsigned char m_pad00[0x2E8];
	TunnelTracker *m_tunnelSystem;
};

class Object
{
public:
	Player *getControllingPlayer() const;
};


class TunnelContainPrimary
{
public:
	virtual void primarySlot00();
	virtual void primarySlot01();
	virtual void primarySlot02();
	virtual void primarySlot03();
	virtual void primarySlot04();
	virtual void primarySlot05();
	virtual void primarySlot06();
	virtual void primarySlot07();
	virtual void primarySlot08();
	virtual void primarySlot09();
	virtual void primarySlot0A();
	virtual void primarySlot0B();
	virtual void primarySlot0C();
	virtual void primarySlot0D();
	virtual void primarySlot0E();
	virtual void primarySlot0F();
	virtual void primarySlot10();
	virtual void primarySlot11();
	virtual void primarySlot12();
	virtual void primarySlot13();
	virtual void primarySlot14();
	virtual void primarySlot15();
	virtual void primarySlot16();
	virtual void primarySlot17();
	virtual void primarySlot18();
	virtual void primarySlot19();
	virtual void primarySlot1A();
	virtual void primarySlot1B();
	virtual void primarySlot1C();
	virtual void primarySlot1D();
	virtual void primarySlot1E();
	virtual void primarySlot1F();
	virtual int primarySlot20( Object *obj );
protected:
	Object *getObject() const { return m_object; }
private:
	const void *m_moduleData;
	Object *m_object;
	unsigned char m_pad0C[0x20 - 0x0C];
};

// The contain interface at +0x20; its inherited removeFromContain body is
// the rowed 0x00479DCD (address-named class and method as rowed).
class Rva00479DCD
{
public:
	virtual void removeFromContain( Object *obj, int exposeStealthUnits ) = 0;
	void rva00479DCD( Object *obj, int exposeStealthUnits );
};

class TunnelContain : public TunnelContainPrimary, public Rva00479DCD
{
public:
	virtual void removeFromContain( Object *obj, int exposeStealthUnits );
};

void TunnelContain::removeFromContain( Object *obj, int exposeStealthUnits )
{
	rva00479DCD( obj, exposeStealthUnits );

	Player *owningPlayer = getObject()->getControllingPlayer();
	if( owningPlayer == 0 )
		return;

	if( primarySlot20( obj ) == 0 && !owningPlayer->getTunnelSystem()->rva004F550A( (ObjectID)(int)obj ) )
		return;

	owningPlayer->getTunnelSystem()->removeFromContain( (ObjectID)(int)obj, exposeStealthUnits );
}
