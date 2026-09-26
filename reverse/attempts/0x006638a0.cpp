// ?rva006638A0@BfmeThingDGD@@QAEXHH@Z
// partial score=0.91 date=2026-09-26
// ?rva006638A0@BfmeThingDGD@@QAEXHH@Z
// partial score=0.91 date=2026-09-26
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// ?rva006638A0@BfmeThingDGD@@QAEXHH@Z, retail 0x006638A0, 286 bytes.
// Virtual slot 22 (offset 0x58) of vtable 0x008E3018 (VA 0x00CE3018), class of
// ??0BfmeThingDGD@@QAE@PAX@Z in BfmeThingDGDConstructor.cpp. Finds a free
// 0x94-byte child at this+0x58 (flag at +8), initializes its buffer at +0x1c
// via Rva00800290Buffer::append of the empty string at 0x00BBAC1C, stores the
// two int args at +0x28/+0x24 with match flag at +0x14, notifies the +0x1c
// sink, then sends BfmeMsgVJH (buffer at this+0x2dc size 0x400) via +0x10 slot
// 0x38 and +0x14 slot 8 with callback 0x006620A0. Layout matches
// BfmeThingDGDDestructor.cpp; callees append/ctor/dtor already rowed.

class Rva00800290Buffer
{
public:
	void append( const char *text );

	char *m_ptr;
	int m_size;
};

class BfmeMsg
{
public:
	BfmeMsg();
	virtual ~BfmeMsg();

protected:
	int m_state;
};

class BfmeMsgVJH : public BfmeMsg
{
public:
	BfmeMsgVJH( char *buffer, int size ) throw();

private:
	int m_field08;
	int m_field0C;
	char *m_buffer;
	int m_size;
	int m_field18;
	int m_field1C;
	int m_field20;
	int m_field24;
	int m_field28;
	int m_count;
	char m_flag;
	char m_pad31[ 3 ];
};

void __cdecl Rva006620A0Callback( void *a, void *b );

class Rva006638A01C
{
public:
	virtual void v00() throw();
	virtual void v04() throw();
	virtual void v08() throw();
	virtual void v0c() throw();
	virtual void v10() throw();
	virtual void v14() throw();
	virtual void v18() throw();
	virtual void v1c() throw();
	virtual void v20() throw();
	virtual void v24() throw();
	virtual void v28() throw();
	virtual void onSlot2C( void *p, int v ) throw();
};

class Rva006638A02D8
{
public:
	virtual void v00() throw();
	virtual void v01() throw();
	virtual void v02() throw();
	virtual void v03() throw();
	virtual void v04() throw();
	virtual void v05() throw();
	virtual void v06() throw();
	virtual void v07() throw();
	virtual void v08() throw();
	virtual int *get9( int *key ) throw();
	virtual int *get10( int *key ) throw();
};

class Rva006638A010
{
public:
	virtual void v00() throw();
	virtual void v04() throw();
	virtual void v08() throw();
	virtual void v0c() throw();
	virtual void v10() throw();
	virtual void v14() throw();
	virtual void v18() throw();
	virtual void v1c() throw();
	virtual void v20() throw();
	virtual void v24() throw();
	virtual void v28() throw();
	virtual void v2c() throw();
	virtual void v30() throw();
	virtual void v34() throw();
	virtual void send( BfmeMsgVJH *msg, int a1, int a2, int sel ) throw();
};

class Rva006638A014
{
public:
	virtual void v00() throw();
	virtual void v04() throw();
	virtual void send( BfmeMsgVJH *msg, void (__cdecl *cb)( void *, void * ), void *owner, int value ) throw();
};

class Rva007F6D60ZeroWord
{
public:
	Rva007F6D60ZeroWord() : m_value( 0 ) {}

	unsigned m_value;
};

class Rva007F6D60Member2C
{
public:
	Rva007F6D60Member2C();

	unsigned char m_data[ 0x10 ];
};

class Rva007F4DA0Member3C
{
public:
	Rva007F4DA0Member3C();

	unsigned char m_data[ 0x28 ];
};

