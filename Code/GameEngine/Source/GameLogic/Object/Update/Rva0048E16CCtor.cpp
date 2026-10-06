// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva0048E16C@@QAE@XZ, retail 0x0048E16C, 29 bytes. Frameless ctor with one
// BfmeE16 vector at +4 via rowed Vector_base 0x00211E58 (one-byte esp+7
// allocator temp) plus ints zeroed at +0/+0x10. No vptr, no base call.
// Callers are unclaimed 0x0048E189 and 0x0048E4E2 (both news 0x14 with this
// as sole ctor). Recipe follows DetachableRiderUpdateModuleDataCtor (vector
// via 0x211E58 with stack temp, ints zeroed).

#include <vector>

struct BfmeE16 { float x, y, z, w; };

class Rva0048E16C
{
public:
	Rva0048E16C();

private:
	int m_00; // +0
	_STL::vector<BfmeE16> m_vec; // +4
	int m_10; // +0x10
};

Rva0048E16C::Rva0048E16C()
{
	m_00 = 0;
	m_10 = 0;
}
