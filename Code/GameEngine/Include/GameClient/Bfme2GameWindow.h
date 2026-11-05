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
class Image;
class UnicodeString;
struct GameWindowEditData;
class GadgetCreateView;
class Gadget210;
class Rva0031468C;
enum WindowMsgHandledType;
typedef WindowMsgHandledType (__cdecl *GameWindowNativeInputFunc)(GameWindow *, unsigned int, unsigned int, unsigned int);
typedef WindowMsgHandledType (__cdecl *GameWindowNativeSystemFunc)(GameWindow *, unsigned int, unsigned int, unsigned int);
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
	WindowMsgHandledType winSendSystemMsg(unsigned int, unsigned int, unsigned int);
	WindowMsgHandledType winSendInputMsg(unsigned int, unsigned int, unsigned int);
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
	GameWindowNativeSystemFunc m_system;
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
public:
	__forceinline void deleteInstance() { ::delete this; }
	void *winGetUserData();
	void winSetUserData(void *data);
	unsigned int winGetStatus();
	GameWindow *winGetParent();
	GameWindow *winGetChild();
	GameWindow *winGetNext();
	GameWindow *winGetPrev();
	GameWindow *winGetOwner();
	int winGetWindowId();
	int winSetWindowId(int value);
	WinInstanceData *winGetInstanceData();
	int winSetInstanceData(WinInstanceData *data);
	GameFont *winGetFont();
	int winNextTab();
	int winPrevTab();
	int winSetEnabledImage(int index, const Image *image);
	int winSetEnabledColor(int index, int color);
	int winSetEnabledBorderColor(int index, int color);
	int winSetDisabledImage(int index, const Image *image);
	int winSetDisabledColor(int index, int color);
	int winSetDisabledBorderColor(int index, int color);
	int winSetHiliteImage(int index, const Image *image);
	int winSetHiliteColor(int index, int color);
	int winSetHiliteBorderColor(int index, int color);
	const Image *winGetEnabledImage(int index);
	int winGetEnabledColor(int index);
	int winGetEnabledBorderColor(int index);
	const Image *winGetDisabledImage(int index);
	int winGetDisabledColor(int index);
	int winGetDisabledBorderColor(int index);
	const Image *winGetHiliteImage(int index);
	int winGetHiliteColor(int index);
	int winGetHiliteBorderColor(int index);
	int winGetEnabledTextColor();
	int winGetEnabledTextBorderColor();
	int winGetDisabledTextColor();
	int winGetDisabledTextBorderColor();
	int winGetHiliteTextColor();
	int winGetHiliteTextBorderColor();
	int winGetIMECompositeTextColor();
	int winGetIMECompositeBorderColor();
	int winGetTextLength();
	UnicodeString winGetText();
	void winSetTooltip(UnicodeString tip);
	unsigned char winPointInWindow(int x, int y);
	GameWindowEditData *winGetEditData();
	void setRva003144FD(int value);
	int rva0009DC32(WinInstanceData *data);
};

typedef char Bfme2GameWindow_extent_218[(sizeof(GameWindow)==0x218)?1:-1];
