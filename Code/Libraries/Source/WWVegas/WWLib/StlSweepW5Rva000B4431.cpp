// cl: /O1 /G7 /arch:SSE /EHsc /MD /Ireference/shims/bfme2_ascii
// RetailB4431/47B and B6614 five-argument caller prove this forward-copy ABI.
// Assign through the canonical string worker366F0; no plain-word operation or pin.
// Original enclosing record/container identities are unknown.
#include "ascii_string.h"
namespace _STL {
struct random_access_iterator_tag;
template<class A,class B,class D>
B __copy(A first,A last,B result,const random_access_iterator_tag&,D*) {
    for (D remaining = last-first; remaining>0; --remaining) {
        result->setCopyInline(*first);
        ++first;
        ++result;
    }
    return result;
}
template AsciiString* __copy<AsciiString*,AsciiString*,int>(AsciiString*,AsciiString*,AsciiString*,const random_access_iterator_tag&,int*);
}
