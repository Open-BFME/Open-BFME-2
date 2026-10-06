// cl: /MD
// ?rva002B57AC@Rva002B57AC@@QAEXXZ @0x002B57AC 41B.
// Chain lane; calls rowed 0x002B44DC recursive free; clears sentinel and count.
// Evidence: calls 0x002B44DC which this session landed; caller 0x002B626E 56B passes ecx with no pushes; unblocks 0x002B626E.
// TU-local honest-address class; Node layout from Rva002B44DC.cpp.
extern "C" void __cdecl free(void *block);
struct Node002B44DC
{
	char m_pad[8];
	Node002B44DC *m_next8;
	Node002B44DC *m_childC;
};
class Rva002B44DC
{
public:
	void rva002B44DC(Node002B44DC *head);
};
struct Head002B57AC
{
	int m_pad0;
	Node002B44DC *m_node4;
	Head002B57AC *m_next8;
	Head002B57AC *m_prevC;
};
class Rva002B57AC
{
	Head002B57AC *m_head0;
	int m_count4;
public:
	void rva002B57AC();
};
void Rva002B57AC::rva002B57AC()
{
	if (m_count4 == 0)
		return;
	((Rva002B44DC *)this)->rva002B44DC(m_head0->m_node4);
	m_head0->m_next8 = m_head0;
	m_head0->m_node4 = 0;
	m_head0->m_prevC = m_head0;
	m_count4 = 0;
}
