// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?Rva005B2FDCPartition@@YAPAURva005B2FDCItem@@PAU1@0U1@URva005B26CECmp@@@Z @0x005B2FDC 74B
// Unguarded partition over 16-byte sort elements with rowed stdcall comparator
// at 0x005B26CE via thiscall twin plus rowed deque-iterator swap at 0x005B2893.
// Evidence: unlock lane ready body; callers 0x005B40BA introsort-loop shape;
// stride 0x10 matches 16-byte elements; pivot at ebp+0x10 comp at ebp+0x20;
// lea ecx for thiscall comp plus two pushes matches 0x00568DB7 precedent.
struct Rva005B2FDCItem
{
    unsigned int w[4];
};

struct Rva005B26CECmp
{
    bool operator()(const void *a, const void *b) const;
};

namespace _STL
{
template <class _Tp> struct _Nonconst_traits;
template <class _Tp, class _Traits> struct _Deque_iterator;
template <class _Tp> void swap(_Tp &a, _Tp &b);
}

Rva005B2FDCItem *Rva005B2FDCPartition(Rva005B2FDCItem *first, Rva005B2FDCItem *last, Rva005B2FDCItem pivot, Rva005B26CECmp comp)
{
    for (;;) {
        while (comp(first, &pivot))
            ++first;
        --last;
        while (comp(&pivot, last))
            --last;
        if (first >= last)
            return first;
        _STL::swap(*(_STL::_Deque_iterator<void *, _STL::_Nonconst_traits<void *> > *)first,
            *(_STL::_Deque_iterator<void *, _STL::_Nonconst_traits<void *> > *)last);
        ++first;
    }
}

Rva005B2FDCItem *Rva005B282EMedian(Rva005B2FDCItem *a, Rva005B2FDCItem *b, Rva005B2FDCItem *c, Rva005B26CECmp comp)
{
    if (comp(a, b)) {
        if (comp(b, c))
            return b;
        else if (comp(a, c))
            return c;
        else
            return a;
    } else {
        if (comp(a, c))
            return a;
        else if (comp(b, c))
            return c;
        else
            return b;
    }
}
