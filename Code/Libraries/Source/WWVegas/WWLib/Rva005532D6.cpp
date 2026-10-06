// cl: /MD
// ?rva005532D6@Rva005532D6@@QAEXXZ @0x005532D6 41B: Clear checks +4 calls erase 0x005531DD on root +4 then restores header self links +8 +0xC zeroes +4. Evidence: chain lane calls just-landed 0x005531DD plus callers 0x00553845 0x005540A3 plus header shape from 0x00553890.
class Rva005531DD
{
public:
	void rva005531DD(void *p);
};
struct Rva005532D6Buf
{
	unsigned char b00;
	char pad01[3];
	void *p04;
	Rva005532D6Buf *p08;
	Rva005532D6Buf *p0C;
};
class Rva005532D6
{
public:
	Rva005532D6Buf *m_buf00;
	unsigned m_u04;
	void rva005532D6();
};
void Rva005532D6::rva005532D6()
{
	if (m_u04 == 0)
		return;
	((Rva005531DD *)this)->rva005531DD(m_buf00->p04);
	m_buf00->p08 = m_buf00;
	m_buf00->p04 = 0;
	m_buf00->p0C = m_buf00;
	m_u04 = 0;
}
