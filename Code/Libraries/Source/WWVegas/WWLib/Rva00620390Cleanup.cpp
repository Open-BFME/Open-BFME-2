// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// ?rva00620390@Rva00620390@@QAEXPAX@Z, RVA 0x00620390, 51 bytes.
// Evidence: unlock missing callee of 0x6206E0 and 0x620A00 which reset sentinel
// at [esi] plus size +4 after calling here; self-recursive plus _free 0x30830
// plus loop on +8 with nop lea matches O2 tree cleanup; +8/+0xC links.

extern "C" void __cdecl free(void *block);

struct Rva00620390Node
{
	char m_pad[8];
	Rva00620390Node *m_next8;
	Rva00620390Node *m_nextC;
};

class Rva00620390
{
public:
	void rva00620390(void *node);
};

void Rva00620390::rva00620390(void *nodePtr)
{
	Rva00620390Node *cur = (Rva00620390Node *)nodePtr;
	while (cur)
	{
		rva00620390(cur->m_nextC);
		Rva00620390Node *next = cur->m_next8;
		free(cur);
		cur = next;
	}
}
