// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// BfmeThingDGD virtual at retail 0x007F8400, 452 bytes. The owner is proven
// by vtable 0x0112B800 slot 6, which the matched constructor 0x007F7FA0
// installs at this+0; that constructor also zeroes the +0x14..+0x30 words
// this body reads and writes. The method identity is not proven, so it
// keeps the address token.
//
// this+4 and this+8 carry the two secondary vtables the constructor writes
// (0x0112B7F8 and 0x0112B7F0), so the pointers handed out at those offsets
// are base conversions. The last store goes through a one-line inline
// setter: its by-value argument is what makes retail form this+8 in ecx
// ahead of the m_24 store on both arms of the duplicated return.
//
// The helper at 0x007EA4F0 ends in `jmp [edx+0x14]` with the stack
// untouched, forwarding its caller's single stack argument to the maker's
// slot 5; this body pushes its third argument for it.

#include <new>

class Rva007F0210;
extern Rva007F0210 bfmeRva0130A9D4TagSlot;	// 0x00E0A3EC
extern Rva007F0210 bfmeRva0130A9F8TagSlot;	// 0x00E0A410
extern Rva007F0210 bfmeRva0130AA58TagSlot;	// 0x00E0A470
extern Rva007F0210 bfmeRva0130AA7CTagSlot;	// 0x00E0A494
extern Rva007F0210 bfmeRva0130AA88TagSlot;	// 0x00E0A4A0
extern Rva007F0210 bfmeRva0130AAA0TagSlot;	// 0x00E0A4B8
extern Rva007F0210 bfmeRva0130AAACTagSlot;	// 0x00E0A4C4
extern Rva007F0210 bfmeRva0130AB00TagSlot;	// 0x00E0A518
extern Rva007F0210 bfmeRva0130AB18TagSlot;	// 0x00E0A530
extern Rva007F0210 bfmeRva0130AB24TagSlot;	// 0x00E0A53C
extern Rva007F0210 bfmeRva0130AB30TagSlot;	// 0x00E0A548

class Rva007E8810Message;
class BfmeDictESI;
class Rva007F7980Browser;
void Rva007F6FC0BrowserGameReply(Rva007E8810Message *value, Rva007F7980Browser *browser);

class Rva007F7980Browser
{
public:
	void onRegion( Rva007E8810Message * value );
	void onLobby( Rva007E8810Message * value );
	void onGame( Rva007E8810Message * value );
	void onPlayer( Rva007E8810Message * value );
	void rva007f63f0( void * value );
};

class BfmeHostESI
{
public:
	void bfmeApplyESI( BfmeDictESI * value );
};

class BfmeThingVJK
{
public:
	void bfmeGoVJK( int value );
};

class BfmeThingZI
{
public:
	void rva007F7640( Rva007E8810Message * value );
	void rva007F7DA0( Rva007E8810Message * value );
};

class BfmeHostBT
{
public:
	void Rva007F7C70( Rva007E8810Message * value );
};

// The reply handlers registered below: each is handed the reply and the owner
// registered with it and forwards the reply to one owner method. All ten
// callees are already matched; the handler names carry their own addresses.
void Rva00663690Handler( Rva007E8810Message * value, Rva007F7980Browser *owner )
{
	owner->onRegion( value );
}

void Rva006636A0Handler( Rva007E8810Message * value, Rva007F7980Browser *owner )
{
	owner->onLobby( value );
}

void Rva006636D0Handler( Rva007E8810Message * value, Rva007F7980Browser *owner )
{
	owner->onGame( value );
}

void Rva006636E0Handler( Rva007E8810Message * value, Rva007F7980Browser *owner )
{
	owner->onPlayer( value );
}

void Rva006636F0Handler( void * value, Rva007F7980Browser *owner )
{
	owner->rva007f63f0( value );
}

void Rva00663700Handler( BfmeDictESI * value, BfmeHostESI *owner )
{
	owner->bfmeApplyESI( value );
}

void Rva00663710Handler( int value, BfmeThingVJK *owner )
{
	owner->bfmeGoVJK( value );
}

void Rva00663FF0Handler( Rva007E8810Message * value, BfmeThingZI *owner )
{
	owner->rva007F7640( value );
}

void Rva00664A60Handler( Rva007E8810Message * value, BfmeThingZI *owner )
{
	owner->rva007F7DA0( value );
}

void Rva00664A70Handler( Rva007E8810Message * value, BfmeHostBT *owner )
{
	owner->Rva007F7C70( value );
}

class Rva0112B800Base
{
public:
	virtual void slot0();
};

class Rva0112B7F8Base
{
public:
	virtual void slot0();
};

class Rva0112B7F0Base
{
public:
	virtual void slot0();
};

