// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
//
// ?rva002268B0@Rva002268B0@@QAEXPAX@Z, retail 0x002268B0 45B.
// Tree free twin of 0x00226829: recursive child at +0x0C then free node and iterate sibling at +0x08.
// Evidence: self-recursive call at 0x2268C2; free row at 0x30830; caller 0x2299D6;
// identical shape to Rva00226829TreeFree.cpp; prev Rva00226883 row.

extern "C" void __cdecl free(void *block);

class Rva002268B0
{
public:
	void rva002268B0(void *node);
};

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
