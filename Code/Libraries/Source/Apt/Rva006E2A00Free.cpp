// cl: /MD
// ?rva006E2A00@Rva006E2A00@@QAEPAV1@H@Z @0x006E2A00 size 101 — pooled clear plus single node free.
// Evidence: calls 0x006F7C10 Clear on this, frees 0x1C data then 0x14 node via
// g_pChainBlockAllocator freeBlock 0x006DB270, flag bit0 frees this size 8, returns this.
// Callers: 0x006E2C10. Prev/next Apt TUs use /O2 /MD.
class Rva006F7C10
{
public:
	void rva006F7C10();
};

class Rva006DB270
{
public:
	void freeBlock(void *block, int blockSize);
};

extern Rva006DB270 *g_pChainBlockAllocator;

struct Rva006E2A00Data
{
	int m00;
	int m04;
	int m08;
	char m_pad0C[0x1C - 0x0C];
};

struct Rva006E2A00Node
{
	int m00;
	Rva006E2A00Data *m04;
	int m08;
	int m0C;
	char m_pad10[0x14 - 0x10];
};

class Rva006E2A00
{
public:
	Rva006E2A00 *rva006E2A00(int flag);

private:
	Rva006E2A00Node *m00;
	int m04;
};

Rva006E2A00 *Rva006E2A00::rva006E2A00(int flag)
{
	((Rva006F7C10 *)this)->rva006F7C10();
	Rva006E2A00Node *node = m00;
	if (node != 0)
	{
		Rva006E2A00Data *data = node->m04;
		node->m00 = 0;
		node->m08 = 0;
		node->m0C = 0;
		if (data != 0)
		{
			data->m00 = 0;
			data->m04 = 0;
			data->m08 = 0;
			g_pChainBlockAllocator->freeBlock(data, 0x1C);
			node->m04 = 0;
		}
		g_pChainBlockAllocator->freeBlock(node, 0x14);
	}
	if (flag & 1)
		g_pChainBlockAllocator->freeBlock(this, 8);
	return this;
}
