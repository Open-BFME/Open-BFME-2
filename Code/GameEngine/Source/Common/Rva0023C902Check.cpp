// cl: /DNDEBUG /MD
// ?rva0023C902@Rva0023C902@@QAE_NXZ @0x0023C902 34B: thiscall bool check of +0xa8 plus Display slot 0x114.
// Evidence: cmp byte [ecx+0xa8] je false; TheDisplay row plus virtual +0x114 test je false else true; callers 0x0043CBB6 0x004E41E9 0x0050EC50 0x0051B3AE 0x005234D9 unblocks 4.
#include "../../Include/GameClient/Display.h"
class Rva0023C902
{
public:
	int rva0023C902();
private:
	char m_pad[0xa8];
	bool m_a8;
};

int Rva0023C902::rva0023C902()
{
	if (m_a8) {
		if (TheDisplay->isMoviePlaying())
			return 1;
	}
	return 0;
}
