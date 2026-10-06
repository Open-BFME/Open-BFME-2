// cl: /DNDEBUG /MD
//
// ??$__uninitialized_copy@PBVRva00568A20@@PAV1@@_STL@@YAPAVRva00568A20@@PBV1@0PAV1@ABU__false_type@0@@Z @0x00568C95 (38B).
// _STL::__uninitialized_copy<Rva00568A20>, retail 38 bytes. Dedicated TU so
// Rva00568A20 _Construct stays out-of-line. Element stride is 0xC via the
// dummy body below; _Construct is declared only and resolves through the
// rowed 0x00568C83. Same 38B shape as throw-spec sibling 0x0004CC82 and
// callers at 0x00568D86 0x0056A225 0x0056A270 prove copy role.
class Rva00568A20
{
	char _m[12];

public:
	Rva00568A20(const Rva00568A20 &that);
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

template Rva00568A20 *_STL::__uninitialized_copy(const Rva00568A20 *, const Rva00568A20 *, Rva00568A20 *, const _STL::__false_type &);
