// cl: /DNDEBUG /MD
//
// ?rva0023C666@Rva0023C666@@QAEHXZ @0x0023C666, 62B.
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

extern Bfme939Helper *g_bfme939Helper;

class NetWrapperCommandMsg
{
public:
	unsigned char *getData();
};

class Rva0023C666
{
public:
	int rva0023C666();

private:
	char m_pad[0x110];
	int m_mode; // +0x110
};

int Rva0023C666::rva0023C666()
{
	if (m_mode == 0 || m_mode == 6)
		return true;
	if (g_bfme939Helper == 0)
		return false;
	if (((NetWrapperCommandMsg *)g_bfme939Helper)->getData() != (unsigned char *)1)
		return false;
	int state = g_bfme939Helper->m_state;
	if (state == 0 || state == 6)
		return true;
	return false;
}
