// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// vector<Rva0014F4C2>::_M_insert_overflow @0x001503EC, 181B.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>

extern "C" const unsigned char __identifier("??_7Base@@6B@")[];

class __declspec(novtable) Rva00BC6F24Base
{
public:
	Rva00BC6F24Base() { *(const void **)this = __identifier("??_7Base@@6B@"); }
	virtual ~Rva00BC6F24Base();
};

inline Rva00BC6F24Base::~Rva00BC6F24Base()
{
	*(const void **)this = __identifier("??_7Base@@6B@");
}

extern "C" const void* const __identifier("??_7Rva0007E04D@@6B@")[];

class __declspec(novtable) Rva0014F401 : public Rva00BC6F24Base
{
public:
	Rva0014F401() { *(const void**)this=__identifier("??_7Rva0007E04D@@6B@"); }
	Rva0014F401(const Rva0014F401 &other);
	virtual ~Rva0014F401() {}
};

extern "C" const void* const __identifier("??_7SourceNamespace_PointLight@FXShaderParameterSourceNamespaceSAS@@6B@")[];

class __declspec(novtable) Rva0014F4C2 : public Rva0014F401
{
public:
	Rva0014F4C2() { *(const void**)this=__identifier("??_7SourceNamespace_PointLight@FXShaderParameterSourceNamespaceSAS@@6B@"); }
	Rva0014F4C2(const Rva0014F4C2 &other);
	virtual ~Rva0014F4C2() {}
	int index;
};

// Preserve STLport placement-copy inlining without another external specialization (StlportConstructCopySiblings.cpp owns the
// retail helper); the direct constructor call carries no /EHsc placement-delete cleanup, which would keep it out of line.
namespace _STL {
static inline void _Construct(Rva0014F4C2 *dest, const Rva0014F4C2 &source) { if (dest) dest->Rva0014F4C2::Rva0014F4C2(source); }
}

template void _STL::vector<Rva0014F4C2, _STL::allocator<Rva0014F4C2> >::_M_insert_overflow(
    Rva0014F4C2 *, const Rva0014F4C2 &, const _STL::__false_type &, unsigned int, bool);
