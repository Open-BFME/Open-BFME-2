// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?Rva0050DE39Init@@YAXXZ @0x0050DE39 597B: observer ControlBar cache init.
// Evidence: caller 0x0031D201; callees rowed nameToKey 0x00148E1A plus nameToKey_ascii 0x0009FA65 plus format 0x00038150 plus releaseBuffer 0x00036410 plus winGetWindowFromId slot 0xF0; strings ControlBar.wnd Observer/Player/Button/StaticText/WinFlag/Portrait/Cancel; globals g_00E0460C g_00E0462C g_00E0464C g_00E04650 g_00E04654 g_00E04674 g_00E04694 g_00E04698 g_00E0469C g_00E046A0 g_00E046A4 g_00E046A8 g_00E046AC g_00E046B0; neighbour Rva0050E776Send.cpp layout.
#include "ascii_string.h"
#include "unicode_string.h"
extern "C" void *__cdecl memset(void *, int, unsigned int);

typedef int Int;

#ifndef NULL
#define NULL 0
#endif

class Image;
class GameWindow
{
public:
	int winHide(bool hide);
	unsigned int winSetStatus(unsigned int status);
	void winSetEnabledTextColors(int color, int borderColor);
	void rva003148A2(UnicodeString tooltip);	// ZH winSetTooltip
	bool winIsHidden();
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

extern Int g_00E0460C[8];
extern Int g_00E0462C[8];
extern GameWindow *g_00E0464C;
extern GameWindow *g_00E04650;
extern GameWindow *g_00E04654[8];
extern GameWindow *g_00E04674[8];
extern Int g_00E04694;
extern GameWindow *g_00E04698;
extern GameWindow *g_00E0469C;
extern GameWindow *g_00E046A0;
extern GameWindow *g_00E046A4;
extern GameWindow *g_00E046A8;
extern GameWindow *g_00E046AC;
extern GameWindow *g_00E046B0;

void __cdecl Rva0050DE39Init()
{
	g_00E0464C = TheWindowManager->winGetWindowFromId(NULL, TheNameKeyGenerator->nameToKey("ControlBar.wnd:ObserverPlayerInfoWindow"));
	g_00E04650 = TheWindowManager->winGetWindowFromId(NULL, TheNameKeyGenerator->nameToKey("ControlBar.wnd:ObserverPlayerListWindow"));
	for (Int i = 0; i < 8; ++i) {
		AsciiString tmp;
		tmp.format("ControlBar.wnd:ButtonPlayer%d", i);
		Int key = TheNameKeyGenerator->nameToKey(tmp);
		g_00E0460C[i] = key;
		g_00E04654[i] = TheWindowManager->winGetWindowFromId(g_00E04650, key);
		tmp.format("ControlBar.wnd:StaticTextPlayer%d", i);
		Int key2 = TheNameKeyGenerator->nameToKey(tmp);
		g_00E0462C[i] = key2;
		g_00E04674[i] = TheWindowManager->winGetWindowFromId(g_00E04650, key2);
	}
	g_00E046A0 = TheWindowManager->winGetWindowFromId(NULL, TheNameKeyGenerator->nameToKey("ControlBar.wnd:StaticTextNumberOfUnits"));
	g_00E046A4 = TheWindowManager->winGetWindowFromId(NULL, TheNameKeyGenerator->nameToKey("ControlBar.wnd:StaticTextNumberOfBuildings"));
	g_00E046A8 = TheWindowManager->winGetWindowFromId(NULL, TheNameKeyGenerator->nameToKey("ControlBar.wnd:StaticTextNumberOfUnitsKilled"));
	g_00E046AC = TheWindowManager->winGetWindowFromId(NULL, TheNameKeyGenerator->nameToKey("ControlBar.wnd:StaticTextNumberOfUnitsLost"));
	g_00E046B0 = TheWindowManager->winGetWindowFromId(NULL, TheNameKeyGenerator->nameToKey("ControlBar.wnd:StaticTextPlayerName"));
	g_00E04698 = TheWindowManager->winGetWindowFromId(NULL, TheNameKeyGenerator->nameToKey("ControlBar.wnd:WinFlag"));
	g_00E0469C = TheWindowManager->winGetWindowFromId(NULL, TheNameKeyGenerator->nameToKey("ControlBar.wnd:WinGeneralPortrait"));
	g_00E04694 = TheNameKeyGenerator->nameToKey("ControlBar.wnd:ButtonCancel");
}

// Zero Hour's ControlBar::populateObserverList (ControlBarObserver.cpp).
// BFME2 names the multiplayer players by their game slots' +0x34 name,
// skips players without a template, labels the team through GameText
// (CONTROLBAR fetchPtr format, the team string fetched by label) and fills
// the single-player list from the first human. Native [50E08E,50E3E5),855B;
// callers pass TheControlBar (0x0050E70D).
class PlayerTemplate
{
public:
	const Image *rva001FD221() const;	// ZH getEnabledImage
	const Image *rva001FD1FB() const;	// ZH getFlagWaterMarkImage
};
class ScoreKeeper
{
public:
	Int getTotalUnitsDestroyed();
	Int getTotalUnitsLost() { return m_totalUnitsLost; }
	unsigned char m_00[0x74];
	Int m_totalUnitsLost;				// +0x74
};
template <int N>
class BitFlags
{
public:
	BitFlags() { memset(m_words, 0, sizeof(m_words)); }
	BitFlags(const BitFlags &other);
	void clear() { memset(m_words, 0, sizeof(m_words)); }
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
class Player
{
public:
	bool rva002AA223() const;			// ZH isPlayerObserver
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
void GadgetButtonSetEnabledImage_Rva002C0433(GameWindow *window, const Image *image);
void GadgetStaticTextSetText(GameWindow *window, UnicodeString text);

class ControlBar
{
public:
	void populateObserverList(void);
	void populateObserverInfoWindow(void);
	unsigned char m_00[0x210];
	Player *m_observerLookAtPlayer;		// +0x210
};

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
			Player *p = ThePlayerList->findPlayerWithNameKey(TheNameKeyGenerator->nameToKey(name));
			if (p && p->m_playerTemplate)
			{
				if (p->rva002AA223())
					continue;
				Rva00328518(g_00E04654[currentButton], (Int)p);
				GadgetButtonSetEnabledImage_Rva002C0433(g_00E04654[currentButton], p->m_playerTemplate->rva001FD221());
				g_00E04654[currentButton]->rva003148A2(p->m_playerDisplayName);
				g_00E04654[currentButton]->winHide(false);
				g_00E04654[currentButton]->winSetStatus(0x200000);

				const GameSlot *slot = TheGameInfo->getConstSlot(currentButton);
				Int playerColor = p->m_color;
				Int backColor = 0xFF000000;
				g_00E04674[currentButton]->winSetEnabledTextColors(playerColor, backColor);
				g_00E04674[currentButton]->winHide(false);
				AsciiString teamStr;
				teamStr.format("Team:%d", slot->m_teamNumber + 1);
				if (slot->isAI() && slot->m_teamNumber == -1)
					teamStr = "Team:AI";

				UnicodeString text;
				text.format(TheGameText->fetchPtr("CONTROLBAR:ObsPlayerLabel"), p->m_playerDisplayName.str(),
					TheGameText->fetch(teamStr).str());
				GadgetStaticTextSetText(g_00E04674[currentButton], text);
				++currentButton;
			}
		}
		for (; currentButton < 8; ++currentButton)
		{
			g_00E04654[currentButton]->winHide(true);
			g_00E04674[currentButton]->winHide(true);
		}
	}
	else
	{
		for (i = 0; i < 20; ++i)
		{
			Player *p = ThePlayerList->getNthPlayer(i);
			if (p && !p->rva002AA223() && p->m_playerType == 0)
			{
				Rva00328518(g_00E04654[currentButton], (Int)p);
				GadgetButtonSetEnabledImage_Rva002C0433(g_00E04654[currentButton], p->m_playerTemplate->rva001FD221());
				g_00E04654[currentButton]->rva003148A2(p->m_playerDisplayName);
				g_00E04654[currentButton]->winHide(false);
				g_00E04654[currentButton]->winSetStatus(0x200000);
				Int playerColor = p->m_color;
				Int backColor = 0xFF000000;
				g_00E04674[currentButton]->winSetEnabledTextColors(playerColor, backColor);
				g_00E04674[currentButton]->winHide(false);
				GadgetStaticTextSetText(g_00E04674[currentButton], p->m_playerDisplayName);
				++currentButton;
				break;
			}
		}
		for (; currentButton < 8; ++currentButton)
		{
			g_00E04654[currentButton]->winHide(true);
			g_00E04674[currentButton]->winHide(true);
		}
	}
}

