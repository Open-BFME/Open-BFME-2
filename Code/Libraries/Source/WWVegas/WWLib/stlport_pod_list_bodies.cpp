// cl: /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Pristine STLport 4.5.3 list members for fixed-size POD elements; same
// evidence and naming rule as stlport_pod_vector_bodies.cpp.
//
// BfmePodN (BfmeShortPodN: 2-byte aligned) is a placeholder for the real
// N-byte element type at each site.
// Where retail's copy construct for that element is non-trivial (it calls a
// copy constructor), _Construct<BfmePodN> is pinned in symbols.csv at the
// address the byte-true call site proves; that body is not compiled from here.
// _M_create_node fixes only the node allocation size (rounded by the node
// allocator), so its N is exact only up to that rounding: BfmeShortPod22/26
// place equally as 24/28-byte int elements under /GX.
#include <list>
// Suppress this TU's non-retail copy of ?insert@?$list@UBfmePod124@@V?$allocator@UBfmePod124@@@_STL@@@_STL@@QAE?AU?$_List_iterator:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod124;
namespace _STL { template <> _List_iterator<BfmePod124,_Nonconst_traits<BfmePod124> > list<BfmePod124,allocator<BfmePod124> >::insert(_List_iterator<BfmePod124,_Nonconst_traits<BfmePod124> >,BfmePod124 const &); }
// Suppress this TU's non-retail copy of ?insert@?$list@UBfmePod72@@V?$allocator@UBfmePod72@@@_STL@@@_STL@@QAE?AU?$_List_iterator@U:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod72;
namespace _STL { template <> _List_iterator<BfmePod72,_Nonconst_traits<BfmePod72> > list<BfmePod72,allocator<BfmePod72> >::insert(_List_iterator<BfmePod72,_Nonconst_traits<BfmePod72> >,BfmePod72 const &); }
// Suppress this TU's non-retail copy of ?insert@?$list@UBfmePod12@@V?$allocator@UBfmePod12@@@_STL@@@_STL@@QAE?AU?$_List_iterator@U:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod12;
namespace _STL { template <> _List_iterator<BfmePod12,_Nonconst_traits<BfmePod12> > list<BfmePod12,allocator<BfmePod12> >::insert(_List_iterator<BfmePod12,_Nonconst_traits<BfmePod12> >,BfmePod12 const &); }
// Suppress this TU's non-retail copy of ?insert@?$list@UBfmePod60@@V?$allocator@UBfmePod60@@@_STL@@@_STL@@QAE?AU?$_List_iterator@U:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod60;
namespace _STL { template <> _List_iterator<BfmePod60,_Nonconst_traits<BfmePod60> > list<BfmePod60,allocator<BfmePod60> >::insert(_List_iterator<BfmePod60,_Nonconst_traits<BfmePod60> >,BfmePod60 const &); }

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
struct BfmePod12 { int a[3]; };

