// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /O1 /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/open-bfme-1/inputs/reference/shims/buddythread /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
//
// Zero Hour's BuddyThreadClass::connectCallback (GameSpy/Thread/BuddyThread.cpp),
// native [551BF4,551FB3),959B, callbackWrapper case 0. Its own unit because
// retail builds it against static STLport strings and BFME2's peer records
// (the 0x1EC-byte request and 0x348-byte response), which BuddyThread.cpp's
// Zero Hour PeerThread.h shim cannot express; the record, login and error
// arms are local views with BFME2's offsets and the GameSpy SDK lengths.
//
// BFME2 deltas: the buddy status is set online first; a failed connect with
// a bad nick or e-mail is retried as a new account carrying the registry CD
// key ("\\ergc", login +0x272); Zero Hour's create-account fix-up stays;
// otherwise the peer disconnect is followed by a fatal buddy disconnect
// (GP_SERVER_ERROR, connection failed).

// BFME 2's WWLib thread base (as in PersistentStorageThread.cpp).
#define THREAD_H
class ThreadClass
{
public:
	ThreadClass(const char *name);
	virtual ~ThreadClass();
	virtual void Execute();
protected:
	virtual void Thread_Function() = 0;
private:
	char m_name[0x40];
	unsigned int m_threadId;
	void *m_handle;
	int m_priority;
};

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "GameNetwork/GameSpy/BuddyThread.h"

class BuddyThreadClass : public ThreadClass
{

public:
	BuddyThreadClass() : ThreadClass(0) { m_isNewAccount = m_isdeleting = m_isConnecting = m_isConnected = false; m_profileID = 0; m_lastErrorCode = 0; }

	void Thread_Function();

	void errorCallback( GPConnection *con, GPErrorArg *arg );
	void messageCallback( GPConnection *con, GPRecvBuddyMessageArg *arg );
	void connectCallback( GPConnection *con, GPConnectResponseArg *arg );
	void requestCallback( GPConnection *con, GPRecvBuddyRequestArg *arg );
	void statusCallback( GPConnection *con, GPRecvBuddyStatusArg *arg );
	void rva00550720( GPConnection *con, GPRecvBuddyRequestArg *arg );

	Bool isConnecting( void ) { return m_isConnecting; }
	Bool isConnected( void ) { return m_isConnected; }

	GPProfile getLocalProfileID( void ) { return m_profileID; }

private:
	Bool m_isNewAccount;
	Bool m_isConnecting;
	Bool m_isConnected;
	GPProfile m_profileID;
	Int m_lastErrorCode;
	Bool m_isdeleting;
	std::string m_nick, m_email, m_pass;
};

// BFME2's peer request (rowed constructor 0x001EF661 / destructor 0x001EF723
// under this record name) with Zero Hour's field offsets.
struct BfmeOpaqueOwnedRecord492
{
	BfmeOpaqueOwnedRecord492();
	~BfmeOpaqueOwnedRecord492();
	Int peerRequestType;			// +0x00
	std::string nick;				// +0x04
	unsigned char text[12];			// +0x10 wide string
	std::string password;			// +0x1C
	std::string email;				// +0x28
	unsigned char m_34[0x118 - 0x34];
	Int loginProfileID;				// +0x118
	unsigned char m_11c[0x1EC - 0x11C];
};
typedef char PeerRequestViewSize[sizeof(BfmeOpaqueOwnedRecord492) == 0x1EC ? 1 : -1];

// BFME2's 0x348-byte peer response (PeerResponseAssign.cpp); the disconnect
// reason is the first payload word.
class PeerResponse
{
public:
	PeerResponse();
	~PeerResponse();
	Int peerResponseType;
	unsigned char m_04[0x10C - 4];
	Int discReason;					// +0x10C
	unsigned char m_110[0x348 - 0x110];
};
typedef char PeerResponseViewSize[sizeof(PeerResponse) == 0x348 ? 1 : -1];

class GameSpyPeerMessageQueueInterface
{
public:
	virtual ~GameSpyPeerMessageQueueInterface();
	virtual void startThread( void );
	virtual void endThread( void );
	virtual Bool isThreadRunning( void );
	virtual Bool isConnected( void );
	virtual Bool isConnecting( void );
	virtual void addRequest( const BfmeOpaqueOwnedRecord492& req );
	virtual Bool getRequest( BfmeOpaqueOwnedRecord492& req );
	virtual void addResponse( const PeerResponse& resp );
};
extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;

