// cl: /MD
//
// ??$__uninitialized_copy@PAUCoord3D@@PAU1@@_STL@@YAPAUCoord3D@@PAU1@00ABU__false_type@0@@Z @0x00346C2D 38B: STLport __uninitialized_copy for 12-byte Coord3D.
// Retail calls the pinned Coord3D _Construct at 0x002CA82C (UCoord3D pin thermodynamics via list node 0x27F4A9) with stride 0x0C adds.
// Callers 0x000E016A 0x0034C0D0 0x002CDF8A pass (first last result false_type) with add esp 0x10 and idiv/imul 0x0C counts; returns result end.
// Dedicated TU so the _Construct stays an out-of-line call (generic declaration, no body) like WeaponTemplateSetUninitializedCopy 0x004AE927.
struct Coord3D
{
	float x, y, z;
	Coord3D(const Coord3D &that);
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
template Coord3D *_STL::__uninitialized_copy(Coord3D *, Coord3D *, Coord3D *, const _STL::__false_type &);
