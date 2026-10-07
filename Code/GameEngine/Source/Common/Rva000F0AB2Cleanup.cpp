// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// ?rva000F0AB2@Rva000F0AB2@@QAEXXZ RVA 0x000F0AB2 size 37 evidence caller 0x0009A314, virtual call slot0 with 0 plus operator delete 0x0002FD60, next-pointer at +0x68
void __cdecl operator delete(void *p);

struct Rva000F0AB2Node
{
	virtual void *rva000F0AB2virt(int arg);
	char m_pad04[0x68 - 4];
	Rva000F0AB2Node *m_next68;
};

class Rva000F0AB2
{
public:
	void rva000F0AB2();
private:
	Rva000F0AB2Node *m_head;
};

void Rva000F0AB2::rva000F0AB2()
{
	Rva000F0AB2Node *head = m_head;
	m_head = 0;
	Rva000F0AB2Node *node = head;
	while (head)
	{
		Rva000F0AB2Node **slot = &node->m_next68;
		head = *slot;
		*slot = 0;
		void *p = node->rva000F0AB2virt(0);
		operator delete(p);
		node = head;
	}
}
