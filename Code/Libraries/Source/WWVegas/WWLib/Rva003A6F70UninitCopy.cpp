// cl: /DNDEBUG /MD
// ??$__uninitialized_copy@PAVRva003A6F70@@PAV1@@_STL@@YAPAVRva003A6F70@@PAV1@00ABU__false_type@0@@Z 0x0052C27E 38B evidence: copy stride 0x20 via rowed _Construct 0x0052BD04; callers 0x0052C854 0x00565DE0 0x00565E2B; sibling Rva00564C58FillN same record same flags
class Rva003A6F70
{
	char _m[0x20];
public:
	Rva003A6F70(const Rva003A6F70 &that);
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
template Rva003A6F70 *_STL::__uninitialized_copy(Rva003A6F70 *, Rva003A6F70 *, Rva003A6F70 *, const _STL::__false_type &);
