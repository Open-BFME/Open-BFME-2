// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /O1 /arch:SSE /G7
// stlport
//
// ?rva0037F26D@UnitRevivalTracker@@QAEXXZ @0x0037F26D 14B
// Evidence: adjacent UnitRevivalTracker methods and retail call of the full
// member vector range to the rowed erase instantiation at 0x002E2690.
#include <vector>

struct Rva002E2690Element;

// The real STLport vector replaces the private three-pointer view; erase stays
// a declaration bound to the rowed 0x002E2690 provider, which clear() calls
// over the whole member range.
namespace _STL
{
template <> vector<Rva002E2690Element>::iterator vector<Rva002E2690Element>::erase(iterator, iterator);
}

class UnitRevivalTracker
{
    int m_unk00;
    _STL::vector<Rva002E2690Element> m_entries;

public:
    void rva0037F26D();
};

void UnitRevivalTracker::rva0037F26D()
{
    m_entries.clear();
}
