// ?make_classic_locale@_Locale_impl@_STL@@SAPAV12@XZ
// partial score=0.0 date=2026-09-05
// ?make_classic_locale@_Locale_impl@_STL@@SAPAV12@XZ
// partial score=0.0 date=2026-09-05
// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 src/locale_impl.cpp, _Locale_impl::make_classic_locale.
// The retail body at 0x0000B730 ends at 0x0000BABB (908 bytes).  Its
// construction order and facet table are the upstream classic-locale builder;
// only the function is kept in this focused TU so the already recovered
// neighboring STLport bodies remain independent.
/*
 * Copyright (c) 1999
 * Silicon Graphics Computer Systems, Inc.
 *
 * Copyright (c) 1999
 * Boris Fomitchev
 *
 * This material is provided "as is", with absolutely no warranty expressed
 * or implied. Any use is at your own risk.
 *
 * Permission to use or copy this software for any purpose is hereby granted
 * without fee, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 */

#pragma inline_depth(255)
#pragma inline_recursion(on)

typedef unsigned int size_t;
typedef unsigned short wchar_t;

inline void *operator new(size_t, void *place)
{
	return place;
}

namespace _STL
{

template <class T>
class char_traits {};

template <class T>
class allocator
{
public:
	allocator() {}
};

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
	typedef Alloc allocator_type;

	basic_string(const CharT *s, const allocator_type &a = allocator_type());
	~basic_string();

private:
	CharT *_M_start;
	CharT *_M_finish;
	_STLP_alloc_proxy<CharT *, CharT, Alloc> _M_end_of_storage;
};

typedef basic_string<char, char_traits<char>, allocator<char> > string;
typedef basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> > wstring;

template <class CharT, class Traits>
class istreambuf_iterator {};

template <class CharT, class Traits>
class ostreambuf_iterator {};

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
		__forceinline explicit facet(unsigned int refs = 0)
			: _Refcount_Base(1), _M_delete(refs == 0) {}
		virtual ~facet();

	private:
		const bool _M_delete;
	};

	class id
	{
	public:
		size_t _M_index;
		static size_t _S_max;
	};
};

class money_base {};
class messages_base {};
class _Messages {};

template <class CharT>
class messages : public locale::facet, public messages_base
{
public:
	messages(_Messages *);

protected:
	virtual ~messages();
};

class mbstate_t {};

class ctype_base
{
public:
	enum mask { mask_value = 0 };
};

template <class CharT>
class ctype;

template <>
class ctype<char> : public locale::facet, public ctype_base
{
public:
	typedef ctype_base::mask mask;
	ctype(const mask *, bool, size_t);

protected:
	virtual ~ctype();
};

template <>
class ctype<wchar_t> : public locale::facet, public ctype_base
{
public:
	__forceinline explicit ctype(size_t refs = 0) : locale::facet(refs) {}

protected:
	virtual ~ctype();
};

template <class CharT>
class collate : public locale::facet
{
public:
	__forceinline explicit collate(size_t refs = 0) : locale::facet(refs) {}

protected:
	virtual ~collate() {}
};

template <class InternT, class ExternT, class StateT>
class codecvt : public locale::facet
{
public:
	__forceinline explicit codecvt(size_t refs = 0) : locale::facet(refs) {}

protected:
	virtual ~codecvt() {}
};

template <class CharT, bool International>
class moneypunct : public locale::facet, public money_base
{
public:
	explicit moneypunct(size_t refs = 0);

protected:
	virtual ~moneypunct();
};

template <class CharT>
class numpunct : public locale::facet
{
public:
	__forceinline explicit numpunct(size_t refs = 0) : locale::facet(refs) {}

protected:
	virtual ~numpunct() {}
};

template <class CharT, class InputIt>
class money_get : public locale::facet
{
public:
	__forceinline explicit money_get(size_t refs = 0) : locale::facet(refs) {}

protected:
	virtual ~money_get() {}
};

template <class CharT, class OutputIt>
class money_put : public locale::facet
{
public:
	__forceinline explicit money_put(size_t refs = 0) : locale::facet(refs) {}

protected:
	virtual ~money_put() {}
};

template <class CharT, class InputIt>
class num_get : public locale::facet
{
public:
	__forceinline explicit num_get(size_t refs = 0) : locale::facet(refs) {}

protected:
	virtual ~num_get() {}
};

