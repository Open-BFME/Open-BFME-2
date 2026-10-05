// cl: /O1 /G7 /DNDEBUG /MD
// ?rva002F36E5@Pathfinder@@QAEPAVRva0052DE5B@@XZ @0x002F36E5 40B
// ?rva002F370D@Pathfinder@@QAEHXZ @0x002F370D 43B clears queue at +0x1D1F0 marking each false via 0x0052DAE9 and popping via 0x002F301F returning count.
// Dequeues front Rva0052DE5B pointer from queue at +0x1D1F0: if empty return 0 else mark front false via 0x0052DAE9 then pop via 0x002F301F and return it.
// Evidence: unlock lane; callees rowed 0x0052DAE9 0x002F301F; callers in 7 Pathfinder bodies; neighbours PathfinderCoordLineWalk share flags.
class Rva0052DE5B
{
public:
	void rva0052DAE9(bool flag);
};

class Rva002F301F
{
public:
	void rva002F301F();
};

class Pathfinder
{
public:
	Rva0052DE5B *rva002F36E5();
	int rva002F370D();
private:
	char m_pad[0x1D1F0];
	struct Queue
	{
		bool empty() const { return m_base == m_end; }
		Rva0052DE5B *front() const { return *m_base; }
		Rva0052DE5B ** volatile m_base;
		Rva0052DE5B ** volatile m_end;
	} m_queue;
};

Rva0052DE5B *Pathfinder::rva002F36E5()
{
	Queue *q = &m_queue;
	Rva0052DE5B **base = q->m_base;
	Rva0052DE5B *front = 0;
	if (base != q->m_end)
	{
		front = *base;
		front->rva0052DAE9(false);
		((Rva002F301F *)q)->rva002F301F();
	}
	return front;
}

int Pathfinder::rva002F370D()
{
	int count = 0;
	Queue *q = &m_queue;
	while (!q->empty())
	{
		Rva0052DE5B *front = q->front();
		front->rva0052DAE9(false);
		((Rva002F301F *)q)->rva002F301F();
		++count;
	}
	return count;
}
