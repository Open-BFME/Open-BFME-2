// cl: /DNDEBUG /MD /EHsc /Ireference/shims/subsystem_bfme2 /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include
// BFME1 clean donor6583b3c1ff21db4a561285717028fdafc780b7db:
// game/GameEngine/Source/GameClient/GUI/Shell/Shell.cpp hideShell(void)
// supplies top-layout shutdown, IME detach and shell-active reset semantics.
// Native35BF4C..35BFBC/112B adds a bool argument gating the shutdown, no
// clear-background write, GlobalData+AF0/display69B25D2F6 cleanup and audio.
// Rowed13B Shell::top35BD7E plus receiver+5C establish the Shell prefix;
// all named global DIR32s verify. WindowLayout slot3 gets an actual true
// local bool; cl reuses the dead argument's high byte at EBP+B naturally.
// The target's original method name is unknown: the existing hide(bool) pin
// is a caller ABI spelling, not proof of Zero Hour's hide-all-layouts method.
// GlobalData+AF0 meaning and AudioManager slot35 method name remain unknown.
// The native audio arguments are three words2/1/0. The full30B audio-handle
// release35BD3F independently verifies and is reached with the same receiver.
// Shell activation35C7CF..35C872/163B follows the BFME1 clean donor
// game/GameEngine/Source/GameClient/GUI/Shell/Shell_showShell_Thunk.cpp at
// 34f59164f6d1efd413c5fd37f4894ec834c3c0fe. BFME2 WB Shell.cpp showShell
// and native calls independently establish top/runInit and menu selection.
// BFME2 native fields: initial-file stringABC, alternate-shell flagAC5,
// shell-map flagAF0; Shell screenCount4C and active5C. Original target
// spelling remains unknown, so retain the existing showShell name.
// Canonical AsciiString inline forwarding constructs the by-value argument
// in its stack slot. Calling StringBase<char>::isEmpty preserves the native
// worker call; the menu selection has two branches and one shared active write.
#include <stddef.h>

typedef bool Bool;
#include "subsystem_interface.h"

class WindowLayout
{
public:
	virtual void runInit(void *userData) = 0;
	virtual void *deleteInstance(int flags) = 0;
	virtual void runUpdate(void *userData) = 0;
	virtual void runShutdown(bool *flag) = 0;
	virtual void s04() = 0;
	virtual void s05() = 0;
	virtual void s06() = 0;
	virtual void s07() = 0;
	virtual void destroyWindows() = 0;
	bool isHidden() { return m_hidden; }
	AsciiString getFilename();
private:
	char _pad14[0x10];
	bool m_hidden;
};

class GlobalData
{
public:
	unsigned char _pad1[0xabc];
	AsciiString m_unk_abc;
	unsigned char _pad2[0xac5 - (0xabc + 4)];
	bool m_unk_ac5;
	unsigned char _pad3[0xaf0 - (0xac5 + 1)];
	bool m_unk_af0;
	unsigned char _pad4[0xB00 - (0xaf0 + 1)];
	bool m_animateWindows;
};

extern GlobalData *TheWritableGlobalData;
extern class Shell *TheShell;

class GameWindow;
class WindowLayout;
class ShellMenuSchemeManager;
enum AnimTypes
{
	WIN_ANIMATION_NONE = 0,
	WIN_ANIMATION_SLIDE_LEFT = 1
};
class AnimateWindowManager;
class Shell : public SubsystemInterface
{
private:
	WindowLayout *m_screenStack[16]; // +0x0C
	int m_screenCount; // +0x4C
	Bool m_pendingPush; // +0x50
	Bool m_pendingPop; // +0x51
	Bool m_byte52; // +0x52
	Bool m_lowLODBackdropDone; // +0x53
	Bool m_clearBackground; // +0x54
	unsigned char _pad5557[3];
	AsciiString m_pendingPushName; // +0x58
	Bool m_isShellActive; // +0x5C
	Bool m_shellMapOn; // +0x5D
	unsigned char _pad5E5F[2];
	AnimateWindowManager *m_animateWindowManager; // +0x60
	ShellMenuSchemeManager *m_schemeManager; // +0x64
	unsigned int m_musicHandle; // +0x68
	Bool m_wantMusic; // +0x6C
	Bool m_skipMusicRestart; // +0x6D
	unsigned char _pad6E[2];
	WindowLayout *m_saveLoadMenuLayout; // +0x70
	WindowLayout *m_popupReplayLayout; // +0x74
protected:
	void linkScreen(WindowLayout *screen);
	void unlinkScreen(WindowLayout *screen);
	void doPop(Bool impendingPush);
	void doPush(AsciiString layoutFile);
public:
	Shell();
	bool isAnimFinished();
	void showShell(bool flag);
	void rva0035BF4C(bool shutdownImmediate);
	virtual ~Shell();
	virtual void update();
	WindowLayout *top();
	Bool rva0035BD5D();
	void rva0035C2B9();
	WindowLayout *findScreenByFilename(AsciiString filename);
	void registerWithAnimateManager(GameWindow *win, AnimTypes animType, Bool needsToFinish, unsigned int delayMS);
	void reverseAnimatewindow();
	Bool isAnimReversed();
	void loadScheme(AsciiString name);
	void pop();
	void popImmediate();
	virtual void reset();
	void shutdownComplete(WindowLayout *screen, Bool impendingPush);
	void push(AsciiString filename, bool shutdownImmediate);
	Bool showShellMap(Bool useShellMap, Bool restartShellGame);
	WindowLayout *getSaveLoadMenuLayout();
	WindowLayout *getPopupReplayLayout();
};

