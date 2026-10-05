// cl: /O1 /EHsc /G7 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include "../../../../../vendor/stlport/stl/_algobase.h"
#include "../../../../../vendor/stlport/stl/_uninitialized.h"
#include <vector>

struct Rva0007E4B5Words { unsigned words[3];
 // ?Rva0007E4B5Words::operator= present-unmatched
 Rva0007E4B5Words&operator=(const Rva0007E4B5Words&s){words[0]=s.words[0];words[1]=s.words[1];words[2]=s.words[2];return *this;} };
template Rva0007E4B5Words* _STL::__copy_backward(Rva0007E4B5Words*,Rva0007E4B5Words*,Rva0007E4B5Words*,const _STL::random_access_iterator_tag&,int*);
// Reference STLport4.5.3; native extent and pointer arithmetic establish
// record width12. Explicit scalar assignment form is target-supported
// for this helper shape; no application record identity or field names inferred.
