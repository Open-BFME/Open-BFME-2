// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// Hero power panel texts. Each builds a UnicodeString through a formatter
// and hands it to the rowed bfmeSetText. Both formatters return a
// UnicodeString by value through a hidden pointer; 0x005B2376 and
// 0x005B2446 are defined below.
//
// ?Rva005B23D7HeroPowersDescription@@YAXPAXABVAsciiString@@1@Z @0x005B23D7 111B
//   APT:HeroPowersDescription with the description text
// ?Rva005B24CDHeroPowerText@@YAXPAXPBDH@Z                      @0x005B24CD 114B
//   APT:%s_%d keyed by the prefix and the 1-based index
// Names are address-derived; the keys are the retail strings.
#include <stdio.h>
#include "ascii_string.h"
#include "unicode_string.h"

#include "../../../Libraries/Source/Apt/BfmeAptWindowManager.h"

#include "../../Include/Common/Rva00222A8BTarget.h"
class Rva00222A8BTarget;
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

UnicodeString __cdecl Rva005B2376Describe(void *power, const AsciiString &unused, const AsciiString &fallback);
UnicodeString __cdecl Rva005B2446Describe(void *power);

void __cdecl Rva005B23D7HeroPowersDescription(void *powerButton, const AsciiString &unused, const AsciiString &fallbackTextKey)
{
	UnicodeString descriptionText = Rva005B2376Describe(powerButton, unused, fallbackTextKey);
	g_bfmeAptWindowManager->bfmeSetText(AsciiString("APT:HeroPowersDescription"), descriptionText, true);
}

void __cdecl Rva005B24CDHeroPowerText(void *power, const char *widgetPrefix, int index)
{
	AsciiString key;
	key.format("APT:%s_%d", widgetPrefix, index + 1);
	g_bfmeAptWindowManager->bfmeSetText(key, Rva005B2446Describe(power), false);
}

// ?rva005B2295@@YA_NPBVCommandButton@@PBDHH@Z @0x005B2295 225B: points the
// Apt image key "%s_%d" (or "%s_%d_%d" for a page >= 0; both 1-based) at the
// button's image, falling back to CircleRed_42x42, and returns whether the
// key changed; with no button the key is cleared. Callers: the level labeller
// AptMyHero::rva005B0416 and the AptCreateAHero power panel. WorldBuilder's
// twin 0x0157F330 is unnamed; the name is address-derived.
class Image;
#include "../../Include/GameClient/CommandButton.h"
class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};
extern ImageCollection *TheMappedImageCollection;
class Rva00223A9F
{
public:
	void *rva00223A9F(const AsciiString *key);
};
class Rva00223A94
{
public:
	int rva00223A94(const AsciiString *key);
};
class Rva002239B2
{
public:
	void rva002239E2(const AsciiString &key, const Image *image);
};

bool __cdecl rva005B2295(const CommandButton *button, const char *widgetPrefix, int index, int pageIndex)
{
	AsciiString key;
	++index;
	if (pageIndex >= 0)
		key.format("%s_%d_%d", widgetPrefix, index, ++pageIndex);
	else
		key.format("%s_%d", widgetPrefix, index);
	bool imageChanged = false;
	if (button != NULL)
	{
		const Image *buttonImage = button->rva0035B19E();
		if (buttonImage == NULL)
			buttonImage = TheMappedImageCollection->findImageByName(AsciiString("CircleRed_42x42"));
		if (((Rva00223A9F *)g_bfmeAptWindowManager)->rva00223A9F(&key) != buttonImage)
		{
			((Rva002239B2 *)g_bfmeAptWindowManager)->rva002239E2(key, buttonImage);
			imageChanged = true;
		}
	}
	else
	{
		((Rva00223A94 *)g_bfmeAptWindowManager)->rva00223A94(&key);
		imageChanged = true;
	}
	return imageChanged;
}

