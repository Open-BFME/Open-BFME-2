// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??$__uninitialized_copy@PAURva005C8624Element@@PAU1@@_STL@@YAPAURva005C8624Element@@PAU1@00ABU__false_type@0@@Z
// Retail 0x005C83FA, 38 bytes. STLport __uninitialized_copy for the 72-byte
// element whose push_back sits at 0x005C8624 (stride 0x48). Calls the pinned
// out-of-line _Construct at 0x005C83CD. Caller is _M_allocate_and_copy at
// 0x005C8445 (45B, same shape as vector<BfmeE8> 0x001D9AD9 which calls the
// PAU/PAU __false_type overload at 0x004C3121). Dedicated TU so the element's
// push_back cannot inline _Construct into this loop.

struct Rva005C8624Element
{
	int a[18];
};

namespace _STL
{

struct __false_type
{
};

template <class T1, class T2>
void __declspec(nothrow) _Construct(T1 *__p, const T2 &__val);

template <class InputIter, class ForwardIter>
ForwardIter __uninitialized_copy(InputIter first, InputIter last, ForwardIter result, const __false_type &)
{
	ForwardIter cur = result;
	for (; first != last; ++first, ++cur)
		_Construct(cur, *first);
	return cur;
}

}

template Rva005C8624Element *_STL::__uninitialized_copy(Rva005C8624Element *, Rva005C8624Element *, Rva005C8624Element *, const _STL::__false_type &);
