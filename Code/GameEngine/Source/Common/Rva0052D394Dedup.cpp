// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?rva0052D394@Rva0052D394@@QAEXABVRva002E0A0A@@@Z 0x0052D394 93B evidence: chain via 0x0052D31E just landed; dedup via StringBase compare 0x000069D6 plus push_back 0x0052D31E; stride 0x28 idiv; caller 0x002E1DD4; v4 no-G7 for regalloc edi-ebx flip; same C++ as overflow-file attempt which was 93-vs-93 regs-only.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>
class Rva002E0A0A {
    char opaque[40];
public:
    Rva002E0A0A(const Rva002E0A0A &);
    Rva002E0A0A &operator=(const Rva002E0A0A &);
    ~Rva002E0A0A();
};
namespace _STL {
template <> void _Construct<Rva002E0A0A, Rva002E0A0A>(
    Rva002E0A0A *, const Rva002E0A0A &);
}
template <typename T> class StringBase { public: int compare(const StringBase &o) const; };
class Rva0052D394 {
    char _m00[0x24];
public:
    _STL::vector<Rva002E0A0A> m_24;
    void rva0052D394(const Rva002E0A0A &arg);
};
void Rva0052D394::rva0052D394(const Rva002E0A0A &arg)
{
    unsigned i = 0;
    for (; i < m_24.size(); ++i) {
        const StringBase<char> &argStr = *(const StringBase<char> *)((const char *)&arg + 8);
        const StringBase<char> &elemStr = *(const StringBase<char> *)((const char *)&m_24[i] + 8);
        if (argStr.compare(elemStr) == 0)
            return;
    }
    m_24.push_back(arg);
}
