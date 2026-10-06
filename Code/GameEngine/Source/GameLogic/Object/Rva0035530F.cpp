// cl: /Ireference/shims/bfme2_ascii /MD /O1 /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// ?rva0035530F@AiOrdersManager@@QAEXHPAX@Z @0x0035530F 73B
// Evidence: AiOrdersManager via rowed pin 0x355183 call with this; holder+4 circular list like rowed 0x355358; switch 0->3 1->2 from sub/dec/je/jne; no callers
class AiOrdersManager
{
public:
	void rva00355183(int a, int b);
	void rva0035530F(int a, void *holder);
};
struct BcastNode
{
	BcastNode *m_next;
	char m_pad4[4];
	void *m_08;
};
void AiOrdersManager::rva0035530F(int a, void *holder)
{
	int code;
	switch (a) {
	case 0:
		code = 3;
		break;
	case 1:
		code = 2;
		break;
	default:
		return;
	}
	BcastNode *head = *(BcastNode **)((char *)holder + 4);
	BcastNode *cur = head->m_next;
	if (cur == head)
		return;
	do {
		void *content = cur->m_08;
		if (content)
			rva00355183(code, *(int *)((char *)content + 0x74));
		cur = cur->m_next;
	} while (cur != *(BcastNode **)((char *)holder + 4));
}
