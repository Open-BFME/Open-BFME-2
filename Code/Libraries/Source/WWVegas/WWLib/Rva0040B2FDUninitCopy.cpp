// cl: /DNDEBUG /MD
// stlport
// ??$__uninitialized_copy@PAVRva0040AEE3@@PAV1@@_STL@@YAPAVRva0040AEE3@@PAV1@00ABU__false_type@0@@Z @ 0x0040B2FD (38B). Copy stride 0x10 via pinned _Construct 0x0040B14E.
// Evidence: retail calls rowed Rva Construct 0x0040B14E stride 0x10; callers 0x0040B872 0x0040B8BD in just-landed overflow 0x0040B834 plus 0x0040B6BB; same 38B shape as rowed Rva003A6F70 copy 0x0052C27E.
// Preserve the visible STL loops and call the existing native placement-copy
// provider for this same record view. The application identity remains unknown.
class Rva0040AEE3;
void Rva0040B14EConstruct(Rva0040AEE3 *, const Rva0040AEE3 &);
#include <utility>
namespace _STL {
// ?_STL::_Construct absent-from-retail
static __forceinline void _Construct(Rva0040AEE3 *destination,
                                    const Rva0040AEE3 &source)
{
    Rva0040B14EConstruct(destination, source);
}
}

class Rva0040AEE3
{
	char _m[0x10];
public:
	Rva0040AEE3(const Rva0040AEE3 &that);
};
namespace _STL
{
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
template Rva0040AEE3 *_STL::__uninitialized_copy(Rva0040AEE3 *, Rva0040AEE3 *, Rva0040AEE3 *, const _STL::__false_type &);
