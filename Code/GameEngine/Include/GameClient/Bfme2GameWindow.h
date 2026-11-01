#pragma once
// Native GameWindow ABI: ctor3145F0, dtor314A0C, tableC0BBCC11slots.
// Extent218 independently bounded by Apt secondary ctor51268C atthis+218.
// Structural field/method labels retain unknown identities; no donor layout.
#include "Bfme2WinInstanceData.h"
class GameWindow;
class GameWindowManager;
class BfmeAptScreenBase;
class GameWindowChild;
class GameFont;
class GadgetCreateView;
class Gadget210;
class Rva0031468C;
enum WindowMsgHandledType;
typedef WindowMsgHandledType (__cdecl *GameWindowNativeInputFunc)(GameWindow *, unsigned int, unsigned int, unsigned int);
typedef void (__cdecl *GameWindowNativeDrawFunc)(GameWindow *, WinInstanceData *);
typedef void (__cdecl *GameWindowNativeTooltipFunc)(GameWindow *, WinInstanceData *, unsigned int);
class GameWindow
{
 friend class GameWindowManager;
 friend class BfmeAptScreenBase;
protected:
	virtual ~GameWindow();
public:
	virtual WindowMsgHandledType input(unsigned int, unsigned int, unsigned int);
public:
	virtual WindowMsgHandledType bfmeGoEHCb(unsigned int, unsigned int, unsigned int);
public:
	virtual int draw(void *);
public:
	virtual int tooltip(WinInstanceData *, unsigned int);
public:
	virtual int rva0009FD78();
public:
	virtual bool vslot6() const;
public:
	virtual void *fetchCreateInstance() = 0;
public:
	virtual bool vslot8() const;
public:
	virtual bool vslot9() const;
public:
	virtual bool vslot10();
public:
	GameWindow *winPointInChild(int, int, bool, bool = false);
public:
	int winSetSize(int width, int height);
public:
	void winSetFont(GameFont *);
public:
	void winSetEnabledTextColors(int color, int borderColor);
public:
	void winSetDisabledTextColors(int color, int borderColor);
public:
	void winSetHiliteTextColors(int color, int borderColor);
public:
	void winSetIMECompositeTextColors(int color, int borderColor);
public:
	GameWindow *winPointInAnyChild(int x, int y, bool ignoreHidden, bool ignoreEnableCheck);
public:
	unsigned int winClearStatus(unsigned int status);
public:
	int winSetInputFunc(GameWindowNativeInputFunc input);
public:
	int winSetDrawFunc(GameWindowNativeDrawFunc draw);
public:
	int winSetTooltipFunc(GameWindowNativeTooltipFunc tooltip);
public:
	int winSetCallbacks(GameWindowNativeInputFunc input, GameWindowNativeDrawFunc draw, GameWindowNativeTooltipFunc tooltip);
public:
	int winGetScreenPosition(int *x, int *y);
public:
	int winGetSize(int *width, int *height);
public:
	int winGetPosition(int *x, int *y);
public:
	bool winIsHidden(void);
public:
	int winSetPosition(int x, int y);
public:
	void orderPairs();
protected:
	GameWindow *findFirstLeaf();
protected:
	GameWindow *findLastLeaf();
protected:
	GameWindow *findPrevLeaf();
protected:
	GameWindow *findNextLeaf();
public:
	GameWindowChild *m_positionSink;
public:
	unsigned int m_status;
public:
	int m_sizeX;
public:
	int m_sizeY;
public:
	int m_regionLoX;
public:
	int m_regionLoY;
public:
	int m_regionHiX;
public:
	int m_regionHiY;
public:
	int m_cursorX;
public:
	int m_cursorY;
public:
	void *m_userData;
public:
	WinInstanceData m_instData;
public:
	void *m_inputData;
public:
	void *m_bfmeInputExtra;
public:
	GameWindowNativeInputFunc m_inputFunc;
public:
	void *m_system;
public:
	GameWindowNativeDrawFunc m_drawFunc;
public:
	GameWindowNativeTooltipFunc m_tooltipFunc;
public:
	void *m_bfmeCallbackExtra;
public:
	int m_bfmeCallbackExtra2;
public:
	GameWindow *m_next;
public:
	GameWindow *m_prev;
public:
	GameWindow *m_parent;
public:
	GameWindow *m_child;
public:
	void *m_nextLayout;
public:
	void *m_prevLayout;
public:
	Gadget210 *m_210;
public:
	void *m_editData;
public:
	int winBringToTop();
public:
	int winGetCursorPosition(int *x, int *y);
public:
	int winActivate();
public:
	int winHide(bool hide);
public:
	unsigned int winSetStatus(unsigned int status);
public:
	int winEnable(bool enable);
public:
	int winSetParent(int arg);
public:
	void snapshotCreateView(GadgetCreateView *view, bool clear);
public:
	GameWindow();
public:
	unsigned int winGetStyle();
public:
	__declspec(noinline) void winDrawBorder();
};

typedef char Bfme2GameWindow_extent_218[(sizeof(GameWindow)==0x218)?1:-1];
