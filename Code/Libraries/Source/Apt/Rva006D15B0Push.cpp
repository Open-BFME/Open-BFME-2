// cl: /O2 /DNDEBUG /MD /EHsc
// ?rva006D15B0@Rva006D15B0Stack@@QAEXPAPAH@Z @0x006D15B0 (65B).
// Pushes a reference-counted handle onto a singly linked stack: allocates an
// 8-byte node from the Apt pool (0x00E176E8, 0x006DB160 allocBlock), copies
// the handle (first dword is the shared count, bumped when the handle is
// non-null), links the node in front of the head at this+0 and makes it the
// new head. Retail does not test the allocation (its null path stores
// through 0). Evidence: allocBlock size 8, inc of the shared dword, thiscall
// ret 4; the owner and node identities are unproven, so both are
// address-named.

class Rva006DB160
{
public:
	void *allocBlock(int blockSize);
};

extern Rva006DB160 *g_aptPoolAllocator;

struct Rva006D15B0Node
{
	Rva006D15B0Node(int *const *handle)
	{
		m_count = *handle;
		if (m_count != 0)
			++*m_count;
		m_next = 0;
	}
	static void *operator new(unsigned int size)
	{
		return g_aptPoolAllocator->allocBlock((int)size);
	}
	static void operator delete(void *, unsigned int) {}

	int *m_count;
	Rva006D15B0Node *m_next;
};

class Rva006D15B0Stack
{
public:
	void rva006D15B0(int *const *handle);

private:
	Rva006D15B0Node *m_head;
};

void Rva006D15B0Stack::rva006D15B0(int *const *handle)
{
	Rva006D15B0Node *node = new Rva006D15B0Node(handle);
	node->m_next = m_head;
	m_head = node;
}
