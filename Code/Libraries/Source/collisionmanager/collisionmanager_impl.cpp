// cl: /O2 /G6 /DNDEBUG /MD
// collisionmanager_impl.cpp -- CollisionManagerImpl::UpdateSort, retail
// 0x00759600 (1244 bytes). WorldBuilder names the function and its file (WB
// 0x01804B90, collisionmanager_impl.cpp:467..607); BFME 1 has the same body at
// b1 0x009A3AD0 (EA evidence name, chain+direct), whose banked donor draft
// (reference/open-bfme-1 targets/game/reverse/attempts/0x009a3ad0.cpp) this
// starts from. Each dirty data refreshes its coordinates; a moved one leaves
// its three sorted axis lists (two 20-byte end points per axis from +0x24) and
// is re-inserted by value, opening overlap pairs with every data whose
// interval it crosses, or pushed to the list fronts while a rebuild is
// pending. A small total move re-sorts the lists by insertion, adding and
// removing overlap pairs as end points cross; otherwise every pair is dropped
// and the lists are merge-sorted (0x007586F0) and swept again. Layout and
// call targets are retail's (the rowed collision-family views); member names
// are structural.

typedef float Real;

#include "../../Include/Lib/Coord3DCtorView.h"

class Object;

// Structural view of the collision interface. Object's table at VA BFC290
// independently establishes slot 0C as a zero-argument primary-object getter
// (299C78, RET), and slots 20/24 as three-argument callbacks (RET 12).
// The location and normal belong to the OUTER callback, not to the getter.
// Method spellings below describe roles; original interface names are unknown.
struct CollisionContactSource
{
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual Object *primaryObject() const = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual bool test(const Object *, const Coord3D &, const Coord3D &) const = 0;
	virtual void respond(Object *, const Coord3D &, const Coord3D &) = 0;
};

// Keep the reversed normal alive through the complete callback expression.
// Copying before negation reproduces the native member-wise copy and FCHS.
struct CollisionReverseNormal
{
	Coord3D value;
	CollisionReverseNormal(const Coord3D &normal) : value(normal)
	{
		value.x = -value.x;
		value.y = -value.y;
		value.z = -value.z;
	}
	operator const Coord3D &() const { return value; }
};

#include <new>

namespace CollisionManager
{
	class Data
	{
	public:
		int UpdateCoord(bool removeAndReInsert);
	};
}

class Rva009A45A0CollisionData;
class Rva009A36F0Thing;
struct Rva009A3540OpaqueOwner;

struct Rva009A3AD0Endpoint
{
	Rva009A3AD0Endpoint *m_prev;	// +0x00
	Rva009A3AD0Endpoint *m_next;	// +0x04
	Rva009A45A0CollisionData *m_node;	// +0x08
	unsigned int m_isMax : 1;	// +0x0c
	Real m_value;	// +0x10

	bool isMin() const { return !m_isMax; }
};

struct Rva009A3AD0Interval
{
	Rva009A3AD0Endpoint m_min;
	Rva009A3AD0Endpoint m_max;
};

class Rva009A45A0CollisionData
{
public:
	~Rva009A45A0CollisionData();

	void *m_owner;	// +0x00
	CollisionContactSource *m_source;	// +0x04
	void *m_rootPrev;	// +0x08
	Rva009A45A0CollisionData *m_rootNext;	// +0x0c
	void *m_dirtyPrev;	// +0x10
	Rva009A45A0CollisionData *m_dirtyNext;	// +0x14
	Rva009A45A0CollisionData **m_openPrev;	// +0x18
	Rva009A45A0CollisionData *m_openNext;	// +0x1c
	int m_rva009A3AD0_020;	// +0x20
	union
	{
		Rva009A3AD0Endpoint m_endpoints[6];	// +0x24
		Rva009A3AD0Interval m_intervals[3];
	};
};

struct CollisionContactNode
{
	Rva009A45A0CollisionData *first;
	Rva009A45A0CollisionData *second;
	unsigned int key0, key1, state;
	Coord3D point, normal;
	CollisionContactNode **back;
	CollisionContactNode *next;
};

class BfmeLinkXX
{
public:
	void bfmeDropXX();
};

class Rva007589F0
{
public:
	void collectAll();
};

class Rva00758B20
{
public:
	void collectAll();
};

