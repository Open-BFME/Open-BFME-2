// cl: /DNDEBUG /MD
// ??$__uninitialized_copy@PAVRva00403927@@PAV1@@_STL@@YAPAVRva00403927@@PAV1@00ABU__false_type@0@@Z @0x00403B87 38B
// _STL::__uninitialized_copy<Rva00403927>, retail 38 bytes. Dedicated TU so
// Rva00403927Construct.cpp cannot inline _Construct into this loop. Element
// stride is 0x14 via the dummy body below; _Construct is declared only and
// resolves through the rowed 0x00403B5A. Called twice by 0x00404457.
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

template <class InputIter, class ForwardIter>
ForwardIter __uninitialized_copy(InputIter first, InputIter last, ForwardIter result, const __false_type &)
{
	ForwardIter cur = result;
	for (; first != last; ++first, ++cur)
		_Construct(cur, *first);
	return cur;
}

}

template Rva00403927 *_STL::__uninitialized_copy(Rva00403927 *, Rva00403927 *, Rva00403927 *, const _STL::__false_type &);
