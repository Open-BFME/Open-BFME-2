// cl: /O2 /DNDEBUG /MD /EHsc

// Open-BFME5: the default STLport 4.5.3 wide time_get destructor at retail
// 0x00409040, 73 bytes, and the scalar deleting destructor at 0x00409020 that
// sits in slot 0 of its vftable. Layout is the one the constructor at
// 0x00408E60 fixes: locale::facet's vptr, reference count and delete flag,
// then _Time_Info at offset 0x0C.
//
// The destructor body is three stores and a call. MSVC 7.1 writes the class's
// own vftable, destroys _M_timeinfo through the out-of-line ~_Time_Info under
// unwind state 0, then writes locale::facet's vftable on the way out - the
// base destructor inlined, which is why ~facet has to be defined empty here
// rather than left declared. The unwind state and the /EHsc frame around it
// exist because ~_Time_Info is a call the compiler cannot see through.

typedef unsigned short wchar_t;

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
		virtual ~facet() {}

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
};

template <class CharT, class InIt>
time_get<CharT, InIt>::~time_get()
{
}

template class time_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >;

}
