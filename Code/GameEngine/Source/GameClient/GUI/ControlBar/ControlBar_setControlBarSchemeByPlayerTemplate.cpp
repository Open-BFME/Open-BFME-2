// cl: /EHsc /MD
// ?setControlBarSchemeByPlayerTemplate@ControlBar@@QAEXPBVPlayerTemplate@@@Z @0x0031C5C8 469B chain: ControlBar observer bar switch
// Evidence: donor BFME1 ControlBar::setControlBarSchemeByPlayerTemplate (ButtonPlaceBeacon/IdleWorker/General statics, winGetWindowFromId NULL+id, FactionObserver compare, switchToContext 9/0, m_isObserverCommandBar +0x20c, winHide/winEnable, switchControlBarStage DEFAULT, hidePurchaseScience); callers none; manager callee 0x31FD0D now rowed.
enum NameKeyType
{
	NK_INVALID = 0
};

enum ControlBarStages
{
	CONTROL_BAR_STAGE_DEFAULT = 0,
	CONTROL_BAR_STAGE_LOW = 1,
	CONTROL_BAR_STAGE_HIDDEN = 2
};

enum GameModeType
{
	GAME_LAN = 1,
	GAME_SINGLE = 2,
	GAME_INTERNET = 5
};

enum ControlBarContext
{
	CB_CONTEXT_NONE = 0,
	CB_CONTEXT_OBSERVER_LIST = 9
};

class PlayerTemplate;
class Player
{
public:
	bool isPlayerActive() const;
};
class NameKeyGenerator;
class GameWindow;
class GameWindowManager;
class PlayerTemplateStore;
class GameLogic;
class GameInfo;
class ControlBarSchemeManager;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *str);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class GameWindow
{
public:
	int winHide(bool b);
	int winEnable(bool b);
};

class GameWindowManager
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03(); virtual void s04();
	virtual void s05(); virtual void s06(); virtual void s07(); virtual void s08(); virtual void s09();
	virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
	virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
	virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
	virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34();
	virtual void s35(); virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
	virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43(); virtual void s44();
	virtual void s45(); virtual void s46(); virtual void s47(); virtual void s48(); virtual void s49();
	virtual void s50(); virtual void s51(); virtual void s52(); virtual void s53(); virtual void s54();
	virtual void s55(); virtual void s56(); virtual void s57(); virtual void s58(); virtual void s59();
	virtual GameWindow *winGetWindowFromId(GameWindow *parent, NameKeyType id);
};

extern GameWindowManager *TheWindowManager;

class PlayerTemplateStore
{
public:
	const PlayerTemplate *findPlayerTemplate(NameKeyType key) const;
};

extern PlayerTemplateStore *ThePlayerTemplateStore;

class GameLogic
{
public:
	char _pad[0x110];
	int m_gameMode;
};

extern GameLogic *TheGameLogic;

class GameInfo
{
public:
	virtual void g00(); virtual void g01(); virtual void g02(); virtual void g03(); virtual void g04();
	virtual void g05(); virtual void g06(); virtual void g07(); virtual void g08(); virtual void g09();
	virtual void g10(); virtual void g11(); virtual void g12(); virtual void g13(); virtual void g14();
	virtual void g15(); virtual void g16(); virtual void g17(); virtual void g18();
	virtual bool isMultiPlayer();
};

extern GameInfo *TheGameInfo;

class ControlBarSchemeManager
{
public:
	void setControlBarSchemeByPlayer(Player *p);
	void setControlBarSchemeByPlayerTemplate(const PlayerTemplate *pt, bool useSmall);
};

class ControlBar
{
public:
	void setControlBarSchemeByPlayer(Player *p);
	void setControlBarSchemeByPlayerTemplate(const PlayerTemplate *pt);
	void switchToContext(int ctx, void *param);
	void switchControlBarStage(ControlBarStages stage);
private:
	char _head[0x44];
	ControlBarSchemeManager *m_controlBarSchemeManager;
	char _mid[0x20c - 0x44 - 4];
	bool m_isObserverCommandBar;
};

void Rva0043C96FEnable();

