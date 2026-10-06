// cl: /DNDEBUG /MD
// ??$__uninitialized_copy@PAURva00413B16Element@@PAU1@@_STL@@YAPAURva00413B16Element@@PAU1@00ABU__false_type@0@@Z @0x004139BB 38B
// _STL::__uninitialized_copy stride 0x18 via rowed _Construct 0x0041398E called twice from insert_overflow 0x00413A5F; sibling Rva004E32F2UninitCopy same flags.
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
template <class InputIter, class ForwardIter>
ForwardIter __uninitialized_copy(InputIter first, InputIter last, ForwardIter result, const __false_type &)
{
	ForwardIter cur = result;
	for (; first != last; ++first, ++cur)
		_Construct(cur, *first);
	return cur;
}
}
template Rva00413B16Element *_STL::__uninitialized_copy(Rva00413B16Element *, Rva00413B16Element *, Rva00413B16Element *, const _STL::__false_type &);
