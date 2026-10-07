// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ?rva004E9600@Rva004E9600@@QAE_NPAX@Z @0x004E9600 42B
// Map<int int> contains-check keyed by the int at arg+0x54 via the rowed
// _M_find 0x00388F63; null arg or a miss returns false. The map sits at +0,
// the layout the matched Rva004E962ACtor.cpp fixes. Caller 0x002A8B24.
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

class Rva004E9600
{
public:
    _STL::map<int, int, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > > m_map;
    void *rva004E95D4(void *p);
    bool rva004E9600(void *p);
};

// ?rva004E95D4@Rva004E9600@@QAEPAXPAX@Z @0x004E95D4 44B
// The find twin directly before rva004E9600: same key (the int at arg+0x54),
// same rowed _M_find 0x00388F63, but a hit returns the mapped int as a pointer
// (+0x14 of the node) and a null arg or a miss returns null. Rva002A8F24.cpp's
// 0x002A8F24 is the same logic with the map at +0x908. Caller 0x002A8AB1
// (Rva002A8AE4.cpp), which returns the result as its record pointer.
void *Rva004E9600::rva004E95D4(void *p)
{
    if (p) {
        int key = *(int *)((char *)p + 0x54);
        _STL::map<int, int>::iterator it = m_map.find(key);
        if (it != m_map.end())
            return (void *)(*it).second;
    }
    return 0;
}

bool Rva004E9600::rva004E9600(void *p)
{
    bool result;
    if (p) {
        int key = *(int *)((char *)p + 0x54);
        result = m_map.find(key) != m_map.end();
    } else {
        result = false;
    }
    return result;
}
