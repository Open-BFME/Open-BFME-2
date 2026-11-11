// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
//
// ?rva002268B0@Rva002268B0@@QAEXPAX@Z, retail 0x002268B0 45B.
// Tree free twin of 0x00226829: recursive child at +0x0C then free node and iterate sibling at +0x08.
// Evidence: self-recursive call at 0x2268C2; free row at 0x30830; caller 0x2299D6;
// identical shape to Rva00226829TreeFree.cpp; prev Rva00226883 row.

// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport.
#define _CRTIMP
#include <stdlib.h>
#undef _CRTIMP

#include "../../Include/Common/Rva002268B0.h"

struct Rva002268B0Node
{
	char m_pad[8]; // +0x00..0x07
	Rva002268B0Node *m_next; // +0x08 sibling
	Rva002268B0Node *m_child; // +0x0C child
};

void Rva002268B0::rva002268B0(void *node)
{
	if (!node)
		return;
	Rva002268B0Node *cur = (Rva002268B0Node *)node;
	do {
		rva002268B0(cur->m_child);
		Rva002268B0Node *next = cur->m_next;
		free(cur);
		cur = next;
	} while (cur);
}
