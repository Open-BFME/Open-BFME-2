// ??1Rva006CD6C0SizedDeleting@@UAE@XZ
// partial score=0.5 date=2026-10-06
// cl: /O1 /MD /DNDEBUG
//
// ??1Rva006DAFA0Walk@@UAE@XZ, retail 0x006DAFA0, 52 bytes
// (Ghidra boundary 0x006DAFA0..0x006DAFD3, int3 padding after).
// The complete destructor behind the sibling TU's jump stub: frees the
// sized allocation at this+0x0C through the .data deallocator pointer at
// 0x00E17730, then walks the linked nodes at this+0x04 freeing each through
// the .data deallocator pointer at 0x00E1772C.
//
// IDENTITY IS NOT RECOVERED. The name is derived from the address: the
// class layout and member meanings are unknown, only the access pattern
// (this+0x0C sized-free, this+0x04 node walk) is established from retail.

extern void (__cdecl *g_Va00E17730)(void *storage, unsigned int size);
extern void (__cdecl *g_Va00E1772C)(void *node);

struct Rva006DAFA0Node
{
	Rva006DAFA0Node *m_next;
};

class Rva006DAFA0Walk
{
public:
	virtual ~Rva006DAFA0Walk();

	void *m_head;
	Rva006DAFA0Node *m_nodes;
	void *m_sized;
};

Rva006DAFA0Walk::~Rva006DAFA0Walk()
{
	void *sized = m_sized;
	void *head = *(void **)this;
	g_Va00E17730((char *)sized + 4, (unsigned int)head);
	Rva006DAFA0Node *node = m_nodes;
	for (;;) {
		Rva006DAFA0Node *next = node->m_next;
		g_Va00E1772C(node);
		node = next;
		if (next == 0)
			break;
	}
}
