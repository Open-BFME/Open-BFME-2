// cl: /MD
// ?Rva002CF830Copy@@YAPAURva000B435F@@PAU1@00@Z @0x002CF830 29B: __cdecl 3-pointer dispatcher forwarding to rowed 5-arg _STL::__copy at 0x000B6830 with random_access tag and null distance. Callers at 0x000C05AF 0x000C08C4 0x000C08E4 0x002D0D07 0x002D0D27. Honest free-function name; struct type from callee template arg.
struct Rva000B435F;
namespace _STL {
struct random_access_iterator_tag {
};
template <class _In, class _Out, class _Dist> _Out __copy(_In, _In, _Out, const random_access_iterator_tag &, _Dist *);
}
struct Rva000B435F *Rva002CF830Copy(struct Rva000B435F *first, struct Rva000B435F *last, struct Rva000B435F *result)
{
	_STL::random_access_iterator_tag tag;
	return _STL::__copy(first, last, result, tag, (int *)0);
}
