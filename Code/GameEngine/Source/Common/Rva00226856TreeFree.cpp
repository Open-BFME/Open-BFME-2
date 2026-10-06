// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
//
// ?rva00226856@Rva00226856@@QAEXPAX@Z, retail 0x00226856 45B.
// Tree free twin of 0x00226829: recursive child at +0x0C then free node and iterate sibling at +0x08.
// Evidence: self-recursive call at 0x226868; free row at 0x30830; caller 0x229984;
// identical shape to Rva00226829TreeFree.cpp; prev Rva00226829 row.

extern "C" void __cdecl free(void *block);

class Rva00226856
{
public:
	void rva00226856(void *node);
};

struct Rva00226856Node
{
	char m_pad[8]; // +0x00..0x07
	Rva00226856Node *m_next; // +0x08 sibling
	Rva00226856Node *m_child; // +0x0C child
};

void Rva00226856::rva00226856(void *node)
{
	if (!node)
		return;
	Rva00226856Node *cur = (Rva00226856Node *)node;
	do {
		rva00226856(cur->m_child);
		Rva00226856Node *next = cur->m_next;
		free(cur);
		cur = next;
	} while (cur);
}
