// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??$__destroy_aux@U?$_Deque_iterator@UPodPayload20@@U?$_Nonconst_traits@UPodPayload20@@@_STL@@@_STL@@@_STL@@YAXU?$_Deque_iterator@UPodPayload20@@U?$_Nonconst_traits@UPodPayload20@@@_STL@@@0@0ABU__false_type@0@@Z retail 0x0054FD83 33B.
// Range destroy over deque<PodPayload20> via string dtor plus _M_increment 0x0054FA88.
// Element is 20B with leading basic_string<char> (12B) plus 8B pad; same stride as trivial PodPayload20.
// Evidence: dtor 0x0007FAB3, increment 0x0054FA88, caller 0x0054FE9B copies two 16B iterators.
#include <deque>
#include <string>
struct PodPayload20
{
	_STL::basic_string<char> m_str;
	char _pad[8];
};
namespace _STL
{
template void __destroy_aux<_Deque_iterator<PodPayload20, _Nonconst_traits<PodPayload20> > >(_Deque_iterator<PodPayload20, _Nonconst_traits<PodPayload20> >, _Deque_iterator<PodPayload20, _Nonconst_traits<PodPayload20> >, const __false_type &);
template void __destroy<_Deque_iterator<PodPayload20, _Nonconst_traits<PodPayload20> >, PodPayload20>(_Deque_iterator<PodPayload20, _Nonconst_traits<PodPayload20> >, _Deque_iterator<PodPayload20, _Nonconst_traits<PodPayload20> >, PodPayload20 *);
}
