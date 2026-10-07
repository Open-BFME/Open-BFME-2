// cl: /O1 /DNDEBUG /MD
// ?rva000E57FF@Rva000E57FF@@QAEXPAVRva000E488F@@@Z @0x000E57FF 63B.
// Copies byte +0x21 onto +0x22, then walks the sentinel list at +0x18.
// A node whose object accepts the arg and whose dword +0x98 is set
// stores 1 at +0x22. Direct call to the rowed 0x000E48BC.

class Rva000E488F;

class Rva000E48BC
{
public:
	bool rva000E48BC(Rva000E488F *container);
	char m_pad[0x98];
	int m_98;
};

struct Rva000E57FFNode
{
	Rva000E57FFNode *next;
	Rva000E57FFNode *prev;
	Rva000E48BC *obj;
};

class Rva000E57FF
{
public:
	void rva000E57FF(Rva000E488F *arg);

	char m_pad[0x18];
	Rva000E57FFNode *m_list;
	char m_pad1C[0x21 - 0x1C];
	unsigned char m_21;
	unsigned char m_22;
};

void Rva000E57FF::rva000E57FF(Rva000E488F *arg)
{
	m_22 = m_21;
	Rva000E57FFNode *head = m_list;
	Rva000E57FFNode *node = head->next;
	if (node == head)
		return;
	do
	{
		if (node->obj->rva000E48BC(arg) && node->obj->m_98 != 0)
			m_22 = 1;
		node = node->next;
	} while (node != *(Rva000E57FFNode *volatile *)&m_list);
}
