// ?do_get_time@?$time_get@DV?$istreambuf_iterator@DV?$char_traits@D@_STL@@@_STL@@@_STL@@MBE?AV?$istreambuf_iterator@DV?$char_traits@D@_STL@@@2@V32@0AAVios_base@2@AAHPAUtm@@@Z
// partial score=0.9 date=2026-09-03
// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 narrow time_get::do_get_weekday and do_get_monthname, the
// char twins of the wide pair at 0x0000F510 and 0x0000F5C0. Both
// retail bodies inline their __get_short_or_long_* helper and the iterator
// comparison but keep __match and istreambuf_iterator::_M_getc out of line, so
// the helpers are written out here rather than pulled in from <locale>: the
// vendored header inlines the opposite pair. _Time_Info always holds narrow
// strings, which is why both name tables stride 12 bytes even in the wide
// facet, and the day table sits at offset 0 while the month table follows it
// at 0xA8.

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
	typedef const CharT *const_iterator;

	const_iterator begin() const { return _M_start; }
	const_iterator end() const { return _M_finish; }

private:
	CharT *_M_start;
	CharT *_M_finish;
	_STLP_alloc_proxy<CharT *, CharT, Alloc> _M_end_of_storage;
};

typedef basic_string<char, char_traits<char>, allocator<char> > string;

template <class CharT, class Traits>
class istreambuf_iterator
{
public:
	bool equal(const istreambuf_iterator &other) const
	{
		if (_M_buf != 0)
			_M_getc();
		if (other._M_buf != 0)
			other._M_getc();

		return _M_eof == other._M_eof;
	}

private:
	void _M_getc() const;

	void *_M_buf;
	mutable CharT _M_c;
	mutable unsigned char _M_eof;
	mutable unsigned char _M_have_c;
};

template <class CharT, class Traits>
inline bool operator==(const istreambuf_iterator<CharT, Traits> &lhs,
		const istreambuf_iterator<CharT, Traits> &rhs)
{
	return lhs.equal(rhs);
}

class _Refcount_Base
{
protected:
	explicit _Refcount_Base(unsigned int count) : _M_ref_count(count) {}

private:
	volatile int _M_ref_count;
};

class locale
{
public:
	class facet : private _Refcount_Base
	{
	protected:
		explicit facet(unsigned int refs = 0)
			: _Refcount_Base(1), _M_delete(refs == 0) {}
		virtual ~facet();

	private:
		const bool _M_delete;
	};
};

class ios_base
{
public:
	typedef int iostate;

	enum { goodbit = 0, eofbit = 2, failbit = 4 };
};

class time_base
{
public:
	enum dateorder { no_order, dmy, mdy, ymd, ydm };
};

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

template <class _InIt>
__forceinline bool __cdecl __get_short_or_long_dayname(_InIt &__first,
		_InIt &__last, const _Time_Info &__table, tm *__t)
{
	const string *__pr =
		__match(__first, __last, __table._M_dayname + 0,
			__table._M_dayname + 14, (long *)0);
	__t->tm_wday = (int)(__pr - __table._M_dayname) % 7;
	return __pr != __table._M_dayname + 14;
}

template <class _InIt>
__forceinline bool __cdecl __get_short_or_long_monthname(_InIt &__first, _InIt &__last,
		const _Time_Info &__table, tm *__t)
{
	const string *__pr =
		__match(__first, __last, (string *)__table._M_monthname + 0,
			(string *)__table._M_monthname + 24, (long *)0);
	__t->tm_mon = (int)(__pr - __table._M_monthname) % 12;
	return __pr != (string *)__table._M_monthname + 24;
}

template <class _InIt1, class _InIt2>
_InIt2 __cdecl __get_formatted_time(_InIt1 __first, _InIt1 __last,
		_InIt2 __format, _InIt2 __format_end, const _Time_Info &__table,
		ios_base::iostate &__err, tm *__t);

template <class CharT, class InIt>
class time_get : public locale::facet, public time_base
{
public:
	typedef InIt iter_type;

	explicit time_get(unsigned int refs = 0);

protected:
	_Time_Info _M_timeinfo;

