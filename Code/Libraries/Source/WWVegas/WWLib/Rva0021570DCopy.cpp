// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// ?Rva0021570DCopy@@YAPAUBfmeVectorRecord0002154F3@@PAU1@00@Z @0x0021570D 29B 4-arg forwarder to rowed 5-arg worker.
// Evidence: unlock lane 29B push-0 plus tag-local at ebp-1 into 5 pushes call add-esp-0x14; callee 0x00215696 dup object-symbol is true BfmeVectorRecord0002154F3 5-arg __copy; caller 0x002157DB passes 4 args.
struct BfmeVectorRecord0002154F3;
namespace _STL {
struct random_access_iterator_tag {
};
template <class _In, class _Out, class _Dist> _Out __copy(_In, _In, _Out, const random_access_iterator_tag &, _Dist *);
}
struct BfmeVectorRecord0002154F3 *Rva0021570DCopy(struct BfmeVectorRecord0002154F3 *first, struct BfmeVectorRecord0002154F3 *last, struct BfmeVectorRecord0002154F3 *result)
{
	_STL::random_access_iterator_tag tag;
	return _STL::__copy(first, last, result, tag, (int *)0);
}
