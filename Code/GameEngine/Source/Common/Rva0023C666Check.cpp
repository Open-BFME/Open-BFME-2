// cl: /DNDEBUG /MD
//
// ?rva0023C666@Rva0023C666@@QAE_NXZ @0x0023C666, 62B.
// Mode-plus-helper predicate: true when this mode word at +0x110 is 0 or 6,
// otherwise needs helper behind 0x00E02290 with getData()==1 and helper state
// at +0xE74 of 0 or 6. Same +0x110/+0xE74/global as neighbour
// BfmeGlob939D::bfmeCall939D at 0x0023C6FD; owner unproven so Rva class.
// Retail: mov eax,[ecx+0x110] test/je cmp6/je; mov ecx,[global] test/je;
// call getData cmp1/jne; mov eax,[global] mov eax,[eax+0xE74] test/je cmp6/je;
// shared xor-eax false and xor-inc true tails.
// Evidence: 6 callers pass this through; global+helper offsets match
// BfmeConv939Call939D; callee row ?getData@NetWrapperCommandMsg@@QAEPAEXZ.

struct Bfme939Helper
{
	char m_pad[0xE74];
	int m_state; // +0xE74
};

class RecorderClass; extern RecorderClass *TheRecorder;

#include "../../Include/GameNetwork/NetWrapperCommandMsg.h"

class Rva0023C666
{
public:
	bool rva0023C666();

private:
	char m_pad[0x110];
	int m_mode; // +0x110
};

bool Rva0023C666::rva0023C666()
{
	return m_mode == 0 || m_mode == 6
		|| (((Bfme939Helper *)TheRecorder) != 0
			&& ((NetWrapperCommandMsg *)((Bfme939Helper *)TheRecorder))->getData() == (unsigned char *)1
			&& (((Bfme939Helper *)TheRecorder)->m_state == 0 || ((Bfme939Helper *)TheRecorder)->m_state == 6));
}
