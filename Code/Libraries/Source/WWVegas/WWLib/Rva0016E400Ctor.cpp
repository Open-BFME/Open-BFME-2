// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// ??0Rva0016E400@@QAE@XZ @ 0x0016E400 (72B). Default ctor for non-virtual wrapper with hash_map<int int> at +0.
// Evidence: push 0x64 matches hash_map() default 100 in vendor/stlport/stl/_hash_map.h; callee is _M_initialize_buckets for hashtable<pair<const int int> hash<int>> rowed at 0x00622410 in stlport_hash_map_int.cpp; zeros at +4 +8 +0xC +0x10 are buckets vector plus num_elements; no vtable store; caller is unclaimed 0x0016E450 which becomes ready.

// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <hash_map>

class Rva0016E400
{
public:
    Rva0016E400();
private:
    _STL::hash_map<int, int> m_map;
};

Rva0016E400::Rva0016E400() : m_map() {}

// ??0Rva00624D60@@QAE@XZ, retail 0x00624D60, 72 bytes: the same constructor (a
// default hash_map<int, int> member) for another class; only the EH handler
// record differs from ??0Rva0016E400's bytes. Identity unknown.
class Rva00624D60
{
public:
    Rva00624D60();
private:
    _STL::hash_map<int, int> m_map;
};
Rva00624D60::Rva00624D60() : m_map() {}
