// cl: /DNDEBUG /MD
//
// _STL::__uninitialized_copy PAURva004F6352, retail 0x004F6B1E 38B,
// and _STL::__uninitialized_fill_n PAURva004F6352, retail 0x004F6B44 37B.
// Dedicated TU so _Construct at 0x004F6A76 stays an out-of-line call.
// Element stride is 0xC (12-byte Rva004F6352 with TreeHintRef at +8).
// Callers of copy at 0x004F6C23 0x004F8FA2 0x004F8FED; caller of fill at
// 0x004F8FCF inside FUN_008f8f61.

struct Rva004F6352
{
	char _m[0xC];

public:
	Rva004F6352(const Rva004F6352 &that);
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

template Rva004F6352 *_STL::__uninitialized_copy(Rva004F6352 *, Rva004F6352 *, Rva004F6352 *, const _STL::__false_type &);
template Rva004F6352 *_STL::__uninitialized_fill_n(Rva004F6352 *, unsigned int, const Rva004F6352 &, const _STL::__false_type &);