extern "C" __declspec(dllimport) char *__cdecl getenv(const char *name);

class IMEManager
{
public:
	virtual void m00() = 0;
	virtual void m04() = 0;
	virtual void m08() = 0;
	virtual void m0C() = 0;
	virtual void m10() = 0;
	virtual void m14() = 0;
	virtual void m18() = 0;
	virtual void m1C() = 0;
	virtual void m20() = 0;
	virtual void m24() = 0;
	virtual void m28() = 0;
	virtual void m2C() = 0;
	virtual void m30() = 0;
	virtual void m34() = 0;
	virtual void m38() = 0;
	virtual void detatch() = 0;
	virtual void m40() = 0;
	virtual void m44() = 0;
	virtual void m48() = 0;
	virtual void m4C() = 0;
	virtual void *m50() = 0;
};
extern IMEManager*TheIMEManager;
class Display;extern Display*TheDisplay;
class W3DDisplay
{
public:
	void rva0025D2F6();
};
class AudioManager { public:
    virtual void slot0() = 0;
    virtual void slot1() = 0;
    virtual void slot2() = 0;
    virtual void slot3() = 0;
    virtual void slot4() = 0;
    virtual void slot5() = 0;
    virtual void slot6() = 0;
    virtual void slot7() = 0;
    virtual void slot8() = 0;
    virtual void slot9() = 0;
    virtual void slot10() = 0;
    virtual void slot11() = 0;
    virtual void slot12() = 0;
    virtual void slot13() = 0;
    virtual void slot14() = 0;
    virtual void slot15() = 0;
    virtual void slot16() = 0;
    virtual void slot17() = 0;
    virtual void slot18() = 0;
    virtual void slot19() = 0;
    virtual void slot20() = 0;
    virtual void slot21() = 0;
    virtual void slot22() = 0;
    virtual void slot23() = 0;
    virtual void slot24() = 0;
    virtual void slot25() = 0;
    virtual void slot26() = 0;
    virtual void slot27() = 0;
    virtual void slot28() = 0;
    virtual void slot29() = 0;
    virtual void slot30() = 0;
    virtual void slot31() = 0;
    virtual void slot32() = 0;
    virtual void slot33() = 0;
    virtual void slot34() = 0;
    virtual void slot35(int, int, int) = 0;
    virtual void slot36() = 0;
    virtual void slot37() = 0;
    virtual void slot38() = 0;
    virtual void slot39() = 0;
    virtual void slot40() = 0;
    virtual void slot41() = 0;
    virtual void slot42() = 0;
    virtual void slot43() = 0;
    virtual void slot44() = 0;
    virtual void slot45() = 0;
    virtual void slot46() = 0;
    virtual void slot47() = 0;
    virtual void slot48() = 0;
    virtual void slot49() = 0;
    virtual void slot50() = 0;
    virtual void slot51() = 0;
    virtual bool slot52(unsigned int handle) = 0;
};
extern AudioManager*TheAudio;
class Rva0035BD3F
{
public:
	void rva0035BD3F();
};

void Shell::showShell(bool flag)
{
	GlobalData *globalData = TheWritableGlobalData;
	if (!reinterpret_cast<const StringBase<char> *>(&globalData->m_unk_abc)->isEmpty() && !globalData->m_unk_ac5)
		return;
	if (flag)
	{
		WindowLayout *windowLayout = top();
		if (windowLayout != 0) {
			windowLayout->runInit(0);
			globalData = TheWritableGlobalData;
		}
	}
	if (!globalData->m_unk_af0 && m_screenCount == 0)
	{
		if (getenv("_EA_RTS_HEADLESS") != 0 || TheWritableGlobalData->m_unk_ac5)
			TheShell->push(AsciiString("Menus/LanLobbyMenu.wnd"), false);
		else
			TheShell->push(AsciiString("MainMenu.apt"), false);
	}
	m_isShellActive = true;
}

void Shell::rva0035BF4C(bool shutdownImmediate) {
 WindowLayout*layout=top();
 if(layout && shutdownImmediate) {bool immediate=true;layout->runShutdown(&immediate);}
 if(TheIMEManager)TheIMEManager->detatch();
 m_isShellActive=false;
 if(!TheWritableGlobalData->m_unk_af0)reinterpret_cast<W3DDisplay*>(TheDisplay)->rva0025D2F6();
 reinterpret_cast<Rva0035BD3F*>(this)->rva0035BD3F();
 TheAudio->slot35(2,1,0);
}

#pragma comment(linker,"/alternatename:?hide@Shell@@QAEX_N@Z=?rva0035BF4C@Shell@@QAEX_N@Z")
