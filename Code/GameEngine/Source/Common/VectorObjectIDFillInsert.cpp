// cl: /DNDEBUG /MD /EHsc
// stlport

// De-lift: STLport vector<ObjectID>::_M_fill_insert, retail 0x002CCBD0,
// 251 bytes.  ObjectID is an enum, so this instantiates separately from the
// shared four-byte-POD siblings (vector<int>, vector<Object *>, vector<void *>).
#define _STLP_NO_EXCEPTIONS 1
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#include <vector>

enum ObjectID { INVALID_ID = 0 };
// Bind the allocator, base teardown and clear to the kept retail copies (InGameUIXfer.cpp emits them).
namespace _STL { template <> void allocator<ObjectID>::deallocate(ObjectID *, size_t) const; }
namespace _STL { template <> _Vector_base<ObjectID, allocator<ObjectID> >::~_Vector_base(); }
namespace _STL { template <> ObjectID *allocator<ObjectID>::allocate(size_t, const void *) const; }
namespace _STL { template <> void vector<ObjectID>::_M_clear(); }
// The growth path: retail's copy (InGameUIXfer.cpp emits it) expands the old
// storage's release inline as a direct free instead of calling _M_clear, which
// this unit binds out of line; spell the STLport 4.5.3 algorithm out so this
// TU's copy is retail's body rather than a second variant.
extern "C" void __cdecl free(void *);
namespace _STL {
template <> void vector<ObjectID>::_M_insert_overflow(ObjectID *position, const ObjectID &value,
    const __false_type &, size_t fillLength, bool atEnd)
{
    const size_type oldSize = size();
    const size_type length = oldSize + (max)(oldSize, fillLength);
    pointer start = this->_M_end_of_storage.allocate(length);
    pointer finish = __uninitialized_copy(this->_M_start, position, start, __false_type());
    if (fillLength == 1) {
        _Construct(finish, value);
        ++finish;
    } else
        finish = __uninitialized_fill_n(finish, fillLength, value, __false_type());
    if (!atEnd)
        finish = __uninitialized_copy(position, this->_M_finish, finish, __false_type());
    if (this->_M_start != 0)
        free(this->_M_start);
    _M_set(start, finish, start + length);
}
}

// The rowed members, plus the copy constructor Player.cpp and Rva00500659ClosestArmies.cpp bind to.
template void _STL::vector<ObjectID>::_M_fill_insert(ObjectID *, size_t, const ObjectID &);
template void _STL::vector<ObjectID>::insert(ObjectID *, size_t, const ObjectID &);
template ObjectID *_STL::vector<ObjectID>::insert(ObjectID *, const ObjectID &);
template ObjectID *_STL::vector<ObjectID>::erase(ObjectID *);
template _STL::vector<ObjectID>::vector(size_t, const ObjectID &, const _STL::allocator<ObjectID> &);
template _STL::vector<ObjectID>::vector(const _STL::vector<ObjectID> &);

// ??$copy_backward@PAW4ObjectID@@PAW41@@_STL@@YAPAW4ObjectID@@PAW41@00@Z RVA 0x005E42D3 size 27
// Evidence: callee __copy_backward_ptrs ObjectID rowed at 0x00583709; callers __linear_insert-like at 0x0040AE5E and 0x005E4862; explicit instantiation exact mod reloc.
template ObjectID* _STL::copy_backward<ObjectID*, ObjectID*>(ObjectID*, ObjectID*, ObjectID*);
