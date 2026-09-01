// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 __match, the name-table matcher time_get::do_get_weekday and
// do_get_monthname call. Both instantiations live here: the narrow one at
// 0x000099D0 and the wide one at 0x0000F2F0, already pinned as the callees of
// those four bodies.
//
// The two 64-entry stack arrays are _MAXNAMES and _MAX_NAME_LENGTH from
// _time_facets.h. The names are always narrow strings whatever the stream
// character type - which is why both instantiations index a 12-byte stride -
// and only the input iterator differs between them.

namespace _STL
{

template <class T>
class char_traits {};

// The retail wide sbumpc returns unsigned short, the narrow one int, so the
// int_type has to come off the traits rather than being fixed.
template <>
class char_traits<char>
{
public:
	typedef int int_type;
};

template <>
class char_traits<unsigned short>
{
public:
	typedef unsigned short int_type;
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

	size_type size() const { return size_type(_M_finish - _M_start); }
	const CharT &operator[](size_type n) const { return _M_start[n]; }

private:
	CharT *_M_start;
	CharT *_M_finish;
	_STLP_alloc_proxy<CharT *, CharT, Alloc> _M_end_of_storage;
};

typedef basic_string<char, char_traits<char>, allocator<char> > string;

template <class CharT, class Traits>
class basic_streambuf
{
public:
	typename Traits::int_type sbumpc();
};

template <class CharT, class Traits>
class istreambuf_iterator
{
public:
	CharT operator*() const { _M_getc(); return _M_c; }

	istreambuf_iterator<CharT, Traits> &operator++() { _M_bumpc(); return *this; }

	bool equal(const istreambuf_iterator<CharT, Traits> &other) const
	{
		if (_M_buf != 0)
			_M_getc();
		if (other._M_buf != 0)
			other._M_getc();

		return _M_eof == other._M_eof;
	}

private:
	void _M_getc() const;

	void _M_bumpc()
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
inline bool operator!=(const istreambuf_iterator<CharT, Traits> &lhs,
		const istreambuf_iterator<CharT, Traits> &rhs)
{
	return !lhs.equal(rhs);
}

typedef istreambuf_iterator<char, char_traits<char> > narrow_iterator;
typedef istreambuf_iterator<unsigned short, char_traits<unsigned short> > wide_iterator;

// max returns a const reference, so the assignment below copies THROUGH the
// selected address rather than moving the value - that is the lea/lea pair
// retail runs, and it is also why the size() temporary and __max_pos each get
// their own stack slot even though nothing ever reads __max_pos.
template <class T>
inline const T &(max)(const T &a, const T &b)
{
	return a < b ? b : a;
}

template <class _InIt, class _RAIt, class _DiffType>
_RAIt __cdecl __match(_InIt &__first, _InIt &__last, _RAIt __name,
		_RAIt __name_end, _DiffType *)
{
	typedef _DiffType difference_type;
	difference_type __n = __name_end - __name;
	unsigned int __max_pos = 0;
	difference_type __i;
	difference_type __pos = 0;
	difference_type __check_count = __n;
	bool __do_check[64];
	_RAIt __matching_name[64];

	for (__i = 0; __i < __n; ++__i)
		__max_pos = (max)(__max_pos, __name[__i].size());

	for (__i = 0; __i < 64; ++__i)
		__do_check[__i] = true;

	for (__i = 0; __i < 64; ++__i)
		__matching_name[__i] = __name_end;

	while (__first != __last) {
		for (__i = 0; __i < __n; ++__i)
			if (__do_check[__i])
				if (*__first == __name[__i][__pos]) {
					if (__pos == _DiffType(__name[__i].size()) - 1) {
						__do_check[__i] = 0;
						__matching_name[__pos + 1] = __name + __i;
						--__check_count;
						if (__check_count == 0) {
							++__first;
							return __name + __i;
						}
					}
				}
				else {
					__do_check[__i] = 0;
					--__check_count;
					if (__check_count == 0)
						return __matching_name[__pos];
				}

		++__first; ++__pos;
	}

	return __matching_name[__pos];
}

template const string *__cdecl __match<narrow_iterator, const string *, long>(
		narrow_iterator &, narrow_iterator &, const string *, const string *, long *);

template const string *__cdecl __match<wide_iterator, const string *, long>(
		wide_iterator &, wide_iterator &, const string *, const string *, long *);

}
