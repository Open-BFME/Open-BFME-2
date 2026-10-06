// cl: /DNDEBUG /MD
// ??$__uninitialized_copy@PAVRva004E32F2@@PAV1@@_STL@@YAPAVRva004E32F2@@PAV1@00ABU__false_type@0@@Z, retail 0x0052D4CF, 38 bytes.
// _STL::__uninitialized_copy<Rva004E32F2> loop calling rowed _Construct 0x0052D4A2.
// Evidence: chain lane calls just-landed 0x0052D4A2; stride 0x18; callers 0x0052D538 0x00566B0B 0x00566B56.
class Rva004E32F2
{
	char _m[0x18];
public:
	Rva004E32F2(const Rva004E32F2 &that);
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
template Rva004E32F2 *_STL::__uninitialized_copy(Rva004E32F2 *, Rva004E32F2 *, Rva004E32F2 *, const _STL::__false_type &);
