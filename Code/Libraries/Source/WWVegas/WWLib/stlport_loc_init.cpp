// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 classic-locale initialisation, the four bodies that guard
// _Stl_classic_locale_impl at 0x00DDEB18 with the counter at 0x00DDEB20.
// Two are the ios_base::_Loc_init pair every stream translation unit drags
// in, two are the locale statics they stand in front of; both pairs test the
// same counter, and only the comparison differs. That is what assigns them:
// the counter is tested == 0 at 0x0000F740 and != 0 at 0x000070E0, <= 0 at
// 0x0000BAC0 and > 0 at 0x00007670, so the four fall into two guard pairs,
// and _locale.h declaring _S_initialize / _S_uninitialize as _STLP_CALL
// statics puts the cdecl pair on the locale side and leaves the thiscall
// pair for _Loc_init.
//
// The counter here is not vanilla 4.5.3. Upstream spells the destructor
// `if (--_S_count == 0)`, decrementing unconditionally; all four of these
// keep the decrement inside the guard.

//
// The two helpers it calls are pinned by ADDRESS from the REL32s here -
// 0x00006F80 then 0x0000B730 - and their names are inferred from the role,
// because they live in STLport's src/ which the vendored tree does not carry.
// Nothing but the addresses is evidenced; the byte match would hold under any
// name, so the names are labelled as inferred in symbols.csv too.

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

ios_base::_Loc_init::~_Loc_init()
{
	if (_S_count != 0)
	{
		_Stl_classic_locale_impl->_M_decr();
		--_S_count;
	}
}

void locale::_S_initialize()
{
	if (ios_base::_Loc_init::_S_count <= 0)
	{
		_Stl_loc_init_facets();
		_Stl_classic_locale_impl = _Stl_make_classic_locale();
		++ios_base::_Loc_init::_S_count;
	}
}

void locale::_S_uninitialize()
{
	if (ios_base::_Loc_init::_S_count > 0)
	{
		_Stl_classic_locale_impl->_M_decr();
		--ios_base::_Loc_init::_S_count;
	}
}

}
