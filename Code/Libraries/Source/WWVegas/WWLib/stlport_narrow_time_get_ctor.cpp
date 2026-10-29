// cl: /DNDEBUG /MD /EHsc
// stlport46

// Open-BFME5: the default STLport 4.5.3 narrow time_get constructor at
// retail 0x00408D80, 108 bytes. This is the constructor body from
// vendor/stlport/stl/_time_facets.h: locale::facet takes the reference policy,
// _Time_Info constructs at offset 0x0C, and _Init_timeinfo fills it.

struct tm;

namespace _STL
{

template <class T>
class char_traits {};

template <class CharT, class Traits>
class istreambuf_iterator {};

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

// STLport defines this out of line in locale_impl.cpp, where retail's
// ??_Gfacet (0x00007490) inlines the empty body; seeing it here makes this
// unit's select-any copy of ??_Gfacet retail's.
inline locale::facet::~facet()
{
}

class time_base
{
public:
	enum dateorder { no_order, dmy, mdy, ymd, ydm };
};

class _Time_Info
{
public:
	_Time_Info();
	~_Time_Info();
};

void __cdecl _Init_timeinfo(_Time_Info &);

class ios_base;

template <class CharT, class InIt>
class time_get : public locale::facet, public time_base
{
public:
	explicit time_get(unsigned int refs = 0)
		: locale::facet(refs)
	{
		_Init_timeinfo(_M_timeinfo);
	}

protected:
	_Time_Info _M_timeinfo;
	virtual ~time_get();
	virtual dateorder do_date_order() const;
	// The remaining STLport slots, as the full facet in stlport_classic_locale.cpp
	// declares them: this TU's table copy then has all seven.
	virtual InIt do_get_time(InIt, InIt, ios_base &, int &, tm *) const;
	virtual InIt do_get_date(InIt, InIt, ios_base &, int &, tm *) const;
	virtual InIt do_get_weekday(InIt, InIt, ios_base &, int &, tm *) const;
	virtual InIt do_get_monthname(InIt, InIt, ios_base &, int &, tm *) const;
	virtual InIt do_get_year(InIt, InIt, ios_base &, int &, tm *) const;
};

template class time_get<char, istreambuf_iterator<char, char_traits<char> > >;

}