struct BfmePod20 { int a[5]; };
struct BfmePod24 { int a[6]; };
inline bool operator==(const BfmePod12 &x, const BfmePod12 &y) { return x.a[0] == y.a[0]; }
// Retail erase(iterator) relinks the node onto the freelist pool head inline
// (pool at VA 0x00DA60E8, head at +0x08; retail 0x002ABB20).
class FreelistPool { public: void *pop(); int m_00; void *m_04; void *m_head; };
extern FreelistPool g_freelistPool;
namespace _STL {
template <> list<BfmePod12>::iterator list<BfmePod12>::erase(iterator __position)
{
	_List_node_base *__prev_node = __position._M_node->_M_prev;
	_List_node_base *__next_node = __position._M_node->_M_next;
	__prev_node->_M_next = __next_node;
	__next_node->_M_prev = __prev_node;
	*(void **)__position._M_node = g_freelistPool.m_head;
	g_freelistPool.m_head = __position._M_node;
	return iterator((_List_node<BfmePod12> *)__next_node);
}
}
inline bool operator<(const BfmePod12 &x, const BfmePod12 &y) { return x.a[0] < y.a[0]; }
inline bool operator==(const BfmePod20 &x, const BfmePod20 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod20 &x, const BfmePod20 &y) { return x.a[0] < y.a[0]; }
inline bool operator==(const BfmePod24 &x, const BfmePod24 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod24 &x, const BfmePod24 &y) { return x.a[0] < y.a[0]; }
struct BfmePod8 { int a[2]; };
inline bool operator==(const BfmePod8 &x, const BfmePod8 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod8 &x, const BfmePod8 &y) { return x.a[0] < y.a[0]; }
struct BfmePod28 { int a[7]; };
inline bool operator==(const BfmePod28 &x, const BfmePod28 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod28 &x, const BfmePod28 &y) { return x.a[0] < y.a[0]; }
struct BfmePod32 { int a[8]; };
inline bool operator==(const BfmePod32 &x, const BfmePod32 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod32 &x, const BfmePod32 &y) { return x.a[0] < y.a[0]; }
// push_back calls retail's 37-byte insert (0x000BC180) out of line; bind it there.
namespace _STL { template <> list<BfmePod32>::iterator list<BfmePod32>::insert(iterator, const BfmePod32 &); }
struct BfmePod60 { int a[15]; };
inline bool operator==(const BfmePod60 &x, const BfmePod60 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod60 &x, const BfmePod60 &y) { return x.a[0] < y.a[0]; }
struct BfmePod72 { int a[18]; };
inline bool operator==(const BfmePod72 &x, const BfmePod72 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod72 &x, const BfmePod72 &y) { return x.a[0] < y.a[0]; }
struct BfmePod124 { int a[31]; };
inline bool operator==(const BfmePod124 &x, const BfmePod124 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod124 &x, const BfmePod124 &y) { return x.a[0] < y.a[0]; }
// These elements copy through real copy constructors; their _Construct
// bodies are rowed under the real element names, so call those.
class Gen_005e9a20;
class Rva004E5012;
struct BfmeVectorRecord001B4A39;
class Rva00263895Member;
struct BfmeStringRecord000B75AE;
namespace _STL {
template <> void _Construct<BfmeStringRecord000B75AE, BfmeStringRecord000B75AE>(BfmeStringRecord000B75AE *, const BfmeStringRecord000B75AE &);
template <> void _Construct<Gen_005e9a20, Gen_005e9a20>(Gen_005e9a20 *, const Gen_005e9a20 &);
template <> void _Construct<Rva004E5012, Rva004E5012>(Rva004E5012 *, const Rva004E5012 &);
template <> void _Construct<BfmeVectorRecord001B4A39, BfmeVectorRecord001B4A39>(BfmeVectorRecord001B4A39 *, const BfmeVectorRecord001B4A39 &);
template <> void _Construct<Rva00263895Member, Rva00263895Member>(Rva00263895Member *, const Rva00263895Member &);
// 0x000B9478: list<BfmePod32>'s only node creator is retail's 0x000BB6CC
// (list<BfmeStringRecord000B75AE>::_M_create_node), which copies through the
// rowed _Construct<BfmeStringRecord000B75AE>, not 0x00421D16.
template <> __declspec(dllimport) __forceinline void _Construct<BfmePod32, BfmePod32>(BfmePod32 *p, const BfmePod32 &v)
{ _Construct((BfmeStringRecord000B75AE *)p, (const BfmeStringRecord000B75AE &)v); }
// 0x004E52FB
template <> __declspec(dllimport) __forceinline void _Construct<BfmePod60, BfmePod60>(BfmePod60 *p, const BfmePod60 &v)
{ _Construct((Rva004E5012 *)p, (const Rva004E5012 &)v); }
// 0x001B4B5C
template <> __declspec(dllimport) __forceinline void _Construct<BfmePod72, BfmePod72>(BfmePod72 *p, const BfmePod72 &v)
{ _Construct((BfmeVectorRecord001B4A39 *)p, (const BfmeVectorRecord001B4A39 &)v); }
// 0x00291608
template <> __declspec(dllimport) __forceinline void _Construct<BfmePod124, BfmePod124>(BfmePod124 *p, const BfmePod124 &v)
{ _Construct((Rva00263895Member *)p, (const Rva00263895Member &)v); }
}
struct BfmePod196 { int a[49]; };
inline bool operator==(const BfmePod196 &x, const BfmePod196 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod196 &x, const BfmePod196 &y) { return x.a[0] < y.a[0]; }
namespace _STL { template<> void _Construct<BfmePod196, BfmePod196>(BfmePod196 *, const BfmePod196 &) throw(); }
// Keep the native 37-byte insert provider from its dedicated unit.
namespace _STL { template <> list<BfmePod196>::iterator list<BfmePod196>::insert(iterator, const BfmePod196 &); }
// Experience payload cleanup is virtual: retail list clear 0x002887EA.
// Keep the proven 0x108-byte node payload and existing provider spelling.
struct BfmePod264 { BfmePod264(const BfmePod264 &); virtual ~BfmePod264(); int a[65]; };
// bfme link decl-only BfmePod264
namespace _STL { template <> void _Construct<BfmePod264, BfmePod264>(BfmePod264 *, BfmePod264 const &); }
inline bool operator==(const BfmePod264 &x, const BfmePod264 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod264 &x, const BfmePod264 &y) { return x.a[0] < y.a[0]; }
// push_back calls retail's 37-byte insert (0x00289ED7, stlport_list_pod264_insert.cpp) out of line; bind it there.
namespace _STL { template <> list<BfmePod264>::iterator list<BfmePod264>::insert(iterator, const BfmePod264 &); }
struct BfmeShortPod22 { short a[11]; };
inline bool operator==(const BfmeShortPod22 &x, const BfmeShortPod22 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmeShortPod22 &x, const BfmeShortPod22 &y) { return x.a[0] < y.a[0]; }
struct BfmeShortPod26 { short a[13]; };
inline bool operator==(const BfmeShortPod26 &x, const BfmeShortPod26 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmeShortPod26 &x, const BfmeShortPod26 &y) { return x.a[0] < y.a[0]; }
// Emit the recovered experience-list operations and their cleanup only.
// Blanket instantiation also emitted unsupported comparisons and POD copies.
template _STL::list<BfmePod264>::list(const _STL::list<BfmePod264> &);
template void _STL::list<BfmePod264>::push_back(const BfmePod264 &);
template _STL::list<BfmePod264>::_Node *_STL::list<BfmePod264>::_M_create_node(const BfmePod264 &);
template _STL::_List_base<BfmePod264, _STL::allocator<BfmePod264> >::~_List_base();


