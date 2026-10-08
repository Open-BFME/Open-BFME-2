// cl: /O1 /MD
// ?rva002D2C21@Rva005248D0@@QBEHXZ @0x002D2C21 (19B): the third bit getter
// beside the rowed 0x002D2C12/0x002D2C18 (Rva002D2C12BitGetters.cpp) on the
// same receiver: 1 when bit 2 of the flag byte at +0x24 is set and the
// signed 8-bit field in the top byte of the word at +0x28 is zero.
// Retail tests that field with test byte [ecx+0x2B],0xFF and returns through
// xor eax,eax / inc eax: a signed int:8 bitfield gives both (an unsigned or
// bool member compiles to cmp/sete). Names stay address-derived.
class Rva005248D0
{
public:
	int rva002D2C21() const;
private:
	char m_pad[0x24];
	unsigned char m_b0 : 1;
	unsigned char m_b1 : 1;
	unsigned char m_b2 : 1;
	unsigned char m_rest : 5;
	char m_pad25[3];
	int m_lo28 : 24;
	int m_hi2B : 8;	// +0x2B
};

int Rva005248D0::rva002D2C21() const
{
	return m_b2 && !m_hi2B;
}
