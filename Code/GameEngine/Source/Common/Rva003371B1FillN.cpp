// cl: /DNDEBUG /MD
//
// ??$__uninitialized_fill_n@PAVRva003371B1@@IV1@@_STL@@YAPAVRva003371B1@@PAV1@IABV1@ABU__false_type@0@@Z @0x00337366 (37B).
// _STL::__uninitialized_fill_n<Rva003371B1>, retail 37 bytes. Dedicated TU
// so Rva003371B1Copy.cpp cannot inline _Construct into this loop.
// Element stride is 0x14 via the dummy body below; _Construct is declared
// only and resolves through the rowed 0x00337313.
class Rva003371B1
{
	char _m[0x14];

public:
	Rva003371B1(const Rva003371B1 &that);
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

template Rva003371B1 *_STL::__uninitialized_fill_n(Rva003371B1 *, unsigned int, const Rva003371B1 &, const _STL::__false_type &);
