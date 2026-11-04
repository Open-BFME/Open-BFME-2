// STLport 4.5.3 vector assignment shape (_vector.c:90).
// Element identity remains opaque; target calls prove the provider bindings below.
// cl: /I. /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>
//
// Retail 0x0051F7AD uses three pointers at +0/+4/+8 and a 12-byte stride.
// Its callees are the rowed allocation at 0x004EE233, clear at 0x004EE540,
// copy forwarding at 0x0051EC31, destruction at 0x0052C37A and uninitialized
// copy at 0x004EE1E2. Their existing names are retained without asserting that
// the opaque element is ProductionPrerequisite::PrereqUnitRec. Only that
// external allocation specialization has a bounded local view; the assignment
// itself uses STLport's vector definition.
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
// Only the external allocation member's existing ABI is known for this
// spelling. Declaring its member specialization on the complete vector ICEs
// cl 7.1 (C1001, P2 main.c:148). Keep this view bounded; the assignment's
// vector<Rva0051F7ADRecord> uses STLport's complete definition above.
template <> class vector<ProductionPrerequisite::PrereqUnitRec, allocator<ProductionPrerequisite::PrereqUnitRec> >
{
protected:
    template <class I> ProductionPrerequisite::PrereqUnitRec *_M_allocate_and_copy(unsigned int, I, I);
};
template <> ProductionPrerequisite::PrereqUnitRec *
__uninitialized_copy<ProductionPrerequisite::PrereqUnitRec *, ProductionPrerequisite::PrereqUnitRec *>(ProductionPrerequisite::PrereqUnitRec *, ProductionPrerequisite::PrereqUnitRec *, ProductionPrerequisite::PrereqUnitRec *, const __false_type &) throw();
}

// A user-provided constructor avoids zero-filling the opaque tag temporary.
struct Rva0051F7ADCopyTag : _STL::__false_type { Rva0051F7ADCopyTag() {} };

class Rva004EE540 { public: void rva004EE540(); };
Rva0051EC31Output *Rva0051EC31RangeForward(Rva0051EC31Input *, Rva0051EC31Input *, Rva0051EC31Output *, const Rva0051EC31IteratorTag &);
void Rva0052C37ADestroyRange(Rva0052BFB5Elem *, Rva0052BFB5Elem *);

// Access the protected member under the allocation owner's existing spelling.
struct Rva0051F7ADAllocate : _STL::vector<ProductionPrerequisite::PrereqUnitRec, _STL::allocator<ProductionPrerequisite::PrereqUnitRec> >
{
    using _STL::vector<ProductionPrerequisite::PrereqUnitRec, _STL::allocator<ProductionPrerequisite::PrereqUnitRec> >::_M_allocate_and_copy;
};

namespace _STL {
template <>
vector<Rva0051F7ADRecord, allocator<Rva0051F7ADRecord> > &
vector<Rva0051F7ADRecord, allocator<Rva0051F7ADRecord> >::operator=(const vector<Rva0051F7ADRecord, allocator<Rva0051F7ADRecord> > &__x)
{
    if (&__x != this) {
        const size_type __xlen = __x.size();
        if (__xlen > capacity()) {
            pointer __tmp = (pointer)((Rva0051F7ADAllocate *)this)->_M_allocate_and_copy<ProductionPrerequisite::PrereqUnitRec *>(__xlen,
                (ProductionPrerequisite::PrereqUnitRec *)__x._M_start, (ProductionPrerequisite::PrereqUnitRec *)__x._M_finish);
            ((Rva004EE540 *)this)->rva004EE540();
            _M_start = __tmp;
            _M_end_of_storage._M_data = _M_start + __xlen;
        }
        else if (size() >= __xlen) {
            pointer __i = (pointer)Rva0051EC31RangeForward((Rva0051EC31Input *)__x._M_start,
                (Rva0051EC31Input *)__x._M_finish, (Rva0051EC31Output *)_M_start,
                (const Rva0051EC31IteratorTag &)Rva0051F7ADCopyTag());
            Rva0052C37ADestroyRange((Rva0052BFB5Elem *)__i, (Rva0052BFB5Elem *)_M_finish);
        }
        else {
            Rva0051EC31RangeForward((Rva0051EC31Input *)__x._M_start,
                (Rva0051EC31Input *)(__x._M_start + size()), (Rva0051EC31Output *)_M_start,
                (const Rva0051EC31IteratorTag &)Rva0051F7ADCopyTag());
            __uninitialized_copy((ProductionPrerequisite::PrereqUnitRec *)(__x._M_start + size()),
                (ProductionPrerequisite::PrereqUnitRec *)__x._M_finish, (ProductionPrerequisite::PrereqUnitRec *)_M_finish, Rva0051F7ADCopyTag());
        }
        _M_finish = _M_start + __xlen;
    }
    return *this;
}
}
