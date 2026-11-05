// cl: /GX /MD /DNDEBUG /Ireference/shims/moduledata /Ireference/shims/bfmelist /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x0048DF7A: Snapshot-derived module data with a four-byte list
// at +8; its scalar fields follow the verified FloodUpdate consumer view.
#include <list>
#include "Common/Snapshot.h"

namespace _STL {
template <> _List_base<int, allocator<int> >::_List_base(const allocator<int> &);
template <> _List_base<int, allocator<int> >::~_List_base();
}

class FloodUpdateModuleData : public Snapshot
{
public:
    FloodUpdateModuleData();
    virtual ~FloodUpdateModuleData();
    int m_unk04;
    _STL::list<int> m_members;
    float m_angleOfFlow;
    bool m_directionIsRelative;
};

FloodUpdateModuleData::FloodUpdateModuleData()
{
}
