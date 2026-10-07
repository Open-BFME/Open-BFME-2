// cl: /Od /Ob1 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 vector<void *>. The reloc sweep names _M_fill_insert and
// reserve out of this instantiation from byte-true call sites, so the
// instantiation is known to exist in the image; this is the same vendored
// route the int and pair vectors here already use.

#include <vector>

template class _STL::vector<void *, _STL::allocator<void *> >;

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