class CollisionManagerImpl
{
public:
	void UpdateSort();
	void rva00759490(Rva009A3540OpaqueOwner *a, Rva009A3540OpaqueOwner *b);	// 0x00759490, WB _AddOverlap
	void unlinkChain(Rva009A36F0Thing *thing);
	void _RemoveOverlap(Rva009A3540OpaqueOwner *a, Rva009A3540OpaqueOwner *b);
	void rva007586F0();
	void bfmeTwoCGD();

	Rva009A45A0CollisionData *m_root;	// +0x00
	unsigned int m_nodeCount;	// +0x04
	Rva009A45A0CollisionData *m_dirty;	// +0x08
	Rva009A3AD0Endpoint *m_axisHeads[3];	// +0x0c
	unsigned char m_table[0xAE10 - 0x18];
	CollisionContactNode *m_contactBuckets[0x493]; // +0xae10
	CollisionContactNode *m_contactActive; // +0xc05c
	int m_contactIndex; // +0xc060
	CollisionContactNode *m_contactCurrent; // +0xc064
	unsigned int m_axisCount;	// +0xc068
	bool m_rebuild;	// +0xc06c

	__forceinline void insertSorted(Rva009A45A0CollisionData *node, Rva009A3AD0Interval *axis, Rva009A3AD0Endpoint **head)
	{
		Rva009A3AD0Endpoint *cur = *head;
		Rva009A3AD0Endpoint *prev = 0;
		Rva009A45A0CollisionData *open = 0;
		Real value = axis->m_max.m_value;
		while (cur != 0 && !(cur->m_value > value))
		{
			if (cur->isMin())
			{
				cur->m_node->m_openPrev = &open;
				cur->m_node->m_openNext = open;
				if (cur->m_node->m_openNext != 0)
					cur->m_node->m_openNext->m_openPrev = &cur->m_node->m_openNext;
				open = cur->m_node;
			}
			else
			{
				if (cur->m_node->m_openNext != 0)
					cur->m_node->m_openNext->m_openPrev = cur->m_node->m_openPrev;
				*cur->m_node->m_openPrev = cur->m_node->m_openNext;
				cur->m_node->m_openPrev = 0;
			}
			prev = cur;
			cur = cur->m_next;
		}

		axis->m_max.m_prev = prev;
		axis->m_max.m_next = cur;
		if (prev != 0)
			prev->m_next = &axis->m_max;
		else
			*head = &axis->m_max;
		if (cur != 0)
			axis->m_max.m_next->m_prev = &axis->m_max;
		prev = &axis->m_max;

		if (cur != 0)
		{
			while (open != 0)
			{
				rva00759490((Rva009A3540OpaqueOwner *)open, (Rva009A3540OpaqueOwner *)node);
				Rva009A45A0CollisionData *closed = open;
				if (closed->m_openNext != 0)
					closed->m_openNext->m_openPrev = closed->m_openPrev;
				*closed->m_openPrev = closed->m_openNext;
				closed->m_openPrev = 0;
			}
			value = axis->m_min.m_value;
			do
			{
				if (!(cur->m_value < value))
					break;
				if (cur->isMin())
					rva00759490((Rva009A3540OpaqueOwner *)cur->m_node, (Rva009A3540OpaqueOwner *)node);
				prev = cur;
				cur = cur->m_next;
			}
			while (cur != 0);
		}

		axis->m_min.m_prev = prev;
		axis->m_min.m_next = cur;
		prev->m_next = &axis->m_min;
		if (cur != 0)
			axis->m_min.m_next->m_prev = &axis->m_min;
	}

	__forceinline void pushFront(Rva009A3AD0Endpoint *endpoint, Rva009A3AD0Endpoint **head)
	{
		endpoint->m_prev = 0;
		endpoint->m_next = *head;
		if (endpoint->m_next != 0)
			endpoint->m_next->m_prev = endpoint;
		*head = endpoint;
	}
};

