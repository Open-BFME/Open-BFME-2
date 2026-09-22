// cl: /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
//
// Pod8 vector resize with the fill value taken BY VALUE (retail 0x005FF96A,
// 63B, ends ret 0xC). STLport 4.5.3 only declares the const-ref resize, so
// this TU derives from the real _STL::vector<BfmePod8> instantiation (same
// headers and flags as stlport_pod_vector_malloc_bodies.cpp, whose prologue
// already matches retail through the erase call) and adds the by-value
// overload retail was built with. The by-value parameter is what emits
// retail's lea edi,[esp+0x10] plus push edi argument forwarding. Callees
// resolve to the rowed 2-argument erase (0x003FA4DB) and _M_fill_insert
// (0x000B02B6).
#include <vector>

struct BfmePod8
{
	int a[2];
};

class BfmePod8Vector : public _STL::vector<BfmePod8, _STL::allocator<BfmePod8> >
{
public:
	void resize(unsigned int n, BfmePod8 x);
};

void BfmePod8Vector::resize(unsigned int n, BfmePod8 x)
{
	if (n < size())
		erase(begin() + n, end());
	else
		_M_fill_insert(end(), n - size(), x);
}
