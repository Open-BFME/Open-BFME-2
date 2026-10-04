// cl: /O1 /DNDEBUG /MD
// ?rva00239380@Rva00239380Holder@@QAEXXZ @0x00239380 42B: circular list clear.
// Same shape as ?rva001EB130@Rva001EB130Holder@@QAEXXZ at 0x001EB130 (42B; /O1
// /DNDEBUG /MD): drains nodes from sentinel at this+0 to freelist then
// reinits sentinel next and prev to itself. Freelist here is 0x009BA5E8.
// Callers at 0x002399E0 0x00239AF7 0x0029BDF5 0x002A3916 0x0030F277 plus
// jmp at 0x00239944. No donor; honest address names.
class Rva00239380Holder
{
public:
	void *m_head;
	void rva00239368(void *node, int dummy);
	void rva00239380();
};
extern void *g_freeList00239380;
// g_freeList00239380: VA 0xdba5e8 (retail .data initial value 0).
void * g_freeList00239380;
// ?rva00239AF4@Rva00239AF4@@QAEXXZ @0x00239AF4 29B: dispose of the same
// circular-list holder cleared by 0x00239380 above (calls it on ecx, then
// pushes the head node at this+0 onto freelist 0x009BA5E8 when non-null).
// Callers include 0x0023B22F 0x0026B2E5 0x0026B36A plus 30 more; owner
// class unproven so honest address name.
class Rva00362862Item
{
public:
	void rva00362862(int a, int b);
};

class Rva00239300
{
	char m_pad[0xe8];
	Rva00362862Item **m_begin;
	Rva00362862Item **m_end;

public:
	void rva00239300(int a, int b);
};

void Rva00239300::rva00239300(int a, int b)
{
	for (Rva00362862Item **it = m_begin; it != m_end; ++it) {
		(*it)->rva00362862(a, b);
	}
}

class Rva00239AF4
{
public:
	void *m_head;
	void rva00239AF4();
};
void Rva00239AF4::rva00239AF4()
{
	((Rva00239380Holder *)this)->rva00239380();
	void *head = m_head;
	if (head != 0) {
		void *freeHead = g_freeList00239380;
		((void **)head)[0] = freeHead;
		g_freeList00239380 = head;
	}
}
void Rva00239380Holder::rva00239368(void *node, int dummy)
{
	if (node != 0) {
		void *freeHead = g_freeList00239380;
		((void **)node)[0] = freeHead;
		g_freeList00239380 = node;
	}
}
void Rva00239380Holder::rva00239380()
{
	void *node = ((void **)m_head)[0];
	if (node != m_head) {
		do {
			void *freeHead = g_freeList00239380;
			void *current = node;
			node = ((void **)current)[0];
			((void **)current)[0] = freeHead;
		g_freeList00239380 = current;
		} while (node != m_head);
	}
	((void **)m_head)[0] = m_head;
	((void **)m_head)[1] = m_head;
}
