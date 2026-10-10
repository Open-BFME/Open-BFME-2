// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ?processProgress@MapTransferLoadScreen@@UAEXHHVAsciiString@@@Z, retail
// 0x00356436 (128 bytes).
// Donor (Zero Hour LoadScreen.cpp MapTransferLoadScreen::processProgress):
// skip an unchanged percentage, remember it, set the slot's progress bar,
// and set the slot's text to TheGameText's translation of stateStr.
// Target evidence: WorldBuilder lead names 0x00356436
// MapTransferLoadScreen::processProgress; retail compares and stores
// m_oldProgress[playerId] (+0x90), maps the slot through m_playerLookup
// (+0x70), calls the matched GadgetProgressBarSetProgress on m_progressBars
// (+0x10) and the matched GadgetStaticTextSetText on m_progressText (+0x50)
// with TheGameText (0x00DFF0BC) slot 14 -- fetch(const AsciiString &) --
// built straight into the argument slot, then destroys the by-value
// stateStr. The donor's debug-only range assert is gone.
// This is a call-only view of the screen, not its construction model.
#include "ascii_string.h"
#include "unicode_string.h"

typedef int Int;

class GameWindow;
void GadgetProgressBarSetProgress(GameWindow *g, Int progress);
void GadgetStaticTextSetText(GameWindow *window, UnicodeString text);

class GameTextInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13();
	virtual UnicodeString fetch(const char *label, bool *exists = 0);
	virtual UnicodeString fetch(const AsciiString &label, bool *exists = 0);
	virtual void slot16();
	virtual const UnicodeString *slot44(const char *label, bool *exists);
};
extern GameTextInterface *TheGameText;

enum { MAX_SLOTS = 8 };

// Views for init (0x00356B78).
enum NameKeyType { NAMEKEY_INVALID = 0 };
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class GameWindow
{
public:
	int winHide(bool hide);
	int winBringToTop(void);
	int winSetEnabledColor(Int index, Int color);
	void winSetEnabledTextColors(Int color, Int borderColor);
	Int winGetEnabledTextBorderColor(void);

	char m_pad000[0x1F4];
	Int m_1f4;	// +0x1F4: cleared by init; meaning unknown
};
inline void GadgetProgressBarSetEnabledBarColor(GameWindow *g, Int color) { g->winSetEnabledColor(4, color); }

class GameWindowManager
{
public:
#define MTL_SLOT(n) virtual void slot##n();
	MTL_SLOT(00) MTL_SLOT(01) MTL_SLOT(02) MTL_SLOT(03) MTL_SLOT(04) MTL_SLOT(05) MTL_SLOT(06) MTL_SLOT(07) MTL_SLOT(08) MTL_SLOT(09)
	MTL_SLOT(10) MTL_SLOT(11) MTL_SLOT(12) MTL_SLOT(13) MTL_SLOT(14) MTL_SLOT(15) MTL_SLOT(16) MTL_SLOT(17) MTL_SLOT(18) MTL_SLOT(19)
	MTL_SLOT(20) MTL_SLOT(21) MTL_SLOT(22) MTL_SLOT(23) MTL_SLOT(24) MTL_SLOT(25) MTL_SLOT(26) MTL_SLOT(27) MTL_SLOT(28) MTL_SLOT(29)
	MTL_SLOT(30)
	virtual GameWindow *winCreateFromScript(AsciiString filename, void *info = 0, void *extra = 0);	// slot 31
	MTL_SLOT(32) MTL_SLOT(33) MTL_SLOT(34) MTL_SLOT(35) MTL_SLOT(36) MTL_SLOT(37) MTL_SLOT(38) MTL_SLOT(39)
	MTL_SLOT(40) MTL_SLOT(41) MTL_SLOT(42) MTL_SLOT(43) MTL_SLOT(44) MTL_SLOT(45) MTL_SLOT(46) MTL_SLOT(47) MTL_SLOT(48) MTL_SLOT(49)
	MTL_SLOT(50) MTL_SLOT(51) MTL_SLOT(52) MTL_SLOT(53) MTL_SLOT(54) MTL_SLOT(55) MTL_SLOT(56) MTL_SLOT(57) MTL_SLOT(58) MTL_SLOT(59)
#undef MTL_SLOT
	virtual GameWindow *winGetWindowFromId(GameWindow *window, Int id);	// slot 60
};
extern GameWindowManager *TheWindowManager;

