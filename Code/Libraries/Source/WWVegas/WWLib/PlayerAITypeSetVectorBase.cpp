// cl: /O1 /G7 /MD /EHsc /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// Native211E58 empty header is the actual29B STLport constructor. Parser
// family uses the independently proven16B name/library-vector record.
// This ordinary instantiation and its11B allocator proxy are complete
// byte-and-relocation twins of the existing owners; neither adds code credit.
#include "ascii_string.h"
#include <vector>
struct BfmeVectorRecord0002154F3 { AsciiString name; _STL::vector<AsciiString> libraries; };
template _STL::_Vector_base<BfmeVectorRecord0002154F3,_STL::allocator<BfmeVectorRecord0002154F3> >::_Vector_base(const _STL::allocator<BfmeVectorRecord0002154F3>&);
