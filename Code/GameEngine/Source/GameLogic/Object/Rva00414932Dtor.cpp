// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
// ??1Rva004147CF@@UAE@XZ @ 0x00414932 75B: novtable dtor restoring Snapshot vtable 0x007BB554,
// calls the ScoredKillTracker vector's dtor at +0x1C, Rva00360D26Member dtor at +0x14,
// StringBase releaseBuffer at +0x04. Precedent Rva0040DB52Dtor; callers include ??_G at 0x00414AEE.
// The vector's element is the registered ScoredKillTracker (44 bytes, virtual destructor): retail's
// _Destroy 0x004144F0 runs it through __destroy_aux 0x0041445C (P134).
#include <vector>

#include "ascii_string.h"
#include "Common/Snapshot.h"
#include "../../Common/ScoredKillTrackerView.h"

// Retail calls the vector's out-of-line destructor 0x004146E2 (StlportVectorDtorDeferred.cpp):
// declare it so this unit does not emit its own copy.
namespace _STL { template <> vector<ScoredKillTracker, allocator<ScoredKillTracker> >::~vector(); }

class __declspec(novtable) Rva004147CF : public Snapshot
{
public:
    virtual ~Rva004147CF();
private:
    AsciiString m_str04;
    char m_pad08[0x14 - 0x08];
    Rva00360D26Member m_member14;
    char m_pad18[0x1C - 0x18];
    _STL::vector<ScoredKillTracker, _STL::allocator<ScoredKillTracker> > m_vec1C;
};

Rva004147CF::~Rva004147CF()
{
}
