// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// GameLogic window cleanup 0x00376D49..0x00376E92, 329B native RET0.
// Semantic reference: Open-BFME-1 34f59164f6d1efd413c5fd37f4894ec834c3c0fe,
// GameLogicCloseWindows.cpp (0x00396950). The same OptionsMenu names, call
// order, ScriptActions victory/defeat callers and owned-layout cleanup
// establish the relationship. The target method keeps its existing RVA name.
// BFME2 adds tribute/chat/notification calls, the strategic message box, and
// guarded Apt resets. Native offsets 1B8/1BC and slots28/F0/E8 replace donor
// offsets1A4/1A8 and slots14/DC/D4. The explicit global delete reproduces the
// destructor(0) then global free; ordinary delete selects destructor(1).
// All direct callees and globals use existing ledger identities. The folded
// notification slot3 thunk retains its existing no-argument ABI view; its
// return is discarded. Pointer-only views never construct competing vtables.

enum NameKeyType { NAMEKEY_INVALID = 0 };
typedef unsigned int WindowMsgData;
enum { GBM_SELECTED = 0x4008 };

class GameWindow;

class WindowLayout
{
public:
	virtual void vslot00(void);
	virtual ~WindowLayout(void);
	virtual void vslot08(void);
	virtual void vslot0C(void);
	virtual void vslot10(void);
	virtual void vslot14(void);
	virtual void vslot18(void);
	virtual void vslot1C(void);
	virtual void destroyWindows(void);
};

class GameWindowManager
{
public:
	virtual void vslot00(void);
	virtual void vslot04(void);
	virtual void vslot08(void);
	virtual void vslot0C(void);
	virtual void vslot10(void);
	virtual void vslot14(void);
	virtual void vslot18(void);
	virtual void vslot1C(void);
	virtual void vslot20(void);
	virtual void vslot24(void);
	virtual void vslot28(void);
	virtual void vslot2C(void);
	virtual void vslot30(void);
	virtual void vslot34(void);
	virtual void vslot38(void);
	virtual void vslot3C(void);
	virtual void vslot40(void);
	virtual void vslot44(void);
	virtual void vslot48(void);
	virtual void vslot4C(void);
	virtual void vslot50(void);
	virtual void vslot54(void);
	virtual void vslot58(void);
	virtual void vslot5C(void);
	virtual void vslot60(void);
	virtual void vslot64(void);
	virtual void vslot68(void);
	virtual void vslot6C(void);
	virtual void vslot70(void);
	virtual void vslot74(void);
	virtual void vslot78(void);
	virtual void vslot7C(void);
	virtual void vslot80(void);
	virtual void vslot84(void);
	virtual void vslot88(void);
	virtual void vslot8C(void);
	virtual void vslot90(void);
	virtual void vslot94(void);
	virtual void vslot98(void);
	virtual void vslot9C(void);
	virtual void vslotA0(void);
	virtual void vslotA4(void);
	virtual void vslotA8(void);
	virtual void vslotAC(void);
	virtual void vslotB0(void);
	virtual void vslotB4(void);
	virtual void vslotB8(void);
	virtual void vslotBC(void);
	virtual void vslotC0(void);
	virtual void vslotC4(void);
	virtual void vslotC8(void);
	virtual void vslotCC(void);
	virtual void vslotD0(void);
	virtual void vslotD4(void);
	virtual void vslotD8(void);
	virtual void vslotDC(void);
	virtual void vslotE0(void);
	virtual void vslotE4(void);
	virtual int winSendSystemMsg(GameWindow *window, unsigned int msg, WindowMsgData mData1, WindowMsgData mData2);
	virtual void vslotEC(void);
	virtual GameWindow *winGetWindowFromId(GameWindow *window, int id);
};

class ControlBar
{
public:
	void rva0031AD8F(void);
	void hideSpecialPowerShortcut(void);
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

#include "../../Common/GameLogicObjectLookupView.h"

void Rva004E400DEnable();
void Rva0050E9D3Enable();
void Rva004E855CClose();
void Rva004E84ABRun();
void Rva00511730(int);
void Rva00518262Enable();
void Rva0051B11CEnable();
void Rva00437E9C(int);
class Rva005CB260;
class InGameUI { public: Rva005CB260 *rva000CF155(); };
class Rva005CB265 { public: virtual int rva005CB265(); };
class Rva0054CBEFTarget { public: void method(int); };
extern InGameUI *TheInGameUI;
extern int g_Va00E05FAC;

extern ControlBar *TheControlBar;
extern NameKeyGenerator *TheNameKeyGenerator;
extern GameWindowManager *TheWindowManager;
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
extern int g_Va00E04910;
extern int g_Va00A04908;

// ?rva00376D49@GameLogic@@QAEXXZ
void GameLogic::rva00376D49(void)
{
	Rva004E400DEnable();
	Rva0050E9D3Enable();
	Rva004E855CClose();
	Rva004E84ABRun();
	Rva00511730(0);
	TheControlBar->rva0031AD8F();
	TheControlBar->hideSpecialPowerShortcut();
    ((Rva005CB265*)TheInGameUI->rva000CF155())->Rva005CB265::rva005CB265();
    if (g_Va00E05FAC)
        ((Rva0054CBEFTarget*)g_Va00E05FAC)->method(1);
	if (g_Va00A04908)
	{
		Rva00518262Enable();
		((GameWindowManager*)g_bfmeAptWindowManager)->vslot28();
	}
	if (g_Va00E04910)
	{
		Rva0051B11CEnable();
		((GameWindowManager*)g_bfmeAptWindowManager)->vslot28();
	}
	TheWindowManager->vslot28();

	// hide the options menu
	NameKeyType buttonID = TheNameKeyGenerator->nameToKey("OptionsMenu.wnd:ButtonBack");
	GameWindow *button = TheWindowManager->winGetWindowFromId(0, buttonID);
	GameWindow *window = TheWindowManager->winGetWindowFromId(0, TheNameKeyGenerator->nameToKey("OptionsMenu.wnd:OptionsMenuParent"));
	if (window)
		TheWindowManager->winSendSystemMsg(window, GBM_SELECTED, (WindowMsgData)button, buttonID);

	if (m_backgroundPending)
	{
		m_backgroundPending = false;
		if (m_background)
		{
			m_background->destroyWindows();
			::delete m_background;
		}
		else
		{
			Rva00437E9C(0);
		}
	}
	m_background = 0;
}
