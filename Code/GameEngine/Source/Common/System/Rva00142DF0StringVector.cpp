// cl: /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// STLport 4.5.3 vector<Rva00142DF0String> helpers, the family that sits at
// 0x00142CE0..0x001431AF: __uninitialized_copy 0x00142CE0, __uninitialized_fill_n
// 0x00142D10, the scalar deleting destructor 0x00142D40, _M_clear 0x00142EA0,
// _M_insert_overflow 0x00143070 and push_back 0x00143170. _Construct is its own
// body at 0x00142CC0 (Rva00142DF0StringConstruct.cpp); its specialization is
// declared, not defined, so the copy loops here call it as retail does.
//
// Rva00142DF0String is the refcounted 4-byte handle of Rva001431B0's member
// vector at +0x13c (Rva001431B0Pop.cpp names it): copying adds 1 to the count
// at +4 of the buffer, and releasing calls slot 0 of the buffer once that count
// drops to zero. These bodies were held as vector<AsciiString>'s until
// 2026-10-02, but they are not AsciiString's: retail has a second, complete
// vector<AsciiString> family (push_back 0x0002DBE6, _Construct 0x0002C485,
// _M_clear 0x0002CD53, __uninitialized_fill_n 0x0002C4D8, ...), every verified
// call to those names in matched code lands there (14 push_back call sites,
// none here), and AsciiString's copy goes through StringBase<char>'s copy row
// at 0x000365F0 with the count at +0 of its buffer, not inline with it at +4.
// The bodies here are called only by this family and by Rva001431B0.
//
// The vendored configuration defines _STLP_LOOP_INLINE_PROBLEMS, so the range
// __destroy_aux is not `inline` and cl 13.10 keeps it a call; retail's _M_clear
// expanded the loop (see the forced specializations below).

// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7 /arch:SSE) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

class Rva00142DF0String
{
	struct Rva00142DF0StringData
	{
		virtual void _M_slot_00();
		int m_refCount;
	};

	Rva00142DF0StringData *m_data;

public:
	Rva00142DF0String();
	Rva00142DF0String(const Rva00142DF0String &that);
	Rva00142DF0String &operator=(const Rva00142DF0String &that);
	// Through a local: retail tests the decrement's own flags and calls slot 0
	// on the same register, where rereading m_data after the store to the
	// count costs a reload and a compare.
	~Rva00142DF0String()
	{
		Rva00142DF0StringData *data = m_data;
		if (data && --data->m_refCount == 0)
			data->_M_slot_00();
	}
};

namespace _STL
{
template <> void _Construct<Rva00142DF0String, Rva00142DF0String>(Rva00142DF0String *, const Rva00142DF0String &);

// The same body for this element, with __forceinline because cl declines a
// plain `inline` through a template specialisation (see
// reference/shims/bfmealloc/README.md).
template <>
__forceinline void __destroy_aux<Rva00142DF0String *>(Rva00142DF0String *__first, Rva00142DF0String *__last, const __false_type &)
{
	for ( ; __first != __last; ++__first)
		_Destroy(&*__first);
}

// The two dispatch layers above it are `inline` upstream but, for the same
// reason, survive as calls unless forced.
template <>
__forceinline void __destroy<Rva00142DF0String *, Rva00142DF0String>(Rva00142DF0String *__first, Rva00142DF0String *__last, Rva00142DF0String *)
{
	__destroy_aux(__first, __last, __false_type());
}

template <>
__forceinline void _Destroy<Rva00142DF0String *>(Rva00142DF0String *__first, Rva00142DF0String *__last)
{
	__destroy(__first, __last, (Rva00142DF0String *)0);
}
}

template void _STL::vector<Rva00142DF0String, _STL::allocator<Rva00142DF0String> >::_M_clear();
template void _STL::vector<Rva00142DF0String, _STL::allocator<Rva00142DF0String> >::_M_insert_overflow(
	Rva00142DF0String *,
	const Rva00142DF0String &,
	const _STL::__false_type &,
	unsigned int,
	bool);
template void _STL::vector<Rva00142DF0String, _STL::allocator<Rva00142DF0String> >::push_back(const Rva00142DF0String &);
template Rva00142DF0String *_STL::__uninitialized_fill_n<Rva00142DF0String *, unsigned int, Rva00142DF0String>(
	Rva00142DF0String *, unsigned int, const Rva00142DF0String &, const _STL::__false_type &);
template Rva00142DF0String *_STL::__uninitialized_copy<Rva00142DF0String *, Rva00142DF0String *>(
	Rva00142DF0String *, Rva00142DF0String *, Rva00142DF0String *, const _STL::__false_type &);
