// ?d_0000c390@@YAXXZ
// partial score=0.7 date=2026-08-30
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 basic_string<char>::reserve. The allocation goes through the
// node allocator, the copy through the CRT import and the release through
// free, which is the shape retail carries.

extern "C" __declspec(dllimport) void *__cdecl memcpy(void *, const void *, unsigned int);
void __cdecl free(void *);

namespace _STL
{

template <class T>
class char_traits {};

template <class T>
class allocator {};

template <class Pointer, class Value, class Alloc>
class _STLP_alloc_proxy : public Alloc
{
public:
	Pointer allocate(unsigned int count);
	Pointer _M_data;
};

template <class CharT, class Traits, class Alloc>
class basic_string
{
public:
	typedef unsigned int size_type;
	void reserve(size_type amount);

private:
	CharT *_M_start;
	CharT *_M_finish;
	_STLP_alloc_proxy<CharT *, CharT, Alloc> _M_end_of_storage;
};

template <class CharT, class Traits, class Alloc>
void basic_string<CharT, Traits, Alloc>::reserve(size_type amount)
{
	const size_type capacity =
			static_cast<size_type>(_M_end_of_storage._M_data - _M_start) - 1;
	if (amount < capacity)
		return;

	const size_type total = amount + 1;
	CharT *newStart = total != 0 ? _M_end_of_storage.allocate(total) : 0;
	CharT *newFinish = newStart;

	if (_M_finish != _M_start)
	{
		const size_type used = static_cast<size_type>(_M_finish - _M_start);
		newFinish = static_cast<CharT *>(memcpy(newStart, _M_start, used));
		newFinish += used;
	}

	*newFinish = CharT();

	if (_M_start != 0)
		free(_M_start);

	_M_start = newStart;
	_M_end_of_storage._M_data = newStart + total;
	_M_finish = newFinish;
}

template void basic_string<char, char_traits<char>, allocator<char> >::reserve(
		unsigned int);

}