class Rva007F6D60ChildBase
{
public:
	virtual ~Rva007F6D60ChildBase();
};

class Rva007F6D60Child : public Rva007F6D60ChildBase
{
public:
	unsigned m_04;
	unsigned m_08;
	unsigned m_0c;
	unsigned m_10;
	unsigned char m_14;
	unsigned char m_pad15[ 3 ];
	Rva007F6D60ZeroWord m_18;
	Rva00800290Buffer m_buffer1C;
	Rva007F6D60ZeroWord m_24holder;
	unsigned m_28;
	Rva007F6D60Member2C m_chain2C;
	Rva007F4DA0Member3C m_chain3C;
	unsigned char m_pad64[ 8 ];
	unsigned char m_6c;
	unsigned char m_pad6D[ 0x27 ];
};

class Rva007F8090Base
{
public:
	unsigned m_v0;
	unsigned m_v4;
	unsigned m_v8;
};

class BfmeThingDGD : public Rva007F8090Base
{
public:
	void rva006638A0( int a1, int a2 );

	unsigned m_0c;											///< +0x0c
	Rva006638A010 *m_10;									///< +0x10 sender slot 0x38
	Rva006638A014 *m_14ptr;									///< +0x14 notifier slot 8
	unsigned m_18;											///< +0x18 unused
	Rva006638A01C *m_1c;									///< +0x1c sink slot 0x2c
	unsigned m_20;											///< +0x20
	unsigned m_24;											///< +0x24
	unsigned m_28val;										///< +0x28
	unsigned m_2cval;										///< +0x2c
	unsigned m_30;											///< +0x30
	unsigned char m_34;
	unsigned char m_35;
	unsigned char m_36;
	unsigned char m_37;
	unsigned char m_38data[ 0x10 ];							///< +0x38
	unsigned char m_48data[ 0x10 ];							///< +0x48
	Rva007F6D60Child m_children[ 4 ];						///< +0x58
	unsigned char m_2a8data[ 0x18 ];						///< +0x2a8
	unsigned m_2c0;
	unsigned m_2c4;
	unsigned m_2c8;
	unsigned m_2cc;
	unsigned m_2d0;
	unsigned m_2d4;
	Rva006638A02D8 *m_2d8;									///< +0x2d8
	char m_tail[ 0x400 ];									///< +0x2dc
	unsigned m_6dc;											///< +0x6dc
};

// ?rva006638A0@BfmeThingDGD@@QAEXHH@Z present-unmatched
void BfmeThingDGD::rva006638A0( int a1, int a2 )
{
	Rva007F6D60Child *slot = m_children;
	Rva007F6D60Child *end = (Rva007F6D60Child *)( (char *)this + 0x2a8 );

	for( ; slot < end; ++slot )
	{
		if( slot->m_08 == 0 )
			goto found;
	}

	m_1c->onSlot2C( 0, -101 );
	return;

found:
	slot->m_04 = (unsigned)this;

	unsigned char flag = 0;
	if( m_2d8 != 0 )
	{
		int *p1 = m_2d8->get9( &a2 );
		if( *p1 == a1 )
		{
			int *p2 = m_2d8->get10( &a2 );
			if( *p2 == a2 )
				flag = 1;
		}
	}

	slot->m_08 = 0;
	slot->m_0c = 0;
	slot->m_10 = 0;
	slot->m_14 = 0;
	slot->m_18.m_value = 0;
	slot->m_buffer1C.append( "" );
	slot->m_6c = 0;
	slot->m_28 = (unsigned)a1;
	slot->m_24holder.m_value = (unsigned)a2;
	slot->m_08 = 1;
	slot->m_14 = flag;

	m_1c->onSlot2C( slot, 0 );

	BfmeMsgVJH msg( m_tail, 0x400 );
	int sel = (int)m_2cval;
	if( sel == 0 )
		sel = (int)m_28val;
	m_10->send( &msg, a1, a2, sel );
	m_14ptr->send( &msg, Rva006620A0Callback, slot, (int)m_6dc );
}
