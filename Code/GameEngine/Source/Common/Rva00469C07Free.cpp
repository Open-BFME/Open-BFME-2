// cl: /MD
// ?rva00469C07@Rva00469C07@@QAEXPAURva00469C07Node@@@Z 0x00469C07 45B evidence: child-sibling tree free via rowed free 0x30830 caller 0x46A923 plus self recursion
extern "C" void __cdecl free(void *block);
struct Rva00469C07Node
{
	char m_pad[8];
	Rva00469C07Node *m_next;
	Rva00469C07Node *m_child;
};
class Rva00469C07
{
public:
	void rva00469C07(Rva00469C07Node *head);
};
void Rva00469C07::rva00469C07(Rva00469C07Node *head)
{
	Rva00469C07Node *node = head;
	if (node == 0)
		return;
	do {
		rva00469C07(node->m_child);
		Rva00469C07Node *next = node->m_next;
		free(node);
		node = next;
	} while (node != 0);
}

// ?rva00469C34@Rva00469C34@@QAEXPAURva00469C34Node@@@Z 0x00469C34 45B evidence: same child-sibling shape as 0x469C07 via rowed free 0x30830 caller 0x46A94C plus self recursion
struct Rva00469C34Node
{
	char m_pad[8];
	Rva00469C34Node *m_next;
	Rva00469C34Node *m_child;
};
class Rva00469C34
{
public:
	void rva00469C34(Rva00469C34Node *head);
};
void Rva00469C34::rva00469C34(Rva00469C34Node *head)
{
	Rva00469C34Node *node = head;
	if (node == 0)
		return;
	do {
		rva00469C34(node->m_child);
		Rva00469C34Node *next = node->m_next;
		free(node);
		node = next;
	} while (node != 0);
}
