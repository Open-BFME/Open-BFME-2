// cl: /DNDEBUG /MD /EHs
// ??1Rva00283081@@UAE@XZ, RVA 0x00283081, 84 bytes.
// Dtor twin of 0x004DFED8: vstore 0x008615D4, calls rowed clear 0x002827F3, frees vec buffers
// at +0x10 and +0x4 via rowed free 0x00030830.
// Evidence: same vtable and clear as Rva004DFED8Dtor; caller 0x00283246 deleting dtor; callees all rowed.

// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport.
#define _CRTIMP
#include <stdlib.h>
#undef _CRTIMP

namespace _STL
{
template <class T>
class allocator
{
};

template <class T, class A>
class vector
{
public:
	~vector() { if (m_start) free(m_start); }
	T *m_start;
	T *m_finish;
	T *m_end_of_storage;
	T *erase(T *first, T *last);
};
}

// Element types: clear 0x002827F3 deletes each +0x10 element through rowed dtor
// 0x00281A06; the +0x4 element type is unknown. Neither is void*: retail's unwind
// actions for both members (ehhandler 0x00773BA2) jump to the 14-byte fold
// 0x0007FAB3, not to the ledger's ~vector<void*> at 0x00027370.
struct Rva00281A06;
struct Rva00283081Entry4;

#include "../../Include/GameLogic/Rva002827F3.h"

class Rva00283081
{
public:
	virtual ~Rva00283081();
private:
	_STL::vector<Rva00283081Entry4 *, _STL::allocator<Rva00283081Entry4 *> > m_vec4;
	_STL::vector<Rva00281A06 *, _STL::allocator<Rva00281A06 *> > m_vec10;
};

Rva00283081::~Rva00283081()
{
	((Rva002827F3 *)this)->rva002827F3();
}
