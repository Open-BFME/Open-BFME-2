// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport46
// STLport 4.5.3 priority_queue<_Rva002EBB53Wrap *, vector<...>,
// Rva002EBB53Compare>::pop, retail 0x002F301F, 26 bytes: pop_heap(c.begin(),
// c.end(), comp) through pop_heap 0x002F1F02, then c.pop_back() as finish -=
// 4. Layout from the body: the vector at +0 (begin +0, finish +4) and the
// empty comparator byte at +0xC, pushed by value. Thiscall callers 0x002F3703
// and 0x002F3726 (pathfinder). The heap family and its element view live in
// Code/Libraries/Source/WWVegas/WWLib/Rva002EBB53SiftUp.cpp; same shape as
// the rowed priority_queue<int, vector<int>, greater<int> >::pop 0x003B032A.
#include <queue>
#include <vector>

struct _Rva002EBB53Inner {
    char m_pad[0x10];
    unsigned short m_key;
};
struct _Rva002EBB53Wrap {
    _Rva002EBB53Inner *m_inner;
};
// Empty comparator, greater-than on the payload key: the smallest key is on
// top of the heap.
struct Rva002EBB53Compare {
    bool operator()(const _Rva002EBB53Wrap *a, const _Rva002EBB53Wrap *b) const
    {
        return a->m_inner->m_key > b->m_inner->m_key;
    }
};

extern template void _STL::pop_heap(_Rva002EBB53Wrap **, _Rva002EBB53Wrap **, Rva002EBB53Compare);
template void _STL::priority_queue<_Rva002EBB53Wrap *, _STL::vector<_Rva002EBB53Wrap *>, Rva002EBB53Compare>::pop();
