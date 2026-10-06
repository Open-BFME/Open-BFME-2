// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva0046AB7D@Rva0046AB7D@@QAEXXZ 0x0046AB7D 41B evidence: chain from rowed free 0x46A9D2 plus caller 0x46E2E8 plus same shape as rowed clear 0x46A93E
struct Rva0046A9D2Node;
class Rva0046A9D2
{
public:
	void rva0046A9D2(Rva0046A9D2Node *head);
};
struct Rva0046AB7DHeader
{
	int m_unk0;
	Rva0046A9D2Node *m_head;
	Rva0046AB7DHeader *m_next;
	Rva0046AB7DHeader *m_prev;
};
class Rva0046AB7D
{
public:
	Rva0046AB7DHeader *m_header;
	int m_flag;
	void rva0046AB7D();
};
void Rva0046AB7D::rva0046AB7D()
{
	if (m_flag == 0)
		return;
	reinterpret_cast<Rva0046A9D2 *>(this)->rva0046A9D2(m_header->m_head);
	m_header->m_next = m_header;
	m_header->m_head = 0;
	m_header->m_prev = m_header;
	m_flag = 0;
}
