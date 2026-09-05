// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 basic_string<unsigned short>::reserve, retail 0x0000DEA0, 102 bytes.
// The body carried only a machine byte-dump row in Code/gen_asm/d_0000b550.asm;
// reverse/reloc_names.csv already held the decorated name with identity=real,
// so only the body was missing.
//
// This is the same template as stlport_narrow_string_reserve.cpp
// (0x0000C390) with the element two bytes wide, and retail shows the width in
// three places: capacity() divides the pointer difference by two (`sar eax,1`),
// the allocation scales the count by two (`lea ecx,[ebp+ebp]`), and the null
// terminator is stored as a word (`mov word ptr [ebx],0`).  The `count != 0`
// guard the narrow body needs is here too, as the `je` off the `inc ebp` that
// increments the request -- retail takes it to a zero pointer when the size
// wraps.
//
// The one shape difference from the narrow body: uninitialized_copy is not
// inlined here.  Retail calls it (`e8 35 ...`, cdecl, first/last/result pushed
// in that order), so the helper is declared and pinned by address rather than
// defined -- see the note at its declaration below.
//
// The whole-class instantiation in stlport_wide_string.cpp cannot own this
// address: it emits the checked form of reserve, with the
// __stl_throw_length_error arm retail does not have.
//
// The element is spelled `unsigned short` rather than `wchar_t` because this
// build has no native wide type (/Zc:wchar_t-), which is also why the decorated
// name reads `G` and not `_W`.

extern "C" void __cdecl free(void *block);

namespace _STL
{

template <class T>
class char_traits {};

template <class T>
class allocator
{
public:
	typedef unsigned int size_type;

	static T *__cdecl allocate(size_type bytes, const void *hint = 0);
};

template <class Pointer, class Value, class Alloc>
class _STLP_alloc_proxy : public Alloc
{
public:
	__declspec(dllimport) __forceinline Pointer allocate(unsigned int count)
	{
		return count != 0 ? Alloc::allocate(count * sizeof(Value), 0) : 0;
	}

	void deallocate(Pointer block, unsigned int)
	{
		if (block != 0)
			free(block);
	}

	Pointer _M_data;
};

// Retail does not inline this: reserve calls it, and the REL32 displacement
// puts the callee at 0x0000DF10, which is itself a five-byte jump (Ghidra reads
// it as thunk_FUN_004179b0) -- the copy helper reached through a folded thunk.
// It is declared here and pinned by address in reverse/symbols.csv rather than
// defined, so the call site keeps retail's displacement.
unsigned short *__cdecl uninitialized_copy(unsigned short *first,
		unsigned short *last, unsigned short *result);

template <class CharT, class Traits, class Alloc>
class basic_string
{
public:
	typedef unsigned int size_type;
	typedef CharT *pointer;

	void reserve(size_type count);

private:
	__declspec(dllimport) __forceinline size_type capacity() const
	{
		return static_cast<size_type>(_M_end_of_storage._M_data - _M_start) - 1;
	}

	__declspec(dllimport) __forceinline void _M_construct_null(pointer p)
	{
		*p = CharT();
	}

	__declspec(dllimport) __forceinline void _M_deallocate_block()
	{
		_M_end_of_storage.deallocate(_M_start,
				static_cast<size_type>(_M_end_of_storage._M_data - _M_start));
	}

	CharT *_M_start;
	CharT *_M_finish;
	_STLP_alloc_proxy<CharT *, CharT, Alloc> _M_end_of_storage;
};

template <class CharT, class Traits, class Alloc>
void basic_string<CharT, Traits, Alloc>::reserve(size_type count)
{
	if (count >= capacity())
	{
		size_type n = count + 1;
		pointer new_start = _M_end_of_storage.allocate(n);
		pointer new_finish = uninitialized_copy(_M_start, _M_finish, new_start);

		_M_construct_null(new_finish);
		_M_deallocate_block();
		_M_start = new_start;
		_M_finish = new_finish;
		_M_end_of_storage._M_data = new_start + n;
	}
}

template void
basic_string<unsigned short, char_traits<unsigned short>,
		allocator<unsigned short> >::reserve(unsigned int);

}
