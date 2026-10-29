// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport46
// ??$__destroy_aux@U?$_Deque_iterator@UPodPayload20@@U?$_Nonconst_traits@UPodPayload20@@@_STL@@@_STL@@@_STL@@YAXU?$_Deque_iterator@UPodPayload20@@U?$_Nonconst_traits@UPodPayload20@@@_STL@@@0@0ABU__false_type@0@@Z retail 0x0054FD83 33B.
// Range destroy over deque<PodPayload20> via string dtor plus _M_increment 0x0054FA88.
// Element is 20B with leading basic_string<char> (12B) plus 8B pad; same stride as trivial PodPayload20.
// Evidence: dtor 0x0007FAB3, increment 0x0054FA88, caller 0x0054FE9B copies two 16B iterators.
#include <deque>
#include <string>
#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> _String_base<char, allocator<char> >::~_String_base(); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::~basic_string(); }
// bfme link decl-only end
// Suppress this TU's non-retail proxy<char> deallocate copy (family2-LK3 row 28):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char*, size_t);
}
struct PodPayload20
{
	_STL::basic_string<char> m_str;
	char _pad[8];
};
namespace _STL
{
// Keep the native loop's inline comparison while leaving the out-of-line
// provider to stlport_deque_destroy_pod.cpp (retail 0x00169C80).
template <> __declspec(dllimport) __forceinline bool _STLP_CALL operator!=<PodPayload20>(
	const _Deque_iterator_base<PodPayload20> &left,
	const _Deque_iterator_base<PodPayload20> &right)
{ return left._M_cur != right._M_cur; }
template void __destroy_aux<_Deque_iterator<PodPayload20, _Nonconst_traits<PodPayload20> > >(_Deque_iterator<PodPayload20, _Nonconst_traits<PodPayload20> >, _Deque_iterator<PodPayload20, _Nonconst_traits<PodPayload20> >, const __false_type &);
template void __destroy<_Deque_iterator<PodPayload20, _Nonconst_traits<PodPayload20> >, PodPayload20>(_Deque_iterator<PodPayload20, _Nonconst_traits<PodPayload20> >, _Deque_iterator<PodPayload20, _Nonconst_traits<PodPayload20> >, PodPayload20 *);
}
