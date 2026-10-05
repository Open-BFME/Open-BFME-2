// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// STLport 4.5.3 _Construct over the independently rowed payload copy ctor.
#include <memory>
class Rva004D971D {
public:
    __declspec(nothrow) Rva004D971D(const Rva004D971D &);
};
template void _STL::_Construct<Rva004D971D, Rva004D971D>(Rva004D971D *, const Rva004D971D &);
