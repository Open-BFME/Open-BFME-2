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

// _Rb_tree_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}
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
		BUDDYREQUEST_ADDBUDDY = 5,
		BUDDYREQUEST_OKADD = 7
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

// Buddy request map value view. Retail's key erase 0x00385CBA calls the
// range erase 0x00384ED4, rowed under this tree; the record is opaque.
struct Rva00384ED4Record { char word; };
typedef _STL::map<Int, Rva00384ED4Record> BuddyRequestMap;
// The key erase calls the range erase out of line; bind it to its row at 0x00384ED4.
typedef _STL::_Rb_tree<Int, BuddyRequestMap::value_type, _STL::_Select1st<BuddyRequestMap::value_type>, _STL::less<Int>, _STL::allocator<BuddyRequestMap::value_type> > BuddyRequestTree;
template <> void BuddyRequestTree::erase(BuddyRequestTree::iterator, BuddyRequestTree::iterator);

#include "../../../Include/GameNetwork/GameSpyInfoInterface.h"
extern GameSpyInfoInterface *TheGameSpyInfo;

#include "../../../Include/GameClient/GameText.h"
extern GameTextInterface *TheGameText;

extern unsigned char g_Va00A0308C;
extern int g_Va00A03090;

// ?Rva004177D5@@YAXH@Z retail 0x004177D5..0x004178C1 (236 bytes cdecl EH).
// The BFME 2 form of Zero Hour's AcceptBuddyRequest (WOLBuddyOverlay.cpp),
// reached from RequestBuddyAdd below when the profile is already a pending
// request: queue BUDDYREQUEST_OKADD, erase the profile from the request map
// (key erase 0x00385CBA), then queue the add-buddy request with
// GUI:BuddyAddReq. The fetched text temporary reuses the dead argument slot.
void Rva004177D5(Int profileID)
{
	BuddyRequest request;
	request.buddyRequestType = BuddyRequest::BUDDYREQUEST_OKADD;
	request.id = profileID;
	TheGameSpyBuddyMessageQueue->addRequest(request);

	((BuddyRequestMap *)TheGameSpyInfo->getBuddyRequestMap())->erase(profileID);

	BuddyRequest addRequest;
	addRequest.buddyRequestType = BuddyRequest::BUDDYREQUEST_ADDBUDDY;
	addRequest.id = profileID;
	UnicodeString text;
	text = TheGameText->fetch("GUI:BuddyAddReq");
	wcsncpy(addRequest.text, text.str(), MAX_BUDDY_CHAT_LEN);
	addRequest.text[MAX_BUDDY_CHAT_LEN - 1] = 0;
	TheGameSpyBuddyMessageQueue->addRequest(addRequest);
}

void Rva004178C1(Int profileID, const AsciiString &nick)
{
	BuddyInfoMap *requests = (BuddyInfoMap *)TheGameSpyInfo->getBuddyRequestMap();
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
	BuddyMessageList *messages = (BuddyMessageList *)TheGameSpyInfo->getBuddyMessages();
	BuddyMessage message;
	message.m_timestamp = time(NULL);
	message.m_senderID = 0;
	message.m_senderNick = g_Rva0107301CEmptyString;
	message.m_recipientID = TheGameSpyInfo->getLocalProfileID();
	message.m_recipientNick = TheGameSpyInfo->getLocalBaseName();
	message.m_message.format(TheGameText->fetchPtr("Buddy:FriendRequestSent"), nick.str());
	messages->push_back(*reinterpret_cast<const BfmeStringRecord00415F34 *>(&message));
	g_Va00A0308C = 0;
	g_Va00A03090 = 0;
}
