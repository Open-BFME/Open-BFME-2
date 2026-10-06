// cl: /DNDEBUG /MD
// ??$__uninitialized_copy@PAVRva003A6360Record@@PAV1@@_STL@@YAPAVRva003A6360Record@@PAV1@00ABU__false_type@0@@Z 0x0052C2CA 41B evidence: stride 0x10 via rowed copy ctor 0x0052BB9A; callers 0x0052C8AB 0x00565FC1; sibling Rva003A6F70UninitCopy same template
class Rva003A6360Record
{
	char _m[0x10];
public:
	Rva003A6360Record(const Rva003A6360Record &that);
};
inline void *operator new(unsigned int, void *p)
{
	return p;
}
namespace _STL
{
struct __false_type {};
template <class InputIter, class ForwardIter>
ForwardIter __uninitialized_copy(InputIter first, InputIter last, ForwardIter result, const __false_type &)
{
	ForwardIter cur = result;
	for (; first != last; ++first, ++cur)
		new (cur) Rva003A6360Record(*first);
	return cur;
}
}
template Rva003A6360Record *_STL::__uninitialized_copy(Rva003A6360Record *, Rva003A6360Record *, Rva003A6360Record *, const _STL::__false_type &);
