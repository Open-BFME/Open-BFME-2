// cl: /O1 /MD
//
// ?rva00422CF3HasOne@@YG_NPAX@Z @0x00422CF3 41B: __stdcall bool over a
// pointer to a circular list head. False while the byte flag 0x00DC84F5 is
// clear; otherwise counts the nodes after the head (an unsigned count, as
// the jae compare shows) and answers whether there is at least one.
// Identity unproven; the global and node type keep address-derived names.
extern unsigned char g_00DC84F5;
struct Rva00422CF3Node
{
	Rva00422CF3Node *m_next;
};
bool __stdcall rva00422CF3HasOne(void *arg)
{
	if (!g_00DC84F5)
		return false;
	Rva00422CF3Node *head = *(Rva00422CF3Node **)arg;
	unsigned int count = 0;
	for (Rva00422CF3Node *cur = head->m_next; cur != head; cur = cur->m_next)
		++count;
	if (count >= 1)
		return true;
	return false;
}
