// cl: /DNDEBUG /MD
// ?rva00115DA7@Rva00115DA7@@QAEXHHHHH@Z @0x00115DA7 43B. Identity: 5-int setter storing first four at +0xA8/+0xB0/+0xB8/+0xC0 via this+8 layout; fifth unused for ret 0x14.
// Evidence: caller 0xE424C; neighbours 0x115F73/0x115DE8; no callees.
class Rva00115DA7
{
public:
	void rva00115DA7(int a, int b, int c, int d, int e);
private:
	unsigned char m_pad[0xA8];
	int m_a8;
	unsigned char m_gapAC[4];
	int m_b0;
	unsigned char m_gapB4[4];
	int m_b8;
	unsigned char m_gapBC[4];
	int m_c0;
};

void Rva00115DA7::rva00115DA7(int a, int b, int c, int d, int e)
{
	m_a8 = a;
	m_b0 = b;
	m_b8 = c;
	m_c0 = d;
	(void)e;
}
