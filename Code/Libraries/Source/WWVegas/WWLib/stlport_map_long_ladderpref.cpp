// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport


#include "unicode_string.h"

// Retail copies each string through its matching narrow or wide StringBase body.
class AsciiString : private StringBase<char>
{
public:
    __forceinline AsciiString(const AsciiString &source) : StringBase<char>(source) {}
    ~AsciiString();
};

// LadderPreferences::loadProfile fills these same offsets; the names agree
// with the upstream Common/LadderPreferences.h record and its time_t map key.
class LadderPref
{
public:
    LadderPref();
    __declspec(noinline) LadderPref(const LadderPref &source);
    ~LadderPref();

    UnicodeString name;
    AsciiString address;
    unsigned short port;
    long lastPlayDate;
};

#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

template class _STL::map<long, LadderPref, _STL::less<long>, _STL::allocator<_STL::pair<const long, LadderPref> > >;
