// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /O1 /arch:SSE /G7
// stlport
//
// ?rva0037F26D@UnitRevivalTracker@@QAEXXZ @0x0037F26D 14B
// Evidence: adjacent UnitRevivalTracker methods and retail call of the full
// member vector range to the rowed erase instantiation at 0x002E2690.
namespace _STL
{
template <class T> class allocator;
template <class T, class A = allocator<T> >
class vector
{
public:
    typedef T *iterator;
    iterator erase(iterator first, iterator last);
    void clear() { erase(_M_start, _M_finish); }
private:
    T *_M_start;
    T *_M_finish;
    T *_M_end_of_storage;
};
}

struct Rva002E2690Element;

class UnitRevivalTracker
{
    int m_unk00;
    _STL::vector<Rva002E2690Element> m_vec04;

public:
    void rva0037F26D();
};

void UnitRevivalTracker::rva0037F26D()
{
    m_vec04.clear();
}
