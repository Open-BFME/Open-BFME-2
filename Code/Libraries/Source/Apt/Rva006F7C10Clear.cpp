// cl: /MD
//
// ?rva006F7C10@Rva006F7C10@@QAEXXZ retail 0x006F7C10 83B.
// Pooled list clear: walks Holder+8 list freeing each node's 0x1C data block
// then the 0x14 node via g_pChainBlockAllocator. Evidence: caller 0x006E2A05
// deleting-dtor shape with flag test plus free-this size 8; pin-only
// freeBlock 0x006DB270; pool g_pChainBlockAllocator 0x00A176E8; sizes 0x1C
// then 0x14; next Rva006F8460Dtor gives flags and pool idiom.

class Rva006DB270
{
public:
	void freeBlock(void *block, int blockSize);
};

extern Rva006DB270 *g_pChainBlockAllocator;
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct Rva006F7C10Data
{
	int m00;
	int m04;
	int m08;
	char m_pad0C[0x1C - 0x0C];
};

struct Rva006F7C10Node
{
	int m00;
	Rva006F7C10Data *m04;
	Rva006F7C10Node *m08;
	int m0C;
	char m_pad10[0x14 - 0x10];
};

struct Rva006F7C10Holder
{
	char m_pad00[8];
	Rva006F7C10Node *m08;
};

class Rva006F7C10
{
public:
	void rva006F7C10();

private:
	Rva006F7C10Holder *m00;
};

void Rva006F7C10::rva006F7C10()
{
	Rva006F7C10Node *node = m00->m08;
	if (node == 0)
		return;
	do
	{
		Rva006F7C10Node *next = node->m08;
		Rva006F7C10Data *data = node->m04;
		_ReadWriteBarrier();
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
		node = next;
	} while (node != 0);
}
