// cl: /Od /Ob1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport46
//
// STLport vector<void *>, the allocating half, built with the 4.6 headers.
// The non-allocating bodies live in stlport_vector_voidptr.cpp; this unit
// uses the game allocator shim rather than the stock allocator.
//
// Retail never reaches __sgi_alloc. _M_allocate_and_copy allocates with
//
//   push 0 / mov eax,[ebp+8] / shl eax,2 / push eax / call 0x000307F0
//
// which is (bytes, hint) __cdecl into the single raw byte allocator that
// symbols.csv already pins - it forwards to the game allocator table at
// 0x00DE0404 with memory class 3. There is no 128-byte small/large split and
// no free-list, which is what the stock header would have produced. _M_clear
// frees through a plain one-argument call to _free at 0x00030830 rather than
// __sgi_alloc::deallocate, so the size argument is computed and discarded.
//
// reference/shims/bfmealloc/stl/_alloc.h is a copy of the vendored header
// with exactly that substitution, and it is opt-in: only a unit that puts the
// shim on its include path sees it.

// Retail does not inline STLport's placement new. push_back at 0x00029140
// reaches _Construct as `push <ptr> / push 4 / call ??2@YAPAXIPAX@Z`, and that
// operator is already in the ledger at 0x00006EE0 as a two-instruction body.
// MSVC's <new> guards its inline definition with __PLACEMENT_NEW_INLINE, so
// defining that macro first suppresses the definition and leaves our
// declaration, which MSVC then has to call.
#define __PLACEMENT_NEW_INLINE
void *__cdecl operator new(unsigned int size, void *place);

#include <vector>

// The native range-erase owner is the 34-byte optimized specialization
// in stlport_vector_voidptr_opt.cpp, not this unit's /Od instantiation.
// Keep its declaration so explicit class instantiation cannot emit a
// competing 84-byte definition. Call sites retain the same symbol and ABI.
template <> void **_STL::vector<void *>::erase(void **first, void **last);
// The 33-byte count-insert wrapper at 0x0002A2D0 is already owned by
// stlport_vector_voidptr.cpp. Do not emit another copy with this unit's
// allocating-template frame bookkeeping.
template <> void _STL::vector<void *>::insert(void **position, size_t n, void *const &value);

// Native _M_fill_assign calls the distinct 78-byte erase at 0x00027400,
// already owned by vector<unsigned int>. Both views use 12-byte vector
// headers and trivially copied four-byte elements; only this proven range
// ABI is projected here. Preserve that callee rather than substituting the
// optimized void-pointer erase at 0x0031BD55.
template <> unsigned int *_STL::vector<unsigned int>::erase(unsigned int *first, unsigned int *last);
// stlport_hash_map_int.cpp owns the retail allocator constructor and _M_set
// (expanded inline here, as retail's /Od bodies do, without an emitted copy),
// stlport_vector_voidptr_opt.cpp the single-element erase. Declare the rest
// of the members this /Od unit does not own so the explicit class
// instantiation below does not emit competing copies of them.
// bfme link decl-only begin
namespace _STL { template <> vector<void *, allocator<void *> >::vector(allocator<void *> const &); }
namespace _STL { template <> __declspec(dllimport) __forceinline void vector<void *, allocator<void *> >::_M_set(void **s, void **f, void **e) { this->_M_start = s; this->_M_finish = f; this->_M_end_of_storage._M_data = e; } }
namespace _STL { template <> void **vector<void *, allocator<void *> >::erase(void **); }
namespace _STL { template <> void *const &vector<void *, allocator<void *> >::operator[](unsigned int) const; }
namespace _STL { template <> void vector<void *, allocator<void *> >::resize(unsigned int, void *); }
namespace _STL { template <> void vector<void *, allocator<void *> >::resize(unsigned int); }
namespace _STL { template <> void *const &vector<void *, allocator<void *> >::at(unsigned int) const; }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_set(void **, void **, void **); }
namespace _STL { template <> void ** vector<void *, allocator<void *> >::erase(void **); }
// bfme link decl-only end

namespace _STL
{
// Native 0x000291D0..0x00029328 proves this 344-byte insertion body.
// Its placement-new/copy-backward/overflow calls and the default-value
// wrapper at 0x00029350 establish the STLport four-byte pointer algorithm.
// Preserve the extra discarded inline word immediately before the copy
// expression: retail's frame is 0x74, not the primary template's 0x70.
// This word is compiler bookkeeping, not an identified game variable.
static __forceinline void retainInsertCompilerTemporary() {
    void *discarded;
}
template <> inline vector<void *>::iterator
vector<void *>::insert(iterator position, void *const &value) {
    size_type index = position - begin();
    if (this->_M_finish != this->_M_end_of_storage._M_data) {
        if (position == end()) {
            _Construct(this->_M_finish, value);
            ++this->_M_finish;
        } else {
            _Construct(this->_M_finish, *(this->_M_finish - 1));
            ++this->_M_finish;
            void *copy = value;
            retainInsertCompilerTemporary();
            __copy_backward_ptrs(position, this->_M_finish - 2, this->_M_finish - 1, _TrivialAss());
            *position = copy;
        }
    } else {
        _M_insert_overflow(position, value, _IsPODType(), 1UL);
    }
    return begin() + index;
}

template <> inline vector<void *, allocator<void *> >::iterator
vector<void *, allocator<void *> >::insert(iterator position)
{
    // The specialized callee now supplies the retained inline frame word.
    value_type value = value_type();
    return insert(position, value);
}
}


