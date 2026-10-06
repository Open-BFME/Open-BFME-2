// cl: /DNDEBUG /MD

// ?rva0006EFC8@Rva0006EFC8@@QAE_NHH@Z, retail 0x0006EFC8, 102 bytes.
// Pool grow with retry, 8-byte node stride (cf FreelistPool::grow 0x001EAEF9
// which uses 0x10 stride and m_00*16+4). Layout matches FreelistPool:
// +0x00 default-size count (size = m_00*8+4 when size==0), +0x04 current
// block, +0x08 free-list head, +0x0C block allocator, +0x10, +0x14 allocator
// argument. Evidence: callers 0x0006F373 (pool init, calls with arena/size
// when +0x04==0), 0x00141800 (pool pop with grow retry on +0x08==0),
// globals 0x009B424C/0x009B4254 used as pool/free head by 0x00142170 and
// 0x00141EF0; carve shapes (aligned=(arena+15)&~7, end=arena+size-0x10,
// 8-byte chaining) read directly off retail bytes.

class Rva0006EFC8
{
public:
	bool rva0006EFC8(int arena, int size);
	void *rva00141800();

	int m_00;		// +0x00 default-size count (size = m_00*8+4 when size==0)
	void *m_04;		// +0x04 current block (linked into block header)
	void *m_head;	// +0x08 free-list head
	void *(__cdecl *m_alloc)(int size, int arg); // +0x0C block allocator
	int m_10;		// +0x10
	int m_14;		// +0x14 allocator argument
};


bool Rva0006EFC8::rva0006EFC8(int arena, int size)
{
retry:
	if (arena != 0)
		goto carve;
	if (size != 0) {
		if (size == -1)
			return false;
		arena = (int)m_alloc(size, m_14);
		if (arena == 0)
			return false;
		goto retry;
	}
	size = m_00 * 8 + 4;
	goto retry;
carve:
	void *old = m_04;
	*(void **)arena = old;
	int aligned = (arena + 15) & ~7;
	void *end = (char *)arena + size - 0x10;
	*(int *)((char *)arena + 4) = size;
	m_04 = (void *)arena;
	m_head = (void *)aligned;
	if ((unsigned int)aligned > (unsigned int)end)
		goto done;
	do {
		int next = aligned + 8;
		*(int *)aligned = next;
		aligned = next;
	} while ((unsigned int)aligned <= (unsigned int)end);
done:
	*(int *)aligned = 0;
	return true;
}

void *Rva0006EFC8::rva00141800()
{
retry:
	if (m_head == 0) {
		if (rva0006EFC8(0, m_00 * 8 + 4))
			goto retry;
		return 0;
	}
	void *node = m_head;
	m_head = *(void **)node;
	return node;
}
