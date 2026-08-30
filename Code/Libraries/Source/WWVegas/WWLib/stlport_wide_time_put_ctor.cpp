// cl: /O2 /DNDEBUG /MD /EHsc

// Open-BFME5: the default STLport 4.5.3 wide time_put constructor at retail
// 0x00408ED0, 108 bytes. This is the wide specialization of the constructor
// body in vendor/stlport/stl/_time_facets.h.

typedef unsigned short wchar_t;

namespace _STL
{

template <class T>
class char_traits {};

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
		explicit facet(unsigned int refs = 0)
			: _Refcount_Base(1), _M_delete(refs == 0) {}
		virtual ~facet();

	private:
		const bool _M_delete;
	};
};

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

template <class CharT, class OutIt>
class time_put : public locale::facet, public time_base
{
public:
	explicit time_put(unsigned int refs = 0)
		: locale::facet(refs)
	{
		_Init_timeinfo(_M_timeinfo);
	}

protected:
	_Time_Info _M_timeinfo;
	virtual ~time_put();
};

template class time_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >;

}
