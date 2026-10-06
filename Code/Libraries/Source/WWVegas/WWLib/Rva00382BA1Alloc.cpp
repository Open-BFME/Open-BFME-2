// cl: /D_STLP_NO_EXCEPTIONS /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ?Rva00382BA1Alloc@@YGPAXPAX@Z 0x00382BA1 34B
// Allocate 20B via byte allocator then copy tail fields at +0x10 via 0x003821A0.
// Evidence: calls 0x000307F0 allocate and 0x003821A0 copy; caller 0x003834AF passes src+0x10.
#include <memory>

void __cdecl Rva003821A0Copy(void* dstRaw, void* srcRaw);

void* __stdcall Rva00382BA1Alloc(void* src)
{
	char* buf = _STL::allocator<char>::allocate(20, 0);
	Rva003821A0Copy(buf + 16, src);
	return buf;
}
