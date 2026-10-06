// cl: /MD
//
// ?rva004D977D@Rva004D977D@@QAEXABURva002C99FB@@0@Z @0x004D977D 51B.
// Conditional copy of two Rva002C99FB structs at +0 and +8.
// Evidence: callee row 0x002C99FB assign; prev Rva004D971DCopy same dir;
// callers at 0x004D981F 0x004D98D3 0x004D9DDB 0x004D9EF4 0x004DA68D.
struct Rva002C99FB
{
	int m_first;
	int m_second;
	Rva002C99FB &operator=(const Rva002C99FB &other);
};

class Rva004D977D
{
public:
	void rva004D977D(const Rva002C99FB &a, const Rva002C99FB &b);
private:
	Rva002C99FB m_00;
	Rva002C99FB m_08;
	char m_pad10[8];
	int m_18;
};

void Rva004D977D::rva004D977D(const Rva002C99FB &a, const Rva002C99FB &b)
{
	if (m_00.m_second == 0 && m_00.m_first == -1)
		m_00 = a;
	if (m_18 != 0 && m_08.m_second == 0)
		m_08 = b;
}
