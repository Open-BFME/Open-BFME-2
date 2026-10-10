// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// ??0Rva006240E0@@QAE@HHHH@Z @ 0x006240E0 (77B). Four-argument wrapper
// constructor whose only used argument is the hash_map's initial bucket count;
// a non-virtual class with a _STL::hash_map<int, int> member at +0.
// Evidence: SEH frame with handler 0x00BA74FB; the four dword stores at
// +4/+8/+0xC/+0x10 are the hashtable bucket vector's three pointers plus
// _M_num_elements, exactly as in the rowed default ctor ??0Rva0016E400; the
// callee at 0x00622410 is the rowed _M_initialize_buckets of the same
// hash_map<int, int> instantiation; no vtable store; ret 0x10 encodes the four
// declared arguments.
// Target bytes are identical to 0x0016E3B0's except the EH handler immediate
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

class Rva006240E0
{
public:
    Rva006240E0(int n, int a, int b, int c);
private:
    _STL::hash_map<int, int> m_map;
};

Rva006240E0::Rva006240E0(int n, int a, int b, int c) : m_map(n) {}
