// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?Rva004166DB@@YA_NABVUnicodeString@@PAVGameWindow@@@Z
// Retail 0x004166DB..0x004168AE (467 bytes), cdecl. Sends a buddy chat
// line: sole caller 0x00381458 (mode 0) passes the text and its third
// argument which this body walks as a begin/end pair of profile IDs (the
// pinned spelling keeps the caller's GameWindow pointer type). Sits in the
// BuddyDefs.cpp region right after Rva00416589 (0x00416589 ends here).
// Without TheGameSpyBuddyMessageQueue answers false. With no recipients it
// adds "GUI:PleaseSelectBuddy" to the chat (Rva00381C82AddChatText with
// GameSpyColor index 22) plays "GUIMessageBuddy" through TheAudio's lookup
// (+0x12C) and addAudioEvent (+0x64) and answers false. Otherwise queues a
// type 3 BuddyRequest (ZH BUDDYREQUEST_MESSAGE: recipient then 128 wide
// chars) per recipient then echoes one BuddyMessage (sender nick from
// getLocalBaseName via AsciiString::format) through Rva00416589.
// Layout and request/message views follow BuddyDefs.cpp; ZH
// WOLBuddyOverlay.cpp's message send is the semantic donor; WorldBuilder
// twin 0x01336B30 (callgraph score 1.0) differs (no-recipient map walk).
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include <wchar.h>
#undef _CRTIMP
#define _CRTIMP
#include "ascii_string.h"
#include "unicode_string.h"
#include "../../../Include/Common/BfmeAudioEventPrefix136.h"

class GameWindow;

class BuddyMessage {public:unsigned timestamp;int sender;AsciiString senderNick;int recipient;AsciiString recipientNick;UnicodeString message;~BuddyMessage();};
struct BfmeStringRecord00415F34 {BuddyMessage message;BfmeStringRecord00415F34(const BfmeStringRecord00415F34 &);};
void Rva00416589(BfmeStringRecord00415F34);
void Rva00381C82AddChatText(int,const UnicodeString &,int);
extern int GameSpyColor[];

struct BuddyRequest
{
	enum { BUDDYREQUEST_MESSAGE = 3 };
	int buddyRequestType;
	union
	{
		struct
		{
			int recipient;
			unsigned short text[128];
		} message;
		char extent[0x2b8 - 4];
	} arg;
};

#define V(n) virtual void slot##n();
class GameSpyBuddyMessageQueueInterface {public:V(0)V(1)V(2)V(3)V(4)V(5)virtual void addRequest(const BuddyRequest &);};
extern GameSpyBuddyMessageQueueInterface *TheGameSpyBuddyMessageQueue;
class GameSpyInfoInterface {public:
V(0)V(1)V(2)V(3)V(4)V(5)V(6)V(7)V(8)V(9)V(10)V(11)V(12)V(13)V(14)V(15)V(16)V(17)V(18)V(19)V(20)V(21)V(22)V(23)
V(24)V(25)V(26)V(27)V(28)V(29)V(30)V(31)V(32)V(33)V(34)V(35)V(36)virtual AsciiString getLocalBaseName();
};
extern GameSpyInfoInterface *TheGameSpyInfo;
class GameTextInterface {public:V(0)V(1)V(2)V(3)V(4)V(5)V(6)V(7)V(8)V(9)V(10)V(11)V(12)V(13)virtual UnicodeString fetch(const char *,bool *exists=0);virtual UnicodeString fetch(const AsciiString &,bool *exists=0);};
extern GameTextInterface *TheGameText;
#undef V

// Owning AudioEventInfo reference returned by TheAudio's +0x12C lookup.
class AudioEventInfoRef
{
public:
	~AudioEventInfoRef() { if (m_ptr) m_ptr->Release_Ref(); }
	bool isValid() const { return m_ptr != 0; }
	const OpaqueRefElement4 &element() const { return *(const OpaqueRefElement4 *)this; }

private:
	OpaqueRefCounted *m_ptr;
};

template <int N> class Rva004166DBAudioSlots : public Rva004166DBAudioSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva004166DBAudioSlots<0>
{
};

class AudioManager : public Rva004166DBAudioSlots<25>
{
public:
	virtual int addAudioEvent(const BfmeAudioEventPrefix136 *event);			// +0x64
	virtual void slot26(); virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31(); virtual void slot32(); virtual void slot33();
	virtual void slot34(); virtual void slot35(); virtual void slot36(); virtual void slot37();
	virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51();
	virtual void slot52(); virtual void slot53(); virtual void slot54(); virtual void slot55();
	virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
	virtual void slot60(); virtual void slot61(); virtual void slot62(); virtual void slot63();
	virtual void slot64(); virtual void slot65(); virtual void slot66(); virtual void slot67();
	virtual void slot68(); virtual void slot69(); virtual void slot70(); virtual void slot71();
	virtual void slot72(); virtual void slot73(); virtual void slot74();
	virtual AudioEventInfoRef findAudioEventInfo(const AsciiString &name) const;	// +0x12C
};
extern AudioManager *TheAudio;

// The recipients: a begin/end pair of profile IDs.
struct Rva004166DBRecipients
{
	int *m_begin;
	int *m_end;
};

// ?Rva004166DB@@YA_NABVUnicodeString@@PAVGameWindow@@@Z
bool Rva004166DB(const UnicodeString &text, GameWindow *window)
{
	if (!TheGameSpyBuddyMessageQueue)
		return false;

	BuddyRequest req;
	req.buddyRequestType = BuddyRequest::BUDDYREQUEST_MESSAGE;
	wcsncpy(req.arg.message.text, text.str(), 128);
	req.arg.message.text[127] = 0;

	Rva004166DBRecipients *recipients = (Rva004166DBRecipients *)window;
	int *begin = recipients->m_begin;
	if (begin == recipients->m_end)
	{
		UnicodeString message = TheGameText->fetch("GUI:PleaseSelectBuddy");
		Rva00381C82AddChatText(0, message, GameSpyColor[22]);
		if (TheAudio)
		{
			AudioEventInfoRef info = TheAudio->findAudioEventInfo(AsciiString("GUIMessageBuddy"));
			if (info.isValid())
			{
				BfmeAudioEventPrefix136 event(info.element(), 2);
				TheAudio->addAudioEvent(&event);
			}
		}
		return false;
	}

	for (int *it = recipients->m_begin; it != recipients->m_end; ++it)
	{
		req.arg.message.recipient = *it;
		TheGameSpyBuddyMessageQueue->addRequest(req);
	}

	BuddyMessage message;
	message.senderNick.format(&TheGameSpyInfo->getLocalBaseName());
	message.message = req.arg.message.text;
	Rva00416589(*(const BfmeStringRecord00415F34 *)&message);
	return true;
}