	virtual ~time_get();
	virtual dateorder do_date_order() const;
	virtual iter_type do_get_time(iter_type, iter_type, ios_base &,
			ios_base::iostate &, tm *) const;
	virtual iter_type do_get_date(iter_type, iter_type, ios_base &,
			ios_base::iostate &, tm *) const;
	virtual iter_type do_get_weekday(iter_type, iter_type, ios_base &,
			ios_base::iostate &, tm *) const;
	virtual iter_type do_get_monthname(iter_type __s, iter_type __end,
			ios_base &__str, ios_base::iostate &__err, tm *__t) const;
	virtual iter_type do_get_year(iter_type, iter_type, ios_base &,
			ios_base::iostate &, tm *) const;
};

template <class CharT, class InIt>
InIt time_get<CharT, InIt>::do_get_time(iter_type __s, iter_type __end,
		ios_base & /* __str */, ios_base::iostate &__err, tm *__t) const
{
	typedef string::const_iterator string_iterator;

	string_iterator __format = _M_timeinfo._M_time_format.begin();
	string_iterator __format_end = _M_timeinfo._M_time_format.end();

	string_iterator __result =
		__get_formatted_time(__s, __end, __format, __format_end,
			_M_timeinfo, __err, __t);
	__err = __result == __format_end ? ios_base::goodbit
		: ios_base::failbit;
	if (__s == __end)
		__err |= ios_base::eofbit;
	return __s;
}

template <class CharT, class InIt>
InIt time_get<CharT, InIt>::do_get_date(iter_type __s, iter_type __end,
		ios_base & /* __str */, ios_base::iostate &__err, tm *__t) const
{
	typedef string::const_iterator string_iterator;

	string_iterator __format = _M_timeinfo._M_date_format.begin();
	string_iterator __format_end = _M_timeinfo._M_date_format.end();

	string_iterator __result =
		__get_formatted_time(__s, __end, __format, __format_end,
			_M_timeinfo, __err, __t);
	if (__result == __format_end)
		__err = ios_base::goodbit;
	else {
		__err = ios_base::failbit;
		if (__s == __end)
			__err |= ios_base::eofbit;
	}
	return __s;
}

template <class CharT, class InIt>
InIt time_get<CharT, InIt>::do_get_weekday(iter_type __s, iter_type __end,
		ios_base & /* __str */, ios_base::iostate &__err, tm *__t) const
{
	bool __result =
		__get_short_or_long_dayname(__s, __end, _M_timeinfo, __t);
	if (__result)
		__err = ios_base::goodbit;
	else {
		__err = ios_base::failbit;
		if (__s == __end)
			__err |= ios_base::eofbit;
	}
	return __s;
}

template <class CharT, class InIt>
InIt time_get<CharT, InIt>::do_get_monthname(iter_type __s, iter_type __end,
		ios_base & /* __str */, ios_base::iostate &__err, tm *__t) const
{
	bool __result =
		__get_short_or_long_monthname(__s, __end, _M_timeinfo, __t);
	if (__result)
		__err = ios_base::goodbit;
	else {
		__err = ios_base::failbit;
		if (__s == __end)
			__err |= ios_base::eofbit;
	}
	return __s;
}

template istreambuf_iterator<char, char_traits<char> >
time_get<char,
	istreambuf_iterator<char, char_traits<char> > >::
	do_get_weekday(
		istreambuf_iterator<char, char_traits<char> >,
		istreambuf_iterator<char, char_traits<char> >,
		ios_base &, ios_base::iostate &, tm *) const;

template istreambuf_iterator<char, char_traits<char> >
time_get<char,
	istreambuf_iterator<char, char_traits<char> > >::
	do_get_monthname(
		istreambuf_iterator<char, char_traits<char> >,
		istreambuf_iterator<char, char_traits<char> >,
		ios_base &, ios_base::iostate &, tm *) const;

template istreambuf_iterator<char, char_traits<char> >
time_get<char,
	istreambuf_iterator<char, char_traits<char> > >::
	do_get_time(
		istreambuf_iterator<char, char_traits<char> >,
		istreambuf_iterator<char, char_traits<char> >,
		ios_base &, ios_base::iostate &, tm *) const;

template istreambuf_iterator<char, char_traits<char> >
time_get<char,
	istreambuf_iterator<char, char_traits<char> > >::
	do_get_date(
		istreambuf_iterator<char, char_traits<char> >,
		istreambuf_iterator<char, char_traits<char> >,
		ios_base &, ios_base::iostate &, tm *) const;

}
