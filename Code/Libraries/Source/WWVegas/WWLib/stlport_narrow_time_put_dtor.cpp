// cl: /O2 /DNDEBUG /MD /EHsc

// Open-BFME5: the default STLport 4.5.3 narrow time_put destructor at retail
// 0x00408FD0, 73 bytes, and the scalar deleting destructor at 0x00408FB0 that
// sits in slot 0 of its vftable. Layout is the one the constructor at
// 0x00408DF0 fixes: locale::facet's vptr, reference count and delete flag,
// then _Time_Info at offset 0x0C.
//
// The destructor body is three stores and a call. MSVC 7.1 writes the class's
// own vftable, destroys _M_timeinfo through the out-of-line ~_Time_Info under
// unwind state 0, then writes locale::facet's vftable on the way out - the
// base destructor inlined, which is why ~facet has to be defined empty here
// rather than left declared. The unwind state and the /EHsc frame around it
// exist because ~_Time_Info is a call the compiler cannot see through.

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

template <class CharT, class OutIt>
time_put<CharT, OutIt>::~time_put()
{
}

template class time_put<char, ostreambuf_iterator<char, char_traits<char> > >;

}
