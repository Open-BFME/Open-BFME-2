// cl: /O1 /arch:SSE /DNDEBUG /MD /EHsc
// ?top@Shell@@QAEPAVWindowLayout@@XZ @ 0x0035BD7E (13B). Donor ZH GeneralsMD Shell.h top plus BFME1 Shell.cpp top; caller Shell push @0x0035C74A calls top then hidden check then runShutdown slot 3; prev Rva0035BD7BGet next GadgetTextEntryValidateCharacter.
class AsciiString;
class WindowLayout
{
public:
	virtual void runInit(void *userData) = 0;
	virtual void *deleteInstance(int flags) = 0;
	virtual void runUpdate(void *userData) = 0;
	virtual void s03(bool *flag) = 0;
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
	virtual void m3C() = 0;
	virtual void m40() = 0;
	virtual void m44() = 0;
	virtual void m48() = 0;
	virtual void m4C() = 0;
	virtual void *m50() = 0;
};

extern IMEManager *TheIMEManager;

class GameSpyInfoInterface;
extern GameSpyInfoInterface *TheGameSpyInfo;

void Rva00548C1ACleanup();

typedef bool Bool;

class GameWindow;
enum AnimTypes
{
	WIN_ANIMATION_NONE = 0,
	WIN_ANIMATION_SLIDE_LEFT = 1
};

class AnimateWindowManager
{
public:
	virtual void *deleteInstance(int flags) = 0;
	virtual void a01() = 0;
	virtual void a02() = 0;
	virtual void a03() = 0;
	virtual void a04() = 0;
	virtual void a05() = 0;
	virtual void a06() = 0;
	virtual void a07() = 0;
	virtual void a08() = 0;
	virtual void reset() = 0;
	virtual void update() = 0;
	void registerGameWindow(GameWindow *win, AnimTypes animType, Bool needsToFinish, unsigned int ms, unsigned int delayMs);
	void reverseAnimateWindow();
};

class GameEngineDeletingBase
{
public:
	virtual ~GameEngineDeletingBase();
private:
	char m_pad04[8];
};

class Rva0035BD3F
{
public:
	void rva0035BD3F();
};

class Rva002007D5
{
public:
	~Rva002007D5();
};

struct GlobalData
{
	unsigned char _pad[0xB00];
	Bool m_animateWindows;
};

extern GlobalData *TheGlobalData;

class ShellMenuSchemeManager;

template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	void releaseBuffer();
	BfmeStringData<T> *m_data;
public:
	StringBase() : m_data(0) {}
	~StringBase() { releaseBuffer(); }
	void set(const T *text);
	void set(const StringBase<T> &other);
};

// Existing public narrow teardown spelling resolves to the verified
// 133-byte releaseBuffer worker at RVA 0x36410. Wide teardown is unchanged.
template <> StringBase<char>::~StringBase();
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")


class AsciiString : public StringBase<char>
{
public:
	AsciiString() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	~AsciiString() {}
	bool isEmpty() const { return m_data == 0 || m_data->length == 0; }
	int compareNoCase(const AsciiString &s) const throw();
	AsciiString &operator=(const AsciiString &other) { set(other); return *this; }
};

class GameWindowManager
{
public:
	virtual void d00() = 0;
	virtual void d01() = 0;
	virtual void d02() = 0;
	virtual void d03() = 0;
	virtual void d04() = 0;
	virtual void d05() = 0;
	virtual void d06() = 0;
	virtual void d07() = 0;
	virtual void d08() = 0;
	virtual void d09() = 0;
	virtual void d10() = 0;
	virtual void d11() = 0;
	virtual void d12() = 0;
	virtual void d13() = 0;
	virtual void d14() = 0;
	virtual void d15() = 0;
	virtual void d16() = 0;
	virtual void d17() = 0;
	virtual void d18() = 0;
	virtual void d19() = 0;
	virtual void d20() = 0;
	virtual void d21() = 0;
	virtual void d22() = 0;
	virtual void d23() = 0;
	virtual void d24() = 0;
	virtual void d25() = 0;
	virtual void d26() = 0;
	virtual void d27() = 0;
	virtual void d28() = 0;
	virtual void d29() = 0;
	virtual void d30() = 0;
	virtual void d31() = 0;
	virtual WindowLayout *winCreateLayout(AsciiString filename) = 0;
};

