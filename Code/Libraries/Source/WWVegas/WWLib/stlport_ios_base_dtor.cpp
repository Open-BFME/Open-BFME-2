// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 ios_base default constructor. Everything is zeroed in
// declaration order, which is why the seven format words are stored before the
// locale is built and the nine cache words after it. The exception frame is
// there for the two members that own storage - the locale at 0x20 and the
// cached grouping string at 0x48.

extern "C" __declspec(dllimport) void __cdecl free(void *block);

// The SECOND spelling of free, and the reason the body needs two. Retail
// frees the three raw arrays through the import above (`ff d7`, hoisted into
// edi, no unwind state between them) but frees the cached grouping string
// with a DIRECT call to 0x00030830, the C++-linkage free that STLport's own
// headers declare, and that call carries the null check and the state store.
// Declaring it inside _STL keeps it distinct from the extern "C" import; the
// array frees below are qualified ::free so they still reach the import.


namespace _STL
{

void __cdecl free(void *block);


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
	~basic_string()
	{
		if (_M_start != 0)
			free(_M_start);
	}

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

class ios_base;

typedef void (__cdecl *event_callback)(int event, ios_base &base, int index);

struct _M_callback_entry
{
	event_callback first;
	int second;
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
	// The destructor settles these two: it reads the live count from +0x2C and
	// the array from +0x24, so the capacity sits between them at +0x28. The
	// constructor could not tell, because it zeroes all three.
	_M_callback_entry *_M_callbacks;
	unsigned int _M_callback_capacity;
	unsigned int _M_num_callbacks;
	long *_M_iwords;
	unsigned int _M_num_iwords;
	void **_M_pwords;
	unsigned int _M_num_pwords;
	void *_M_cached_ctype;
	void *_M_cached_numpunct;
	narrow_string _M_cached_grouping;
};

// The destructor. Two different frees, and the difference is the point: the
// three raw arrays go through the CRT's free, the import at 0x00BBA6E8, while
// the cached grouping string's buffer goes through the C++-linkage free at
// 0x00030830 that STLport's allocator uses. Only the string's destructor is
// inlined here; the locale's is called.
ios_base::~ios_base()
{
	for (unsigned int i = _M_num_callbacks; i > 0; --i)
	{
		event_callback f = _M_callbacks[i - 1].first;
		int n = _M_callbacks[i - 1].second;
		f(0, *this, n);
	}

	::free(_M_callbacks);
	::free(_M_iwords);
	::free(_M_pwords);
}

ios_base::ios_base()
	: _M_fmtflags(0), _M_iostate(0), _M_openmode(0), _M_seekdir(0),
	  _M_exception_mask(0), _M_precision(0), _M_width(0), _M_locale(),
	  _M_callbacks(0), _M_callback_capacity(0), _M_num_callbacks(0), _M_iwords(0),
	  _M_num_iwords(0), _M_pwords(0), _M_num_pwords(0), _M_cached_ctype(0),
	  _M_cached_numpunct(0), _M_cached_grouping()
{
}

}
