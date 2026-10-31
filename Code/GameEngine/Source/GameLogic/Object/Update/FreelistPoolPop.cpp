// cl: /DNDEBUG /MD

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
