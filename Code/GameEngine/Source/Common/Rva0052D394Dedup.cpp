// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?AddPlayer@LivingWorldCampaign@@QAEXABVRva002E0A0A@@@Z 0x0052D394 93B evidence: chain via 0x0052D31E just landed; dedup via StringBase compare 0x000069D6 plus push_back 0x0052D31E; stride 0x28 idiv; caller 0x002E1DD4; v4 no-G7 for regalloc edi-ebx flip; same C++ as overflow-file attempt which was 93-vs-93 regs-only.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

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
class LivingWorldCampaign {
    char _m00[0x24];
public:
    _STL::vector<Rva002E0A0A> m_24;
    void AddPlayer(const Rva002E0A0A &arg);
};
void LivingWorldCampaign::AddPlayer(const Rva002E0A0A &arg)
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
