// cl: /MD
// ?rva002B5522@Rva002B5522@@QAEXXZ @0x002B5522 41B.
// Chain lane; calls rowed 0x002B438D recursive free; clears sentinel and count.
// Evidence: calls 0x002B438D which this session landed; callers 0x002B602E 56B 0x002B964F 606B 0x002B5FF1 56B pass ecx with no pushes.
// TU-local honest-address class; Node layout from Rva002B438D.cpp.
extern "C" void __cdecl free(void *block);
struct Node002B438D
{
	char m_pad[8];
	Node002B438D *m_next8;
	Node002B438D *m_childC;
};
class Rva002B438D
{
public:
	void rva002B438D(Node002B438D *head);
};
struct Head002B5522
{
	int m_pad0;
	Node002B438D *m_node4;
	Head002B5522 *m_next8;
	Head002B5522 *m_prevC;
};
class Rva002B5522
{
	Head002B5522 *m_head0;
	int m_count4;
public:
	void rva002B5522();
};
void Rva002B5522::rva002B5522()
{
	if (m_count4 == 0)
		return;
	((Rva002B438D *)this)->rva002B438D(m_head0->m_node4);
	m_head0->m_next8 = m_head0;
	m_head0->m_node4 = 0;
	m_head0->m_prevC = m_head0;
	m_count4 = 0;
}
