// cl:
// 0x007F6260: FESL game-browser ConnectingProtocol reply handler.
//
// The assertion names state 2.  The bytes establish the listener at +0x1c,
// the demangler/connect owner at +0x24, state at +0x30, and the optional-
// connect flag at +0x34.  The exact original interface names are unavailable;
// address- and state-derived names are used for those views.

class Rva007E8810Message
{
public:
	bool hasError();                                                  // 0x007E88A0
	int getError();                                                   // 0x007E88B0
	int getInt( const char *key, int defaultValue );                  // 0x007E8900

	char m_head[ 0x28 ];
	int m_txn;
};

class Rva007F6260Listener
{
public:
	virtual void onSlot0( int status );
};

class Rva008006C0Owner
{
public:
	int connect(const char *ugid, const char *secret, int flag);
};

struct Rva007EB810Diag
{
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void fail( const char *expression, const char *file, int line );
};

extern Rva007EB810Diag *Rva007EB810Get();

class Rva007F6260GameBrowser
{
public:
	void handleConnectingProtocolReply( Rva007E8810Message *msg );
	char m_pad00[0x1C];
private:
	Rva007F6260Listener *m_listener; // +0x1C
	char m_pad20[0x4];
	Rva008006C0Owner *m_connectOwner; // +0x24
	char m_pad28[0x8];
	int m_state; // +0x30
	bool m_connectProtocol; // +0x34
	char m_pad35[0x3];
};

void Rva007F6260GameBrowser::handleConnectingProtocolReply(
	Rva007E8810Message *msg )
{
	int status = 0;

	if( m_state != 2 )
	{
		Rva007EB810Get()->fail(
			"mState == GameBrowserStateConnectingProtocol",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\gamebrowser\\gamebrowser.cpp",
			0x508 );
	}

	if( msg->hasError() )
	{
		status = msg->getError();
	}
	else
	{
		m_state = 3;
		if( m_connectProtocol )
			m_connectOwner->connect( 0, 0, 0 );
	}

	m_listener->onSlot0( status );
}
