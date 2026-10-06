// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?Rva005472D3Alloc@@YGPAXABUBfmeFloat4Record00469C61@@@Z retail 0x005472D3 37B
// Allocate 20B node, zero the head int, construct Float4 record at +4.
// Evidence: unlock lane calls allocate 0x000307F0 plus _Construct 0x00469C61;
// callers at 0x00547334 0x00547460 unblock 0x005472F8 0x00547430.
#include <memory>
#include <vector>
struct BfmeFloat4Record00469C61 {
	float x, y, z, w;
	BfmeFloat4Record00469C61() {}
	BfmeFloat4Record00469C61(const BfmeFloat4Record00469C61 &o) : x(o.x), y(o.y), z(o.z), w(o.w) {}
	BfmeFloat4Record00469C61 &operator=(const BfmeFloat4Record00469C61 &o) { x = o.x; y = o.y; z = o.z; w = o.w; return *this; }
};
void *__stdcall Rva005472D3Alloc(const BfmeFloat4Record00469C61 &src)
{
	char *p = _STL::allocator<char>::allocate(0x14, 0);
	*(int *)p = 0;
	_STL::_Construct((BfmeFloat4Record00469C61 *)(p + 4), src);
	return p;
}