// Zero Hour's ControlBar::populateObserverInfoWindow; BFME2 stops after the
// player name, colour, flag and portrait. Native [50E3E5,50E6A6),705B.
void ControlBar::populateObserverInfoWindow(void)
{
	if (g_00E0464C->winIsHidden())
		return;

	if (!m_observerLookAtPlayer)
	{
		g_00E0464C->winHide(true);
		g_00E04650->winHide(false);
		populateObserverList();
		return;
	}

	UnicodeString uString;
	KindOfMaskType mask, clearmask;
	mask.set(KINDOF_SCORE);
	clearmask.set(KINDOF_STRUCTURE);
	uString.format(L"%d", m_observerLookAtPlayer->countObjects(mask, clearmask));
	GadgetStaticTextSetText(g_00E046A0, uString);
	Int numBuildings = 0;
	mask.clear();
	mask.set(KINDOF_SCORE);
	mask.set(KINDOF_STRUCTURE);
	clearmask.clear();
	numBuildings = m_observerLookAtPlayer->countObjects(mask, clearmask);
	mask.clear();
	mask.set(KINDOF_SCORE_CREATE);
	mask.set(KINDOF_STRUCTURE);
	numBuildings += m_observerLookAtPlayer->countObjects(mask, clearmask);
	mask.clear();
	mask.set(KINDOF_SCORE_DESTROY);
	mask.set(KINDOF_STRUCTURE);
	numBuildings += m_observerLookAtPlayer->countObjects(mask, clearmask);
	uString.format(L"%d", numBuildings);
	GadgetStaticTextSetText(g_00E046A4, uString);
	uString.format(L"%d", m_observerLookAtPlayer->getScoreKeeper()->getTotalUnitsDestroyed());
	GadgetStaticTextSetText(g_00E046A8, uString);
	uString.format(L"%d", m_observerLookAtPlayer->getScoreKeeper()->getTotalUnitsLost());
	GadgetStaticTextSetText(g_00E046AC, uString);
	GadgetStaticTextSetText(g_00E046B0, m_observerLookAtPlayer->m_playerDisplayName);
	Int color = m_observerLookAtPlayer->m_color;
	g_00E046B0->winSetEnabledTextColors(color, 0xFF000000);
	g_00E04698->winSetEnabledImage(0, m_observerLookAtPlayer->m_playerTemplate->rva001FD1FB());
	g_00E0469C->winHide(false);
}
