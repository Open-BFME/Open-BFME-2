// cl: /O1 /DNDEBUG /MD
// ??$__uninitialized_fill_n@PAURva00413B16Element@@IU1@@_STL@@YAPAURva00413B16Element@@PAU1@IABU1@ABU__false_type@0@@Z @0x004139E1 37B
// _STL::__uninitialized_fill_n stride 0x18 via rowed _Construct 0x0041398E called from 0x00413ACD; sibling Rva00403927FillN same flags.
struct Rva00413B16Element
{
	char _m[0x18];

public:
	Rva00413B16Element(const Rva00413B16Element &that);
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

template Rva00413B16Element *_STL::__uninitialized_fill_n(Rva00413B16Element *, unsigned int, const Rva00413B16Element &, const _STL::__false_type &);
