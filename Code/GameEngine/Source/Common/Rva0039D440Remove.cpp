// flags: region default (reverse/retail_inventory/flag_regions.csv)

// ?rva0039D440@Rva0039D440@@QAEXPAPAV1@@Z @0x0039D440 (48B).
// List-remove: unlinks this from the +0x3C/+0x40 doubly-linked list, updating
// the head through its slot when this has no prev, then clears both links.
// Retail shape is next-gated prev store plus prev-gated next store else head
// store plus two and-zero clears plus ret 4. Sibling of the 0x0039D429 prepend
// and 0x0039D40F isInList sharing the same link layout; caller at 0x0039D4F2
// passes a +0x334 list head. Owner unproven so the name keeps the address token.

class Rva0039D440
{
public:
	void rva0039D440(Rva0039D440 **head);

private:
	char m_pad00[0x3C];
	Rva0039D440 *m_prev3C; // +0x3C
	Rva0039D440 *m_next40; // +0x40
};

void Rva0039D440::rva0039D440(Rva0039D440 **head)
{
	if( m_next40 )
	{
		m_next40->m_prev3C = m_prev3C;
	}
	if( m_prev3C )
	{
		m_prev3C->m_next40 = m_next40;
	}
	else
	{
		*head = m_next40;
	}
	m_prev3C = 0;
	m_next40 = 0;
}
