// cl: /GS /GX-
// The matched callback wrapper, Rva007F7000, calls body 0x007F63F0 as a member of Rva007F7980Browser.
// Retail passes the address of Rva00808CB0LanGameEntry::m_sequence to both output calls before it constructs the object.

#include <new>

// BFME 2: the assert text and file the donor declared as BFME 1 data
// (g_0112B7D0 / g_0112B6B0) are written as the literals game.dat holds at
// .rdata 0x00CE2FE8 / 0x00CE2EC8, so the unit needs no data definition.

class Rva007E8810Message;
class Rva007F51D0Ticket
{
public:
    Rva007F51D0Ticket(Rva007E8810Message *message);
    int m_pid;
    __int64 m_uid;
    int m_port;
    char m_name[0x80];
    char m_ip[0x20];
    char m_ticket[0x80];
};
class Rva007E8760Addr
{
public:
    void parse(const char *text, int port);
private:
    char m_pad00[8];
    unsigned int m_address;
    int m_port;
};
struct Rva007EB810Diag
{
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void fail( const char *expression, const char *file, int line );
};
extern Rva007EB810Diag *Rva007EB810Get();
class BfmeB1251;
class BfmeS1251;
class BfmeA1251
{
public:
    void bfmeInit1251(BfmeB1251 *, BfmeS1251 *);
};
class Rva00802680Owner
{
public:
    virtual void v0(); virtual void v1();
    virtual int *v2(void *value);
};
class Gen007F0130
{
public:
    static void *operator new(unsigned int size);
};
class Rva00802040Src;
class Rva00802040OwnerSrc;
class Rva00802680Owner;
class Rva00802040Owner : public Gen007F0130
{
public:
    Rva00802040Owner(Rva00802040Src *game, Rva00802040OwnerSrc *owner);
    Rva00802680Owner *findFree();
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual int *v9(void *out);
    virtual int *v10(void *out);
    virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(void *value);
    virtual void v15(void *secret);
private:
    char m_storage[0xd4];
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
class Rva00800920Owner
{
public:
    int rva00800a40(void *record, unsigned char flag, int extra);
};
class Rva007E86B0Base
{
public:
    Rva007E86B0Base();
    virtual ~Rva007E86B0Base();
    int m_field04;
};
class Rva00808CB0LanGameEntry : public Rva007E86B0Base
{
public:
    __forceinline Rva00808CB0LanGameEntry()
    {
        m_field08 = 0;
        m_field0c = 0;
        m_field04 = 0;
    }
    virtual ~Rva00808CB0LanGameEntry();
    int m_field08;
    int m_field0c;
    int m_sequence;
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
void Rva007F7980Browser::rva007f63f0(void *message)
{
    if (field2d8 == 0)
        return;
    int storage[5];
    Rva007F51D0Ticket ticket((Rva007E8810Message *)message);
    Rva00802680Owner *freeSlot = field2d8->findFree();
    if (freeSlot == 0)
    {
        Rva007EB810Get()->fail("mPlayer",
                               "\\views\\feslbuild_main\\jabba\\fesl\\source\\gamebrowser\\gamebrowser.cpp", 0x57d);
        return;
    }
    ((BfmeA1251 *)freeSlot)->bfmeInit1251((BfmeB1251 *)&ticket, (BfmeS1251 *)this);
    int slot = *freeSlot->v2(reinterpret_cast<int **>(&storage[4]));
    m_listener->v15(slot);
    int *value = field2d8->v9(reinterpret_cast<int **>(&storage[4]));
    if (*value != -2)
    {
        ::new ((void *)storage) Rva00808CB0LanGameEntry();
        ((Rva007E8760Addr *)storage)->parse(ticket.m_ip, ticket.m_port);
        field24->rva00800a40(reinterpret_cast<Rva00808CB0LanGameEntry *>(storage), 0, 0);
        reinterpret_cast<Rva00808CB0LanGameEntry *>(storage)->Rva00808CB0LanGameEntry::~Rva00808CB0LanGameEntry();
    }
}
