// cl: /O1 /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// STLport 4.5.3 bit-vector clear used by retail 0x0006D52A.
// Out-of-line clear delegating to the rowed erase RANGE overload.
#include <vector>
template void _STL::vector<bool>::clear();