struct BuddyLoginArmBFME2	// GameSpy SDK lengths: nick 31, email 51, password 31
{
	char nick[31];
	char email[51];
	char password[31];
	Bool hasFirewall;
	unsigned char m_72[0x272 - 0x72];
	char cdkey[1];
};
struct BuddyErrorResponseArm	// BFME2 keeps the GPResult ZH commented out
{
	GPResult result;
	GPErrorCode errorCode;
	char errorString[MAX_BUDDY_CHAT_LEN];
	GPEnum fatal;
};
Bool GetStringFromRegistry(AsciiString path, AsciiString key, AsciiString& val);
// The empty-string literal, distinct from AsciiString::str()'s null
// character in retail (both fold to VA 0x00BBAC1C).
extern const char g_Rva0107301CEmptyString[];
enum GameSpyBuddyStatus { BUDDY_OFFLINE, BUDDY_ONLINE, BUDDY_LOBBY, BUDDY_STAGING, BUDDY_LOADING, BUDDY_PLAYING, BUDDY_MATCHING, BUDDY_MAX };
void updateBuddyStatus( GameSpyBuddyStatus status, Int gameID = 0, std::string gameName = "" );

void BuddyThreadClass::connectCallback( GPConnection *con, GPConnectResponseArg *arg )
{
	if (arg->result == 0)
	{
		updateBuddyStatus( BUDDY_ONLINE );
		BuddyResponse loginResponse;
		loginResponse.buddyResponseType = BuddyResponse::BUDDYRESPONSE_LOGIN;
		loginResponse.result = arg->result;
		loginResponse.profile = arg->profile;
		TheGameSpyBuddyMessageQueue->addResponse( loginResponse );
		m_profileID = arg->profile;

		if (!TheGameSpyPeerMessageQueue->isConnected() && !TheGameSpyPeerMessageQueue->isConnecting())
		{
			BfmeOpaqueOwnedRecord492 req;
			req.peerRequestType = 0;	// PEERREQUEST_LOGIN
			req.nick = m_nick.c_str();
			req.password = m_pass;
			req.email = m_email;
			req.loginProfileID = arg->profile;
			TheGameSpyPeerMessageQueue->addRequest( req );
		}
		m_isConnected = true;
	}
	else
	{
		if (!TheGameSpyPeerMessageQueue->isConnected() && !TheGameSpyPeerMessageQueue->isConnecting())
		{
			if (m_lastErrorCode == 0x0102 || m_lastErrorCode == 0x0103)	// GP_LOGIN_BAD_NICK/EMAIL
			{
				BuddyRequest req;
				BuddyLoginArmBFME2 &login = *(BuddyLoginArmBFME2 *)&req.arg;
				req.buddyRequestType = BuddyRequest::BUDDYREQUEST_LOGINNEW;
				strcpy(login.nick, m_nick.c_str());
				strcpy(login.email, m_email.c_str());
				strcpy(login.password, m_pass.c_str());
				login.hasFirewall = true;
				AsciiString cdkey;
				GetStringFromRegistry("\\ergc", g_Rva0107301CEmptyString, cdkey);
				strcpy(login.cdkey, cdkey.str());
				TheGameSpyBuddyMessageQueue->addRequest( req );
				return;
			}
			if (m_lastErrorCode == 0x0201)	// GP_NEWUSER_BAD_NICK
			{
				m_isNewAccount = FALSE;
				BuddyRequest req;
				BuddyLoginArmBFME2 &login = *(BuddyLoginArmBFME2 *)&req.arg;
				req.buddyRequestType = BuddyRequest::BUDDYREQUEST_LOGIN;
				strcpy(login.nick, m_nick.c_str());
				strcpy(login.email, m_email.c_str());
				strcpy(login.password, m_pass.c_str());
				login.hasFirewall = true;
				TheGameSpyBuddyMessageQueue->addRequest( req );
				return;
			}
			PeerResponse resp;
			resp.peerResponseType = 1;	// PEERRESPONSE_DISCONNECT
			resp.discReason = 4;		// DISCONNECT_COULDNOTCONNECT
			switch (m_lastErrorCode)
			{
			case 0x0101: resp.discReason = 5; break;
			case 0x0102: resp.discReason = 6; break;
			case 0x0103: resp.discReason = 7; break;
			case 0x0104: resp.discReason = 8; break;
			case 0x0105: resp.discReason = 9; break;
			case 0x0106: resp.discReason = 10; break;
			case 0x0107: resp.discReason = 11; break;
			case 0x0108: resp.discReason = 12; break;
			case 0x0201: resp.discReason = 16; break;
			case 0x0202: resp.discReason = 17; break;
			case 0x0401: resp.discReason = 18; break;
			case 0x0402: resp.discReason = 19; break;
			}
			TheGameSpyPeerMessageQueue->addResponse(resp);

			BuddyResponse errorResponse;
			BuddyErrorResponseArm &error = *(BuddyErrorResponseArm *)&errorResponse.arg;
			errorResponse.buddyResponseType = BuddyResponse::BUDDYRESPONSE_DISCONNECT;
			errorResponse.result = (GPResult)4;			// GP_SERVER_ERROR
			error.errorCode = (GPErrorCode)0x0107;		// GP_LOGIN_CONNECTION_FAILED
			error.fatal = (GPEnum)1;					// GP_FATAL
			TheGameSpyBuddyMessageQueue->addResponse( errorResponse );
		}
	}
	m_isConnecting = false;
}
