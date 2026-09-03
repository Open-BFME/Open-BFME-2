// ?reserve@?$basic_string@GV?$char_traits@G@_STL@@V?$allocator@G@2@@_STL@@QAEXI@Z
// partial score=0.94 date=2026-09-03
// ?reserve@?$basic_string@GV?$char_traits@G@_STL@@V?$allocator@G@2@@_STL@@QAEXI@Z
// partial score=0.94 date=2026-09-02
// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
//
// 2026-09-03: re-measured. Six bytes differ, at 0x2F, 0x32, 0x34, 0x35, 0x55
// and 0x5D, and they are a register swap and nothing else - retail does
//   mov edx, [esi+4] / mov eax, [esi] / push edi / push edx / push eax
// and cl does the same three loads and pushes in the same order through eax
// and ecx. The values, their order and every other byte agree.
// Also checked and refuted here: /arch:SSE changes nothing.
//
// And one more, from a source rather than a guess. Open-BFME-1 landed this
// same function for the BFME1 binary at its 0x00839590, 110 bytes, and its
// body opens `if (resArg < capacity()) return;` where this one wraps the work
// in an if. Rewriting to the early-return form changes nothing here - cl 13.10
// emits the identical body either way, the same six bytes still differ. The
// two binaries' reserve are not the same length, so BFME2's is its own shape;
// the BFME1 conversion does not carry over.
// stlport
//
// STLport 4.5.3 basic_string<wchar_t>::reserve, the wide twin of 0x0000C390.
// The capacity test is against
// _M_end_of_storage._M_data - _M_start - 1, the null terminator's slot is
// written by hand after the copy, and the old block is released through the
// inlined _M_deallocate_block rather than a call.
//
// The proxy's allocate keeps its `count != 0` guard: that is the `je` retail
// takes to a zero pointer when the requested size wraps.
//
// Two things differ from the narrow twin. The copy goes through the
// __copy_trivial DECLARATION - retail calls the five-byte jump thunk at
// 0x0000DF10 rather than folding the memmove in - and the three pointer
// assignments run start, finish, storage where the narrow body runs start,
// storage, finish. Swapping them back costs six bytes.
//
// STILL OPEN: 96 of the 102 bytes match and the six that do not are one
// register-assignment swap. Retail loads _M_finish into edx and _M_start into
// eax for the copy call and lands the new end in ecx; MSVC 7.1 uses eax and
// ecx there and edx at the end. /G6 and /Ox reproduce the same six, /G7
// rewrites the body, and naming _M_finish or the new end as locals changes
// nothing.

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

void *__cdecl __copy_trivial(const void *first, const void *last, void *result);

inline unsigned short *uninitialized_copy(unsigned short *first,
		unsigned short *last, unsigned short *result)
{
	return static_cast<unsigned short *>(__copy_trivial(first, last, result));
}

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
