// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva0046A93E@Rva0046A93E@@QAEXXZ 0x0046A93E 41B evidence: unlock caller 0x46AB1B frees header after clear plus rowed tree-free 0x469C34 at call 0x46A94C
struct Rva00469C34Node;
class Rva00469C34
{
public:
	void rva00469C34(Rva00469C34Node *head);
};
struct Rva0046A93EHeader
{
	int m_unk0;
	Rva00469C34Node *m_head;
	Rva0046A93EHeader *m_next;
	Rva0046A93EHeader *m_prev;
};
class Rva0046A93E
{
public:
	Rva0046A93EHeader *m_header;
	int m_flag;
	void rva0046A93E();
};
void Rva0046A93E::rva0046A93E()
{
	if (m_flag == 0)
		return;
	reinterpret_cast<Rva00469C34 *>(this)->rva00469C34(m_header->m_head);
	m_header->m_next = m_header;
	m_header->m_head = 0;
	m_header->m_prev = m_header;
	m_flag = 0;
}