extern GameWindowManager *TheWindowManager;

class Shell : public GameEngineDeletingBase
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
	unsigned int _pad6C; // +0x6C
	WindowLayout *m_saveLoadMenuLayout; // +0x70
	WindowLayout *m_popupReplayLayout; // +0x74
protected:
	void linkScreen(WindowLayout *screen);
	void unlinkScreen(WindowLayout *screen);
	void doPop(Bool impendingPush);
	void doPush(AsciiString layoutFile);
public:
	virtual ~Shell();
	virtual void update();
	WindowLayout *top();
	Bool rva0035BD5D();
	void rva0035C2B9();
	WindowLayout *findScreenByFilename(AsciiString filename);
	void registerWithAnimateManager(GameWindow *win, AnimTypes animType, Bool needsToFinish, unsigned int delayMS);
	void reverseAnimatewindow();
	void loadScheme(AsciiString name);
	void rva0035BEC7();
	void rva0035BF0E();
	void rva0035C16A();
	void shutdownComplete(WindowLayout *screen, Bool impendingPush);
	void push(AsciiString filename, bool shutdownImmediate);
};

class ShellMenuSchemeManager
{
public:
	void setShellMenuScheme(AsciiString name);
	void update();
};

// BFME 2's Shell::update additions: the low-LOD shell map backdrop and the
// transition it fades in with.
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);
class Image;
class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};
extern ImageCollection *TheMappedImageCollection;
class BfmeStrVM0
{
public:
	void rva0025C72C(int image, int arg, float x0, float y0, float x1, float y1);
};
struct ShellDisplayView
{
	unsigned char m_pad000[0x114];
	Bool m_byte114;
};
extern ShellDisplayView *TheDisplay;
class GameWindowTransitionsHandler
{
public:
	virtual void t00(); virtual void t01(); virtual void t02(); virtual void t03();
	virtual void t04(); virtual void t05(); virtual void t06(); virtual void t07();
	virtual void t08(); virtual void t09();
	virtual void slot0A();
	void reverse(AsciiString groupName);
};
extern GameWindowTransitionsHandler *TheTransitionHandler;

WindowLayout *Shell::top()
{
	if (m_screenCount == 0)
		return 0;
	return m_screenStack[m_screenCount - 1];
}

// ?update@Shell@@UAEXXZ @ 0x0035C566 (334B), slot 10 of the Shell vftable
// 0x00816208 (slot 9 is the rowed reset-like rva0035C16A). Zero Hour's timed
// layout update (30 per second via a static timeGetTime stamp), without the
// m_background teardown; the scheme manager's update is the empty folded
// 0x000B3FD0. BFME 2 then shows the "ShellMapLowLOD" backdrop once when the
// shell map is off, and finally runs 0x0035BD5D / 0x0035C2B9 (unrowed Shell
// members, pinned from this body) while the shell map is off.
void Shell::update()
{
	static int lastUpdate = timeGetTime();
	static const int shellUpdateDelay = 30;  // try to update 30 frames a second
	int now = timeGetTime();

	//
	// we keep the shell updates fixed in time so that we can write consitent animation
	// speeds during the screen update functions
	//
	if( now - lastUpdate >= ((1000.0f / shellUpdateDelay ) - 1) )
	{

		// run the updates for every window layout on the stack
		for( int i = m_screenCount - 1; i >= 0; i-- )
			m_screenStack[ i ]->runUpdate( 0 );

		// Update the animate window manager
		m_animateWindowManager->update();

		m_schemeManager->update();

		// mark last time we ran the updates
		lastUpdate = now;

	}  // end if

	if( !m_lowLODBackdropDone && m_byte52 && !m_shellMapOn )
	{
		m_lowLODBackdropDone = true;
		AsciiString name( "ShellMapLowLOD" );
		const Image *image = TheMappedImageCollection->findImageByName( name );
		if( image )
		{
			TheDisplay->m_byte114 = true;
			((BfmeStrVM0 *)TheDisplay)->rva0025C72C( (int)image, 0, 0.0f, 0.0f, 1.0f, 1.0f );
			TheTransitionHandler->reverse( AsciiString( "FadeInGameMovie_NoAudio" ) );
			TheTransitionHandler->slot0A();
		}
	}

	if( !m_shellMapOn && !rva0035BD5D() )
		rva0035C2B9();

}  // end update

