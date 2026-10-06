// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva0039D429@Rva0039D429@@QAEXPAPAV1@@Z @0x0039D429 (23B).
// Head-prepend: stores the current head into this+0x40, links the old head
// back through its +0x3C slot when present, then publishes this as the new
// head. Retail shape is two loads of *head (aliasing forces the reload
// after the next store) plus test plus back-link plus head store plus
// ret 4. Caller at 0x0039D4CF passes a +0x334 list head; the +0x3C/+0x40
// pair is the standard doubly-linked layout, owner unproven so the name
// keeps the address token.

class Rva0039D429
{
public:
	void rva0039D429(Rva0039D429 **head);

private:
	char m_pad00[0x3C];
	Rva0039D429 *m_prev3C; // +0x3C
	Rva0039D429 *m_next40; // +0x40
};

void Rva0039D429::rva0039D429(Rva0039D429 **head)
{
	m_next40 = *head;
	Rva0039D429 *old = *head;
	if (old) {
		old->m_prev3C = this;
	}
	*head = this;
}
