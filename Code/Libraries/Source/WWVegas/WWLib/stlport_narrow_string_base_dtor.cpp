// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport46
//
// STLport 4.5.3 basic_string<wchar_t>::~basic_string, the out-of-line COMDAT
// at 0x0000B3C0. The body is the inlined ~_String_base - `if (_M_start)
// free(_M_start)`, its _M_deallocate_block against the game allocator -
// wrapped in a full /EHsc frame.
//
// Retail's unwind maps name the two string destructor bodies. A state that
// holds a complete string (the atexit thunks 0x007B6A00/10/40, state 22 of
// 0x0000DF20) jumps here; a base-only state inside a basic_string constructor
// (0x00009100, 0x00009170, 0x0000BF20, 0x0000EA90, 0x00017830) jumps to the
// frameless 14-byte ~_String_base at 0x00142D70 instead. This body is the
// complete-object destructor with the base destructor inlined: its one unwind
// state covers the free call, and the funclet behind it destroys the
// allocator proxy member at this+8.
//
// Three things the body needs:
//
//   * free declared with C++ linkage. As extern "C" it is nothrow, the call
//     needs no unwind region, and the frame collapses to the 14 bytes the
//     0x00142D70 body has.
//   * a proxy destructor the front end cannot see through. Given an empty body
//     - or one that only reads a member - MSVC 7.1 folds the member
//     destruction away before it lays out the EH states and drops the whole
//     frame with it. A call the optimiser removes later leaves exactly what
//     retail carries: the state store, no cleanup in the straight-line path,
//     and a funclet pointing at the (empty after optimisation) out-of-line
//     destructor.
//   * the destructor out of line. Inlined into a caller it is the 13-byte
//     sequence that appears all over the readers instead.

extern "C" void __cdecl free(void *block) throw(...);

namespace _STL
{

// Leak bookkeeping, compiled out of the retail build.
enum { _STLP_LEAKS_CHECK = 0 };

template <class T>
class allocator {};

template <class CharT>
class char_traits {};

template <class Pointer, class Value, class Alloc>
class _STLP_alloc_proxy : public Alloc
{
public:
	Pointer _M_data;

	~_STLP_alloc_proxy()
	{
		if (_STLP_LEAKS_CHECK)
			free(_M_data);
	}
};

// Named for this unit only: the frameless 14-byte ~_String_base at 0x00142D70
// is a separate body, and this view's unused out-of-line copy (EH-framed, like
// the destructor below) must not compete with it.
template <class CharT, class Alloc>
class _WideStringBaseView
{
public:
	~_WideStringBaseView()
	{
		if (_M_start != 0)
			free(_M_start);
	}

	CharT *_M_start;
	CharT *_M_finish;
	_STLP_alloc_proxy<CharT *, CharT, Alloc> _M_end_of_storage;
};

template <class CharT, class Traits, class Alloc>
class basic_string : private _WideStringBaseView<CharT, Alloc>
{
public:
	~basic_string();
};

template <class CharT, class Traits, class Alloc>
basic_string<CharT, Traits, Alloc>::~basic_string()
{
}

template class basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> >;

}
