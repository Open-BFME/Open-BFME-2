// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?Rva0040B17BConstruct@@YAXPAVRva0040AF66@@ABV1@@Z @ 0x0040B17B (45B). Construct Rva0040AF66 via copy ctor.
// Evidence: calls rowed copy ctor 0x0040AF66; EH prolog with state 0; null check on dst; callers 0x0040B1DB 0x0040B206 stride 0x68; same 45B shape as rowed 0x0040B14E.
#include <vector>
#include <new>

class Rva0040AF66
{
public:
	Rva0040AF66(const Rva0040AF66 &other);
};

void __cdecl Rva0040B17BConstruct(Rva0040AF66 *p, const Rva0040AF66 &src)
{
	new (p) Rva0040AF66(src);
}