class MultiplayerColorDefinition
{
public:
	Int getColor() const { return m_color; }
private:
	unsigned char m_00[0x10];
	Int m_color;	// +0x10
};
class MultiplayerSettings
{
public:
	MultiplayerColorDefinition *getColor(Int which);
};
extern MultiplayerSettings *TheMultiplayerSettings;

class GameSlot
{
public:
	bool isHuman() const;
	Int getApparentColor() const;
	bool hasMap() const { return m_hasMap; }
	const UnicodeString &getName() const { return m_name; }
private:
	unsigned char m_00[0x09];
	bool m_hasMap;			// +0x09
	unsigned char m_0a[0x30 - 0x0A];
	UnicodeString m_name;	// +0x30
};
class GameInfo
{
public:
	GameSlot *getSlot(Int index);
	const GameSlot *getConstSlot(Int index) const;
};
extern GameInfo *TheGameInfo;

class GameState
{
public:
	AsciiString getMapLeafName(const AsciiString &in) const;
};
extern GameState *TheGameState;

class MapTransferLoadScreen
{
public:
	virtual void processProgress(Int playerId, Int percentage, AsciiString stateStr);
	void processTimeout(Int secondsLeft);
	virtual void init(GameInfo *game);
	void setCurrentFilename(AsciiString filename);

private:
	char m_pad04[0x08 - 0x04];
	GameWindow *m_loadScreen;               // +0x08
	char m_pad0c[0x10 - 0x0C];
	GameWindow *m_progressBars[MAX_SLOTS];  // +0x10
	GameWindow *m_playerNames[MAX_SLOTS];   // +0x30
	GameWindow *m_progressText[MAX_SLOTS];  // +0x50
	Int m_playerLookup[MAX_SLOTS];          // +0x70
	Int m_oldProgress[MAX_SLOTS];           // +0x90
	GameWindow *m_fileNameText;             // +0xB0
	GameWindow *m_timeoutText;              // +0xB4
	Int m_oldTimeout;                      // +0xB8
};

void MapTransferLoadScreen::processProgress(Int playerId, Int percentage, AsciiString stateStr)
{
	if (m_oldProgress[playerId] == percentage)
		return;
	m_oldProgress[playerId] = percentage;

	Int translatedSlot = m_playerLookup[playerId];
	if (m_progressBars[translatedSlot])
		GadgetProgressBarSetProgress(m_progressBars[translatedSlot], percentage);
	if (m_progressText[translatedSlot])
		GadgetStaticTextSetText(m_progressText[translatedSlot], TheGameText->fetch(stateStr));
}

// ?processTimeout@MapTransferLoadScreen@@QAEXH@Z @0x003564B6 (139 bytes).
// Donor: Open-BFME-1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f,
// game/GameEngine/Source/GameClient/GUI/LoadScreen.cpp::processTimeout.
// Identity and offsets are independently supported by retail's comparison
// and store at +0xB8, nullable text window at +0xB4, and actual ASCII literal
// "MapTransfer:Timeout" at RVA 0x00814EEC (not a vtable address). Retail
// fetches a UnicodeString pointer through GameText slot +0x44, then calls
// the rowed string formatter with seconds/60 and seconds%60, and sends
// the by-value copy to rowed GadgetStaticTextSetText (0x00321552).
void MapTransferLoadScreen::processTimeout(Int secondsLeft)
{
    if (m_oldTimeout == secondsLeft)
        return;
    m_oldTimeout = secondsLeft;
    if (m_timeoutText) {
        UnicodeString text;
        text.format(TheGameText->slot44("MapTransfer:Timeout", 0),
                    secondsLeft / 60, secondsLeft % 60);
        GadgetStaticTextSetText(m_timeoutText, text);
    }
}