// ?rva005B9378@Rva005B9378@@QAEXHABVUnicodeString@@@Z @0x005B9378 178B: one
// ticker row. The field text is the game-text label for the row's entry in
// the label table at VA 0x00DD3B90, fetched through TheGameText's
// fetch(const char *, bool *) (slot 0x3C), with L":" appended. It is set under
// APT:TickerField_%d, then the caller's value under APT:TickerValue_%d. Callers
// (0x005B945D and four more) pass this in ecx, which the body never reads.
#include "../../Include/GameClient/GameText.h"

extern GameTextInterface *TheGameText;

// ?Rva005B2376Describe@@YA?AVUnicodeString@@PAXABVAsciiString@@1@Z @0x005B2376
// 97B: the game text for the button's current description label (rowed
// CommandButton getter 0x0035B26F), else for the caller's fallback label,
// else L" ". The early push of 0 is fetch's exists argument, evaluated
// before the label. WorldBuilder's twin 0x0157F520 is unnamed.
UnicodeString __cdecl Rva005B2376Describe(void *powerButton, const AsciiString &unused, const AsciiString &fallbackTextKey)
{
	if (powerButton != NULL)
		return TheGameText->fetch(((const CommandButton *)powerButton)->rva0035B26F());
	if (!fallbackTextKey.isEmpty())
		return TheGameText->fetch(fallbackTextKey);
	return UnicodeString((const unsigned short *)L" ");
}

// ?Rva005B2446Describe@@YA?AVUnicodeString@@PAX@Z @0x005B2446 135B: the
// game text for "CAH:" + the power's +0x10 name + "_Name", or L" " without
// a power. WorldBuilder's twin 0x0157F670 (strings CAH:, _Name) is unnamed.
UnicodeString __cdecl Rva005B2446Describe(void *power)
{
	if (power == NULL)
		return UnicodeString((const unsigned short *)L" ");
	AsciiString label("CAH:");
	label += *(const AsciiString *)((const char *)power + 0x10);
	label += "_Name";
	return TheGameText->fetch(label);
}
extern const char *g_00DD3B90[];

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
#include "../../Include/GameNetwork/GameSpyInfoInterface.h"
extern GameSpyInfoInterface *TheGameSpyInfo;
#include "../../Include/GameClient/Shell.h"
extern Shell *TheShell;
void HandleBuddyResponses();			// ZH HandleBuddyResponses (pinned)
void HandlePersistentStorageResponses();			// ZH HandlePersistentStorageResponses (pinned)
void Rva00548C1ACleanup();	// ZH GameSpyCloseAllOverlays
void GSMessageBoxOk(UnicodeString title, UnicodeString message, void (*okFunc)());
void TearDownGameSpy();


// ?rva00513497@Rva00513497@@QAEXHVUnicodeString@@@Z @0x00513497 193B: the
// disconnect screen's player name. It is set under
// DisconnectScreen::PlayerName%d, or L" " when the name is null or empty
// (inline length test at +4). The slot then goes through the rowed bar update
// 0x00513040 with 0 or, for a real name, the rowed 0x00512CE9 (false) and the
// bar update with 100. 0x00512CE9 is AptDisconnectScreen's; the bar update
// keeps an address-named view of this same object.
class AptDisconnectScreen
{
public:
	void rva00512CE9(int slot, bool b);
};

class Rva00513040
{
public:
	void rva00513040(int v1, int v2);
};

// StringBase<unsigned short>::isEmpty, inline here as retail expands it.
static inline bool Rva00513497IsEmpty(const UnicodeString &unicodeString)
{
	const char *data = *(const char *const *)&unicodeString;
	return data == 0 || *(const unsigned short *)(data + 4) == 0;
}

class Rva00513497
{
public:
	void rva00513497(int playerSlot, UnicodeString playerName);
};

