// cl: /GX- /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 operator!= over two narrow strings. operator== inlines into it
// whole: equal lengths, then a traits compare of the two data pointers, and the
// trailing sete/mov pair is the negation operator!= wraps around it.

extern "C" int __cdecl memcmp(const void *left, const void *right,
		unsigned int count);

#pragma intrinsic(memcmp)

namespace _STL
{

template <class T>
class char_traits;

template <>
class char_traits<char>
{
public:
	__declspec(dllimport) __forceinline static int compare(
			const char *left, const char *right, unsigned int count)
	{
		return memcmp(left, right, count);
	}
};

template <class T>
class allocator {};

template <class Pointer, class Value, class Alloc>
class _STLP_alloc_proxy : public Alloc
{
public:
	Pointer _M_data;
};

template <class CharT, class Traits, class Alloc>
class basic_string
{
public:
	typedef unsigned int size_type;

	__declspec(dllimport) __forceinline size_type size() const
	{
		return static_cast<size_type>(_M_finish - _M_start);
	}

	__declspec(dllimport) __forceinline const CharT *data() const
	{
		return _M_start;
	}

private:
	CharT *_M_start;
	CharT *_M_finish;
	_STLP_alloc_proxy<CharT *, CharT, Alloc> _M_end_of_storage;
};

template <class CharT, class Traits, class Alloc>
__declspec(dllimport) __forceinline bool __cdecl operator==(
		const basic_string<CharT, Traits, Alloc> &left,
		const basic_string<CharT, Traits, Alloc> &right)
{
	return left.size() == right.size() &&
			!Traits::compare(left.data(), right.data(), left.size());
}

template <class CharT, class Traits, class Alloc>
bool __cdecl operator!=(const basic_string<CharT, Traits, Alloc> &left,
		const basic_string<CharT, Traits, Alloc> &right)
{
	return !(left == right);
}

typedef basic_string<char, char_traits<char>, allocator<char> > narrow_string;

template bool __cdecl operator!=(const narrow_string &, const narrow_string &);

}
