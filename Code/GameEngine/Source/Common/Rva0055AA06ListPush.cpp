// cl: /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0055AA06@Rva0055AA06@@QAEXPBUCoord3D@@@Z @ 0x0055AA06, 49 bytes.
// Push TheGameLogic+0x40 onto list at +0x18 inc count at +0x1C copy 12B to +0x20.
// Evidence: retail lea-push-call push_back 0x5548F inc [esi+0x1C] lea edi [esi+0x20] movsd x3; caller 0x39CF0A.
extern class GameLogic *TheGameLogic;

#include <list>

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct GameLogic0055AA06
{
	char m_pad[0x40];
	unsigned int m_val;
};
#define TheGameLogic (*(GameLogic0055AA06 **)&TheGameLogic)

class Rva0055AA06
{
public:
	void rva0055AA06(const Coord3D *src);
	void rva0055AA37();
	char m_pad0[0x4];
	unsigned int m_unk04;
	char m_pad1[0x10];
	_STL::list<int, _STL::allocator<int> > m_list;
	int m_count;
	Coord3D m_pos;
};

void Rva0055AA06::rva0055AA06(const Coord3D *src)
{
	int tmp = TheGameLogic->m_val;
	m_list.push_back(tmp);
	++m_count;
	m_pos = *src;
}

// ?rva0055AA37@Rva0055AA06@@QAEXXZ @ 0x0055AA37, 49 bytes.
// Drain list at +0x18 while front+0x04 ult TheGameLogic+0x40 dec count at +0x1C.
// Evidence: retail lea edi plus18 jmp cond mov eax triple-deref plus8 add plus04 cmp TheGameLogic plus0x40 jae exit pop_front 0x37BCF9; caller 0x39D3FC.
void Rva0055AA06::rva0055AA37()
{
	while (!m_list.empty() && m_list.front() + m_unk04 < TheGameLogic->m_val) {
		m_list.pop_front();
		--m_count;
	}
}
