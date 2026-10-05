// cl: /O1 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Target destroyloop3615B1/28 steps148 and calls full128B record destructor
// 360FDB. Destroy3615CD/24 forwards first/last with a const false_type tag.
// Opaque148 view asserts no fields. In particular the former StringHead148
// emitter label is not evidence of an AsciiString at element offset zero:
// native360FDB instead tears down six vectors inside the composite record.
// Bind the destructor to its full address-scoped provider via the linker.
// Rehome the existing two helper rows; this adds no byte coverage. STLport
// 4.5.3 is the algorithm guide, target boundaries/calls prove the consumed ABI.
#include <vector>
struct Rva003615E5Record {unsigned char unknown[148]; ~Rva003615E5Record();};
template void _STL::__destroy_aux<Rva003615E5Record*>(Rva003615E5Record*,Rva003615E5Record*,const _STL::__false_type&);
template void _STL::_Destroy<Rva003615E5Record*>(Rva003615E5Record*,Rva003615E5Record*);
#pragma comment(linker, "/alternatename:??1Rva003615E5Record@@QAE@XZ=??1Rva00360F55@@QAE@XZ")
