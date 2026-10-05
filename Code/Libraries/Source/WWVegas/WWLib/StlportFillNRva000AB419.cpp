// cl: /O1 /DNDEBUG /MD
//
// ??$__uninitialized_fill_n@PAURva000AB419Element@@IU1@@_STL@@YAPAURva000AB419Element@@PAU1@IABU1@ABU__false_type@0@@Z @0x000A9E8D (37B).
// _STL::__uninitialized_fill_n<Rva000AB419Element> retail 37 bytes. Dedicated TU
// so Rva000AB419Element _Construct stays out-of-line. Evidence: loop calls pinned
// _Construct 0x000A9E0A stride 0x10 caller 0x000AAFC6 same shape as rowed
// fill_n 0x00565770 and sibling 0x000A9E42; neighbours 0x000A9E42/0x000A9EB2.
struct Rva000AB419Element
{
	int a[4];

public:
	Rva000AB419Element(const Rva000AB419Element &that);
};

namespace _STL
{

struct __false_type {};

template <class T1, class T2>
void _Construct(T1 *p, const T2 &value);

template <class ForwardIter, class Size, class T>
ForwardIter __uninitialized_fill_n(ForwardIter first, Size n, const T &x, const __false_type &)
{
	ForwardIter cur = first;
	for (; n > 0; --n, ++cur)
		_Construct(cur, x);
	return cur;
}

}

template Rva000AB419Element *_STL::__uninitialized_fill_n(Rva000AB419Element *, unsigned int, const Rva000AB419Element &, const _STL::__false_type &);
