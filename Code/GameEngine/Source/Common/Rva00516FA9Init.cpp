// cl: /Ireference/shims/bfme2_ascii /MD
#include "ascii_string.h"

// ?rva00516FA9@@YAXXZ 60B @0x00516FA9.
// Target facts: Ghidra bounds 0x00516FA9-0x00516FE4; early return on the
// global at VA 0x00E04904; then a direct call to 0x005BD82E, an
// "OnlineShell.apt" push through rowed Shell::push, and a call to rowed
// 0x002233A6 with argument 1 on the Apt window manager global. The helper's
// identity and purpose remain unknown.
struct Rva00517048;
extern Rva00517048 *g_Va00A04904;

class Shell
{
public:
	void push(AsciiString screen, bool flag);
};
extern Shell *TheShell;

class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

class Rva00222A8BTarget
{
public:
	void rva002233A6(int mode);
};

void rva005BD82E();

void rva00516FA9()
{
	if (g_Va00A04904 != 0)
		return;
	rva005BD82E();
	TheShell->push(AsciiString("OnlineShell.apt"), false);
	((Rva00222A8BTarget *)g_bfmeAptWindowManager)->rva002233A6(1);
}
