// Two walks over stored things: a search through four fixed entries, and a pass
// writing a value into every row whose mark is set.

// cl: /GS

struct BfmeEntryZI
{
	unsigned char m_bfmeHead[8];		// 0x00
	int m_bfmeUsed;				// 0x08
	unsigned char m_bfmeBody[0x18];		// 0x0c
	int m_bfmeOther;			// 0x24
	int m_bfmeKey;				// 0x28
	unsigned char m_bfmeTail[0x68];		// 0x2c
};

class BfmeThingZI
{
public:
	__declspec( noinline ) BfmeEntryZI *bfmeFindZI(int key, int other);
	void rva007F7DA0(class Rva007E8810Message *msg);

private:
	unsigned char m_bfmeHead[0x58];		// 0x000
	BfmeEntryZI m_bfmeEntries[4];		// 0x058
};

BfmeEntryZI *BfmeThingZI::bfmeFindZI(int key, int other)
{
	BfmeEntryZI *at = m_bfmeEntries;
	BfmeEntryZI *end = m_bfmeEntries + 4;

	while (at < end)
	{
		if (at->m_bfmeUsed != 0 && at->m_bfmeKey == key && at->m_bfmeOther == other)
			return at;

		++at;
	}

	return 0;
}

struct BfmeGridZJ
{
	unsigned char m_bfmeHead[0xc];		// 0x0c
	int m_bfmeValue;			// 0x0c
	unsigned char m_bfmeGap[8];		// 0x10
	unsigned char *m_bfmeRows;		// 0x18
	int m_bfmeStride;			// 0x1c
	unsigned char m_bfmeMask;		// 0x20
	unsigned char m_bfmeSpare[3];		// 0x21
	int *m_bfmeOut;				// 0x24
	unsigned char m_bfmeTail[0x64];		// 0x28
	unsigned int m_bfmeCount;		// 0x8c
};

void bfmeFillZJ(BfmeGridZJ *grid)
{
	unsigned int i = 0;
	int value = grid->m_bfmeValue;

	while (i < grid->m_bfmeCount)
	{
		unsigned char mark = grid->m_bfmeRows[grid->m_bfmeStride * i];

		if ((grid->m_bfmeMask & mark) != 0)
			grid->m_bfmeOut[i] = value;

		++i;
	}
}

#include <string.h>

class Rva007E8810Message;

void Rva007E8640Copy( char *destination, unsigned size, const char *source );

class Rva007FC020Ticket
{
public:
	Rva007FC020Ticket( Rva007E8810Message *msg );

	int m_lid;
	int m_gid;
	int m_pid;
	int m_p;
	char m_ticket[ 0x80 ];
	char m_reason[ 0x100 ];
	char m_i[ 0x20 ];
	char m_host[ 0x20 ];
	char m_platform[ 0x10 ];
	char m_ugid[ 0x25 ];
};

class Rva00800290Buffer
{
public:
	void append( const char *text );

	char *m_ptr;
	int m_size;
};

class BfmeOwnerYA
{
public:
	void bfmeParseYA( const char *text );

	char m_pad[ 0x68 ];
	int m_value;
};

class Rva007E8760Addr
{
public:
	void parse( const char *text, int extra );

	char m_pad[ 8 ];
	unsigned m_address;
	int m_extra;
};

class BfmeE1029
{
public:
	void bfmeGo1029E( char *text, int value );

	char m_pad[ 8 ];
	char m_text[ 0x1c ];
	int m_value;
};

class BfmeListenerZI
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual void v10();
	virtual void onEntry( BfmeEntryZI *entry, int value );
};

class Rva007EB810Diag
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void fail( const char *expression, const char *file, int line );
};

extern int Rva007EB810Get();

class Rva00800920Owner
{
public:
	int rva00800a40( void *input, unsigned char flag, int value );
};

// ?rva007F7DA0@BfmeThingZI@@QAEXPAVRva007E8810Message@@@Z
// Grafted into the bfmeFindZI home TU: the caller needs its callee defined
// in-TU for retail's register coloring (lid in ebp, no redundant mov).
void BfmeThingZI::rva007F7DA0( Rva007E8810Message *msg )
{
	BfmeThingZI *self = this;
	Rva007FC020Ticket ticket( msg );
	int lid = ticket.m_lid;
	BfmeEntryZI *entry = self->bfmeFindZI( lid, ticket.m_gid );

	if( entry == 0 )
	{
		((Rva007EB810Diag *)Rva007EB810Get())->fail(
			"peri",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\gamebrowser\\gamebrowser.cpp",
			0x59f );
	}
	else
	{
		int ticketLength = strlen( ticket.m_ticket );
		if( ticketLength == 0 )
		{
			entry->m_bfmeUsed = 0;
			((BfmeOwnerYA *)entry)->bfmeParseYA( ticket.m_reason );
			(*(BfmeListenerZI **)((char *)self + 0x1c))->onEntry( entry, 0x6a64656e );
			entry->m_bfmeUsed = 0;
			*(int *)((char *)entry + 0x0c) = 0;
			*(int *)((char *)entry + 0x10) = 0;
			*(unsigned char *)((char *)entry + 0x14) = 0;
			*(int *)((char *)entry + 0x18) = 0;
			((Rva00800290Buffer *)((char *)entry + 0x1c))->append( (const char *)0x00BBAC1C );
			entry->m_bfmeOther = 0;
			entry->m_bfmeKey = 0;
			*(char *)((char *)entry + 0x6c) = 0;
		}
		else
		{
			bool notifyOwner;
			if( *(unsigned char *)((char *)entry + 0x14) == 0 )
			{
				notifyOwner = true;
				if( lid == -2 )
					notifyOwner = false;
			}
			else
				notifyOwner = false;

			entry->m_bfmeUsed = 4;
			*(int *)((char *)entry + 0x18) = ticket.m_pid;
			((Rva00800290Buffer *)((char *)entry + 0x1c))->append( ticket.m_ticket );
			Rva007E8640Copy( (char *)entry + 0x6c, 0x25, ticket.m_ugid );

			if( ticket.m_host[ 0 ] != 0 )
			{
				((BfmeE1029 *)( (char *)entry + 0x3c ))->bfmeGo1029E(
					ticket.m_host, ticket.m_p );
				*(void **)((char *)entry + 0x64) = (void *)((char *)entry + 0x3c);
			}
			else
			{
				((Rva007E8760Addr *)( (char *)entry + 0x2c ))->parse(
					ticket.m_i, ticket.m_p );
				*(void **)((char *)entry + 0x64) = (void *)((char *)entry + 0x2c);
			}
			if( !notifyOwner )
			{
				entry->m_bfmeUsed = 5;
				(*(BfmeListenerZI **)((char *)self + 0x1c))->onEntry( entry, 0 );
			}
			else
			{
				(*(BfmeListenerZI **)((char *)self + 0x1c))->onEntry( entry, 0 );
				(*(Rva00800920Owner **)((char *)self + 0x24))->rva00800a40(
					*(void **)((char *)entry + 0x64), 1, (int)entry );
			}
		}
	}
}