// ?setCurrentFilename@MapTransferLoadScreen@@QAEXVAsciiString@@@Z @0x00356E8E
// (198 bytes). Donor: Zero Hour LoadScreen.cpp
// MapTransferLoadScreen::setCurrentFilename, unchanged. Target evidence: the
// nullable m_fileNameText (+0xB0), TheGameState (0x00DFF08C) with the pinned
// GameState::getMapLeafName 0x002DC802, "MapTransfer:CurrentFile" through
// GameText slot +0x44 into the rowed formatter, and the by-value copy to
// GadgetStaticTextSetText.
void MapTransferLoadScreen::setCurrentFilename(AsciiString filename)
{
	if (m_fileNameText)
	{
		UnicodeString txt;
		txt.translate(TheGameState->getMapLeafName(filename));
		txt.format(TheGameText->slot44("MapTransfer:CurrentFile", 0), txt.str());
		GadgetStaticTextSetText(m_fileNameText, txt);
	}
}

// ?init@MapTransferLoadScreen@@UAEXPAVGameInfo@@@Z @0x00356B78 (790 bytes).
// Donor: Zero Hour LoadScreen.cpp MapTransferLoadScreen::init. Target
// evidence: the MapTransferScreen.wnd literals, TheWindowManager slots 31
// (winCreateFromScript, two extra null arguments in BFME2) and 60, the
// members above, the folded winGetEnabledTextBorderColor pin 0x00313E93 and
// TheGameInfo at 0x00E02EEC. BFME2 drops the debug output and clears the
// layout window's +0x1F4 after bringing it to the top.
void MapTransferLoadScreen::init(GameInfo *game)
{
	m_loadScreen = TheWindowManager->winCreateFromScript(AsciiString("Menus/MapTransferScreen.wnd"));
	if (!m_loadScreen)
		return;

	m_loadScreen->winHide(false);
	// Codegen: same-valued PHI receiver closes the native register role of the layout window.
	(m_loadScreen?m_loadScreen:m_loadScreen)->winBringToTop();
	m_loadScreen->m_1f4 = 0;

	AsciiString winName;
	Int i;

	winName.format("MapTransferScreen.wnd:StaticTextCurrentFile");
	m_fileNameText = TheWindowManager->winGetWindowFromId(m_loadScreen, TheNameKeyGenerator->nameToKey(winName));

	winName.format("MapTransferScreen.wnd:StaticTextTimeout");
	m_timeoutText = TheWindowManager->winGetWindowFromId(m_loadScreen, TheNameKeyGenerator->nameToKey(winName));

	Int netSlot = 0;
	for (i = 0; i < MAX_SLOTS; ++i)
	{
		winName.format("MapTransferScreen.wnd:ProgressLoad%d", i);
		m_progressBars[i] = TheWindowManager->winGetWindowFromId(m_loadScreen, TheNameKeyGenerator->nameToKey(winName));
		GadgetProgressBarSetProgress(m_progressBars[i], 0);

		winName.format("MapTransferScreen.wnd:StaticTextPlayer%d", i);
		m_playerNames[i] = TheWindowManager->winGetWindowFromId(m_loadScreen, TheNameKeyGenerator->nameToKey(winName));

		winName.format("MapTransferScreen.wnd:StaticTextProgress%d", i);
		m_progressText[i] = TheWindowManager->winGetWindowFromId(m_loadScreen, TheNameKeyGenerator->nameToKey(winName));

		GameSlot *slot = game->getSlot(i);
		if (!slot || !slot->isHuman())
			continue;
		Int houseColor = TheMultiplayerSettings->getColor(slot->getApparentColor())->getColor();
		GadgetProgressBarSetEnabledBarColor(m_progressBars[netSlot], houseColor);

		UnicodeString name = slot->getName();
		GadgetStaticTextSetText(m_playerNames[netSlot], name);
		m_playerNames[netSlot]->winSetEnabledTextColors(houseColor, m_playerNames[netSlot]->winGetEnabledTextBorderColor());

		GadgetStaticTextSetText(m_progressText[netSlot], UnicodeString::TheEmptyString);
		m_progressText[netSlot]->winSetEnabledTextColors(houseColor, m_progressText[netSlot]->winGetEnabledTextBorderColor());

		if ((i == 0 || (TheGameInfo->getConstSlot(i)->isHuman() && TheGameInfo->getConstSlot(i)->hasMap())) && m_progressBars[netSlot])
			m_progressBars[netSlot]->winHide(true);

		m_playerLookup[i] = netSlot;

		netSlot++;
	}

	for (i = netSlot; i < MAX_SLOTS; ++i)
	{
		m_progressBars[i]->winHide(true);
		m_playerNames[i]->winHide(true);
		m_progressText[i]->winHide(true);
	}
}
