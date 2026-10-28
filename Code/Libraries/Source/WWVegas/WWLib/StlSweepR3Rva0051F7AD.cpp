// STLport 4.5.3 vector assignment shape (_vector.c:90).
// Element identity remains opaque; target calls prove the provider bindings below.
// cl: /I. /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// Retail 0x0051F7AD uses three pointers at +0/+4/+8 and a 12-byte stride.
// Its callees are the rowed allocation at 0x004EE233, clear at 0x004EE540,
// copy forwarding at 0x0051EC31, destruction at 0x0052C37A and uninitialized
// copy at 0x004EE1E2. Their existing names are retained without asserting that
// the opaque element is ProductionPrerequisite::PrereqUnitRec. A local vector
// view avoids emitting a second, non-retail family of helpers over that element
// (StlSweepR3Rva003F318C.cpp uses the same bounded specialization pattern).
struct Rva0051F7ADRecord { char bytes[12]; };
class ProductionPrerequisite
{
public:
	struct PrereqUnitRec;
};
struct Rva0052BFB5Elem;
struct Rva0051EC31Input;
struct Rva0051EC31Output;
struct Rva0051EC31IteratorTag;

namespace _STL {
struct __false_type { __false_type() {} };
template <class T> class allocator {};
template <class T, class A> class vector
{
public:
    typedef T *pointer;
    typedef unsigned int size_type;
    size_type size() const { return size_type(_M_finish - _M_start); }
    size_type capacity() const { return size_type(_M_end_of_storage - _M_start); }
    vector &operator=(const vector &x);
protected:
    template <class I> T *_M_allocate_and_copy(size_type n, I first, I last);
    T *_M_start;
    T *_M_finish;
    T *_M_end_of_storage;
};
template <class I, class O> O __uninitialized_copy(I, I, O, const __false_type &);
}

class Rva004EE540 { public: void rva004EE540(); };
Rva0051EC31Output *Rva0051EC31RangeForward(Rva0051EC31Input *, Rva0051EC31Input *, Rva0051EC31Output *, const Rva0051EC31IteratorTag &);
void Rva0052C37ADestroyRange(Rva0052BFB5Elem *, Rva0052BFB5Elem *);

// Access the protected member under the allocation owner's existing spelling.
struct Rva0051F7ADAllocate : _STL::vector<ProductionPrerequisite::PrereqUnitRec, _STL::allocator<ProductionPrerequisite::PrereqUnitRec> >
{
    ProductionPrerequisite::PrereqUnitRec *call(unsigned int n, ProductionPrerequisite::PrereqUnitRec *first, ProductionPrerequisite::PrereqUnitRec *last)
    {
        return _M_allocate_and_copy(n, first, last);
    }
};

namespace _STL {
template <>
vector<Rva0051F7ADRecord, allocator<Rva0051F7ADRecord> > &
vector<Rva0051F7ADRecord, allocator<Rva0051F7ADRecord> >::operator=(const vector<Rva0051F7ADRecord, allocator<Rva0051F7ADRecord> > &__x)
{
    if (&__x != this) {
        const size_type __xlen = __x.size();
        if (__xlen > capacity()) {
            pointer __tmp = (pointer)((Rva0051F7ADAllocate *)this)->call(__xlen,
                (ProductionPrerequisite::PrereqUnitRec *)__x._M_start, (ProductionPrerequisite::PrereqUnitRec *)__x._M_finish);
            ((Rva004EE540 *)this)->rva004EE540();
            _M_start = __tmp;
            _M_end_of_storage = _M_start + __xlen;
        }
        else if (size() >= __xlen) {
            pointer __i = (pointer)Rva0051EC31RangeForward((Rva0051EC31Input *)__x._M_start,
                (Rva0051EC31Input *)__x._M_finish, (Rva0051EC31Output *)_M_start,
                (const Rva0051EC31IteratorTag &)__false_type());
            Rva0052C37ADestroyRange((Rva0052BFB5Elem *)__i, (Rva0052BFB5Elem *)_M_finish);
        }
        else {
            Rva0051EC31RangeForward((Rva0051EC31Input *)__x._M_start,
                (Rva0051EC31Input *)(__x._M_start + size()), (Rva0051EC31Output *)_M_start,
                (const Rva0051EC31IteratorTag &)__false_type());
            __uninitialized_copy((ProductionPrerequisite::PrereqUnitRec *)(__x._M_start + size()),
                (ProductionPrerequisite::PrereqUnitRec *)__x._M_finish, (ProductionPrerequisite::PrereqUnitRec *)_M_finish, __false_type());
        }
        _M_finish = _M_start + __xlen;
    }
    return *this;
}
}
