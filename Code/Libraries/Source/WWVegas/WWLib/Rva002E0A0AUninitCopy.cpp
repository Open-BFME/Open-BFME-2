// cl: /DNDEBUG /MD
// ??$__uninitialized_copy@PAVRva002E0A0A@@PAV1@@_STL@@YAPAVRva002E0A0A@@PAV1@00ABU__false_type@0@@Z 0x0052C203 38B evidence: copy stride 0x28 via rowed _Construct 0x0052C1D6; callers 0x0052D157 0x0052D1A2; siblings Rva003A6F70UninitCopy Rva004E18A2UninitCopy same flags
class Rva002E0A0A
{
	char _m[0x28];
public:
	Rva002E0A0A(const Rva002E0A0A &that);
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
template Rva002E0A0A *_STL::__uninitialized_copy(Rva002E0A0A *, Rva002E0A0A *, Rva002E0A0A *, const _STL::__false_type &);
