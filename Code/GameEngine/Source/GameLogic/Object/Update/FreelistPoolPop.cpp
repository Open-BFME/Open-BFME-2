// cl: /O1 /DNDEBUG /MD

// FreelistPool::pop, retail 0x002393E2, 38 bytes: pop-with-grow-retry
// over the behavior-ctor node pool (see Rva0029FB3BMemberInit.cpp, whose
// init pops through the twin pin at this address). The pool head lives at
// +0x08; an empty head grows the pool through 0x001EAEF9 (pinned grow,
// bool(int,int)) and retries, giving up with NULL when grow fails. The
// retry is goto-spelled: a for(;;) phrasing emits a taken jumper where
// retail falls through into the grow call and loops with the bare jne.

class FreelistPool
{
public:
	void *pop();

private:
	bool grow( int arena, int size );

	int m_00;			// +0x00 default-size count (size = m_00*16+4 when size==0)
	void *m_04;			// +0x04 current block (linked into block header)
	void *m_head;		// +0x08 free-list head
	void *(__cdecl *m_alloc)( int size, int arg ); // +0x0C block allocator
	int m_10;			// +0x10
	int m_14;			// +0x14 allocator argument
};


// ?pop@FreelistPool@@QAEPAXXZ
void *FreelistPool::pop()
{
retry:
	if ( m_head == 0 )
	{
		if ( grow( 0, 0 ) )
			goto retry;
		return 0;
	}
	void *node = m_head;
	m_head = *(void **)node;
	return node;
}

// Retail 0x001EAEF9, 101 bytes: pool grow with retry. While arena==0,
// default the size (m_00*16+4), fail on -1, allocate through m_alloc and
// retry; then carve the block into 0x10-sized nodes aligned to 8, chaining
// them from m_head. /O1 gives and-[mem],0 and pop/pop cleanup.
bool FreelistPool::grow(int arena, int size)
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
	size = m_00 * 16 + 4;
	goto retry;
carve:
	void *old = m_04;
	*(void **)arena = old;
	int aligned = (arena + 15) & ~7;
	void *end = (char *)arena + size - 0x20;
	*(int *)((char *)arena + 4) = size;
	m_04 = (void *)arena;
	m_head = (void *)aligned;
	if ((unsigned int)aligned > (unsigned int)end)
		goto done;
	do {
		int next = aligned + 0x10;
		*(int *)aligned = next;
		aligned = next;
	} while ((unsigned int)aligned <= (unsigned int)end);
done:
	*(int *)aligned = 0;
	return true;
}
