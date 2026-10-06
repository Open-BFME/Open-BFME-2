// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
//
// ?rva00226829@Rva00226829@@QAEXPAX@Z, retail 0x00226829 45B.
// Tree free: recursive child at +0x0C then free node and iterate sibling at +0x08.
// Evidence: self-recursive call at 0x22683B; free row at 0x30830; caller 0x22995B;
// identical twins at 0x226856 0x226883 0x2268B0 with same shape; prev GameEngineDestructor row.

extern "C" void __cdecl free(void *block);

class Rva00226829
{
public:
	void rva00226829(void *node);
};

struct Rva00226829Node
{
	char m_pad[8]; // +0x00..0x07
	Rva00226829Node *m_next; // +0x08 sibling
	Rva00226829Node *m_child; // +0x0C child
};

void Rva00226829::rva00226829(void *node)
{
	if (!node)
		return;
	Rva00226829Node *cur = (Rva00226829Node *)node;
	do {
		rva00226829(cur->m_child);
		Rva00226829Node *next = cur->m_next;
		free(cur);
		cur = next;
	} while (cur);
}
