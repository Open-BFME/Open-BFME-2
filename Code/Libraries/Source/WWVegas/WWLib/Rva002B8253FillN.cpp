// cl: /O1 /DNDEBUG /MD
// ??$__uninitialized_fill_n@PAURva002B72C9@@IU1@@_STL@@YAPAURva002B72C9@@PAU1@IABU1@ABU__false_type@0@@Z @0x002B8253 37B
// _STL::__uninitialized_fill_n<Rva002B72C9>, retail 37 bytes. Dedicated TU so
// no local _Construct definition can inline into this loop. Element stride is
// 0x14 via the dummy body below; _Construct is declared only and resolves
// through the rowed 0x002B8226. Called by 0x002BC434 in 0x002BC3C6; unblocks
// 0x002BC3C6. (Rva00403927FillN.cpp precedent.)
struct Rva002B72C9
{
	char _m[0x14];

public:
	Rva002B72C9(const Rva002B72C9 &that);
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

template Rva002B72C9 *_STL::__uninitialized_fill_n(Rva002B72C9 *, unsigned int, const Rva002B72C9 &, const _STL::__false_type &);
