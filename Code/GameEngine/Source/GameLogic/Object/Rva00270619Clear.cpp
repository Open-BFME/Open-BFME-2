// cl: /MD
// ?Rva00270619Clear@Rva00270619@@QAEXH@Z @0x00270619 43B
// Clears bit in dword at +0x118; when bit is 0x10 also inits +0x68 subobject (+0x34 to 10 and +0x38 to 2).
// Evidence: callers at 0x004830A3 and 0x004AD669 and 0x004AD797 and 0x00291E7A; no donor; honest Rva name.
struct Rva00270619Sub
{
	unsigned char m_pad00[0x34];
	int m_34;
	unsigned char m_38;
};

class Rva00270619
{
public:
	void Rva00270619Clear(int bit);

private:
	unsigned char m_pad00[0x68];
	Rva00270619Sub *m_68;
	unsigned char m_pad6C[0x118 - 0x6C];
	int m_118;
};

void Rva00270619::Rva00270619Clear(int bit)
{
	m_118 &= ~bit;
	if (bit == 0x10) {
		if (m_68) {
			m_68->m_34 = 10;
			m_68->m_38 = 2;
		}
	}
}
