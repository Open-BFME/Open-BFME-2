// cl: /GX- /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 __get_monetary_value, the digit reader money_get::do_get
// runs over the input before handing the result to the decimal readers.
// The upstream body is in vendor/stlport/stl/_monetary.c.
//
// Identified from the call graph of the 648-byte dump at 0x00011E30: six
// istreambuf_iterator::equal, _M_getc and sbumpc for the character reads,
// __valid_grouping once, and basic_string::push_back exactly three times -
// which is the count of `*__out++ =` sites in the upstream body, one in the
// digit loop, one in the fraction-padding loop and one in the fraction loop.
// Nothing else in _monetary.c has that shape.
//
// The ctype layout comes straight out of the prologue. Retail reads the
// facet's table from [facet+0x0C], indexes it with the zero-extended
// character at a four-byte stride, and tests bit 2 - so the table is dwords
// and ctype_base::digit is 4, which c_locale.h confirms.
//
// The last sixteen bytes were the type of that table, and they are worth
// spelling out. Retail tests the flag as
//
//   8b 0c 88     mov ecx, [eax+ecx*4]
//   c1 e9 02     shr ecx, 2
//   f6 c1 01     test cl, 1
//
// where a table of unsigned int gives the shorter `f6 04 88 04`, a direct
// test of the byte, at all four call sites. No spelling of the expression
// reaches the longer form - a named temporary, swapped operands and a double
// negation are all identical - because it is not the expression that decides
// it, it is the type. _ctype.h declares the table as `const mask*`, an enum,
// and _Locale_SPACE folds in the blank class at bit 31, so that enum's
// underlying type is UNSIGNED. Testing a bit in an unsigned enum is what
// makes cl 13.10 load, shift the bit down to position zero and test it there.
// Declaring the enum with its real c_locale.h values closes the body.

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
	typedef CharT value_type;

	void push_back(CharT);
	__declspec(dllimport) __forceinline unsigned int size() const
	{
		return static_cast<unsigned int>(_M_finish - _M_start);
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

typedef basic_string<char, char_traits<char>, allocator<char> > string;

class locale
{
public:
	class facet {};
};

class ctype_base
{
public:
	// c_locale.h values verbatim. _Locale_SPACE carries the blank class at
	// bit 31, which is what makes this enum unsigned.
	enum mask {
		space  = 0x00000008 | 0x80000000,
		print  = 0x00000010 | 0x00000001 | 0x00000002 | 0x00000004 |
			 0x00000200 | 0x00000080 | 0x00000400,
		cntrl  = 0x00000020,
		upper  = 0x00000001,
		lower  = 0x00000002,
		alpha  = 0x00000200,
		digit  = 0x00000004,
		punct  = 0x00000010,
		xdigit = 0x00000080,
		alnum  = alpha | digit,
		graph  = alnum | punct
	};
};

template <class CharT>
class ctype : public locale::facet, public ctype_base
{
public:
	__declspec(dllimport) __forceinline bool is(mask __m, CharT __c) const
	{
		return ((*(_M_ctype_table + (unsigned char)__c)) & __m) != 0;
	}

private:
	void *_M_unused0;
	void *_M_unused1;
	const mask *_M_ctype_table;
};

template <class CharT, class Traits>
class basic_streambuf
{
public:
	int sbumpc();
};

template <class CharT, class Traits>
class istreambuf_iterator
{
public:
	__declspec(dllimport) __forceinline CharT operator*() const
	{
		_M_getc();
		return _M_c;
	}

	istreambuf_iterator &operator++() { _M_bumpc(); return *this; }

	__declspec(dllimport) __forceinline istreambuf_iterator operator++(int)
	{
		istreambuf_iterator __tmp = *this;
		_M_bumpc();
		return __tmp;
	}

	bool equal(const istreambuf_iterator &) const;

private:
	void _M_getc() const;

	__declspec(dllimport) __forceinline void _M_bumpc()
	{
		_M_buf->sbumpc();
		_M_have_c = false;
	}

	basic_streambuf<CharT, Traits> *_M_buf;
	mutable CharT _M_c;
	mutable unsigned char _M_eof;
	mutable unsigned char _M_have_c;
};

template <class CharT, class Traits>
__declspec(dllimport) __forceinline bool operator==(
		const istreambuf_iterator<CharT, Traits> &__x,
		const istreambuf_iterator<CharT, Traits> &__y)
{
	return __x.equal(__y);
}

template <class CharT, class Traits>
__declspec(dllimport) __forceinline bool operator!=(
		const istreambuf_iterator<CharT, Traits> &__x,
		const istreambuf_iterator<CharT, Traits> &__y)
{
	return !__x.equal(__y);
}

typedef istreambuf_iterator<char, char_traits<char> > narrow_iterator;

template <class Container>
class back_insert_iterator
{
public:
	__declspec(dllimport) __forceinline back_insert_iterator &operator*()
	{
		return *this;
	}
	__declspec(dllimport) __forceinline back_insert_iterator &operator++()
	{
		return *this;
	}
	__declspec(dllimport) __forceinline back_insert_iterator &operator++(int)
	{
		return *this;
	}
	__declspec(dllimport) __forceinline back_insert_iterator &operator=(
			const typename Container::value_type &__v)
	{
		container->push_back(__v);
		return *this;
	}

	Container *container;
};

typedef back_insert_iterator<string> narrow_back_inserter;

bool __cdecl __valid_grouping(const char *, const char *, const char *,
		const char *);

template <class _InIt, class _OuIt, class _CharT>
bool __cdecl __get_monetary_value(_InIt &__first, _InIt __last, _OuIt __out,
		const ctype<_CharT> &_c_type, _CharT __point, int __frac_digits,
		_CharT __sep, const string &__grouping, bool &__syntax_ok)
{
	if (__first == __last || !_c_type.is(ctype_base::digit, *__first))
		return false;

	char __group_sizes[128];
	char *__group_sizes_end = __grouping.size() == 0 ? 0 : __group_sizes;
	char __current_group_size = 0;

	while (__first != __last) {
		if (_c_type.is(ctype_base::digit, *__first)) {
			++__current_group_size;
			*__out++ = *__first++;
		}
		else if (__group_sizes_end) {
			if (*__first == __sep) {
				*__group_sizes_end++ = __current_group_size;
				__current_group_size = 0;
				++__first;
			}
			else break;
		}
		else
			break;
	}

	if (__grouping.size() == 0)
		__syntax_ok = true;
	else {
		if (__group_sizes_end != __group_sizes)
			*__group_sizes_end++ = __current_group_size;

		__syntax_ok = __valid_grouping(__group_sizes, __group_sizes_end,
				__grouping.data(), __grouping.data() + __grouping.size());

		if (__first == __last || *__first != __point) {
			for (int __digits = 0; __digits != __frac_digits; ++__digits)
				*__out++ = _CharT('0');
			return true;
		}
	}

	++__first;

	unsigned int __digits = 0;

	while (__first != __last && _c_type.is(ctype_base::digit, *__first)) {
		*__out++ = *__first++;
		++__digits;
	}

	__syntax_ok = __syntax_ok && (__digits == (unsigned int)__frac_digits);

	return true;
}

template bool __cdecl __get_monetary_value<narrow_iterator,
		narrow_back_inserter, char>(
	narrow_iterator &, narrow_iterator, narrow_back_inserter,
	const ctype<char> &, char, int, char, const string &, bool &);

}
