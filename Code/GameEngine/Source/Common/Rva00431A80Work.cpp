// cl: /MD
// ?work@Rva00431A80@@QAEXXZ @0x00431A80 54B: guarded factory via pinned guard 0x004318A8 plus rowed operator new 0x0002FDA0 (8B) plus immediate vtable 0x00C3C988 plus rowed setter 0x00575674 on (m_04+8). Evidence: je guard shape plus new-8 plus vtable immediate plus REL32s; sibling 0x00431F0C pattern.
class Object;
#include "../../Include/Common/Rva00575674.h"

// 0x004318A8 is matched as int AreBothButtonsUp(); retail tests only AL.
int __cdecl AreBothButtonsUp();

extern "C" const void *const __identifier("??_7Rva0043190E@@6B@")[];
extern "C" const void *const __identifier("??_7Rva004318FC@@6B@")[];

#include <new>

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
	if (!(char)AreBothButtonsUp())
		return;
	void *mem = operator new(8);
	Rva00431A80Helper *h;
	if (mem != 0) {
		h = (Rva00431A80Helper *)mem;
		h->m_parent = m_04;
		h->m_vptr = (void *)__identifier("??_7Rva0043190E@@6B@");
	} else {
		h = 0;
	}
	Rva00575674 *q = (Rva00575674 *)((char *)m_04 + 8);
	q->rva00575674((Object *)h);
}

// ?work@Rva00431AB6@@QAEXXZ @0x00431AB6 54B: same factory with inverted guard (works when guard is false) and vtable g_00C3C97C.
class Rva00431AB6
{
public:
	void work();
private:
	char m_00[4];
	void *m_04;
};

void Rva00431AB6::work()
{
	if ((char)AreBothButtonsUp())
		return;
	void *mem = operator new(8);
	Rva00431A80Helper *h;
	if (mem != 0) {
		h = (Rva00431A80Helper *)mem;
		h->m_parent = m_04;
		h->m_vptr = (void *)__identifier("??_7Rva004318FC@@6B@");
	} else {
		h = 0;
	}
	Rva00575674 *q = (Rva00575674 *)((char *)m_04 + 8);
	q->rva00575674((Object *)h);
}

// ?work@Rva00431ED6@@QAEXXZ @0x00431ED6 54B: same factory as 0x00431A80 with vtable g_00C3C97C.
class Rva00431ED6
{
public:
	void work();
private:
	char m_00[4];
	void *m_04;
};

void Rva00431ED6::work()
{
	if (!(char)AreBothButtonsUp())
		return;
	void *mem = operator new(8);
	Rva00431A80Helper *h;
	if (mem != 0) {
		h = (Rva00431A80Helper *)mem;
		h->m_parent = m_04;
		h->m_vptr = (void *)__identifier("??_7Rva004318FC@@6B@");
	} else {
		h = 0;
	}
	Rva00575674 *q = (Rva00575674 *)((char *)m_04 + 8);
	q->rva00575674((Object *)h);
}