void Rva00513497::rva00513497(int playerSlot, UnicodeString playerName)
{
	AsciiString key;
	key.format("DisconnectScreen::PlayerName%d", playerSlot);
	if (Rva00513497IsEmpty(playerName))
	{
		g_bfmeAptWindowManager->bfmeSetText(key, UnicodeString(L" "), false);
		((Rva00513040 *)this)->rva00513040(playerSlot, 0);
	}
	else
	{
		g_bfmeAptWindowManager->bfmeSetText(key, playerName, false);
		((AptDisconnectScreen *)this)->rva00512CE9(playerSlot, false);
		((Rva00513040 *)this)->rva00513040(playerSlot, 100);
	}
}

// ?rva0057F538@Rva0057F538@@QAEXVUnicodeString@@@Z @0x0057F538 181B: the clan
// error text. An unchanged message is skipped. Otherwise it runs the Apt
// ResetClanErrorMessage callback on the owner (virtual slot 2) through the
// rowed Rva0043DB23, keeps the message at +0xB0, and sets CLAN:Error to it
// (L" " when empty).
int Rva0043DB23(Rva00222A8BTarget *target, void *owner, const char *name);

class Rva0057F538
{
public:
	virtual void v00();
	virtual void v04();
	virtual void *v08();
	void rva0057F538(UnicodeString message);
private:
	char m_pad04[0xAC];
	UnicodeString m_error;		// +0xB0
};

void Rva0057F538::rva0057F538(UnicodeString message)
{
	if (message.compare(m_error) == 0)
		return;
	Rva0043DB23(((Rva00222A8BTarget *)g_bfmeAptWindowManager), v08(), "ResetClanErrorMessage");
	m_error = message;
	if (Rva00513497IsEmpty(message))
		message = L" ";
	g_bfmeAptWindowManager->bfmeSetText(AsciiString("CLAN:Error"), message, false);
}

// ?rva0051C2E2@Rva0051C2E2@@QAEXPAHABVAsciiString@@H@Z @0x0051C2E2 201B: one
// score-screen region bonus row, APT:ScoreRegionBonus%d keyed by the running
// row counter. A positive bonus formats the label's game-text format string
// (TheGameText slot 0x40, as in Rva0052906BUpdate.cpp) with it. A negative
// bonus sets L" ". Either way the counter advances. A zero bonus sets
// nothing. Callers pass this in ecx, which the body never reads.
class Rva0051C2E2
{
public:
	void rva0051C2E2(int *outputRow, const AsciiString &bonusTextKey, int bonus);
};

void Rva0051C2E2::rva0051C2E2(int *outputRow, const AsciiString &bonusTextKey, int bonus)
{
	AsciiString key;
	key.format("APT:ScoreRegionBonus%d", *outputRow);
	if (bonus > 0)
	{
		UnicodeString bonusText;
		bonusText.format(TheGameText->fetchPtr(bonusTextKey, 0), bonus);
		g_bfmeAptWindowManager->bfmeSetText(key, bonusText, false);
		++*outputRow;
	}
	else if (bonus < 0)
	{
		g_bfmeAptWindowManager->bfmeSetText(key, UnicodeString(L" "), false);
		++*outputRow;
	}
}

// ?ProcessProgress@AptFileTransferPopup@@QAEXHHVUnicodeString@@@Z @0x00583121 225B: one
// file-transfer row. For a valid player (0..7) whose Apt slot at +0x5C is
// assigned (-1 means none), it sets FileTransfer::Status%d to the text, then
// calls SetBarTo with the slot and the percentage as "%d" strings through
// the rowed Rva00222A8BTarget::invoke (owner 13, two arguments).

class AptFileTransferPopup
{
public:
	void ProcessProgress(int playerIndex, int completionPercent, UnicodeString statusText);
private:
	char m_pad00[0x5C];
	int m_slots[8];				// +0x5C
};

