// cl: /DNDEBUG /MD
//
// ??$__uninitialized_copy@PAURva00423A4A@@PAU1@@_STL@@YAPAURva00423A4A@@PAU1@00ABU__false_type@0@@Z @0x00423ED1 (38B).
// _STL::__uninitialized_copy<Rva00423A4A>, retail 38 bytes. Dedicated TU so
// _Construct cannot inline into this loop. Element stride is 0xC via dummy
// body; _Construct is declared only and resolves through the rowed 0x00423E83.
struct Rva00423A4A
{
	char _m[0xC];
public:
	Rva00423A4A(const Rva00423A4A &that);
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
template Rva00423A4A *_STL::__uninitialized_copy(Rva00423A4A *, Rva00423A4A *, Rva00423A4A *, const _STL::__false_type &);
