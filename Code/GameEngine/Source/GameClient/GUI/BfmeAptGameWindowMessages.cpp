// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// The Apt screen base's window message handler (vslot 2 of its vftable
// 0x00C659E8; the ctor is BfmeAptGameWindowConstructor.cpp, the dtor
// BfmeAptGameWindowDestructor.cpp). Screen handlers such as
// AptMessenger::rva00511990 and the LAN lobby's 0x0044484A call it for the
// messages they do not answer themselves.

#include "ascii_string.h"
#include "unicode_string.h"

class GameWindow
{
protected:
	virtual ~GameWindow();

private:
	unsigned char m_pad004[0x218 - 4];
};

class Rva005248D0
{
public:
	virtual ~Rva005248D0();

private:
	unsigned char m_pad004[0x58 - 4];
};

// The Apt window manager (VA 0x00DFE4CC) and the window holding its focus.
class BfmeAptWindowManager
{
public:
	unsigned char m_pad000[0x314];
	void *m_focus; // +0x314
};

extern BfmeAptWindowManager *g_bfmeAptWindowManager;

class _bfme_AptGameWindow : public GameWindow, public Rva005248D0
{
public:
	_bfme_AptGameWindow(void *context);
	virtual ~_bfme_AptGameWindow();
	int rva0051274F(int message, unsigned int data1, unsigned int data2);

private:
	AsciiString m_filename; // +0x270
	int m_274;
	char m_278;
};

// Retail 0x0051274F, 136 bytes: answers messages 1 and 2 (destroying the
// focused window clears the window manager's focus), 0x17 (data1 1 takes the
// focus and sets *data2, any other value drops it) and 0x1D with 0x7D0 (the
// owning Apt window, stored to *data2); everything else is not handled.
int _bfme_AptGameWindow::rva0051274F(int message, unsigned int data1, unsigned int data2)
{
	UnicodeString unused;
	switch (message)
	{
	case 1:
		break;
	case 2:
		if (g_bfmeAptWindowManager != 0 && g_bfmeAptWindowManager->m_focus == this)
			g_bfmeAptWindowManager->m_focus = 0;
		break;
	case 0x17:
		if (data1 == 1)
		{
			*(bool *)data2 = true;
			g_bfmeAptWindowManager->m_focus = this;
		}
		else if (g_bfmeAptWindowManager->m_focus == this)
			g_bfmeAptWindowManager->m_focus = 0;
		break;
	case 0x1D:
		if (data1 != 0x7D0)
			return 0;
		*(void **)data2 = this;
		break;
	default:
		return 0;
	}
	return 1;
}
