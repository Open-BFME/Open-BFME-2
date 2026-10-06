// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
// ?resize@BfmePod36Vector@@QAEXIUBfmePod36@@@Z @0x000B06D4 73B. 36-byte vector resize by value.
// Evidence: 0x24 element size via idiv imul, ret 0x28 by-value shape, calls rowed rva00335C88 erase 0x00335C88 plus Pod36 fill-insert 0x000B0478, neighbours E16 resize 0x000B0693 plus Pod8 resize, unblocks 0x000B0899, caller 0x000B08EC.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>

struct BfmePod36
{
	float f[8];
	unsigned char b0;
	unsigned char b1;
	unsigned short w;
};

class Rva00335C88
{
public:
	void *rva00335C88(void *a, void *b);
};

class BfmePod36Vector : public _STL::vector<BfmePod36, _STL::allocator<BfmePod36> >
{
public:
	void resize(unsigned int n, BfmePod36 x);
	void resize(unsigned int n);
};

void BfmePod36Vector::resize(unsigned int n, BfmePod36 x)
{
	if (n < size())
		((Rva00335C88 *)this)->rva00335C88((void *)(begin() + n), (void *)end());
	else
		_M_fill_insert(end(), n - size(), x);
}

void BfmePod36Vector::resize(unsigned int n)
{
	BfmePod36 x = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0 };
	resize(n, x);
}
