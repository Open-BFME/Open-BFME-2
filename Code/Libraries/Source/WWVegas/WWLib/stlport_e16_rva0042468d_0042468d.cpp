// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
// ?rva0042468D@BfmeE16Vector@@QAEXI@Z @0x0042468D 48B. BfmeE16Vector zero-resize wrapper calling rowed two-arg resize.
// Evidence: calls rowed ?resize@BfmeE16Vector@@QAEXIUBfmeE16@@@Z 0x000B0693; forwards ecx; zeroes 16-byte element.
#include <vector>

struct BfmeE16 { float x, y, z, w; };
struct BfmePod16 { int a[4]; };

class BfmeE16Vector : public _STL::vector<BfmeE16, _STL::allocator<BfmeE16> >
{
public:
	void resize(unsigned int n, BfmeE16 x);
	void rva0042468D(unsigned int n);
};

void BfmeE16Vector::rva0042468D(unsigned int n)
{
	BfmePod16 z;
	z.a[0] = 0;
	z.a[1] = 0;
	z.a[2] = 0;
	z.a[3] = 0;
	resize(n, *(BfmeE16*)&z);
}
