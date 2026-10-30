// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G7 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
/*
 *
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Copyright (c) 1996,1997
 * Silicon Graphics Computer Systems, Inc.
 *
 * Copyright (c) 1997
 * Moscow Center for SPARC Technology
 *
 * Copyright (c) 1999
 * Boris Fomitchev
 *
 * This material is provided "as is", with absolutely no warranty expressed
 * or implied. Any use is at your own risk.
 *
 * Permission to use or copy this software for any purpose is hereby granted
 * without fee, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 * Modified here to bind the retail count-insert calls to existing ABI views.
 *
 */
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>

struct Rva001524F9Element { Rva001524F9Element();Rva001524F9Element(const Rva001524F9Element&);~Rva001524F9Element();Rva001524F9Element&operator=(const Rva001524F9Element&);char bytes[36]; bool operator<(const Rva001524F9Element&)const; bool operator==(const Rva001524F9Element&)const; };

// Native calls identify two existing ABI views of this 36-byte record:
// copy/destroy/uninitialized helpers use Rva0007BB16Record; assignment
// helpers use BfmeAssignRecord36. Keep those providers at the call boundary
// rather than emitting another lifetime or overflow implementation.
struct Rva0007BB16Record {
    Rva0007BB16Record(const Rva0007BB16Record &);
    ~Rva0007BB16Record();
    char bytes[36];
};
struct BfmeAssignRecord36 {
    BfmeAssignRecord36 &operator=(const BfmeAssignRecord36 &);
    char bytes[36];
};
namespace _STL {
template <> Rva0007BB16Record *_STLP_alloc_proxy<Rva0007BB16Record *, Rva0007BB16Record, allocator<Rva0007BB16Record> >::allocate(size_t);
template <> void _STLP_alloc_proxy<Rva0007BB16Record *, Rva0007BB16Record, allocator<Rva0007BB16Record> >::deallocate(Rva0007BB16Record *, size_t);
template <> void __destroy_aux(Rva0007BB16Record *, Rva0007BB16Record *, const __false_type &);
template <> void __destroy<Rva0007BB16Record *, Rva0007BB16Record>(Rva0007BB16Record *, Rva0007BB16Record *, Rva0007BB16Record *);
template <> Rva0007BB16Record *uninitialized_fill_n<Rva0007BB16Record *, unsigned int, Rva0007BB16Record>(Rva0007BB16Record *, unsigned int, const Rva0007BB16Record &);
template <> void fill<BfmeAssignRecord36 *, BfmeAssignRecord36>(BfmeAssignRecord36 *, BfmeAssignRecord36 *, const BfmeAssignRecord36 &);
}
// Access-only ABI view; no new native class identity is asserted.
struct NativeRecordOverflowView : _STL::vector<Rva0007BB16Record> {
    using _STL::vector<Rva0007BB16Record>::_M_insert_overflow;
};

// STLport 4.5.3 count-insertion semantics, with the native providers above.
// Keep the tagged helper definitions visible: declaration-only specializations
// make cl initialize their empty tag temporaries and change the retail frame.
namespace _STL {
template <> void vector<Rva001524F9Element>::_M_fill_insert(
    iterator __position, size_type __n, const Rva001524F9Element &__x)
{
    if (__n != 0) {
        if (size_type(this->_M_end_of_storage._M_data - this->_M_finish) >= __n) {
            Rva0007BB16Record __x_copy = reinterpret_cast<const Rva0007BB16Record &>(__x);
            const size_type __elems_after = this->_M_finish - __position;
            pointer __old_finish = this->_M_finish;
            if (__elems_after > __n) {
                __uninitialized_copy(reinterpret_cast<Rva0007BB16Record *>(this->_M_finish - __n),
                    reinterpret_cast<Rva0007BB16Record *>(this->_M_finish),
                    reinterpret_cast<Rva0007BB16Record *>(this->_M_finish), _IsPODType());
                this->_M_finish += __n;
                __copy_backward_ptrs(reinterpret_cast<BfmeAssignRecord36 *>(__position),
                    reinterpret_cast<BfmeAssignRecord36 *>(__old_finish - __n),
                    reinterpret_cast<BfmeAssignRecord36 *>(__old_finish), _TrivialAss());
                _STLP_STD::fill(reinterpret_cast<BfmeAssignRecord36 *>(__position),
                    reinterpret_cast<BfmeAssignRecord36 *>(__position + __n),
                    reinterpret_cast<const BfmeAssignRecord36 &>(__x_copy));
            }
            else {
                uninitialized_fill_n(reinterpret_cast<Rva0007BB16Record *>(this->_M_finish), __n - __elems_after, __x_copy);
                this->_M_finish += __n - __elems_after;
                __uninitialized_copy(reinterpret_cast<Rva0007BB16Record *>(__position),
                    reinterpret_cast<Rva0007BB16Record *>(__old_finish),
                    reinterpret_cast<Rva0007BB16Record *>(this->_M_finish), _IsPODType());
                this->_M_finish += __elems_after;
                _STLP_STD::fill(reinterpret_cast<BfmeAssignRecord36 *>(__position),
                    reinterpret_cast<BfmeAssignRecord36 *>(__old_finish),
                    reinterpret_cast<const BfmeAssignRecord36 &>(__x_copy));
            }
        }
        else {
            reinterpret_cast<NativeRecordOverflowView *>(this)->_M_insert_overflow(
                reinterpret_cast<Rva0007BB16Record *>(__position),
                reinterpret_cast<const Rva0007BB16Record &>(__x), _IsPODType(), __n, false);
        }
    }
}
}

// Independent native entry 0x00152659..0x0015265E forwards the unchanged
// receiver and three arguments to the verified fill-insert at 0x001524F9.
// The destination establishes the vector/argument view; the original
// wrapper name and application element identity remain unknown.
class Rva00152659 : public _STL::vector<Rva001524F9Element, _STL::allocator<Rva001524F9Element> >
{
public:
	void insert(Rva001524F9Element *position, unsigned int count, const Rva001524F9Element &value);
};

void Rva00152659::insert(Rva001524F9Element *position, unsigned int count, const Rva001524F9Element &value)
{
	_M_fill_insert(position, count, value);
}
