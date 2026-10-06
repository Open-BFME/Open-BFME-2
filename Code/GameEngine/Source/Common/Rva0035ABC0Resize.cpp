// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
// ?rva0035ABC0@Rva0035ABC0@@QAEXI@Z retail 0x0035ABC0 32B
// Honest wrapper resizing the Pod8 vector at +0 with a zeroed 8-byte fill:
// xor plus two stosd build theZero pod, then forwards this plus count plus
// the pod by value to the rowed BfmePod8Vector::resize 0x005FF96A.
// Evidence: unlock lane, EBP frame with double stosd, callers at 0x0035ADB5
// and 0x0035AE0A, callee row in stlport_pod8_resize_byvalue.cpp.
#include <vector>
#include <cstring>
#pragma intrinsic(memset)

struct BfmePod8
{
	int a[2];
};

class BfmePod8Vector : public _STL::vector<BfmePod8, _STL::allocator<BfmePod8> >
{
public:
	void resize(unsigned int n, BfmePod8 x);
};

class Rva0035ABC0
{
public:
	void rva0035ABC0(unsigned int n);

private:
	BfmePod8Vector m_vec;
};

void Rva0035ABC0::rva0035ABC0(unsigned int n)
{
	BfmePod8 x;
	memset(&x, 0, sizeof(x));
	m_vec.resize(n, x);
}
