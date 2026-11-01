// cl: /O1 /G7 /Ow /arch:SSE /DNDEBUG /MD
// /Ow matches native scheduling across the distinct queue object and flag storage.
// Native550921..550995 is the sole slot of listener vtableC6AC08.
// Constructor550918 installs it; native Thread_Function552027 allocates four
// bytes and installs the same table before registering the listener at658680.
// This is an event callback with three stack words (RET12), not a destructor.
// Event4 sets ready; event0 plus a non-null error header whose first word is
// -204 emits BuddyResponse kind6/result4/error6/fatal1 and sets failed.
// Target bytes establish offsets and ABI; original API and argument names
// remain unknown. The second word is unused and modeled without a type claim.
// Sole storage for native one-byte flags E05FC0/E05FC1. No defined global at
// either address occurs in the current compiled ledger's DIR32 address index.
bool g_buddyFeslReady;
bool g_buddyFeslFailed;

#include "../../../../../../reference/open-bfme-1/inputs/reference/shims/sweep/GameSpy/GP/GP.h"
#define MAX_BUDDY_CHAT_LEN 128
class BuddyRequest;

class BuddyResponse
{
public:
	enum
	{
		BUDDYRESPONSE_LOGIN,
		BUDDYRESPONSE_DISCONNECT,
		BUDDYRESPONSE_MESSAGE,
		BUDDYRESPONSE_REQUEST,
		BUDDYRESPONSE_STATUS,
		BUDDYRESPONSE_MAX
	} buddyResponseType;

	GPProfile profile;
	GPResult result;

	union
	{
		struct
		{
			unsigned int date;
			char nick[GP_NICK_LEN];
			unsigned short text[MAX_BUDDY_CHAT_LEN];
		} message;

		struct
		{
			char nick[GP_NICK_LEN];
			char email[GP_EMAIL_LEN];
			char countrycode[GP_COUNTRYCODE_LEN];
			unsigned short text[GP_REASON_LEN];
		} request;

		struct
		{
			//GPResult result;
			GPErrorCode errorCode;
			char errorString[MAX_BUDDY_CHAT_LEN];
			GPEnum fatal;
		} error;

		struct
		{
			char nick[GP_NICK_LEN];
			char email[GP_EMAIL_LEN];
			char countrycode[GP_COUNTRYCODE_LEN];
			char location[GP_LOCATION_STRING_LEN];
			GPEnum status;
			char statusString[GP_STATUS_STRING_LEN];
		} status;
	} arg;

	// BFME's BuddyResponse is 0x864 bytes, not this header's 0x2D8:
	// GameSpyBuddyMessageQueue::getResponse @0x63C840 copies it with
	// `mov ecx,0x219` dwords where we emit 0xB6. Only the SIZE is proven,
	// so the pad sits at the tail and moves no existing member.
	char _bfme_pad_tail[0x864 - 0x2D8];
};


struct BuddyErrorResponseArm
{
	GPResult result;
	GPErrorCode errorCode;
	char errorString[MAX_BUDDY_CHAT_LEN];
	GPEnum fatal;
};
typedef char BuddyResponseSize[sizeof(BuddyResponse)==0x864?1:-1];
class GameSpyBuddyMessageQueueInterface
{
public:
	virtual ~GameSpyBuddyMessageQueueInterface() {}
	virtual void startThread( void ) = 0;
	virtual void endThread( void ) = 0;
	virtual bool isThreadRunning( void ) = 0;
	virtual bool isConnected( void ) = 0;
	virtual bool isConnecting( void ) = 0;

	virtual void addRequest( const BuddyRequest& req ) = 0;
	virtual bool getRequest( BuddyRequest& req ) = 0;

	virtual void addResponse( const BuddyResponse& resp ) = 0;
	virtual bool getResponse( BuddyResponse& resp ) = 0;

	virtual GPProfile getLocalProfileID( void ) = 0;

	static GameSpyBuddyMessageQueueInterface* createNewMessageQueue( void );
};

extern GameSpyBuddyMessageQueueInterface *TheGameSpyBuddyMessageQueue;
// The existing linker alternate binds this canonical name to the sole queue
// storage in Rva00627AA0Call.cpp; no new storage or alternate is introduced.

class Rva00550918 {
public:
 Rva00550918();
 virtual void rva00550921(int event, unsigned int opaque, const int *error);
};
void Rva00550918::rva00550921(int event, unsigned int opaque, const int *error)
{
 if(event!=0) {
  if(event==4)g_buddyFeslReady=true;
  return;
 }
 if(error && *error==-204) {
  BuddyResponse response;
  *(int *)&response.buddyResponseType=6;
  response.result=4;
  BuddyErrorResponseArm &errorArm=*(BuddyErrorResponseArm *)&response.arg;
  errorArm.errorCode=6;
  errorArm.fatal=1;
  g_buddyFeslReady=false;
  g_buddyFeslFailed=true;
  TheGameSpyBuddyMessageQueue->addResponse(response);
 }
}

// The existing9B constructor is emitted by BuddyThreadClassThreadFunction.cpp
// from this same one-slot listener view. Keep its sole real callback here;
// the owner unit supplies the byte-and-relocation-identical constructor copy.
