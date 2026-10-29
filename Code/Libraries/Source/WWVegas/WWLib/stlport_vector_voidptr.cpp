// cl: /Od /Ob1 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport46
//
// STLport 4.5.3 vector<void *>. The reloc sweep names _M_fill_insert and
// reserve out of this instantiation from byte-true call sites, so the
// instantiation is known to exist in the image; this is the same vendored
// route the int and pair vectors here already use.

#include <vector>
// bfme link decl-only begin
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::~_Vector_base(); }
namespace _STL { template <> vector<void *, allocator<void *> >::~vector(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_clear(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_insert_overflow(void **, void *const &, __true_type const &, unsigned int, bool); }
namespace _STL { template <> void vector<void *, allocator<void *> >::reserve(unsigned int); }
namespace _STL { template <> vector<void *, allocator<void *> >::vector(vector<void *, allocator<void *> > const &); }
namespace _STL { template <> vector<void *, allocator<void *> >::vector(unsigned int); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_insert_overflow(void **, void *const &, __false_type const &, unsigned int, bool); }
namespace _STL { template <> void ** vector<void *, allocator<void *> >::insert(void **); }
namespace _STL { template <> void vector<void *, allocator<void *> >::push_back(void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::push_back(); }
namespace _STL { template <> vector<void *, allocator<void *> >::vector(unsigned int, void *const &, allocator<void *> const &); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::_Vector_base(unsigned int, allocator<void *> const &); }
namespace _STL { template <> vector<void *, allocator<void *> > &vector<void *, allocator<void *> >::operator=(vector<void *, allocator<void *> > const &); }
namespace _STL { template <> vector<void *, allocator<void *> >::vector(allocator<void *> const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_set(void **, void **, void **); }
namespace _STL { template <> void **vector<void *, allocator<void *> >::erase(void **); }
namespace _STL { template <> void *const &vector<void *, allocator<void *> >::operator[](unsigned int) const; }
namespace _STL { template <> void vector<void *, allocator<void *> >::resize(unsigned int, void *); }
namespace _STL { template <> void vector<void *, allocator<void *> >::resize(unsigned int); }
// bfme link decl-only end
// ~_STLP_alloc_proxy is rowed here (retail 1-instruction body); the declared-only constructors above no longer emit it, so anchor it.
template _STL::_STLP_alloc_proxy<void **, void *, _STL::allocator<void *> >::~_STLP_alloc_proxy();

// The native range-erase owner is the 34-byte optimized specialization
// in stlport_vector_voidptr_opt.cpp, not this unit's /Od instantiation.
// Keep its declaration so explicit class instantiation cannot emit a
// competing 84-byte definition. Call sites retain the same symbol and ABI.
template <> void **_STL::vector<void *>::erase(void **first, void **last);
// The allocating unit owns the verified fill-assign specialization.
template <> void _STL::vector<void *>::_M_fill_assign(size_t n, void *const &value);
// The allocating unit owns native 0x00029CA0's 525-byte fill insertion.
// Preserve its provider rather than emitting this allocator's other copy.
template <> void _STL::vector<void *>::_M_fill_insert(void **position, size_t n, void *const &value);
// Likewise, the allocating unit owns native insertion at 0x000291D0.
template <> void **_STL::vector<void *>::insert(void **position, void *const &value);
// Its 38-byte default-value wrapper at 0x00029350 has the same owner.
template <> void **_STL::vector<void *>::insert(void **position);
// Suppress this unit's non-retail clear copy (row 57 family2-LK3) so the link
// keeps the retail copy another unit provides.
template <> void _STL::vector<void *>::clear();

template class _STL::vector<void *, _STL::allocator<void *> >;

// The byte-vector swap at retail 0x003079C1 calls this /Od 34-byte
// allocator-proxy swap. It folds with the void-pointer owner at 0x00025AD0;
// retain its actual typed instantiation for whole-body fold verification.
template void _STL::swap(
    _STL::_STLP_alloc_proxy<char *, char, _STL::allocator<char> > &,
    _STL::_STLP_alloc_proxy<char *, char, _STL::allocator<char> > &);

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeThrowV56@BfmeStrV56@@QAEXXZ=??1?$_STLP_alloc_proxy@PAPAXPAXV?$allocator@PAX@_STL@@@_STL@@QAE@XZ")
#pragma comment(linker, "/alternatename:?bfmeThrowV43@BfmeStrV43@@QAEXXZ=??1?$_STLP_alloc_proxy@PAPAXPAXV?$allocator@PAX@_STL@@@_STL@@QAE@XZ")
#pragma comment(linker, "/alternatename:?bfmeThrowV53@BfmeStrV53@@QAEXXZ=??1?$_STLP_alloc_proxy@PAPAXPAXV?$allocator@PAX@_STL@@@_STL@@QAE@XZ")
#pragma comment(linker, "/alternatename:?bfmeThrowV35@BfmeVecV35@@QAEXXZ=??1?$_STLP_alloc_proxy@PAPAXPAXV?$allocator@PAX@_STL@@@_STL@@QAE@XZ")
#pragma comment(linker, "/alternatename:?bfmeGrowV23@BfmeStrV23@@QAEXXZ=??1?$_STLP_alloc_proxy@PAPAXPAXV?$allocator@PAX@_STL@@@_STL@@QAE@XZ")
#pragma comment(linker, "/alternatename:?bfmeThrowV38@BfmeStrV38@@QAEXXZ=??1?$_STLP_alloc_proxy@PAPAXPAXV?$allocator@PAX@_STL@@@_STL@@QAE@XZ")
#pragma comment(linker, "/alternatename:?bfmeGrowV22@BfmeStrV22@@QAEXXZ=??1?$_STLP_alloc_proxy@PAPAXPAXV?$allocator@PAX@_STL@@@_STL@@QAE@XZ")
#pragma comment(linker, "/alternatename:?bfmeGrowV21@BfmeStrV21@@QAEXXZ=??1?$_STLP_alloc_proxy@PAPAXPAXV?$allocator@PAX@_STL@@@_STL@@QAE@XZ")
#pragma comment(linker, "/alternatename:?bfmeThrowV36@BfmeStrV36@@QAEXXZ=??1?$_STLP_alloc_proxy@PAPAXPAXV?$allocator@PAX@_STL@@@_STL@@QAE@XZ")
#pragma comment(linker, "/alternatename:?bfmeThrow1153@BfmeS1153@@QAEXXZ=??1?$_STLP_alloc_proxy@PAPAXPAXV?$allocator@PAX@_STL@@@_STL@@QAE@XZ")
#pragma comment(linker, "/alternatename:?bfmeThrow1152@BfmeS1152@@QAEXXZ=??1?$_STLP_alloc_proxy@PAPAXPAXV?$allocator@PAX@_STL@@@_STL@@QAE@XZ")
#pragma comment(linker, "/alternatename:?bfmeThrow1154@BfmeS1154@@QAEXXZ=??1?$_STLP_alloc_proxy@PAPAXPAXV?$allocator@PAX@_STL@@@_STL@@QAE@XZ")
#pragma comment(linker, "/alternatename:?bfmeRangeErrorQX@BfmeThingQX@@QAEXXZ=??1?$_STLP_alloc_proxy@PAPAXPAXV?$allocator@PAX@_STL@@@_STL@@QAE@XZ")
#pragma comment(linker, "/alternatename:?grow@Rva0082C300Buf@@AAEXXZ=??1?$_STLP_alloc_proxy@PAPAXPAXV?$allocator@PAX@_STL@@@_STL@@QAE@XZ")

// Target bytes at 0x00023A50 establish a framed cdecl int return of 0x10.
// The address-derived name preserves the unresolved semantic identity.
int Rva00023A50(void)
{
	return 0x10;
}

int Rva00023A60(void)
{
	return 8;
}

// Target bytes at 0x00023990: framed cdecl/free bool return of false (xor al, al).
bool Rva00023990(void)
{
	return false;
}

// Target bytes at 0x00023A30: round up to multiple of 8 ((n + 7) & ~7).
unsigned int Rva00023A30(unsigned int n)
{
	return (n + 7) & ~7;
}

// Target bytes at 0x00023B80: empty member function taking one pointer.
struct Rva00023B80
{
	void apply(void *p);
};

void Rva00023B80::apply(void *p)
{
}