namespace _STL {
// VC7.1 /Od retains five discarded words from the visible inline erase
// body in _M_fill_assign's 0x9C frame. The external declaration removes
// that bookkeeping. This empty inline scope preserves those words at
// their original lifetime position; it emits no runtime instructions.
// These are compiler frame slots, not claimed game variables.
static __forceinline void retainEraseCompilerTemporaries() {
    void *first; void *last; void *result; void *begin; void *end;
}
template <> inline void vector<void *>::_M_fill_assign(size_t n, void *const &value) {
    if (n > capacity()) {
        vector<void *> temporary(n, value, get_allocator());
        temporary.swap(*this);
    } else if (n > size()) {
        fill(begin(), end(), value);
        this->_M_finish = _STL::uninitialized_fill_n(this->_M_finish, n-size(), value);
    } else {
        reinterpret_cast<vector<unsigned int> *>(this)->erase(
            reinterpret_cast<unsigned int *>(_STL::fill_n(begin(), n, value)),
            reinterpret_cast<unsigned int *>(end()));
        retainEraseCompilerTemporaries();
    }
}
}

// Suppress this unit's non-retail clear copy (row 57 family2-LK3) so the link
// keeps the retail copy another unit provides.
namespace _STL {
template <> void _STL::vector<void *>::clear();
}

namespace _STL {
// Native 0x00029CA0..0x00029EAD is the complete 525-byte
// STLport pointer-vector fill insertion, ending in RET12. Preserve the
// discarded inline word between copy-backward and fill: retail's frame
// is 0x80, with the later fill/copy homes four bytes below the primary
// template's 0x7C frame. This is compiler bookkeeping, with no claim
// about an original game variable. The algorithm below follows the
// committed BFME1 9e3be919b10ae956e3c8a13995e0d62f2be1d016
// inputs/vendor/stlport/stl/_vector.c, STLport 4.5.3.
static __forceinline void retainFillCompilerTemporary() { void *discarded; }
template <> inline void vector<void *>::_M_fill_insert(iterator __position, size_type __n, void *const &__x) {
  if (__n != 0) {
    if (size_type(this->_M_end_of_storage._M_data - this->_M_finish) >= __n) {
      void *__x_copy = __x;
      const size_type __elems_after = this->_M_finish - __position;
      pointer __old_finish = this->_M_finish;
      if (__elems_after > __n) {
        __uninitialized_copy(this->_M_finish - __n, this->_M_finish, this->_M_finish, _IsPODType());
        this->_M_finish += __n;
        __copy_backward_ptrs(__position, __old_finish - __n, __old_finish, _TrivialAss());
        retainFillCompilerTemporary();
        _STL::fill(__position, __position + __n, __x_copy);
      }
      else {
        uninitialized_fill_n(this->_M_finish, __n - __elems_after, __x_copy);
        this->_M_finish += __n - __elems_after;
        __uninitialized_copy(__position, __old_finish, this->_M_finish, _IsPODType());
        this->_M_finish += __elems_after;
        _STL::fill(__position, __old_finish, __x_copy);
      }
    }
    else 
      _M_insert_overflow(__position, __x, _IsPODType(), __n);
  }
}
}

// Native 0x00027BA0 (407 B): vector<void *>::operator=, STLport 4.5.3's
// 4.5.x form (see vendor _vector.c): grow with allocate_and_copy and clear,
// else copy over the front and destroy the tail, else copy the head and
// uninitialized_copy the rest; every path ends in finish = start + xlen.
namespace _STL {
static __forceinline void *copyPointers(const void *first, const void *last, void *result, const __true_type &)
{
    return __copy_trivial(first, last, result);
}
template <> vector<void *> &vector<void *>::operator=(const vector<void *> &x)
{
    if (&x != this) {
        const size_type xlen = x.size();
        if (xlen > capacity()) {
            pointer tmp = _M_allocate_and_copy(xlen, (const_pointer)x._M_start + 0, (const_pointer)x._M_finish + 0);
            _M_clear();
            this->_M_start = tmp;
            this->_M_end_of_storage._M_data = this->_M_start + xlen;
        } else if (size() >= xlen) {
            pointer i = (pointer)copyPointers((const_pointer)x._M_start + 0, (const_pointer)x._M_finish + 0, (pointer)this->_M_start, _TrivialAss());
            _Destroy(i, this->_M_finish);
        } else {
            copyPointers((const_pointer)x._M_start, (const_pointer)x._M_start + size(), (pointer)this->_M_start, _TrivialAss());
            __uninitialized_copy((const_pointer)x._M_start + size(), (const_pointer)x._M_finish + 0, this->_M_finish, _IsPODType());
        }
        this->_M_finish = this->_M_start + xlen;
    }
    return *this;
}
}

template class _STL::vector<void *, _STL::allocator<void *> >;
// _Vector_base's dtor (0x000251F0) is only an EH cleanup callee in vector's
// bodies, and with __copy_trivial nothrow none of them needs it here.
template class _STL::_Vector_base<void *, _STL::allocator<void *> >;

// _String_base<char>::_M_throw_out_of_range is the same empty /Od method body
// (0x00023A40) under _STLP_NO_EXCEPTIONS. The narrow-string units call it out
// of line and nothing else defines it, so this unit's flags supply it.
// The narrow-string units' own _String_base view; <string> is not included,
// so the funclet labels of the instantiations above keep their numbers.
namespace _STL {
template <class _Tp, class _Alloc> class _String_base
{
public:
	void _M_throw_out_of_range() const;
};
template <> void _String_base<char, allocator<char> >::_M_throw_out_of_range() const
{
}
}
