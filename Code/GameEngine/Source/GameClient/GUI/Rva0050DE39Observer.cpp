// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// platformsdk
// ?initObserverControls@ControlBar@@QAEXXZ @0x0050DE39 597B: observer ControlBar cache init.
// Evidence: caller 0x0031D201; callees rowed nameToKey 0x00148E1A plus nameToKey_ascii 0x0009FA65 plus format 0x00038150 plus releaseBuffer 0x00036410 plus winGetWindowFromId slot 0xF0; strings ControlBar.wnd Observer/Player/Button/StaticText/WinFlag/Portrait/Cancel; globals buttonPlayerID staticTextPlayerID ObserverPlayerInfoWindow ObserverPlayerListWindow buttonPlayer staticTextPlayer buttonCancelID winFlag winGeneralPortrait staticTextNumberOfUnits staticTextNumberOfBuildings staticTextNumberOfUnitsKilled staticTextNumberOfUnitsLost staticTextPlayerName; neighbour Rva0050E776Send.cpp layout.
#include <string.h>
#include <windows.h>
#include "ascii_string.h"
#include "unicode_string.h"

typedef int Int;

class Image;
class GameWindow
{
public:
	int winHide(bool hide);
	unsigned int winSetStatus(unsigned int status);
	void winSetEnabledTextColors(int color, int borderColor);
	void winSetTooltip(UnicodeString tooltip);	// ZH winSetTooltip
	bool winIsHidden();
	Int winGetWindowId();
	int winSetEnabledImage(int index, const Image *image);
	unsigned char m_pad[8];
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *nameString);
	NameKeyType nameToKey(const AsciiString &nameString);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class GameWindowManager
{
public:
	virtual void pad00();
	virtual void pad01();
	virtual void pad02();
	virtual void pad03();
	virtual void pad04();
	virtual void pad05();
	virtual void pad06();
	virtual void pad07();
	virtual void pad08();
	virtual void pad09();
	virtual void pad10();
	virtual void pad11();
	virtual void pad12();
	virtual void pad13();
	virtual void pad14();
	virtual void pad15();
	virtual void pad16();
	virtual void pad17();
	virtual void pad18();
	virtual void pad19();
	virtual void pad20();
	virtual void pad21();
	virtual void pad22();
	virtual void pad23();
	virtual void pad24();
	virtual void pad25();
	virtual void pad26();
	virtual void pad27();
	virtual void pad28();
	virtual void pad29();
	virtual void pad30();
	virtual void pad31();
	virtual void pad32();
	virtual void pad33();
	virtual void pad34();
	virtual void pad35();
	virtual void pad36();
	virtual void pad37();
	virtual void pad38();
	virtual void pad39();
	virtual void pad40();
	virtual void pad41();
	virtual void pad42();
	virtual void pad43();
	virtual void pad44();
	virtual void pad45();
	virtual void pad46();
	virtual void pad47();
	virtual void pad48();
	virtual void pad49();
	virtual void pad50();
	virtual void pad51();
	virtual void pad52();
	virtual void pad53();
	virtual void pad54();
	virtual void pad55();
	virtual void pad56();
	virtual void pad57();
	virtual void pad58();
	virtual void pad59();
	virtual GameWindow *winGetWindowFromId(GameWindow *window, Int id);
};

extern GameWindowManager *TheWindowManager;