template <class CharT, class OutputIt>
class num_put : public locale::facet
{
public:
	__forceinline explicit num_put(size_t refs = 0) : locale::facet(refs) {}

protected:
	virtual ~num_put() {}
};

class _Time_Info
{
public:
	_Time_Info();
	~_Time_Info();
};

void __cdecl _Init_timeinfo(_Time_Info &);

class time_base
{
public:
	enum dateorder { no_order, dmy, mdy, ymd, ydm };
};

template <class CharT, class InputIt>
class time_get : public locale::facet, public time_base
{
public:
	__forceinline explicit time_get(size_t refs = 0) : locale::facet(refs)
	{
		_Init_timeinfo(_M_timeinfo);
	}

protected:
	_Time_Info _M_timeinfo;
	virtual ~time_get();
};

template <class CharT, class OutputIt>
class time_put : public locale::facet, public time_base
{
public:
	__forceinline explicit time_put(size_t refs = 0) : locale::facet(refs)
	{
		_Init_timeinfo(_M_timeinfo);
	}

protected:
	_Time_Info _M_timeinfo;
	virtual ~time_put();
};

template <class T>
union _Stl_aligned_buffer
{
	char buf[sizeof(T)];
	struct { double a; double b; } padding;
};

class _Locale_impl
{
public:
	__forceinline _Locale_impl(const char *s) : name(s) {}
	virtual ~_Locale_impl();
	virtual void incr();
	virtual void decr();

	static _Locale_impl *make_classic_locale();

	locale::facet **facets;
	size_t _M_size;
	string name;
};

static _Stl_aligned_buffer<_Locale_impl> _S_classic_locale;

static _Stl_aligned_buffer<collate<char> > _S_collate_char;
static _Stl_aligned_buffer<ctype<char> > _S_ctype_char;
static _Stl_aligned_buffer<codecvt<char, char, mbstate_t> > _S_codecvt_char;
static _Stl_aligned_buffer<moneypunct<char, true> > _S_moneypunct_true_char;
static _Stl_aligned_buffer<moneypunct<char, false> > _S_moneypunct_false_char;
static _Stl_aligned_buffer<numpunct<char> > _S_numpunct_char;
static _Stl_aligned_buffer<messages<char> > _S_messages_char;
static _Stl_aligned_buffer<money_get<char, istreambuf_iterator<char, char_traits<char> > > > _S_money_get_char;
static _Stl_aligned_buffer<money_put<char, ostreambuf_iterator<char, char_traits<char> > > > _S_money_put_char;
static _Stl_aligned_buffer<num_get<char, istreambuf_iterator<char, char_traits<char> > > > _S_num_get_char;
static _Stl_aligned_buffer<num_put<char, ostreambuf_iterator<char, char_traits<char> > > > _S_num_put_char;
static _Stl_aligned_buffer<time_get<char, istreambuf_iterator<char, char_traits<char> > > > _S_time_get_char;
static _Stl_aligned_buffer<time_put<char, ostreambuf_iterator<char, char_traits<char> > > > _S_time_put_char;

static _Stl_aligned_buffer<collate<wchar_t> > _S_collate_wchar;
static _Stl_aligned_buffer<ctype<wchar_t> > _S_ctype_wchar;
static _Stl_aligned_buffer<codecvt<wchar_t, char, mbstate_t> > _S_codecvt_wchar;
static _Stl_aligned_buffer<moneypunct<wchar_t, true> > _S_moneypunct_true_wchar;
static _Stl_aligned_buffer<moneypunct<wchar_t, false> > _S_moneypunct_false_wchar;
static _Stl_aligned_buffer<numpunct<wchar_t> > _S_numpunct_wchar;
static _Stl_aligned_buffer<messages<wchar_t> > _S_messages_wchar;
static _Stl_aligned_buffer<money_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > > > _S_money_get_wchar;
static _Stl_aligned_buffer<money_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > > > _S_money_put_wchar;
static _Stl_aligned_buffer<num_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > > > _S_num_get_wchar;
static _Stl_aligned_buffer<num_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > > > _S_num_put_wchar;
static _Stl_aligned_buffer<time_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > > > _S_time_get_wchar;
static _Stl_aligned_buffer<time_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > > > _S_time_put_wchar;

static _Messages _Null_messages;

