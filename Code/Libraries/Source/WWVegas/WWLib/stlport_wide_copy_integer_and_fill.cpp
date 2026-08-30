// cl: /EHs /EHc- /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.6 wide integer padding helper. The iterator's copying
// primitive and character assignment remain in the retail STLport library;
// the public copy dispatch and fill loop are instantiated inline here.

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
		adjustfield = left | right | internal,
		hex = 0x0010,
		oct = 0x0020,
		basefield = 0x0038,
		showbase = 0x0200
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
OutputIter __cdecl __copy_integer_and_fill(
		const CharT *buffer, int length, OutputIter out,
		ios_base::fmtflags flags, ios_base::streamsize width, CharT fill,
		CharT plus, CharT minus)
{
	if (length >= width)
		return copy(buffer, buffer + length, out);
	else
	{
		int pad = width - length;
		ios_base::fmtflags direction = flags & ios_base::adjustfield;

		if (direction == ios_base::left)
		{
			return fill_n(copy(buffer, buffer + length, out), pad, fill);
		}
		else if (direction == ios_base::internal && length != 0 &&
				(buffer[0] == plus || buffer[0] == minus))
		{
			*out++ = buffer[0];
			return copy(buffer + 1, buffer + length, fill_n(out, pad, fill));
		}
		else if (direction == ios_base::internal && length >= 2 &&
				(flags & ios_base::showbase) &&
				(flags & ios_base::basefield) == ios_base::hex)
		{
			*out++ = buffer[0];
			*out++ = buffer[1];
			return copy(buffer + 2, buffer + length, fill_n(out, pad, fill));
		}
		else
		{
			return copy(buffer, buffer + length, fill_n(out, pad, fill));
		}
	}
}

typedef ostreambuf_iterator<wchar_t, char_traits<wchar_t> > wide_output_iterator;

template wide_output_iterator __copy_integer_and_fill<
		wchar_t, wide_output_iterator>(
		const wchar_t *, int, wide_output_iterator,
		ios_base::fmtflags, ios_base::streamsize, wchar_t, wchar_t, wchar_t);

}