// Owned here: the two name-key tables are filled in this TU's init loop
// (ButtonPlayer / StaticTextPlayer keys) and read back by input handling;
// retail .data starts them at 0.
Int buttonPlayerID[8] = { 0 };
Int staticTextPlayerID[8] = { 0 };
// Zero Hour's file statics (VA 0x00E0464C/0x00E04650): only this unit's
// observer functions touch them, and retail schedules around them as
// non-aliased statics (0x0050E6E6).
static GameWindow *ObserverPlayerInfoWindow = NULL;
static GameWindow *ObserverPlayerListWindow = NULL;
extern GameWindow *buttonPlayer[8];
extern GameWindow *staticTextPlayer[8];
extern Int buttonCancelID;
// Owned here: observer button windows, cancel key and the trio above are all
// written in this TU; retail .data starts them at 0.
GameWindow *buttonPlayer[8] = { 0 };
GameWindow *staticTextPlayer[8] = { 0 };
Int buttonCancelID = 0;
// Owned here: WinFlag, general portrait and the two count windows are
// written in this TU's init (winGetWindowFromId) and read back by the
// observer-panel refresh; retail .data starts them at 0.
GameWindow *winFlag = 0;
GameWindow *winGeneralPortrait = 0;
GameWindow *staticTextNumberOfUnits = 0;
GameWindow *staticTextNumberOfBuildings = 0;
// Owned here: the three observer static-text windows below are written in
// this TU's init (winGetWindowFromId) and read back on every observer-panel
// refresh; retail .data starts them at 0.
GameWindow *staticTextNumberOfUnitsKilled = 0;
GameWindow *staticTextNumberOfUnitsLost = 0;
GameWindow *staticTextPlayerName = 0;


// Zero Hour's ControlBar::populateObserverList (ControlBarObserver.cpp).
// BFME2 names the multiplayer players by their game slots' +0x34 name,
// skips players without a template, labels the team through GameText
// (CONTROLBAR fetchPtr format, the team string fetched by label) and fills
// the single-player list from the first human. Native [50E08E,50E3E5),855B;
// callers pass TheControlBar (0x0050E70D).
class PlayerTemplate
{
public:
	const Image *getEnabledImage() const;	// ZH getEnabledImage
	const Image *getFlagWaterMarkImage() const;	// ZH getFlagWaterMarkImage
};
class ScoreKeeper
{
public:
	Int getTotalUnitsDestroyed();
	Int getTotalUnitsLost() { return m_totalUnitsLost; }
	unsigned char m_00[0x74];
	Int m_totalUnitsLost;				// +0x74
};
// Clear the local masks directly at their use sites. A clear() definition here
// emits a competing body for the retail-owned BitFlags<116>::clear.
template <int N>
class BitFlags
{
public:
	__declspec(dllimport) __forceinline BitFlags() { memset(m_words, 0, sizeof(m_words)); }
	BitFlags(const BitFlags &other);
	void set(int idx) { m_words[idx >> 5] |= 1u << (idx & 31); }
	unsigned m_words[7];
};
typedef BitFlags<116> KindOfMaskType;
enum
{
	KINDOF_STRUCTURE = 7,
	KINDOF_SCORE = 39,
	KINDOF_SCORE_CREATE = 40,
	KINDOF_SCORE_DESTROY = 41
};
class ParticleSystem { public: bool isSaveable() const; };	// 0x002AA223 (rowed under this name)
class Player
{
public:
	unsigned char m_00[0x34];
	PlayerTemplate *m_playerTemplate;	// +0x34
	UnicodeString m_playerDisplayName;	// +0x38
	unsigned char m_3c[0x20];
	Int m_playerType;					// +0x5C
	unsigned char m_60[0x220];
	Int m_color;						// +0x280
	unsigned char m_284[0x138];
	ScoreKeeper m_scoreKeeper;			// +0x3BC

