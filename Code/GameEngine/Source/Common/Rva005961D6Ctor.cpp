// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva005961D6@@QAE@XZ, retail 0x005961D6, 79 bytes.
// Derived ctor calling base Rva0025BFE3 ctor at 0x0025BFC7, then two
// Rva003ECA4BElement ctors at +0x10 and +0x54 (0x44 apart, rowed at 0x003ECA4B),
// then vector<BfmeE16> at +0x98 via rowed vector_base at 0x00211E58. Stores
// derived vtable 0x00870A4C. Layout: base 0x10 bytes (vtable+vector), two
// 0x44 elements abutting (+0x10..+0x53, +0x54..+0x97), vector 12 bytes at +0x98.
// Caller at 0x004E0363 constructs this; unblocks 0x004E030B.
#include <vector>
struct BfmeE16 { float x, y, z, w; };
class Rva0025BFE3
{
public:
	Rva0025BFE3();
	virtual ~Rva0025BFE3();
private:
	_STL::vector<BfmeE16> m_vec04;
};
class Rva003ECA4BElement
{
public:
	Rva003ECA4BElement();
};
class Rva005961D6 : public Rva0025BFE3
{
public:
	Rva005961D6();
private:
	Rva003ECA4BElement m_e10;
	char m_pad11[0x43];
	Rva003ECA4BElement m_e54;
	char m_pad55[0x43];
	_STL::vector<BfmeE16> m_vec98;
};
Rva005961D6::Rva005961D6() : Rva0025BFE3(), m_e10(), m_e54(), m_vec98()
{
}
