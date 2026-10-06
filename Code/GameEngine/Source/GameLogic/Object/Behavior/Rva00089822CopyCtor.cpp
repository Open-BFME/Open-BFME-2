// cl: /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
// ??0Rva00089822@@QAE@ABV0@@Z, retail 0x00089822, 35 bytes.
// Copy ctor: 8-byte head via two movs, Rva0073DAB0 member at +8 via rowed
// set 0x00087A74 on other's +8 as Blk (same address as first member).
// Evidence: frameless thiscall ret 4, no self-check, returns this,
// rowed set callee, unblocks 0x0008A173. Owner unknown so honest Rva name.
struct Rva0073DAB0Blk
{
	int a;
	int b;
	int c;
	char d;
};

class Rva0073DAB0
{
public:
	Rva0073DAB0 &set(const Rva0073DAB0Blk *p) throw();
};

class Rva00089822
{
public:
	Rva00089822(const Rva00089822 &other);

private:
	int m_00;
	int m_04;
	Rva0073DAB0 m_rva;
};

Rva00089822::Rva00089822(const Rva00089822 &other)
{
	m_00 = other.m_00;
	m_04 = other.m_04;
	m_rva.set((const Rva0073DAB0Blk *)&other.m_rva);
}
