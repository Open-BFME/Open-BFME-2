// cl: /DNDEBUG /MD /EHsc
// ?Rva0041154FHide@@YAXXZ, retail 0x0041154F 90B.
// Window-video table walk over global at 0x00E02FE4 via first 0x00427195 and
// rowed next 0x00411084, hiding visible windows and setting status 0x10000000.
// Same first/next shape as Rva00411523Walk; node GameWindow at +0x18 flag at +0x2C.
// Evidence: winIsHidden 0x313CD9 winHide 0x313C64 winSetStatus 0x313CE3 caller 0x22246C.
#include "../../Include/GameClient/Rva000411084.h"

#include "../../Include/GameLogic/Rva000427195.h"

// VA 0x00E02FE4: the component-window table AptComponentWindowLookup.cpp owns.
extern unsigned int AptComponentWindowDataTableStorage[5];

#include "../../Include/GameClient/Bfme2GameWindow.h"

struct Rva0041154FNode
{
	char m_pad[0x18];
	GameWindow *m_window;
	char m_pad2[0x2C - 0x18 - 4];
	unsigned char m_2C;
};

void Rva0041154FHide()
{
	Rva000411084 iter;
	reinterpret_cast<Rva000427195 *>(AptComponentWindowDataTableStorage)->first(&iter);
	while (iter.m_current != 0) {
		Rva0041154FNode *node = (Rva0041154FNode *)iter.m_current;
		if (node->m_2C == 0) {
			GameWindow *win = node->m_window;
			if (win != 0) {
				if (!win->winIsHidden()) {
					win->winHide(true);
					win->winSetStatus(0x10000000);
				}
			}
		}
		iter.next();
	}
}

// The global(s) below are defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