void AptFileTransferPopup::ProcessProgress(int playerIndex, int completionPercent, UnicodeString statusText)
{
	if (playerIndex < 0 || playerIndex >= 8)
		return;
	int displaySlot = m_slots[playerIndex];
	if (displaySlot == -1)
		return;
	AsciiString key;
	key.format("FileTransfer::Status%d", displaySlot);
	g_bfmeAptWindowManager->bfmeSetText(key, statusText, false);
	char slotText[64];
	char percentText[64];
	sprintf(slotText, "%d", displaySlot);
	sprintf(percentText, "%d", completionPercent);
	((Rva00222A8BTarget *)g_bfmeAptWindowManager)->invoke((void *)13, "SetBarTo", 2, slotText, percentText, 0, 0, 0);
}

// ?rva0057C7BA@Rva0057E3DB@@QAEXH@Z @0x0057C7BA 216B: the lobby map title
// (the existing pin's class, the AptMpGameSetup panel's +0x60 member). It keeps
// the game type at +0x1C and sets APT:LobbyMapTiltle (the retail spelling)
// to that label's own game text for type 0 and GUI:GameTypeScenario for
// type 1.
class Rva0057E3DB
{
public:
	void rva0057C7BA(int gameType);
private:
	char m_pad00[0x1C];
	int m_type;					// +0x1C
};

void Rva0057E3DB::rva0057C7BA(int gameType)
{
	m_type = gameType;
	switch (gameType)
	{
	case 0:
		{
			AsciiString key("APT:LobbyMapTiltle");
			g_bfmeAptWindowManager->bfmeSetText(key, TheGameText->fetch("APT:LobbyMapTiltle", 0), false);
		}
		break;
	case 1:
		{
			AsciiString key("APT:LobbyMapTiltle");
			g_bfmeAptWindowManager->bfmeSetText(key, TheGameText->fetch("GUI:GameTypeScenario", 0), false);
		}
		break;
	}
}

// ?rva0043C8E4@AptSpellStore@@QAEXHH@Z @0x0043C8E4 79B: one spell button's
// state. SetSpellButtonState receives the 1-based button number as "%d" and
// the state's name from the table at VA 0x00C3D700. It goes through the
// rowed invoke on the owner the rowed Rva00222547Get resolves for this
// window. The number buffer reuses the index parameter's slot, as in retail.
class GameWindow;
extern const char *g_00C3D700[];

#include "../../Include/GameClient/AptSpellStore.h"


// ??1Rva00582FC1@@UAE@XZ @0x00582FC1 84B (the existing pin's name): the file
// transfer popup's destructor. It closes the popup through the rowed invoke
// (owner 13, FileTransferPopUpClose, no arguments), clears the instance
// global at VA 0x00E06398, then the rowed base destructor 0x005248D0 runs.
#include "../../Include/GameClient/Rva005248D0.h"

class Rva00582FC1 : public Rva005248D0
{
public:
	virtual ~Rva00582FC1();
};

// The ledger's name for VA 0x00E06398 (ColdGlobalDwordGetters.cpp).
extern int g_Va00E06398;

Rva00582FC1::~Rva00582FC1()
{
	((Rva00222A8BTarget *)g_bfmeAptWindowManager)->invoke((void *)13, "FileTransferPopUpClose", 0, 0, 0, 0, 0, 0);
	g_Va00E06398 = 0;
}

// ?processProgress@AptLoadScreen@@UAEXHH@Z @0x0043A15D 99B: SetBarTo on the panel's
// Apt owner (+0x8C) with the slot's id from the table at +0xB0 and the
// percentage, both formatted by sprintf "%d". The canonical header keeps the
// owner handle as field8C and the id table as fieldB0.
#include "../../Include/GameClient/AptLoadScreen.h"

void AptLoadScreen::processProgress(int playerSlot, int completionPercent)
{
	char idText[64];
	char percentText[64];
	sprintf(idText, "%d", fieldB0[playerSlot]);
	sprintf(percentText, "%d", completionPercent);
	((Rva00222A8BTarget *)g_bfmeAptWindowManager)->invoke(field8C, "SetBarTo", 2, idText, percentText, 0, 0, 0);
}
