// cl: /O2 /Oy /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ?contains@BfmeUnsignedKeyTree620C70@@QAE_NI@Z, retail 0x00620C70, 39 bytes.
//
// Unsigned-key containment test over the signed-key stlport map<int,void*>.
// Lifted from the banked attempt at score 0.96; two corrections took it to an
// exact match, and both are visible in the retail bytes:
//
// 1. /Oy, NOT /Oy-. Retail opens `push ecx / push esi / mov esi,ecx` with no
//    `push ebp`, so it was built with frame-pointer omission. The bank carried
//    /Oy-, which forces `push ebp / mov ebp,esp` and put a frame-pointer diff
//    at +0 -- the sole reason the bank never reached zero.
//
// 2. THE KEY IS PASSED BY ADDRESS, NEVER COPIED. Retail computes
//    `lea eax,[esp+0xc]` -- the address of its OWN argument slot -- and pushes
//    that, so find receives a pointer into the caller's frame and the key is
//    never loaded. Binding a reference first (`const int &k = (const int&)key`)
//    makes MSVC materialise the argument into a register or stack slot and the
//    copy shows up in the body. Taking the address at the point of use keeps
//    the key where the caller put it.
//
// The tree is the signed-key _Rb_tree<int,...,less<int>>: its find@H thunk is
// the 20B body placed at 0x004D7546 by WWVegas/WWLib/stlport_map_int_ptr_o1.cpp,
// and that thunk tails the unsigned _M_find@I at 0x357180, so retail's call
// resolves against the rowed address rather than self-referencing the way an
// unplaced unsigned thunk would.
//
// Evidence: call target 0x4D7546 is rowed and its bytes are the
// `mov ecx,[esp+4] / mov [ecx],eax / mov eax,ecx / ret 8` out-parameter thunk;
// the body is 0x00620C70..0x00620C97 with `ret 4` at 0x00620C96 and 0xCC
// padding after.
// The linked game shares one copy of the signed-key tree's find@H: retail's
// /O1 thunk at 0x004D7546 (stlport_map_int_ptr_o1.cpp). Through <map>, this
// /O2 unit emits its own, different instantiations of it, of _M_find@H and of
// map::find, which every other object would then link against
// (tools/link_check.py refuses that), and an explicit specialization
// declaration crashes cl 7.1 (C1001). So the unit declares only what it
// calls: STLport's names as their mangling records them, with no bodies.
// map<int, void *> holds just its _Rb_tree, whose header-node pointer is its
// first word: retail's end() is the `mov ecx,[esi]` after the call.
namespace _STL
{
template <class _Tp> struct less;
template <class _Tp> class allocator;
template <class _T1, class _T2> struct pair;
template <class _Pair> struct _Select1st;
template <class _Tp> struct _Nonconst_traits;
struct _Rb_tree_node_base;
template <class _Value> struct _Rb_tree_node;

struct _Rb_tree_base_iterator
{
	_Rb_tree_node_base *_M_node;
	bool operator!=(const _Rb_tree_base_iterator &__y) const { return _M_node != __y._M_node; }
};

template <class _Value, class _Traits>
struct _Rb_tree_iterator : public _Rb_tree_base_iterator
{
	_Rb_tree_iterator(_Rb_tree_node<_Value> *__x) { _M_node = (_Rb_tree_node_base *)__x; }
};

template <class _Key, class _Value, class _KeyOfValue, class _Compare, class _Alloc>
class _Rb_tree
{
public:
	typedef _Rb_tree_iterator<_Value, _Nonconst_traits<_Value> > iterator;
	template <class _KT> iterator find(const _KT &__k);
	iterator end() { return iterator(_M_header); }

private:
	_Rb_tree_node<_Value> *_M_header;
};
}

typedef _STL::pair<const int, void *> BfmeUnsignedKeyTree620C70Value;

class BfmeUnsignedKeyTree620C70
{
public:
	bool contains(unsigned int key);

private:
	typedef _STL::_Rb_tree<int, BfmeUnsignedKeyTree620C70Value, _STL::_Select1st<BfmeUnsignedKeyTree620C70Value>,
		_STL::less<int>, _STL::allocator<BfmeUnsignedKeyTree620C70Value> > Tree;
	Tree m_tree;
};

bool BfmeUnsignedKeyTree620C70::contains(unsigned int key)
{
	Tree::iterator it = m_tree.find(*(const int *)&key);
	return it != m_tree.end();
}
