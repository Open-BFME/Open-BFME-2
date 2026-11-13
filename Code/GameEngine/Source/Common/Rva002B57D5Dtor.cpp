// cl: /DNDEBUG /MD /EHs
// ??1Rva002B57D5@@QAE@XZ @0x002B62A6 56B.
// List destructor for the Rva002B57D5 family: clears via the rowed
// rva002B57D5, then the inline head-handle member dtor frees the sentinel
// via the rowed free 0x00030830 with a null guard. Same 56B clear-plus-free
// shape as the rowed ??1Rva001FD42B@@QAE@XZ 0x001FD6BC and siblings
// ??1Rva002B5558@@QAE@XZ 0x002B609F and ??1Rva002B57AC@@QAE@XZ 0x002B626E;
// the inline member dtor needs unwind across the clear, giving the
// __EH_prolog frame.
// Callers at 0x002B82ED and jmp at 0x002B7396; unblocks 0x002B82D5.

// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport. /EHs lets free throw,
// preserving retail's unwind states.
#define _CRTIMP
#include <stdlib.h>
#undef _CRTIMP

#include "../../Include/Common/Node002B4509.h"

struct Head002B57D5
{
	int m_pad0;
	Node002B4509 *m_node4;
	Head002B57D5 *m_next8;
	Head002B57D5 *m_prevC;
};

struct Rva002B57D5HeadHandle
{
	~Rva002B57D5HeadHandle()
	{
		if (m_header)
			free(m_header);
	}
	Head002B57D5 *m_header;
};

class Rva002B57D5
{
public:
	void rva002B57D5();
	~Rva002B57D5();
private:
	Rva002B57D5HeadHandle m_handle;
	int m_count;
};

Rva002B57D5::~Rva002B57D5()
{
	rva002B57D5();
}
