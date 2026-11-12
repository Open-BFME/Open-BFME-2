// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHs -Ireference/open-bfme-1/game/GameEngine/Source/GameClient/GUI /Ireference/open-bfme-1/game/GameEngine/Include/GameClient

// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport.
#define _CRTIMP
#include <stdlib.h>
#undef _CRTIMP

#include "../../../Include/GameClient/BfmeAptScreenBaseLayout.h"

#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"


class _bfme_AptGameWindow
{
public:
	virtual ~_bfme_AptGameWindow();

private:
	BfmeAptScreenBaseLayout<> m_primaryStorage;
};

#include "../../../Include/GameClient/BfmeAptFunctorMarker.h"

#include "../../../Include/GameClient/Shell.h"

void _bfme_closeAptScreen(const AsciiString &name);

struct GlobalA01E48;
class Shell;
extern Shell *TheShell;
int g_00E04914;

// This member owns CRT storage. The terrain TU's similarly named helper
// owns GameFree storage; they do not represent one native class.
struct AptScoreScreenBuffer
{
	void *p;
	~AptScoreScreenBuffer() { if (p) free(p); }
};

class __multiple_inheritance AptScoreScreen
	: public _bfme_AptGameWindow, public BfmeAptFunctorMarker
{
public:
	virtual ~AptScoreScreen();

private:
	char m_pad21C[100];
	int m_280;
	char m_pad284[8];
	AptScoreScreenBuffer m_28c;
	char m_pad290[32];
	AsciiString m_2b0;
	char m_pad2b4[12];
	AsciiString m_2c0;
};

// ??1AptScoreScreen@@UAE@XZ (was rowed as Rva0051CBC6), RVA 0x0051CBC6, 188 bytes.
// AptScoreScreen dtor: resets both vtables, closes AptScoreScreen via
// InitGadgets literal, hides Shell when slot 0x280 is empty, clears
// g_00E04914, releases string slots 0x2c0 and 0x2b0, frees pointer 0x28c,
// then the rowed _bfme_AptGameWindow base dtor. Evidence: vtable stores
// 0x00866FAC and 0x00866FA8, string AptScoreScreen::InitGadgets, callees
// 0x00037BA0 0x0041149A 0x00036410 0x0035BF4C 0x00030830 0x005126F5 all rowed
// or pinned, caller 0x0051CE56 is the ??_G deleting dtor.
AptScoreScreen::~AptScoreScreen()
{
	_bfme_closeAptScreen(AsciiString("AptScoreScreen::InitGadgets"));
	if (m_280 == 0 && TheShell != 0)
		((Shell *)TheShell)->hide(false);
	g_00E04914 = 0;
}
