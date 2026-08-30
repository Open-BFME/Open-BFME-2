// cl: /MD /D_STLP_USE_STATIC_LIB
// stlport

typedef unsigned short wchar_t;

namespace _STL
{

struct input_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template <class RandomAccessIter, class Value>
RandomAccessIter __cdecl __find(
		RandomAccessIter first, RandomAccessIter last, const Value &value,
		const random_access_iterator_tag &)
{
	int trip_count = (last - first) >> 2;
	for (; trip_count > 0; --trip_count)
	{
		if (*first == value) return first;
		++first;
		if (*first == value) return first;
		++first;
		if (*first == value) return first;
		++first;
		if (*first == value) return first;
		++first;
	}

	switch (last - first)
	{
	case 3:
		if (*first == value) return first;
		++first;
	case 2:
		if (*first == value) return first;
		++first;
	case 1:
		if (*first == value) return first;
		++first;
	case 0:
	default:
		return last;
	}
}

template wchar_t *__find<wchar_t *, wchar_t>(
		wchar_t *, wchar_t *, const wchar_t &,
		const random_access_iterator_tag &);

}