	Int countObjects(KindOfMaskType setMask, KindOfMaskType clearMask);
	ScoreKeeper *getScoreKeeper() { return &m_scoreKeeper; }
};
class PlayerList
{
public:
	Player *findPlayerWithNameKey(NameKeyType key);
	Player *getNthPlayer(Int i);
};
extern PlayerList *ThePlayerList;
class GameSlot
{
public:
	bool isAI() const;
	unsigned char m_00[0x1C];
	Int m_teamNumber;					// +0x1C
	unsigned char m_20[0x14];
	AsciiString m_name;					// +0x34
};
class GameInfo
{
public:
	GameSlot *getSlot(Int index);
	const GameSlot *getConstSlot(Int index) const;
};
extern GameInfo *TheGameInfo;
class RecorderClass
{
public:
	bool isMultiplayer();
};
extern RecorderClass *TheRecorder;
class GameTextInterface
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
	virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
	virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
	virtual UnicodeString fetch(const char *label, bool *exists = 0);
	virtual UnicodeString fetch(const AsciiString &label, bool *exists = 0);
	virtual UnicodeString *fetchPtr(const char *label, bool *exists = 0);
	virtual UnicodeString *fetchPtr(const AsciiString &label, bool *exists = 0);
};
extern GameTextInterface *TheGameText;
void Rva00328518(GameWindow *window, Int data);	// ZH GadgetButtonSetData
void GadgetButtonSetEnabledImage(GameWindow *window, const Image *image);
void GadgetStaticTextSetText(GameWindow *window, UnicodeString text);

class ControlBar
{
public:
	void populateObserverList(void);
	void populateObserverInfoWindow(void);
	void initObserverControls(void);	// 0x0050DE39
	void setObserverLookAtPlayer(Player *player) { m_observerLookAtPlayer = player; }
	Player *getObserverLookAtPlayer(void) { return m_observerLookAtPlayer; }
	unsigned char m_00[0x210];
	Player *m_observerLookAtPlayer;		// +0x210
};

// Zero Hour's ControlBar::initObserverControls (ControlBarObserver.cpp):
// ControlBar::init calls it last (0x0031D201, ECX = the control bar); the
// body reads no member.
void ControlBar::initObserverControls(void)
{
	ObserverPlayerInfoWindow = TheWindowManager->winGetWindowFromId(NULL, TheNameKeyGenerator->nameToKey("ControlBar.wnd:ObserverPlayerInfoWindow"));
	ObserverPlayerListWindow = TheWindowManager->winGetWindowFromId(NULL, TheNameKeyGenerator->nameToKey("ControlBar.wnd:ObserverPlayerListWindow"));
	for (Int i = 0; i < 8; ++i) {
		AsciiString tmp;
		tmp.format("ControlBar.wnd:ButtonPlayer%d", i);
		Int key = TheNameKeyGenerator->nameToKey(tmp);
		buttonPlayerID[i] = key;
		buttonPlayer[i] = TheWindowManager->winGetWindowFromId(ObserverPlayerListWindow, key);
		tmp.format("ControlBar.wnd:StaticTextPlayer%d", i);
		Int key2 = TheNameKeyGenerator->nameToKey(tmp);
		staticTextPlayerID[i] = key2;
		staticTextPlayer[i] = TheWindowManager->winGetWindowFromId(ObserverPlayerListWindow, key2);
	}
	staticTextNumberOfUnits = TheWindowManager->winGetWindowFromId(NULL, TheNameKeyGenerator->nameToKey("ControlBar.wnd:StaticTextNumberOfUnits"));
	staticTextNumberOfBuildings = TheWindowManager->winGetWindowFromId(NULL, TheNameKeyGenerator->nameToKey("ControlBar.wnd:StaticTextNumberOfBuildings"));
	staticTextNumberOfUnitsKilled = TheWindowManager->winGetWindowFromId(NULL, TheNameKeyGenerator->nameToKey("ControlBar.wnd:StaticTextNumberOfUnitsKilled"));
	staticTextNumberOfUnitsLost = TheWindowManager->winGetWindowFromId(NULL, TheNameKeyGenerator->nameToKey("ControlBar.wnd:StaticTextNumberOfUnitsLost"));
	staticTextPlayerName = TheWindowManager->winGetWindowFromId(NULL, TheNameKeyGenerator->nameToKey("ControlBar.wnd:StaticTextPlayerName"));
	winFlag = TheWindowManager->winGetWindowFromId(NULL, TheNameKeyGenerator->nameToKey("ControlBar.wnd:WinFlag"));
	winGeneralPortrait = TheWindowManager->winGetWindowFromId(NULL, TheNameKeyGenerator->nameToKey("ControlBar.wnd:WinGeneralPortrait"));
	buttonCancelID = TheNameKeyGenerator->nameToKey("ControlBar.wnd:ButtonCancel");
}

