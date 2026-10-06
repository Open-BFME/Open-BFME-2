// cl: /DNDEBUG /MD
// ??$__uninitialized_copy@PAVRva004E18A2@@PAV1@@_STL@@YAPAVRva004E18A2@@PAV1@00ABU__false_type@0@@Z 0x0052C2A4 38B evidence: copy stride 0x10 via rowed _Construct 0x0052BD16; callers 0x0052C898 0x00565F4B 0x00565F96; siblings Rva003A6F70UninitCopy Rva003A6360UninitCopy same flags
class Rva004E18A2
{
	char _m[0x10];
public:
	Rva004E18A2(const Rva004E18A2 &that);
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
template Rva004E18A2 *_STL::__uninitialized_copy(Rva004E18A2 *, Rva004E18A2 *, Rva004E18A2 *, const _STL::__false_type &);
