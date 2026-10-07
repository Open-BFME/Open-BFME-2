// cl: /O1 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /Ireference/shims/bfmealloc
// ??1Rva001E7087@@MAE@XZ @0x001E86D0 96B
// Banked attempt reverse/attempts/0x001e86d0.cpp, re-verified exact against the current ledger
// (its callees have since been rowed or pinned); landed unchanged by the
// banked-attempt sweep. Identity and evidence: see reverse/re_attempts.log.
// stlport
// Scratch layout proof only. The native four-slot table at BDE950 has a
// no-argument empty slot then a name getter and a413B worker, so this view
// must not be landed as proof of the canonical Snapshot virtual interface.
// Native96B dtor and53B ctor prove pointer-vector4 and string18/1C cleanup.
#include <vector>
void Rva00030830FreeAllocation(void *);
namespace _STL {
template<> inline void allocator<void *>::deallocate(void **p, unsigned int) const
{ if (p) ::Rva00030830FreeAllocation(p); }
}
#pragma comment(linker, "/alternatename:?Rva00030830FreeAllocation@@YAXPAX@Z=_free")
#include "ascii_string.h"
#include "Common/Snapshot.h"
class Rva001E7087 : public Snapshot {
public:
    Rva001E7087();
protected:
    virtual ~Rva001E7087();
private:
    void rvaClear();
    _STL::vector<void *> m_vec04;
    int m_10;
    unsigned char m_14, m_15;
    AsciiString m_18, m_1c;
    float m_20;
};
Rva001E7087::Rva001E7087()
    : m_vec04(_STL::allocator<void *>()), m_10(0), m_14(0), m_15(0), m_20(0.0f) {}
Rva001E7087::~Rva001E7087() { rvaClear(); }

// Banked byte proof: [1E86D0,1E8730)96B, original53B ctor1E7087,
// complete29B pointer-vector base211E58, complete11B proxy14F3C4 exact.
// Clear call has the full83B independently rowed provider1E7E25; its
// consumed pointer-vector4 and flags10/14/15 agree with this native view.
// C++ free30830/17 reproduces the EH-state store before vector deallocation.
// Native virtual table7DE950 has28B delete1E8F03;1B empty B3FD0;
// 6B name getter1E70BC returning LocomotorSet;413B worker1E8730.
// The canonical Snapshot view instead declares crc(Xfer*),xfer(Xfer*),
// loadPostProcess(). Neither its virtual signatures nor this class's
// inherited relationship is proved by the identical final BBB554 store.
// Landing must reconcile that interface and all kept provider definitions;
// do not emit a guessed purecall table or claim vector<BfmeE16> semantics.
#pragma comment(linker, "/alternatename:?rvaClear@Rva001E7087@@AAEXXZ=?rva001E7E25@Rva001E7E25@@QAEXXZ")
