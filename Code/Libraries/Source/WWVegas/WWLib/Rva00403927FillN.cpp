// cl: /DNDEBUG /MD
// ??$__uninitialized_fill_n@PAVRva00403927@@IV1@@_STL@@YAPAVRva00403927@@PAV1@IABV1@ABU__false_type@0@@Z @0x00403BAD 37B
// _STL::__uninitialized_fill_n<Rva00403927>, retail 37 bytes. Dedicated TU so
// no local _Construct definition can inline into this loop. Element stride is
// 0x14 via the dummy body below; _Construct is declared only and resolves
// through the rowed 0x00403B5A. Called by 0x004044C5 in 0x00404457; unblocks
// 0x00404457. (Rva00564C58FillN.cpp precedent.)
class Rva00403927
{
	char _m[0x14];

public:
	Rva00403927(const Rva00403927 &that);
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

template Rva00403927 *_STL::__uninitialized_fill_n(Rva00403927 *, unsigned int, const Rva00403927 &, const _STL::__false_type &);
