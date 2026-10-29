// cl: /O1 /G7 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/stlp_nodealloc
// stlport46
// ??1Rva0073F4F3@@QAE@XZ @0x0073F4F3 105B.
// Dtor with EH states destroying +0x28/+0x20 Rva0040EDB then +0x1c cleanup
// then +0x14/+0x0c Rva0040EDB then +0x08 cleanup. Evidence: chain lane packet
// calls 0x0073F368 twice plus rowed 0x00040EDB four times; callers unclaimed.
#include "../../Include/Common/Rva00041004Lock.h"
// Same12B queue element as the actual producer/consumer and list provider.
#include <list>
class Rva0036CA00Str {public:void *m_item;Rva0036CA00Str();Rva0036CA00Str(const Rva0036CA00Str&);~Rva0036CA00Str();};
struct TargetNestedHandleData;
struct TargetNestedHandle {TargetNestedHandleData*item;};
struct Rva0073EEE0ListValue {Rva0036CA00Str helperManagedPointer;unsigned unknown_04;TargetNestedHandle handle_08;Rva0073EEE0ListValue();Rva0073EEE0ListValue(const Rva0073EEE0ListValue&);~Rva0073EEE0ListValue();};
namespace _STL {template<> _List_base<Rva0073EEE0ListValue,allocator<Rva0073EEE0ListValue> >::~_List_base();}
typedef _STL::list<Rva0073EEE0ListValue> WorkList;
class Rva0073F4F3 {
public:
    ~Rva0073F4F3();
    char m_pad00[8];
    WorkList m_08;
    Rva0040EDB m_0c;
    Rva0040EDB m_14;
    WorkList m_1c;
    Rva0040EDB m_20;
    Rva0040EDB m_28;
};
Rva0073F4F3::~Rva0073F4F3()
{
}
