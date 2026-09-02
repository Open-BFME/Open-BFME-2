// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 _String_base<char>::~_String_base, the out-of-line COMDAT the
// wide num_get readers reach when they drop the narrow strings numpunct hands
// them back. The body is the inlined _M_deallocate_block - `if (_M_start)
// free(_M_start)` against the game allocator - wrapped in a full /EHsc frame.
//
// The frame is the identity here, and it is what tells this destructor apart
// from ??1?$basic_string@D...@XZ at 0x00142D70, which carries the same four
// instructions with no frame at all. Retail stores one unwind state at
// [esp+0x0C], never lowers it, and the funclet behind it destroys the
// allocator proxy at this+8: an offset that only makes sense inside
// _String_base, whose three members are _M_start, _M_finish and
// _M_end_of_storage. In ~basic_string the proxy sits in the base subobject and
// the cleanup would run ~_String_base at this+0 instead.
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

void __cdecl free(void *);

namespace _STL
{

// Leak bookkeeping, compiled out of the retail build.
enum { _STLP_LEAKS_CHECK = 0 };

template <class T>
class allocator {};

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

template <class CharT, class Alloc>
class _String_base
{
public:
	~_String_base();

	CharT *_M_start;
	CharT *_M_finish;
	_STLP_alloc_proxy<CharT *, CharT, Alloc> _M_end_of_storage;
};

template <class CharT, class Alloc>
_String_base<CharT, Alloc>::~_String_base()
{
	if (_M_start != 0)
		free(_M_start);
}

template class _String_base<char, allocator<char> >;

}
