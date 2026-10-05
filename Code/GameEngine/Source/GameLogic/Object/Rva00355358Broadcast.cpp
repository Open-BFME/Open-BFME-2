// cl: /Ireference/shims/bfme2_ascii /MD /O1 /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// ?rva00355358@AiOrdersManager@@QAEXHPAX@Z @0x00355358 52B: walks circular list at [holder+4] calling rowed AiOrdersManager 0x00355183.
// Evidence: retail mov edi [esp+0x14] mov eax [edi+4] loop calling pin 0x00355183 with [esp+0x14] and [eax+0x74]; ret 8.

class AiOrdersManager
{
public:
	void rva00355183(int a, int b);
	void rva00355358(int a, void *holder);
};

struct BcastNode
{
	BcastNode *m_next;
	char m_pad4[4];
	void *m_08;
};

void AiOrdersManager::rva00355358(int a, void *holder)
{
	BcastNode *head = *(BcastNode **)((char *)holder + 4);
	BcastNode *cur = head->m_next;
	if (cur == head)
		return;
	do {
		void *content = cur->m_08;
		if (content)
			rva00355183(a, *(int *)((char *)content + 0x74));
		cur = cur->m_next;
	} while (cur != *(BcastNode **)((char *)holder + 4));
}
