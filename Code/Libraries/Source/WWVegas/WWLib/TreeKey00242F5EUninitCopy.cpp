// cl: /DNDEBUG /MD
// ??$__uninitialized_copy@PAUTreeKey00242F5E@@PAU1@@_STL@@YAPAUTreeKey00242F5E@@PAU1@00ABU__false_type@0@@Z @0x00523E01 38B:
// _STL::__uninitialized_copy<TreeKey00242F5E> stride 8 via dup _Construct
// 0x00523DD4 called through dup cast per Rva00212354NewNode precedent so the
// gate resolves to the dup address. Callers 0x0052451A 0x00524565 in 0x005244DC.
// Dedicated TU so the call stays external.
struct TreeKey00242F5E
{
	char _m[8];
public:
	TreeKey00242F5E(const TreeKey00242F5E &that);
};
void __cdecl dup_00523DD4(void);
typedef void (__cdecl *TreeKeyConstructFn)(TreeKey00242F5E *, const TreeKey00242F5E &);
namespace _STL
{
struct __false_type {};
template <class InputIter, class ForwardIter>
ForwardIter __uninitialized_copy(InputIter first, InputIter last, ForwardIter result, const __false_type &)
{
	ForwardIter cur = result;
	for (; first != last; ++first, ++cur)
		((TreeKeyConstructFn)&dup_00523DD4)(cur, *first);
	return cur;
}
}
template TreeKey00242F5E *_STL::__uninitialized_copy(TreeKey00242F5E *, TreeKey00242F5E *, TreeKey00242F5E *, const _STL::__false_type &);
