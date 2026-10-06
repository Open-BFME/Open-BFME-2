// cl: /DNDEBUG /MD /EHsc
//
// ?Rva0052DE9BRelease (retail 0x0052DE9B, 56 bytes): walks a MixFileInfoBuffer
// list via +0x34, unlinks each node, clears 0x10 at +0x2c and calls
// PathfindCell::ReleaseInfo on the state at +0x30 when present, returning the
// node count. Callees are declared-only so the gate resolves them; the
// do-while with next prefetch reproduces retail's edi/esi allocation. Evidence:
// sole caller at 0x002F40FC pushes [esi+0x34] and accumulates eax into
// [esi+0x44]; callee ?bfmeUnlink@MixFileInfoBuffer@@AAEXXZ proves the walked
// type is MixFileInfoBuffer, and ?ReleaseInfo@PathfindCell@@QAEXXZ is rowed.

struct WalkNode;

class PathfindCell
{
public:
	void ReleaseInfo();
};

class MixFileInfoBuffer
{
private:
	void bfmeUnlink();
public:
	void releaseInto(void *pool);
	friend int Rva0052DE9BRelease(MixFileInfoBuffer *head);
	char m_head[0x34];
	MixFileInfoBuffer *m_next;
	MixFileInfoBuffer **m_prevNext;
};

struct WalkNode
{
	unsigned char m_pad[0x2c];
	unsigned int m_flags2c;
	PathfindCell *m_state;
	WalkNode *m_next;
	WalkNode **m_prevNext;
};

int Rva0052DE9BRelease(MixFileInfoBuffer *head)
{
	if (head == 0)
		return 0;
	int count = 0;
	WalkNode *next = (WalkNode *)head;
	do
	{
		WalkNode *cur = next;
		next = next->m_next;
		++count;
		((MixFileInfoBuffer *)cur)->bfmeUnlink();
		PathfindCell *state = cur->m_state;
		cur->m_flags2c &= ~0x10u;
		if (state != 0)
			state->ReleaseInfo();
	} while (next != 0);
	return count;
}
