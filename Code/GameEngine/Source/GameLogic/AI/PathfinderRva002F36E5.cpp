// cl: /O1 /G7 /DNDEBUG /MD
// ?rva002F36E5@Pathfinder@@QAEPAVRva0052DE5B@@XZ @0x002F36E5 40B
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
private:
	char m_pad[0x1D1F0];
	struct Queue
	{
		Rva0052DE5B **m_base;
		Rva0052DE5B **m_end;
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
