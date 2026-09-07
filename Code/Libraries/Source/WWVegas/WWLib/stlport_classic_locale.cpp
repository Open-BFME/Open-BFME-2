// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// Modified reconstruction of STLport 4.5.3 src/locale_impl.cpp and the time
// facets in stl/_time_facets.h. Retail make_classic_locale is 908 bytes at
// RVA 0xB730; its original 40-entry facet table occupies 160 bytes.
//
// The ordinary placement-new/delete pair supplied by the vendor headers is
// essential: without matching placement delete MSVC refuses to inline every
// facet constructor and emits a 363-byte call-only body. Keeping that contract
// restores the original constructor expansion and exception-lifetime states.
//
// The time-facet declarations retain all 45 string members and virtual slots.
// Only _Time_Info construction/destruction and the narrow name-string
// constructor are kept opaque to select their already verified library bodies.
// _Locale_impl uses this repository's recovered _M_incr/_M_decr spellings for
// the virtual methods called incr/decr in the original private library header.
//
// Source archive: STLport-4.5.3.tar.gz, the project's SourceForge archive.
// SHA256: 74917eee7d57577518063b4caf7fb13577f21472fb92ecc239fc1ecf2fc9b1ec
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
 *
 */
#define _STLP_INTERNAL_TIME_FACETS_H
#include <string>
namespace _STL { template<> basic_string<char>::basic_string(const char*, const allocator<char>&); }
#include <locale>
#include <ctime>
namespace _STL {
class _Messages {
public:
 _Messages();
 virtual int do_open(const string&,const locale&) const;
 virtual string do_get(int,int,int,const string&) const;
 virtual wstring do_get(int,int,int,const wstring&) const;
 virtual void do_close(int) const;
 virtual ~_Messages();
 bool _M_delete;
};
class _STLP_CLASS_DECLSPEC _Time_Info {
public:
 _Time_Info();
 ~_Time_Info();
  string _M_dayname[14];
  string _M_monthname[24];
  string _M_am_pm[2];
  string _M_time_format;
  string _M_date_format;
  string _M_date_time_format;
  string _M_long_date_format;
  string _M_long_date_time_format;
};

void _STLP_CALL _Init_timeinfo(_Time_Info&);
void _STLP_CALL _Init_timeinfo(_Time_Info&, _Locale_time*);

class _STLP_CLASS_DECLSPEC time_base {
public:
  enum dateorder {no_order, dmy, mdy, ymd, ydm};
};


template <class _Ch, __DFL_TMPL_PARAM( _InIt , istreambuf_iterator<_Ch>) >
class time_get : public locale::facet, public time_base 
{
  friend class _Locale;

public:
  typedef _Ch   char_type;
  typedef _InIt iter_type;

  explicit time_get(size_t __refs = 0)   : _BaseFacet(__refs) {
      _Init_timeinfo(_M_timeinfo);
  }
  dateorder date_order() const { return do_date_order(); }
  iter_type get_time(iter_type __s, iter_type  __end, ios_base&  __str,
                     ios_base::iostate&  __err, tm* __t) const
    { return do_get_time(__s,  __end,  __str,  __err, __t); }
  iter_type get_date(iter_type __s, iter_type  __end, ios_base&  __str,
                     ios_base::iostate&  __err, tm* __t) const
    { return do_get_date(__s,  __end,  __str,  __err, __t); }
  iter_type get_weekday(iter_type __s, iter_type  __end, ios_base&  __str,
                        ios_base::iostate&  __err, tm* __t) const
    { return do_get_weekday(__s,  __end,  __str,  __err, __t); }
  iter_type get_monthname(iter_type __s, iter_type  __end, ios_base&  __str,
                          ios_base::iostate&  __err, tm* __t) const
    { return do_get_monthname(__s,  __end,  __str,  __err, __t); }
  iter_type get_year(iter_type __s, iter_type  __end, ios_base&  __str,
                     ios_base::iostate&  __err, tm* __t) const
    { return do_get_year(__s,  __end,  __str,  __err, __t); }

  _STLP_STATIC_MEMBER_DECLSPEC static locale::id id;

protected:
  _Time_Info _M_timeinfo;

  time_get(_Locale_time *, size_t __refs) : _BaseFacet(__refs) {}

  ~time_get() {}

  virtual dateorder do_date_order() const {return no_order;}
    
  virtual iter_type do_get_time(iter_type __s, iter_type  __end,
                                ios_base&, ios_base::iostate&  __err,
                                tm* __t) const;
    
  virtual iter_type do_get_date(iter_type __s, iter_type  __end,
                                ios_base&, ios_base::iostate& __err,
                                tm* __t) const;

  virtual iter_type do_get_weekday(iter_type __s, iter_type  __end,
                                   ios_base&,
                                   ios_base::iostate& __err,
                                   tm* __t) const;
  virtual iter_type do_get_monthname(iter_type __s, iter_type  __end,
                                     ios_base&,
                                     ios_base::iostate& __err,
                                     tm* __t) const;
  
  virtual iter_type do_get_year(iter_type __s, iter_type  __end,
                                ios_base&, ios_base::iostate& __err,
                                tm* __t) const;
};

time_base::dateorder _STLP_CALL
__get_date_order(_Locale_time*);
_Locale_time* _STLP_CALL __acquire_time(const char* __name);
void          _STLP_CALL __release_time(_Locale_time* __time);

template<class _Ch, __DFL_TMPL_PARAM( _OutputIter , ostreambuf_iterator<_Ch> ) >
class time_put : public locale::facet, public time_base
{
  friend class _Locale;
public:
  typedef _Ch      char_type;
  typedef _OutputIter iter_type;

  explicit time_put(size_t __refs = 0) : _BaseFacet(__refs) {
    _Init_timeinfo(_M_timeinfo);
  }

  _OutputIter put(iter_type __s, ios_base& __f, _Ch __fill,
		  const tm* __tmb,
		  const _Ch* __pat, const _Ch* __pat_end) const;
  
  _OutputIter put(iter_type __s, ios_base& __f, _Ch  __fill,
		  const tm* __tmb, char __format, char __modifier = 0) const { 
    return do_put(__s, __f,  __fill, __tmb, __format, __modifier); 
  }
  
  _STLP_STATIC_MEMBER_DECLSPEC static locale::id id;
  
protected:
  _Time_Info _M_timeinfo;

  time_put(_Locale_time* /*__time*/, size_t __refs) : _BaseFacet(__refs) {
    //    _Init_timeinfo(_M_timeinfo, __time);
  }

  ~time_put() {}
  virtual iter_type do_put(iter_type __s, ios_base& __f,
                           char_type  /* __fill */, const tm* __tmb,
                           char __format, char /* __modifier */) const;
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
	virtual void _M_incr();
	virtual void _M_decr();

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

// Full storage matters even though relocation resolution moves the globals.
typedef char _ClassicTimeInfoSize[(sizeof(_Time_Info) == 540) ? 1 : -1];
typedef char _ClassicTimeFacetSize[(sizeof(_S_time_get_char) == 552) ? 1 : -1];
typedef char _ClassicLocaleSize[(sizeof(_S_classic_locale) == 24) ? 1 : -1];
typedef char _ClassicMessageSize[(sizeof(_Null_messages) == 8) ? 1 : -1];


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
