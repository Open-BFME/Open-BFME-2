// cl: /DNDEBUG /MD /EHsc /Ireference/shims/subsystem_bfme2 /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include
// ??0Shell@@QAE@XZ @0x0035BFBC (203B): chain ctor calls baseConstruct 0x001B4E63 then sets vtable 0x00816208; clears stack +0xC-0x4B; String set at +0x58 with empty string; NEW AnimateWindowManager 0x38 at +0x60 via 0x0053B550; NEW Rva002007D5 8 at +0x64 via 0x00200774.
// Retail's unwind map destroys the SubsystemInterface-style base (0x001B4E74)
// in state 0 and the narrow string at +0x58 in state 1, then guards both
// allocations (states 2 and 3). The string therefore has a destructor; the
// banked 0.93 attempt gave it none and lost state 1.
// The constructor and ShellTop's destructor use the rowed subsystem base.
typedef bool Bool;
#define BFME_ASCII_DTOR_DECL
#include "subsystem_interface.h"

class WindowLayout;
class GameWindow;
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

class Rva002007D5
{
public:
	~Rva002007D5();
	Rva002007D5();
	char m_pad00[0x8];
};

class ShellMenuSchemeManager;
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
	virtual ~Shell();	// rowed elsewhere; declared so this unit binds to it
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
	virtual void reset();	// slot 9, as ShellTop.cpp's view names it
	void shutdownComplete(WindowLayout *screen, Bool impendingPush);
	void push(AsciiString filename, bool shutdownImmediate);
	Bool showShellMap(Bool useShellMap, Bool restartShellGame);
	WindowLayout *getSaveLoadMenuLayout();
	WindowLayout *getPopupReplayLayout();
};

Shell::Shell()
{
	int i;
	m_screenCount = 0;
	for (i = 0; i < 16; i++)
		m_screenStack[i] = 0;
	m_byte52 = 0;
	m_lowLODBackdropDone = 0;
	m_pendingPush = 0;
	m_pendingPop = 0;
	m_clearBackground = 0;
	m_pendingPushName.set("");
	m_isShellActive = true;
	m_shellMapOn = false;
	m_animateWindowManager = new AnimateWindowManager;
	m_schemeManager = reinterpret_cast<ShellMenuSchemeManager *>(new Rva002007D5);
	m_musicHandle = 1;
	m_wantMusic = true;
	m_skipMusicRestart = true;
	m_saveLoadMenuLayout = 0;
	m_popupReplayLayout = 0;
	m_screenCount = 0;
}
