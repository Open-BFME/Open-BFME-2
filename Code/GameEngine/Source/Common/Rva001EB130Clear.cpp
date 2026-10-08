// cl: /DNDEBUG /MD
// ?rva001EB130@Rva001EB130Holder@@QAEXXZ @0x001EB130 42B: circular list clear.
// Same shape as ?reset@Rva0029FB3BMember@@QAEXXZ at 0x0026549E (42B; /O1
// /DNDEBUG /MD): drains nodes from sentinel at this+0 to freelist then
// reinits sentinel next and prev to itself. Freelist here is 0x009B8FF4
// versus 0x009A60F0 there. Callers at 0x001EB76C 0x00241520 0x0029D7B3
// 0x00423A7F 0x00452959. No donor; honest address names.
class Rva001EB130Holder
{
public:
	void *m_head;
	void rva001EB130();
};
extern void *g_freeList001EB130;
// g_freeList001EB130: VA 0xdb8ff4 (retail .data initial value 0).
void * g_freeList001EB130;
// ?rva001EB769@Rva001EB769@@QAEXXZ @0x001EB769 29B: dispose of the same
// circular-list holder cleared by 0x001EB130 above (calls it on ecx, then
// pushes the head node at this+0 onto freelist 0x009B8FF4 when non-null).
// Callers at 0x001EC845 0x00243DCC 0x002A57A1 0x00372811 etc. are all
// unclaimed so the owner class is unproven; honest address names.
class Rva001EB769
{
public:
	void *m_head;
	void rva001EB769();
};
void Rva001EB769::rva001EB769()
{
	((Rva001EB130Holder *)this)->rva001EB130();
	void *head = m_head;
	if (head != 0) {
		void *freeHead = g_freeList001EB130;
		((void **)head)[0] = freeHead;
		g_freeList001EB130 = head;
	}
}
void Rva001EB130Holder::rva001EB130()
{
	void *node = ((void **)m_head)[0];
	if (node != m_head) {
		do {
			void *freeHead = g_freeList001EB130;
			void *current = node;
			node = ((void **)current)[0];
			((void **)current)[0] = freeHead;
			g_freeList001EB130 = current;
		} while (node != m_head);
	}
	((void **)m_head)[0] = m_head;
	((void **)m_head)[1] = m_head;
}

// ??1Rva001EB940@@QAE@XZ @0x001EB940 5B: out-of-line destructor of an object
// whose only member work is the circular-list holder at +0 -- a tail jmp to
// its disposal 0x001EB769 above, `this` unchanged. Called by the deleting dtor
// 0x0046ACDA and the destroy-aux family.
class Rva001EB940
{
public:
	~Rva001EB940();
};

Rva001EB940::~Rva001EB940()
{
	reinterpret_cast<Rva001EB769 *>(this)->rva001EB769();
}
