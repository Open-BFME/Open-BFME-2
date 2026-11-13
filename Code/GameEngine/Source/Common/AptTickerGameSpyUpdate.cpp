// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// The ticker response pump, split from the Apt display functions.
#include "ascii_string.h"
#include "unicode_string.h"

#include "../../Include/GameClient/GameText.h"

extern GameTextInterface *TheGameText;


#include "../../Include/Common/Rva005B9378.h"

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
#include "../../Include/GameNetwork/GameSpyInfoInterface.h"
extern GameSpyInfoInterface *TheGameSpyInfo;
#include "../../Include/GameClient/Shell.h"
extern Shell *TheShell;
void HandleBuddyResponses();			// ZH HandleBuddyResponses (pinned)
void HandlePersistentStorageResponses();			// ZH HandlePersistentStorageResponses (pinned)
#include "../../Include/GameClient/AptMessengerOnline.h"
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
	PeerResponse peerResponse;
	while (allowedMessages-- && !sawImportantMessage && TheGameSpyPeerMessageQueue->getResponse(peerResponse))
	{
		AptMessengerOnline::ProcessGameSpyResponse(&peerResponse);
		switch (peerResponse.peerResponseType)
		{
		case 1:	// PEERRESPONSE_DISCONNECT
			{
				sawImportantMessage = true;
				UnicodeString title, body;
				AsciiString disconnectReasonKey;
				disconnectReasonKey.format("GUI:GSDisconReason%d", peerResponse.words[0]);
				title = TheGameText->fetch("GUI:GSErrorTitle");
				body = TheGameText->fetch(disconnectReasonKey);
				Rva00548C1ACleanup();
				GSMessageBoxOk(title, body, 0);
				TheShell->pop();
				TearDownGameSpy();
			}
			break;
		case 21:
			rva005B942A(5, peerResponse.words[6]);
			rva005B942A(4, peerResponse.words[7] < 1 ? 1 : peerResponse.words[7]);
			break;
		}
	}
}

