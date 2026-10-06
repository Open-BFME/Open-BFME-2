// cl: /MD
// ?rva002B54F9@Rva002B54F9@@QAEXXZ @0x002B54F9 41B.
// Chain lane; calls rowed 0x002B4360 recursive free; clears sentinel and count.
// Evidence: calls 0x002B4360 which this session landed; callers 0x002B5FF1 56B 0x002B5F8A 98B 0x002B6900 63B pass ecx with no pushes.
// TU-local honest-address class; Node layout from Rva002B4360.cpp.
extern "C" void __cdecl free(void *block);
struct Node002B4360
{
	char m_pad[8];
	Node002B4360 *m_next8;
	Node002B4360 *m_childC;
};
class Rva002B4360
{
public:
	void rva002B4360(Node002B4360 *head);
};
struct Head002B54F9
{
	int m_pad0;
	Node002B4360 *m_node4;
	Head002B54F9 *m_next8;
	Head002B54F9 *m_prevC;
};
class Rva002B54F9
{
	Head002B54F9 *m_head0;
	int m_count4;
public:
	void rva002B54F9();
};
void Rva002B54F9::rva002B54F9()
{
	if (m_count4 == 0)
		return;
	((Rva002B4360 *)this)->rva002B4360(m_head0->m_node4);
	m_head0->m_next8 = m_head0;
	m_head0->m_node4 = 0;
	m_head0->m_prevC = m_head0;
	m_count4 = 0;
}