void CollisionManagerImpl::UpdateSort()
{
	unsigned int totalScore = 0;
	Rva009A45A0CollisionData *node = m_dirty;
	while (node != 0)
	{
		unsigned int score = ((CollisionManager::Data *)node)->UpdateCoord(true);
		if (score == 0)
		{
			node = node->m_dirtyNext;
			continue;
		}
		totalScore += score;
		unlinkChain((Rva009A36F0Thing *)node);
		Rva009A45A0CollisionData *next = node->m_dirtyNext;
		if (node->m_source != 0)
		{
			if (node->m_endpoints[0].m_prev != 0)
			{
				unsigned int index = 0;
				do
				{
					Rva009A3AD0Endpoint *endpoint = &node->m_endpoints[index];
					if (endpoint->m_prev != 0)
						endpoint->m_prev->m_next = endpoint->m_next;
					else
						m_axisHeads[index >> 1] = endpoint->m_next;
					if (endpoint->m_next != 0)
						endpoint->m_next->m_prev = endpoint->m_prev;
					endpoint->m_prev = 0;
					endpoint->m_next = 0;
					++index;
				}
				while (index < 6);
			}

			unsigned int k = 0;
			do
			{
				if (k < m_axisCount && !m_rebuild)
					insertSorted(node, &node->m_intervals[k], &m_axisHeads[k]);
				else
				{
					pushFront(&node->m_intervals[k].m_min, &m_axisHeads[k]);
					pushFront(&node->m_intervals[k].m_max, &m_axisHeads[k]);
				}
				++k;
			}
			while (k < 3);

			((BfmeLinkXX *)node)->bfmeDropXX();
		}
		else
		{
			delete node;
		}
		node = next;
	}

	while (m_dirty != 0)
	{
		totalScore += ((CollisionManager::Data *)m_dirty)->UpdateCoord(false);
		((BfmeLinkXX *)m_dirty)->bfmeDropXX();
	}

	if (m_root == 0)
		return;

	if (totalScore * 100 <= m_nodeCount * 100 && !m_rebuild)
	{
		for (unsigned int k = 0; k < m_axisCount; ++k)
		{
			Rva009A3AD0Endpoint **head = &m_axisHeads[k];
			Rva009A3AD0Endpoint *cur = (*head)->m_next;
			while (cur != 0)
			{
				if (cur->m_prev->m_value <= cur->m_value)
				{
					cur = cur->m_next;
					continue;
				}
				Rva009A3AD0Endpoint *pos = cur;
				while (pos->m_prev != 0 && pos->m_prev->m_value > cur->m_value)
				{
					Rva009A3AD0Endpoint *before = pos->m_prev;
					if (before->m_isMax && cur->isMin())
						rva00759490((Rva009A3540OpaqueOwner *)before->m_node, (Rva009A3540OpaqueOwner *)cur->m_node);
					else if (before->isMin() && cur->m_isMax)
						_RemoveOverlap(
							(Rva009A3540OpaqueOwner *)before->m_node,
							(Rva009A3540OpaqueOwner *)cur->m_node);
					pos = pos->m_prev;
				}

				Rva009A3AD0Endpoint *next = cur->m_next;
				if (cur->m_prev != 0)
					cur->m_prev->m_next = cur->m_next;
				else
					*head = cur->m_next;
				if (cur->m_next != 0)
					cur->m_next->m_prev = cur->m_prev;
				cur->m_prev = 0;
				cur->m_next = 0;

				cur->m_prev = pos->m_prev;
				cur->m_next = pos;
				pos->m_prev = cur;
				if (cur->m_prev != 0)
					cur->m_prev->m_next = cur;
				else
					*head = cur;
				cur = next;
			}
		}
		return;
	}

	m_rebuild = false;
	((Rva007589F0 *)((char *)this + 0x18))->collectAll();
	((Rva00758B20 *)((char *)this + 0xAE10))->collectAll();
	for (Rva009A45A0CollisionData *root = m_root; root != 0; root = root->m_rootNext)
		root->m_rva009A3AD0_020 = 0;
	rva007586F0();

	for (unsigned int k = 0; k < m_axisCount; ++k)
	{
		Rva009A45A0CollisionData *open = 0;
		for (Rva009A3AD0Endpoint *cur = m_axisHeads[k]; cur != 0; cur = cur->m_next)
		{
			if (cur->isMin())
			{
				for (Rva009A45A0CollisionData *other = open; other != 0; other = other->m_openNext)
					rva00759490((Rva009A3540OpaqueOwner *)other, (Rva009A3540OpaqueOwner *)cur->m_node);
				cur->m_node->m_openPrev = &open;
				cur->m_node->m_openNext = open;
				if (cur->m_node->m_openNext != 0)
					cur->m_node->m_openNext->m_openPrev = &cur->m_node->m_openNext;
				open = cur->m_node;
			}
			else
			{
				if (cur->m_node->m_openNext != 0)
					cur->m_node->m_openNext->m_openPrev = cur->m_node->m_openPrev;
				*cur->m_node->m_openPrev = cur->m_node->m_openNext;
				cur->m_node->m_openPrev = 0;
			}
		}
	}
}

