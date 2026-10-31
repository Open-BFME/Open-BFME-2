// flags: region default (reverse/retail_inventory/flag_regions.csv)
// 0x007F7640: BfmeThingZI FESL game-browser entry reply handler.
//
// The retail caller and the 0x007FBC30 constructor establish the message and
// LID/GID key.  The 0x007F6A40 lookup establishes the entry type.  The "peri"
// assertion and the listener call at vtable slot 11 identify the remaining
// operations at this address.

class BfmeThingRF
{
public:
	void *bfmeGoRF( void *a, void *b );
};

class Rva007E8810Message
{
public:
	bool hasError();                                                  // 0x007E88A0
	int getError();                                                   // 0x007E88B0
	int getInt( const char *key, int defaultValue );                  // 0x007E8900

	char m_head[ 0x28 ];
	int m_txn;
};

class Rva007FBC30GameKey
{
public:
	Rva007FBC30GameKey( Rva007E8810Message *msg );

	int m_lid;
	int m_gid;
};

struct BfmeEntryZI
{
public:
	char m_head[ 8 ]; // +0x00
	int m_active; // +0x08
	void *m_listenerB; // +0x0C
	void *m_listenerA; // +0x10
};

struct Rva007F7640Results
{
	void *m_resultA;
	void * volatile m_resultBSpill;
};

struct Rva007F7640Locals
{
	Rva007FBC30GameKey m_key;
	Rva007F7640Results m_results;

	__forceinline Rva007F7640Locals( Rva007E8810Message *msg )
		: m_key( msg )
	{
	}
};

class Rva007F7980Listener
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void onRegionCountDone( int status );                     // slot 3
	virtual void onLobbyCountDone( int status );                      // slot 4
	virtual void onLobbyCounts( int lid, int status );                // slot 5
	virtual void v6( int lid, int gid );
	virtual void v7();
	virtual void v8();
	virtual void gameReady( int lid, int gid );                       // slot 9
	virtual void v10( int lid, int gid, int pid );
	virtual void onEntry( BfmeEntryZI *entry, int flag );             // slot 11
	virtual void onSlot12( int lid, int gid, int status );
	virtual void v13();
	virtual void v14();
	virtual void v15( int value );
	virtual void v16();
	virtual void v17();
	virtual void onSlot18( int status );                              // slot 18
	virtual void onSlot19( int status );                              // slot 19
};

extern int g_bfmeKeyAVHC;
extern int g_bfmeKeyBVHC;

struct Rva007EB810Diag
{
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void fail( const char *expression, const char *file, int line );
};

extern Rva007EB810Diag *Rva007EB810Get();

class BfmeThingZI
{
public:
	BfmeEntryZI *bfmeFindZI( int key, int other );
	void Rva007F72D0( Rva007E8810Message *msg );
	void rva007F7640( Rva007E8810Message *msg );

private:
	char m_pad000[ 0x1c ];
	Rva007F7980Listener *m_listener;
};

void BfmeThingZI::rva007F7640( Rva007E8810Message *msg )
{
	Rva007F7640Locals locals( msg );
	locals.m_results.m_resultA = ((BfmeThingRF *)msg)->bfmeGoRF( &g_bfmeKeyAVHC, 0 );
	void *resultB;
	resultB = ((BfmeThingRF *)msg)->bfmeGoRF( &g_bfmeKeyBVHC, 0 );
	locals.m_results.m_resultBSpill = resultB;
	BfmeEntryZI *entry = bfmeFindZI( locals.m_key.m_lid, locals.m_key.m_gid );

	if( entry == 0 )
	{
		Rva007EB810Get()->fail(
			"peri",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\gamebrowser\\gamebrowser.cpp",
			0x5df );
		return;
	}

	entry->m_listenerB = resultB;
	entry->m_listenerA = locals.m_results.m_resultA;
	m_listener->onEntry( entry, 0 );
}
