// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 ios_base default constructor. Everything is zeroed in
// declaration order, which is why the seven format words are stored before the
// locale is built and the nine cache words after it. The exception frame is
// there for the two members that own storage - the locale at 0x20 and the
// cached grouping string at 0x48.

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
	basic_string();
	~basic_string();

private:
	CharT *_M_start;
	CharT *_M_finish;
	_STLP_alloc_proxy<CharT *, CharT, Alloc> _M_end_of_storage;
};

typedef basic_string<char, char_traits<char>, allocator<char> > narrow_string;

class _Locale_impl;

class locale
{
public:
	locale();
	~locale();

private:
	_Locale_impl *_M_impl;
};

class ios_base
{
public:
	typedef int fmtflags;

	virtual ~ios_base();

protected:
	ios_base();

private:
	fmtflags _M_fmtflags;
	int _M_iostate;
	int _M_openmode;
	int _M_seekdir;
	int _M_exception_mask;
	int _M_precision;
	int _M_width;
	locale _M_locale;
	void *_M_callbacks;
	unsigned int _M_num_callbacks;
	unsigned int _M_callback_index;
	long *_M_iwords;
	unsigned int _M_num_iwords;
	void **_M_pwords;
	unsigned int _M_num_pwords;
	void *_M_cached_ctype;
	void *_M_cached_numpunct;
	narrow_string _M_cached_grouping;
};

ios_base::ios_base()
	: _M_fmtflags(0), _M_iostate(0), _M_openmode(0), _M_seekdir(0),
	  _M_exception_mask(0), _M_precision(0), _M_width(0), _M_locale(),
	  _M_callbacks(0), _M_num_callbacks(0), _M_callback_index(0), _M_iwords(0),
	  _M_num_iwords(0), _M_pwords(0), _M_num_pwords(0), _M_cached_ctype(0),
	  _M_cached_numpunct(0), _M_cached_grouping()
{
}

}
