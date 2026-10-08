// cl: /O1 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
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
// spelling remains unknown, so retain the existing rva0035C7CF name.
// Canonical AsciiString inline forwarding constructs the by-value argument
// in its stack slot. Calling StringBase<char>::isEmpty preserves the native
// worker call; the menu selection has two branches and one shared active write.
#include <stddef.h>

#include "ascii_string.h"

class WindowLayout
{
public:
	virtual void runInit(void *userData) = 0;
	virtual void *deleteInstance(int flags) = 0;
	virtual void s02() = 0;
	virtual void runShutdown(bool*) = 0;
	virtual void s04() = 0;
	virtual void s05() = 0;
	virtual void s06() = 0;
	virtual void s07() = 0;
	virtual void destroyWindows() = 0;
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

class Shell
{
private:
	unsigned char _pad[12];
	WindowLayout *m_screenStack[16];
	int m_screenCount;
	bool m_pendingPush;
	bool m_pendingPop;
	unsigned char _pad5253[2];
	bool m_clearBackground;
	unsigned char _pad5557[3];
	AsciiString m_pendingPushName;
	bool m_isShellActive;
	bool m_shellMapOn;
	unsigned char _pad5E5F[2];
	void *m_animateWindowManager;
public:
	WindowLayout *top();
	void push(AsciiString name, bool flag);
	void rva0035C7CF(bool flag);
	void rva0035BF4C(bool shutdownImmediate);
};

extern "C" __declspec(dllimport) char *__cdecl getenv(const char *name);

class IMEManager {public:
virtual void slot0()=0;
virtual void slot1()=0;
virtual void slot2()=0;
virtual void slot3()=0;
virtual void slot4()=0;
virtual void slot5()=0;
virtual void slot6()=0;
virtual void slot7()=0;
virtual void slot8()=0;
virtual void slot9()=0;
virtual void slot10()=0;
virtual void slot11()=0;
virtual void slot12()=0;
virtual void slot13()=0;
virtual void slot14()=0;
virtual void detatch()=0;};extern IMEManager*TheIMEManager;
class Display;extern Display*TheDisplay;
class W3DDisplay {public:void rva0025D2F6();};
class AudioManager {public:
virtual void slot0()=0;
virtual void slot1()=0;
virtual void slot2()=0;
virtual void slot3()=0;
virtual void slot4()=0;
virtual void slot5()=0;
virtual void slot6()=0;
virtual void slot7()=0;
virtual void slot8()=0;
virtual void slot9()=0;
virtual void slot10()=0;
virtual void slot11()=0;
virtual void slot12()=0;
virtual void slot13()=0;
virtual void slot14()=0;
virtual void slot15()=0;
virtual void slot16()=0;
virtual void slot17()=0;
virtual void slot18()=0;
virtual void slot19()=0;
virtual void slot20()=0;
virtual void slot21()=0;
virtual void slot22()=0;
virtual void slot23()=0;
virtual void slot24()=0;
virtual void slot25()=0;
virtual void slot26()=0;
virtual void slot27()=0;
virtual void slot28()=0;
virtual void slot29()=0;
virtual void slot30()=0;
virtual void slot31()=0;
virtual void slot32()=0;
virtual void slot33()=0;
virtual void slot34()=0;
virtual void slot35(int,int,int)=0;};extern AudioManager*TheAudio;
class Rva0035BD3F {public:void rva0035BD3F();};

void Shell::rva0035C7CF(bool flag)
{
	GlobalData *g = TheWritableGlobalData;
	if (!reinterpret_cast<const StringBase<char> *>(&g->m_unk_abc)->isEmpty() && !g->m_unk_ac5)
		return;
	if (flag)
	{
		WindowLayout *t = top();
		if (t != 0) {
			t->runInit(0);
			g = TheWritableGlobalData;
		}
	}
	if (!g->m_unk_af0 && m_screenCount == 0)
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
