// cl: /MD /DNDEBUG
//
// The three members of BFME 2's pathfind request ring that
// Pathfinder::queueForPath (0x002EBD31, PathfinderQueueForPath.cpp) calls: a 512-entry ObjectID ring at
// Pathfinder +0x1C1E0 with head +0x800 and tail +0x804.
//   0x002EABF3 33B  hasRoom: the slot after the tail is not the head
//   0x002EAC14 45B  push: store at the tail, advance it
//   0x002EAC41 59B  contains: scan head..tail for the ID
// Zero Hour keeps the same queue as m_queuedPathfindRequests with head and
// tail indices inside Pathfinder; BFME 2 factors it into this ring. The
// ring's class and member names are descriptive, not recovered.

typedef bool Bool;
typedef int Int;

enum ObjectID
{
	INVALID_ID = 0
};

class PathfindRequestRing
{
public:
	enum { RING_SIZE = 512 };

	Bool hasRoom() const;
	void push(const ObjectID &id);
	Bool contains(const ObjectID &id) const;

private:
	static Int next(Int slot) { return slot != RING_SIZE - 1 ? slot + 1 : 0; }

	ObjectID m_requests[RING_SIZE];
	Int m_head;
	Int m_tail;
};

Bool PathfindRequestRing::hasRoom() const
{
	return next(m_tail) != m_head;
}

void PathfindRequestRing::push(const ObjectID &id)
{
	m_requests[m_tail] = id;
	m_tail = next(m_tail);
}

Bool PathfindRequestRing::contains(const ObjectID &id) const
{
	for (Int slot = m_head; slot != m_tail; slot = next(slot))
	{
		if (m_requests[slot] == id)
			return true;
	}
	return false;
}
