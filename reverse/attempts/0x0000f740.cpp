// ??0_Loc_init@ios_base@_STL@@QAE@XZ
// partial score=0.9 date=2026-09-02
// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 classic-locale initialisation, the four bodies that guard
// _Stl_classic_locale_impl at 0x00DDEB18 with the counter at 0x00DDEB20.
// Two are the ios_base::_Loc_init pair every stream translation unit drags
// in, two are the locale statics they stand in front of; both pairs test the
// same counter, and only the comparison differs.

namespace _STL
{

class locale
{
public:
	class facet {};

	static void _S_initialize();
	static void _S_uninitialize();
};

class _Locale_impl
{
public:
	virtual ~_Locale_impl();
	virtual void _M_incr();
	virtual void _M_decr();

	locale::facet **_M_facets;
	unsigned int _M_count;
};

class ios_base
{
public:
	class _Loc_init
	{
	public:
		_Loc_init();
		~_Loc_init();

	private:
		static long _S_count;
	};
};

// The facet tables the classic locale is built out of, and the builder that
// returns the impl itself.
void _Stl_loc_init_facets();
_Locale_impl *_Stl_make_classic_locale();

_Locale_impl *_Stl_classic_locale_impl;
long ios_base::_Loc_init::_S_count;

ios_base::_Loc_init::_Loc_init()
{
	if (_S_count == 0)
	{
		_Stl_loc_init_facets();
		_Stl_classic_locale_impl = _Stl_make_classic_locale();
		++_S_count;
	}
}

}
