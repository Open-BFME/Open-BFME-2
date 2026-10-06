// cl: /DNDEBUG /MD
//
// ??$__uninitialized_copy@PAVRva0054103E@@PAV1@@_STL@@YAPAVRva0054103E@@PAV1@00ABU__false_type@0@@Z @0x005411EE (38B).
// _STL::__uninitialized_copy<Rva0054103E>, retail 38 bytes. Dedicated TU so
// Rva0054103EConstruct.cpp cannot inline _Construct into this loop. Element
// stride is 0x14 via the dummy body below; _Construct is declared only and
// resolves through the rowed 0x0054106D.

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

template <class InputIter, class ForwardIter>
ForwardIter __uninitialized_copy(InputIter first, InputIter last, ForwardIter result, const __false_type &)
{
	ForwardIter cur = result;
	for (; first != last; ++first, ++cur)
		_Construct(cur, *first);
	return cur;
}

}

template Rva0054103E *_STL::__uninitialized_copy(Rva0054103E *, Rva0054103E *, Rva0054103E *, const _STL::__false_type &);