static locale::facet* _S_classic_facets[] = {
	(locale::facet*)0,
	(locale::facet*)&_S_collate_char,
	(locale::facet*)&_S_ctype_char,
	(locale::facet*)&_S_codecvt_char,
	(locale::facet*)&_S_moneypunct_true_char,
	(locale::facet*)&_S_moneypunct_false_char,
	(locale::facet*)&_S_numpunct_char,
	(locale::facet*)&_S_messages_char,
	(locale::facet*)&_S_money_get_char,
	(locale::facet*)0,
	(locale::facet*)&_S_money_put_char,
	(locale::facet*)0,
	(locale::facet*)&_S_num_get_char,
	(locale::facet*)0,
	(locale::facet*)&_S_num_put_char,
	(locale::facet*)0,
	(locale::facet*)&_S_time_get_char,
	(locale::facet*)0,
	(locale::facet*)&_S_time_put_char,
	(locale::facet*)0,
	(locale::facet*)&_S_collate_wchar,
	(locale::facet*)&_S_ctype_wchar,
	(locale::facet*)&_S_codecvt_wchar,
	(locale::facet*)&_S_moneypunct_true_wchar,
	(locale::facet*)&_S_moneypunct_false_wchar,
	(locale::facet*)&_S_numpunct_wchar,
	(locale::facet*)&_S_messages_wchar,
	(locale::facet*)&_S_money_get_wchar,
	(locale::facet*)0,
	(locale::facet*)&_S_money_put_wchar,
	(locale::facet*)0,
	(locale::facet*)&_S_num_get_wchar,
	(locale::facet*)0,
	(locale::facet*)&_S_num_put_wchar,
	(locale::facet*)0,
	(locale::facet*)&_S_time_get_wchar,
	(locale::facet*)0,
	(locale::facet*)&_S_time_put_wchar,
	(locale::facet*)0,
	0
};

_Locale_impl *
_Locale_impl::make_classic_locale()
{
	// The classic locale contains every facet that belongs to a category.
	_Locale_impl *classic = (_Locale_impl *)&_S_classic_locale;

	new (classic) _Locale_impl("C");

	classic->facets = _S_classic_facets;
	classic->_M_size = locale::id::_S_max;

	// ctype category
	new (&_S_ctype_char) ctype<char>(0, false, 1);
	// collate category
	new (&_S_collate_char) collate<char>(1);
	new (&_S_codecvt_char) codecvt<char, char, mbstate_t>(1);
	// numeric category
	new (&_S_numpunct_char) numpunct<char>(1);
	new (&_S_num_get_char) num_get<char, istreambuf_iterator<char, char_traits<char> > >(1);
	new (&_S_num_put_char) num_put<char, ostreambuf_iterator<char, char_traits<char> > >(1);
	new (&_S_time_get_char) time_get<char, istreambuf_iterator<char, char_traits<char> > >(1);
	new (&_S_time_put_char) time_put<char, ostreambuf_iterator<char, char_traits<char> > >(1);
	// monetary category
	new (&_S_moneypunct_true_char) moneypunct<char, true>(1);
	new (&_S_moneypunct_false_char) moneypunct<char, false>(1);
	new (&_S_money_get_char) money_get<char, istreambuf_iterator<char, char_traits<char> > >(1);
	new (&_S_money_put_char) money_put<char, ostreambuf_iterator<char, char_traits<char> > >(1);
	// messages category
	new (&_S_messages_char) messages<char>(&_Null_messages);

	// ctype category
	new (&_S_ctype_wchar) ctype<wchar_t>(1);
	// collate category
	new (&_S_collate_wchar) collate<wchar_t>(1);
	new (&_S_codecvt_wchar) codecvt<wchar_t, char, mbstate_t>(1);
	// numeric category
	new (&_S_numpunct_wchar) numpunct<wchar_t>(1);
	new (&_S_num_get_wchar) num_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >(1);
	new (&_S_num_put_wchar) num_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >(1);
	new (&_S_time_get_wchar) time_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >(1);
	new (&_S_time_put_wchar) time_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >(1);
	new (&_S_messages_wchar) messages<wchar_t>(&_Null_messages);
	// monetary category
	new (&_S_moneypunct_true_wchar) moneypunct<wchar_t, true>(1);
	new (&_S_moneypunct_false_wchar) moneypunct<wchar_t, false>(1);
	new (&_S_money_get_wchar) money_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >(1);
	new (&_S_money_put_wchar) money_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >(1);

	return classic;
}

}
