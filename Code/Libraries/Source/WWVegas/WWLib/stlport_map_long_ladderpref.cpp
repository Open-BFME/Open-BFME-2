// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport

#include "string_base.h"

// Retail copies each string through its matching narrow or wide StringBase body.
class AsciiString : private StringBase<char>
{
public:
    __forceinline AsciiString(const AsciiString &source) : StringBase<char>(source) {}
    ~AsciiString();
};

class UnicodeString : private StringBase<unsigned short>
{
public:
    __forceinline UnicodeString(const UnicodeString &source) : StringBase<unsigned short>(source) {}
    ~UnicodeString();
};

// LadderPreferences::loadProfile fills these same offsets; the names agree
// with the upstream Common/LadderPreferences.h record and its time_t map key.
class LadderPref
{
public:
    LadderPref();
    __declspec(noinline) LadderPref(const LadderPref &source);

    UnicodeString name;
    AsciiString address;
    unsigned short port;
    long lastPlayDate;
};

#include <map>

template class _STL::map<long, LadderPref, _STL::less<long>, _STL::allocator<_STL::pair<const long, LadderPref> > >;
