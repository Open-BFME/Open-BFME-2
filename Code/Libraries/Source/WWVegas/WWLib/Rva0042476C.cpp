// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva0042476C@@QAE@ABV0@@Z @0x0042476C 61B
// Copy ctor of honest two-vector class: vector<Rva00423A4A> at +0 then vector<unsigned int> at +0xC in declaration order with EH state. Evidence: calls rowed vector copy ctors 0x004244EE then 0x002CFAB9; unblocks 0x00424BF4 via caller 0x00424C10; neighbours stlport vector family same dir and flags.
#include <vector>

struct Rva00423A4A
{
	unsigned int m_data[3];
	~Rva00423A4A() {}
};

class Rva0042476C
{
public:
	Rva0042476C(const Rva0042476C &src);
private:
	_STL::vector<Rva00423A4A> m_vec00;
	_STL::vector<unsigned int> m_vec0C;
};

Rva0042476C::Rva0042476C(const Rva0042476C &src)
	: m_vec00(src.m_vec00)
	, m_vec0C(src.m_vec0C)
{
}
