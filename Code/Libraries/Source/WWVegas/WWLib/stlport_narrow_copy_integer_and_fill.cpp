// cl: /EHs /EHc- /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// Modified STLport 4.5.3 _num_put.c integer padding algorithm and _algobase.h
// copy/fill loops, reconstructed for BFME2. Retail RVA 0x95E0 is 569 bytes.
// The first three copy operations remain calls to the held 114-byte __copy
// instantiation at 0x98A0. Hexadecimal and ordinary leading-padding paths
// inline that same loop; the local inline dispatch preserves this distinction.
// Every character write calls the held ostreambuf_iterator assignment at
// 0x9820. The iterator layout is its buffer pointer and success flag.
//
/*
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Copyright (c) 1996,1997,1999
 * Silicon Graphics Computer Systems, Inc.
 *
 * Copyright (c) 1997
 * Moscow Center for SPARC Technology
 *
 * Copyright (c) 1999 
 * Boris Fomitchev
 *
 * This material is provided "as is", with absolutely no warranty expressed
 * or implied. Any use is at your own risk.
 *
 * Permission to use or copy this software for any purpose is hereby granted 
 * without fee, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */

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
	__forceinline ostreambuf_iterator &operator*()
	{
		return *this;
	}
	__forceinline ostreambuf_iterator &operator++()
	{
		return *this;
	}
	__forceinline ostreambuf_iterator &operator++(int)
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
__declspec(noinline) OutputIter __cdecl __copy(
		RandomAccessIter first, RandomAccessIter last, OutputIter out,
		const random_access_iterator_tag &, Distance *);

template <class RandomAccessIter, class OutputIter, class Distance>
__forceinline OutputIter __cdecl __copy_inline(
		RandomAccessIter first, RandomAccessIter last, OutputIter out,
		const random_access_iterator_tag &, Distance *)
{
	for (Distance n = last - first; n > 0; --n) {
		*out = *first;
		++first;
		++out;
	}
	return out;
}

template <class InputIter, class OutputIter>
__forceinline OutputIter copy(
		InputIter first, InputIter last, OutputIter result)
{
	return __copy(
			first, last, result, random_access_iterator_tag(), (int *)0);
}

template <class InputIter, class OutputIter>
__forceinline OutputIter copy_inline(
		InputIter first, InputIter last, OutputIter result)
{
	return __copy_inline(
			first, last, result, random_access_iterator_tag(), (int *)0);
}

template <class OutputIter, class Size, class Value>
__forceinline OutputIter fill_n(
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
			out = copy(buffer, buffer + length, out);
			return fill_n(out, pad, fill);
		}
		else if (direction == ios_base::internal && length != 0 &&
				(buffer[0] == plus || buffer[0] == minus))
		{
			*out++ = buffer[0];
			out = fill_n(out, pad, fill);
			return copy(buffer + 1, buffer + length, out);
		}
		else if (direction == ios_base::internal && length >= 2 &&
				(flags & ios_base::showbase) &&
				(flags & ios_base::basefield) == ios_base::hex)
		{
			*out++ = buffer[0];
			*out++ = buffer[1];
			out = fill_n(out, pad, fill);
			return copy_inline(buffer + 2, buffer + length, out);
		}
		else
		{
			out = fill_n(out, pad, fill);
			return copy_inline(buffer, buffer + length, out);
		}
	}
}

typedef ostreambuf_iterator<char, char_traits<char> > narrow_output_iterator;

typedef char _NarrowOutputLayout[(sizeof(narrow_output_iterator) == 8) ? 1 : -1];

template narrow_output_iterator __copy_integer_and_fill<
		char, narrow_output_iterator>(
		const char *, int, narrow_output_iterator,
		ios_base::fmtflags, ios_base::streamsize, char, char, char);

}
