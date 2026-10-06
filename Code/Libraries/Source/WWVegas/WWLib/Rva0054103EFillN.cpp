// cl: /DNDEBUG /MD
//
// ??$__uninitialized_fill_n@PAVRva0054103E@@IV1@@_STL@@YAPAVRva0054103E@@PAV1@IABV1@ABU__false_type@0@@Z @0x00541108 (37B).
// _STL::__uninitialized_fill_n<Rva0054103E>, retail 37 bytes. Dedicated TU
// so Rva0054103EConstruct.cpp cannot inline _Construct into this loop.
// Element stride is 0x14 via the dummy body below; _Construct is declared
// only and resolves through the rowed 0x0054106D.

class Rva0054103E
{
	char _m[0x14];

public:
	Rva0054103E(const Rva0054103E &that);
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

template Rva0054103E *_STL::__uninitialized_fill_n(Rva0054103E *, unsigned int, const Rva0054103E &, const _STL::__false_type &);
