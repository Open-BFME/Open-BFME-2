// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??1?$vector@UBfmeVectorRecord00319C84@@V?$allocator@UBfmeVectorRecord00319C84@@@_STL@@@_STL@@QAE@XZ retail 0x00319B58 63B: vector dtor via Destroy plus free.
// Evidence: calls pin Destroy 0x00319784 and rowed free 0x00030830 with EH prolog scopetable 0x00B7A8FD; callers include thunk and unwinds.
#include "ascii_string.h"
#include <vector>
struct BfmeVectorRecord00319C84 {
    AsciiString text;
    _STL::vector<AsciiString> names;
    BfmeVectorRecord00319C84();
    BfmeVectorRecord00319C84(const BfmeVectorRecord00319C84 &);
};
namespace _STL {
template <> void _Construct<BfmeVectorRecord00319C84, BfmeVectorRecord00319C84>(BfmeVectorRecord00319C84 *, const BfmeVectorRecord00319C84 &);
}
template _STL::vector<BfmeVectorRecord00319C84, _STL::allocator<BfmeVectorRecord00319C84> >::~vector();
