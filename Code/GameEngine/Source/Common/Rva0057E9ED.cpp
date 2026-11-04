// cl: /DNDEBUG /MD
// ?rva0057E9ED@Rva0057E97A@@QAEXIH@Z @0x0057E9ED 34B
// Bounded store to the +0xB4 int vector of the Rva0057E97A window holder:
// size is (finish-start)/4 via sub+sar, index in [esp+4] checked against it,
// then start[index] = value in [esp+8]. Same class and flags as the neighbour
// 0x0057E97A TU (which reads the same +0xB4 flags), next is a vector<ObjectID>
// TU. Evidence: packet disasm, single caller 0x00441ECE, prev/next rows.
#include "../GameClient/GUI/GUICallbacks/Apt/AptMpGameRulesView.h"

void Rva0057E97A::rva0057E9ED(unsigned int index, int value)
{
	int **flags = &m_enableFlags; // begin, end
	int size = flags[1] - flags[0];
	if (index >= (unsigned int)size)
		return;
	_ReadWriteBarrier();
	flags[0][index] = value;
}
