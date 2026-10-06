// cl: /MD
// ?rva0046A9D2@Rva0046A9D2@@QAEXPAURva0046A9D2Node@@@Z 0x0046A9D2 45B evidence: unlock frees via rowed free 0x30830 plus self recursion caller 0x46AB8B in clear 0x46AB7D
extern "C" void __cdecl free(void *block);
struct Rva0046A9D2Node
{
	char m_pad[8];
	Rva0046A9D2Node *m_next;
	Rva0046A9D2Node *m_child;
};
class Rva0046A9D2
{
public:
	void rva0046A9D2(Rva0046A9D2Node *head);
};
void Rva0046A9D2::rva0046A9D2(Rva0046A9D2Node *head)
{
	Rva0046A9D2Node *node = head;
	if (node == 0)
		return;
	do {
		rva0046A9D2(node->m_child);
		Rva0046A9D2Node *next = node->m_next;
		free(node);
		node = next;
	} while (node != 0);
}
