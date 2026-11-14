// cl: /O1 /MD /EHs
// ??1Rva00523775@@UAE@XZ @0x00523775 137B: Apt-screen dtor with UI hide and free.
// Evidence: callers 0x0052380C; callees rowed _free 0x00030830 plus pin Shell hide 0x0035BF4C plus pin AptGameWindow 0x005126F5; base secondary vptr +0x218 and member +0x288 free; globals g_Va00A04934 TheInGameUI g_Va00A01E48; vtables 0x00867C34 0x00867C30; neighbours ConstIntGetters.
// The base's real two-base prefix: GameWindow218 + secondary58 + tailC.
// The constructor51268C and factory2D1E55 prove its complete27C extent.
#include "../../Include/GameClient/Bfme2GameWindow.h"
#include "../../Include/GameClient/Rva005248D0.h"
class _bfme_AptGameWindow : public GameWindow, public Rva005248D0
{
public: virtual ~_bfme_AptGameWindow();
private: unsigned char tail270[0xC];
};

struct GlobalA04934;
extern GlobalA04934 *g_Va00A04934;

struct GlobalA01E48;
class Shell;
extern Shell *TheShell;

#include "../../Include/GameClient/InGameUI.h"
extern InGameUI *TheInGameUI;

#include "../../Include/GameClient/Shell.h"

// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport.
#define _CRTIMP
#include <stdlib.h>
#undef _CRTIMP

struct AutoFreePtr
{
	void *p;
	~AutoFreePtr() { if (p) free(p); }
};

class __multiple_inheritance AptStrategicPlayerStatus
	: public _bfme_AptGameWindow
{
public:
	virtual ~AptStrategicPlayerStatus();
private:
	char m_pad27C[0x288 - 0x27C];
	AutoFreePtr m_288;
};

AptStrategicPlayerStatus::~AptStrategicPlayerStatus()
{
	if ((void *)this == (void *)g_Va00A04934) {
		g_Va00A04934 = (GlobalA04934 *)0;
		if (TheInGameUI)
			TheInGameUI->rva0029AC03(0);
		if (TheShell)
			((Shell *)TheShell)->hide(false);
	}
}

// AptMessenger::~AptMessenger (WorldBuilder name lead for 0x005125ED; the
// body clears AptMessenger::s_instance) from scalar-delete51265C and
// tableC659A0. Native111 consumes singletonE046B8, vector28C and free280.
// Primary/secondary table stores remain at0/218 through the real base view.
class Rva0051211C
{
public: ~Rva0051211C();
private: unsigned char consumed[12];
};
class AptMessenger : public _bfme_AptGameWindow
{
public: virtual ~AptMessenger();
 static AptMessenger *s_instance;
private:
 unsigned char unknown27C[4];
 AutoFreePtr m_280;
 unsigned char unknown284[8];
 Rva0051211C m_28C;
};
AptMessenger::~AptMessenger()
{
 if (this == AptMessenger::s_instance)
  AptMessenger::s_instance = 0;
}
