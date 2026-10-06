// cl: /DNDEBUG /MD
// ??$__uninitialized_fill_n@PAUTreeKey00242F5E@@IU1@@_STL@@YAPAUTreeKey00242F5E@@PAU1@IABU1@ABU__false_type@0@@Z @0x00523E27 37B:
// _STL::__uninitialized_fill_n<TreeKey00242F5E> stride 8 via dup _Construct
// 0x00523DD4 (true at 0x000A7876) called through dup cast per Rva00212354NewNode
// precedent so the gate resolves to the dup address. Caller 0x00524547 pushes
// 4 args pops 0x10. Dedicated TU so the call stays external.
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
template <class ForwardIter, class Size, class T>
ForwardIter __uninitialized_fill_n(ForwardIter first, Size n, const T &x, const __false_type &)
{
	ForwardIter cur = first;
	for (; n > 0; --n, ++cur)
		((TreeKeyConstructFn)&dup_00523DD4)(cur, x);
	return cur;
}
}
template TreeKey00242F5E *_STL::__uninitialized_fill_n(TreeKey00242F5E *, unsigned int, const TreeKey00242F5E &, const _STL::__false_type &);