// ?findScreenByFilename@Shell@@QAEPAVWindowLayout@@VAsciiString@@@Z @ 0x0035C6B4
// (150B). Zero Hour's body: walk all sixteen stack slots from +0x0C and return
// the first screen whose filename (WindowLayout::getFilename, a by-value
// AsciiString getter folded at 0x00564DF2) compares equal ignoring case
// (AsciiString::compareNoCase 0x00006A00). No direct reference in retail.
// Retail keeps no unwind state across the compareNoCase call while the
// getFilename temporary is live, so the view declares that leaf throw().
WindowLayout *Shell::findScreenByFilename(AsciiString filename)
{

	if (filename.isEmpty())
		return 0;

	// search screen list
	WindowLayout *screen;
	int i;
	for( i = 0; i < 16; i++ )
	{

		screen = m_screenStack[ i ];
		if( screen && filename.compareNoCase(screen->getFilename()) == 0 )
			return screen;

	}  // end for i

	return 0;

}  // end findScreenByFilename

// ?linkScreen@Shell@@IAEXPAVWindowLayout@@@Z @ 0x0035BD8B (26B). Donor BFME1 Shell.cpp linkScreen plus ZH Shell.h protected linkScreen; callee of Shell doPush path; prev top next unlink.
void Shell::linkScreen(WindowLayout *screen)
{
	if (screen == 0)
		return;
	if (m_screenCount == 16)
		return;
	m_screenStack[m_screenCount++] = screen;
}

// ?unlinkScreen@Shell@@IAEXPAVWindowLayout@@@Z @ 0x0035BDA5 (29B). Donor BFME1 Shell.cpp unlinkScreen plus ZH Shell.h protected unlinkScreen; callee of Shell doPop path; prev linkScreen next Shell pop work.
void Shell::unlinkScreen(WindowLayout *screen)
{
	if (screen == 0)
		return;
	if (m_screenStack[m_screenCount - 1] == screen)
		m_screenStack[--m_screenCount] = 0;
}

// ?doPop@Shell@@IAEX_N@Z @ 0x0035BDC2 (97B). Donor BFME1 Shell.cpp doPop plus ZH Shell.h protected doPop; callers Shell pop path; vtable WindowLayout runInit slot0 deleteInstance slot1 destroyWindows slot8 and IMEManager detatch slot15.
void Shell::doPop(Bool impendingPush)
{
	WindowLayout *currentTop = top();
	unlinkScreen(currentTop);
	currentTop->destroyWindows();
	::operator delete(currentTop->deleteInstance(0));
	WindowLayout *newTop = top();
	if (newTop && !impendingPush && !m_clearBackground)
		newTop->runInit(0);
	else
		m_clearBackground = false;
	if (TheIMEManager)
		TheIMEManager->m3C();
}

// ?doPush@Shell@@IAEXVAsciiString@@@Z @ 0x0035C3C3 (130B). Donor BFME1 Shell.cpp doPush: GameSpy check then winCreateLayout slot 0x80 then linkScreen then IMEManager detatch slot 0x3C then runInit slot0 then bringForward slot 0x14; caller 0x0035C445 passes pendingPushName; callees linkScreen rowed Rva00548C1ACleanup rowed StringBase copy and releaseBuffer rowed.
void Shell::doPush(AsciiString layoutFile)
{
	if (TheGameSpyInfo)
		Rva00548C1ACleanup();
	WindowLayout *newScreen = TheWindowManager->winCreateLayout(layoutFile);
	linkScreen(newScreen);
	if (TheIMEManager)
		TheIMEManager->m3C();
	newScreen->runInit(0);
	newScreen->s05();
}

