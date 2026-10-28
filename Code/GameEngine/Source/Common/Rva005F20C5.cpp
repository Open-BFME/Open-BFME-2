// cl: /MD
// ?erase@Rva005F20C5@@QAEXPAURva005F20C5Node@@@Z, retail 0x005F20C5, 45 bytes.
// Evidence: unlock lane; recursive self-call at 0x005F20D7 plus game free row 0x00030830; callers at 0x005F20D7 self and 0x005F2100 in 0x005F20F2; node +8 next plus +0xC child freed in loop.

// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport.
#define _CRTIMP
#include <stdlib.h>
#undef _CRTIMP

struct Rva005F20C5Node
{
	char m_pad00[4];
	Rva005F20C5Node *m_parent;
	Rva005F20C5Node *m_left;
	Rva005F20C5Node *m_right;
};

class Rva005F20C5
{
public:
	void erase(Rva005F20C5Node *node);
	void rva005F20F2();
private:
	Rva005F20C5Node *m_head00;
	int m_count04;
};

void Rva005F20C5::erase(Rva005F20C5Node *node)
{
	if (node == 0)
		return;
	Rva005F20C5Node *cur = node;
	do {
		erase(cur->m_right);
		Rva005F20C5Node *next = cur->m_left;
		free(cur);
		cur = next;
	} while (cur != 0);
}

void Rva005F20C5::rva005F20F2()
{
	if (m_count04 == 0)
		return;
	erase(m_head00->m_parent);
	m_head00->m_left = m_head00;
	m_head00->m_parent = 0;
	m_head00->m_right = m_head00;
	m_count04 = 0;
}
