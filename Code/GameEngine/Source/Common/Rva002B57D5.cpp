// cl: /MD
// ?rva002B57D5@Rva002B57D5@@QAEXXZ @0x002B57D5 41B.
// Chain lane; calls rowed 0x002B4509 recursive free; clears sentinel and count.
// Evidence: calls 0x002B4509 which this session landed; caller 0x002B62A6 56B passes ecx with no pushes; unblocks 0x002B62A6.
// TU-local honest-address class; Node layout from Rva002B4509.cpp.
extern "C" void __cdecl free(void *block);
struct Node002B4509
{
	char m_pad[8];
	Node002B4509 *m_next8;
	Node002B4509 *m_childC;
};
class Rva002B4509
{
public:
	void rva002B4509(Node002B4509 *head);
};
struct Head002B57D5
{
	int m_pad0;
	Node002B4509 *m_node4;
	Head002B57D5 *m_next8;
	Head002B57D5 *m_prevC;
};
class Rva002B57D5
{
	Head002B57D5 *m_head0;
	int m_count4;
public:
	void rva002B57D5();
};
void Rva002B57D5::rva002B57D5()
{
	if (m_count4 == 0)
		return;
	((Rva002B4509 *)this)->rva002B4509(m_head0->m_node4);
	m_head0->m_next8 = m_head0;
	m_head0->m_node4 = 0;
	m_head0->m_prevC = m_head0;
	m_count4 = 0;
}
