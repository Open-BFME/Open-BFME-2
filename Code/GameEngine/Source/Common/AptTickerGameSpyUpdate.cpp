// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// The ticker response pump, split from the Apt display functions.
#include "ascii_string.h"
#include "unicode_string.h"

#include "../../Include/GameClient/GameText.h"

extern GameTextInterface *TheGameText;


class Rva005B9378
{
public:
	void rva005B9378(int index, const UnicodeString &value);
	void rva005B942A(int index, int value);
	void rva005BA02B();
};

// ?rva005BA02B@Rva005B9378@@QAEXXZ @0x005BA02B 466B: the ticker screen's
// GameSpy update, Zero Hour's WOLGameSetupMenuUpdate response pump: buddy and
// persistent-storage responses first (pinned 0x00416C69, 0x005BDAC1), then up
// to TheGameSpyInfo's per-update budget (slot 93) of peer responses, each
// passed to the shared hook 0x005AF12F. A disconnect shows
// GUI:GSDisconReason%d under GUI:GSErrorTitle after closing the overlays,
// pops the shell and tears GameSpy down; response 21 updates ticker rows 5
// (payload word 6) and 4 (word 7, at least 1).
class PeerResponse
{
public:
	PeerResponse();
	~PeerResponse();
	int peerResponseType;
	unsigned char m_04[0x10C - 4];
	int words[143];
};
typedef char TickerPeerResponseSize[sizeof(PeerResponse) == 0x348 ? 1 : -1];
class GameSpyPeerMessageQueueInterface
{
public:
	virtual ~GameSpyPeerMessageQueueInterface();
	virtual void startThread(void);
	virtual void endThread(void);
	virtual bool isThreadRunning(void);
	virtual bool isConnected(void);
	virtual bool isConnecting(void);
	virtual void addRequest(const void *req);
	virtual bool getRequest(void *req);
	virtual void addResponse(const PeerResponse &resp);
	virtual bool getResponse(PeerResponse &resp);
};
extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;
class GameSpyInfoInterface
{
public:
#define TICKER_SLOT(n) virtual void slot##n();
	TICKER_SLOT(00) TICKER_SLOT(01) TICKER_SLOT(02) TICKER_SLOT(03) TICKER_SLOT(04) TICKER_SLOT(05) TICKER_SLOT(06) TICKER_SLOT(07) TICKER_SLOT(08) TICKER_SLOT(09)
	TICKER_SLOT(10) TICKER_SLOT(11) TICKER_SLOT(12) TICKER_SLOT(13) TICKER_SLOT(14) TICKER_SLOT(15) TICKER_SLOT(16) TICKER_SLOT(17) TICKER_SLOT(18) TICKER_SLOT(19)
	TICKER_SLOT(20) TICKER_SLOT(21) TICKER_SLOT(22) TICKER_SLOT(23) TICKER_SLOT(24) TICKER_SLOT(25) TICKER_SLOT(26) TICKER_SLOT(27) TICKER_SLOT(28) TICKER_SLOT(29)
	TICKER_SLOT(30) TICKER_SLOT(31) TICKER_SLOT(32) TICKER_SLOT(33) TICKER_SLOT(34) TICKER_SLOT(35) TICKER_SLOT(36) TICKER_SLOT(37) TICKER_SLOT(38) TICKER_SLOT(39)
	TICKER_SLOT(40) TICKER_SLOT(41) TICKER_SLOT(42) TICKER_SLOT(43) TICKER_SLOT(44) TICKER_SLOT(45) TICKER_SLOT(46) TICKER_SLOT(47) TICKER_SLOT(48) TICKER_SLOT(49)
	TICKER_SLOT(50) TICKER_SLOT(51) TICKER_SLOT(52) TICKER_SLOT(53) TICKER_SLOT(54) TICKER_SLOT(55) TICKER_SLOT(56) TICKER_SLOT(57) TICKER_SLOT(58) TICKER_SLOT(59)
	TICKER_SLOT(60) TICKER_SLOT(61) TICKER_SLOT(62) TICKER_SLOT(63) TICKER_SLOT(64) TICKER_SLOT(65) TICKER_SLOT(66) TICKER_SLOT(67) TICKER_SLOT(68) TICKER_SLOT(69)
	TICKER_SLOT(70) TICKER_SLOT(71) TICKER_SLOT(72) TICKER_SLOT(73) TICKER_SLOT(74) TICKER_SLOT(75) TICKER_SLOT(76) TICKER_SLOT(77) TICKER_SLOT(78) TICKER_SLOT(79)
	TICKER_SLOT(80) TICKER_SLOT(81) TICKER_SLOT(82) TICKER_SLOT(83) TICKER_SLOT(84) TICKER_SLOT(85) TICKER_SLOT(86) TICKER_SLOT(87) TICKER_SLOT(88) TICKER_SLOT(89)
	TICKER_SLOT(90) TICKER_SLOT(91) TICKER_SLOT(92)
#undef TICKER_SLOT
	virtual int getMaxMessagesPerUpdate(void);
};
extern GameSpyInfoInterface *TheGameSpyInfo;
class Shell
{
public:
	void pop();	// ZH Shell::pop
};
extern Shell *TheShell;
void HandleBuddyResponses();			// ZH HandleBuddyResponses (pinned)
void HandlePersistentStorageResponses();			// ZH HandlePersistentStorageResponses (pinned)
class AptMessengerOnline { public: static bool ProcessGameSpyResponse(void *resp); };	// shared peer-response hook
void Rva00548C1ACleanup();	// ZH GameSpyCloseAllOverlays
void GSMessageBoxOk(UnicodeString title, UnicodeString message, void (*okFunc)());
void TearDownGameSpy();

void Rva005B9378::rva005BA02B()
{
	if (!TheGameSpyPeerMessageQueue)
		return;

	HandleBuddyResponses();
	HandlePersistentStorageResponses();

	int allowedMessages = TheGameSpyInfo->getMaxMessagesPerUpdate();
	bool sawImportantMessage = false;
	PeerResponse resp;
	while (allowedMessages-- && !sawImportantMessage && TheGameSpyPeerMessageQueue->getResponse(resp))
	{
		AptMessengerOnline::ProcessGameSpyResponse(&resp);
		switch (resp.peerResponseType)
		{
		case 1:	// PEERRESPONSE_DISCONNECT
			{
				sawImportantMessage = true;
				UnicodeString title, body;
				AsciiString disconMunkee;
				disconMunkee.format("GUI:GSDisconReason%d", resp.words[0]);
				title = TheGameText->fetch("GUI:GSErrorTitle");
				body = TheGameText->fetch(disconMunkee);
				Rva00548C1ACleanup();
				GSMessageBoxOk(title, body, 0);
				TheShell->pop();
				TearDownGameSpy();
			}
			break;
		case 21:
			rva005B942A(5, resp.words[6]);
			rva005B942A(4, resp.words[7] < 1 ? 1 : resp.words[7]);
			break;
		}
	}
}

