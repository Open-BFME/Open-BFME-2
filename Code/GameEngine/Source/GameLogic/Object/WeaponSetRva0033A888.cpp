// cl: /DNDEBUG /MD /GX-
// stlport
// ?rva0033A888@Rva002C752F@@QAEXXZ @0x0033A888 (81B).
// Ctor-like init for the six-slot WeaponSet block: resets the bitset at
// +0x04 then constructs the 0x1C/0x1C/0x4C arrays through the rowed member
// ctors 0x24C7B3/0x42526 and finishes with the rowed clear 0x002C752F.
// Evidence: caller 0x0033D362 same layout as Rva002C752F clear TU.

namespace _STL
{

template <unsigned _Bits>
class bitset
{
public:
	unsigned long m_words[(_Bits + 31) / 32];
	bitset<128> &reset();
};

}

class Rva0024C7B3Member
{
public:
	Rva0024C7B3Member() throw();

	unsigned char m_data[0x1C];
};

class Rva0042526Member
{
public:
	Rva0042526Member() throw();

private:
	unsigned char m_pad[0x4C];
};

class Rva002C752FBase
{
public:
	Rva002C752FBase() { m_bits.reset(); }

private:
	int m_00;
	_STL::bitset<128> m_bits;
};

class Rva002C752F : public Rva002C752FBase
{
public:
	Rva002C752F();
	void rva002C752F();

private:
	const void *m_tmpl[6];
	int m_mask[6];
	Rva0024C7B3Member m_a[6];
	Rva0024C7B3Member m_b[6];
	Rva0042526Member m_c[6];
	unsigned char m_35C;
	unsigned char m_35D;
	char m_pad35E[2];
	int m_360;
	unsigned char m_364;
};

Rva002C752F::Rva002C752F()
{
	rva002C752F();
}
