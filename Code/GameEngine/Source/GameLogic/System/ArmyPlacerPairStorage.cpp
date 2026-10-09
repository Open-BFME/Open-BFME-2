// cl: /O1 /arch:SSE /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/bfme_stlport_unsigned_max_link
// stlport
#include "unsigned_max.h"
#include <vector>
#include "ArmyPlacerCopyRecord.h"
// STLport4.5.3 typed pair storage. Native 0x00380014 establishes this
// record type at reserve/push_back; all folds must preserve whole bodies
// and the existing allocator/copy/free providers.
namespace _STL {
template<> __declspec(nothrow) void _Construct<Rva0037F8AC,Rva0037F8AC>(Rva0037F8AC*,const Rva0037F8AC&);
}
template void _STL::vector<Rva0037F8AC>::reserve(unsigned);
template void _STL::vector<Rva0037F8AC>::push_back(const Rva0037F8AC&);
namespace _STL {
template<> __declspec(nothrow) void _Construct<Rva0037F8AC,Rva0037F8AC>(Rva0037F8AC *p,const Rva0037F8AC &v) {
    if(p) reinterpret_cast<Rva0037F551*>(p)->rva0037F551(
        *reinterpret_cast<const Rva0037F551*>(&v));
}
}
