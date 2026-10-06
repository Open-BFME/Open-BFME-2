// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva0046A915@Rva0046A915@@QAEXXZ 0x0046A915 41B evidence: ready leaf same shape as rowed clears 0x46A93E 0x46AB7D via rowed free 0x469C07
struct Rva00469C07Node;
class Rva00469C07
{
public:
	void rva00469C07(Rva00469C07Node *head);
};
struct Rva0046A915Header
{
	int m_unk0;
	Rva00469C07Node *m_head;
	Rva0046A915Header *m_next;
	Rva0046A915Header *m_prev;
};
class Rva0046A915
{
public:
	Rva0046A915Header *m_header;
	int m_flag;
	void rva0046A915();
};
void Rva0046A915::rva0046A915()
{
	if (m_flag == 0)
		return;
	reinterpret_cast<Rva00469C07 *>(this)->rva00469C07(m_header->m_head);
	m_header->m_next = m_header;
	m_header->m_head = 0;
	m_header->m_prev = m_header;
	m_flag = 0;
}
