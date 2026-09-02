// ??8locale@_STL@@QBE_NABV01@@Z
// partial score=0.97 date=2026-09-02
// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 locale::operator==. Two impls that are the same object are
// the same locale; otherwise the names decide, and a nameless locale is
// never equal to anything.

extern "C" void __cdecl free(void *block);

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
	Pointer _M_data;
};

template <class CharT, class Traits, class Alloc>
class basic_string
{
public:
	typedef unsigned int size_type;

	basic_string(const basic_string<CharT, Traits, Alloc> &that);
	~basic_string()
	{
		if (_M_start != 0)
			free(_M_start);
	}

	const CharT *data() const { return _M_start; }
	size_type size() const { return (size_type)(_M_finish - _M_start); }

private:
	CharT *_M_start;
	CharT *_M_finish;
	_STLP_alloc_proxy<CharT *, CharT, Alloc> _M_end_of_storage;
};

typedef basic_string<char, char_traits<char>, allocator<char> > string;

template <class CharT, class Traits, class Alloc>
bool __cdecl operator!=(const basic_string<CharT, Traits, Alloc> &x,
	const basic_string<CharT, Traits, Alloc> &y);

extern "C" int __cdecl memcmp(const void *a, const void *b, unsigned int n);
#pragma intrinsic(memcmp)

template <class CharT, class Traits, class Alloc>
inline bool __cdecl operator==(const basic_string<CharT, Traits, Alloc> &x,
	const basic_string<CharT, Traits, Alloc> &y)
{
	return x.size() == y.size() && memcmp(x.data(), y.data(), x.size()) == 0;
}

class _Locale_impl;

class locale
{
public:
	string name() const;
	bool operator==(const locale &that) const;

private:
	_Locale_impl *_M_impl;
};

extern const string _Nameless;

bool locale::operator==(const locale &that) const
{
	return _M_impl == that._M_impl ||
		(name() == that.name() && name() != _Nameless);
}

}
