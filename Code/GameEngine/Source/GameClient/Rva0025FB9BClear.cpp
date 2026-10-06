// cl: /MD /EHsc
// ?rva0025FB9B@Rva0025FB9B@@QAEXXZ @0x0025FB9B 33B. Conditional clears at +0x28/+0x14 with +0x18 to +0x1C copy. Evidence: no calls no immediates caller 0x00260BBF.
class Rva0025FB9B
{
public:
	void rva0025FB9B();
private:
	char m_pad[0x14];
	int m_14;
	int m_18;
	int m_1c;
	char m_pad20[0x8];
	int m_28;
};

void Rva0025FB9B::rva0025FB9B()
{
	int v = m_14;
	if (v == 1 || v == 4)
		m_28 = 0;
	m_1c = m_18;
	if (v == 3)
		return;
	m_14 = 0;
}