void ControlBar::populateObserverList(void)
{
	Int currentButton = 0, i;
	if (TheRecorder->isMultiplayer())
	{
		for (i = 0; i < 8; ++i)
		{
			AsciiString name;
			if (TheGameInfo)
				name = TheGameInfo->getSlot(i)->m_name;
			Player *player = ThePlayerList->findPlayerWithNameKey(TheNameKeyGenerator->nameToKey(name));
			if (player && player->m_playerTemplate)
			{
				if (((const ParticleSystem *)player)->isSaveable())
					continue;
				Rva00328518(buttonPlayer[currentButton], (Int)player);
				GadgetButtonSetEnabledImage(buttonPlayer[currentButton], player->m_playerTemplate->getEnabledImage());
				buttonPlayer[currentButton]->winSetTooltip(player->m_playerDisplayName);
				buttonPlayer[currentButton]->winHide(false);
				buttonPlayer[currentButton]->winSetStatus(0x200000);

				const GameSlot *slot = TheGameInfo->getConstSlot(currentButton);
				Int playerColor = player->m_color;
				Int backColor = 0xFF000000;
				staticTextPlayer[currentButton]->winSetEnabledTextColors(playerColor, backColor);
				staticTextPlayer[currentButton]->winHide(false);
				AsciiString teamStr;
				teamStr.format("Team:%d", slot->m_teamNumber + 1);
				if (slot->isAI() && slot->m_teamNumber == -1)
					teamStr = "Team:AI";

				UnicodeString text;
				text.format(TheGameText->fetchPtr("CONTROLBAR:ObsPlayerLabel"), player->m_playerDisplayName.str(),
					TheGameText->fetch(teamStr).str());
				GadgetStaticTextSetText(staticTextPlayer[currentButton], text);
				++currentButton;
			}
		}
		for (; currentButton < 8; ++currentButton)
		{
			buttonPlayer[currentButton]->winHide(true);
			staticTextPlayer[currentButton]->winHide(true);
		}
	}
	else
	{
		for (i = 0; i < 20; ++i)
		{
			Player *player = ThePlayerList->getNthPlayer(i);
			if (player && !((const ParticleSystem *)player)->isSaveable() && player->m_playerType == 0)
			{
				Rva00328518(buttonPlayer[currentButton], (Int)player);
				GadgetButtonSetEnabledImage(buttonPlayer[currentButton], player->m_playerTemplate->getEnabledImage());
				buttonPlayer[currentButton]->winSetTooltip(player->m_playerDisplayName);
				buttonPlayer[currentButton]->winHide(false);
				buttonPlayer[currentButton]->winSetStatus(0x200000);
				Int playerColor = player->m_color;
				Int backColor = 0xFF000000;
				staticTextPlayer[currentButton]->winSetEnabledTextColors(playerColor, backColor);
				staticTextPlayer[currentButton]->winHide(false);
				GadgetStaticTextSetText(staticTextPlayer[currentButton], player->m_playerDisplayName);
				++currentButton;
				break;
			}
		}
		for (; currentButton < 8; ++currentButton)
		{
			buttonPlayer[currentButton]->winHide(true);
			staticTextPlayer[currentButton]->winHide(true);
		}
	}
}

