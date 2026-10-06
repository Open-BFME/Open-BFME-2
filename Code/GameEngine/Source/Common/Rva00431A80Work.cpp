// cl: /O1 /MD
// ?work@Rva00431A80@@QAEXXZ @0x00431A80 54B: guarded factory via pinned guard 0x004318A8 plus rowed operator new 0x0002FDA0 (8B) plus immediate vtable 0x00C3C988 plus rowed setter 0x00575674 on (m_04+8). Evidence: je guard shape plus new-8 plus vtable immediate plus REL32s; sibling 0x00431F0C pattern.
class Object;
class Rva00575674
{
public:
	void rva00575674(Object *o);
};

bool __cdecl Rva004318A8Guard();

extern const void *const g_00C3C988[];

void *__cdecl operator new(unsigned int size);

struct Rva00431A80Helper
{
	void *m_vptr;
	void *m_parent;
};

class Rva00431A80
{
public:
	void work();
private:
	char m_00[4];
	void *m_04;
};

void Rva00431A80::work()
{
	if (!Rva004318A8Guard())
		return;
	void *mem = operator new(8);
	Rva00431A80Helper *h;
	if (mem != 0) {
		h = (Rva00431A80Helper *)mem;
		h->m_parent = m_04;
		h->m_vptr = (void *)g_00C3C988;
	} else {
		h = 0;
	}
	Rva00575674 *q = (Rva00575674 *)((char *)m_04 + 8);
	q->rva00575674((Object *)h);
}
