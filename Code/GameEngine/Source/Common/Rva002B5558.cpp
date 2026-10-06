// cl: /MD
// ?rva002B5558@Rva002B5558@@QAEXXZ @0x002B5558 41B.
// Chain lane; calls rowed 0x002B43BA recursive free; clears sentinel and count.
// Evidence: calls 0x002B43BA which this session landed; callers 0x002B609F 56B and 0x002B62DE 115B pass ecx with no pushes; unblocks 0x002B609F and 0x002B62DE.
// TU-local honest-address class; Node layout from Rva002B43BA.cpp.
extern "C" void __cdecl free(void *block);
struct Node002B43BA
{
	char m_pad[8];
	Node002B43BA *m_next8;
	Node002B43BA *m_childC;
};
class Rva002B43BA
{
public:
	void rva002B43BA(Node002B43BA *head);
};
struct Head002B5558
{
	int m_pad0;
	Node002B43BA *m_node4;
	Head002B5558 *m_next8;
	Head002B5558 *m_prevC;
};
class Rva002B5558
{
	Head002B5558 *m_head0;
	int m_count4;
public:
	void rva002B5558();
};
void Rva002B5558::rva002B5558()
{
	if (m_count4 == 0)
		return;
	((Rva002B43BA *)this)->rva002B43BA(m_head0->m_node4);
	m_head0->m_next8 = m_head0;
	m_head0->m_node4 = 0;
	m_head0->m_prevC = m_head0;
	m_count4 = 0;
}
