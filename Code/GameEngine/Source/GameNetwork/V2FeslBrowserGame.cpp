// cl: /GS

// EA FESL browser game reply handler at retail RVA 0x007F6890.
// The browser's vtable slot 21 looks up a game element, and the listener's
// slot 9 receives the game and lobby identifiers after the record is stored.

class Rva007E8810Message
{
public:
	bool hasError();                                                  // 0x007E88A0
	int getError();                                                   // 0x007E88B0
	int getInt( const char *key, int defaultValue );                  // 0x007E8900

	char m_head[ 0x28 ];
	int m_txn;
};

class Rva007FBEF0GameRecord
{
public:
	Rva007FBEF0GameRecord(Rva007E8810Message *message);

	int m_lid;
	int m_gid;
	Rva007E8810Message *m_message;
	char m_ugid[0x25];
};

class Rva00802B30Element
{
public:
};

class BfmeKeyZP;
class BfmeOwnerZP
{
public:
	void bfmeFindZP(BfmeKeyZP *key);
};

struct BfmeEntryZI;

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

class Rva007F6BA0
{
public:
	void clear();                                                     // 0x007F6BA0
	void *m_array;
	int m_count;
};

class Rva007F6C60
{
public:
	void clear();                                                     // 0x007F6C60
	void *m_array;
	int m_count;
};

class Rva007F77B0Block : public Rva007F6BA0
{
public:
	void allocate( int count );                                       // 0x007F77B0
};

class Rva007F7810Block : public Rva007F6C60
{
public:
	void allocate( int count );                                       // 0x007F7810
};

class Rva00802B30Element;
class Rva00800920Owner;
class Rva00802040Owner;

class Rva007F7980Browser
{
public:
	void onRegionCount( Rva007E8810Message *msg );
	void onLobbyCount( Rva007E8810Message *msg );
	void onGame( Rva007E8810Message *message );
	void onPlayer( Rva007E8810Message *message );
	void rva007f63f0( void *message );

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
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual Rva00802B30Element *findGame( int lid );                  // slot 21

	char m_head[ 0x18 ];
	Rva007F7980Listener *m_listener;
	char m_pad20[ 4 ];
	Rva00800920Owner *field24;
	char m_pad28[ 0x10 ];
	Rva007F77B0Block m_regions;
	int m_regionIndex;
	int m_regionTxn;
	Rva007F7810Block m_lobbies;
	int m_lobbyIndex;
	int m_lobbyTxn;
	char m_pad58[ 0x280 ];
	Rva00802040Owner *field2d8;
};

void Rva007F7980Browser::onGame(Rva007E8810Message *message)
{
	Rva007FBEF0GameRecord record(message);
	int lid = record.m_lid;
	int gid = record.m_gid;
	if (message->hasError())
		return;
	Rva00802B30Element *element = findGame(lid);
	if (element != 0)
		((BfmeOwnerZP *)element)->bfmeFindZP((BfmeKeyZP *)&record);
	m_listener->gameReady(lid, gid);
}
