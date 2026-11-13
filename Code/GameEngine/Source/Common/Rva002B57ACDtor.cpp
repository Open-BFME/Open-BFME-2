// cl: /DNDEBUG /MD /EHs
// ??1Rva002B57AC@@QAE@XZ @0x002B626E 56B.
// List destructor for the Rva002B57AC family: clears via the rowed
// rva002B57AC, then the inline head-handle member dtor frees the sentinel
// via the rowed free 0x00030830 with a null guard. Same 56B clear-plus-free
// shape as the rowed ??1Rva001FD42B@@QAE@XZ 0x001FD6BC and the just-landed
// ??1Rva002B5558@@QAE@XZ 0x002B609F; the inline member dtor needs unwind
// across the clear, giving the __EH_prolog frame.
// Callers at 0x002B82F8 and jmp at 0x002B7391; unblocks 0x002B82D5.

// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport. /EHs lets free throw,
// preserving retail's unwind states.
#define _CRTIMP
#include <stdlib.h>
#undef _CRTIMP

#include "../../Include/Common/Node002B44DC.h"

struct Head002B57AC
{
	int m_pad0;
	Node002B44DC *m_node4;
	Head002B57AC *m_next8;
	Head002B57AC *m_prevC;
};

struct Rva002B57ACHeadHandle
{
	~Rva002B57ACHeadHandle()
	{
		if (m_header)
			free(m_header);
	}
	Head002B57AC *m_header;
};

class Rva002B57AC
{
public:
	void rva002B57AC();
	~Rva002B57AC();
private:
	Rva002B57ACHeadHandle m_handle;
	int m_count;
};

Rva002B57AC::~Rva002B57AC()
{
	rva002B57AC();
}

// Native0x002B7391..0x002B7396 tail JMP to sole rowed nonvirtual dtor
// at0x002B626E. Unadjusted receiver no stack args RET0; original wrapper
// name enclosing type and lifetime role remain unknown.
struct Rva002B7391CleanupForward { void cleanup(); };
void Rva002B7391CleanupForward::cleanup()
{
    reinterpret_cast<Rva002B57AC*>(this)->~Rva002B57AC();
}
