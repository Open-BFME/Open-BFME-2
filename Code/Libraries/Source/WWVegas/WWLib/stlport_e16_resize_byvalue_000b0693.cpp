// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
// ?resize@BfmeE16Vector@@QAEXIUBfmeE16@@@Z @0x000B0693 65B. 16-byte vector resize by value.
// Evidence: calls rowed erase 0x002BF70F and just-landed fill-insert 0x000B0395; shape follows stlport_pod8_resize_byvalue.cpp.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

struct BfmeE16 { float x, y, z, w; };
struct BfmePod16 { int a[4]; };

class BfmeE16Vector : public _STL::vector<BfmeE16, _STL::allocator<BfmeE16 > >
{
public:
	void resize(unsigned int n, BfmeE16 x);
	void resize(unsigned int n);
};

void BfmeE16Vector::resize(unsigned int n, BfmeE16 x)
{
	if (n < size())
		(( _STL::vector<BfmePod16, _STL::allocator<BfmePod16> >*)this)->erase((BfmePod16*)(begin() + n), (BfmePod16*)end());
	else
		_M_fill_insert(end(), n - size(), x);
}

void BfmeE16Vector::resize(unsigned int n)
{
	BfmePod16 z;
	for (int i = 0; i < 4; ++i)
		z.a[i] = 0;
	resize(n, *(BfmeE16*)&z);
}
