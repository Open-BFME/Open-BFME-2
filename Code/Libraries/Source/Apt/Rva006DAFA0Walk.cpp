// cl: /O2 /MD
// Native [0x6DAFA0,0x6DAFD4),52B, thiscall with no arguments: frees the sized block
// at +0x0C through the .data sized-free pointer, then walks the nodes at +0x04
// freeing each through the .data free pointer. Address-derived names.
extern void (__cdecl *g_Va00E17730)(void *storage, unsigned int size);
// VA 0x00E1772C is Apt.cpp's g_aptFreeCallback (gAptFuncs.pfnMemFree).
extern void (__cdecl *g_aptFreeCallback)(void *node);
struct Rva006DAFA0Node
{
	Rva006DAFA0Node *m_next;
};
class Rva006DAFA0Walk
{
public:
	void rva006DAFA0(void);
	void *m_head;
	Rva006DAFA0Node *m_nodes;
	char pad08[4];
	void *m_sized;
};
void Rva006DAFA0Walk::rva006DAFA0(void)
{
	g_Va00E17730(m_head, (unsigned int)((char *)m_sized + 4));
	Rva006DAFA0Node *node = m_nodes;
	for (;;) {
		Rva006DAFA0Node *next = node->m_next;
		g_aptFreeCallback(node);
		node = next;
		if (next == 0)
			break;
	}
}
