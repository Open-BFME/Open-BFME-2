// cl: /O1 /MD /DNDEBUG
//
// Pathfinder::queueForPath (retail 0x002EBD31, 52 bytes, pinned from the
// byte-verified AIUpdateInterface::requestPath). It calls the three members
// of BFME 2's pathfind request ring (PathfindRequestRing_Rva002EABF3.cpp): a 512-entry ObjectID ring at
// Pathfinder +0x1C1E0 with head +0x800 and tail +0x804.
//   0x002EABF3 33B  hasRoom: the slot after the tail is not the head
//   0x002EAC14 45B  push: store at the tail, advance it
//   0x002EAC41 59B  contains: scan head..tail for the ID
// Zero Hour keeps the same queue as m_queuedPathfindRequests with head and
// tail indices inside Pathfinder; BFME 2 factors it into this ring. The
// ring's class and member names are descriptive, not recovered. The ring
// lives in its own unit: retail reloads ecx before each ring call, which a
// caller only does when the callees are compiled elsewhere.

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

class Pathfinder
{
public:
	Bool queueForPath(ObjectID id);
private:
	unsigned char m_pad[0x1C1E0];
	PathfindRequestRing m_requestRing;
};

Bool Pathfinder::queueForPath(ObjectID id)
{
	if (!m_requestRing.contains(id))
	{
		if (!m_requestRing.hasRoom())
			return false;
		m_requestRing.push(id);
	}
	return true;
}

