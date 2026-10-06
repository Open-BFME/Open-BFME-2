// flags: region default (reverse/retail_inventory/flag_regions.csv)
// Doubly-linked list remove with prev at +0x328 and next at +0x32C.
// ?Rva0028A704@Rva28A6E7Node@@QAEXPAPAV1@@Z 0x0028A704 75B: caller 0x0028A796; siblings 0x0028A6C7 0x0028A6E7 share 0x328/0x32C
class Rva28A6E7Node
{
public:
	void Rva0028A704(Rva28A6E7Node **head);
	char m_pad[0x328];
	Rva28A6E7Node *m_prev;
	Rva28A6E7Node *m_next;
};

void Rva28A6E7Node::Rva0028A704(Rva28A6E7Node **head)
{
	if (m_next != 0)
		m_next->m_prev = m_prev;
	Rva28A6E7Node **prevPtr = &m_prev;
	if (*prevPtr != 0)
		(*prevPtr)->m_next = m_next;
	else
		*head = m_next;
	m_prev = 0;
	m_next = 0;
}
