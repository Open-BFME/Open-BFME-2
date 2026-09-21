// cl: /O1 /GX- /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// less<pair<AsciiString,AsciiString>>::operator() at 0x00207150 (18B): push
// both arguments, call the free pair operator< (matched at 0x00206BCF in
// AsciiStringPairLess.cpp), pop-pop, ret 8. This address was rowed as
// less<AsciiString> from the ZH ThingTemplate.cpp spelling, but its call
// target is the pair compare, not the string one at 0x0005598C.

#include <functional>
#include <utility>

class AsciiString
{
public:
    void *m_data;
};

bool operator<(const _STL::pair<AsciiString, AsciiString> &a,
    const _STL::pair<AsciiString, AsciiString> &b);

template struct _STL::less<_STL::pair<AsciiString, AsciiString> >;
