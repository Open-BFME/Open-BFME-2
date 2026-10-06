// cl: /DNDEBUG /MD
//
// _STL::__uninitialized_copy PBUBfmeNarrowRecord00427F75 PAU, retail 0x00428123 38B,
// and _STL::__uninitialized_fill_n PAUBfmeNarrowRecord00427F75, retail 0x00428149 37B.
// Dedicated TU so _Construct at 0x004280F6 stays an out-of-line call. Element stride
// is 0x18 (two STLport basic_string<char>). Callers at 0x0042847F 0x004284CA
// (copy) and 0x004284AC (fill) inside FUN_0082843e.

struct BfmeNarrowRecord00427F75
{
	char _m[0x18];

public:
	BfmeNarrowRecord00427F75(const BfmeNarrowRecord00427F75 &that);
};

namespace _STL
{

struct __false_type {};

template <class T1, class T2>
void _Construct(T1 *p, const T2 &value);

template <class InputIter, class ForwardIter>
ForwardIter __uninitialized_copy(InputIter first, InputIter last,
	ForwardIter result, const __false_type &)
{
	ForwardIter cur = result;
	for (; first != last; ++first, ++cur)
		_Construct(cur, *first);
	return cur;
}

template <class ForwardIter, class Size, class T>
ForwardIter __uninitialized_fill_n(ForwardIter first, Size n,
	const T &x, const __false_type &)
{
	ForwardIter cur = first;
	for (; n > 0; --n, ++cur)
		_Construct(cur, x);
	return cur;
}

}

template BfmeNarrowRecord00427F75 *_STL::__uninitialized_copy(const BfmeNarrowRecord00427F75 *, const BfmeNarrowRecord00427F75 *, BfmeNarrowRecord00427F75 *, const _STL::__false_type &);
template BfmeNarrowRecord00427F75 *_STL::__uninitialized_fill_n(BfmeNarrowRecord00427F75 *, unsigned int, const BfmeNarrowRecord00427F75 &, const _STL::__false_type &);
