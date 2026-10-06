// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// ??0Rva005A9562@@QAE@PAX@Z, retail 0x005A9562 38B.
// Ctor: void* at +0 stored, vector<BfmeE16> at +4 via rowed Vector_base
// 0x00211E58, int at +0x10 cleared, int at +0x14 set to -1. Evidence: retail
// calls Vector_base<BfmeE16> ctor, sets [esi+0x10]=0 and [esi+0x14]=-1, returns
// this with ret 4. BfmeE16 is the 16B stand-in from stlport_vector_e16_o1.
#include <vector>
struct BfmeE16 { float x, y, z, w; };
class Rva005A9562
{
public:
	Rva005A9562(void *p);
private:
	void *m_ptr; // +0
	_STL::vector<BfmeE16> m_vec; // +4
	int m_a; // +0x10
	int m_b; // +0x14
};
Rva005A9562::Rva005A9562(void *p)
	: m_ptr(p), m_vec(_STL::allocator<BfmeE16>())
{
	m_a = 0;
	m_b = -1;
}
