// cl: /DNDEBUG /MD
// ?rva002F36E5@Pathfinder@@QAEPAVPathfindCell@@XZ @0x002F36E5 40B
// ?rva002F370D@Pathfinder@@QAEHXZ @0x002F370D 43B clears queue at +0x1D1F0 marking each false via 0x0052DAE9 and popping via 0x002F301F returning count.
// ?rva002F40E7@Pathfinder@@QAEHXZ @0x002F40E7 46B chain from 0x002F370D plus release 0x0052DE9B and stat adds at +0x34 +0x3C +0x40 +0x44 returning release result.
// Dequeues front PathfindCell pointer from queue at +0x1D1F0: if empty return 0 else mark front false via 0x0052DAE9 then pop via 0x002F301F and return it.
// Evidence: unlock lane; callees rowed 0x0052DAE9 0x002F301F; callers in 7 Pathfinder bodies; neighbours PathfinderCoordLineWalk share flags.
#include "../../../Include/GameLogic/PathfindCell.h"

// The queue at +0x1D1F0 is an STLport priority_queue; 0x002F301F is its
// out-of-line pop (Rva002F301FRva002F301F.cpp). Its element and comparator
// keep that unit's address-derived names.
struct _Rva002EBB53Wrap;
struct Rva002EBB53Compare;
namespace _STL {
template <class T> class allocator;
template <class T, class A> class vector;
template <class T, class S, class C> class priority_queue
{
public:
	void pop();
};
}
typedef _STL::priority_queue<_Rva002EBB53Wrap *,
	_STL::vector<_Rva002EBB53Wrap *, _STL::allocator<_Rva002EBB53Wrap *> >,
	Rva002EBB53Compare> Rva002EBB53Queue;

class MixFileInfoBuffer;


class Pathfinder
{
public:
	PathfindCell *rva002F36E5();
	int rva002F370D();
	int rva002F40E7();
private:
	char m_pad00[0x34];
	MixFileInfoBuffer *m_34;
	char m_pad38[4];
	int m_3C;
	int m_40;
	int m_44;
	char m_pad48[0x1D1F0 - 0x48];
	struct Queue
	{
		bool empty() const { return m_base == m_end; }
		PathfindCell *front() const { return *m_base; }
		PathfindCell ** volatile m_base;
		PathfindCell ** volatile m_end;
	} m_queue;
};

PathfindCell *Pathfinder::rva002F36E5()
{
	Queue *queue = &m_queue;
	PathfindCell **base = queue->m_base;
	PathfindCell *front = 0;
	if (base != queue->m_end)
	{
		front = *base;
		front->SetOpen(false);
		((Rva002EBB53Queue *)queue)->pop();
	}
	return front;
}

int Pathfinder::rva002F370D()
{
	int count = 0;
	Queue *queue = &m_queue;
	while (!queue->empty())
	{
		PathfindCell *front = queue->front();
		front->SetOpen(false);
		((Rva002EBB53Queue *)queue)->pop();
		++count;
	}
	return count;
}

int Pathfinder::rva002F40E7()
{
	int n = rva002F370D();
	MixFileInfoBuffer *mixFileInfoBuffer = m_34;
	int r = 0;
	if (mixFileInfoBuffer != 0)
	{
		r = PathfindCell::ReleaseClosedList(mixFileInfoBuffer);
		m_34 = 0;
	}
	m_40 += n;
	m_44 += r;
	m_3C += r + n;
	return r;
}
