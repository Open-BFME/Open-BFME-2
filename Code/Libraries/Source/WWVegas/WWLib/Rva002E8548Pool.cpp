// cl: /O1 /G7 /DNDEBUG /MD
// Retail 24-byte-node pool; original template and application owner unknown.
// Reference algorithm: matched 16-byte sibling FreelistPoolPop.cpp at
// 1EAEF9. Target [2E8548,2E85AD) independently establishes stride24,
// six-word pool storage and the allocator callback ABI. /G7 preserves IMUL.
// Field names describe their observed use rather than original identities.
class Rva002E8548
{
public:
    void *rva002EB448();
private:
    bool rva002E8548(int arena, int size);
    int m_00; // default node count
    void *m_04; // allocated-block list
    void *m_head; // free-node list
    void *(__cdecl *m_alloc)(int size, int context);
    void (__cdecl *m_free)(void *block, int context);
    int m_14; // callback context
};

bool Rva002E8548::rva002E8548(int arena, int size)
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
	size = m_00 * 24 + 4;
	goto retry;
carve:
	void *old = m_04;
	*(void **)arena = old;
	int aligned = (arena + 15) & ~7;
	void *end = (char *)arena + size - 0x30;
	*(int *)((char *)arena + 4) = size;
	m_04 = (void *)arena;
	m_head = (void *)aligned;
	if ((unsigned int)aligned > (unsigned int)end)
		goto done;
	do {
		int next = aligned + 0x18;
		*(int *)aligned = next;
		aligned = next;
	} while ((unsigned int)aligned <= (unsigned int)end);
done:
	*(int *)aligned = 0;
	return true;
}
