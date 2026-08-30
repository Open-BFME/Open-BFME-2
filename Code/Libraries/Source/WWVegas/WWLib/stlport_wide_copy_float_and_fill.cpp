// cl: /EHs /EHc- /MD /D_STLP_USE_STATIC_LIB
// stlport

typedef unsigned short wchar_t;

namespace _STL
{

template <class T>
class char_traits {};

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template <class CharT, class Traits>
class ostreambuf_iterator
{
public:
	ostreambuf_iterator &operator=(CharT);
	__declspec(dllimport) __forceinline ostreambuf_iterator &operator*()
	{
		return *this;
	}
	__declspec(dllimport) __forceinline ostreambuf_iterator &operator++()
	{
		return *this;
	}
	__declspec(dllimport) __forceinline ostreambuf_iterator &operator++(int)
	{
		return *this;
	}

private:
	void *_M_buf;
	bool _M_ok;
};

class ios_base
{
public:
	typedef int fmtflags;
	typedef int streamsize;

	enum
	{
		left = 0x0001,
		right = 0x0002,
		internal = 0x0004,
		adjustfield = left | right | internal
	};
};

template <class RandomAccessIter, class OutputIter, class Distance>
OutputIter __cdecl __copy(
		RandomAccessIter, RandomAccessIter, OutputIter,
		const random_access_iterator_tag &, Distance *);

template <class InputIter, class OutputIter>
__declspec(dllimport) __forceinline OutputIter copy(
		InputIter first, InputIter last, OutputIter result)
{
	return __copy(
			first, last, result, random_access_iterator_tag(), (int *)0);
}

template <class OutputIter, class Size, class Value>
__declspec(dllimport) __forceinline OutputIter fill_n(
		OutputIter first, Size count, const Value &value)
{
	for (; count > 0; --count, ++first)
		*first = value;
	return first;
}

template <class CharT, class OutputIter>
OutputIter __cdecl __copy_float_and_fill(
		const CharT *first, const CharT *last, OutputIter out,
		ios_base::fmtflags flags, ios_base::streamsize width, CharT fill,
		CharT plus, CharT minus)
{
	if (width <= last - first)
		return copy(first, last, out);
	else
	{
		ios_base::streamsize pad = width - (last - first);
		ios_base::fmtflags direction = flags & ios_base::adjustfield;

		if (direction == ios_base::left)
		{
			return fill_n(copy(first, last, out), pad, fill);
		}
		else if (direction == ios_base::internal && first != last &&
				(*first == plus || *first == minus))
		{
			*out++ = *first++;
			return copy(first, last, fill_n(out, pad, fill));
		}
		else
		{
			return copy(first, last, fill_n(out, pad, fill));
		}
	}
}

typedef ostreambuf_iterator<wchar_t, char_traits<wchar_t> > wide_output_iterator;

template wide_output_iterator __copy_float_and_fill<
		wchar_t, wide_output_iterator>(
		const wchar_t *, const wchar_t *, wide_output_iterator,
		ios_base::fmtflags, ios_base::streamsize, wchar_t, wchar_t, wchar_t);

}