// Instantiate the recovered list operations and their native callees only.
template _STL::list<BfmePod20>::list(const _STL::allocator<BfmePod20> &);
template _STL::list<BfmePod24>::list(const _STL::allocator<BfmePod24> &);
template _STL::list<BfmePod28>::list(const _STL::allocator<BfmePod28> &);
template _STL::list<BfmePod32>::list(const _STL::allocator<BfmePod32> &);
template _STL::list<BfmePod60>::list(const _STL::allocator<BfmePod60> &);
template _STL::list<BfmePod8>::list(const _STL::allocator<BfmePod8> &);
template _STL::list<BfmePod124>::list(const _STL::allocator<BfmePod124> &);
template _STL::list<BfmePod196>::list(const _STL::allocator<BfmePod196> &);
template _STL::list<BfmePod72>::list(const _STL::allocator<BfmePod72> &);
template _STL::list<BfmePod32>::list(const _STL::list<BfmePod32> &);
template _STL::list<BfmePod196>::list(const _STL::list<BfmePod196> &);
template _STL::list<BfmePod60>::_Node *_STL::list<BfmePod60>::_M_create_node(const BfmePod60 &);
template _STL::list<BfmePod72>::_Node *_STL::list<BfmePod72>::_M_create_node(const BfmePod72 &);
template _STL::list<BfmePod124>::_Node *_STL::list<BfmePod124>::_M_create_node(const BfmePod124 &);
template _STL::list<BfmePod196>::_Node *_STL::list<BfmePod196>::_M_create_node(const BfmePod196 &);
template _STL::list<BfmePod12>::_Node *_STL::list<BfmePod12>::_M_create_node(const BfmePod12 &);
template void _STL::list<BfmePod12>::remove(const BfmePod12 &);
template void _STL::list<BfmePod32>::push_back(const BfmePod32 &);
template _STL::list<BfmePod196> &_STL::list<BfmePod196>::operator=(const _STL::list<BfmePod196> &);
template _STL::list<BfmePod32>::_Node *_STL::list<BfmePod32>::_M_create_node(const BfmePod32 &);