// Zero Hour's ControlBar::populateObserverInfoWindow; BFME2 stops after the
// player name, colour, flag and portrait. Native [50E3E5,50E6A6),705B.
void ControlBar::populateObserverInfoWindow(void)
{
	if (ObserverPlayerInfoWindow->winIsHidden())
		return;

	if (!m_observerLookAtPlayer)
	{
		ObserverPlayerInfoWindow->winHide(true);
		ObserverPlayerListWindow->winHide(false);
		populateObserverList();
		return;
	}

	UnicodeString uString;
	KindOfMaskType mask, clearmask;
	mask.set(KINDOF_SCORE);
	clearmask.set(KINDOF_STRUCTURE);
	uString.format(L"%d", m_observerLookAtPlayer->countObjects(mask, clearmask));
	GadgetStaticTextSetText(staticTextNumberOfUnits, uString);
	Int numBuildings = 0;
	memset(mask.m_words, 0, sizeof(mask.m_words));
	mask.set(KINDOF_SCORE);
	mask.set(KINDOF_STRUCTURE);
	memset(clearmask.m_words, 0, sizeof(clearmask.m_words));
	numBuildings = m_observerLookAtPlayer->countObjects(mask, clearmask);
	memset(mask.m_words, 0, sizeof(mask.m_words));
	mask.set(KINDOF_SCORE_CREATE);
	mask.set(KINDOF_STRUCTURE);
	numBuildings += m_observerLookAtPlayer->countObjects(mask, clearmask);
	memset(mask.m_words, 0, sizeof(mask.m_words));
	mask.set(KINDOF_SCORE_DESTROY);
	mask.set(KINDOF_STRUCTURE);
	numBuildings += m_observerLookAtPlayer->countObjects(mask, clearmask);
	uString.format(L"%d", numBuildings);
	GadgetStaticTextSetText(staticTextNumberOfBuildings, uString);
	uString.format(L"%d", m_observerLookAtPlayer->getScoreKeeper()->getTotalUnitsDestroyed());
	GadgetStaticTextSetText(staticTextNumberOfUnitsKilled, uString);
	uString.format(L"%d", m_observerLookAtPlayer->getScoreKeeper()->getTotalUnitsLost());
	GadgetStaticTextSetText(staticTextNumberOfUnitsLost, uString);
	GadgetStaticTextSetText(staticTextPlayerName, m_observerLookAtPlayer->m_playerDisplayName);
	Int color = m_observerLookAtPlayer->m_color;
	staticTextPlayerName->winSetEnabledTextColors(color, 0xFF000000);
	winFlag->winSetEnabledImage(0, m_observerLookAtPlayer->m_playerTemplate->getFlagWaterMarkImage());
	winGeneralPortrait->winHide(false);
}

// Zero Hour's ControlBarObserverSystem: the cancel button returns to the
// player list, a player button opens that player's info window. Handles
// create (1) and the 0x4006..0x4009 button messages. Native
// [50E6A6,50E776),208B.
enum WindowMsgHandledType { MSG_IGNORED, MSG_HANDLED };
extern ControlBar *TheControlBar;
void *GadgetButtonGetData(GameWindow *window);
WindowMsgHandledType ControlBarObserverSystem(GameWindow *window, unsigned int msg, unsigned int mData1, unsigned int mData2)
{
	switch (msg)
	{
	case 1:
	case 0x4006:
	case 0x4007:
		break;
	case 0x4008:
	case 0x4009:
		{
			GameWindow *control = (GameWindow *)mData1;
			Int controlID = control->winGetWindowId();
			if (controlID == buttonCancelID)
			{
				TheControlBar->setObserverLookAtPlayer(0);
				ObserverPlayerInfoWindow->winHide(true);
				ObserverPlayerListWindow->winHide(false);
				TheControlBar->populateObserverList();
			}
			for (Int i = 0; i < 8; ++i)
			{
				if (controlID == buttonPlayerID[i])
				{
					ObserverPlayerInfoWindow->winHide(false);
					ObserverPlayerListWindow->winHide(true);
					TheControlBar->setObserverLookAtPlayer((Player *)GadgetButtonGetData(buttonPlayer[i]));
					if (TheControlBar->getObserverLookAtPlayer())
						TheControlBar->populateObserverInfoWindow();
					return MSG_HANDLED;
				}
			}
			break;
		}
	default:
		return MSG_IGNORED;
	}
	return MSG_HANDLED;
}
