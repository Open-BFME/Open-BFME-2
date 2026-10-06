// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??$_Construct@URva00541021@@U1@@_STL@@YAXPAURva00541021@@ABU1@@Z @0x0054105B 18B: STLport placement-copy for 28-byte Rva00541021 element. Evidence: calls rowed copy ctor 0x00541021; callers are vector helpers 0x005410E3 0x005411C8 0x00541709 0x00541D10; throw on callee suppresses EH per section 4.2.
#include <memory>
struct Rva00541021
{
public:
    Rva00541021(const Rva00541021 &other) throw();
};
template void _STL::_Construct<Rva00541021, Rva00541021>(Rva00541021 *, const Rva00541021 &);
