// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport46
//
// Word-element vector resize (retail 0x000824F9, 61 bytes, two-argument
// form; the 15-byte one-argument form at 0x00157E50 tail-calls it with a
// literal zero). The element is a native 2-byte unit: every loop strides
// by 2, every distance shifts by 1, the one-argument form pushes an
// immediate 0, and the fill callee reads its value with a word load.
// (G is unsigned short here; the toolchain builds without native wchar_t,
// so this spelling also covers a wchar_t element.)
//
// The fill value arrives BY VALUE (retail takes its address off the stack
// slot with lea for the const-ref callee), so the resize lives on a derived
// vector that re-spells it by value, rather than on the base whose const-ref
// form pushes the pointer. The /O1 setting is load-bearing: it outlines the
// erase and _M_fill_insert calls the way retail has them, where the default
// build inlines them. Repoint the derived name if the real container's
// identity is ever recovered from a call site.
//
// The ledger previously served 0x824F9 as narrow-string resize via a
// locate.py pin, but the stride-2 arithmetic disproves a char element;
// the erase/fill callees (0x31BD55 vector erase, 0x7FF18 fill-insert) are
// the vector family.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>
// bfme link decl-only begin
// stlport_wide_num_put.cpp supplies the 4.6 name at retail's shared word
// allocator (0x00017710); keep the native growth calls out of line.
namespace _STL { template <> unsigned short * allocator<unsigned short>::allocate(unsigned int, void const *); }
// Keep the header's inline word construction, but leave the external copy to
// stlport_wide_string.cpp (retail 0x00019A00). This TU's compiler settings
// otherwise emit a competing out-of-line implementation of the same function.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _Construct<unsigned short, unsigned short>(unsigned short *p, const unsigned short &value)
{ new (p) unsigned short(value); }
}
// bfme link decl-only end
// The wide-string units ahead in link order emit the first copies of these word helpers;
// this TU takes them inline only.
namespace _STL {
template <> __declspec(dllimport) __forceinline
unsigned short *__uninitialized_copy<unsigned short *, unsigned short *>(unsigned short *first, unsigned short *last, unsigned short *result, const __true_type &)
{
    return __copy_aux(first, last, result, _BothPtrType<unsigned short *, unsigned short *>::_Ret());
}
template <> __declspec(dllimport) __forceinline
unsigned short *__uninitialized_fill_n<unsigned short *, unsigned int, unsigned short>(unsigned short *__first, unsigned int __n, const unsigned short &__x, const __true_type &)
{ return fill_n(__first, __n, __x); }
template <> __declspec(dllimport) __forceinline
unsigned short *uninitialized_fill_n<unsigned short *, unsigned int, unsigned short>(unsigned short *__first, unsigned int __n, const unsigned short &__x)
{ return __uninitialized_fill_n(__first, __n, __x, __true_type()); }
}
struct BfmeWordVec : _STL::vector<unsigned short, _STL::allocator<unsigned short> >
{
	void resize(unsigned n, unsigned short x);
	void resize(unsigned n);
	// Null fill steers the one-argument form's codegen the way stlport
	// string's _M_null() call does: evaluating a call expression for the
	// fill keeps n in eax (mov + push eax) where a literal folds to a
	// push from memory.
	static unsigned short null_fill() { return 0; }
};
__declspec(noinline) inline void BfmeWordVec::resize(unsigned n, unsigned short x)
{
	if (n < size())
		erase(begin() + n, end());
	else
		_M_fill_insert(end(), n - size(), x);
}
template class _STL::vector<unsigned short, _STL::allocator<unsigned short> >;

// ?_bfmeWordVecResizeAnchor@@YAXPAUBfmeWordVec@@IG@Z absent-from-retail
void _bfmeWordVecResizeAnchor(BfmeWordVec *vector, unsigned n, unsigned short value)
{
    vector->resize(n, value);
}
