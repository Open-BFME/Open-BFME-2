// cl: /GS /EHs-c-
// Retail starts this request at 0x007F7AE0 after a separate 15-byte reply
// adapter and an alignment int3. It joins two caller-supplied lists and sends
// them with eight other caller-supplied words to FESL service slot 0x18.
class Rva007E8810Message;
class Rva007F7980Browser;
class BfmeMsg
{
public:
	virtual ~BfmeMsg() throw();

protected:
	int m_state;
};

class BfmeMsgVJH : public BfmeMsg
{
public:
	BfmeMsgVJH(char *buf, int n) throw();
	virtual ~BfmeMsgVJH() throw();
	int m_pad[0x0B]; // no /GS cookie in retail frames holding this object
};
void Rva00800040JoinI64(const __int64 *parts, unsigned count,
	char *dest, unsigned destSize, char separator);
void Rva00800170Join(const char **parts, unsigned count,
	char *dest, unsigned destSize, char separator);
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

class Rva007F7980Listener;
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

// BFME 2 0x00664150 (15B): forward the reply to the browser's onLobbyCount
// (0x006640E0).
void __cdecl Rva007F7AD0Callback(Rva007E8810Message *message,
	Rva007F7980Browser *browser)
{
	browser->onLobbyCount(message);
}

class LobbyListRequestService
{
public:
	virtual void v00() = 0;
	virtual void v04() = 0;
	virtual void v08() = 0;
	virtual void v0c() = 0;
	virtual void v10() = 0;
	virtual void v14() = 0;
	virtual void send(BfmeMsgVJH *message,
		int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8,
		const char *ids, const char *strings) = 0;
};
class LobbyListAsyncService
{
public:
	virtual void v00() = 0;
	virtual void v04() = 0;
	virtual void send(BfmeMsgVJH *message,
		void (__cdecl *callback)(Rva007E8810Message *, Rva007F7980Browser *),
		Rva007F7980Browser *browser, int transaction) = 0;
};
class Rva007F7AE0Owner
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0c();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1c();
	virtual void v20();
	virtual void v24();
	virtual void v28();
	virtual void v2c();
	virtual void v30();
	virtual void v34();
	virtual void v38();
	virtual void v3c();
	virtual void v40();
	virtual void beforeRequest();

	void request(int a1, int a2, int a3, int a4,
		int a5, int a6, int a7, int a8,
		const __int64 *ids, unsigned idCount,
		const char **strings, unsigned stringCount) throw();
	char m_pad04[0x0c];
	LobbyListRequestService *m_request;
	LobbyListAsyncService *m_async;
	char m_pad18[0x2c4];
	char m_buffer[0x400];
	int m_transaction;
};
void Rva007F7AE0Owner::request(int a1, int a2, int a3, int a4,
	int a5, int a6, int a7, int a8,
	const __int64 *ids, unsigned idCount,
	const char **strings, unsigned stringCount) throw()
{
	beforeRequest();
	BfmeMsgVJH message(m_buffer, sizeof(m_buffer));
	char stringText[0x100];
	char idText[0x100];
	stringText[0] = 0;
	idText[0] = 0;
	Rva00800040JoinI64(ids, idCount, idText, sizeof(idText), ';');
	Rva00800170Join(strings, stringCount, stringText, sizeof(stringText), ';');
	m_request->send(&message, a1, a2, a3, a4, a5, a6, a7, a8,
		idText, stringText);
	m_async->send(&message, Rva007F7AD0Callback,
		(Rva007F7980Browser *)this, m_transaction);
}
