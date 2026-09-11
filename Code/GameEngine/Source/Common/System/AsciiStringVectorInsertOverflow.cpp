// cl: /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// STLport 4.5.3 vector<AsciiString>::_M_insert_overflow at 0x00143070 and the
// _M_clear it calls at 0x00142EA0, the growth path of the push_back that
// Upgrade.cpp already matches at 0x00143170.
//
// They cannot come from Upgrade.cpp, whose AsciiString carries Zero Hour's
// heavier release: there __destroy_aux stays a call, _M_clear stays small and
// is inlined into _M_insert_overflow.  BFME's string releases its buffer
// through slot 0 of the buffer once the count at +4 drops to zero, and with
// that dtor _M_clear takes the whole destroy loop and one-argument free, and
// retail keeps it out of line.  The reduced AsciiString below is that string
// and nothing more.
//
// _Construct<AsciiString, AsciiString> is its own body at 0x00142CC0
// (AsciiStringConstruct.cpp); its specialization is declared, not defined,
// so the copy loops here call it as retail does.

#include <vector>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
	struct AsciiStringData
	{
		virtual void _M_slot_00();
		int m_refCount;
	};

	AsciiStringData *m_data;

public:
	AsciiString();
	AsciiString(const AsciiString &that);
	AsciiString &operator=(const AsciiString &that);
	// Through a local: retail tests the decrement's own flags and calls slot 0
	// on the same register, where rereading m_data after the store to the
	// count costs a reload and a compare.
	~AsciiString()
	{
		AsciiStringData *data = m_data;
		if (data && --data->m_refCount == 0)
			data->_M_slot_00();
	}
};

namespace _STL
{
template <> void _Construct<AsciiString, AsciiString>(AsciiString *, const AsciiString &);

// The vendored configuration defines _STLP_LOOP_INLINE_PROBLEMS, so the range
// __destroy_aux is not `inline` and cl 13.10 keeps it a call; retail's
// _M_clear expanded the loop.  The same body for this element, with
// __forceinline because cl declines a plain `inline` through a template
// specialisation (see reference/shims/bfmealloc/README.md).
template <>
__forceinline void __destroy_aux<AsciiString *>(AsciiString *__first, AsciiString *__last, const __false_type &)
{
	for ( ; __first != __last; ++__first)
		_Destroy(&*__first);
}

// The two dispatch layers above it are `inline` upstream but, for the same
// reason, survive as calls unless forced.
template <>
__forceinline void __destroy<AsciiString *, AsciiString>(AsciiString *__first, AsciiString *__last, AsciiString *)
{
	__destroy_aux(__first, __last, __false_type());
}

template <>
__forceinline void _Destroy<AsciiString *>(AsciiString *__first, AsciiString *__last)
{
	__destroy(__first, __last, (AsciiString *)0);
}
}

template class _STL::vector<AsciiString, _STL::allocator<AsciiString> >;