// Native 758DE0..758F2D (333 bytes), called by Update at 75A4AB.
// Save the contact before advancing the shared cursor: callbacks can unregister
// an object and alter that cursor or clear either data's source pointer.
// State zero requests a test; state two skips responses. Recheck both sources
// before the reverse response and negate only its normal.
// Evidence: reverse/attempt_support/cgd-abi-758de0-20261023/README.md.
void CollisionManagerImpl::bfmeTwoCGD()
{
	m_contactIndex = 0;
	m_contactCurrent = m_contactBuckets[0];
	for (;;)
	{
		while (m_contactCurrent == 0)
		{
			int i = m_contactIndex + 1;
			if (i == 0x493)
				return;
			m_contactIndex = i;
			m_contactCurrent = m_contactBuckets[i];
		}
		CollisionContactNode *node = m_contactCurrent;
		m_contactCurrent = m_contactCurrent->next;
		if (node == 0)
			return;
		if (node->first->m_source == 0 || node->second->m_source == 0)
			continue;
		if (node->state == 0)
			node->state = node->first->m_source->test(
				node->second->m_source->primaryObject(), node->point, node->normal) ? 1 : 2;
		if (node->state == 2)
			continue;
		node->first->m_source->respond(
			node->second->m_source->primaryObject(), node->point, node->normal);
		if (node->first->m_source == 0 || node->second->m_source == 0)
			continue;
		node->second->m_source->respond(node->first->m_source->primaryObject(),
			node->point, CollisionReverseNormal(node->normal));
	}
}

// Bottom-up axis-list merge sort at 0x007586F0 (460 bytes). The UpdateSort
// caller and identical WorldBuilder body at 0x01802EC0 establish its purpose
// and layout; the original method name is unknown. The two left-run count
// reads use a volatile-qualified accessor to reproduce VC7.1 register costs,
// preserving the same reads and merge operations. This is a codegen choice,
// not evidence that the original field was declared volatile.
struct SortList
{
	Rva009A3AD0Endpoint *head;
	Rva009A3AD0Endpoint *tail;
	unsigned int count;
	unsigned int getCount() const volatile { return count; }
};
typedef Rva009A3AD0Endpoint Endpoint;


void CollisionManagerImpl::rva007586F0()
{
	for (unsigned int k = 0; k < m_axisCount; k++)
	{
		SortList lists[4];
		lists[1].count = 0;
		lists[0].count = 0;
		lists[0].head = 0;
		int i = 0;
		Endpoint *cur = m_axisHeads[k];
		while (cur)
		{
			Endpoint *next = cur->m_next;
			cur->m_next = lists[i].head;
			lists[i].head = cur;
			lists[i].count++;
			i ^= 1;
			cur = next;
		}
		int src = 0;
		unsigned int runLen = 1;
		while (lists[src + 1].count != 0)
		{
			SortList *leftList = &lists[src];
			SortList *rightList = &lists[src + 1];

			int out = src ^ 2;
			lists[out + 1].count = 0;
			lists[out].count = 0;
			while (leftList->getCount() != 0)
			{
				unsigned int rightRemaining = runLen;
				unsigned int leftRemaining = runLen;
				SortList *o = &lists[out];
				for (;;)
				{
					SortList *from;
					if (leftRemaining != 0 && leftList->getCount() != 0)
					{
						if (rightRemaining != 0 && rightList->count != 0 && leftList->head->m_value > rightList->head->m_value)
						{
							from = rightList;
							rightRemaining--;
						}
						else
						{
							from = leftList;
							leftRemaining--;
						}
					}
					else if (rightRemaining != 0 && rightList->count != 0)
					{
						from = rightList;
						rightRemaining--;
					}
					else
						break;
					from->count--;
					Endpoint *e = from->head;
					from->head = e->m_next;
					if (o->count == 0)
					{
						o->head = e;
						o->tail = e;
					}
					else
					{
						o->tail->m_next = e;
						o->tail = e;
					}
					o->count++;
				}
				out ^= 1;
			}
			runLen <<= 1;
			src ^= 2;
		}
		if (lists[src].count > 1)
			lists[src].tail->m_next = 0;
		m_axisHeads[k] = lists[src].head;
		m_axisHeads[k]->m_prev = 0;
		for (Endpoint *currentEndpoint = m_axisHeads[k]; currentEndpoint->m_next != 0; currentEndpoint = currentEndpoint->m_next)
			currentEndpoint->m_next->m_prev = currentEndpoint;
	}
}
