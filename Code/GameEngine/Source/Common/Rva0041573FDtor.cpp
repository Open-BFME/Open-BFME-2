// cl: /Ireference/shims/bfme2_ascii /EHs /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva0041573F@@QAE@XZ @0x004156BC 64B
// Dtor for the Rva0041573F container (copy 0x0041573F 67B): 56 x Rva002390CB
// at +0 via eh vector destructor with rowed ??1Rva002390CB 0x004C9F38, plus
// rowed _Rb_tree900 dtor 0x0025742C at +0x1C0. Same layout as the copy TU.
// Evidence: lea ecx [esi+0x1C0] call rowed tree dtor then push dtor 0x004C9F38
// push 0x38 push 8 push esi call eh vector destructor; __EH_prolog frame with
// and [ebp-4] 0 and or [ebp-4] -1. Callers at 0x00415C0D 0x00415C44 and jmp at
// 0x004156FF; unblocks 0x004156FC 0x00415B91.
#include <map>
#include "ascii_string.h"

class Rva002390CB
{
	void *m_unknown00;
	void *m_owner04;
public:
	~Rva002390CB();
};

struct BfmeStringRecord002CF550
{
	~BfmeStringRecord002CF550();
	AsciiString text;
	Rva002390CB ref;
};

bool operator<(const BfmeStringRecord002CF550 &l, const BfmeStringRecord002CF550 &r);

namespace _STL
{
template <> struct less<BfmeStringRecord002CF550>
{
	bool operator()(const BfmeStringRecord002CF550 &l, const BfmeStringRecord002CF550 &r) const;
};
}

typedef _STL::_Rb_tree<BfmeStringRecord002CF550, BfmeStringRecord002CF550, _STL::_Identity<BfmeStringRecord002CF550>, _STL::less<BfmeStringRecord002CF550>, _STL::allocator<BfmeStringRecord002CF550> > Tree900;

class Rva0041573F
{
public:
	~Rva0041573F();
private:
	Rva002390CB m_arr[56];
	Tree900 m_tree;
};

Rva0041573F::~Rva0041573F()
{
}
