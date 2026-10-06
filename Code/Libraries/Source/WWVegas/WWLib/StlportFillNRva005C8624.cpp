// cl: /DNDEBUG /MD
//
// ??$__uninitialized_fill_n@PAURva005C8624Element@@IU1@@_STL@@YAPAURva005C8624Element@@PAU1@IABU1@ABU__false_type@0@@Z @0x005C8420 (37B).
// _STL::__uninitialized_fill_n<Rva005C8624Element> retail 37 bytes. Dedicated TU
// so Rva005C8624Element _Construct stays out-of-line. Evidence: loop calls rowed
// _Construct 0x005C83CD stride 0x48 caller 0x005C85DB same shape as rowed
// fill_n 0x00565770 and 0x005655DC; neighbours 0x005C83FA/0x005C8445.
struct Rva005C8624Element
{
	int a[18];

public:
	Rva005C8624Element(const Rva005C8624Element &that);
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

template Rva005C8624Element *_STL::__uninitialized_fill_n(Rva005C8624Element *, unsigned int, const Rva005C8624Element &, const _STL::__false_type &);
