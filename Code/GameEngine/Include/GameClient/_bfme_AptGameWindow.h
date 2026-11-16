// _bfme_AptGameWindow: the Apt screen base. Ctor 0x0051268C installs vftables 0x008659E8 at +0 and 0x008659E4 at +0x218
// and stores the 4/4/1-byte fields at +0x270/+0x274/+0x278; factory 0x002D1E55 allocates 0x27C. Dtor 0x005126F5 releases
// the AsciiString at +0x270, then the Rva005248D0 and GameWindow bases. Field names are unproven and spell their offsets.
#ifndef CANONICAL__BFME_APTGAMEWINDOW_H
#define CANONICAL__BFME_APTGAMEWINDOW_H

#include "Bfme2GameWindow.h"
#include "Rva005248D0.h"
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

class _bfme_AptGameWindow : public GameWindow, public Rva005248D0
{
public:
	_bfme_AptGameWindow(void *context);
	virtual ~_bfme_AptGameWindow();
	int rva0051274F(int a1, unsigned int a2, unsigned int a3);

private:
	AsciiString m_270;

protected:
	// AptDisconnectScreen::rva00512CE9 (0x00512CE9) reads it from the derived screen.
	int m_274;

private:
	char m_278;
};

typedef char _bfme_AptGameWindow_extent_27C[(sizeof(_bfme_AptGameWindow) == 0x27C) ? 1 : -1];

#endif // CANONICAL__BFME_APTGAMEWINDOW_H
