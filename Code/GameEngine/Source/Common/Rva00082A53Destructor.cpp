// cl: /O1 /Oy- /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva00082A53@@QAE@HHHMPAHH@Z @ 0x00082A53 153B.
// Ctor with two vector members (E12 at +4 via rowed 0x0007FAEA, E16 at +0x18
// via rowed 0x00211E58), ints at +0/+0x10/+0x14, three ints from pointer at
// +0x24/+0x28/+0x2C, float at +0x30. Word resize at +4 via rowed 0x000824F9
// and Pod44 reserve at +0x18 via rowed 0x00081A75. Evidence: callees all
// rowed; caller 0x0008304A; prev/next OpaqueScalarDeletingDtors.
#include <vector>

struct BfmeE12 { float x, y, z; };
struct BfmeE16 { float x, y, z, w; };
void Rva00030830FreeAllocation(void *);
namespace _STL {
 template<> inline void allocator<BfmeE12>::deallocate(BfmeE12 *p,size_type) const { if(p)Rva00030830FreeAllocation(p); }
 template<> inline void allocator<BfmeE16>::deallocate(BfmeE16 *p,size_type) const { if(p)Rva00030830FreeAllocation(p); }
}
struct BfmePod44 { int a[11]; };
struct BfmeWordVec : _STL::vector<unsigned short, _STL::allocator<unsigned short> >
{
	void resize(unsigned int n, unsigned short x);
};

class Rva00082A53
{
	int m_unk00;
	_STL::vector<BfmeE12, _STL::allocator<BfmeE12> > m_vec04;
	int m_dim10;
	int m_dim14;
	_STL::vector<BfmeE16, _STL::allocator<BfmeE16> > m_vec18;
	int m_data24;
	int m_data28;
	int m_data2C;
	float m_val30;
public:
	Rva00082A53(int a1, int a2, int a3, float a4, int *a5, int a6);
	~Rva00082A53();
};

// Native81EC1..81F03: automatic vector cleanup in reverse member order.
// Throwing allocator free preserves the native two-state EH frame.
// Owner name remains neutral; vector offsets established by target and rowed ctor.
Rva00082A53::~Rva00082A53() {}
