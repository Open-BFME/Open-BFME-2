// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 wide __get_formatted_time, the worker behind
// time_get<wchar_t>::do_get_time and do_get_date. Its its four callees
// are all landed, so nothing here needed a new address: _M_getc at
// 0x00007C40, sbumpc at 0x00007E90, __match at 0x000099D0 and
// __get_decimal_integer at 0x00009CD0.
//
// The body is the upstream one from vendor/stlport/stl/_time_facets.c with
// one difference this tree already knows about: __match here takes a fifth
// parameter, an unused _DiffType*, which is how the landed 0x000099D0 row
// models it, so every call site passes a null one.
//
// The whole body turns on one line, the else arm's
//
//   if (*__first++ != *__format) break;
//
// and specifically on that being a POST-increment. The iterator model this
// TU inherits from the __match unit carries only a prefix operator++, and
// with prefix the body comes out 841 bytes and wrong in three separate
// places: no frame at all where retail reserves eight bytes, __format kept
// live in ebx across the loop where retail reloads and writes back its home
// slot every iteration, and read-modify-write memory forms - `or [eax], 4`
// for the failbit, `add [ebp+8], 12` for the pm hour - where retail loads,
// operates and stores.
//
// All three are the same cause. Post-increment has to copy the iterator, and
// that eight-byte temporary is retail's frame; the temporary raises register
// pressure enough to evict __format to memory; and with __format evicted the
// scheduler has the registers to split the memory operations. Giving the
// model a real postfix operator++ closes all 818 bytes at once. Nothing else
// was changed - and /G7 is wrong here, it turns retail's inc into add 1.
//
// About the width of the tm fields. The mangled name pinned for this body
// takes `struct tm *`, and tm's fields are int, so the reader it calls is
// the int instantiation. The row already landed at 0x00009CD0 carries the
// long one. Nothing in the bytes separates int from long on this target -
// they are the same four bytes and the same code - and the call from here
// lands on 0x00009CD0 regardless, so the two instantiations are one address:
// either the linker folded them or the existing row is labelled with the
// wrong one. The int name is pinned to that address rather than the existing
// row being rewritten, because a pin is additive and a rename would be a
// claim the bytes cannot support.

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

	istreambuf_iterator<CharT, Traits> operator++(int)
	{
		istreambuf_iterator<CharT, Traits> __tmp = *this;
		_M_bumpc();
		return __tmp;
	}

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

typedef istreambuf_iterator<unsigned short, char_traits<unsigned short> > wide_iterator;


struct __false_type {};

}

struct tm
{
	int tm_sec;
	int tm_min;
	int tm_hour;
	int tm_mday;
	int tm_mon;
	int tm_year;
	int tm_wday;
	int tm_yday;
	int tm_isdst;
};

namespace _STL
{

class _Time_Info
{
public:
	string _M_dayname[14];
	string _M_monthname[24];
	string _M_am_pm[2];
	string _M_time_format;
	string _M_date_format;
	string _M_date_time_format;
	string _M_long_date_format;
	string _M_long_date_time_format;
};

template <class _InIt, class _RAIt, class _DiffType>
_RAIt __cdecl __match(_InIt &__first, _InIt &__last, _RAIt __name,
		_RAIt __name_end, _DiffType *);

template <class _InIt, class _Integer>
bool __cdecl __get_decimal_integer(_InIt &__first, _InIt &__last,
		_Integer &__val);

template <class _InIt1, class _InIt2>
_InIt2 __cdecl __get_formatted_time(_InIt1 __first, _InIt1 __last,
		_InIt2 __format, _InIt2 __format_end,
		const _Time_Info &__table, int &__err, tm *__t)
{
	while (__first != __last && __format != __format_end) {
		if (*__format == '%') {
			++__format;
			char __c = *__format;
			switch (__c) {
				case 'a': {
					const string *__pr =
						__match(__first, __last,
							__table._M_dayname + 0, __table._M_dayname + 7, (long *)0);
					if (__pr == __table._M_dayname + 7)
						return __format;
					__t->tm_wday = (int)(__pr - __table._M_dayname);
					break;
				}

				case 'A': {
					const string *__pr =
						__match(__first, __last,
							__table._M_dayname + 7, __table._M_dayname + 14, (long *)0);
					if (__pr == __table._M_dayname + 14)
						return __format;
					__t->tm_wday = (int)(__pr - __table._M_dayname - 7);
					break;
				}

				case 'b': {
					const string *__pr =
						__match(__first, __last,
							__table._M_monthname + 0, __table._M_monthname + 12, (long *)0);
					if (__pr == __table._M_monthname + 12)
						return __format;
					__t->tm_mon = (int)(__pr - __table._M_monthname);
					break;
				}

				case 'B': {
					const string *__pr =
						__match(__first, __last,
							__table._M_monthname + 12, __table._M_monthname + 24, (long *)0);
					if (__pr == __table._M_monthname + 24)
						return __format;
					__t->tm_mon = (int)(__pr - __table._M_monthname - 12);
					break;
				}

				case 'd': {
					bool __pr = __get_decimal_integer(__first, __last, __t->tm_mday);
					if (!__pr || __t->tm_mday < 1 || __t->tm_mday > 31) {
						__err |= 4;
						return __format;
					}
					break;
				}

				case 'H': case 'I': {
					bool __pr = __get_decimal_integer(__first, __last, __t->tm_hour);
					if (!__pr)
						return __format;
					break;
				}

				case 'j': {
					bool __pr = __get_decimal_integer(__first, __last, __t->tm_yday);
					if (!__pr)
						return __format;
					break;
				}

				case 'm': {
					bool __pr = __get_decimal_integer(__first, __last, __t->tm_mon);
					--__t->tm_mon;
					if (!__pr || __t->tm_mon < 0 || __t->tm_mon > 11) {
						__err |= 4;
						return __format;
					}
					break;
				}

				case 'M': {
					bool __pr = __get_decimal_integer(__first, __last, __t->tm_min);
					if (!__pr)
						return __format;
					break;
				}

				case 'p': {
					const string *__pr =
						__match(__first, __last,
							__table._M_am_pm + 0, __table._M_am_pm + 2, (long *)0);
					if (__pr == __table._M_am_pm + 2)
						return __format;
					if (__pr == __table._M_am_pm + 1)
						__t->tm_hour += 12;
					break;
				}

				case 'S': {
					bool __pr = __get_decimal_integer(__first, __last, __t->tm_sec);
					if (!__pr)
						return __format;
					break;
				}

				case 'y': {
					bool __pr = __get_decimal_integer(__first, __last, __t->tm_year);
					if (!__pr)
						return __format;
					break;
				}

				case 'Y': {
					bool __pr = __get_decimal_integer(__first, __last, __t->tm_year);
					__t->tm_year -= 1900;
					if (!__pr)
						return __format;
					break;
				}

				default:
					break;
			}
		}
		else {
			if (*__first++ != *__format) break;
		}

		++__format;
	}

	return __format;
}

template const char *__cdecl __get_formatted_time<wide_iterator, const char *>(
		wide_iterator, wide_iterator, const char *, const char *,
		const _Time_Info &, int &, tm *);

}
