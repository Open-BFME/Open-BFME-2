// cl: /MD
// RVA 0x0056A9B5 sets byte at +0x1E to 1 when bytes at +0x1C and +0x1D are both nonzero.
class Rva0056A9B5
{
public:
	void rva0056A9B5();
	void rva0056A9C6();
	char m_lead[0x1C];
	unsigned char m_a;
	unsigned char m_b;
	unsigned char m_c;
};
void Rva0056A9B5::rva0056A9B5()
{
	if (m_a == 0)
		return;
	if (m_b == 0)
		return;
	m_c = 1;
}

// RVA 0x0056A9C6 (9 bytes), right after it and reached only as slot 3 of
// 0x0086D2E8 (??_7Rva0056B0BF@@6BRva0056AC26@@@): set the +0x1C byte, then
// the same guarded set (a tail jump into the body above).
void Rva0056A9B5::rva0056A9C6()
{
	m_a = 1;
	rva0056A9B5();
}
