// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Retail 0x0040B17B (45B): STLport _Construct<Rva0040AF66,Rva0040AF66>.
// Native vector overflow/push-back calls target this copy-construction body.
// Element stride 0x68 is proven by those callers; source identity follows
// their existing STLport specialization and the generic placement-new body.
// Evidence: calls rowed copy ctor 0x0040AF66; EH prolog with state 0; null check on dst; callers 0x0040B1DB 0x0040B206 stride 0x68; same 45B shape as rowed 0x0040B14E.
#include <vector>
#include <new>

class Rva0040AF66
{
public:
	Rva0040AF66(const Rva0040AF66 &other);
private:
	char m_unrecovered[0x68];
};

template void _STL::_Construct<Rva0040AF66, Rva0040AF66>(
	Rva0040AF66 *, const Rva0040AF66 &);
