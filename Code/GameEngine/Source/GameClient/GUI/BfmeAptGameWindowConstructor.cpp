// cl: /O1 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// ??0_bfme_AptGameWindow@@QAE@PAX@Z @0x0051268C 94B ctor for 0x27C AptGameWindow via rowed base 0x00313847 plus matched 0x002D2C34 plus vtables C659E8/C659E4 plus 270/274/278 inits evidence factory 0x002D1E55 size 0x27C and dtor 0x005126F5 same vtables
// Retail destroys this GameWindow-derived screen base through the rowed
// protected ~GameWindow 0x00314A0C (the unwind funclet / vtable slot 0 target).
#include "../../../Include/GameClient/Bfme2GameWindow.h"

class __declspec(novtable) BfmeAptScreenBase
{
public:
	BfmeAptScreenBase(void *context);
	virtual ~BfmeAptScreenBase() { ((GameWindow *)this)->GameWindow::~GameWindow(); }
private:
	char m_pad[0x218 - 4];
};

#include "../../../Include/GameClient/Rva005248D0.h"

extern "C" const void *const __identifier("??_7_bfme_AptGameWindow@@6BGameWindow@@@")[];
extern "C" const void *const __identifier("??_7_bfme_AptGameWindow@@6BRva005248D0@@@")[];

class _bfme_AptGameWindow
{
public:
	_bfme_AptGameWindow(void *context);
private:
	BfmeAptScreenBase m_primary;
	char m_sec[0x58];
	int m_270;
	int m_274;
	char m_278;
};

_bfme_AptGameWindow::_bfme_AptGameWindow(void *context)
	: m_primary(context)
{
	Rva005248D0 *sec = (Rva005248D0 *)m_sec;
	sec->Rva005248D0::Rva005248D0();
	*(const void **)this = __identifier("??_7_bfme_AptGameWindow@@6BGameWindow@@@");
	*(const void **)sec = __identifier("??_7_bfme_AptGameWindow@@6BRva005248D0@@@");
	m_270 = 0;
	m_274 = -1;
	m_278 = 0;
}
