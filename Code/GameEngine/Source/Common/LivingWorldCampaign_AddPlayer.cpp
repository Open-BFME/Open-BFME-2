// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /ICode/GameEngine/Source /Ireference/shims/moduledata /Ireference/shims/bfmealloc
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
    char opaque[36];
public:
    Rva002E0A0A(const Rva002E0A0A &);
    Rva002E0A0A &operator=(const Rva002E0A0A &);
    virtual ~Rva002E0A0A();
};
namespace _STL {
template <> void _Construct<Rva002E0A0A, Rva002E0A0A>(
    Rva002E0A0A *, const Rva002E0A0A &);
}
#include "string_base.h"
#include "ascii_string.h"
#include "../../../Libraries/Include/Lib/BfmeE16.h"
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"
// +0x1C and +0x20 hold objects released through virtual slot 0.
struct RvaItem0052CFB1 { virtual void *get(int x); };
struct Sub0052BAC1;
struct Rva0052CA2D {
 __forceinline Rva0052CA2D():storage(_STL::allocator<BfmeE16>()){}
 ~Rva0052CA2D();
 _STL::_Vector_base<BfmeE16,_STL::allocator<BfmeE16> > storage;
};
struct Rva0052CA6C {
 __forceinline Rva0052CA6C():storage(_STL::allocator<BfmeE16>()){}
 ~Rva0052CA6C();
 _STL::_Vector_base<BfmeE16,_STL::allocator<BfmeE16> > storage;
};
class Rva002E0A0A;
class LivingWorldCampaign : public Snapshot {
public:
 LivingWorldCampaign(const AsciiString &name);
 virtual ~LivingWorldCampaign();
 virtual void loadPostProcess();
 virtual const char *GetSnapshotName() const;
 virtual void xfer(Xfer *);
 void rva0052C0C8();
 static void ParseLivingWorldCampaignBlock(class INI *ini);
 void CreatePlayers(); int AdjustStartingPositionForScenario(int);
 void AddPlayer(const Rva002E0A0A &arg);
 AsciiString m_04; int m_08; Rva0052CA2D m_records; int m_currentIndex;
 Sub0052BAC1 *m_1C; RvaItem0052CFB1 *m_20; Rva0052CA6C players; AsciiString localName;
 AsciiString m_34; int m_38; int m_3c; int m_40; float m_44; float m_48;
 bool fromCampaign; bool m_4d; bool m_4e;
};
void LivingWorldCampaign::AddPlayer(const Rva002E0A0A &arg)
{
    unsigned i = 0;
    for (; i < ((_STL::vector<Rva002E0A0A> &)players).size(); ++i) {
        const StringBase<char> &argStr = *(const StringBase<char> *)((const char *)&arg + 8);
        const StringBase<char> &elemStr = *(const StringBase<char> *)((const char *)&((_STL::vector<Rva002E0A0A> &)players)[i] + 8);
        if (argStr.compare(elemStr) == 0)
            return;
    }
    ((_STL::vector<Rva002E0A0A> &)players).push_back(arg);
}