struct BfmeOwnerUNC;
class BfmeOwnerAEB;
struct Rva00800920Host;

class BfmeThingRE
{
public:
	void bfmeRunRE( void *value );
};

class Rva007EADC0Owner
{
public:
	void send();
};

class Rva007F8400Node
{
public:
	virtual void v0( int value );
	virtual Rva007F8400Node *v1();
	virtual void v2();
	virtual void v3( void *value, int flag );
	virtual void v4( void *table, void *helper, void *owner );

	unsigned char m_pad[ 0x6a4 ];
	Rva007F8400Node *m_6a8;
};

class Rva00803890Owner
{
public:
	Rva00803890Owner( unsigned char value, BfmeOwnerUNC *owner );
};

class BfmeThingAEB
{
public:
	void bfmeStartAEB( BfmeOwnerAEB *owner );
};

class Rva00803080
{
public:
	Rva00803080 &set( int value );
	void initPool();
};

class Rva00800920Owner
{
public:
	Rva00800920Owner( Rva00800920Host *host );

	void set0c( Rva0112B7F0Base *value ) { m_0c = value; }

	unsigned char m_pad[ 0x0c ];
	Rva0112B7F0Base *m_0c;
};

class Gen007F0130
{
public:
	static void *operator new( unsigned int size );
};

class BfmeThingDGD : public Rva0112B800Base, public Rva0112B7F8Base, public Rva0112B7F0Base
{
public:
	void rva007F8400( unsigned char arg34, int arg35, void *forwarded );

	void *m_0c;
	Rva007F8400Node *m_10;
	Rva007F8400Node *m_14;
	Rva00803890Owner *m_18;
	Rva007F8400Node *m_1c;
	Rva00803080 *m_20;
	Rva00800920Owner *m_24;
	unsigned m_28;
	unsigned m_2c;
	unsigned m_30;
	unsigned char m_34;
	unsigned char m_35;
};

// ?rva007F8400@BfmeThingDGD@@QAEXEHPAX@Z
void BfmeThingDGD::rva007F8400( unsigned char arg34, int arg35, void *forwarded )
{
	if( m_30 != 0 )
	{
		m_1c->v0( -105 );
		return;
	}

	unsigned char byte35 = (unsigned char)arg35;
	m_34 = arg34;
	m_30 = 1;
	m_35 = byte35;
	((BfmeThingRE *)m_0c)->bfmeRunRE( forwarded );
	m_14 = m_10->v1();
	m_14->m_6a8->v3( static_cast< Rva0112B7F8Base * >( this ), 0 );
	m_14->v4( (void *)&bfmeRva0130A9D4TagSlot, (void *)Rva00663690Handler, this );
	m_14->v4( (void *)&bfmeRva0130A9F8TagSlot, (void *)Rva006636A0Handler, this );
	m_14->v4( (void *)&bfmeRva0130AAACTagSlot, (void *)Rva007F6FC0BrowserGameReply, this );
	m_14->v4( (void *)&bfmeRva0130AAA0TagSlot, (void *)Rva006636D0Handler, this );
	m_14->v4( (void *)&bfmeRva0130AA58TagSlot, (void *)Rva006636E0Handler, this );
	m_14->v4( (void *)&bfmeRva0130AB18TagSlot, (void *)Rva006636F0Handler, this );
	m_14->v4( (void *)&bfmeRva0130AB30TagSlot, (void *)Rva00664A60Handler, this );
	m_14->v4( (void *)&bfmeRva0130AB00TagSlot, (void *)Rva00663FF0Handler, this );
	m_14->v4( (void *)&bfmeRva0130AB24TagSlot, (void *)Rva00663700Handler, this );
	m_14->v4( (void *)&bfmeRva0130AA88TagSlot, (void *)Rva00663710Handler, this );
	m_14->v4( (void *)&bfmeRva0130AA7CTagSlot, (void *)Rva00664A70Handler, this );

	if( byte35 != 0 )
	{
		Rva00803890Owner *node = new (Gen007F0130::operator new( 0x1c )) Rva00803890Owner( arg34, (BfmeOwnerUNC *)this );
		m_18 = node;
		((BfmeThingAEB *)node)->bfmeStartAEB( (BfmeOwnerAEB *)m_14 );
	}

	if( arg34 )
		((Rva007EADC0Owner *)m_0c)->send();

	Rva00803080 *pool = (Rva00803080 *)Gen007F0130::operator new( 0x14 );
	if( pool != 0 )
		pool = &pool->set( (int)this );
	else
		pool = 0;
	m_20 = pool;
	pool->initPool();

	m_24 = new (Gen007F0130::operator new( 0x1f8 )) Rva00800920Owner( (Rva00800920Host *)this );
	m_24->set0c( this );
}
