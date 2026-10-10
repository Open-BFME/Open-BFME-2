// cl: /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii
// stlport
// Native358C60..358C7B is the27B return-buffer pair-factory twin of2C621.
// Its owned50EDB3 ctor establishes a narrow string plus counted4B handle.
// The call supplies the result pointer and two references; original factory
// identifier is unknown. Preserve the existing constructor specialization.
#include <utility>
#include "ascii_string.h"
struct TargetRef00217D4C;
struct TreeHintRef00217D4C {
 TargetRef00217D4C *m_ptr;
 TreeHintRef00217D4C(const TreeHintRef00217D4C &);
 ~TreeHintRef00217D4C();
};
typedef _STL::pair<const AsciiString,TreeHintRef00217D4C> Pair358C60;
namespace _STL { template<> Pair358C60::pair(const AsciiString &,const TreeHintRef00217D4C &); }
Pair358C60 __cdecl Rva00358C60Factory(const AsciiString &key,const TreeHintRef00217D4C &value) {
 return Pair358C60(key,value);
}
