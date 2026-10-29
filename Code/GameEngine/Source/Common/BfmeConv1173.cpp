// Open-BFME5 conversions.

class BfmeSlot1173
{
public:
	void bfmeStore1173(void *k, int v);
};

class BfmeE1173
{
public:
	bool bfmeHit1173(void *a1, void *transactions);
	char m_bfmePad0[4];
	int m_bfme04;
	char m_bfmePad1[0x34];
	char *m_bfme3c;
	int m_bfme40;
	int m_bfme44;
	void *m_transaction;
};

bool BfmeE1173::bfmeHit1173(void *a1, void *transactions)
{
	BfmeSlot1173 *e;
	int i;

	if (transactions != m_transaction)
		return false;

	i = m_bfme44;

	if (i >= m_bfme40)
		e = 0;
	else
		e = (BfmeSlot1173 *)(m_bfme3c + i * 48);

	m_bfme44 = i + 1;
	e->bfmeStore1173(a1, m_bfme04);

	int nextSlot = m_bfme44;
	int slotCount = m_bfme40;

	return nextSlot >= slotCount;
}