// ?shutdownComplete@Shell@@QAEXPAVWindowLayout@@_N@Z @ 0x0035C445 (87B). Donor BFME1 Shell.cpp shutdownComplete: animate reset slot 0x24 then pendingPush via doPush then clear and set empty then pendingPop via doPop; callers 0x0035C7AE 0x0040FD13 0x0050CEA5; callees doPush doPop rowed StringBase copy and set rowed.
void Shell::shutdownComplete(WindowLayout *screen, Bool impendingPush)
{
	m_animateWindowManager->reset();
	if (m_pendingPush) {
		doPush(m_pendingPushName);
		m_pendingPush = false;
		m_pendingPushName.set("");
	} else if (m_pendingPop) {
		doPop(impendingPush);
		m_pendingPop = false;
	}
}

// ?push@Shell@@QAEXVAsciiString@@_N@Z @ 0x0035C74A (133B). Donor BFME1 Shell.cpp push and ZH Shell.cpp push: isEmpty then GameSpy cleanup then count check then pendingPush plus pendingPushName set then top plus hidden check then runShutdown slot3 else shutdownComplete.
void Shell::push(AsciiString filename, bool shutdownImmediate)
{
	if (filename.isEmpty())
		return;
	if (TheGameSpyInfo)
		Rva00548C1ACleanup();
	if (m_screenCount >= 16)
		return;
	m_pendingPush = true;
	m_pendingPushName = filename;
	WindowLayout *currentTop = top();
	if (currentTop && !currentTop->isHidden())
		currentTop->s03(&shutdownImmediate);
	else
		shutdownComplete(0, false);
}

// ?registerWithAnimateManager@Shell@@QAEXPAVGameWindow@@W4AnimTypes@@_NI@Z @ 0x0035BE23 (50B). Donor BFME1 Shell.cpp registerWithAnimateManager plus ZH Shell.h public; GlobalData animateWindows at +0xB00 and animateManager at +0x60; callee AnimateWindowManager registerGameWindow.
void Shell::registerWithAnimateManager(GameWindow *win, AnimTypes animType, Bool needsToFinish, unsigned int delayMS)
{
	if (!m_animateWindowManager)
		return;
	if (!TheGlobalData->m_animateWindows)
		return;
	m_animateWindowManager->registerGameWindow(win, animType, needsToFinish, 500, delayMS);
}

// ?reverseAnimatewindow@Shell@@QAEXXZ @0x0035BE8F 27B
// Guarded tail reverse: null manager or disabled animateWindows returns,
// else tail-jmps to AnimateWindowManager::reverseAnimateWindow.
// Evidence: ecx-first thiscall ret; global TheWritableGlobalData flag +0xB00;
// rowed callee 0x0053B417; callers 0x0050CF0E 0x0050CED9; Shell +0x60.
void Shell::reverseAnimatewindow()
{
	if (!m_animateWindowManager)
		return;
	if (!TheGlobalData->m_animateWindows)
		return;
	return m_animateWindowManager->reverseAnimateWindow();
}

// ?loadScheme@Shell@@QAEXVAsciiString@@@Z @0x0035C49C 74B donor BFME1 Shell.cpp loadScheme forwards by-value name to m_schemeManager+0x64 setShellMenuScheme; callers none; chain via 0x002005DE.
void Shell::loadScheme(AsciiString name)
{
	if (!m_schemeManager)
		return;
	m_schemeManager->setShellMenuScheme(name);
}

// ?rva0035BF0E@Shell@@QAEXXZ retail 0x0035BF0E 62B
// Unlock: top then WindowLayout slot 0xC with bool flag then m_pendingPop=0 then doPop(false) then TheIMEManager m3C.
// Evidence: callees top 0x0035BD7E doPop 0x0035BDC2 rowed, TheIMEManager extern in use, member +0x51 pendingPop, callers 0x0035C087 0x005A20A7.
// ?rva0035BEC7@Shell@@QAEXXZ @0x0035BEC7 71B
// Gap between registerWithAnimateManager and rva0035BF0E: top then GameSpy cleanup then pendingPop=1 then s03 slot 0xC with false flag then IMEManager m3C slot 0x3C.
// Evidence: callees top 0x0035BD7E Rva00548C1ACleanup rowed, TheGameSpyInfo TheIMEManager externs in use, member +0x51, callers in packet.
void Shell::rva0035BEC7()
{
	WindowLayout *layout = top();
	if (TheGameSpyInfo)
		Rva00548C1ACleanup();
	if (!layout)
		return;
	m_pendingPop = true;
	bool flag = false;
	layout->s03(&flag);
	if (TheIMEManager)
		TheIMEManager->m3C();
}
void Shell::rva0035BF0E()
{
	WindowLayout *layout = top();
	if (!layout)
		return;
	m_pendingPop = false;
	bool flag = true;
	layout->s03(&flag);
	doPop(false);
	if (TheIMEManager)
		TheIMEManager->m3C();
}

