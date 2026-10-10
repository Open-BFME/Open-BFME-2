// cl: /O1 /G7 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
#include <list>
class Object;
namespace _STL {
template<> _List_base<int,allocator<int> >::_List_base(const allocator<int>&);
template<> _List_base<int,allocator<int> >::~_List_base();
}
class Xfer;
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"
// Retail C63230 is the secondary counter interface at primary+4.
// Its source identity is not established; retain a neutral local view.
class TunnelCounter
{
public:
    TunnelCounter() {}
    virtual void rva004F5391(bool) = 0;
};
// Identity: literal TunnelTracker at C63234 slot2; named destructor,
// loadPostProcess and xfer providers occupy the remaining primary slots.
// Layout: constructor writes vptrs at0/4; lists8/10/14, counterC;
// words18/1C/20/24. Secondary counter body accesses secondary-this+8.
class TunnelTracker : public Snapshot, public TunnelCounter
{
public:
    TunnelTracker();
    virtual void rva004F5391(bool);
protected:
    virtual ~TunnelTracker();
    virtual void loadPostProcess();
    virtual const char *GetSnapshotName() const;
    virtual void xfer(Xfer*);
private:
    _STL::list<int> ids;
    unsigned unknownC;
    _STL::list<Object*> contained;
    _STL::list<int> transfer;
    unsigned unknown18, unknown1C, nemesis, timestamp;
};
TunnelTracker::TunnelTracker()
{
    unknown1C = 0;
    unknown18 = 0;
    nemesis = 0;
    timestamp = 0;
    unknownC = 0;
}

void TunnelTracker::rva004F5391(bool up)
{
    if (up) ++unknownC;
    else --unknownC;
}
const char *TunnelTracker::GetSnapshotName() const
{
    return "TunnelTracker";
}
