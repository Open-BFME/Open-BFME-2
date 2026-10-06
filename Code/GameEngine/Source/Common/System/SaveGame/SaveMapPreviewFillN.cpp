// cl: /MD
// ??$__uninitialized_fill_n@PAVSaveMapPreview@@IV1@@_STL@@YAPAVSaveMapPreview@@PAV1@IABV1@ABU__false_type@0@@Z @0x002DBF28 40B
// Evidence: unlock lane; caller 0x002DDDB9 pushes dst count value false_type; callee rowed copy ctor 0x2262E7; stride 0x14.
inline void *__cdecl operator new(unsigned int, void *p) throw() { return p; }
inline void __cdecl operator delete(void *, void *) throw() { }
class SaveMapPreview
{
	char _m[0x14];
public:
	__declspec(nothrow) SaveMapPreview(const SaveMapPreview &that);
};
namespace _STL {
struct __false_type {};
template <class ForwardIter, class Size, class T>
ForwardIter __uninitialized_fill_n(ForwardIter first, Size n, const T &x, const __false_type &)
{
	ForwardIter cur = first;
	for (; n > 0; --n, ++cur) {
		if (cur != 0)
			new (cur) SaveMapPreview(x);
	}
	return cur;
}
}
template SaveMapPreview *_STL::__uninitialized_fill_n(SaveMapPreview *, unsigned int, const SaveMapPreview &, const _STL::__false_type &);
