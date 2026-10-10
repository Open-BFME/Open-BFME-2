// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
//
// ??0Rva0016E3B0@@QAE@HHHH@Z @ 0x0016E3B0 (77B). Four-argument wrapper
// constructor whose only used argument is the hash_map's initial bucket count;
// a non-virtual class with a _STL::hash_map<int, int> member at +0.
// Evidence: SEH frame with handler 0x00B677AB; the four dword stores at
// +4/+8/+0xC/+0x10 are the hashtable bucket vector's three pointers plus
// _M_num_elements, exactly as in the rowed default ctor ??0Rva0016E400; the
// callee at 0x00622410 is the rowed _M_initialize_buckets of the same
// hash_map<int, int> instantiation; no vtable store; ret 0x10 encodes the four
// declared arguments.
// Target bytes are identical to 0x006240E0's except the EH handler immediate
// and the REL32 to _M_initialize_buckets.

// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <hash_map>

class Rva0016E3B0
{
public:
    Rva0016E3B0(int n, int a, int b, int c);
private:
    _STL::hash_map<int, int> m_map;
};

Rva0016E3B0::Rva0016E3B0(int n, int a, int b, int c) : m_map(n) {}

// ??1?$hashtable@U?$pair@$$CBW4NameKeyType@@VDamageFX@@@_STL@@W4NameKeyType@@U?$hash@W4NameKeyType@@@rts@@U?$_Select1st@U?$pair@$$CBW4NameKeyType@@VDamageFX@@@_STL@@@2@U?$equal_to@W4NameKeyType@@@5@V?$allocator@U?$pair@$$CBW4NameKeyType@@VDamageFX@@@_STL@@@2@@_STL@@QAE@XZ
// @ 0x0016DEE0 (82B). The DamageFX hash_map's hashtable destructor, inlined
// straight out of the header: ~hashtable() { clear(); } then the bucket
// vector's teardown. Evidence: SEH frame with handler 0x00B677AB (the same TU
// handler as ??0Rva0016E3B0); calls the rowed ?clear@...hashtable 0x0016D610;
// the bucket vector's teardown frees _M_start at +4 through the direct game
// free 0x00030830 (reached, not the msvcr71 import, via /D_CRTIMP= and
// /D_STLP_USE_MALLOC); no vtable store; ret (no stack arguments). /GX, not
// /EHsc, is what keeps the destructor's unwind state.
// The NameKeyType/DamageFX/hash declarations below mirror the real DamageFX.h
// instantiation already recovered in DamageFX_hashtableResize.cpp.

enum NameKeyType
{
    NAMEKEY_INVALID = 0,
    FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

class DamageFX
{
public:
    int m_valueWords[0x1E0];
};

inline bool operator==(const DamageFX &x, const DamageFX &y)
{
    return x.m_valueWords[0] == y.m_valueWords[0];
}

namespace rts
{

template<class _Key>
struct hash
{
};

template<>
struct hash<NameKeyType>
{
    unsigned int operator()(const NameKeyType &key) const
    {
        const unsigned int *words = (const unsigned int *)&key;
        return (words[1] << 16) + words[0];
    }
};

template<class _Key>
struct equal_to
{
    bool operator()(const _Key &left, const _Key &right) const
    {
        return left == right;
    }
};

}

// Explicit instantiation of the DamageFX map so this TU emits the rowed
// hashtable members, in particular the destructor that inlines ?clear@... and
// the bucket-vector free. No wrapper function is declared: the matching symbol
// is ??1?$hashtable@... itself (retail's compiler inlined the hash_map and
// hashtable destructor layers straight into it).
template class _STL::hash_map<NameKeyType, DamageFX, rts::hash<NameKeyType>, rts::equal_to<NameKeyType> >;
