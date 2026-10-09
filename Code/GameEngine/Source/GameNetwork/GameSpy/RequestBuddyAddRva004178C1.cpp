// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?Rva004178C1@@YAXHABVAsciiString@@@Z retail 0x004178C1..0x00417A66
// (421 bytes cdecl EH). The BFME 2 form of Zero Hour's RequestBuddyAdd
// (WOLBuddyOverlay.cpp) called from the APT:AddFriendOnSaveTitle answer
// 0x00435107. When the profile is already in TheGameSpyInfo's buddy request
// map (slot 25; rowed map<int int>::_M_find) it hands over to 0x004177D5
// instead. Otherwise it queues an add-buddy request (type 5) carrying
// GUI:BuddyAddReq through TheGameSpyBuddyMessageQueue (slot +0x18) and
// appends a BuddyMessage (time / no sender / local profile slot 31 and base
// name slot 37 / Buddy:FriendRequestSent formatted with the nick) to the
// buddy message list (slot 26) and clears the two buddy-window globals at
// 0x00A0308C / 0x00A03090. The ZH exists check and chat insertion are gone.
#include <map>
// The empty string at 0x00BBAC1C under the name Rva000B992CBuild.cpp gives it:
// retail pushes the immediate for the sender nick instead of reusing one
// register for every "" (the shared literal would be CSEd into esi).
extern const char g_Rva0107301CEmptyString[];
#include <list>
#include <string.h>
#include <time.h>
#include "ascii_string.h"
#include "unicode_string.h"

typedef int Int;
typedef unsigned short WideChar;

enum { MAX_BUDDY_CHAT_LEN = 0x80 };

class BuddyRequest
{
public:
	enum
	{
		BUDDYREQUEST_ADDBUDDY = 5
	};
	Int buddyRequestType; // +0x00
	Int id; // +0x04 (arg.addbuddy.id)
	WideChar text[MAX_BUDDY_CHAT_LEN]; // +0x08 (arg.addbuddy.text)
	char m_pad108[0x2b8 - 0x108];
};

class GameSpyBuddyMessageQueueInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05();
	virtual void addRequest(const BuddyRequest &req); // +0x18
};
extern GameSpyBuddyMessageQueueInterface *TheGameSpyBuddyMessageQueue;

// The buddy message list element (rowed list insert/push_back owner).
struct BfmeStringRecord00415F34 { unsigned char m_data[24]; };
typedef _STL::list<BfmeStringRecord00415F34> BuddyMessageList;
template <> void _STL::list<BfmeStringRecord00415F34, _STL::allocator<BfmeStringRecord00415F34> >::push_back(const BfmeStringRecord00415F34 &x);

class BuddyMessage
{
public:
	~BuddyMessage();

	time_t m_timestamp; // +0x00
	Int m_senderID; // +0x04
	AsciiString m_senderNick; // +0x08
	Int m_recipientID; // +0x0C
	AsciiString m_recipientNick; // +0x10
	UnicodeString m_message; // +0x14
};

typedef _STL::map<Int, Int> BuddyInfoMap;

class GameSpyInfoInterface
{
public:
#define V(n) virtual void slot##n();
#define V10(n) V(n##0) V(n##1) V(n##2) V(n##3) V(n##4) V(n##5) V(n##6) V(n##7) V(n##8) V(n##9)
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
	V(20) V(21) V(22) V(23)
	virtual BuddyInfoMap *getBuddyMap(); // slot 24
	virtual BuddyInfoMap *getBuddyRequestMap(); // slot 25
	virtual BuddyMessageList *getBuddyMessages(); // slot 26
	V(27) V(28) V(29) V(30)
	virtual Int getLocalProfileID(); // slot 31
	V(32) V(33) V(34) V(35) V(36)
	virtual AsciiString getLocalBaseName(); // slot 37
#undef V10
#undef V
};
extern GameSpyInfoInterface *TheGameSpyInfo;

class GameTextInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual UnicodeString fetch(const char *label, bool *exists = 0); // +0x3C
	virtual void slot16();
	virtual const UnicodeString *fetchFormat(const char *label, bool *exists = 0); // +0x44
};
extern GameTextInterface *TheGameText;

extern unsigned char g_Va00A0308C;
extern int g_Va00A03090;

void Rva004177D5(Int profileID);

void Rva004178C1(Int profileID, const AsciiString &nick)
{
	BuddyInfoMap *requests = TheGameSpyInfo->getBuddyRequestMap();
	if (requests && requests->find(profileID) != requests->end())
	{
		Rva004177D5(profileID);
		return;
	}

	// request to add a buddy
	BuddyRequest req;
	req.buddyRequestType = BuddyRequest::BUDDYREQUEST_ADDBUDDY;
	req.id = profileID;
	UnicodeString buddyAddstr;
	buddyAddstr = TheGameText->fetch("GUI:BuddyAddReq");
	wcsncpy(req.text, buddyAddstr.str(), MAX_BUDDY_CHAT_LEN);
	req.text[MAX_BUDDY_CHAT_LEN - 1] = 0;
	TheGameSpyBuddyMessageQueue->addRequest(req);

	// save message for future incarnations of the buddy window
	BuddyMessageList *messages = TheGameSpyInfo->getBuddyMessages();
	BuddyMessage message;
	message.m_timestamp = time(NULL);
	message.m_senderID = 0;
	message.m_senderNick = g_Rva0107301CEmptyString;
	message.m_recipientID = TheGameSpyInfo->getLocalProfileID();
	message.m_recipientNick = TheGameSpyInfo->getLocalBaseName();
	message.m_message.format(TheGameText->fetchFormat("Buddy:FriendRequestSent"), nick.str());
	messages->push_back(*reinterpret_cast<const BfmeStringRecord00415F34 *>(&message));
	g_Va00A0308C = 0;
	g_Va00A03090 = 0;
}
