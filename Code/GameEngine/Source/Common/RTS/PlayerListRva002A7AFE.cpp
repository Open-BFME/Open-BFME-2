// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2 /Ireference/shims/moduledata /Ireference/shims/bfmealloc
// ?rva002A7AFE@PlayerList@@QAEXPAX@Z @0x002A7AFE 30B.
// PlayerList fan-out over 20 slots calling rowed armor remove. Evidence:
// chain lane via 0x002AD19E, prev PlayerList::reset same TU, push-imm 0x14
// pop-edi /O1 idiom, frameless dec-jne loop, returns void ret 4.
// The slots are canonical PlayerList::m_players (+0x18, twenty Player
// pointers); the callee 0x002AD19E is a Player member (its armor store at
// Player +0x334) still rowed under the Rva002AD19E view, reached by a cast.
#include "../../../Include/Common/Player.h"
#include "../../../Include/Common/PlayerList.h"

class Rva002AD19E
{
public:
	bool rva002AD19E(void *arg);
};

void PlayerList::rva002A7AFE(void *arg)
{
	Player **slot = m_players;
	int count = 20;
	do {
		((Rva002AD19E *)*slot)->rva002AD19E(arg);
		++slot;
	} while (--count != 0);
}
