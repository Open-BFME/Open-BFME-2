// ?rva00422CF3HasOne@@YG_NPAX@Z
// partial score=0.8 date=2026-10-06
// cl: /O1 /MD
// ?rva00422CF3HasOne@@YG_NPAX@Z @0x00422CF3 41B
extern unsigned char g_Va00DC84F5;
struct Rva00422CF3Node
{
	Rva00422CF3Node *m_next;
};
bool __stdcall rva00422CF3HasOne(void *arg)
{
	unsigned count = 0;
	if (g_Va00DC84F5 == 0)
		return false;
	Rva00422CF3Node *head = *(Rva00422CF3Node **)arg;
	Rva00422CF3Node *cur = head->m_next;
	if (cur == head)
		return false;
	do {
		cur = cur->m_next;
		count++;
	} while (cur != head);
	if (count < 1)
		return false;
	return true;
}
