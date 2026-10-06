// cl: /DNDEBUG /MD
//
// ??$__uninitialized_fill_n@PAURva000AB3E2Element@@IU1@@_STL@@YAPAURva000AB3E2Element@@PAU1@IABU1@ABU__false_type@0@@Z @0x000A9E42 (37B).
// _STL::__uninitialized_fill_n<Rva000AB3E2Element> retail 37 bytes. Dedicated TU
// so Rva000AB3E2Element _Construct stays out-of-line. Evidence: loop calls pinned
// _Construct 0x000A9DF8 stride 0x18 caller 0x000AAF77 same shape as rowed
// fill_n 0x00565770 and 0x005C8420; neighbours 0x000A9DF3/0x000A9EB2.
struct Rva000AB3E2Element
{
	int a[6];

public:
	Rva000AB3E2Element(const Rva000AB3E2Element &that);
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

template Rva000AB3E2Element *_STL::__uninitialized_fill_n(Rva000AB3E2Element *, unsigned int, const Rva000AB3E2Element &, const _STL::__false_type &);
