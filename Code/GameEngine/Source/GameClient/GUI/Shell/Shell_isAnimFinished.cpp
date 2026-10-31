// cl: /DNDEBUG /MD /EHsc /Ireference/shims/subsystem_bfme2 /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include
//
// ?isAnimFinished@Shell@@QAE_NXZ @0x0035BE55 58B (4 matched callers pin this name).
// Evidence: neighbors Shell +0x60 in ShellTop.cpp; callees rowed GameWindowTransitionsHandler::isFinished 0x001DBFEE and global 0x00DFDC14 (TheTransitionHandler) plus TheWritableGlobalData +0xB00; callers 0x0050D145 0x0050D162; returns bool.
// Zero Hour's Shell::isAnimFinished has this shape (transition handler first,
// then the animate-window flag and the animate manager).

typedef bool Bool;
#include "subsystem_interface.h"
class GameWindowTransitionsHandler
{
public:
	void reverse(AsciiString groupName);
	bool isFinished();
	virtual void t00();
	virtual void t01();
	virtual void t02();
	virtual void t03();
	virtual void t04();
	virtual void t05();
	virtual void t06();
	virtual void t07();
	virtual void t08();
	virtual void t09();
	virtual void slot0A();
};

// Target DIR32 is 0x00DFDC14; TheAudio is the distinct pointer at 0x00DFE6E8.
extern GameWindowTransitionsHandler *TheTransitionHandler;

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

class GameWindow;
class WindowLayout;
class ShellMenuSchemeManager;
enum AnimTypes
{
	WIN_ANIMATION_NONE = 0,
	WIN_ANIMATION_SLIDE_LEFT = 1
};
class AnimateWindowManager
{
public:
	AnimateWindowManager();
	virtual void *deleteInstance(int flags);
	virtual void a01();
	virtual void a02();
	virtual void a03();
	virtual void a04();
	virtual void a05();
	virtual void a06();
	virtual void a07();
	virtual void a08();
	virtual void reset();
	virtual void update();
	void registerGameWindow(GameWindow *win, AnimTypes animType, Bool needsToFinish, unsigned int ms, unsigned int delayMs);
	void reverseAnimateWindow();
	Bool isReversed() { return m_reverse; }
private:
	char m_pad04[0x14 - 4];
public:
	unsigned char m_14;
private:
	Bool m_reverse; // +0x15
	char m_pad16[0x38 - 0x16];
};

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

bool Shell::isAnimFinished()
{
	if (!TheTransitionHandler->isFinished())
		return false;
	if (m_animateWindowManager == 0)
		return true;
	if (TheWritableGlobalData->m_animateWindows)
		return m_animateWindowManager->m_14 == 0;
	return true;
}
