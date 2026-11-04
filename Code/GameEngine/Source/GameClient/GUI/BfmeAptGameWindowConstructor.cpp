// cl: /O1 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// ??0_bfme_AptGameWindow@@QAE@PAX@Z @0x0051268C 94B ctor for 0x27C AptGameWindow via rowed base 0x00313847 plus matched 0x002D2C34 plus vtables C659E8/C659E4 plus 270/274/278 inits evidence factory 0x002D1E55 size 0x27C and dtor 0x005126F5 same vtables
// Retail destroys this GameWindow-derived screen base through the rowed
// protected ~GameWindow 0x00314A0C (the unwind funclet / vtable slot 0 target).
#include "../../../Include/GameClient/Bfme2GameWindow.h"

#include "ascii_string.h"

// The native primary base occupies GameWindow's 0x218-byte extent.
// Its context constructor is rowed at 0x00313847; teardown is GameWindow's.
class __declspec(novtable) BfmeAptScreenBase : public GameWindow
{
public:
    BfmeAptScreenBase(void *context);
    virtual ~BfmeAptScreenBase() {}
};

#include "../../../Include/GameClient/Rva005248D0.h"

class _bfme_AptGameWindow : public BfmeAptScreenBase, public Rva005248D0 {
public:
	virtual ~_bfme_AptGameWindow();
private:
	AsciiString filename270;
	int m_274;
	char m_278;
public:
	_bfme_AptGameWindow(void *context);
public:
	int rva0051274F(int message, unsigned int data1, unsigned int data2);
};

_bfme_AptGameWindow::_bfme_AptGameWindow(void *context)
    : BfmeAptScreenBase(context)
{
    m_274 = -1;
    m_278 = 0;
}
