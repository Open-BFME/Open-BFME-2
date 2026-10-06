// cl: /MD
//
// ?rva006E3BF0@Rva006E3BF0@@QAEXXZ @0x006E3BF0 74B
// Pool teardown: release up to m_count non-null slots in order (early out
// once all are released), then return the backing store to the allocator via
// pinned freeBlock@Rva006DB270 with (array, capacity * 4). Layout: word
// count at +0, word capacity at +2, element array at +4; elements expose
// AddRef/Release like AptCIH (Release at vtable slot 1).
// Evidence: unlock lane; callers in 0x006E6430 plus EH-unwind callers (dtor
// family); callee freeBlock resolved by pin; Apt /O2 /MD sibling TUs.
class Rva006DB270
{
public:
	void freeBlock(void *p, int bytes);
};
extern Rva006DB270 *g_pChainBlockAllocator;

class Rva006E3BF0Elem
{
public:
	virtual void AddRef();
	virtual void Release();
};

class Rva006E3BF0
{
public:
	void rva006E3BF0();
private:
	unsigned short m_count;
	unsigned short m_capacity;
	Rva006E3BF0Elem **m_arr;
};

void Rva006E3BF0::rva006E3BF0()
{
	int left = m_count;
	int i = 0;
	if (i < m_capacity) {
		do {
			if (m_arr[i] != 0) {
				m_arr[i]->Release();
				if (--left == 0)
					break;
			}
			++i;
		} while (i < m_capacity);
	}
	g_pChainBlockAllocator->freeBlock(m_arr, m_capacity * 4);
}
