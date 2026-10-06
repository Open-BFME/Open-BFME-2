// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ??$_M_allocate_and_copy@PAVRva0036CA00Str@@@?$vector@VRva0036CA00Str@@V?$allocator@VRva0036CA00Str@@@_STL@@@_STL@@IAEPAVRva0036CA00Str@@IPAV2@0@Z @0x00239408 45B
// vector<Rva0036CA00Str>::_M_allocate_and_copy via rowed __uninitialized_copy 0x002393BC and allocator twin 0x00068E15. Caller 0x00239F0A.
class Rva0036CA00Str {
public:
    unsigned char m_data[4];
};
namespace _STL {
struct __false_type { __false_type() {} };
template <class T> class allocator {
public:
    T *allocate(unsigned int n, const void *hint) const;
};
template <class T, class Alloc> class vector {
public:
    typedef T *pointer;
    typedef const T *const_pointer;
    typedef unsigned int size_type;
protected:
    template <class ForwardIter>
    pointer _M_allocate_and_copy(size_type n, ForwardIter first, ForwardIter last);
private:
    pointer m_start;
    pointer m_finish;
    struct Proxy { allocator<T> m_alloc; pointer m_data; };
    Proxy m_endOfStorage;
};
template <class InputIter, class OutputIter>
OutputIter __uninitialized_copy(InputIter first, InputIter last, OutputIter result, const __false_type &tag);
}
template <class Type, class Allocator>
template <class ForwardIter>
Type *_STL::vector<Type, Allocator>::_M_allocate_and_copy(size_type n, ForwardIter first, ForwardIter last)
{
    Type *result = m_endOfStorage.m_alloc.allocate(n, 0);
    __uninitialized_copy(first, last, result, __false_type());
    return result;
}
template Rva0036CA00Str *_STL::vector<Rva0036CA00Str, _STL::allocator<Rva0036CA00Str> >::_M_allocate_and_copy<Rva0036CA00Str *>(unsigned int, Rva0036CA00Str *, Rva0036CA00Str *);
