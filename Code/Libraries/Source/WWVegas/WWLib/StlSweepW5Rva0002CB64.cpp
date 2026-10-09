// cl: /O1 /G7 /EHsc /MD /Ireference/shims/bfme2_ascii
#define BFME_ASCII_DTOR_DECL
// Retail2CB64/25B and erase2CCFC prove two cdecl pointer arguments/4B stride.
// Cleanup calls the genuine ordinary5B destructor48BA39, which releases36410.
// Original enclosing record/container identities are unknown.
#include "ascii_string.h"
namespace _STL {
template<class I> void _Destroy(I first,I last) {
    for (;first!=last;++first) first->~AsciiString();
}
template void _Destroy<AsciiString*>(AsciiString*,AsciiString*);
}
