// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?rva00604374@Rva00604374@@QAEPAXABVRva0060426C@@@Z @0x00604374 34B node alloc 0x20 via rowed 0x000307F0 then rowed Construct 0x00604289 at +0x10. Evidence: callers 0x00604400 0x00604419 in insert 0x006043CE same shape as Rva00397CC9Alloc.
#include <memory>

class Rva0060426C;
void Rva00604289Construct(Rva0060426C *dest, const Rva0060426C &src);

class Rva00604374
{
public:
	void *rva00604374(const Rva0060426C &src);
};

void *Rva00604374::rva00604374(const Rva0060426C &src)
{
	char *p = _STL::allocator<char>::allocate(0x20, 0);
	Rva00604289Construct((Rva0060426C *)(p + 0x10), src);
	return p;
}
