// cl: /EHsc /Ireference/shims/bfme2_ascii
// stlport
// ??4?$vector@UBfmeRecord0040B61A@@...@QAEAAV01@ABV01@@Z, retail 0x0040B61A, 186 bytes.
// Evidence: same bytes as vector<GeometryRecord>::operator= except two calls:
// the destroy reads the rowed Rva0040B52EDestroy at 0x0040B52E, which frees a
// narrow string at +0 of a 16-byte element, and the uninitialized copy reads
// 0x0040B2FD. Its other calls read the neighbouring 0x0040B323, 0x0040B350
// and the rowed destroy-and-free 0x0040B5DE. The element name is generated;
// the string at +0 and the 16-byte stride come from those bodies. The
// AsciiString member and the int fields are placeholders: the string's exact
// type and the remaining fields are not established. The flags follow
// GeometryRecordVector.cpp; /MD with the STLport static-lib defines adds a
// distance argument retail does not pass.
// Preserve the visible STL loops and call the existing native placement-copy
// provider for this same record view. The application identity remains unknown.

#include <vector>

#include "ascii_string.h"
class Rva0040AEE3;
void Rva0040B14EConstruct(Rva0040AEE3 *, const Rva0040AEE3 &);
namespace _STL {
// ?_STL::_Construct absent-from-retail
static __forceinline void _Construct(Rva0040AEE3 *destination,
                                    const Rva0040AEE3 &source)
{
    Rva0040B14EConstruct(destination, source);
}
}
// Suppress this TU's non-retail copy of ?_M_clear@?$vector@UBfmeRecord0040B61A@@V?$allocator@UBfmeRecord0040B61A@@@_STL@@@_STL@@IA:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmeRecord0040B61A;
namespace _STL { template <> void vector<BfmeRecord0040B61A,allocator<BfmeRecord0040B61A> >::_M_clear(); }
// Suppress this TU's non-retail copy of ?allocate@?$_STLP_alloc_proxy@PAUBfmeRecord0040B61A@@U1@V?$allocator@UBfmeRecord0040B61A@@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmeRecord0040B61A;
namespace _STL { template <> BfmeRecord0040B61A * _STLP_alloc_proxy<BfmeRecord0040B61A *,BfmeRecord0040B61A,allocator<BfmeRecord0040B61A> >::allocate(unsigned int); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@UBfmeRecord0040B61A@@@_STL@@QBEXPAUBfmeRecord0040B61A@@I@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmeRecord0040B61A;
namespace _STL { template <> void allocator<BfmeRecord0040B61A>::deallocate(BfmeRecord0040B61A *,unsigned int) const; }
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}

struct BfmeRecord0040B61A
{
	AsciiString m_str;
	int m_04;
	int m_08;
	int m_0C;
};

// The retail tail calls the existing 16-byte copy worker at 0x0040B2FD.
// Its row retains the opaque Rva0040AEE3 spelling; do not emit a second
// template copy using this unit's provisional element view.
class Rva0040AEE3 { char data[16]; public: Rva0040AEE3(const Rva0040AEE3 &); };
struct DestroyElem0040B52E;
void Rva0040B52EDestroy(DestroyElem0040B52E *, DestroyElem0040B52E *);
namespace _STL {

template <> BfmeRecord0040B61A *__uninitialized_copy<const BfmeRecord0040B61A *, BfmeRecord0040B61A *>(
    const BfmeRecord0040B61A *, const BfmeRecord0040B61A *, BfmeRecord0040B61A *, const __false_type &);
template <> inline Rva0040AEE3 *__uninitialized_copy<Rva0040AEE3 *, Rva0040AEE3 *>(
    Rva0040AEE3 *first, Rva0040AEE3 *last, Rva0040AEE3 *result, const __false_type &)
{
    Rva0040AEE3 *cur = result;
    for (; first != last; ++first, ++cur)
        _Construct(cur, *first);
    return cur;
}
template <>
vector<BfmeRecord0040B61A, allocator<BfmeRecord0040B61A> > &
vector<BfmeRecord0040B61A, allocator<BfmeRecord0040B61A> >::operator=(
    const vector<BfmeRecord0040B61A, allocator<BfmeRecord0040B61A> > &__x)
{
    if (&__x != this) {
        const size_type __xlen = __x.size();
        if (__xlen > capacity()) {
            pointer __tmp = _M_allocate_and_copy(__xlen, (const_pointer)__x._M_start+0,
                (const_pointer)__x._M_finish+0);
            _M_clear();
            _M_start = __tmp;
            _M_end_of_storage._M_data = _M_start + __xlen;
        } else if (size() >= __xlen) {
            pointer __i = __copy_ptrs((const_pointer)__x._M_start+0,
                (const_pointer)__x._M_finish+0, (pointer)_M_start, _TrivialAss());
            Rva0040B52EDestroy((DestroyElem0040B52E *)__i,
                (DestroyElem0040B52E *)_M_finish);
        } else {
            __copy_ptrs((const_pointer)__x._M_start,
                (const_pointer)__x._M_start + size(), (pointer)_M_start, _TrivialAss());
            __uninitialized_copy((Rva0040AEE3 *)(__x._M_start + size()),
                (Rva0040AEE3 *)__x._M_finish, (Rva0040AEE3 *)_M_finish, _IsPODType());
        }
        _M_finish = _M_start + __xlen;
    }
    return *this;
}
}
