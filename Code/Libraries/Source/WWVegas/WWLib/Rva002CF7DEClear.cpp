// cl: /MD
// ?rva002CF7DE@Rva002CF7DE@@QAEXXZ @0x002CF7DE 41B.
// Tree clear: if size at +4 !=0 erase root at header+4 via rowed 0x002CF302,
// reset header left/right to self and root to 0, zero size, ret. Same 41B
// shape as the rowed clear 0x002CF7B5. Callers at 0x002D01B5 0x0033BD9D
// 0x0033E15F unblocks 0x0033BD88 0x002D01A9 0x0033E102.
struct Rva002CF302Node
{
	unsigned char m_pad00[8];
	Rva002CF302Node *m_left;
	Rva002CF302Node *m_right;
};

struct Rva002CF302
{
	void eraseSubtree(Rva002CF302Node *x);
};

struct Rva002CF7DEHeader
{
	unsigned char m_pad00[4];
	Rva002CF302Node *m_root;
	void *m_left;
	void *m_right;
};

#include "../../../../GameEngine/Include/Common/Rva002CF7DE.h"

void Rva002CF7DE::rva002CF7DE()
{
	if (m_size != 0) {
		((Rva002CF302 *)this)->eraseSubtree(((Rva002CF7DEHeader *)m_header)->m_root);
		((Rva002CF7DEHeader *)m_header)->m_left = m_header;
		((Rva002CF7DEHeader *)m_header)->m_root = 0;
		((Rva002CF7DEHeader *)m_header)->m_right = m_header;
		m_size = 0;
	}
}