void ControlBar::setControlBarSchemeByPlayerTemplate(const PlayerTemplate *pt)
{
	if (m_controlBarSchemeManager)
		m_controlBarSchemeManager->setControlBarSchemeByPlayerTemplate(pt, false);

	static NameKeyType buttonPlaceBeaconID = TheNameKeyGenerator->nameToKey("ControlBar.wnd:ButtonPlaceBeacon");
	static NameKeyType buttonIdleWorkerID = TheNameKeyGenerator->nameToKey("ControlBar.wnd:ButtonIdleWorker");
	static NameKeyType buttonGeneralID = TheNameKeyGenerator->nameToKey("ControlBar.wnd:ButtonGeneral");
	GameWindow *buttonPlaceBeacon = TheWindowManager->winGetWindowFromId(0, buttonPlaceBeaconID);
	GameWindow *buttonIdleWorker = TheWindowManager->winGetWindowFromId(0, buttonIdleWorkerID);
	GameWindow *buttonGeneral = TheWindowManager->winGetWindowFromId(0, buttonGeneralID);

	if (pt == ThePlayerTemplateStore->findPlayerTemplate(TheNameKeyGenerator->nameToKey("FactionObserver")))
	{
		m_isObserverCommandBar = true;
		switchToContext(CB_CONTEXT_OBSERVER_LIST, 0);

		if (buttonPlaceBeacon)
			buttonPlaceBeacon->winHide(true);
		if (buttonIdleWorker)
			buttonIdleWorker->winHide(true);
		if (buttonGeneral)
			buttonGeneral->winEnable(false);
	}
	else
	{
		switchToContext(CB_CONTEXT_NONE, 0);
		m_isObserverCommandBar = false;

		if (buttonPlaceBeacon)
			buttonPlaceBeacon->winHide((TheGameLogic->m_gameMode != GAME_LAN && TheGameLogic->m_gameMode != GAME_INTERNET) || !TheGameInfo->isMultiPlayer());
		if (buttonIdleWorker)
			buttonIdleWorker->winHide(false);
		if (buttonGeneral)
		{
			buttonGeneral->winHide(false);
			buttonGeneral->winEnable(true);
		}
	}
	switchControlBarStage(CONTROL_BAR_STAGE_DEFAULT);

	Rva0043C96FEnable();
}

// ZH ControlBar.cpp setControlBarSchemeByPlayer at the verified BFME 1
// reference ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f. Target 31C40E..31C5C8
// has the same three button names and observer/active control flow. Layouts
// come from the matched template overload above; native calls independently
// reach manager 31FE49 and the Player active predicate 2AA231. No BFME 1
// lifted body is used. The game's original method name is donor evidence.
void ControlBar::setControlBarSchemeByPlayer(Player *p)
{
	if (m_controlBarSchemeManager)
		m_controlBarSchemeManager->setControlBarSchemeByPlayer(p);

	static NameKeyType buttonPlaceBeaconID = TheNameKeyGenerator->nameToKey("ControlBar.wnd:ButtonPlaceBeacon");
	static NameKeyType buttonIdleWorkerID = TheNameKeyGenerator->nameToKey("ControlBar.wnd:ButtonIdleWorker");
	static NameKeyType buttonGeneralID = TheNameKeyGenerator->nameToKey("ControlBar.wnd:ButtonGeneral");
	GameWindow *buttonPlaceBeacon = TheWindowManager->winGetWindowFromId(0, buttonPlaceBeaconID);
	GameWindow *buttonIdleWorker = TheWindowManager->winGetWindowFromId(0, buttonIdleWorkerID);
	GameWindow *buttonGeneral = TheWindowManager->winGetWindowFromId(0, buttonGeneralID);

	if (!p->isPlayerActive())
	{
		m_isObserverCommandBar = true;
		switchToContext(CB_CONTEXT_OBSERVER_LIST, 0);

		if (buttonPlaceBeacon)
			buttonPlaceBeacon->winHide(true);
		if (buttonIdleWorker)
			buttonIdleWorker->winHide(true);
		if (buttonGeneral)
			buttonGeneral->winEnable(false);
	}
	else
	{
		switchToContext(CB_CONTEXT_NONE, 0);
		m_isObserverCommandBar = false;

		if (buttonPlaceBeacon)
			buttonPlaceBeacon->winHide((TheGameLogic->m_gameMode != GAME_LAN && TheGameLogic->m_gameMode != GAME_INTERNET) || !TheGameInfo->isMultiPlayer());
		if (buttonIdleWorker)
			buttonIdleWorker->winHide(false);
		if (buttonGeneral)
		{
			buttonGeneral->winHide(false);
			buttonGeneral->winEnable(true);
		}
	}
	switchControlBarStage(CONTROL_BAR_STAGE_DEFAULT);

}
