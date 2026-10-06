// ??0BfmeChainRecord@@QAE@PAX0PAPAV0@@Z
// cl: /Ob0

class BfmeChainRecord
{
	void *m_first;
	void *m_second;
	BfmeChainRecord **m_ownerLink;
	BfmeChainRecord *m_next;
	void *m_value10;
	void *m_value14;
	void *m_value18;

public:
	BfmeChainRecord(void *first, void *second, BfmeChainRecord **ownerLink);
};

BfmeChainRecord::BfmeChainRecord(void *first, void *second, BfmeChainRecord **ownerLink) :
	m_second(second),
	m_first(first)
{
	m_value10 = 0;
	m_value18 = 0;
	m_ownerLink = ownerLink;
	m_next = *ownerLink;
	if (m_next)
		m_next->m_ownerLink = &m_next;
	*ownerLink = this;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??0BfmeRecEQR@@QAE@PAX0PAPAV0@@Z=??0BfmeChainRecord@@QAE@PAX0PAPAV0@@Z")
