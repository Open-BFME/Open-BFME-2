// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 narrow time_put::do_put, the narrow twin of 0x0000F680.
// It formats into a 64-byte stack buffer through __write_formatted_time at
// 0x00018780 and hands the result to copy.
//
// Two things the body needs. The copy has to be the upstream random-access
// __copy, which counts down a distance rather than comparing pointers - that
// is the `sub eax,ecx` / `test eax,eax` / `dec edi` shape retail runs, where a
// hand-written pointer loop gives `cmp` on every iteration. And both copy and
// __copy need __forceinline: as plain inlines MSVC 7.1 leaves __copy out of
// line and the body ends at 71 bytes with a call where retail has the loop.

struct tm;

namespace _STL
{

template <class T>
class char_traits {};

template <>
class char_traits<char>
{
public:
	typedef int int_type;
};

template <class CharT, class Traits>
class basic_streambuf
{
public:
	typename Traits::int_type sputc(CharT value);
};

template <class CharT, class Traits>
class ostreambuf_iterator
{
public:
	ostreambuf_iterator &operator=(CharT value);
	ostreambuf_iterator &operator*() { return *this; }
	ostreambuf_iterator &operator++() { return *this; }
	ostreambuf_iterator &operator++(int) { return *this; }

private:
	basic_streambuf<CharT, Traits> *_M_buf;
	bool _M_ok;
};

class ios_base;

struct input_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template <class T>
inline random_access_iterator_tag __iterator_category(const T *)
{
	return random_access_iterator_tag();
}

template <class T>
inline int *__distance_type(const T *) { return 0; }

template <class RandomIter, class OutIt, class Distance>
__forceinline OutIt __copy(RandomIter first, RandomIter last, OutIt result,
		const random_access_iterator_tag &, Distance *)
{
	for (Distance n = last - first; n > 0; --n, ++first, ++result)
		*result = *first;
	return result;
}

template <class InIt, class OutIt>
__forceinline OutIt copy(InIt first, InIt last, OutIt result)
{
	return __copy(first, last, result, __iterator_category(first),
			__distance_type(first));
}

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

char *__cdecl __write_formatted_time(char *buffer, char format, char modifier,
		const _Time_Info &table, const tm *time);

template <class CharT, class OutIt>
class time_put : public locale::facet, public time_base
{
public:
	typedef OutIt iter_type;

	virtual ~time_put();

protected:
	virtual iter_type do_put(iter_type s, ios_base &f, CharT fill, const tm *t,
			char format, char modifier) const;

	_Time_Info _M_timeinfo;
};

template <class CharT, class OutIt>
OutIt time_put<CharT, OutIt>::do_put(OutIt __s, ios_base &, CharT, const tm *__t,
		char __format, char __modifier) const
{
	char __buf[64];
	char *__iend = __write_formatted_time(__buf, __format, __modifier,
			_M_timeinfo, __t);

	return copy(__buf, __iend, __s);
}

template class time_put<char, ostreambuf_iterator<char, char_traits<char> > >;

}
