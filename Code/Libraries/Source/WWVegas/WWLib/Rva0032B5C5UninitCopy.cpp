// cl: /DNDEBUG /MD
// ??$__uninitialized_copy@PAV?$vector@UBfmeE8@@V?$allocator@UBfmeE8@@@_STL@@@_STL@@PAV12@@_STL@@YAPAV?$vector@UBfmeE8@@V?$allocator@UBfmeE8@@@_STL@@@0@PAV10@00ABU__false_type@0@@Z
// @ 0x0032B5C5 (38B). _STL::__uninitialized_copy over vector<BfmeE8> elements:
// 0xC-stride loop calling rowed _Construct 0x0032B598 per element. Evidence:
// same 38B push-esi/edi jmp-to-cmp shape as siblings Rva002E0A0AUninitCopy
// Rva004E32F2UninitCopy Rva003F1EA8UninitCopy; callers 0x0032BFAE 0x0032E883
// 0x0032E8CE; stride 0xC matches sizeof vector<BfmeE8>.
struct BfmeE8
{
	int a, b;
};
namespace _STL
{
template <class T>
class allocator
{
};
template <class T, class Alloc>
class vector
{
	T *_m_start;
	T *_m_finish;
	T *_m_end;
public:
	vector(const vector &that);
};
struct __false_type
{
};
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
typedef _STL::vector<BfmeE8, _STL::allocator<BfmeE8> > E8Vec;
template E8Vec *_STL::__uninitialized_copy(E8Vec *, E8Vec *, E8Vec *, const _STL::__false_type &);
