// cl: /DNDEBUG /MD
//
// ??$__uninitialized_copy@PAVRva001ED03C@@PAV1@@_STL@@YAPAVRva001ED03C@@PAV1@00ABU__false_type@0@@Z @0x001ED21E 38B.
// _STL::__uninitialized_copy<Rva001ED03C> retail 38 bytes. Dedicated TU
// so Rva001ED03C _Construct stays out-of-line. Evidence: chain via rowed
// _Construct 0x001ED1F1 stride 0x24 callers 0x001ED4B7 0x001ED502 same shape
// as Rva002E0A0A copy 0x0052C203 and Rva003F1EA8 copy 0x003F1EA8.
class Rva001ED03C
{
	char m_body[0x24];

public:
	Rva001ED03C(const Rva001ED03C &that);
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

template Rva001ED03C *_STL::__uninitialized_copy(Rva001ED03C *, Rva001ED03C *, Rva001ED03C *, const _STL::__false_type &);
