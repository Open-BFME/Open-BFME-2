// cl: /O1 /MD
//
// ??1Rva002859EADtor@@QAE@XZ retail 0x002859EA, 32 B.
// Target evidence: frees the singly linked block list at +0x04 one block at
// a time through the CRT free (0x00030830), storing each block's first dword
// (the next block) back into +0x04 until it is null. Five unwind funclets
// (0x007B6B73, 0x007B781A, 0x007B7824, 0x007B7CD7, 0x007B92A2) jump here.
// The shape is WWLib's ObjectPoolClass destructor (mempool.h: walk
// BlockListHead, delete each block); an earlier attempt compiled the
// CameraShakeSystemClass instantiation and lost only on the delete binding.
// Retail frees straight through free, so the owner stays address-named.
extern "C" void __cdecl free(void *p);

struct Rva002859EABlock
{
	Rva002859EABlock *m_next;
};

class Rva002859EADtor
{
public:
	~Rva002859EADtor();

private:
	void *m_00;
	Rva002859EABlock *m_blocks;	// +0x04
};

Rva002859EADtor::~Rva002859EADtor()
{
	while (m_blocks)
	{
		Rva002859EABlock *next = m_blocks->m_next;
		free(m_blocks);
		m_blocks = next;
	}
}