// ?rva0035C16A@Shell@@QAEXXZ @ 0x0035C16A (42B). Vtable slot 9 of 0x00816208; IMEManager m3C then while m_screenCount rva0035BEC7 then tail reset slot 0x24.
// Evidence: callees TheIMEManager m3C rva0035BEC7 rowed and animate reset slot 9; members +0x4C +0x60; chain via 0x0035BEC7.
void Shell::rva0035C16A()
{
	if (TheIMEManager)
		TheIMEManager->m3C();
	while (m_screenCount != 0)
		rva0035BEC7();
	return m_animateWindowManager->reset();
}

// ??1Shell@@UAE@XZ @ 0x0035C087 (227B). Shell dtor: pops screens via top/rva0035BF0E loop then animate deleteInstance+delete scheme delete layouts destroy+deleteInstance+delete audio string base. Evidence: vtable 0x00816208 callers 0x0035C54A deleting dtor callees top rva0035BF0E scheme 0x002007D5 releaseBuffer 0x00036410 base 0x001B4E74 audio 0x0035BD3F BFME1 ShellDestructor donor.
inline Shell::~Shell()
{
	WindowLayout *cur = top();
	while (cur != 0) {
		rva0035BF0E();
		cur = top();
	}
	if (m_animateWindowManager)
		::operator delete(m_animateWindowManager->deleteInstance(0));
	m_animateWindowManager = 0;
	if (m_schemeManager)
		delete (Rva002007D5 *)m_schemeManager;
	m_schemeManager = 0;
	if (m_saveLoadMenuLayout) {
		m_saveLoadMenuLayout->destroyWindows();
		::operator delete(m_saveLoadMenuLayout ? m_saveLoadMenuLayout->deleteInstance(0) : 0);
		m_saveLoadMenuLayout = 0;
	}
	if (m_popupReplayLayout) {
		m_popupReplayLayout->destroyWindows();
		::operator delete(m_popupReplayLayout ? m_popupReplayLayout->deleteInstance(0) : 0);
		m_popupReplayLayout = 0;
	}
	((Rva0035BD3F *)this)->rva0035BD3F();
}

// ?TheGlobalData@@3PAUGlobalData@@A: the global at this VA is ?TheGlobalData@@3PAVGlobalData@@A; this name is an alias for it.
#pragma comment(linker, "/alternatename:?TheGlobalData@@3PAUGlobalData@@A=?TheGlobalData@@3PAVGlobalData@@A")
#pragma comment(linker, "/alternatename:?g_Va009FE758@@3PAVGlobal9FE758@@A=?TheGlobalData@@3PAVGlobalData@@A")
#pragma comment(linker, "/alternatename:?g_00DFE758@@3PAURva00DFE758Holder@@A=?TheGlobalData@@3PAVGlobalData@@A")
#pragma comment(linker, "/alternatename:?TheWritableGlobalData@@3PAUGlobalData@@A=?TheGlobalData@@3PAVGlobalData@@A")
#pragma comment(linker, "/alternatename:?g_rampageGlobal@@3PAUGlobalWithB8@@A=?TheGlobalData@@3PAVGlobalData@@A")
// ?TheGlobalData@@3PAUGlobalData@@A: the global at VA 0xdfe758 is ?TheGlobalData@@3PAVGlobalData@@A.
#pragma comment(linker, "/alternatename:?TheGlobalData@@3PAUGlobalData@@A=?TheGlobalData@@3PAVGlobalData@@A")
#pragma inline_depth(0)
// ?bfmeEmitShellTop@@YAXPAVShell@@@Z present-unmatched
void bfmeEmitShellTop(Shell *p)
{
	p->Shell::~Shell();
}
#pragma inline_depth()
